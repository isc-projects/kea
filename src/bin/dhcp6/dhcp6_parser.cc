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
#line 283 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 400 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 283 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 406 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 283 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 412 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 283 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 418 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 283 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 424 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 283 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 430 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 283 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 436 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 283 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 442 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 283 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 448 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 283 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 454 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 283 "dhcp6_parser.yy"
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
#line 292 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 739 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 293 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 745 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 294 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 751 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 295 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 757 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 296 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 763 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 297 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 769 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 298 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 775 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 299 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 781 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 300 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 787 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 301 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 793 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 302 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 799 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 303 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 805 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 304 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 811 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 305 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 817 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 313 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 314 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 315 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 316 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 317 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 847 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 318 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 319 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 859 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 322 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 868 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 327 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 879 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 332 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 889 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 338 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 345 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 905 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 350 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 45: // $@16: %empty
#line 358 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 925 "dhcp6_parser.cc"
    break;

  case 46: // list_generic: "[" $@16 list_content "]"
#line 361 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 933 "dhcp6_parser.cc"
    break;

  case 49: // not_empty_list: value
#line 369 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 942 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list "," value
#line 373 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp6_parser.cc"
    break;

  case 51: // $@17: %empty
#line 380 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 959 "dhcp6_parser.cc"
    break;

  case 52: // list_strings: "[" $@17 list_strings_content "]"
#line 382 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 968 "dhcp6_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 391 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 977 "dhcp6_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 395 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 986 "dhcp6_parser.cc"
    break;

  case 57: // unknown_map_entry: "constant string" ":"
#line 406 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 997 "dhcp6_parser.cc"
    break;

  case 58: // $@18: %empty
#line 415 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1008 "dhcp6_parser.cc"
    break;

  case 59: // syntax_map: "{" $@18 global_object "}"
#line 420 "dhcp6_parser.yy"
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
#line 430 "dhcp6_parser.yy"
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
#line 439 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp6_parser.cc"
    break;

  case 62: // $@20: %empty
#line 447 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp6_parser.cc"
    break;

  case 63: // sub_dhcp6: "{" $@20 global_params "}"
#line 451 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1065 "dhcp6_parser.cc"
    break;

  case 127: // $@21: %empty
#line 525 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1074 "dhcp6_parser.cc"
    break;

  case 128: // data_directory: "data-directory" $@21 ":" "constant string"
#line 528 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1084 "dhcp6_parser.cc"
    break;

  case 129: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 534 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1094 "dhcp6_parser.cc"
    break;

  case 130: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 540 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 131: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 546 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1114 "dhcp6_parser.cc"
    break;

  case 132: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 552 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 133: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 558 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1134 "dhcp6_parser.cc"
    break;

  case 134: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 564 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1144 "dhcp6_parser.cc"
    break;

  case 135: // renew_timer: "renew-timer" ":" "integer"
#line 570 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1154 "dhcp6_parser.cc"
    break;

  case 136: // rebind_timer: "rebind-timer" ":" "integer"
#line 576 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1164 "dhcp6_parser.cc"
    break;

  case 137: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 582 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1174 "dhcp6_parser.cc"
    break;

  case 138: // t1_percent: "t1-percent" ":" "floating point"
#line 588 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1184 "dhcp6_parser.cc"
    break;

  case 139: // t2_percent: "t2-percent" ":" "floating point"
#line 594 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1194 "dhcp6_parser.cc"
    break;

  case 140: // cache_threshold: "cache-threshold" ":" "floating point"
#line 600 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1204 "dhcp6_parser.cc"
    break;

  case 141: // cache_max_age: "cache-max-age" ":" "integer"
#line 606 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1214 "dhcp6_parser.cc"
    break;

  case 142: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 612 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 143: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 618 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1234 "dhcp6_parser.cc"
    break;

  case 144: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 624 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1244 "dhcp6_parser.cc"
    break;

  case 145: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 630 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1254 "dhcp6_parser.cc"
    break;

  case 146: // $@22: %empty
#line 636 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 147: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 639 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 148: // ddns_replace_client_name_value: "when-present"
#line 645 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1280 "dhcp6_parser.cc"
    break;

  case 149: // ddns_replace_client_name_value: "never"
#line 648 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1288 "dhcp6_parser.cc"
    break;

  case 150: // ddns_replace_client_name_value: "always"
#line 651 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1296 "dhcp6_parser.cc"
    break;

  case 151: // ddns_replace_client_name_value: "when-not-present"
#line 654 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1304 "dhcp6_parser.cc"
    break;

  case 152: // ddns_replace_client_name_value: "boolean"
#line 657 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1313 "dhcp6_parser.cc"
    break;

  case 153: // $@23: %empty
#line 663 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp6_parser.cc"
    break;

  case 154: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 666 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1332 "dhcp6_parser.cc"
    break;

  case 155: // $@24: %empty
#line 672 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp6_parser.cc"
    break;

  case 156: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 675 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc"
    break;

  case 157: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 681 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1361 "dhcp6_parser.cc"
    break;

  case 158: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 687 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1371 "dhcp6_parser.cc"
    break;

  case 159: // $@25: %empty
#line 693 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1380 "dhcp6_parser.cc"
    break;

  case 160: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 696 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1390 "dhcp6_parser.cc"
    break;

  case 161: // $@26: %empty
#line 702 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 162: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 705 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1409 "dhcp6_parser.cc"
    break;

  case 163: // store_extended_info: "store-extended-info" ":" "boolean"
#line 711 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 164: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 717 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1429 "dhcp6_parser.cc"
    break;

  case 165: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 723 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1439 "dhcp6_parser.cc"
    break;

  case 166: // $@27: %empty
#line 729 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1448 "dhcp6_parser.cc"
    break;

  case 167: // server_tag: "server-tag" $@27 ":" "constant string"
#line 732 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1458 "dhcp6_parser.cc"
    break;

  case 168: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 738 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1468 "dhcp6_parser.cc"
    break;

  case 169: // $@28: %empty
#line 744 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 170: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 750 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 171: // $@29: %empty
#line 756 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1500 "dhcp6_parser.cc"
    break;

  case 172: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 760 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1509 "dhcp6_parser.cc"
    break;

  case 180: // $@30: %empty
#line 776 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1521 "dhcp6_parser.cc"
    break;

  case 181: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 782 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1530 "dhcp6_parser.cc"
    break;

  case 182: // re_detect: "re-detect" ":" "boolean"
#line 787 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1540 "dhcp6_parser.cc"
    break;

  case 183: // $@31: %empty
#line 793 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1552 "dhcp6_parser.cc"
    break;

  case 184: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 799 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1563 "dhcp6_parser.cc"
    break;

  case 185: // $@32: %empty
#line 806 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1575 "dhcp6_parser.cc"
    break;

  case 186: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 812 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1586 "dhcp6_parser.cc"
    break;

  case 187: // $@33: %empty
#line 819 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1598 "dhcp6_parser.cc"
    break;

  case 188: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 825 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1607 "dhcp6_parser.cc"
    break;

  case 193: // $@34: %empty
#line 838 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1617 "dhcp6_parser.cc"
    break;

  case 194: // database: "{" $@34 database_map_params "}"
#line 842 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1627 "dhcp6_parser.cc"
    break;

  case 218: // $@35: %empty
#line 875 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1636 "dhcp6_parser.cc"
    break;

  case 219: // database_type: "type" $@35 ":" db_type
#line 878 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1645 "dhcp6_parser.cc"
    break;

  case 220: // db_type: "memfile"
#line 883 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1651 "dhcp6_parser.cc"
    break;

  case 221: // db_type: "mysql"
#line 884 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1657 "dhcp6_parser.cc"
    break;

  case 222: // db_type: "postgresql"
#line 885 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1663 "dhcp6_parser.cc"
    break;

  case 223: // db_type: "cql"
#line 886 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1669 "dhcp6_parser.cc"
    break;

  case 224: // $@36: %empty
#line 889 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1678 "dhcp6_parser.cc"
    break;

  case 225: // user: "user" $@36 ":" "constant string"
#line 892 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1688 "dhcp6_parser.cc"
    break;

  case 226: // $@37: %empty
#line 898 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1697 "dhcp6_parser.cc"
    break;

  case 227: // password: "password" $@37 ":" "constant string"
#line 901 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1707 "dhcp6_parser.cc"
    break;

  case 228: // $@38: %empty
#line 907 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1716 "dhcp6_parser.cc"
    break;

  case 229: // host: "host" $@38 ":" "constant string"
#line 910 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1726 "dhcp6_parser.cc"
    break;

  case 230: // port: "port" ":" "integer"
#line 916 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1736 "dhcp6_parser.cc"
    break;

  case 231: // $@39: %empty
#line 922 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1745 "dhcp6_parser.cc"
    break;

  case 232: // name: "name" $@39 ":" "constant string"
#line 925 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 233: // persist: "persist" ":" "boolean"
#line 931 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1765 "dhcp6_parser.cc"
    break;

  case 234: // lfc_interval: "lfc-interval" ":" "integer"
#line 937 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1775 "dhcp6_parser.cc"
    break;

  case 235: // readonly: "readonly" ":" "boolean"
#line 943 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1785 "dhcp6_parser.cc"
    break;

  case 236: // connect_timeout: "connect-timeout" ":" "integer"
#line 949 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1795 "dhcp6_parser.cc"
    break;

  case 237: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 955 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1805 "dhcp6_parser.cc"
    break;

  case 238: // max_row_errors: "max-row-errors" ":" "integer"
#line 961 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1815 "dhcp6_parser.cc"
    break;

  case 239: // request_timeout: "request-timeout" ":" "integer"
#line 967 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 240: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 973 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1835 "dhcp6_parser.cc"
    break;

  case 241: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 979 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 242: // $@40: %empty
#line 985 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1854 "dhcp6_parser.cc"
    break;

  case 243: // contact_points: "contact-points" $@40 ":" "constant string"
#line 988 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1864 "dhcp6_parser.cc"
    break;

  case 244: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 994 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 245: // $@41: %empty
#line 1000 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1883 "dhcp6_parser.cc"
    break;

  case 246: // keyspace: "keyspace" $@41 ":" "constant string"
#line 1003 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1893 "dhcp6_parser.cc"
    break;

  case 247: // $@42: %empty
#line 1009 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1902 "dhcp6_parser.cc"
    break;

  case 248: // consistency: "consistency" $@42 ":" "constant string"
#line 1012 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1912 "dhcp6_parser.cc"
    break;

  case 249: // $@43: %empty
#line 1018 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1921 "dhcp6_parser.cc"
    break;

  case 250: // serial_consistency: "serial-consistency" $@43 ":" "constant string"
#line 1021 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1931 "dhcp6_parser.cc"
    break;

  case 251: // $@44: %empty
#line 1027 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1943 "dhcp6_parser.cc"
    break;

  case 252: // sanity_checks: "sanity-checks" $@44 ":" "{" sanity_checks_params "}"
#line 1033 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1952 "dhcp6_parser.cc"
    break;

  case 256: // $@45: %empty
#line 1043 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1961 "dhcp6_parser.cc"
    break;

  case 257: // lease_checks: "lease-checks" $@45 ":" "constant string"
#line 1046 "dhcp6_parser.yy"
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
#line 1981 "dhcp6_parser.cc"
    break;

  case 258: // $@46: %empty
#line 1062 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1993 "dhcp6_parser.cc"
    break;

  case 259: // mac_sources: "mac-sources" $@46 ":" "[" mac_sources_list "]"
#line 1068 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2002 "dhcp6_parser.cc"
    break;

  case 264: // duid_id: "duid"
#line 1081 "dhcp6_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2011 "dhcp6_parser.cc"
    break;

  case 265: // string_id: "constant string"
