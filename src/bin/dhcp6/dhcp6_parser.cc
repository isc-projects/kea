// A Bison parser, made by GNU Bison 3.7.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
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
    YYUSE (yyoutput);
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
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 905 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 343 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 45: // $@16: %empty
#line 351 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 925 "dhcp6_parser.cc"
    break;

  case 46: // list_generic: "[" $@16 list_content "]"
#line 354 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 933 "dhcp6_parser.cc"
    break;

  case 49: // not_empty_list: value
#line 362 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 942 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list "," value
#line 366 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp6_parser.cc"
    break;

  case 51: // $@17: %empty
#line 373 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 959 "dhcp6_parser.cc"
    break;

  case 52: // list_strings: "[" $@17 list_strings_content "]"
#line 375 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 968 "dhcp6_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 384 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 977 "dhcp6_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 388 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 986 "dhcp6_parser.cc"
    break;

  case 57: // unknown_map_entry: "constant string" ":"
#line 399 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 997 "dhcp6_parser.cc"
    break;

  case 58: // $@18: %empty
#line 408 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1008 "dhcp6_parser.cc"
    break;

  case 59: // syntax_map: "{" $@18 global_object "}"
#line 413 "dhcp6_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1021 "dhcp6_parser.cc"
    break;

  case 60: // $@19: %empty
#line 423 "dhcp6_parser.yy"
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
#line 1036 "dhcp6_parser.cc"
    break;

  case 61: // global_object: "Dhcp6" $@19 ":" "{" global_params "}"
#line 432 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp6_parser.cc"
    break;

  case 62: // $@20: %empty
#line 440 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp6_parser.cc"
    break;

  case 63: // sub_dhcp6: "{" $@20 global_params "}"
#line 444 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1065 "dhcp6_parser.cc"
    break;

  case 121: // $@21: %empty
#line 512 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1074 "dhcp6_parser.cc"
    break;

  case 122: // data_directory: "data-directory" $@21 ":" "constant string"
#line 515 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1084 "dhcp6_parser.cc"
    break;

  case 123: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 521 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1094 "dhcp6_parser.cc"
    break;

  case 124: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 527 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 125: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 533 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1114 "dhcp6_parser.cc"
    break;

  case 126: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 539 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 127: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 545 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1134 "dhcp6_parser.cc"
    break;

  case 128: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 551 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1144 "dhcp6_parser.cc"
    break;

  case 129: // renew_timer: "renew-timer" ":" "integer"
#line 557 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1154 "dhcp6_parser.cc"
    break;

  case 130: // rebind_timer: "rebind-timer" ":" "integer"
#line 563 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1164 "dhcp6_parser.cc"
    break;

  case 131: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 569 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1174 "dhcp6_parser.cc"
    break;

  case 132: // t1_percent: "t1-percent" ":" "floating point"
#line 575 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1184 "dhcp6_parser.cc"
    break;

  case 133: // t2_percent: "t2-percent" ":" "floating point"
#line 581 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1194 "dhcp6_parser.cc"
    break;

  case 134: // cache_threshold: "cache-threshold" ":" "floating point"
#line 587 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1204 "dhcp6_parser.cc"
    break;

  case 135: // cache_max: "cache-max" ":" "integer"
