// A Bison parser, made by GNU Bison 3.7.1.

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
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 400 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 406 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 412 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 418 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 424 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 430 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 436 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 442 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 448 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 454 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 274 "dhcp6_parser.yy"
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
#line 283 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 739 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 284 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 745 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 285 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 751 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 286 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 757 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 287 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 763 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 288 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 769 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 289 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 775 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 290 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 781 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 291 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 787 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 292 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 793 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 293 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 799 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 294 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 805 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 295 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 811 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 296 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 817 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 304 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 305 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 306 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 307 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 308 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 847 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 309 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 310 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 859 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 313 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 868 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 318 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 879 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 323 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 889 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 329 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 336 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 904 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 340 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 914 "dhcp6_parser.cc"
    break;

  case 45: // $@16: %empty
#line 347 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 923 "dhcp6_parser.cc"
    break;

  case 46: // list_generic: "[" $@16 list_content "]"
#line 350 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 931 "dhcp6_parser.cc"
    break;

  case 49: // not_empty_list: value
#line 358 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 940 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list "," value
#line 362 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 949 "dhcp6_parser.cc"
    break;

  case 51: // $@17: %empty
#line 369 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 957 "dhcp6_parser.cc"
    break;

  case 52: // list_strings: "[" $@17 list_strings_content "]"
#line 371 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 966 "dhcp6_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 380 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 975 "dhcp6_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 384 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 984 "dhcp6_parser.cc"
    break;

  case 57: // unknown_map_entry: "constant string" ":"
#line 395 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 995 "dhcp6_parser.cc"
    break;

  case 58: // $@18: %empty
#line 404 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1006 "dhcp6_parser.cc"
    break;

  case 59: // syntax_map: "{" $@18 global_object "}"
#line 409 "dhcp6_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1019 "dhcp6_parser.cc"
    break;

  case 60: // $@19: %empty
#line 419 "dhcp6_parser.yy"
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

  case 61: // global_object: "Dhcp6" $@19 ":" "{" global_params "}"
#line 428 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1044 "dhcp6_parser.cc"
    break;

  case 62: // $@20: %empty
#line 436 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1054 "dhcp6_parser.cc"
    break;

  case 63: // sub_dhcp6: "{" $@20 global_params "}"
#line 440 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1063 "dhcp6_parser.cc"
    break;

  case 119: // $@21: %empty
#line 506 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1071 "dhcp6_parser.cc"
    break;

  case 120: // data_directory: "data-directory" $@21 ":" "constant string"
#line 508 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 121: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 514 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1090 "dhcp6_parser.cc"
    break;

  case 122: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 519 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 123: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 524 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 124: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 529 "dhcp6_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1117 "dhcp6_parser.cc"
    break;

  case 125: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 534 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1126 "dhcp6_parser.cc"
    break;

  case 126: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 539 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 127: // renew_timer: "renew-timer" ":" "integer"
#line 544 "dhcp6_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1144 "dhcp6_parser.cc"
    break;

  case 128: // rebind_timer: "rebind-timer" ":" "integer"
#line 549 "dhcp6_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1153 "dhcp6_parser.cc"
    break;

  case 129: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 554 "dhcp6_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1162 "dhcp6_parser.cc"
    break;

  case 130: // t1_percent: "t1-percent" ":" "floating point"
#line 559 "dhcp6_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 131: // t2_percent: "t2-percent" ":" "floating point"
#line 564 "dhcp6_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1180 "dhcp6_parser.cc"
    break;

  case 132: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 569 "dhcp6_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1189 "dhcp6_parser.cc"
    break;

  case 133: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 574 "dhcp6_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1198 "dhcp6_parser.cc"
    break;

  case 134: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 579 "dhcp6_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1207 "dhcp6_parser.cc"
    break;

  case 135: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 584 "dhcp6_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1216 "dhcp6_parser.cc"
    break;

  case 136: // $@22: %empty
#line 589 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 137: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 591 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 138: // ddns_replace_client_name_value: "when-present"
#line 597 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1241 "dhcp6_parser.cc"
    break;

  case 139: // ddns_replace_client_name_value: "never"
#line 600 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1249 "dhcp6_parser.cc"
    break;

  case 140: // ddns_replace_client_name_value: "always"
#line 603 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1257 "dhcp6_parser.cc"
    break;

  case 141: // ddns_replace_client_name_value: "when-not-present"
#line 606 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1265 "dhcp6_parser.cc"
    break;

  case 142: // ddns_replace_client_name_value: "boolean"
#line 609 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1274 "dhcp6_parser.cc"
    break;

  case 143: // $@23: %empty
#line 615 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1282 "dhcp6_parser.cc"
    break;

  case 144: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 617 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1292 "dhcp6_parser.cc"
    break;

  case 145: // $@24: %empty
#line 623 "dhcp6_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1300 "dhcp6_parser.cc"
    break;

  case 146: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 625 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1310 "dhcp6_parser.cc"
    break;

  case 147: // $@25: %empty
#line 631 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1318 "dhcp6_parser.cc"
    break;

  case 148: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 633 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1328 "dhcp6_parser.cc"
    break;

  case 149: // $@26: %empty
#line 639 "dhcp6_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1336 "dhcp6_parser.cc"
    break;

  case 150: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 641 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1346 "dhcp6_parser.cc"
    break;

  case 151: // store_extended_info: "store-extended-info" ":" "boolean"
