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
#line 277 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 400 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 277 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 406 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 277 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 412 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 277 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 418 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 277 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 424 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 277 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 430 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 277 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 436 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 277 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 442 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 277 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 448 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 277 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 454 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 277 "dhcp6_parser.yy"
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
#line 286 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 739 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 287 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 745 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 288 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 751 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 289 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 757 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 290 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 763 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 291 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 769 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 292 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 775 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 293 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 781 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 294 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 787 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 295 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 793 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 296 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 799 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 297 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 805 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 298 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 811 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 299 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 817 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 307 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 308 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 309 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 310 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 311 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 847 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 312 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 313 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 859 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 316 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 868 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 321 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 879 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 326 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 889 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 332 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 339 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 905 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 344 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 45: // $@16: %empty
#line 352 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 925 "dhcp6_parser.cc"
    break;

  case 46: // list_generic: "[" $@16 list_content "]"
#line 355 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 933 "dhcp6_parser.cc"
    break;

  case 49: // not_empty_list: value
#line 363 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 942 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list "," value
#line 367 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp6_parser.cc"
    break;

  case 51: // $@17: %empty
#line 374 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 959 "dhcp6_parser.cc"
    break;

  case 52: // list_strings: "[" $@17 list_strings_content "]"
#line 376 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 968 "dhcp6_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 385 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 977 "dhcp6_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 389 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 986 "dhcp6_parser.cc"
    break;

  case 57: // unknown_map_entry: "constant string" ":"
#line 400 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 997 "dhcp6_parser.cc"
    break;

  case 58: // $@18: %empty
#line 409 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1008 "dhcp6_parser.cc"
    break;

  case 59: // syntax_map: "{" $@18 global_object "}"
#line 414 "dhcp6_parser.yy"
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
#line 424 "dhcp6_parser.yy"
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
#line 433 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp6_parser.cc"
    break;

  case 62: // $@20: %empty
#line 441 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp6_parser.cc"
    break;

  case 63: // sub_dhcp6: "{" $@20 global_params "}"
#line 445 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1065 "dhcp6_parser.cc"
    break;

  case 122: // $@21: %empty
#line 514 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1074 "dhcp6_parser.cc"
    break;

  case 123: // data_directory: "data-directory" $@21 ":" "constant string"
#line 517 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1084 "dhcp6_parser.cc"
    break;

  case 124: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 523 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1094 "dhcp6_parser.cc"
    break;

  case 125: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 529 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 126: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 535 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1114 "dhcp6_parser.cc"
    break;

  case 127: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 541 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 128: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 547 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1134 "dhcp6_parser.cc"
    break;

  case 129: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 553 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1144 "dhcp6_parser.cc"
    break;

  case 130: // renew_timer: "renew-timer" ":" "integer"
#line 559 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1154 "dhcp6_parser.cc"
    break;

  case 131: // rebind_timer: "rebind-timer" ":" "integer"
#line 565 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1164 "dhcp6_parser.cc"
    break;

  case 132: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 571 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1174 "dhcp6_parser.cc"
    break;

  case 133: // t1_percent: "t1-percent" ":" "floating point"
#line 577 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1184 "dhcp6_parser.cc"
    break;

  case 134: // t2_percent: "t2-percent" ":" "floating point"
#line 583 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1194 "dhcp6_parser.cc"
    break;

  case 135: // cache_threshold: "cache-threshold" ":" "floating point"
#line 589 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1204 "dhcp6_parser.cc"
    break;

  case 136: // cache_max_age: "cache-max-age" ":" "integer"
#line 595 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1214 "dhcp6_parser.cc"
    break;

  case 137: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 601 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 138: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 607 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1234 "dhcp6_parser.cc"
    break;

  case 139: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 613 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1244 "dhcp6_parser.cc"
    break;

  case 140: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 619 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1254 "dhcp6_parser.cc"
    break;

  case 141: // $@22: %empty
#line 625 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 142: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 628 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 143: // ddns_replace_client_name_value: "when-present"
#line 634 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1280 "dhcp6_parser.cc"
    break;

  case 144: // ddns_replace_client_name_value: "never"
#line 637 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1288 "dhcp6_parser.cc"
    break;

  case 145: // ddns_replace_client_name_value: "always"
#line 640 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1296 "dhcp6_parser.cc"
    break;

  case 146: // ddns_replace_client_name_value: "when-not-present"
#line 643 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1304 "dhcp6_parser.cc"
    break;

  case 147: // ddns_replace_client_name_value: "boolean"
#line 646 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1313 "dhcp6_parser.cc"
    break;

  case 148: // $@23: %empty
#line 652 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp6_parser.cc"
    break;

  case 149: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 655 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1332 "dhcp6_parser.cc"
    break;

  case 150: // $@24: %empty
#line 661 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp6_parser.cc"
    break;

  case 151: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 664 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc"
    break;

  case 152: // $@25: %empty
#line 670 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1360 "dhcp6_parser.cc"
    break;

  case 153: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 673 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1370 "dhcp6_parser.cc"
    break;

  case 154: // $@26: %empty
#line 679 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1379 "dhcp6_parser.cc"
    break;

  case 155: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 682 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 156: // store_extended_info: "store-extended-info" ":" "boolean"
#line 688 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 157: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 694 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1409 "dhcp6_parser.cc"
    break;

  case 158: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 700 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 159: // $@27: %empty
#line 706 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1428 "dhcp6_parser.cc"
    break;

  case 160: // server_tag: "server-tag" $@27 ":" "constant string"
#line 709 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1438 "dhcp6_parser.cc"
    break;

  case 161: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 715 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1448 "dhcp6_parser.cc"
    break;

  case 162: // $@28: %empty
#line 721 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 163: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 727 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 164: // $@29: %empty
#line 733 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 165: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 737 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1489 "dhcp6_parser.cc"
    break;

  case 173: // $@30: %empty
#line 753 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1501 "dhcp6_parser.cc"
    break;

  case 174: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 759 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1510 "dhcp6_parser.cc"
    break;

  case 175: // re_detect: "re-detect" ":" "boolean"
#line 764 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1520 "dhcp6_parser.cc"
    break;

  case 176: // $@31: %empty
#line 770 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 177: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 776 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1543 "dhcp6_parser.cc"
    break;

  case 178: // $@32: %empty
#line 783 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1555 "dhcp6_parser.cc"
    break;

  case 179: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 789 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1566 "dhcp6_parser.cc"
    break;

  case 180: // $@33: %empty
#line 796 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1578 "dhcp6_parser.cc"
    break;

  case 181: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 802 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1587 "dhcp6_parser.cc"
    break;

  case 186: // $@34: %empty
#line 815 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1597 "dhcp6_parser.cc"
    break;

  case 187: // database: "{" $@34 database_map_params "}"
#line 819 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1607 "dhcp6_parser.cc"
    break;

  case 211: // $@35: %empty
#line 852 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1616 "dhcp6_parser.cc"
    break;

  case 212: // database_type: "type" $@35 ":" db_type
#line 855 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1625 "dhcp6_parser.cc"
    break;

  case 213: // db_type: "memfile"
#line 860 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1631 "dhcp6_parser.cc"
    break;

  case 214: // db_type: "mysql"
#line 861 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1637 "dhcp6_parser.cc"
    break;

  case 215: // db_type: "postgresql"
#line 862 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1643 "dhcp6_parser.cc"
    break;

  case 216: // db_type: "cql"
#line 863 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1649 "dhcp6_parser.cc"
    break;

  case 217: // $@36: %empty
#line 866 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1658 "dhcp6_parser.cc"
    break;

  case 218: // user: "user" $@36 ":" "constant string"
#line 869 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 219: // $@37: %empty
#line 875 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1677 "dhcp6_parser.cc"
    break;

  case 220: // password: "password" $@37 ":" "constant string"
#line 878 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1687 "dhcp6_parser.cc"
    break;

  case 221: // $@38: %empty
#line 884 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1696 "dhcp6_parser.cc"
    break;

  case 222: // host: "host" $@38 ":" "constant string"
#line 887 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1706 "dhcp6_parser.cc"
    break;

  case 223: // port: "port" ":" "integer"
#line 893 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1716 "dhcp6_parser.cc"
    break;

  case 224: // $@39: %empty
#line 899 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1725 "dhcp6_parser.cc"
    break;

  case 225: // name: "name" $@39 ":" "constant string"
#line 902 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1735 "dhcp6_parser.cc"
    break;

  case 226: // persist: "persist" ":" "boolean"
#line 908 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1745 "dhcp6_parser.cc"
    break;

  case 227: // lfc_interval: "lfc-interval" ":" "integer"
#line 914 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 228: // readonly: "readonly" ":" "boolean"
#line 920 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1765 "dhcp6_parser.cc"
    break;

  case 229: // connect_timeout: "connect-timeout" ":" "integer"
#line 926 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1775 "dhcp6_parser.cc"
    break;

  case 230: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 932 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1785 "dhcp6_parser.cc"
    break;

  case 231: // max_row_errors: "max-row-errors" ":" "integer"
#line 938 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1795 "dhcp6_parser.cc"
    break;

  case 232: // request_timeout: "request-timeout" ":" "integer"
#line 944 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1805 "dhcp6_parser.cc"
    break;

  case 233: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 950 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1815 "dhcp6_parser.cc"
    break;

  case 234: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 956 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 235: // $@40: %empty
#line 962 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1834 "dhcp6_parser.cc"
    break;

  case 236: // contact_points: "contact-points" $@40 ":" "constant string"
#line 965 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 237: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 971 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1854 "dhcp6_parser.cc"
    break;

  case 238: // $@41: %empty
#line 977 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1863 "dhcp6_parser.cc"
    break;

  case 239: // keyspace: "keyspace" $@41 ":" "constant string"
#line 980 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1873 "dhcp6_parser.cc"
    break;

  case 240: // $@42: %empty
#line 986 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1882 "dhcp6_parser.cc"
    break;

  case 241: // consistency: "consistency" $@42 ":" "constant string"
#line 989 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1892 "dhcp6_parser.cc"
    break;

  case 242: // $@43: %empty
#line 995 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1901 "dhcp6_parser.cc"
    break;

  case 243: // serial_consistency: "serial-consistency" $@43 ":" "constant string"
#line 998 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1911 "dhcp6_parser.cc"
    break;

  case 244: // $@44: %empty
#line 1004 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1923 "dhcp6_parser.cc"
    break;

  case 245: // sanity_checks: "sanity-checks" $@44 ":" "{" sanity_checks_params "}"
#line 1010 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1932 "dhcp6_parser.cc"
    break;

  case 249: // $@45: %empty
#line 1020 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1941 "dhcp6_parser.cc"
    break;

  case 250: // lease_checks: "lease-checks" $@45 ":" "constant string"
#line 1023 "dhcp6_parser.yy"
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
#line 1961 "dhcp6_parser.cc"
    break;

  case 251: // $@46: %empty
#line 1039 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1973 "dhcp6_parser.cc"
    break;

  case 252: // mac_sources: "mac-sources" $@46 ":" "[" mac_sources_list "]"
#line 1045 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1982 "dhcp6_parser.cc"
    break;

  case 257: // duid_id: "duid"
#line 1058 "dhcp6_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1991 "dhcp6_parser.cc"
    break;

  case 258: // string_id: "constant string"
