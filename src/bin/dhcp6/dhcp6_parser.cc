// A Bison parser, made by GNU Bison 3.7.6.

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
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 400 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 406 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 412 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 418 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 424 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 430 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 436 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 442 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 448 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 454 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 276 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 460 "dhcp6_parser.cc"
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
#line 285 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 739 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 286 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 745 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 287 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 751 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 288 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 757 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 289 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 763 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 290 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 769 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 291 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 775 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 292 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 781 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 293 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 787 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 294 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 793 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 295 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 799 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 296 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 805 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 297 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 811 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 298 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 817 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 306 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 307 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 308 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 309 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 310 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 847 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 311 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 312 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 859 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 315 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 868 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 320 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 879 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 325 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 889 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 331 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 338 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 904 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 342 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 914 "dhcp6_parser.cc"
    break;

  case 45: // $@16: %empty
#line 349 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 923 "dhcp6_parser.cc"
    break;

  case 46: // list_generic: "[" $@16 list_content "]"
#line 352 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 931 "dhcp6_parser.cc"
    break;

  case 49: // not_empty_list: value
#line 360 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 940 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list "," value
#line 364 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 949 "dhcp6_parser.cc"
    break;

  case 51: // $@17: %empty
#line 371 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 957 "dhcp6_parser.cc"
    break;

  case 52: // list_strings: "[" $@17 list_strings_content "]"
#line 373 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 966 "dhcp6_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 382 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 975 "dhcp6_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 386 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 984 "dhcp6_parser.cc"
    break;

  case 57: // unknown_map_entry: "constant string" ":"
#line 397 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 995 "dhcp6_parser.cc"
    break;

  case 58: // $@18: %empty
#line 406 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1006 "dhcp6_parser.cc"
    break;

  case 59: // syntax_map: "{" $@18 global_objects "}"
#line 411 "dhcp6_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1019 "dhcp6_parser.cc"
    break;

  case 63: // $@19: %empty
#line 429 "dhcp6_parser.yy"
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
#line 1034 "dhcp6_parser.cc"
    break;

  case 64: // dhcp6_object: "Dhcp6" $@19 ":" "{" global_params "}"
#line 438 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1044 "dhcp6_parser.cc"
    break;

  case 65: // $@20: %empty
#line 446 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1054 "dhcp6_parser.cc"
    break;

  case 66: // sub_dhcp6: "{" $@20 global_params "}"
#line 450 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1063 "dhcp6_parser.cc"
    break;

  case 124: // $@21: %empty
#line 518 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1071 "dhcp6_parser.cc"
    break;

  case 125: // data_directory: "data-directory" $@21 ":" "constant string"
#line 520 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 126: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 526 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1090 "dhcp6_parser.cc"
    break;

  case 127: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 531 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 128: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 536 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 129: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 541 "dhcp6_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1117 "dhcp6_parser.cc"
    break;

  case 130: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 546 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1126 "dhcp6_parser.cc"
    break;

  case 131: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 551 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 132: // renew_timer: "renew-timer" ":" "integer"
#line 556 "dhcp6_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1144 "dhcp6_parser.cc"
    break;

  case 133: // rebind_timer: "rebind-timer" ":" "integer"
#line 561 "dhcp6_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1153 "dhcp6_parser.cc"
    break;

  case 134: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 566 "dhcp6_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1162 "dhcp6_parser.cc"
    break;

  case 135: // t1_percent: "t1-percent" ":" "floating point"
#line 571 "dhcp6_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 136: // t2_percent: "t2-percent" ":" "floating point"
#line 576 "dhcp6_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1180 "dhcp6_parser.cc"
    break;

  case 137: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 581 "dhcp6_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1189 "dhcp6_parser.cc"
    break;

  case 138: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 586 "dhcp6_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1198 "dhcp6_parser.cc"
    break;

  case 139: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 591 "dhcp6_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1207 "dhcp6_parser.cc"
    break;

  case 140: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 596 "dhcp6_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1216 "dhcp6_parser.cc"
    break;

  case 141: // $@22: %empty
#line 601 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 142: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 603 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 143: // ddns_replace_client_name_value: "when-present"
#line 609 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1241 "dhcp6_parser.cc"
    break;

  case 144: // ddns_replace_client_name_value: "never"
#line 612 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1249 "dhcp6_parser.cc"
    break;

  case 145: // ddns_replace_client_name_value: "always"
#line 615 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1257 "dhcp6_parser.cc"
    break;

  case 146: // ddns_replace_client_name_value: "when-not-present"
#line 618 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1265 "dhcp6_parser.cc"
    break;

  case 147: // ddns_replace_client_name_value: "boolean"
#line 621 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1274 "dhcp6_parser.cc"
    break;

  case 148: // $@23: %empty
#line 627 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1282 "dhcp6_parser.cc"
    break;

  case 149: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 629 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1292 "dhcp6_parser.cc"
    break;

  case 150: // $@24: %empty
#line 635 "dhcp6_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1300 "dhcp6_parser.cc"
    break;

  case 151: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 637 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1310 "dhcp6_parser.cc"
    break;

  case 152: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 643 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1320 "dhcp6_parser.cc"
    break;

  case 153: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 649 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1330 "dhcp6_parser.cc"
    break;

  case 154: // $@25: %empty
#line 655 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp6_parser.cc"
    break;

  case 155: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 657 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1348 "dhcp6_parser.cc"
    break;

  case 156: // $@26: %empty
#line 663 "dhcp6_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1356 "dhcp6_parser.cc"
    break;

  case 157: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 665 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1366 "dhcp6_parser.cc"
    break;

  case 158: // store_extended_info: "store-extended-info" ":" "boolean"
