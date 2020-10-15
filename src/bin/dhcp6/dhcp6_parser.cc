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
#line 282 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 400 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 282 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 406 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 282 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 412 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 282 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 418 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 282 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 424 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 282 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 430 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 282 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 436 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 282 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 442 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 282 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 448 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 282 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 454 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 282 "dhcp6_parser.yy"
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
#line 291 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 739 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 292 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 745 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 293 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 751 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 294 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 757 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 295 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 763 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 296 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 769 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 297 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 775 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 298 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 781 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 299 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 787 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 300 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 793 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 301 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 799 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 302 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 805 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 303 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 811 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 304 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 817 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 312 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 313 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 314 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 315 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 316 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 847 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 317 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 318 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 859 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 321 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 868 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 326 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 879 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 331 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 889 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 337 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 344 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 905 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 349 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 45: // $@16: %empty
#line 357 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 925 "dhcp6_parser.cc"
    break;

  case 46: // list_generic: "[" $@16 list_content "]"
#line 360 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 933 "dhcp6_parser.cc"
    break;

  case 49: // not_empty_list: value
#line 368 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 942 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list "," value
#line 372 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp6_parser.cc"
    break;

  case 51: // $@17: %empty
#line 379 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 959 "dhcp6_parser.cc"
    break;

  case 52: // list_strings: "[" $@17 list_strings_content "]"
#line 381 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 968 "dhcp6_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 390 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 977 "dhcp6_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 394 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 986 "dhcp6_parser.cc"
    break;

  case 57: // unknown_map_entry: "constant string" ":"
#line 405 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 997 "dhcp6_parser.cc"
    break;

  case 58: // $@18: %empty
#line 414 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1008 "dhcp6_parser.cc"
    break;

  case 59: // syntax_map: "{" $@18 global_object "}"
#line 419 "dhcp6_parser.yy"
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
#line 1036 "dhcp6_parser.cc"
    break;

  case 61: // global_object: "Dhcp6" $@19 ":" "{" global_params "}"
#line 438 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp6_parser.cc"
    break;

  case 62: // $@20: %empty
#line 446 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp6_parser.cc"
    break;

  case 63: // sub_dhcp6: "{" $@20 global_params "}"
#line 450 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1065 "dhcp6_parser.cc"
    break;

  case 126: // $@21: %empty
#line 523 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1074 "dhcp6_parser.cc"
    break;

  case 127: // data_directory: "data-directory" $@21 ":" "constant string"
#line 526 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1084 "dhcp6_parser.cc"
    break;

  case 128: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 532 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1094 "dhcp6_parser.cc"
    break;

  case 129: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 538 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 130: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 544 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1114 "dhcp6_parser.cc"
    break;

  case 131: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 550 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 132: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 556 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1134 "dhcp6_parser.cc"
    break;

  case 133: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 562 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1144 "dhcp6_parser.cc"
    break;

  case 134: // renew_timer: "renew-timer" ":" "integer"
#line 568 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1154 "dhcp6_parser.cc"
    break;

  case 135: // rebind_timer: "rebind-timer" ":" "integer"
#line 574 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1164 "dhcp6_parser.cc"
    break;

  case 136: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 580 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1174 "dhcp6_parser.cc"
    break;

  case 137: // t1_percent: "t1-percent" ":" "floating point"
#line 586 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1184 "dhcp6_parser.cc"
    break;

  case 138: // t2_percent: "t2-percent" ":" "floating point"
#line 592 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1194 "dhcp6_parser.cc"
    break;

  case 139: // cache_threshold: "cache-threshold" ":" "floating point"
#line 598 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1204 "dhcp6_parser.cc"
    break;

  case 140: // cache_max_age: "cache-max-age" ":" "integer"
#line 604 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1214 "dhcp6_parser.cc"
    break;

  case 141: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 610 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 142: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 616 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1234 "dhcp6_parser.cc"
    break;

  case 143: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 622 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1244 "dhcp6_parser.cc"
    break;

  case 144: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 628 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1254 "dhcp6_parser.cc"
    break;

  case 145: // $@22: %empty
#line 634 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 146: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 637 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 147: // ddns_replace_client_name_value: "when-present"
#line 643 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1280 "dhcp6_parser.cc"
    break;

  case 148: // ddns_replace_client_name_value: "never"
#line 646 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1288 "dhcp6_parser.cc"
    break;

  case 149: // ddns_replace_client_name_value: "always"
#line 649 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1296 "dhcp6_parser.cc"
    break;

  case 150: // ddns_replace_client_name_value: "when-not-present"
#line 652 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1304 "dhcp6_parser.cc"
    break;

  case 151: // ddns_replace_client_name_value: "boolean"
#line 655 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1313 "dhcp6_parser.cc"
    break;

  case 152: // $@23: %empty
#line 661 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp6_parser.cc"
    break;

  case 153: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 664 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1332 "dhcp6_parser.cc"
    break;

  case 154: // $@24: %empty
#line 670 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp6_parser.cc"
    break;

  case 155: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 673 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc"
    break;

  case 156: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 679 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1361 "dhcp6_parser.cc"
    break;

  case 157: // $@25: %empty
#line 685 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1370 "dhcp6_parser.cc"
    break;

  case 158: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 688 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1380 "dhcp6_parser.cc"
    break;

  case 159: // $@26: %empty
#line 694 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 160: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 697 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 161: // store_extended_info: "store-extended-info" ":" "boolean"
#line 703 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1409 "dhcp6_parser.cc"
    break;

  case 162: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 709 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 163: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 715 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1429 "dhcp6_parser.cc"
    break;

  case 164: // $@27: %empty
#line 721 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1438 "dhcp6_parser.cc"
    break;

  case 165: // server_tag: "server-tag" $@27 ":" "constant string"
#line 724 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1448 "dhcp6_parser.cc"
    break;

  case 166: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 730 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1458 "dhcp6_parser.cc"
    break;

  case 167: // $@28: %empty
#line 736 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 168: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 742 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 169: // $@29: %empty
#line 748 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 170: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 752 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 178: // $@30: %empty
#line 768 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 179: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 774 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1520 "dhcp6_parser.cc"
    break;

  case 180: // re_detect: "re-detect" ":" "boolean"
#line 779 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1530 "dhcp6_parser.cc"
    break;

  case 181: // $@31: %empty
#line 785 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1542 "dhcp6_parser.cc"
    break;

  case 182: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 791 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1553 "dhcp6_parser.cc"
    break;

  case 183: // $@32: %empty
#line 798 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1565 "dhcp6_parser.cc"
    break;

  case 184: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 804 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1576 "dhcp6_parser.cc"
    break;

  case 185: // $@33: %empty
#line 811 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1588 "dhcp6_parser.cc"
    break;

  case 186: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 817 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1597 "dhcp6_parser.cc"
    break;

  case 191: // $@34: %empty
#line 830 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1607 "dhcp6_parser.cc"
    break;

  case 192: // database: "{" $@34 database_map_params "}"
#line 834 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1617 "dhcp6_parser.cc"
    break;

  case 216: // $@35: %empty
#line 867 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1626 "dhcp6_parser.cc"
    break;

  case 217: // database_type: "type" $@35 ":" db_type
#line 870 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1635 "dhcp6_parser.cc"
    break;

  case 218: // db_type: "memfile"
#line 875 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1641 "dhcp6_parser.cc"
    break;

  case 219: // db_type: "mysql"
#line 876 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1647 "dhcp6_parser.cc"
    break;

  case 220: // db_type: "postgresql"
#line 877 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1653 "dhcp6_parser.cc"
    break;

  case 221: // db_type: "cql"
#line 878 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1659 "dhcp6_parser.cc"
    break;

  case 222: // $@36: %empty
#line 881 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 223: // user: "user" $@36 ":" "constant string"
#line 884 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1678 "dhcp6_parser.cc"
    break;

  case 224: // $@37: %empty
#line 890 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1687 "dhcp6_parser.cc"
    break;

  case 225: // password: "password" $@37 ":" "constant string"
#line 893 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1697 "dhcp6_parser.cc"
    break;

  case 226: // $@38: %empty
#line 899 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1706 "dhcp6_parser.cc"
    break;

  case 227: // host: "host" $@38 ":" "constant string"
#line 902 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1716 "dhcp6_parser.cc"
    break;

  case 228: // port: "port" ":" "integer"
#line 908 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1726 "dhcp6_parser.cc"
    break;

  case 229: // $@39: %empty
#line 914 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1735 "dhcp6_parser.cc"
    break;

  case 230: // name: "name" $@39 ":" "constant string"
#line 917 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1745 "dhcp6_parser.cc"
    break;

  case 231: // persist: "persist" ":" "boolean"
#line 923 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 232: // lfc_interval: "lfc-interval" ":" "integer"
#line 929 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1765 "dhcp6_parser.cc"
    break;

  case 233: // readonly: "readonly" ":" "boolean"
#line 935 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1775 "dhcp6_parser.cc"
    break;

  case 234: // connect_timeout: "connect-timeout" ":" "integer"
#line 941 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1785 "dhcp6_parser.cc"
    break;

  case 235: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 947 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1795 "dhcp6_parser.cc"
    break;

  case 236: // max_row_errors: "max-row-errors" ":" "integer"
#line 953 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1805 "dhcp6_parser.cc"
    break;

  case 237: // request_timeout: "request-timeout" ":" "integer"
#line 959 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1815 "dhcp6_parser.cc"
    break;

  case 238: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 965 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 239: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 971 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1835 "dhcp6_parser.cc"
    break;

  case 240: // $@40: %empty
#line 977 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 241: // contact_points: "contact-points" $@40 ":" "constant string"
#line 980 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1854 "dhcp6_parser.cc"
    break;

  case 242: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 986 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1864 "dhcp6_parser.cc"
    break;

  case 243: // $@41: %empty
#line 992 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1873 "dhcp6_parser.cc"
    break;

  case 244: // keyspace: "keyspace" $@41 ":" "constant string"
#line 995 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc"
    break;

  case 245: // $@42: %empty
#line 1001 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1892 "dhcp6_parser.cc"
    break;

  case 246: // consistency: "consistency" $@42 ":" "constant string"
#line 1004 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1902 "dhcp6_parser.cc"
    break;

  case 247: // $@43: %empty
#line 1010 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1911 "dhcp6_parser.cc"
    break;

  case 248: // serial_consistency: "serial-consistency" $@43 ":" "constant string"
#line 1013 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc"
    break;

  case 249: // $@44: %empty
#line 1019 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1933 "dhcp6_parser.cc"
    break;

  case 250: // sanity_checks: "sanity-checks" $@44 ":" "{" sanity_checks_params "}"
#line 1025 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1942 "dhcp6_parser.cc"
    break;

  case 254: // $@45: %empty
#line 1035 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1951 "dhcp6_parser.cc"
    break;

  case 255: // lease_checks: "lease-checks" $@45 ":" "constant string"
#line 1038 "dhcp6_parser.yy"
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
#line 1971 "dhcp6_parser.cc"
    break;

  case 256: // $@46: %empty
#line 1054 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 257: // mac_sources: "mac-sources" $@46 ":" "[" mac_sources_list "]"
#line 1060 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1992 "dhcp6_parser.cc"
    break;

  case 262: // duid_id: "duid"
#line 1073 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2001 "dhcp6_parser.cc"
    break;

  case 263: // string_id: "constant string"
#line 1078 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2010 "dhcp6_parser.cc"
    break;

  case 264: // $@47: %empty
#line 1083 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2022 "dhcp6_parser.cc"
    break;

  case 265: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1089 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2031 "dhcp6_parser.cc"
    break;

  case 271: // hw_address_id: "hw-address"
#line 1103 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2040 "dhcp6_parser.cc"
    break;

  case 272: // flex_id: "flex-id"
#line 1108 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2049 "dhcp6_parser.cc"
    break;

  case 273: // $@48: %empty
