// A Bison parser, made by GNU Bison 3.7.5.

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
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

  /*---------------.
  | symbol kinds.  |
  `---------------*/



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
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 291 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 291 "dhcp6_parser.yy"
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
  Dhcp6Parser::yypop_ (int n)
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
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue)
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
#line 300 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 301 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 302 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 303 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 304 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 305 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 306 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 307 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 308 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 309 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 310 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 311 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 312 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 313 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 321 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 322 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 323 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 324 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 325 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 326 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 327 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 330 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 335 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 340 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 346 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 353 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 358 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // $@16: %empty
#line 366 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 936 "dhcp6_parser.cc"
    break;

  case 46: // list_generic: "[" $@16 list_content "]"
#line 369 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 944 "dhcp6_parser.cc"
    break;

  case 49: // not_empty_list: value
#line 377 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 953 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list "," value
#line 381 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 962 "dhcp6_parser.cc"
    break;

  case 51: // $@17: %empty
#line 388 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // list_strings: "[" $@17 list_strings_content "]"
#line 390 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 979 "dhcp6_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 399 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 988 "dhcp6_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 403 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 997 "dhcp6_parser.cc"
    break;

  case 57: // unknown_map_entry: "constant string" ":"
#line 414 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1008 "dhcp6_parser.cc"
    break;

  case 58: // $@18: %empty
#line 423 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1019 "dhcp6_parser.cc"
    break;

  case 59: // syntax_map: "{" $@18 global_object "}"
#line 428 "dhcp6_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 60: // $@19: %empty
#line 438 "dhcp6_parser.yy"
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
#line 1047 "dhcp6_parser.cc"
    break;

  case 61: // global_object: "Dhcp6" $@19 ":" "{" global_params "}"
#line 447 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1057 "dhcp6_parser.cc"
    break;

  case 62: // $@20: %empty
#line 455 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1067 "dhcp6_parser.cc"
    break;

  case 63: // sub_dhcp6: "{" $@20 global_params "}"
#line 459 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1076 "dhcp6_parser.cc"
    break;

  case 128: // $@21: %empty
#line 534 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp6_parser.cc"
    break;

  case 129: // data_directory: "data-directory" $@21 ":" "constant string"
#line 537 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1095 "dhcp6_parser.cc"
    break;

  case 130: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 543 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 131: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 549 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 132: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 555 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 133: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 561 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 134: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 567 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 135: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 573 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 136: // renew_timer: "renew-timer" ":" "integer"
#line 579 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 137: // rebind_timer: "rebind-timer" ":" "integer"
#line 585 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 138: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 591 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 139: // t1_percent: "t1-percent" ":" "floating point"
#line 597 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 140: // t2_percent: "t2-percent" ":" "floating point"
#line 603 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 141: // cache_threshold: "cache-threshold" ":" "floating point"
#line 609 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 142: // cache_max_age: "cache-max-age" ":" "integer"
#line 615 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 143: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 621 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 144: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 627 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 145: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 633 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 146: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 639 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 147: // $@22: %empty
#line 645 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1274 "dhcp6_parser.cc"
    break;

  case 148: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 648 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1283 "dhcp6_parser.cc"
    break;

  case 149: // ddns_replace_client_name_value: "when-present"
#line 654 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1291 "dhcp6_parser.cc"
    break;

  case 150: // ddns_replace_client_name_value: "never"
#line 657 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1299 "dhcp6_parser.cc"
    break;

  case 151: // ddns_replace_client_name_value: "always"
#line 660 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1307 "dhcp6_parser.cc"
    break;

  case 152: // ddns_replace_client_name_value: "when-not-present"
#line 663 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1315 "dhcp6_parser.cc"
    break;

  case 153: // ddns_replace_client_name_value: "boolean"
#line 666 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1324 "dhcp6_parser.cc"
    break;

  case 154: // $@23: %empty
#line 672 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1333 "dhcp6_parser.cc"
    break;

  case 155: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 675 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1343 "dhcp6_parser.cc"
    break;

  case 156: // $@24: %empty
#line 681 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1352 "dhcp6_parser.cc"
    break;

  case 157: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 684 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1362 "dhcp6_parser.cc"
    break;

  case 158: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 690 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1372 "dhcp6_parser.cc"
    break;

  case 159: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 696 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1382 "dhcp6_parser.cc"
    break;

  case 160: // $@25: %empty
#line 702 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1391 "dhcp6_parser.cc"
    break;

  case 161: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 705 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1401 "dhcp6_parser.cc"
    break;

  case 162: // $@26: %empty
#line 711 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1410 "dhcp6_parser.cc"
    break;

  case 163: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 714 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1420 "dhcp6_parser.cc"
    break;

  case 164: // store_extended_info: "store-extended-info" ":" "boolean"
#line 720 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1430 "dhcp6_parser.cc"
    break;

  case 165: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 726 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 166: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 732 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 167: // $@27: %empty
#line 738 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1459 "dhcp6_parser.cc"
    break;

  case 168: // server_tag: "server-tag" $@27 ":" "constant string"
#line 741 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1469 "dhcp6_parser.cc"
    break;

  case 169: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 747 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1479 "dhcp6_parser.cc"
    break;

  case 170: // $@28: %empty
#line 753 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1491 "dhcp6_parser.cc"
    break;

  case 171: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 759 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1501 "dhcp6_parser.cc"
    break;

  case 172: // $@29: %empty
#line 765 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 173: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 769 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1520 "dhcp6_parser.cc"
    break;

  case 181: // $@30: %empty
#line 785 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 182: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 791 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 183: // re_detect: "re-detect" ":" "boolean"
#line 796 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1551 "dhcp6_parser.cc"
    break;

  case 184: // $@31: %empty
#line 802 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 185: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 808 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1574 "dhcp6_parser.cc"
    break;

  case 186: // $@32: %empty
#line 815 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1586 "dhcp6_parser.cc"
    break;

  case 187: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 821 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1597 "dhcp6_parser.cc"
    break;

  case 188: // $@33: %empty
#line 828 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1609 "dhcp6_parser.cc"
    break;

  case 189: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 834 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1618 "dhcp6_parser.cc"
    break;

  case 194: // $@34: %empty
#line 847 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1628 "dhcp6_parser.cc"
    break;

  case 195: // database: "{" $@34 database_map_params "}"
#line 851 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 220: // $@35: %empty
#line 885 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1647 "dhcp6_parser.cc"
    break;

  case 221: // database_type: "type" $@35 ":" db_type
#line 888 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1656 "dhcp6_parser.cc"
    break;

  case 222: // db_type: "memfile"
#line 893 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1662 "dhcp6_parser.cc"
    break;

  case 223: // db_type: "mysql"
#line 894 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1668 "dhcp6_parser.cc"
    break;

  case 224: // db_type: "postgresql"
#line 895 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1674 "dhcp6_parser.cc"
    break;

  case 225: // db_type: "cql"
#line 896 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1680 "dhcp6_parser.cc"
    break;

  case 226: // $@36: %empty
#line 899 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 227: // user: "user" $@36 ":" "constant string"
#line 902 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 228: // $@37: %empty
#line 908 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 229: // password: "password" $@37 ":" "constant string"
#line 911 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1718 "dhcp6_parser.cc"
    break;

  case 230: // $@38: %empty
#line 917 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1727 "dhcp6_parser.cc"
    break;

  case 231: // host: "host" $@38 ":" "constant string"
#line 920 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 232: // port: "port" ":" "integer"
#line 926 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 233: // $@39: %empty
#line 932 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1756 "dhcp6_parser.cc"
    break;

  case 234: // name: "name" $@39 ":" "constant string"
#line 935 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1766 "dhcp6_parser.cc"
    break;

  case 235: // persist: "persist" ":" "boolean"
#line 941 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1776 "dhcp6_parser.cc"
    break;

  case 236: // lfc_interval: "lfc-interval" ":" "integer"
#line 947 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1786 "dhcp6_parser.cc"
    break;

  case 237: // readonly: "readonly" ":" "boolean"
#line 953 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1796 "dhcp6_parser.cc"
    break;

  case 238: // connect_timeout: "connect-timeout" ":" "integer"
#line 959 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1806 "dhcp6_parser.cc"
    break;

  case 239: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 965 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1816 "dhcp6_parser.cc"
    break;

  case 240: // $@40: %empty
#line 971 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 241: // on_fail: "on-fail" $@40 ":" on_fail_mode
#line 974 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1834 "dhcp6_parser.cc"
    break;

  case 242: // on_fail_mode: "stop-retry-exit"
#line 979 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1840 "dhcp6_parser.cc"
    break;

  case 243: // on_fail_mode: "serve-retry-exit"
#line 980 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1846 "dhcp6_parser.cc"
    break;

  case 244: // on_fail_mode: "serve-retry-continue"
#line 981 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 1852 "dhcp6_parser.cc"
    break;

  case 245: // max_row_errors: "max-row-errors" ":" "integer"
#line 984 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 246: // request_timeout: "request-timeout" ":" "integer"
#line 990 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1872 "dhcp6_parser.cc"
    break;

  case 247: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 996 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1882 "dhcp6_parser.cc"
    break;

  case 248: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1002 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1892 "dhcp6_parser.cc"
    break;

  case 249: // $@41: %empty
#line 1008 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1901 "dhcp6_parser.cc"
    break;

  case 250: // contact_points: "contact-points" $@41 ":" "constant string"
#line 1011 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1911 "dhcp6_parser.cc"
    break;

  case 251: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1017 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1921 "dhcp6_parser.cc"
    break;

  case 252: // $@42: %empty
#line 1023 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1930 "dhcp6_parser.cc"
    break;

  case 253: // keyspace: "keyspace" $@42 ":" "constant string"
#line 1026 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1940 "dhcp6_parser.cc"
    break;

  case 254: // $@43: %empty
#line 1032 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1949 "dhcp6_parser.cc"
    break;

  case 255: // consistency: "consistency" $@43 ":" "constant string"
#line 1035 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1959 "dhcp6_parser.cc"
    break;

  case 256: // $@44: %empty
#line 1041 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1968 "dhcp6_parser.cc"
    break;

  case 257: // serial_consistency: "serial-consistency" $@44 ":" "constant string"
#line 1044 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1978 "dhcp6_parser.cc"
    break;

  case 258: // $@45: %empty
#line 1050 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1990 "dhcp6_parser.cc"
    break;

  case 259: // sanity_checks: "sanity-checks" $@45 ":" "{" sanity_checks_params "}"
#line 1056 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1999 "dhcp6_parser.cc"
    break;

  case 263: // $@46: %empty
#line 1066 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 264: // lease_checks: "lease-checks" $@46 ":" "constant string"
#line 1069 "dhcp6_parser.yy"
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
#line 2028 "dhcp6_parser.cc"
    break;

  case 265: // $@47: %empty
#line 1085 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2040 "dhcp6_parser.cc"
    break;

  case 266: // mac_sources: "mac-sources" $@47 ":" "[" mac_sources_list "]"
#line 1091 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2049 "dhcp6_parser.cc"
    break;

  case 271: // duid_id: "duid"
#line 1104 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2058 "dhcp6_parser.cc"
    break;

  case 272: // string_id: "constant string"
#line 1109 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 273: // $@48: %empty
#line 1114 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2079 "dhcp6_parser.cc"
    break;

  case 274: // host_reservation_identifiers: "host-reservation-identifiers" $@48 ":" "[" host_reservation_identifiers_list "]"
#line 1120 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2088 "dhcp6_parser.cc"
    break;

  case 280: // hw_address_id: "hw-address"
#line 1134 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2097 "dhcp6_parser.cc"
    break;

  case 281: // flex_id: "flex-id"
#line 1139 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2106 "dhcp6_parser.cc"
    break;

  case 282: // $@49: %empty
#line 1146 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2118 "dhcp6_parser.cc"
    break;

  case 283: // relay_supplied_options: "relay-supplied-options" $@49 ":" "[" list_content "]"
#line 1152 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2127 "dhcp6_parser.cc"
    break;

  case 284: // $@50: %empty
#line 1159 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2139 "dhcp6_parser.cc"
    break;

  case 285: // dhcp_multi_threading: "multi-threading" $@50 ":" "{" multi_threading_params "}"