#line 1063 "dhcp6_parser.yy"
                   {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2000 "dhcp6_parser.cc"
    break;

  case 259: // $@47: %empty
#line 1068 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2012 "dhcp6_parser.cc"
    break;

  case 260: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1074 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2021 "dhcp6_parser.cc"
    break;

  case 266: // hw_address_id: "hw-address"
#line 1088 "dhcp6_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2030 "dhcp6_parser.cc"
    break;

  case 267: // flex_id: "flex-id"
#line 1093 "dhcp6_parser.yy"
                  {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2039 "dhcp6_parser.cc"
    break;

  case 268: // $@48: %empty
#line 1100 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2051 "dhcp6_parser.cc"
    break;

  case 269: // relay_supplied_options: "relay-supplied-options" $@48 ":" "[" list_content "]"
#line 1106 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2060 "dhcp6_parser.cc"
    break;

  case 270: // $@49: %empty
#line 1113 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2072 "dhcp6_parser.cc"
    break;

  case 271: // dhcp_multi_threading: "multi-threading" $@49 ":" "{" multi_threading_params "}"
#line 1119 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2083 "dhcp6_parser.cc"
    break;

  case 280: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1138 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 281: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1144 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2103 "dhcp6_parser.cc"
    break;

  case 282: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1150 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2113 "dhcp6_parser.cc"
    break;

  case 283: // $@50: %empty
#line 1156 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2125 "dhcp6_parser.cc"
    break;

  case 284: // hooks_libraries: "hooks-libraries" $@50 ":" "[" hooks_libraries_list "]"
#line 1162 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2134 "dhcp6_parser.cc"
    break;

  case 289: // $@51: %empty
#line 1175 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2144 "dhcp6_parser.cc"
    break;

  case 290: // hooks_library: "{" $@51 hooks_params "}"
#line 1179 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2154 "dhcp6_parser.cc"
    break;

  case 291: // $@52: %empty
#line 1185 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 292: // sub_hooks_library: "{" $@52 hooks_params "}"
#line 1189 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2174 "dhcp6_parser.cc"
    break;

  case 298: // $@53: %empty
#line 1204 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2183 "dhcp6_parser.cc"
    break;

  case 299: // library: "library" $@53 ":" "constant string"
#line 1207 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2193 "dhcp6_parser.cc"
    break;

  case 300: // $@54: %empty
#line 1213 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 301: // parameters: "parameters" $@54 ":" map_value
#line 1216 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 302: // $@55: %empty
#line 1222 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2223 "dhcp6_parser.cc"
    break;

  case 303: // expired_leases_processing: "expired-leases-processing" $@55 ":" "{" expired_leases_params "}"
#line 1228 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2233 "dhcp6_parser.cc"
    break;

  case 312: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1246 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2243 "dhcp6_parser.cc"
    break;

  case 313: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1252 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2253 "dhcp6_parser.cc"
    break;

  case 314: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1258 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2263 "dhcp6_parser.cc"
    break;

  case 315: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1264 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2273 "dhcp6_parser.cc"
    break;

  case 316: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1270 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2283 "dhcp6_parser.cc"
    break;

  case 317: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1276 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2293 "dhcp6_parser.cc"
    break;

  case 318: // $@56: %empty
#line 1285 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2305 "dhcp6_parser.cc"
    break;

  case 319: // subnet6_list: "subnet6" $@56 ":" "[" subnet6_list_content "]"
#line 1291 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2314 "dhcp6_parser.cc"
    break;

  case 324: // $@57: %empty
#line 1311 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2324 "dhcp6_parser.cc"
    break;

  case 325: // subnet6: "{" $@57 subnet6_params "}"
#line 1315 "dhcp6_parser.yy"
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
#line 2350 "dhcp6_parser.cc"
    break;

  case 326: // $@58: %empty
#line 1337 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2360 "dhcp6_parser.cc"
    break;

  case 327: // sub_subnet6: "{" $@58 subnet6_params "}"
#line 1341 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2370 "dhcp6_parser.cc"
    break;

  case 368: // $@59: %empty
#line 1393 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2379 "dhcp6_parser.cc"
    break;

  case 369: // subnet: "subnet" $@59 ":" "constant string"
#line 1396 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2389 "dhcp6_parser.cc"
    break;

  case 370: // $@60: %empty
#line 1402 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2398 "dhcp6_parser.cc"
    break;

  case 371: // interface: "interface" $@60 ":" "constant string"
#line 1405 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2408 "dhcp6_parser.cc"
    break;

  case 372: // $@61: %empty
#line 1411 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2417 "dhcp6_parser.cc"
    break;

  case 373: // interface_id: "interface-id" $@61 ":" "constant string"
#line 1414 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2427 "dhcp6_parser.cc"
    break;

  case 374: // $@62: %empty
#line 1420 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2436 "dhcp6_parser.cc"
    break;

  case 375: // client_class: "client-class" $@62 ":" "constant string"
#line 1423 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2446 "dhcp6_parser.cc"
    break;

  case 376: // $@63: %empty
#line 1429 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2458 "dhcp6_parser.cc"
    break;

  case 377: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1435 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2467 "dhcp6_parser.cc"
    break;

  case 378: // $@64: %empty
#line 1440 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2476 "dhcp6_parser.cc"
    break;

  case 379: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1443 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2485 "dhcp6_parser.cc"
    break;

  case 380: // hr_mode: "disabled"
#line 1448 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2491 "dhcp6_parser.cc"
    break;

  case 381: // hr_mode: "out-of-pool"
#line 1449 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2497 "dhcp6_parser.cc"
    break;

  case 382: // hr_mode: "global"
#line 1450 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2503 "dhcp6_parser.cc"
    break;

  case 383: // hr_mode: "all"
#line 1451 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2509 "dhcp6_parser.cc"
    break;

  case 384: // id: "id" ":" "integer"
#line 1454 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2519 "dhcp6_parser.cc"
    break;

  case 385: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1460 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2529 "dhcp6_parser.cc"
    break;

  case 386: // $@65: %empty
#line 1468 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2541 "dhcp6_parser.cc"
    break;

  case 387: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1474 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2550 "dhcp6_parser.cc"
    break;

  case 392: // $@66: %empty
#line 1489 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 393: // shared_network: "{" $@66 shared_network_params "}"
#line 1493 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2568 "dhcp6_parser.cc"
    break;

  case 431: // $@67: %empty
#line 1542 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2580 "dhcp6_parser.cc"
    break;

  case 432: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1548 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp6_parser.cc"
    break;

  case 433: // $@68: %empty
#line 1556 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2598 "dhcp6_parser.cc"
    break;

  case 434: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1559 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2606 "dhcp6_parser.cc"
    break;

  case 439: // $@69: %empty
#line 1575 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2616 "dhcp6_parser.cc"
    break;

  case 440: // option_def_entry: "{" $@69 option_def_params "}"
#line 1579 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2628 "dhcp6_parser.cc"
    break;

  case 441: // $@70: %empty
#line 1590 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 442: // sub_option_def: "{" $@70 option_def_params "}"
#line 1594 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2650 "dhcp6_parser.cc"
    break;

  case 458: // code: "code" ":" "integer"
#line 1626 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2660 "dhcp6_parser.cc"
    break;

  case 460: // $@71: %empty
#line 1634 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp6_parser.cc"
    break;

  case 461: // option_def_type: "type" $@71 ":" "constant string"
#line 1637 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2679 "dhcp6_parser.cc"
    break;

  case 462: // $@72: %empty
#line 1643 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2688 "dhcp6_parser.cc"
    break;

  case 463: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1646 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2698 "dhcp6_parser.cc"
    break;

  case 464: // $@73: %empty
#line 1652 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2707 "dhcp6_parser.cc"
    break;

  case 465: // space: "space" $@73 ":" "constant string"
#line 1655 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2717 "dhcp6_parser.cc"
    break;

  case 467: // $@74: %empty
#line 1663 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp6_parser.cc"
    break;

  case 468: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1666 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2736 "dhcp6_parser.cc"
    break;

  case 469: // option_def_array: "array" ":" "boolean"
#line 1672 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2746 "dhcp6_parser.cc"
    break;

  case 470: // $@75: %empty
#line 1682 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2758 "dhcp6_parser.cc"
    break;

  case 471: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1688 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2767 "dhcp6_parser.cc"
    break;

  case 476: // $@76: %empty
#line 1707 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2777 "dhcp6_parser.cc"
    break;

  case 477: // option_data_entry: "{" $@76 option_data_params "}"
#line 1711 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 478: // $@77: %empty
#line 1719 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2796 "dhcp6_parser.cc"
    break;

  case 479: // sub_option_data: "{" $@77 option_data_params "}"
#line 1723 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2805 "dhcp6_parser.cc"
    break;

  case 494: // $@78: %empty
#line 1756 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2814 "dhcp6_parser.cc"
    break;

  case 495: // option_data_data: "data" $@78 ":" "constant string"
#line 1759 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2824 "dhcp6_parser.cc"
    break;

  case 498: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1769 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2834 "dhcp6_parser.cc"
    break;

  case 499: // option_data_always_send: "always-send" ":" "boolean"
#line 1775 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2844 "dhcp6_parser.cc"
    break;

  case 500: // $@79: %empty
#line 1784 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2856 "dhcp6_parser.cc"
    break;

  case 501: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1790 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2865 "dhcp6_parser.cc"
    break;

  case 506: // $@80: %empty
#line 1805 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 507: // pool_list_entry: "{" $@80 pool_params "}"
#line 1809 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 508: // $@81: %empty
#line 1815 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2895 "dhcp6_parser.cc"
    break;

  case 509: // sub_pool6: "{" $@81 pool_params "}"
#line 1819 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 519: // $@82: %empty
#line 1838 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 520: // pool_entry: "pool" $@82 ":" "constant string"
#line 1841 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2924 "dhcp6_parser.cc"
    break;

  case 521: // $@83: %empty
#line 1847 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp6_parser.cc"
    break;

  case 522: // user_context: "user-context" $@83 ":" map_value
#line 1849 "dhcp6_parser.yy"
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
#line 2959 "dhcp6_parser.cc"
    break;

  case 523: // $@84: %empty
#line 1872 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2967 "dhcp6_parser.cc"
    break;

  case 524: // comment: "comment" $@84 ":" "constant string"
#line 1874 "dhcp6_parser.yy"
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
#line 2996 "dhcp6_parser.cc"
    break;

  case 525: // $@85: %empty
#line 1902 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3008 "dhcp6_parser.cc"
    break;

  case 526: // pd_pools_list: "pd-pools" $@85 ":" "[" pd_pools_list_content "]"
#line 1908 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 531: // $@86: %empty
#line 1923 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 532: // pd_pool_entry: "{" $@86 pd_pool_params "}"
#line 1927 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3039 "dhcp6_parser.cc"
    break;

  case 533: // $@87: %empty
#line 1935 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3049 "dhcp6_parser.cc"
    break;

  case 534: // sub_pd_pool: "{" $@87 pd_pool_params "}"
#line 1939 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3061 "dhcp6_parser.cc"
    break;

  case 548: // $@88: %empty
#line 1964 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3070 "dhcp6_parser.cc"
    break;

  case 549: // pd_prefix: "prefix" $@88 ":" "constant string"
#line 1967 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3080 "dhcp6_parser.cc"
    break;

  case 550: // pd_prefix_len: "prefix-len" ":" "integer"
#line 1973 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3090 "dhcp6_parser.cc"
    break;

  case 551: // $@89: %empty
#line 1979 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3099 "dhcp6_parser.cc"
    break;

  case 552: // excluded_prefix: "excluded-prefix" $@89 ":" "constant string"
#line 1982 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3109 "dhcp6_parser.cc"
    break;

  case 553: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 1988 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3119 "dhcp6_parser.cc"
    break;

  case 554: // pd_delegated_len: "delegated-len" ":" "integer"
#line 1994 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3129 "dhcp6_parser.cc"
    break;

  case 555: // $@90: %empty
#line 2003 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3141 "dhcp6_parser.cc"
    break;

  case 556: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2009 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3150 "dhcp6_parser.cc"
    break;

  case 561: // $@91: %empty
#line 2022 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3160 "dhcp6_parser.cc"
    break;

  case 562: // reservation: "{" $@91 reservation_params "}"
#line 2026 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3169 "dhcp6_parser.cc"
    break;

  case 563: // $@92: %empty
#line 2031 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 564: // sub_reservation: "{" $@92 reservation_params "}"
#line 2035 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3188 "dhcp6_parser.cc"
    break;

  case 580: // $@93: %empty
#line 2062 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3200 "dhcp6_parser.cc"
    break;

  case 581: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2068 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3209 "dhcp6_parser.cc"
    break;

  case 582: // $@94: %empty
#line 2073 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 583: // prefixes: "prefixes" $@94 ":" list_strings
#line 2079 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3230 "dhcp6_parser.cc"
    break;

  case 584: // $@95: %empty
#line 2084 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp6_parser.cc"
    break;

  case 585: // duid: "duid" $@95 ":" "constant string"
#line 2087 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3249 "dhcp6_parser.cc"
    break;

  case 586: // $@96: %empty
#line 2093 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3258 "dhcp6_parser.cc"
    break;

  case 587: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2096 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3268 "dhcp6_parser.cc"
    break;

  case 588: // $@97: %empty
#line 2102 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3277 "dhcp6_parser.cc"
    break;

  case 589: // hostname: "hostname" $@97 ":" "constant string"
#line 2105 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3287 "dhcp6_parser.cc"
    break;

  case 590: // $@98: %empty
#line 2111 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3296 "dhcp6_parser.cc"
    break;

  case 591: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2114 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3306 "dhcp6_parser.cc"
    break;

  case 592: // $@99: %empty
#line 2120 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp6_parser.cc"
    break;

  case 593: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2126 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3327 "dhcp6_parser.cc"
    break;

  case 594: // $@100: %empty
#line 2134 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3339 "dhcp6_parser.cc"
    break;

  case 595: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2140 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 598: // $@101: %empty
#line 2149 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3357 "dhcp6_parser.cc"
    break;

  case 599: // ip_address: "ip-address" $@101 ":" "constant string"
#line 2152 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3367 "dhcp6_parser.cc"
    break;

  case 600: // $@102: %empty
#line 2161 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3379 "dhcp6_parser.cc"
    break;

  case 601: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2167 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3388 "dhcp6_parser.cc"
    break;

  case 604: // $@103: %empty
#line 2176 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 605: // client_class_entry: "{" $@103 client_class_params "}"
#line 2180 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3408 "dhcp6_parser.cc"
    break;

  case 618: // $@104: %empty
#line 2205 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3417 "dhcp6_parser.cc"
    break;

  case 619: // client_class_test: "test" $@104 ":" "constant string"
#line 2208 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3427 "dhcp6_parser.cc"
    break;

  case 620: // only_if_required: "only-if-required" ":" "boolean"
#line 2214 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3437 "dhcp6_parser.cc"
    break;

  case 621: // $@105: %empty
#line 2223 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3449 "dhcp6_parser.cc"
    break;

  case 622: // server_id: "server-id" $@105 ":" "{" server_id_params "}"
#line 2229 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3460 "dhcp6_parser.cc"
    break;

  case 634: // $@106: %empty
#line 2251 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3469 "dhcp6_parser.cc"
    break;

  case 635: // server_id_type: "type" $@106 ":" duid_type
#line 2254 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3478 "dhcp6_parser.cc"
    break;

  case 636: // duid_type: "LLT"
#line 2259 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3484 "dhcp6_parser.cc"
    break;

  case 637: // duid_type: "EN"
#line 2260 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3490 "dhcp6_parser.cc"
    break;

  case 638: // duid_type: "LL"
#line 2261 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3496 "dhcp6_parser.cc"
    break;

  case 639: // htype: "htype" ":" "integer"
#line 2264 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3506 "dhcp6_parser.cc"
    break;

  case 640: // $@107: %empty
#line 2270 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3515 "dhcp6_parser.cc"
    break;

  case 641: // identifier: "identifier" $@107 ":" "constant string"
#line 2273 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3525 "dhcp6_parser.cc"
    break;

  case 642: // time: "time" ":" "integer"
#line 2279 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3535 "dhcp6_parser.cc"
    break;

  case 643: // enterprise_id: "enterprise-id" ":" "integer"
#line 2285 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3545 "dhcp6_parser.cc"
    break;

  case 644: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2293 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 645: // $@108: %empty
#line 2301 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3567 "dhcp6_parser.cc"
    break;

  case 646: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2307 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3576 "dhcp6_parser.cc"
    break;

  case 654: // $@109: %empty
#line 2323 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3585 "dhcp6_parser.cc"
    break;

  case 655: // socket_type: "socket-type" $@109 ":" "constant string"
#line 2326 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3595 "dhcp6_parser.cc"
    break;

  case 656: // $@110: %empty
#line 2332 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3604 "dhcp6_parser.cc"
    break;

  case 657: // socket_name: "socket-name" $@110 ":" "constant string"
#line 2335 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3614 "dhcp6_parser.cc"
    break;

  case 658: // $@111: %empty
#line 2344 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3626 "dhcp6_parser.cc"
    break;

  case 659: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2350 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3637 "dhcp6_parser.cc"
    break;

  case 668: // enable_queue: "enable-queue" ":" "boolean"
#line 2369 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3647 "dhcp6_parser.cc"
    break;

  case 669: // $@112: %empty
#line 2375 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3656 "dhcp6_parser.cc"
    break;

  case 670: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2378 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3666 "dhcp6_parser.cc"
    break;

  case 671: // capacity: "capacity" ":" "integer"
#line 2384 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3676 "dhcp6_parser.cc"
    break;

  case 672: // $@113: %empty
#line 2390 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3685 "dhcp6_parser.cc"
    break;

  case 673: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2393 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3694 "dhcp6_parser.cc"
    break;

  case 674: // $@114: %empty
#line 2400 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 675: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2406 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3717 "dhcp6_parser.cc"
    break;

  case 676: // $@115: %empty
#line 2413 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 677: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2417 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 698: // enable_updates: "enable-updates" ":" "boolean"
#line 2447 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3747 "dhcp6_parser.cc"
    break;

  case 699: // $@116: %empty
#line 2454 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 700: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2457 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 701: // $@117: %empty
#line 2463 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 702: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2466 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 703: // server_port: "server-port" ":" "integer"
#line 2472 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3795 "dhcp6_parser.cc"
    break;

  case 704: // $@118: %empty
#line 2478 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3804 "dhcp6_parser.cc"
    break;

  case 705: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2481 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 706: // sender_port: "sender-port" ":" "integer"
#line 2487 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 707: // max_queue_size: "max-queue-size" ":" "integer"
#line 2493 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 708: // $@119: %empty
#line 2499 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3843 "dhcp6_parser.cc"
    break;

  case 709: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2502 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3852 "dhcp6_parser.cc"
    break;

  case 710: // ncr_protocol_value: "UDP"
#line 2508 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3858 "dhcp6_parser.cc"
    break;

  case 711: // ncr_protocol_value: "TCP"
#line 2509 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3864 "dhcp6_parser.cc"
    break;

  case 712: // $@120: %empty
#line 2512 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 713: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2515 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 714: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2522 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3893 "dhcp6_parser.cc"
    break;

  case 715: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2529 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3903 "dhcp6_parser.cc"
    break;

  case 716: // $@121: %empty
#line 2536 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3912 "dhcp6_parser.cc"
    break;

  case 717: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2539 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3921 "dhcp6_parser.cc"
    break;

  case 718: // $@122: %empty
#line 2545 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3930 "dhcp6_parser.cc"
    break;

  case 719: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2548 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3940 "dhcp6_parser.cc"
    break;

  case 720: // $@123: %empty
#line 2555 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3949 "dhcp6_parser.cc"
    break;

  case 721: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2558 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3959 "dhcp6_parser.cc"
    break;

  case 722: // $@124: %empty
#line 2565 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3968 "dhcp6_parser.cc"
    break;

  case 723: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2568 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3978 "dhcp6_parser.cc"
    break;

  case 724: // $@125: %empty
#line 2577 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3990 "dhcp6_parser.cc"
    break;

  case 725: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2583 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 726: // $@126: %empty
#line 2589 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4010 "dhcp6_parser.cc"
    break;

  case 727: // sub_config_control: "{" $@126 config_control_params "}"
#line 2593 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4019 "dhcp6_parser.cc"
    break;

  case 732: // $@127: %empty
#line 2608 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 733: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2614 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4040 "dhcp6_parser.cc"
    break;

  case 734: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2619 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 735: // $@128: %empty
#line 2627 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4062 "dhcp6_parser.cc"
    break;

  case 736: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2633 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 739: // $@129: %empty
#line 2645 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 740: // logger_entry: "{" $@129 logger_params "}"
#line 2649 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4089 "dhcp6_parser.cc"
    break;

  case 750: // debuglevel: "debuglevel" ":" "integer"
#line 2666 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4099 "dhcp6_parser.cc"
    break;

  case 751: // $@130: %empty
#line 2672 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4108 "dhcp6_parser.cc"
    break;

  case 752: // severity: "severity" $@130 ":" "constant string"
#line 2675 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 753: // $@131: %empty
#line 2681 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4130 "dhcp6_parser.cc"
    break;

  case 754: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2687 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4139 "dhcp6_parser.cc"
    break;

  case 757: // $@132: %empty
#line 2696 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4149 "dhcp6_parser.cc"
    break;

  case 758: // output_entry: "{" $@132 output_params_list "}"
#line 2700 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4157 "dhcp6_parser.cc"
    break;

  case 766: // $@133: %empty
#line 2715 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4166 "dhcp6_parser.cc"
    break;

  case 767: // output: "output" $@133 ":" "constant string"
#line 2718 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4176 "dhcp6_parser.cc"
    break;

  case 768: // flush: "flush" ":" "boolean"
#line 2724 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 769: // maxsize: "maxsize" ":" "integer"
#line 2730 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4196 "dhcp6_parser.cc"
    break;

  case 770: // maxver: "maxver" ":" "integer"
#line 2736 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4206 "dhcp6_parser.cc"
    break;

  case 771: // $@134: %empty
#line 2742 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4215 "dhcp6_parser.cc"
    break;

  case 772: // pattern: "pattern" $@134 ":" "constant string"
#line 2745 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4225 "dhcp6_parser.cc"
    break;


#line 4229 "dhcp6_parser.cc"

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
     503,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,    37,    34,    41,    74,    80,
      88,   118,   124,   140,   141,   142,   189,   216,   217,   230,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,    34,  -157,
     202,   115,    28,   513,   139,   187,   261,   -27,    65,    25,
     -75,   636,    55,  -941,   245,   236,    53,   244,   263,  -941,
     269,  -941,  -941,  -941,  -941,  -941,  -941,   265,   279,   280,
     286,   288,   305,   306,   341,   359,   361,   365,   368,   375,
     405,  -941,   406,   408,   409,   416,   418,  -941,  -941,  -941,
     421,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,   422,  -941,  -941,
    -941,  -941,  -941,  -941,   424,  -941,   425,  -941,    48,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,   428,  -941,   101,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   429,
     430,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,   104,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   129,
    -941,  -941,  -941,  -941,  -941,   431,  -941,   432,   434,  -941,
    -941,  -941,  -941,  -941,  -941,   137,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,   283,   304,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,   336,  -941,  -941,   436,  -941,  -941,  -941,
     444,  -941,  -941,   374,   446,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   448,   449,
    -941,  -941,  -941,  -941,   442,   451,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   138,  -941,
    -941,  -941,   452,  -941,  -941,   456,  -941,   464,   465,  -941,
    -941,   468,   469,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
     197,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   470,   205,
    -941,  -941,  -941,  -941,    34,    34,  -941,   258,   471,  -941,
     472,   473,   474,   476,   481,   483,   291,   292,   293,   294,
     297,   298,   299,   302,   308,   289,   311,   317,   309,   322,
     500,   323,   324,   325,   326,   330,   501,   502,   519,   331,
     520,   530,   531,   532,   533,   536,   537,   538,   539,   540,
     541,   543,   544,   545,   546,   547,   355,   548,   550,   551,
     552,   566,   567,   372,   569,  -941,   115,  -941,   577,   382,
      28,  -941,   580,   581,   582,   583,   584,   391,   392,   586,
     587,   590,   513,  -941,   592,   139,  -941,   594,   401,   605,
     412,   413,   187,  -941,   608,   609,   610,   611,   613,   614,
     615,  -941,   261,  -941,   617,   618,   427,   622,   623,   624,
     438,  -941,    65,   625,   439,   440,  -941,    25,   626,   628,
     -62,  -941,   441,   632,   638,   445,   640,   447,   450,   642,
     643,   454,   455,   652,   653,   654,   655,   636,  -941,   656,
     463,    55,  -941,  -941,  -941,   658,   657,   477,   659,   660,
     661,   662,   665,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,   478,  -941,  -941,
    -941,  -941,  -941,  -106,   479,   480,  -941,   666,   668,   673,
     672,   484,   307,   675,   677,   678,   695,   694,   697,   698,
     699,   719,   720,  -941,   729,   732,   733,   734,   549,   553,
    -941,   737,  -941,   738,  -941,  -941,   739,   740,   554,   555,
     556,  -941,  -941,   738,   557,   741,  -941,   560,  -941,   563,
    -941,   568,  -941,  -941,  -941,   738,   738,   738,   570,   571,
     572,   573,  -941,   574,   575,  -941,   576,   578,   579,  -941,
    -941,   585,  -941,  -941,  -941,   589,   672,  -941,  -941,   603,
     604,  -941,   606,  -941,  -941,   -54,   499,  -941,  -941,  -106,
     607,   612,   616,  -941,   742,  -941,  -941,    34,   115,  -941,
      55,    28,   287,   287,   756,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,   757,   759,   771,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,   772,   -76,    34,    72,   644,
     773,   774,   776,    66,   167,   211,    62,   190,   636,  -941,
    -941,   777,  -941,  -941,   795,   798,  -941,  -941,  -941,  -941,
    -941,   -41,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,   756,  -941,   233,   277,   290,  -941,  -941,  -941,  -941,
     802,   806,   807,   808,   810,  -941,   811,   812,  -941,  -941,
    -941,   813,   814,   815,   816,  -941,   303,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   332,  -941,
     817,   818,  -941,  -941,   819,   821,  -941,  -941,   820,   824,
    -941,  -941,   822,   826,  -941,  -941,   825,   827,  -941,  -941,
    -941,    82,  -941,  -941,  -941,   828,  -941,  -941,  -941,   195,
    -941,  -941,  -941,  -941,   338,  -941,  -941,  -941,   196,  -941,
    -941,   829,   833,  -941,  -941,   831,   837,  -941,   838,   839,
     840,   841,   842,   843,   339,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,   844,   845,   846,  -941,  -941,  -941,
    -941,   340,  -941,  -941,  -941,  -941,  -941,  -941,   847,   848,
     849,  -941,   351,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,   352,  -941,  -941,  -941,   850,  -941,
     851,  -941,  -941,  -941,   354,  -941,  -941,  -941,  -941,  -941,
     358,  -941,   208,  -941,   635,  -941,   835,   853,  -941,  -941,
     852,   854,  -941,  -941,  -941,   855,  -941,   856,  -941,  -941,
    -941,   857,   861,   862,   863,   670,   669,   674,   671,   676,
     866,   679,   680,   869,   871,   872,   681,   682,   683,   684,
     287,  -941,  -941,   287,  -941,   756,   513,  -941,   757,    65,
    -941,   759,    25,  -941,   771,   667,  -941,   772,   -76,  -941,
    -941,    72,  -941,   877,   644,  -941,   159,   773,  -941,   261,
    -941,   774,   -75,  -941,   776,   686,   688,   689,   692,   701,
     702,    66,  -941,   888,   889,   704,   705,   711,   167,  -941,
     714,   722,   725,   211,  -941,   891,   926,    62,  -941,   731,
     930,   751,   935,   190,  -941,  -941,   193,   777,  -941,  -941,
     934,   953,   139,  -941,   795,   187,  -941,   798,   955,  -941,
    -941,   394,   663,   768,   778,  -941,  -941,  -941,  -941,  -941,
     779,  -941,  -941,   781,   782,   786,  -941,  -941,  -941,  -941,
    -941,   377,  -941,   378,  -941,   960,  -941,   963,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
     380,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   787,
    -941,  -941,   983,  -941,  -941,  -941,  -941,  -941,   982,   989,
    -941,  -941,  -941,  -941,  -941,   997,  -941,   386,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,   201,   823,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,   830,   832,  -941,  -941,
     836,  -941,    34,  -941,  -941,  1005,  -941,  -941,  -941,  -941,
    -941,   388,  -941,  -941,  -941,  -941,  -941,  -941,   858,   389,
    -941,   390,  -941,   859,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
     667,  -941,  -941,  1009,   860,  -941,   159,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  1014,   834,
    1017,   193,  -941,  -941,  -941,  -941,  -941,  -941,   864,  -941,
    -941,  1019,  -941,   865,  -941,  -941,  1015,  -941,  -941,   257,
    -941,   -24,  1015,  -941,  -941,  1021,  1024,  1026,  -941,   399,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  1031,   867,   868,
     870,  1032,   -24,  -941,   873,  -941,  -941,  -941,   874,  -941,
    -941,  -941
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   164,     9,   326,    11,
     508,    13,   533,    15,   563,    17,   433,    19,   441,    21,
     478,    23,   291,    25,   676,    27,   726,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   565,     0,   443,   480,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   122,   724,   162,   176,   178,   180,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,     0,     0,     0,     0,     0,   141,   148,   150,
       0,   318,   431,   470,   521,   523,   378,   386,   251,   268,
     259,   244,   600,   555,   283,   302,   621,     0,   270,   645,
     658,   674,   152,   154,     0,   735,     0,   121,     0,    64,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   102,
     103,   104,   105,   106,    75,   110,   111,   112,   113,   114,
     115,   108,   109,   116,   117,   118,   100,   120,    78,    79,
      80,    81,    97,    82,    84,    83,   119,    88,    89,    76,
     101,    77,    86,    87,    95,    96,    98,    85,    90,    91,
      92,    93,    94,    99,   107,   173,     0,   172,     0,   166,
     168,   169,   170,   171,   500,   525,   368,   370,   372,     0,
       0,   376,   374,   594,   367,   330,   331,   332,   333,   334,
     335,   336,   337,   353,   354,   355,   356,   357,   360,   361,
     362,   363,   364,   365,   358,   359,   366,     0,   328,   341,
     342,   343,   346,   347,   349,   344,   345,   338,   339,   351,
     352,   340,   348,   350,   519,   518,   514,   515,   513,     0,
     510,   512,   516,   517,   548,     0,   551,     0,     0,   547,
     541,   542,   540,   545,   546,     0,   535,   537,   538,   543,
     544,   539,   592,   580,   582,   584,   586,   588,   590,   579,
     576,   577,   578,     0,   566,   567,   571,   572,   569,   573,
     574,   575,   570,     0,   460,   224,     0,   464,   462,   467,
       0,   456,   457,     0,   444,   445,   447,   459,   448,   449,
     450,   466,   451,   452,   453,   454,   455,   494,     0,     0,
     492,   493,   496,   497,     0,   481,   482,   484,   485,   486,
     487,   488,   489,   490,   491,   298,   300,   295,     0,   293,
     296,   297,     0,   699,   701,     0,   704,     0,     0,   708,
     712,     0,     0,   716,   718,   720,   722,   697,   695,   696,
       0,   678,   680,   692,   681,   682,   683,   684,   685,   686,
     687,   688,   689,   690,   691,   693,   694,   732,     0,     0,
     728,   730,   731,    46,     0,     0,    39,     0,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    57,     0,    63,     0,     0,
       0,   165,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   327,     0,     0,   509,     0,     0,     0,
       0,     0,     0,   534,     0,     0,     0,     0,     0,     0,
       0,   564,     0,   434,     0,     0,     0,     0,     0,     0,
       0,   442,     0,     0,     0,     0,   479,     0,     0,     0,
       0,   292,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   677,     0,
       0,     0,   727,    50,    43,     0,     0,     0,     0,     0,
       0,     0,     0,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,     0,   157,   158,
     138,   139,   140,     0,     0,     0,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   644,     0,     0,     0,     0,     0,     0,
     161,     0,    65,     0,   175,   167,     0,     0,     0,     0,
       0,   384,   385,     0,     0,     0,   329,     0,   511,     0,
     550,     0,   553,   554,   536,     0,     0,     0,     0,     0,
       0,     0,   568,     0,     0,   458,     0,     0,     0,   469,
     446,     0,   498,   499,   483,     0,     0,   294,   698,     0,
       0,   703,     0,   706,   707,     0,     0,   714,   715,     0,
       0,     0,     0,   679,     0,   734,   729,     0,     0,   123,
       0,     0,     0,     0,   182,   160,   143,   144,   145,   146,
     147,   142,   149,   151,   320,   435,   472,    40,   522,   524,
     380,   381,   382,   383,   379,   388,     0,    47,     0,     0,
       0,   557,   285,     0,     0,     0,     0,     0,     0,   153,
     155,     0,    51,   174,   502,   527,   369,   371,   373,   377,
     375,     0,   520,   549,   552,   593,   581,   583,   585,   587,
     589,   591,   461,   225,   465,   463,   468,   495,   299,   301,
     700,   702,   705,   710,   711,   709,   713,   717,   719,   721,
     723,   182,    44,     0,     0,     0,   211,   217,   219,   221,
       0,     0,     0,     0,     0,   235,     0,     0,   238,   240,
     242,     0,     0,     0,     0,   210,     0,   188,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   202,   209,
     203,   204,   205,   200,   201,   206,   207,   208,     0,   186,
       0,   183,   184,   324,     0,   321,   322,   439,     0,   436,
     437,   476,     0,   473,   474,   392,     0,   389,   390,   257,
     258,     0,   253,   255,   256,     0,   266,   267,   263,     0,
     261,   264,   265,   249,     0,   246,   248,   604,     0,   602,
     561,     0,   558,   559,   289,     0,   286,   287,     0,     0,
       0,     0,     0,     0,     0,   304,   306,   307,   308,   309,
     310,   311,   634,   640,     0,     0,     0,   633,   630,   631,
     632,     0,   623,   625,   628,   626,   627,   629,     0,     0,
       0,   279,     0,   272,   274,   275,   276,   277,   278,   654,
     656,   653,   651,   652,     0,   647,   649,   650,     0,   669,
       0,   672,   665,   666,     0,   660,   662,   663,   664,   667,
       0,   739,     0,   737,    53,   506,     0,   503,   504,   531,
       0,   528,   529,   598,   597,     0,   596,     0,    61,   725,
     163,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   177,   179,     0,   181,     0,     0,   319,     0,   443,
     432,     0,   480,   471,     0,     0,   387,     0,     0,   252,
     269,     0,   260,     0,     0,   245,   606,     0,   601,   565,
     556,     0,     0,   284,     0,     0,     0,     0,     0,     0,
       0,     0,   303,     0,     0,     0,     0,     0,     0,   622,
       0,     0,     0,     0,   271,     0,     0,     0,   646,     0,
       0,     0,     0,     0,   659,   675,     0,     0,   736,    55,
       0,    54,     0,   501,     0,     0,   526,     0,     0,   595,
     733,     0,     0,     0,     0,   223,   226,   227,   228,   229,
       0,   237,   230,     0,     0,     0,   232,   233,   234,   231,
     189,     0,   185,     0,   323,     0,   438,     0,   475,   430,
     407,   408,   409,   411,   412,   413,   400,   401,   416,   417,
     418,   419,   420,   423,   424,   425,   426,   427,   428,   421,
     422,   429,   396,   397,   398,   399,   405,   406,   404,   410,
       0,   394,   402,   414,   415,   403,   391,   254,   262,     0,
     247,   618,     0,   616,   617,   613,   614,   615,     0,   607,
     608,   610,   611,   612,   603,     0,   560,     0,   288,   312,
     313,   314,   315,   316,   317,   305,     0,     0,   639,   642,
     643,   624,   280,   281,   282,   273,     0,     0,   648,   668,
       0,   671,     0,   661,   753,     0,   751,   749,   743,   747,
     748,     0,   741,   745,   746,   744,   738,    52,     0,     0,
     505,     0,   530,     0,   213,   214,   215,   216,   212,   218,
     220,   222,   236,   239,   241,   243,   187,   325,   440,   477,
       0,   393,   250,     0,     0,   605,     0,   562,   290,   636,
     637,   638,   635,   641,   655,   657,   670,   673,     0,     0,
       0,     0,   740,    56,   507,   532,   599,   395,     0,   620,
     609,     0,   750,     0,   742,   619,     0,   752,   757,     0,
     755,     0,     0,   754,   766,     0,     0,     0,   771,     0,
     759,   761,   762,   763,   764,   765,   756,     0,     0,     0,
       0,     0,     0,   758,     0,   768,   769,   770,     0,   760,
     767,   772
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,    -4,  -941,  -531,  -941,
     176,  -941,  -941,  -941,  -941,   162,  -941,  -560,  -941,  -941,
    -941,   -71,  -941,  -941,  -941,  -941,  -941,  -941,   369,   588,
    -941,  -941,   -59,   -43,   -40,   -39,   -37,   -23,   -21,   -19,
     -18,   -15,    -3,    -1,    16,  -941,    29,    30,    32,    33,
    -941,   379,    35,  -941,    45,  -941,    46,  -941,    47,  -941,
      50,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
     370,   593,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,   295,  -941,    85,  -941,  -657,    93,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,   -47,  -941,  -693,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
      70,  -941,  -941,  -941,  -941,  -941,    77,  -676,  -941,  -941,
    -941,  -941,    76,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
      49,  -941,  -941,  -941,  -941,  -941,  -941,  -941,    64,  -941,
    -941,  -941,    67,   558,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,    59,  -941,  -941,  -941,  -941,  -941,  -941,  -940,  -941,
    -941,  -941,    95,  -941,  -941,  -941,   102,   591,  -941,  -941,
    -938,  -941,  -937,  -941,     9,  -941,    54,  -941,    51,  -941,
    -941,  -941,  -936,  -941,  -941,  -941,  -941,    84,  -941,  -941,
    -123,   987,  -941,  -941,  -941,  -941,  -941,    98,  -941,  -941,
    -941,   106,  -941,   562,  -941,   -73,  -941,  -941,  -941,  -941,
    -941,   -66,  -941,  -941,  -941,  -941,  -941,    17,  -941,  -941,
    -941,   105,  -941,  -941,  -941,   110,  -941,   564,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,    56,
    -941,  -941,  -941,    60,   598,  -941,  -941,   -55,  -941,     1,
    -941,  -941,  -941,  -941,  -941,    57,  -941,  -941,  -941,    52,
     595,  -941,  -941,  -941,  -941,  -941,  -941,  -941,   -58,  -941,
    -941,  -941,    94,  -941,  -941,  -941,   107,  -941,   596,   364,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -930,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,   111,  -941,  -941,  -941,   -97,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,    92,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,    86,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,    78,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,   384,   559,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,  -941,
    -941,  -941,  -941,  -941,  -941,  -941,   433,   561,  -941,  -941,
    -941,  -941,  -941,  -941,    83,  -941,  -941,  -107,  -941,  -941,
    -941,  -941,  -941,  -941,  -127,  -941,  -941,  -145,  -941,  -941,
    -941,  -941,  -941,  -941,  -941
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     688,    87,    88,    41,    68,    84,    85,   713,   914,  1020,
    1021,   775,    43,    70,    90,   408,    45,    71,   148,   149,
     150,   410,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     436,   681,   169,   437,   170,   438,   171,   461,   172,   462,
     173,   174,   175,   176,   430,   177,   178,   412,    47,    72,
     208,   209,   210,   468,   211,   179,   413,   180,   414,   181,
     415,   800,   801,   802,   953,   776,   777,   778,   931,  1168,
     779,   932,   780,   933,   781,   934,   782,   783,   505,   784,
     785,   786,   787,   788,   789,   790,   791,   792,   793,   940,
     794,   795,   943,   796,   944,   797,   945,   182,   450,   834,
     835,   836,   973,   183,   447,   821,   822,   823,   824,   184,
     449,   829,   830,   831,   832,   185,   448,   186,   457,   882,
     883,   884,   885,   886,   187,   453,   845,   846,   847,   982,
      63,    80,   358,   359,   360,   518,   361,   519,   188,   454,
     854,   855,   856,   857,   858,   859,   860,   861,   189,   440,
     804,   805,   806,   956,    49,    73,   247,   248,   249,   474,
     250,   475,   251,   476,   252,   480,   253,   479,   190,   445,
     694,   255,   256,   191,   446,   816,   817,   818,   965,  1090,
    1091,   192,   441,    57,    77,   808,   809,   810,   959,    59,
      78,   323,   324,   325,   326,   327,   328,   329,   504,   330,
     508,   331,   507,   332,   333,   509,   334,   193,   442,   812,
     813,   814,   962,    61,    79,   344,   345,   346,   347,   348,
     513,   349,   350,   351,   352,   258,   472,   916,   917,   918,
    1022,    51,    74,   269,   270,   271,   484,   194,   443,   195,
     444,   261,   473,   920,   921,   922,  1025,    53,    75,   285,
     286,   287,   487,   288,   289,   489,   290,   291,   196,   452,
     841,   842,   843,   979,    55,    76,   303,   304,   305,   306,
     495,   307,   496,   308,   497,   309,   498,   310,   499,   311,
     500,   312,   494,   263,   481,   925,   926,  1028,   197,   451,
     838,   839,   976,  1108,  1109,  1110,  1111,  1112,  1183,  1113,
     198,   455,   871,   872,   873,   993,  1192,   874,   875,   994,
     876,   877,   199,   200,   458,   894,   895,   896,  1005,   897,
    1006,   201,   459,   904,   905,   906,   907,  1010,   908,   909,
    1012,   202,   460,    65,    81,   380,   381,   382,   383,   523,
     384,   524,   385,   386,   526,   387,   388,   389,   529,   745,
     390,   530,   391,   392,   393,   533,   394,   534,   395,   535,
     396,   536,   203,   411,    67,    82,   399,   400,   401,   539,
     402,   204,   464,   912,   913,  1016,  1151,  1152,  1153,  1154,
    1200,  1155,  1198,  1219,  1220,  1221,  1229,  1230,  1231,  1237,
    1232,  1233,  1234,  1235,  1241
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     147,   207,   224,   265,   279,   299,   342,   321,   340,   357,
     377,   868,    38,   343,   225,   262,   798,   212,   259,   272,
     283,   301,   828,   335,   353,  1083,   378,  1084,  1085,  1089,
     226,   322,   341,   227,   228,  1095,   229,    30,   819,    31,
      86,    32,   122,    33,   205,   206,   355,   356,    42,   687,
     230,   466,   231,   719,   232,   233,   467,   405,   234,   355,
     356,   676,   677,   678,   679,   725,   726,   727,   397,   398,
     235,   293,   236,   213,   260,   273,   284,   302,   923,   336,
     354,    44,   379,   266,   280,   968,   314,    46,   969,   237,
     257,   268,   282,   300,   680,    48,   315,   337,   316,   317,
     338,   339,   238,   239,   470,   240,   241,   482,   242,   471,
     743,   744,   483,   124,   125,   687,   124,   125,   243,   244,
     245,   820,   146,   246,   254,    50,    91,    92,   267,   281,
      93,    52,   485,    94,    95,    96,   315,   486,   316,   317,
     492,   520,   318,   319,   320,   493,   521,    54,    56,    58,
     124,   125,  1224,   124,   125,  1225,  1226,  1227,  1228,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   819,   826,   862,   827,
     848,   849,   850,   851,   852,   853,    60,   761,   971,   977,
     537,   972,   978,   124,   125,   538,   889,   890,   541,   123,
     126,  1017,    89,   542,  1018,   127,   128,   129,   130,   131,
     264,   132,   146,    62,    64,   146,   133,   124,   125,   123,
     315,    34,    35,    36,    37,   134,   466,    66,   135,   404,
    1083,   928,  1084,  1085,  1089,   136,   221,   124,   125,   222,
    1095,   403,   406,   137,   138,   124,   125,   123,   139,   146,
    1222,   140,   146,  1223,   315,   141,   407,  1101,  1102,   416,
     274,   275,   276,   277,   278,   124,   125,   409,   124,   125,
     541,   124,   125,   417,   418,   929,   142,   143,   144,   145,
     419,   501,   420,   470,   221,   828,  1051,   222,   930,   124,
     125,   863,   864,   865,   866,   868,   950,   502,   756,   421,
     422,   951,   146,   757,   758,   759,   760,   761,   762,   763,
     764,   765,   766,   767,   768,   769,   770,   771,   772,   773,
     774,   123,  1189,  1190,  1191,   950,   146,   898,   899,   900,
     952,   974,   991,   998,   503,   423,   975,   992,   999,   124,
     125,   878,   879,   880,  1003,  1007,   146,  1013,   315,  1004,
    1008,   537,  1014,   424,   146,   425,  1015,   292,  1144,   426,
    1145,  1146,   427,   293,   294,   295,   296,   297,   298,   428,
     950,   482,   511,  1180,   146,  1176,  1177,   901,  1181,   520,
     146,  1201,   485,   492,  1188,   147,  1202,  1204,  1205,   207,
     543,   544,  1242,   690,   691,   692,   693,  1243,   146,   429,
     431,   224,   432,   433,   265,   212,  1164,  1165,  1166,  1167,
     434,   279,   435,   225,   262,   439,   456,   259,   463,   465,
     272,   299,   469,   477,   478,   488,   490,   283,   491,   226,
     506,   321,   227,   228,   342,   229,   340,   301,   510,   512,
     516,   343,   514,   515,   517,   545,   522,   335,   146,   230,
     525,   231,   353,   232,   233,   322,   377,   234,   527,   528,
     341,   213,   531,   532,   540,   546,   547,   548,   549,   235,
     550,   236,   378,   260,   146,   551,   273,   552,   562,   553,
     554,   555,   556,   284,   266,   557,   558,   559,   237,   257,
     560,   280,   268,   302,   567,   573,   574,   565,   561,   282,
     563,   238,   239,   336,   240,   241,   564,   242,   354,   300,
     566,   568,   569,   575,   577,   570,   571,   243,   244,   245,
     572,   576,   246,   254,   578,   579,   580,   581,   379,   267,
     582,   583,   584,   585,   586,   587,   281,   588,   589,   590,
     591,   592,   594,   593,   595,   596,   597,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     598,   599,   600,   601,   114,   115,   116,   117,   118,   119,
     120,   603,   604,   123,   606,   607,   608,   609,   610,   611,
     613,   614,   612,   214,   615,   215,   617,   147,   619,   620,
     207,   124,   125,   216,   217,   218,   219,   220,   126,   621,
     622,   623,   625,   626,   627,   628,   212,   629,   630,   631,
     221,   633,   634,   222,   133,   635,   636,   637,   638,   641,
     645,   223,   646,   867,   881,   891,   649,   377,   639,   642,
     643,   648,   650,   651,   652,   653,   655,   656,   654,   869,
     887,   892,   902,   378,   657,   658,   659,   660,   661,   662,
     664,   665,   667,   752,   668,   746,   670,   671,   672,   673,
     674,   684,   213,   685,   669,   675,   682,   683,   686,    32,
     695,   689,   696,   697,   142,   143,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
     698,   699,   700,   701,   702,   870,   888,   893,   903,   379,
     146,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   124,   125,   703,   704,   114,   115,
     116,   117,   118,   119,   120,   121,   705,   123,   315,   706,
     707,   708,   711,   712,   714,   715,   709,   751,   721,   833,
     710,   716,   717,   718,   720,   124,   125,   722,   217,   218,
     723,   220,   126,   799,   803,   724,   807,   728,   729,   730,
     731,   732,   733,   734,   221,   735,   736,   222,   811,   815,
     837,   840,   737,   844,   911,   223,   738,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     740,   741,   915,   742,   748,   919,   935,   375,   376,   749,
     936,   937,   938,   750,   939,   941,   942,   946,   947,   948,
     949,   955,   739,   954,   958,   957,   960,   961,   963,   964,
     967,   966,  1019,   146,   970,   980,   981,   983,   142,   143,
     984,  1023,   985,   986,   987,   988,   989,   990,   995,   996,
     997,  1000,  1001,  1002,  1009,  1011,  1024,  1027,  1026,   825,
    1169,  1031,  1030,  1029,   146,  1032,  1033,  1034,  1035,  1036,
    1040,  1038,  1037,  1043,  1039,  1044,  1045,  1041,  1042,  1046,
    1047,  1099,  1049,  1048,  1119,   224,  1120,  1121,   321,   342,
    1122,   340,  1126,  1127,  1059,  1136,   343,   225,   262,  1123,
    1124,   259,  1128,  1129,   335,  1103,  1060,   353,   299,  1130,
    1093,   357,   322,   226,  1132,   341,   227,   228,  1082,   229,
    1133,  1106,  1061,  1134,   301,  1062,  1063,   867,  1064,  1104,
    1137,  1139,   881,   230,  1140,   231,   891,   232,   233,  1142,
    1157,   234,  1065,   869,  1066,  1147,  1067,  1068,   887,  1141,
    1069,   265,   892,   235,   279,   236,  1158,   260,   902,  1163,
     336,  1149,  1070,   354,  1071,  1170,  1094,   272,  1178,  1148,
     283,  1179,   237,   257,  1086,  1171,  1172,  1107,  1173,  1174,
     302,  1072,  1092,  1175,  1182,   238,   239,  1184,   240,   241,
    1185,   242,  1186,  1105,  1073,  1074,   300,  1075,  1076,   870,
    1077,   243,   244,   245,   888,  1187,   246,   254,   893,  1199,
    1078,  1079,  1080,  1208,   903,  1081,  1088,  1150,  1211,  1087,
    1193,  1213,  1218,   273,  1216,  1238,   284,  1194,  1239,  1195,
    1240,   266,  1212,  1196,   280,  1244,  1248,   753,   747,   268,
    1052,   755,   282,  1050,  1100,  1097,   927,  1098,  1118,  1117,
    1125,  1096,  1135,  1054,   602,  1203,  1206,  1207,  1053,  1056,
    1209,  1215,  1217,   605,   313,  1055,  1246,  1245,  1247,  1058,
    1250,  1251,  1057,   616,   640,  1116,   267,  1161,   647,   281,
    1160,   644,  1159,   618,  1162,   924,  1115,   624,  1114,  1210,
    1131,  1143,   910,  1138,  1214,  1236,   663,  1249,   632,     0,
    1156,     0,   666,   754,     0,     0,     0,     0,     0,  1059,
       0,     0,     0,     0,     0,  1103,     0,     0,     0,     0,
       0,  1060,     0,     0,     0,  1093,     0,     0,     0,     0,
    1147,  1106,     0,  1082,     0,     0,     0,  1061,  1197,  1104,
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
      73,    78,    79,    73,    73,   965,    73,     0,   114,     5,
     197,     7,    69,     9,    16,    17,   121,   122,     7,   580,
      73,     3,    73,   613,    73,    73,     8,     4,    73,   121,
     122,   167,   168,   169,   170,   625,   626,   627,    13,    14,
      73,   112,    73,    72,    73,    74,    75,    76,   119,    78,
      79,     7,    81,    74,    75,     3,    21,     7,     6,    73,
      73,    74,    75,    76,   200,     7,    71,    72,    73,    74,
      75,    76,    73,    73,     3,    73,    73,     3,    73,     8,
     164,   165,     8,    88,    89,   646,    88,    89,    73,    73,
      73,   197,   197,    73,    73,     7,    11,    12,    74,    75,
      15,     7,     3,    18,    19,    20,    71,     8,    73,    74,
       3,     3,    77,    78,    79,     8,     8,     7,     7,     7,
      88,    89,   176,    88,    89,   179,   180,   181,   182,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,   114,   115,    21,   117,
     124,   125,   126,   127,   128,   129,     7,    30,     3,     3,
       3,     6,     6,    88,    89,     8,   144,   145,     3,    70,
      95,     3,    10,     8,     6,   100,   101,   102,   103,   104,
      81,   106,   197,     7,     7,   197,   111,    88,    89,    70,
      71,   197,   198,   199,   200,   120,     3,     7,   123,     3,
    1180,     8,  1180,  1180,  1180,   130,   107,    88,    89,   110,
    1180,     6,     8,   138,   139,    88,    89,    70,   143,   197,
       3,   146,   197,     6,    71,   150,     3,   108,   109,     4,
      83,    84,    85,    86,    87,    88,    89,     8,    88,    89,
       3,    88,    89,     4,     4,     8,   171,   172,   173,   174,
       4,     8,     4,     3,   107,   971,   953,   110,     8,    88,
      89,   134,   135,   136,   137,   998,     3,     3,    21,     4,
       4,     8,   197,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    70,   131,   132,   133,     3,   197,   147,   148,   149,
       8,     3,     3,     3,     8,     4,     8,     8,     8,    88,
      89,   140,   141,   142,     3,     3,   197,     3,    71,     8,
       8,     3,     8,     4,   197,     4,     8,   106,   175,     4,
     177,   178,     4,   112,   113,   114,   115,   116,   117,     4,
       3,     3,     8,     3,   197,     8,     8,   197,     8,     3,
     197,     3,     3,     3,     8,   466,     8,     8,     8,   470,
     404,   405,     3,    96,    97,    98,    99,     8,   197,     4,
       4,   482,     4,     4,   485,   470,    22,    23,    24,    25,
       4,   492,     4,   482,   482,     4,     4,   482,     4,     4,
     485,   502,     4,     4,     4,     4,     4,   492,     4,   482,
       4,   512,   482,   482,   517,   482,   517,   502,     4,     3,
       8,   517,     4,     4,     3,   197,     4,   512,   197,   482,
       4,   482,   517,   482,   482,   512,   537,   482,     4,     4,
     517,   470,     4,     4,     4,     4,     4,     4,     4,   482,
       4,   482,   537,   482,   197,     4,   485,     4,   199,   198,
     198,   198,   198,   492,   485,   198,   198,   198,   482,   482,
     198,   492,   485,   502,     4,     4,     4,   198,   200,   492,
     199,   482,   482,   512,   482,   482,   199,   482,   517,   502,
     198,   198,   198,     4,     4,   200,   200,   482,   482,   482,
     200,   200,   482,   482,     4,     4,     4,     4,   537,   485,
       4,     4,     4,     4,     4,     4,   492,     4,     4,     4,
       4,     4,     4,   198,     4,     4,     4,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
       4,     4,   200,     4,    61,    62,    63,    64,    65,    66,
      67,     4,   200,    70,     4,     4,     4,     4,     4,   198,
       4,     4,   200,    80,     4,    82,     4,   668,     4,   198,
     671,    88,    89,    90,    91,    92,    93,    94,    95,     4,
     198,   198,     4,     4,     4,     4,   671,     4,     4,     4,
     107,     4,     4,   110,   111,   198,     4,     4,     4,     4,
       4,   118,     4,   704,   705,   706,     4,   708,   200,   200,
     200,   200,     4,   198,     4,   198,     4,     4,   198,   704,
     705,   706,   707,   708,   200,   200,     4,     4,     4,     4,
       4,   198,     4,   667,     7,   166,     7,     7,     7,     7,
       5,     5,   671,     5,   197,   197,   197,   197,     5,     7,
       5,   197,     5,     5,   171,   172,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
       5,     7,     5,     5,     5,   704,   705,   706,   707,   708,
     197,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    88,    89,     7,     7,    61,    62,
      63,    64,    65,    66,    67,    68,     7,    70,    71,     7,
       7,     7,     5,     5,     5,     5,   197,     5,     7,   105,
     197,   197,   197,   197,   197,    88,    89,   197,    91,    92,
     197,    94,    95,     7,     7,   197,     7,   197,   197,   197,
     197,   197,   197,   197,   107,   197,   197,   110,     7,     7,
       7,     7,   197,     7,     7,   118,   197,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     197,   197,     7,   197,   197,     7,     4,   171,   172,   197,
       4,     4,     4,   197,     4,     4,     4,     4,     4,     4,
       4,     3,   646,     6,     3,     6,     6,     3,     6,     3,
       3,     6,   197,   197,     6,     6,     3,     6,   171,   172,
       3,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,     3,     6,   697,
     197,     4,     6,     8,   197,     4,     4,     4,   198,   200,
       4,   200,   198,     4,   198,     4,     4,   198,   198,   198,
     198,     4,   198,   200,   198,   956,   198,   198,   959,   962,
     198,   962,     4,     4,   965,     4,   962,   956,   956,   198,
     198,   956,   198,   198,   959,   976,   965,   962,   979,   198,
     965,   982,   959,   956,   200,   962,   956,   956,   965,   956,
     198,   976,   965,   198,   979,   965,   965,   998,   965,   976,
       4,   200,  1003,   956,     4,   956,  1007,   956,   956,     4,
       6,   956,   965,   998,   965,  1016,   965,   965,  1003,   198,
     965,  1022,  1007,   956,  1025,   956,     3,   956,  1013,     4,
     959,  1016,   965,   962,   965,   197,   965,  1022,     8,  1016,
    1025,     8,   956,   956,   965,   197,   197,   976,   197,   197,
     979,   965,   965,   197,   197,   956,   956,     4,   956,   956,
       8,   956,     3,   976,   965,   965,   979,   965,   965,   998,
     965,   956,   956,   956,  1003,     8,   956,   956,  1007,     4,
     965,   965,   965,     4,  1013,   965,   965,  1016,     4,   965,
     197,     4,     7,  1022,     5,     4,  1025,   197,     4,   197,
       4,  1022,   198,   197,  1025,     4,     4,   668,   659,  1022,
     955,   671,  1025,   950,   974,   968,   751,   971,   984,   982,
     991,   967,  1003,   958,   466,   197,   197,  1180,   956,   961,
     200,   197,   197,   470,    77,   959,   198,   200,   198,   964,
     197,   197,   962,   482,   512,   981,  1022,  1025,   520,  1025,
    1024,   517,  1022,   485,  1027,   721,   979,   492,   977,  1186,
     998,  1013,   708,  1007,  1201,  1222,   537,  1242,   502,    -1,
    1017,    -1,   541,   670,    -1,    -1,    -1,    -1,    -1,  1180,
      -1,    -1,    -1,    -1,    -1,  1186,    -1,    -1,    -1,    -1,
      -1,  1180,    -1,    -1,    -1,  1180,    -1,    -1,    -1,    -1,
    1201,  1186,    -1,  1180,    -1,    -1,    -1,  1180,  1142,  1186,
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
       0,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
       0,     5,     7,     9,   197,   198,   199,   200,   217,   218,
     219,   224,     7,   233,     7,   237,     7,   279,     7,   385,
       7,   462,     7,   478,     7,   495,     7,   414,     7,   420,
       7,   444,     7,   361,     7,   564,     7,   595,   225,   220,
     234,   238,   280,   386,   463,   479,   496,   415,   421,   445,
     362,   565,   596,   217,   226,   227,   197,   222,   223,    10,
     235,    11,    12,    15,    18,    19,    20,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    88,    89,    95,   100,   101,   102,
     103,   104,   106,   111,   120,   123,   130,   138,   139,   143,
     146,   150,   171,   172,   173,   174,   197,   232,   239,   240,
     241,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   263,
     265,   267,   269,   271,   272,   273,   274,   276,   277,   286,
     288,   290,   328,   334,   340,   346,   348,   355,   369,   379,
     399,   404,   412,   438,   468,   470,   489,   519,   531,   543,
     544,   552,   562,   593,   602,    16,    17,   232,   281,   282,
     283,   285,   468,   470,    80,    82,    90,    91,    92,    93,
      94,   107,   110,   118,   232,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   257,   258,
     259,   260,   263,   265,   267,   269,   271,   387,   388,   389,
     391,   393,   395,   397,   399,   402,   403,   438,   456,   468,
     470,   472,   489,   514,    81,   232,   395,   397,   438,   464,
     465,   466,   468,   470,    83,    84,    85,    86,    87,   232,
     395,   397,   438,   468,   470,   480,   481,   482,   484,   485,
     487,   488,   106,   112,   113,   114,   115,   116,   117,   232,
     438,   468,   470,   497,   498,   499,   500,   502,   504,   506,
     508,   510,   512,   412,    21,    71,    73,    74,    77,    78,
      79,   232,   308,   422,   423,   424,   425,   426,   427,   428,
     430,   432,   434,   435,   437,   468,   470,    72,    75,    76,
     232,   308,   426,   432,   446,   447,   448,   449,   450,   452,
     453,   454,   455,   468,   470,   121,   122,   232,   363,   364,
     365,   367,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   171,   172,   232,   468,   470,
     566,   567,   568,   569,   571,   573,   574,   576,   577,   578,
     581,   583,   584,   585,   587,   589,   591,    13,    14,   597,
     598,   599,   601,     6,     3,     4,     8,     3,   236,     8,
     242,   594,   278,   287,   289,   291,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     275,     4,     4,     4,     4,     4,   261,   264,   266,     4,
     380,   413,   439,   469,   471,   400,   405,   335,   347,   341,
     329,   520,   490,   356,   370,   532,     4,   349,   545,   553,
     563,   268,   270,     4,   603,     4,     3,     8,   284,     4,
       3,     8,   457,   473,   390,   392,   394,     4,     4,   398,
     396,   515,     3,     8,   467,     3,     8,   483,     4,   486,
       4,     4,     3,     8,   513,   501,   503,   505,   507,   509,
     511,     8,     3,     8,   429,   309,     4,   433,   431,   436,
       4,     8,     3,   451,     4,     4,     8,     3,   366,   368,
       3,     8,     4,   570,   572,     4,   575,     4,     4,   579,
     582,     4,     4,   586,   588,   590,   592,     3,     8,   600,
       4,     3,     8,   217,   217,   197,     4,     4,     4,     4,
       4,     4,     4,   198,   198,   198,   198,   198,   198,   198,
     198,   200,   199,   199,   199,   198,   198,     4,   198,   198,
     200,   200,   200,     4,     4,     4,   200,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   198,     4,     4,     4,     4,     4,     4,
     200,     4,   240,     4,   200,   282,     4,     4,     4,     4,
       4,   198,   200,     4,     4,     4,   388,     4,   465,     4,
     198,     4,   198,   198,   481,     4,     4,     4,     4,     4,
       4,     4,   499,     4,     4,   198,     4,     4,     4,   200,
     424,     4,   200,   200,   448,     4,     4,   364,   200,     4,
       4,   198,     4,   198,   198,     4,     4,   200,   200,     4,
       4,     4,     4,   567,     4,   198,   598,     4,     7,   197,
       7,     7,     7,     7,     5,   197,   167,   168,   169,   170,
     200,   262,   197,   197,     5,     5,     5,   219,   221,   197,
      96,    97,    98,    99,   401,     5,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     7,     7,   197,
     197,     5,     5,   228,     5,     5,   197,   197,   197,   228,
     197,     7,   197,   197,   197,   228,   228,   228,   197,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   221,
     197,   197,   197,   164,   165,   580,   166,   262,   197,   197,
     197,     5,   217,   239,   597,   281,    21,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,   232,   296,   297,   298,   301,
     303,   305,   307,   308,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   321,   322,   324,   326,   296,     7,
     292,   293,   294,     7,   381,   382,   383,     7,   416,   417,
     418,     7,   440,   441,   442,     7,   406,   407,   408,   114,
     197,   336,   337,   338,   339,   226,   115,   117,   338,   342,
     343,   344,   345,   105,   330,   331,   332,     7,   521,   522,
       7,   491,   492,   493,     7,   357,   358,   359,   124,   125,
     126,   127,   128,   129,   371,   372,   373,   374,   375,   376,
     377,   378,    21,   134,   135,   136,   137,   232,   310,   468,
     470,   533,   534,   535,   538,   539,   541,   542,   140,   141,
     142,   232,   350,   351,   352,   353,   354,   468,   470,   144,
     145,   232,   468,   470,   546,   547,   548,   550,   147,   148,
     149,   197,   468,   470,   554,   555,   556,   557,   559,   560,
     566,     7,   604,   605,   229,     7,   458,   459,   460,     7,
     474,   475,   476,   119,   500,   516,   517,   292,     8,     8,
       8,   299,   302,   304,   306,     4,     4,     4,     4,     4,
     320,     4,     4,   323,   325,   327,     4,     4,     4,     4,
       3,     8,     8,   295,     6,     3,   384,     6,     3,   419,
       6,     3,   443,     6,     3,   409,     6,     3,     3,     6,
       6,     3,     6,   333,     3,     8,   523,     3,     6,   494,
       6,     3,   360,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   536,   540,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   549,   551,     3,     8,     4,
     558,     4,   561,     3,     8,     8,   606,     3,     6,   197,
     230,   231,   461,     6,     3,   477,     6,     3,   518,     8,
       6,     4,     4,     4,     4,   198,   200,   198,   200,   198,
       4,   198,   198,     4,     4,     4,   198,   198,   200,   198,
     297,   296,   294,   387,   383,   422,   418,   446,   442,   232,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   257,   258,   259,   260,   263,   265,   267,
     269,   271,   308,   379,   391,   393,   395,   397,   399,   403,
     410,   411,   438,   468,   470,   514,   408,   337,   343,     4,
     331,   108,   109,   232,   308,   438,   468,   470,   524,   525,
     526,   527,   528,   530,   522,   497,   493,   363,   359,   198,
     198,   198,   198,   198,   198,   372,     4,     4,   198,   198,
     198,   534,   200,   198,   198,   351,     4,     4,   547,   200,
       4,   198,     4,   555,   175,   177,   178,   232,   308,   468,
     470,   607,   608,   609,   610,   612,   605,     6,     3,   464,
     460,   480,   476,     4,    22,    23,    24,    25,   300,   197,
     197,   197,   197,   197,   197,   197,     8,     8,     8,     8,
       3,     8,   197,   529,     4,     8,     3,     8,     8,   131,
     132,   133,   537,   197,   197,   197,   197,   217,   613,     4,
     611,     3,     8,   197,     8,     8,   197,   411,     4,   200,
     526,     4,   198,     4,   608,   197,     5,   197,     7,   614,
     615,   616,     3,     6,   176,   179,   180,   181,   182,   617,
     618,   619,   621,   622,   623,   624,   615,   620,     4,     4,
       4,   625,     3,     8,     4,   200,   198,   198,     4,   618,
     197,   197
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   201,   203,   202,   204,   202,   205,   202,   206,   202,
     207,   202,   208,   202,   209,   202,   210,   202,   211,   202,
     212,   202,   213,   202,   214,   202,   215,   202,   216,   202,
     217,   217,   217,   217,   217,   217,   217,   218,   220,   219,
     221,   222,   222,   223,   223,   225,   224,   226,   226,   227,
     227,   229,   228,   230,   230,   231,   231,   232,   234,   233,
     236,   235,   238,   237,   239,   239,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   242,   241,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   261,   260,   262,   262,   262,   262,   262,   264,   263,
     266,   265,   268,   267,   270,   269,   271,   272,   273,   275,
     274,   276,   278,   277,   280,   279,   281,   281,   282,   282,
     282,   282,   282,   284,   283,   285,   287,   286,   289,   288,
     291,   290,   292,   292,   293,   293,   295,   294,   296,   296,
     297,   297,   297,   297,   297,   297,   297,   297,   297,   297,
     297,   297,   297,   297,   297,   297,   297,   297,   297,   297,
     297,   299,   298,   300,   300,   300,   300,   302,   301,   304,
     303,   306,   305,   307,   309,   308,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   320,   319,   321,   323,   322,
     325,   324,   327,   326,   329,   328,   330,   330,   331,   333,
     332,   335,   334,   336,   336,   337,   337,   338,   339,   341,
     340,   342,   342,   343,   343,   343,   344,   345,   347,   346,
     349,   348,   350,   350,   351,   351,   351,   351,   351,   351,
     352,   353,   354,   356,   355,   357,   357,   358,   358,   360,
     359,   362,   361,   363,   363,   363,   364,   364,   366,   365,
     368,   367,   370,   369,   371,   371,   372,   372,   372,   372,
     372,   372,   373,   374,   375,   376,   377,   378,   380,   379,
     381,   381,   382,   382,   384,   383,   386,   385,   387,   387,
     388,   388,   388,   388,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   390,   389,
     392,   391,   394,   393,   396,   395,   398,   397,   400,   399,
     401,   401,   401,   401,   402,   403,   405,   404,   406,   406,
     407,   407,   409,   408,   410,   410,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   413,   412,   415,   414,   416,   416,   417,   417,   419,
     418,   421,   420,   422,   422,   423,   423,   424,   424,   424,
     424,   424,   424,   424,   424,   424,   424,   425,   426,   427,
     429,   428,   431,   430,   433,   432,   434,   436,   435,   437,
     439,   438,   440,   440,   441,   441,   443,   442,   445,   444,
     446,   446,   447,   447,   448,   448,   448,   448,   448,   448,
     448,   448,   448,   449,   451,   450,   452,   453,   454,   455,
     457,   456,   458,   458,   459,   459,   461,   460,   463,   462,
     464,   464,   465,   465,   465,   465,   465,   465,   465,   467,
     466,   469,   468,   471,   470,   473,   472,   474,   474,   475,
     475,   477,   476,   479,   478,   480,   480,   481,   481,   481,
     481,   481,   481,   481,   481,   481,   481,   481,   483,   482,
     484,   486,   485,   487,   488,   490,   489,   491,   491,   492,
     492,   494,   493,   496,   495,   497,   497,   498,   498,   499,
     499,   499,   499,   499,   499,   499,   499,   499,   499,   499,
     501,   500,   503,   502,   505,   504,   507,   506,   509,   508,
     511,   510,   513,   512,   515,   514,   516,   516,   518,   517,
     520,   519,   521,   521,   523,   522,   524,   524,   525,   525,
     526,   526,   526,   526,   526,   526,   526,   527,   529,   528,
     530,   532,   531,   533,   533,   534,   534,   534,   534,   534,
     534,   534,   534,   534,   536,   535,   537,   537,   537,   538,
     540,   539,   541,   542,   543,   545,   544,   546,   546,   547,
     547,   547,   547,   547,   549,   548,   551,   550,   553,   552,
     554,   554,   555,   555,   555,   555,   555,   555,   556,   558,
     557,   559,   561,   560,   563,   562,   565,   564,   566,   566,
     567,   567,   567,   567,   567,   567,   567,   567,   567,   567,
     567,   567,   567,   567,   567,   567,   567,   567,   568,   570,
     569,   572,   571,   573,   575,   574,   576,   577,   579,   578,
     580,   580,   582,   581,   583,   584,   586,   585,   588,   587,
     590,   589,   592,   591,   594,   593,   596,   595,   597,   597,
     598,   598,   600,   599,   601,   603,   602,   604,   604,   606,
     605,   607,   607,   608,   608,   608,   608,   608,   608,   608,
     609,   611,   610,   613,   612,   614,   614,   616,   615,   617,
     617,   618,   618,   618,   618,   618,   620,   619,   621,   622,
     623,   625,   624
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
       1,     1,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     0,
       4,     3,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     3,     0,     6,     0,     6,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
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
  "ddns_qualifying_suffix", "$@24", "hostname_char_set", "$@25",
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
  "reconnect_wait_time", "max_row_errors", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@40",
  "max_reconnect_tries", "keyspace", "$@41", "consistency", "$@42",
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
       0,   286,   286,   286,   287,   287,   288,   288,   289,   289,
     290,   290,   291,   291,   292,   292,   293,   293,   294,   294,
     295,   295,   296,   296,   297,   297,   298,   298,   299,   299,
     307,   308,   309,   310,   311,   312,   313,   316,   321,   321,
     332,   335,   336,   339,   344,   352,   352,   359,   360,   363,
     367,   374,   374,   381,   382,   385,   389,   400,   409,   409,
     424,   424,   441,   441,   450,   451,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   514,   514,   523,   529,   535,   541,   547,   553,
     559,   565,   571,   577,   583,   589,   595,   601,   607,   613,
     619,   625,   625,   634,   637,   640,   643,   646,   652,   652,
     661,   661,   670,   670,   679,   679,   688,   694,   700,   706,
     706,   715,   721,   721,   733,   733,   742,   743,   746,   747,
     748,   749,   750,   753,   753,   764,   770,   770,   783,   783,
     796,   796,   807,   808,   811,   812,   815,   815,   825,   826,
     829,   830,   831,   832,   833,   834,   835,   836,   837,   838,
     839,   840,   841,   842,   843,   844,   845,   846,   847,   848,
     849,   852,   852,   860,   861,   862,   863,   866,   866,   875,
     875,   884,   884,   893,   899,   899,   908,   914,   920,   926,
     932,   938,   944,   950,   956,   962,   962,   971,   977,   977,
     986,   986,   995,   995,  1004,  1004,  1015,  1016,  1018,  1020,
    1020,  1039,  1039,  1050,  1051,  1054,  1055,  1058,  1063,  1068,
    1068,  1079,  1080,  1083,  1084,  1085,  1088,  1093,  1100,  1100,
    1113,  1113,  1126,  1127,  1130,  1131,  1132,  1133,  1134,  1135,
    1138,  1144,  1150,  1156,  1156,  1167,  1168,  1171,  1172,  1175,
    1175,  1185,  1185,  1195,  1196,  1197,  1200,  1201,  1204,  1204,
    1213,  1213,  1222,  1222,  1234,  1235,  1238,  1239,  1240,  1241,
    1242,  1243,  1246,  1252,  1258,  1264,  1270,  1276,  1285,  1285,
    1299,  1300,  1303,  1304,  1311,  1311,  1337,  1337,  1348,  1349,
    1353,  1354,  1355,  1356,  1357,  1358,  1359,  1360,  1361,  1362,
    1363,  1364,  1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,
    1373,  1374,  1375,  1376,  1377,  1378,  1379,  1380,  1381,  1382,
    1383,  1384,  1385,  1386,  1387,  1388,  1389,  1390,  1393,  1393,
    1402,  1402,  1411,  1411,  1420,  1420,  1429,  1429,  1440,  1440,
    1448,  1449,  1450,  1451,  1454,  1460,  1468,  1468,  1480,  1481,
    1485,  1486,  1489,  1489,  1497,  1498,  1501,  1502,  1503,  1504,
    1505,  1506,  1507,  1508,  1509,  1510,  1511,  1512,  1513,  1514,
    1515,  1516,  1517,  1518,  1519,  1520,  1521,  1522,  1523,  1524,
    1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,
    1535,  1542,  1542,  1556,  1556,  1565,  1566,  1569,  1570,  1575,
    1575,  1590,  1590,  1604,  1605,  1608,  1609,  1612,  1613,  1614,
    1615,  1616,  1617,  1618,  1619,  1620,  1621,  1624,  1626,  1632,
    1634,  1634,  1643,  1643,  1652,  1652,  1661,  1663,  1663,  1672,
    1682,  1682,  1695,  1696,  1701,  1702,  1707,  1707,  1719,  1719,
    1731,  1732,  1737,  1738,  1743,  1744,  1745,  1746,  1747,  1748,
    1749,  1750,  1751,  1754,  1756,  1756,  1765,  1767,  1769,  1775,
    1784,  1784,  1797,  1798,  1801,  1802,  1805,  1805,  1815,  1815,
    1825,  1826,  1829,  1830,  1831,  1832,  1833,  1834,  1835,  1838,
    1838,  1847,  1847,  1872,  1872,  1902,  1902,  1915,  1916,  1919,
    1920,  1923,  1923,  1935,  1935,  1947,  1948,  1951,  1952,  1953,
    1954,  1955,  1956,  1957,  1958,  1959,  1960,  1961,  1964,  1964,
    1973,  1979,  1979,  1988,  1994,  2003,  2003,  2014,  2015,  2018,
    2019,  2022,  2022,  2031,  2031,  2040,  2041,  2044,  2045,  2049,
    2050,  2051,  2052,  2053,  2054,  2055,  2056,  2057,  2058,  2059,
    2062,  2062,  2073,  2073,  2084,  2084,  2093,  2093,  2102,  2102,
    2111,  2111,  2120,  2120,  2134,  2134,  2145,  2146,  2149,  2149,
    2161,  2161,  2172,  2173,  2176,  2176,  2186,  2187,  2190,  2191,
    2194,  2195,  2196,  2197,  2198,  2199,  2200,  2203,  2205,  2205,
    2214,  2223,  2223,  2236,  2237,  2240,  2241,  2242,  2243,  2244,
    2245,  2246,  2247,  2248,  2251,  2251,  2259,  2260,  2261,  2264,
    2270,  2270,  2279,  2285,  2293,  2301,  2301,  2312,  2313,  2316,
    2317,  2318,  2319,  2320,  2323,  2323,  2332,  2332,  2344,  2344,
    2357,  2358,  2361,  2362,  2363,  2364,  2365,  2366,  2369,  2375,
    2375,  2384,  2390,  2390,  2400,  2400,  2413,  2413,  2423,  2424,
    2427,  2428,  2429,  2430,  2431,  2432,  2433,  2434,  2435,  2436,
    2437,  2438,  2439,  2440,  2441,  2442,  2443,  2444,  2447,  2454,
    2454,  2463,  2463,  2472,  2478,  2478,  2487,  2493,  2499,  2499,
    2508,  2509,  2512,  2512,  2522,  2529,  2536,  2536,  2545,  2545,
    2555,  2555,  2565,  2565,  2577,  2577,  2589,  2589,  2599,  2600,
    2604,  2605,  2608,  2608,  2619,  2627,  2627,  2640,  2641,  2645,
    2645,  2653,  2654,  2657,  2658,  2659,  2660,  2661,  2662,  2663,
    2666,  2672,  2672,  2681,  2681,  2692,  2693,  2696,  2696,  2704,
    2705,  2708,  2709,  2710,  2711,  2712,  2715,  2715,  2724,  2730,
    2736,  2742,  2742
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
#line 5786 "dhcp6_parser.cc"

#line 2751 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
