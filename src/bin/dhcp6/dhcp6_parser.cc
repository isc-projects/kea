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

  case 152: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 670 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1361 "dhcp6_parser.cc"
    break;

  case 153: // $@25: %empty
#line 676 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1370 "dhcp6_parser.cc"
    break;

  case 154: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 679 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1380 "dhcp6_parser.cc"
    break;

  case 155: // $@26: %empty
#line 685 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 156: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 688 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 157: // store_extended_info: "store-extended-info" ":" "boolean"
#line 694 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1409 "dhcp6_parser.cc"
    break;

  case 158: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 700 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 159: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 706 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1429 "dhcp6_parser.cc"
    break;

  case 160: // $@27: %empty
#line 712 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1438 "dhcp6_parser.cc"
    break;

  case 161: // server_tag: "server-tag" $@27 ":" "constant string"
#line 715 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
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

  case 369: // $@59: %empty
#line 1394 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2379 "dhcp6_parser.cc"
    break;

  case 370: // subnet: "subnet" $@59 ":" "constant string"
#line 1397 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2389 "dhcp6_parser.cc"
    break;

  case 371: // $@60: %empty
#line 1403 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2398 "dhcp6_parser.cc"
    break;

  case 372: // interface: "interface" $@60 ":" "constant string"
#line 1406 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2408 "dhcp6_parser.cc"
    break;

  case 373: // $@61: %empty
#line 1412 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2417 "dhcp6_parser.cc"
    break;

  case 374: // interface_id: "interface-id" $@61 ":" "constant string"
#line 1415 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2427 "dhcp6_parser.cc"
    break;

  case 375: // $@62: %empty
#line 1421 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2436 "dhcp6_parser.cc"
    break;

  case 376: // client_class: "client-class" $@62 ":" "constant string"
#line 1424 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2446 "dhcp6_parser.cc"
    break;

  case 377: // $@63: %empty
#line 1430 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2458 "dhcp6_parser.cc"
    break;

  case 378: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1436 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2467 "dhcp6_parser.cc"
    break;

  case 379: // $@64: %empty
#line 1441 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2476 "dhcp6_parser.cc"
    break;

  case 380: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1444 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2485 "dhcp6_parser.cc"
    break;

  case 381: // hr_mode: "disabled"
#line 1449 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2491 "dhcp6_parser.cc"
    break;

  case 382: // hr_mode: "out-of-pool"
#line 1450 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2497 "dhcp6_parser.cc"
    break;

  case 383: // hr_mode: "global"
#line 1451 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2503 "dhcp6_parser.cc"
    break;

  case 384: // hr_mode: "all"
#line 1452 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2509 "dhcp6_parser.cc"
    break;

  case 385: // id: "id" ":" "integer"
#line 1455 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2519 "dhcp6_parser.cc"
    break;

  case 386: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1461 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2529 "dhcp6_parser.cc"
    break;

  case 387: // $@65: %empty
#line 1469 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2541 "dhcp6_parser.cc"
    break;

  case 388: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1475 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2550 "dhcp6_parser.cc"
    break;

  case 393: // $@66: %empty
#line 1490 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 394: // shared_network: "{" $@66 shared_network_params "}"
#line 1494 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2568 "dhcp6_parser.cc"
    break;

  case 433: // $@67: %empty
#line 1544 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2580 "dhcp6_parser.cc"
    break;

  case 434: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1550 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp6_parser.cc"
    break;

  case 435: // $@68: %empty
#line 1558 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2598 "dhcp6_parser.cc"
    break;

  case 436: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1561 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2606 "dhcp6_parser.cc"
    break;

  case 441: // $@69: %empty
#line 1577 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2616 "dhcp6_parser.cc"
    break;

  case 442: // option_def_entry: "{" $@69 option_def_params "}"
#line 1581 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2628 "dhcp6_parser.cc"
    break;

  case 443: // $@70: %empty
#line 1592 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 444: // sub_option_def: "{" $@70 option_def_params "}"
#line 1596 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2650 "dhcp6_parser.cc"
    break;

  case 460: // code: "code" ":" "integer"
#line 1628 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2660 "dhcp6_parser.cc"
    break;

  case 462: // $@71: %empty
#line 1636 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2669 "dhcp6_parser.cc"
    break;

  case 463: // option_def_type: "type" $@71 ":" "constant string"
#line 1639 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2679 "dhcp6_parser.cc"
    break;

  case 464: // $@72: %empty
#line 1645 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2688 "dhcp6_parser.cc"
    break;

  case 465: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1648 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2698 "dhcp6_parser.cc"
    break;

  case 466: // $@73: %empty
#line 1654 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2707 "dhcp6_parser.cc"
    break;

  case 467: // space: "space" $@73 ":" "constant string"
#line 1657 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2717 "dhcp6_parser.cc"
    break;

  case 469: // $@74: %empty
#line 1665 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2726 "dhcp6_parser.cc"
    break;

  case 470: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1668 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2736 "dhcp6_parser.cc"
    break;

  case 471: // option_def_array: "array" ":" "boolean"
#line 1674 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2746 "dhcp6_parser.cc"
    break;

  case 472: // $@75: %empty
#line 1684 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2758 "dhcp6_parser.cc"
    break;

  case 473: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1690 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2767 "dhcp6_parser.cc"
    break;

  case 478: // $@76: %empty
#line 1709 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2777 "dhcp6_parser.cc"
    break;

  case 479: // option_data_entry: "{" $@76 option_data_params "}"
#line 1713 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2786 "dhcp6_parser.cc"
    break;

  case 480: // $@77: %empty
#line 1721 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2796 "dhcp6_parser.cc"
    break;

  case 481: // sub_option_data: "{" $@77 option_data_params "}"
#line 1725 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2805 "dhcp6_parser.cc"
    break;

  case 496: // $@78: %empty
#line 1758 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2814 "dhcp6_parser.cc"
    break;

  case 497: // option_data_data: "data" $@78 ":" "constant string"
#line 1761 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2824 "dhcp6_parser.cc"
    break;

  case 500: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1771 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2834 "dhcp6_parser.cc"
    break;

  case 501: // option_data_always_send: "always-send" ":" "boolean"
#line 1777 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2844 "dhcp6_parser.cc"
    break;

  case 502: // $@79: %empty
#line 1786 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2856 "dhcp6_parser.cc"
    break;

  case 503: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1792 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2865 "dhcp6_parser.cc"
    break;

  case 508: // $@80: %empty
#line 1807 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 509: // pool_list_entry: "{" $@80 pool_params "}"
#line 1811 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 510: // $@81: %empty
#line 1817 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2895 "dhcp6_parser.cc"
    break;

  case 511: // sub_pool6: "{" $@81 pool_params "}"
#line 1821 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 521: // $@82: %empty
#line 1840 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2914 "dhcp6_parser.cc"
    break;

  case 522: // pool_entry: "pool" $@82 ":" "constant string"
#line 1843 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2924 "dhcp6_parser.cc"
    break;

  case 523: // $@83: %empty
#line 1849 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2932 "dhcp6_parser.cc"
    break;

  case 524: // user_context: "user-context" $@83 ":" map_value
#line 1851 "dhcp6_parser.yy"
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

  case 525: // $@84: %empty
#line 1874 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2967 "dhcp6_parser.cc"
    break;

  case 526: // comment: "comment" $@84 ":" "constant string"
#line 1876 "dhcp6_parser.yy"
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

  case 527: // $@85: %empty
#line 1904 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3008 "dhcp6_parser.cc"
    break;

  case 528: // pd_pools_list: "pd-pools" $@85 ":" "[" pd_pools_list_content "]"
#line 1910 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3017 "dhcp6_parser.cc"
    break;

  case 533: // $@86: %empty
#line 1925 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 534: // pd_pool_entry: "{" $@86 pd_pool_params "}"
#line 1929 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3039 "dhcp6_parser.cc"
    break;

  case 535: // $@87: %empty
#line 1937 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3049 "dhcp6_parser.cc"
    break;

  case 536: // sub_pd_pool: "{" $@87 pd_pool_params "}"
#line 1941 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3061 "dhcp6_parser.cc"
    break;

  case 550: // $@88: %empty
#line 1966 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3070 "dhcp6_parser.cc"
    break;

  case 551: // pd_prefix: "prefix" $@88 ":" "constant string"
#line 1969 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3080 "dhcp6_parser.cc"
    break;

  case 552: // pd_prefix_len: "prefix-len" ":" "integer"
#line 1975 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3090 "dhcp6_parser.cc"
    break;

  case 553: // $@89: %empty
#line 1981 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3099 "dhcp6_parser.cc"
    break;

  case 554: // excluded_prefix: "excluded-prefix" $@89 ":" "constant string"
#line 1984 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3109 "dhcp6_parser.cc"
    break;

  case 555: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 1990 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3119 "dhcp6_parser.cc"
    break;

  case 556: // pd_delegated_len: "delegated-len" ":" "integer"
#line 1996 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3129 "dhcp6_parser.cc"
    break;

  case 557: // $@90: %empty
#line 2005 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3141 "dhcp6_parser.cc"
    break;

  case 558: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2011 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3150 "dhcp6_parser.cc"
    break;

  case 563: // $@91: %empty