#line 1165 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2150 "dhcp6_parser.cc"
    break;

  case 294: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1184 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2160 "dhcp6_parser.cc"
    break;

  case 295: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1190 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2170 "dhcp6_parser.cc"
    break;

  case 296: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1196 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2180 "dhcp6_parser.cc"
    break;

  case 297: // $@51: %empty
#line 1202 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 298: // hooks_libraries: "hooks-libraries" $@51 ":" "[" hooks_libraries_list "]"
#line 1208 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 303: // $@52: %empty
#line 1221 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 304: // hooks_library: "{" $@52 hooks_params "}"
#line 1225 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 305: // $@53: %empty
#line 1231 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2231 "dhcp6_parser.cc"
    break;

  case 306: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1235 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2241 "dhcp6_parser.cc"
    break;

  case 312: // $@54: %empty
#line 1250 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2250 "dhcp6_parser.cc"
    break;

  case 313: // library: "library" $@54 ":" "constant string"
#line 1253 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2260 "dhcp6_parser.cc"
    break;

  case 314: // $@55: %empty
#line 1259 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2269 "dhcp6_parser.cc"
    break;

  case 315: // parameters: "parameters" $@55 ":" map_value
#line 1262 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2278 "dhcp6_parser.cc"
    break;

  case 316: // $@56: %empty
#line 1268 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2290 "dhcp6_parser.cc"
    break;

  case 317: // expired_leases_processing: "expired-leases-processing" $@56 ":" "{" expired_leases_params "}"
#line 1274 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2300 "dhcp6_parser.cc"
    break;

  case 326: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1292 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2310 "dhcp6_parser.cc"
    break;

  case 327: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1298 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2320 "dhcp6_parser.cc"
    break;

  case 328: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1304 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2330 "dhcp6_parser.cc"
    break;

  case 329: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1310 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2340 "dhcp6_parser.cc"
    break;

  case 330: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1316 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2350 "dhcp6_parser.cc"
    break;

  case 331: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1322 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2360 "dhcp6_parser.cc"
    break;

  case 332: // $@57: %empty
#line 1331 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2372 "dhcp6_parser.cc"
    break;

  case 333: // subnet6_list: "subnet6" $@57 ":" "[" subnet6_list_content "]"
#line 1337 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2381 "dhcp6_parser.cc"
    break;

  case 338: // $@58: %empty
#line 1357 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2391 "dhcp6_parser.cc"
    break;

  case 339: // subnet6: "{" $@58 subnet6_params "}"
#line 1361 "dhcp6_parser.yy"
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
#line 2417 "dhcp6_parser.cc"
    break;

  case 340: // $@59: %empty
#line 1383 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2427 "dhcp6_parser.cc"
    break;

  case 341: // sub_subnet6: "{" $@59 subnet6_params "}"
#line 1387 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2437 "dhcp6_parser.cc"
    break;

  case 387: // $@60: %empty
#line 1444 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp6_parser.cc"
    break;

  case 388: // subnet: "subnet" $@60 ":" "constant string"
#line 1447 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc"
    break;

  case 389: // $@61: %empty
#line 1453 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2465 "dhcp6_parser.cc"
    break;

  case 390: // interface: "interface" $@61 ":" "constant string"
#line 1456 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2475 "dhcp6_parser.cc"
    break;

  case 391: // $@62: %empty
#line 1462 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2484 "dhcp6_parser.cc"
    break;

  case 392: // interface_id: "interface-id" $@62 ":" "constant string"
#line 1465 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2494 "dhcp6_parser.cc"
    break;

  case 393: // $@63: %empty
#line 1471 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2503 "dhcp6_parser.cc"
    break;

  case 394: // client_class: "client-class" $@63 ":" "constant string"
#line 1474 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2513 "dhcp6_parser.cc"
    break;

  case 395: // $@64: %empty
#line 1480 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 396: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1486 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2534 "dhcp6_parser.cc"
    break;

  case 397: // reservations_global: "reservations-global" ":" "boolean"
#line 1491 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2544 "dhcp6_parser.cc"
    break;

  case 398: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1497 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2554 "dhcp6_parser.cc"
    break;

  case 399: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1503 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2564 "dhcp6_parser.cc"
    break;

  case 400: // $@65: %empty
#line 1509 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2573 "dhcp6_parser.cc"
    break;

  case 401: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1512 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2582 "dhcp6_parser.cc"
    break;

  case 402: // hr_mode: "disabled"
#line 1517 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2588 "dhcp6_parser.cc"
    break;

  case 403: // hr_mode: "out-of-pool"
#line 1518 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2594 "dhcp6_parser.cc"
    break;

  case 404: // hr_mode: "global"
#line 1519 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2600 "dhcp6_parser.cc"
    break;

  case 405: // hr_mode: "all"
#line 1520 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2606 "dhcp6_parser.cc"
    break;

  case 406: // id: "id" ":" "integer"
#line 1523 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2616 "dhcp6_parser.cc"
    break;

  case 407: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1529 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2626 "dhcp6_parser.cc"
    break;

  case 408: // $@66: %empty
#line 1537 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 409: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1543 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2647 "dhcp6_parser.cc"
    break;

  case 414: // $@67: %empty
#line 1558 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2657 "dhcp6_parser.cc"
    break;

  case 415: // shared_network: "{" $@67 shared_network_params "}"
#line 1562 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2665 "dhcp6_parser.cc"
    break;

  case 458: // $@68: %empty
#line 1616 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2677 "dhcp6_parser.cc"
    break;

  case 459: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1622 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2686 "dhcp6_parser.cc"
    break;

  case 460: // $@69: %empty
#line 1630 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2695 "dhcp6_parser.cc"
    break;

  case 461: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1633 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2703 "dhcp6_parser.cc"
    break;

  case 466: // $@70: %empty
#line 1649 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 467: // option_def_entry: "{" $@70 option_def_params "}"
#line 1653 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2725 "dhcp6_parser.cc"
    break;

  case 468: // $@71: %empty
#line 1664 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2735 "dhcp6_parser.cc"
    break;

  case 469: // sub_option_def: "{" $@71 option_def_params "}"
#line 1668 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2747 "dhcp6_parser.cc"
    break;

  case 485: // code: "code" ":" "integer"
#line 1700 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2757 "dhcp6_parser.cc"
    break;

  case 487: // $@72: %empty
#line 1708 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2766 "dhcp6_parser.cc"
    break;

  case 488: // option_def_type: "type" $@72 ":" "constant string"
#line 1711 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 489: // $@73: %empty
#line 1717 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2785 "dhcp6_parser.cc"
    break;

  case 490: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1720 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2795 "dhcp6_parser.cc"
    break;

  case 491: // $@74: %empty
#line 1726 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 492: // space: "space" $@74 ":" "constant string"
#line 1729 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2814 "dhcp6_parser.cc"
    break;

  case 494: // $@75: %empty
#line 1737 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2823 "dhcp6_parser.cc"
    break;

  case 495: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1740 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2833 "dhcp6_parser.cc"
    break;

  case 496: // option_def_array: "array" ":" "boolean"
#line 1746 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2843 "dhcp6_parser.cc"
    break;

  case 497: // $@76: %empty
#line 1756 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2855 "dhcp6_parser.cc"
    break;

  case 498: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1762 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2864 "dhcp6_parser.cc"
    break;

  case 503: // $@77: %empty
#line 1781 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2874 "dhcp6_parser.cc"
    break;

  case 504: // option_data_entry: "{" $@77 option_data_params "}"
#line 1785 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2883 "dhcp6_parser.cc"
    break;

  case 505: // $@78: %empty
#line 1793 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2893 "dhcp6_parser.cc"
    break;

  case 506: // sub_option_data: "{" $@78 option_data_params "}"
#line 1797 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2902 "dhcp6_parser.cc"
    break;

  case 521: // $@79: %empty
#line 1830 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2911 "dhcp6_parser.cc"
    break;

  case 522: // option_data_data: "data" $@79 ":" "constant string"
#line 1833 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 525: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1843 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2931 "dhcp6_parser.cc"
    break;

  case 526: // option_data_always_send: "always-send" ":" "boolean"
#line 1849 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2941 "dhcp6_parser.cc"
    break;

  case 527: // $@80: %empty
#line 1858 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2953 "dhcp6_parser.cc"
    break;

  case 528: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1864 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 533: // $@81: %empty
#line 1879 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2972 "dhcp6_parser.cc"
    break;

  case 534: // pool_list_entry: "{" $@81 pool_params "}"
#line 1883 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2982 "dhcp6_parser.cc"
    break;

  case 535: // $@82: %empty
#line 1889 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2992 "dhcp6_parser.cc"
    break;

  case 536: // sub_pool6: "{" $@82 pool_params "}"
#line 1893 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3002 "dhcp6_parser.cc"
    break;

  case 546: // $@83: %empty
#line 1912 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp6_parser.cc"
    break;

  case 547: // pool_entry: "pool" $@83 ":" "constant string"
#line 1915 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3021 "dhcp6_parser.cc"
    break;

  case 548: // $@84: %empty
#line 1921 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3029 "dhcp6_parser.cc"
    break;

  case 549: // user_context: "user-context" $@84 ":" map_value
#line 1923 "dhcp6_parser.yy"
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
#line 3056 "dhcp6_parser.cc"
    break;

  case 550: // $@85: %empty
#line 1946 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 551: // comment: "comment" $@85 ":" "constant string"
#line 1948 "dhcp6_parser.yy"
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
#line 3093 "dhcp6_parser.cc"
    break;

  case 552: // $@86: %empty
#line 1976 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3105 "dhcp6_parser.cc"
    break;

  case 553: // pd_pools_list: "pd-pools" $@86 ":" "[" pd_pools_list_content "]"
#line 1982 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3114 "dhcp6_parser.cc"
    break;

  case 558: // $@87: %empty
#line 1997 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3124 "dhcp6_parser.cc"
    break;

  case 559: // pd_pool_entry: "{" $@87 pd_pool_params "}"
#line 2001 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3136 "dhcp6_parser.cc"
    break;

  case 560: // $@88: %empty
#line 2009 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3146 "dhcp6_parser.cc"
    break;

  case 561: // sub_pd_pool: "{" $@88 pd_pool_params "}"
#line 2013 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3158 "dhcp6_parser.cc"
    break;

  case 575: // $@89: %empty
#line 2038 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3167 "dhcp6_parser.cc"
    break;

  case 576: // pd_prefix: "prefix" $@89 ":" "constant string"
#line 2041 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3177 "dhcp6_parser.cc"
    break;

  case 577: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2047 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3187 "dhcp6_parser.cc"
    break;

  case 578: // $@90: %empty
#line 2053 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3196 "dhcp6_parser.cc"
    break;

  case 579: // excluded_prefix: "excluded-prefix" $@90 ":" "constant string"
#line 2056 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3206 "dhcp6_parser.cc"
    break;

  case 580: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2062 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3216 "dhcp6_parser.cc"
    break;

  case 581: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2068 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3226 "dhcp6_parser.cc"
    break;

  case 582: // $@91: %empty
#line 2077 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3238 "dhcp6_parser.cc"
    break;

  case 583: // reservations: "reservations" $@91 ":" "[" reservations_list "]"
#line 2083 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3247 "dhcp6_parser.cc"
    break;

  case 588: // $@92: %empty
#line 2096 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 589: // reservation: "{" $@92 reservation_params "}"
#line 2100 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 590: // $@93: %empty
#line 2105 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 591: // sub_reservation: "{" $@93 reservation_params "}"
#line 2109 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3285 "dhcp6_parser.cc"
    break;

  case 607: // $@94: %empty
#line 2136 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3297 "dhcp6_parser.cc"
    break;

  case 608: // ip_addresses: "ip-addresses" $@94 ":" list_strings
#line 2142 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3306 "dhcp6_parser.cc"
    break;

  case 609: // $@95: %empty
#line 2147 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp6_parser.cc"
    break;

  case 610: // prefixes: "prefixes" $@95 ":" list_strings
#line 2153 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3327 "dhcp6_parser.cc"
    break;

  case 611: // $@96: %empty
#line 2158 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3336 "dhcp6_parser.cc"
    break;

  case 612: // duid: "duid" $@96 ":" "constant string"
