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
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 288 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 288 "dhcp6_parser.yy"
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
#line 297 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 298 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 299 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 762 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 300 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 301 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 774 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 302 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 303 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 786 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 304 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 792 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 305 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 798 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 306 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 804 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 307 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 810 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 308 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 816 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 309 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 822 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 310 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 828 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 318 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 319 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 320 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 321 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 322 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 858 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 323 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 324 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 870 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 327 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 879 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 332 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 890 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 337 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 900 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 343 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 350 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 355 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 927 "dhcp6_parser.cc"
    break;

  case 45: // $@16: %empty
#line 363 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 936 "dhcp6_parser.cc"
    break;

  case 46: // list_generic: "[" $@16 list_content "]"
#line 366 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 944 "dhcp6_parser.cc"
    break;

  case 49: // not_empty_list: value
#line 374 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 953 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list "," value
#line 378 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 962 "dhcp6_parser.cc"
    break;

  case 51: // $@17: %empty
#line 385 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 970 "dhcp6_parser.cc"
    break;

  case 52: // list_strings: "[" $@17 list_strings_content "]"
#line 387 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 979 "dhcp6_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 396 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 988 "dhcp6_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 400 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 997 "dhcp6_parser.cc"
    break;

  case 57: // unknown_map_entry: "constant string" ":"
#line 411 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1008 "dhcp6_parser.cc"
    break;

  case 58: // $@18: %empty
#line 420 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1019 "dhcp6_parser.cc"
    break;

  case 59: // syntax_map: "{" $@18 global_object "}"
#line 425 "dhcp6_parser.yy"
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
#line 435 "dhcp6_parser.yy"
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
#line 444 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1057 "dhcp6_parser.cc"
    break;

  case 62: // $@20: %empty
#line 452 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1067 "dhcp6_parser.cc"
    break;

  case 63: // sub_dhcp6: "{" $@20 global_params "}"
#line 456 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1076 "dhcp6_parser.cc"
    break;

  case 127: // $@21: %empty
#line 530 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1085 "dhcp6_parser.cc"
    break;

  case 128: // data_directory: "data-directory" $@21 ":" "constant string"
#line 533 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1095 "dhcp6_parser.cc"
    break;

  case 129: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 539 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1105 "dhcp6_parser.cc"
    break;

  case 130: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 545 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1115 "dhcp6_parser.cc"
    break;

  case 131: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 551 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 132: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 557 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 133: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 563 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1145 "dhcp6_parser.cc"
    break;

  case 134: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 569 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1155 "dhcp6_parser.cc"
    break;

  case 135: // renew_timer: "renew-timer" ":" "integer"
#line 575 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1165 "dhcp6_parser.cc"
    break;

  case 136: // rebind_timer: "rebind-timer" ":" "integer"
#line 581 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1175 "dhcp6_parser.cc"
    break;

  case 137: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 587 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1185 "dhcp6_parser.cc"
    break;

  case 138: // t1_percent: "t1-percent" ":" "floating point"
#line 593 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1195 "dhcp6_parser.cc"
    break;

  case 139: // t2_percent: "t2-percent" ":" "floating point"
#line 599 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1205 "dhcp6_parser.cc"
    break;

  case 140: // cache_threshold: "cache-threshold" ":" "floating point"
#line 605 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 141: // cache_max_age: "cache-max-age" ":" "integer"
#line 611 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1225 "dhcp6_parser.cc"
    break;

  case 142: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 617 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1235 "dhcp6_parser.cc"
    break;

  case 143: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 623 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1245 "dhcp6_parser.cc"
    break;

  case 144: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 629 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1255 "dhcp6_parser.cc"
    break;

  case 145: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 635 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1265 "dhcp6_parser.cc"
    break;

  case 146: // $@22: %empty
#line 641 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1274 "dhcp6_parser.cc"
    break;

  case 147: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 644 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1283 "dhcp6_parser.cc"
    break;

  case 148: // ddns_replace_client_name_value: "when-present"
#line 650 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1291 "dhcp6_parser.cc"
    break;

  case 149: // ddns_replace_client_name_value: "never"
#line 653 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1299 "dhcp6_parser.cc"
    break;

  case 150: // ddns_replace_client_name_value: "always"
#line 656 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1307 "dhcp6_parser.cc"
    break;

  case 151: // ddns_replace_client_name_value: "when-not-present"
#line 659 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1315 "dhcp6_parser.cc"
    break;

  case 152: // ddns_replace_client_name_value: "boolean"
#line 662 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1324 "dhcp6_parser.cc"
    break;

  case 153: // $@23: %empty
#line 668 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1333 "dhcp6_parser.cc"
    break;

  case 154: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 671 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1343 "dhcp6_parser.cc"
    break;

  case 155: // $@24: %empty
#line 677 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1352 "dhcp6_parser.cc"
    break;

  case 156: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 680 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1362 "dhcp6_parser.cc"
    break;

  case 157: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 686 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1372 "dhcp6_parser.cc"
    break;

  case 158: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 692 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1382 "dhcp6_parser.cc"
    break;

  case 159: // $@25: %empty
#line 698 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1391 "dhcp6_parser.cc"
    break;

  case 160: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 701 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1401 "dhcp6_parser.cc"
    break;

  case 161: // $@26: %empty
#line 707 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1410 "dhcp6_parser.cc"
    break;

  case 162: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 710 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1420 "dhcp6_parser.cc"
    break;

  case 163: // store_extended_info: "store-extended-info" ":" "boolean"
#line 716 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1430 "dhcp6_parser.cc"
    break;

  case 164: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 722 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1440 "dhcp6_parser.cc"
    break;

  case 165: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 728 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 166: // $@27: %empty
#line 734 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1459 "dhcp6_parser.cc"
    break;

  case 167: // server_tag: "server-tag" $@27 ":" "constant string"
#line 737 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1469 "dhcp6_parser.cc"
    break;

  case 168: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 743 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1479 "dhcp6_parser.cc"
    break;

  case 169: // $@28: %empty
#line 749 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1491 "dhcp6_parser.cc"
    break;

  case 170: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 755 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1501 "dhcp6_parser.cc"
    break;

  case 171: // $@29: %empty
#line 761 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 172: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 765 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1520 "dhcp6_parser.cc"
    break;

  case 180: // $@30: %empty
#line 781 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 181: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 787 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 182: // re_detect: "re-detect" ":" "boolean"
#line 792 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1551 "dhcp6_parser.cc"
    break;

  case 183: // $@31: %empty
#line 798 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 184: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 804 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1574 "dhcp6_parser.cc"
    break;

  case 185: // $@32: %empty
#line 811 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1586 "dhcp6_parser.cc"
    break;

  case 186: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 817 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1597 "dhcp6_parser.cc"
    break;

  case 187: // $@33: %empty
#line 824 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1609 "dhcp6_parser.cc"
    break;

  case 188: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 830 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1618 "dhcp6_parser.cc"
    break;

  case 193: // $@34: %empty
#line 843 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1628 "dhcp6_parser.cc"
    break;

  case 194: // database: "{" $@34 database_map_params "}"
#line 847 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 219: // $@35: %empty
#line 881 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1647 "dhcp6_parser.cc"
    break;

  case 220: // database_type: "type" $@35 ":" db_type
#line 884 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1656 "dhcp6_parser.cc"
    break;

  case 221: // db_type: "memfile"
#line 889 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1662 "dhcp6_parser.cc"
    break;

  case 222: // db_type: "mysql"
#line 890 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1668 "dhcp6_parser.cc"
    break;

  case 223: // db_type: "postgresql"
#line 891 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1674 "dhcp6_parser.cc"
    break;

  case 224: // db_type: "cql"
#line 892 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1680 "dhcp6_parser.cc"
    break;

  case 225: // $@36: %empty
#line 895 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1689 "dhcp6_parser.cc"
    break;

  case 226: // user: "user" $@36 ":" "constant string"
#line 898 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1699 "dhcp6_parser.cc"
    break;

  case 227: // $@37: %empty
#line 904 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1708 "dhcp6_parser.cc"
    break;

  case 228: // password: "password" $@37 ":" "constant string"
#line 907 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1718 "dhcp6_parser.cc"
    break;

  case 229: // $@38: %empty
#line 913 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1727 "dhcp6_parser.cc"
    break;

  case 230: // host: "host" $@38 ":" "constant string"
#line 916 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 231: // port: "port" ":" "integer"
#line 922 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 232: // $@39: %empty
#line 928 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1756 "dhcp6_parser.cc"
    break;

  case 233: // name: "name" $@39 ":" "constant string"
#line 931 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1766 "dhcp6_parser.cc"
    break;

  case 234: // persist: "persist" ":" "boolean"
#line 937 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1776 "dhcp6_parser.cc"
    break;

  case 235: // lfc_interval: "lfc-interval" ":" "integer"
#line 943 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1786 "dhcp6_parser.cc"
    break;

  case 236: // readonly: "readonly" ":" "boolean"
#line 949 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1796 "dhcp6_parser.cc"
    break;

  case 237: // connect_timeout: "connect-timeout" ":" "integer"
#line 955 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1806 "dhcp6_parser.cc"
    break;

  case 238: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 961 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1816 "dhcp6_parser.cc"
    break;

  case 239: // $@40: %empty
#line 967 "dhcp6_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 240: // on_fail: "on-fail" $@40 ":" on_fail_mode
#line 970 "dhcp6_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1834 "dhcp6_parser.cc"
    break;

  case 241: // on_fail_mode: "stop-retry-exit"
#line 975 "dhcp6_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1840 "dhcp6_parser.cc"
    break;

  case 242: // on_fail_mode: "serve-retry-exit"
#line 976 "dhcp6_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 1846 "dhcp6_parser.cc"
    break;

  case 243: // on_fail_mode: "serve-retry-continue"
#line 977 "dhcp6_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 1852 "dhcp6_parser.cc"
    break;

  case 244: // max_row_errors: "max-row-errors" ":" "integer"
#line 980 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1862 "dhcp6_parser.cc"
    break;

  case 245: // request_timeout: "request-timeout" ":" "integer"
#line 986 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1872 "dhcp6_parser.cc"
    break;

  case 246: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 992 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1882 "dhcp6_parser.cc"
    break;

  case 247: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 998 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1892 "dhcp6_parser.cc"
    break;

  case 248: // $@41: %empty
#line 1004 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1901 "dhcp6_parser.cc"
    break;

  case 249: // contact_points: "contact-points" $@41 ":" "constant string"
#line 1007 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1911 "dhcp6_parser.cc"
    break;

  case 250: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1013 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1921 "dhcp6_parser.cc"
    break;

  case 251: // $@42: %empty
#line 1019 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1930 "dhcp6_parser.cc"
    break;

  case 252: // keyspace: "keyspace" $@42 ":" "constant string"
#line 1022 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1940 "dhcp6_parser.cc"
    break;

  case 253: // $@43: %empty
#line 1028 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1949 "dhcp6_parser.cc"
    break;

  case 254: // consistency: "consistency" $@43 ":" "constant string"
#line 1031 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1959 "dhcp6_parser.cc"
    break;

  case 255: // $@44: %empty
#line 1037 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1968 "dhcp6_parser.cc"
    break;

  case 256: // serial_consistency: "serial-consistency" $@44 ":" "constant string"
#line 1040 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1978 "dhcp6_parser.cc"
    break;

  case 257: // $@45: %empty
#line 1046 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1990 "dhcp6_parser.cc"
    break;

  case 258: // sanity_checks: "sanity-checks" $@45 ":" "{" sanity_checks_params "}"
#line 1052 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1999 "dhcp6_parser.cc"
    break;

  case 262: // $@46: %empty
#line 1062 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2008 "dhcp6_parser.cc"
    break;

  case 263: // lease_checks: "lease-checks" $@46 ":" "constant string"
#line 1065 "dhcp6_parser.yy"
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

  case 264: // $@47: %empty
#line 1081 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 2040 "dhcp6_parser.cc"
    break;

  case 265: // mac_sources: "mac-sources" $@47 ":" "[" mac_sources_list "]"
#line 1087 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2049 "dhcp6_parser.cc"
    break;

  case 270: // duid_id: "duid"