#line 1086 "dhcp6_parser.yy"
                  {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2020 "dhcp6_parser.cc"
    break;

  case 266: // $@47: %empty
#line 1091 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2032 "dhcp6_parser.cc"
    break;

  case 267: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1097 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2041 "dhcp6_parser.cc"
    break;

  case 273: // hw_address_id: "hw-address"
#line 1111 "dhcp6_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2050 "dhcp6_parser.cc"
    break;

  case 274: // flex_id: "flex-id"
#line 1116 "dhcp6_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2059 "dhcp6_parser.cc"
    break;

  case 275: // $@48: %empty
#line 1123 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2071 "dhcp6_parser.cc"
    break;

  case 276: // relay_supplied_options: "relay-supplied-options" $@48 ":" "[" list_content "]"
#line 1129 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2080 "dhcp6_parser.cc"
    break;

  case 277: // $@49: %empty
#line 1136 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2092 "dhcp6_parser.cc"
    break;

  case 278: // dhcp_multi_threading: "multi-threading" $@49 ":" "{" multi_threading_params "}"
#line 1142 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2103 "dhcp6_parser.cc"
    break;

  case 287: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1161 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2113 "dhcp6_parser.cc"
    break;

  case 288: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1167 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2123 "dhcp6_parser.cc"
    break;

  case 289: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1173 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2133 "dhcp6_parser.cc"
    break;

  case 290: // $@50: %empty
#line 1179 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2145 "dhcp6_parser.cc"
    break;

  case 291: // hooks_libraries: "hooks-libraries" $@50 ":" "[" hooks_libraries_list "]"
#line 1185 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2154 "dhcp6_parser.cc"
    break;

  case 296: // $@51: %empty
#line 1198 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 297: // hooks_library: "{" $@51 hooks_params "}"
#line 1202 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2174 "dhcp6_parser.cc"
    break;

  case 298: // $@52: %empty
#line 1208 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2184 "dhcp6_parser.cc"
    break;

  case 299: // sub_hooks_library: "{" $@52 hooks_params "}"
#line 1212 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2194 "dhcp6_parser.cc"
    break;

  case 305: // $@53: %empty
#line 1227 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp6_parser.cc"
    break;

  case 306: // library: "library" $@53 ":" "constant string"
#line 1230 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2213 "dhcp6_parser.cc"
    break;

  case 307: // $@54: %empty
#line 1236 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2222 "dhcp6_parser.cc"
    break;

  case 308: // parameters: "parameters" $@54 ":" map_value
#line 1239 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2231 "dhcp6_parser.cc"
    break;

  case 309: // $@55: %empty
#line 1245 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2243 "dhcp6_parser.cc"
    break;

  case 310: // expired_leases_processing: "expired-leases-processing" $@55 ":" "{" expired_leases_params "}"
#line 1251 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2253 "dhcp6_parser.cc"
    break;

  case 319: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1269 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2263 "dhcp6_parser.cc"
    break;

  case 320: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1275 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2273 "dhcp6_parser.cc"
    break;

  case 321: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1281 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2283 "dhcp6_parser.cc"
    break;

  case 322: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1287 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2293 "dhcp6_parser.cc"
    break;

  case 323: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1293 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2303 "dhcp6_parser.cc"
    break;

  case 324: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1299 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2313 "dhcp6_parser.cc"
    break;

  case 325: // $@56: %empty
#line 1308 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2325 "dhcp6_parser.cc"
    break;

  case 326: // subnet6_list: "subnet6" $@56 ":" "[" subnet6_list_content "]"
#line 1314 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2334 "dhcp6_parser.cc"
    break;

  case 331: // $@57: %empty
#line 1334 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2344 "dhcp6_parser.cc"
    break;

  case 332: // subnet6: "{" $@57 subnet6_params "}"
#line 1338 "dhcp6_parser.yy"
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
#line 2370 "dhcp6_parser.cc"
    break;

  case 333: // $@58: %empty
#line 1360 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2380 "dhcp6_parser.cc"
    break;

  case 334: // sub_subnet6: "{" $@58 subnet6_params "}"
#line 1364 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2390 "dhcp6_parser.cc"
    break;

  case 380: // $@59: %empty
#line 1421 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2399 "dhcp6_parser.cc"
    break;

  case 381: // subnet: "subnet" $@59 ":" "constant string"
#line 1424 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2409 "dhcp6_parser.cc"
    break;

  case 382: // $@60: %empty
#line 1430 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2418 "dhcp6_parser.cc"
    break;

  case 383: // interface: "interface" $@60 ":" "constant string"
#line 1433 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2428 "dhcp6_parser.cc"
    break;

  case 384: // $@61: %empty
#line 1439 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2437 "dhcp6_parser.cc"
    break;

  case 385: // interface_id: "interface-id" $@61 ":" "constant string"
#line 1442 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2447 "dhcp6_parser.cc"
    break;

  case 386: // $@62: %empty
#line 1448 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2456 "dhcp6_parser.cc"
    break;

  case 387: // client_class: "client-class" $@62 ":" "constant string"
#line 1451 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2466 "dhcp6_parser.cc"
    break;

  case 388: // $@63: %empty
#line 1457 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2478 "dhcp6_parser.cc"
    break;

  case 389: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1463 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2487 "dhcp6_parser.cc"
    break;

  case 390: // reservations_global: "reservations-global" ":" "boolean"
#line 1468 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2497 "dhcp6_parser.cc"
    break;

  case 391: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1474 "dhcp6_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2507 "dhcp6_parser.cc"
    break;

  case 392: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1480 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2517 "dhcp6_parser.cc"
    break;

  case 393: // $@64: %empty
#line 1486 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2526 "dhcp6_parser.cc"
    break;

  case 394: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1489 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2535 "dhcp6_parser.cc"
    break;

  case 395: // hr_mode: "disabled"
#line 1494 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2541 "dhcp6_parser.cc"
    break;

  case 396: // hr_mode: "out-of-pool"
#line 1495 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2547 "dhcp6_parser.cc"
    break;

  case 397: // hr_mode: "global"
#line 1496 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2553 "dhcp6_parser.cc"
    break;

  case 398: // hr_mode: "all"
#line 1497 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2559 "dhcp6_parser.cc"
    break;

  case 399: // id: "id" ":" "integer"
#line 1500 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2569 "dhcp6_parser.cc"
    break;

  case 400: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1506 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2579 "dhcp6_parser.cc"
    break;

  case 401: // $@65: %empty
#line 1514 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2591 "dhcp6_parser.cc"
    break;

  case 402: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1520 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 407: // $@66: %empty
#line 1535 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2610 "dhcp6_parser.cc"
    break;

  case 408: // shared_network: "{" $@66 shared_network_params "}"
#line 1539 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2618 "dhcp6_parser.cc"
    break;

  case 451: // $@67: %empty
#line 1593 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2630 "dhcp6_parser.cc"
    break;

  case 452: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1599 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2639 "dhcp6_parser.cc"
    break;

  case 453: // $@68: %empty
#line 1607 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2648 "dhcp6_parser.cc"
    break;

  case 454: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1610 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2656 "dhcp6_parser.cc"
    break;

  case 459: // $@69: %empty
#line 1626 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2666 "dhcp6_parser.cc"
    break;

  case 460: // option_def_entry: "{" $@69 option_def_params "}"
#line 1630 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2678 "dhcp6_parser.cc"
    break;

  case 461: // $@70: %empty
#line 1641 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2688 "dhcp6_parser.cc"
    break;

  case 462: // sub_option_def: "{" $@70 option_def_params "}"
#line 1645 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2700 "dhcp6_parser.cc"
    break;

  case 478: // code: "code" ":" "integer"
#line 1677 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2710 "dhcp6_parser.cc"
    break;

  case 480: // $@71: %empty
#line 1685 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp6_parser.cc"
    break;

  case 481: // option_def_type: "type" $@71 ":" "constant string"
#line 1688 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2729 "dhcp6_parser.cc"
    break;

  case 482: // $@72: %empty
#line 1694 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2738 "dhcp6_parser.cc"
    break;

  case 483: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1697 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2748 "dhcp6_parser.cc"
    break;

  case 484: // $@73: %empty
#line 1703 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2757 "dhcp6_parser.cc"
    break;

  case 485: // space: "space" $@73 ":" "constant string"
#line 1706 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2767 "dhcp6_parser.cc"
    break;

  case 487: // $@74: %empty
#line 1714 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2776 "dhcp6_parser.cc"
    break;

  case 488: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1717 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 489: // option_def_array: "array" ":" "boolean"
#line 1723 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2796 "dhcp6_parser.cc"
    break;

  case 490: // $@75: %empty
#line 1733 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2808 "dhcp6_parser.cc"
    break;

  case 491: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1739 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2817 "dhcp6_parser.cc"
    break;

  case 496: // $@76: %empty
#line 1758 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2827 "dhcp6_parser.cc"
    break;

  case 497: // option_data_entry: "{" $@76 option_data_params "}"
#line 1762 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2836 "dhcp6_parser.cc"
    break;

  case 498: // $@77: %empty
#line 1770 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2846 "dhcp6_parser.cc"
    break;

  case 499: // sub_option_data: "{" $@77 option_data_params "}"
#line 1774 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2855 "dhcp6_parser.cc"
    break;

  case 514: // $@78: %empty
#line 1807 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2864 "dhcp6_parser.cc"
    break;

  case 515: // option_data_data: "data" $@78 ":" "constant string"
#line 1810 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2874 "dhcp6_parser.cc"
    break;

  case 518: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1820 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2884 "dhcp6_parser.cc"
    break;

  case 519: // option_data_always_send: "always-send" ":" "boolean"
#line 1826 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2894 "dhcp6_parser.cc"
    break;

  case 520: // $@79: %empty
#line 1835 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2906 "dhcp6_parser.cc"
    break;

  case 521: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1841 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2915 "dhcp6_parser.cc"
    break;

  case 526: // $@80: %empty
#line 1856 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 527: // pool_list_entry: "{" $@80 pool_params "}"
#line 1860 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2935 "dhcp6_parser.cc"
    break;

  case 528: // $@81: %empty
#line 1866 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2945 "dhcp6_parser.cc"
    break;

  case 529: // sub_pool6: "{" $@81 pool_params "}"
#line 1870 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2955 "dhcp6_parser.cc"
    break;

  case 539: // $@82: %empty
#line 1889 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2964 "dhcp6_parser.cc"
    break;

  case 540: // pool_entry: "pool" $@82 ":" "constant string"
#line 1892 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2974 "dhcp6_parser.cc"
    break;

  case 541: // $@83: %empty
#line 1898 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2982 "dhcp6_parser.cc"
    break;

  case 542: // user_context: "user-context" $@83 ":" map_value
#line 1900 "dhcp6_parser.yy"
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
#line 3009 "dhcp6_parser.cc"
    break;

  case 543: // $@84: %empty
#line 1923 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 544: // comment: "comment" $@84 ":" "constant string"
#line 1925 "dhcp6_parser.yy"
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
#line 3046 "dhcp6_parser.cc"
    break;

  case 545: // $@85: %empty
#line 1953 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3058 "dhcp6_parser.cc"
    break;

  case 546: // pd_pools_list: "pd-pools" $@85 ":" "[" pd_pools_list_content "]"
#line 1959 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3067 "dhcp6_parser.cc"
    break;

  case 551: // $@86: %empty
#line 1974 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3077 "dhcp6_parser.cc"
    break;

  case 552: // pd_pool_entry: "{" $@86 pd_pool_params "}"
#line 1978 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3089 "dhcp6_parser.cc"
    break;

  case 553: // $@87: %empty
#line 1986 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3099 "dhcp6_parser.cc"
    break;

  case 554: // sub_pd_pool: "{" $@87 pd_pool_params "}"
#line 1990 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3111 "dhcp6_parser.cc"
    break;

  case 568: // $@88: %empty
#line 2015 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3120 "dhcp6_parser.cc"
    break;

  case 569: // pd_prefix: "prefix" $@88 ":" "constant string"
#line 2018 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3130 "dhcp6_parser.cc"
    break;

  case 570: // pd_prefix_len: "prefix-len" ":" "integer"
#line 2024 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3140 "dhcp6_parser.cc"
    break;

  case 571: // $@89: %empty
#line 2030 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3149 "dhcp6_parser.cc"
    break;

  case 572: // excluded_prefix: "excluded-prefix" $@89 ":" "constant string"
#line 2033 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3159 "dhcp6_parser.cc"
    break;

  case 573: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 2039 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3169 "dhcp6_parser.cc"
    break;

  case 574: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2045 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 575: // $@90: %empty
#line 2054 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3191 "dhcp6_parser.cc"
    break;

  case 576: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2060 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3200 "dhcp6_parser.cc"
    break;

  case 581: // $@91: %empty
#line 2073 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3210 "dhcp6_parser.cc"
    break;

  case 582: // reservation: "{" $@91 reservation_params "}"
#line 2077 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3219 "dhcp6_parser.cc"
    break;

  case 583: // $@92: %empty
#line 2082 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3229 "dhcp6_parser.cc"
    break;

  case 584: // sub_reservation: "{" $@92 reservation_params "}"
#line 2086 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3238 "dhcp6_parser.cc"
    break;

  case 600: // $@93: %empty
#line 2113 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3250 "dhcp6_parser.cc"
    break;

  case 601: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2119 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3259 "dhcp6_parser.cc"
    break;

  case 602: // $@94: %empty
#line 2124 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3271 "dhcp6_parser.cc"
    break;

  case 603: // prefixes: "prefixes" $@94 ":" list_strings
#line 2130 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3280 "dhcp6_parser.cc"
    break;

  case 604: // $@95: %empty
#line 2135 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3289 "dhcp6_parser.cc"
    break;

  case 605: // duid: "duid" $@95 ":" "constant string"
#line 2138 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3299 "dhcp6_parser.cc"
    break;

  case 606: // $@96: %empty
#line 2144 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3308 "dhcp6_parser.cc"
    break;

  case 607: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2147 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3318 "dhcp6_parser.cc"
    break;

  case 608: // $@97: %empty
#line 2153 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3327 "dhcp6_parser.cc"
    break;

  case 609: // hostname: "hostname" $@97 ":" "constant string"
#line 2156 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3337 "dhcp6_parser.cc"
    break;

  case 610: // $@98: %empty
#line 2162 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3346 "dhcp6_parser.cc"
    break;

  case 611: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2165 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3356 "dhcp6_parser.cc"
    break;

  case 612: // $@99: %empty
#line 2171 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3368 "dhcp6_parser.cc"
    break;

  case 613: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2177 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3377 "dhcp6_parser.cc"
    break;

  case 614: // $@100: %empty
#line 2185 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3389 "dhcp6_parser.cc"
    break;

  case 615: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2191 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 618: // $@101: %empty
#line 2200 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3407 "dhcp6_parser.cc"
    break;

  case 619: // ip_address: "ip-address" $@101 ":" "constant string"
#line 2203 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3417 "dhcp6_parser.cc"
    break;

  case 620: // $@102: %empty
#line 2212 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3429 "dhcp6_parser.cc"
    break;

  case 621: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2218 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3438 "dhcp6_parser.cc"
    break;

  case 624: // $@103: %empty
#line 2227 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3448 "dhcp6_parser.cc"
    break;

  case 625: // client_class_entry: "{" $@103 client_class_params "}"
#line 2231 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3458 "dhcp6_parser.cc"
    break;

  case 638: // $@104: %empty
#line 2256 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 639: // client_class_test: "test" $@104 ":" "constant string"
#line 2259 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3477 "dhcp6_parser.cc"
    break;

  case 640: // only_if_required: "only-if-required" ":" "boolean"
#line 2265 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3487 "dhcp6_parser.cc"
    break;

  case 641: // $@105: %empty
#line 2274 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3499 "dhcp6_parser.cc"
    break;

  case 642: // server_id: "server-id" $@105 ":" "{" server_id_params "}"
#line 2280 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3510 "dhcp6_parser.cc"
    break;

  case 654: // $@106: %empty
#line 2302 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3519 "dhcp6_parser.cc"
    break;

  case 655: // server_id_type: "type" $@106 ":" duid_type
#line 2305 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3528 "dhcp6_parser.cc"
    break;

  case 656: // duid_type: "LLT"
#line 2310 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3534 "dhcp6_parser.cc"
    break;

  case 657: // duid_type: "EN"
#line 2311 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3540 "dhcp6_parser.cc"
    break;

  case 658: // duid_type: "LL"
#line 2312 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3546 "dhcp6_parser.cc"
    break;

  case 659: // htype: "htype" ":" "integer"
#line 2315 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3556 "dhcp6_parser.cc"
    break;

  case 660: // $@107: %empty
#line 2321 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3565 "dhcp6_parser.cc"
    break;

  case 661: // identifier: "identifier" $@107 ":" "constant string"
#line 2324 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3575 "dhcp6_parser.cc"
    break;

  case 662: // time: "time" ":" "integer"
#line 2330 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3585 "dhcp6_parser.cc"
    break;

  case 663: // enterprise_id: "enterprise-id" ":" "integer"
#line 2336 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3595 "dhcp6_parser.cc"
    break;

  case 664: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2344 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3605 "dhcp6_parser.cc"
    break;

  case 665: // $@108: %empty
#line 2352 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3617 "dhcp6_parser.cc"
    break;

  case 666: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2358 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3626 "dhcp6_parser.cc"
    break;

  case 674: // $@109: %empty
#line 2374 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3635 "dhcp6_parser.cc"
    break;

  case 675: // socket_type: "socket-type" $@109 ":" "constant string"
#line 2377 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3645 "dhcp6_parser.cc"
    break;

  case 676: // $@110: %empty
#line 2383 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3654 "dhcp6_parser.cc"
    break;

  case 677: // socket_name: "socket-name" $@110 ":" "constant string"
#line 2386 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3664 "dhcp6_parser.cc"
    break;

  case 678: // $@111: %empty
#line 2395 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3676 "dhcp6_parser.cc"
    break;

  case 679: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2401 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3687 "dhcp6_parser.cc"
    break;

  case 688: // enable_queue: "enable-queue" ":" "boolean"
#line 2420 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3697 "dhcp6_parser.cc"
    break;

  case 689: // $@112: %empty
#line 2426 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 690: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2429 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3716 "dhcp6_parser.cc"
    break;

  case 691: // capacity: "capacity" ":" "integer"
#line 2435 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3726 "dhcp6_parser.cc"
    break;

  case 692: // $@113: %empty
#line 2441 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3735 "dhcp6_parser.cc"
    break;

  case 693: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2444 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3744 "dhcp6_parser.cc"
    break;

  case 694: // $@114: %empty
#line 2451 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 695: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2457 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 696: // $@115: %empty
#line 2464 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3777 "dhcp6_parser.cc"
    break;

  case 697: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2468 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3787 "dhcp6_parser.cc"
    break;

  case 718: // enable_updates: "enable-updates" ":" "boolean"
#line 2498 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3797 "dhcp6_parser.cc"
    break;

  case 719: // $@116: %empty
#line 2505 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3806 "dhcp6_parser.cc"
    break;

  case 720: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2508 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3816 "dhcp6_parser.cc"
    break;

  case 721: // $@117: %empty
#line 2514 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3825 "dhcp6_parser.cc"
    break;

  case 722: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2517 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3835 "dhcp6_parser.cc"
    break;

  case 723: // server_port: "server-port" ":" "integer"
#line 2523 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3845 "dhcp6_parser.cc"
    break;

  case 724: // $@118: %empty
#line 2529 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 725: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2532 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3864 "dhcp6_parser.cc"
    break;

  case 726: // sender_port: "sender-port" ":" "integer"
#line 2538 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3874 "dhcp6_parser.cc"
    break;

  case 727: // max_queue_size: "max-queue-size" ":" "integer"
#line 2544 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3884 "dhcp6_parser.cc"
    break;

  case 728: // $@119: %empty
#line 2550 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3893 "dhcp6_parser.cc"
    break;

  case 729: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2553 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 730: // ncr_protocol_value: "UDP"
#line 2559 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3908 "dhcp6_parser.cc"
    break;

  case 731: // ncr_protocol_value: "TCP"
#line 2560 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3914 "dhcp6_parser.cc"
    break;

  case 732: // $@120: %empty
#line 2563 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3923 "dhcp6_parser.cc"
    break;

  case 733: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2566 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3933 "dhcp6_parser.cc"
    break;

  case 734: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2573 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3943 "dhcp6_parser.cc"
    break;

  case 735: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2580 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3953 "dhcp6_parser.cc"
    break;

  case 736: // $@121: %empty
#line 2587 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3962 "dhcp6_parser.cc"
    break;

  case 737: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2590 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3971 "dhcp6_parser.cc"
    break;

  case 738: // $@122: %empty
#line 2596 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3980 "dhcp6_parser.cc"
    break;

  case 739: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2599 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3990 "dhcp6_parser.cc"
    break;

  case 740: // $@123: %empty
#line 2606 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3999 "dhcp6_parser.cc"
    break;

  case 741: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2609 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4009 "dhcp6_parser.cc"
    break;

  case 742: // $@124: %empty
#line 2616 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4018 "dhcp6_parser.cc"
    break;

  case 743: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2619 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4028 "dhcp6_parser.cc"
    break;

  case 744: // $@125: %empty
#line 2628 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4040 "dhcp6_parser.cc"
    break;

  case 745: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2634 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 746: // $@126: %empty
#line 2640 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4060 "dhcp6_parser.cc"
    break;

  case 747: // sub_config_control: "{" $@126 config_control_params "}"
#line 2644 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4069 "dhcp6_parser.cc"
    break;

  case 752: // $@127: %empty
#line 2659 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 753: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2665 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4090 "dhcp6_parser.cc"
    break;

  case 754: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2670 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4100 "dhcp6_parser.cc"
    break;

  case 755: // $@128: %empty
#line 2678 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4112 "dhcp6_parser.cc"
    break;

  case 756: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2684 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4121 "dhcp6_parser.cc"
    break;

  case 759: // $@129: %empty
#line 2696 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4131 "dhcp6_parser.cc"
    break;

  case 760: // logger_entry: "{" $@129 logger_params "}"
#line 2700 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4139 "dhcp6_parser.cc"
    break;

  case 770: // debuglevel: "debuglevel" ":" "integer"
#line 2717 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4149 "dhcp6_parser.cc"
    break;

  case 771: // $@130: %empty
#line 2723 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4158 "dhcp6_parser.cc"
    break;

  case 772: // severity: "severity" $@130 ":" "constant string"
#line 2726 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4168 "dhcp6_parser.cc"
    break;

  case 773: // $@131: %empty
#line 2732 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4180 "dhcp6_parser.cc"
    break;

  case 774: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2738 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4189 "dhcp6_parser.cc"
    break;

  case 777: // $@132: %empty
#line 2747 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4199 "dhcp6_parser.cc"
    break;

  case 778: // output_entry: "{" $@132 output_params_list "}"
#line 2751 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4207 "dhcp6_parser.cc"
    break;

  case 786: // $@133: %empty
#line 2766 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4216 "dhcp6_parser.cc"
    break;

  case 787: // output: "output" $@133 ":" "constant string"
#line 2769 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4226 "dhcp6_parser.cc"
    break;

  case 788: // flush: "flush" ":" "boolean"
#line 2775 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4236 "dhcp6_parser.cc"
    break;

  case 789: // maxsize: "maxsize" ":" "integer"
#line 2781 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4246 "dhcp6_parser.cc"
    break;

  case 790: // maxver: "maxver" ":" "integer"
#line 2787 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4256 "dhcp6_parser.cc"
    break;

  case 791: // $@134: %empty
#line 2793 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4265 "dhcp6_parser.cc"
    break;

  case 792: // pattern: "pattern" $@134 ":" "constant string"
#line 2796 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4275 "dhcp6_parser.cc"
    break;


#line 4279 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -964;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     510,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,    59,    33,    44,    54,    60,
      95,   105,   131,   139,   146,   192,   208,   219,   226,   233,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,    33,  -131,
      86,   116,    52,   278,   276,   485,   286,    39,    41,   119,
     -61,   588,   322,  -964,   236,   259,   268,   255,   288,  -964,
     343,  -964,  -964,  -964,  -964,  -964,  -964,   351,   358,   361,
     362,   382,   385,   394,   432,   434,   435,   436,   438,   440,
     442,  -964,   444,   448,   449,   452,   454,  -964,  -964,  -964,
     460,   464,   465,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
     468,   469,   479,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,   480,  -964,  -964,  -964,  -964,  -964,  -964,   481,
    -964,   488,  -964,    75,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,   494,  -964,    89,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,   496,
     500,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,    92,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,    96,  -964,  -964,  -964,  -964,  -964,
     501,  -964,   503,   504,  -964,  -964,  -964,  -964,  -964,  -964,
     134,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,   345,   393,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,   391,  -964,
    -964,   506,  -964,  -964,  -964,   512,  -964,  -964,   406,   430,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,   513,   517,  -964,  -964,  -964,  -964,   516,
     486,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,   144,  -964,  -964,  -964,   522,  -964,  -964,
     524,  -964,   525,   532,  -964,  -964,   535,   537,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,   210,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,   539,   231,  -964,  -964,  -964,  -964,    33,
      33,  -964,   312,   541,  -964,   542,   545,   546,   547,   549,
     550,   352,   359,   363,   365,   366,   367,   379,   380,   354,
     357,   360,   407,   396,   411,   561,   412,   413,   414,   415,
     416,   594,   613,   614,   418,   423,   424,   620,   622,   623,
     626,   629,   632,   635,   437,   441,   443,   636,   643,   645,
     646,   647,   649,   650,   652,   653,   458,   660,   661,   662,
     663,   664,   665,   466,   666,  -964,   116,  -964,   668,   476,
      52,  -964,   669,   679,   680,   681,   682,   487,   483,   685,
     687,   688,   278,  -964,   689,   276,  -964,   690,   492,   692,
     509,   511,   485,  -964,   709,   711,   714,   715,   716,   717,
     718,  -964,   286,  -964,   719,   720,   523,   721,   723,   724,
     530,  -964,    41,   725,   531,   533,  -964,   119,   733,   735,
     -73,  -964,   536,   736,   739,   554,   754,   557,   558,   755,
     758,   562,   563,   759,   762,   765,   766,   588,  -964,   767,
     569,   322,  -964,  -964,  -964,   769,   768,   572,   770,   771,
     772,   773,   776,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,   574,  -964,  -964,
    -964,  -964,  -964,    56,   580,   581,  -964,  -964,  -964,   779,
     780,   781,   782,   784,   586,   395,  -964,  -964,  -964,   787,
     788,   789,   790,   791,   793,   794,   795,   796,  -964,   797,
     798,   799,   800,   587,   593,  -964,   803,  -964,   804,  -964,
    -964,   805,   806,   598,   599,   610,  -964,  -964,   804,   611,
     807,  -964,   615,  -964,   616,  -964,   617,  -964,  -964,  -964,
     804,   804,   804,   618,   619,   621,   624,  -964,   625,   627,
    -964,   628,   630,   631,  -964,  -964,   633,  -964,  -964,  -964,
     634,   784,  -964,  -964,   637,   638,  -964,   639,  -964,  -964,
    -121,   644,  -964,  -964,    56,   640,   641,   642,  -964,   811,
    -964,  -964,    33,   116,  -964,   322,    52,   247,   247,   815,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,   817,
     818,   821,   824,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,   -78,    33,   191,   727,   827,   831,   838,   174,    64,
     154,    67,    48,   588,  -964,  -964,   839,  -964,  -964,   840,
     841,  -964,  -964,  -964,  -964,  -964,   -80,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,   815,  -964,   249,   250,
     262,  -964,  -964,  -964,  -964,   845,   846,   847,   848,   849,
    -964,   850,   851,  -964,  -964,  -964,   852,   853,   854,   855,
    -964,   309,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,   311,  -964,   856,   857,  -964,  -964,   858,
     860,  -964,  -964,   859,   863,  -964,  -964,   861,   865,  -964,
    -964,   864,   866,  -964,  -964,  -964,    57,  -964,  -964,  -964,
     867,  -964,  -964,  -964,    78,  -964,  -964,  -964,  -964,   346,
    -964,  -964,  -964,   103,  -964,  -964,   868,   869,  -964,  -964,
     870,   872,  -964,   873,   874,   875,   876,   877,   878,   349,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,   879,
     880,   881,  -964,  -964,  -964,  -964,   356,  -964,  -964,  -964,
    -964,  -964,  -964,   882,   883,   884,  -964,   376,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,   377,
    -964,  -964,  -964,   885,  -964,   886,  -964,  -964,  -964,   384,
    -964,  -964,  -964,  -964,  -964,   392,  -964,   151,  -964,   659,
    -964,   887,   888,  -964,  -964,   889,   891,  -964,  -964,  -964,
     890,  -964,   893,  -964,  -964,  -964,   892,   896,   897,   898,
     694,   698,   701,   700,   703,   903,   705,   706,   907,   908,
     910,   712,   722,   713,   734,   247,  -964,  -964,   247,  -964,
     815,   278,  -964,   817,    41,  -964,   818,   119,  -964,   821,
     540,  -964,   824,   -78,  -964,  -964,   191,  -964,   923,   727,
    -964,   224,   827,  -964,   286,  -964,   831,   -61,  -964,   838,
     740,   741,   742,   753,   756,   801,   174,  -964,   924,   961,
     809,   834,   835,    64,  -964,   785,   843,   844,   154,  -964,
     967,   980,    67,  -964,   792,   989,   862,   992,    48,  -964,
    -964,   329,   839,  -964,  -964,   994,  1031,   276,  -964,   840,
     485,  -964,   841,  1039,  -964,  -964,   556,   842,   871,   894,
    -964,  -964,  -964,  -964,  -964,   895,  -964,  -964,   901,   902,
     904,  -964,  -964,  -964,  -964,  -964,   408,  -964,   409,  -964,
    1041,  -964,  1042,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
     410,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,   905,
    -964,  -964,  1048,  -964,  -964,  -964,  -964,  -964,  1045,  1051,
    -964,  -964,  -964,  -964,  -964,  1047,  -964,   419,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,    53,   906,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,   909,   911,  -964,  -964,
     912,  -964,    33,  -964,  -964,  1052,  -964,  -964,  -964,  -964,
    -964,   420,  -964,  -964,  -964,  -964,  -964,  -964,   913,   421,
    -964,   422,  -964,   914,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
     540,  -964,  -964,  1053,   915,  -964,   224,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  1054,   916,
    1055,   329,  -964,  -964,  -964,  -964,  -964,  -964,   919,  -964,
    -964,  1056,  -964,   920,  -964,  -964,  1057,  -964,  -964,   206,
    -964,   -36,  1057,  -964,  -964,  1058,  1062,  1063,  -964,   429,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  1064,   918,   921,
     922,  1065,   -36,  -964,   925,  -964,  -964,  -964,   926,  -964,
    -964,  -964
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   171,     9,   333,    11,
     528,    13,   553,    15,   583,    17,   453,    19,   461,    21,
     498,    23,   298,    25,   696,    27,   746,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   585,     0,   463,   500,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   127,   744,   169,   183,   185,   187,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,     0,     0,     0,     0,     0,   146,   153,   155,
       0,     0,     0,   325,   451,   490,   401,   541,   543,   393,
       0,     0,     0,   258,   275,   266,   251,   620,   575,   290,
     309,   641,     0,   277,   665,   678,   694,   159,   161,     0,
     755,     0,   126,     0,    64,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   105,   106,   107,   108,   109,    75,
     113,   114,   115,   116,   117,   118,   119,   120,   111,   112,
     121,   122,   123,   100,   125,    78,    79,    80,    81,    97,
      82,    84,    83,   124,    88,    89,    76,   102,   103,   104,
     101,    77,    86,    87,    95,    96,    98,    85,    90,    91,
      92,    93,    94,    99,   110,   180,     0,   179,     0,   173,
     175,   176,   177,   178,   520,   545,   380,   382,   384,     0,
       0,   388,   386,   614,   379,   337,   338,   339,   340,   341,
     342,   343,   344,   363,   364,   365,   366,   367,   370,   371,
     372,   373,   374,   375,   376,   377,   368,   369,   378,     0,
     335,   348,   349,   350,   353,   354,   357,   358,   359,   356,
     351,   352,   345,   346,   361,   362,   347,   355,   360,   539,
     538,   534,   535,   533,     0,   530,   532,   536,   537,   568,
       0,   571,     0,     0,   567,   561,   562,   560,   565,   566,
       0,   555,   557,   558,   563,   564,   559,   612,   600,   602,
     604,   606,   608,   610,   599,   596,   597,   598,     0,   586,
     587,   591,   592,   589,   593,   594,   595,   590,     0,   480,
     231,     0,   484,   482,   487,     0,   476,   477,     0,   464,
     465,   467,   479,   468,   469,   470,   486,   471,   472,   473,
     474,   475,   514,     0,     0,   512,   513,   516,   517,     0,
     501,   502,   504,   505,   506,   507,   508,   509,   510,   511,
     305,   307,   302,     0,   300,   303,   304,     0,   719,   721,
       0,   724,     0,     0,   728,   732,     0,     0,   736,   738,
     740,   742,   717,   715,   716,     0,   698,   700,   712,   701,
     702,   703,   704,   705,   706,   707,   708,   709,   710,   711,
     713,   714,   752,     0,     0,   748,   750,   751,    46,     0,
       0,    39,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,    63,     0,     0,
       0,   172,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   334,     0,     0,   529,     0,     0,     0,
       0,     0,     0,   554,     0,     0,     0,     0,     0,     0,
       0,   584,     0,   454,     0,     0,     0,     0,     0,     0,
       0,   462,     0,     0,     0,     0,   499,     0,     0,     0,
       0,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   697,     0,
       0,     0,   747,    50,    43,     0,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,     0,   164,   165,
     143,   144,   145,     0,     0,     0,   157,   158,   163,     0,
       0,     0,     0,     0,     0,     0,   390,   391,   392,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   664,     0,
       0,     0,     0,     0,     0,   168,     0,    65,     0,   182,
     174,     0,     0,     0,     0,     0,   399,   400,     0,     0,
       0,   336,     0,   531,     0,   570,     0,   573,   574,   556,
       0,     0,     0,     0,     0,     0,     0,   588,     0,     0,
     478,     0,     0,     0,   489,   466,     0,   518,   519,   503,
       0,     0,   301,   718,     0,     0,   723,     0,   726,   727,
       0,     0,   734,   735,     0,     0,     0,     0,   699,     0,
     754,   749,     0,     0,   128,     0,     0,     0,     0,   189,
     167,   148,   149,   150,   151,   152,   147,   154,   156,   327,
     455,   492,   403,    40,   542,   544,   395,   396,   397,   398,
     394,     0,    47,     0,     0,     0,   577,   292,     0,     0,
       0,     0,     0,     0,   160,   162,     0,    51,   181,   522,
     547,   381,   383,   385,   389,   387,     0,   540,   569,   572,
     613,   601,   603,   605,   607,   609,   611,   481,   232,   485,
     483,   488,   515,   306,   308,   720,   722,   725,   730,   731,
     729,   733,   737,   739,   741,   743,   189,    44,     0,     0,
       0,   218,   224,   226,   228,     0,     0,     0,     0,     0,
     242,     0,     0,   245,   247,   249,     0,     0,     0,     0,
     217,     0,   195,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   209,   216,   210,   211,   212,   207,   208,
     213,   214,   215,     0,   193,     0,   190,   191,   331,     0,
     328,   329,   459,     0,   456,   457,   496,     0,   493,   494,
     407,     0,   404,   405,   264,   265,     0,   260,   262,   263,
       0,   273,   274,   270,     0,   268,   271,   272,   256,     0,
     253,   255,   624,     0,   622,   581,     0,   578,   579,   296,
       0,   293,   294,     0,     0,     0,     0,     0,     0,     0,
     311,   313,   314,   315,   316,   317,   318,   654,   660,     0,
       0,     0,   653,   650,   651,   652,     0,   643,   645,   648,
     646,   647,   649,     0,     0,     0,   286,     0,   279,   281,
     282,   283,   284,   285,   674,   676,   673,   671,   672,     0,
     667,   669,   670,     0,   689,     0,   692,   685,   686,     0,
     680,   682,   683,   684,   687,     0,   759,     0,   757,    53,
     526,     0,   523,   524,   551,     0,   548,   549,   618,   617,
       0,   616,     0,    61,   745,   170,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   184,   186,     0,   188,
       0,     0,   326,     0,   463,   452,     0,   500,   491,     0,
       0,   402,     0,     0,   259,   276,     0,   267,     0,     0,
     252,   626,     0,   621,   585,   576,     0,     0,   291,     0,
       0,     0,     0,     0,     0,     0,     0,   310,     0,     0,
       0,     0,     0,     0,   642,     0,     0,     0,     0,   278,
       0,     0,     0,   666,     0,     0,     0,     0,     0,   679,
     695,     0,     0,   756,    55,     0,    54,     0,   521,     0,
       0,   546,     0,     0,   615,   753,     0,     0,     0,     0,
     230,   233,   234,   235,   236,     0,   244,   237,     0,     0,
       0,   239,   240,   241,   238,   196,     0,   192,     0,   330,
       0,   458,     0,   495,   450,   425,   426,   427,   429,   430,
     431,   415,   416,   434,   435,   436,   437,   438,   441,   442,
     443,   444,   445,   446,   447,   448,   439,   440,   449,   411,
     412,   413,   414,   423,   424,   420,   421,   422,   419,   428,
       0,   409,   417,   432,   433,   418,   406,   261,   269,     0,
     254,   638,     0,   636,   637,   633,   634,   635,     0,   627,
     628,   630,   631,   632,   623,     0,   580,     0,   295,   319,
     320,   321,   322,   323,   324,   312,     0,     0,   659,   662,
     663,   644,   287,   288,   289,   280,     0,     0,   668,   688,
       0,   691,     0,   681,   773,     0,   771,   769,   763,   767,
     768,     0,   761,   765,   766,   764,   758,    52,     0,     0,
     525,     0,   550,     0,   220,   221,   222,   223,   219,   225,
     227,   229,   243,   246,   248,   250,   194,   332,   460,   497,
       0,   408,   257,     0,     0,   625,     0,   582,   297,   656,
     657,   658,   655,   661,   675,   677,   690,   693,     0,     0,
       0,     0,   760,    56,   527,   552,   619,   410,     0,   640,
     629,     0,   770,     0,   762,   639,     0,   772,   777,     0,
     775,     0,     0,   774,   786,     0,     0,     0,   791,     0,
     779,   781,   782,   783,   784,   785,   776,     0,     0,     0,
       0,     0,     0,   778,     0,   788,   789,   790,     0,   780,
     787,   792
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,   -10,  -964,  -564,  -964,
     200,  -964,  -964,  -964,  -964,   170,  -964,  -595,  -964,  -964,
    -964,   -71,  -964,  -964,  -964,  -964,  -964,  -964,   378,   584,
    -964,  -964,   -59,   -43,   -42,   -40,   -39,   -28,   -27,   -26,
     -23,   -21,   -15,    -9,    -3,  -964,    -1,    17,    18,    20,
    -964,   388,    25,  -964,    28,  -964,    30,    32,    35,  -964,
      38,  -964,    40,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,   381,   585,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,   298,  -964,    98,  -964,  -676,   101,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,   -67,
    -964,  -714,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,    80,  -964,  -964,  -964,  -964,  -964,    87,  -698,
    -964,  -964,  -964,  -964,    85,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,    58,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
      73,  -964,  -964,  -964,    76,   544,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,    69,  -964,  -964,  -964,  -964,  -964,  -964,
    -963,  -964,  -964,  -964,   104,  -964,  -964,  -964,   107,   589,
    -964,  -964,  -962,  -964,  -961,  -964,    51,  -964,    55,  -964,
      42,    45,    46,    50,  -964,  -964,  -964,  -955,  -964,  -964,
    -964,  -964,    97,  -964,  -964,  -120,  1015,  -964,  -964,  -964,
    -964,  -964,   108,  -964,  -964,  -964,   109,  -964,   567,  -964,
     -66,  -964,  -964,  -964,  -964,  -964,   -47,  -964,  -964,  -964,
    -964,  -964,    13,  -964,  -964,  -964,   106,  -964,  -964,  -964,
     113,  -964,   573,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,    63,  -964,  -964,  -964,    62,   612,
    -964,  -964,   -55,  -964,     1,  -964,  -964,  -964,  -964,  -964,
      66,  -964,  -964,  -964,    79,   651,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,   -57,  -964,  -964,  -964,   120,  -964,  -964,
    -964,   126,  -964,   609,   386,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -954,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,   132,  -964,  -964,  -964,
     -83,  -964,  -964,  -964,  -964,  -964,  -964,  -964,   112,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,   110,  -964,  -964,  -964,  -964,  -964,  -964,  -964,    99,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
     403,   583,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,  -964,
    -964,   446,   577,  -964,  -964,  -964,  -964,  -964,  -964,   102,
    -964,  -964,   -85,  -964,  -964,  -964,  -964,  -964,  -964,  -105,
    -964,  -964,  -124,  -964,  -964,  -964,  -964,  -964,  -964,  -964
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     714,    87,    88,    41,    68,    84,    85,   738,   939,  1045,
    1046,   800,    43,    70,    90,   423,    45,    71,   153,   154,
     155,   425,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     451,   706,   174,   452,   175,   453,   176,   177,   178,   481,
     179,   482,   180,   181,   182,   183,   445,   184,   185,   427,
      47,    72,   218,   219,   220,   488,   221,   186,   428,   187,
     429,   188,   430,   825,   826,   827,   978,   801,   802,   803,
     956,  1198,   804,   957,   805,   958,   806,   959,   807,   808,
     525,   809,   810,   811,   812,   813,   814,   815,   816,   817,
     818,   965,   819,   820,   968,   821,   969,   822,   970,   189,
     470,   859,   860,   861,   998,   190,   467,   846,   847,   848,
     849,   191,   469,   854,   855,   856,   857,   192,   468,   193,
     477,   907,   908,   909,   910,   911,   194,   473,   870,   871,
     872,  1007,    63,    80,   373,   374,   375,   538,   376,   539,
     195,   474,   879,   880,   881,   882,   883,   884,   885,   886,
     196,   457,   829,   830,   831,   981,    49,    73,   259,   260,
     261,   494,   262,   495,   263,   496,   264,   500,   265,   499,
     197,   198,   199,   200,   463,   720,   270,   271,   201,   460,
     841,   842,   843,   990,  1120,  1121,   202,   458,    57,    77,
     833,   834,   835,   984,    59,    78,   338,   339,   340,   341,
     342,   343,   344,   524,   345,   528,   346,   527,   347,   348,
     529,   349,   203,   459,   837,   838,   839,   987,    61,    79,
     359,   360,   361,   362,   363,   533,   364,   365,   366,   367,
     273,   492,   941,   942,   943,  1047,    51,    74,   284,   285,
     286,   504,   204,   461,   205,   462,   276,   493,   945,   946,
     947,  1050,    53,    75,   300,   301,   302,   507,   303,   304,
     509,   305,   306,   206,   472,   866,   867,   868,  1004,    55,
      76,   318,   319,   320,   321,   515,   322,   516,   323,   517,
     324,   518,   325,   519,   326,   520,   327,   514,   278,   501,
     950,   951,  1053,   207,   471,   863,   864,  1001,  1138,  1139,
    1140,  1141,  1142,  1213,  1143,   208,   475,   896,   897,   898,
    1018,  1222,   899,   900,  1019,   901,   902,   209,   210,   478,
     919,   920,   921,  1030,   922,  1031,   211,   479,   929,   930,
     931,   932,  1035,   933,   934,  1037,   212,   480,    65,    81,
     395,   396,   397,   398,   543,   399,   544,   400,   401,   546,
     402,   403,   404,   549,   770,   405,   550,   406,   407,   408,
     553,   409,   554,   410,   555,   411,   556,   213,   426,    67,
      82,   414,   415,   416,   559,   417,   214,   484,   937,   938,
    1041,  1181,  1182,  1183,  1184,  1230,  1185,  1228,  1249,  1250,
    1251,  1259,  1260,  1261,  1267,  1262,  1263,  1264,  1265,  1271
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     152,   217,   234,   280,   294,   314,    38,   336,   355,   372,
     392,   337,   356,   357,   235,   893,   277,   222,   274,   287,
     298,   316,   823,   350,   368,   853,   393,  1110,  1111,  1112,
     236,   237,   358,   238,   239,  1119,  1125,   308,    31,   713,
      32,   844,    33,   744,   948,   240,   241,   242,   768,   769,
     243,    42,   244,   370,   371,   750,   751,   752,   245,    30,
     993,    44,   329,   994,   246,   370,   371,    46,   215,   216,
     247,    86,   248,   223,   275,   288,   299,   317,   486,   351,
     369,   996,   394,   487,   997,   887,   272,   283,   297,   315,
     249,   250,   490,   251,   786,   502,    89,   491,   252,   505,
     503,   253,    48,   254,   506,   255,  1002,   713,   256,  1003,
     124,   257,    50,   258,   330,   266,   331,   332,   267,   268,
     333,   334,   335,   269,   845,   281,   295,    91,    92,   282,
     296,    93,   127,   128,    94,    95,    96,   512,    52,   127,
     128,   151,   513,   127,   128,  1254,    54,   540,  1255,  1256,
    1257,  1258,   541,    56,  1042,   127,   128,  1043,   127,   128,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,  1219,
    1220,  1221,   330,   352,   331,   332,   353,   354,   126,    58,
     923,   924,   925,   888,   889,   890,   891,   127,   128,  1252,
     127,   128,  1253,   557,   129,    60,   914,   915,   558,   130,
     131,   132,   133,   134,   135,   136,    62,   137,   701,   702,
     703,   704,   138,    64,   561,    34,    35,    36,    37,   562,
      66,   139,   418,   151,   140,   127,   128,  1110,  1111,  1112,
     926,   141,   486,   561,   151,  1119,  1125,   953,   954,   142,
     143,   705,   419,   421,   144,   490,   151,   145,   781,   151,
     955,   146,   420,   782,   783,   784,   785,   786,   787,   788,
     789,   790,   791,   792,   793,   794,   795,   796,   797,   798,
     799,   422,   147,   148,   149,   150,   125,   330,   853,   903,
     904,   905,  1076,   873,   874,   875,   876,   877,   878,   893,
     844,   851,   975,   852,   975,   127,   128,   976,   151,   977,
     330,   151,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   412,   413,  1131,  1132,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   125,   999,
     125,   424,  1016,   521,  1000,   431,   151,  1017,   125,  1023,
     279,   224,   432,   225,  1024,   433,   434,   127,   128,   127,
     128,   226,   227,   228,   229,   230,   129,   127,   128,  1028,
    1032,   130,   131,   132,  1029,  1033,   435,  1038,   231,   436,
     231,   232,  1039,   232,   138,   557,   522,   307,   437,   523,
    1040,   233,   330,   308,   309,   310,   311,   312,   313,   563,
     564,   975,   502,  1210,   531,   152,  1206,  1207,  1211,   217,
     127,   128,   540,  1231,   505,   512,   151,  1218,  1232,  1234,
    1235,   234,  1272,   532,   280,   222,   438,  1273,   439,   440,
     441,   294,   442,   235,   443,   277,   444,   274,   446,   151,
     287,   314,   447,   448,   147,   148,   449,   298,   450,   236,
     237,   336,   238,   239,   454,   337,   355,   316,   455,   456,
     356,   357,   464,   465,   240,   241,   242,   350,   151,   243,
     151,   244,   368,   466,   476,   483,   392,   245,   151,   537,
     358,   223,   485,   246,   716,   717,   718,   719,   489,   247,
     497,   248,   393,   275,   498,   508,   288,   510,   511,  1174,
     526,  1175,  1176,   299,   565,   272,   530,   534,   283,   249,
     250,   535,   251,   317,   536,   297,   542,   252,   545,   547,
     253,   151,   254,   351,   255,   315,   548,   256,   369,   551,
     257,   552,   258,   560,   266,   566,   567,   267,   268,   568,
     569,   570,   269,   571,   572,   573,   281,   125,   394,   581,
     282,   582,   574,   295,   583,   587,   575,   296,   576,   577,
     578,   289,   290,   291,   292,   293,   127,   128,  1194,  1195,
    1196,  1197,   579,   580,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   231,   593,   585,
     232,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   584,   125,   330,   586,   588,   589,   594,   595,   590,
     591,   592,   152,   596,   599,   217,   600,   601,   597,   598,
     602,   127,   128,   603,   227,   228,   604,   230,   129,   605,
     609,   222,   606,   130,   131,   132,   607,   610,   608,   611,
     612,   613,   231,   614,   615,   232,   616,   617,   892,   906,
     916,   618,   392,   233,   619,   620,   621,   622,   623,   624,
     626,   625,   628,   631,   894,   912,   917,   927,   393,   127,
     128,   629,   777,   632,   633,   634,   635,   151,   637,   638,
     636,   639,   640,   642,   644,   645,   646,   223,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   647,   650,   648,   651,   147,   148,   652,   653,
     654,   655,   656,   658,   659,   661,   660,   662,   663,   666,
     895,   913,   918,   928,   394,   664,   667,   670,   668,   671,
     674,   673,   151,   675,   377,   378,   379,   380,   381,   382,
     383,   384,   385,   386,   387,   388,   389,   676,   677,   680,
     678,   679,   681,   684,   390,   391,   685,   682,   683,   686,
     687,   689,   690,   692,   694,   693,   700,   695,   696,   697,
     698,   699,   707,   708,   709,   710,   711,   712,   715,   734,
     151,    32,   721,   722,   723,   735,   725,   724,   726,   727,
     741,   742,   728,   729,   730,   731,   732,   733,   736,   737,
     739,   740,   743,   745,   746,   771,   776,   747,   748,   749,
     753,   754,   824,   755,   828,   832,   756,   757,   836,   758,
     759,   840,   760,   761,   862,   762,   763,   858,   865,   765,
     766,   767,   773,   774,   775,   869,   936,   940,   944,   960,
     961,   962,   963,   964,   966,   967,   971,   972,   973,   974,
     980,  1044,   979,   983,   982,   985,   986,   988,   989,   992,
     991,   764,  1006,   995,  1005,  1009,  1008,  1010,  1011,  1012,
    1013,  1014,  1015,  1020,  1021,  1022,  1025,  1026,  1027,  1034,
    1036,  1049,   850,  1048,  1052,  1051,  1056,  1060,  1054,  1055,
    1057,  1058,  1059,  1061,  1062,  1063,  1064,  1065,  1066,  1067,
     234,  1068,  1069,   336,  1070,  1071,   355,   337,  1073,  1084,
     356,   357,   235,  1109,   277,  1072,   274,  1129,  1156,   350,
    1133,  1085,   368,   314,  1134,  1123,   372,  1074,   236,   237,
     358,   238,   239,  1149,  1150,  1151,  1136,  1086,  1087,   316,
    1088,  1089,   892,   240,   241,   242,  1152,   906,   243,  1153,
     244,   916,  1090,  1091,  1092,  1157,   245,  1093,   894,  1094,
    1177,  1166,   246,   912,  1178,  1095,   280,   917,   247,   294,
     248,  1096,   275,   927,  1167,   351,  1179,  1097,   369,  1098,
    1162,  1124,   287,  1170,   272,   298,  1172,  1169,   249,   250,
    1187,   251,  1137,  1122,  1154,   317,   252,  1099,  1100,   253,
    1101,   254,  1158,   255,  1135,  1102,   256,   315,  1103,   257,
    1104,   258,  1105,   266,   895,  1106,   267,   268,  1107,   913,
    1108,   269,  1115,   918,  1188,  1116,  1117,  1159,  1160,   928,
    1118,  1113,  1180,  1193,  1199,  1114,  1163,  1164,   288,  1208,
    1209,   299,  1214,  1215,  1216,  1217,  1229,  1238,  1241,  1243,
     283,  1246,  1268,   297,  1248,  1171,  1269,  1270,  1274,  1278,
     627,   778,   772,  1200,   952,   630,  1075,   780,  1077,  1130,
    1127,  1128,  1148,  1147,   672,  1155,  1165,  1079,  1078,  1126,
    1237,   641,   328,  1080,  1081,  1083,  1201,  1202,   281,   665,
    1082,   295,   282,  1203,  1204,   296,  1205,  1212,  1223,  1189,
     669,  1224,  1190,  1225,  1226,  1233,  1236,   643,  1192,  1242,
    1239,  1245,  1247,  1275,  1276,  1277,  1146,  1280,  1281,  1191,
    1145,   657,   949,  1240,  1144,  1161,   935,  1173,   691,  1084,
     688,   779,  1168,  1109,  1186,  1133,  1244,  1266,  1279,  1134,
       0,  1085,     0,     0,     0,  1123,     0,     0,     0,     0,
    1177,  1136,  1227,   649,  1178,     0,     0,  1086,  1087,     0,
    1088,  1089,     0,     0,     0,     0,  1179,     0,     0,     0,
       0,     0,  1090,  1091,  1092,     0,     0,  1093,     0,  1094,
       0,     0,     0,     0,     0,  1095,     0,     0,     0,     0,
       0,  1096,     0,     0,     0,     0,     0,  1097,     0,  1098,
       0,  1124,     0,     0,     0,     0,     0,  1137,     0,     0,
       0,     0,     0,  1122,     0,     0,     0,  1099,  1100,  1135,
    1101,     0,  1180,     0,     0,  1102,     0,     0,  1103,     0,
    1104,     0,  1105,     0,     0,  1106,     0,     0,  1107,     0,
    1108,     0,  1115,     0,     0,  1116,  1117,     0,     0,     0,
    1118,  1113,     0,     0,     0,  1114
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    78,    79,    79,    73,   729,    73,    72,    73,    74,
      75,    76,   698,    78,    79,   723,    81,   990,   990,   990,
      73,    73,    79,    73,    73,   990,   990,   117,     5,   603,
       7,   119,     9,   638,   124,    73,    73,    73,   169,   170,
      73,     7,    73,   126,   127,   650,   651,   652,    73,     0,
       3,     7,    21,     6,    73,   126,   127,     7,    16,    17,
      73,   202,    73,    72,    73,    74,    75,    76,     3,    78,
      79,     3,    81,     8,     6,    21,    73,    74,    75,    76,
      73,    73,     3,    73,    30,     3,    10,     8,    73,     3,
       8,    73,     7,    73,     8,    73,     3,   671,    73,     6,
      71,    73,     7,    73,    73,    73,    75,    76,    73,    73,
      79,    80,    81,    73,   202,    74,    75,    11,    12,    74,
      75,    15,    91,    92,    18,    19,    20,     3,     7,    91,
      92,   202,     8,    91,    92,   181,     7,     3,   184,   185,
     186,   187,     8,     7,     3,    91,    92,     6,    91,    92,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,   136,
     137,   138,    73,    74,    75,    76,    77,    78,    82,     7,
     152,   153,   154,   139,   140,   141,   142,    91,    92,     3,
      91,    92,     6,     3,    98,     7,   149,   150,     8,   103,
     104,   105,   106,   107,   108,   109,     7,   111,   172,   173,
     174,   175,   116,     7,     3,   202,   203,   204,   205,     8,
       7,   125,     6,   202,   128,    91,    92,  1210,  1210,  1210,
     202,   135,     3,     3,   202,  1210,  1210,     8,     8,   143,
     144,   205,     3,     8,   148,     3,   202,   151,    21,   202,
       8,   155,     4,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,     3,   176,   177,   178,   179,    72,    73,   996,   145,
     146,   147,   978,   129,   130,   131,   132,   133,   134,  1023,
     119,   120,     3,   122,     3,    91,    92,     8,   202,     8,
      73,   202,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    13,    14,   113,   114,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    72,     3,
      72,     8,     3,     8,     8,     4,   202,     8,    72,     3,
      84,    83,     4,    85,     8,     4,     4,    91,    92,    91,
      92,    93,    94,    95,    96,    97,    98,    91,    92,     3,
       3,   103,   104,   105,     8,     8,     4,     3,   112,     4,
     112,   115,     8,   115,   116,     3,     3,   111,     4,     8,
       8,   123,    73,   117,   118,   119,   120,   121,   122,   419,
     420,     3,     3,     3,     8,   486,     8,     8,     8,   490,
      91,    92,     3,     3,     3,     3,   202,     8,     8,     8,
       8,   502,     3,     3,   505,   490,     4,     8,     4,     4,
       4,   512,     4,   502,     4,   502,     4,   502,     4,   202,
     505,   522,     4,     4,   176,   177,     4,   512,     4,   502,
     502,   532,   502,   502,     4,   532,   537,   522,     4,     4,
     537,   537,     4,     4,   502,   502,   502,   532,   202,   502,
     202,   502,   537,     4,     4,     4,   557,   502,   202,     3,
     537,   490,     4,   502,    99,   100,   101,   102,     4,   502,
       4,   502,   557,   502,     4,     4,   505,     4,     4,   180,
       4,   182,   183,   512,   202,   502,     4,     4,   505,   502,
     502,     4,   502,   522,     8,   512,     4,   502,     4,     4,
     502,   202,   502,   532,   502,   522,     4,   502,   537,     4,
     502,     4,   502,     4,   502,     4,     4,   502,   502,     4,
       4,     4,   502,     4,     4,   203,   505,    72,   557,   205,
     505,   204,   203,   512,   204,     4,   203,   512,   203,   203,
     203,    86,    87,    88,    89,    90,    91,    92,    22,    23,
      24,    25,   203,   203,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,   112,     4,   203,
     115,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,   204,    72,    73,   203,   203,   203,     4,     4,   205,
     205,   205,   693,   205,     4,   696,     4,     4,   205,   205,
       4,    91,    92,     4,    94,    95,     4,    97,    98,     4,
       4,   696,   205,   103,   104,   105,   205,     4,   205,     4,
       4,     4,   112,     4,     4,   115,     4,     4,   729,   730,
     731,   203,   733,   123,     4,     4,     4,     4,     4,     4,
       4,   205,     4,     4,   729,   730,   731,   732,   733,    91,
      92,   205,   692,     4,     4,     4,     4,   202,   205,     4,
     203,     4,     4,     4,     4,   203,     4,   696,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   203,     4,   203,     4,   176,   177,     4,     4,
       4,     4,     4,     4,     4,     4,   203,     4,     4,     4,
     729,   730,   731,   732,   733,   205,   205,     4,   205,     4,
       4,   205,   202,     4,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   203,     4,     4,
     203,   203,     4,     4,   176,   177,     4,   205,   205,     4,
       4,     4,   203,     4,   202,     7,   202,     7,     7,     7,
       7,     5,   202,   202,     5,     5,     5,     5,   202,   202,
     202,     7,     5,     5,     5,   202,     5,     7,     5,     5,
     202,   202,     7,     7,     7,     7,     7,     7,     5,     5,
       5,     5,   202,   202,     7,   171,     5,   202,   202,   202,
     202,   202,     7,   202,     7,     7,   202,   202,     7,   202,
     202,     7,   202,   202,     7,   202,   202,   110,     7,   202,
     202,   202,   202,   202,   202,     7,     7,     7,     7,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   202,     6,     3,     6,     6,     3,     6,     3,     3,
       6,   671,     3,     6,     6,     3,     6,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   722,     6,     3,     6,     4,   203,     8,     6,
       4,     4,     4,   205,   203,   205,   203,     4,   203,   203,
     981,     4,     4,   984,     4,   203,   987,   984,   205,   990,
     987,   987,   981,   990,   981,   203,   981,     4,     4,   984,
    1001,   990,   987,  1004,  1001,   990,  1007,   203,   981,   981,
     987,   981,   981,   203,   203,   203,  1001,   990,   990,  1004,
     990,   990,  1023,   981,   981,   981,   203,  1028,   981,   203,
     981,  1032,   990,   990,   990,     4,   981,   990,  1023,   990,
    1041,     4,   981,  1028,  1041,   990,  1047,  1032,   981,  1050,
     981,   990,   981,  1038,     4,   984,  1041,   990,   987,   990,
     205,   990,  1047,     4,   981,  1050,     4,   205,   981,   981,
       6,   981,  1001,   990,   203,  1004,   981,   990,   990,   981,
     990,   981,   203,   981,  1001,   990,   981,  1004,   990,   981,
     990,   981,   990,   981,  1023,   990,   981,   981,   990,  1028,
     990,   981,   990,  1032,     3,   990,   990,   203,   203,  1038,
     990,   990,  1041,     4,   202,   990,   203,   203,  1047,     8,
       8,  1050,     4,     8,     3,     8,     4,     4,     4,     4,
    1047,     5,     4,  1050,     7,   203,     4,     4,     4,     4,
     486,   693,   684,   202,   776,   490,   975,   696,   980,   999,
     993,   996,  1009,  1007,   540,  1016,  1028,   983,   981,   992,
    1210,   502,    77,   984,   986,   989,   202,   202,  1047,   532,
     987,  1050,  1047,   202,   202,  1050,   202,   202,   202,  1047,
     537,   202,  1049,   202,   202,   202,   202,   505,  1052,   203,
     205,   202,   202,   205,   203,   203,  1006,   202,   202,  1050,
    1004,   522,   746,  1216,  1002,  1023,   733,  1038,   561,  1210,
     557,   695,  1032,  1210,  1042,  1216,  1231,  1252,  1272,  1216,
      -1,  1210,    -1,    -1,    -1,  1210,    -1,    -1,    -1,    -1,
    1231,  1216,  1172,   512,  1231,    -1,    -1,  1210,  1210,    -1,
    1210,  1210,    -1,    -1,    -1,    -1,  1231,    -1,    -1,    -1,
      -1,    -1,  1210,  1210,  1210,    -1,    -1,  1210,    -1,  1210,
      -1,    -1,    -1,    -1,    -1,  1210,    -1,    -1,    -1,    -1,
      -1,  1210,    -1,    -1,    -1,    -1,    -1,  1210,    -1,  1210,
      -1,  1210,    -1,    -1,    -1,    -1,    -1,  1216,    -1,    -1,
      -1,    -1,    -1,  1210,    -1,    -1,    -1,  1210,  1210,  1216,
    1210,    -1,  1231,    -1,    -1,  1210,    -1,    -1,  1210,    -1,
    1210,    -1,  1210,    -1,    -1,  1210,    -1,    -1,  1210,    -1,
    1210,    -1,  1210,    -1,    -1,  1210,  1210,    -1,    -1,    -1,
    1210,  1210,    -1,    -1,    -1,  1210
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
       0,     5,     7,     9,   202,   203,   204,   205,   222,   223,
     224,   229,     7,   238,     7,   242,     7,   286,     7,   392,
       7,   472,     7,   488,     7,   505,     7,   424,     7,   430,
       7,   454,     7,   368,     7,   574,     7,   605,   230,   225,
     239,   243,   287,   393,   473,   489,   506,   425,   431,   455,
     369,   575,   606,   222,   231,   232,   202,   227,   228,    10,
     240,    11,    12,    15,    18,    19,    20,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    82,    91,    92,    98,
     103,   104,   105,   106,   107,   108,   109,   111,   116,   125,
     128,   135,   143,   144,   148,   151,   155,   176,   177,   178,
     179,   202,   237,   244,   245,   246,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   268,   270,   272,   273,   274,   276,
     278,   279,   280,   281,   283,   284,   293,   295,   297,   335,
     341,   347,   353,   355,   362,   376,   386,   406,   407,   408,
     409,   414,   422,   448,   478,   480,   499,   529,   541,   553,
     554,   562,   572,   603,   612,    16,    17,   237,   288,   289,
     290,   292,   478,   480,    83,    85,    93,    94,    95,    96,
      97,   112,   115,   123,   237,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   262,   263,
     264,   265,   268,   270,   272,   273,   274,   276,   278,   394,
     395,   396,   398,   400,   402,   404,   406,   407,   408,   409,
     412,   413,   448,   466,   478,   480,   482,   499,   524,    84,
     237,   402,   404,   448,   474,   475,   476,   478,   480,    86,
      87,    88,    89,    90,   237,   402,   404,   448,   478,   480,
     490,   491,   492,   494,   495,   497,   498,   111,   117,   118,
     119,   120,   121,   122,   237,   448,   478,   480,   507,   508,
     509,   510,   512,   514,   516,   518,   520,   522,   422,    21,
      73,    75,    76,    79,    80,    81,   237,   315,   432,   433,
     434,   435,   436,   437,   438,   440,   442,   444,   445,   447,
     478,   480,    74,    77,    78,   237,   315,   436,   442,   456,
     457,   458,   459,   460,   462,   463,   464,   465,   478,   480,
     126,   127,   237,   370,   371,   372,   374,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     176,   177,   237,   478,   480,   576,   577,   578,   579,   581,
     583,   584,   586,   587,   588,   591,   593,   594,   595,   597,
     599,   601,    13,    14,   607,   608,   609,   611,     6,     3,
       4,     8,     3,   241,     8,   247,   604,   285,   294,   296,
     298,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   282,     4,     4,     4,     4,
       4,   266,   269,   271,     4,     4,     4,   387,   423,   449,
     415,   479,   481,   410,     4,     4,     4,   342,   354,   348,
     336,   530,   500,   363,   377,   542,     4,   356,   555,   563,
     573,   275,   277,     4,   613,     4,     3,     8,   291,     4,
       3,     8,   467,   483,   397,   399,   401,     4,     4,   405,
     403,   525,     3,     8,   477,     3,     8,   493,     4,   496,
       4,     4,     3,     8,   523,   511,   513,   515,   517,   519,
     521,     8,     3,     8,   439,   316,     4,   443,   441,   446,
       4,     8,     3,   461,     4,     4,     8,     3,   373,   375,
       3,     8,     4,   580,   582,     4,   585,     4,     4,   589,
     592,     4,     4,   596,   598,   600,   602,     3,     8,   610,
       4,     3,     8,   222,   222,   202,     4,     4,     4,     4,
       4,     4,     4,   203,   203,   203,   203,   203,   203,   203,
     203,   205,   204,   204,   204,   203,   203,     4,   203,   203,
     205,   205,   205,     4,     4,     4,   205,   205,   205,     4,
       4,     4,     4,     4,     4,     4,   205,   205,   205,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   203,     4,
       4,     4,     4,     4,     4,   205,     4,   245,     4,   205,
     289,     4,     4,     4,     4,     4,   203,   205,     4,     4,
       4,   395,     4,   475,     4,   203,     4,   203,   203,   491,
       4,     4,     4,     4,     4,     4,     4,   509,     4,     4,
     203,     4,     4,     4,   205,   434,     4,   205,   205,   458,
       4,     4,   371,   205,     4,     4,   203,     4,   203,   203,
       4,     4,   205,   205,     4,     4,     4,     4,   577,     4,
     203,   608,     4,     7,   202,     7,     7,     7,     7,     5,
     202,   172,   173,   174,   175,   205,   267,   202,   202,     5,
       5,     5,     5,   224,   226,   202,    99,   100,   101,   102,
     411,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   202,   202,     5,     5,   233,     5,
       5,   202,   202,   202,   233,   202,     7,   202,   202,   202,
     233,   233,   233,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   226,   202,   202,   202,   169,   170,
     590,   171,   267,   202,   202,   202,     5,   222,   244,   607,
     288,    21,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
     237,   303,   304,   305,   308,   310,   312,   314,   315,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   328,
     329,   331,   333,   303,     7,   299,   300,   301,     7,   388,
     389,   390,     7,   426,   427,   428,     7,   450,   451,   452,
       7,   416,   417,   418,   119,   202,   343,   344,   345,   346,
     231,   120,   122,   345,   349,   350,   351,   352,   110,   337,
     338,   339,     7,   531,   532,     7,   501,   502,   503,     7,
     364,   365,   366,   129,   130,   131,   132,   133,   134,   378,
     379,   380,   381,   382,   383,   384,   385,    21,   139,   140,
     141,   142,   237,   317,   478,   480,   543,   544,   545,   548,
     549,   551,   552,   145,   146,   147,   237,   357,   358,   359,
     360,   361,   478,   480,   149,   150,   237,   478,   480,   556,
     557,   558,   560,   152,   153,   154,   202,   478,   480,   564,
     565,   566,   567,   569,   570,   576,     7,   614,   615,   234,
       7,   468,   469,   470,     7,   484,   485,   486,   124,   510,
     526,   527,   299,     8,     8,     8,   306,   309,   311,   313,
       4,     4,     4,     4,     4,   327,     4,     4,   330,   332,
     334,     4,     4,     4,     4,     3,     8,     8,   302,     6,
       3,   391,     6,     3,   429,     6,     3,   453,     6,     3,
     419,     6,     3,     3,     6,     6,     3,     6,   340,     3,
       8,   533,     3,     6,   504,     6,     3,   367,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   546,   550,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     559,   561,     3,     8,     4,   568,     4,   571,     3,     8,
       8,   616,     3,     6,   202,   235,   236,   471,     6,     3,
     487,     6,     3,   528,     8,     6,     4,     4,     4,     4,
     203,   205,   203,   205,   203,     4,   203,   203,     4,     4,
       4,   203,   203,   205,   203,   304,   303,   301,   394,   390,
     432,   428,   456,   452,   237,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   262,   263,
     264,   265,   268,   270,   272,   273,   274,   276,   278,   315,
     386,   398,   400,   402,   404,   406,   407,   408,   409,   413,
     420,   421,   448,   478,   480,   524,   418,   344,   350,     4,
     338,   113,   114,   237,   315,   448,   478,   480,   534,   535,
     536,   537,   538,   540,   532,   507,   503,   370,   366,   203,
     203,   203,   203,   203,   203,   379,     4,     4,   203,   203,
     203,   544,   205,   203,   203,   358,     4,     4,   557,   205,
       4,   203,     4,   565,   180,   182,   183,   237,   315,   478,
     480,   617,   618,   619,   620,   622,   615,     6,     3,   474,
     470,   490,   486,     4,    22,    23,    24,    25,   307,   202,
     202,   202,   202,   202,   202,   202,     8,     8,     8,     8,
       3,     8,   202,   539,     4,     8,     3,     8,     8,   136,
     137,   138,   547,   202,   202,   202,   202,   222,   623,     4,
     621,     3,     8,   202,     8,     8,   202,   421,     4,   205,
     536,     4,   203,     4,   618,   202,     5,   202,     7,   624,
     625,   626,     3,     6,   181,   184,   185,   186,   187,   627,
     628,   629,   631,   632,   633,   634,   625,   630,     4,     4,
       4,   635,     3,     8,     4,   205,   203,   203,     4,   628,
     202,   202
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   206,   208,   207,   209,   207,   210,   207,   211,   207,
     212,   207,   213,   207,   214,   207,   215,   207,   216,   207,
     217,   207,   218,   207,   219,   207,   220,   207,   221,   207,
     222,   222,   222,   222,   222,   222,   222,   223,   225,   224,
     226,   227,   227,   228,   228,   230,   229,   231,   231,   232,
     232,   234,   233,   235,   235,   236,   236,   237,   239,   238,
     241,   240,   243,   242,   244,   244,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   247,   246,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   266,   265,   267,   267,
     267,   267,   267,   269,   268,   271,   270,   272,   273,   275,
     274,   277,   276,   278,   279,   280,   282,   281,   283,   285,
     284,   287,   286,   288,   288,   289,   289,   289,   289,   289,
     291,   290,   292,   294,   293,   296,   295,   298,   297,   299,
     299,   300,   300,   302,   301,   303,   303,   304,   304,   304,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,   304,   304,   304,   306,   305,
     307,   307,   307,   307,   309,   308,   311,   310,   313,   312,
     314,   316,   315,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   327,   326,   328,   330,   329,   332,   331,   334,
     333,   336,   335,   337,   337,   338,   340,   339,   342,   341,
     343,   343,   344,   344,   345,   346,   348,   347,   349,   349,
     350,   350,   350,   351,   352,   354,   353,   356,   355,   357,
     357,   358,   358,   358,   358,   358,   358,   359,   360,   361,
     363,   362,   364,   364,   365,   365,   367,   366,   369,   368,
     370,   370,   370,   371,   371,   373,   372,   375,   374,   377,
     376,   378,   378,   379,   379,   379,   379,   379,   379,   380,
     381,   382,   383,   384,   385,   387,   386,   388,   388,   389,
     389,   391,   390,   393,   392,   394,   394,   395,   395,   395,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     397,   396,   399,   398,   401,   400,   403,   402,   405,   404,
     406,   407,   408,   410,   409,   411,   411,   411,   411,   412,
     413,   415,   414,   416,   416,   417,   417,   419,   418,   420,
     420,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   423,   422,   425,   424,   426,   426,   427,   427,   429,
     428,   431,   430,   432,   432,   433,   433,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   435,   436,   437,
     439,   438,   441,   440,   443,   442,   444,   446,   445,   447,
     449,   448,   450,   450,   451,   451,   453,   452,   455,   454,
     456,   456,   457,   457,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   459,   461,   460,   462,   463,   464,   465,
     467,   466,   468,   468,   469,   469,   471,   470,   473,   472,
     474,   474,   475,   475,   475,   475,   475,   475,   475,   477,
     476,   479,   478,   481,   480,   483,   482,   484,   484,   485,
     485,   487,   486,   489,   488,   490,   490,   491,   491,   491,
     491,   491,   491,   491,   491,   491,   491,   491,   493,   492,
     494,   496,   495,   497,   498,   500,   499,   501,   501,   502,
     502,   504,   503,   506,   505,   507,   507,   508,   508,   509,
     509,   509,   509,   509,   509,   509,   509,   509,   509,   509,
     511,   510,   513,   512,   515,   514,   517,   516,   519,   518,
     521,   520,   523,   522,   525,   524,   526,   526,   528,   527,
     530,   529,   531,   531,   533,   532,   534,   534,   535,   535,
     536,   536,   536,   536,   536,   536,   536,   537,   539,   538,
     540,   542,   541,   543,   543,   544,   544,   544,   544,   544,
     544,   544,   544,   544,   546,   545,   547,   547,   547,   548,
     550,   549,   551,   552,   553,   555,   554,   556,   556,   557,
     557,   557,   557,   557,   559,   558,   561,   560,   563,   562,
     564,   564,   565,   565,   565,   565,   565,   565,   566,   568,
     567,   569,   571,   570,   573,   572,   575,   574,   576,   576,
     577,   577,   577,   577,   577,   577,   577,   577,   577,   577,
     577,   577,   577,   577,   577,   577,   577,   577,   578,   580,
     579,   582,   581,   583,   585,   584,   586,   587,   589,   588,
     590,   590,   592,   591,   593,   594,   596,   595,   598,   597,
     600,   599,   602,   601,   604,   603,   606,   605,   607,   607,
     608,   608,   610,   609,   611,   613,   612,   614,   614,   616,
     615,   617,   617,   618,   618,   618,   618,   618,   618,   618,
     619,   621,   620,   623,   622,   624,   624,   626,   625,   627,
     627,   628,   628,   628,   628,   628,   630,   629,   631,   632,
     633,   635,   634
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     3,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
  "\"t1-percent\"", "\"t2-percent\"", "\"cache-threshold\"",
  "\"cache-max-age\"", "\"decline-probation-period\"", "\"server-tag\"",
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
  "$@62", "require_client_classes", "$@63", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
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
       0,   292,   292,   292,   293,   293,   294,   294,   295,   295,
     296,   296,   297,   297,   298,   298,   299,   299,   300,   300,
     301,   301,   302,   302,   303,   303,   304,   304,   305,   305,
     313,   314,   315,   316,   317,   318,   319,   322,   327,   327,
     338,   341,   342,   345,   350,   358,   358,   365,   366,   369,
     373,   380,   380,   387,   388,   391,   395,   406,   415,   415,
     430,   430,   447,   447,   456,   457,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     506,   507,   508,   509,   510,   511,   512,   513,   514,   515,
     516,   517,   518,   519,   520,   521,   522,   525,   525,   534,
     540,   546,   552,   558,   564,   570,   576,   582,   588,   594,
     600,   606,   612,   618,   624,   630,   636,   636,   645,   648,
     651,   654,   657,   663,   663,   672,   672,   681,   687,   693,
     693,   702,   702,   711,   717,   723,   729,   729,   738,   744,
     744,   756,   756,   765,   766,   769,   770,   771,   772,   773,
     776,   776,   787,   793,   793,   806,   806,   819,   819,   830,
     831,   834,   835,   838,   838,   848,   849,   852,   853,   854,
     855,   856,   857,   858,   859,   860,   861,   862,   863,   864,
     865,   866,   867,   868,   869,   870,   871,   872,   875,   875,
     883,   884,   885,   886,   889,   889,   898,   898,   907,   907,
     916,   922,   922,   931,   937,   943,   949,   955,   961,   967,
     973,   979,   985,   985,   994,  1000,  1000,  1009,  1009,  1018,
    1018,  1027,  1027,  1038,  1039,  1041,  1043,  1043,  1062,  1062,
    1073,  1074,  1077,  1078,  1081,  1086,  1091,  1091,  1102,  1103,
    1106,  1107,  1108,  1111,  1116,  1123,  1123,  1136,  1136,  1149,
    1150,  1153,  1154,  1155,  1156,  1157,  1158,  1161,  1167,  1173,
    1179,  1179,  1190,  1191,  1194,  1195,  1198,  1198,  1208,  1208,
    1218,  1219,  1220,  1223,  1224,  1227,  1227,  1236,  1236,  1245,
    1245,  1257,  1258,  1261,  1262,  1263,  1264,  1265,  1266,  1269,
    1275,  1281,  1287,  1293,  1299,  1308,  1308,  1322,  1323,  1326,
    1327,  1334,  1334,  1360,  1360,  1371,  1372,  1376,  1377,  1378,
    1379,  1380,  1381,  1382,  1383,  1384,  1385,  1386,  1387,  1388,
    1389,  1390,  1391,  1392,  1393,  1394,  1395,  1396,  1397,  1398,
    1399,  1400,  1401,  1402,  1403,  1404,  1405,  1406,  1407,  1408,
    1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,  1418,
    1421,  1421,  1430,  1430,  1439,  1439,  1448,  1448,  1457,  1457,
    1468,  1474,  1480,  1486,  1486,  1494,  1495,  1496,  1497,  1500,
    1506,  1514,  1514,  1526,  1527,  1531,  1532,  1535,  1535,  1543,
    1544,  1547,  1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,
    1556,  1557,  1558,  1559,  1560,  1561,  1562,  1563,  1564,  1565,
    1566,  1567,  1568,  1569,  1570,  1571,  1572,  1573,  1574,  1575,
    1576,  1577,  1578,  1579,  1580,  1581,  1582,  1583,  1584,  1585,
    1586,  1593,  1593,  1607,  1607,  1616,  1617,  1620,  1621,  1626,
    1626,  1641,  1641,  1655,  1656,  1659,  1660,  1663,  1664,  1665,
    1666,  1667,  1668,  1669,  1670,  1671,  1672,  1675,  1677,  1683,
    1685,  1685,  1694,  1694,  1703,  1703,  1712,  1714,  1714,  1723,
    1733,  1733,  1746,  1747,  1752,  1753,  1758,  1758,  1770,  1770,
    1782,  1783,  1788,  1789,  1794,  1795,  1796,  1797,  1798,  1799,
    1800,  1801,  1802,  1805,  1807,  1807,  1816,  1818,  1820,  1826,
    1835,  1835,  1848,  1849,  1852,  1853,  1856,  1856,  1866,  1866,
    1876,  1877,  1880,  1881,  1882,  1883,  1884,  1885,  1886,  1889,
    1889,  1898,  1898,  1923,  1923,  1953,  1953,  1966,  1967,  1970,
    1971,  1974,  1974,  1986,  1986,  1998,  1999,  2002,  2003,  2004,
    2005,  2006,  2007,  2008,  2009,  2010,  2011,  2012,  2015,  2015,
    2024,  2030,  2030,  2039,  2045,  2054,  2054,  2065,  2066,  2069,
    2070,  2073,  2073,  2082,  2082,  2091,  2092,  2095,  2096,  2100,
    2101,  2102,  2103,  2104,  2105,  2106,  2107,  2108,  2109,  2110,
    2113,  2113,  2124,  2124,  2135,  2135,  2144,  2144,  2153,  2153,
    2162,  2162,  2171,  2171,  2185,  2185,  2196,  2197,  2200,  2200,
    2212,  2212,  2223,  2224,  2227,  2227,  2237,  2238,  2241,  2242,
    2245,  2246,  2247,  2248,  2249,  2250,  2251,  2254,  2256,  2256,
    2265,  2274,  2274,  2287,  2288,  2291,  2292,  2293,  2294,  2295,
    2296,  2297,  2298,  2299,  2302,  2302,  2310,  2311,  2312,  2315,
    2321,  2321,  2330,  2336,  2344,  2352,  2352,  2363,  2364,  2367,
    2368,  2369,  2370,  2371,  2374,  2374,  2383,  2383,  2395,  2395,
    2408,  2409,  2412,  2413,  2414,  2415,  2416,  2417,  2420,  2426,
    2426,  2435,  2441,  2441,  2451,  2451,  2464,  2464,  2474,  2475,
    2478,  2479,  2480,  2481,  2482,  2483,  2484,  2485,  2486,  2487,
    2488,  2489,  2490,  2491,  2492,  2493,  2494,  2495,  2498,  2505,
    2505,  2514,  2514,  2523,  2529,  2529,  2538,  2544,  2550,  2550,
    2559,  2560,  2563,  2563,  2573,  2580,  2587,  2587,  2596,  2596,
    2606,  2606,  2616,  2616,  2628,  2628,  2640,  2640,  2650,  2651,
    2655,  2656,  2659,  2659,  2670,  2678,  2678,  2691,  2692,  2696,
    2696,  2704,  2705,  2708,  2709,  2710,  2711,  2712,  2713,  2714,
    2717,  2723,  2723,  2732,  2732,  2743,  2744,  2747,  2747,  2755,
    2756,  2759,  2760,  2761,  2762,  2763,  2766,  2766,  2775,  2781,
    2787,  2793,  2793
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
#line 5861 "dhcp6_parser.cc"

#line 2802 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