#line 2161 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3346 "dhcp6_parser.cc"
    break;

  case 613: // $@97: %empty
#line 2167 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3355 "dhcp6_parser.cc"
    break;

  case 614: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2170 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3365 "dhcp6_parser.cc"
    break;

  case 615: // $@98: %empty
#line 2176 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3374 "dhcp6_parser.cc"
    break;

  case 616: // hostname: "hostname" $@98 ":" "constant string"
#line 2179 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 617: // $@99: %empty
#line 2185 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3393 "dhcp6_parser.cc"
    break;

  case 618: // flex_id_value: "flex-id" $@99 ":" "constant string"
#line 2188 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3403 "dhcp6_parser.cc"
    break;

  case 619: // $@100: %empty
#line 2194 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3415 "dhcp6_parser.cc"
    break;

  case 620: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2200 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3424 "dhcp6_parser.cc"
    break;

  case 621: // $@101: %empty
#line 2208 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3436 "dhcp6_parser.cc"
    break;

  case 622: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2214 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3445 "dhcp6_parser.cc"
    break;

  case 625: // $@102: %empty
#line 2223 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3454 "dhcp6_parser.cc"
    break;

  case 626: // ip_address: "ip-address" $@102 ":" "constant string"
#line 2226 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3464 "dhcp6_parser.cc"
    break;

  case 627: // $@103: %empty
#line 2235 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3476 "dhcp6_parser.cc"
    break;

  case 628: // client_classes: "client-classes" $@103 ":" "[" client_classes_list "]"
#line 2241 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3485 "dhcp6_parser.cc"
    break;

  case 631: // $@104: %empty
#line 2250 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3495 "dhcp6_parser.cc"
    break;

  case 632: // client_class_entry: "{" $@104 client_class_params "}"
#line 2254 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3505 "dhcp6_parser.cc"
    break;

  case 645: // $@105: %empty
#line 2279 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3514 "dhcp6_parser.cc"
    break;

  case 646: // client_class_test: "test" $@105 ":" "constant string"
#line 2282 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3524 "dhcp6_parser.cc"
    break;

  case 647: // only_if_required: "only-if-required" ":" "boolean"
#line 2288 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3534 "dhcp6_parser.cc"
    break;

  case 648: // $@106: %empty
#line 2297 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3546 "dhcp6_parser.cc"
    break;

  case 649: // server_id: "server-id" $@106 ":" "{" server_id_params "}"
#line 2303 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3557 "dhcp6_parser.cc"
    break;

  case 661: // $@107: %empty
#line 2325 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3566 "dhcp6_parser.cc"
    break;

  case 662: // server_id_type: "type" $@107 ":" duid_type
#line 2328 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3575 "dhcp6_parser.cc"
    break;

  case 663: // duid_type: "LLT"
#line 2333 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3581 "dhcp6_parser.cc"
    break;

  case 664: // duid_type: "EN"
#line 2334 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3587 "dhcp6_parser.cc"
    break;

  case 665: // duid_type: "LL"
#line 2335 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3593 "dhcp6_parser.cc"
    break;

  case 666: // htype: "htype" ":" "integer"
#line 2338 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3603 "dhcp6_parser.cc"
    break;

  case 667: // $@108: %empty
#line 2344 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3612 "dhcp6_parser.cc"
    break;

  case 668: // identifier: "identifier" $@108 ":" "constant string"
#line 2347 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3622 "dhcp6_parser.cc"
    break;

  case 669: // time: "time" ":" "integer"
#line 2353 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3632 "dhcp6_parser.cc"
    break;

  case 670: // enterprise_id: "enterprise-id" ":" "integer"
#line 2359 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 671: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2367 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 672: // $@109: %empty
#line 2375 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3664 "dhcp6_parser.cc"
    break;

  case 673: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2381 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3673 "dhcp6_parser.cc"
    break;

  case 681: // $@110: %empty
#line 2397 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3682 "dhcp6_parser.cc"
    break;

  case 682: // socket_type: "socket-type" $@110 ":" "constant string"
#line 2400 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3692 "dhcp6_parser.cc"
    break;

  case 683: // $@111: %empty
#line 2406 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3701 "dhcp6_parser.cc"
    break;

  case 684: // socket_name: "socket-name" $@111 ":" "constant string"
#line 2409 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3711 "dhcp6_parser.cc"
    break;

  case 685: // $@112: %empty
#line 2418 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3723 "dhcp6_parser.cc"
    break;

  case 686: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2424 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3734 "dhcp6_parser.cc"
    break;

  case 695: // enable_queue: "enable-queue" ":" "boolean"
#line 2443 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3744 "dhcp6_parser.cc"
    break;

  case 696: // $@113: %empty
#line 2449 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3753 "dhcp6_parser.cc"
    break;

  case 697: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2452 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3763 "dhcp6_parser.cc"
    break;

  case 698: // capacity: "capacity" ":" "integer"
#line 2458 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3773 "dhcp6_parser.cc"
    break;

  case 699: // $@114: %empty
#line 2464 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3782 "dhcp6_parser.cc"
    break;

  case 700: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2467 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3791 "dhcp6_parser.cc"
    break;

  case 701: // $@115: %empty
#line 2474 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3803 "dhcp6_parser.cc"
    break;

  case 702: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2480 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 703: // $@116: %empty
#line 2487 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 704: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2491 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 725: // enable_updates: "enable-updates" ":" "boolean"
#line 2521 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3844 "dhcp6_parser.cc"
    break;

  case 726: // $@117: %empty
#line 2528 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3853 "dhcp6_parser.cc"
    break;

  case 727: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2531 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 728: // $@118: %empty
#line 2537 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp6_parser.cc"
    break;

  case 729: // server_ip: "server-ip" $@118 ":" "constant string"
#line 2540 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3882 "dhcp6_parser.cc"
    break;

  case 730: // server_port: "server-port" ":" "integer"
#line 2546 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 731: // $@119: %empty
#line 2552 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3901 "dhcp6_parser.cc"
    break;

  case 732: // sender_ip: "sender-ip" $@119 ":" "constant string"
#line 2555 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 733: // sender_port: "sender-port" ":" "integer"
#line 2561 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3921 "dhcp6_parser.cc"
    break;

  case 734: // max_queue_size: "max-queue-size" ":" "integer"
#line 2567 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3931 "dhcp6_parser.cc"
    break;

  case 735: // $@120: %empty
#line 2573 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3940 "dhcp6_parser.cc"
    break;

  case 736: // ncr_protocol: "ncr-protocol" $@120 ":" ncr_protocol_value
#line 2576 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3949 "dhcp6_parser.cc"
    break;

  case 737: // ncr_protocol_value: "UDP"
#line 2582 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3955 "dhcp6_parser.cc"
    break;

  case 738: // ncr_protocol_value: "TCP"
#line 2583 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3961 "dhcp6_parser.cc"
    break;

  case 739: // $@121: %empty
#line 2586 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3970 "dhcp6_parser.cc"
    break;

  case 740: // ncr_format: "ncr-format" $@121 ":" "JSON"
#line 2589 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3980 "dhcp6_parser.cc"
    break;

  case 741: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2596 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3990 "dhcp6_parser.cc"
    break;

  case 742: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2603 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 743: // $@122: %empty
#line 2610 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4009 "dhcp6_parser.cc"
    break;

  case 744: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2613 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4018 "dhcp6_parser.cc"
    break;

  case 745: // $@123: %empty
#line 2619 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4027 "dhcp6_parser.cc"
    break;

  case 746: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2622 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4037 "dhcp6_parser.cc"
    break;

  case 747: // $@124: %empty
#line 2629 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4046 "dhcp6_parser.cc"
    break;

  case 748: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2632 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4056 "dhcp6_parser.cc"
    break;

  case 749: // $@125: %empty
#line 2639 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4065 "dhcp6_parser.cc"
    break;

  case 750: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2642 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4075 "dhcp6_parser.cc"
    break;

  case 751: // $@126: %empty
#line 2651 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4087 "dhcp6_parser.cc"
    break;

  case 752: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2657 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4097 "dhcp6_parser.cc"
    break;

  case 753: // $@127: %empty
#line 2663 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4107 "dhcp6_parser.cc"
    break;

  case 754: // sub_config_control: "{" $@127 config_control_params "}"
#line 2667 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4116 "dhcp6_parser.cc"
    break;

  case 759: // $@128: %empty
#line 2682 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4128 "dhcp6_parser.cc"
    break;

  case 760: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2688 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 761: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2693 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 762: // $@129: %empty
#line 2701 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4159 "dhcp6_parser.cc"
    break;

  case 763: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2707 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4168 "dhcp6_parser.cc"
    break;

  case 766: // $@130: %empty
#line 2719 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4178 "dhcp6_parser.cc"
    break;

  case 767: // logger_entry: "{" $@130 logger_params "}"
#line 2723 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 777: // debuglevel: "debuglevel" ":" "integer"
#line 2740 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4196 "dhcp6_parser.cc"
    break;

  case 778: // $@131: %empty
#line 2746 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4205 "dhcp6_parser.cc"
    break;

  case 779: // severity: "severity" $@131 ":" "constant string"
#line 2749 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4215 "dhcp6_parser.cc"
    break;

  case 780: // $@132: %empty
#line 2755 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4227 "dhcp6_parser.cc"
    break;

  case 781: // output_options_list: "output_options" $@132 ":" "[" output_options_list_content "]"
#line 2761 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4236 "dhcp6_parser.cc"
    break;

  case 784: // $@133: %empty
#line 2770 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4246 "dhcp6_parser.cc"
    break;

  case 785: // output_entry: "{" $@133 output_params_list "}"
#line 2774 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4254 "dhcp6_parser.cc"
    break;

  case 793: // $@134: %empty
#line 2789 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 794: // output: "output" $@134 ":" "constant string"
#line 2792 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4273 "dhcp6_parser.cc"
    break;

  case 795: // flush: "flush" ":" "boolean"
#line 2798 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4283 "dhcp6_parser.cc"
    break;

  case 796: // maxsize: "maxsize" ":" "integer"
#line 2804 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4293 "dhcp6_parser.cc"
    break;

  case 797: // maxver: "maxver" ":" "integer"
#line 2810 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4303 "dhcp6_parser.cc"
    break;

  case 798: // $@135: %empty
#line 2816 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4312 "dhcp6_parser.cc"
    break;

  case 799: // pattern: "pattern" $@135 ":" "constant string"
#line 2819 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4322 "dhcp6_parser.cc"
    break;

  case 800: // $@136: %empty
#line 2825 "dhcp6_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4334 "dhcp6_parser.cc"
    break;

  case 801: // compatibility: "compatibility" $@136 ":" "{" compatibility_params "}"
#line 2831 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4343 "dhcp6_parser.cc"
    break;

  case 806: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2844 "dhcp6_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4353 "dhcp6_parser.cc"
    break;