#line 1100 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2058 "dhcp6_parser.cc"
    break;

  case 271: // string_id: "constant string"
#line 1105 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 272: // $@48: %empty
#line 1110 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2079 "dhcp6_parser.cc"
    break;

  case 273: // host_reservation_identifiers: "host-reservation-identifiers" $@48 ":" "[" host_reservation_identifiers_list "]"
#line 1116 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2088 "dhcp6_parser.cc"
    break;

  case 279: // hw_address_id: "hw-address"
#line 1130 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2097 "dhcp6_parser.cc"
    break;

  case 280: // flex_id: "flex-id"
#line 1135 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2106 "dhcp6_parser.cc"
    break;

  case 281: // $@49: %empty
#line 1142 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2118 "dhcp6_parser.cc"
    break;

  case 282: // relay_supplied_options: "relay-supplied-options" $@49 ":" "[" list_content "]"
#line 1148 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2127 "dhcp6_parser.cc"
    break;

  case 283: // $@50: %empty
#line 1155 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2139 "dhcp6_parser.cc"
    break;

  case 284: // dhcp_multi_threading: "multi-threading" $@50 ":" "{" multi_threading_params "}"
#line 1161 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2150 "dhcp6_parser.cc"
    break;

  case 293: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1180 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2160 "dhcp6_parser.cc"
    break;

  case 294: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1186 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2170 "dhcp6_parser.cc"
    break;

  case 295: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1192 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2180 "dhcp6_parser.cc"
    break;

  case 296: // $@51: %empty
#line 1198 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 297: // hooks_libraries: "hooks-libraries" $@51 ":" "[" hooks_libraries_list "]"
#line 1204 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 302: // $@52: %empty
#line 1217 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 303: // hooks_library: "{" $@52 hooks_params "}"
#line 1221 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 304: // $@53: %empty
#line 1227 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2231 "dhcp6_parser.cc"
    break;

  case 305: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1231 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2241 "dhcp6_parser.cc"
    break;

  case 311: // $@54: %empty
#line 1246 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2250 "dhcp6_parser.cc"
    break;

  case 312: // library: "library" $@54 ":" "constant string"
#line 1249 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2260 "dhcp6_parser.cc"
    break;

  case 313: // $@55: %empty
#line 1255 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2269 "dhcp6_parser.cc"
    break;

  case 314: // parameters: "parameters" $@55 ":" map_value
#line 1258 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2278 "dhcp6_parser.cc"
    break;

  case 315: // $@56: %empty
#line 1264 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2290 "dhcp6_parser.cc"
    break;

  case 316: // expired_leases_processing: "expired-leases-processing" $@56 ":" "{" expired_leases_params "}"
#line 1270 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2300 "dhcp6_parser.cc"
    break;

  case 325: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1288 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2310 "dhcp6_parser.cc"
    break;

  case 326: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1294 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2320 "dhcp6_parser.cc"
    break;

  case 327: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1300 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2330 "dhcp6_parser.cc"
    break;

  case 328: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1306 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2340 "dhcp6_parser.cc"
    break;

  case 329: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1312 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2350 "dhcp6_parser.cc"
    break;

  case 330: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1318 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2360 "dhcp6_parser.cc"
    break;

  case 331: // $@57: %empty
#line 1327 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2372 "dhcp6_parser.cc"
    break;

  case 332: // subnet6_list: "subnet6" $@57 ":" "[" subnet6_list_content "]"
#line 1333 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2381 "dhcp6_parser.cc"
    break;

  case 337: // $@58: %empty
#line 1353 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2391 "dhcp6_parser.cc"
    break;

  case 338: // subnet6: "{" $@58 subnet6_params "}"
#line 1357 "dhcp6_parser.yy"
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

  case 339: // $@59: %empty
#line 1379 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2427 "dhcp6_parser.cc"
    break;

  case 340: // sub_subnet6: "{" $@59 subnet6_params "}"
#line 1383 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2437 "dhcp6_parser.cc"
    break;

  case 386: // $@60: %empty
#line 1440 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp6_parser.cc"
    break;

  case 387: // subnet: "subnet" $@60 ":" "constant string"
#line 1443 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc"
    break;

  case 388: // $@61: %empty
#line 1449 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2465 "dhcp6_parser.cc"
    break;

  case 389: // interface: "interface" $@61 ":" "constant string"
#line 1452 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2475 "dhcp6_parser.cc"
    break;

  case 390: // $@62: %empty
#line 1458 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2484 "dhcp6_parser.cc"
    break;

  case 391: // interface_id: "interface-id" $@62 ":" "constant string"
#line 1461 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2494 "dhcp6_parser.cc"
    break;

  case 392: // $@63: %empty
#line 1467 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2503 "dhcp6_parser.cc"
    break;

  case 393: // client_class: "client-class" $@63 ":" "constant string"
#line 1470 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2513 "dhcp6_parser.cc"
    break;

  case 394: // $@64: %empty
#line 1476 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 395: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1482 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2534 "dhcp6_parser.cc"
    break;

  case 396: // reservations_global: "reservations-global" ":" "boolean"
#line 1487 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2544 "dhcp6_parser.cc"
    break;

  case 397: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1493 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2554 "dhcp6_parser.cc"
    break;

  case 398: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1499 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2564 "dhcp6_parser.cc"
    break;

  case 399: // $@65: %empty
#line 1505 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2573 "dhcp6_parser.cc"
    break;

  case 400: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1508 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2582 "dhcp6_parser.cc"
    break;

  case 401: // hr_mode: "disabled"
#line 1513 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2588 "dhcp6_parser.cc"
    break;

  case 402: // hr_mode: "out-of-pool"
#line 1514 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2594 "dhcp6_parser.cc"
    break;

  case 403: // hr_mode: "global"
#line 1515 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2600 "dhcp6_parser.cc"
    break;

  case 404: // hr_mode: "all"
#line 1516 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2606 "dhcp6_parser.cc"
    break;

  case 405: // id: "id" ":" "integer"
#line 1519 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2616 "dhcp6_parser.cc"
    break;

  case 406: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1525 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2626 "dhcp6_parser.cc"
    break;

  case 407: // $@66: %empty
#line 1533 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 408: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1539 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2647 "dhcp6_parser.cc"
    break;

  case 413: // $@67: %empty
#line 1554 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2657 "dhcp6_parser.cc"
    break;

  case 414: // shared_network: "{" $@67 shared_network_params "}"
#line 1558 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2665 "dhcp6_parser.cc"
    break;

  case 457: // $@68: %empty
#line 1612 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2677 "dhcp6_parser.cc"
    break;

  case 458: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1618 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2686 "dhcp6_parser.cc"
    break;

  case 459: // $@69: %empty
#line 1626 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2695 "dhcp6_parser.cc"
    break;

  case 460: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1629 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2703 "dhcp6_parser.cc"
    break;

  case 465: // $@70: %empty
#line 1645 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 466: // option_def_entry: "{" $@70 option_def_params "}"
#line 1649 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2725 "dhcp6_parser.cc"
    break;

  case 467: // $@71: %empty
#line 1660 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2735 "dhcp6_parser.cc"
    break;

  case 468: // sub_option_def: "{" $@71 option_def_params "}"
#line 1664 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2747 "dhcp6_parser.cc"
    break;

  case 484: // code: "code" ":" "integer"
#line 1696 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2757 "dhcp6_parser.cc"
    break;

  case 486: // $@72: %empty
#line 1704 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2766 "dhcp6_parser.cc"
    break;

  case 487: // option_def_type: "type" $@72 ":" "constant string"
#line 1707 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 488: // $@73: %empty
#line 1713 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2785 "dhcp6_parser.cc"
    break;

  case 489: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1716 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2795 "dhcp6_parser.cc"
    break;

  case 490: // $@74: %empty
#line 1722 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 491: // space: "space" $@74 ":" "constant string"
#line 1725 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2814 "dhcp6_parser.cc"
    break;

  case 493: // $@75: %empty
#line 1733 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2823 "dhcp6_parser.cc"
    break;

  case 494: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1736 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2833 "dhcp6_parser.cc"
    break;

  case 495: // option_def_array: "array" ":" "boolean"
#line 1742 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2843 "dhcp6_parser.cc"
    break;

  case 496: // $@76: %empty
#line 1752 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2855 "dhcp6_parser.cc"
    break;

  case 497: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1758 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2864 "dhcp6_parser.cc"
    break;

  case 502: // $@77: %empty
#line 1777 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2874 "dhcp6_parser.cc"
    break;

  case 503: // option_data_entry: "{" $@77 option_data_params "}"
#line 1781 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2883 "dhcp6_parser.cc"
    break;

  case 504: // $@78: %empty
#line 1789 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2893 "dhcp6_parser.cc"
    break;

  case 505: // sub_option_data: "{" $@78 option_data_params "}"
#line 1793 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2902 "dhcp6_parser.cc"
    break;

  case 520: // $@79: %empty
#line 1826 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2911 "dhcp6_parser.cc"
    break;

  case 521: // option_data_data: "data" $@79 ":" "constant string"
#line 1829 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 524: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1839 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2931 "dhcp6_parser.cc"
    break;

  case 525: // option_data_always_send: "always-send" ":" "boolean"
#line 1845 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2941 "dhcp6_parser.cc"
    break;

  case 526: // $@80: %empty
#line 1854 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2953 "dhcp6_parser.cc"
    break;

  case 527: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1860 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 532: // $@81: %empty
#line 1875 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2972 "dhcp6_parser.cc"
    break;

  case 533: // pool_list_entry: "{" $@81 pool_params "}"
#line 1879 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2982 "dhcp6_parser.cc"
    break;

  case 534: // $@82: %empty
#line 1885 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2992 "dhcp6_parser.cc"
    break;

  case 535: // sub_pool6: "{" $@82 pool_params "}"
#line 1889 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3002 "dhcp6_parser.cc"
    break;

  case 545: // $@83: %empty
#line 1908 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3011 "dhcp6_parser.cc"
    break;

  case 546: // pool_entry: "pool" $@83 ":" "constant string"
#line 1911 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3021 "dhcp6_parser.cc"
    break;

  case 547: // $@84: %empty
#line 1917 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3029 "dhcp6_parser.cc"
    break;

  case 548: // user_context: "user-context" $@84 ":" map_value
#line 1919 "dhcp6_parser.yy"
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

  case 549: // $@85: %empty
#line 1942 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3064 "dhcp6_parser.cc"
    break;

  case 550: // comment: "comment" $@85 ":" "constant string"
#line 1944 "dhcp6_parser.yy"
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

  case 551: // $@86: %empty
#line 1972 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3105 "dhcp6_parser.cc"
    break;

  case 552: // pd_pools_list: "pd-pools" $@86 ":" "[" pd_pools_list_content "]"
#line 1978 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3114 "dhcp6_parser.cc"
    break;

  case 557: // $@87: %empty
#line 1993 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3124 "dhcp6_parser.cc"
    break;

  case 558: // pd_pool_entry: "{" $@87 pd_pool_params "}"
#line 1997 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3136 "dhcp6_parser.cc"
    break;

  case 559: // $@88: %empty
#line 2005 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3146 "dhcp6_parser.cc"
    break;

  case 560: // sub_pd_pool: "{" $@88 pd_pool_params "}"
#line 2009 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3158 "dhcp6_parser.cc"
    break;

  case 574: // $@89: %empty
#line 2034 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3167 "dhcp6_parser.cc"
    break;

  case 575: // pd_prefix: "prefix" $@89 ":" "constant string"
#line 2037 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3177 "dhcp6_parser.cc"
    break;

  case 576: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2043 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3187 "dhcp6_parser.cc"
    break;

  case 577: // $@90: %empty
#line 2049 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3196 "dhcp6_parser.cc"
    break;

  case 578: // excluded_prefix: "excluded-prefix" $@90 ":" "constant string"
#line 2052 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3206 "dhcp6_parser.cc"
    break;

  case 579: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2058 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3216 "dhcp6_parser.cc"
    break;

  case 580: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2064 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3226 "dhcp6_parser.cc"
    break;

  case 581: // $@91: %empty
#line 2073 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3238 "dhcp6_parser.cc"
    break;

  case 582: // reservations: "reservations" $@91 ":" "[" reservations_list "]"