#line 2024 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3160 "dhcp6_parser.cc"
    break;

  case 564: // reservation: "{" $@91 reservation_params "}"
#line 2028 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3169 "dhcp6_parser.cc"
    break;

  case 565: // $@92: %empty
#line 2033 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 566: // sub_reservation: "{" $@92 reservation_params "}"
#line 2037 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3188 "dhcp6_parser.cc"
    break;

  case 582: // $@93: %empty
#line 2064 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3200 "dhcp6_parser.cc"
    break;

  case 583: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2070 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3209 "dhcp6_parser.cc"
    break;

  case 584: // $@94: %empty
#line 2075 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3221 "dhcp6_parser.cc"
    break;

  case 585: // prefixes: "prefixes" $@94 ":" list_strings
#line 2081 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3230 "dhcp6_parser.cc"
    break;

  case 586: // $@95: %empty
#line 2086 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3239 "dhcp6_parser.cc"
    break;

  case 587: // duid: "duid" $@95 ":" "constant string"
#line 2089 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3249 "dhcp6_parser.cc"
    break;

  case 588: // $@96: %empty
#line 2095 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3258 "dhcp6_parser.cc"
    break;

  case 589: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2098 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3268 "dhcp6_parser.cc"
    break;

  case 590: // $@97: %empty
#line 2104 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3277 "dhcp6_parser.cc"
    break;

  case 591: // hostname: "hostname" $@97 ":" "constant string"
#line 2107 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3287 "dhcp6_parser.cc"
    break;

  case 592: // $@98: %empty
#line 2113 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3296 "dhcp6_parser.cc"
    break;

  case 593: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2116 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3306 "dhcp6_parser.cc"
    break;

  case 594: // $@99: %empty
#line 2122 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp6_parser.cc"
    break;

  case 595: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2128 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3327 "dhcp6_parser.cc"
    break;

  case 596: // $@100: %empty
#line 2136 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3339 "dhcp6_parser.cc"
    break;

  case 597: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2142 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 600: // $@101: %empty
#line 2151 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3357 "dhcp6_parser.cc"
    break;

  case 601: // ip_address: "ip-address" $@101 ":" "constant string"
#line 2154 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3367 "dhcp6_parser.cc"
    break;

  case 602: // $@102: %empty
#line 2163 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3379 "dhcp6_parser.cc"
    break;

  case 603: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2169 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3388 "dhcp6_parser.cc"
    break;

  case 606: // $@103: %empty
#line 2178 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 607: // client_class_entry: "{" $@103 client_class_params "}"
#line 2182 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3408 "dhcp6_parser.cc"
    break;

  case 620: // $@104: %empty
#line 2207 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3417 "dhcp6_parser.cc"
    break;

  case 621: // client_class_test: "test" $@104 ":" "constant string"
#line 2210 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3427 "dhcp6_parser.cc"
    break;

  case 622: // only_if_required: "only-if-required" ":" "boolean"
#line 2216 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3437 "dhcp6_parser.cc"
    break;

  case 623: // $@105: %empty
#line 2225 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3449 "dhcp6_parser.cc"
    break;

  case 624: // server_id: "server-id" $@105 ":" "{" server_id_params "}"
#line 2231 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3460 "dhcp6_parser.cc"
    break;

  case 636: // $@106: %empty
#line 2253 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3469 "dhcp6_parser.cc"
    break;

  case 637: // server_id_type: "type" $@106 ":" duid_type
#line 2256 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3478 "dhcp6_parser.cc"
    break;

  case 638: // duid_type: "LLT"
#line 2261 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3484 "dhcp6_parser.cc"
    break;

  case 639: // duid_type: "EN"
#line 2262 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3490 "dhcp6_parser.cc"
    break;

  case 640: // duid_type: "LL"
#line 2263 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3496 "dhcp6_parser.cc"
    break;

  case 641: // htype: "htype" ":" "integer"
#line 2266 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3506 "dhcp6_parser.cc"
    break;

  case 642: // $@107: %empty
#line 2272 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3515 "dhcp6_parser.cc"
    break;

  case 643: // identifier: "identifier" $@107 ":" "constant string"
#line 2275 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3525 "dhcp6_parser.cc"
    break;

  case 644: // time: "time" ":" "integer"
#line 2281 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3535 "dhcp6_parser.cc"
    break;

  case 645: // enterprise_id: "enterprise-id" ":" "integer"
#line 2287 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3545 "dhcp6_parser.cc"
    break;

  case 646: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2295 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 647: // $@108: %empty
#line 2303 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3567 "dhcp6_parser.cc"
    break;

  case 648: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2309 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3576 "dhcp6_parser.cc"
    break;

  case 656: // $@109: %empty
#line 2325 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3585 "dhcp6_parser.cc"
    break;

  case 657: // socket_type: "socket-type" $@109 ":" "constant string"
#line 2328 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3595 "dhcp6_parser.cc"
    break;

  case 658: // $@110: %empty
#line 2334 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3604 "dhcp6_parser.cc"
    break;

  case 659: // socket_name: "socket-name" $@110 ":" "constant string"
#line 2337 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3614 "dhcp6_parser.cc"
    break;

  case 660: // $@111: %empty
#line 2346 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3626 "dhcp6_parser.cc"
    break;

  case 661: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2352 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3637 "dhcp6_parser.cc"
    break;

  case 670: // enable_queue: "enable-queue" ":" "boolean"
#line 2371 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3647 "dhcp6_parser.cc"
    break;

  case 671: // $@112: %empty
#line 2377 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3656 "dhcp6_parser.cc"
    break;

  case 672: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2380 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3666 "dhcp6_parser.cc"
    break;

  case 673: // capacity: "capacity" ":" "integer"
#line 2386 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3676 "dhcp6_parser.cc"
    break;

  case 674: // $@113: %empty
#line 2392 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3685 "dhcp6_parser.cc"
    break;

  case 675: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2395 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3694 "dhcp6_parser.cc"
    break;

  case 676: // $@114: %empty
#line 2402 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3706 "dhcp6_parser.cc"
    break;

  case 677: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2408 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3717 "dhcp6_parser.cc"
    break;

  case 678: // $@115: %empty
#line 2415 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 679: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2419 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 700: // enable_updates: "enable-updates" ":" "boolean"
#line 2449 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3747 "dhcp6_parser.cc"
    break;

  case 701: // $@116: %empty
#line 2456 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3756 "dhcp6_parser.cc"
    break;

  case 702: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2459 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 703: // $@117: %empty
#line 2465 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 704: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2468 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 705: // server_port: "server-port" ":" "integer"
#line 2474 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3795 "dhcp6_parser.cc"
    break;

  case 706: // $@118: %empty
#line 2480 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3804 "dhcp6_parser.cc"
    break;

  case 707: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2483 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 708: // sender_port: "sender-port" ":" "integer"
#line 2489 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 709: // max_queue_size: "max-queue-size" ":" "integer"
#line 2495 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 710: // $@119: %empty
#line 2501 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3843 "dhcp6_parser.cc"
    break;

  case 711: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2504 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3852 "dhcp6_parser.cc"
    break;

  case 712: // ncr_protocol_value: "UDP"
#line 2510 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3858 "dhcp6_parser.cc"
    break;

  case 713: // ncr_protocol_value: "TCP"
#line 2511 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3864 "dhcp6_parser.cc"
    break;

  case 714: // $@120: %empty
#line 2514 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3873 "dhcp6_parser.cc"
    break;

  case 715: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2517 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 716: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2524 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3893 "dhcp6_parser.cc"
    break;

  case 717: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2531 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3903 "dhcp6_parser.cc"
    break;

  case 718: // $@121: %empty
#line 2538 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3912 "dhcp6_parser.cc"
    break;

  case 719: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2541 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3921 "dhcp6_parser.cc"
    break;

  case 720: // $@122: %empty
#line 2547 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3930 "dhcp6_parser.cc"
    break;

  case 721: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2550 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3940 "dhcp6_parser.cc"
    break;

  case 722: // $@123: %empty
#line 2557 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3949 "dhcp6_parser.cc"
    break;

  case 723: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2560 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3959 "dhcp6_parser.cc"
    break;

  case 724: // $@124: %empty
#line 2567 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3968 "dhcp6_parser.cc"
    break;

  case 725: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2570 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3978 "dhcp6_parser.cc"
    break;

  case 726: // $@125: %empty
#line 2579 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3990 "dhcp6_parser.cc"
    break;

  case 727: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2585 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 728: // $@126: %empty
#line 2591 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4010 "dhcp6_parser.cc"
    break;

  case 729: // sub_config_control: "{" $@126 config_control_params "}"
#line 2595 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4019 "dhcp6_parser.cc"
    break;

  case 734: // $@127: %empty
#line 2610 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 735: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2616 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4040 "dhcp6_parser.cc"
    break;

  case 736: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2621 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 737: // $@128: %empty
#line 2629 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4062 "dhcp6_parser.cc"
    break;

  case 738: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2635 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4071 "dhcp6_parser.cc"
    break;

  case 741: // $@129: %empty
#line 2647 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 742: // logger_entry: "{" $@129 logger_params "}"
#line 2651 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4089 "dhcp6_parser.cc"
    break;

  case 752: // debuglevel: "debuglevel" ":" "integer"