#line 1115 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2061 "dhcp6_parser.cc"
    break;

  case 274: // relay_supplied_options: "relay-supplied-options" $@48 ":" "[" list_content "]"
#line 1121 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2070 "dhcp6_parser.cc"
    break;

  case 275: // $@49: %empty
#line 1128 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2082 "dhcp6_parser.cc"
    break;

  case 276: // dhcp_multi_threading: "multi-threading" $@49 ":" "{" multi_threading_params "}"
#line 1134 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 285: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1153 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2103 "dhcp6_parser.cc"
    break;

  case 286: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1159 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2113 "dhcp6_parser.cc"
    break;

  case 287: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1165 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2123 "dhcp6_parser.cc"
    break;

  case 288: // $@50: %empty
#line 1171 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2135 "dhcp6_parser.cc"
    break;

  case 289: // hooks_libraries: "hooks-libraries" $@50 ":" "[" hooks_libraries_list "]"
#line 1177 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc"
    break;

  case 294: // $@51: %empty
#line 1190 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2154 "dhcp6_parser.cc"
    break;

  case 295: // hooks_library: "{" $@51 hooks_params "}"
#line 1194 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 296: // $@52: %empty
#line 1200 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2174 "dhcp6_parser.cc"
    break;

  case 297: // sub_hooks_library: "{" $@52 hooks_params "}"
#line 1204 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2184 "dhcp6_parser.cc"
    break;

  case 303: // $@53: %empty
#line 1219 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2193 "dhcp6_parser.cc"
    break;

  case 304: // library: "library" $@53 ":" "constant string"
#line 1222 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2203 "dhcp6_parser.cc"
    break;

  case 305: // $@54: %empty
#line 1228 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp6_parser.cc"
    break;

  case 306: // parameters: "parameters" $@54 ":" map_value
#line 1231 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 307: // $@55: %empty
#line 1237 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2233 "dhcp6_parser.cc"
    break;

  case 308: // expired_leases_processing: "expired-leases-processing" $@55 ":" "{" expired_leases_params "}"
#line 1243 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2243 "dhcp6_parser.cc"
    break;

  case 317: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1261 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2253 "dhcp6_parser.cc"
    break;

  case 318: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1267 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2263 "dhcp6_parser.cc"
    break;

  case 319: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1273 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2273 "dhcp6_parser.cc"
    break;

  case 320: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1279 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2283 "dhcp6_parser.cc"
    break;

  case 321: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1285 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2293 "dhcp6_parser.cc"
    break;

  case 322: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1291 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2303 "dhcp6_parser.cc"
    break;

  case 323: // $@56: %empty
#line 1300 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2315 "dhcp6_parser.cc"
    break;

  case 324: // subnet6_list: "subnet6" $@56 ":" "[" subnet6_list_content "]"
#line 1306 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2324 "dhcp6_parser.cc"
    break;

  case 329: // $@57: %empty
#line 1326 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2334 "dhcp6_parser.cc"
    break;

  case 330: // subnet6: "{" $@57 subnet6_params "}"
#line 1330 "dhcp6_parser.yy"
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
#line 2360 "dhcp6_parser.cc"
    break;

  case 331: // $@58: %empty
#line 1352 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2370 "dhcp6_parser.cc"
    break;

  case 332: // sub_subnet6: "{" $@58 subnet6_params "}"
#line 1356 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2380 "dhcp6_parser.cc"
    break;

  case 377: // $@59: %empty
#line 1412 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2389 "dhcp6_parser.cc"
    break;

  case 378: // subnet: "subnet" $@59 ":" "constant string"
#line 1415 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2399 "dhcp6_parser.cc"
    break;

  case 379: // $@60: %empty
#line 1421 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2408 "dhcp6_parser.cc"
    break;

  case 380: // interface: "interface" $@60 ":" "constant string"
#line 1424 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2418 "dhcp6_parser.cc"
    break;

  case 381: // $@61: %empty
#line 1430 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2427 "dhcp6_parser.cc"
    break;

  case 382: // interface_id: "interface-id" $@61 ":" "constant string"
#line 1433 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2437 "dhcp6_parser.cc"
    break;

  case 383: // $@62: %empty
#line 1439 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp6_parser.cc"
    break;

  case 384: // client_class: "client-class" $@62 ":" "constant string"
#line 1442 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc"
    break;

  case 385: // $@63: %empty
#line 1448 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2468 "dhcp6_parser.cc"
    break;

  case 386: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1454 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2477 "dhcp6_parser.cc"
    break;

  case 387: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1459 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2487 "dhcp6_parser.cc"
    break;

  case 388: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1465 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2497 "dhcp6_parser.cc"
    break;

  case 389: // reservations_global: "reservations-global" ":" "boolean"
#line 1471 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2507 "dhcp6_parser.cc"
    break;

  case 390: // $@64: %empty
#line 1477 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2516 "dhcp6_parser.cc"
    break;

  case 391: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1480 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 392: // hr_mode: "disabled"
#line 1485 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2531 "dhcp6_parser.cc"
    break;

  case 393: // hr_mode: "out-of-pool"
#line 1486 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2537 "dhcp6_parser.cc"
    break;

  case 394: // hr_mode: "global"
#line 1487 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2543 "dhcp6_parser.cc"
    break;

  case 395: // hr_mode: "all"
#line 1488 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2549 "dhcp6_parser.cc"
    break;

  case 396: // id: "id" ":" "integer"
#line 1491 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2559 "dhcp6_parser.cc"
    break;

  case 397: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1497 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2569 "dhcp6_parser.cc"
    break;

  case 398: // $@65: %empty
#line 1505 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2581 "dhcp6_parser.cc"
    break;

  case 399: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1511 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2590 "dhcp6_parser.cc"
    break;

  case 404: // $@66: %empty
#line 1526 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 405: // shared_network: "{" $@66 shared_network_params "}"
#line 1530 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2608 "dhcp6_parser.cc"
    break;

  case 447: // $@67: %empty
#line 1583 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2620 "dhcp6_parser.cc"
    break;

  case 448: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1589 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2629 "dhcp6_parser.cc"
    break;

  case 449: // $@68: %empty
#line 1597 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 450: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1600 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2646 "dhcp6_parser.cc"
    break;

  case 455: // $@69: %empty
#line 1616 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2656 "dhcp6_parser.cc"
    break;

  case 456: // option_def_entry: "{" $@69 option_def_params "}"
#line 1620 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2668 "dhcp6_parser.cc"
    break;

  case 457: // $@70: %empty
#line 1631 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2678 "dhcp6_parser.cc"
    break;

  case 458: // sub_option_def: "{" $@70 option_def_params "}"
#line 1635 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2690 "dhcp6_parser.cc"
    break;

  case 474: // code: "code" ":" "integer"
#line 1667 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2700 "dhcp6_parser.cc"
    break;

  case 476: // $@71: %empty
#line 1675 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2709 "dhcp6_parser.cc"
    break;

  case 477: // option_def_type: "type" $@71 ":" "constant string"
#line 1678 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2719 "dhcp6_parser.cc"
    break;

  case 478: // $@72: %empty
#line 1684 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2728 "dhcp6_parser.cc"
    break;

  case 479: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1687 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2738 "dhcp6_parser.cc"
    break;

  case 480: // $@73: %empty
#line 1693 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2747 "dhcp6_parser.cc"
    break;

  case 481: // space: "space" $@73 ":" "constant string"
#line 1696 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2757 "dhcp6_parser.cc"
    break;

  case 483: // $@74: %empty
#line 1704 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2766 "dhcp6_parser.cc"
    break;

  case 484: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1707 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 485: // option_def_array: "array" ":" "boolean"
#line 1713 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 486: // $@75: %empty
#line 1723 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2798 "dhcp6_parser.cc"
    break;

  case 487: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1729 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2807 "dhcp6_parser.cc"
    break;

  case 492: // $@76: %empty
#line 1748 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2817 "dhcp6_parser.cc"
    break;

  case 493: // option_data_entry: "{" $@76 option_data_params "}"
#line 1752 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2826 "dhcp6_parser.cc"
    break;

  case 494: // $@77: %empty
#line 1760 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2836 "dhcp6_parser.cc"
    break;

  case 495: // sub_option_data: "{" $@77 option_data_params "}"
#line 1764 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2845 "dhcp6_parser.cc"
    break;

  case 510: // $@78: %empty
#line 1797 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2854 "dhcp6_parser.cc"
    break;

  case 511: // option_data_data: "data" $@78 ":" "constant string"
#line 1800 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2864 "dhcp6_parser.cc"
    break;

  case 514: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1810 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2874 "dhcp6_parser.cc"
    break;

  case 515: // option_data_always_send: "always-send" ":" "boolean"
#line 1816 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2884 "dhcp6_parser.cc"
    break;

  case 516: // $@79: %empty
#line 1825 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2896 "dhcp6_parser.cc"
    break;

  case 517: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1831 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 522: // $@80: %empty
#line 1846 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2915 "dhcp6_parser.cc"
    break;

  case 523: // pool_list_entry: "{" $@80 pool_params "}"
#line 1850 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 524: // $@81: %empty
#line 1856 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2935 "dhcp6_parser.cc"
    break;

  case 525: // sub_pool6: "{" $@81 pool_params "}"
#line 1860 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2945 "dhcp6_parser.cc"
    break;

  case 535: // $@82: %empty
#line 1879 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2954 "dhcp6_parser.cc"
    break;

  case 536: // pool_entry: "pool" $@82 ":" "constant string"
#line 1882 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2964 "dhcp6_parser.cc"
    break;

  case 537: // $@83: %empty
#line 1888 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2972 "dhcp6_parser.cc"
    break;

  case 538: // user_context: "user-context" $@83 ":" map_value
#line 1890 "dhcp6_parser.yy"
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
#line 2999 "dhcp6_parser.cc"
    break;

  case 539: // $@84: %empty
#line 1913 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3007 "dhcp6_parser.cc"
    break;

  case 540: // comment: "comment" $@84 ":" "constant string"
#line 1915 "dhcp6_parser.yy"
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
#line 3036 "dhcp6_parser.cc"
    break;

  case 541: // $@85: %empty
#line 1943 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3048 "dhcp6_parser.cc"
    break;

  case 542: // pd_pools_list: "pd-pools" $@85 ":" "[" pd_pools_list_content "]"
#line 1949 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3057 "dhcp6_parser.cc"
    break;

  case 547: // $@86: %empty
#line 1964 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3067 "dhcp6_parser.cc"
    break;

  case 548: // pd_pool_entry: "{" $@86 pd_pool_params "}"
#line 1968 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3079 "dhcp6_parser.cc"
    break;

  case 549: // $@87: %empty
#line 1976 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3089 "dhcp6_parser.cc"
    break;

  case 550: // sub_pd_pool: "{" $@87 pd_pool_params "}"
#line 1980 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3101 "dhcp6_parser.cc"
    break;

  case 564: // $@88: %empty
#line 2005 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3110 "dhcp6_parser.cc"
    break;

  case 565: // pd_prefix: "prefix" $@88 ":" "constant string"
#line 2008 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3120 "dhcp6_parser.cc"
    break;

  case 566: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2014 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 567: // $@89: %empty
#line 2020 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3139 "dhcp6_parser.cc"
    break;

  case 568: // excluded_prefix: "excluded-prefix" $@89 ":" "constant string"
#line 2023 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3149 "dhcp6_parser.cc"
    break;

  case 569: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2029 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3159 "dhcp6_parser.cc"
    break;

  case 570: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2035 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3169 "dhcp6_parser.cc"
    break;

  case 571: // $@90: %empty
#line 2044 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3181 "dhcp6_parser.cc"
    break;

  case 572: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2050 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3190 "dhcp6_parser.cc"
    break;

  case 577: // $@91: %empty