#line 2079 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3247 "dhcp6_parser.cc"
    break;

  case 587: // $@92: %empty
#line 2092 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 588: // reservation: "{" $@92 reservation_params "}"
#line 2096 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 589: // $@93: %empty
#line 2101 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 590: // sub_reservation: "{" $@93 reservation_params "}"
#line 2105 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3285 "dhcp6_parser.cc"
    break;

  case 606: // $@94: %empty
#line 2132 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3297 "dhcp6_parser.cc"
    break;

  case 607: // ip_addresses: "ip-addresses" $@94 ":" list_strings
#line 2138 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3306 "dhcp6_parser.cc"
    break;

  case 608: // $@95: %empty
#line 2143 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp6_parser.cc"
    break;

  case 609: // prefixes: "prefixes" $@95 ":" list_strings
#line 2149 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3327 "dhcp6_parser.cc"
    break;

  case 610: // $@96: %empty
#line 2154 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3336 "dhcp6_parser.cc"
    break;

  case 611: // duid: "duid" $@96 ":" "constant string"
#line 2157 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3346 "dhcp6_parser.cc"
    break;

  case 612: // $@97: %empty
#line 2163 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3355 "dhcp6_parser.cc"
    break;

  case 613: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2166 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3365 "dhcp6_parser.cc"
    break;

  case 614: // $@98: %empty
#line 2172 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3374 "dhcp6_parser.cc"
    break;

  case 615: // hostname: "hostname" $@98 ":" "constant string"
#line 2175 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3384 "dhcp6_parser.cc"
    break;

  case 616: // $@99: %empty
#line 2181 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3393 "dhcp6_parser.cc"
    break;

  case 617: // flex_id_value: "flex-id" $@99 ":" "constant string"
#line 2184 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3403 "dhcp6_parser.cc"
    break;

  case 618: // $@100: %empty
#line 2190 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3415 "dhcp6_parser.cc"
    break;

  case 619: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2196 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3424 "dhcp6_parser.cc"
    break;

  case 620: // $@101: %empty
#line 2204 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3436 "dhcp6_parser.cc"
    break;

  case 621: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2210 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3445 "dhcp6_parser.cc"
    break;

  case 624: // $@102: %empty
#line 2219 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3454 "dhcp6_parser.cc"
    break;

  case 625: // ip_address: "ip-address" $@102 ":" "constant string"
#line 2222 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3464 "dhcp6_parser.cc"
    break;

  case 626: // $@103: %empty
#line 2231 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3476 "dhcp6_parser.cc"
    break;

  case 627: // client_classes: "client-classes" $@103 ":" "[" client_classes_list "]"
#line 2237 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3485 "dhcp6_parser.cc"
    break;

  case 630: // $@104: %empty
#line 2246 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3495 "dhcp6_parser.cc"
    break;

  case 631: // client_class_entry: "{" $@104 client_class_params "}"
#line 2250 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3505 "dhcp6_parser.cc"
    break;

  case 644: // $@105: %empty
#line 2275 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3514 "dhcp6_parser.cc"
    break;

  case 645: // client_class_test: "test" $@105 ":" "constant string"
#line 2278 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3524 "dhcp6_parser.cc"
    break;

  case 646: // only_if_required: "only-if-required" ":" "boolean"
#line 2284 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3534 "dhcp6_parser.cc"
    break;

  case 647: // $@106: %empty
#line 2293 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3546 "dhcp6_parser.cc"
    break;

  case 648: // server_id: "server-id" $@106 ":" "{" server_id_params "}"
#line 2299 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3557 "dhcp6_parser.cc"
    break;

  case 660: // $@107: %empty
#line 2321 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3566 "dhcp6_parser.cc"
    break;

  case 661: // server_id_type: "type" $@107 ":" duid_type
#line 2324 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3575 "dhcp6_parser.cc"
    break;

  case 662: // duid_type: "LLT"
#line 2329 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3581 "dhcp6_parser.cc"
    break;

  case 663: // duid_type: "EN"
#line 2330 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3587 "dhcp6_parser.cc"
    break;

  case 664: // duid_type: "LL"
#line 2331 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3593 "dhcp6_parser.cc"
    break;

  case 665: // htype: "htype" ":" "integer"
#line 2334 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3603 "dhcp6_parser.cc"
    break;

  case 666: // $@108: %empty
#line 2340 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3612 "dhcp6_parser.cc"
    break;

  case 667: // identifier: "identifier" $@108 ":" "constant string"
#line 2343 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3622 "dhcp6_parser.cc"
    break;

  case 668: // time: "time" ":" "integer"
#line 2349 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3632 "dhcp6_parser.cc"
    break;

  case 669: // enterprise_id: "enterprise-id" ":" "integer"
#line 2355 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 670: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2363 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 671: // $@109: %empty
#line 2371 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3664 "dhcp6_parser.cc"
    break;

  case 672: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2377 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3673 "dhcp6_parser.cc"
    break;

  case 680: // $@110: %empty
#line 2393 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3682 "dhcp6_parser.cc"
    break;

  case 681: // socket_type: "socket-type" $@110 ":" "constant string"
#line 2396 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3692 "dhcp6_parser.cc"
    break;

  case 682: // $@111: %empty
#line 2402 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3701 "dhcp6_parser.cc"
    break;

  case 683: // socket_name: "socket-name" $@111 ":" "constant string"
#line 2405 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3711 "dhcp6_parser.cc"
    break;

  case 684: // $@112: %empty
#line 2414 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3723 "dhcp6_parser.cc"
    break;

  case 685: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2420 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3734 "dhcp6_parser.cc"
    break;

  case 694: // enable_queue: "enable-queue" ":" "boolean"
#line 2439 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3744 "dhcp6_parser.cc"
    break;

  case 695: // $@113: %empty
#line 2445 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3753 "dhcp6_parser.cc"
    break;

  case 696: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2448 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3763 "dhcp6_parser.cc"
    break;

  case 697: // capacity: "capacity" ":" "integer"
#line 2454 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3773 "dhcp6_parser.cc"
    break;

  case 698: // $@114: %empty
#line 2460 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3782 "dhcp6_parser.cc"
    break;

  case 699: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2463 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3791 "dhcp6_parser.cc"
    break;

  case 700: // $@115: %empty
#line 2470 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3803 "dhcp6_parser.cc"
    break;

  case 701: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2476 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 702: // $@116: %empty
#line 2483 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 703: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2487 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 724: // enable_updates: "enable-updates" ":" "boolean"
#line 2517 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3844 "dhcp6_parser.cc"
    break;

  case 725: // $@117: %empty
#line 2524 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3853 "dhcp6_parser.cc"
    break;

  case 726: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2527 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 727: // $@118: %empty
#line 2533 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3872 "dhcp6_parser.cc"
    break;

  case 728: // server_ip: "server-ip" $@118 ":" "constant string"
#line 2536 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3882 "dhcp6_parser.cc"
    break;

  case 729: // server_port: "server-port" ":" "integer"
#line 2542 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 730: // $@119: %empty
#line 2548 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3901 "dhcp6_parser.cc"
    break;

  case 731: // sender_ip: "sender-ip" $@119 ":" "constant string"
#line 2551 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 732: // sender_port: "sender-port" ":" "integer"
#line 2557 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3921 "dhcp6_parser.cc"
    break;

  case 733: // max_queue_size: "max-queue-size" ":" "integer"
#line 2563 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3931 "dhcp6_parser.cc"
    break;

  case 734: // $@120: %empty
#line 2569 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3940 "dhcp6_parser.cc"
    break;

  case 735: // ncr_protocol: "ncr-protocol" $@120 ":" ncr_protocol_value
#line 2572 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3949 "dhcp6_parser.cc"
    break;

  case 736: // ncr_protocol_value: "UDP"
#line 2578 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3955 "dhcp6_parser.cc"
    break;

  case 737: // ncr_protocol_value: "TCP"
#line 2579 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3961 "dhcp6_parser.cc"
    break;

  case 738: // $@121: %empty
#line 2582 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3970 "dhcp6_parser.cc"
    break;

  case 739: // ncr_format: "ncr-format" $@121 ":" "JSON"
#line 2585 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3980 "dhcp6_parser.cc"
    break;

  case 740: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2592 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3990 "dhcp6_parser.cc"
    break;

  case 741: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2599 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 742: // $@122: %empty
#line 2606 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4009 "dhcp6_parser.cc"
    break;

  case 743: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2609 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4018 "dhcp6_parser.cc"
    break;

  case 744: // $@123: %empty
#line 2615 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4027 "dhcp6_parser.cc"
    break;

  case 745: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2618 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4037 "dhcp6_parser.cc"
    break;

  case 746: // $@124: %empty
#line 2625 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4046 "dhcp6_parser.cc"
    break;

  case 747: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2628 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4056 "dhcp6_parser.cc"
    break;

  case 748: // $@125: %empty
#line 2635 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4065 "dhcp6_parser.cc"
    break;

  case 749: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2638 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4075 "dhcp6_parser.cc"
    break;

  case 750: // $@126: %empty
#line 2647 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4087 "dhcp6_parser.cc"
    break;

  case 751: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2653 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4097 "dhcp6_parser.cc"
    break;

  case 752: // $@127: %empty
#line 2659 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4107 "dhcp6_parser.cc"
    break;

  case 753: // sub_config_control: "{" $@127 config_control_params "}"
#line 2663 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4116 "dhcp6_parser.cc"
    break;

  case 758: // $@128: %empty
#line 2678 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4128 "dhcp6_parser.cc"
    break;

  case 759: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2684 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4137 "dhcp6_parser.cc"
    break;

  case 760: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2689 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 761: // $@129: %empty
#line 2697 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4159 "dhcp6_parser.cc"
    break;

  case 762: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2703 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4168 "dhcp6_parser.cc"
    break;

  case 765: // $@130: %empty
#line 2715 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4178 "dhcp6_parser.cc"
    break;

  case 766: // logger_entry: "{" $@130 logger_params "}"
#line 2719 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 776: // debuglevel: "debuglevel" ":" "integer"
#line 2736 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4196 "dhcp6_parser.cc"
    break;

  case 777: // $@131: %empty
#line 2742 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4205 "dhcp6_parser.cc"
    break;

  case 778: // severity: "severity" $@131 ":" "constant string"
#line 2745 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4215 "dhcp6_parser.cc"
    break;

  case 779: // $@132: %empty
#line 2751 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4227 "dhcp6_parser.cc"
    break;

  case 780: // output_options_list: "output_options" $@132 ":" "[" output_options_list_content "]"
#line 2757 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4236 "dhcp6_parser.cc"
    break;

  case 783: // $@133: %empty
#line 2766 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4246 "dhcp6_parser.cc"
    break;

  case 784: // output_entry: "{" $@133 output_params_list "}"
#line 2770 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4254 "dhcp6_parser.cc"
    break;

  case 792: // $@134: %empty
#line 2785 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4263 "dhcp6_parser.cc"
    break;

  case 793: // output: "output" $@134 ":" "constant string"
#line 2788 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4273 "dhcp6_parser.cc"
    break;

  case 794: // flush: "flush" ":" "boolean"
#line 2794 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4283 "dhcp6_parser.cc"
    break;

  case 795: // maxsize: "maxsize" ":" "integer"
#line 2800 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4293 "dhcp6_parser.cc"
    break;

  case 796: // maxver: "maxver" ":" "integer"
#line 2806 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4303 "dhcp6_parser.cc"
    break;

  case 797: // $@135: %empty
#line 2812 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4312 "dhcp6_parser.cc"
    break;

  case 798: // pattern: "pattern" $@135 ":" "constant string"
#line 2815 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4322 "dhcp6_parser.cc"
    break;