#line 671 "dhcp6_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1375 "dhcp6_parser.cc"
    break;

  case 159: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 676 "dhcp6_parser.yy"
                                                                             {
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1384 "dhcp6_parser.cc"
    break;

  case 160: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 681 "dhcp6_parser.yy"
                                                                         {
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1393 "dhcp6_parser.cc"
    break;

  case 161: // $@27: %empty
#line 686 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1401 "dhcp6_parser.cc"
    break;

  case 162: // server_tag: "server-tag" $@27 ":" "constant string"
#line 688 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1411 "dhcp6_parser.cc"
    break;

  case 163: // $@28: %empty
#line 694 "dhcp6_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 164: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 699 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1432 "dhcp6_parser.cc"
    break;

  case 165: // $@29: %empty
#line 705 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1442 "dhcp6_parser.cc"
    break;

  case 166: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 709 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 174: // $@30: %empty
#line 725 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1462 "dhcp6_parser.cc"
    break;

  case 175: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 730 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1471 "dhcp6_parser.cc"
    break;

  case 176: // re_detect: "re-detect" ":" "boolean"
#line 735 "dhcp6_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 177: // $@31: %empty
#line 740 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1491 "dhcp6_parser.cc"
    break;

  case 178: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 745 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1502 "dhcp6_parser.cc"
    break;

  case 179: // $@32: %empty
#line 752 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1513 "dhcp6_parser.cc"
    break;

  case 180: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 757 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1524 "dhcp6_parser.cc"
    break;

  case 181: // $@33: %empty
#line 764 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1535 "dhcp6_parser.cc"
    break;

  case 182: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 769 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1544 "dhcp6_parser.cc"
    break;

  case 187: // $@34: %empty
#line 782 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1554 "dhcp6_parser.cc"
    break;

  case 188: // database: "{" $@34 database_map_params "}"
#line 786 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1564 "dhcp6_parser.cc"
    break;

  case 212: // $@35: %empty
#line 819 "dhcp6_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1572 "dhcp6_parser.cc"
    break;

  case 213: // database_type: "type" $@35 ":" db_type
#line 821 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1581 "dhcp6_parser.cc"
    break;

  case 214: // db_type: "memfile"
#line 826 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1587 "dhcp6_parser.cc"
    break;

  case 215: // db_type: "mysql"
#line 827 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1593 "dhcp6_parser.cc"
    break;

  case 216: // db_type: "postgresql"
#line 828 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1599 "dhcp6_parser.cc"
    break;

  case 217: // db_type: "cql"
#line 829 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1605 "dhcp6_parser.cc"
    break;

  case 218: // $@36: %empty
#line 832 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1613 "dhcp6_parser.cc"
    break;

  case 219: // user: "user" $@36 ":" "constant string"
#line 834 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1623 "dhcp6_parser.cc"
    break;

  case 220: // $@37: %empty
#line 840 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1631 "dhcp6_parser.cc"
    break;

  case 221: // password: "password" $@37 ":" "constant string"
#line 842 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1641 "dhcp6_parser.cc"
    break;

  case 222: // $@38: %empty
#line 848 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1649 "dhcp6_parser.cc"
    break;

  case 223: // host: "host" $@38 ":" "constant string"
#line 850 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1659 "dhcp6_parser.cc"
    break;

  case 224: // port: "port" ":" "integer"
#line 856 "dhcp6_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 225: // $@39: %empty
#line 861 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1676 "dhcp6_parser.cc"
    break;

  case 226: // name: "name" $@39 ":" "constant string"
#line 863 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1686 "dhcp6_parser.cc"
    break;

  case 227: // persist: "persist" ":" "boolean"
#line 869 "dhcp6_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1695 "dhcp6_parser.cc"
    break;

  case 228: // lfc_interval: "lfc-interval" ":" "integer"
#line 874 "dhcp6_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1704 "dhcp6_parser.cc"
    break;

  case 229: // readonly: "readonly" ":" "boolean"
#line 879 "dhcp6_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1713 "dhcp6_parser.cc"
    break;

  case 230: // connect_timeout: "connect-timeout" ":" "integer"
#line 884 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1722 "dhcp6_parser.cc"
    break;

  case 231: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 889 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1731 "dhcp6_parser.cc"
    break;

  case 232: // max_row_errors: "max-row-errors" ":" "integer"
#line 894 "dhcp6_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1740 "dhcp6_parser.cc"
    break;

  case 233: // request_timeout: "request-timeout" ":" "integer"
#line 899 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1749 "dhcp6_parser.cc"
    break;

  case 234: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 904 "dhcp6_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1758 "dhcp6_parser.cc"
    break;

  case 235: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 909 "dhcp6_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1767 "dhcp6_parser.cc"
    break;

  case 236: // $@40: %empty
#line 914 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1775 "dhcp6_parser.cc"
    break;

  case 237: // contact_points: "contact-points" $@40 ":" "constant string"
#line 916 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1785 "dhcp6_parser.cc"
    break;

  case 238: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 922 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1794 "dhcp6_parser.cc"
    break;

  case 239: // $@41: %empty
#line 927 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1802 "dhcp6_parser.cc"
    break;

  case 240: // keyspace: "keyspace" $@41 ":" "constant string"
#line 929 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1812 "dhcp6_parser.cc"
    break;

  case 241: // $@42: %empty
#line 935 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1820 "dhcp6_parser.cc"
    break;

  case 242: // consistency: "consistency" $@42 ":" "constant string"
#line 937 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1830 "dhcp6_parser.cc"
    break;

  case 243: // $@43: %empty
#line 943 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1838 "dhcp6_parser.cc"
    break;

  case 244: // serial_consistency: "serial-consistency" $@43 ":" "constant string"
#line 945 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1848 "dhcp6_parser.cc"
    break;

  case 245: // $@44: %empty
#line 951 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1859 "dhcp6_parser.cc"
    break;

  case 246: // sanity_checks: "sanity-checks" $@44 ":" "{" sanity_checks_params "}"
#line 956 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1868 "dhcp6_parser.cc"
    break;

  case 250: // $@45: %empty
#line 966 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1876 "dhcp6_parser.cc"
    break;

  case 251: // lease_checks: "lease-checks" $@45 ":" "constant string"
#line 968 "dhcp6_parser.yy"
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
#line 1896 "dhcp6_parser.cc"
    break;

  case 252: // $@46: %empty
#line 984 "dhcp6_parser.yy"
                         {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1907 "dhcp6_parser.cc"
    break;

  case 253: // mac_sources: "mac-sources" $@46 ":" "[" mac_sources_list "]"
#line 989 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1916 "dhcp6_parser.cc"
    break;

  case 258: // duid_id: "duid"
#line 1002 "dhcp6_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 259: // string_id: "constant string"
#line 1007 "dhcp6_parser.yy"
                   {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1934 "dhcp6_parser.cc"
    break;

  case 260: // $@47: %empty
#line 1012 "dhcp6_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1945 "dhcp6_parser.cc"
    break;

  case 261: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1017 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1954 "dhcp6_parser.cc"
    break;

  case 267: // hw_address_id: "hw-address"
#line 1031 "dhcp6_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1963 "dhcp6_parser.cc"
    break;

  case 268: // flex_id: "flex-id"
#line 1036 "dhcp6_parser.yy"
                  {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 269: // $@48: %empty
#line 1043 "dhcp6_parser.yy"
                                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 270: // relay_supplied_options: "relay-supplied-options" $@48 ":" "[" list_content "]"
#line 1048 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1992 "dhcp6_parser.cc"
    break;

  case 271: // $@49: %empty
#line 1055 "dhcp6_parser.yy"
                                           {
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2003 "dhcp6_parser.cc"
    break;

  case 272: // dhcp_multi_threading: "multi-threading" $@49 ":" "{" multi_threading_params "}"
#line 1060 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2014 "dhcp6_parser.cc"
    break;

  case 281: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1079 "dhcp6_parser.yy"
                                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2023 "dhcp6_parser.cc"
    break;

  case 282: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1084 "dhcp6_parser.yy"
                                                 {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2032 "dhcp6_parser.cc"
    break;

  case 283: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1089 "dhcp6_parser.yy"
                                                   {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2041 "dhcp6_parser.cc"
    break;

  case 284: // $@50: %empty
#line 1094 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2052 "dhcp6_parser.cc"
    break;

  case 285: // hooks_libraries: "hooks-libraries" $@50 ":" "[" hooks_libraries_list "]"
#line 1099 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2061 "dhcp6_parser.cc"
    break;

  case 290: // $@51: %empty
#line 1112 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2071 "dhcp6_parser.cc"
    break;

  case 291: // hooks_library: "{" $@51 hooks_params "}"
#line 1116 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2081 "dhcp6_parser.cc"
    break;

  case 292: // $@52: %empty
#line 1122 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2091 "dhcp6_parser.cc"
    break;

  case 293: // sub_hooks_library: "{" $@52 hooks_params "}"
#line 1126 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2101 "dhcp6_parser.cc"
    break;

  case 299: // $@53: %empty
#line 1141 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2109 "dhcp6_parser.cc"
    break;

  case 300: // library: "library" $@53 ":" "constant string"
#line 1143 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2119 "dhcp6_parser.cc"
    break;

  case 301: // $@54: %empty
#line 1149 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2127 "dhcp6_parser.cc"
    break;

  case 302: // parameters: "parameters" $@54 ":" map_value
#line 1151 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2136 "dhcp6_parser.cc"
    break;

  case 303: // $@55: %empty
#line 1157 "dhcp6_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2147 "dhcp6_parser.cc"
    break;

  case 304: // expired_leases_processing: "expired-leases-processing" $@55 ":" "{" expired_leases_params "}"
#line 1162 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2157 "dhcp6_parser.cc"
    break;

  case 313: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1180 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2166 "dhcp6_parser.cc"
    break;

  case 314: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1185 "dhcp6_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2175 "dhcp6_parser.cc"
    break;

  case 315: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1190 "dhcp6_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2184 "dhcp6_parser.cc"
    break;

  case 316: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1195 "dhcp6_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2193 "dhcp6_parser.cc"
    break;

  case 317: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1200 "dhcp6_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 318: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1205 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 319: // $@56: %empty
#line 1213 "dhcp6_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2222 "dhcp6_parser.cc"
    break;

  case 320: // subnet6_list: "subnet6" $@56 ":" "[" subnet6_list_content "]"
#line 1218 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2231 "dhcp6_parser.cc"
    break;

  case 325: // $@57: %empty
#line 1238 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2241 "dhcp6_parser.cc"
    break;

  case 326: // subnet6: "{" $@57 subnet6_params "}"
#line 1242 "dhcp6_parser.yy"
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
#line 2267 "dhcp6_parser.cc"
    break;

  case 327: // $@58: %empty
#line 1264 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2277 "dhcp6_parser.cc"
    break;

  case 328: // sub_subnet6: "{" $@58 subnet6_params "}"
#line 1268 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2287 "dhcp6_parser.cc"
    break;

  case 369: // $@59: %empty
#line 1320 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2295 "dhcp6_parser.cc"
    break;

  case 370: // subnet: "subnet" $@59 ":" "constant string"
#line 1322 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2305 "dhcp6_parser.cc"
    break;

  case 371: // $@60: %empty
#line 1328 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2313 "dhcp6_parser.cc"
    break;

  case 372: // interface: "interface" $@60 ":" "constant string"
#line 1330 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2323 "dhcp6_parser.cc"
    break;

  case 373: // $@61: %empty
#line 1336 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2331 "dhcp6_parser.cc"
    break;

  case 374: // interface_id: "interface-id" $@61 ":" "constant string"
#line 1338 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2341 "dhcp6_parser.cc"
    break;

  case 375: // $@62: %empty
#line 1344 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2349 "dhcp6_parser.cc"
    break;

  case 376: // client_class: "client-class" $@62 ":" "constant string"
#line 1346 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2359 "dhcp6_parser.cc"
    break;

  case 377: // $@63: %empty
#line 1352 "dhcp6_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp6_parser.cc"
    break;

  case 378: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1357 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2379 "dhcp6_parser.cc"
    break;

  case 379: // $@64: %empty
#line 1362 "dhcp6_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2387 "dhcp6_parser.cc"
    break;

  case 380: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1364 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2396 "dhcp6_parser.cc"
    break;

  case 381: // hr_mode: "disabled"
#line 1369 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2402 "dhcp6_parser.cc"
    break;

  case 382: // hr_mode: "out-of-pool"
#line 1370 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2408 "dhcp6_parser.cc"
    break;

  case 383: // hr_mode: "global"
#line 1371 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2414 "dhcp6_parser.cc"
    break;

  case 384: // hr_mode: "all"
#line 1372 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2420 "dhcp6_parser.cc"
    break;

  case 385: // id: "id" ":" "integer"
#line 1375 "dhcp6_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2429 "dhcp6_parser.cc"
    break;

  case 386: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1380 "dhcp6_parser.yy"
                                         {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2438 "dhcp6_parser.cc"
    break;

  case 387: // $@65: %empty
#line 1387 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2449 "dhcp6_parser.cc"
    break;

  case 388: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1392 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2458 "dhcp6_parser.cc"
    break;

  case 393: // $@66: %empty
#line 1407 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2468 "dhcp6_parser.cc"
    break;

  case 394: // shared_network: "{" $@66 shared_network_params "}"
#line 1411 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2476 "dhcp6_parser.cc"
    break;

  case 432: // $@67: %empty
#line 1460 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2487 "dhcp6_parser.cc"
    break;

  case 433: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1465 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2496 "dhcp6_parser.cc"
    break;

  case 434: // $@68: %empty
#line 1473 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2505 "dhcp6_parser.cc"
    break;

  case 435: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1476 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2513 "dhcp6_parser.cc"
    break;

  case 440: // $@69: %empty
#line 1492 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2523 "dhcp6_parser.cc"
    break;

  case 441: // option_def_entry: "{" $@69 option_def_params "}"
#line 1496 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2535 "dhcp6_parser.cc"
    break;

  case 442: // $@70: %empty
#line 1507 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2545 "dhcp6_parser.cc"
    break;

  case 443: // sub_option_def: "{" $@70 option_def_params "}"
#line 1511 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2557 "dhcp6_parser.cc"
    break;

  case 459: // code: "code" ":" "integer"
#line 1543 "dhcp6_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2566 "dhcp6_parser.cc"
    break;

  case 461: // $@71: %empty
#line 1550 "dhcp6_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2574 "dhcp6_parser.cc"
    break;

  case 462: // option_def_type: "type" $@71 ":" "constant string"
#line 1552 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2584 "dhcp6_parser.cc"
    break;

  case 463: // $@72: %empty
#line 1558 "dhcp6_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2592 "dhcp6_parser.cc"
    break;

  case 464: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1560 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2602 "dhcp6_parser.cc"
    break;

  case 465: // $@73: %empty
#line 1566 "dhcp6_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2610 "dhcp6_parser.cc"
    break;

  case 466: // space: "space" $@73 ":" "constant string"
#line 1568 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2620 "dhcp6_parser.cc"
    break;

  case 468: // $@74: %empty
#line 1576 "dhcp6_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2628 "dhcp6_parser.cc"
    break;

  case 469: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1578 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 470: // option_def_array: "array" ":" "boolean"
#line 1584 "dhcp6_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2647 "dhcp6_parser.cc"
    break;

  case 471: // $@75: %empty
#line 1593 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2658 "dhcp6_parser.cc"
    break;

  case 472: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1598 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2667 "dhcp6_parser.cc"
    break;

  case 477: // $@76: %empty
#line 1617 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2677 "dhcp6_parser.cc"
    break;

  case 478: // option_data_entry: "{" $@76 option_data_params "}"
#line 1621 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2686 "dhcp6_parser.cc"
    break;

  case 479: // $@77: %empty
#line 1629 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2696 "dhcp6_parser.cc"
    break;

  case 480: // sub_option_data: "{" $@77 option_data_params "}"
#line 1633 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2705 "dhcp6_parser.cc"
    break;

  case 495: // $@78: %empty
#line 1666 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2713 "dhcp6_parser.cc"
    break;

  case 496: // option_data_data: "data" $@78 ":" "constant string"
#line 1668 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2723 "dhcp6_parser.cc"
    break;

  case 499: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1678 "dhcp6_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2732 "dhcp6_parser.cc"
    break;

  case 500: // option_data_always_send: "always-send" ":" "boolean"
#line 1683 "dhcp6_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2741 "dhcp6_parser.cc"
    break;

  case 501: // $@79: %empty
#line 1691 "dhcp6_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2752 "dhcp6_parser.cc"
    break;

  case 502: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1696 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2761 "dhcp6_parser.cc"
    break;

  case 507: // $@80: %empty
#line 1711 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2771 "dhcp6_parser.cc"
    break;

  case 508: // pool_list_entry: "{" $@80 pool_params "}"
#line 1715 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2781 "dhcp6_parser.cc"
    break;

  case 509: // $@81: %empty
#line 1721 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2791 "dhcp6_parser.cc"
    break;

  case 510: // sub_pool6: "{" $@81 pool_params "}"
#line 1725 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2801 "dhcp6_parser.cc"
    break;

  case 520: // $@82: %empty
#line 1744 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2809 "dhcp6_parser.cc"
    break;

  case 521: // pool_entry: "pool" $@82 ":" "constant string"
#line 1746 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2819 "dhcp6_parser.cc"
    break;

  case 522: // $@83: %empty
#line 1752 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2827 "dhcp6_parser.cc"
    break;

  case 523: // user_context: "user-context" $@83 ":" map_value
#line 1754 "dhcp6_parser.yy"
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
#line 2854 "dhcp6_parser.cc"
    break;

  case 524: // $@84: %empty
#line 1777 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2862 "dhcp6_parser.cc"
    break;

  case 525: // comment: "comment" $@84 ":" "constant string"
#line 1779 "dhcp6_parser.yy"
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
#line 2891 "dhcp6_parser.cc"
    break;

  case 526: // $@85: %empty
#line 1807 "dhcp6_parser.yy"
                        {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2902 "dhcp6_parser.cc"
    break;

  case 527: // pd_pools_list: "pd-pools" $@85 ":" "[" pd_pools_list_content "]"
#line 1812 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2911 "dhcp6_parser.cc"
    break;

  case 532: // $@86: %empty
#line 1827 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2921 "dhcp6_parser.cc"
    break;

  case 533: // pd_pool_entry: "{" $@86 pd_pool_params "}"
#line 1831 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 534: // $@87: %empty
#line 1839 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 535: // sub_pd_pool: "{" $@87 pd_pool_params "}"
#line 1843 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2955 "dhcp6_parser.cc"
    break;

  case 549: // $@88: %empty
#line 1868 "dhcp6_parser.yy"
                  {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2963 "dhcp6_parser.cc"
    break;

  case 550: // pd_prefix: "prefix" $@88 ":" "constant string"
#line 1870 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2973 "dhcp6_parser.cc"
    break;

  case 551: // pd_prefix_len: "prefix-len" ":" "integer"
#line 1876 "dhcp6_parser.yy"
                                        {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2982 "dhcp6_parser.cc"
    break;

  case 552: // $@89: %empty
#line 1881 "dhcp6_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2990 "dhcp6_parser.cc"
    break;

  case 553: // excluded_prefix: "excluded-prefix" $@89 ":" "constant string"
#line 1883 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3000 "dhcp6_parser.cc"
    break;

  case 554: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 1889 "dhcp6_parser.yy"
                                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3009 "dhcp6_parser.cc"
    break;

  case 555: // pd_delegated_len: "delegated-len" ":" "integer"
#line 1894 "dhcp6_parser.yy"
                                              {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3018 "dhcp6_parser.cc"
    break;

  case 556: // $@90: %empty
#line 1902 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3029 "dhcp6_parser.cc"
    break;

  case 557: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 1907 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3038 "dhcp6_parser.cc"
    break;

  case 562: // $@91: %empty
#line 1920 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3048 "dhcp6_parser.cc"
    break;

  case 563: // reservation: "{" $@91 reservation_params "}"
#line 1924 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3057 "dhcp6_parser.cc"
    break;

  case 564: // $@92: %empty
#line 1929 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3067 "dhcp6_parser.cc"
    break;

  case 565: // sub_reservation: "{" $@92 reservation_params "}"
#line 1933 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3076 "dhcp6_parser.cc"
    break;

  case 581: // $@93: %empty
#line 1960 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3087 "dhcp6_parser.cc"
    break;

  case 582: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 1965 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3096 "dhcp6_parser.cc"
    break;

  case 583: // $@94: %empty
#line 1970 "dhcp6_parser.yy"
                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3107 "dhcp6_parser.cc"
    break;

  case 584: // prefixes: "prefixes" $@94 ":" list_strings
#line 1975 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3116 "dhcp6_parser.cc"
    break;

  case 585: // $@95: %empty
#line 1980 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3124 "dhcp6_parser.cc"
    break;

  case 586: // duid: "duid" $@95 ":" "constant string"
#line 1982 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3134 "dhcp6_parser.cc"
    break;

  case 587: // $@96: %empty
#line 1988 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3142 "dhcp6_parser.cc"
    break;

  case 588: // hw_address: "hw-address" $@96 ":" "constant string"
#line 1990 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3152 "dhcp6_parser.cc"
    break;

  case 589: // $@97: %empty
#line 1996 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3160 "dhcp6_parser.cc"
    break;

  case 590: // hostname: "hostname" $@97 ":" "constant string"
#line 1998 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3170 "dhcp6_parser.cc"
    break;

  case 591: // $@98: %empty
#line 2004 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3178 "dhcp6_parser.cc"
    break;

  case 592: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2006 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3188 "dhcp6_parser.cc"
    break;

  case 593: // $@99: %empty
#line 2012 "dhcp6_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3199 "dhcp6_parser.cc"
    break;

  case 594: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2017 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3208 "dhcp6_parser.cc"
    break;

  case 595: // $@100: %empty
#line 2025 "dhcp6_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3219 "dhcp6_parser.cc"
    break;

  case 596: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2030 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3228 "dhcp6_parser.cc"
    break;

  case 599: // $@101: %empty
#line 2039 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3236 "dhcp6_parser.cc"
    break;

  case 600: // ip_address: "ip-address" $@101 ":" "constant string"
#line 2041 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 601: // $@102: %empty
#line 2050 "dhcp6_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 602: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2055 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 605: // $@103: %empty
#line 2064 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 606: // client_class_entry: "{" $@103 client_class_params "}"
#line 2068 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3286 "dhcp6_parser.cc"
    break;

  case 619: // $@104: %empty
#line 2093 "dhcp6_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3294 "dhcp6_parser.cc"
    break;

  case 620: // client_class_test: "test" $@104 ":" "constant string"
#line 2095 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 621: // only_if_required: "only-if-required" ":" "boolean"
#line 2101 "dhcp6_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3313 "dhcp6_parser.cc"
    break;

  case 622: // $@105: %empty
#line 2109 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3324 "dhcp6_parser.cc"
    break;

  case 623: // server_id: "server-id" $@105 ":" "{" server_id_params "}"
#line 2114 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3335 "dhcp6_parser.cc"
    break;

  case 635: // $@106: %empty
#line 2136 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3343 "dhcp6_parser.cc"
    break;

  case 636: // server_id_type: "type" $@106 ":" duid_type
#line 2138 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3352 "dhcp6_parser.cc"
    break;

  case 637: // duid_type: "LLT"
#line 2143 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3358 "dhcp6_parser.cc"
    break;

  case 638: // duid_type: "EN"
#line 2144 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3364 "dhcp6_parser.cc"
    break;

  case 639: // duid_type: "LL"
#line 2145 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3370 "dhcp6_parser.cc"
    break;

  case 640: // htype: "htype" ":" "integer"
#line 2148 "dhcp6_parser.yy"
                           {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3379 "dhcp6_parser.cc"
    break;

  case 641: // $@107: %empty
#line 2153 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3387 "dhcp6_parser.cc"
    break;

  case 642: // identifier: "identifier" $@107 ":" "constant string"
#line 2155 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3397 "dhcp6_parser.cc"
    break;

  case 643: // time: "time" ":" "integer"
#line 2161 "dhcp6_parser.yy"
                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3406 "dhcp6_parser.cc"
    break;

  case 644: // enterprise_id: "enterprise-id" ":" "integer"
#line 2166 "dhcp6_parser.yy"
                                           {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3415 "dhcp6_parser.cc"
    break;

  case 645: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2173 "dhcp6_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3424 "dhcp6_parser.cc"
    break;

  case 646: // $@108: %empty
#line 2180 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3435 "dhcp6_parser.cc"
    break;

  case 647: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2185 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3444 "dhcp6_parser.cc"
    break;

  case 655: // $@109: %empty
#line 2201 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3452 "dhcp6_parser.cc"
    break;

  case 656: // socket_type: "socket-type" $@109 ":" "constant string"
#line 2203 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3462 "dhcp6_parser.cc"
    break;

  case 657: // $@110: %empty
#line 2209 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3470 "dhcp6_parser.cc"
    break;

  case 658: // socket_name: "socket-name" $@110 ":" "constant string"
#line 2211 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3480 "dhcp6_parser.cc"
    break;

  case 659: // $@111: %empty
#line 2220 "dhcp6_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3491 "dhcp6_parser.cc"
    break;

  case 660: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2225 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3502 "dhcp6_parser.cc"
    break;

  case 669: // enable_queue: "enable-queue" ":" "boolean"
#line 2244 "dhcp6_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3511 "dhcp6_parser.cc"
    break;

  case 670: // $@112: %empty
#line 2249 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3519 "dhcp6_parser.cc"
    break;

  case 671: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2251 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3529 "dhcp6_parser.cc"
    break;

  case 672: // capacity: "capacity" ":" "integer"
#line 2257 "dhcp6_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3538 "dhcp6_parser.cc"
    break;

  case 673: // $@113: %empty
#line 2262 "dhcp6_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3546 "dhcp6_parser.cc"
    break;

  case 674: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2264 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 675: // $@114: %empty
#line 2271 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3566 "dhcp6_parser.cc"
    break;

  case 676: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2276 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3577 "dhcp6_parser.cc"
    break;

  case 677: // $@115: %empty
#line 2283 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3587 "dhcp6_parser.cc"
    break;

  case 678: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2287 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3597 "dhcp6_parser.cc"
    break;

  case 699: // enable_updates: "enable-updates" ":" "boolean"
#line 2317 "dhcp6_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3606 "dhcp6_parser.cc"
    break;

  case 700: // $@116: %empty
#line 2322 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3614 "dhcp6_parser.cc"
    break;

  case 701: // qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2324 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3624 "dhcp6_parser.cc"
    break;

  case 702: // $@117: %empty
#line 2330 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3632 "dhcp6_parser.cc"
    break;

  case 703: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2332 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3642 "dhcp6_parser.cc"
    break;

  case 704: // server_port: "server-port" ":" "integer"
#line 2338 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3651 "dhcp6_parser.cc"
    break;

  case 705: // $@118: %empty
#line 2343 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3659 "dhcp6_parser.cc"
    break;

  case 706: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2345 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3669 "dhcp6_parser.cc"
    break;

  case 707: // sender_port: "sender-port" ":" "integer"
#line 2351 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3678 "dhcp6_parser.cc"
    break;

  case 708: // max_queue_size: "max-queue-size" ":" "integer"
#line 2356 "dhcp6_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 709: // $@119: %empty
#line 2361 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3695 "dhcp6_parser.cc"
    break;

  case 710: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2363 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3704 "dhcp6_parser.cc"
    break;

  case 711: // ncr_protocol_value: "UDP"
#line 2369 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3710 "dhcp6_parser.cc"
    break;

  case 712: // ncr_protocol_value: "TCP"
#line 2370 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3716 "dhcp6_parser.cc"
    break;

  case 713: // $@120: %empty
#line 2373 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3724 "dhcp6_parser.cc"
    break;

  case 714: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2375 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3734 "dhcp6_parser.cc"
    break;

  case 715: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2382 "dhcp6_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3743 "dhcp6_parser.cc"
    break;

  case 716: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2388 "dhcp6_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3752 "dhcp6_parser.cc"
    break;

  case 717: // $@121: %empty
#line 2394 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3760 "dhcp6_parser.cc"
    break;

  case 718: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2396 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3769 "dhcp6_parser.cc"
    break;

  case 719: // $@122: %empty
#line 2402 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3777 "dhcp6_parser.cc"
    break;

  case 720: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2404 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3787 "dhcp6_parser.cc"
    break;

  case 721: // $@123: %empty
#line 2411 "dhcp6_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3795 "dhcp6_parser.cc"
    break;

  case 722: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2413 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3805 "dhcp6_parser.cc"
    break;

  case 723: // $@124: %empty
#line 2420 "dhcp6_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3813 "dhcp6_parser.cc"
    break;

  case 724: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2422 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3823 "dhcp6_parser.cc"
    break;

  case 725: // $@125: %empty
#line 2431 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 726: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2436 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3844 "dhcp6_parser.cc"
    break;

  case 727: // $@126: %empty
#line 2442 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 728: // sub_config_control: "{" $@126 config_control_params "}"
#line 2446 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 733: // $@127: %empty
#line 2461 "dhcp6_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3874 "dhcp6_parser.cc"
    break;

  case 734: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2466 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 735: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2471 "dhcp6_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 736: // $@128: %empty
#line 2478 "dhcp6_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3903 "dhcp6_parser.cc"
    break;

  case 737: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2483 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3912 "dhcp6_parser.cc"
    break;

  case 740: // $@129: %empty
#line 2495 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3922 "dhcp6_parser.cc"
    break;

  case 741: // logger_entry: "{" $@129 logger_params "}"
#line 2499 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3930 "dhcp6_parser.cc"
    break;

  case 751: // debuglevel: "debuglevel" ":" "integer"
#line 2516 "dhcp6_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3939 "dhcp6_parser.cc"
    break;

  case 752: // $@130: %empty
#line 2521 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3947 "dhcp6_parser.cc"
    break;

  case 753: // severity: "severity" $@130 ":" "constant string"
#line 2523 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3957 "dhcp6_parser.cc"
    break;

  case 754: // $@131: %empty
#line 2529 "dhcp6_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3968 "dhcp6_parser.cc"
    break;

  case 755: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2534 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3977 "dhcp6_parser.cc"
    break;

  case 758: // $@132: %empty
#line 2543 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3987 "dhcp6_parser.cc"
    break;

  case 759: // output_entry: "{" $@132 output_params_list "}"
#line 2547 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 3995 "dhcp6_parser.cc"
    break;

  case 767: // $@133: %empty
#line 2562 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4003 "dhcp6_parser.cc"
    break;

  case 768: // output: "output" $@133 ":" "constant string"
#line 2564 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4013 "dhcp6_parser.cc"
    break;

  case 769: // flush: "flush" ":" "boolean"
#line 2570 "dhcp6_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4022 "dhcp6_parser.cc"
    break;

  case 770: // maxsize: "maxsize" ":" "integer"
#line 2575 "dhcp6_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 771: // maxver: "maxver" ":" "integer"
#line 2580 "dhcp6_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4040 "dhcp6_parser.cc"
    break;

  case 772: // $@134: %empty
#line 2585 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4048 "dhcp6_parser.cc"
    break;

  case 773: // pattern: "pattern" $@134 ":" "constant string"
#line 2587 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4058 "dhcp6_parser.cc"
    break;


#line 4062 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -941;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     528,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,    57,    34,    81,   104,   114,
     125,   131,   135,   151,   198,   216,   222,   232,   234,   244,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,    34,  -143,
     103,   115,    28,   278,   139,   295,   471,    -9,    66,   118,
     -84,   530,   182,  -941,   119,   252,   298,   296,   307,  -941,
      53,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   308,
     317,   342,   349,   359,   360,   372,   373,   390,   393,   402,
     403,  -941,   406,   412,   415,   422,   428,  -941,  -941,  -941,
     448,   450,   454,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   468,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,   476,  -941,    59,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,   480,  -941,    78,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   481,
     483,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,    96,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   106,
    -941,  -941,  -941,  -941,  -941,   484,  -941,   485,   486,  -941,
    -941,  -941,  -941,  -941,  -941,   107,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,   326,   433,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,   410,  -941,  -941,   488,  -941,  -941,  -941,
     491,  -941,  -941,   461,   453,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   492,   493,
    -941,  -941,  -941,  -941,   496,   502,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   133,  -941,
    -941,  -941,   503,  -941,  -941,   506,  -941,   512,   516,  -941,
    -941,   517,   518,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
     143,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   519,   194,
    -941,  -941,  -941,  -941,    34,    34,  -941,   310,   520,   103,
    -941,   521,   522,   526,   527,   531,   532,   311,   337,   340,
     343,   345,   346,   347,   348,   362,   364,   375,   350,   572,
     381,   382,   391,   392,   395,   576,   577,   578,   404,   405,
     407,   585,   597,   598,   601,   603,   604,   605,   606,   608,
     609,   611,   613,   616,   617,   619,   620,   429,   621,   623,
     624,   625,   626,   627,   628,  -941,   115,  -941,   632,   439,
      28,  -941,   635,   636,   637,   638,   639,   447,   446,   642,
     643,   644,   278,  -941,   650,   139,  -941,   651,   459,   653,
     462,   463,   295,  -941,   654,   657,   658,   660,   661,   662,
     664,  -941,   471,  -941,   665,   666,   474,   669,   670,   673,
     479,  -941,    66,   675,   495,   497,  -941,   118,   676,   691,
      91,  -941,   498,   694,   695,   507,   699,   533,   534,   720,
     721,   529,   535,   723,   725,   728,   729,   530,  -941,   731,
     539,   182,  -941,  -941,  -941,   733,   732,  -941,   542,   734,
     735,   736,   737,   740,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,   544,  -941,  -941,  -941,
    -941,  -941,  -121,   550,   551,  -941,  -941,  -941,   743,   744,
     745,   746,   555,   379,   747,   749,   750,   751,   752,   753,
     755,   756,   757,   758,  -941,   759,   760,   761,   762,   561,
     566,   765,  -941,   766,  -941,  -941,   767,   768,   567,   579,
     580,  -941,  -941,   766,   581,   771,  -941,   583,  -941,   584,
    -941,   586,  -941,  -941,  -941,   766,   766,   766,   587,   588,
     589,   590,  -941,   591,   592,  -941,   593,   594,   595,  -941,
    -941,   596,  -941,  -941,  -941,   599,   746,  -941,  -941,   600,
     602,  -941,   607,  -941,  -941,   102,   615,  -941,  -941,  -121,
     610,   612,   614,  -941,   769,  -941,  -941,    34,   115,  -941,
     182,    28,   242,   242,   786,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,   787,   790,   792,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,   793,   -74,    34,   -46,   696,
     795,   797,   798,   191,    64,   159,    12,   202,   530,  -941,
    -941,   800,  -941,  -941,   802,   804,  -941,  -941,  -941,  -941,
    -941,   -53,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,   786,  -941,   249,   256,   286,  -941,  -941,  -941,  -941,
     808,   809,   810,   811,   812,  -941,   813,   814,  -941,  -941,
    -941,   815,   816,   817,   818,  -941,   289,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   290,  -941,
     819,   820,  -941,  -941,   821,   823,  -941,  -941,   822,   826,
    -941,  -941,   824,   828,  -941,  -941,   827,   829,  -941,  -941,
    -941,   144,  -941,  -941,  -941,   830,  -941,  -941,  -941,   208,
    -941,  -941,  -941,  -941,   344,  -941,  -941,  -941,   219,  -941,
    -941,   831,   832,  -941,  -941,   833,   835,  -941,   836,   837,
     838,   839,   840,   841,   351,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,   842,   843,   844,  -941,  -941,  -941,
    -941,   353,  -941,  -941,  -941,  -941,  -941,  -941,   845,   846,
     847,  -941,   354,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,   383,  -941,  -941,  -941,   848,  -941,
     849,  -941,  -941,  -941,   400,  -941,  -941,  -941,  -941,  -941,
     401,  -941,   330,  -941,   659,  -941,   850,   851,  -941,  -941,
     852,   854,  -941,  -941,  -941,   853,  -941,   856,  -941,  -941,
    -941,   855,   859,   860,   861,   663,   667,   671,   668,   672,
     866,   674,   677,   868,   869,   871,   679,   680,   681,   682,
     242,  -941,  -941,   242,  -941,   786,   278,  -941,   787,    66,
    -941,   790,   118,  -941,   792,   504,  -941,   793,   -74,  -941,
    -941,   -46,  -941,   874,   696,  -941,   304,   795,  -941,   471,
    -941,   797,   -84,  -941,   798,   684,   685,   686,   687,   689,
     690,   191,  -941,   886,   888,   698,   702,   703,    64,  -941,
     704,   705,   712,   159,  -941,   889,   910,    12,  -941,   724,
     916,   742,   926,   202,  -941,  -941,    60,   800,  -941,  -941,
     925,   931,   139,  -941,   802,   295,  -941,   804,   936,  -941,
    -941,    73,   763,   772,   775,  -941,  -941,  -941,  -941,  -941,
     779,  -941,  -941,   780,   782,   783,  -941,  -941,  -941,  -941,
    -941,   414,  -941,   417,  -941,   941,  -941,   948,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
     425,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   788,
    -941,  -941,   961,  -941,  -941,  -941,  -941,  -941,   975,   984,
    -941,  -941,  -941,  -941,  -941,   982,  -941,   426,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,    55,   796,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,   825,   834,  -941,  -941,
     857,  -941,    34,  -941,  -941,  1001,  -941,  -941,  -941,  -941,
    -941,   432,  -941,  -941,  -941,  -941,  -941,  -941,   858,   445,
    -941,   452,  -941,   862,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
     504,  -941,  -941,  1005,   863,  -941,   304,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  1009,   864,
    1014,    60,  -941,  -941,  -941,  -941,  -941,  -941,   867,  -941,
    -941,  1015,  -941,   870,  -941,  -941,  1017,  -941,  -941,   384,
    -941,   128,  1017,  -941,  -941,  1018,  1021,  1023,  -941,   465,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  1024,   865,   872,
     873,  1025,   128,  -941,   875,  -941,  -941,  -941,   876,  -941,
    -941,  -941
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    65,     7,   165,     9,   327,    11,
     509,    13,   534,    15,   564,    17,   434,    19,   442,    21,
     479,    23,   292,    25,   677,    27,   727,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   566,     0,   444,   481,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    63,
       0,    60,    62,   124,   725,   163,   177,   179,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   161,     0,     0,     0,     0,     0,   141,   148,   150,
       0,     0,     0,   319,   432,   471,   522,   524,   379,   387,
     252,   269,   260,   245,   601,   556,   284,   303,   622,     0,
     271,   646,   659,   675,   154,   156,   736,     0,   123,     0,
      67,    69,    70,    71,    72,    73,    74,    75,    76,    77,
     105,   106,   107,    78,   111,   112,   113,   114,   115,   116,
     117,   118,   109,   110,   119,   120,   121,   103,    81,    82,
      83,    84,   100,    85,    87,    86,   122,    91,    92,    79,
     104,    80,    89,    90,    98,    99,   101,    88,    93,    94,
      95,    96,    97,   102,   108,   174,     0,   173,     0,   167,
     169,   170,   171,   172,   501,   526,   369,   371,   373,     0,
       0,   377,   375,   595,   368,   331,   332,   333,   334,   335,
     336,   337,   338,   354,   355,   356,   359,   360,   361,   362,
     363,   364,   365,   366,   357,   358,   367,     0,   329,   342,
     343,   344,   347,   348,   350,   345,   346,   339,   340,   352,
     353,   341,   349,   351,   520,   519,   515,   516,   514,     0,
     511,   513,   517,   518,   549,     0,   552,     0,     0,   548,
     542,   543,   541,   546,   547,     0,   536,   538,   539,   544,
     545,   540,   593,   581,   583,   585,   587,   589,   591,   580,
     577,   578,   579,     0,   567,   568,   572,   573,   570,   574,
     575,   576,   571,     0,   461,   225,     0,   465,   463,   468,
       0,   457,   458,     0,   445,   446,   448,   460,   449,   450,
     451,   467,   452,   453,   454,   455,   456,   495,     0,     0,
     493,   494,   497,   498,     0,   482,   483,   485,   486,   487,
     488,   489,   490,   491,   492,   299,   301,   296,     0,   294,
     297,   298,     0,   700,   702,     0,   705,     0,     0,   709,
     713,     0,     0,   717,   719,   721,   723,   698,   696,   697,
       0,   679,   681,   682,   683,   684,   685,   686,   687,   688,
     689,   690,   691,   692,   693,   694,   695,   733,     0,     0,
     729,   731,   732,    46,     0,     0,    39,     0,     0,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,    66,     0,     0,
       0,   166,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   328,     0,     0,   510,     0,     0,     0,
       0,     0,     0,   535,     0,     0,     0,     0,     0,     0,
       0,   565,     0,   435,     0,     0,     0,     0,     0,     0,
       0,   443,     0,     0,     0,     0,   480,     0,     0,     0,
       0,   293,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   678,     0,
       0,     0,   728,    50,    43,     0,     0,    61,     0,     0,
       0,     0,     0,     0,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,     0,   159,   160,   138,
     139,   140,     0,     0,     0,   152,   153,   158,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   645,     0,     0,     0,     0,     0,
       0,     0,    68,     0,   176,   168,     0,     0,     0,     0,
       0,   385,   386,     0,     0,     0,   330,     0,   512,     0,
     551,     0,   554,   555,   537,     0,     0,     0,     0,     0,
       0,     0,   569,     0,     0,   459,     0,     0,     0,   470,
     447,     0,   499,   500,   484,     0,     0,   295,   699,     0,
       0,   704,     0,   707,   708,     0,     0,   715,   716,     0,
       0,     0,     0,   680,     0,   735,   730,     0,     0,   125,
       0,     0,     0,     0,   183,   162,   143,   144,   145,   146,
     147,   142,   149,   151,   321,   436,   473,    40,   523,   525,
     381,   382,   383,   384,   380,   389,     0,    47,     0,     0,
       0,   558,   286,     0,     0,     0,     0,     0,     0,   155,
     157,     0,    51,   175,   503,   528,   370,   372,   374,   378,
     376,     0,   521,   550,   553,   594,   582,   584,   586,   588,
     590,   592,   462,   226,   466,   464,   469,   496,   300,   302,
     701,   703,   706,   711,   712,   710,   714,   718,   720,   722,
     724,   183,    44,     0,     0,     0,   212,   218,   220,   222,
       0,     0,     0,     0,     0,   236,     0,     0,   239,   241,
     243,     0,     0,     0,     0,   211,     0,   189,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   203,   210,
     204,   205,   206,   201,   202,   207,   208,   209,     0,   187,
       0,   184,   185,   325,     0,   322,   323,   440,     0,   437,
     438,   477,     0,   474,   475,   393,     0,   390,   391,   258,
     259,     0,   254,   256,   257,     0,   267,   268,   264,     0,
     262,   265,   266,   250,     0,   247,   249,   605,     0,   603,
     562,     0,   559,   560,   290,     0,   287,   288,     0,     0,
       0,     0,     0,     0,     0,   305,   307,   308,   309,   310,
     311,   312,   635,   641,     0,     0,     0,   634,   631,   632,
     633,     0,   624,   626,   629,   627,   628,   630,     0,     0,
       0,   280,     0,   273,   275,   276,   277,   278,   279,   655,
     657,   654,   652,   653,     0,   648,   650,   651,     0,   670,
       0,   673,   666,   667,     0,   661,   663,   664,   665,   668,
       0,   740,     0,   738,    53,   507,     0,   504,   505,   532,
       0,   529,   530,   599,   598,     0,   597,     0,    64,   726,
     164,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,   180,     0,   182,     0,     0,   320,     0,   444,
     433,     0,   481,   472,     0,     0,   388,     0,     0,   253,
     270,     0,   261,     0,     0,   246,   607,     0,   602,   566,
     557,     0,     0,   285,     0,     0,     0,     0,     0,     0,
       0,     0,   304,     0,     0,     0,     0,     0,     0,   623,
       0,     0,     0,     0,   272,     0,     0,     0,   647,     0,
       0,     0,     0,     0,   660,   676,     0,     0,   737,    55,
       0,    54,     0,   502,     0,     0,   527,     0,     0,   596,
     734,     0,     0,     0,     0,   224,   227,   228,   229,   230,
       0,   238,   231,     0,     0,     0,   233,   234,   235,   232,
     190,     0,   186,     0,   324,     0,   439,     0,   476,   431,
     408,   409,   410,   412,   413,   414,   401,   402,   417,   418,
     419,   422,   423,   424,   425,   426,   427,   428,   429,   420,
     421,   430,   397,   398,   399,   400,   406,   407,   405,   411,
       0,   395,   403,   415,   416,   404,   392,   255,   263,     0,
     248,   619,     0,   617,   618,   614,   615,   616,     0,   608,
     609,   611,   612,   613,   604,     0,   561,     0,   289,   313,
     314,   315,   316,   317,   318,   306,     0,     0,   640,   643,
     644,   625,   281,   282,   283,   274,     0,     0,   649,   669,
       0,   672,     0,   662,   754,     0,   752,   750,   744,   748,
     749,     0,   742,   746,   747,   745,   739,    52,     0,     0,
     506,     0,   531,     0,   214,   215,   216,   217,   213,   219,
     221,   223,   237,   240,   242,   244,   188,   326,   441,   478,
       0,   394,   251,     0,     0,   606,     0,   563,   291,   637,
     638,   639,   636,   642,   656,   658,   671,   674,     0,     0,
       0,     0,   741,    56,   508,   533,   600,   396,     0,   621,
     610,     0,   751,     0,   743,   620,     0,   753,   758,     0,
     756,     0,     0,   755,   767,     0,     0,     0,   772,     0,
     760,   762,   763,   764,   765,   766,   757,     0,     0,     0,
       0,     0,     0,   759,     0,   769,   770,   771,     0,   761,
     768,   773
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,    -4,  -941,  -539,  -941,
     178,  -941,  -941,  -941,  -941,   137,  -941,  -562,  -941,  -941,
    -941,   -71,  -941,  -941,  -941,   629,  -941,  -941,  -941,  -941,
     365,   569,  -941,  -941,   -59,   -43,   -40,   -39,   -37,   -23,
     -21,   -19,   -18,   -15,    -3,  -941,    -1,    16,    29,    30,
    -941,   377,    32,  -941,    33,  -941,    35,    45,    46,  -941,
      47,  -941,    50,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,   361,   570,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,   292,  -941,    82,  -941,  -657,    94,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   -47,  -941,
    -693,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,    67,  -941,  -941,  -941,  -941,  -941,    77,  -676,  -941,
    -941,  -941,  -941,    75,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,    44,  -941,  -941,  -941,  -941,  -941,  -941,  -941,    65,
    -941,  -941,  -941,    68,   536,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,    61,  -941,  -941,  -941,  -941,  -941,  -941,  -940,
    -941,  -941,  -941,    90,  -941,  -941,  -941,    95,   573,  -941,
    -941,  -938,  -941,  -937,  -941,     9,  -941,    54,  -941,    51,
    -941,  -941,  -941,  -936,  -941,  -941,  -941,  -941,    92,  -941,
    -941,  -123,   983,  -941,  -941,  -941,  -941,  -941,   112,  -941,
    -941,  -941,   108,  -941,   553,  -941,   -73,  -941,  -941,  -941,
    -941,  -941,   -66,  -941,  -941,  -941,  -941,  -941,    17,  -941,
    -941,  -941,   110,  -941,  -941,  -941,   113,  -941,   560,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
      56,  -941,  -941,  -941,    62,   618,  -941,  -941,   -55,  -941,
       1,  -941,  -941,  -941,  -941,  -941,    41,  -941,  -941,  -941,
      58,   622,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   -58,
    -941,  -941,  -941,    97,  -941,  -941,  -941,   109,  -941,   630,
     366,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -930,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,   105,  -941,  -941,  -941,  -105,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,    87,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,    79,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,    76,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,   385,   554,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,   420,   556,  -941,
    -941,  -941,  -941,  -941,  -941,    83,  -941,  -941,  -109,  -941,
    -941,  -941,  -941,  -941,  -941,  -128,  -941,  -941,  -147,  -941,
    -941,  -941,  -941,  -941,  -941,  -941
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     688,    87,    88,    41,    68,    84,    85,   713,   914,  1020,
    1021,   775,    43,    70,    90,    91,    92,   408,    45,    71,
     149,   150,   151,   411,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     435,   681,   168,   436,   169,   437,   170,   171,   172,   462,
     173,   463,   174,   175,   176,   177,   429,   178,   413,    47,
      72,   208,   209,   210,   468,   211,   179,   414,   180,   415,
     181,   416,   800,   801,   802,   953,   776,   777,   778,   931,
    1168,   779,   932,   780,   933,   781,   934,   782,   783,   505,
     784,   785,   786,   787,   788,   789,   790,   791,   792,   793,
     940,   794,   795,   943,   796,   944,   797,   945,   182,   451,
     834,   835,   836,   973,   183,   448,   821,   822,   823,   824,
     184,   450,   829,   830,   831,   832,   185,   449,   186,   458,
     882,   883,   884,   885,   886,   187,   454,   845,   846,   847,
     982,    63,    80,   358,   359,   360,   518,   361,   519,   188,
     455,   854,   855,   856,   857,   858,   859,   860,   861,   189,
     441,   804,   805,   806,   956,    49,    73,   247,   248,   249,
     474,   250,   475,   251,   476,   252,   480,   253,   479,   190,
     446,   694,   255,   256,   191,   447,   816,   817,   818,   965,
    1090,  1091,   192,   442,    57,    77,   808,   809,   810,   959,
      59,    78,   323,   324,   325,   326,   327,   328,   329,   504,
     330,   508,   331,   507,   332,   333,   509,   334,   193,   443,
     812,   813,   814,   962,    61,    79,   344,   345,   346,   347,
     348,   513,   349,   350,   351,   352,   258,   472,   916,   917,
     918,  1022,    51,    74,   269,   270,   271,   484,   194,   444,
     195,   445,   261,   473,   920,   921,   922,  1025,    53,    75,
     285,   286,   287,   487,   288,   289,   489,   290,   291,   196,
     453,   841,   842,   843,   979,    55,    76,   303,   304,   305,
     306,   495,   307,   496,   308,   497,   309,   498,   310,   499,
     311,   500,   312,   494,   263,   481,   925,   926,  1028,   197,
     452,   838,   839,   976,  1108,  1109,  1110,  1111,  1112,  1183,
    1113,   198,   456,   871,   872,   873,   993,  1192,   874,   875,
     994,   876,   877,   199,   200,   459,   894,   895,   896,  1005,
     897,  1006,   201,   460,   904,   905,   906,   907,  1010,   908,
     909,  1012,   202,   461,    65,    81,   380,   381,   382,   383,
     523,   384,   524,   385,   386,   526,   387,   388,   389,   529,
     745,   390,   530,   391,   392,   393,   533,   394,   534,   395,
     535,   396,   536,   203,   412,    67,    82,   399,   400,   401,
     539,   402,   204,   464,   912,   913,  1016,  1151,  1152,  1153,
    1154,  1200,  1155,  1198,  1219,  1220,  1221,  1229,  1230,  1231,
    1237,  1232,  1233,  1234,  1235,  1241
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     148,   207,   224,   265,   279,   299,   342,   321,   340,   357,
     377,   868,    38,   343,   225,   262,   798,   212,   259,   272,
     283,   301,   828,   335,   353,  1083,   378,  1084,  1085,  1089,
     226,   322,   341,   227,   228,  1095,   229,   355,   356,    31,
     819,    32,   687,    33,   205,   206,   676,   677,   678,   679,
     230,   719,   231,    86,   232,   233,   409,    30,   234,   293,
     124,   410,   466,   725,   726,   727,   923,   467,   819,   826,
     235,   827,   236,   213,   260,   273,   284,   302,   680,   336,
     354,   470,   379,   266,   280,   862,   471,   314,    42,   237,
     257,   268,   282,   300,   761,  1164,  1165,  1166,  1167,   482,
     126,   127,   238,   239,   483,   240,   241,   687,   242,   485,
     492,    44,   147,    89,   486,   493,   126,   127,   243,   244,
     245,    46,   820,   246,   254,   403,    93,    94,   267,   281,
      95,   315,    48,    96,    97,    98,   520,   315,    50,   316,
     317,   521,    52,   318,   319,   320,   537,   968,   126,   127,
     969,   538,   126,   127,   126,   127,   889,   890,    54,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,  1189,  1190,  1191,   315,
     337,   316,   317,   338,   339,   397,   398,   541,   863,   864,
     865,   866,   542,   126,   127,    56,   126,   127,   147,   125,
     128,   971,   355,   356,   972,   129,   130,   131,   132,   133,
     264,   134,   977,    58,   147,   978,   135,   126,   127,    60,
      34,    35,    36,    37,  1144,   136,  1145,  1146,   137,    62,
    1083,    64,  1084,  1085,  1089,   138,   221,   126,   127,   222,
    1095,    66,   466,   139,   140,   404,   147,   928,   141,   541,
     147,   142,   147,   756,   929,   143,   743,   744,   757,   758,
     759,   760,   761,   762,   763,   764,   765,   766,   767,   768,
     769,   770,   771,   772,   773,   774,   144,   145,   146,   470,
     126,   127,   950,   950,   930,   828,  1051,   951,   952,   878,
     879,   880,   405,  1224,   406,   868,  1225,  1226,  1227,  1228,
     407,   147,   417,   315,   147,   848,   849,   850,   851,   852,
     853,   418,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,  1017,   501,   147,  1018,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   419,   974,   125,   898,
     899,   900,   975,   420,   991,   147,   998,  1003,   214,   992,
     215,   999,  1004,   421,   422,   125,   126,   127,   216,   217,
     218,   219,   220,   128,   125,   315,   423,   424,   274,   275,
     276,   277,   278,   126,   127,   221,  1007,  1222,   222,   135,
    1223,  1008,   126,   127,   425,   148,   223,   426,   901,   207,
     543,   544,   221,  1013,   537,   222,   427,   428,  1014,  1015,
     430,   224,  1101,  1102,   265,   212,   431,   950,   503,   432,
     482,   279,  1176,   225,   262,  1177,   433,   259,  1180,   520,
     272,   299,   434,  1181,  1188,  1201,   502,   283,   147,   226,
    1202,   321,   227,   228,   342,   229,   340,   301,   485,   144,
     145,   343,   438,  1204,   439,   492,   512,   335,   440,   230,
    1205,   231,   353,   232,   233,   322,   377,   234,  1242,   511,
     341,   213,   457,  1243,   147,   690,   691,   692,   693,   235,
     465,   236,   378,   260,   469,   477,   273,   478,   488,   490,
     491,   147,   506,   284,   266,   510,   514,   515,   237,   257,
     147,   280,   268,   302,   516,   517,   545,   522,   554,   282,
     525,   238,   239,   336,   240,   241,   527,   242,   354,   300,
     528,   531,   532,   540,   546,   548,   549,   243,   244,   245,
     550,   551,   246,   254,   555,   552,   553,   556,   379,   267,
     557,   125,   558,   559,   560,   561,   281,   565,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   126,
     127,   562,   563,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   564,   125,   315,   566,   292,   567,   568,
     572,   573,   574,   293,   294,   295,   296,   297,   298,   578,
     569,   570,   126,   127,   571,   217,   218,   148,   220,   128,
     207,   579,   580,   575,   576,   581,   577,   582,   583,   584,
     585,   221,   586,   587,   222,   588,   212,   589,   126,   127,
     590,   591,   223,   592,   593,   595,   594,   596,   597,   598,
     599,   600,   601,   867,   881,   891,   603,   377,   604,   606,
     607,   608,   609,   610,   611,   612,   613,   614,   615,   869,
     887,   892,   902,   378,   617,   619,   620,   621,   625,   622,
     623,   626,   627,   752,   628,   629,   630,   147,   631,   633,
     634,   635,   213,   636,   637,   144,   145,   638,   639,   641,
     645,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   642,   646,   643,   648,   649,   650,
     147,   375,   376,   652,   651,   870,   888,   893,   903,   379,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,   655,   656,   147,   659,   657,   660,
     653,   654,   661,   662,   658,   664,   665,   667,   669,   668,
     675,   670,   671,   672,   673,   674,   682,   683,   684,   685,
     686,   689,   695,    32,   696,   697,   698,   709,   700,   699,
     701,   702,   710,   716,   703,   704,   705,   706,   707,   708,
     711,   712,   714,   715,   751,   717,   718,   720,   721,   722,
     723,   746,   724,   728,   729,   730,   731,   732,   733,   734,
     735,   736,   737,   799,   803,   738,   740,   807,   741,   811,
     815,   833,   837,   742,   840,   844,   748,   911,   749,   915,
     750,   919,   935,   936,   937,   938,   939,   941,   942,   946,
     947,   948,   949,   955,   739,   954,   958,   957,   960,   961,
     963,   964,   967,   966,   825,   981,   970,   980,   984,   983,
     985,   986,   987,   988,   989,   990,   995,   996,   997,  1000,
    1001,  1002,  1009,  1011,  1024,  1019,  1023,  1027,  1026,  1031,
    1035,  1029,  1030,  1032,  1033,  1034,  1036,  1038,  1037,  1039,
    1040,  1041,  1043,  1044,  1042,  1045,  1046,  1047,  1099,  1049,
    1048,  1119,  1120,  1121,  1122,   224,  1123,  1124,   321,   342,
    1126,   340,  1127,  1136,  1059,  1128,   343,   225,   262,  1129,
    1130,   259,  1133,  1132,   335,  1103,  1060,   353,   299,  1134,
    1093,   357,   322,   226,  1137,   341,   227,   228,  1082,   229,
    1140,  1106,  1061,  1139,   301,  1062,  1063,   867,  1064,  1104,
    1142,  1157,   881,   230,  1158,   231,   891,   232,   233,  1141,
    1163,   234,  1065,   869,  1066,  1147,  1067,  1068,   887,  1178,
    1069,   265,   892,   235,   279,   236,  1179,   260,   902,  1169,
     336,  1149,  1070,   354,  1071,  1184,  1094,   272,  1170,  1148,
     283,  1171,   237,   257,  1086,  1172,  1173,  1107,  1174,  1175,
     302,  1072,  1092,  1185,  1182,   238,   239,  1186,   240,   241,
    1187,   242,  1193,  1105,  1073,  1074,   300,  1075,  1076,   870,
    1077,   243,   244,   245,   888,  1199,   246,   254,   893,  1208,
    1078,  1079,  1080,  1211,   903,  1081,  1088,  1150,  1213,  1087,
    1216,  1194,  1238,   273,  1218,  1239,   284,  1240,  1244,  1248,
    1195,   266,   755,   753,   280,   602,   747,  1052,   547,   268,
     605,  1100,   282,   927,  1050,  1097,  1098,  1135,  1054,  1118,
    1117,  1053,  1125,  1196,  1203,   616,   647,  1207,  1206,  1096,
     313,  1212,  1209,  1215,  1245,   640,  1217,  1055,  1162,  1246,
    1247,  1250,  1251,  1056,  1058,  1057,   267,   644,  1116,   281,
    1160,  1210,  1114,  1161,  1159,  1131,  1138,   924,  1115,  1143,
     754,   663,  1214,   910,  1236,  1249,     0,   666,     0,     0,
    1156,     0,     0,   618,     0,     0,     0,     0,     0,  1059,
       0,     0,     0,     0,   624,  1103,     0,     0,     0,     0,
       0,  1060,     0,     0,     0,  1093,     0,     0,     0,     0,
    1147,  1106,   632,  1082,     0,     0,     0,  1061,  1197,  1104,
    1062,  1063,     0,  1064,     0,     0,  1149,     0,     0,     0,
       0,     0,     0,     0,  1148,     0,     0,  1065,     0,  1066,
       0,  1067,  1068,     0,     0,  1069,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1070,     0,  1071,
       0,  1094,     0,     0,     0,     0,     0,  1107,     0,  1086,
       0,     0,     0,     0,     0,     0,  1072,  1092,     0,     0,
       0,     0,  1150,  1105,     0,     0,     0,     0,     0,  1073,
    1074,     0,  1075,  1076,     0,  1077,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1078,  1079,  1080,     0,     0,
    1081,  1088,     0,     0,  1087
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    79,    78,    79,    80,
      81,   704,    16,    79,    73,    73,   673,    72,    73,    74,
      75,    76,   698,    78,    79,   965,    81,   965,   965,   965,
      73,    78,    79,    73,    73,   965,    73,   121,   122,     5,
     114,     7,   581,     9,    16,    17,   167,   168,   169,   170,
      73,   613,    73,   196,    73,    73,     3,     0,    73,   112,
      69,     8,     3,   625,   626,   627,   119,     8,   114,   115,
      73,   117,    73,    72,    73,    74,    75,    76,   199,    78,
      79,     3,    81,    74,    75,    21,     8,    21,     7,    73,
      73,    74,    75,    76,    30,    22,    23,    24,    25,     3,
      88,    89,    73,    73,     8,    73,    73,   646,    73,     3,
       3,     7,   196,    10,     8,     8,    88,    89,    73,    73,
      73,     7,   196,    73,    73,     6,    11,    12,    74,    75,
      15,    71,     7,    18,    19,    20,     3,    71,     7,    73,
      74,     8,     7,    77,    78,    79,     3,     3,    88,    89,
       6,     8,    88,    89,    88,    89,   144,   145,     7,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,   131,   132,   133,    71,
      72,    73,    74,    75,    76,    13,    14,     3,   134,   135,
     136,   137,     8,    88,    89,     7,    88,    89,   196,    70,
      95,     3,   121,   122,     6,   100,   101,   102,   103,   104,
      81,   106,     3,     7,   196,     6,   111,    88,    89,     7,
     196,   197,   198,   199,   174,   120,   176,   177,   123,     7,
    1180,     7,  1180,  1180,  1180,   130,   107,    88,    89,   110,
    1180,     7,     3,   138,   139,     3,   196,     8,   143,     3,
     196,   146,   196,    21,     8,   150,   164,   165,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,   171,   172,   173,     3,
      88,    89,     3,     3,     8,   971,   953,     8,     8,   140,
     141,   142,     4,   175,     8,   998,   178,   179,   180,   181,
       3,   196,     4,    71,   196,   124,   125,   126,   127,   128,
     129,     4,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,     3,     8,   196,     6,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     4,     3,    70,   147,
     148,   149,     8,     4,     3,   196,     3,     3,    80,     8,
      82,     8,     8,     4,     4,    70,    88,    89,    90,    91,
      92,    93,    94,    95,    70,    71,     4,     4,    83,    84,
      85,    86,    87,    88,    89,   107,     3,     3,   110,   111,
       6,     8,    88,    89,     4,   466,   118,     4,   196,   470,
     404,   405,   107,     3,     3,   110,     4,     4,     8,     8,
       4,   482,   108,   109,   485,   470,     4,     3,     8,     4,
       3,   492,     8,   482,   482,     8,     4,   482,     3,     3,
     485,   502,     4,     8,     8,     3,     3,   492,   196,   482,
       8,   512,   482,   482,   517,   482,   517,   502,     3,   171,
     172,   517,     4,     8,     4,     3,     3,   512,     4,   482,
       8,   482,   517,   482,   482,   512,   537,   482,     3,     8,
     517,   470,     4,     8,   196,    96,    97,    98,    99,   482,
       4,   482,   537,   482,     4,     4,   485,     4,     4,     4,
       4,   196,     4,   492,   485,     4,     4,     4,   482,   482,
     196,   492,   485,   502,     8,     3,   196,     4,   197,   492,
       4,   482,   482,   512,   482,   482,     4,   482,   517,   502,
       4,     4,     4,     4,     4,     4,     4,   482,   482,   482,
       4,     4,   482,   482,   197,     4,     4,   197,   537,   485,
     197,    70,   197,   197,   197,   197,   492,   197,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    88,
      89,   199,   198,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,   198,    70,    71,     4,   106,   197,   197,
       4,     4,     4,   112,   113,   114,   115,   116,   117,     4,
     199,   199,    88,    89,   199,    91,    92,   668,    94,    95,
     671,     4,     4,   199,   199,     4,   199,     4,     4,     4,
       4,   107,     4,     4,   110,     4,   671,     4,    88,    89,
       4,     4,   118,     4,     4,     4,   197,     4,     4,     4,
       4,     4,     4,   704,   705,   706,     4,   708,   199,     4,
       4,     4,     4,     4,   197,   199,     4,     4,     4,   704,
     705,   706,   707,   708,     4,     4,   197,     4,     4,   197,
     197,     4,     4,   667,     4,     4,     4,   196,     4,     4,
       4,   197,   671,     4,     4,   171,   172,     4,   199,     4,
       4,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   199,     4,   199,   199,     4,     4,
     196,   171,   172,     4,   197,   704,   705,   706,   707,   708,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,     4,     4,   196,     4,   199,     4,
     197,   197,     4,     4,   199,     4,   197,     4,   196,     7,
     196,     7,     7,     7,     7,     5,   196,   196,     5,     5,
       5,   196,     5,     7,     5,     5,     5,   196,     5,     7,
       5,     5,   196,   196,     7,     7,     7,     7,     7,     7,
       5,     5,     5,     5,     5,   196,   196,   196,     7,   196,
     196,   166,   196,   196,   196,   196,   196,   196,   196,   196,
     196,   196,   196,     7,     7,   196,   196,     7,   196,     7,
       7,   105,     7,   196,     7,     7,   196,     7,   196,     7,
     196,     7,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   646,     6,     3,     6,     6,     3,
       6,     3,     3,     6,   697,     3,     6,     6,     3,     6,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   196,     6,     3,     6,     4,
     197,     8,     6,     4,     4,     4,   199,   199,   197,   197,
       4,   197,     4,     4,   197,     4,   197,   197,     4,   197,
     199,   197,   197,   197,   197,   956,   197,   197,   959,   962,
       4,   962,     4,     4,   965,   197,   962,   956,   956,   197,
     197,   956,   197,   199,   959,   976,   965,   962,   979,   197,
     965,   982,   959,   956,     4,   962,   956,   956,   965,   956,
       4,   976,   965,   199,   979,   965,   965,   998,   965,   976,
       4,     6,  1003,   956,     3,   956,  1007,   956,   956,   197,
       4,   956,   965,   998,   965,  1016,   965,   965,  1003,     8,
     965,  1022,  1007,   956,  1025,   956,     8,   956,  1013,   196,
     959,  1016,   965,   962,   965,     4,   965,  1022,   196,  1016,
    1025,   196,   956,   956,   965,   196,   196,   976,   196,   196,
     979,   965,   965,     8,   196,   956,   956,     3,   956,   956,
       8,   956,   196,   976,   965,   965,   979,   965,   965,   998,
     965,   956,   956,   956,  1003,     4,   956,   956,  1007,     4,
     965,   965,   965,     4,  1013,   965,   965,  1016,     4,   965,
       5,   196,     4,  1022,     7,     4,  1025,     4,     4,     4,
     196,  1022,   671,   668,  1025,   466,   659,   955,   409,  1022,
     470,   974,  1025,   751,   950,   968,   971,  1003,   958,   984,
     982,   956,   991,   196,   196,   482,   520,  1180,   196,   967,
      77,   197,   199,   196,   199,   512,   196,   959,  1027,   197,
     197,   196,   196,   961,   964,   962,  1022,   517,   981,  1025,
    1024,  1186,   977,  1025,  1022,   998,  1007,   721,   979,  1013,
     670,   537,  1201,   708,  1222,  1242,    -1,   541,    -1,    -1,
    1017,    -1,    -1,   485,    -1,    -1,    -1,    -1,    -1,  1180,
      -1,    -1,    -1,    -1,   492,  1186,    -1,    -1,    -1,    -1,
      -1,  1180,    -1,    -1,    -1,  1180,    -1,    -1,    -1,    -1,
    1201,  1186,   502,  1180,    -1,    -1,    -1,  1180,  1142,  1186,
    1180,  1180,    -1,  1180,    -1,    -1,  1201,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1201,    -1,    -1,  1180,    -1,  1180,
      -1,  1180,  1180,    -1,    -1,  1180,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1180,    -1,  1180,
      -1,  1180,    -1,    -1,    -1,    -1,    -1,  1186,    -1,  1180,
      -1,    -1,    -1,    -1,    -1,    -1,  1180,  1180,    -1,    -1,
      -1,    -1,  1201,  1186,    -1,    -1,    -1,    -1,    -1,  1180,
    1180,    -1,  1180,  1180,    -1,  1180,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1180,  1180,  1180,    -1,    -1,
    1180,  1180,    -1,    -1,  1180
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
       0,     5,     7,     9,   196,   197,   198,   199,   216,   217,
     218,   223,     7,   232,     7,   238,     7,   279,     7,   385,
       7,   462,     7,   478,     7,   495,     7,   414,     7,   420,
       7,   444,     7,   361,     7,   564,     7,   595,   224,   219,
     233,   239,   280,   386,   463,   479,   496,   415,   421,   445,
     362,   565,   596,   216,   225,   226,   196,   221,   222,    10,
     234,   235,   236,    11,    12,    15,    18,    19,    20,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    88,    89,    95,   100,
     101,   102,   103,   104,   106,   111,   120,   123,   130,   138,
     139,   143,   146,   150,   171,   172,   173,   196,   231,   240,
     241,   242,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   262,   264,
     266,   267,   268,   270,   272,   273,   274,   275,   277,   286,
     288,   290,   328,   334,   340,   346,   348,   355,   369,   379,
     399,   404,   412,   438,   468,   470,   489,   519,   531,   543,
     544,   552,   562,   593,   602,    16,    17,   231,   281,   282,
     283,   285,   468,   470,    80,    82,    90,    91,    92,    93,
      94,   107,   110,   118,   231,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   256,   257,   258,   259,
     262,   264,   266,   267,   268,   270,   272,   387,   388,   389,
     391,   393,   395,   397,   399,   402,   403,   438,   456,   468,
     470,   472,   489,   514,    81,   231,   395,   397,   438,   464,
     465,   466,   468,   470,    83,    84,    85,    86,    87,   231,
     395,   397,   438,   468,   470,   480,   481,   482,   484,   485,
     487,   488,   106,   112,   113,   114,   115,   116,   117,   231,
     438,   468,   470,   497,   498,   499,   500,   502,   504,   506,
     508,   510,   512,   412,    21,    71,    73,    74,    77,    78,
      79,   231,   308,   422,   423,   424,   425,   426,   427,   428,
     430,   432,   434,   435,   437,   468,   470,    72,    75,    76,
     231,   308,   426,   432,   446,   447,   448,   449,   450,   452,
     453,   454,   455,   468,   470,   121,   122,   231,   363,   364,
     365,   367,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   171,   172,   231,   468,   470,
     566,   567,   568,   569,   571,   573,   574,   576,   577,   578,
     581,   583,   584,   585,   587,   589,   591,    13,    14,   597,
     598,   599,   601,     6,     3,     4,     8,     3,   237,     3,
       8,   243,   594,   278,   287,   289,   291,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   276,
       4,     4,     4,     4,     4,   260,   263,   265,     4,     4,
       4,   380,   413,   439,   469,   471,   400,   405,   335,   347,
     341,   329,   520,   490,   356,   370,   532,     4,   349,   545,
     553,   563,   269,   271,   603,     4,     3,     8,   284,     4,
       3,     8,   457,   473,   390,   392,   394,     4,     4,   398,
     396,   515,     3,     8,   467,     3,     8,   483,     4,   486,
       4,     4,     3,     8,   513,   501,   503,   505,   507,   509,
     511,     8,     3,     8,   429,   309,     4,   433,   431,   436,
       4,     8,     3,   451,     4,     4,     8,     3,   366,   368,
       3,     8,     4,   570,   572,     4,   575,     4,     4,   579,
     582,     4,     4,   586,   588,   590,   592,     3,     8,   600,
       4,     3,     8,   216,   216,   196,     4,   235,     4,     4,
       4,     4,     4,     4,   197,   197,   197,   197,   197,   197,
     197,   197,   199,   198,   198,   197,     4,   197,   197,   199,
     199,   199,     4,     4,     4,   199,   199,   199,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   197,     4,     4,     4,     4,     4,
       4,     4,   241,     4,   199,   282,     4,     4,     4,     4,
       4,   197,   199,     4,     4,     4,   388,     4,   465,     4,
     197,     4,   197,   197,   481,     4,     4,     4,     4,     4,
       4,     4,   499,     4,     4,   197,     4,     4,     4,   199,
     424,     4,   199,   199,   448,     4,     4,   364,   199,     4,
       4,   197,     4,   197,   197,     4,     4,   199,   199,     4,
       4,     4,     4,   567,     4,   197,   598,     4,     7,   196,
       7,     7,     7,     7,     5,   196,   167,   168,   169,   170,
     199,   261,   196,   196,     5,     5,     5,   218,   220,   196,
      96,    97,    98,    99,   401,     5,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     7,     7,   196,
     196,     5,     5,   227,     5,     5,   196,   196,   196,   227,
     196,     7,   196,   196,   196,   227,   227,   227,   196,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   220,
     196,   196,   196,   164,   165,   580,   166,   261,   196,   196,
     196,     5,   216,   240,   597,   281,    21,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,   231,   296,   297,   298,   301,
     303,   305,   307,   308,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   321,   322,   324,   326,   296,     7,
     292,   293,   294,     7,   381,   382,   383,     7,   416,   417,
     418,     7,   440,   441,   442,     7,   406,   407,   408,   114,
     196,   336,   337,   338,   339,   225,   115,   117,   338,   342,
     343,   344,   345,   105,   330,   331,   332,     7,   521,   522,
       7,   491,   492,   493,     7,   357,   358,   359,   124,   125,
     126,   127,   128,   129,   371,   372,   373,   374,   375,   376,
     377,   378,    21,   134,   135,   136,   137,   231,   310,   468,
     470,   533,   534,   535,   538,   539,   541,   542,   140,   141,
     142,   231,   350,   351,   352,   353,   354,   468,   470,   144,
     145,   231,   468,   470,   546,   547,   548,   550,   147,   148,
     149,   196,   468,   470,   554,   555,   556,   557,   559,   560,
     566,     7,   604,   605,   228,     7,   458,   459,   460,     7,
     474,   475,   476,   119,   500,   516,   517,   292,     8,     8,
       8,   299,   302,   304,   306,     4,     4,     4,     4,     4,
     320,     4,     4,   323,   325,   327,     4,     4,     4,     4,
       3,     8,     8,   295,     6,     3,   384,     6,     3,   419,
       6,     3,   443,     6,     3,   409,     6,     3,     3,     6,
       6,     3,     6,   333,     3,     8,   523,     3,     6,   494,
       6,     3,   360,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   536,   540,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   549,   551,     3,     8,     4,
     558,     4,   561,     3,     8,     8,   606,     3,     6,   196,
     229,   230,   461,     6,     3,   477,     6,     3,   518,     8,
       6,     4,     4,     4,     4,   197,   199,   197,   199,   197,
       4,   197,   197,     4,     4,     4,   197,   197,   199,   197,
     297,   296,   294,   387,   383,   422,   418,   446,   442,   231,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   256,   257,   258,   259,   262,   264,   266,   267,   268,
     270,   272,   308,   379,   391,   393,   395,   397,   399,   403,
     410,   411,   438,   468,   470,   514,   408,   337,   343,     4,
     331,   108,   109,   231,   308,   438,   468,   470,   524,   525,
     526,   527,   528,   530,   522,   497,   493,   363,   359,   197,
     197,   197,   197,   197,   197,   372,     4,     4,   197,   197,
     197,   534,   199,   197,   197,   351,     4,     4,   547,   199,
       4,   197,     4,   555,   174,   176,   177,   231,   308,   468,
     470,   607,   608,   609,   610,   612,   605,     6,     3,   464,
     460,   480,   476,     4,    22,    23,    24,    25,   300,   196,
     196,   196,   196,   196,   196,   196,     8,     8,     8,     8,
       3,     8,   196,   529,     4,     8,     3,     8,     8,   131,
     132,   133,   537,   196,   196,   196,   196,   216,   613,     4,
     611,     3,     8,   196,     8,     8,   196,   411,     4,   199,
     526,     4,   197,     4,   608,   196,     5,   196,     7,   614,
     615,   616,     3,     6,   175,   178,   179,   180,   181,   617,
     618,   619,   621,   622,   623,   624,   615,   620,     4,     4,
       4,   625,     3,     8,     4,   199,   197,   197,     4,   618,
     196,   196
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   200,   202,   201,   203,   201,   204,   201,   205,   201,
     206,   201,   207,   201,   208,   201,   209,   201,   210,   201,
     211,   201,   212,   201,   213,   201,   214,   201,   215,   201,
     216,   216,   216,   216,   216,   216,   216,   217,   219,   218,
     220,   221,   221,   222,   222,   224,   223,   225,   225,   226,
     226,   228,   227,   229,   229,   230,   230,   231,   233,   232,
     234,   234,   235,   237,   236,   239,   238,   240,   240,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   243,   242,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   260,   259,   261,   261,   261,   261,   261,   263,   262,
     265,   264,   266,   267,   269,   268,   271,   270,   272,   273,
     274,   276,   275,   278,   277,   280,   279,   281,   281,   282,
     282,   282,   282,   282,   284,   283,   285,   287,   286,   289,
     288,   291,   290,   292,   292,   293,   293,   295,   294,   296,
     296,   297,   297,   297,   297,   297,   297,   297,   297,   297,
     297,   297,   297,   297,   297,   297,   297,   297,   297,   297,
     297,   297,   299,   298,   300,   300,   300,   300,   302,   301,
     304,   303,   306,   305,   307,   309,   308,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   320,   319,   321,   323,
     322,   325,   324,   327,   326,   329,   328,   330,   330,   331,
     333,   332,   335,   334,   336,   336,   337,   337,   338,   339,
     341,   340,   342,   342,   343,   343,   343,   344,   345,   347,
     346,   349,   348,   350,   350,   351,   351,   351,   351,   351,
     351,   352,   353,   354,   356,   355,   357,   357,   358,   358,
     360,   359,   362,   361,   363,   363,   363,   364,   364,   366,
     365,   368,   367,   370,   369,   371,   371,   372,   372,   372,
     372,   372,   372,   373,   374,   375,   376,   377,   378,   380,
     379,   381,   381,   382,   382,   384,   383,   386,   385,   387,
     387,   388,   388,   388,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   388,   390,
     389,   392,   391,   394,   393,   396,   395,   398,   397,   400,
     399,   401,   401,   401,   401,   402,   403,   405,   404,   406,
     406,   407,   407,   409,   408,   410,   410,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   413,   412,   415,   414,   416,   416,   417,   417,
     419,   418,   421,   420,   422,   422,   423,   423,   424,   424,
     424,   424,   424,   424,   424,   424,   424,   424,   425,   426,
     427,   429,   428,   431,   430,   433,   432,   434,   436,   435,
     437,   439,   438,   440,   440,   441,   441,   443,   442,   445,
     444,   446,   446,   447,   447,   448,   448,   448,   448,   448,
     448,   448,   448,   448,   449,   451,   450,   452,   453,   454,
     455,   457,   456,   458,   458,   459,   459,   461,   460,   463,
     462,   464,   464,   465,   465,   465,   465,   465,   465,   465,
     467,   466,   469,   468,   471,   470,   473,   472,   474,   474,
     475,   475,   477,   476,   479,   478,   480,   480,   481,   481,
     481,   481,   481,   481,   481,   481,   481,   481,   481,   483,
     482,   484,   486,   485,   487,   488,   490,   489,   491,   491,
     492,   492,   494,   493,   496,   495,   497,   497,   498,   498,
     499,   499,   499,   499,   499,   499,   499,   499,   499,   499,
     499,   501,   500,   503,   502,   505,   504,   507,   506,   509,
     508,   511,   510,   513,   512,   515,   514,   516,   516,   518,
     517,   520,   519,   521,   521,   523,   522,   524,   524,   525,
     525,   526,   526,   526,   526,   526,   526,   526,   527,   529,
     528,   530,   532,   531,   533,   533,   534,   534,   534,   534,
     534,   534,   534,   534,   534,   536,   535,   537,   537,   537,
     538,   540,   539,   541,   542,   543,   545,   544,   546,   546,
     547,   547,   547,   547,   547,   549,   548,   551,   550,   553,
     552,   554,   554,   555,   555,   555,   555,   555,   555,   556,
     558,   557,   559,   561,   560,   563,   562,   565,   564,   566,
     566,   567,   567,   567,   567,   567,   567,   567,   567,   567,
     567,   567,   567,   567,   567,   567,   567,   567,   567,   568,
     570,   569,   572,   571,   573,   575,   574,   576,   577,   579,
     578,   580,   580,   582,   581,   583,   584,   586,   585,   588,
     587,   590,   589,   592,   591,   594,   593,   596,   595,   597,
     597,   598,   598,   600,   599,   601,   603,   602,   604,   604,
     606,   605,   607,   607,   608,   608,   608,   608,   608,   608,
     608,   609,   611,   610,   613,   612,   614,   614,   616,   615,
     617,   617,   618,   618,   618,   618,   618,   620,   619,   621,
     622,   623,   625,   624
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
       1,     3,     1,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     4,     0,     4,     3,     3,
       3,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     3,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     0,
       6,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     4,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     1,     0,
       4,     0,     6,     1,     3,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       3,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     0,     6,     3,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4
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
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"consistency\"",
  "\"serial-consistency\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"decline-probation-period\"",
  "\"server-tag\"", "\"statistic-default-sample-count\"",
  "\"statistic-default-sample-age\"", "\"ddns-send-updates\"",
  "\"ddns-override-no-update\"", "\"ddns-override-client-update\"",
  "\"ddns-replace-client-name\"", "\"ddns-generated-prefix\"",
  "\"ddns-qualifying-suffix\"", "\"ddns-update-on-renew\"",
  "\"ddns-use-conflict-resolution\"", "\"store-extended-info\"",
  "\"subnet6\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"shared-networks\"", "\"mac-sources\"", "\"relay-supplied-options\"",
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
  "\"hostname-char-replacement\"", "\"loggers\"", "\"output_options\"",
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
  "syntax_map", "$@18", "global_objects", "global_object", "dhcp6_object",
  "$@19", "sub_dhcp6", "$@20", "global_params", "global_param",
  "data_directory", "$@21", "preferred_lifetime", "min_preferred_lifetime",
  "max_preferred_lifetime", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "hostname_char_set", "$@25", "hostname_char_replacement", "$@26",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "server_tag", "$@27",
  "interfaces_config", "$@28", "sub_interfaces6", "$@29",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@30", "re_detect", "lease_database", "$@31", "hosts_database", "$@32",
  "hosts_databases", "$@33", "database_list", "not_empty_database_list",
  "database", "$@34", "database_map_params", "database_map_param",
  "database_type", "$@35", "db_type", "user", "$@36", "password", "$@37",
  "host", "$@38", "port", "name", "$@39", "persist", "lfc_interval",
  "readonly", "connect_timeout", "reconnect_wait_time", "max_row_errors",
  "request_timeout", "tcp_keepalive", "tcp_nodelay", "contact_points",
  "$@40", "max_reconnect_tries", "keyspace", "$@41", "consistency", "$@42",
  "serial_consistency", "$@43", "sanity_checks", "$@44",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@45",
  "mac_sources", "$@46", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@47",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@48",
  "dhcp_multi_threading", "$@49", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@50", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@51",
  "sub_hooks_library", "$@52", "hooks_params", "hooks_param", "library",
  "$@53", "parameters", "$@54", "expired_leases_processing", "$@55",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@56",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@57",
  "sub_subnet6", "$@58", "subnet6_params", "subnet6_param", "subnet",
  "$@59", "interface", "$@60", "interface_id", "$@61", "client_class",
  "$@62", "require_client_classes", "$@63", "reservation_mode", "$@64",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@65",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@66", "shared_network_params", "shared_network_param",
  "option_def_list", "$@67", "sub_option_def_list", "$@68",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@69", "sub_option_def", "$@70",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@71",
  "option_def_record_types", "$@72", "space", "$@73", "option_def_space",
  "option_def_encapsulate", "$@74", "option_def_array", "option_data_list",
  "$@75", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@76", "sub_option_data", "$@77",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@78",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@79", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@80", "sub_pool6", "$@81",
  "pool_params", "pool_param", "pool_entry", "$@82", "user_context",
  "$@83", "comment", "$@84", "pd_pools_list", "$@85",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@86", "sub_pd_pool", "$@87", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@88", "pd_prefix_len", "excluded_prefix", "$@89",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@90",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@91", "sub_reservation", "$@92", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@93", "prefixes", "$@94", "duid", "$@95", "hw_address", "$@96",
  "hostname", "$@97", "flex_id_value", "$@98",
  "reservation_client_classes", "$@99", "relay", "$@100", "relay_map",
  "ip_address", "$@101", "client_classes", "$@102", "client_classes_list",
  "client_class_entry", "$@103", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@104", "only_if_required",
  "server_id", "$@105", "server_id_params", "server_id_param",
  "server_id_type", "$@106", "duid_type", "htype", "identifier", "$@107",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@108",
  "control_socket_params", "control_socket_param", "socket_type", "$@109",
  "socket_name", "$@110", "dhcp_queue_control", "$@111",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@112", "capacity", "arbitrary_map_entry", "$@113",
  "dhcp_ddns", "$@114", "sub_dhcp_ddns", "$@115", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@116",
  "server_ip", "$@117", "server_port", "sender_ip", "$@118", "sender_port",
  "max_queue_size", "ncr_protocol", "$@119", "ncr_protocol_value",
  "ncr_format", "$@120", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@121",
  "dep_generated_prefix", "$@122", "dep_hostname_char_set", "$@123",
  "dep_hostname_char_replacement", "$@124", "config_control", "$@125",
  "sub_config_control", "$@126", "config_control_params",
  "config_control_param", "config_databases", "$@127",
  "config_fetch_wait_time", "loggers", "$@128", "loggers_entries",
  "logger_entry", "$@129", "logger_params", "logger_param", "debuglevel",
  "severity", "$@130", "output_options_list", "$@131",
  "output_options_list_content", "output_entry", "$@132",
  "output_params_list", "output_params", "output", "$@133", "flush",
  "maxsize", "maxver", "pattern", "$@134", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   285,   285,   285,   286,   286,   287,   287,   288,   288,
     289,   289,   290,   290,   291,   291,   292,   292,   293,   293,
     294,   294,   295,   295,   296,   296,   297,   297,   298,   298,
     306,   307,   308,   309,   310,   311,   312,   315,   320,   320,
     331,   334,   335,   338,   342,   349,   349,   356,   357,   360,
     364,   371,   371,   378,   379,   382,   386,   397,   406,   406,
     421,   422,   426,   429,   429,   446,   446,   455,   456,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,   513,   514,   515,   518,   518,   526,   531,   536,   541,
     546,   551,   556,   561,   566,   571,   576,   581,   586,   591,
     596,   601,   601,   609,   612,   615,   618,   621,   627,   627,
     635,   635,   643,   649,   655,   655,   663,   663,   671,   676,
     681,   686,   686,   694,   694,   705,   705,   714,   715,   718,
     719,   720,   721,   722,   725,   725,   735,   740,   740,   752,
     752,   764,   764,   774,   775,   778,   779,   782,   782,   792,
     793,   796,   797,   798,   799,   800,   801,   802,   803,   804,
     805,   806,   807,   808,   809,   810,   811,   812,   813,   814,
     815,   816,   819,   819,   826,   827,   828,   829,   832,   832,
     840,   840,   848,   848,   856,   861,   861,   869,   874,   879,
     884,   889,   894,   899,   904,   909,   914,   914,   922,   927,
     927,   935,   935,   943,   943,   951,   951,   961,   962,   964,
     966,   966,   984,   984,   994,   995,   998,   999,  1002,  1007,
    1012,  1012,  1022,  1023,  1026,  1027,  1028,  1031,  1036,  1043,
    1043,  1055,  1055,  1067,  1068,  1071,  1072,  1073,  1074,  1075,
    1076,  1079,  1084,  1089,  1094,  1094,  1104,  1105,  1108,  1109,
    1112,  1112,  1122,  1122,  1132,  1133,  1134,  1137,  1138,  1141,
    1141,  1149,  1149,  1157,  1157,  1168,  1169,  1172,  1173,  1174,
    1175,  1176,  1177,  1180,  1185,  1190,  1195,  1200,  1205,  1213,
    1213,  1226,  1227,  1230,  1231,  1238,  1238,  1264,  1264,  1275,
    1276,  1280,  1281,  1282,  1283,  1284,  1285,  1286,  1287,  1288,
    1289,  1290,  1291,  1292,  1293,  1294,  1295,  1296,  1297,  1298,
    1299,  1300,  1301,  1302,  1303,  1304,  1305,  1306,  1307,  1308,
    1309,  1310,  1311,  1312,  1313,  1314,  1315,  1316,  1317,  1320,
    1320,  1328,  1328,  1336,  1336,  1344,  1344,  1352,  1352,  1362,
    1362,  1369,  1370,  1371,  1372,  1375,  1380,  1387,  1387,  1398,
    1399,  1403,  1404,  1407,  1407,  1415,  1416,  1419,  1420,  1421,
    1422,  1423,  1424,  1425,  1426,  1427,  1428,  1429,  1430,  1431,
    1432,  1433,  1434,  1435,  1436,  1437,  1438,  1439,  1440,  1441,
    1442,  1443,  1444,  1445,  1446,  1447,  1448,  1449,  1450,  1451,
    1452,  1453,  1460,  1460,  1473,  1473,  1482,  1483,  1486,  1487,
    1492,  1492,  1507,  1507,  1521,  1522,  1525,  1526,  1529,  1530,
    1531,  1532,  1533,  1534,  1535,  1536,  1537,  1538,  1541,  1543,
    1548,  1550,  1550,  1558,  1558,  1566,  1566,  1574,  1576,  1576,
    1584,  1593,  1593,  1605,  1606,  1611,  1612,  1617,  1617,  1629,
    1629,  1641,  1642,  1647,  1648,  1653,  1654,  1655,  1656,  1657,
    1658,  1659,  1660,  1661,  1664,  1666,  1666,  1674,  1676,  1678,
    1683,  1691,  1691,  1703,  1704,  1707,  1708,  1711,  1711,  1721,
    1721,  1731,  1732,  1735,  1736,  1737,  1738,  1739,  1740,  1741,
    1744,  1744,  1752,  1752,  1777,  1777,  1807,  1807,  1819,  1820,
    1823,  1824,  1827,  1827,  1839,  1839,  1851,  1852,  1855,  1856,
    1857,  1858,  1859,  1860,  1861,  1862,  1863,  1864,  1865,  1868,
    1868,  1876,  1881,  1881,  1889,  1894,  1902,  1902,  1912,  1913,
    1916,  1917,  1920,  1920,  1929,  1929,  1938,  1939,  1942,  1943,
    1947,  1948,  1949,  1950,  1951,  1952,  1953,  1954,  1955,  1956,
    1957,  1960,  1960,  1970,  1970,  1980,  1980,  1988,  1988,  1996,
    1996,  2004,  2004,  2012,  2012,  2025,  2025,  2035,  2036,  2039,
    2039,  2050,  2050,  2060,  2061,  2064,  2064,  2074,  2075,  2078,
    2079,  2082,  2083,  2084,  2085,  2086,  2087,  2088,  2091,  2093,
    2093,  2101,  2109,  2109,  2121,  2122,  2125,  2126,  2127,  2128,
    2129,  2130,  2131,  2132,  2133,  2136,  2136,  2143,  2144,  2145,
    2148,  2153,  2153,  2161,  2166,  2173,  2180,  2180,  2190,  2191,
    2194,  2195,  2196,  2197,  2198,  2201,  2201,  2209,  2209,  2220,
    2220,  2232,  2233,  2236,  2237,  2238,  2239,  2240,  2241,  2244,
    2249,  2249,  2257,  2262,  2262,  2271,  2271,  2283,  2283,  2293,
    2294,  2297,  2298,  2299,  2300,  2301,  2302,  2303,  2304,  2305,
    2306,  2307,  2308,  2309,  2310,  2311,  2312,  2313,  2314,  2317,
    2322,  2322,  2330,  2330,  2338,  2343,  2343,  2351,  2356,  2361,
    2361,  2369,  2370,  2373,  2373,  2382,  2388,  2394,  2394,  2402,
    2402,  2411,  2411,  2420,  2420,  2431,  2431,  2442,  2442,  2452,
    2453,  2457,  2458,  2461,  2461,  2471,  2478,  2478,  2490,  2491,
    2495,  2495,  2503,  2504,  2507,  2508,  2509,  2510,  2511,  2512,
    2513,  2516,  2521,  2521,  2529,  2529,  2539,  2540,  2543,  2543,
    2551,  2552,  2555,  2556,  2557,  2558,  2559,  2562,  2562,  2570,
    2575,  2580,  2585,  2585
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
#line 5619 "dhcp6_parser.cc"

#line 2593 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