#line 2063 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3200 "dhcp6_parser.cc"
    break;

  case 578: // reservation: "{" $@91 reservation_params "}"
#line 2067 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3209 "dhcp6_parser.cc"
    break;

  case 579: // $@92: %empty
#line 2072 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3219 "dhcp6_parser.cc"
    break;

  case 580: // sub_reservation: "{" $@92 reservation_params "}"
#line 2076 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3228 "dhcp6_parser.cc"
    break;

  case 596: // $@93: %empty
#line 2103 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3240 "dhcp6_parser.cc"
    break;

  case 597: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2109 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3249 "dhcp6_parser.cc"
    break;

  case 598: // $@94: %empty
#line 2114 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3261 "dhcp6_parser.cc"
    break;

  case 599: // prefixes: "prefixes" $@94 ":" list_strings
#line 2120 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3270 "dhcp6_parser.cc"
    break;

  case 600: // $@95: %empty
#line 2125 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3279 "dhcp6_parser.cc"
    break;

  case 601: // duid: "duid" $@95 ":" "constant string"
#line 2128 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3289 "dhcp6_parser.cc"
    break;

  case 602: // $@96: %empty
#line 2134 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3298 "dhcp6_parser.cc"
    break;

  case 603: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2137 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3308 "dhcp6_parser.cc"
    break;

  case 604: // $@97: %empty
#line 2143 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3317 "dhcp6_parser.cc"
    break;

  case 605: // hostname: "hostname" $@97 ":" "constant string"
#line 2146 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3327 "dhcp6_parser.cc"
    break;

  case 606: // $@98: %empty
#line 2152 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3336 "dhcp6_parser.cc"
    break;

  case 607: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2155 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3346 "dhcp6_parser.cc"
    break;

  case 608: // $@99: %empty
#line 2161 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3358 "dhcp6_parser.cc"
    break;

  case 609: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2167 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3367 "dhcp6_parser.cc"
    break;

  case 610: // $@100: %empty
#line 2175 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3379 "dhcp6_parser.cc"
    break;

  case 611: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2181 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3388 "dhcp6_parser.cc"
    break;

  case 614: // $@101: %empty
#line 2190 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3397 "dhcp6_parser.cc"
    break;

  case 615: // ip_address: "ip-address" $@101 ":" "constant string"
#line 2193 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3407 "dhcp6_parser.cc"
    break;

  case 616: // $@102: %empty
#line 2202 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3419 "dhcp6_parser.cc"
    break;

  case 617: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2208 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3428 "dhcp6_parser.cc"
    break;

  case 620: // $@103: %empty
#line 2217 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 621: // client_class_entry: "{" $@103 client_class_params "}"
#line 2221 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 634: // $@104: %empty
#line 2246 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3457 "dhcp6_parser.cc"
    break;

  case 635: // client_class_test: "test" $@104 ":" "constant string"
#line 2249 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 636: // only_if_required: "only-if-required" ":" "boolean"
#line 2255 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3477 "dhcp6_parser.cc"
    break;

  case 637: // $@105: %empty
#line 2264 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3489 "dhcp6_parser.cc"
    break;

  case 638: // server_id: "server-id" $@105 ":" "{" server_id_params "}"
#line 2270 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3500 "dhcp6_parser.cc"
    break;

  case 650: // $@106: %empty
#line 2292 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3509 "dhcp6_parser.cc"
    break;

  case 651: // server_id_type: "type" $@106 ":" duid_type
#line 2295 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 652: // duid_type: "LLT"
#line 2300 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3524 "dhcp6_parser.cc"
    break;

  case 653: // duid_type: "EN"
#line 2301 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3530 "dhcp6_parser.cc"
    break;

  case 654: // duid_type: "LL"
#line 2302 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3536 "dhcp6_parser.cc"
    break;

  case 655: // htype: "htype" ":" "integer"
#line 2305 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3546 "dhcp6_parser.cc"
    break;

  case 656: // $@107: %empty
#line 2311 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 657: // identifier: "identifier" $@107 ":" "constant string"
#line 2314 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3565 "dhcp6_parser.cc"
    break;

  case 658: // time: "time" ":" "integer"
#line 2320 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3575 "dhcp6_parser.cc"
    break;

  case 659: // enterprise_id: "enterprise-id" ":" "integer"
#line 2326 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3585 "dhcp6_parser.cc"
    break;

  case 660: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2334 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3595 "dhcp6_parser.cc"
    break;

  case 661: // $@108: %empty
#line 2342 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3607 "dhcp6_parser.cc"
    break;

  case 662: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2348 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 670: // $@109: %empty
#line 2364 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3625 "dhcp6_parser.cc"
    break;

  case 671: // socket_type: "socket-type" $@109 ":" "constant string"
#line 2367 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3635 "dhcp6_parser.cc"
    break;

  case 672: // $@110: %empty
#line 2373 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3644 "dhcp6_parser.cc"
    break;

  case 673: // socket_name: "socket-name" $@110 ":" "constant string"
#line 2376 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3654 "dhcp6_parser.cc"
    break;

  case 674: // $@111: %empty
#line 2385 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3666 "dhcp6_parser.cc"
    break;

  case 675: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2391 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3677 "dhcp6_parser.cc"
    break;

  case 684: // enable_queue: "enable-queue" ":" "boolean"
#line 2410 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 685: // $@112: %empty
#line 2416 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3696 "dhcp6_parser.cc"
    break;

  case 686: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2419 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 687: // capacity: "capacity" ":" "integer"
#line 2425 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3716 "dhcp6_parser.cc"
    break;

  case 688: // $@113: %empty
#line 2431 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3725 "dhcp6_parser.cc"
    break;

  case 689: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2434 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3734 "dhcp6_parser.cc"
    break;

  case 690: // $@114: %empty
#line 2441 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3746 "dhcp6_parser.cc"
    break;

  case 691: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2447 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 692: // $@115: %empty
#line 2454 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 693: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2458 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3777 "dhcp6_parser.cc"
    break;

  case 714: // enable_updates: "enable-updates" ":" "boolean"
#line 2488 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3787 "dhcp6_parser.cc"
    break;

  case 715: // $@116: %empty
#line 2495 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3796 "dhcp6_parser.cc"
    break;

  case 716: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2498 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3806 "dhcp6_parser.cc"
    break;

  case 717: // $@117: %empty
#line 2504 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3815 "dhcp6_parser.cc"
    break;

  case 718: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2507 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3825 "dhcp6_parser.cc"
    break;

  case 719: // server_port: "server-port" ":" "integer"
#line 2513 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3835 "dhcp6_parser.cc"
    break;

  case 720: // $@118: %empty
#line 2519 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3844 "dhcp6_parser.cc"
    break;

  case 721: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2522 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 722: // sender_port: "sender-port" ":" "integer"
#line 2528 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3864 "dhcp6_parser.cc"
    break;

  case 723: // max_queue_size: "max-queue-size" ":" "integer"
#line 2534 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3874 "dhcp6_parser.cc"
    break;

  case 724: // $@119: %empty
#line 2540 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 725: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2543 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 726: // ncr_protocol_value: "UDP"
#line 2549 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3898 "dhcp6_parser.cc"
    break;

  case 727: // ncr_protocol_value: "TCP"
#line 2550 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3904 "dhcp6_parser.cc"
    break;

  case 728: // $@120: %empty
#line 2553 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3913 "dhcp6_parser.cc"
    break;

  case 729: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2556 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 730: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2563 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3933 "dhcp6_parser.cc"
    break;

  case 731: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2570 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3943 "dhcp6_parser.cc"
    break;

  case 732: // $@121: %empty
#line 2577 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3952 "dhcp6_parser.cc"
    break;

  case 733: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2580 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3961 "dhcp6_parser.cc"
    break;

  case 734: // $@122: %empty
#line 2586 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3970 "dhcp6_parser.cc"
    break;

  case 735: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2589 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3980 "dhcp6_parser.cc"
    break;

  case 736: // $@123: %empty
#line 2596 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3989 "dhcp6_parser.cc"
    break;

  case 737: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2599 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3999 "dhcp6_parser.cc"
    break;

  case 738: // $@124: %empty
#line 2606 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4008 "dhcp6_parser.cc"
    break;

  case 739: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2609 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4018 "dhcp6_parser.cc"
    break;

  case 740: // $@125: %empty
#line 2618 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4030 "dhcp6_parser.cc"
    break;

  case 741: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2624 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4040 "dhcp6_parser.cc"
    break;

  case 742: // $@126: %empty
#line 2630 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 743: // sub_config_control: "{" $@126 config_control_params "}"
#line 2634 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4059 "dhcp6_parser.cc"
    break;

  case 748: // $@127: %empty
#line 2649 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 749: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2655 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4080 "dhcp6_parser.cc"
    break;

  case 750: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2660 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4090 "dhcp6_parser.cc"
    break;

  case 751: // $@128: %empty
#line 2668 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4102 "dhcp6_parser.cc"
    break;

  case 752: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2674 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4111 "dhcp6_parser.cc"
    break;

  case 755: // $@129: %empty
#line 2686 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4121 "dhcp6_parser.cc"
    break;

  case 756: // logger_entry: "{" $@129 logger_params "}"
#line 2690 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4129 "dhcp6_parser.cc"
    break;

  case 766: // debuglevel: "debuglevel" ":" "integer"
#line 2707 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4139 "dhcp6_parser.cc"
    break;

  case 767: // $@130: %empty
#line 2713 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4148 "dhcp6_parser.cc"
    break;

  case 768: // severity: "severity" $@130 ":" "constant string"
#line 2716 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4158 "dhcp6_parser.cc"
    break;

  case 769: // $@131: %empty
#line 2722 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4170 "dhcp6_parser.cc"
    break;

  case 770: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2728 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4179 "dhcp6_parser.cc"
    break;

  case 773: // $@132: %empty
#line 2737 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4189 "dhcp6_parser.cc"
    break;

  case 774: // output_entry: "{" $@132 output_params_list "}"
#line 2741 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4197 "dhcp6_parser.cc"
    break;

  case 782: // $@133: %empty
#line 2756 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4206 "dhcp6_parser.cc"
    break;

  case 783: // output: "output" $@133 ":" "constant string"
#line 2759 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4216 "dhcp6_parser.cc"
    break;

  case 784: // flush: "flush" ":" "boolean"
#line 2765 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4226 "dhcp6_parser.cc"
    break;

  case 785: // maxsize: "maxsize" ":" "integer"
#line 2771 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4236 "dhcp6_parser.cc"
    break;

  case 786: // maxver: "maxver" ":" "integer"
#line 2777 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4246 "dhcp6_parser.cc"
    break;

  case 787: // $@134: %empty
#line 2783 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4255 "dhcp6_parser.cc"
    break;

  case 788: // pattern: "pattern" $@134 ":" "constant string"
#line 2786 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4265 "dhcp6_parser.cc"
    break;