#line 4326 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -967;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     376,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,    41,    33,    58,    77,    99,
     103,   131,   139,   186,   206,   251,   258,   293,   295,   329,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,    33,  -135,
     132,   116,    37,   537,   161,   191,    26,    86,    60,   274,
     -82,   523,   265,  -967,   110,   200,   246,   226,   318,  -967,
     330,  -967,  -967,  -967,  -967,  -967,  -967,   342,   377,   394,
     400,   402,   403,   404,   412,   413,   414,   420,   421,   423,
     424,  -967,   425,   426,   428,   429,   432,  -967,  -967,  -967,
     433,   434,   435,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
     436,   438,   440,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,   442,  -967,  -967,  -967,  -967,  -967,  -967,   444,
    -967,   445,  -967,    75,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,   448,  -967,    96,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   449,
     450,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   106,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,   109,  -967,  -967,  -967,  -967,  -967,
     451,  -967,   452,   454,  -967,  -967,  -967,  -967,  -967,  -967,
     154,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   354,   334,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   356,  -967,
    -967,   460,  -967,  -967,  -967,   464,  -967,  -967,   372,   389,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   465,   468,  -967,  -967,  -967,  -967,   470,
     480,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   155,  -967,  -967,  -967,   469,  -967,  -967,
     481,  -967,   484,   485,  -967,  -967,   488,   490,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,   197,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   491,   211,  -967,  -967,  -967,  -967,    33,
      33,  -967,   278,   492,  -967,   493,   494,   496,   501,   503,
     504,   302,   304,   305,   307,   309,   310,   317,   319,   301,
     313,   320,   321,   324,   332,   532,   336,   338,   337,   340,
     341,   547,   549,   550,   346,   348,   350,   557,   558,   560,
     561,   562,   578,   579,   375,   390,   392,   594,   596,   607,
     608,   610,   611,   612,   613,   616,   416,   617,   623,   624,
     625,   626,   627,   431,   638,  -967,   116,  -967,   639,   439,
      37,  -967,   643,   645,   646,   647,   648,   447,   446,   657,
     659,   661,   537,  -967,   662,   161,  -967,   663,   461,   665,
     463,   466,   191,  -967,   667,   668,   675,   676,   677,   692,
     694,  -967,    26,  -967,   695,   697,   495,   701,   702,   703,
     499,  -967,    60,   705,   502,   505,  -967,   274,   706,   708,
     159,  -967,   506,   709,   712,   512,   716,   514,   515,   719,
     720,   516,   517,   723,   724,   731,   732,   523,  -967,   733,
     531,   265,  -967,  -967,  -967,   735,   534,   535,   693,   750,
     751,   752,   737,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,   554,  -967,  -967,
    -967,  -967,  -967,  -117,   565,   568,  -967,  -967,  -967,   770,
     771,   772,   773,   774,   573,   244,  -967,  -967,  -967,   775,
     777,   778,   779,   780,   782,   783,   786,   789,  -967,   792,
     793,   794,   795,   583,   584,  -967,   801,  -967,   802,  -967,
    -967,   803,   804,   604,   605,   614,  -967,  -967,   802,   615,
     806,  -967,   618,  -967,   619,  -967,   620,  -967,  -967,  -967,
     802,   802,   802,   621,   622,   628,   629,  -967,   630,   631,
    -967,   632,   633,   634,  -967,  -967,   635,  -967,  -967,  -967,
     636,   774,  -967,  -967,   637,   640,  -967,   641,  -967,  -967,
     135,   609,  -967,  -967,  -117,   642,   644,   649,  -967,   809,
    -967,  -967,    33,   116,  -967,   265,    37,   298,   298,   810,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   811,
     812,   815,   822,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,   -86,    33,   277,   717,   823,   825,   826,    61,    64,
     208,     0,   220,   523,  -967,  -967,   837,  -967,  -967,   838,
     842,  -967,  -967,  -967,  -967,  -967,   -77,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,   810,  -967,   212,   213,
     214,  -967,  -967,  -967,  -967,   736,   847,   848,   849,   850,
    -967,   852,   853,  -967,  -967,  -967,  -967,   854,   855,   856,
     857,  -967,   227,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,   230,  -967,   858,   813,  -967,
    -967,   859,   860,  -967,  -967,   861,   863,  -967,  -967,   862,
     866,  -967,  -967,   864,   868,  -967,  -967,  -967,    94,  -967,
    -967,  -967,   867,  -967,  -967,  -967,   198,  -967,  -967,  -967,
    -967,   243,  -967,  -967,  -967,   241,  -967,  -967,   869,   871,
    -967,  -967,   872,   876,  -967,   877,   878,   879,   880,   881,
     882,   266,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,   883,   884,   885,  -967,  -967,  -967,  -967,   285,  -967,
    -967,  -967,  -967,  -967,  -967,   886,   887,   888,  -967,   303,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,   315,  -967,  -967,  -967,   889,  -967,   890,  -967,  -967,
    -967,   357,  -967,  -967,  -967,  -967,  -967,   358,  -967,   256,
    -967,   656,  -967,   874,   892,  -967,  -967,   891,   893,  -967,
    -967,  -967,   895,  -967,   894,  -967,  -967,  -967,   897,   900,
     901,   902,   691,   690,   700,   699,   704,   905,   707,   710,
     906,   908,   911,   914,   714,   721,   722,   739,   298,  -967,
    -967,   298,  -967,   810,   537,  -967,   811,    60,  -967,   812,
     274,  -967,   815,   696,  -967,   822,   -86,  -967,  -967,   277,
    -967,   926,   717,  -967,   196,   823,  -967,    26,  -967,   825,
     -82,  -967,   826,   740,   741,   755,   761,   767,   796,    61,
    -967,   936,   955,   800,   808,   830,    64,  -967,   784,   833,
     834,   208,  -967,   983,   992,     0,  -967,   790,   996,   839,
    1043,   220,  -967,  -967,   199,   837,  -967,  -967,  1044,  1046,
     161,  -967,   838,   191,  -967,   842,  1048,  -967,  -967,   398,
     666,   851,   865,  -967,  -967,  -967,  -967,  -967,   870,  -967,
    -967,   333,   873,   875,   896,  -967,  -967,  -967,  -967,  -967,
     360,  -967,   371,  -967,  1045,  -967,  1047,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,   379,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   903,  -967,  -967,  1052,  -967,  -967,  -967,
    -967,  -967,  1050,  1056,  -967,  -967,  -967,  -967,  -967,  1053,
    -967,   381,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
     271,   904,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
     907,   909,  -967,  -967,   910,  -967,    33,  -967,  -967,  1058,
    -967,  -967,  -967,  -967,  -967,   385,  -967,  -967,  -967,  -967,
    -967,  -967,   912,   387,  -967,   388,  -967,   913,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   696,  -967,
    -967,  1060,   898,  -967,   196,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  1061,   899,  1063,   199,
    -967,  -967,  -967,  -967,  -967,  -967,   915,  -967,  -967,  1055,
    -967,   916,  -967,  -967,  1062,  -967,  -967,   314,  -967,  -122,
    1062,  -967,  -967,  1064,  1066,  1068,  -967,   391,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  1069,   917,   918,   920,  1070,
    -122,  -967,   922,  -967,  -967,  -967,   923,  -967,  -967,  -967
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   171,     9,   339,    11,
     534,    13,   559,    15,   589,    17,   459,    19,   467,    21,
     504,    23,   304,    25,   702,    27,   752,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   591,     0,   469,   506,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   127,   750,   169,   183,   185,   187,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,     0,     0,     0,     0,     0,   146,   153,   155,
       0,     0,     0,   331,   457,   496,   407,   547,   549,   399,
       0,     0,     0,   264,   281,   272,   257,   626,   581,   296,
     315,   647,     0,   283,   671,   684,   700,   159,   161,     0,
     761,     0,   126,     0,    64,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   105,   106,   107,   108,   109,    75,
     113,   114,   115,   116,   117,   118,   119,   120,   111,   112,
     121,   122,   123,   100,   125,    78,    79,    80,    81,    97,
      82,    84,    83,   124,    88,    89,    76,   102,   103,   104,
     101,    77,    86,    87,    95,    96,    98,    85,    90,    91,
      92,    93,    94,    99,   110,   180,     0,   179,     0,   173,
     175,   176,   177,   178,   526,   551,   386,   388,   390,     0,
       0,   394,   392,   620,   385,   343,   344,   345,   346,   347,
     348,   349,   350,   369,   370,   371,   372,   373,   376,   377,
     378,   379,   380,   381,   382,   383,   374,   375,   384,     0,
     341,   354,   355,   356,   359,   360,   363,   364,   365,   362,
     357,   358,   351,   352,   367,   368,   353,   361,   366,   545,
     544,   540,   541,   539,     0,   536,   538,   542,   543,   574,
       0,   577,     0,     0,   573,   567,   568,   566,   571,   572,
       0,   561,   563,   564,   569,   570,   565,   618,   606,   608,
     610,   612,   614,   616,   605,   602,   603,   604,     0,   592,
     593,   597,   598,   595,   599,   600,   601,   596,     0,   486,
     232,     0,   490,   488,   493,     0,   482,   483,     0,   470,
     471,   473,   485,   474,   475,   476,   492,   477,   478,   479,
     480,   481,   520,     0,     0,   518,   519,   522,   523,     0,
     507,   508,   510,   511,   512,   513,   514,   515,   516,   517,
     311,   313,   308,     0,   306,   309,   310,     0,   725,   727,
       0,   730,     0,     0,   734,   738,     0,     0,   742,   744,
     746,   748,   723,   721,   722,     0,   704,   706,   718,   707,
     708,   709,   710,   711,   712,   713,   714,   715,   716,   717,
     719,   720,   758,     0,     0,   754,   756,   757,    46,     0,
       0,    39,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,    63,     0,     0,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   340,     0,     0,   535,     0,     0,     0,
       0,     0,     0,   560,     0,     0,     0,     0,     0,     0,
       0,   590,     0,   460,     0,     0,     0,     0,     0,     0,
       0,   468,     0,     0,     0,     0,   505,     0,     0,     0,
       0,   305,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   703,     0,
       0,     0,   753,    50,    43,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,     0,   164,   165,
     143,   144,   145,     0,     0,     0,   157,   158,   163,     0,
       0,     0,     0,     0,     0,     0,   396,   397,   398,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   670,     0,
       0,     0,     0,     0,     0,   168,     0,    65,     0,   182,
     174,     0,     0,     0,     0,     0,   405,   406,     0,     0,
       0,   342,     0,   537,     0,   576,     0,   579,   580,   562,
       0,     0,     0,     0,     0,     0,     0,   594,     0,     0,
     484,     0,     0,     0,   495,   472,     0,   524,   525,   509,
       0,     0,   307,   724,     0,     0,   729,     0,   732,   733,
       0,     0,   740,   741,     0,     0,     0,     0,   705,     0,
     760,   755,     0,     0,   128,     0,     0,     0,     0,   189,
     167,   148,   149,   150,   151,   152,   147,   154,   156,   333,
     461,   498,   409,    40,   548,   550,   401,   402,   403,   404,
     400,     0,    47,     0,     0,     0,   583,   298,     0,     0,
       0,     0,     0,     0,   160,   162,     0,    51,   181,   528,
     553,   387,   389,   391,   395,   393,     0,   546,   575,   578,
     619,   607,   609,   611,   613,   615,   617,   487,   233,   491,
     489,   494,   521,   312,   314,   726,   728,   731,   736,   737,
     735,   739,   743,   745,   747,   749,   189,    44,     0,     0,
       0,   219,   225,   227,   229,     0,     0,     0,     0,     0,
     248,     0,     0,   239,   251,   253,   255,     0,     0,     0,
       0,   218,     0,   195,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   209,   210,   217,   211,   212,   213,
     207,   208,   214,   215,   216,     0,   193,     0,   190,   191,
     337,     0,   334,   335,   465,     0,   462,   463,   502,     0,
     499,   500,   413,     0,   410,   411,   270,   271,     0,   266,
     268,   269,     0,   279,   280,   276,     0,   274,   277,   278,
     262,     0,   259,   261,   630,     0,   628,   587,     0,   584,
     585,   302,     0,   299,   300,     0,     0,     0,     0,     0,
       0,     0,   317,   319,   320,   321,   322,   323,   324,   660,
     666,     0,     0,     0,   659,   656,   657,   658,     0,   649,
     651,   654,   652,   653,   655,     0,     0,     0,   292,     0,
     285,   287,   288,   289,   290,   291,   680,   682,   679,   677,
     678,     0,   673,   675,   676,     0,   695,     0,   698,   691,
     692,     0,   686,   688,   689,   690,   693,     0,   765,     0,
     763,    53,   532,     0,   529,   530,   557,     0,   554,   555,
     624,   623,     0,   622,     0,    61,   751,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   184,
     186,     0,   188,     0,     0,   332,     0,   469,   458,     0,
     506,   497,     0,     0,   408,     0,     0,   265,   282,     0,
     273,     0,     0,   258,   632,     0,   627,   591,   582,     0,
       0,   297,     0,     0,     0,     0,     0,     0,     0,     0,
     316,     0,     0,     0,     0,     0,     0,   648,     0,     0,
       0,     0,   284,     0,     0,     0,   672,     0,     0,     0,
       0,     0,   685,   701,     0,     0,   762,    55,     0,    54,
       0,   527,     0,     0,   552,     0,     0,   621,   759,     0,
       0,     0,     0,   231,   234,   235,   236,   237,     0,   250,
     238,     0,     0,     0,     0,   245,   246,   247,   244,   196,
       0,   192,     0,   336,     0,   464,     0,   501,   456,   431,
     432,   433,   435,   436,   437,   421,   422,   440,   441,   442,
     443,   444,   447,   448,   449,   450,   451,   452,   453,   454,
     445,   446,   455,   417,   418,   419,   420,   429,   430,   426,
     427,   428,   425,   434,     0,   415,   423,   438,   439,   424,
     412,   267,   275,     0,   260,   644,     0,   642,   643,   639,
     640,   641,     0,   633,   634,   636,   637,   638,   629,     0,
     586,     0,   301,   325,   326,   327,   328,   329,   330,   318,
       0,     0,   665,   668,   669,   650,   293,   294,   295,   286,
       0,     0,   674,   694,     0,   697,     0,   687,   779,     0,
     777,   775,   769,   773,   774,     0,   767,   771,   772,   770,
     764,    52,     0,     0,   531,     0,   556,     0,   221,   222,
     223,   224,   220,   226,   228,   230,   249,   241,   242,   243,
     240,   252,   254,   256,   194,   338,   466,   503,     0,   414,
     263,     0,     0,   631,     0,   588,   303,   662,   663,   664,
     661,   667,   681,   683,   696,   699,     0,     0,     0,     0,
     766,    56,   533,   558,   625,   416,     0,   646,   635,     0,
     776,     0,   768,   645,     0,   778,   783,     0,   781,     0,
       0,   780,   792,     0,     0,     0,   797,     0,   785,   787,
     788,   789,   790,   791,   782,     0,     0,     0,     0,     0,
       0,   784,     0,   794,   795,   796,     0,   786,   793,   798
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,   -10,  -967,  -564,  -967,
     406,  -967,  -967,  -967,  -967,   353,  -967,  -595,  -967,  -967,
    -967,   -71,  -967,  -967,  -967,  -967,  -967,  -967,   393,   592,
    -967,  -967,   -59,   -43,   -42,   -40,   -39,   -28,   -27,   -26,
     -23,   -21,   -15,    -9,    -3,  -967,    -1,    17,    18,    20,
    -967,   396,    25,  -967,    28,  -967,    30,    32,    35,  -967,
      38,  -967,    40,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,   386,   593,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   308,  -967,   102,  -967,  -676,   111,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   -67,
    -967,  -714,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,    85,  -967,  -967,  -967,  -967,
    -967,    92,  -698,  -967,  -967,  -967,  -967,    91,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,    62,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,    79,  -967,  -967,  -967,    82,   555,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,    78,  -967,  -967,  -967,
    -967,  -967,  -967,  -966,  -967,  -967,  -967,   108,  -967,  -967,
    -967,   112,   597,  -967,  -967,  -965,  -967,  -964,  -967,    51,
    -967,    55,  -967,    42,    45,    46,    50,  -967,  -967,  -967,
    -958,  -967,  -967,  -967,  -967,   105,  -967,  -967,  -120,  1026,
    -967,  -967,  -967,  -967,  -967,   122,  -967,  -967,  -967,   125,
    -967,   582,  -967,   -66,  -967,  -967,  -967,  -967,  -967,   -47,
    -967,  -967,  -967,  -967,  -967,    13,  -967,  -967,  -967,   128,
    -967,  -967,  -967,   127,  -967,   586,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,    72,  -967,  -967,
    -967,    80,   650,  -967,  -967,   -55,  -967,     1,  -967,  -967,
    -967,  -967,  -967,    76,  -967,  -967,  -967,    81,   652,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,   -57,  -967,  -967,  -967,
     123,  -967,  -967,  -967,   126,  -967,   651,   395,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -957,  -967,  -967,  -967,  -967,  -967,  -967,  -967,   130,
    -967,  -967,  -967,   -88,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,   113,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,   107,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,    97,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,   407,   580,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,  -967,
    -967,  -967,  -967,  -967,   453,   585,  -967,  -967,  -967,  -967,
    -967,  -967,    98,  -967,  -967,   -95,  -967,  -967,  -967,  -967,
    -967,  -967,  -115,  -967,  -967,  -131,  -967,  -967,  -967,  -967,
    -967,  -967,  -967
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     714,    87,    88,    41,    68,    84,    85,   738,   941,  1048,
    1049,   801,    43,    70,    90,   423,    45,    71,   153,   154,
     155,   425,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     451,   706,   174,   452,   175,   453,   176,   177,   178,   481,
     179,   482,   180,   181,   182,   183,   445,   184,   185,   427,
      47,    72,   218,   219,   220,   488,   221,   186,   428,   187,
     429,   188,   430,   827,   828,   829,   981,   802,   803,   804,
     958,  1202,   805,   959,   806,   960,   807,   961,   808,   809,
     525,   810,   811,   812,   813,   814,   815,   970,  1210,   816,
     817,   818,   819,   820,   967,   821,   822,   971,   823,   972,
     824,   973,   189,   470,   861,   862,   863,  1001,   190,   467,
     848,   849,   850,   851,   191,   469,   856,   857,   858,   859,
     192,   468,   193,   477,   909,   910,   911,   912,   913,   194,
     473,   872,   873,   874,  1010,    63,    80,   373,   374,   375,
     538,   376,   539,   195,   474,   881,   882,   883,   884,   885,
     886,   887,   888,   196,   457,   831,   832,   833,   984,    49,
      73,   259,   260,   261,   494,   262,   495,   263,   496,   264,
     500,   265,   499,   197,   198,   199,   200,   463,   720,   270,
     271,   201,   460,   843,   844,   845,   993,  1124,  1125,   202,
     458,    57,    77,   835,   836,   837,   987,    59,    78,   338,
     339,   340,   341,   342,   343,   344,   524,   345,   528,   346,
     527,   347,   348,   529,   349,   203,   459,   839,   840,   841,
     990,    61,    79,   359,   360,   361,   362,   363,   533,   364,
     365,   366,   367,   273,   492,   943,   944,   945,  1050,    51,
      74,   284,   285,   286,   504,   204,   461,   205,   462,   276,
     493,   947,   948,   949,  1053,    53,    75,   300,   301,   302,
     507,   303,   304,   509,   305,   306,   206,   472,   868,   869,
     870,  1007,    55,    76,   318,   319,   320,   321,   515,   322,
     516,   323,   517,   324,   518,   325,   519,   326,   520,   327,
     514,   278,   501,   952,   953,  1056,   207,   471,   865,   866,
    1004,  1142,  1143,  1144,  1145,  1146,  1221,  1147,   208,   475,
     898,   899,   900,  1021,  1230,   901,   902,  1022,   903,   904,
     209,   210,   478,   921,   922,   923,  1033,   924,  1034,   211,
     479,   931,   932,   933,   934,  1038,   935,   936,  1040,   212,
     480,    65,    81,   395,   396,   397,   398,   543,   399,   544,
     400,   401,   546,   402,   403,   404,   549,   770,   405,   550,
     406,   407,   408,   553,   409,   554,   410,   555,   411,   556,
     213,   426,    67,    82,   414,   415,   416,   559,   417,   214,
     484,   939,   940,  1044,  1185,  1186,  1187,  1188,  1238,  1189,
    1236,  1257,  1258,  1259,  1267,  1268,  1269,  1275,  1270,  1271,
    1272,  1273,  1279
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     152,   217,   234,   280,   294,   314,    38,   336,   355,   372,
     392,   337,   356,   357,   235,   895,   277,   222,   274,   287,
     298,   316,   825,   350,   368,   855,   393,  1114,  1115,  1116,
     236,   237,   358,   238,   239,  1123,  1129,   846,    31,   713,
      32,    30,    33,   744,   308,   240,   241,   242,   370,   371,
     243,   950,   244,   215,   216,   750,   751,   752,   245,   701,
     702,   703,   704,  1262,   246,    42,  1263,  1264,  1265,  1266,
     247,    86,   248,   223,   275,   288,   299,   317,   486,   351,
     369,   329,   394,   487,    44,   889,   272,   283,   297,   315,
     249,   250,   705,   251,   786,   127,   128,   996,   252,   490,
     997,   253,   125,   254,   491,   255,    46,   713,   256,   502,
      48,   257,   505,   258,   503,   266,   418,   506,   267,   268,
     847,   127,   128,   269,   151,   281,   295,    91,    92,   282,
     296,    93,   127,   128,    94,    95,    96,   330,    50,   331,
     332,   307,    89,   333,   334,   335,    52,   308,   309,   310,
     311,   312,   313,   916,   917,   127,   128,   512,   540,   127,
     128,   124,   513,   541,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,    54,   875,   876,   877,   878,   879,   880,
     557,   999,   126,   419,  1000,   558,   151,   890,   891,   892,
     893,   127,   128,    56,   561,   486,   561,   490,   129,   562,
     955,   956,   957,   130,   131,   132,   133,   134,   135,   136,
     978,   137,   151,   978,   421,   979,   138,   125,   980,    34,
      35,    36,    37,   151,  1005,   139,  1002,  1006,   140,   279,
     420,  1003,  1114,  1115,  1116,   141,   127,   128,    58,  1045,
    1123,  1129,  1046,   142,   143,    60,   151,   125,   144,  1019,
     151,   145,   125,   330,  1020,   146,   330,   231,   412,   413,
     232,   289,   290,   291,   292,   293,   127,   128,  1026,   370,
     371,   127,   128,  1027,   127,   128,   147,   148,   149,   150,
      62,   855,    64,   127,   128,  1080,  1031,   231,   768,   769,
     232,  1032,   895,  1135,  1136,   127,   128,  1260,  1035,   781,
    1261,   422,   151,  1036,   782,   783,   784,   785,   786,   787,
     788,   789,   790,   791,   792,   793,    66,   522,   424,   794,
     795,   796,   797,   798,   799,   800,   431,   716,   717,   718,
     719,   330,   352,   331,   332,   353,   354,   905,   906,   907,
    1041,   557,   521,   978,   523,  1042,  1043,   151,  1214,   127,
     128,  1207,  1208,  1209,   502,   330,   925,   926,   927,  1215,
     531,   432,  1218,  1178,   540,  1179,  1180,  1219,  1239,  1226,
     505,   512,   532,  1240,  1280,  1242,  1243,   151,   433,  1281,
     846,   853,   151,   854,   434,   151,   435,   436,   437,   563,
     564,  1227,  1228,  1229,   151,   152,   438,   439,   440,   217,
    1198,  1199,  1200,  1201,   441,   442,   928,   443,   444,   446,
     447,   234,   448,   449,   280,   222,   450,   454,   455,   456,
     464,   294,   465,   235,   466,   277,   476,   274,   483,   485,
     287,   314,   489,   497,   498,   508,   510,   298,   511,   236,
     237,   336,   238,   239,   526,   337,   355,   316,   530,   534,
     356,   357,   535,   542,   240,   241,   242,   350,   536,   243,
     151,   244,   368,   537,   565,   545,   392,   245,   547,   548,
     358,   223,   551,   246,   552,   560,   566,   567,   568,   247,
     569,   248,   393,   275,   151,   570,   288,   571,   572,   573,
     581,   574,   575,   299,   576,   272,   577,   578,   283,   249,
     250,   582,   251,   317,   579,   297,   580,   252,   583,   584,
     253,   585,   254,   351,   255,   315,   587,   256,   369,   586,
     257,   693,   258,   588,   266,   589,   590,   267,   268,   591,
     592,   593,   269,   594,   595,   596,   281,   597,   394,   598,
     282,   599,   600,   295,   601,   602,   603,   296,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   604,   605,   606,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   609,   607,
     610,   608,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   611,   612,   125,   613,   614,   615,   616,   127,   128,
     617,   619,   152,   618,   224,   217,   225,   620,   621,   622,
     623,   624,   127,   128,   226,   227,   228,   229,   230,   129,
     625,   222,   626,   628,   130,   131,   132,   631,   629,   632,
     633,   634,   635,   231,   636,   637,   232,   138,   894,   908,
     918,   638,   392,   639,   233,   640,   642,   644,   645,   646,
     647,   650,   651,   648,   896,   914,   919,   929,   393,   652,
     653,   654,   777,   377,   378,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   655,   223,   656,   658,
     695,   659,   660,   390,   391,   661,   662,   663,   664,   666,
     670,   667,   671,   674,   668,   673,   675,   147,   148,   676,
     677,   678,   679,   680,   681,   682,   683,   684,   685,   151,
     897,   915,   920,   930,   394,   686,   687,   689,   690,   692,
     962,   694,   699,   151,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   696,   697,   698,
     700,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   707,   125,   330,   708,   709,   710,   711,   712,   715,
     721,    32,   722,   723,   771,   725,   724,   726,   727,   734,
     735,   127,   128,   728,   227,   228,   729,   230,   129,   730,
     731,   732,   733,   130,   131,   132,   736,   737,   739,   740,
     741,   742,   231,   746,   776,   232,   983,   826,   830,   834,
     743,   745,   838,   233,   747,   748,   749,   753,   754,   842,
     864,   860,   867,   871,   755,   756,   757,   758,   759,   760,
     761,   762,   763,   765,   938,   942,   766,   767,   773,   946,
     774,   963,   964,   965,   966,   775,   968,   969,   974,   975,
     976,   977,  1047,   986,   982,   985,   989,   988,   991,   992,
     994,   995,  1203,   998,  1009,  1008,   147,   148,  1011,  1012,
    1051,  1013,  1014,  1015,  1016,  1017,  1018,  1023,  1024,  1025,
    1028,  1029,  1030,  1037,  1039,  1052,  1055,  1054,  1063,  1064,
    1058,  1059,   151,  1057,  1060,  1061,  1062,  1065,  1066,  1068,
    1071,  1067,  1072,   234,  1069,  1073,   336,  1070,  1074,   355,
     337,  1075,  1088,   356,   357,   235,  1113,   277,  1076,   274,
    1133,  1077,   350,  1137,  1089,   368,   314,  1138,  1127,   372,
    1160,   236,   237,   358,   238,   239,  1078,  1153,  1154,  1140,
    1090,  1091,   316,  1092,  1093,   894,   240,   241,   242,  1161,
     908,   243,  1155,   244,   918,  1094,  1095,  1096,  1156,   245,
    1097,   896,  1098,  1181,  1157,   246,   914,  1182,  1099,   280,
     919,   247,   294,   248,  1100,   275,   929,  1170,   351,  1183,
    1101,   369,  1102,  1166,  1128,   287,  1171,   272,   298,  1173,
    1174,   249,   250,  1158,   251,  1141,  1126,  1162,   317,   252,
    1103,  1104,   253,  1105,   254,  1163,   255,  1139,  1106,   256,
     315,  1107,   257,  1108,   258,  1109,   266,   897,  1110,   267,
     268,  1111,   915,  1112,   269,  1119,   920,  1164,  1120,  1121,
    1167,  1168,   930,  1122,  1117,  1184,  1175,  1176,  1118,  1192,
    1191,   288,  1197,  1216,   299,  1217,  1222,  1204,  1223,  1224,
    1254,  1225,  1237,   283,  1246,  1249,   297,  1251,  1276,  1256,
    1277,  1205,  1278,  1282,  1286,   852,  1206,   764,   627,  1211,
     772,  1212,   780,   630,   954,  1081,   778,  1134,  1131,  1079,
    1132,  1152,  1151,  1169,  1083,   672,  1082,  1159,  1245,   641,
    1130,   281,  1213,   328,   295,   282,  1250,  1247,   296,  1220,
    1231,  1085,  1084,  1232,   665,  1233,  1234,  1086,  1241,  1244,
    1087,  1253,  1255,   669,  1194,  1284,  1283,  1285,  1288,  1289,
    1193,  1196,  1150,  1149,  1195,  1148,  1248,   688,  1177,  1165,
     937,   951,  1172,  1190,  1252,  1274,   691,  1088,   779,  1287,
       0,  1113,     0,  1137,     0,   643,     0,  1138,     0,  1089,
       0,     0,     0,  1127,   649,     0,  1235,     0,  1181,  1140,
       0,     0,  1182,   657,     0,  1090,  1091,     0,  1092,  1093,
       0,     0,     0,     0,  1183,     0,     0,     0,     0,     0,
    1094,  1095,  1096,     0,     0,  1097,     0,  1098,     0,     0,
       0,     0,     0,  1099,     0,     0,     0,     0,     0,  1100,
       0,     0,     0,     0,     0,  1101,     0,  1102,     0,  1128,
       0,     0,     0,     0,     0,  1141,     0,     0,     0,     0,
       0,  1126,     0,     0,     0,  1103,  1104,  1139,  1105,     0,
    1184,     0,     0,  1106,     0,     0,  1107,     0,  1108,     0,
    1109,     0,     0,  1110,     0,     0,  1111,     0,  1112,     0,
    1119,     0,     0,  1120,  1121,     0,     0,     0,  1122,  1117,
       0,     0,     0,  1118
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    78,    79,    79,    73,   729,    73,    72,    73,    74,
      75,    76,   698,    78,    79,   723,    81,   993,   993,   993,
      73,    73,    79,    73,    73,   993,   993,   123,     5,   603,
       7,     0,     9,   638,   121,    73,    73,    73,   130,   131,
      73,   128,    73,    16,    17,   650,   651,   652,    73,   176,
     177,   178,   179,   185,    73,     7,   188,   189,   190,   191,
      73,   206,    73,    72,    73,    74,    75,    76,     3,    78,
      79,    21,    81,     8,     7,    21,    73,    74,    75,    76,
      73,    73,   209,    73,    30,    95,    96,     3,    73,     3,
       6,    73,    76,    73,     8,    73,     7,   671,    73,     3,
       7,    73,     3,    73,     8,    73,     6,     8,    73,    73,
     206,    95,    96,    73,   206,    74,    75,    11,    12,    74,
      75,    15,    95,    96,    18,    19,    20,    77,     7,    79,
      80,   115,    10,    83,    84,    85,     7,   121,   122,   123,
     124,   125,   126,   153,   154,    95,    96,     3,     3,    95,
      96,    75,     8,     8,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,     7,   133,   134,   135,   136,   137,   138,
       3,     3,    86,     3,     6,     8,   206,   143,   144,   145,
     146,    95,    96,     7,     3,     3,     3,     3,   102,     8,
       8,     8,     8,   107,   108,   109,   110,   111,   112,   113,
       3,   115,   206,     3,     8,     8,   120,    76,     8,   206,
     207,   208,   209,   206,     3,   129,     3,     6,   132,    88,
       4,     8,  1218,  1218,  1218,   139,    95,    96,     7,     3,
    1218,  1218,     6,   147,   148,     7,   206,    76,   152,     3,
     206,   155,    76,    77,     8,   159,    77,   116,    13,    14,
     119,    90,    91,    92,    93,    94,    95,    96,     3,   130,
     131,    95,    96,     8,    95,    96,   180,   181,   182,   183,
       7,   999,     7,    95,    96,   981,     3,   116,   173,   174,
     119,     8,  1026,   117,   118,    95,    96,     3,     3,    21,
       6,     3,   206,     8,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     7,     3,     8,    41,
      42,    43,    44,    45,    46,    47,     4,   103,   104,   105,
     106,    77,    78,    79,    80,    81,    82,   149,   150,   151,
       3,     3,     8,     3,     8,     8,     8,   206,     8,    95,
      96,    38,    39,    40,     3,    77,   156,   157,   158,     8,
       8,     4,     3,   184,     3,   186,   187,     8,     3,     8,
       3,     3,     3,     8,     3,     8,     8,   206,     4,     8,
     123,   124,   206,   126,     4,   206,     4,     4,     4,   419,
     420,   140,   141,   142,   206,   486,     4,     4,     4,   490,
      22,    23,    24,    25,     4,     4,   206,     4,     4,     4,
       4,   502,     4,     4,   505,   490,     4,     4,     4,     4,
       4,   512,     4,   502,     4,   502,     4,   502,     4,     4,
     505,   522,     4,     4,     4,     4,     4,   512,     4,   502,
     502,   532,   502,   502,     4,   532,   537,   522,     4,     4,
     537,   537,     4,     4,   502,   502,   502,   532,     8,   502,
     206,   502,   537,     3,   206,     4,   557,   502,     4,     4,
     537,   490,     4,   502,     4,     4,     4,     4,     4,   502,
       4,   502,   557,   502,   206,     4,   505,     4,     4,   207,
     209,   207,   207,   512,   207,   502,   207,   207,   505,   502,
     502,   208,   502,   522,   207,   512,   207,   502,   208,   208,
     502,   207,   502,   532,   502,   522,     4,   502,   537,   207,
     502,     7,   502,   207,   502,   207,   209,   502,   502,   209,
     209,     4,   502,     4,     4,   209,   505,   209,   557,   209,
     505,     4,     4,   512,     4,     4,     4,   512,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,     4,     4,   209,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     4,   209,
       4,   209,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     4,     4,    76,     4,     4,     4,     4,    95,    96,
       4,     4,   693,   207,    87,   696,    89,     4,     4,     4,
       4,     4,    95,    96,    97,    98,    99,   100,   101,   102,
     209,   696,     4,     4,   107,   108,   109,     4,   209,     4,
       4,     4,     4,   116,   207,   209,   119,   120,   729,   730,
     731,     4,   733,     4,   127,     4,     4,     4,   207,     4,
     207,     4,     4,   207,   729,   730,   731,   732,   733,     4,
       4,     4,   692,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,     4,   696,     4,     4,
       7,     4,   207,   180,   181,     4,     4,     4,   209,     4,
       4,   209,     4,     4,   209,   209,     4,   180,   181,   207,
       4,   207,   207,     4,     4,   209,   209,     4,     4,   206,
     729,   730,   731,   732,   733,     4,     4,     4,   207,     4,
       4,   206,     5,   206,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,     7,     7,     7,
     206,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,   206,    76,    77,   206,     5,     5,     5,     5,   206,
       5,     7,     5,     5,   175,     5,     7,     5,     5,   206,
     206,    95,    96,     7,    98,    99,     7,   101,   102,     7,
       7,     7,     7,   107,   108,   109,     5,     5,     5,     5,
     206,   206,   116,     7,     5,   119,     3,     7,     7,     7,
     206,   206,     7,   127,   206,   206,   206,   206,   206,     7,
       7,   114,     7,     7,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,     7,     7,   206,   206,   206,     7,
     206,     4,     4,     4,     4,   206,     4,     4,     4,     4,
       4,     4,   206,     3,     6,     6,     3,     6,     6,     3,
       6,     3,   206,     6,     3,     6,   180,   181,     6,     3,
       6,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     3,     6,   207,   209,
       6,     4,   206,     8,     4,     4,     4,   207,   209,     4,
       4,   207,     4,   984,   207,     4,   987,   207,     4,   990,
     987,   207,   993,   990,   990,   984,   993,   984,   207,   984,
       4,   209,   987,  1004,   993,   990,  1007,  1004,   993,  1010,
       4,   984,   984,   990,   984,   984,   207,   207,   207,  1004,
     993,   993,  1007,   993,   993,  1026,   984,   984,   984,     4,
    1031,   984,   207,   984,  1035,   993,   993,   993,   207,   984,
     993,  1026,   993,  1044,   207,   984,  1031,  1044,   993,  1050,
    1035,   984,  1053,   984,   993,   984,  1041,     4,   987,  1044,
     993,   990,   993,   209,   993,  1050,     4,   984,  1053,   209,
       4,   984,   984,   207,   984,  1004,   993,   207,  1007,   984,
     993,   993,   984,   993,   984,   207,   984,  1004,   993,   984,
    1007,   993,   984,   993,   984,   993,   984,  1026,   993,   984,
     984,   993,  1031,   993,   984,   993,  1035,   207,   993,   993,
     207,   207,  1041,   993,   993,  1044,   207,     4,   993,     3,
       6,  1050,     4,     8,  1053,     8,     4,   206,     8,     3,
       5,     8,     4,  1050,     4,     4,  1053,     4,     4,     7,
       4,   206,     4,     4,     4,   722,   206,   671,   486,   206,
     684,   206,   696,   490,   776,   983,   693,  1002,   996,   978,
     999,  1012,  1010,  1031,   986,   540,   984,  1019,  1218,   502,
     995,  1050,   206,    77,  1053,  1050,   207,   209,  1053,   206,
     206,   989,   987,   206,   532,   206,   206,   990,   206,   206,
     992,   206,   206,   537,  1052,   207,   209,   207,   206,   206,
    1050,  1055,  1009,  1007,  1053,  1005,  1224,   557,  1041,  1026,
     733,   746,  1035,  1045,  1239,  1260,   561,  1218,   695,  1280,
      -1,  1218,    -1,  1224,    -1,   505,    -1,  1224,    -1,  1218,
      -1,    -1,    -1,  1218,   512,    -1,  1176,    -1,  1239,  1224,
      -1,    -1,  1239,   522,    -1,  1218,  1218,    -1,  1218,  1218,
      -1,    -1,    -1,    -1,  1239,    -1,    -1,    -1,    -1,    -1,
    1218,  1218,  1218,    -1,    -1,  1218,    -1,  1218,    -1,    -1,
      -1,    -1,    -1,  1218,    -1,    -1,    -1,    -1,    -1,  1218,
      -1,    -1,    -1,    -1,    -1,  1218,    -1,  1218,    -1,  1218,
      -1,    -1,    -1,    -1,    -1,  1224,    -1,    -1,    -1,    -1,
      -1,  1218,    -1,    -1,    -1,  1218,  1218,  1224,  1218,    -1,
    1239,    -1,    -1,  1218,    -1,    -1,  1218,    -1,  1218,    -1,
    1218,    -1,    -1,  1218,    -1,    -1,  1218,    -1,  1218,    -1,
    1218,    -1,    -1,  1218,  1218,    -1,    -1,    -1,  1218,  1218,
      -1,    -1,    -1,  1218
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
       0,     5,     7,     9,   206,   207,   208,   209,   226,   227,
     228,   233,     7,   242,     7,   246,     7,   290,     7,   399,
       7,   479,     7,   495,     7,   512,     7,   431,     7,   437,
       7,   461,     7,   375,     7,   581,     7,   612,   234,   229,
     243,   247,   291,   400,   480,   496,   513,   432,   438,   462,
     376,   582,   613,   226,   235,   236,   206,   231,   232,    10,
     244,    11,    12,    15,    18,    19,    20,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    86,    95,    96,   102,
     107,   108,   109,   110,   111,   112,   113,   115,   120,   129,
     132,   139,   147,   148,   152,   155,   159,   180,   181,   182,
     183,   206,   241,   248,   249,   250,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   272,   274,   276,   277,   278,   280,
     282,   283,   284,   285,   287,   288,   297,   299,   301,   342,
     348,   354,   360,   362,   369,   383,   393,   413,   414,   415,
     416,   421,   429,   455,   485,   487,   506,   536,   548,   560,
     561,   569,   579,   610,   619,    16,    17,   241,   292,   293,
     294,   296,   485,   487,    87,    89,    97,    98,    99,   100,
     101,   116,   119,   127,   241,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   266,   267,
     268,   269,   272,   274,   276,   277,   278,   280,   282,   401,
     402,   403,   405,   407,   409,   411,   413,   414,   415,   416,
     419,   420,   455,   473,   485,   487,   489,   506,   531,    88,
     241,   409,   411,   455,   481,   482,   483,   485,   487,    90,
      91,    92,    93,    94,   241,   409,   411,   455,   485,   487,
     497,   498,   499,   501,   502,   504,   505,   115,   121,   122,
     123,   124,   125,   126,   241,   455,   485,   487,   514,   515,
     516,   517,   519,   521,   523,   525,   527,   529,   429,    21,
      77,    79,    80,    83,    84,    85,   241,   319,   439,   440,
     441,   442,   443,   444,   445,   447,   449,   451,   452,   454,
     485,   487,    78,    81,    82,   241,   319,   443,   449,   463,
     464,   465,   466,   467,   469,   470,   471,   472,   485,   487,
     130,   131,   241,   377,   378,   379,   381,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     180,   181,   241,   485,   487,   583,   584,   585,   586,   588,
     590,   591,   593,   594,   595,   598,   600,   601,   602,   604,
     606,   608,    13,    14,   614,   615,   616,   618,     6,     3,
       4,     8,     3,   245,     8,   251,   611,   289,   298,   300,
     302,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   286,     4,     4,     4,     4,
       4,   270,   273,   275,     4,     4,     4,   394,   430,   456,
     422,   486,   488,   417,     4,     4,     4,   349,   361,   355,
     343,   537,   507,   370,   384,   549,     4,   363,   562,   570,
     580,   279,   281,     4,   620,     4,     3,     8,   295,     4,
       3,     8,   474,   490,   404,   406,   408,     4,     4,   412,
     410,   532,     3,     8,   484,     3,     8,   500,     4,   503,
       4,     4,     3,     8,   530,   518,   520,   522,   524,   526,
     528,     8,     3,     8,   446,   320,     4,   450,   448,   453,
       4,     8,     3,   468,     4,     4,     8,     3,   380,   382,
       3,     8,     4,   587,   589,     4,   592,     4,     4,   596,
     599,     4,     4,   603,   605,   607,   609,     3,     8,   617,
       4,     3,     8,   226,   226,   206,     4,     4,     4,     4,
       4,     4,     4,   207,   207,   207,   207,   207,   207,   207,
     207,   209,   208,   208,   208,   207,   207,     4,   207,   207,
     209,   209,   209,     4,     4,     4,   209,   209,   209,     4,
       4,     4,     4,     4,     4,     4,   209,   209,   209,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   207,     4,
       4,     4,     4,     4,     4,   209,     4,   249,     4,   209,
     293,     4,     4,     4,     4,     4,   207,   209,     4,     4,
       4,   402,     4,   482,     4,   207,     4,   207,   207,   498,
       4,     4,     4,     4,     4,     4,     4,   516,     4,     4,
     207,     4,     4,     4,   209,   441,     4,   209,   209,   465,
       4,     4,   378,   209,     4,     4,   207,     4,   207,   207,
       4,     4,   209,   209,     4,     4,     4,     4,   584,     4,
     207,   615,     4,     7,   206,     7,     7,     7,     7,     5,
     206,   176,   177,   178,   179,   209,   271,   206,   206,     5,
       5,     5,     5,   228,   230,   206,   103,   104,   105,   106,
     418,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   206,   206,     5,     5,   237,     5,
       5,   206,   206,   206,   237,   206,     7,   206,   206,   206,
     237,   237,   237,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   230,   206,   206,   206,   173,   174,
     597,   175,   271,   206,   206,   206,     5,   226,   248,   614,
     292,    21,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    41,    42,    43,    44,    45,    46,
      47,   241,   307,   308,   309,   312,   314,   316,   318,   319,
     321,   322,   323,   324,   325,   326,   329,   330,   331,   332,
     333,   335,   336,   338,   340,   307,     7,   303,   304,   305,
       7,   395,   396,   397,     7,   433,   434,   435,     7,   457,
     458,   459,     7,   423,   424,   425,   123,   206,   350,   351,
     352,   353,   235,   124,   126,   352,   356,   357,   358,   359,
     114,   344,   345,   346,     7,   538,   539,     7,   508,   509,
     510,     7,   371,   372,   373,   133,   134,   135,   136,   137,
     138,   385,   386,   387,   388,   389,   390,   391,   392,    21,
     143,   144,   145,   146,   241,   321,   485,   487,   550,   551,
     552,   555,   556,   558,   559,   149,   150,   151,   241,   364,
     365,   366,   367,   368,   485,   487,   153,   154,   241,   485,
     487,   563,   564,   565,   567,   156,   157,   158,   206,   485,
     487,   571,   572,   573,   574,   576,   577,   583,     7,   621,
     622,   238,     7,   475,   476,   477,     7,   491,   492,   493,
     128,   517,   533,   534,   303,     8,     8,     8,   310,   313,
     315,   317,     4,     4,     4,     4,     4,   334,     4,     4,
     327,   337,   339,   341,     4,     4,     4,     4,     3,     8,
       8,   306,     6,     3,   398,     6,     3,   436,     6,     3,
     460,     6,     3,   426,     6,     3,     3,     6,     6,     3,
       6,   347,     3,     8,   540,     3,     6,   511,     6,     3,
     374,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   553,   557,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   566,   568,     3,     8,     4,   575,     4,
     578,     3,     8,     8,   623,     3,     6,   206,   239,   240,
     478,     6,     3,   494,     6,     3,   535,     8,     6,     4,
       4,     4,     4,   207,   209,   207,   209,   207,     4,   207,
     207,     4,     4,     4,     4,   207,   207,   209,   207,   308,
     307,   305,   401,   397,   439,   435,   463,   459,   241,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   266,   267,   268,   269,   272,   274,   276,   277,
     278,   280,   282,   319,   393,   405,   407,   409,   411,   413,
     414,   415,   416,   420,   427,   428,   455,   485,   487,   531,
     425,   351,   357,     4,   345,   117,   118,   241,   319,   455,
     485,   487,   541,   542,   543,   544,   545,   547,   539,   514,
     510,   377,   373,   207,   207,   207,   207,   207,   207,   386,
       4,     4,   207,   207,   207,   551,   209,   207,   207,   365,
       4,     4,   564,   209,     4,   207,     4,   572,   184,   186,
     187,   241,   319,   485,   487,   624,   625,   626,   627,   629,
     622,     6,     3,   481,   477,   497,   493,     4,    22,    23,
      24,    25,   311,   206,   206,   206,   206,    38,    39,    40,
     328,   206,   206,   206,     8,     8,     8,     8,     3,     8,
     206,   546,     4,     8,     3,     8,     8,   140,   141,   142,
     554,   206,   206,   206,   206,   226,   630,     4,   628,     3,
       8,   206,     8,     8,   206,   428,     4,   209,   543,     4,
     207,     4,   625,   206,     5,   206,     7,   631,   632,   633,
       3,     6,   185,   188,   189,   190,   191,   634,   635,   636,
     638,   639,   640,   641,   632,   637,     4,     4,     4,   642,
       3,     8,     4,   209,   207,   207,     4,   635,   206,   206
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   210,   212,   211,   213,   211,   214,   211,   215,   211,
     216,   211,   217,   211,   218,   211,   219,   211,   220,   211,
     221,   211,   222,   211,   223,   211,   224,   211,   225,   211,
     226,   226,   226,   226,   226,   226,   226,   227,   229,   228,
     230,   231,   231,   232,   232,   234,   233,   235,   235,   236,
     236,   238,   237,   239,   239,   240,   240,   241,   243,   242,
     245,   244,   247,   246,   248,   248,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   251,   250,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   270,   269,   271,   271,
     271,   271,   271,   273,   272,   275,   274,   276,   277,   279,
     278,   281,   280,   282,   283,   284,   286,   285,   287,   289,
     288,   291,   290,   292,   292,   293,   293,   293,   293,   293,
     295,   294,   296,   298,   297,   300,   299,   302,   301,   303,
     303,   304,   304,   306,   305,   307,   307,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   308,
     308,   308,   308,   308,   308,   308,   308,   308,   308,   310,
     309,   311,   311,   311,   311,   313,   312,   315,   314,   317,
     316,   318,   320,   319,   321,   322,   323,   324,   325,   327,
     326,   328,   328,   328,   329,   330,   331,   332,   334,   333,
     335,   337,   336,   339,   338,   341,   340,   343,   342,   344,
     344,   345,   347,   346,   349,   348,   350,   350,   351,   351,
     352,   353,   355,   354,   356,   356,   357,   357,   357,   358,
     359,   361,   360,   363,   362,   364,   364,   365,   365,   365,
     365,   365,   365,   366,   367,   368,   370,   369,   371,   371,
     372,   372,   374,   373,   376,   375,   377,   377,   377,   378,
     378,   380,   379,   382,   381,   384,   383,   385,   385,   386,
     386,   386,   386,   386,   386,   387,   388,   389,   390,   391,
     392,   394,   393,   395,   395,   396,   396,   398,   397,   400,
     399,   401,   401,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   404,   403,   406,   405,
     408,   407,   410,   409,   412,   411,   413,   414,   415,   417,
     416,   418,   418,   418,   418,   419,   420,   422,   421,   423,
     423,   424,   424,   426,   425,   427,   427,   428,   428,   428,
     428,   428,   428,   428,   428,   428,   428,   428,   428,   428,
     428,   428,   428,   428,   428,   428,   428,   428,   428,   428,
     428,   428,   428,   428,   428,   428,   428,   428,   428,   428,
     428,   428,   428,   428,   428,   428,   428,   430,   429,   432,
     431,   433,   433,   434,   434,   436,   435,   438,   437,   439,
     439,   440,   440,   441,   441,   441,   441,   441,   441,   441,
     441,   441,   441,   442,   443,   444,   446,   445,   448,   447,
     450,   449,   451,   453,   452,   454,   456,   455,   457,   457,
     458,   458,   460,   459,   462,   461,   463,   463,   464,   464,
     465,   465,   465,   465,   465,   465,   465,   465,   465,   466,
     468,   467,   469,   470,   471,   472,   474,   473,   475,   475,
     476,   476,   478,   477,   480,   479,   481,   481,   482,   482,
     482,   482,   482,   482,   482,   484,   483,   486,   485,   488,
     487,   490,   489,   491,   491,   492,   492,   494,   493,   496,
     495,   497,   497,   498,   498,   498,   498,   498,   498,   498,
     498,   498,   498,   498,   500,   499,   501,   503,   502,   504,
     505,   507,   506,   508,   508,   509,   509,   511,   510,   513,
     512,   514,   514,   515,   515,   516,   516,   516,   516,   516,
     516,   516,   516,   516,   516,   516,   518,   517,   520,   519,
     522,   521,   524,   523,   526,   525,   528,   527,   530,   529,
     532,   531,   533,   533,   535,   534,   537,   536,   538,   538,
     540,   539,   541,   541,   542,   542,   543,   543,   543,   543,
     543,   543,   543,   544,   546,   545,   547,   549,   548,   550,
     550,   551,   551,   551,   551,   551,   551,   551,   551,   551,
     553,   552,   554,   554,   554,   555,   557,   556,   558,   559,
     560,   562,   561,   563,   563,   564,   564,   564,   564,   564,
     566,   565,   568,   567,   570,   569,   571,   571,   572,   572,
     572,   572,   572,   572,   573,   575,   574,   576,   578,   577,
     580,   579,   582,   581,   583,   583,   584,   584,   584,   584,
     584,   584,   584,   584,   584,   584,   584,   584,   584,   584,
     584,   584,   584,   584,   585,   587,   586,   589,   588,   590,
     592,   591,   593,   594,   596,   595,   597,   597,   599,   598,
     600,   601,   603,   602,   605,   604,   607,   606,   609,   608,
     611,   610,   613,   612,   614,   614,   615,   615,   617,   616,
     618,   620,   619,   621,   621,   623,   622,   624,   624,   625,
     625,   625,   625,   625,   625,   625,   626,   628,   627,   630,
     629,   631,   631,   633,   632,   634,   634,   635,   635,   635,
     635,   635,   637,   636,   638,   639,   640,   642,   641
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       4,     0,     4,     3,     3,     3,     0,     4,     3,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     3,     3,     3,     3,     0,     4,
       3,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     1,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     3,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     0,     6,
       3,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     0,     4
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
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
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
  "syntax_map", "$@18", "global_object", "$@19", "sub_dhcp6", "$@20",
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
  "ip_reservations_unique", "interfaces_config", "$@28", "sub_interfaces6",
  "$@29", "interfaces_config_params", "interfaces_config_param",
  "interfaces_list", "$@30", "re_detect", "lease_database", "$@31",
  "hosts_database", "$@32", "hosts_databases", "$@33", "database_list",
  "not_empty_database_list", "database", "$@34", "database_map_params",
  "database_map_param", "database_type", "$@35", "db_type", "user", "$@36",
  "password", "$@37", "host", "$@38", "port", "name", "$@39", "persist",
  "lfc_interval", "readonly", "connect_timeout", "reconnect_wait_time",
  "on_fail", "$@40", "on_fail_mode", "max_row_errors", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@41",
  "max_reconnect_tries", "keyspace", "$@42", "consistency", "$@43",
  "serial_consistency", "$@44", "sanity_checks", "$@45",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@46",
  "mac_sources", "$@47", "mac_sources_list", "mac_sources_value",
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
  "maxsize", "maxver", "pattern", "$@135", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   297,   297,   297,   298,   298,   299,   299,   300,   300,
     301,   301,   302,   302,   303,   303,   304,   304,   305,   305,
     306,   306,   307,   307,   308,   308,   309,   309,   310,   310,
     318,   319,   320,   321,   322,   323,   324,   327,   332,   332,
     343,   346,   347,   350,   355,   363,   363,   370,   371,   374,
     378,   385,   385,   392,   393,   396,   400,   411,   420,   420,
     435,   435,   452,   452,   461,   462,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   530,   530,   539,
     545,   551,   557,   563,   569,   575,   581,   587,   593,   599,
     605,   611,   617,   623,   629,   635,   641,   641,   650,   653,
     656,   659,   662,   668,   668,   677,   677,   686,   692,   698,
     698,   707,   707,   716,   722,   728,   734,   734,   743,   749,
     749,   761,   761,   770,   771,   774,   775,   776,   777,   778,
     781,   781,   792,   798,   798,   811,   811,   824,   824,   835,
     836,   839,   840,   843,   843,   853,   854,   857,   858,   859,
     860,   861,   862,   863,   864,   865,   866,   867,   868,   869,
     870,   871,   872,   873,   874,   875,   876,   877,   878,   881,
     881,   889,   890,   891,   892,   895,   895,   904,   904,   913,
     913,   922,   928,   928,   937,   943,   949,   955,   961,   967,
     967,   975,   976,   977,   980,   986,   992,   998,  1004,  1004,
    1013,  1019,  1019,  1028,  1028,  1037,  1037,  1046,  1046,  1057,
    1058,  1060,  1062,  1062,  1081,  1081,  1092,  1093,  1096,  1097,
    1100,  1105,  1110,  1110,  1121,  1122,  1125,  1126,  1127,  1130,
    1135,  1142,  1142,  1155,  1155,  1168,  1169,  1172,  1173,  1174,
    1175,  1176,  1177,  1180,  1186,  1192,  1198,  1198,  1209,  1210,
    1213,  1214,  1217,  1217,  1227,  1227,  1237,  1238,  1239,  1242,
    1243,  1246,  1246,  1255,  1255,  1264,  1264,  1276,  1277,  1280,
    1281,  1282,  1283,  1284,  1285,  1288,  1294,  1300,  1306,  1312,
    1318,  1327,  1327,  1341,  1342,  1345,  1346,  1353,  1353,  1379,
    1379,  1390,  1391,  1395,  1396,  1397,  1398,  1399,  1400,  1401,
    1402,  1403,  1404,  1405,  1406,  1407,  1408,  1409,  1410,  1411,
    1412,  1413,  1414,  1415,  1416,  1417,  1418,  1419,  1420,  1421,
    1422,  1423,  1424,  1425,  1426,  1427,  1428,  1429,  1430,  1431,
    1432,  1433,  1434,  1435,  1436,  1437,  1440,  1440,  1449,  1449,
    1458,  1458,  1467,  1467,  1476,  1476,  1487,  1493,  1499,  1505,
    1505,  1513,  1514,  1515,  1516,  1519,  1525,  1533,  1533,  1545,
    1546,  1550,  1551,  1554,  1554,  1562,  1563,  1566,  1567,  1568,
    1569,  1570,  1571,  1572,  1573,  1574,  1575,  1576,  1577,  1578,
    1579,  1580,  1581,  1582,  1583,  1584,  1585,  1586,  1587,  1588,
    1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,
    1599,  1600,  1601,  1602,  1603,  1604,  1605,  1612,  1612,  1626,
    1626,  1635,  1636,  1639,  1640,  1645,  1645,  1660,  1660,  1674,
    1675,  1678,  1679,  1682,  1683,  1684,  1685,  1686,  1687,  1688,
    1689,  1690,  1691,  1694,  1696,  1702,  1704,  1704,  1713,  1713,
    1722,  1722,  1731,  1733,  1733,  1742,  1752,  1752,  1765,  1766,
    1771,  1772,  1777,  1777,  1789,  1789,  1801,  1802,  1807,  1808,
    1813,  1814,  1815,  1816,  1817,  1818,  1819,  1820,  1821,  1824,
    1826,  1826,  1835,  1837,  1839,  1845,  1854,  1854,  1867,  1868,
    1871,  1872,  1875,  1875,  1885,  1885,  1895,  1896,  1899,  1900,
    1901,  1902,  1903,  1904,  1905,  1908,  1908,  1917,  1917,  1942,
    1942,  1972,  1972,  1985,  1986,  1989,  1990,  1993,  1993,  2005,
    2005,  2017,  2018,  2021,  2022,  2023,  2024,  2025,  2026,  2027,
    2028,  2029,  2030,  2031,  2034,  2034,  2043,  2049,  2049,  2058,
    2064,  2073,  2073,  2084,  2085,  2088,  2089,  2092,  2092,  2101,
    2101,  2110,  2111,  2114,  2115,  2119,  2120,  2121,  2122,  2123,
    2124,  2125,  2126,  2127,  2128,  2129,  2132,  2132,  2143,  2143,
    2154,  2154,  2163,  2163,  2172,  2172,  2181,  2181,  2190,  2190,
    2204,  2204,  2215,  2216,  2219,  2219,  2231,  2231,  2242,  2243,
    2246,  2246,  2256,  2257,  2260,  2261,  2264,  2265,  2266,  2267,
    2268,  2269,  2270,  2273,  2275,  2275,  2284,  2293,  2293,  2306,
    2307,  2310,  2311,  2312,  2313,  2314,  2315,  2316,  2317,  2318,
    2321,  2321,  2329,  2330,  2331,  2334,  2340,  2340,  2349,  2355,
    2363,  2371,  2371,  2382,  2383,  2386,  2387,  2388,  2389,  2390,
    2393,  2393,  2402,  2402,  2414,  2414,  2427,  2428,  2431,  2432,
    2433,  2434,  2435,  2436,  2439,  2445,  2445,  2454,  2460,  2460,
    2470,  2470,  2483,  2483,  2493,  2494,  2497,  2498,  2499,  2500,
    2501,  2502,  2503,  2504,  2505,  2506,  2507,  2508,  2509,  2510,
    2511,  2512,  2513,  2514,  2517,  2524,  2524,  2533,  2533,  2542,
    2548,  2548,  2557,  2563,  2569,  2569,  2578,  2579,  2582,  2582,
    2592,  2599,  2606,  2606,  2615,  2615,  2625,  2625,  2635,  2635,
    2647,  2647,  2659,  2659,  2669,  2670,  2674,  2675,  2678,  2678,
    2689,  2697,  2697,  2710,  2711,  2715,  2715,  2723,  2724,  2727,
    2728,  2729,  2730,  2731,  2732,  2733,  2736,  2742,  2742,  2751,
    2751,  2762,  2763,  2766,  2766,  2774,  2775,  2778,  2779,  2780,
    2781,  2782,  2785,  2785,  2794,  2800,  2806,  2812,  2812
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
#line 5915 "dhcp6_parser.cc"

#line 2821 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