#line 2668 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4099 "dhcp6_parser.cc"
    break;

  case 753: // $@130: %empty
#line 2674 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4108 "dhcp6_parser.cc"
    break;

  case 754: // severity: "severity" $@130 ":" "constant string"
#line 2677 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 755: // $@131: %empty
#line 2683 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4130 "dhcp6_parser.cc"
    break;

  case 756: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2689 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4139 "dhcp6_parser.cc"
    break;

  case 759: // $@132: %empty
#line 2698 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4149 "dhcp6_parser.cc"
    break;

  case 760: // output_entry: "{" $@132 output_params_list "}"
#line 2702 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4157 "dhcp6_parser.cc"
    break;

  case 768: // $@133: %empty
#line 2717 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4166 "dhcp6_parser.cc"
    break;

  case 769: // output: "output" $@133 ":" "constant string"
#line 2720 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4176 "dhcp6_parser.cc"
    break;

  case 770: // flush: "flush" ":" "boolean"
#line 2726 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 771: // maxsize: "maxsize" ":" "integer"
#line 2732 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4196 "dhcp6_parser.cc"
    break;

  case 772: // maxver: "maxver" ":" "integer"
#line 2738 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4206 "dhcp6_parser.cc"
    break;

  case 773: // $@134: %empty
#line 2744 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4215 "dhcp6_parser.cc"
    break;

  case 774: // pattern: "pattern" $@134 ":" "constant string"