#line 593 "dhcp6_parser.yy"
                                   {
    ctx.unique("cache-max", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max", cm);
}
#line 1214 "dhcp6_parser.cc"
    break;

  case 136: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 599 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 137: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 605 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1234 "dhcp6_parser.cc"
    break;

  case 138: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 611 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1244 "dhcp6_parser.cc"
    break;

  case 139: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 617 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1254 "dhcp6_parser.cc"
    break;

  case 140: // $@22: %empty
#line 623 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 141: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 626 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 142: // ddns_replace_client_name_value: "when-present"
#line 632 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1280 "dhcp6_parser.cc"
    break;

  case 143: // ddns_replace_client_name_value: "never"
#line 635 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1288 "dhcp6_parser.cc"
    break;

  case 144: // ddns_replace_client_name_value: "always"
#line 638 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1296 "dhcp6_parser.cc"
    break;

  case 145: // ddns_replace_client_name_value: "when-not-present"
#line 641 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1304 "dhcp6_parser.cc"
    break;

  case 146: // ddns_replace_client_name_value: "boolean"
#line 644 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1313 "dhcp6_parser.cc"
    break;

  case 147: // $@23: %empty
#line 650 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp6_parser.cc"
    break;

  case 148: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 653 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1332 "dhcp6_parser.cc"
    break;

  case 149: // $@24: %empty
#line 659 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp6_parser.cc"
    break;

  case 150: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 662 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc"
    break;

  case 151: // $@25: %empty
#line 668 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1360 "dhcp6_parser.cc"
    break;

  case 152: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 671 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1370 "dhcp6_parser.cc"
    break;

  case 153: // $@26: %empty
#line 677 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1379 "dhcp6_parser.cc"
    break;

  case 154: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 680 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 155: // store_extended_info: "store-extended-info" ":" "boolean"
#line 686 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 156: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 692 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1409 "dhcp6_parser.cc"
    break;

  case 157: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 698 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 158: // $@27: %empty
#line 704 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1428 "dhcp6_parser.cc"
    break;

  case 159: // server_tag: "server-tag" $@27 ":" "constant string"
#line 707 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1438 "dhcp6_parser.cc"
    break;

  case 160: // $@28: %empty
#line 713 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1450 "dhcp6_parser.cc"
    break;

  case 161: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 719 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 162: // $@29: %empty
#line 725 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 163: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 729 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1479 "dhcp6_parser.cc"
    break;

  case 171: // $@30: %empty
#line 745 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1491 "dhcp6_parser.cc"
    break;

  case 172: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 751 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1500 "dhcp6_parser.cc"
    break;

  case 173: // re_detect: "re-detect" ":" "boolean"
#line 756 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1510 "dhcp6_parser.cc"
    break;

  case 174: // $@31: %empty
#line 762 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1522 "dhcp6_parser.cc"
    break;

  case 175: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 768 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1533 "dhcp6_parser.cc"
    break;

  case 176: // $@32: %empty
#line 775 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1545 "dhcp6_parser.cc"
    break;

  case 177: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 781 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1556 "dhcp6_parser.cc"
    break;

  case 178: // $@33: %empty
#line 788 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1568 "dhcp6_parser.cc"
    break;

  case 179: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 794 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1577 "dhcp6_parser.cc"
    break;

  case 184: // $@34: %empty
#line 807 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1587 "dhcp6_parser.cc"
    break;

  case 185: // database: "{" $@34 database_map_params "}"
#line 811 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1597 "dhcp6_parser.cc"
    break;

  case 209: // $@35: %empty
#line 844 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1606 "dhcp6_parser.cc"
    break;

  case 210: // database_type: "type" $@35 ":" db_type
#line 847 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1615 "dhcp6_parser.cc"
    break;

  case 211: // db_type: "memfile"
#line 852 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1621 "dhcp6_parser.cc"
    break;

  case 212: // db_type: "mysql"
#line 853 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1627 "dhcp6_parser.cc"
    break;

  case 213: // db_type: "postgresql"
#line 854 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1633 "dhcp6_parser.cc"
    break;

  case 214: // db_type: "cql"
#line 855 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1639 "dhcp6_parser.cc"
    break;

  case 215: // $@36: %empty
#line 858 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1648 "dhcp6_parser.cc"
    break;

  case 216: // user: "user" $@36 ":" "constant string"
#line 861 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1658 "dhcp6_parser.cc"
    break;

  case 217: // $@37: %empty
#line 867 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1667 "dhcp6_parser.cc"
    break;

  case 218: // password: "password" $@37 ":" "constant string"
#line 870 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1677 "dhcp6_parser.cc"
    break;

  case 219: // $@38: %empty
#line 876 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1686 "dhcp6_parser.cc"
    break;

  case 220: // host: "host" $@38 ":" "constant string"
#line 879 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1696 "dhcp6_parser.cc"
    break;

  case 221: // port: "port" ":" "integer"
#line 885 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1706 "dhcp6_parser.cc"
    break;

  case 222: // $@39: %empty
#line 891 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1715 "dhcp6_parser.cc"
    break;

  case 223: // name: "name" $@39 ":" "constant string"
#line 894 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1725 "dhcp6_parser.cc"
    break;

  case 224: // persist: "persist" ":" "boolean"
#line 900 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1735 "dhcp6_parser.cc"
    break;

  case 225: // lfc_interval: "lfc-interval" ":" "integer"
#line 906 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1745 "dhcp6_parser.cc"
    break;

  case 226: // readonly: "readonly" ":" "boolean"
#line 912 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 227: // connect_timeout: "connect-timeout" ":" "integer"
#line 918 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1765 "dhcp6_parser.cc"
    break;

  case 228: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 924 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1775 "dhcp6_parser.cc"
    break;

  case 229: // max_row_errors: "max-row-errors" ":" "integer"
#line 930 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1785 "dhcp6_parser.cc"
    break;

  case 230: // request_timeout: "request-timeout" ":" "integer"
#line 936 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1795 "dhcp6_parser.cc"
    break;

  case 231: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 942 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1805 "dhcp6_parser.cc"
    break;

  case 232: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 948 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1815 "dhcp6_parser.cc"
    break;

  case 233: // $@40: %empty
#line 954 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1824 "dhcp6_parser.cc"
    break;

  case 234: // contact_points: "contact-points" $@40 ":" "constant string"
#line 957 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1834 "dhcp6_parser.cc"
    break;

  case 235: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 963 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 236: // $@41: %empty
#line 969 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1853 "dhcp6_parser.cc"
    break;

  case 237: // keyspace: "keyspace" $@41 ":" "constant string"
#line 972 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1863 "dhcp6_parser.cc"
    break;

  case 238: // $@42: %empty
#line 978 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1872 "dhcp6_parser.cc"
    break;

  case 239: // consistency: "consistency" $@42 ":" "constant string"
#line 981 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1882 "dhcp6_parser.cc"
    break;

  case 240: // $@43: %empty
#line 987 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1891 "dhcp6_parser.cc"
    break;

  case 241: // serial_consistency: "serial-consistency" $@43 ":" "constant string"
#line 990 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1901 "dhcp6_parser.cc"
    break;

  case 242: // $@44: %empty
#line 996 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1913 "dhcp6_parser.cc"
    break;

  case 243: // sanity_checks: "sanity-checks" $@44 ":" "{" sanity_checks_params "}"
#line 1002 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1922 "dhcp6_parser.cc"
    break;

  case 247: // $@45: %empty
#line 1012 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1931 "dhcp6_parser.cc"
    break;

  case 248: // lease_checks: "lease-checks" $@45 ":" "constant string"
#line 1015 "dhcp6_parser.yy"
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
#line 1951 "dhcp6_parser.cc"
    break;

  case 249: // $@46: %empty
#line 1031 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1963 "dhcp6_parser.cc"
    break;

  case 250: // mac_sources: "mac-sources" $@46 ":" "[" mac_sources_list "]"
#line 1037 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 255: // duid_id: "duid"
#line 1050 "dhcp6_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1981 "dhcp6_parser.cc"
    break;

  case 256: // string_id: "constant string"
#line 1055 "dhcp6_parser.yy"
                   {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1990 "dhcp6_parser.cc"
    break;

  case 257: // $@47: %empty
#line 1060 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2002 "dhcp6_parser.cc"
    break;

  case 258: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1066 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2011 "dhcp6_parser.cc"
    break;

  case 264: // hw_address_id: "hw-address"
#line 1080 "dhcp6_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2020 "dhcp6_parser.cc"
    break;

  case 265: // flex_id: "flex-id"
#line 1085 "dhcp6_parser.yy"
                  {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2029 "dhcp6_parser.cc"
    break;

  case 266: // $@48: %empty
#line 1092 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2041 "dhcp6_parser.cc"
    break;

  case 267: // relay_supplied_options: "relay-supplied-options" $@48 ":" "[" list_content "]"
#line 1098 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2050 "dhcp6_parser.cc"
    break;

  case 268: // $@49: %empty
#line 1105 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2062 "dhcp6_parser.cc"
    break;

  case 269: // dhcp_multi_threading: "multi-threading" $@49 ":" "{" multi_threading_params "}"
#line 1111 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2073 "dhcp6_parser.cc"
    break;

  case 278: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1130 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 279: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1136 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 280: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1142 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2103 "dhcp6_parser.cc"
    break;

  case 281: // $@50: %empty
#line 1148 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2115 "dhcp6_parser.cc"
    break;

  case 282: // hooks_libraries: "hooks-libraries" $@50 ":" "[" hooks_libraries_list "]"
#line 1154 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2124 "dhcp6_parser.cc"
    break;

  case 287: // $@51: %empty
#line 1167 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2134 "dhcp6_parser.cc"
    break;

  case 288: // hooks_library: "{" $@51 hooks_params "}"
#line 1171 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2144 "dhcp6_parser.cc"
    break;

  case 289: // $@52: %empty
#line 1177 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2154 "dhcp6_parser.cc"
    break;

  case 290: // sub_hooks_library: "{" $@52 hooks_params "}"
#line 1181 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 296: // $@53: %empty
#line 1196 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 297: // library: "library" $@53 ":" "constant string"
#line 1199 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2183 "dhcp6_parser.cc"
    break;

  case 298: // $@54: %empty
#line 1205 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2192 "dhcp6_parser.cc"
    break;

  case 299: // parameters: "parameters" $@54 ":" map_value
#line 1208 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2201 "dhcp6_parser.cc"
    break;

  case 300: // $@55: %empty
#line 1214 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2213 "dhcp6_parser.cc"
    break;

  case 301: // expired_leases_processing: "expired-leases-processing" $@55 ":" "{" expired_leases_params "}"
#line 1220 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2223 "dhcp6_parser.cc"
    break;

  case 310: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1238 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2233 "dhcp6_parser.cc"
    break;

  case 311: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1244 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2243 "dhcp6_parser.cc"
    break;

  case 312: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1250 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2253 "dhcp6_parser.cc"
    break;

  case 313: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1256 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2263 "dhcp6_parser.cc"
    break;

  case 314: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1262 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2273 "dhcp6_parser.cc"
    break;

  case 315: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1268 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2283 "dhcp6_parser.cc"
    break;

  case 316: // $@56: %empty
#line 1277 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2295 "dhcp6_parser.cc"
    break;

  case 317: // subnet6_list: "subnet6" $@56 ":" "[" subnet6_list_content "]"
#line 1283 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2304 "dhcp6_parser.cc"
    break;

  case 322: // $@57: %empty
#line 1303 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2314 "dhcp6_parser.cc"
    break;

  case 323: // subnet6: "{" $@57 subnet6_params "}"
#line 1307 "dhcp6_parser.yy"
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
#line 2340 "dhcp6_parser.cc"
    break;

  case 324: // $@58: %empty
#line 1329 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2350 "dhcp6_parser.cc"
    break;

  case 325: // sub_subnet6: "{" $@58 subnet6_params "}"
#line 1333 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2360 "dhcp6_parser.cc"
    break;

  case 366: // $@59: %empty
#line 1385 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2369 "dhcp6_parser.cc"
    break;

  case 367: // subnet: "subnet" $@59 ":" "constant string"
#line 1388 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2379 "dhcp6_parser.cc"
    break;

  case 368: // $@60: %empty
#line 1394 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp6_parser.cc"
    break;

  case 369: // interface: "interface" $@60 ":" "constant string"
#line 1397 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2398 "dhcp6_parser.cc"
    break;

  case 370: // $@61: %empty
#line 1403 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2407 "dhcp6_parser.cc"
    break;

  case 371: // interface_id: "interface-id" $@61 ":" "constant string"
#line 1406 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2417 "dhcp6_parser.cc"
    break;

  case 372: // $@62: %empty
#line 1412 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2426 "dhcp6_parser.cc"
    break;

  case 373: // client_class: "client-class" $@62 ":" "constant string"
#line 1415 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2436 "dhcp6_parser.cc"
    break;

  case 374: // $@63: %empty
#line 1421 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 375: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1427 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2457 "dhcp6_parser.cc"
    break;

  case 376: // $@64: %empty
#line 1432 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2466 "dhcp6_parser.cc"
    break;

  case 377: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1435 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2475 "dhcp6_parser.cc"
    break;

  case 378: // hr_mode: "disabled"
#line 1440 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2481 "dhcp6_parser.cc"
    break;

  case 379: // hr_mode: "out-of-pool"
#line 1441 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2487 "dhcp6_parser.cc"
    break;

  case 380: // hr_mode: "global"
#line 1442 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2493 "dhcp6_parser.cc"
    break;

  case 381: // hr_mode: "all"
#line 1443 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2499 "dhcp6_parser.cc"
    break;

  case 382: // id: "id" ":" "integer"
#line 1446 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2509 "dhcp6_parser.cc"
    break;

  case 383: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1452 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2519 "dhcp6_parser.cc"
    break;

  case 384: // $@65: %empty
#line 1460 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2531 "dhcp6_parser.cc"
    break;

  case 385: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1466 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2540 "dhcp6_parser.cc"
    break;

  case 390: // $@66: %empty
#line 1481 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2550 "dhcp6_parser.cc"
    break;

  case 391: // shared_network: "{" $@66 shared_network_params "}"
#line 1485 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2558 "dhcp6_parser.cc"
    break;

  case 429: // $@67: %empty
#line 1534 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2570 "dhcp6_parser.cc"
    break;

  case 430: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1540 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2579 "dhcp6_parser.cc"
    break;

  case 431: // $@68: %empty
#line 1548 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2588 "dhcp6_parser.cc"
    break;

  case 432: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1551 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2596 "dhcp6_parser.cc"
    break;

  case 437: // $@69: %empty
#line 1567 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2606 "dhcp6_parser.cc"
    break;

  case 438: // option_def_entry: "{" $@69 option_def_params "}"
#line 1571 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2618 "dhcp6_parser.cc"
    break;

  case 439: // $@70: %empty
#line 1582 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2628 "dhcp6_parser.cc"
    break;

  case 440: // sub_option_def: "{" $@70 option_def_params "}"
#line 1586 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2640 "dhcp6_parser.cc"
    break;

  case 456: // code: "code" ":" "integer"
#line 1618 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2650 "dhcp6_parser.cc"
    break;

  case 458: // $@71: %empty
#line 1626 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2659 "dhcp6_parser.cc"
    break;

  case 459: // option_def_type: "type" $@71 ":" "constant string"
#line 1629 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2669 "dhcp6_parser.cc"
    break;

  case 460: // $@72: %empty
#line 1635 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2678 "dhcp6_parser.cc"
    break;

  case 461: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1638 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2688 "dhcp6_parser.cc"
    break;

  case 462: // $@73: %empty
#line 1644 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2697 "dhcp6_parser.cc"
    break;

  case 463: // space: "space" $@73 ":" "constant string"
#line 1647 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2707 "dhcp6_parser.cc"
    break;

  case 465: // $@74: %empty
#line 1655 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2716 "dhcp6_parser.cc"
    break;

  case 466: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1658 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2726 "dhcp6_parser.cc"
    break;

  case 467: // option_def_array: "array" ":" "boolean"
#line 1664 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2736 "dhcp6_parser.cc"
    break;

  case 468: // $@75: %empty
#line 1674 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2748 "dhcp6_parser.cc"
    break;

  case 469: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1680 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2757 "dhcp6_parser.cc"
    break;

  case 474: // $@76: %empty
#line 1699 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2767 "dhcp6_parser.cc"
    break;

  case 475: // option_data_entry: "{" $@76 option_data_params "}"
#line 1703 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 476: // $@77: %empty
#line 1711 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 477: // sub_option_data: "{" $@77 option_data_params "}"
#line 1715 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2795 "dhcp6_parser.cc"
    break;

  case 492: // $@78: %empty
#line 1748 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 493: // option_data_data: "data" $@78 ":" "constant string"
#line 1751 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2814 "dhcp6_parser.cc"
    break;

  case 496: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1761 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2824 "dhcp6_parser.cc"
    break;

  case 497: // option_data_always_send: "always-send" ":" "boolean"
#line 1767 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2834 "dhcp6_parser.cc"
    break;

  case 498: // $@79: %empty
#line 1776 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2846 "dhcp6_parser.cc"
    break;

  case 499: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1782 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2855 "dhcp6_parser.cc"
    break;

  case 504: // $@80: %empty
#line 1797 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2865 "dhcp6_parser.cc"
    break;

  case 505: // pool_list_entry: "{" $@80 pool_params "}"
#line 1801 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 506: // $@81: %empty
#line 1807 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 507: // sub_pool6: "{" $@81 pool_params "}"
#line 1811 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2895 "dhcp6_parser.cc"
    break;

  case 517: // $@82: %empty
#line 1830 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2904 "dhcp6_parser.cc"
    break;

  case 518: // pool_entry: "pool" $@82 ":" "constant string"
#line 1833 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 519: // $@83: %empty
#line 1839 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2922 "dhcp6_parser.cc"
    break;

  case 520: // user_context: "user-context" $@83 ":" map_value
#line 1841 "dhcp6_parser.yy"
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
#line 2949 "dhcp6_parser.cc"
    break;

  case 521: // $@84: %empty
#line 1864 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2957 "dhcp6_parser.cc"
    break;

  case 522: // comment: "comment" $@84 ":" "constant string"
#line 1866 "dhcp6_parser.yy"
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
#line 2986 "dhcp6_parser.cc"
    break;

  case 523: // $@85: %empty
#line 1894 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2998 "dhcp6_parser.cc"
    break;

  case 524: // pd_pools_list: "pd-pools" $@85 ":" "[" pd_pools_list_content "]"
#line 1900 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3007 "dhcp6_parser.cc"
    break;

  case 529: // $@86: %empty
#line 1915 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 530: // pd_pool_entry: "{" $@86 pd_pool_params "}"
#line 1919 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3029 "dhcp6_parser.cc"
    break;

  case 531: // $@87: %empty
#line 1927 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3039 "dhcp6_parser.cc"
    break;

  case 532: // sub_pd_pool: "{" $@87 pd_pool_params "}"
#line 1931 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3051 "dhcp6_parser.cc"
    break;

  case 546: // $@88: %empty
#line 1956 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3060 "dhcp6_parser.cc"
    break;

  case 547: // pd_prefix: "prefix" $@88 ":" "constant string"
#line 1959 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3070 "dhcp6_parser.cc"
    break;

  case 548: // pd_prefix_len: "prefix-len" ":" "integer"
#line 1965 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3080 "dhcp6_parser.cc"
    break;

  case 549: // $@89: %empty
#line 1971 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3089 "dhcp6_parser.cc"
    break;

  case 550: // excluded_prefix: "excluded-prefix" $@89 ":" "constant string"
#line 1974 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3099 "dhcp6_parser.cc"
    break;

  case 551: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 1980 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3109 "dhcp6_parser.cc"
    break;

  case 552: // pd_delegated_len: "delegated-len" ":" "integer"
#line 1986 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3119 "dhcp6_parser.cc"
    break;

  case 553: // $@90: %empty
#line 1995 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3131 "dhcp6_parser.cc"
    break;

  case 554: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2001 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3140 "dhcp6_parser.cc"
    break;

  case 559: // $@91: %empty
#line 2014 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3150 "dhcp6_parser.cc"
    break;

  case 560: // reservation: "{" $@91 reservation_params "}"
#line 2018 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3159 "dhcp6_parser.cc"
    break;

  case 561: // $@92: %empty
#line 2023 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3169 "dhcp6_parser.cc"
    break;

  case 562: // sub_reservation: "{" $@92 reservation_params "}"
#line 2027 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3178 "dhcp6_parser.cc"
    break;

  case 578: // $@93: %empty
#line 2054 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3190 "dhcp6_parser.cc"
    break;

  case 579: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2060 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3199 "dhcp6_parser.cc"
    break;

  case 580: // $@94: %empty
#line 2065 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 581: // prefixes: "prefixes" $@94 ":" list_strings
#line 2071 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3220 "dhcp6_parser.cc"
    break;

  case 582: // $@95: %empty
#line 2076 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3229 "dhcp6_parser.cc"
    break;

  case 583: // duid: "duid" $@95 ":" "constant string"
#line 2079 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3239 "dhcp6_parser.cc"
    break;

  case 584: // $@96: %empty
#line 2085 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3248 "dhcp6_parser.cc"
    break;

  case 585: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2088 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3258 "dhcp6_parser.cc"
    break;

  case 586: // $@97: %empty
#line 2094 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3267 "dhcp6_parser.cc"
    break;

  case 587: // hostname: "hostname" $@97 ":" "constant string"
#line 2097 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3277 "dhcp6_parser.cc"
    break;

  case 588: // $@98: %empty
#line 2103 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3286 "dhcp6_parser.cc"
    break;

  case 589: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2106 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3296 "dhcp6_parser.cc"
    break;

  case 590: // $@99: %empty
#line 2112 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3308 "dhcp6_parser.cc"
    break;

  case 591: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2118 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3317 "dhcp6_parser.cc"
    break;

  case 592: // $@100: %empty
#line 2126 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3329 "dhcp6_parser.cc"
    break;

  case 593: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2132 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3338 "dhcp6_parser.cc"
    break;

  case 596: // $@101: %empty
#line 2141 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3347 "dhcp6_parser.cc"
    break;

  case 597: // ip_address: "ip-address" $@101 ":" "constant string"
#line 2144 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3357 "dhcp6_parser.cc"
    break;

  case 598: // $@102: %empty
#line 2153 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3369 "dhcp6_parser.cc"
    break;

  case 599: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2159 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3378 "dhcp6_parser.cc"
    break;

  case 602: // $@103: %empty
#line 2168 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3388 "dhcp6_parser.cc"
    break;

  case 603: // client_class_entry: "{" $@103 client_class_params "}"
#line 2172 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 616: // $@104: %empty
#line 2197 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3407 "dhcp6_parser.cc"
    break;

  case 617: // client_class_test: "test" $@104 ":" "constant string"
#line 2200 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3417 "dhcp6_parser.cc"
    break;

  case 618: // only_if_required: "only-if-required" ":" "boolean"
#line 2206 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3427 "dhcp6_parser.cc"
    break;

  case 619: // $@105: %empty
#line 2215 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3439 "dhcp6_parser.cc"
    break;

  case 620: // server_id: "server-id" $@105 ":" "{" server_id_params "}"
#line 2221 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3450 "dhcp6_parser.cc"
    break;

  case 632: // $@106: %empty
#line 2243 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3459 "dhcp6_parser.cc"
    break;

  case 633: // server_id_type: "type" $@106 ":" duid_type
#line 2246 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3468 "dhcp6_parser.cc"
    break;

  case 634: // duid_type: "LLT"
#line 2251 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3474 "dhcp6_parser.cc"
    break;

  case 635: // duid_type: "EN"
#line 2252 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3480 "dhcp6_parser.cc"
    break;

  case 636: // duid_type: "LL"
#line 2253 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3486 "dhcp6_parser.cc"
    break;

  case 637: // htype: "htype" ":" "integer"
#line 2256 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3496 "dhcp6_parser.cc"
    break;

  case 638: // $@107: %empty
#line 2262 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3505 "dhcp6_parser.cc"
    break;

  case 639: // identifier: "identifier" $@107 ":" "constant string"
#line 2265 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3515 "dhcp6_parser.cc"
    break;

  case 640: // time: "time" ":" "integer"
#line 2271 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3525 "dhcp6_parser.cc"
    break;

  case 641: // enterprise_id: "enterprise-id" ":" "integer"
#line 2277 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3535 "dhcp6_parser.cc"
    break;

  case 642: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2285 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3545 "dhcp6_parser.cc"
    break;

  case 643: // $@108: %empty
#line 2293 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3557 "dhcp6_parser.cc"
    break;

  case 644: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2299 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3566 "dhcp6_parser.cc"
    break;

  case 652: // $@109: %empty
#line 2315 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3575 "dhcp6_parser.cc"
    break;

  case 653: // socket_type: "socket-type" $@109 ":" "constant string"
#line 2318 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3585 "dhcp6_parser.cc"
    break;

  case 654: // $@110: %empty
#line 2324 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3594 "dhcp6_parser.cc"
    break;

  case 655: // socket_name: "socket-name" $@110 ":" "constant string"
#line 2327 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3604 "dhcp6_parser.cc"
    break;

  case 656: // $@111: %empty
#line 2336 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 657: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2342 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3627 "dhcp6_parser.cc"
    break;

  case 666: // enable_queue: "enable-queue" ":" "boolean"
#line 2361 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3637 "dhcp6_parser.cc"
    break;

  case 667: // $@112: %empty
#line 2367 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3646 "dhcp6_parser.cc"
    break;

  case 668: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2370 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3656 "dhcp6_parser.cc"
    break;

  case 669: // capacity: "capacity" ":" "integer"
#line 2376 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3666 "dhcp6_parser.cc"
    break;

  case 670: // $@113: %empty
#line 2382 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3675 "dhcp6_parser.cc"
    break;

  case 671: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2385 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3684 "dhcp6_parser.cc"
    break;

  case 672: // $@114: %empty
#line 2392 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3696 "dhcp6_parser.cc"
    break;

  case 673: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2398 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3707 "dhcp6_parser.cc"
    break;

  case 674: // $@115: %empty
#line 2405 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3717 "dhcp6_parser.cc"
    break;

  case 675: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2409 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 696: // enable_updates: "enable-updates" ":" "boolean"
#line 2439 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 697: // $@116: %empty
#line 2446 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 698: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2449 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 699: // $@117: %empty
#line 2455 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3765 "dhcp6_parser.cc"
    break;

  case 700: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2458 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 701: // server_port: "server-port" ":" "integer"
#line 2464 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 702: // $@118: %empty
#line 2470 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3794 "dhcp6_parser.cc"
    break;

  case 703: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2473 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3804 "dhcp6_parser.cc"
    break;

  case 704: // sender_port: "sender-port" ":" "integer"
#line 2479 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 705: // max_queue_size: "max-queue-size" ":" "integer"
#line 2485 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 706: // $@119: %empty
#line 2491 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3833 "dhcp6_parser.cc"
    break;

  case 707: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2494 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3842 "dhcp6_parser.cc"
    break;

  case 708: // ncr_protocol_value: "UDP"
#line 2500 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3848 "dhcp6_parser.cc"
    break;

  case 709: // ncr_protocol_value: "TCP"
#line 2501 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3854 "dhcp6_parser.cc"
    break;

  case 710: // $@120: %empty
#line 2504 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 711: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2507 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 712: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2514 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 713: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2521 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3893 "dhcp6_parser.cc"
    break;

  case 714: // $@121: %empty
#line 2528 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 715: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2531 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3911 "dhcp6_parser.cc"
    break;

  case 716: // $@122: %empty
#line 2537 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3920 "dhcp6_parser.cc"
    break;

  case 717: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2540 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3930 "dhcp6_parser.cc"
    break;

  case 718: // $@123: %empty
#line 2547 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3939 "dhcp6_parser.cc"
    break;

  case 719: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2550 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3949 "dhcp6_parser.cc"
    break;

  case 720: // $@124: %empty
#line 2557 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3958 "dhcp6_parser.cc"
    break;

  case 721: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2560 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3968 "dhcp6_parser.cc"
    break;

  case 722: // $@125: %empty
#line 2569 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3980 "dhcp6_parser.cc"
    break;

  case 723: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2575 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3990 "dhcp6_parser.cc"
    break;

  case 724: // $@126: %empty
#line 2581 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 725: // sub_config_control: "{" $@126 config_control_params "}"
#line 2585 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4009 "dhcp6_parser.cc"
    break;

  case 730: // $@127: %empty
#line 2600 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4021 "dhcp6_parser.cc"
    break;

  case 731: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2606 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4030 "dhcp6_parser.cc"
    break;

  case 732: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2611 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4040 "dhcp6_parser.cc"
    break;

  case 733: // $@128: %empty
#line 2619 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4052 "dhcp6_parser.cc"
    break;

  case 734: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2625 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4061 "dhcp6_parser.cc"
    break;

  case 737: // $@129: %empty
#line 2637 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 738: // logger_entry: "{" $@129 logger_params "}"
#line 2641 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4079 "dhcp6_parser.cc"
    break;

  case 748: // debuglevel: "debuglevel" ":" "integer"
#line 2658 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4089 "dhcp6_parser.cc"
    break;

  case 749: // $@130: %empty
#line 2664 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4098 "dhcp6_parser.cc"
    break;

  case 750: // severity: "severity" $@130 ":" "constant string"
#line 2667 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4108 "dhcp6_parser.cc"
    break;

  case 751: // $@131: %empty
#line 2673 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4120 "dhcp6_parser.cc"
    break;

  case 752: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2679 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4129 "dhcp6_parser.cc"
    break;

  case 755: // $@132: %empty
#line 2688 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4139 "dhcp6_parser.cc"
    break;

  case 756: // output_entry: "{" $@132 output_params_list "}"
#line 2692 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4147 "dhcp6_parser.cc"
    break;

  case 764: // $@133: %empty
#line 2707 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4156 "dhcp6_parser.cc"
    break;

  case 765: // output: "output" $@133 ":" "constant string"
#line 2710 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4166 "dhcp6_parser.cc"
    break;

  case 766: // flush: "flush" ":" "boolean"
#line 2716 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4176 "dhcp6_parser.cc"
    break;

  case 767: // maxsize: "maxsize" ":" "integer"
#line 2722 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 768: // maxver: "maxver" ":" "integer"
#line 2728 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4196 "dhcp6_parser.cc"
    break;

  case 769: // $@134: %empty
#line 2734 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4205 "dhcp6_parser.cc"
    break;

  case 770: // pattern: "pattern" $@134 ":" "constant string"
#line 2737 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4215 "dhcp6_parser.cc"
    break;


#line 4219 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -935;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     501,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,    44,    36,    39,    43,    74,
      81,    88,   116,   118,   144,   148,   158,   159,   166,   168,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,    36,   -80,
     167,   149,    31,   510,    82,   241,   253,   119,   151,   192,
     -65,   632,    46,  -935,   235,   251,   252,   265,   307,  -935,
     304,  -935,  -935,  -935,  -935,  -935,  -935,   327,   339,   342,
     345,   356,   381,   383,   385,   387,   389,   390,   395,   396,
     402,  -935,   403,   405,   406,   413,   415,  -935,  -935,  -935,
     417,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,   418,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,   422,  -935,    75,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,   425,  -935,    93,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,   426,   427,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,    99,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,   101,  -935,  -935,
    -935,  -935,  -935,   428,  -935,   429,   432,  -935,  -935,  -935,
    -935,  -935,  -935,   124,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,   332,   376,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,   374,  -935,  -935,   444,  -935,  -935,  -935,   446,  -935,
    -935,   445,   392,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,   451,   452,  -935,  -935,
    -935,  -935,   449,   462,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,   150,  -935,  -935,  -935,
     463,  -935,  -935,   465,  -935,   466,   467,  -935,  -935,   468,
     469,  -935,  -935,  -935,  -935,  -935,  -935,  -935,   171,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,   470,   183,  -935,  -935,
    -935,  -935,    36,    36,  -935,   270,   471,  -935,   472,   473,
     477,   478,   480,   481,   289,   290,   291,   292,   294,   296,
     302,   308,   295,   303,   309,   310,   314,   316,   498,   321,
     324,   323,   326,   328,   499,   500,   502,   334,   519,   522,
     524,   527,   530,   534,   535,   536,   537,   538,   539,   541,
     542,   543,   544,   545,   353,   547,   548,   549,   563,   564,
     565,   566,  -935,   149,  -935,   574,   380,    31,  -935,   577,
     578,   579,   580,   581,   394,   388,   582,   584,   585,   510,
    -935,   590,    82,  -935,   591,   400,   602,   410,   411,   241,
    -935,   605,   606,   607,   609,   610,   611,   612,  -935,   253,
    -935,   614,   615,   430,   618,   619,   620,   433,  -935,   151,
     621,   435,   436,  -935,   192,   622,   633,   -51,  -935,   437,
     634,   635,   443,   637,   447,   453,   638,   639,   454,   455,
     647,   648,   651,   652,   632,  -935,   653,   464,    46,  -935,
    -935,  -935,   655,   656,   474,   657,   658,   659,   660,   664,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,   475,  -935,  -935,  -935,  -935,  -935,
    -106,   476,   479,  -935,   668,   669,   671,   670,   482,   306,
     674,   675,   692,   693,   715,   694,   695,   718,   725,   728,
    -935,   729,   730,   731,   732,   546,   550,   735,  -935,   736,
    -935,  -935,   738,   739,   551,   552,   553,  -935,  -935,   736,
     554,   746,  -935,   560,  -935,   567,  -935,   568,  -935,  -935,
    -935,   736,   736,   736,   569,   570,   571,   572,  -935,   573,
     575,  -935,   576,   583,   586,  -935,  -935,   600,  -935,  -935,
    -935,   601,   670,  -935,  -935,   603,   604,  -935,   613,  -935,
    -935,    97,   494,  -935,  -935,  -106,   616,   617,   623,  -935,
     740,  -935,  -935,    36,   149,  -935,    46,    31,   107,   107,
     752,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
     753,   754,   755,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,   767,   -79,    36,   -30,   557,   768,   769,   770,    56,
     227,   194,   229,   205,   632,  -935,  -935,   771,  -935,  -935,
     773,   791,  -935,  -935,  -935,  -935,  -935,   -70,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,   752,  -935,   218,
     228,   267,  -935,  -935,  -935,  -935,   797,   798,   801,   802,
     803,  -935,   804,   806,  -935,  -935,  -935,   807,   810,   811,
     812,  -935,   281,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,   282,  -935,   814,   815,  -935,  -935,
     816,   818,  -935,  -935,   817,   821,  -935,  -935,   819,   823,
    -935,  -935,   824,   826,  -935,  -935,  -935,   109,  -935,  -935,
    -935,   825,  -935,  -935,  -935,   156,  -935,  -935,  -935,  -935,
     283,  -935,  -935,  -935,   184,  -935,  -935,   827,   829,  -935,
    -935,   830,   834,  -935,   813,   835,   836,   837,   838,   839,
     297,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
     840,   841,   842,  -935,  -935,  -935,  -935,   298,  -935,  -935,
    -935,  -935,  -935,  -935,   843,   844,   845,  -935,   301,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
     305,  -935,  -935,  -935,   846,  -935,   847,  -935,  -935,  -935,
     311,  -935,  -935,  -935,  -935,  -935,   329,  -935,   217,  -935,
     631,  -935,   832,   849,  -935,  -935,   848,   850,  -935,  -935,
    -935,   852,  -935,   851,  -935,  -935,  -935,   854,   857,   858,
     859,   667,   666,   672,   673,   676,   862,   677,   678,   863,
     864,   866,   679,   680,   681,   682,   107,  -935,  -935,   107,
    -935,   752,   510,  -935,   753,   151,  -935,   754,   192,  -935,
     755,   663,  -935,   767,   -79,  -935,  -935,   -30,  -935,   867,
     557,  -935,   188,   768,  -935,   253,  -935,   769,   -65,  -935,
     770,   685,   686,   689,   691,   697,   699,    56,  -935,   874,
     885,   702,   708,   713,   227,  -935,   712,   717,   719,   194,
    -935,   914,   915,   229,  -935,   726,   922,   733,   923,   205,
    -935,  -935,   -20,   771,  -935,  -935,   930,   853,    82,  -935,
     773,   241,  -935,   791,   925,  -935,  -935,   391,   749,   756,
     759,  -935,  -935,  -935,  -935,  -935,   762,  -935,  -935,   765,
     776,   779,  -935,  -935,  -935,  -935,  -935,   330,  -935,   336,
    -935,   956,  -935,   959,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,   347,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,   787,  -935,  -935,   982,  -935,
    -935,  -935,  -935,  -935,   980,  1004,  -935,  -935,  -935,  -935,
    -935,  1001,  -935,   368,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,   225,   822,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,   828,   831,  -935,  -935,   833,  -935,    36,  -935,
    -935,  1007,  -935,  -935,  -935,  -935,  -935,   369,  -935,  -935,
    -935,  -935,  -935,  -935,   855,   372,  -935,   375,  -935,   856,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,   663,  -935,  -935,  1011,
     860,  -935,   188,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  1013,   861,  1016,   -20,  -935,  -935,
    -935,  -935,  -935,  -935,   865,  -935,  -935,  1018,  -935,   868,
    -935,  -935,  1014,  -935,  -935,   268,  -935,   -81,  1014,  -935,
    -935,  1021,  1022,  1024,  -935,   378,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  1026,   870,   869,   873,  1027,   -81,  -935,
     871,  -935,  -935,  -935,   875,  -935,  -935,  -935
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   162,     9,   324,    11,
     506,    13,   531,    15,   561,    17,   431,    19,   439,    21,
     476,    23,   289,    25,   674,    27,   724,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   563,     0,   441,   478,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   121,   722,   160,   174,   176,   178,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,     0,     0,     0,     0,   140,   147,   149,
       0,   316,   429,   468,   519,   521,   376,   384,   249,   266,
     257,   242,   598,   553,   281,   300,   619,     0,   268,   643,
     656,   672,   151,   153,   733,     0,   120,     0,    64,    66,
      67,    68,    69,    70,    71,    72,    73,    74,   102,   103,
     104,   105,   106,    75,   110,   111,   112,   113,   114,   115,
     108,   109,   116,   117,   118,   100,    78,    79,    80,    81,
      97,    82,    84,    83,   119,    88,    89,    76,   101,    77,
      86,    87,    95,    96,    98,    85,    90,    91,    92,    93,
      94,    99,   107,   171,     0,   170,     0,   164,   166,   167,
     168,   169,   498,   523,   366,   368,   370,     0,     0,   374,
     372,   592,   365,   328,   329,   330,   331,   332,   333,   334,
     335,   351,   352,   353,   354,   355,   358,   359,   360,   361,
     362,   363,   356,   357,   364,     0,   326,   339,   340,   341,
     344,   345,   347,   342,   343,   336,   337,   349,   350,   338,
     346,   348,   517,   516,   512,   513,   511,     0,   508,   510,
     514,   515,   546,     0,   549,     0,     0,   545,   539,   540,
     538,   543,   544,     0,   533,   535,   536,   541,   542,   537,
     590,   578,   580,   582,   584,   586,   588,   577,   574,   575,
     576,     0,   564,   565,   569,   570,   567,   571,   572,   573,
     568,     0,   458,   222,     0,   462,   460,   465,     0,   454,
     455,     0,   442,   443,   445,   457,   446,   447,   448,   464,
     449,   450,   451,   452,   453,   492,     0,     0,   490,   491,
     494,   495,     0,   479,   480,   482,   483,   484,   485,   486,
     487,   488,   489,   296,   298,   293,     0,   291,   294,   295,
       0,   697,   699,     0,   702,     0,     0,   706,   710,     0,
       0,   714,   716,   718,   720,   695,   693,   694,     0,   676,
     678,   690,   679,   680,   681,   682,   683,   684,   685,   686,
     687,   688,   689,   691,   692,   730,     0,     0,   726,   728,
     729,    46,     0,     0,    39,     0,     0,    59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    57,     0,    63,     0,     0,     0,   163,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     325,     0,     0,   507,     0,     0,     0,     0,     0,     0,
     532,     0,     0,     0,     0,     0,     0,     0,   562,     0,
     432,     0,     0,     0,     0,     0,     0,     0,   440,     0,
       0,     0,     0,   477,     0,     0,     0,     0,   290,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   675,     0,     0,     0,   725,
      50,    43,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,     0,   156,   157,   137,   138,   139,
       0,     0,     0,   155,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     642,     0,     0,     0,     0,     0,     0,     0,    65,     0,
     173,   165,     0,     0,     0,     0,     0,   382,   383,     0,
       0,     0,   327,     0,   509,     0,   548,     0,   551,   552,
     534,     0,     0,     0,     0,     0,     0,     0,   566,     0,
       0,   456,     0,     0,     0,   467,   444,     0,   496,   497,
     481,     0,     0,   292,   696,     0,     0,   701,     0,   704,
     705,     0,     0,   712,   713,     0,     0,     0,     0,   677,
       0,   732,   727,     0,     0,   122,     0,     0,     0,     0,
     180,   159,   142,   143,   144,   145,   146,   141,   148,   150,
     318,   433,   470,    40,   520,   522,   378,   379,   380,   381,
     377,   386,     0,    47,     0,     0,     0,   555,   283,     0,
       0,     0,     0,     0,     0,   152,   154,     0,    51,   172,
     500,   525,   367,   369,   371,   375,   373,     0,   518,   547,
     550,   591,   579,   581,   583,   585,   587,   589,   459,   223,
     463,   461,   466,   493,   297,   299,   698,   700,   703,   708,
     709,   707,   711,   715,   717,   719,   721,   180,    44,     0,
       0,     0,   209,   215,   217,   219,     0,     0,     0,     0,
       0,   233,     0,     0,   236,   238,   240,     0,     0,     0,
       0,   208,     0,   186,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   200,   207,   201,   202,   203,   198,
     199,   204,   205,   206,     0,   184,     0,   181,   182,   322,
       0,   319,   320,   437,     0,   434,   435,   474,     0,   471,
     472,   390,     0,   387,   388,   255,   256,     0,   251,   253,
     254,     0,   264,   265,   261,     0,   259,   262,   263,   247,
       0,   244,   246,   602,     0,   600,   559,     0,   556,   557,
     287,     0,   284,   285,     0,     0,     0,     0,     0,     0,
       0,   302,   304,   305,   306,   307,   308,   309,   632,   638,
       0,     0,     0,   631,   628,   629,   630,     0,   621,   623,
     626,   624,   625,   627,     0,     0,     0,   277,     0,   270,
     272,   273,   274,   275,   276,   652,   654,   651,   649,   650,
       0,   645,   647,   648,     0,   667,     0,   670,   663,   664,
       0,   658,   660,   661,   662,   665,     0,   737,     0,   735,
      53,   504,     0,   501,   502,   529,     0,   526,   527,   596,
     595,     0,   594,     0,    61,   723,   161,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   175,   177,     0,
     179,     0,     0,   317,     0,   441,   430,     0,   478,   469,
       0,     0,   385,     0,     0,   250,   267,     0,   258,     0,
       0,   243,   604,     0,   599,   563,   554,     0,     0,   282,
       0,     0,     0,     0,     0,     0,     0,     0,   301,     0,
       0,     0,     0,     0,     0,   620,     0,     0,     0,     0,
     269,     0,     0,     0,   644,     0,     0,     0,     0,     0,
     657,   673,     0,     0,   734,    55,     0,    54,     0,   499,
       0,     0,   524,     0,     0,   593,   731,     0,     0,     0,
       0,   221,   224,   225,   226,   227,     0,   235,   228,     0,
       0,     0,   230,   231,   232,   229,   187,     0,   183,     0,
     321,     0,   436,     0,   473,   428,   405,   406,   407,   409,
     410,   411,   398,   399,   414,   415,   416,   417,   418,   421,
     422,   423,   424,   425,   426,   419,   420,   427,   394,   395,
     396,   397,   403,   404,   402,   408,     0,   392,   400,   412,
     413,   401,   389,   252,   260,     0,   245,   616,     0,   614,
     615,   611,   612,   613,     0,   605,   606,   608,   609,   610,
     601,     0,   558,     0,   286,   310,   311,   312,   313,   314,
     315,   303,     0,     0,   637,   640,   641,   622,   278,   279,
     280,   271,     0,     0,   646,   666,     0,   669,     0,   659,
     751,     0,   749,   747,   741,   745,   746,     0,   739,   743,
     744,   742,   736,    52,     0,     0,   503,     0,   528,     0,
     211,   212,   213,   214,   210,   216,   218,   220,   234,   237,
     239,   241,   185,   323,   438,   475,     0,   391,   248,     0,
       0,   603,     0,   560,   288,   634,   635,   636,   633,   639,
     653,   655,   668,   671,     0,     0,     0,     0,   738,    56,
     505,   530,   597,   393,     0,   618,   607,     0,   748,     0,
     740,   617,     0,   750,   755,     0,   753,     0,     0,   752,
     764,     0,     0,     0,   769,     0,   757,   759,   760,   761,
     762,   763,   754,     0,     0,     0,     0,     0,     0,   756,
       0,   766,   767,   768,     0,   758,   765,   770
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,    -5,  -935,  -537,  -935,
     213,  -935,  -935,  -935,  -935,   340,  -935,  -556,  -935,  -935,
    -935,   -71,  -935,  -935,  -935,  -935,  -935,  -935,   370,   587,
    -935,  -935,   -59,   -40,   -39,   -21,   -19,   -18,   -15,    -1,
      13,    16,    17,    18,    19,  -935,    30,    33,    35,    37,
    -935,   377,    38,  -935,    40,  -935,    41,  -935,    45,  -935,
      51,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,   371,
     588,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
     288,  -935,    85,  -935,  -647,    91,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,   -63,  -935,  -687,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,    69,
    -935,  -935,  -935,  -935,  -935,    76,  -669,  -935,  -935,  -935,
    -935,    77,  -935,  -935,  -935,  -935,  -935,  -935,  -935,    42,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,    62,  -935,  -935,
    -935,    65,   528,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
      59,  -935,  -935,  -935,  -935,  -935,  -935,  -934,  -935,  -935,
    -935,    94,  -935,  -935,  -935,    95,   593,  -935,  -935,  -933,
    -935,  -931,  -935,    47,  -935,    55,  -935,    53,  -935,  -935,
    -935,  -930,  -935,  -935,  -935,  -935,    86,  -935,  -935,  -123,
     977,  -935,  -935,  -935,  -935,  -935,   100,  -935,  -935,  -935,
     105,  -935,   589,  -935,   -73,  -935,  -935,  -935,  -935,  -935,
     -67,  -935,  -935,  -935,  -935,  -935,   -37,  -935,  -935,  -935,
      96,  -935,  -935,  -935,   104,  -935,   561,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,    54,  -935,
    -935,  -935,    60,   595,  -935,  -935,   -55,  -935,     1,  -935,
    -935,  -935,  -935,  -935,    57,  -935,  -935,  -935,    58,   592,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,   -44,  -935,  -935,
    -935,   106,  -935,  -935,  -935,   110,  -935,   594,   346,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -929,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
     111,  -935,  -935,  -935,  -100,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,    92,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,    84,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,    79,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,   386,   555,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,  -935,
    -935,  -935,  -935,  -935,  -935,   431,   556,  -935,  -935,  -935,
    -935,  -935,  -935,    78,  -935,  -935,  -105,  -935,  -935,  -935,
    -935,  -935,  -935,  -122,  -935,  -935,  -143,  -935,  -935,  -935,
    -935,  -935,  -935,  -935
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     684,    87,    88,    41,    68,    84,    85,   709,   910,  1016,
    1017,   771,    43,    70,    90,   406,    45,    71,   147,   148,
     149,   408,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     434,   677,   168,   435,   169,   436,   170,   459,   171,   460,
     172,   173,   174,   175,   428,   176,   410,    47,    72,   206,
     207,   208,   465,   209,   177,   411,   178,   412,   179,   413,
     796,   797,   798,   949,   772,   773,   774,   927,  1164,   775,
     928,   776,   929,   777,   930,   778,   779,   502,   780,   781,
     782,   783,   784,   785,   786,   787,   788,   789,   936,   790,
     791,   939,   792,   940,   793,   941,   180,   448,   830,   831,
     832,   969,   181,   445,   817,   818,   819,   820,   182,   447,
     825,   826,   827,   828,   183,   446,   184,   455,   878,   879,
     880,   881,   882,   185,   451,   841,   842,   843,   978,    63,
      80,   356,   357,   358,   515,   359,   516,   186,   452,   850,
     851,   852,   853,   854,   855,   856,   857,   187,   438,   800,
     801,   802,   952,    49,    73,   245,   246,   247,   471,   248,
     472,   249,   473,   250,   477,   251,   476,   188,   443,   690,
     253,   254,   189,   444,   812,   813,   814,   961,  1086,  1087,
     190,   439,    57,    77,   804,   805,   806,   955,    59,    78,
     321,   322,   323,   324,   325,   326,   327,   501,   328,   505,
     329,   504,   330,   331,   506,   332,   191,   440,   808,   809,
     810,   958,    61,    79,   342,   343,   344,   345,   346,   510,
     347,   348,   349,   350,   256,   469,   912,   913,   914,  1018,
      51,    74,   267,   268,   269,   481,   192,   441,   193,   442,
     259,   470,   916,   917,   918,  1021,    53,    75,   283,   284,
     285,   484,   286,   287,   486,   288,   289,   194,   450,   837,
     838,   839,   975,    55,    76,   301,   302,   303,   304,   492,
     305,   493,   306,   494,   307,   495,   308,   496,   309,   497,
     310,   491,   261,   478,   921,   922,  1024,   195,   449,   834,
     835,   972,  1104,  1105,  1106,  1107,  1108,  1179,  1109,   196,
     453,   867,   868,   869,   989,  1188,   870,   871,   990,   872,
     873,   197,   198,   456,   890,   891,   892,  1001,   893,  1002,
     199,   457,   900,   901,   902,   903,  1006,   904,   905,  1008,
     200,   458,    65,    81,   378,   379,   380,   381,   520,   382,
     521,   383,   384,   523,   385,   386,   387,   526,   741,   388,
     527,   389,   390,   391,   530,   392,   531,   393,   532,   394,
     533,   201,   409,    67,    82,   397,   398,   399,   536,   400,
     202,   461,   908,   909,  1012,  1147,  1148,  1149,  1150,  1196,
    1151,  1194,  1215,  1216,  1217,  1225,  1226,  1227,  1233,  1228,
    1229,  1230,  1231,  1237
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     146,   205,   222,   263,   277,   297,   340,   319,   338,   355,
     375,    38,   341,   864,   223,   320,   339,   210,   257,   270,
     281,   299,   794,   333,   351,   824,   376,  1079,  1080,   260,
    1081,  1085,  1091,   224,   225,   815,   255,   266,   280,   298,
     683,    31,   291,    32,    30,    33,    42,   203,   204,   919,
      44,   313,   226,   715,   227,   228,   353,   354,   229,   395,
     396,   672,   673,   674,   675,   721,   722,   723,   124,   125,
     353,   354,   230,   211,   258,   271,   282,   300,   463,   334,
     352,    46,   377,   464,   815,   822,   231,   823,    48,   232,
     233,   234,   235,   676,  1220,    50,   467,  1221,  1222,  1223,
    1224,   468,   479,   236,   482,   683,   237,   480,   238,   483,
     239,   240,   964,   241,   242,   965,    86,   816,   243,   124,
     125,   264,   278,    52,   244,    54,   252,   489,   752,   265,
     279,   145,   490,   753,   754,   755,   756,   757,   758,   759,
     760,   761,   762,   763,   764,   765,   766,   767,   768,   769,
     770,    56,   123,   517,  1140,    58,  1141,  1142,   518,   967,
      91,    92,   968,   262,    93,    60,    62,    94,    95,    96,
     124,   125,   312,    64,   534,    66,   145,    89,   313,   535,
     844,   845,   846,   847,   848,   849,   538,   973,   122,   219,
     974,   539,   220,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
    1013,   463,   313,  1014,   314,   315,   924,   145,   316,   317,
     318,   538,    34,    35,    36,    37,   925,   124,   125,   124,
     125,   401,  1079,  1080,   126,  1081,  1085,  1091,   858,   127,
     128,   129,   130,   131,   402,   132,   403,   757,   123,   313,
     133,   739,   740,   313,   335,   314,   315,   336,   337,   134,
     467,  1218,   135,   404,  1219,   926,   124,   125,   145,   136,
     124,   125,   124,   125,   946,   946,   970,   137,   138,   947,
     948,   971,   139,   124,   125,   140,  1097,  1098,   824,   141,
     987,   994,  1047,   145,   999,   988,   995,   864,  1003,  1000,
     405,   123,   407,  1004,  1009,   124,   125,   124,   125,  1010,
     142,   143,   144,   123,   272,   273,   274,   275,   276,   124,
     125,   414,   534,   946,   874,   875,   876,  1011,  1172,   479,
     498,   124,   125,   415,  1173,   145,   416,   145,   219,   417,
    1176,   220,   894,   895,   896,  1177,  1185,  1186,  1187,   290,
     418,   859,   860,   861,   862,   291,   292,   293,   294,   295,
     296,   517,  1197,   885,   886,   482,  1184,  1198,   489,   499,
    1200,  1238,   500,  1201,   145,   419,  1239,   420,   145,   421,
     145,   422,   146,   423,   424,   509,   205,   540,   541,   425,
     426,   897,   686,   687,   688,   689,   427,   429,   222,   430,
     431,   263,   210,  1160,  1161,  1162,  1163,   432,   277,   433,
     223,   437,   454,   145,   257,   145,   462,   270,   297,   466,
     474,   475,   485,   487,   281,   260,   488,   145,   319,   224,
     225,   340,   255,   338,   299,   266,   320,   341,   503,   145,
     507,   339,   280,   508,   333,   511,   512,   513,   226,   351,
     227,   228,   298,   375,   229,   514,   542,   519,   211,   522,
     524,   525,   528,   529,   537,   543,   544,   545,   230,   376,
     258,   546,   547,   271,   548,   549,   550,   551,   552,   553,
     282,   554,   231,   555,   558,   232,   233,   234,   235,   556,
     300,   559,   564,   570,   571,   557,   572,   560,   561,   236,
     334,   562,   237,   563,   238,   352,   239,   240,   565,   241,
     242,   566,   567,   574,   243,   568,   575,   569,   576,   264,
     244,   577,   252,   573,   578,   377,   278,   265,   579,   580,
     581,   582,   583,   584,   279,   585,   586,   587,   588,   589,
     590,   591,   592,   593,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   594,   595,   596,
     597,   114,   115,   116,   117,   118,   119,   120,   599,   600,
     123,   602,   603,   604,   605,   606,   609,   608,   610,   611,
     212,   607,   213,   146,   613,   615,   205,   616,   124,   125,
     214,   215,   216,   217,   218,   126,   617,   618,   619,   621,
     622,   623,   210,   624,   625,   626,   627,   219,   629,   630,
     220,   133,   632,   633,   634,   637,   641,   631,   221,   863,
     877,   887,   635,   375,   638,   639,   644,   642,   645,   646,
     647,   648,   651,   652,   649,   865,   883,   888,   898,   376,
     650,   655,   656,   653,   654,   657,   658,   660,   748,   663,
     742,   661,   829,   664,   666,   667,   668,   669,   211,   670,
     665,   671,   678,   680,   681,   679,   682,    32,   685,   691,
     692,   142,   143,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   693,   694,   696,
     697,   866,   884,   889,   899,   377,   145,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     124,   125,   695,   698,   114,   115,   116,   117,   118,   119,
     120,   121,   699,   123,   313,   700,   701,   702,   703,   704,
     707,   708,   705,   710,   711,   747,   706,   712,   713,   714,
     716,   124,   125,   717,   215,   216,   718,   218,   126,   795,
     799,   803,   807,   719,   720,   724,   725,   726,   727,   728,
     219,   729,   730,   220,   811,   833,   836,   840,   907,   731,
     911,   221,   732,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   372,   733,   734,   915,   736,
     737,   931,   932,   373,   374,   933,   934,   935,   937,   738,
     938,   942,   744,   745,   943,   944,   945,   981,   951,   746,
     950,   954,   953,   956,   957,   959,   960,  1015,   145,   963,
     962,   966,   977,   976,   142,   143,   979,   980,  1019,   982,
     983,   984,   985,   986,   991,   992,   993,   996,   997,   998,
    1005,  1007,  1020,  1023,  1022,   735,  1154,  1026,  1027,   145,
    1025,  1028,  1029,  1030,  1031,  1032,  1036,  1039,  1040,  1033,
    1041,  1095,  1034,  1035,  1037,  1038,  1042,  1043,  1122,  1045,
    1044,   222,  1115,  1116,   319,   340,  1117,   338,  1118,  1123,
    1055,   341,   320,   223,  1119,   339,  1120,   257,  1078,  1124,
     333,  1099,  1056,   351,   297,  1125,  1089,   355,   260,  1100,
    1126,  1128,   224,   225,  1129,   255,  1130,  1102,  1132,  1133,
     299,  1057,  1058,   863,  1088,  1135,  1136,  1138,   877,  1159,
    1137,   226,   887,   227,   228,  1101,  1153,   229,   298,   865,
    1059,  1143,  1060,  1061,   883,  1165,  1062,   263,   888,  1144,
     277,   230,  1166,   258,   898,  1167,   334,  1145,  1168,   352,
    1063,  1169,  1090,   270,  1174,   231,   281,  1175,   232,   233,
     234,   235,  1170,  1103,  1064,  1171,   300,  1065,  1066,  1067,
    1068,   266,   236,  1178,   280,   237,  1180,   238,  1181,   239,
     240,  1069,   241,   242,  1070,   866,  1071,   243,  1072,  1073,
     884,  1074,  1075,   244,   889,   252,  1076,  1182,  1082,  1183,
     899,  1195,  1077,  1146,  1084,  1204,  1083,  1207,  1189,   271,
    1209,  1214,   282,  1212,  1190,  1234,  1235,  1191,  1236,  1192,
    1240,  1244,   743,   821,   749,   923,  1048,  1046,   751,  1096,
    1093,  1131,  1114,  1113,  1094,   643,  1121,  1049,  1050,  1092,
     598,  1199,  1202,  1203,   311,   601,  1054,  1052,  1208,  1205,
    1051,  1211,  1053,   920,  1213,   264,  1242,  1246,   278,  1241,
    1243,  1247,   612,   265,  1156,   640,   279,   614,  1155,  1157,
    1158,   620,  1206,  1112,  1110,  1111,  1127,  1134,  1139,   659,
     906,  1152,  1210,   628,   662,  1245,  1232,   750,   636,     0,
       0,     0,     0,     0,     0,  1055,     0,     0,     0,     0,
       0,  1099,     0,  1078,     0,     0,     0,  1056,     0,  1100,
       0,  1089,     0,     0,     0,     0,  1143,  1102,     0,     0,
       0,     0,     0,  1193,  1144,     0,  1057,  1058,     0,  1088,
       0,     0,  1145,     0,     0,  1101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1059,     0,  1060,  1061,     0,
       0,  1062,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1063,     0,  1090,     0,     0,
       0,     0,     0,  1103,     0,     0,     0,     0,     0,  1064,
       0,     0,  1065,  1066,  1067,  1068,     0,     0,  1146,     0,
       0,     0,     0,     0,     0,     0,  1069,     0,     0,  1070,
       0,  1071,     0,  1072,  1073,     0,  1074,  1075,     0,     0,
       0,  1076,     0,  1082,     0,     0,     0,  1077,     0,  1084,
       0,  1083
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    79,    78,    79,    80,
      81,    16,    79,   700,    73,    78,    79,    72,    73,    74,
      75,    76,   669,    78,    79,   694,    81,   961,   961,    73,
     961,   961,   961,    73,    73,   114,    73,    74,    75,    76,
     577,     5,   112,     7,     0,     9,     7,    16,    17,   119,
       7,    71,    73,   609,    73,    73,   121,   122,    73,    13,
      14,   167,   168,   169,   170,   621,   622,   623,    88,    89,
     121,   122,    73,    72,    73,    74,    75,    76,     3,    78,
      79,     7,    81,     8,   114,   115,    73,   117,     7,    73,
      73,    73,    73,   199,   175,     7,     3,   178,   179,   180,
     181,     8,     3,    73,     3,   642,    73,     8,    73,     8,
      73,    73,     3,    73,    73,     6,   196,   196,    73,    88,
      89,    74,    75,     7,    73,     7,    73,     3,    21,    74,
      75,   196,     8,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,     7,    70,     3,   174,     7,   176,   177,     8,     3,
      11,    12,     6,    81,    15,     7,     7,    18,    19,    20,
      88,    89,    21,     7,     3,     7,   196,    10,    71,     8,
     124,   125,   126,   127,   128,   129,     3,     3,    69,   107,
       6,     8,   110,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
       3,     3,    71,     6,    73,    74,     8,   196,    77,    78,
      79,     3,   196,   197,   198,   199,     8,    88,    89,    88,
      89,     6,  1176,  1176,    95,  1176,  1176,  1176,    21,   100,
     101,   102,   103,   104,     3,   106,     4,    30,    70,    71,
     111,   164,   165,    71,    72,    73,    74,    75,    76,   120,
       3,     3,   123,     8,     6,     8,    88,    89,   196,   130,
      88,    89,    88,    89,     3,     3,     3,   138,   139,     8,
       8,     8,   143,    88,    89,   146,   108,   109,   967,   150,
       3,     3,   949,   196,     3,     8,     8,   994,     3,     8,
       3,    70,     8,     8,     3,    88,    89,    88,    89,     8,
     171,   172,   173,    70,    83,    84,    85,    86,    87,    88,
      89,     4,     3,     3,   140,   141,   142,     8,     8,     3,
       8,    88,    89,     4,     8,   196,     4,   196,   107,     4,
       3,   110,   147,   148,   149,     8,   131,   132,   133,   106,
       4,   134,   135,   136,   137,   112,   113,   114,   115,   116,
     117,     3,     3,   144,   145,     3,     8,     8,     3,     3,
       8,     3,     8,     8,   196,     4,     8,     4,   196,     4,
     196,     4,   463,     4,     4,     3,   467,   402,   403,     4,
       4,   196,    96,    97,    98,    99,     4,     4,   479,     4,
       4,   482,   467,    22,    23,    24,    25,     4,   489,     4,
     479,     4,     4,   196,   479,   196,     4,   482,   499,     4,
       4,     4,     4,     4,   489,   479,     4,   196,   509,   479,
     479,   514,   479,   514,   499,   482,   509,   514,     4,   196,
       4,   514,   489,     8,   509,     4,     4,     8,   479,   514,
     479,   479,   499,   534,   479,     3,   196,     4,   467,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   479,   534,
     479,     4,     4,   482,     4,     4,   197,   197,   197,   197,
     489,   197,   479,   197,   199,   479,   479,   479,   479,   197,
     499,   198,     4,     4,     4,   197,     4,   198,   198,   479,
     509,   197,   479,   197,   479,   514,   479,   479,   197,   479,
     479,   197,   199,     4,   479,   199,     4,   199,     4,   482,
     479,     4,   479,   199,     4,   534,   489,   482,     4,     4,
       4,     4,     4,     4,   489,     4,     4,     4,     4,     4,
     197,     4,     4,     4,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,     4,     4,     4,
       4,    61,    62,    63,    64,    65,    66,    67,     4,   199,
      70,     4,     4,     4,     4,     4,     4,   199,     4,     4,
      80,   197,    82,   664,     4,     4,   667,   197,    88,    89,
      90,    91,    92,    93,    94,    95,     4,   197,   197,     4,
       4,     4,   667,     4,     4,     4,     4,   107,     4,     4,
     110,   111,     4,     4,     4,     4,     4,   197,   118,   700,
     701,   702,   199,   704,   199,   199,   199,     4,     4,     4,
     197,     4,     4,     4,   197,   700,   701,   702,   703,   704,
     197,     4,     4,   199,   199,     4,     4,     4,   663,     4,
     166,   197,   105,     7,     7,     7,     7,     7,   667,     5,
     196,   196,   196,     5,     5,   196,     5,     7,   196,     5,
       5,   171,   172,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,     5,     5,     5,
       5,   700,   701,   702,   703,   704,   196,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      88,    89,     7,     5,    61,    62,    63,    64,    65,    66,
      67,    68,     7,    70,    71,     7,     7,     7,     7,     7,
       5,     5,   196,     5,     5,     5,   196,   196,   196,   196,
     196,    88,    89,     7,    91,    92,   196,    94,    95,     7,
       7,     7,     7,   196,   196,   196,   196,   196,   196,   196,
     107,   196,   196,   110,     7,     7,     7,     7,     7,   196,
       7,   118,   196,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   196,   196,     7,   196,
     196,     4,     4,   171,   172,     4,     4,     4,     4,   196,
       4,     4,   196,   196,     4,     4,     4,     4,     3,   196,
       6,     3,     6,     6,     3,     6,     3,   196,   196,     3,
       6,     6,     3,     6,   171,   172,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,     3,     6,   642,     3,     6,     4,   196,
       8,     4,     4,     4,   197,   199,     4,     4,     4,   197,
       4,     4,   199,   197,   197,   197,   197,   197,     4,   197,
     199,   952,   197,   197,   955,   958,   197,   958,   197,     4,
     961,   958,   955,   952,   197,   958,   197,   952,   961,   197,
     955,   972,   961,   958,   975,   197,   961,   978,   952,   972,
     197,   199,   952,   952,   197,   952,   197,   972,     4,     4,
     975,   961,   961,   994,   961,   199,     4,     4,   999,     4,
     197,   952,  1003,   952,   952,   972,     6,   952,   975,   994,
     961,  1012,   961,   961,   999,   196,   961,  1018,  1003,  1012,
    1021,   952,   196,   952,  1009,   196,   955,  1012,   196,   958,
     961,   196,   961,  1018,     8,   952,  1021,     8,   952,   952,
     952,   952,   196,   972,   961,   196,   975,   961,   961,   961,
     961,  1018,   952,   196,  1021,   952,     4,   952,     8,   952,
     952,   961,   952,   952,   961,   994,   961,   952,   961,   961,
     999,   961,   961,   952,  1003,   952,   961,     3,   961,     8,
    1009,     4,   961,  1012,   961,     4,   961,     4,   196,  1018,
       4,     7,  1021,     5,   196,     4,     4,   196,     4,   196,
       4,     4,   655,   693,   664,   747,   951,   946,   667,   970,
     964,   999,   980,   978,   967,   517,   987,   952,   954,   963,
     463,   196,   196,  1176,    77,   467,   960,   957,   197,   199,
     955,   196,   958,   717,   196,  1018,   197,   196,  1021,   199,
     197,   196,   479,  1018,  1020,   514,  1021,   482,  1018,  1021,
    1023,   489,  1182,   977,   973,   975,   994,  1003,  1009,   534,
     704,  1013,  1197,   499,   538,  1238,  1218,   666,   509,    -1,
      -1,    -1,    -1,    -1,    -1,  1176,    -1,    -1,    -1,    -1,
      -1,  1182,    -1,  1176,    -1,    -1,    -1,  1176,    -1,  1182,
      -1,  1176,    -1,    -1,    -1,    -1,  1197,  1182,    -1,    -1,
      -1,    -1,    -1,  1138,  1197,    -1,  1176,  1176,    -1,  1176,
      -1,    -1,  1197,    -1,    -1,  1182,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1176,    -1,  1176,  1176,    -1,
      -1,  1176,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1176,    -1,  1176,    -1,    -1,
      -1,    -1,    -1,  1182,    -1,    -1,    -1,    -1,    -1,  1176,
      -1,    -1,  1176,  1176,  1176,  1176,    -1,    -1,  1197,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1176,    -1,    -1,  1176,
      -1,  1176,    -1,  1176,  1176,    -1,  1176,  1176,    -1,    -1,
      -1,  1176,    -1,  1176,    -1,    -1,    -1,  1176,    -1,  1176,
      -1,  1176
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
       0,     5,     7,     9,   196,   197,   198,   199,   216,   217,
     218,   223,     7,   232,     7,   236,     7,   277,     7,   383,
       7,   460,     7,   476,     7,   493,     7,   412,     7,   418,
       7,   442,     7,   359,     7,   562,     7,   593,   224,   219,
     233,   237,   278,   384,   461,   477,   494,   413,   419,   443,
     360,   563,   594,   216,   225,   226,   196,   221,   222,    10,
     234,    11,    12,    15,    18,    19,    20,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    88,    89,    95,   100,   101,   102,
     103,   104,   106,   111,   120,   123,   130,   138,   139,   143,
     146,   150,   171,   172,   173,   196,   231,   238,   239,   240,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   262,   264,
     266,   268,   270,   271,   272,   273,   275,   284,   286,   288,
     326,   332,   338,   344,   346,   353,   367,   377,   397,   402,
     410,   436,   466,   468,   487,   517,   529,   541,   542,   550,
     560,   591,   600,    16,    17,   231,   279,   280,   281,   283,
     466,   468,    80,    82,    90,    91,    92,    93,    94,   107,
     110,   118,   231,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   256,   257,   258,   259,
     262,   264,   266,   268,   270,   385,   386,   387,   389,   391,
     393,   395,   397,   400,   401,   436,   454,   466,   468,   470,
     487,   512,    81,   231,   393,   395,   436,   462,   463,   464,
     466,   468,    83,    84,    85,    86,    87,   231,   393,   395,
     436,   466,   468,   478,   479,   480,   482,   483,   485,   486,
     106,   112,   113,   114,   115,   116,   117,   231,   436,   466,
     468,   495,   496,   497,   498,   500,   502,   504,   506,   508,
     510,   410,    21,    71,    73,    74,    77,    78,    79,   231,
     306,   420,   421,   422,   423,   424,   425,   426,   428,   430,
     432,   433,   435,   466,   468,    72,    75,    76,   231,   306,
     424,   430,   444,   445,   446,   447,   448,   450,   451,   452,
     453,   466,   468,   121,   122,   231,   361,   362,   363,   365,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   171,   172,   231,   466,   468,   564,   565,
     566,   567,   569,   571,   572,   574,   575,   576,   579,   581,
     582,   583,   585,   587,   589,    13,    14,   595,   596,   597,
     599,     6,     3,     4,     8,     3,   235,     8,   241,   592,
     276,   285,   287,   289,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   274,     4,
       4,     4,     4,     4,   260,   263,   265,     4,   378,   411,
     437,   467,   469,   398,   403,   333,   345,   339,   327,   518,
     488,   354,   368,   530,     4,   347,   543,   551,   561,   267,
     269,   601,     4,     3,     8,   282,     4,     3,     8,   455,
     471,   388,   390,   392,     4,     4,   396,   394,   513,     3,
       8,   465,     3,     8,   481,     4,   484,     4,     4,     3,
       8,   511,   499,   501,   503,   505,   507,   509,     8,     3,
       8,   427,   307,     4,   431,   429,   434,     4,     8,     3,
     449,     4,     4,     8,     3,   364,   366,     3,     8,     4,
     568,   570,     4,   573,     4,     4,   577,   580,     4,     4,
     584,   586,   588,   590,     3,     8,   598,     4,     3,     8,
     216,   216,   196,     4,     4,     4,     4,     4,     4,     4,
     197,   197,   197,   197,   197,   197,   197,   197,   199,   198,
     198,   198,   197,   197,     4,   197,   197,   199,   199,   199,
       4,     4,     4,   199,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     197,     4,     4,     4,     4,     4,     4,     4,   239,     4,
     199,   280,     4,     4,     4,     4,     4,   197,   199,     4,
       4,     4,   386,     4,   463,     4,   197,     4,   197,   197,
     479,     4,     4,     4,     4,     4,     4,     4,   497,     4,
       4,   197,     4,     4,     4,   199,   422,     4,   199,   199,
     446,     4,     4,   362,   199,     4,     4,   197,     4,   197,
     197,     4,     4,   199,   199,     4,     4,     4,     4,   565,
       4,   197,   596,     4,     7,   196,     7,     7,     7,     7,
       5,   196,   167,   168,   169,   170,   199,   261,   196,   196,
       5,     5,     5,   218,   220,   196,    96,    97,    98,    99,
     399,     5,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,     7,     7,     7,   196,   196,     5,     5,   227,
       5,     5,   196,   196,   196,   227,   196,     7,   196,   196,
     196,   227,   227,   227,   196,   196,   196,   196,   196,   196,
     196,   196,   196,   196,   196,   220,   196,   196,   196,   164,
     165,   578,   166,   261,   196,   196,   196,     5,   216,   238,
     595,   279,    21,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,   231,   294,   295,   296,   299,   301,   303,   305,   306,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     319,   320,   322,   324,   294,     7,   290,   291,   292,     7,
     379,   380,   381,     7,   414,   415,   416,     7,   438,   439,
     440,     7,   404,   405,   406,   114,   196,   334,   335,   336,
     337,   225,   115,   117,   336,   340,   341,   342,   343,   105,
     328,   329,   330,     7,   519,   520,     7,   489,   490,   491,
       7,   355,   356,   357,   124,   125,   126,   127,   128,   129,
     369,   370,   371,   372,   373,   374,   375,   376,    21,   134,
     135,   136,   137,   231,   308,   466,   468,   531,   532,   533,
     536,   537,   539,   540,   140,   141,   142,   231,   348,   349,
     350,   351,   352,   466,   468,   144,   145,   231,   466,   468,
     544,   545,   546,   548,   147,   148,   149,   196,   466,   468,
     552,   553,   554,   555,   557,   558,   564,     7,   602,   603,
     228,     7,   456,   457,   458,     7,   472,   473,   474,   119,
     498,   514,   515,   290,     8,     8,     8,   297,   300,   302,
     304,     4,     4,     4,     4,     4,   318,     4,     4,   321,
     323,   325,     4,     4,     4,     4,     3,     8,     8,   293,
       6,     3,   382,     6,     3,   417,     6,     3,   441,     6,
       3,   407,     6,     3,     3,     6,     6,     3,     6,   331,
       3,     8,   521,     3,     6,   492,     6,     3,   358,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   534,
     538,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   547,   549,     3,     8,     4,   556,     4,   559,     3,
       8,     8,   604,     3,     6,   196,   229,   230,   459,     6,
       3,   475,     6,     3,   516,     8,     6,     4,     4,     4,
       4,   197,   199,   197,   199,   197,     4,   197,   197,     4,
       4,     4,   197,   197,   199,   197,   295,   294,   292,   385,
     381,   420,   416,   444,   440,   231,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   256,
     257,   258,   259,   262,   264,   266,   268,   270,   306,   377,
     389,   391,   393,   395,   397,   401,   408,   409,   436,   466,
     468,   512,   406,   335,   341,     4,   329,   108,   109,   231,
     306,   436,   466,   468,   522,   523,   524,   525,   526,   528,
     520,   495,   491,   361,   357,   197,   197,   197,   197,   197,
     197,   370,     4,     4,   197,   197,   197,   532,   199,   197,
     197,   349,     4,     4,   545,   199,     4,   197,     4,   553,
     174,   176,   177,   231,   306,   466,   468,   605,   606,   607,
     608,   610,   603,     6,     3,   462,   458,   478,   474,     4,
      22,    23,    24,    25,   298,   196,   196,   196,   196,   196,
     196,   196,     8,     8,     8,     8,     3,     8,   196,   527,
       4,     8,     3,     8,     8,   131,   132,   133,   535,   196,
     196,   196,   196,   216,   611,     4,   609,     3,     8,   196,
       8,     8,   196,   409,     4,   199,   524,     4,   197,     4,
     606,   196,     5,   196,     7,   612,   613,   614,     3,     6,
     175,   178,   179,   180,   181,   615,   616,   617,   619,   620,
     621,   622,   613,   618,     4,     4,     4,   623,     3,     8,
       4,   199,   197,   197,     4,   616,   196,   196
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
     235,   234,   237,   236,   238,   238,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   241,   240,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     260,   259,   261,   261,   261,   261,   261,   263,   262,   265,
     264,   267,   266,   269,   268,   270,   271,   272,   274,   273,
     276,   275,   278,   277,   279,   279,   280,   280,   280,   280,
     280,   282,   281,   283,   285,   284,   287,   286,   289,   288,
     290,   290,   291,   291,   293,   292,   294,   294,   295,   295,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   297,
     296,   298,   298,   298,   298,   300,   299,   302,   301,   304,
     303,   305,   307,   306,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   318,   317,   319,   321,   320,   323,   322,
     325,   324,   327,   326,   328,   328,   329,   331,   330,   333,
     332,   334,   334,   335,   335,   336,   337,   339,   338,   340,
     340,   341,   341,   341,   342,   343,   345,   344,   347,   346,
     348,   348,   349,   349,   349,   349,   349,   349,   350,   351,
     352,   354,   353,   355,   355,   356,   356,   358,   357,   360,
     359,   361,   361,   361,   362,   362,   364,   363,   366,   365,
     368,   367,   369,   369,   370,   370,   370,   370,   370,   370,
     371,   372,   373,   374,   375,   376,   378,   377,   379,   379,
     380,   380,   382,   381,   384,   383,   385,   385,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   388,   387,   390,   389,
     392,   391,   394,   393,   396,   395,   398,   397,   399,   399,
     399,   399,   400,   401,   403,   402,   404,   404,   405,   405,
     407,   406,   408,   408,   409,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   409,   409,   409,   411,
     410,   413,   412,   414,   414,   415,   415,   417,   416,   419,
     418,   420,   420,   421,   421,   422,   422,   422,   422,   422,
     422,   422,   422,   422,   422,   423,   424,   425,   427,   426,
     429,   428,   431,   430,   432,   434,   433,   435,   437,   436,
     438,   438,   439,   439,   441,   440,   443,   442,   444,   444,
     445,   445,   446,   446,   446,   446,   446,   446,   446,   446,
     446,   447,   449,   448,   450,   451,   452,   453,   455,   454,
     456,   456,   457,   457,   459,   458,   461,   460,   462,   462,
     463,   463,   463,   463,   463,   463,   463,   465,   464,   467,
     466,   469,   468,   471,   470,   472,   472,   473,   473,   475,
     474,   477,   476,   478,   478,   479,   479,   479,   479,   479,
     479,   479,   479,   479,   479,   479,   481,   480,   482,   484,
     483,   485,   486,   488,   487,   489,   489,   490,   490,   492,
     491,   494,   493,   495,   495,   496,   496,   497,   497,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   499,   498,
     501,   500,   503,   502,   505,   504,   507,   506,   509,   508,
     511,   510,   513,   512,   514,   514,   516,   515,   518,   517,
     519,   519,   521,   520,   522,   522,   523,   523,   524,   524,
     524,   524,   524,   524,   524,   525,   527,   526,   528,   530,
     529,   531,   531,   532,   532,   532,   532,   532,   532,   532,
     532,   532,   534,   533,   535,   535,   535,   536,   538,   537,
     539,   540,   541,   543,   542,   544,   544,   545,   545,   545,
     545,   545,   547,   546,   549,   548,   551,   550,   552,   552,
     553,   553,   553,   553,   553,   553,   554,   556,   555,   557,
     559,   558,   561,   560,   563,   562,   564,   564,   565,   565,
     565,   565,   565,   565,   565,   565,   565,   565,   565,   565,
     565,   565,   565,   565,   565,   565,   566,   568,   567,   570,
     569,   571,   573,   572,   574,   575,   577,   576,   578,   578,
     580,   579,   581,   582,   584,   583,   586,   585,   588,   587,
     590,   589,   592,   591,   594,   593,   595,   595,   596,   596,
     598,   597,   599,   601,   600,   602,   602,   604,   603,   605,
     605,   606,   606,   606,   606,   606,   606,   606,   607,   609,
     608,   611,   610,   612,   612,   614,   613,   615,   615,   616,
     616,   616,   616,   616,   618,   617,   619,   620,   621,   623,
     622
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
       1,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     0,     6,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     3,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     6,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       4,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     1,     0,     4,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     3,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       0,     6,     3,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4
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
  "\"t1-percent\"", "\"t2-percent\"", "\"cache-threshold\"",
  "\"cache-max\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"store-extended-info\"", "\"subnet6\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"shared-networks\"",
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
  "syntax_map", "$@18", "global_object", "$@19", "sub_dhcp6", "$@20",
  "global_params", "global_param", "data_directory", "$@21",
  "preferred_lifetime", "min_preferred_lifetime", "max_preferred_lifetime",
  "valid_lifetime", "min_valid_lifetime", "max_valid_lifetime",
  "renew_timer", "rebind_timer", "calculate_tee_times", "t1_percent",
  "t2_percent", "cache_threshold", "cache_max", "decline_probation_period",
  "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@22",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@23",
  "ddns_qualifying_suffix", "$@24", "hostname_char_set", "$@25",
  "hostname_char_replacement", "$@26", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "server_tag", "$@27", "interfaces_config", "$@28", "sub_interfaces6",
  "$@29", "interfaces_config_params", "interfaces_config_param",
  "interfaces_list", "$@30", "re_detect", "lease_database", "$@31",
  "hosts_database", "$@32", "hosts_databases", "$@33", "database_list",
  "not_empty_database_list", "database", "$@34", "database_map_params",
  "database_map_param", "database_type", "$@35", "db_type", "user", "$@36",
  "password", "$@37", "host", "$@38", "port", "name", "$@39", "persist",
  "lfc_interval", "readonly", "connect_timeout", "reconnect_wait_time",
  "max_row_errors", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@40", "max_reconnect_tries", "keyspace", "$@41",
  "consistency", "$@42", "serial_consistency", "$@43", "sanity_checks",
  "$@44", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@45", "mac_sources", "$@46", "mac_sources_list", "mac_sources_value",
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
  "dhcp_ddns_param", "enable_updates", "dep_qualifying_suffix", "$@116",
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
     331,   334,   335,   338,   343,   351,   351,   358,   359,   362,
     366,   373,   373,   380,   381,   384,   388,   399,   408,   408,
     423,   423,   440,   440,   449,   450,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   512,   512,   521,   527,   533,   539,   545,   551,   557,
     563,   569,   575,   581,   587,   593,   599,   605,   611,   617,
     623,   623,   632,   635,   638,   641,   644,   650,   650,   659,
     659,   668,   668,   677,   677,   686,   692,   698,   704,   704,
     713,   713,   725,   725,   734,   735,   738,   739,   740,   741,
     742,   745,   745,   756,   762,   762,   775,   775,   788,   788,
     799,   800,   803,   804,   807,   807,   817,   818,   821,   822,
     823,   824,   825,   826,   827,   828,   829,   830,   831,   832,
     833,   834,   835,   836,   837,   838,   839,   840,   841,   844,
     844,   852,   853,   854,   855,   858,   858,   867,   867,   876,
     876,   885,   891,   891,   900,   906,   912,   918,   924,   930,
     936,   942,   948,   954,   954,   963,   969,   969,   978,   978,
     987,   987,   996,   996,  1007,  1008,  1010,  1012,  1012,  1031,
    1031,  1042,  1043,  1046,  1047,  1050,  1055,  1060,  1060,  1071,
    1072,  1075,  1076,  1077,  1080,  1085,  1092,  1092,  1105,  1105,
    1118,  1119,  1122,  1123,  1124,  1125,  1126,  1127,  1130,  1136,
    1142,  1148,  1148,  1159,  1160,  1163,  1164,  1167,  1167,  1177,
    1177,  1187,  1188,  1189,  1192,  1193,  1196,  1196,  1205,  1205,
    1214,  1214,  1226,  1227,  1230,  1231,  1232,  1233,  1234,  1235,
    1238,  1244,  1250,  1256,  1262,  1268,  1277,  1277,  1291,  1292,
    1295,  1296,  1303,  1303,  1329,  1329,  1340,  1341,  1345,  1346,
    1347,  1348,  1349,  1350,  1351,  1352,  1353,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,  1361,  1362,  1363,  1364,  1365,  1366,
    1367,  1368,  1369,  1370,  1371,  1372,  1373,  1374,  1375,  1376,
    1377,  1378,  1379,  1380,  1381,  1382,  1385,  1385,  1394,  1394,
    1403,  1403,  1412,  1412,  1421,  1421,  1432,  1432,  1440,  1441,
    1442,  1443,  1446,  1452,  1460,  1460,  1472,  1473,  1477,  1478,
    1481,  1481,  1489,  1490,  1493,  1494,  1495,  1496,  1497,  1498,
    1499,  1500,  1501,  1502,  1503,  1504,  1505,  1506,  1507,  1508,
    1509,  1510,  1511,  1512,  1513,  1514,  1515,  1516,  1517,  1518,
    1519,  1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,  1534,
    1534,  1548,  1548,  1557,  1558,  1561,  1562,  1567,  1567,  1582,
    1582,  1596,  1597,  1600,  1601,  1604,  1605,  1606,  1607,  1608,
    1609,  1610,  1611,  1612,  1613,  1616,  1618,  1624,  1626,  1626,
    1635,  1635,  1644,  1644,  1653,  1655,  1655,  1664,  1674,  1674,
    1687,  1688,  1693,  1694,  1699,  1699,  1711,  1711,  1723,  1724,
    1729,  1730,  1735,  1736,  1737,  1738,  1739,  1740,  1741,  1742,
    1743,  1746,  1748,  1748,  1757,  1759,  1761,  1767,  1776,  1776,
    1789,  1790,  1793,  1794,  1797,  1797,  1807,  1807,  1817,  1818,
    1821,  1822,  1823,  1824,  1825,  1826,  1827,  1830,  1830,  1839,
    1839,  1864,  1864,  1894,  1894,  1907,  1908,  1911,  1912,  1915,
    1915,  1927,  1927,  1939,  1940,  1943,  1944,  1945,  1946,  1947,
    1948,  1949,  1950,  1951,  1952,  1953,  1956,  1956,  1965,  1971,
    1971,  1980,  1986,  1995,  1995,  2006,  2007,  2010,  2011,  2014,
    2014,  2023,  2023,  2032,  2033,  2036,  2037,  2041,  2042,  2043,
    2044,  2045,  2046,  2047,  2048,  2049,  2050,  2051,  2054,  2054,
    2065,  2065,  2076,  2076,  2085,  2085,  2094,  2094,  2103,  2103,
    2112,  2112,  2126,  2126,  2137,  2138,  2141,  2141,  2153,  2153,
    2164,  2165,  2168,  2168,  2178,  2179,  2182,  2183,  2186,  2187,
    2188,  2189,  2190,  2191,  2192,  2195,  2197,  2197,  2206,  2215,
    2215,  2228,  2229,  2232,  2233,  2234,  2235,  2236,  2237,  2238,
    2239,  2240,  2243,  2243,  2251,  2252,  2253,  2256,  2262,  2262,
    2271,  2277,  2285,  2293,  2293,  2304,  2305,  2308,  2309,  2310,
    2311,  2312,  2315,  2315,  2324,  2324,  2336,  2336,  2349,  2350,
    2353,  2354,  2355,  2356,  2357,  2358,  2361,  2367,  2367,  2376,
    2382,  2382,  2392,  2392,  2405,  2405,  2415,  2416,  2419,  2420,
    2421,  2422,  2423,  2424,  2425,  2426,  2427,  2428,  2429,  2430,
    2431,  2432,  2433,  2434,  2435,  2436,  2439,  2446,  2446,  2455,
    2455,  2464,  2470,  2470,  2479,  2485,  2491,  2491,  2500,  2501,
    2504,  2504,  2514,  2521,  2528,  2528,  2537,  2537,  2547,  2547,
    2557,  2557,  2569,  2569,  2581,  2581,  2591,  2592,  2596,  2597,
    2600,  2600,  2611,  2619,  2619,  2632,  2633,  2637,  2637,  2645,
    2646,  2649,  2650,  2651,  2652,  2653,  2654,  2655,  2658,  2664,
    2664,  2673,  2673,  2684,  2685,  2688,  2688,  2696,  2697,  2700,
    2701,  2702,  2703,  2704,  2707,  2707,  2716,  2722,  2728,  2734,
    2734
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
#line 5771 "dhcp6_parser.cc"

#line 2743 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