#line 4357 "dhcp6_parser.cc"

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

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
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


  const short Dhcp6Parser::yypact_ninf_ = -977;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     407,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,    48,    30,    31,    83,    97,
     101,   107,   115,   117,   125,   137,   149,   159,   175,   220,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,    30,  -149,
      60,   140,    66,   641,   187,   284,    24,   162,    88,   286,
     -78,   419,   156,  -977,    59,   251,   252,   256,   264,  -977,
     269,  -977,  -977,  -977,  -977,  -977,  -977,   274,   287,   297,
     300,   310,   311,   320,   327,   342,   343,   357,   358,   369,
     379,  -977,   380,   386,   398,   400,   401,  -977,  -977,  -977,
     402,   413,   429,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
     437,   438,   439,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,   443,  -977,  -977,  -977,  -977,  -977,  -977,   445,
    -977,  -977,   447,  -977,    91,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,   455,  -977,
     113,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,   457,   459,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,   173,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,   225,  -977,  -977,  -977,
    -977,  -977,   461,  -977,   462,   463,  -977,  -977,  -977,  -977,
    -977,  -977,   262,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
     282,   291,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
     305,  -977,  -977,   467,  -977,  -977,  -977,   468,  -977,  -977,
     408,   423,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,   469,   473,  -977,  -977,  -977,
    -977,   428,   480,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,   263,  -977,  -977,  -977,   483,
    -977,  -977,   484,  -977,   487,   493,  -977,  -977,   494,   495,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,   265,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,   496,   277,  -977,  -977,  -977,
    -977,    30,    30,  -977,   276,   498,  -977,   500,   502,   503,
     506,   507,   513,   313,   317,   321,   323,   324,   326,   331,
     332,   307,   334,   336,   337,   341,   344,   516,   345,   347,
     340,   351,   353,   527,   530,   532,   354,   355,   359,   548,
     554,   564,   565,   568,   569,   570,   364,   365,   366,   588,
     589,   590,   591,   592,   593,   594,   611,   612,   409,   613,
     615,   616,   617,   618,   619,   414,   620,   624,  -977,   140,
    -977,   626,   425,    66,  -977,   627,   628,   629,   630,   631,
     430,   426,   634,   636,   637,   641,  -977,   638,   187,  -977,
     639,   435,   642,   440,   441,   284,  -977,   643,   644,   647,
     648,   649,   650,   651,  -977,    24,  -977,   652,   653,   449,
     655,   656,   657,   454,  -977,    88,   663,   458,   460,  -977,
     286,   664,   668,    23,  -977,   464,   669,   670,   474,   672,
     475,   476,   673,   683,   491,   492,   700,   701,   711,   712,
     419,  -977,   714,   510,   156,  -977,  -977,  -977,   716,   719,
     519,   722,   724,   725,   726,   729,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
     536,  -977,  -977,  -977,  -977,  -977,   -36,   537,   538,  -977,
    -977,  -977,   730,   742,   746,   747,   748,   545,   266,  -977,
    -977,  -977,   749,   751,   753,   752,   757,   758,   759,   760,
     762,  -977,   763,   764,   765,   766,   557,   558,  -977,   769,
     768,  -977,   771,  -977,  -977,   772,   773,   571,   572,   573,
    -977,  -977,   771,   574,   776,  -977,   576,  -977,   577,  -977,
     578,  -977,  -977,  -977,   771,   771,   771,   595,   606,   609,
     610,  -977,   621,   622,  -977,   623,   625,   635,  -977,  -977,
     645,  -977,  -977,  -977,   646,   748,  -977,  -977,   654,   659,
    -977,   660,  -977,  -977,    12,   661,  -977,  -977,   -36,   662,
     665,   666,  -977,   795,  -977,  -977,    30,   140,  -977,   156,
      66,   308,   308,   794,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,   812,   813,   816,   817,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,   -82,    30,    10,   688,   818,
     819,   820,    87,   213,    68,   -51,   231,   419,  -977,  -977,
     821,  -136,  -977,  -977,   825,   832,  -977,  -977,  -977,  -977,
    -977,   -70,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,   794,  -977,   278,   281,   290,  -977,  -977,  -977,  -977,
     838,   840,   841,   846,   847,  -977,   848,   852,  -977,  -977,
    -977,  -977,   853,   855,   856,   857,  -977,   294,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
     302,  -977,   858,   860,  -977,  -977,   859,   866,  -977,  -977,
     865,   869,  -977,  -977,   870,   872,  -977,  -977,   871,   875,
    -977,  -977,  -977,    65,  -977,  -977,  -977,   873,  -977,  -977,
    -977,    78,  -977,  -977,  -977,  -977,   309,  -977,  -977,  -977,
      85,  -977,  -977,   874,   878,  -977,  -977,   876,   880,  -977,
     881,   882,   883,   884,   885,   886,   322,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,   887,   888,   889,  -977,
    -977,  -977,  -977,   325,  -977,  -977,  -977,  -977,  -977,  -977,
     890,   891,   892,  -977,   383,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,   389,  -977,  -977,  -977,
     893,  -977,   894,  -977,  -977,  -977,   390,  -977,  -977,  -977,
    -977,  -977,   391,  -977,    95,  -977,   895,  -977,   393,  -977,
    -977,   676,  -977,   896,   897,  -977,  -977,   898,   900,  -977,
    -977,  -977,   899,  -977,   902,  -977,  -977,  -977,   901,   905,
     906,   907,   692,   695,   703,   702,   705,   911,   707,   708,
     914,   917,   918,   920,   718,   721,   717,   732,   308,  -977,
    -977,   308,  -977,   794,   641,  -977,   812,    88,  -977,   813,
     286,  -977,   816,   739,  -977,   817,   -82,  -977,  -977,    10,
    -977,   921,   688,  -977,   -21,   818,  -977,    24,  -977,   819,
     -78,  -977,   820,   741,   744,   745,   770,   780,   784,    87,
    -977,   927,   929,   785,   792,   803,   213,  -977,   723,   806,
     808,    68,  -977,   934,   952,   -51,  -977,   767,  1000,   811,
    1026,   231,  -977,  -977,   223,   821,  -977,   834,  -136,  -977,
    -977,  1054,  1059,   187,  -977,   825,   284,  -977,   832,  1060,
    -977,  -977,   433,   861,   863,   864,  -977,  -977,  -977,  -977,
    -977,   867,  -977,  -977,   191,   868,   877,   879,  -977,  -977,
    -977,  -977,  -977,   405,  -977,   411,  -977,  1055,  -977,  1065,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,   412,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,   903,  -977,  -977,  1064,
    -977,  -977,  -977,  -977,  -977,  1066,  1074,  -977,  -977,  -977,
    -977,  -977,  1070,  -977,   420,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,   104,   904,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,   908,   909,  -977,  -977,   910,  -977,    30,
    -977,  -977,  1075,  -977,  -977,  -977,  -977,  -977,   421,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,   912,   422,  -977,
     424,  -977,   913,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,   739,  -977,  -977,  1076,   916,  -977,   -21,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  1077,   915,  1078,   223,  -977,  -977,  -977,  -977,  -977,
    -977,   922,  -977,  -977,  1079,  -977,   923,  -977,  -977,  1081,
    -977,  -977,   109,  -977,   -11,  1081,  -977,  -977,  1082,  1085,
    1086,  -977,   432,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    1087,   924,   919,   925,  1088,   -11,  -977,   928,  -977,  -977,
    -977,   930,  -977,  -977,  -977
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   172,     9,   340,    11,
     535,    13,   560,    15,   590,    17,   460,    19,   468,    21,
     505,    23,   305,    25,   703,    27,   753,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   592,     0,   470,   507,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   128,   751,   170,   184,   186,   188,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   167,     0,     0,     0,     0,     0,   147,   154,   156,
       0,     0,     0,   332,   458,   497,   408,   548,   550,   400,
       0,     0,     0,   265,   282,   273,   258,   627,   582,   297,
     316,   648,     0,   284,   672,   685,   701,   160,   162,     0,
     762,   800,     0,   127,     0,    64,    66,    67,    68,    69,
      70,    71,    72,    73,    74,   105,   106,   107,   108,   109,
      75,   113,   114,   115,   116,   117,   118,   119,   120,   111,
     112,   121,   122,   123,   100,   125,    78,    79,    80,    81,
      97,    82,    84,    83,   124,    88,    89,    76,   102,   103,
     104,   101,    77,    86,    87,    95,    96,    98,    85,    90,
      91,    92,    93,    94,    99,   110,   126,   181,     0,   180,
       0,   174,   176,   177,   178,   179,   527,   552,   387,   389,
     391,     0,     0,   395,   393,   621,   386,   344,   345,   346,
     347,   348,   349,   350,   351,   370,   371,   372,   373,   374,
     377,   378,   379,   380,   381,   382,   383,   384,   375,   376,
     385,     0,   342,   355,   356,   357,   360,   361,   364,   365,
     366,   363,   358,   359,   352,   353,   368,   369,   354,   362,
     367,   546,   545,   541,   542,   540,     0,   537,   539,   543,
     544,   575,     0,   578,     0,     0,   574,   568,   569,   567,
     572,   573,     0,   562,   564,   565,   570,   571,   566,   619,
     607,   609,   611,   613,   615,   617,   606,   603,   604,   605,
       0,   593,   594,   598,   599,   596,   600,   601,   602,   597,
       0,   487,   233,     0,   491,   489,   494,     0,   483,   484,
       0,   471,   472,   474,   486,   475,   476,   477,   493,   478,
     479,   480,   481,   482,   521,     0,     0,   519,   520,   523,
     524,     0,   508,   509,   511,   512,   513,   514,   515,   516,
     517,   518,   312,   314,   309,     0,   307,   310,   311,     0,
     726,   728,     0,   731,     0,     0,   735,   739,     0,     0,
     743,   745,   747,   749,   724,   722,   723,     0,   705,   707,
     719,   708,   709,   710,   711,   712,   713,   714,   715,   716,
     717,   718,   720,   721,   759,     0,     0,   755,   757,   758,
      46,     0,     0,    39,     0,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    57,     0,
      63,     0,     0,     0,   173,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   341,     0,     0,   536,
       0,     0,     0,     0,     0,     0,   561,     0,     0,     0,
       0,     0,     0,     0,   591,     0,   461,     0,     0,     0,
       0,     0,     0,     0,   469,     0,     0,     0,     0,   506,
       0,     0,     0,     0,   306,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   704,     0,     0,     0,   754,    50,    43,     0,     0,
       0,     0,     0,     0,     0,     0,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
       0,   165,   166,   144,   145,   146,     0,     0,     0,   158,
     159,   164,     0,     0,     0,     0,     0,     0,     0,   397,
     398,   399,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   671,     0,     0,     0,     0,     0,     0,   169,     0,
       0,    65,     0,   183,   175,     0,     0,     0,     0,     0,
     406,   407,     0,     0,     0,   343,     0,   538,     0,   577,
       0,   580,   581,   563,     0,     0,     0,     0,     0,     0,
       0,   595,     0,     0,   485,     0,     0,     0,   496,   473,
       0,   525,   526,   510,     0,     0,   308,   725,     0,     0,
     730,     0,   733,   734,     0,     0,   741,   742,     0,     0,
       0,     0,   706,     0,   761,   756,     0,     0,   129,     0,
       0,     0,     0,   190,   168,   149,   150,   151,   152,   153,
     148,   155,   157,   334,   462,   499,   410,    40,   549,   551,
     402,   403,   404,   405,   401,     0,    47,     0,     0,     0,
     584,   299,     0,     0,     0,     0,     0,     0,   161,   163,
       0,     0,    51,   182,   529,   554,   388,   390,   392,   396,
     394,     0,   547,   576,   579,   620,   608,   610,   612,   614,
     616,   618,   488,   234,   492,   490,   495,   522,   313,   315,
     727,   729,   732,   737,   738,   736,   740,   744,   746,   748,
     750,   190,    44,     0,     0,     0,   220,   226,   228,   230,
       0,     0,     0,     0,     0,   249,     0,     0,   240,   252,
     254,   256,     0,     0,     0,     0,   219,     0,   196,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   210,
     211,   218,   212,   213,   214,   208,   209,   215,   216,   217,
       0,   194,     0,   191,   192,   338,     0,   335,   336,   466,
       0,   463,   464,   503,     0,   500,   501,   414,     0,   411,
     412,   271,   272,     0,   267,   269,   270,     0,   280,   281,
     277,     0,   275,   278,   279,   263,     0,   260,   262,   631,
       0,   629,   588,     0,   585,   586,   303,     0,   300,   301,
       0,     0,     0,     0,     0,     0,     0,   318,   320,   321,
     322,   323,   324,   325,   661,   667,     0,     0,     0,   660,
     657,   658,   659,     0,   650,   652,   655,   653,   654,   656,
       0,     0,     0,   293,     0,   286,   288,   289,   290,   291,
     292,   681,   683,   680,   678,   679,     0,   674,   676,   677,
       0,   696,     0,   699,   692,   693,     0,   687,   689,   690,
     691,   694,     0,   766,     0,   764,     0,   805,     0,   802,
     804,    53,   533,     0,   530,   531,   558,     0,   555,   556,
     625,   624,     0,   623,     0,    61,   752,   171,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   185,
     187,     0,   189,     0,     0,   333,     0,   470,   459,     0,
     507,   498,     0,     0,   409,     0,     0,   266,   283,     0,
     274,     0,     0,   259,   633,     0,   628,   592,   583,     0,
       0,   298,     0,     0,     0,     0,     0,     0,     0,     0,
     317,     0,     0,     0,     0,     0,     0,   649,     0,     0,
       0,     0,   285,     0,     0,     0,   673,     0,     0,     0,
       0,     0,   686,   702,     0,     0,   763,     0,     0,   801,
      55,     0,    54,     0,   528,     0,     0,   553,     0,     0,
     622,   760,     0,     0,     0,     0,   232,   235,   236,   237,
     238,     0,   251,   239,     0,     0,     0,     0,   246,   247,
     248,   245,   197,     0,   193,     0,   337,     0,   465,     0,
     502,   457,   432,   433,   434,   436,   437,   438,   422,   423,
     441,   442,   443,   444,   445,   448,   449,   450,   451,   452,
     453,   454,   455,   446,   447,   456,   418,   419,   420,   421,
     430,   431,   427,   428,   429,   426,   435,     0,   416,   424,
     439,   440,   425,   413,   268,   276,     0,   261,   645,     0,
     643,   644,   640,   641,   642,     0,   634,   635,   637,   638,
     639,   630,     0,   587,     0,   302,   326,   327,   328,   329,
     330,   331,   319,     0,     0,   666,   669,   670,   651,   294,
     295,   296,   287,     0,     0,   675,   695,     0,   698,     0,
     688,   780,     0,   778,   776,   770,   774,   775,     0,   768,
     772,   773,   771,   765,   806,   803,    52,     0,     0,   532,
       0,   557,     0,   222,   223,   224,   225,   221,   227,   229,
     231,   250,   242,   243,   244,   241,   253,   255,   257,   195,
     339,   467,   504,     0,   415,   264,     0,     0,   632,     0,
     589,   304,   663,   664,   665,   662,   668,   682,   684,   697,
     700,     0,     0,     0,     0,   767,    56,   534,   559,   626,
     417,     0,   647,   636,     0,   777,     0,   769,   646,     0,
     779,   784,     0,   782,     0,     0,   781,   793,     0,     0,
       0,   798,     0,   786,   788,   789,   790,   791,   792,   783,
       0,     0,     0,     0,     0,     0,   785,     0,   795,   796,
     797,     0,   787,   794,   799
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,   -10,  -977,  -557,  -977,
     418,  -977,  -977,  -977,  -977,   368,  -977,  -569,  -977,  -977,
    -977,   -71,  -977,  -977,  -977,  -977,  -977,  -977,   399,   608,
    -977,  -977,   -59,   -43,   -37,   -31,   -30,   -27,   -26,   -23,
     -19,     3,    16,    19,    20,  -977,    22,    32,    33,    34,
    -977,   395,    37,  -977,    38,  -977,    40,    44,    50,  -977,
      52,  -977,    54,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,   403,   602,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,   318,  -977,   105,  -977,  -680,   112,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,   -45,
    -977,  -720,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,    89,  -977,  -977,  -977,  -977,
    -977,    96,  -702,  -977,  -977,  -977,  -977,    98,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,    64,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,    82,  -977,  -977,  -977,    86,   566,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,    79,  -977,  -977,  -977,
    -977,  -977,  -977,  -976,  -977,  -977,  -977,   114,  -977,  -977,
    -977,   119,   614,  -977,  -977,  -975,  -977,  -974,  -977,   -63,
    -977,    63,  -977,    55,    56,    58,    62,  -977,  -977,  -977,
    -972,  -977,  -977,  -977,  -977,   110,  -977,  -977,  -119,  1045,
    -977,  -977,  -977,  -977,  -977,   124,  -977,  -977,  -977,   128,
    -977,   597,  -977,   -64,  -977,  -977,  -977,  -977,  -977,   -39,
    -977,  -977,  -977,  -977,  -977,     4,  -977,  -977,  -977,   131,
    -977,  -977,  -977,   139,  -977,   600,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,    72,  -977,  -977,
    -977,    80,   633,  -977,  -977,   -55,  -977,   -12,  -977,  -977,
    -977,  -977,  -977,    74,  -977,  -977,  -977,    81,   640,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,   -57,  -977,  -977,  -977,
     126,  -977,  -977,  -977,   127,  -977,   632,   397,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -971,  -977,  -977,  -977,  -977,  -977,  -977,  -977,   134,
    -977,  -977,  -977,   -93,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,   116,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,   106,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,    99,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,   416,   596,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,   465,   599,  -977,  -977,  -977,  -977,
    -977,  -977,   103,  -977,  -977,  -100,  -977,  -977,  -977,  -977,
    -977,  -977,  -116,  -977,  -977,  -135,  -977,  -977,  -977,  -977,
    -977,  -977,  -977,  -977,  -977,  -977,   108,  -977
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     718,    87,    88,    41,    68,    84,    85,   743,   951,  1061,
    1062,   806,    43,    70,    90,   425,    45,    71,   154,   155,
     156,   427,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     453,   710,   175,   454,   176,   455,   177,   178,   179,   483,
     180,   484,   181,   182,   183,   184,   447,   185,   186,   429,
      47,    72,   220,   221,   222,   491,   223,   187,   430,   188,
     431,   189,   432,   832,   833,   834,   991,   807,   808,   809,
     968,  1217,   810,   969,   811,   970,   812,   971,   813,   814,
     528,   815,   816,   817,   818,   819,   820,   980,  1225,   821,
     822,   823,   824,   825,   977,   826,   827,   981,   828,   982,
     829,   983,   190,   472,   866,   867,   868,  1011,   191,   469,
     853,   854,   855,   856,   192,   471,   861,   862,   863,   864,
     193,   470,   194,   479,   914,   915,   916,   917,   918,   195,
     475,   877,   878,   879,  1020,    63,    80,   375,   376,   377,
     541,   378,   542,   196,   476,   886,   887,   888,   889,   890,
     891,   892,   893,   197,   459,   836,   837,   838,   994,    49,
      73,   261,   262,   263,   497,   264,   498,   265,   499,   266,
     503,   267,   502,   198,   199,   200,   201,   465,   724,   272,
     273,   202,   462,   848,   849,   850,  1003,  1137,  1138,   203,
     460,    57,    77,   840,   841,   842,   997,    59,    78,   340,
     341,   342,   343,   344,   345,   346,   527,   347,   531,   348,
     530,   349,   350,   532,   351,   204,   461,   844,   845,   846,
    1000,    61,    79,   361,   362,   363,   364,   365,   536,   366,
     367,   368,   369,   275,   495,   953,   954,   955,  1063,    51,
      74,   286,   287,   288,   507,   205,   463,   206,   464,   278,
     496,   957,   958,   959,  1066,    53,    75,   302,   303,   304,
     510,   305,   306,   512,   307,   308,   207,   474,   873,   874,
     875,  1017,    55,    76,   320,   321,   322,   323,   518,   324,
     519,   325,   520,   326,   521,   327,   522,   328,   523,   329,
     517,   280,   504,   962,   963,  1069,   208,   473,   870,   871,
    1014,  1155,  1156,  1157,  1158,  1159,  1236,  1160,   209,   477,
     903,   904,   905,  1031,  1245,   906,   907,  1032,   908,   909,
     210,   211,   480,   926,   927,   928,  1043,   929,  1044,   212,
     481,   936,   937,   938,   939,  1048,   940,   941,  1050,   213,
     482,    65,    81,   397,   398,   399,   400,   546,   401,   547,
     402,   403,   549,   404,   405,   406,   552,   775,   407,   553,
     408,   409,   410,   556,   411,   557,   412,   558,   413,   559,
     214,   428,    67,    82,   416,   417,   418,   562,   419,   215,
     486,   944,   945,  1054,  1198,  1199,  1200,  1201,  1253,  1202,
    1251,  1272,  1273,  1274,  1282,  1283,  1284,  1290,  1285,  1286,
    1287,  1288,  1294,   216,   487,   948,   949,   950
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     153,   219,   236,   282,   296,   316,    38,   338,   357,   374,
     394,   283,   297,   900,   237,   359,   279,   224,   276,   289,
     300,   318,   830,   352,   370,   860,   395,  1127,  1128,  1129,
     238,  1136,  1142,   339,   358,    31,   239,    32,    42,    33,
     360,   851,   240,   241,   127,   128,   242,   243,    30,   717,
     244,   310,   372,   373,   245,   125,   332,   946,   960,    86,
     225,   277,   290,   301,   319,   420,   353,   371,  1006,   396,
      89,  1007,   152,   749,   127,   128,   246,   274,   285,   299,
     317,  1009,   217,   218,  1010,   755,   756,   757,  1015,   247,
      44,  1016,   248,   249,   489,   250,  1148,  1149,  1055,   490,
     125,  1056,   921,   922,    46,   251,   252,   253,    48,   331,
     254,   255,  1275,   256,    50,  1276,   493,   257,   717,   127,
     128,   494,    52,   258,    54,   259,   852,   260,   268,   269,
     152,   270,    56,   851,   858,   271,   859,   284,   298,   309,
     705,   706,   707,   708,    58,   310,   311,   312,   313,   314,
     315,    91,    92,   372,   373,    93,    60,   152,    94,    95,
      96,   127,   128,   127,   128,   332,    62,   333,   334,   414,
     415,   335,   336,   337,  1277,   709,   505,  1278,  1279,  1280,
    1281,   506,    64,   127,   128,   773,   774,   152,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   910,   911,   912,
     880,   881,   882,   883,   884,   885,   126,    66,   508,  1222,
    1223,  1224,   152,   509,   894,   127,   128,   124,    34,    35,
      36,    37,   129,   791,  1242,  1243,  1244,   130,   131,   132,
     133,   134,   135,   136,   421,   137,   422,  1127,  1128,  1129,
     138,  1136,  1142,   125,   423,   515,   543,   424,   560,   139,
     516,   544,   140,   561,   152,   281,   152,   426,   433,   141,
     564,   489,   127,   128,   564,   565,   965,   142,   143,   966,
     524,   434,   144,   493,   525,   145,   152,   988,   967,   146,
     332,   435,   989,   233,   436,   988,   234,   860,   127,   128,
     990,  1093,  1012,   526,   437,   438,   900,  1013,   127,   128,
     147,   148,   149,   150,   439,  1029,   127,   128,  1036,   786,
    1030,   440,   151,  1037,   787,   788,   789,   790,   791,   792,
     793,   794,   795,   796,   797,   798,   441,   442,   152,   799,
     800,   801,   802,   803,   804,   805,   895,   896,   897,   898,
     125,   443,   444,   332,   354,   333,   334,   355,   356,   720,
     721,   722,   723,   445,   291,   292,   293,   294,   295,   127,
     128,   127,   128,   446,   448,   332,  1041,   930,   931,   932,
     449,  1042,  1045,  1051,   560,   152,  1058,  1046,  1052,  1053,
     233,  1059,   450,   234,   451,   452,   456,  1191,   988,  1192,
    1193,   566,   567,  1229,   505,  1233,   534,   457,   153,  1230,
    1234,   152,   219,   543,  1254,   508,   535,   515,  1241,  1255,
    1257,   152,  1258,   458,   236,  1295,   539,   282,   224,   933,
    1296,   466,   467,   468,   296,   283,   237,   478,   279,   485,
     276,   488,   297,   289,   316,  1213,  1214,  1215,  1216,   492,
     300,   500,   238,   501,   338,   511,   513,   514,   239,   357,
     318,   529,   533,   537,   240,   241,   359,   538,   242,   243,
     352,   225,   244,   540,   568,   370,   245,   545,   548,   394,
     339,   550,   152,   277,   152,   358,   290,   551,   554,   555,
     563,   360,   569,   301,   570,   395,   571,   572,   246,   274,
     573,   574,   285,   319,   127,   128,   152,   575,   584,   299,
     590,   247,   576,   353,   248,   249,   577,   250,   371,   317,
     578,   596,   579,   580,   597,   581,   598,   251,   252,   253,
     582,   583,   254,   255,   585,   256,   586,   587,   396,   257,
     588,   593,   602,   589,   591,   258,   592,   259,   603,   260,
     268,   269,   594,   270,   595,   599,   600,   271,   604,   605,
     601,   284,   606,   607,   608,   609,   610,   611,   298,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   612,   613,   614,   615,   616,   617,   618,   392,
     393,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   619,   620,   622,   621,   623,
     624,   625,   626,   627,   629,   628,   153,   152,   630,   219,
     632,   635,   636,   637,   638,   639,   633,   641,   642,   640,
     643,   644,   646,   648,   649,   224,   650,   654,   655,   651,
     652,   656,   657,   658,   659,   660,   662,   663,   664,   665,
     666,   667,   899,   913,   923,   668,   394,   670,   674,   671,
     947,   672,   675,   678,   679,   677,   681,   684,   901,   919,
     924,   934,   395,   680,   682,   683,   782,   685,   225,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   686,   687,   688,   689,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   690,   691,   125,   693,   694,
     696,   902,   920,   925,   935,   396,   697,   698,   226,   699,
     227,   700,   701,   702,   703,   713,   127,   128,   228,   229,
     230,   231,   232,   129,   704,   711,   712,   714,   130,   131,
     132,   715,   716,   719,   725,    32,   726,   233,   727,   728,
     234,   138,   729,   730,   731,   738,   739,   732,   235,   733,
     734,   735,   736,   737,   740,   741,   742,   744,   745,   746,
     747,   748,   750,   751,   752,   753,   754,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     781,   831,   865,   758,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   759,   125,   332,   760,   761,   835,
     839,   147,   148,   843,   847,   869,   872,   876,   943,   762,
     763,   764,   952,   765,   127,   128,   776,   229,   230,   956,
     232,   129,   972,   766,   973,   974,   130,   131,   132,   152,
     975,   976,   978,   767,   768,   233,   979,   984,   234,   985,
     986,   987,   770,   993,   992,   995,   235,   771,   772,   996,
     778,   998,   999,   779,   780,  1002,  1001,  1004,  1005,  1008,
    1018,  1019,  1021,  1022,  1060,  1023,  1024,  1025,  1026,  1027,
    1028,  1033,  1034,  1035,  1038,  1039,  1040,  1047,  1049,  1057,
    1065,  1076,  1064,  1068,  1067,  1072,  1077,  1070,  1071,  1073,
    1074,  1075,  1078,  1079,  1080,  1081,  1082,  1083,  1084,   147,
     148,  1085,  1086,   236,  1087,  1146,   338,  1088,  1090,   357,
    1089,  1173,  1101,  1174,  1179,   237,   359,   279,  1183,   276,
    1130,  1091,   352,  1150,  1102,   370,   316,   152,  1140,   374,
    1166,   238,   339,  1167,  1168,   358,  1184,   239,  1126,  1153,
    1103,   360,   318,   240,   241,   899,  1104,   242,   243,  1151,
     913,   244,  1105,  1106,   923,   245,  1107,  1108,  1186,  1169,
    1109,   901,   277,  1194,  1110,   353,   919,   947,   371,  1170,
     924,  1141,   282,  1171,  1175,   296,   934,   246,   274,  1196,
     283,  1176,  1154,   297,  1187,   319,  1111,  1139,   289,  1195,
     247,   300,  1177,   248,   249,  1180,   250,  1181,  1152,  1112,
    1188,   317,  1113,  1114,   902,  1115,   251,   252,   253,   920,
    1189,   254,   255,   925,   256,  1116,  1117,  1118,   257,   935,
    1119,  1120,  1197,  1121,   258,  1204,   259,  1122,   260,   268,
     269,   290,   270,  1123,   301,  1124,   271,  1125,  1132,  1133,
    1206,  1134,  1207,  1231,  1212,  1135,  1131,   285,  1237,  1218,
     299,  1219,  1220,  1232,  1238,  1221,  1226,  1239,  1240,  1252,
    1261,  1264,  1266,   777,  1269,  1227,  1291,  1228,  1271,  1292,
    1293,  1297,  1301,   769,   857,   634,   783,   631,  1094,   964,
    1092,  1147,  1144,   785,  1165,  1182,  1164,  1145,  1172,   676,
    1096,  1235,  1246,  1095,  1260,  1143,  1247,  1248,  1249,   645,
    1256,  1259,   330,  1098,  1265,  1097,   284,  1262,  1299,   298,
    1268,  1270,   669,  1100,  1300,  1298,  1303,  1209,  1304,  1099,
     673,   647,  1211,  1208,  1162,  1163,  1263,  1210,   961,  1161,
    1190,  1185,  1178,   942,  1267,   653,   692,   661,  1203,  1289,
    1302,     0,  1101,   695,   784,     0,  1205,     0,  1150,     0,
    1130,     0,     0,     0,  1102,     0,     0,     0,  1140,  1250,
       0,     0,     0,  1194,  1153,     0,     0,     0,  1126,     0,
    1103,     0,     0,     0,  1151,     0,  1104,     0,     0,  1196,
       0,     0,  1105,  1106,     0,     0,  1107,  1108,     0,  1195,
    1109,     0,     0,     0,  1110,     0,     0,     0,     0,     0,
       0,  1141,     0,     0,     0,     0,     0,  1154,     0,     0,
       0,     0,     0,     0,     0,     0,  1111,  1139,     0,     0,
       0,     0,  1197,  1152,     0,     0,     0,     0,     0,  1112,
       0,     0,  1113,  1114,     0,  1115,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1116,  1117,  1118,     0,     0,
    1119,  1120,     0,  1121,     0,     0,     0,  1122,     0,     0,
       0,     0,     0,  1123,     0,  1124,     0,  1125,  1132,  1133,
       0,  1134,     0,     0,     0,  1135,  1131
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    74,    75,   733,    73,    79,    73,    72,    73,    74,
      75,    76,   702,    78,    79,   727,    81,  1003,  1003,  1003,
      73,  1003,  1003,    78,    79,     5,    73,     7,     7,     9,
      79,   123,    73,    73,    95,    96,    73,    73,     0,   606,
      73,   121,   130,   131,    73,    76,    77,   193,   128,   208,
      72,    73,    74,    75,    76,     6,    78,    79,     3,    81,
      10,     6,   208,   642,    95,    96,    73,    73,    74,    75,
      76,     3,    16,    17,     6,   654,   655,   656,     3,    73,
       7,     6,    73,    73,     3,    73,   117,   118,     3,     8,
      76,     6,   153,   154,     7,    73,    73,    73,     7,    21,
      73,    73,     3,    73,     7,     6,     3,    73,   675,    95,
      96,     8,     7,    73,     7,    73,   208,    73,    73,    73,
     208,    73,     7,   123,   124,    73,   126,    74,    75,   115,
     176,   177,   178,   179,     7,   121,   122,   123,   124,   125,
     126,    11,    12,   130,   131,    15,     7,   208,    18,    19,
      20,    95,    96,    95,    96,    77,     7,    79,    80,    13,
      14,    83,    84,    85,   185,   211,     3,   188,   189,   190,
     191,     8,     7,    95,    96,   173,   174,   208,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,   149,   150,   151,
     133,   134,   135,   136,   137,   138,    86,     7,     3,    38,
      39,    40,   208,     8,    21,    95,    96,    75,   208,   209,
     210,   211,   102,    30,   140,   141,   142,   107,   108,   109,
     110,   111,   112,   113,     3,   115,     4,  1233,  1233,  1233,
     120,  1233,  1233,    76,     8,     3,     3,     3,     3,   129,
       8,     8,   132,     8,   208,    88,   208,     8,     4,   139,
       3,     3,    95,    96,     3,     8,     8,   147,   148,     8,
       8,     4,   152,     3,     3,   155,   208,     3,     8,   159,
      77,     4,     8,   116,     4,     3,   119,  1009,    95,    96,
       8,   991,     3,     8,     4,     4,  1036,     8,    95,    96,
     180,   181,   182,   183,     4,     3,    95,    96,     3,    21,
       8,     4,   192,     8,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     4,     4,   208,    41,
      42,    43,    44,    45,    46,    47,   143,   144,   145,   146,
      76,     4,     4,    77,    78,    79,    80,    81,    82,   103,
     104,   105,   106,     4,    90,    91,    92,    93,    94,    95,
      96,    95,    96,     4,     4,    77,     3,   156,   157,   158,
       4,     8,     3,     3,     3,   208,     3,     8,     8,     8,
     116,     8,     4,   119,     4,     4,     4,   184,     3,   186,
     187,   421,   422,     8,     3,     3,     8,     4,   489,     8,
       8,   208,   493,     3,     3,     3,     3,     3,     8,     8,
       8,   208,     8,     4,   505,     3,     8,   508,   493,   208,
       8,     4,     4,     4,   515,   508,   505,     4,   505,     4,
     505,     4,   515,   508,   525,    22,    23,    24,    25,     4,
     515,     4,   505,     4,   535,     4,     4,     4,   505,   540,
     525,     4,     4,     4,   505,   505,   540,     4,   505,   505,
     535,   493,   505,     3,   208,   540,   505,     4,     4,   560,
     535,     4,   208,   505,   208,   540,   508,     4,     4,     4,
       4,   540,     4,   515,     4,   560,     4,     4,   505,   505,
       4,     4,   508,   525,    95,    96,   208,     4,   211,   515,
       4,   505,   209,   535,   505,   505,   209,   505,   540,   525,
     209,     4,   209,   209,     4,   209,     4,   505,   505,   505,
     209,   209,   505,   505,   210,   505,   210,   210,   560,   505,
     209,   211,     4,   209,   209,   505,   209,   505,     4,   505,
     505,   505,   211,   505,   211,   211,   211,   505,     4,     4,
     211,   508,     4,     4,     4,   211,   211,   211,   515,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,     4,     4,     4,     4,     4,     4,     4,   180,
     181,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,     4,     4,     4,   209,     4,
       4,     4,     4,     4,     4,   211,   697,   208,     4,   700,
       4,     4,     4,     4,     4,     4,   211,   211,     4,   209,
       4,     4,     4,     4,   209,   700,     4,     4,     4,   209,
     209,     4,     4,     4,     4,     4,     4,     4,   209,     4,
       4,     4,   733,   734,   735,   211,   737,     4,     4,   211,
     741,   211,     4,     4,     4,   211,     4,     4,   733,   734,
     735,   736,   737,   209,   209,   209,   696,     4,   700,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,   211,   211,     4,     4,    65,    66,    67,    68,
      69,    70,    71,    72,    73,     4,     4,    76,     4,   209,
       4,   733,   734,   735,   736,   737,     7,   208,    87,     7,
      89,     7,     7,     7,     5,     5,    95,    96,    97,    98,
      99,   100,   101,   102,   208,   208,   208,     5,   107,   108,
     109,     5,     5,   208,     5,     7,     5,   116,     5,     7,
     119,   120,     5,     5,     5,   208,   208,     7,   127,     7,
       7,     7,     7,     7,     5,     7,     5,     5,     5,   208,
     208,   208,   208,     7,   208,   208,   208,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
       5,     7,   114,   208,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   208,    76,    77,   208,   208,     7,
       7,   180,   181,     7,     7,     7,     7,     7,     7,   208,
     208,   208,     7,   208,    95,    96,   175,    98,    99,     7,
     101,   102,     4,   208,     4,     4,   107,   108,   109,   208,
       4,     4,     4,   208,   208,   116,     4,     4,   119,     4,
       4,     4,   208,     3,     6,     6,   127,   208,   208,     3,
     208,     6,     3,   208,   208,     3,     6,     6,     3,     6,
       6,     3,     6,     3,   208,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   209,     6,     3,     6,     4,   211,     8,     6,     4,
       4,     4,   209,   211,   209,     4,   209,   209,     4,   180,
     181,     4,     4,   994,     4,     4,   997,   209,   211,  1000,
     209,     4,  1003,     4,   211,   994,  1000,   994,     4,   994,
    1003,   209,   997,  1014,  1003,  1000,  1017,   208,  1003,  1020,
     209,   994,   997,   209,   209,  1000,     4,   994,  1003,  1014,
    1003,  1000,  1017,   994,   994,  1036,  1003,   994,   994,  1014,
    1041,   994,  1003,  1003,  1045,   994,  1003,  1003,   211,   209,
    1003,  1036,   994,  1054,  1003,   997,  1041,  1058,  1000,   209,
    1045,  1003,  1063,   209,   209,  1066,  1051,   994,   994,  1054,
    1063,   209,  1014,  1066,     4,  1017,  1003,  1003,  1063,  1054,
     994,  1066,   209,   994,   994,   209,   994,   209,  1014,  1003,
     209,  1017,  1003,  1003,  1036,  1003,   994,   994,   994,  1041,
       4,   994,   994,  1045,   994,  1003,  1003,  1003,   994,  1051,
    1003,  1003,  1054,  1003,   994,   211,   994,  1003,   994,   994,
     994,  1063,   994,  1003,  1066,  1003,   994,  1003,  1003,  1003,
       6,  1003,     3,     8,     4,  1003,  1003,  1063,     4,   208,
    1066,   208,   208,     8,     8,   208,   208,     3,     8,     4,
       4,     4,     4,   688,     5,   208,     4,   208,     7,     4,
       4,     4,     4,   675,   726,   493,   697,   489,   993,   781,
     988,  1012,  1006,   700,  1022,  1041,  1020,  1009,  1029,   543,
     996,   208,   208,   994,  1233,  1005,   208,   208,   208,   505,
     208,   208,    77,   999,   209,   997,  1063,   211,   209,  1066,
     208,   208,   535,  1002,   209,   211,   208,  1065,   208,  1000,
     540,   508,  1068,  1063,  1017,  1019,  1239,  1066,   751,  1015,
    1051,  1045,  1036,   737,  1254,   515,   560,   525,  1055,  1275,
    1295,    -1,  1233,   564,   699,    -1,  1058,    -1,  1239,    -1,
    1233,    -1,    -1,    -1,  1233,    -1,    -1,    -1,  1233,  1189,
      -1,    -1,    -1,  1254,  1239,    -1,    -1,    -1,  1233,    -1,
    1233,    -1,    -1,    -1,  1239,    -1,  1233,    -1,    -1,  1254,
      -1,    -1,  1233,  1233,    -1,    -1,  1233,  1233,    -1,  1254,
    1233,    -1,    -1,    -1,  1233,    -1,    -1,    -1,    -1,    -1,
      -1,  1233,    -1,    -1,    -1,    -1,    -1,  1239,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1233,  1233,    -1,    -1,
      -1,    -1,  1254,  1239,    -1,    -1,    -1,    -1,    -1,  1233,
      -1,    -1,  1233,  1233,    -1,  1233,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1233,  1233,  1233,    -1,    -1,
    1233,  1233,    -1,  1233,    -1,    -1,    -1,  1233,    -1,    -1,
      -1,    -1,    -1,  1233,    -1,  1233,    -1,  1233,  1233,  1233,
      -1,  1233,    -1,    -1,    -1,  1233,  1233
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
       0,     5,     7,     9,   208,   209,   210,   211,   228,   229,
     230,   235,     7,   244,     7,   248,     7,   292,     7,   401,
       7,   481,     7,   497,     7,   514,     7,   433,     7,   439,
       7,   463,     7,   377,     7,   583,     7,   614,   236,   231,
     245,   249,   293,   402,   482,   498,   515,   434,   440,   464,
     378,   584,   615,   228,   237,   238,   208,   233,   234,    10,
     246,    11,    12,    15,    18,    19,    20,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    86,    95,    96,   102,
     107,   108,   109,   110,   111,   112,   113,   115,   120,   129,
     132,   139,   147,   148,   152,   155,   159,   180,   181,   182,
     183,   192,   208,   243,   250,   251,   252,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   274,   276,   278,   279,   280,
     282,   284,   285,   286,   287,   289,   290,   299,   301,   303,
     344,   350,   356,   362,   364,   371,   385,   395,   415,   416,
     417,   418,   423,   431,   457,   487,   489,   508,   538,   550,
     562,   563,   571,   581,   612,   621,   645,    16,    17,   243,
     294,   295,   296,   298,   487,   489,    87,    89,    97,    98,
      99,   100,   101,   116,   119,   127,   243,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     268,   269,   270,   271,   274,   276,   278,   279,   280,   282,
     284,   403,   404,   405,   407,   409,   411,   413,   415,   416,
     417,   418,   421,   422,   457,   475,   487,   489,   491,   508,
     533,    88,   243,   411,   413,   457,   483,   484,   485,   487,
     489,    90,    91,    92,    93,    94,   243,   411,   413,   457,
     487,   489,   499,   500,   501,   503,   504,   506,   507,   115,
     121,   122,   123,   124,   125,   126,   243,   457,   487,   489,
     516,   517,   518,   519,   521,   523,   525,   527,   529,   531,
     431,    21,    77,    79,    80,    83,    84,    85,   243,   321,
     441,   442,   443,   444,   445,   446,   447,   449,   451,   453,
     454,   456,   487,   489,    78,    81,    82,   243,   321,   445,
     451,   465,   466,   467,   468,   469,   471,   472,   473,   474,
     487,   489,   130,   131,   243,   379,   380,   381,   383,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   180,   181,   243,   487,   489,   585,   586,   587,
     588,   590,   592,   593,   595,   596,   597,   600,   602,   603,
     604,   606,   608,   610,    13,    14,   616,   617,   618,   620,
       6,     3,     4,     8,     3,   247,     8,   253,   613,   291,
     300,   302,   304,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   288,     4,     4,
       4,     4,     4,   272,   275,   277,     4,     4,     4,   396,
     432,   458,   424,   488,   490,   419,     4,     4,     4,   351,
     363,   357,   345,   539,   509,   372,   386,   551,     4,   365,
     564,   572,   582,   281,   283,     4,   622,   646,     4,     3,
       8,   297,     4,     3,     8,   476,   492,   406,   408,   410,
       4,     4,   414,   412,   534,     3,     8,   486,     3,     8,
     502,     4,   505,     4,     4,     3,     8,   532,   520,   522,
     524,   526,   528,   530,     8,     3,     8,   448,   322,     4,
     452,   450,   455,     4,     8,     3,   470,     4,     4,     8,
       3,   382,   384,     3,     8,     4,   589,   591,     4,   594,
       4,     4,   598,   601,     4,     4,   605,   607,   609,   611,
       3,     8,   619,     4,     3,     8,   228,   228,   208,     4,
       4,     4,     4,     4,     4,     4,   209,   209,   209,   209,
     209,   209,   209,   209,   211,   210,   210,   210,   209,   209,
       4,   209,   209,   211,   211,   211,     4,     4,     4,   211,
     211,   211,     4,     4,     4,     4,     4,     4,     4,   211,
     211,   211,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   209,     4,     4,     4,     4,     4,     4,   211,     4,
       4,   251,     4,   211,   295,     4,     4,     4,     4,     4,
     209,   211,     4,     4,     4,   404,     4,   484,     4,   209,
       4,   209,   209,   500,     4,     4,     4,     4,     4,     4,
       4,   518,     4,     4,   209,     4,     4,     4,   211,   443,
       4,   211,   211,   467,     4,     4,   380,   211,     4,     4,
     209,     4,   209,   209,     4,     4,   211,   211,     4,     4,
       4,     4,   586,     4,   209,   617,     4,     7,   208,     7,
       7,     7,     7,     5,   208,   176,   177,   178,   179,   211,
     273,   208,   208,     5,     5,     5,     5,   230,   232,   208,
     103,   104,   105,   106,   420,     5,     5,     5,     7,     5,
       5,     5,     7,     7,     7,     7,     7,     7,   208,   208,
       5,     7,     5,   239,     5,     5,   208,   208,   208,   239,
     208,     7,   208,   208,   208,   239,   239,   239,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   232,
     208,   208,   208,   173,   174,   599,   175,   273,   208,   208,
     208,     5,   228,   250,   616,   294,    21,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    41,
      42,    43,    44,    45,    46,    47,   243,   309,   310,   311,
     314,   316,   318,   320,   321,   323,   324,   325,   326,   327,
     328,   331,   332,   333,   334,   335,   337,   338,   340,   342,
     309,     7,   305,   306,   307,     7,   397,   398,   399,     7,
     435,   436,   437,     7,   459,   460,   461,     7,   425,   426,
     427,   123,   208,   352,   353,   354,   355,   237,   124,   126,
     354,   358,   359,   360,   361,   114,   346,   347,   348,     7,
     540,   541,     7,   510,   511,   512,     7,   373,   374,   375,
     133,   134,   135,   136,   137,   138,   387,   388,   389,   390,
     391,   392,   393,   394,    21,   143,   144,   145,   146,   243,
     323,   487,   489,   552,   553,   554,   557,   558,   560,   561,
     149,   150,   151,   243,   366,   367,   368,   369,   370,   487,
     489,   153,   154,   243,   487,   489,   565,   566,   567,   569,
     156,   157,   158,   208,   487,   489,   573,   574,   575,   576,
     578,   579,   585,     7,   623,   624,   193,   243,   647,   648,
     649,   240,     7,   477,   478,   479,     7,   493,   494,   495,
     128,   519,   535,   536,   305,     8,     8,     8,   312,   315,
     317,   319,     4,     4,     4,     4,     4,   336,     4,     4,
     329,   339,   341,   343,     4,     4,     4,     4,     3,     8,
       8,   308,     6,     3,   400,     6,     3,   438,     6,     3,
     462,     6,     3,   428,     6,     3,     3,     6,     6,     3,
       6,   349,     3,     8,   542,     3,     6,   513,     6,     3,
     376,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   555,   559,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   568,   570,     3,     8,     4,   577,     4,
     580,     3,     8,     8,   625,     3,     6,     4,     3,     8,
     208,   241,   242,   480,     6,     3,   496,     6,     3,   537,
       8,     6,     4,     4,     4,     4,   209,   211,   209,   211,
     209,     4,   209,   209,     4,     4,     4,     4,   209,   209,
     211,   209,   310,   309,   307,   403,   399,   441,   437,   465,
     461,   243,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   268,   269,   270,   271,   274,
     276,   278,   279,   280,   282,   284,   321,   395,   407,   409,
     411,   413,   415,   416,   417,   418,   422,   429,   430,   457,
     487,   489,   533,   427,   353,   359,     4,   347,   117,   118,
     243,   321,   457,   487,   489,   543,   544,   545,   546,   547,
     549,   541,   516,   512,   379,   375,   209,   209,   209,   209,
     209,   209,   388,     4,     4,   209,   209,   209,   553,   211,
     209,   209,   367,     4,     4,   566,   211,     4,   209,     4,
     574,   184,   186,   187,   243,   321,   487,   489,   626,   627,
     628,   629,   631,   624,   211,   648,     6,     3,   483,   479,
     499,   495,     4,    22,    23,    24,    25,   313,   208,   208,
     208,   208,    38,    39,    40,   330,   208,   208,   208,     8,
       8,     8,     8,     3,     8,   208,   548,     4,     8,     3,
       8,     8,   140,   141,   142,   556,   208,   208,   208,   208,
     228,   632,     4,   630,     3,     8,   208,     8,     8,   208,
     430,     4,   211,   545,     4,   209,     4,   627,   208,     5,
     208,     7,   633,   634,   635,     3,     6,   185,   188,   189,
     190,   191,   636,   637,   638,   640,   641,   642,   643,   634,
     639,     4,     4,     4,   644,     3,     8,     4,   211,   209,
     209,     4,   637,   208,   208
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   212,   214,   213,   215,   213,   216,   213,   217,   213,
     218,   213,   219,   213,   220,   213,   221,   213,   222,   213,
     223,   213,   224,   213,   225,   213,   226,   213,   227,   213,
     228,   228,   228,   228,   228,   228,   228,   229,   231,   230,
     232,   233,   233,   234,   234,   236,   235,   237,   237,   238,
     238,   240,   239,   241,   241,   242,   242,   243,   245,   244,
     247,   246,   249,   248,   250,   250,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   251,   251,
     251,   251,   251,   251,   251,   251,   251,   251,   253,   252,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   272,   271,   273,
     273,   273,   273,   273,   275,   274,   277,   276,   278,   279,
     281,   280,   283,   282,   284,   285,   286,   288,   287,   289,
     291,   290,   293,   292,   294,   294,   295,   295,   295,   295,
     295,   297,   296,   298,   300,   299,   302,   301,   304,   303,
     305,   305,   306,   306,   308,   307,   309,   309,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     310,   310,   310,   310,   310,   310,   310,   310,   310,   310,
     312,   311,   313,   313,   313,   313,   315,   314,   317,   316,
     319,   318,   320,   322,   321,   323,   324,   325,   326,   327,
     329,   328,   330,   330,   330,   331,   332,   333,   334,   336,
     335,   337,   339,   338,   341,   340,   343,   342,   345,   344,
     346,   346,   347,   349,   348,   351,   350,   352,   352,   353,
     353,   354,   355,   357,   356,   358,   358,   359,   359,   359,
     360,   361,   363,   362,   365,   364,   366,   366,   367,   367,
     367,   367,   367,   367,   368,   369,   370,   372,   371,   373,
     373,   374,   374,   376,   375,   378,   377,   379,   379,   379,
     380,   380,   382,   381,   384,   383,   386,   385,   387,   387,
     388,   388,   388,   388,   388,   388,   389,   390,   391,   392,
     393,   394,   396,   395,   397,   397,   398,   398,   400,   399,
     402,   401,   403,   403,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   406,   405,   408,
     407,   410,   409,   412,   411,   414,   413,   415,   416,   417,
     419,   418,   420,   420,   420,   420,   421,   422,   424,   423,
     425,   425,   426,   426,   428,   427,   429,   429,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   432,   431,
     434,   433,   435,   435,   436,   436,   438,   437,   440,   439,
     441,   441,   442,   442,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   444,   445,   446,   448,   447,   450,
     449,   452,   451,   453,   455,   454,   456,   458,   457,   459,
     459,   460,   460,   462,   461,   464,   463,   465,   465,   466,
     466,   467,   467,   467,   467,   467,   467,   467,   467,   467,
     468,   470,   469,   471,   472,   473,   474,   476,   475,   477,
     477,   478,   478,   480,   479,   482,   481,   483,   483,   484,
     484,   484,   484,   484,   484,   484,   486,   485,   488,   487,
     490,   489,   492,   491,   493,   493,   494,   494,   496,   495,
     498,   497,   499,   499,   500,   500,   500,   500,   500,   500,
     500,   500,   500,   500,   500,   502,   501,   503,   505,   504,
     506,   507,   509,   508,   510,   510,   511,   511,   513,   512,
     515,   514,   516,   516,   517,   517,   518,   518,   518,   518,
     518,   518,   518,   518,   518,   518,   518,   520,   519,   522,
     521,   524,   523,   526,   525,   528,   527,   530,   529,   532,
     531,   534,   533,   535,   535,   537,   536,   539,   538,   540,
     540,   542,   541,   543,   543,   544,   544,   545,   545,   545,
     545,   545,   545,   545,   546,   548,   547,   549,   551,   550,
     552,   552,   553,   553,   553,   553,   553,   553,   553,   553,
     553,   555,   554,   556,   556,   556,   557,   559,   558,   560,
     561,   562,   564,   563,   565,   565,   566,   566,   566,   566,
     566,   568,   567,   570,   569,   572,   571,   573,   573,   574,
     574,   574,   574,   574,   574,   575,   577,   576,   578,   580,
     579,   582,   581,   584,   583,   585,   585,   586,   586,   586,
     586,   586,   586,   586,   586,   586,   586,   586,   586,   586,
     586,   586,   586,   586,   586,   587,   589,   588,   591,   590,
     592,   594,   593,   595,   596,   598,   597,   599,   599,   601,
     600,   602,   603,   605,   604,   607,   606,   609,   608,   611,
     610,   613,   612,   615,   614,   616,   616,   617,   617,   619,
     618,   620,   622,   621,   623,   623,   625,   624,   626,   626,
     627,   627,   627,   627,   627,   627,   627,   628,   630,   629,
     632,   631,   633,   633,   635,   634,   636,   636,   637,   637,
     637,   637,   637,   639,   638,   640,   641,   642,   644,   643,
     646,   645,   647,   647,   648,   648,   649
  };

  const signed char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     4,     0,     4,     3,     3,     3,     0,     4,     3,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       0,     4,     1,     1,     1,     3,     3,     3,     3,     0,
       4,     3,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     6,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     4,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     4,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     3,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     0,
       6,     3,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       0,     6,     1,     3,     1,     1,     3
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
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"reservations-global\"", "\"reservations-in-subnet\"",
  "\"reservations-out-of-pool\"", "\"mac-sources\"",
  "\"relay-supplied-options\"", "\"host-reservation-identifiers\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"client-classes\"",
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
  "\"ip-reservations-unique\"", "\"loggers\"", "\"output_options\"",
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
  "global_object", "$@19", "sub_dhcp6", "$@20", "global_params",
  "global_param", "data_directory", "$@21", "preferred_lifetime",
  "min_preferred_lifetime", "max_preferred_lifetime", "valid_lifetime",
  "min_valid_lifetime", "max_valid_lifetime", "renew_timer",
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "cache_threshold", "cache_max_age", "decline_probation_period",
  "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@22",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@23",
  "ddns_qualifying_suffix", "$@24", "ddns_update_on_renew",
  "ddns_use_conflict_resolution", "hostname_char_set", "$@25",
  "hostname_char_replacement", "$@26", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "server_tag", "$@27", "ip_reservations_unique", "interfaces_config",
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
       0,   300,   300,   300,   301,   301,   302,   302,   303,   303,
     304,   304,   305,   305,   306,   306,   307,   307,   308,   308,
     309,   309,   310,   310,   311,   311,   312,   312,   313,   313,
     321,   322,   323,   324,   325,   326,   327,   330,   335,   335,
     346,   349,   350,   353,   358,   366,   366,   373,   374,   377,
     381,   388,   388,   395,   396,   399,   403,   414,   423,   423,
     438,   438,   455,   455,   464,   465,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,   489,   490,   491,   492,   493,
     494,   495,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   534,   534,
     543,   549,   555,   561,   567,   573,   579,   585,   591,   597,
     603,   609,   615,   621,   627,   633,   639,   645,   645,   654,
     657,   660,   663,   666,   672,   672,   681,   681,   690,   696,
     702,   702,   711,   711,   720,   726,   732,   738,   738,   747,
     753,   753,   765,   765,   774,   775,   778,   779,   780,   781,
     782,   785,   785,   796,   802,   802,   815,   815,   828,   828,
     839,   840,   843,   844,   847,   847,   857,   858,   861,   862,
     863,   864,   865,   866,   867,   868,   869,   870,   871,   872,
     873,   874,   875,   876,   877,   878,   879,   880,   881,   882,
     885,   885,   893,   894,   895,   896,   899,   899,   908,   908,
     917,   917,   926,   932,   932,   941,   947,   953,   959,   965,
     971,   971,   979,   980,   981,   984,   990,   996,  1002,  1008,
    1008,  1017,  1023,  1023,  1032,  1032,  1041,  1041,  1050,  1050,
    1061,  1062,  1064,  1066,  1066,  1085,  1085,  1096,  1097,  1100,
    1101,  1104,  1109,  1114,  1114,  1125,  1126,  1129,  1130,  1131,
    1134,  1139,  1146,  1146,  1159,  1159,  1172,  1173,  1176,  1177,
    1178,  1179,  1180,  1181,  1184,  1190,  1196,  1202,  1202,  1213,
    1214,  1217,  1218,  1221,  1221,  1231,  1231,  1241,  1242,  1243,
    1246,  1247,  1250,  1250,  1259,  1259,  1268,  1268,  1280,  1281,
    1284,  1285,  1286,  1287,  1288,  1289,  1292,  1298,  1304,  1310,
    1316,  1322,  1331,  1331,  1345,  1346,  1349,  1350,  1357,  1357,
    1383,  1383,  1394,  1395,  1399,  1400,  1401,  1402,  1403,  1404,
    1405,  1406,  1407,  1408,  1409,  1410,  1411,  1412,  1413,  1414,
    1415,  1416,  1417,  1418,  1419,  1420,  1421,  1422,  1423,  1424,
    1425,  1426,  1427,  1428,  1429,  1430,  1431,  1432,  1433,  1434,
    1435,  1436,  1437,  1438,  1439,  1440,  1441,  1444,  1444,  1453,
    1453,  1462,  1462,  1471,  1471,  1480,  1480,  1491,  1497,  1503,
    1509,  1509,  1517,  1518,  1519,  1520,  1523,  1529,  1537,  1537,
    1549,  1550,  1554,  1555,  1558,  1558,  1566,  1567,  1570,  1571,
    1572,  1573,  1574,  1575,  1576,  1577,  1578,  1579,  1580,  1581,
    1582,  1583,  1584,  1585,  1586,  1587,  1588,  1589,  1590,  1591,
    1592,  1593,  1594,  1595,  1596,  1597,  1598,  1599,  1600,  1601,
    1602,  1603,  1604,  1605,  1606,  1607,  1608,  1609,  1616,  1616,
    1630,  1630,  1639,  1640,  1643,  1644,  1649,  1649,  1664,  1664,
    1678,  1679,  1682,  1683,  1686,  1687,  1688,  1689,  1690,  1691,
    1692,  1693,  1694,  1695,  1698,  1700,  1706,  1708,  1708,  1717,
    1717,  1726,  1726,  1735,  1737,  1737,  1746,  1756,  1756,  1769,
    1770,  1775,  1776,  1781,  1781,  1793,  1793,  1805,  1806,  1811,
    1812,  1817,  1818,  1819,  1820,  1821,  1822,  1823,  1824,  1825,
    1828,  1830,  1830,  1839,  1841,  1843,  1849,  1858,  1858,  1871,
    1872,  1875,  1876,  1879,  1879,  1889,  1889,  1899,  1900,  1903,
    1904,  1905,  1906,  1907,  1908,  1909,  1912,  1912,  1921,  1921,
    1946,  1946,  1976,  1976,  1989,  1990,  1993,  1994,  1997,  1997,
    2009,  2009,  2021,  2022,  2025,  2026,  2027,  2028,  2029,  2030,
    2031,  2032,  2033,  2034,  2035,  2038,  2038,  2047,  2053,  2053,
    2062,  2068,  2077,  2077,  2088,  2089,  2092,  2093,  2096,  2096,
    2105,  2105,  2114,  2115,  2118,  2119,  2123,  2124,  2125,  2126,
    2127,  2128,  2129,  2130,  2131,  2132,  2133,  2136,  2136,  2147,
    2147,  2158,  2158,  2167,  2167,  2176,  2176,  2185,  2185,  2194,
    2194,  2208,  2208,  2219,  2220,  2223,  2223,  2235,  2235,  2246,
    2247,  2250,  2250,  2260,  2261,  2264,  2265,  2268,  2269,  2270,
    2271,  2272,  2273,  2274,  2277,  2279,  2279,  2288,  2297,  2297,
    2310,  2311,  2314,  2315,  2316,  2317,  2318,  2319,  2320,  2321,
    2322,  2325,  2325,  2333,  2334,  2335,  2338,  2344,  2344,  2353,
    2359,  2367,  2375,  2375,  2386,  2387,  2390,  2391,  2392,  2393,
    2394,  2397,  2397,  2406,  2406,  2418,  2418,  2431,  2432,  2435,
    2436,  2437,  2438,  2439,  2440,  2443,  2449,  2449,  2458,  2464,
    2464,  2474,  2474,  2487,  2487,  2497,  2498,  2501,  2502,  2503,
    2504,  2505,  2506,  2507,  2508,  2509,  2510,  2511,  2512,  2513,
    2514,  2515,  2516,  2517,  2518,  2521,  2528,  2528,  2537,  2537,
    2546,  2552,  2552,  2561,  2567,  2573,  2573,  2582,  2583,  2586,
    2586,  2596,  2603,  2610,  2610,  2619,  2619,  2629,  2629,  2639,
    2639,  2651,  2651,  2663,  2663,  2673,  2674,  2678,  2679,  2682,
    2682,  2693,  2701,  2701,  2714,  2715,  2719,  2719,  2727,  2728,
    2731,  2732,  2733,  2734,  2735,  2736,  2737,  2740,  2746,  2746,
    2755,  2755,  2766,  2767,  2770,  2770,  2778,  2779,  2782,  2783,
    2784,  2785,  2786,  2789,  2789,  2798,  2804,  2810,  2816,  2816,
    2825,  2825,  2836,  2837,  2840,  2841,  2844
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
#line 5960 "dhcp6_parser.cc"

#line 2850 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