#line 2747 "dhcp6_parser.yy"
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


  const short Dhcp6Parser::yypact_ninf_ = -942;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     174,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,    49,    34,    64,    81,    87,
     103,   118,   120,   155,   176,   177,   191,   232,   252,   286,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,    34,  -144,
      57,   159,    43,   514,   183,   229,   237,   131,   178,    91,
     -85,   636,   121,  -942,   111,   243,   298,   303,   309,  -942,
     328,  -942,  -942,  -942,  -942,  -942,  -942,   341,   387,   410,
     416,   417,   419,   423,   425,   426,   429,   431,   432,   433,
     435,  -942,   437,   445,   446,   447,   449,  -942,  -942,  -942,
     450,   451,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   452,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,   453,  -942,    60,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,   455,  -942,    61,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   457,
     465,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   101,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
     108,  -942,  -942,  -942,  -942,  -942,   466,  -942,   469,   470,
    -942,  -942,  -942,  -942,  -942,  -942,   184,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,   364,   392,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,   399,  -942,  -942,   471,  -942,  -942,
    -942,   472,  -942,  -942,   473,   474,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   475,
     481,  -942,  -942,  -942,  -942,   478,   485,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   188,
    -942,  -942,  -942,   486,  -942,  -942,   487,  -942,   488,   489,
    -942,  -942,   492,   493,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,   192,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   494,
     194,  -942,  -942,  -942,  -942,    34,    34,  -942,   292,   497,
    -942,   501,   502,   503,   504,   505,   507,   280,   319,   323,
     324,   325,   326,   327,   329,   335,   333,   338,   339,   343,
     344,   522,   345,   346,   348,   349,   350,   527,   541,   542,
     351,   352,   549,   550,   551,   552,   553,   567,   568,   569,
     570,   579,   580,   582,   583,   584,   585,   586,   393,   588,
     589,   590,   592,   595,   596,   598,  -942,   159,  -942,   607,
     412,    43,  -942,   609,   610,   611,   612,   614,   421,   420,
     617,   619,   620,   514,  -942,   623,   183,  -942,   624,   434,
     625,   439,   441,   229,  -942,   626,   627,   637,   638,   639,
     640,   641,  -942,   237,  -942,   642,   643,   442,   644,   645,
     651,   456,  -942,   178,   653,   458,   459,  -942,    91,   656,
     657,   -77,  -942,   462,   659,   661,   468,   663,   476,   477,
     664,   665,   479,   480,   666,   667,   672,   673,   636,  -942,
     674,   483,   121,  -942,  -942,  -942,   678,   676,   491,   677,
     682,   683,   684,   680,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   495,  -942,
    -942,  -942,  -942,  -942,   -14,   496,   498,  -942,  -942,   689,
     691,   692,   693,   506,    -2,   694,   696,   697,   699,   698,
     722,   723,   733,   734,   735,  -942,   736,   737,   738,   739,
     554,   555,   742,  -942,   743,  -942,  -942,   744,   745,   556,
     557,   558,  -942,  -942,   743,   559,   752,  -942,   565,  -942,
     571,  -942,   572,  -942,  -942,  -942,   743,   743,   743,   573,
     574,   575,   576,  -942,   577,   578,  -942,   581,   587,   604,
    -942,  -942,   605,  -942,  -942,  -942,   606,   693,  -942,  -942,
     608,   613,  -942,   615,  -942,  -942,  -109,   531,  -942,  -942,
     -14,   616,   618,   621,  -942,   760,  -942,  -942,    34,   159,
    -942,   121,    43,   110,   110,   759,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,   770,   773,   774,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,   775,   -75,    34,   160,
     566,   776,   778,   779,   195,   100,   -28,   196,   180,   636,
    -942,  -942,   797,  -942,  -942,   799,   800,  -942,  -942,  -942,
    -942,  -942,   -69,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,   759,  -942,   239,   281,   284,  -942,  -942,  -942,
    -942,   763,   807,   810,   812,   813,  -942,   815,   816,  -942,
    -942,  -942,   817,   818,   819,   820,  -942,   301,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   331,
    -942,   821,   822,  -942,  -942,   823,   825,  -942,  -942,   824,
     828,  -942,  -942,   826,   831,  -942,  -942,   829,   833,  -942,
    -942,  -942,    75,  -942,  -942,  -942,   832,  -942,  -942,  -942,
     169,  -942,  -942,  -942,  -942,   368,  -942,  -942,  -942,   182,
    -942,  -942,   836,   834,  -942,  -942,   837,   841,  -942,   835,
     842,   843,   844,   845,   846,   370,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,   847,   848,   849,  -942,  -942,
    -942,  -942,   371,  -942,  -942,  -942,  -942,  -942,  -942,   850,
     851,   852,  -942,   378,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,   379,  -942,  -942,  -942,   853,
    -942,   854,  -942,  -942,  -942,   380,  -942,  -942,  -942,  -942,
    -942,   381,  -942,   271,  -942,   629,  -942,   839,   856,  -942,
    -942,   855,   857,  -942,  -942,  -942,   858,  -942,   861,  -942,
    -942,  -942,   859,   860,   864,   865,   675,   662,   679,   670,
     681,   867,   685,   686,   868,   870,   871,   687,   690,   700,
     695,   110,  -942,  -942,   110,  -942,   759,   514,  -942,   770,
     178,  -942,   773,    91,  -942,   774,   668,  -942,   775,   -75,
    -942,  -942,   160,  -942,   872,   566,  -942,   -24,   776,  -942,
     237,  -942,   778,   -85,  -942,   779,   703,   705,   706,   712,
     717,   726,   195,  -942,   874,   876,   762,   768,   771,   100,
    -942,   721,   781,   782,   -28,  -942,   877,   878,   196,  -942,
     731,   883,   786,   887,   180,  -942,  -942,   104,   797,  -942,
    -942,   888,   893,   183,  -942,   799,   229,  -942,   800,   928,
    -942,  -942,   136,   753,   780,   788,  -942,  -942,  -942,  -942,
    -942,   791,  -942,  -942,   794,   796,   809,  -942,  -942,  -942,
    -942,  -942,   382,  -942,   389,  -942,   927,  -942,   932,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,   391,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,   840,  -942,  -942,   937,  -942,  -942,  -942,  -942,  -942,
     949,   969,  -942,  -942,  -942,  -942,  -942,   968,  -942,   395,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   285,   862,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   863,   866,
    -942,  -942,   869,  -942,    34,  -942,  -942,  1010,  -942,  -942,
    -942,  -942,  -942,   401,  -942,  -942,  -942,  -942,  -942,  -942,
     873,   402,  -942,   403,  -942,   875,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,   668,  -942,  -942,  1017,   830,  -942,   -24,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    1018,   827,  1019,   104,  -942,  -942,  -942,  -942,  -942,  -942,
     879,  -942,  -942,  1021,  -942,   881,  -942,  -942,  1022,  -942,
    -942,   332,  -942,   167,  1022,  -942,  -942,  1024,  1027,  1029,
    -942,   405,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  1030,
     838,   884,   885,  1032,   167,  -942,   882,  -942,  -942,  -942,
     889,  -942,  -942,  -942
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   164,     9,   326,    11,
     510,    13,   535,    15,   565,    17,   435,    19,   443,    21,
     480,    23,   291,    25,   678,    27,   728,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   567,     0,   445,   482,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   122,   726,   162,   176,   178,   180,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   160,     0,     0,     0,     0,     0,   141,   148,   150,
       0,     0,   318,   433,   472,   523,   525,   379,   387,   251,
     268,   259,   244,   602,   557,   283,   302,   623,     0,   270,
     647,   660,   676,   153,   155,   737,     0,   121,     0,    64,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   102,
     103,   104,   105,   106,    75,   110,   111,   112,   113,   114,
     115,   116,   108,   109,   117,   118,   119,   100,    78,    79,
      80,    81,    97,    82,    84,    83,   120,    88,    89,    76,
     101,    77,    86,    87,    95,    96,    98,    85,    90,    91,
      92,    93,    94,    99,   107,   173,     0,   172,     0,   166,
     168,   169,   170,   171,   502,   527,   369,   371,   373,     0,
       0,   377,   375,   596,   368,   330,   331,   332,   333,   334,
     335,   336,   337,   353,   354,   355,   356,   357,   360,   361,
     362,   363,   364,   365,   366,   358,   359,   367,     0,   328,
     341,   342,   343,   346,   347,   349,   344,   345,   338,   339,
     351,   352,   340,   348,   350,   521,   520,   516,   517,   515,
       0,   512,   514,   518,   519,   550,     0,   553,     0,     0,
     549,   543,   544,   542,   547,   548,     0,   537,   539,   540,
     545,   546,   541,   594,   582,   584,   586,   588,   590,   592,
     581,   578,   579,   580,     0,   568,   569,   573,   574,   571,
     575,   576,   577,   572,     0,   462,   224,     0,   466,   464,
     469,     0,   458,   459,     0,   446,   447,   449,   461,   450,
     451,   452,   468,   453,   454,   455,   456,   457,   496,     0,
       0,   494,   495,   498,   499,     0,   483,   484,   486,   487,
     488,   489,   490,   491,   492,   493,   298,   300,   295,     0,
     293,   296,   297,     0,   701,   703,     0,   706,     0,     0,
     710,   714,     0,     0,   718,   720,   722,   724,   699,   697,
     698,     0,   680,   682,   694,   683,   684,   685,   686,   687,
     688,   689,   690,   691,   692,   693,   695,   696,   734,     0,
       0,   730,   732,   733,    46,     0,     0,    39,     0,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,     0,    63,     0,
       0,     0,   165,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   327,     0,     0,   511,     0,     0,
       0,     0,     0,     0,   536,     0,     0,     0,     0,     0,
       0,     0,   566,     0,   436,     0,     0,     0,     0,     0,
       0,     0,   444,     0,     0,     0,     0,   481,     0,     0,
       0,     0,   292,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   679,
       0,     0,     0,   729,    50,    43,     0,     0,     0,     0,
       0,     0,     0,     0,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,     0,   158,
     159,   138,   139,   140,     0,     0,     0,   152,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   646,     0,     0,     0,     0,
       0,     0,     0,    65,     0,   175,   167,     0,     0,     0,
       0,     0,   385,   386,     0,     0,     0,   329,     0,   513,
       0,   552,     0,   555,   556,   538,     0,     0,     0,     0,
       0,     0,     0,   570,     0,     0,   460,     0,     0,     0,
     471,   448,     0,   500,   501,   485,     0,     0,   294,   700,
       0,     0,   705,     0,   708,   709,     0,     0,   716,   717,
       0,     0,     0,     0,   681,     0,   736,   731,     0,     0,
     123,     0,     0,     0,     0,   182,   161,   143,   144,   145,
     146,   147,   142,   149,   151,   320,   437,   474,    40,   524,
     526,   381,   382,   383,   384,   380,   389,     0,    47,     0,
       0,     0,   559,   285,     0,     0,     0,     0,     0,     0,
     154,   156,     0,    51,   174,   504,   529,   370,   372,   374,
     378,   376,     0,   522,   551,   554,   595,   583,   585,   587,
     589,   591,   593,   463,   225,   467,   465,   470,   497,   299,
     301,   702,   704,   707,   712,   713,   711,   715,   719,   721,
     723,   725,   182,    44,     0,     0,     0,   211,   217,   219,
     221,     0,     0,     0,     0,     0,   235,     0,     0,   238,
     240,   242,     0,     0,     0,     0,   210,     0,   188,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   202,
     209,   203,   204,   205,   200,   201,   206,   207,   208,     0,
     186,     0,   183,   184,   324,     0,   321,   322,   441,     0,
     438,   439,   478,     0,   475,   476,   393,     0,   390,   391,
     257,   258,     0,   253,   255,   256,     0,   266,   267,   263,
       0,   261,   264,   265,   249,     0,   246,   248,   606,     0,
     604,   563,     0,   560,   561,   289,     0,   286,   287,     0,
       0,     0,     0,     0,     0,     0,   304,   306,   307,   308,
     309,   310,   311,   636,   642,     0,     0,     0,   635,   632,
     633,   634,     0,   625,   627,   630,   628,   629,   631,     0,
       0,     0,   279,     0,   272,   274,   275,   276,   277,   278,
     656,   658,   655,   653,   654,     0,   649,   651,   652,     0,
     671,     0,   674,   667,   668,     0,   662,   664,   665,   666,
     669,     0,   741,     0,   739,    53,   508,     0,   505,   506,
     533,     0,   530,   531,   600,   599,     0,   598,     0,    61,
     727,   163,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   177,   179,     0,   181,     0,     0,   319,     0,
     445,   434,     0,   482,   473,     0,     0,   388,     0,     0,
     252,   269,     0,   260,     0,     0,   245,   608,     0,   603,
     567,   558,     0,     0,   284,     0,     0,     0,     0,     0,
       0,     0,     0,   303,     0,     0,     0,     0,     0,     0,
     624,     0,     0,     0,     0,   271,     0,     0,     0,   648,
       0,     0,     0,     0,     0,   661,   677,     0,     0,   738,
      55,     0,    54,     0,   503,     0,     0,   528,     0,     0,
     597,   735,     0,     0,     0,     0,   223,   226,   227,   228,
     229,     0,   237,   230,     0,     0,     0,   232,   233,   234,
     231,   189,     0,   185,     0,   323,     0,   440,     0,   477,
     432,   408,   409,   410,   412,   413,   414,   401,   402,   417,
     418,   419,   420,   421,   424,   425,   426,   427,   428,   429,
     430,   422,   423,   431,   397,   398,   399,   400,   406,   407,
     405,   411,     0,   395,   403,   415,   416,   404,   392,   254,
     262,     0,   247,   620,     0,   618,   619,   615,   616,   617,
       0,   609,   610,   612,   613,   614,   605,     0,   562,     0,
     288,   312,   313,   314,   315,   316,   317,   305,     0,     0,
     641,   644,   645,   626,   280,   281,   282,   273,     0,     0,
     650,   670,     0,   673,     0,   663,   755,     0,   753,   751,
     745,   749,   750,     0,   743,   747,   748,   746,   740,    52,
       0,     0,   507,     0,   532,     0,   213,   214,   215,   216,
     212,   218,   220,   222,   236,   239,   241,   243,   187,   325,
     442,   479,     0,   394,   250,     0,     0,   607,     0,   564,
     290,   638,   639,   640,   637,   643,   657,   659,   672,   675,
       0,     0,     0,     0,   742,    56,   509,   534,   601,   396,
       0,   622,   611,     0,   752,     0,   744,   621,     0,   754,
     759,     0,   757,     0,     0,   756,   768,     0,     0,     0,
     773,     0,   761,   763,   764,   765,   766,   767,   758,     0,
       0,     0,     0,     0,     0,   760,     0,   770,   771,   772,
       0,   762,   769,   774
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,    -4,  -942,  -540,  -942,
     394,  -942,  -942,  -942,  -942,   347,  -942,  -527,  -942,  -942,
    -942,   -71,  -942,  -942,  -942,  -942,  -942,  -942,   373,   591,
    -942,  -942,   -59,   -43,   -40,   -39,   -37,   -23,   -21,   -19,
     -18,   -15,    -3,    -1,    16,  -942,    29,    30,    32,    33,
    -942,   384,    35,  -942,    45,  -942,    46,    47,  -942,    50,
    -942,    51,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
     367,   593,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,   294,  -942,    92,  -942,  -658,    96,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,   -47,  -942,  -694,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
      74,  -942,  -942,  -942,  -942,  -942,    82,  -677,  -942,  -942,
    -942,  -942,    78,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
      48,  -942,  -942,  -942,  -942,  -942,  -942,  -942,    68,  -942,
    -942,  -942,    71,   534,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,    65,  -942,  -942,  -942,  -942,  -942,  -942,  -941,  -942,
    -942,  -942,    97,  -942,  -942,  -942,   105,   601,  -942,  -942,
    -939,  -942,  -938,  -942,     9,  -942,    54,  -942,    53,  -942,
    -942,  -942,  -937,  -942,  -942,  -942,  -942,    93,  -942,  -942,
    -117,   990,  -942,  -942,  -942,  -942,  -942,   106,  -942,  -942,
    -942,   109,  -942,   560,  -942,   -73,  -942,  -942,  -942,  -942,
    -942,   -66,  -942,  -942,  -942,  -942,  -942,    17,  -942,  -942,
    -942,   116,  -942,  -942,  -942,   112,  -942,   594,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,    62,
    -942,  -942,  -942,    66,   599,  -942,  -942,   -55,  -942,     1,
    -942,  -942,  -942,  -942,  -942,    63,  -942,  -942,  -942,    67,
     597,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   -58,  -942,
    -942,  -942,    89,  -942,  -942,  -942,    94,  -942,   600,   366,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -931,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,   114,  -942,  -942,  -942,   -94,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,    98,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,    88,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,    84,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,   386,   561,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,   430,   562,  -942,  -942,
    -942,  -942,  -942,  -942,    90,  -942,  -942,  -103,  -942,  -942,
    -942,  -942,  -942,  -942,  -122,  -942,  -942,  -139,  -942,  -942,
    -942,  -942,  -942,  -942,  -942
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     689,    87,    88,    41,    68,    84,    85,   714,   915,  1021,
    1022,   776,    43,    70,    90,   409,    45,    71,   148,   149,
     150,   411,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     437,   682,   169,   438,   170,   439,   171,   172,   463,   173,
     464,   174,   175,   176,   177,   431,   178,   413,    47,    72,
     208,   209,   210,   469,   211,   179,   414,   180,   415,   181,
     416,   801,   802,   803,   954,   777,   778,   779,   932,  1170,
     780,   933,   781,   934,   782,   935,   783,   784,   506,   785,
     786,   787,   788,   789,   790,   791,   792,   793,   794,   941,
     795,   796,   944,   797,   945,   798,   946,   182,   452,   835,
     836,   837,   974,   183,   449,   822,   823,   824,   825,   184,
     451,   830,   831,   832,   833,   185,   450,   186,   459,   883,
     884,   885,   886,   887,   187,   455,   846,   847,   848,   983,
      63,    80,   359,   360,   361,   519,   362,   520,   188,   456,
     855,   856,   857,   858,   859,   860,   861,   862,   189,   442,
     805,   806,   807,   957,    49,    73,   248,   249,   250,   475,
     251,   476,   252,   477,   253,   481,   254,   480,   190,   447,
     695,   256,   257,   191,   448,   817,   818,   819,   966,  1092,
    1093,   192,   443,    57,    77,   809,   810,   811,   960,    59,
      78,   324,   325,   326,   327,   328,   329,   330,   505,   331,
     509,   332,   508,   333,   334,   510,   335,   193,   444,   813,
     814,   815,   963,    61,    79,   345,   346,   347,   348,   349,
     514,   350,   351,   352,   353,   259,   473,   917,   918,   919,
    1023,    51,    74,   270,   271,   272,   485,   194,   445,   195,
     446,   262,   474,   921,   922,   923,  1026,    53,    75,   286,
     287,   288,   488,   289,   290,   490,   291,   292,   196,   454,
     842,   843,   844,   980,    55,    76,   304,   305,   306,   307,
     496,   308,   497,   309,   498,   310,   499,   311,   500,   312,
     501,   313,   495,   264,   482,   926,   927,  1029,   197,   453,
     839,   840,   977,  1110,  1111,  1112,  1113,  1114,  1185,  1115,
     198,   457,   872,   873,   874,   994,  1194,   875,   876,   995,
     877,   878,   199,   200,   460,   895,   896,   897,  1006,   898,
    1007,   201,   461,   905,   906,   907,   908,  1011,   909,   910,
    1013,   202,   462,    65,    81,   381,   382,   383,   384,   524,
     385,   525,   386,   387,   527,   388,   389,   390,   530,   746,
     391,   531,   392,   393,   394,   534,   395,   535,   396,   536,
     397,   537,   203,   412,    67,    82,   400,   401,   402,   540,
     403,   204,   465,   913,   914,  1017,  1153,  1154,  1155,  1156,
    1202,  1157,  1200,  1221,  1222,  1223,  1231,  1232,  1233,  1239,
    1234,  1235,  1236,  1237,  1243
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     147,   207,   224,   266,   280,   300,   343,   322,   341,   358,
     378,   869,    38,   344,   225,   263,   799,   212,   260,   273,
     284,   302,   829,   336,   354,  1085,   379,  1086,  1087,  1091,
     226,   323,   342,   227,   228,  1097,   229,   356,   357,    31,
     820,    32,   688,    33,   294,   356,   357,   124,   316,    30,
     230,   924,   231,    86,   232,   233,   744,   745,   234,   205,
     206,   125,   126,   467,   471,   125,   126,    89,   468,   472,
     235,    42,   236,   213,   261,   274,   285,   303,   969,   337,
     355,   970,   380,   267,   281,  1103,  1104,   720,    44,   237,
     258,   269,   283,   301,    46,   691,   692,   693,   694,   726,
     727,   728,   238,   239,   483,   240,   241,   688,   242,   484,
      48,   486,   146,   879,   880,   881,   487,   404,   243,   244,
     245,   863,   821,   246,   247,    50,   255,    52,   268,   282,
     762,   757,   125,   126,   398,   399,   758,   759,   760,   761,
     762,   763,   764,   765,   766,   767,   768,   769,   770,   771,
     772,   773,   774,   775,   677,   678,   679,   680,  1166,  1167,
    1168,  1169,    54,   316,   338,   317,   318,   339,   340,   146,
      91,    92,   972,   146,    93,   973,   316,    94,    95,    96,
     125,   126,   316,    56,    58,   978,   681,   493,   979,   125,
     126,   521,   494,   125,   126,   538,   522,   542,    60,   315,
     539,   123,   543,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,    34,    35,    36,    37,   864,   865,   866,   867,    62,
     146,  1085,   467,  1086,  1087,  1091,   405,   929,   125,   126,
     316,  1097,   317,   318,   124,   127,   319,   320,   321,    64,
     128,   129,   130,   131,   132,   265,   133,   125,   126,   125,
     126,   134,   125,   126,  1018,   820,   827,  1019,   828,  1146,
     135,  1147,  1148,   136,   542,   125,   126,   471,   146,   930,
     137,   221,   931,    66,   222,   829,  1052,   146,   138,   139,
     124,   146,   406,   140,   951,   869,   141,   146,   124,   952,
     142,   407,   408,   275,   276,   277,   278,   279,   125,   126,
     849,   850,   851,   852,   853,   854,   125,   126,   899,   900,
     901,   143,   144,   145,   951,  1224,   410,   221,  1225,   953,
     222,   890,   891,  1226,   293,   417,  1227,  1228,  1229,  1230,
     294,   295,   296,   297,   298,   299,   146,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   975,   502,   992,   999,   146,   976,   902,   993,  1000,
     146,  1004,  1008,  1014,   538,   951,  1005,  1009,  1015,  1016,
    1178,   418,   483,   146,  1182,   503,   147,  1179,   521,  1183,
     207,   544,   545,  1190,  1203,   486,   493,   504,  1244,  1204,
    1206,  1207,   224,  1245,   419,   266,   212,  1191,  1192,  1193,
     420,   421,   280,   422,   225,   263,   146,   423,   260,   424,
     425,   273,   300,   426,   146,   427,   428,   429,   284,   430,
     226,   432,   322,   227,   228,   343,   229,   341,   302,   433,
     434,   435,   344,   436,   440,   441,   458,   466,   336,   470,
     230,   478,   231,   354,   232,   233,   323,   378,   234,   479,
     489,   342,   213,   491,   492,   507,   511,   513,   554,   515,
     235,   512,   236,   379,   261,   516,   517,   274,   518,   546,
     523,   526,   528,   529,   285,   267,   532,   533,   541,   237,
     258,   547,   281,   269,   303,   548,   549,   550,   551,   552,
     283,   553,   238,   239,   337,   240,   241,   555,   242,   355,
     301,   556,   557,   558,   559,   560,   568,   561,   243,   244,
     245,   574,   563,   246,   247,   562,   255,   564,   565,   380,
     268,   566,   567,   569,   570,   575,   576,   282,   571,   572,
     573,   577,   578,   579,   580,   581,   582,   583,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   584,   585,   586,   587,   114,   115,   116,   117,   118,
     119,   120,   121,   588,   589,   124,   590,   591,   592,   593,
     594,   595,   596,   597,   598,   214,   599,   215,   147,   600,
     601,   207,   602,   125,   126,   216,   217,   218,   219,   220,
     127,   604,   605,   607,   608,   609,   610,   212,   611,   612,
     613,   614,   221,   615,   616,   222,   134,   618,   620,   622,
     626,   627,   621,   223,   868,   882,   892,   623,   378,   624,
     636,   628,   629,   630,   631,   632,   634,   635,   637,   638,
     870,   888,   893,   903,   379,   639,   640,   642,   643,   644,
     646,   647,   649,   650,   753,   651,   652,   653,   656,   657,
     660,   661,   834,   213,   654,   655,   662,   663,   665,   658,
     659,   666,   668,   669,   671,   675,   143,   144,   670,   672,
     673,   674,   676,   683,   685,   684,   686,   687,   747,   696,
      32,   697,   698,   690,   699,   700,   871,   889,   894,   904,
     380,   146,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   125,   126,   701,   702,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   703,   124,
     316,   704,   705,   706,   707,   708,   709,   712,   713,   715,
     716,   710,   711,   717,   718,   719,   721,   125,   126,   722,
     217,   218,   723,   220,   127,   752,   800,   936,   724,   725,
     729,   730,   731,   732,   733,   734,   221,   804,   735,   222,
     808,   812,   816,   838,   736,   841,   845,   223,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   737,   738,   739,   912,   741,   916,   920,   376,   377,
     742,   937,   743,   749,   938,   750,   939,   940,   751,   942,
     943,   947,   948,   949,   950,   956,  1020,   955,   959,   958,
     961,   962,   964,   146,   965,   967,   968,   982,   971,   986,
     143,   144,   981,   984,   985,  1024,   987,   988,   989,   990,
     991,   996,   997,   998,  1001,  1002,  1003,  1010,  1012,  1025,
    1028,  1027,  1037,  1032,  1033,   146,  1030,  1031,  1034,  1035,
    1039,  1041,  1044,  1036,  1045,  1046,  1101,  1038,  1128,  1040,
    1129,  1138,  1139,  1042,  1043,  1047,   224,  1142,  1048,   322,
     343,  1144,   341,  1050,  1159,  1060,  1160,   344,   225,   263,
    1049,  1121,   260,  1122,  1123,   336,  1105,  1061,   354,   300,
    1124,  1095,   358,   323,   226,  1125,   342,   227,   228,  1084,
     229,  1134,  1108,  1062,  1126,   302,  1063,  1064,   868,  1065,
    1106,  1141,  1165,   882,   230,  1180,   231,   892,   232,   233,
    1181,  1186,   234,  1066,   870,  1067,  1149,  1068,  1069,   888,
    1171,  1070,   266,   893,   235,   280,   236,  1187,   261,   903,
    1130,   337,  1151,  1071,   355,  1072,  1131,  1096,   273,  1132,
    1150,   284,  1188,   237,   258,  1088,  1189,  1172,  1109,  1135,
    1136,   303,  1073,  1094,  1143,  1173,   238,   239,  1174,   240,
     241,  1175,   242,  1176,  1107,  1074,  1075,   301,  1076,  1077,
     871,  1078,   243,   244,   245,   889,  1177,   246,   247,   894,
     255,  1079,  1080,  1081,  1201,   904,  1082,  1083,  1152,  1090,
    1089,  1210,  1213,  1215,   274,  1214,  1218,   285,  1240,  1220,
    1211,  1241,   267,  1242,  1246,   281,  1250,  1184,  1247,   756,
     269,   740,   754,   283,   748,   826,   928,  1051,  1053,  1102,
    1100,  1099,  1137,  1120,  1119,   648,  1055,  1127,   603,  1195,
    1196,  1098,  1054,  1197,   606,  1209,  1198,   314,  1057,  1056,
    1205,  1118,  1208,   641,  1117,  1058,  1217,   268,  1219,  1252,
     282,  1059,  1248,  1249,   617,   619,  1253,  1162,   925,  1161,
     625,  1164,  1116,  1163,  1212,   911,  1140,  1133,  1145,   664,
    1216,   755,  1238,   633,   667,  1251,     0,     0,  1158,     0,
       0,  1060,   645,     0,     0,     0,     0,  1105,     0,     0,
       0,     0,     0,  1061,     0,     0,     0,  1095,     0,     0,
       0,     0,  1149,  1108,     0,  1084,     0,     0,     0,  1062,
    1199,  1106,  1063,  1064,     0,  1065,     0,     0,  1151,     0,
       0,     0,     0,     0,     0,     0,  1150,     0,     0,  1066,
       0,  1067,     0,  1068,  1069,     0,     0,  1070,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1071,
       0,  1072,     0,  1096,     0,     0,     0,     0,     0,  1109,
       0,  1088,     0,     0,     0,     0,     0,     0,  1073,  1094,
       0,     0,     0,     0,  1152,  1107,     0,     0,     0,     0,
       0,  1074,  1075,     0,  1076,  1077,     0,  1078,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1079,  1080,  1081,
       0,     0,  1082,  1083,     0,  1090,  1089
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    79,    78,    79,    80,
      81,   705,    16,    79,    73,    73,   674,    72,    73,    74,
      75,    76,   699,    78,    79,   966,    81,   966,   966,   966,
      73,    78,    79,    73,    73,   966,    73,   122,   123,     5,
     115,     7,   582,     9,   113,   122,   123,    71,    72,     0,
      73,   120,    73,   197,    73,    73,   165,   166,    73,    16,
      17,    89,    90,     3,     3,    89,    90,    10,     8,     8,
      73,     7,    73,    72,    73,    74,    75,    76,     3,    78,
      79,     6,    81,    74,    75,   109,   110,   614,     7,    73,
      73,    74,    75,    76,     7,    97,    98,    99,   100,   626,
     627,   628,    73,    73,     3,    73,    73,   647,    73,     8,
       7,     3,   197,   141,   142,   143,     8,     6,    73,    73,
      73,    21,   197,    73,    73,     7,    73,     7,    74,    75,
      30,    21,    89,    90,    13,    14,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,   168,   169,   170,   171,    22,    23,
      24,    25,     7,    72,    73,    74,    75,    76,    77,   197,
      11,    12,     3,   197,    15,     6,    72,    18,    19,    20,
      89,    90,    72,     7,     7,     3,   200,     3,     6,    89,
      90,     3,     8,    89,    90,     3,     8,     3,     7,    21,
       8,    70,     8,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,   197,   198,   199,   200,   135,   136,   137,   138,     7,
     197,  1182,     3,  1182,  1182,  1182,     3,     8,    89,    90,
      72,  1182,    74,    75,    71,    96,    78,    79,    80,     7,
     101,   102,   103,   104,   105,    82,   107,    89,    90,    89,
      90,   112,    89,    90,     3,   115,   116,     6,   118,   175,
     121,   177,   178,   124,     3,    89,    90,     3,   197,     8,
     131,   108,     8,     7,   111,   972,   954,   197,   139,   140,
      71,   197,     4,   144,     3,   999,   147,   197,    71,     8,
     151,     8,     3,    84,    85,    86,    87,    88,    89,    90,
     125,   126,   127,   128,   129,   130,    89,    90,   148,   149,
     150,   172,   173,   174,     3,     3,     8,   108,     6,     8,
     111,   145,   146,   176,   107,     4,   179,   180,   181,   182,
     113,   114,   115,   116,   117,   118,   197,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,     3,     8,     3,     3,   197,     8,   197,     8,     8,
     197,     3,     3,     3,     3,     3,     8,     8,     8,     8,
       8,     4,     3,   197,     3,     3,   467,     8,     3,     8,
     471,   405,   406,     8,     3,     3,     3,     8,     3,     8,
       8,     8,   483,     8,     4,   486,   471,   132,   133,   134,
       4,     4,   493,     4,   483,   483,   197,     4,   483,     4,
       4,   486,   503,     4,   197,     4,     4,     4,   493,     4,
     483,     4,   513,   483,   483,   518,   483,   518,   503,     4,
       4,     4,   518,     4,     4,     4,     4,     4,   513,     4,
     483,     4,   483,   518,   483,   483,   513,   538,   483,     4,
       4,   518,   471,     4,     4,     4,     4,     3,   198,     4,
     483,     8,   483,   538,   483,     4,     8,   486,     3,   197,
       4,     4,     4,     4,   493,   486,     4,     4,     4,   483,
     483,     4,   493,   486,   503,     4,     4,     4,     4,     4,
     493,     4,   483,   483,   513,   483,   483,   198,   483,   518,
     503,   198,   198,   198,   198,   198,     4,   198,   483,   483,
     483,     4,   199,   483,   483,   200,   483,   199,   199,   538,
     486,   198,   198,   198,   198,     4,     4,   493,   200,   200,
     200,   200,   200,     4,     4,     4,     4,     4,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,     4,     4,     4,     4,    61,    62,    63,    64,    65,
      66,    67,    68,     4,     4,    71,     4,     4,     4,     4,
       4,   198,     4,     4,     4,    81,     4,    83,   669,     4,
       4,   672,     4,    89,    90,    91,    92,    93,    94,    95,
      96,     4,   200,     4,     4,     4,     4,   672,     4,   198,
     200,     4,   108,     4,     4,   111,   112,     4,     4,     4,
       4,     4,   198,   119,   705,   706,   707,   198,   709,   198,
     198,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     705,   706,   707,   708,   709,     4,   200,     4,   200,   200,
       4,     4,   200,     4,   668,     4,   198,     4,     4,     4,
       4,     4,   106,   672,   198,   198,     4,     4,     4,   200,
     200,   198,     4,     7,     7,     5,   172,   173,   197,     7,
       7,     7,   197,   197,     5,   197,     5,     5,   167,     5,
       7,     5,     5,   197,     5,     7,   705,   706,   707,   708,
     709,   197,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    89,    90,     5,     5,    61,
      62,    63,    64,    65,    66,    67,    68,    69,     5,    71,
      72,     7,     7,     7,     7,     7,     7,     5,     5,     5,
       5,   197,   197,   197,   197,   197,   197,    89,    90,     7,
      92,    93,   197,    95,    96,     5,     7,     4,   197,   197,
     197,   197,   197,   197,   197,   197,   108,     7,   197,   111,
       7,     7,     7,     7,   197,     7,     7,   119,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   197,   197,   197,     7,   197,     7,     7,   172,   173,
     197,     4,   197,   197,     4,   197,     4,     4,   197,     4,
       4,     4,     4,     4,     4,     3,   197,     6,     3,     6,
       6,     3,     6,   197,     3,     6,     3,     3,     6,     4,
     172,   173,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
       3,     6,   200,     4,     4,   197,     8,     6,     4,     4,
     200,     4,     4,   198,     4,     4,     4,   198,     4,   198,
       4,     4,     4,   198,   198,   198,   957,     4,   198,   960,
     963,     4,   963,   198,     6,   966,     3,   963,   957,   957,
     200,   198,   957,   198,   198,   960,   977,   966,   963,   980,
     198,   966,   983,   960,   957,   198,   963,   957,   957,   966,
     957,   200,   977,   966,   198,   980,   966,   966,   999,   966,
     977,   200,     4,  1004,   957,     8,   957,  1008,   957,   957,
       8,     4,   957,   966,   999,   966,  1017,   966,   966,  1004,
     197,   966,  1023,  1008,   957,  1026,   957,     8,   957,  1014,
     198,   960,  1017,   966,   963,   966,   198,   966,  1023,   198,
    1017,  1026,     3,   957,   957,   966,     8,   197,   977,   198,
     198,   980,   966,   966,   198,   197,   957,   957,   197,   957,
     957,   197,   957,   197,   977,   966,   966,   980,   966,   966,
     999,   966,   957,   957,   957,  1004,   197,   957,   957,  1008,
     957,   966,   966,   966,     4,  1014,   966,   966,  1017,   966,
     966,     4,     4,     4,  1023,   198,     5,  1026,     4,     7,
     200,     4,  1023,     4,     4,  1026,     4,   197,   200,   672,
    1023,   647,   669,  1026,   660,   698,   752,   951,   956,   975,
     972,   969,  1004,   985,   983,   521,   959,   992,   467,   197,
     197,   968,   957,   197,   471,  1182,   197,    77,   962,   960,
     197,   982,   197,   513,   980,   963,   197,  1023,   197,   197,
    1026,   965,   198,   198,   483,   486,   197,  1025,   722,  1023,
     493,  1028,   978,  1026,  1188,   709,  1008,   999,  1014,   538,
    1203,   671,  1224,   503,   542,  1244,    -1,    -1,  1018,    -1,
      -1,  1182,   518,    -1,    -1,    -1,    -1,  1188,    -1,    -1,
      -1,    -1,    -1,  1182,    -1,    -1,    -1,  1182,    -1,    -1,
      -1,    -1,  1203,  1188,    -1,  1182,    -1,    -1,    -1,  1182,
    1144,  1188,  1182,  1182,    -1,  1182,    -1,    -1,  1203,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1203,    -1,    -1,  1182,
      -1,  1182,    -1,  1182,  1182,    -1,    -1,  1182,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1182,
      -1,  1182,    -1,  1182,    -1,    -1,    -1,    -1,    -1,  1188,
      -1,  1182,    -1,    -1,    -1,    -1,    -1,    -1,  1182,  1182,
      -1,    -1,    -1,    -1,  1203,  1188,    -1,    -1,    -1,    -1,
      -1,  1182,  1182,    -1,  1182,  1182,    -1,  1182,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1182,  1182,  1182,
      -1,    -1,  1182,  1182,    -1,  1182,  1182
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
      67,    68,    69,    70,    71,    89,    90,    96,   101,   102,
     103,   104,   105,   107,   112,   121,   124,   131,   139,   140,
     144,   147,   151,   172,   173,   174,   197,   232,   239,   240,
     241,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   263,
     265,   267,   268,   270,   272,   273,   274,   275,   277,   286,
     288,   290,   328,   334,   340,   346,   348,   355,   369,   379,
     399,   404,   412,   438,   468,   470,   489,   519,   531,   543,
     544,   552,   562,   593,   602,    16,    17,   232,   281,   282,
     283,   285,   468,   470,    81,    83,    91,    92,    93,    94,
      95,   108,   111,   119,   232,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   257,   258,
     259,   260,   263,   265,   267,   268,   270,   272,   387,   388,
     389,   391,   393,   395,   397,   399,   402,   403,   438,   456,
     468,   470,   472,   489,   514,    82,   232,   395,   397,   438,
     464,   465,   466,   468,   470,    84,    85,    86,    87,    88,
     232,   395,   397,   438,   468,   470,   480,   481,   482,   484,
     485,   487,   488,   107,   113,   114,   115,   116,   117,   118,
     232,   438,   468,   470,   497,   498,   499,   500,   502,   504,
     506,   508,   510,   512,   412,    21,    72,    74,    75,    78,
      79,    80,   232,   308,   422,   423,   424,   425,   426,   427,
     428,   430,   432,   434,   435,   437,   468,   470,    73,    76,
      77,   232,   308,   426,   432,   446,   447,   448,   449,   450,
     452,   453,   454,   455,   468,   470,   122,   123,   232,   363,
     364,   365,   367,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   172,   173,   232,   468,
     470,   566,   567,   568,   569,   571,   573,   574,   576,   577,
     578,   581,   583,   584,   585,   587,   589,   591,    13,    14,
     597,   598,   599,   601,     6,     3,     4,     8,     3,   236,
       8,   242,   594,   278,   287,   289,   291,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   276,     4,     4,     4,     4,     4,   261,   264,   266,
       4,     4,   380,   413,   439,   469,   471,   400,   405,   335,
     347,   341,   329,   520,   490,   356,   370,   532,     4,   349,
     545,   553,   563,   269,   271,   603,     4,     3,     8,   284,
       4,     3,     8,   457,   473,   390,   392,   394,     4,     4,
     398,   396,   515,     3,     8,   467,     3,     8,   483,     4,
     486,     4,     4,     3,     8,   513,   501,   503,   505,   507,
     509,   511,     8,     3,     8,   429,   309,     4,   433,   431,
     436,     4,     8,     3,   451,     4,     4,     8,     3,   366,
     368,     3,     8,     4,   570,   572,     4,   575,     4,     4,
     579,   582,     4,     4,   586,   588,   590,   592,     3,     8,
     600,     4,     3,     8,   217,   217,   197,     4,     4,     4,
       4,     4,     4,     4,   198,   198,   198,   198,   198,   198,
     198,   198,   200,   199,   199,   199,   198,   198,     4,   198,
     198,   200,   200,   200,     4,     4,     4,   200,   200,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   198,     4,     4,     4,     4,
       4,     4,     4,   240,     4,   200,   282,     4,     4,     4,
       4,     4,   198,   200,     4,     4,     4,   388,     4,   465,
       4,   198,     4,   198,   198,   481,     4,     4,     4,     4,
       4,     4,     4,   499,     4,     4,   198,     4,     4,     4,
     200,   424,     4,   200,   200,   448,     4,     4,   364,   200,
       4,     4,   198,     4,   198,   198,     4,     4,   200,   200,
       4,     4,     4,     4,   567,     4,   198,   598,     4,     7,
     197,     7,     7,     7,     7,     5,   197,   168,   169,   170,
     171,   200,   262,   197,   197,     5,     5,     5,   219,   221,
     197,    97,    98,    99,   100,   401,     5,     5,     5,     5,
       7,     5,     5,     5,     7,     7,     7,     7,     7,     7,
     197,   197,     5,     5,   228,     5,     5,   197,   197,   197,
     228,   197,     7,   197,   197,   197,   228,   228,   228,   197,
     197,   197,   197,   197,   197,   197,   197,   197,   197,   197,
     221,   197,   197,   197,   165,   166,   580,   167,   262,   197,
     197,   197,     5,   217,   239,   597,   281,    21,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,   232,   296,   297,   298,
     301,   303,   305,   307,   308,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   321,   322,   324,   326,   296,
       7,   292,   293,   294,     7,   381,   382,   383,     7,   416,
     417,   418,     7,   440,   441,   442,     7,   406,   407,   408,
     115,   197,   336,   337,   338,   339,   226,   116,   118,   338,
     342,   343,   344,   345,   106,   330,   331,   332,     7,   521,
     522,     7,   491,   492,   493,     7,   357,   358,   359,   125,
     126,   127,   128,   129,   130,   371,   372,   373,   374,   375,
     376,   377,   378,    21,   135,   136,   137,   138,   232,   310,
     468,   470,   533,   534,   535,   538,   539,   541,   542,   141,
     142,   143,   232,   350,   351,   352,   353,   354,   468,   470,
     145,   146,   232,   468,   470,   546,   547,   548,   550,   148,
     149,   150,   197,   468,   470,   554,   555,   556,   557,   559,
     560,   566,     7,   604,   605,   229,     7,   458,   459,   460,
       7,   474,   475,   476,   120,   500,   516,   517,   292,     8,
       8,     8,   299,   302,   304,   306,     4,     4,     4,     4,
       4,   320,     4,     4,   323,   325,   327,     4,     4,     4,
       4,     3,     8,     8,   295,     6,     3,   384,     6,     3,
     419,     6,     3,   443,     6,     3,   409,     6,     3,     3,
       6,     6,     3,     6,   333,     3,     8,   523,     3,     6,
     494,     6,     3,   360,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,   536,   540,     4,     4,     4,     3,
       8,     4,     4,     4,     3,     8,   549,   551,     3,     8,
       4,   558,     4,   561,     3,     8,     8,   606,     3,     6,
     197,   230,   231,   461,     6,     3,   477,     6,     3,   518,
       8,     6,     4,     4,     4,     4,   198,   200,   198,   200,
     198,     4,   198,   198,     4,     4,     4,   198,   198,   200,
     198,   297,   296,   294,   387,   383,   422,   418,   446,   442,
     232,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   257,   258,   259,   260,   263,   265,
     267,   268,   270,   272,   308,   379,   391,   393,   395,   397,
     399,   403,   410,   411,   438,   468,   470,   514,   408,   337,
     343,     4,   331,   109,   110,   232,   308,   438,   468,   470,
     524,   525,   526,   527,   528,   530,   522,   497,   493,   363,
     359,   198,   198,   198,   198,   198,   198,   372,     4,     4,
     198,   198,   198,   534,   200,   198,   198,   351,     4,     4,
     547,   200,     4,   198,     4,   555,   175,   177,   178,   232,
     308,   468,   470,   607,   608,   609,   610,   612,   605,     6,
       3,   464,   460,   480,   476,     4,    22,    23,    24,    25,
     300,   197,   197,   197,   197,   197,   197,   197,     8,     8,
       8,     8,     3,     8,   197,   529,     4,     8,     3,     8,
       8,   132,   133,   134,   537,   197,   197,   197,   197,   217,
     613,     4,   611,     3,     8,   197,     8,     8,   197,   411,
       4,   200,   526,     4,   198,     4,   608,   197,     5,   197,
       7,   614,   615,   616,     3,     6,   176,   179,   180,   181,
     182,   617,   618,   619,   621,   622,   623,   624,   615,   620,
       4,     4,     4,   625,     3,     8,     4,   200,   198,   198,
       4,   618,   197,   197
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
     266,   265,   267,   269,   268,   271,   270,   272,   273,   274,
     276,   275,   278,   277,   280,   279,   281,   281,   282,   282,
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
     388,   388,   388,   388,   388,   388,   388,   388,   388,   390,
     389,   392,   391,   394,   393,   396,   395,   398,   397,   400,
     399,   401,   401,   401,   401,   402,   403,   405,   404,   406,
     406,   407,   407,   409,   408,   410,   410,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   413,   412,   415,   414,   416,   416,   417,
     417,   419,   418,   421,   420,   422,   422,   423,   423,   424,
     424,   424,   424,   424,   424,   424,   424,   424,   424,   425,
     426,   427,   429,   428,   431,   430,   433,   432,   434,   436,
     435,   437,   439,   438,   440,   440,   441,   441,   443,   442,
     445,   444,   446,   446,   447,   447,   448,   448,   448,   448,
     448,   448,   448,   448,   448,   449,   451,   450,   452,   453,
     454,   455,   457,   456,   458,   458,   459,   459,   461,   460,
     463,   462,   464,   464,   465,   465,   465,   465,   465,   465,
     465,   467,   466,   469,   468,   471,   470,   473,   472,   474,
     474,   475,   475,   477,   476,   479,   478,   480,   480,   481,
     481,   481,   481,   481,   481,   481,   481,   481,   481,   481,
     483,   482,   484,   486,   485,   487,   488,   490,   489,   491,
     491,   492,   492,   494,   493,   496,   495,   497,   497,   498,
     498,   499,   499,   499,   499,   499,   499,   499,   499,   499,
     499,   499,   501,   500,   503,   502,   505,   504,   507,   506,
     509,   508,   511,   510,   513,   512,   515,   514,   516,   516,
     518,   517,   520,   519,   521,   521,   523,   522,   524,   524,
     525,   525,   526,   526,   526,   526,   526,   526,   526,   527,
     529,   528,   530,   532,   531,   533,   533,   534,   534,   534,
     534,   534,   534,   534,   534,   534,   536,   535,   537,   537,
     537,   538,   540,   539,   541,   542,   543,   545,   544,   546,
     546,   547,   547,   547,   547,   547,   549,   548,   551,   550,
     553,   552,   554,   554,   555,   555,   555,   555,   555,   555,
     556,   558,   557,   559,   561,   560,   563,   562,   565,   564,
     566,   566,   567,   567,   567,   567,   567,   567,   567,   567,
     567,   567,   567,   567,   567,   567,   567,   567,   567,   567,
     568,   570,   569,   572,   571,   573,   575,   574,   576,   577,
     579,   578,   580,   580,   582,   581,   583,   584,   586,   585,
     588,   587,   590,   589,   592,   591,   594,   593,   596,   595,
     597,   597,   598,   598,   600,   599,   601,   603,   602,   604,
     604,   606,   605,   607,   607,   608,   608,   608,   608,   608,
     608,   608,   609,   611,   610,   613,   612,   614,   614,   616,
     615,   617,   617,   618,   618,   618,   618,   618,   620,   619,
     621,   622,   623,   625,   624
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
       0,     4,     3,     0,     4,     0,     4,     3,     3,     3,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     1,
       0,     4,     0,     6,     1,     3,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     3,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     0,     6,     3,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     0,     4
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
  "t2_percent", "cache_threshold", "cache_max_age",
  "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_update_on_renew", "hostname_char_set", "$@25",
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
     661,   661,   670,   676,   676,   685,   685,   694,   700,   706,
     712,   712,   721,   721,   733,   733,   742,   743,   746,   747,
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
    1383,  1384,  1385,  1386,  1387,  1388,  1389,  1390,  1391,  1394,
    1394,  1403,  1403,  1412,  1412,  1421,  1421,  1430,  1430,  1441,
    1441,  1449,  1450,  1451,  1452,  1455,  1461,  1469,  1469,  1481,
    1482,  1486,  1487,  1490,  1490,  1498,  1499,  1502,  1503,  1504,
    1505,  1506,  1507,  1508,  1509,  1510,  1511,  1512,  1513,  1514,
    1515,  1516,  1517,  1518,  1519,  1520,  1521,  1522,  1523,  1524,
    1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,
    1535,  1536,  1537,  1544,  1544,  1558,  1558,  1567,  1568,  1571,
    1572,  1577,  1577,  1592,  1592,  1606,  1607,  1610,  1611,  1614,
    1615,  1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1626,
    1628,  1634,  1636,  1636,  1645,  1645,  1654,  1654,  1663,  1665,
    1665,  1674,  1684,  1684,  1697,  1698,  1703,  1704,  1709,  1709,
    1721,  1721,  1733,  1734,  1739,  1740,  1745,  1746,  1747,  1748,
    1749,  1750,  1751,  1752,  1753,  1756,  1758,  1758,  1767,  1769,
    1771,  1777,  1786,  1786,  1799,  1800,  1803,  1804,  1807,  1807,
    1817,  1817,  1827,  1828,  1831,  1832,  1833,  1834,  1835,  1836,
    1837,  1840,  1840,  1849,  1849,  1874,  1874,  1904,  1904,  1917,
    1918,  1921,  1922,  1925,  1925,  1937,  1937,  1949,  1950,  1953,
    1954,  1955,  1956,  1957,  1958,  1959,  1960,  1961,  1962,  1963,
    1966,  1966,  1975,  1981,  1981,  1990,  1996,  2005,  2005,  2016,
    2017,  2020,  2021,  2024,  2024,  2033,  2033,  2042,  2043,  2046,
    2047,  2051,  2052,  2053,  2054,  2055,  2056,  2057,  2058,  2059,
    2060,  2061,  2064,  2064,  2075,  2075,  2086,  2086,  2095,  2095,
    2104,  2104,  2113,  2113,  2122,  2122,  2136,  2136,  2147,  2148,
    2151,  2151,  2163,  2163,  2174,  2175,  2178,  2178,  2188,  2189,
    2192,  2193,  2196,  2197,  2198,  2199,  2200,  2201,  2202,  2205,
    2207,  2207,  2216,  2225,  2225,  2238,  2239,  2242,  2243,  2244,
    2245,  2246,  2247,  2248,  2249,  2250,  2253,  2253,  2261,  2262,
    2263,  2266,  2272,  2272,  2281,  2287,  2295,  2303,  2303,  2314,
    2315,  2318,  2319,  2320,  2321,  2322,  2325,  2325,  2334,  2334,
    2346,  2346,  2359,  2360,  2363,  2364,  2365,  2366,  2367,  2368,
    2371,  2377,  2377,  2386,  2392,  2392,  2402,  2402,  2415,  2415,
    2425,  2426,  2429,  2430,  2431,  2432,  2433,  2434,  2435,  2436,
    2437,  2438,  2439,  2440,  2441,  2442,  2443,  2444,  2445,  2446,
    2449,  2456,  2456,  2465,  2465,  2474,  2480,  2480,  2489,  2495,
    2501,  2501,  2510,  2511,  2514,  2514,  2524,  2531,  2538,  2538,
    2547,  2547,  2557,  2557,  2567,  2567,  2579,  2579,  2591,  2591,
    2601,  2602,  2606,  2607,  2610,  2610,  2621,  2629,  2629,  2642,
    2643,  2647,  2647,  2655,  2656,  2659,  2660,  2661,  2662,  2663,
    2664,  2665,  2668,  2674,  2674,  2683,  2683,  2694,  2695,  2698,
    2698,  2706,  2707,  2710,  2711,  2712,  2713,  2714,  2717,  2717,
    2726,  2732,  2738,  2744,  2744
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
#line 5785 "dhcp6_parser.cc"

#line 2753 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