#line 4269 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -959;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     199,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,    63,    33,    89,    99,   103,
     123,   126,   142,   185,   212,   221,   238,   253,   290,   294,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,    33,  -132,
      61,   116,    50,   534,   127,   225,   233,    53,   121,   283,
     -72,   633,   219,  -959,   110,   154,   295,   234,   302,  -959,
     312,  -959,  -959,  -959,  -959,  -959,  -959,   327,   358,   365,
     368,   378,   406,   412,   415,   420,   421,   424,   425,   428,
     429,  -959,   431,   434,   438,   440,   441,  -959,  -959,  -959,
     448,   450,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   456,
     460,   461,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,   464,  -959,  -959,  -959,  -959,  -959,  -959,   465,  -959,
     470,  -959,    92,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,   472,  -959,    94,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,   475,   476,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,    96,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,   106,  -959,  -959,  -959,  -959,  -959,   477,  -959,   481,
     484,  -959,  -959,  -959,  -959,  -959,  -959,   109,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,   326,   399,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,   363,  -959,  -959,   486,  -959,
    -959,  -959,   487,  -959,  -959,   393,   411,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     488,   489,  -959,  -959,  -959,  -959,   492,   491,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     129,  -959,  -959,  -959,   497,  -959,  -959,   499,  -959,   500,
     501,  -959,  -959,   502,   503,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,   140,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     504,   144,  -959,  -959,  -959,  -959,    33,    33,  -959,   309,
     508,  -959,   509,   513,   516,   518,   520,   521,   325,   333,
     335,   337,   339,   340,   343,   344,   328,   293,   346,   347,
     345,   349,   549,   354,   355,   356,   357,   359,   554,   558,
     560,   361,   362,   563,   564,   565,   566,   567,   568,   569,
     370,   371,   372,   573,   587,   588,   589,   590,   599,   600,
     602,   603,   407,   604,   606,   607,   608,   609,   610,   417,
     611,  -959,   116,  -959,   615,   418,    50,  -959,   619,   631,
     634,   635,   636,   435,   437,   638,   639,   640,   534,  -959,
     642,   127,  -959,   643,   449,   646,   457,   458,   225,  -959,
     648,   654,   657,   658,   659,   660,   661,  -959,   233,  -959,
     662,   663,   466,   670,   671,   672,   474,  -959,   121,   675,
     478,   479,  -959,   283,   676,   677,   146,  -959,   480,   681,
     682,   485,   684,   505,   506,   685,   686,   526,   527,   687,
     689,   716,   728,   633,  -959,   729,   532,   219,  -959,  -959,
    -959,   732,   730,   537,   735,   738,   744,   745,   734,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,   552,  -959,  -959,  -959,  -959,  -959,  -112,
     553,   555,  -959,  -959,   750,   752,   753,   754,   755,   559,
      87,  -959,  -959,  -959,   758,   760,   761,   762,   763,   765,
     766,   767,   768,  -959,   769,   770,   771,   772,   572,   579,
    -959,   776,  -959,   777,  -959,  -959,   778,   779,   584,   585,
     586,  -959,  -959,   777,   601,   794,  -959,   605,  -959,   612,
    -959,   613,  -959,  -959,  -959,   777,   777,   777,   614,   616,
     617,   618,  -959,   620,   621,  -959,   622,   623,   626,  -959,
    -959,   627,  -959,  -959,  -959,   628,   755,  -959,  -959,   629,
     630,  -959,   632,  -959,  -959,   176,   597,  -959,  -959,  -112,
     637,   641,   644,  -959,   798,  -959,  -959,    33,   116,  -959,
     219,    50,   247,   247,   797,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,   800,   803,   804,   805,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,   -77,    33,   -70,   696,
     809,   813,   825,   248,    64,   239,    60,    -7,   633,  -959,
    -959,   828,  -959,  -959,   829,   830,  -959,  -959,  -959,  -959,
    -959,   -79,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,   797,  -959,   150,   217,   236,  -959,  -959,  -959,  -959,
     835,   836,   837,   839,   840,  -959,   842,   843,  -959,  -959,
    -959,   844,   845,   846,   848,  -959,   249,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   259,  -959,
     847,   851,  -959,  -959,   849,   853,  -959,  -959,   852,   854,
    -959,  -959,   855,   856,  -959,  -959,   857,   859,  -959,  -959,
    -959,    62,  -959,  -959,  -959,   858,  -959,  -959,  -959,    75,
    -959,  -959,  -959,  -959,   261,  -959,  -959,  -959,   153,  -959,
    -959,   860,   862,  -959,  -959,   861,   865,  -959,   866,   867,
     868,   869,   870,   871,   292,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,   872,   873,   874,  -959,  -959,  -959,
    -959,   300,  -959,  -959,  -959,  -959,  -959,  -959,   875,   876,
     877,  -959,   324,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,   330,  -959,  -959,  -959,   878,  -959,
     879,  -959,  -959,  -959,   332,  -959,  -959,  -959,  -959,  -959,
     334,  -959,   250,  -959,   668,  -959,   880,   881,  -959,  -959,
     882,   884,  -959,  -959,  -959,   883,  -959,   886,  -959,  -959,
    -959,   885,   889,   890,   891,   683,   656,   688,   692,   695,
     894,   697,   698,   897,   898,   899,   702,   704,   703,   707,
     247,  -959,  -959,   247,  -959,   797,   534,  -959,   800,   121,
    -959,   803,   283,  -959,   804,   650,  -959,   805,   -77,  -959,
    -959,   -70,  -959,   906,   696,  -959,   235,   809,  -959,   233,
    -959,   813,   -72,  -959,   825,   711,   718,   720,   721,   736,
     737,   248,  -959,   928,   936,   749,   764,   783,    64,  -959,
     756,   786,   789,   239,  -959,   950,   975,    60,  -959,   788,
     991,   824,   995,    -7,  -959,  -959,    48,   828,  -959,  -959,
    1001,  1026,   127,  -959,   829,   225,  -959,   830,  1029,  -959,
    -959,   398,   834,   838,   841,  -959,  -959,  -959,  -959,  -959,
     850,  -959,  -959,   863,   864,   887,  -959,  -959,  -959,  -959,
    -959,   338,  -959,   360,  -959,  1030,  -959,  1032,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,   367,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,   893,  -959,  -959,  1037,  -959,  -959,  -959,
    -959,  -959,  1036,  1042,  -959,  -959,  -959,  -959,  -959,  1039,
    -959,   397,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     314,   896,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     900,   901,  -959,  -959,   902,  -959,    33,  -959,  -959,  1044,
    -959,  -959,  -959,  -959,  -959,   400,  -959,  -959,  -959,  -959,
    -959,  -959,   903,   401,  -959,   409,  -959,   904,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,   650,  -959,  -959,  1045,   895,  -959,
     235,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  1046,   888,  1048,    48,  -959,  -959,  -959,  -959,
    -959,  -959,   905,  -959,  -959,  1049,  -959,   907,  -959,  -959,
    1050,  -959,  -959,   315,  -959,   181,  1050,  -959,  -959,  1052,
    1055,  1056,  -959,   410,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  1057,   908,   909,   911,  1058,   181,  -959,   913,  -959,
    -959,  -959,   914,  -959,  -959,  -959
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   169,     9,   331,    11,
     524,    13,   549,    15,   579,    17,   449,    19,   457,    21,
     494,    23,   296,    25,   692,    27,   742,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   581,     0,   459,   496,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   126,   740,   167,   181,   183,   185,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   164,     0,     0,     0,     0,     0,   145,   152,   154,
       0,     0,   323,   447,   486,   398,   537,   539,   390,     0,
       0,     0,   256,   273,   264,   249,   616,   571,   288,   307,
     637,     0,   275,   661,   674,   690,   157,   159,     0,   751,
       0,   125,     0,    64,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   105,   106,   107,   108,   109,    75,   113,
     114,   115,   116,   117,   118,   119,   111,   112,   120,   121,
     122,   100,   124,    78,    79,    80,    81,    97,    82,    84,
      83,   123,    88,    89,    76,   102,   103,   104,   101,    77,
      86,    87,    95,    96,    98,    85,    90,    91,    92,    93,
      94,    99,   110,   178,     0,   177,     0,   171,   173,   174,
     175,   176,   516,   541,   377,   379,   381,     0,     0,   385,
     383,   610,   376,   335,   336,   337,   338,   339,   340,   341,
     342,   361,   362,   363,   364,   365,   368,   369,   370,   371,
     372,   373,   374,   366,   367,   375,     0,   333,   346,   347,
     348,   351,   352,   355,   356,   357,   354,   349,   350,   343,
     344,   359,   360,   345,   353,   358,   535,   534,   530,   531,
     529,     0,   526,   528,   532,   533,   564,     0,   567,     0,
       0,   563,   557,   558,   556,   561,   562,     0,   551,   553,
     554,   559,   560,   555,   608,   596,   598,   600,   602,   604,
     606,   595,   592,   593,   594,     0,   582,   583,   587,   588,
     585,   589,   590,   591,   586,     0,   476,   229,     0,   480,
     478,   483,     0,   472,   473,     0,   460,   461,   463,   475,
     464,   465,   466,   482,   467,   468,   469,   470,   471,   510,
       0,     0,   508,   509,   512,   513,     0,   497,   498,   500,
     501,   502,   503,   504,   505,   506,   507,   303,   305,   300,
       0,   298,   301,   302,     0,   715,   717,     0,   720,     0,
       0,   724,   728,     0,     0,   732,   734,   736,   738,   713,
     711,   712,     0,   694,   696,   708,   697,   698,   699,   700,
     701,   702,   703,   704,   705,   706,   707,   709,   710,   748,
       0,     0,   744,   746,   747,    46,     0,     0,    39,     0,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,     0,    63,     0,     0,     0,   170,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   332,
       0,     0,   525,     0,     0,     0,     0,     0,     0,   550,
       0,     0,     0,     0,     0,     0,     0,   580,     0,   450,
       0,     0,     0,     0,     0,     0,     0,   458,     0,     0,
       0,     0,   495,     0,     0,     0,     0,   297,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   693,     0,     0,     0,   743,    50,
      43,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,     0,   162,   163,   142,   143,   144,     0,
       0,     0,   156,   161,     0,     0,     0,     0,     0,     0,
       0,   387,   388,   389,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   660,     0,     0,     0,     0,     0,     0,
     166,     0,    65,     0,   180,   172,     0,     0,     0,     0,
       0,   396,   397,     0,     0,     0,   334,     0,   527,     0,
     566,     0,   569,   570,   552,     0,     0,     0,     0,     0,
       0,     0,   584,     0,     0,   474,     0,     0,     0,   485,
     462,     0,   514,   515,   499,     0,     0,   299,   714,     0,
       0,   719,     0,   722,   723,     0,     0,   730,   731,     0,
       0,     0,     0,   695,     0,   750,   745,     0,     0,   127,
       0,     0,     0,     0,   187,   165,   147,   148,   149,   150,
     151,   146,   153,   155,   325,   451,   488,   400,    40,   538,
     540,   392,   393,   394,   395,   391,     0,    47,     0,     0,
       0,   573,   290,     0,     0,     0,     0,     0,     0,   158,
     160,     0,    51,   179,   518,   543,   378,   380,   382,   386,
     384,     0,   536,   565,   568,   609,   597,   599,   601,   603,
     605,   607,   477,   230,   481,   479,   484,   511,   304,   306,
     716,   718,   721,   726,   727,   725,   729,   733,   735,   737,
     739,   187,    44,     0,     0,     0,   216,   222,   224,   226,
       0,     0,     0,     0,     0,   240,     0,     0,   243,   245,
     247,     0,     0,     0,     0,   215,     0,   193,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   207,   214,
     208,   209,   210,   205,   206,   211,   212,   213,     0,   191,
       0,   188,   189,   329,     0,   326,   327,   455,     0,   452,
     453,   492,     0,   489,   490,   404,     0,   401,   402,   262,
     263,     0,   258,   260,   261,     0,   271,   272,   268,     0,
     266,   269,   270,   254,     0,   251,   253,   620,     0,   618,
     577,     0,   574,   575,   294,     0,   291,   292,     0,     0,
       0,     0,     0,     0,     0,   309,   311,   312,   313,   314,
     315,   316,   650,   656,     0,     0,     0,   649,   646,   647,
     648,     0,   639,   641,   644,   642,   643,   645,     0,     0,
       0,   284,     0,   277,   279,   280,   281,   282,   283,   670,
     672,   669,   667,   668,     0,   663,   665,   666,     0,   685,
       0,   688,   681,   682,     0,   676,   678,   679,   680,   683,
       0,   755,     0,   753,    53,   522,     0,   519,   520,   547,
       0,   544,   545,   614,   613,     0,   612,     0,    61,   741,
     168,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   184,     0,   186,     0,     0,   324,     0,   459,
     448,     0,   496,   487,     0,     0,   399,     0,     0,   257,
     274,     0,   265,     0,     0,   250,   622,     0,   617,   581,
     572,     0,     0,   289,     0,     0,     0,     0,     0,     0,
       0,     0,   308,     0,     0,     0,     0,     0,     0,   638,
       0,     0,     0,     0,   276,     0,     0,     0,   662,     0,
       0,     0,     0,     0,   675,   691,     0,     0,   752,    55,
       0,    54,     0,   517,     0,     0,   542,     0,     0,   611,
     749,     0,     0,     0,     0,   228,   231,   232,   233,   234,
       0,   242,   235,     0,     0,     0,   237,   238,   239,   236,
     194,     0,   190,     0,   328,     0,   454,     0,   491,   446,
     422,   423,   424,   426,   427,   428,   412,   413,   431,   432,
     433,   434,   435,   438,   439,   440,   441,   442,   443,   444,
     436,   437,   445,   408,   409,   410,   411,   420,   421,   417,
     418,   419,   416,   425,     0,   406,   414,   429,   430,   415,
     403,   259,   267,     0,   252,   634,     0,   632,   633,   629,
     630,   631,     0,   623,   624,   626,   627,   628,   619,     0,
     576,     0,   293,   317,   318,   319,   320,   321,   322,   310,
       0,     0,   655,   658,   659,   640,   285,   286,   287,   278,
       0,     0,   664,   684,     0,   687,     0,   677,   769,     0,
     767,   765,   759,   763,   764,     0,   757,   761,   762,   760,
     754,    52,     0,     0,   521,     0,   546,     0,   218,   219,
     220,   221,   217,   223,   225,   227,   241,   244,   246,   248,
     192,   330,   456,   493,     0,   405,   255,     0,     0,   621,
       0,   578,   295,   652,   653,   654,   651,   657,   671,   673,
     686,   689,     0,     0,     0,     0,   756,    56,   523,   548,
     615,   407,     0,   636,   625,     0,   766,     0,   758,   635,
       0,   768,   773,     0,   771,     0,     0,   770,   782,     0,
       0,     0,   787,     0,   775,   777,   778,   779,   780,   781,
     772,     0,     0,     0,     0,     0,     0,   774,     0,   784,
     785,   786,     0,   776,   783,   788
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,   -10,  -959,  -559,  -959,
     387,  -959,  -959,  -959,  -959,   350,  -959,  -590,  -959,  -959,
    -959,   -71,  -959,  -959,  -959,  -959,  -959,  -959,   375,   591,
    -959,  -959,   -59,   -43,   -42,   -40,   -39,   -28,   -27,   -26,
     -23,   -21,   -15,    -9,    -3,  -959,    -1,    17,    18,    20,
    -959,   389,    25,  -959,    28,  -959,    30,    32,  -959,    35,
    -959,    38,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,   379,   580,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,   298,  -959,    97,  -959,  -671,   101,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   -67,  -959,
    -709,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,    80,  -959,  -959,  -959,  -959,  -959,    88,  -693,  -959,
    -959,  -959,  -959,    84,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,    54,  -959,  -959,  -959,  -959,  -959,  -959,  -959,    74,
    -959,  -959,  -959,    77,   544,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,    70,  -959,  -959,  -959,  -959,  -959,  -959,  -958,
    -959,  -959,  -959,   104,  -959,  -959,  -959,   107,   593,  -959,
    -959,  -957,  -959,  -956,  -959,    47,  -959,    51,  -959,    40,
      42,    45,    46,  -959,  -959,  -959,  -950,  -959,  -959,  -959,
    -959,    98,  -959,  -959,  -120,  1009,  -959,  -959,  -959,  -959,
    -959,   114,  -959,  -959,  -959,   108,  -959,   570,  -959,   -66,
    -959,  -959,  -959,  -959,  -959,   -47,  -959,  -959,  -959,  -959,
    -959,    13,  -959,  -959,  -959,   125,  -959,  -959,  -959,   118,
    -959,   574,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,    66,  -959,  -959,  -959,    76,   624,  -959,
    -959,   -55,  -959,     1,  -959,  -959,  -959,  -959,  -959,    69,
    -959,  -959,  -959,    72,   645,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,   -57,  -959,  -959,  -959,   119,  -959,  -959,  -959,
     120,  -959,   649,   380,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -949,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,   130,  -959,  -959,  -959,   -88,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,   105,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     102,  -959,  -959,  -959,  -959,  -959,  -959,  -959,    91,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   402,
     575,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     436,   577,  -959,  -959,  -959,  -959,  -959,  -959,    95,  -959,
    -959,   -94,  -959,  -959,  -959,  -959,  -959,  -959,  -111,  -959,
    -959,  -130,  -959,  -959,  -959,  -959,  -959,  -959,  -959
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     709,    87,    88,    41,    68,    84,    85,   733,   934,  1040,
    1041,   795,    43,    70,    90,   420,    45,    71,   152,   153,
     154,   422,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     448,   701,   173,   449,   174,   450,   175,   176,   477,   177,
     478,   178,   179,   180,   181,   442,   182,   183,   424,    47,
      72,   216,   217,   218,   484,   219,   184,   425,   185,   426,
     186,   427,   820,   821,   822,   973,   796,   797,   798,   951,
    1192,   799,   952,   800,   953,   801,   954,   802,   803,   521,
     804,   805,   806,   807,   808,   809,   810,   811,   812,   813,
     960,   814,   815,   963,   816,   964,   817,   965,   187,   466,
     854,   855,   856,   993,   188,   463,   841,   842,   843,   844,
     189,   465,   849,   850,   851,   852,   190,   464,   191,   473,
     902,   903,   904,   905,   906,   192,   469,   865,   866,   867,
    1002,    63,    80,   370,   371,   372,   534,   373,   535,   193,
     470,   874,   875,   876,   877,   878,   879,   880,   881,   194,
     453,   824,   825,   826,   976,    49,    73,   256,   257,   258,
     490,   259,   491,   260,   492,   261,   496,   262,   495,   195,
     196,   197,   198,   459,   715,   267,   268,   199,   456,   836,
     837,   838,   985,  1114,  1115,   200,   454,    57,    77,   828,
     829,   830,   979,    59,    78,   335,   336,   337,   338,   339,
     340,   341,   520,   342,   524,   343,   523,   344,   345,   525,
     346,   201,   455,   832,   833,   834,   982,    61,    79,   356,
     357,   358,   359,   360,   529,   361,   362,   363,   364,   270,
     488,   936,   937,   938,  1042,    51,    74,   281,   282,   283,
     500,   202,   457,   203,   458,   273,   489,   940,   941,   942,
    1045,    53,    75,   297,   298,   299,   503,   300,   301,   505,
     302,   303,   204,   468,   861,   862,   863,   999,    55,    76,
     315,   316,   317,   318,   511,   319,   512,   320,   513,   321,
     514,   322,   515,   323,   516,   324,   510,   275,   497,   945,
     946,  1048,   205,   467,   858,   859,   996,  1132,  1133,  1134,
    1135,  1136,  1207,  1137,   206,   471,   891,   892,   893,  1013,
    1216,   894,   895,  1014,   896,   897,   207,   208,   474,   914,
     915,   916,  1025,   917,  1026,   209,   475,   924,   925,   926,
     927,  1030,   928,   929,  1032,   210,   476,    65,    81,   392,
     393,   394,   395,   539,   396,   540,   397,   398,   542,   399,
     400,   401,   545,   765,   402,   546,   403,   404,   405,   549,
     406,   550,   407,   551,   408,   552,   211,   423,    67,    82,
     411,   412,   413,   555,   414,   212,   480,   932,   933,  1036,
    1175,  1176,  1177,  1178,  1224,  1179,  1222,  1243,  1244,  1245,
    1253,  1254,  1255,  1261,  1256,  1257,  1258,  1259,  1265
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     151,   215,   232,   277,   291,   311,    38,   333,   352,   369,
     389,   334,   353,   354,   233,   888,   274,   220,   271,   284,
     295,   313,   818,   347,   365,   848,   390,  1104,  1105,  1106,
     234,   235,   355,   236,   237,  1113,  1119,   305,    31,   708,
      32,   839,    33,   739,   943,   238,   239,   240,   839,   846,
     241,   847,   242,   367,   368,   745,   746,   747,   243,   696,
     697,   698,   699,    30,   244,   988,   213,   214,   989,    86,
     245,    89,   246,   221,   272,   285,   296,   314,   991,   348,
     366,   992,   391,   126,   127,   882,   269,   280,   294,   312,
     247,   248,   700,   249,   781,   482,    42,   486,   250,   498,
     483,   251,   487,   252,   499,   253,    44,   708,   254,   501,
      46,   255,   508,   263,   502,   264,   415,   509,   265,   266,
     327,   278,   292,   123,   840,   279,   293,    91,    92,   150,
      48,    93,   536,    50,    94,    95,    96,   537,   126,   127,
     126,   127,   326,   553,   918,   919,   920,   557,   554,    52,
     126,   127,   558,   482,   126,   127,   997,   416,   948,   998,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   711,   712,
     713,   714,    54,   327,   921,   328,   329,   125,   124,   330,
     331,   332,   883,   884,   885,   886,   126,   127,   909,   910,
     276,   126,   127,   128,   129,   130,   131,   126,   127,    56,
     557,   132,   133,   134,   135,   949,   136,  1168,    58,  1169,
    1170,   137,   409,   410,    34,    35,    36,    37,   229,   486,
     138,   230,   418,   139,   950,    60,  1104,  1105,  1106,   150,
     140,   150,   970,  1037,  1113,  1119,  1038,   971,   141,   142,
      62,   150,   970,   143,   994,   150,   144,   972,   776,   995,
     145,   367,   368,   777,   778,   779,   780,   781,   782,   783,
     784,   785,   786,   787,   788,   789,   790,   791,   792,   793,
     794,   146,   147,   148,   149,  1011,   124,    64,   848,   417,
    1012,    66,  1071,  1018,   124,   419,   124,   327,  1019,   888,
     286,   287,   288,   289,   290,   126,   127,   150,  1246,   327,
     421,  1247,   150,   126,   127,   126,   127,  1023,   150,   126,
     127,   428,  1024,  1027,   517,  1033,   229,   553,  1028,   230,
    1034,   970,  1035,   304,   763,   764,  1200,  1125,  1126,   305,
     306,   307,   308,   309,   310,   327,   349,   328,   329,   350,
     351,  1248,   429,   498,  1249,  1250,  1251,  1252,  1201,   430,
    1204,   519,   431,   126,   127,  1205,   868,   869,   870,   871,
     872,   873,   432,   898,   899,   900,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     536,   527,   518,  1225,   501,  1212,   559,   560,  1226,  1228,
     433,   151,   508,  1266,   528,   215,   434,  1229,  1267,   435,
    1188,  1189,  1190,  1191,   436,   437,   150,   232,   438,   439,
     277,   220,   440,   441,   150,   443,   150,   291,   444,   233,
     150,   274,   445,   271,   446,   447,   284,   311,   150,  1213,
    1214,  1215,   451,   295,   452,   234,   235,   333,   236,   237,
     460,   334,   352,   313,   461,   462,   353,   354,   472,   479,
     238,   239,   240,   347,   481,   241,   485,   242,   365,   493,
     494,   504,   389,   243,   150,   506,   355,   221,   507,   244,
     522,   526,   530,   531,   533,   245,   578,   246,   390,   272,
     532,   538,   285,   541,   543,   544,   547,   548,   556,   296,
     561,   269,   562,   563,   280,   247,   248,   564,   249,   314,
     565,   294,   566,   250,   567,   568,   251,   569,   252,   348,
     253,   312,   577,   254,   366,   570,   255,   571,   263,   572,
     264,   573,   574,   265,   266,   575,   576,   581,   278,   579,
     580,   582,   279,   583,   391,   292,   584,   585,   589,   293,
     586,   587,   590,   588,   591,   592,   593,   594,   595,   596,
     597,   598,   599,   600,   601,   602,   603,   604,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   605,   606,   607,   608,   114,   115,   116,   117,   118,
     119,   120,   121,   609,   610,   124,   611,   612,   614,   613,
     615,   616,   617,   618,   619,   621,   222,   151,   223,   623,
     215,   620,   624,   626,   126,   127,   224,   225,   226,   227,
     228,   128,   129,   130,   131,   627,   220,   631,   628,   629,
     630,   632,   633,   634,   635,   229,   637,   639,   230,   137,
     641,   640,   645,   887,   901,   911,   231,   389,   646,   642,
     643,   647,   648,   649,   650,   651,   653,   654,   655,   889,
     907,   912,   922,   390,   656,   657,   658,   772,   659,   661,
     665,   666,   662,   663,   668,   669,   670,   671,   672,   675,
     676,   679,   221,   680,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   673,   674,   146,
     147,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     681,   124,   327,   126,   127,   890,   908,   913,   923,   391,
     677,   678,   682,   684,   685,   150,   687,   688,   689,   694,
     126,   127,   690,   225,   226,   691,   228,   128,   129,   130,
     131,   692,   693,   695,   702,   704,   703,   705,   706,   707,
     710,   229,    32,   716,   230,   717,   718,   766,   720,   719,
     721,   722,   231,   729,   723,   724,   725,   726,   727,   728,
     730,   731,   732,   734,   735,   736,   737,   738,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   741,   740,   771,   819,   853,   742,   823,   387,   388,
     827,   831,   835,   743,   744,   748,   857,   749,   750,   751,
     860,   752,   753,   754,   755,   146,   147,   756,   757,   758,
     760,   761,   864,   762,   150,   931,   935,   939,   768,   955,
     956,   957,   769,   958,   959,   770,   961,   962,   966,   967,
     968,   150,   969,   974,   975,   977,   978,   981,   980,   984,
    1056,   983,   987,   986,   990,  1001,  1000,  1003,  1004,  1039,
    1005,  1006,  1007,  1008,  1009,  1010,  1015,  1016,  1017,  1020,
    1021,  1022,  1029,  1031,  1044,  1055,  1043,  1047,  1046,  1051,
    1057,  1049,  1050,  1052,  1053,  1054,  1058,  1059,  1060,  1061,
    1062,  1063,  1064,  1065,  1066,   232,  1067,  1068,   333,  1069,
    1123,   352,   334,  1143,  1079,   353,   354,   233,  1103,   274,
    1144,   271,  1145,  1146,   347,  1127,  1080,   365,   311,  1128,
    1117,   369,  1150,   234,   235,   355,   236,   237,  1147,  1148,
    1151,  1130,  1081,  1082,   313,  1083,  1084,   887,   238,   239,
     240,  1152,   901,   241,  1160,   242,   911,  1085,  1086,  1087,
    1156,   243,  1088,   889,  1089,  1171,  1153,   244,   907,  1172,
    1090,   277,   912,   245,   291,   246,  1091,   272,   922,  1161,
     348,  1173,  1092,   366,  1093,  1154,  1118,   284,  1157,   269,
     295,  1158,  1163,   247,   248,  1164,   249,  1131,  1116,  1166,
     314,   250,  1094,  1095,   251,  1096,   252,  1181,   253,  1129,
    1097,   254,   312,  1098,   255,  1099,   263,  1100,   264,   890,
    1101,   265,   266,  1102,   908,  1109,  1165,  1110,   913,  1182,
    1111,  1112,  1107,  1187,   923,  1193,  1108,  1174,  1202,  1194,
    1203,  1208,  1195,   285,  1209,  1210,   296,  1211,  1223,  1232,
    1235,  1196,  1237,   759,  1240,   280,  1262,  1242,   294,  1263,
    1264,  1268,  1272,   773,  1197,  1198,   625,   845,   767,   947,
     775,  1070,  1072,   622,  1124,  1122,  1121,  1159,  1142,  1141,
     667,  1149,  1074,  1073,  1231,  1120,   325,  1075,  1199,   278,
    1236,   636,   292,   279,  1206,  1076,   293,  1217,   660,  1233,
    1077,  1218,  1219,  1220,  1227,  1230,  1239,   664,  1241,  1078,
    1184,  1270,  1269,  1271,  1274,  1275,  1186,  1185,  1183,  1139,
    1140,   944,  1234,  1155,  1167,   638,   774,  1138,   683,  1162,
     930,  1238,  1180,  1079,   686,  1260,  1273,  1103,     0,  1127,
       0,     0,     0,  1128,     0,  1080,     0,     0,     0,  1117,
       0,     0,     0,   644,  1171,  1130,  1221,     0,  1172,     0,
       0,  1081,  1082,     0,  1083,  1084,     0,   652,     0,     0,
    1173,     0,     0,     0,     0,     0,  1085,  1086,  1087,     0,
       0,  1088,     0,  1089,     0,     0,     0,     0,     0,  1090,
       0,     0,     0,     0,     0,  1091,     0,     0,     0,     0,
       0,  1092,     0,  1093,     0,  1118,     0,     0,     0,     0,
       0,  1131,     0,     0,     0,     0,     0,  1116,     0,     0,
       0,  1094,  1095,  1129,  1096,     0,  1174,     0,     0,  1097,
       0,     0,  1098,     0,  1099,     0,  1100,     0,     0,  1101,
       0,     0,  1102,     0,  1109,     0,  1110,     0,     0,  1111,
    1112,  1107,     0,     0,     0,  1108
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    78,    79,    79,    73,   724,    73,    72,    73,    74,
      75,    76,   693,    78,    79,   718,    81,   985,   985,   985,
      73,    73,    79,    73,    73,   985,   985,   116,     5,   598,
       7,   118,     9,   633,   123,    73,    73,    73,   118,   119,
      73,   121,    73,   125,   126,   645,   646,   647,    73,   171,
     172,   173,   174,     0,    73,     3,    16,    17,     6,   201,
      73,    10,    73,    72,    73,    74,    75,    76,     3,    78,
      79,     6,    81,    90,    91,    21,    73,    74,    75,    76,
      73,    73,   204,    73,    30,     3,     7,     3,    73,     3,
       8,    73,     8,    73,     8,    73,     7,   666,    73,     3,
       7,    73,     3,    73,     8,    73,     6,     8,    73,    73,
      72,    74,    75,    70,   201,    74,    75,    11,    12,   201,
       7,    15,     3,     7,    18,    19,    20,     8,    90,    91,
      90,    91,    21,     3,   151,   152,   153,     3,     8,     7,
      90,    91,     8,     3,    90,    91,     3,     3,     8,     6,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,   101,   102,
     103,   104,     7,    72,   201,    74,    75,    81,    71,    78,
      79,    80,   138,   139,   140,   141,    90,    91,   148,   149,
      83,    90,    91,    97,    98,    99,   100,    90,    91,     7,
       3,   105,   106,   107,   108,     8,   110,   179,     7,   181,
     182,   115,    13,    14,   201,   202,   203,   204,   111,     3,
     124,   114,     8,   127,     8,     7,  1204,  1204,  1204,   201,
     134,   201,     3,     3,  1204,  1204,     6,     8,   142,   143,
       7,   201,     3,   147,     3,   201,   150,     8,    21,     8,
     154,   125,   126,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,   175,   176,   177,   178,     3,    71,     7,   991,     4,
       8,     7,   973,     3,    71,     3,    71,    72,     8,  1018,
      85,    86,    87,    88,    89,    90,    91,   201,     3,    72,
       8,     6,   201,    90,    91,    90,    91,     3,   201,    90,
      91,     4,     8,     3,     8,     3,   111,     3,     8,   114,
       8,     3,     8,   110,   168,   169,     8,   112,   113,   116,
     117,   118,   119,   120,   121,    72,    73,    74,    75,    76,
      77,   180,     4,     3,   183,   184,   185,   186,     8,     4,
       3,     8,     4,    90,    91,     8,   128,   129,   130,   131,
     132,   133,     4,   144,   145,   146,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
       3,     8,     3,     3,     3,     8,   416,   417,     8,     8,
       4,   482,     3,     3,     3,   486,     4,     8,     8,     4,
      22,    23,    24,    25,     4,     4,   201,   498,     4,     4,
     501,   486,     4,     4,   201,     4,   201,   508,     4,   498,
     201,   498,     4,   498,     4,     4,   501,   518,   201,   135,
     136,   137,     4,   508,     4,   498,   498,   528,   498,   498,
       4,   528,   533,   518,     4,     4,   533,   533,     4,     4,
     498,   498,   498,   528,     4,   498,     4,   498,   533,     4,
       4,     4,   553,   498,   201,     4,   533,   486,     4,   498,
       4,     4,     4,     4,     3,   498,   203,   498,   553,   498,
       8,     4,   501,     4,     4,     4,     4,     4,     4,   508,
     201,   498,     4,     4,   501,   498,   498,     4,   498,   518,
       4,   508,     4,   498,     4,     4,   498,   202,   498,   528,
     498,   518,   204,   498,   533,   202,   498,   202,   498,   202,
     498,   202,   202,   498,   498,   202,   202,   202,   501,   203,
     203,   202,   501,     4,   553,   508,   202,   202,     4,   508,
     204,   204,     4,   204,     4,   204,   204,     4,     4,     4,
       4,     4,     4,     4,   204,   204,   204,     4,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,     4,     4,     4,     4,    61,    62,    63,    64,    65,
      66,    67,    68,     4,     4,    71,     4,     4,     4,   202,
       4,     4,     4,     4,     4,     4,    82,   688,    84,     4,
     691,   204,   204,     4,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,     4,   691,   202,     4,     4,
       4,   204,     4,     4,     4,   111,     4,     4,   114,   115,
       4,   202,     4,   724,   725,   726,   122,   728,     4,   202,
     202,     4,     4,     4,     4,     4,     4,     4,   202,   724,
     725,   726,   727,   728,     4,     4,     4,   687,   204,     4,
       4,     4,   204,   204,   204,     4,     4,   202,     4,     4,
       4,     4,   691,     4,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,   202,   202,   175,
     176,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       4,    71,    72,    90,    91,   724,   725,   726,   727,   728,
     204,   204,     4,     4,   202,   201,     4,     7,   201,     5,
      90,    91,     7,    93,    94,     7,    96,    97,    98,    99,
     100,     7,     7,   201,   201,     5,   201,     5,     5,     5,
     201,   111,     7,     5,   114,     5,     5,   170,     5,     7,
       5,     5,   122,   201,     7,     7,     7,     7,     7,     7,
     201,     5,     5,     5,     5,   201,   201,   201,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,     7,   201,     5,     7,   109,   201,     7,   175,   176,
       7,     7,     7,   201,   201,   201,     7,   201,   201,   201,
       7,   201,   201,   201,   201,   175,   176,   201,   201,   201,
     201,   201,     7,   201,   201,     7,     7,     7,   201,     4,
       4,     4,   201,     4,     4,   201,     4,     4,     4,     4,
       4,   201,     4,     6,     3,     6,     3,     3,     6,     3,
     204,     6,     3,     6,     6,     3,     6,     6,     3,   201,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   202,     6,     3,     6,     4,
     202,     8,     6,     4,     4,     4,   204,   202,     4,   202,
     202,     4,     4,     4,   202,   976,   202,   204,   979,   202,
       4,   982,   979,   202,   985,   982,   982,   976,   985,   976,
     202,   976,   202,   202,   979,   996,   985,   982,   999,   996,
     985,  1002,     4,   976,   976,   982,   976,   976,   202,   202,
       4,   996,   985,   985,   999,   985,   985,  1018,   976,   976,
     976,   202,  1023,   976,     4,   976,  1027,   985,   985,   985,
     204,   976,   985,  1018,   985,  1036,   202,   976,  1023,  1036,
     985,  1042,  1027,   976,  1045,   976,   985,   976,  1033,     4,
     979,  1036,   985,   982,   985,   202,   985,  1042,   202,   976,
    1045,   202,   204,   976,   976,     4,   976,   996,   985,     4,
     999,   976,   985,   985,   976,   985,   976,     6,   976,   996,
     985,   976,   999,   985,   976,   985,   976,   985,   976,  1018,
     985,   976,   976,   985,  1023,   985,   202,   985,  1027,     3,
     985,   985,   985,     4,  1033,   201,   985,  1036,     8,   201,
       8,     4,   201,  1042,     8,     3,  1045,     8,     4,     4,
       4,   201,     4,   666,     5,  1042,     4,     7,  1045,     4,
       4,     4,     4,   688,   201,   201,   486,   717,   679,   771,
     691,   970,   975,   482,   994,   991,   988,  1023,  1004,  1002,
     536,  1011,   978,   976,  1204,   987,    77,   979,   201,  1042,
     202,   498,  1045,  1042,   201,   981,  1045,   201,   528,   204,
     982,   201,   201,   201,   201,   201,   201,   533,   201,   984,
    1044,   202,   204,   202,   201,   201,  1047,  1045,  1042,   999,
    1001,   741,  1210,  1018,  1033,   501,   690,   997,   553,  1027,
     728,  1225,  1037,  1204,   557,  1246,  1266,  1204,    -1,  1210,
      -1,    -1,    -1,  1210,    -1,  1204,    -1,    -1,    -1,  1204,
      -1,    -1,    -1,   508,  1225,  1210,  1166,    -1,  1225,    -1,
      -1,  1204,  1204,    -1,  1204,  1204,    -1,   518,    -1,    -1,
    1225,    -1,    -1,    -1,    -1,    -1,  1204,  1204,  1204,    -1,
      -1,  1204,    -1,  1204,    -1,    -1,    -1,    -1,    -1,  1204,
      -1,    -1,    -1,    -1,    -1,  1204,    -1,    -1,    -1,    -1,
      -1,  1204,    -1,  1204,    -1,  1204,    -1,    -1,    -1,    -1,
      -1,  1210,    -1,    -1,    -1,    -1,    -1,  1204,    -1,    -1,
      -1,  1204,  1204,  1210,  1204,    -1,  1225,    -1,    -1,  1204,
      -1,    -1,  1204,    -1,  1204,    -1,  1204,    -1,    -1,  1204,
      -1,    -1,  1204,    -1,  1204,    -1,  1204,    -1,    -1,  1204,
    1204,  1204,    -1,    -1,    -1,  1204
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
       0,     5,     7,     9,   201,   202,   203,   204,   221,   222,
     223,   228,     7,   237,     7,   241,     7,   284,     7,   390,
       7,   470,     7,   486,     7,   503,     7,   422,     7,   428,
       7,   452,     7,   366,     7,   572,     7,   603,   229,   224,
     238,   242,   285,   391,   471,   487,   504,   423,   429,   453,
     367,   573,   604,   221,   230,   231,   201,   226,   227,    10,
     239,    11,    12,    15,    18,    19,    20,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    81,    90,    91,    97,    98,
      99,   100,   105,   106,   107,   108,   110,   115,   124,   127,
     134,   142,   143,   147,   150,   154,   175,   176,   177,   178,
     201,   236,   243,   244,   245,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   267,   269,   271,   272,   274,   276,   277,
     278,   279,   281,   282,   291,   293,   295,   333,   339,   345,
     351,   353,   360,   374,   384,   404,   405,   406,   407,   412,
     420,   446,   476,   478,   497,   527,   539,   551,   552,   560,
     570,   601,   610,    16,    17,   236,   286,   287,   288,   290,
     476,   478,    82,    84,    92,    93,    94,    95,    96,   111,
     114,   122,   236,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   261,   262,   263,   264,
     267,   269,   271,   272,   274,   276,   392,   393,   394,   396,
     398,   400,   402,   404,   405,   406,   407,   410,   411,   446,
     464,   476,   478,   480,   497,   522,    83,   236,   400,   402,
     446,   472,   473,   474,   476,   478,    85,    86,    87,    88,
      89,   236,   400,   402,   446,   476,   478,   488,   489,   490,
     492,   493,   495,   496,   110,   116,   117,   118,   119,   120,
     121,   236,   446,   476,   478,   505,   506,   507,   508,   510,
     512,   514,   516,   518,   520,   420,    21,    72,    74,    75,
      78,    79,    80,   236,   313,   430,   431,   432,   433,   434,
     435,   436,   438,   440,   442,   443,   445,   476,   478,    73,
      76,    77,   236,   313,   434,   440,   454,   455,   456,   457,
     458,   460,   461,   462,   463,   476,   478,   125,   126,   236,
     368,   369,   370,   372,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   175,   176,   236,
     476,   478,   574,   575,   576,   577,   579,   581,   582,   584,
     585,   586,   589,   591,   592,   593,   595,   597,   599,    13,
      14,   605,   606,   607,   609,     6,     3,     4,     8,     3,
     240,     8,   246,   602,   283,   292,   294,   296,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   280,     4,     4,     4,     4,     4,   265,   268,
     270,     4,     4,   385,   421,   447,   413,   477,   479,   408,
       4,     4,     4,   340,   352,   346,   334,   528,   498,   361,
     375,   540,     4,   354,   553,   561,   571,   273,   275,     4,
     611,     4,     3,     8,   289,     4,     3,     8,   465,   481,
     395,   397,   399,     4,     4,   403,   401,   523,     3,     8,
     475,     3,     8,   491,     4,   494,     4,     4,     3,     8,
     521,   509,   511,   513,   515,   517,   519,     8,     3,     8,
     437,   314,     4,   441,   439,   444,     4,     8,     3,   459,
       4,     4,     8,     3,   371,   373,     3,     8,     4,   578,
     580,     4,   583,     4,     4,   587,   590,     4,     4,   594,
     596,   598,   600,     3,     8,   608,     4,     3,     8,   221,
     221,   201,     4,     4,     4,     4,     4,     4,     4,   202,
     202,   202,   202,   202,   202,   202,   202,   204,   203,   203,
     203,   202,   202,     4,   202,   202,   204,   204,   204,     4,
       4,     4,   204,   204,     4,     4,     4,     4,     4,     4,
       4,   204,   204,   204,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   202,     4,     4,     4,     4,     4,     4,
     204,     4,   244,     4,   204,   287,     4,     4,     4,     4,
       4,   202,   204,     4,     4,     4,   393,     4,   473,     4,
     202,     4,   202,   202,   489,     4,     4,     4,     4,     4,
       4,     4,   507,     4,     4,   202,     4,     4,     4,   204,
     432,     4,   204,   204,   456,     4,     4,   369,   204,     4,
       4,   202,     4,   202,   202,     4,     4,   204,   204,     4,
       4,     4,     4,   575,     4,   202,   606,     4,     7,   201,
       7,     7,     7,     7,     5,   201,   171,   172,   173,   174,
     204,   266,   201,   201,     5,     5,     5,     5,   223,   225,
     201,   101,   102,   103,   104,   409,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     7,     7,   201,
     201,     5,     5,   232,     5,     5,   201,   201,   201,   232,
     201,     7,   201,   201,   201,   232,   232,   232,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   225,
     201,   201,   201,   168,   169,   588,   170,   266,   201,   201,
     201,     5,   221,   243,   605,   286,    21,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,   236,   301,   302,   303,   306,
     308,   310,   312,   313,   315,   316,   317,   318,   319,   320,
     321,   322,   323,   324,   326,   327,   329,   331,   301,     7,
     297,   298,   299,     7,   386,   387,   388,     7,   424,   425,
     426,     7,   448,   449,   450,     7,   414,   415,   416,   118,
     201,   341,   342,   343,   344,   230,   119,   121,   343,   347,
     348,   349,   350,   109,   335,   336,   337,     7,   529,   530,
       7,   499,   500,   501,     7,   362,   363,   364,   128,   129,
     130,   131,   132,   133,   376,   377,   378,   379,   380,   381,
     382,   383,    21,   138,   139,   140,   141,   236,   315,   476,
     478,   541,   542,   543,   546,   547,   549,   550,   144,   145,
     146,   236,   355,   356,   357,   358,   359,   476,   478,   148,
     149,   236,   476,   478,   554,   555,   556,   558,   151,   152,
     153,   201,   476,   478,   562,   563,   564,   565,   567,   568,
     574,     7,   612,   613,   233,     7,   466,   467,   468,     7,
     482,   483,   484,   123,   508,   524,   525,   297,     8,     8,
       8,   304,   307,   309,   311,     4,     4,     4,     4,     4,
     325,     4,     4,   328,   330,   332,     4,     4,     4,     4,
       3,     8,     8,   300,     6,     3,   389,     6,     3,   427,
       6,     3,   451,     6,     3,   417,     6,     3,     3,     6,
       6,     3,     6,   338,     3,     8,   531,     3,     6,   502,
       6,     3,   365,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   544,   548,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   557,   559,     3,     8,     4,
     566,     4,   569,     3,     8,     8,   614,     3,     6,   201,
     234,   235,   469,     6,     3,   485,     6,     3,   526,     8,
       6,     4,     4,     4,     4,   202,   204,   202,   204,   202,
       4,   202,   202,     4,     4,     4,   202,   202,   204,   202,
     302,   301,   299,   392,   388,   430,   426,   454,   450,   236,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   261,   262,   263,   264,   267,   269,   271,
     272,   274,   276,   313,   384,   396,   398,   400,   402,   404,
     405,   406,   407,   411,   418,   419,   446,   476,   478,   522,
     416,   342,   348,     4,   336,   112,   113,   236,   313,   446,
     476,   478,   532,   533,   534,   535,   536,   538,   530,   505,
     501,   368,   364,   202,   202,   202,   202,   202,   202,   377,
       4,     4,   202,   202,   202,   542,   204,   202,   202,   356,
       4,     4,   555,   204,     4,   202,     4,   563,   179,   181,
     182,   236,   313,   476,   478,   615,   616,   617,   618,   620,
     613,     6,     3,   472,   468,   488,   484,     4,    22,    23,
      24,    25,   305,   201,   201,   201,   201,   201,   201,   201,
       8,     8,     8,     8,     3,     8,   201,   537,     4,     8,
       3,     8,     8,   135,   136,   137,   545,   201,   201,   201,
     201,   221,   621,     4,   619,     3,     8,   201,     8,     8,
     201,   419,     4,   204,   534,     4,   202,     4,   616,   201,
       5,   201,     7,   622,   623,   624,     3,     6,   180,   183,
     184,   185,   186,   625,   626,   627,   629,   630,   631,   632,
     623,   628,     4,     4,     4,   633,     3,     8,     4,   204,
     202,   202,     4,   626,   201,   201
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   205,   207,   206,   208,   206,   209,   206,   210,   206,
     211,   206,   212,   206,   213,   206,   214,   206,   215,   206,
     216,   206,   217,   206,   218,   206,   219,   206,   220,   206,
     221,   221,   221,   221,   221,   221,   221,   222,   224,   223,
     225,   226,   226,   227,   227,   229,   228,   230,   230,   231,
     231,   233,   232,   234,   234,   235,   235,   236,   238,   237,
     240,   239,   242,   241,   243,   243,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   246,   245,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   265,   264,   266,   266,   266,
     266,   266,   268,   267,   270,   269,   271,   273,   272,   275,
     274,   276,   277,   278,   280,   279,   281,   283,   282,   285,
     284,   286,   286,   287,   287,   287,   287,   287,   289,   288,
     290,   292,   291,   294,   293,   296,   295,   297,   297,   298,
     298,   300,   299,   301,   301,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   304,   303,   305,   305,
     305,   305,   307,   306,   309,   308,   311,   310,   312,   314,
     313,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     325,   324,   326,   328,   327,   330,   329,   332,   331,   334,
     333,   335,   335,   336,   338,   337,   340,   339,   341,   341,
     342,   342,   343,   344,   346,   345,   347,   347,   348,   348,
     348,   349,   350,   352,   351,   354,   353,   355,   355,   356,
     356,   356,   356,   356,   356,   357,   358,   359,   361,   360,
     362,   362,   363,   363,   365,   364,   367,   366,   368,   368,
     368,   369,   369,   371,   370,   373,   372,   375,   374,   376,
     376,   377,   377,   377,   377,   377,   377,   378,   379,   380,
     381,   382,   383,   385,   384,   386,   386,   387,   387,   389,
     388,   391,   390,   392,   392,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   395,   394,   397,
     396,   399,   398,   401,   400,   403,   402,   404,   405,   406,
     408,   407,   409,   409,   409,   409,   410,   411,   413,   412,
     414,   414,   415,   415,   417,   416,   418,   418,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   421,   420,   423,
     422,   424,   424,   425,   425,   427,   426,   429,   428,   430,
     430,   431,   431,   432,   432,   432,   432,   432,   432,   432,
     432,   432,   432,   433,   434,   435,   437,   436,   439,   438,
     441,   440,   442,   444,   443,   445,   447,   446,   448,   448,
     449,   449,   451,   450,   453,   452,   454,   454,   455,   455,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   457,
     459,   458,   460,   461,   462,   463,   465,   464,   466,   466,
     467,   467,   469,   468,   471,   470,   472,   472,   473,   473,
     473,   473,   473,   473,   473,   475,   474,   477,   476,   479,
     478,   481,   480,   482,   482,   483,   483,   485,   484,   487,
     486,   488,   488,   489,   489,   489,   489,   489,   489,   489,
     489,   489,   489,   489,   491,   490,   492,   494,   493,   495,
     496,   498,   497,   499,   499,   500,   500,   502,   501,   504,
     503,   505,   505,   506,   506,   507,   507,   507,   507,   507,
     507,   507,   507,   507,   507,   507,   509,   508,   511,   510,
     513,   512,   515,   514,   517,   516,   519,   518,   521,   520,
     523,   522,   524,   524,   526,   525,   528,   527,   529,   529,
     531,   530,   532,   532,   533,   533,   534,   534,   534,   534,
     534,   534,   534,   535,   537,   536,   538,   540,   539,   541,
     541,   542,   542,   542,   542,   542,   542,   542,   542,   542,
     544,   543,   545,   545,   545,   546,   548,   547,   549,   550,
     551,   553,   552,   554,   554,   555,   555,   555,   555,   555,
     557,   556,   559,   558,   561,   560,   562,   562,   563,   563,
     563,   563,   563,   563,   564,   566,   565,   567,   569,   568,
     571,   570,   573,   572,   574,   574,   575,   575,   575,   575,
     575,   575,   575,   575,   575,   575,   575,   575,   575,   575,
     575,   575,   575,   575,   576,   578,   577,   580,   579,   581,
     583,   582,   584,   585,   587,   586,   588,   588,   590,   589,
     591,   592,   594,   593,   596,   595,   598,   597,   600,   599,
     602,   601,   604,   603,   605,   605,   606,   606,   608,   607,
     609,   611,   610,   612,   612,   614,   613,   615,   615,   616,
     616,   616,   616,   616,   616,   616,   617,   619,   618,   621,
     620,   622,   622,   624,   623,   625,   625,   626,   626,   626,
     626,   626,   628,   627,   629,   630,   631,   633,   632
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
       1,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     0,     4,     0,
       4,     3,     3,     3,     0,     4,     3,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     3,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     6,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
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
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"consistency\"",
  "\"serial-consistency\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"cache-threshold\"",
  "\"cache-max-age\"", "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"store-extended-info\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"reservations-out-of-pool\"", "\"reservations-in-subnet\"",
  "\"reservations-global\"", "\"disabled\"", "\"out-of-pool\"",
  "\"global\"", "\"all\"", "\"mac-sources\"", "\"relay-supplied-options\"",
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
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6",
  "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION",
  "SUB_OPTION_DEFS", "SUB_OPTION_DEF", "SUB_OPTION_DATA",
  "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_CONFIG_CONTROL",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "value", "sub_json", "map2", "$@15", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@16", "list_content",
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
  "$@62", "require_client_classes", "$@63", "reservations_out_of_pool",
  "reservations_in_subnet", "reservations_global", "reservation_mode",
  "$@64", "hr_mode", "id", "rapid_commit", "shared_networks", "$@65",
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
       0,   291,   291,   291,   292,   292,   293,   293,   294,   294,
     295,   295,   296,   296,   297,   297,   298,   298,   299,   299,
     300,   300,   301,   301,   302,   302,   303,   303,   304,   304,
     312,   313,   314,   315,   316,   317,   318,   321,   326,   326,
     337,   340,   341,   344,   349,   357,   357,   364,   365,   368,
     372,   379,   379,   386,   387,   390,   394,   405,   414,   414,
     429,   429,   446,   446,   455,   456,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   523,   523,   532,   538,
     544,   550,   556,   562,   568,   574,   580,   586,   592,   598,
     604,   610,   616,   622,   628,   634,   634,   643,   646,   649,
     652,   655,   661,   661,   670,   670,   679,   685,   685,   694,
     694,   703,   709,   715,   721,   721,   730,   736,   736,   748,
     748,   757,   758,   761,   762,   763,   764,   765,   768,   768,
     779,   785,   785,   798,   798,   811,   811,   822,   823,   826,
     827,   830,   830,   840,   841,   844,   845,   846,   847,   848,
     849,   850,   851,   852,   853,   854,   855,   856,   857,   858,
     859,   860,   861,   862,   863,   864,   867,   867,   875,   876,
     877,   878,   881,   881,   890,   890,   899,   899,   908,   914,
     914,   923,   929,   935,   941,   947,   953,   959,   965,   971,
     977,   977,   986,   992,   992,  1001,  1001,  1010,  1010,  1019,
    1019,  1030,  1031,  1033,  1035,  1035,  1054,  1054,  1065,  1066,
    1069,  1070,  1073,  1078,  1083,  1083,  1094,  1095,  1098,  1099,
    1100,  1103,  1108,  1115,  1115,  1128,  1128,  1141,  1142,  1145,
    1146,  1147,  1148,  1149,  1150,  1153,  1159,  1165,  1171,  1171,
    1182,  1183,  1186,  1187,  1190,  1190,  1200,  1200,  1210,  1211,
    1212,  1215,  1216,  1219,  1219,  1228,  1228,  1237,  1237,  1249,
    1250,  1253,  1254,  1255,  1256,  1257,  1258,  1261,  1267,  1273,
    1279,  1285,  1291,  1300,  1300,  1314,  1315,  1318,  1319,  1326,
    1326,  1352,  1352,  1363,  1364,  1368,  1369,  1370,  1371,  1372,
    1373,  1374,  1375,  1376,  1377,  1378,  1379,  1380,  1381,  1382,
    1383,  1384,  1385,  1386,  1387,  1388,  1389,  1390,  1391,  1392,
    1393,  1394,  1395,  1396,  1397,  1398,  1399,  1400,  1401,  1402,
    1403,  1404,  1405,  1406,  1407,  1408,  1409,  1412,  1412,  1421,
    1421,  1430,  1430,  1439,  1439,  1448,  1448,  1459,  1465,  1471,
    1477,  1477,  1485,  1486,  1487,  1488,  1491,  1497,  1505,  1505,
    1517,  1518,  1522,  1523,  1526,  1526,  1534,  1535,  1538,  1539,
    1540,  1541,  1542,  1543,  1544,  1545,  1546,  1547,  1548,  1549,
    1550,  1551,  1552,  1553,  1554,  1555,  1556,  1557,  1558,  1559,
    1560,  1561,  1562,  1563,  1564,  1565,  1566,  1567,  1568,  1569,
    1570,  1571,  1572,  1573,  1574,  1575,  1576,  1583,  1583,  1597,
    1597,  1606,  1607,  1610,  1611,  1616,  1616,  1631,  1631,  1645,
    1646,  1649,  1650,  1653,  1654,  1655,  1656,  1657,  1658,  1659,
    1660,  1661,  1662,  1665,  1667,  1673,  1675,  1675,  1684,  1684,
    1693,  1693,  1702,  1704,  1704,  1713,  1723,  1723,  1736,  1737,
    1742,  1743,  1748,  1748,  1760,  1760,  1772,  1773,  1778,  1779,
    1784,  1785,  1786,  1787,  1788,  1789,  1790,  1791,  1792,  1795,
    1797,  1797,  1806,  1808,  1810,  1816,  1825,  1825,  1838,  1839,
    1842,  1843,  1846,  1846,  1856,  1856,  1866,  1867,  1870,  1871,
    1872,  1873,  1874,  1875,  1876,  1879,  1879,  1888,  1888,  1913,
    1913,  1943,  1943,  1956,  1957,  1960,  1961,  1964,  1964,  1976,
    1976,  1988,  1989,  1992,  1993,  1994,  1995,  1996,  1997,  1998,
    1999,  2000,  2001,  2002,  2005,  2005,  2014,  2020,  2020,  2029,
    2035,  2044,  2044,  2055,  2056,  2059,  2060,  2063,  2063,  2072,
    2072,  2081,  2082,  2085,  2086,  2090,  2091,  2092,  2093,  2094,
    2095,  2096,  2097,  2098,  2099,  2100,  2103,  2103,  2114,  2114,
    2125,  2125,  2134,  2134,  2143,  2143,  2152,  2152,  2161,  2161,
    2175,  2175,  2186,  2187,  2190,  2190,  2202,  2202,  2213,  2214,
    2217,  2217,  2227,  2228,  2231,  2232,  2235,  2236,  2237,  2238,
    2239,  2240,  2241,  2244,  2246,  2246,  2255,  2264,  2264,  2277,
    2278,  2281,  2282,  2283,  2284,  2285,  2286,  2287,  2288,  2289,
    2292,  2292,  2300,  2301,  2302,  2305,  2311,  2311,  2320,  2326,
    2334,  2342,  2342,  2353,  2354,  2357,  2358,  2359,  2360,  2361,
    2364,  2364,  2373,  2373,  2385,  2385,  2398,  2399,  2402,  2403,
    2404,  2405,  2406,  2407,  2410,  2416,  2416,  2425,  2431,  2431,
    2441,  2441,  2454,  2454,  2464,  2465,  2468,  2469,  2470,  2471,
    2472,  2473,  2474,  2475,  2476,  2477,  2478,  2479,  2480,  2481,
    2482,  2483,  2484,  2485,  2488,  2495,  2495,  2504,  2504,  2513,
    2519,  2519,  2528,  2534,  2540,  2540,  2549,  2550,  2553,  2553,
    2563,  2570,  2577,  2577,  2586,  2586,  2596,  2596,  2606,  2606,
    2618,  2618,  2630,  2630,  2640,  2641,  2645,  2646,  2649,  2649,
    2660,  2668,  2668,  2681,  2682,  2686,  2686,  2694,  2695,  2698,
    2699,  2700,  2701,  2702,  2703,  2704,  2707,  2713,  2713,  2722,
    2722,  2733,  2734,  2737,  2737,  2745,  2746,  2749,  2750,  2751,
    2752,  2753,  2756,  2756,  2765,  2771,  2777,  2783,  2783
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
#line 5841 "dhcp6_parser.cc"

#line 2792 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