#line 647 "dhcp6_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1355 "dhcp6_parser.cc"
    break;

  case 152: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 652 "dhcp6_parser.yy"
                                                                             {
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1364 "dhcp6_parser.cc"
    break;

  case 153: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 657 "dhcp6_parser.yy"
                                                                         {
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 154: // $@27: %empty
#line 662 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1381 "dhcp6_parser.cc"
    break;

  case 155: // server_tag: "server-tag" $@27 ":" "constant string"
#line 664 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1391 "dhcp6_parser.cc"
    break;

  case 156: // $@28: %empty
#line 670 "dhcp6_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 157: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 675 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 158: // $@29: %empty
#line 681 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 159: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 685 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 167: // $@30: %empty
#line 701 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp6_parser.cc"
    break;

  case 168: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 706 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 169: // re_detect: "re-detect" ":" "boolean"
#line 711 "dhcp6_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 170: // $@31: %empty
#line 716 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1471 "dhcp6_parser.cc"
    break;

  case 171: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 721 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1482 "dhcp6_parser.cc"
    break;

  case 172: // $@32: %empty
#line 728 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1493 "dhcp6_parser.cc"
    break;

  case 173: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 733 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc"
    break;

  case 174: // $@33: %empty
#line 740 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1515 "dhcp6_parser.cc"
    break;

  case 175: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 745 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1524 "dhcp6_parser.cc"
    break;

  case 180: // $@34: %empty
#line 758 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1534 "dhcp6_parser.cc"
    break;

  case 181: // database: "{" $@34 database_map_params "}"
#line 762 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1544 "dhcp6_parser.cc"
    break;

  case 205: // $@35: %empty
#line 795 "dhcp6_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1552 "dhcp6_parser.cc"
    break;

  case 206: // database_type: "type" $@35 ":" db_type
#line 797 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 207: // db_type: "memfile"
#line 802 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1567 "dhcp6_parser.cc"
    break;

  case 208: // db_type: "mysql"
#line 803 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1573 "dhcp6_parser.cc"
    break;

  case 209: // db_type: "postgresql"
#line 804 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1579 "dhcp6_parser.cc"
    break;

  case 210: // db_type: "cql"
#line 805 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1585 "dhcp6_parser.cc"
    break;

  case 211: // $@36: %empty
#line 808 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1593 "dhcp6_parser.cc"
    break;

  case 212: // user: "user" $@36 ":" "constant string"
#line 810 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1603 "dhcp6_parser.cc"
    break;

  case 213: // $@37: %empty
#line 816 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1611 "dhcp6_parser.cc"
    break;

  case 214: // password: "password" $@37 ":" "constant string"
#line 818 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 215: // $@38: %empty
#line 824 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 216: // host: "host" $@38 ":" "constant string"
#line 826 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1639 "dhcp6_parser.cc"
    break;

  case 217: // port: "port" ":" "integer"
#line 832 "dhcp6_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1648 "dhcp6_parser.cc"
    break;

  case 218: // $@39: %empty
#line 837 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1656 "dhcp6_parser.cc"
    break;

  case 219: // name: "name" $@39 ":" "constant string"
#line 839 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1666 "dhcp6_parser.cc"
    break;

  case 220: // persist: "persist" ":" "boolean"
#line 845 "dhcp6_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1675 "dhcp6_parser.cc"
    break;

  case 221: // lfc_interval: "lfc-interval" ":" "integer"
#line 850 "dhcp6_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1684 "dhcp6_parser.cc"
    break;

  case 222: // readonly: "readonly" ":" "boolean"
#line 855 "dhcp6_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1693 "dhcp6_parser.cc"
    break;

  case 223: // connect_timeout: "connect-timeout" ":" "integer"
#line 860 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1702 "dhcp6_parser.cc"
    break;

  case 224: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 865 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1711 "dhcp6_parser.cc"
    break;

  case 225: // max_row_errors: "max-row-errors" ":" "integer"
#line 870 "dhcp6_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1720 "dhcp6_parser.cc"
    break;

  case 226: // request_timeout: "request-timeout" ":" "integer"
#line 875 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1729 "dhcp6_parser.cc"
    break;

  case 227: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 880 "dhcp6_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1738 "dhcp6_parser.cc"
    break;

  case 228: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 885 "dhcp6_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 229: // $@40: %empty
#line 890 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 230: // contact_points: "contact-points" $@40 ":" "constant string"
#line 892 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1765 "dhcp6_parser.cc"
    break;

  case 231: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 898 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1774 "dhcp6_parser.cc"
    break;

  case 232: // $@41: %empty
#line 903 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1782 "dhcp6_parser.cc"
    break;

  case 233: // keyspace: "keyspace" $@41 ":" "constant string"
#line 905 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1792 "dhcp6_parser.cc"
    break;

  case 234: // $@42: %empty
#line 911 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 235: // consistency: "consistency" $@42 ":" "constant string"
#line 913 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1810 "dhcp6_parser.cc"
    break;

  case 236: // $@43: %empty
#line 919 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1818 "dhcp6_parser.cc"
    break;

  case 237: // serial_consistency: "serial-consistency" $@43 ":" "constant string"
#line 921 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1828 "dhcp6_parser.cc"
    break;

  case 238: // $@44: %empty
#line 927 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1839 "dhcp6_parser.cc"
    break;

  case 239: // sanity_checks: "sanity-checks" $@44 ":" "{" sanity_checks_params "}"
#line 932 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1848 "dhcp6_parser.cc"
    break;

  case 243: // $@45: %empty
#line 942 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1856 "dhcp6_parser.cc"
    break;

  case 244: // lease_checks: "lease-checks" $@45 ":" "constant string"
#line 944 "dhcp6_parser.yy"
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
#line 1876 "dhcp6_parser.cc"
    break;

  case 245: // $@46: %empty
#line 960 "dhcp6_parser.yy"
                         {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1887 "dhcp6_parser.cc"
    break;

  case 246: // mac_sources: "mac-sources" $@46 ":" "[" mac_sources_list "]"
#line 965 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1896 "dhcp6_parser.cc"
    break;

  case 251: // duid_id: "duid"
#line 978 "dhcp6_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1905 "dhcp6_parser.cc"
    break;

  case 252: // string_id: "constant string"
#line 983 "dhcp6_parser.yy"
                   {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1914 "dhcp6_parser.cc"
    break;

  case 253: // $@47: %empty
#line 988 "dhcp6_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 254: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 993 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1934 "dhcp6_parser.cc"
    break;

  case 260: // hw_address_id: "hw-address"
#line 1007 "dhcp6_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1943 "dhcp6_parser.cc"
    break;

  case 261: // flex_id: "flex-id"
#line 1012 "dhcp6_parser.yy"
                  {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1952 "dhcp6_parser.cc"
    break;

  case 262: // $@48: %empty
#line 1019 "dhcp6_parser.yy"
                                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp6_parser.cc"
    break;

  case 263: // relay_supplied_options: "relay-supplied-options" $@48 ":" "[" list_content "]"
#line 1024 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 264: // $@49: %empty
#line 1031 "dhcp6_parser.yy"
                                           {
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 265: // dhcp_multi_threading: "multi-threading" $@49 ":" "{" multi_threading_params "}"
#line 1036 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1994 "dhcp6_parser.cc"
    break;

  case 274: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1055 "dhcp6_parser.yy"
                                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2003 "dhcp6_parser.cc"
    break;

  case 275: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1060 "dhcp6_parser.yy"
                                                 {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2012 "dhcp6_parser.cc"
    break;

  case 276: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1065 "dhcp6_parser.yy"
                                                   {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2021 "dhcp6_parser.cc"
    break;

  case 277: // $@50: %empty
#line 1070 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2032 "dhcp6_parser.cc"
    break;

  case 278: // hooks_libraries: "hooks-libraries" $@50 ":" "[" hooks_libraries_list "]"
#line 1075 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2041 "dhcp6_parser.cc"
    break;

  case 283: // $@51: %empty
#line 1088 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2051 "dhcp6_parser.cc"
    break;

  case 284: // hooks_library: "{" $@51 hooks_params "}"
#line 1092 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2061 "dhcp6_parser.cc"
    break;

  case 285: // $@52: %empty
#line 1098 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2071 "dhcp6_parser.cc"
    break;

  case 286: // sub_hooks_library: "{" $@52 hooks_params "}"
#line 1102 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2081 "dhcp6_parser.cc"
    break;

  case 292: // $@53: %empty
#line 1117 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2089 "dhcp6_parser.cc"
    break;

  case 293: // library: "library" $@53 ":" "constant string"
#line 1119 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2099 "dhcp6_parser.cc"
    break;

  case 294: // $@54: %empty
#line 1125 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2107 "dhcp6_parser.cc"
    break;

  case 295: // parameters: "parameters" $@54 ":" map_value
#line 1127 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2116 "dhcp6_parser.cc"
    break;

  case 296: // $@55: %empty
#line 1133 "dhcp6_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2127 "dhcp6_parser.cc"
    break;

  case 297: // expired_leases_processing: "expired-leases-processing" $@55 ":" "{" expired_leases_params "}"
#line 1138 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2137 "dhcp6_parser.cc"
    break;

  case 306: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1156 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2146 "dhcp6_parser.cc"
    break;

  case 307: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1161 "dhcp6_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2155 "dhcp6_parser.cc"
    break;

  case 308: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1166 "dhcp6_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 309: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1171 "dhcp6_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 310: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1176 "dhcp6_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2182 "dhcp6_parser.cc"
    break;

  case 311: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1181 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2191 "dhcp6_parser.cc"
    break;

  case 312: // $@56: %empty
#line 1189 "dhcp6_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 313: // subnet6_list: "subnet6" $@56 ":" "[" subnet6_list_content "]"
#line 1194 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 318: // $@57: %empty
#line 1214 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 319: // subnet6: "{" $@57 subnet6_params "}"
#line 1218 "dhcp6_parser.yy"
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
#line 2247 "dhcp6_parser.cc"
    break;

  case 320: // $@58: %empty
#line 1240 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2257 "dhcp6_parser.cc"
    break;

  case 321: // sub_subnet6: "{" $@58 subnet6_params "}"
#line 1244 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2267 "dhcp6_parser.cc"
    break;

  case 360: // $@59: %empty
#line 1294 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp6_parser.cc"
    break;

  case 361: // subnet: "subnet" $@59 ":" "constant string"
#line 1296 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2285 "dhcp6_parser.cc"
    break;

  case 362: // $@60: %empty
#line 1302 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp6_parser.cc"
    break;

  case 363: // interface: "interface" $@60 ":" "constant string"
#line 1304 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2303 "dhcp6_parser.cc"
    break;

  case 364: // $@61: %empty
#line 1310 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2311 "dhcp6_parser.cc"
    break;

  case 365: // interface_id: "interface-id" $@61 ":" "constant string"
#line 1312 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc"
    break;

  case 366: // $@62: %empty
#line 1318 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2329 "dhcp6_parser.cc"
    break;

  case 367: // client_class: "client-class" $@62 ":" "constant string"
#line 1320 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2339 "dhcp6_parser.cc"
    break;

  case 368: // $@63: %empty
#line 1326 "dhcp6_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp6_parser.cc"
    break;

  case 369: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1331 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2359 "dhcp6_parser.cc"
    break;

  case 370: // $@64: %empty
#line 1336 "dhcp6_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2367 "dhcp6_parser.cc"
    break;

  case 371: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1338 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2376 "dhcp6_parser.cc"
    break;

  case 372: // hr_mode: "disabled"
#line 1343 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2382 "dhcp6_parser.cc"
    break;

  case 373: // hr_mode: "out-of-pool"
#line 1344 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2388 "dhcp6_parser.cc"
    break;

  case 374: // hr_mode: "global"
#line 1345 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2394 "dhcp6_parser.cc"
    break;

  case 375: // hr_mode: "all"
#line 1346 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2400 "dhcp6_parser.cc"
    break;

  case 376: // id: "id" ":" "integer"
#line 1349 "dhcp6_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2409 "dhcp6_parser.cc"
    break;

  case 377: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1354 "dhcp6_parser.yy"
                                         {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2418 "dhcp6_parser.cc"
    break;

  case 378: // $@65: %empty
#line 1361 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2429 "dhcp6_parser.cc"
    break;

  case 379: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1366 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2438 "dhcp6_parser.cc"
    break;

  case 384: // $@66: %empty
#line 1381 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 385: // shared_network: "{" $@66 shared_network_params "}"
#line 1385 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2456 "dhcp6_parser.cc"
    break;

  case 421: // $@67: %empty
#line 1432 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2467 "dhcp6_parser.cc"
    break;

  case 422: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1437 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc"
    break;

  case 423: // $@68: %empty
#line 1445 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2485 "dhcp6_parser.cc"
    break;

  case 424: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1448 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2493 "dhcp6_parser.cc"
    break;

  case 429: // $@69: %empty
#line 1464 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2503 "dhcp6_parser.cc"
    break;

  case 430: // option_def_entry: "{" $@69 option_def_params "}"
#line 1468 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2515 "dhcp6_parser.cc"
    break;

  case 431: // $@70: %empty
#line 1479 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 432: // sub_option_def: "{" $@70 option_def_params "}"
#line 1483 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2537 "dhcp6_parser.cc"
    break;

  case 448: // code: "code" ":" "integer"
#line 1515 "dhcp6_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2546 "dhcp6_parser.cc"
    break;

  case 450: // $@71: %empty
#line 1522 "dhcp6_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2554 "dhcp6_parser.cc"
    break;

  case 451: // option_def_type: "type" $@71 ":" "constant string"
#line 1524 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2564 "dhcp6_parser.cc"
    break;

  case 452: // $@72: %empty
#line 1530 "dhcp6_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2572 "dhcp6_parser.cc"
    break;

  case 453: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1532 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2582 "dhcp6_parser.cc"
    break;

  case 454: // $@73: %empty
#line 1538 "dhcp6_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2590 "dhcp6_parser.cc"
    break;

  case 455: // space: "space" $@73 ":" "constant string"
#line 1540 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 457: // $@74: %empty
#line 1548 "dhcp6_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2608 "dhcp6_parser.cc"
    break;

  case 458: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1550 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2618 "dhcp6_parser.cc"
    break;

  case 459: // option_def_array: "array" ":" "boolean"
#line 1556 "dhcp6_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2627 "dhcp6_parser.cc"
    break;

  case 460: // $@75: %empty
#line 1565 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 461: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1570 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2647 "dhcp6_parser.cc"
    break;

  case 466: // $@76: %empty
#line 1589 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2657 "dhcp6_parser.cc"
    break;

  case 467: // option_data_entry: "{" $@76 option_data_params "}"
#line 1593 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2666 "dhcp6_parser.cc"
    break;

  case 468: // $@77: %empty
#line 1601 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2676 "dhcp6_parser.cc"
    break;

  case 469: // sub_option_data: "{" $@77 option_data_params "}"
#line 1605 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 484: // $@78: %empty
#line 1638 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2693 "dhcp6_parser.cc"
    break;

  case 485: // option_data_data: "data" $@78 ":" "constant string"
#line 1640 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2703 "dhcp6_parser.cc"
    break;

  case 488: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1650 "dhcp6_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2712 "dhcp6_parser.cc"
    break;

  case 489: // option_data_always_send: "always-send" ":" "boolean"
#line 1655 "dhcp6_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2721 "dhcp6_parser.cc"
    break;

  case 490: // $@79: %empty
#line 1663 "dhcp6_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2732 "dhcp6_parser.cc"
    break;

  case 491: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1668 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2741 "dhcp6_parser.cc"
    break;

  case 496: // $@80: %empty
#line 1683 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2751 "dhcp6_parser.cc"
    break;

  case 497: // pool_list_entry: "{" $@80 pool_params "}"
#line 1687 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2761 "dhcp6_parser.cc"
    break;

  case 498: // $@81: %empty
#line 1693 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2771 "dhcp6_parser.cc"
    break;

  case 499: // sub_pool6: "{" $@81 pool_params "}"
#line 1697 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2781 "dhcp6_parser.cc"
    break;

  case 509: // $@82: %empty
#line 1716 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp6_parser.cc"
    break;

  case 510: // pool_entry: "pool" $@82 ":" "constant string"
#line 1718 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2799 "dhcp6_parser.cc"
    break;

  case 511: // $@83: %empty
#line 1724 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2807 "dhcp6_parser.cc"
    break;

  case 512: // user_context: "user-context" $@83 ":" map_value
#line 1726 "dhcp6_parser.yy"
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
#line 2834 "dhcp6_parser.cc"
    break;

  case 513: // $@84: %empty
#line 1749 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2842 "dhcp6_parser.cc"
    break;

  case 514: // comment: "comment" $@84 ":" "constant string"
#line 1751 "dhcp6_parser.yy"
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
#line 2871 "dhcp6_parser.cc"
    break;

  case 515: // $@85: %empty
#line 1779 "dhcp6_parser.yy"
                        {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2882 "dhcp6_parser.cc"
    break;

  case 516: // pd_pools_list: "pd-pools" $@85 ":" "[" pd_pools_list_content "]"
#line 1784 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2891 "dhcp6_parser.cc"
    break;

  case 521: // $@86: %empty
#line 1799 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2901 "dhcp6_parser.cc"
    break;

  case 522: // pd_pool_entry: "{" $@86 pd_pool_params "}"
#line 1803 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2913 "dhcp6_parser.cc"
    break;

  case 523: // $@87: %empty
#line 1811 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2923 "dhcp6_parser.cc"
    break;

  case 524: // sub_pd_pool: "{" $@87 pd_pool_params "}"
#line 1815 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2935 "dhcp6_parser.cc"
    break;

  case 538: // $@88: %empty
#line 1840 "dhcp6_parser.yy"
                  {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 539: // pd_prefix: "prefix" $@88 ":" "constant string"
#line 1842 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2953 "dhcp6_parser.cc"
    break;

  case 540: // pd_prefix_len: "prefix-len" ":" "integer"
#line 1848 "dhcp6_parser.yy"
                                        {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 541: // $@89: %empty
#line 1853 "dhcp6_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp6_parser.cc"
    break;

  case 542: // excluded_prefix: "excluded-prefix" $@89 ":" "constant string"
#line 1855 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2980 "dhcp6_parser.cc"
    break;

  case 543: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 1861 "dhcp6_parser.yy"
                                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2989 "dhcp6_parser.cc"
    break;

  case 544: // pd_delegated_len: "delegated-len" ":" "integer"
#line 1866 "dhcp6_parser.yy"
                                              {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2998 "dhcp6_parser.cc"
    break;

  case 545: // $@90: %empty
#line 1874 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3009 "dhcp6_parser.cc"
    break;

  case 546: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 1879 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3018 "dhcp6_parser.cc"
    break;

  case 551: // $@91: %empty
#line 1892 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3028 "dhcp6_parser.cc"
    break;

  case 552: // reservation: "{" $@91 reservation_params "}"
#line 1896 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3037 "dhcp6_parser.cc"
    break;

  case 553: // $@92: %empty
#line 1901 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3047 "dhcp6_parser.cc"
    break;

  case 554: // sub_reservation: "{" $@92 reservation_params "}"
#line 1905 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3056 "dhcp6_parser.cc"
    break;

  case 570: // $@93: %empty
#line 1932 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3067 "dhcp6_parser.cc"
    break;

  case 571: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 1937 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3076 "dhcp6_parser.cc"
    break;

  case 572: // $@94: %empty
#line 1942 "dhcp6_parser.yy"
                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3087 "dhcp6_parser.cc"
    break;

  case 573: // prefixes: "prefixes" $@94 ":" list_strings
#line 1947 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3096 "dhcp6_parser.cc"
    break;

  case 574: // $@95: %empty
#line 1952 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3104 "dhcp6_parser.cc"
    break;

  case 575: // duid: "duid" $@95 ":" "constant string"
#line 1954 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3114 "dhcp6_parser.cc"
    break;

  case 576: // $@96: %empty
#line 1960 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3122 "dhcp6_parser.cc"
    break;

  case 577: // hw_address: "hw-address" $@96 ":" "constant string"
#line 1962 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3132 "dhcp6_parser.cc"
    break;

  case 578: // $@97: %empty
#line 1968 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3140 "dhcp6_parser.cc"
    break;

  case 579: // hostname: "hostname" $@97 ":" "constant string"
#line 1970 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3150 "dhcp6_parser.cc"
    break;

  case 580: // $@98: %empty
#line 1976 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3158 "dhcp6_parser.cc"
    break;

  case 581: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 1978 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 582: // $@99: %empty
#line 1984 "dhcp6_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 583: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 1989 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3188 "dhcp6_parser.cc"
    break;

  case 584: // $@100: %empty
#line 1997 "dhcp6_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3199 "dhcp6_parser.cc"
    break;

  case 585: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2002 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3208 "dhcp6_parser.cc"
    break;

  case 588: // $@101: %empty
#line 2011 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3216 "dhcp6_parser.cc"
    break;

  case 589: // ip_address: "ip-address" $@101 ":" "constant string"
#line 2013 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3226 "dhcp6_parser.cc"
    break;

  case 590: // $@102: %empty
#line 2022 "dhcp6_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3237 "dhcp6_parser.cc"
    break;

  case 591: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2027 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 594: // $@103: %empty
#line 2036 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3256 "dhcp6_parser.cc"
    break;

  case 595: // client_class_entry: "{" $@103 client_class_params "}"
#line 2040 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 608: // $@104: %empty
#line 2065 "dhcp6_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc"
    break;

  case 609: // client_class_test: "test" $@104 ":" "constant string"
#line 2067 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3284 "dhcp6_parser.cc"
    break;

  case 610: // only_if_required: "only-if-required" ":" "boolean"
#line 2073 "dhcp6_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3293 "dhcp6_parser.cc"
    break;

  case 611: // $@105: %empty
#line 2081 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 612: // server_id: "server-id" $@105 ":" "{" server_id_params "}"
#line 2086 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3315 "dhcp6_parser.cc"
    break;

  case 624: // $@106: %empty
#line 2108 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3323 "dhcp6_parser.cc"
    break;

  case 625: // server_id_type: "type" $@106 ":" duid_type
#line 2110 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3332 "dhcp6_parser.cc"
    break;

  case 626: // duid_type: "LLT"
#line 2115 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3338 "dhcp6_parser.cc"
    break;

  case 627: // duid_type: "EN"
#line 2116 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3344 "dhcp6_parser.cc"
    break;

  case 628: // duid_type: "LL"
#line 2117 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3350 "dhcp6_parser.cc"
    break;

  case 629: // htype: "htype" ":" "integer"
#line 2120 "dhcp6_parser.yy"
                           {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3359 "dhcp6_parser.cc"
    break;

  case 630: // $@107: %empty
#line 2125 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3367 "dhcp6_parser.cc"
    break;

  case 631: // identifier: "identifier" $@107 ":" "constant string"
#line 2127 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3377 "dhcp6_parser.cc"
    break;

  case 632: // time: "time" ":" "integer"
#line 2133 "dhcp6_parser.yy"
                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3386 "dhcp6_parser.cc"
    break;

  case 633: // enterprise_id: "enterprise-id" ":" "integer"
#line 2138 "dhcp6_parser.yy"
                                           {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3395 "dhcp6_parser.cc"
    break;

  case 634: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2145 "dhcp6_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3404 "dhcp6_parser.cc"
    break;

  case 635: // $@108: %empty
#line 2152 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3415 "dhcp6_parser.cc"
    break;

  case 636: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2157 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3424 "dhcp6_parser.cc"
    break;

  case 644: // $@109: %empty
#line 2173 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3432 "dhcp6_parser.cc"
    break;

  case 645: // socket_type: "socket-type" $@109 ":" "constant string"
#line 2175 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3442 "dhcp6_parser.cc"
    break;

  case 646: // $@110: %empty
#line 2181 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3450 "dhcp6_parser.cc"
    break;

  case 647: // socket_name: "socket-name" $@110 ":" "constant string"
#line 2183 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3460 "dhcp6_parser.cc"
    break;

  case 648: // $@111: %empty
#line 2192 "dhcp6_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3471 "dhcp6_parser.cc"
    break;

  case 649: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2197 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3482 "dhcp6_parser.cc"
    break;

  case 658: // enable_queue: "enable-queue" ":" "boolean"
#line 2216 "dhcp6_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3491 "dhcp6_parser.cc"
    break;

  case 659: // $@112: %empty
#line 2221 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3499 "dhcp6_parser.cc"
    break;

  case 660: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2223 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3509 "dhcp6_parser.cc"
    break;

  case 661: // capacity: "capacity" ":" "integer"
#line 2229 "dhcp6_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 662: // $@113: %empty
#line 2234 "dhcp6_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3526 "dhcp6_parser.cc"
    break;

  case 663: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2236 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3535 "dhcp6_parser.cc"
    break;

  case 664: // $@114: %empty
#line 2243 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3546 "dhcp6_parser.cc"
    break;

  case 665: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2248 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3557 "dhcp6_parser.cc"
    break;

  case 666: // $@115: %empty
#line 2255 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3567 "dhcp6_parser.cc"
    break;

  case 667: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2259 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3577 "dhcp6_parser.cc"
    break;

  case 688: // enable_updates: "enable-updates" ":" "boolean"
#line 2289 "dhcp6_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3586 "dhcp6_parser.cc"
    break;

  case 689: // $@116: %empty
#line 2295 "dhcp6_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3594 "dhcp6_parser.cc"
    break;

  case 690: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2297 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3604 "dhcp6_parser.cc"
    break;

  case 691: // $@117: %empty
#line 2303 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3612 "dhcp6_parser.cc"
    break;

  case 692: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2305 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3622 "dhcp6_parser.cc"
    break;

  case 693: // server_port: "server-port" ":" "integer"
#line 2311 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3631 "dhcp6_parser.cc"
    break;

  case 694: // $@118: %empty
#line 2316 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3639 "dhcp6_parser.cc"
    break;

  case 695: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2318 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3649 "dhcp6_parser.cc"
    break;

  case 696: // sender_port: "sender-port" ":" "integer"
#line 2324 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 697: // max_queue_size: "max-queue-size" ":" "integer"
#line 2329 "dhcp6_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3667 "dhcp6_parser.cc"
    break;

  case 698: // $@119: %empty
#line 2334 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3675 "dhcp6_parser.cc"
    break;

  case 699: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2336 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3684 "dhcp6_parser.cc"
    break;

  case 700: // ncr_protocol_value: "UDP"
#line 2342 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3690 "dhcp6_parser.cc"
    break;

  case 701: // ncr_protocol_value: "TCP"
#line 2343 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3696 "dhcp6_parser.cc"
    break;

  case 702: // $@120: %empty
#line 2346 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3704 "dhcp6_parser.cc"
    break;

  case 703: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2348 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3714 "dhcp6_parser.cc"
    break;

  case 704: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2355 "dhcp6_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3723 "dhcp6_parser.cc"
    break;

  case 705: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2361 "dhcp6_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3732 "dhcp6_parser.cc"
    break;

  case 706: // $@121: %empty
#line 2367 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3740 "dhcp6_parser.cc"
    break;

  case 707: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2369 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3749 "dhcp6_parser.cc"
    break;

  case 708: // $@122: %empty
#line 2375 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 709: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2377 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 710: // $@123: %empty
#line 2384 "dhcp6_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 711: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2386 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 712: // $@124: %empty
#line 2393 "dhcp6_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 713: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2395 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3803 "dhcp6_parser.cc"
    break;

  case 714: // $@125: %empty
#line 2404 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 715: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2409 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 716: // $@126: %empty
#line 2415 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 717: // sub_config_control: "{" $@126 config_control_params "}"
#line 2419 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3843 "dhcp6_parser.cc"
    break;

  case 722: // $@127: %empty
#line 2434 "dhcp6_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 723: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2439 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 724: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2444 "dhcp6_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3872 "dhcp6_parser.cc"
    break;

  case 725: // $@128: %empty
#line 2451 "dhcp6_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 726: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2456 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 729: // $@129: %empty
#line 2468 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 730: // logger_entry: "{" $@129 logger_params "}"
#line 2472 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3910 "dhcp6_parser.cc"
    break;

  case 740: // debuglevel: "debuglevel" ":" "integer"
#line 2489 "dhcp6_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3919 "dhcp6_parser.cc"
    break;

  case 741: // $@130: %empty
#line 2494 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3927 "dhcp6_parser.cc"
    break;

  case 742: // severity: "severity" $@130 ":" "constant string"
#line 2496 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3937 "dhcp6_parser.cc"
    break;

  case 743: // $@131: %empty
#line 2502 "dhcp6_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3948 "dhcp6_parser.cc"
    break;

  case 744: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2507 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3957 "dhcp6_parser.cc"
    break;

  case 747: // $@132: %empty
#line 2516 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3967 "dhcp6_parser.cc"
    break;

  case 748: // output_entry: "{" $@132 output_params_list "}"
#line 2520 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 3975 "dhcp6_parser.cc"
    break;

  case 756: // $@133: %empty
#line 2535 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3983 "dhcp6_parser.cc"
    break;

  case 757: // output: "output" $@133 ":" "constant string"
#line 2537 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3993 "dhcp6_parser.cc"
    break;

  case 758: // flush: "flush" ":" "boolean"
#line 2543 "dhcp6_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4002 "dhcp6_parser.cc"
    break;

  case 759: // maxsize: "maxsize" ":" "integer"
#line 2548 "dhcp6_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4011 "dhcp6_parser.cc"
    break;

  case 760: // maxver: "maxver" ":" "integer"
#line 2553 "dhcp6_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4020 "dhcp6_parser.cc"
    break;

  case 761: // $@134: %empty
#line 2558 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4028 "dhcp6_parser.cc"
    break;

  case 762: // pattern: "pattern" $@134 ":" "constant string"
#line 2560 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4038 "dhcp6_parser.cc"
    break;


#line 4042 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -925;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     557,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,    41,    33,    44,    46,    50,
      52,    56,    62,    89,   101,   109,   132,   134,   148,   179,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,    33,  -123,
     225,   116,    27,   484,    51,   186,   263,    59,    71,   269,
     -65,   455,   119,  -925,   237,   244,   276,   280,   286,  -925,
     299,  -925,  -925,  -925,  -925,  -925,  -925,   325,   332,   340,
     341,   375,   377,   379,   381,   385,   386,   397,   398,  -925,
     401,   404,   407,   409,   411,  -925,  -925,  -925,   413,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,   414,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,   417,  -925,    75,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
     418,  -925,    92,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,   419,   420,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,    96,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,   112,  -925,  -925,  -925,  -925,  -925,   421,  -925,   423,
     429,  -925,  -925,  -925,  -925,  -925,  -925,   114,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,   356,   290,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,   358,  -925,  -925,   433,  -925,
    -925,  -925,   434,  -925,  -925,   439,   438,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
     445,   448,  -925,  -925,  -925,  -925,   446,   450,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
     115,  -925,  -925,  -925,   454,  -925,  -925,   457,  -925,   460,
     461,  -925,  -925,   462,   463,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,   184,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
     465,   192,  -925,  -925,  -925,  -925,    33,    33,  -925,   248,
     469,  -925,   470,   472,   473,   474,   476,   477,   288,   291,
     295,   302,   303,   305,   310,   311,   313,   312,   316,   318,
     481,   319,   320,   322,   323,   324,   489,   491,   513,   326,
     518,   520,   521,   522,   535,   536,   546,   547,   549,   550,
     551,   552,   553,   554,   555,   556,   366,   559,   561,   562,
     563,   564,   565,   574,  -925,   116,  -925,   575,   383,    27,
    -925,   577,   578,   580,   581,   583,   393,   394,   586,   590,
     591,   484,  -925,   592,    51,  -925,   593,   403,   595,   406,
     408,   186,  -925,   613,   614,   618,   622,   623,   624,   625,
    -925,   263,  -925,   626,   627,   437,   629,   630,   636,   444,
    -925,    71,   638,   447,   449,  -925,   269,   641,   643,    74,
    -925,   451,   646,   647,   464,   648,   466,   467,   651,   652,
     478,   479,   653,   656,   659,   673,   455,  -925,   683,   495,
     119,  -925,  -925,  -925,   692,   690,   504,   693,   694,   695,
     696,   699,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,   505,  -925,  -925,  -925,  -925,  -925,
    -100,   511,   514,  -925,   706,   709,   710,   711,   523,   298,
     714,   715,   716,   717,   719,   718,   722,   724,   723,   725,
    -925,   726,   727,   728,   744,   530,   537,   747,  -925,   748,
    -925,  -925,   749,   750,   566,   567,   568,  -925,  -925,   748,
     569,   751,  -925,   570,  -925,   571,  -925,   572,  -925,  -925,
    -925,   748,   748,   748,   573,   576,   579,   582,  -925,   584,
     585,  -925,   587,   588,   589,  -925,  -925,   594,  -925,  -925,
    -925,   597,   711,  -925,  -925,   598,   599,  -925,   600,  -925,
    -925,   100,   604,  -925,  -925,  -100,   601,   602,   603,  -925,
     752,  -925,  -925,    33,   116,  -925,   119,    27,   285,   285,
     762,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
     764,   765,   767,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,   768,   -73,    33,   294,   674,   773,   777,   778,   235,
      64,    67,   136,   188,   455,  -925,  -925,   779,  -925,  -925,
     780,   791,  -925,  -925,  -925,  -925,  -925,   -61,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,   762,  -925,   205,
     216,   223,  -925,  -925,  -925,  -925,   712,   755,   795,   796,
     797,  -925,   798,   799,  -925,  -925,  -925,   800,   801,   802,
     803,  -925,   230,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,   243,  -925,   804,   753,  -925,  -925,
     805,   806,  -925,  -925,   807,   809,  -925,  -925,   810,   812,
    -925,  -925,   811,   815,  -925,  -925,  -925,    78,  -925,  -925,
    -925,   813,  -925,  -925,  -925,   146,  -925,  -925,  -925,  -925,
     247,  -925,  -925,  -925,   198,  -925,  -925,   814,   818,  -925,
    -925,   816,   820,  -925,   821,   822,   823,   824,   825,   826,
     273,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
     827,   828,   829,  -925,  -925,  -925,  -925,   274,  -925,  -925,
    -925,  -925,  -925,  -925,   830,   831,   832,  -925,   287,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
     289,  -925,  -925,  -925,   833,  -925,   834,  -925,  -925,  -925,
     293,  -925,  -925,  -925,  -925,  -925,   296,  -925,   233,  -925,
     645,  -925,   835,   837,  -925,  -925,   836,   840,  -925,  -925,
    -925,   838,  -925,   839,  -925,  -925,  -925,   843,   844,   845,
     846,   649,   611,   657,   654,   658,   850,   660,   661,   853,
     854,   855,   665,   666,   667,   668,   285,  -925,  -925,   285,
    -925,   762,   484,  -925,   764,    71,  -925,   765,   269,  -925,
     767,   620,  -925,   768,   -73,  -925,  -925,   294,  -925,   858,
     674,  -925,    38,   773,  -925,   263,  -925,   777,   -65,  -925,
     778,   670,   671,   672,   675,   677,   678,   235,  -925,   864,
     865,   680,   681,   684,    64,  -925,   689,   703,   731,    67,
    -925,   884,   885,   136,  -925,   707,   901,   737,   902,   188,
    -925,  -925,   197,   779,  -925,  -925,   911,   917,    51,  -925,
     780,   186,  -925,   791,   941,  -925,  -925,   374,   757,   760,
     763,  -925,  -925,  -925,  -925,  -925,   771,  -925,  -925,   783,
     786,   788,  -925,  -925,  -925,  -925,  -925,   297,  -925,   300,
    -925,   950,  -925,   953,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,   329,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,   790,  -925,  -925,   969,  -925,  -925,  -925,
    -925,  -925,   979,   986,  -925,  -925,  -925,  -925,  -925,   983,
    -925,   343,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
      81,   808,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
     817,   819,  -925,  -925,   841,  -925,    33,  -925,  -925,   988,
    -925,  -925,  -925,  -925,  -925,   344,  -925,  -925,  -925,  -925,
    -925,  -925,   842,   345,  -925,   360,  -925,   847,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,   620,  -925,  -925,   989,   852,  -925,
      38,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,   991,   849,   992,   197,  -925,  -925,  -925,  -925,
    -925,  -925,   848,  -925,  -925,   993,  -925,   856,  -925,  -925,
     990,  -925,  -925,   253,  -925,    12,   990,  -925,  -925,   995,
     997,  1000,  -925,   362,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  1001,   857,   860,   861,  1002,    12,  -925,   859,  -925,
    -925,  -925,   863,  -925,  -925,  -925
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   158,     9,   320,    11,
     498,    13,   523,    15,   553,    17,   423,    19,   431,    21,
     468,    23,   285,    25,   666,    27,   716,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   555,     0,   433,   470,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   119,   714,   156,   170,   172,   174,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   154,
       0,     0,     0,     0,     0,   136,   143,   145,     0,   312,
     421,   460,   511,   513,   370,   378,   245,   262,   253,   238,
     590,   545,   277,   296,   611,     0,   264,   635,   648,   664,
     147,   149,   725,     0,   118,     0,    64,    66,    67,    68,
      69,    70,    71,    72,    73,    74,   102,   103,   104,    75,
     108,   109,   110,   111,   112,   113,   106,   107,   114,   115,
     116,   100,    78,    79,    80,    81,    97,    82,    84,    83,
     117,    88,    89,    76,   101,    77,    86,    87,    95,    96,
      98,    85,    90,    91,    92,    93,    94,    99,   105,   167,
       0,   166,     0,   160,   162,   163,   164,   165,   490,   515,
     360,   362,   364,     0,     0,   368,   366,   584,   359,   324,
     325,   326,   327,   328,   329,   330,   331,   347,   348,   349,
     352,   353,   354,   355,   356,   357,   350,   351,   358,     0,
     322,   335,   336,   337,   340,   341,   343,   338,   339,   332,
     333,   345,   346,   334,   342,   344,   509,   508,   504,   505,
     503,     0,   500,   502,   506,   507,   538,     0,   541,     0,
       0,   537,   531,   532,   530,   535,   536,     0,   525,   527,
     528,   533,   534,   529,   582,   570,   572,   574,   576,   578,
     580,   569,   566,   567,   568,     0,   556,   557,   561,   562,
     559,   563,   564,   565,   560,     0,   450,   218,     0,   454,
     452,   457,     0,   446,   447,     0,   434,   435,   437,   449,
     438,   439,   440,   456,   441,   442,   443,   444,   445,   484,
       0,     0,   482,   483,   486,   487,     0,   471,   472,   474,
     475,   476,   477,   478,   479,   480,   481,   292,   294,   289,
       0,   287,   290,   291,     0,   689,   691,     0,   694,     0,
       0,   698,   702,     0,     0,   706,   708,   710,   712,   687,
     685,   686,     0,   668,   670,   682,   671,   672,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   683,   684,   722,
       0,     0,   718,   720,   721,    46,     0,     0,    39,     0,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    57,     0,    63,     0,     0,     0,
     159,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   321,     0,     0,   499,     0,     0,     0,     0,
       0,     0,   524,     0,     0,     0,     0,     0,     0,     0,
     554,     0,   424,     0,     0,     0,     0,     0,     0,     0,
     432,     0,     0,     0,     0,   469,     0,     0,     0,     0,
     286,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   667,     0,     0,
       0,   717,    50,    43,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,     0,   152,   153,   133,   134,   135,
       0,     0,     0,   151,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     634,     0,     0,     0,     0,     0,     0,     0,    65,     0,
     169,   161,     0,     0,     0,     0,     0,   376,   377,     0,
       0,     0,   323,     0,   501,     0,   540,     0,   543,   544,
     526,     0,     0,     0,     0,     0,     0,     0,   558,     0,
       0,   448,     0,     0,     0,   459,   436,     0,   488,   489,
     473,     0,     0,   288,   688,     0,     0,   693,     0,   696,
     697,     0,     0,   704,   705,     0,     0,     0,     0,   669,
       0,   724,   719,     0,     0,   120,     0,     0,     0,     0,
     176,   155,   138,   139,   140,   141,   142,   137,   144,   146,
     314,   425,   462,    40,   512,   514,   372,   373,   374,   375,
     371,   380,     0,    47,     0,     0,     0,   547,   279,     0,
       0,     0,     0,     0,     0,   148,   150,     0,    51,   168,
     492,   517,   361,   363,   365,   369,   367,     0,   510,   539,
     542,   583,   571,   573,   575,   577,   579,   581,   451,   219,
     455,   453,   458,   485,   293,   295,   690,   692,   695,   700,
     701,   699,   703,   707,   709,   711,   713,   176,    44,     0,
       0,     0,   205,   211,   213,   215,     0,     0,     0,     0,
       0,   229,     0,     0,   232,   234,   236,     0,     0,     0,
       0,   204,     0,   182,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   196,   203,   197,   198,   199,   194,
     195,   200,   201,   202,     0,   180,     0,   177,   178,   318,
       0,   315,   316,   429,     0,   426,   427,   466,     0,   463,
     464,   384,     0,   381,   382,   251,   252,     0,   247,   249,
     250,     0,   260,   261,   257,     0,   255,   258,   259,   243,
       0,   240,   242,   594,     0,   592,   551,     0,   548,   549,
     283,     0,   280,   281,     0,     0,     0,     0,     0,     0,
       0,   298,   300,   301,   302,   303,   304,   305,   624,   630,
       0,     0,     0,   623,   620,   621,   622,     0,   613,   615,
     618,   616,   617,   619,     0,     0,     0,   273,     0,   266,
     268,   269,   270,   271,   272,   644,   646,   643,   641,   642,
       0,   637,   639,   640,     0,   659,     0,   662,   655,   656,
       0,   650,   652,   653,   654,   657,     0,   729,     0,   727,
      53,   496,     0,   493,   494,   521,     0,   518,   519,   588,
     587,     0,   586,     0,    61,   715,   157,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   171,   173,     0,
     175,     0,     0,   313,     0,   433,   422,     0,   470,   461,
       0,     0,   379,     0,     0,   246,   263,     0,   254,     0,
       0,   239,   596,     0,   591,   555,   546,     0,     0,   278,
       0,     0,     0,     0,     0,     0,     0,     0,   297,     0,
       0,     0,     0,     0,     0,   612,     0,     0,     0,     0,
     265,     0,     0,     0,   636,     0,     0,     0,     0,     0,
     649,   665,     0,     0,   726,    55,     0,    54,     0,   491,
       0,     0,   516,     0,     0,   585,   723,     0,     0,     0,
       0,   217,   220,   221,   222,   223,     0,   231,   224,     0,
       0,     0,   226,   227,   228,   225,   183,     0,   179,     0,
     317,     0,   428,     0,   465,   420,   399,   400,   401,   403,
     404,   405,   392,   393,   408,   409,   410,   413,   414,   415,
     416,   417,   418,   411,   412,   419,   388,   389,   390,   391,
     397,   398,   396,   402,     0,   386,   394,   406,   407,   395,
     383,   248,   256,     0,   241,   608,     0,   606,   607,   603,
     604,   605,     0,   597,   598,   600,   601,   602,   593,     0,
     550,     0,   282,   306,   307,   308,   309,   310,   311,   299,
       0,     0,   629,   632,   633,   614,   274,   275,   276,   267,
       0,     0,   638,   658,     0,   661,     0,   651,   743,     0,
     741,   739,   733,   737,   738,     0,   731,   735,   736,   734,
     728,    52,     0,     0,   495,     0,   520,     0,   207,   208,
     209,   210,   206,   212,   214,   216,   230,   233,   235,   237,
     181,   319,   430,   467,     0,   385,   244,     0,     0,   595,
       0,   552,   284,   626,   627,   628,   625,   631,   645,   647,
     660,   663,     0,     0,     0,     0,   730,    56,   497,   522,
     589,   387,     0,   610,   599,     0,   740,     0,   732,   609,
       0,   742,   747,     0,   745,     0,     0,   744,   756,     0,
       0,     0,   761,     0,   749,   751,   752,   753,   754,   755,
     746,     0,     0,     0,     0,     0,     0,   748,     0,   758,
     759,   760,     0,   750,   757,   762
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,   -10,  -925,  -530,  -925,
     376,  -925,  -925,  -925,  -925,   141,  -925,  -551,  -925,  -925,
    -925,   -71,  -925,  -925,  -925,  -925,  -925,  -925,   353,   560,
    -925,  -925,   -59,   -43,   -42,   -40,   -39,   -28,   -27,   -26,
     -23,   -21,   -15,  -925,    -9,    -3,    -1,    17,  -925,   365,
      18,  -925,    20,  -925,    25,  -925,    28,  -925,    30,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,   357,   558,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,   279,  -925,
      77,  -925,  -637,    83,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,   -67,  -925,  -675,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,    60,  -925,  -925,
    -925,  -925,  -925,    68,  -659,  -925,  -925,  -925,  -925,    66,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,    36,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,    57,  -925,  -925,  -925,    58,
     519,  -925,  -925,  -925,  -925,  -925,  -925,  -925,    53,  -925,
    -925,  -925,  -925,  -925,  -925,  -924,  -925,  -925,  -925,    85,
    -925,  -925,  -925,    90,   596,  -925,  -925,  -923,  -925,  -922,
    -925,    35,  -925,    37,  -925,    32,  -925,  -925,  -925,  -916,
    -925,  -925,  -925,  -925,    80,  -925,  -925,  -133,   957,  -925,
    -925,  -925,  -925,  -925,    91,  -925,  -925,  -925,    94,  -925,
     539,  -925,   -66,  -925,  -925,  -925,  -925,  -925,   -47,  -925,
    -925,  -925,  -925,  -925,    13,  -925,  -925,  -925,    87,  -925,
    -925,  -925,    99,  -925,   545,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,    42,  -925,  -925,  -925,
      54,   605,  -925,  -925,   -55,  -925,     1,  -925,  -925,  -925,
    -925,  -925,    45,  -925,  -925,  -925,    48,   606,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,   -57,  -925,  -925,  -925,    93,
    -925,  -925,  -925,    98,  -925,   607,   354,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -915,  -925,  -925,  -925,  -925,  -925,  -925,  -925,   102,  -925,
    -925,  -925,  -106,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
      82,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,    76,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,    69,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,   378,   544,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,  -925,
    -925,  -925,  -925,   415,   543,  -925,  -925,  -925,  -925,  -925,
    -925,    72,  -925,  -925,  -111,  -925,  -925,  -925,  -925,  -925,
    -925,  -130,  -925,  -925,  -149,  -925,  -925,  -925,  -925,  -925,
    -925,  -925
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     674,    87,    88,    41,    68,    84,    85,   699,   900,  1006,
    1007,   761,    43,    70,    90,   400,    45,    71,   145,   146,
     147,   402,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   426,   667,
     164,   427,   165,   428,   166,   451,   167,   452,   168,   169,
     170,   171,   420,   172,   404,    47,    72,   202,   203,   204,
     457,   205,   173,   405,   174,   406,   175,   407,   786,   787,
     788,   939,   762,   763,   764,   917,  1152,   765,   918,   766,
     919,   767,   920,   768,   769,   494,   770,   771,   772,   773,
     774,   775,   776,   777,   778,   779,   926,   780,   781,   929,
     782,   930,   783,   931,   176,   440,   820,   821,   822,   959,
     177,   437,   807,   808,   809,   810,   178,   439,   815,   816,
     817,   818,   179,   438,   180,   447,   868,   869,   870,   871,
     872,   181,   443,   831,   832,   833,   968,    63,    80,   350,
     351,   352,   507,   353,   508,   182,   444,   840,   841,   842,
     843,   844,   845,   846,   847,   183,   430,   790,   791,   792,
     942,    49,    73,   239,   240,   241,   463,   242,   464,   243,
     465,   244,   469,   245,   468,   184,   435,   680,   247,   248,
     185,   436,   802,   803,   804,   951,  1074,  1075,   186,   431,
      57,    77,   794,   795,   796,   945,    59,    78,   315,   316,
     317,   318,   319,   320,   321,   493,   322,   497,   323,   496,
     324,   325,   498,   326,   187,   432,   798,   799,   800,   948,
      61,    79,   336,   337,   338,   339,   340,   502,   341,   342,
     343,   344,   250,   461,   902,   903,   904,  1008,    51,    74,
     261,   262,   263,   473,   188,   433,   189,   434,   253,   462,
     906,   907,   908,  1011,    53,    75,   277,   278,   279,   476,
     280,   281,   478,   282,   283,   190,   442,   827,   828,   829,
     965,    55,    76,   295,   296,   297,   298,   484,   299,   485,
     300,   486,   301,   487,   302,   488,   303,   489,   304,   483,
     255,   470,   911,   912,  1014,   191,   441,   824,   825,   962,
    1092,  1093,  1094,  1095,  1096,  1167,  1097,   192,   445,   857,
     858,   859,   979,  1176,   860,   861,   980,   862,   863,   193,
     194,   448,   880,   881,   882,   991,   883,   992,   195,   449,
     890,   891,   892,   893,   996,   894,   895,   998,   196,   450,
      65,    81,   372,   373,   374,   375,   512,   376,   513,   377,
     378,   515,   379,   380,   381,   518,   731,   382,   519,   383,
     384,   385,   522,   386,   523,   387,   524,   388,   525,   197,
     403,    67,    82,   391,   392,   393,   528,   394,   198,   453,
     898,   899,  1002,  1135,  1136,  1137,  1138,  1184,  1139,  1182,
    1203,  1204,  1205,  1213,  1214,  1215,  1221,  1216,  1217,  1218,
    1219,  1225
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     144,   201,   218,   257,   271,   291,    38,   313,   332,   349,
     369,   314,   333,   334,   219,   854,   254,   206,   251,   264,
     275,   293,   784,   327,   345,   814,   370,  1067,  1068,  1069,
     220,   221,   335,   222,   223,  1073,  1079,   673,    31,   805,
      32,    30,    33,   199,   200,   224,   225,   226,   705,   285,
     227,    42,   228,    44,   347,   348,   909,    46,   229,    48,
     711,   712,   713,    50,   230,   662,   663,   664,   665,    52,
     231,    86,   232,   207,   252,   265,   276,   294,   455,   328,
     346,   954,   371,   456,   955,   848,   249,   260,   274,   292,
     233,   234,   306,   235,   747,   459,    54,   666,   236,   471,
     460,   237,   673,   238,   472,   246,   121,   307,    56,   258,
     272,   259,   273,   122,   123,   474,    58,   481,   509,   121,
     475,   806,   482,   510,   122,   123,   120,    91,    92,   143,
     256,    93,   389,   390,    94,    95,    96,   122,   123,    60,
     307,    62,   308,   309,  1085,  1086,   310,   311,   312,   957,
     122,   123,   958,   122,   123,    64,   215,   122,   123,   216,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,  1208,    66,   526,  1209,  1210,
    1211,  1212,   527,   347,   348,   530,   849,   850,   851,   852,
     531,   963,   122,   123,   964,   864,   865,   866,   455,   124,
    1173,  1174,  1175,   914,   125,   126,   127,   128,   129,   530,
     130,   143,   122,   123,   915,   131,   459,    34,    35,    36,
      37,   916,   143,   936,   132,    89,  1003,   133,   937,  1004,
    1067,  1068,  1069,   395,   134,   143,   936,   396,  1073,  1079,
     960,   938,   135,   136,   121,   961,  1206,   137,   143,  1207,
     138,   143,   729,   730,   139,   143,   307,   266,   267,   268,
     269,   270,   122,   123,   122,   123,   977,   984,   875,   876,
     397,   978,   985,   122,   123,   140,   141,   142,   398,   399,
     989,   215,   993,   491,   216,   990,   999,   994,   814,   526,
     936,  1000,  1037,   471,  1001,  1160,   742,   401,  1161,   854,
     143,   743,   744,   745,   746,   747,   748,   749,   750,   751,
     752,   753,   754,   755,   756,   757,   758,   759,   760,   408,
     143,   121,  1164,   884,   885,   886,   409,  1165,   307,   329,
     308,   309,   330,   331,   410,   411,   509,  1185,   474,   122,
     123,  1172,  1186,  1188,   307,   122,   123,   834,   835,   836,
     837,   838,   839,   481,   490,  1226,   492,   284,  1189,  1128,
    1227,  1129,  1130,   285,   286,   287,   288,   289,   290,   412,
     143,   413,   887,   414,   144,   415,   532,   533,   201,   416,
     417,   143,   676,   677,   678,   679,  1148,  1149,  1150,  1151,
     218,   418,   419,   257,   206,   421,   805,   812,   422,   813,
     271,   423,   219,   424,   254,   425,   251,   429,   446,   264,
     291,   454,   458,   466,   467,   477,   275,   479,   220,   221,
     313,   222,   223,   480,   314,   332,   293,   495,   499,   333,
     334,   501,   534,   224,   225,   226,   327,   500,   227,   503,
     228,   345,   504,   506,   505,   369,   229,   143,   511,   335,
     207,   514,   230,   143,   516,   517,   520,   521,   231,   529,
     232,   370,   252,   535,   536,   265,   537,   538,   539,   143,
     540,   541,   276,   542,   249,   554,   543,   260,   233,   234,
     544,   235,   294,   560,   274,   561,   236,   545,   546,   237,
     547,   238,   328,   246,   292,   548,   549,   346,   551,   258,
     550,   259,   552,   553,   555,   556,   272,   562,   273,   557,
     558,   559,   564,   563,   565,   566,   567,   371,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   568,
     569,   122,   123,   112,   113,   114,   115,   116,   117,   118,
     570,   571,   121,   572,   573,   574,   575,   576,   577,   578,
     579,   580,   208,   581,   209,   582,   583,   584,   585,   586,
     122,   123,   210,   211,   212,   213,   214,   124,   587,   589,
     590,   592,   593,   144,   594,   595,   201,   596,   597,   215,
     599,   598,   216,   131,   600,   601,   603,   605,   606,   607,
     217,   608,   206,   609,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   611,   612,   853,
     867,   877,   613,   369,   367,   368,   614,   615,   616,   617,
     619,   620,   621,   622,   623,   855,   873,   878,   888,   370,
     624,   625,   627,   738,   628,   631,   629,   632,   634,   143,
     635,   636,   638,   140,   141,   641,   642,   645,   207,   637,
     646,   639,   640,   647,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   643,   644,   648,   143,   112,
     113,   114,   115,   116,   117,   118,   119,   650,   121,   307,
     651,   856,   874,   879,   889,   371,   653,   654,   655,   661,
     656,   657,   658,   659,   660,   668,   122,   123,   669,   211,
     212,   670,   214,   124,   671,   672,   921,   675,    32,   681,
     682,   683,   684,   686,   695,   215,   685,   687,   216,   688,
     689,   696,   690,   691,   692,   693,   217,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   694,   697,   698,   700,   701,   941,   737,   707,   922,
     702,   703,   704,   706,   708,   709,   710,   714,   732,   785,
     715,   789,   793,   716,   797,   801,   717,   819,   718,   719,
     823,   720,   721,   722,   826,   830,   897,   901,   723,   140,
     141,   724,   726,   727,   728,   734,   735,   736,   905,   923,
     924,   925,   927,   928,   932,   933,   934,   935,  1022,   944,
     940,   943,   947,   946,   143,   950,   949,   952,   953,   956,
     966,   967,   969,   970,   811,   971,   972,   973,   974,   975,
     976,   981,   982,   983,   986,   987,   988,   995,   997,  1005,
    1010,  1009,  1012,  1013,  1021,  1016,  1015,  1017,  1018,  1019,
    1020,  1024,  1023,  1025,  1026,  1027,  1028,  1029,  1030,  1031,
    1032,  1033,  1083,  1035,  1034,  1103,  1104,  1105,  1110,  1111,
    1106,   218,  1107,  1108,   313,  1112,  1113,   332,   314,  1114,
    1045,   333,   334,   219,  1066,   254,  1116,   251,  1120,  1121,
     327,  1087,  1046,   345,   291,  1088,  1077,   349,  1117,   220,
     221,   335,   222,   223,  1123,  1124,  1126,  1090,  1047,  1048,
     293,  1049,  1050,   853,   224,   225,   226,  1141,   867,   227,
    1142,   228,   877,  1051,  1052,  1053,  1118,   229,  1054,   855,
    1055,  1131,  1125,   230,   873,  1132,  1056,   257,   878,   231,
     271,   232,  1057,   252,   888,  1147,   328,  1133,  1058,   346,
    1059,  1153,  1078,   264,  1154,   249,   275,  1155,  1162,   233,
     234,  1163,   235,  1091,  1076,  1156,   294,   236,  1060,  1061,
     237,  1062,   238,  1168,   246,  1089,  1063,  1157,   292,  1064,
    1158,  1065,  1159,  1072,  1166,   856,  1070,  1169,  1071,  1170,
     874,  1171,  1183,  1192,   879,  1195,  1197,  1202,  1200,  1222,
     889,  1223,  1177,  1134,  1224,  1228,  1232,   739,   725,   265,
     733,  1178,   276,  1179,   741,   588,   913,   591,  1038,  1036,
    1084,   260,  1081,  1082,   274,  1119,  1101,  1102,   633,  1040,
    1109,  1191,  1039,  1080,   305,  1180,  1187,  1044,  1042,  1041,
     626,  1190,  1199,   258,  1196,   259,   272,  1043,   273,  1193,
    1201,   630,  1144,  1234,  1229,  1230,  1231,  1235,  1146,  1145,
    1100,   910,  1143,  1099,  1194,  1098,  1115,   602,  1127,  1122,
     649,   740,   896,   652,  1198,  1140,  1220,  1233,     0,   604,
       0,     0,     0,     0,     0,     0,     0,   610,     0,     0,
       0,     0,     0,  1045,     0,     0,     0,  1066,   618,  1087,
       0,     0,     0,  1088,     0,  1046,     0,     0,     0,  1077,
       0,     0,     0,     0,  1131,  1090,  1181,     0,  1132,     0,
       0,  1047,  1048,     0,  1049,  1050,     0,     0,     0,     0,
    1133,     0,     0,     0,     0,     0,  1051,  1052,  1053,     0,
       0,  1054,     0,  1055,     0,     0,     0,     0,     0,  1056,
       0,     0,     0,     0,     0,  1057,     0,     0,     0,     0,
       0,  1058,     0,  1059,     0,  1078,     0,     0,     0,     0,
       0,  1091,     0,     0,     0,     0,     0,  1076,     0,     0,
       0,  1060,  1061,  1089,  1062,     0,  1134,     0,     0,  1063,
       0,     0,  1064,     0,  1065,     0,  1072,     0,     0,  1070,
       0,  1071
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    78,    79,    79,    73,   690,    73,    72,    73,    74,
      75,    76,   659,    78,    79,   684,    81,   951,   951,   951,
      73,    73,    79,    73,    73,   951,   951,   567,     5,   112,
       7,     0,     9,    16,    17,    73,    73,    73,   599,   110,
      73,     7,    73,     7,   119,   120,   117,     7,    73,     7,
     611,   612,   613,     7,    73,   165,   166,   167,   168,     7,
      73,   194,    73,    72,    73,    74,    75,    76,     3,    78,
      79,     3,    81,     8,     6,    21,    73,    74,    75,    76,
      73,    73,    21,    73,    30,     3,     7,   197,    73,     3,
       8,    73,   632,    73,     8,    73,    68,    69,     7,    74,
      75,    74,    75,    86,    87,     3,     7,     3,     3,    68,
       8,   194,     8,     8,    86,    87,    67,    11,    12,   194,
      79,    15,    13,    14,    18,    19,    20,    86,    87,     7,
      69,     7,    71,    72,   106,   107,    75,    76,    77,     3,
      86,    87,     6,    86,    87,     7,   105,    86,    87,   108,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,   173,     7,     3,   176,   177,
     178,   179,     8,   119,   120,     3,   132,   133,   134,   135,
       8,     3,    86,    87,     6,   138,   139,   140,     3,    93,
     129,   130,   131,     8,    98,    99,   100,   101,   102,     3,
     104,   194,    86,    87,     8,   109,     3,   194,   195,   196,
     197,     8,   194,     3,   118,    10,     3,   121,     8,     6,
    1164,  1164,  1164,     6,   128,   194,     3,     3,  1164,  1164,
       3,     8,   136,   137,    68,     8,     3,   141,   194,     6,
     144,   194,   162,   163,   148,   194,    69,    81,    82,    83,
      84,    85,    86,    87,    86,    87,     3,     3,   142,   143,
       4,     8,     8,    86,    87,   169,   170,   171,     8,     3,
       3,   105,     3,     3,   108,     8,     3,     8,   957,     3,
       3,     8,   939,     3,     8,     8,    21,     8,     8,   984,
     194,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,     4,
     194,    68,     3,   145,   146,   147,     4,     8,    69,    70,
      71,    72,    73,    74,     4,     4,     3,     3,     3,    86,
      87,     8,     8,     8,    69,    86,    87,   122,   123,   124,
     125,   126,   127,     3,     8,     3,     8,   104,     8,   172,
       8,   174,   175,   110,   111,   112,   113,   114,   115,     4,
     194,     4,   194,     4,   455,     4,   396,   397,   459,     4,
       4,   194,    94,    95,    96,    97,    22,    23,    24,    25,
     471,     4,     4,   474,   459,     4,   112,   113,     4,   115,
     481,     4,   471,     4,   471,     4,   471,     4,     4,   474,
     491,     4,     4,     4,     4,     4,   481,     4,   471,   471,
     501,   471,   471,     4,   501,   506,   491,     4,     4,   506,
     506,     3,   194,   471,   471,   471,   501,     8,   471,     4,
     471,   506,     4,     3,     8,   526,   471,   194,     4,   506,
     459,     4,   471,   194,     4,     4,     4,     4,   471,     4,
     471,   526,   471,     4,     4,   474,     4,     4,     4,   194,
       4,     4,   481,   195,   471,     4,   195,   474,   471,   471,
     195,   471,   491,     4,   481,     4,   471,   195,   195,   471,
     195,   471,   501,   471,   491,   195,   195,   506,   196,   474,
     197,   474,   196,   195,   195,   195,   481,     4,   481,   197,
     197,   197,     4,   197,     4,     4,     4,   526,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,     4,
       4,    86,    87,    59,    60,    61,    62,    63,    64,    65,
       4,     4,    68,     4,     4,     4,     4,     4,     4,     4,
       4,   195,    78,     4,    80,     4,     4,     4,     4,     4,
      86,    87,    88,    89,    90,    91,    92,    93,     4,     4,
     197,     4,     4,   654,     4,     4,   657,     4,   195,   105,
       4,   197,   108,   109,     4,     4,     4,     4,   195,     4,
     116,   195,   657,   195,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,     4,     4,   690,
     691,   692,     4,   694,   169,   170,     4,     4,     4,     4,
       4,     4,   195,     4,     4,   690,   691,   692,   693,   694,
       4,   197,     4,   653,   197,     4,   197,     4,   197,   194,
       4,     4,     4,   169,   170,     4,     4,     4,   657,   195,
       4,   195,   195,     4,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,   197,   197,     4,   194,    59,
      60,    61,    62,    63,    64,    65,    66,     4,    68,    69,
     195,   690,   691,   692,   693,   694,     4,     7,   194,   194,
       7,     7,     7,     7,     5,   194,    86,    87,   194,    89,
      90,     5,    92,    93,     5,     5,     4,   194,     7,     5,
       5,     5,     5,     5,   194,   105,     7,     5,   108,     5,
       7,   194,     7,     7,     7,     7,   116,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,     7,     5,     5,     5,     5,     3,     5,     7,     4,
     194,   194,   194,   194,   194,   194,   194,   194,   164,     7,
     194,     7,     7,   194,     7,     7,   194,   103,   194,   194,
       7,   194,   194,   194,     7,     7,     7,     7,   194,   169,
     170,   194,   194,   194,   194,   194,   194,   194,     7,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   197,     3,
       6,     6,     3,     6,   194,     3,     6,     6,     3,     6,
       6,     3,     6,     3,   683,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   194,
       3,     6,     6,     3,   195,     6,     8,     4,     4,     4,
       4,   197,   195,   195,     4,   195,   195,     4,     4,     4,
     195,   195,     4,   195,   197,   195,   195,   195,     4,     4,
     195,   942,   195,   195,   945,   195,   195,   948,   945,   195,
     951,   948,   948,   942,   951,   942,   197,   942,     4,     4,
     945,   962,   951,   948,   965,   962,   951,   968,   195,   942,
     942,   948,   942,   942,   197,     4,     4,   962,   951,   951,
     965,   951,   951,   984,   942,   942,   942,     6,   989,   942,
       3,   942,   993,   951,   951,   951,   195,   942,   951,   984,
     951,  1002,   195,   942,   989,  1002,   951,  1008,   993,   942,
    1011,   942,   951,   942,   999,     4,   945,  1002,   951,   948,
     951,   194,   951,  1008,   194,   942,  1011,   194,     8,   942,
     942,     8,   942,   962,   951,   194,   965,   942,   951,   951,
     942,   951,   942,     4,   942,   962,   951,   194,   965,   951,
     194,   951,   194,   951,   194,   984,   951,     8,   951,     3,
     989,     8,     4,     4,   993,     4,     4,     7,     5,     4,
     999,     4,   194,  1002,     4,     4,     4,   654,   632,  1008,
     645,   194,  1011,   194,   657,   455,   737,   459,   941,   936,
     960,  1008,   954,   957,  1011,   989,   968,   970,   509,   944,
     977,  1164,   942,   953,    77,   194,   194,   950,   947,   945,
     501,   194,   194,  1008,   195,  1008,  1011,   948,  1011,   197,
     194,   506,  1010,   194,   197,   195,   195,   194,  1013,  1011,
     967,   707,  1008,   965,  1170,   963,   984,   471,   999,   993,
     526,   656,   694,   530,  1185,  1003,  1206,  1226,    -1,   474,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   481,    -1,    -1,
      -1,    -1,    -1,  1164,    -1,    -1,    -1,  1164,   491,  1170,
      -1,    -1,    -1,  1170,    -1,  1164,    -1,    -1,    -1,  1164,
      -1,    -1,    -1,    -1,  1185,  1170,  1126,    -1,  1185,    -1,
      -1,  1164,  1164,    -1,  1164,  1164,    -1,    -1,    -1,    -1,
    1185,    -1,    -1,    -1,    -1,    -1,  1164,  1164,  1164,    -1,
      -1,  1164,    -1,  1164,    -1,    -1,    -1,    -1,    -1,  1164,
      -1,    -1,    -1,    -1,    -1,  1164,    -1,    -1,    -1,    -1,
      -1,  1164,    -1,  1164,    -1,  1164,    -1,    -1,    -1,    -1,
      -1,  1170,    -1,    -1,    -1,    -1,    -1,  1164,    -1,    -1,
      -1,  1164,  1164,  1170,  1164,    -1,  1185,    -1,    -1,  1164,
      -1,    -1,  1164,    -1,  1164,    -1,  1164,    -1,    -1,  1164,
      -1,  1164
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
       0,     5,     7,     9,   194,   195,   196,   197,   214,   215,
     216,   221,     7,   230,     7,   234,     7,   273,     7,   379,
       7,   456,     7,   472,     7,   489,     7,   408,     7,   414,
       7,   438,     7,   355,     7,   558,     7,   589,   222,   217,
     231,   235,   274,   380,   457,   473,   490,   409,   415,   439,
     356,   559,   590,   214,   223,   224,   194,   219,   220,    10,
     232,    11,    12,    15,    18,    19,    20,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    86,    87,    93,    98,    99,   100,   101,   102,
     104,   109,   118,   121,   128,   136,   137,   141,   144,   148,
     169,   170,   171,   194,   229,   236,   237,   238,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   258,   260,   262,   264,   266,   267,
     268,   269,   271,   280,   282,   284,   322,   328,   334,   340,
     342,   349,   363,   373,   393,   398,   406,   432,   462,   464,
     483,   513,   525,   537,   538,   546,   556,   587,   596,    16,
      17,   229,   275,   276,   277,   279,   462,   464,    78,    80,
      88,    89,    90,    91,    92,   105,   108,   116,   229,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     252,   253,   254,   255,   258,   260,   262,   264,   266,   381,
     382,   383,   385,   387,   389,   391,   393,   396,   397,   432,
     450,   462,   464,   466,   483,   508,    79,   229,   389,   391,
     432,   458,   459,   460,   462,   464,    81,    82,    83,    84,
      85,   229,   389,   391,   432,   462,   464,   474,   475,   476,
     478,   479,   481,   482,   104,   110,   111,   112,   113,   114,
     115,   229,   432,   462,   464,   491,   492,   493,   494,   496,
     498,   500,   502,   504,   506,   406,    21,    69,    71,    72,
      75,    76,    77,   229,   302,   416,   417,   418,   419,   420,
     421,   422,   424,   426,   428,   429,   431,   462,   464,    70,
      73,    74,   229,   302,   420,   426,   440,   441,   442,   443,
     444,   446,   447,   448,   449,   462,   464,   119,   120,   229,
     357,   358,   359,   361,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   169,   170,   229,
     462,   464,   560,   561,   562,   563,   565,   567,   568,   570,
     571,   572,   575,   577,   578,   579,   581,   583,   585,    13,
      14,   591,   592,   593,   595,     6,     3,     4,     8,     3,
     233,     8,   239,   588,   272,   281,   283,   285,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     270,     4,     4,     4,     4,     4,   256,   259,   261,     4,
     374,   407,   433,   463,   465,   394,   399,   329,   341,   335,
     323,   514,   484,   350,   364,   526,     4,   343,   539,   547,
     557,   263,   265,   597,     4,     3,     8,   278,     4,     3,
       8,   451,   467,   384,   386,   388,     4,     4,   392,   390,
     509,     3,     8,   461,     3,     8,   477,     4,   480,     4,
       4,     3,     8,   507,   495,   497,   499,   501,   503,   505,
       8,     3,     8,   423,   303,     4,   427,   425,   430,     4,
       8,     3,   445,     4,     4,     8,     3,   360,   362,     3,
       8,     4,   564,   566,     4,   569,     4,     4,   573,   576,
       4,     4,   580,   582,   584,   586,     3,     8,   594,     4,
       3,     8,   214,   214,   194,     4,     4,     4,     4,     4,
       4,     4,   195,   195,   195,   195,   195,   195,   195,   195,
     197,   196,   196,   195,     4,   195,   195,   197,   197,   197,
       4,     4,     4,   197,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     195,     4,     4,     4,     4,     4,     4,     4,   237,     4,
     197,   276,     4,     4,     4,     4,     4,   195,   197,     4,
       4,     4,   382,     4,   459,     4,   195,     4,   195,   195,
     475,     4,     4,     4,     4,     4,     4,     4,   493,     4,
       4,   195,     4,     4,     4,   197,   418,     4,   197,   197,
     442,     4,     4,   358,   197,     4,     4,   195,     4,   195,
     195,     4,     4,   197,   197,     4,     4,     4,     4,   561,
       4,   195,   592,     4,     7,   194,     7,     7,     7,     7,
       5,   194,   165,   166,   167,   168,   197,   257,   194,   194,
       5,     5,     5,   216,   218,   194,    94,    95,    96,    97,
     395,     5,     5,     5,     5,     7,     5,     5,     5,     7,
       7,     7,     7,     7,     7,   194,   194,     5,     5,   225,
       5,     5,   194,   194,   194,   225,   194,     7,   194,   194,
     194,   225,   225,   225,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   218,   194,   194,   194,   162,
     163,   574,   164,   257,   194,   194,   194,     5,   214,   236,
     591,   275,    21,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,   229,   290,   291,   292,   295,   297,   299,   301,   302,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     315,   316,   318,   320,   290,     7,   286,   287,   288,     7,
     375,   376,   377,     7,   410,   411,   412,     7,   434,   435,
     436,     7,   400,   401,   402,   112,   194,   330,   331,   332,
     333,   223,   113,   115,   332,   336,   337,   338,   339,   103,
     324,   325,   326,     7,   515,   516,     7,   485,   486,   487,
       7,   351,   352,   353,   122,   123,   124,   125,   126,   127,
     365,   366,   367,   368,   369,   370,   371,   372,    21,   132,
     133,   134,   135,   229,   304,   462,   464,   527,   528,   529,
     532,   533,   535,   536,   138,   139,   140,   229,   344,   345,
     346,   347,   348,   462,   464,   142,   143,   229,   462,   464,
     540,   541,   542,   544,   145,   146,   147,   194,   462,   464,
     548,   549,   550,   551,   553,   554,   560,     7,   598,   599,
     226,     7,   452,   453,   454,     7,   468,   469,   470,   117,
     494,   510,   511,   286,     8,     8,     8,   293,   296,   298,
     300,     4,     4,     4,     4,     4,   314,     4,     4,   317,
     319,   321,     4,     4,     4,     4,     3,     8,     8,   289,
       6,     3,   378,     6,     3,   413,     6,     3,   437,     6,
       3,   403,     6,     3,     3,     6,     6,     3,     6,   327,
       3,     8,   517,     3,     6,   488,     6,     3,   354,     6,
       3,     4,     4,     4,     4,     4,     4,     3,     8,   530,
     534,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   543,   545,     3,     8,     4,   552,     4,   555,     3,
       8,     8,   600,     3,     6,   194,   227,   228,   455,     6,
       3,   471,     6,     3,   512,     8,     6,     4,     4,     4,
       4,   195,   197,   195,   197,   195,     4,   195,   195,     4,
       4,     4,   195,   195,   197,   195,   291,   290,   288,   381,
     377,   416,   412,   440,   436,   229,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   252,   253,   254,
     255,   258,   260,   262,   264,   266,   302,   373,   385,   387,
     389,   391,   393,   397,   404,   405,   432,   462,   464,   508,
     402,   331,   337,     4,   325,   106,   107,   229,   302,   432,
     462,   464,   518,   519,   520,   521,   522,   524,   516,   491,
     487,   357,   353,   195,   195,   195,   195,   195,   195,   366,
       4,     4,   195,   195,   195,   528,   197,   195,   195,   345,
       4,     4,   541,   197,     4,   195,     4,   549,   172,   174,
     175,   229,   302,   462,   464,   601,   602,   603,   604,   606,
     599,     6,     3,   458,   454,   474,   470,     4,    22,    23,
      24,    25,   294,   194,   194,   194,   194,   194,   194,   194,
       8,     8,     8,     8,     3,     8,   194,   523,     4,     8,
       3,     8,     8,   129,   130,   131,   531,   194,   194,   194,
     194,   214,   607,     4,   605,     3,     8,   194,     8,     8,
     194,   405,     4,   197,   520,     4,   195,     4,   602,   194,
       5,   194,     7,   608,   609,   610,     3,     6,   173,   176,
     177,   178,   179,   611,   612,   613,   615,   616,   617,   618,
     609,   614,     4,     4,     4,   619,     3,     8,     4,   197,
     195,   195,     4,   612,   194,   194
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   198,   200,   199,   201,   199,   202,   199,   203,   199,
     204,   199,   205,   199,   206,   199,   207,   199,   208,   199,
     209,   199,   210,   199,   211,   199,   212,   199,   213,   199,
     214,   214,   214,   214,   214,   214,   214,   215,   217,   216,
     218,   219,   219,   220,   220,   222,   221,   223,   223,   224,
     224,   226,   225,   227,   227,   228,   228,   229,   231,   230,
     233,   232,   235,   234,   236,   236,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   237,
     237,   237,   237,   237,   237,   237,   237,   237,   237,   239,
     238,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   256,   255,   257,   257,
     257,   257,   257,   259,   258,   261,   260,   263,   262,   265,
     264,   266,   267,   268,   270,   269,   272,   271,   274,   273,
     275,   275,   276,   276,   276,   276,   276,   278,   277,   279,
     281,   280,   283,   282,   285,   284,   286,   286,   287,   287,
     289,   288,   290,   290,   291,   291,   291,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   291,   291,   291,   293,   292,   294,   294,   294,
     294,   296,   295,   298,   297,   300,   299,   301,   303,   302,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   314,
     313,   315,   317,   316,   319,   318,   321,   320,   323,   322,
     324,   324,   325,   327,   326,   329,   328,   330,   330,   331,
     331,   332,   333,   335,   334,   336,   336,   337,   337,   337,
     338,   339,   341,   340,   343,   342,   344,   344,   345,   345,
     345,   345,   345,   345,   346,   347,   348,   350,   349,   351,
     351,   352,   352,   354,   353,   356,   355,   357,   357,   357,
     358,   358,   360,   359,   362,   361,   364,   363,   365,   365,
     366,   366,   366,   366,   366,   366,   367,   368,   369,   370,
     371,   372,   374,   373,   375,   375,   376,   376,   378,   377,
     380,   379,   381,   381,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     382,   382,   382,   382,   382,   382,   382,   382,   382,   382,
     384,   383,   386,   385,   388,   387,   390,   389,   392,   391,
     394,   393,   395,   395,   395,   395,   396,   397,   399,   398,
     400,   400,   401,   401,   403,   402,   404,   404,   405,   405,
     405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   407,   406,   409,   408,   410,   410,   411,   411,   413,
     412,   415,   414,   416,   416,   417,   417,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   419,   420,   421,
     423,   422,   425,   424,   427,   426,   428,   430,   429,   431,
     433,   432,   434,   434,   435,   435,   437,   436,   439,   438,
     440,   440,   441,   441,   442,   442,   442,   442,   442,   442,
     442,   442,   442,   443,   445,   444,   446,   447,   448,   449,
     451,   450,   452,   452,   453,   453,   455,   454,   457,   456,
     458,   458,   459,   459,   459,   459,   459,   459,   459,   461,
     460,   463,   462,   465,   464,   467,   466,   468,   468,   469,
     469,   471,   470,   473,   472,   474,   474,   475,   475,   475,
     475,   475,   475,   475,   475,   475,   475,   475,   477,   476,
     478,   480,   479,   481,   482,   484,   483,   485,   485,   486,
     486,   488,   487,   490,   489,   491,   491,   492,   492,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     495,   494,   497,   496,   499,   498,   501,   500,   503,   502,
     505,   504,   507,   506,   509,   508,   510,   510,   512,   511,
     514,   513,   515,   515,   517,   516,   518,   518,   519,   519,
     520,   520,   520,   520,   520,   520,   520,   521,   523,   522,
     524,   526,   525,   527,   527,   528,   528,   528,   528,   528,
     528,   528,   528,   528,   530,   529,   531,   531,   531,   532,
     534,   533,   535,   536,   537,   539,   538,   540,   540,   541,
     541,   541,   541,   541,   543,   542,   545,   544,   547,   546,
     548,   548,   549,   549,   549,   549,   549,   549,   550,   552,
     551,   553,   555,   554,   557,   556,   559,   558,   560,   560,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   562,   564,
     563,   566,   565,   567,   569,   568,   570,   571,   573,   572,
     574,   574,   576,   575,   577,   578,   580,   579,   582,   581,
     584,   583,   586,   585,   588,   587,   590,   589,   591,   591,
     592,   592,   594,   593,   595,   597,   596,   598,   598,   600,
     599,   601,   601,   602,   602,   602,   602,   602,   602,   602,
     603,   605,   604,   607,   606,   608,   608,   610,   609,   611,
     611,   612,   612,   612,   612,   612,   614,   613,   615,   616,
     617,   619,   618
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       0,     6,     0,     6,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
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
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     1,     1,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     1,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     0,     6,     3,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4
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
  "\"ddns-qualifying-suffix\"", "\"store-extended-info\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
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
  "t2_percent", "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
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
       0,   283,   283,   283,   284,   284,   285,   285,   286,   286,
     287,   287,   288,   288,   289,   289,   290,   290,   291,   291,
     292,   292,   293,   293,   294,   294,   295,   295,   296,   296,
     304,   305,   306,   307,   308,   309,   310,   313,   318,   318,
     329,   332,   333,   336,   340,   347,   347,   354,   355,   358,
     362,   369,   369,   376,   377,   380,   384,   395,   404,   404,
     419,   419,   436,   436,   445,   446,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   506,
     506,   514,   519,   524,   529,   534,   539,   544,   549,   554,
     559,   564,   569,   574,   579,   584,   589,   589,   597,   600,
     603,   606,   609,   615,   615,   623,   623,   631,   631,   639,
     639,   647,   652,   657,   662,   662,   670,   670,   681,   681,
     690,   691,   694,   695,   696,   697,   698,   701,   701,   711,
     716,   716,   728,   728,   740,   740,   750,   751,   754,   755,
     758,   758,   768,   769,   772,   773,   774,   775,   776,   777,
     778,   779,   780,   781,   782,   783,   784,   785,   786,   787,
     788,   789,   790,   791,   792,   795,   795,   802,   803,   804,
     805,   808,   808,   816,   816,   824,   824,   832,   837,   837,
     845,   850,   855,   860,   865,   870,   875,   880,   885,   890,
     890,   898,   903,   903,   911,   911,   919,   919,   927,   927,
     937,   938,   940,   942,   942,   960,   960,   970,   971,   974,
     975,   978,   983,   988,   988,   998,   999,  1002,  1003,  1004,
    1007,  1012,  1019,  1019,  1031,  1031,  1043,  1044,  1047,  1048,
    1049,  1050,  1051,  1052,  1055,  1060,  1065,  1070,  1070,  1080,
    1081,  1084,  1085,  1088,  1088,  1098,  1098,  1108,  1109,  1110,
    1113,  1114,  1117,  1117,  1125,  1125,  1133,  1133,  1144,  1145,
    1148,  1149,  1150,  1151,  1152,  1153,  1156,  1161,  1166,  1171,
    1176,  1181,  1189,  1189,  1202,  1203,  1206,  1207,  1214,  1214,
    1240,  1240,  1251,  1252,  1256,  1257,  1258,  1259,  1260,  1261,
    1262,  1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,  1271,
    1272,  1273,  1274,  1275,  1276,  1277,  1278,  1279,  1280,  1281,
    1282,  1283,  1284,  1285,  1286,  1287,  1288,  1289,  1290,  1291,
    1294,  1294,  1302,  1302,  1310,  1310,  1318,  1318,  1326,  1326,
    1336,  1336,  1343,  1344,  1345,  1346,  1349,  1354,  1361,  1361,
    1372,  1373,  1377,  1378,  1381,  1381,  1389,  1390,  1393,  1394,
    1395,  1396,  1397,  1398,  1399,  1400,  1401,  1402,  1403,  1404,
    1405,  1406,  1407,  1408,  1409,  1410,  1411,  1412,  1413,  1414,
    1415,  1416,  1417,  1418,  1419,  1420,  1421,  1422,  1423,  1424,
    1425,  1432,  1432,  1445,  1445,  1454,  1455,  1458,  1459,  1464,
    1464,  1479,  1479,  1493,  1494,  1497,  1498,  1501,  1502,  1503,
    1504,  1505,  1506,  1507,  1508,  1509,  1510,  1513,  1515,  1520,
    1522,  1522,  1530,  1530,  1538,  1538,  1546,  1548,  1548,  1556,
    1565,  1565,  1577,  1578,  1583,  1584,  1589,  1589,  1601,  1601,
    1613,  1614,  1619,  1620,  1625,  1626,  1627,  1628,  1629,  1630,
    1631,  1632,  1633,  1636,  1638,  1638,  1646,  1648,  1650,  1655,
    1663,  1663,  1675,  1676,  1679,  1680,  1683,  1683,  1693,  1693,
    1703,  1704,  1707,  1708,  1709,  1710,  1711,  1712,  1713,  1716,
    1716,  1724,  1724,  1749,  1749,  1779,  1779,  1791,  1792,  1795,
    1796,  1799,  1799,  1811,  1811,  1823,  1824,  1827,  1828,  1829,
    1830,  1831,  1832,  1833,  1834,  1835,  1836,  1837,  1840,  1840,
    1848,  1853,  1853,  1861,  1866,  1874,  1874,  1884,  1885,  1888,
    1889,  1892,  1892,  1901,  1901,  1910,  1911,  1914,  1915,  1919,
    1920,  1921,  1922,  1923,  1924,  1925,  1926,  1927,  1928,  1929,
    1932,  1932,  1942,  1942,  1952,  1952,  1960,  1960,  1968,  1968,
    1976,  1976,  1984,  1984,  1997,  1997,  2007,  2008,  2011,  2011,
    2022,  2022,  2032,  2033,  2036,  2036,  2046,  2047,  2050,  2051,
    2054,  2055,  2056,  2057,  2058,  2059,  2060,  2063,  2065,  2065,
    2073,  2081,  2081,  2093,  2094,  2097,  2098,  2099,  2100,  2101,
    2102,  2103,  2104,  2105,  2108,  2108,  2115,  2116,  2117,  2120,
    2125,  2125,  2133,  2138,  2145,  2152,  2152,  2162,  2163,  2166,
    2167,  2168,  2169,  2170,  2173,  2173,  2181,  2181,  2192,  2192,
    2204,  2205,  2208,  2209,  2210,  2211,  2212,  2213,  2216,  2221,
    2221,  2229,  2234,  2234,  2243,  2243,  2255,  2255,  2265,  2266,
    2269,  2270,  2271,  2272,  2273,  2274,  2275,  2276,  2277,  2278,
    2279,  2280,  2281,  2282,  2283,  2284,  2285,  2286,  2289,  2295,
    2295,  2303,  2303,  2311,  2316,  2316,  2324,  2329,  2334,  2334,
    2342,  2343,  2346,  2346,  2355,  2361,  2367,  2367,  2375,  2375,
    2384,  2384,  2393,  2393,  2404,  2404,  2415,  2415,  2425,  2426,
    2430,  2431,  2434,  2434,  2444,  2451,  2451,  2463,  2464,  2468,
    2468,  2476,  2477,  2480,  2481,  2482,  2483,  2484,  2485,  2486,
    2489,  2494,  2494,  2502,  2502,  2512,  2513,  2516,  2516,  2524,
    2525,  2528,  2529,  2530,  2531,  2532,  2535,  2535,  2543,  2548,
    2553,  2558,  2558
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
#line 5581 "dhcp6_parser.cc"

#line 2566 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
