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
#line 278 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 400 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 278 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 406 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 278 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 412 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 278 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 418 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 278 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 424 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 278 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 430 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 278 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 436 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 278 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 442 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 278 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 448 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_duid_type: // duid_type
#line 278 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 454 "dhcp6_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 278 "dhcp6_parser.yy"
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
#line 287 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 739 "dhcp6_parser.cc"
    break;

  case 4: // $@2: %empty
#line 288 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 745 "dhcp6_parser.cc"
    break;

  case 6: // $@3: %empty
#line 289 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 751 "dhcp6_parser.cc"
    break;

  case 8: // $@4: %empty
#line 290 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 757 "dhcp6_parser.cc"
    break;

  case 10: // $@5: %empty
#line 291 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 763 "dhcp6_parser.cc"
    break;

  case 12: // $@6: %empty
#line 292 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 769 "dhcp6_parser.cc"
    break;

  case 14: // $@7: %empty
#line 293 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 775 "dhcp6_parser.cc"
    break;

  case 16: // $@8: %empty
#line 294 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 781 "dhcp6_parser.cc"
    break;

  case 18: // $@9: %empty
#line 295 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 787 "dhcp6_parser.cc"
    break;

  case 20: // $@10: %empty
#line 296 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 793 "dhcp6_parser.cc"
    break;

  case 22: // $@11: %empty
#line 297 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 799 "dhcp6_parser.cc"
    break;

  case 24: // $@12: %empty
#line 298 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 805 "dhcp6_parser.cc"
    break;

  case 26: // $@13: %empty
#line 299 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 811 "dhcp6_parser.cc"
    break;

  case 28: // $@14: %empty
#line 300 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 817 "dhcp6_parser.cc"
    break;

  case 30: // value: "integer"
#line 308 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc"
    break;

  case 31: // value: "floating point"
#line 309 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc"
    break;

  case 32: // value: "boolean"
#line 310 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc"
    break;

  case 33: // value: "constant string"
#line 311 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc"
    break;

  case 34: // value: "null"
#line 312 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 847 "dhcp6_parser.cc"
    break;

  case 35: // value: map2
#line 313 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc"
    break;

  case 36: // value: list_generic
#line 314 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 859 "dhcp6_parser.cc"
    break;

  case 37: // sub_json: value
#line 317 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 868 "dhcp6_parser.cc"
    break;

  case 38: // $@15: %empty
#line 322 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 879 "dhcp6_parser.cc"
    break;

  case 39: // map2: "{" $@15 map_content "}"
#line 327 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 889 "dhcp6_parser.cc"
    break;

  case 40: // map_value: map2
#line 333 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp6_parser.cc"
    break;

  case 43: // not_empty_map: "constant string" ":" value
#line 340 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 905 "dhcp6_parser.cc"
    break;

  case 44: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 345 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp6_parser.cc"
    break;

  case 45: // $@16: %empty
#line 353 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 925 "dhcp6_parser.cc"
    break;

  case 46: // list_generic: "[" $@16 list_content "]"
#line 356 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 933 "dhcp6_parser.cc"
    break;

  case 49: // not_empty_list: value
#line 364 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 942 "dhcp6_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list "," value
#line 368 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp6_parser.cc"
    break;

  case 51: // $@17: %empty
#line 375 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 959 "dhcp6_parser.cc"
    break;

  case 52: // list_strings: "[" $@17 list_strings_content "]"
#line 377 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 968 "dhcp6_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 386 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 977 "dhcp6_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 390 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 986 "dhcp6_parser.cc"
    break;

  case 57: // unknown_map_entry: "constant string" ":"
#line 401 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 997 "dhcp6_parser.cc"
    break;

  case 58: // $@18: %empty
#line 410 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1008 "dhcp6_parser.cc"
    break;

  case 59: // syntax_map: "{" $@18 global_object "}"
#line 415 "dhcp6_parser.yy"
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
#line 425 "dhcp6_parser.yy"
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
#line 434 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1046 "dhcp6_parser.cc"
    break;

  case 62: // $@20: %empty
#line 442 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1056 "dhcp6_parser.cc"
    break;

  case 63: // sub_dhcp6: "{" $@20 global_params "}"
#line 446 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1065 "dhcp6_parser.cc"
    break;

  case 123: // $@21: %empty
#line 516 "dhcp6_parser.yy"
                               {
    ctx.unique("data-directory", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1074 "dhcp6_parser.cc"
    break;

  case 124: // data_directory: "data-directory" $@21 ":" "constant string"
#line 519 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1084 "dhcp6_parser.cc"
    break;

  case 125: // preferred_lifetime: "preferred-lifetime" ":" "integer"
#line 525 "dhcp6_parser.yy"
                                                     {
    ctx.unique("preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1094 "dhcp6_parser.cc"
    break;

  case 126: // min_preferred_lifetime: "min-preferred-lifetime" ":" "integer"
#line 531 "dhcp6_parser.yy"
                                                             {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 127: // max_preferred_lifetime: "max-preferred-lifetime" ":" "integer"
#line 537 "dhcp6_parser.yy"
                                                             {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1114 "dhcp6_parser.cc"
    break;

  case 128: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 543 "dhcp6_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1124 "dhcp6_parser.cc"
    break;

  case 129: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 549 "dhcp6_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1134 "dhcp6_parser.cc"
    break;

  case 130: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 555 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1144 "dhcp6_parser.cc"
    break;

  case 131: // renew_timer: "renew-timer" ":" "integer"
#line 561 "dhcp6_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1154 "dhcp6_parser.cc"
    break;

  case 132: // rebind_timer: "rebind-timer" ":" "integer"
#line 567 "dhcp6_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1164 "dhcp6_parser.cc"
    break;

  case 133: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 573 "dhcp6_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1174 "dhcp6_parser.cc"
    break;

  case 134: // t1_percent: "t1-percent" ":" "floating point"
#line 579 "dhcp6_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1184 "dhcp6_parser.cc"
    break;

  case 135: // t2_percent: "t2-percent" ":" "floating point"
#line 585 "dhcp6_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1194 "dhcp6_parser.cc"
    break;

  case 136: // cache_threshold: "cache-threshold" ":" "floating point"
#line 591 "dhcp6_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1204 "dhcp6_parser.cc"
    break;

  case 137: // cache_max_age: "cache-max-age" ":" "integer"
#line 597 "dhcp6_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1214 "dhcp6_parser.cc"
    break;

  case 138: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 603 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 139: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 609 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1234 "dhcp6_parser.cc"
    break;

  case 140: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 615 "dhcp6_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1244 "dhcp6_parser.cc"
    break;

  case 141: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 621 "dhcp6_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1254 "dhcp6_parser.cc"
    break;

  case 142: // $@22: %empty
#line 627 "dhcp6_parser.yy"
                                                   {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1263 "dhcp6_parser.cc"
    break;

  case 143: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 630 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1272 "dhcp6_parser.cc"
    break;

  case 144: // ddns_replace_client_name_value: "when-present"
#line 636 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1280 "dhcp6_parser.cc"
    break;

  case 145: // ddns_replace_client_name_value: "never"
#line 639 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1288 "dhcp6_parser.cc"
    break;

  case 146: // ddns_replace_client_name_value: "always"
#line 642 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1296 "dhcp6_parser.cc"
    break;

  case 147: // ddns_replace_client_name_value: "when-not-present"
#line 645 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1304 "dhcp6_parser.cc"
    break;

  case 148: // ddns_replace_client_name_value: "boolean"
#line 648 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1313 "dhcp6_parser.cc"
    break;

  case 149: // $@23: %empty
#line 654 "dhcp6_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp6_parser.cc"
    break;

  case 150: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 657 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1332 "dhcp6_parser.cc"
    break;

  case 151: // $@24: %empty
#line 663 "dhcp6_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp6_parser.cc"
    break;

  case 152: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 666 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1351 "dhcp6_parser.cc"
    break;

  case 153: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 672 "dhcp6_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1361 "dhcp6_parser.cc"
    break;

  case 154: // $@25: %empty
#line 678 "dhcp6_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1370 "dhcp6_parser.cc"
    break;

  case 155: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 681 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1380 "dhcp6_parser.cc"
    break;

  case 156: // $@26: %empty
#line 687 "dhcp6_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1389 "dhcp6_parser.cc"
    break;

  case 157: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 690 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 158: // store_extended_info: "store-extended-info" ":" "boolean"
#line 696 "dhcp6_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1409 "dhcp6_parser.cc"
    break;

  case 159: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 702 "dhcp6_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1419 "dhcp6_parser.cc"
    break;

  case 160: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 708 "dhcp6_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1429 "dhcp6_parser.cc"
    break;

  case 161: // $@27: %empty
#line 714 "dhcp6_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1438 "dhcp6_parser.cc"
    break;

  case 162: // server_tag: "server-tag" $@27 ":" "constant string"
#line 717 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1448 "dhcp6_parser.cc"
    break;

  case 163: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 723 "dhcp6_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1458 "dhcp6_parser.cc"
    break;

  case 164: // $@28: %empty
#line 729 "dhcp6_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1470 "dhcp6_parser.cc"
    break;

  case 165: // interfaces_config: "interfaces-config" $@28 ":" "{" interfaces_config_params "}"
#line 735 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1480 "dhcp6_parser.cc"
    break;

  case 166: // $@29: %empty
#line 741 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1490 "dhcp6_parser.cc"
    break;

  case 167: // sub_interfaces6: "{" $@29 interfaces_config_params "}"
#line 745 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1499 "dhcp6_parser.cc"
    break;

  case 175: // $@30: %empty
#line 761 "dhcp6_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1511 "dhcp6_parser.cc"
    break;

  case 176: // interfaces_list: "interfaces" $@30 ":" list_strings
#line 767 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1520 "dhcp6_parser.cc"
    break;

  case 177: // re_detect: "re-detect" ":" "boolean"
#line 772 "dhcp6_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1530 "dhcp6_parser.cc"
    break;

  case 178: // $@31: %empty
#line 778 "dhcp6_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1542 "dhcp6_parser.cc"
    break;

  case 179: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 784 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1553 "dhcp6_parser.cc"
    break;

  case 180: // $@32: %empty
#line 791 "dhcp6_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1565 "dhcp6_parser.cc"
    break;

  case 181: // hosts_database: "hosts-database" $@32 ":" "{" database_map_params "}"
#line 797 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1576 "dhcp6_parser.cc"
    break;

  case 182: // $@33: %empty
#line 804 "dhcp6_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1588 "dhcp6_parser.cc"
    break;

  case 183: // hosts_databases: "hosts-databases" $@33 ":" "[" database_list "]"
#line 810 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1597 "dhcp6_parser.cc"
    break;

  case 188: // $@34: %empty
#line 823 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1607 "dhcp6_parser.cc"
    break;

  case 189: // database: "{" $@34 database_map_params "}"
#line 827 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1617 "dhcp6_parser.cc"
    break;

  case 213: // $@35: %empty
#line 860 "dhcp6_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1626 "dhcp6_parser.cc"
    break;

  case 214: // database_type: "type" $@35 ":" db_type
#line 863 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1635 "dhcp6_parser.cc"
    break;

  case 215: // db_type: "memfile"
#line 868 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1641 "dhcp6_parser.cc"
    break;

  case 216: // db_type: "mysql"
#line 869 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1647 "dhcp6_parser.cc"
    break;

  case 217: // db_type: "postgresql"
#line 870 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1653 "dhcp6_parser.cc"
    break;

  case 218: // db_type: "cql"
#line 871 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1659 "dhcp6_parser.cc"
    break;

  case 219: // $@36: %empty
#line 874 "dhcp6_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1668 "dhcp6_parser.cc"
    break;

  case 220: // user: "user" $@36 ":" "constant string"
#line 877 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1678 "dhcp6_parser.cc"
    break;

  case 221: // $@37: %empty
#line 883 "dhcp6_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1687 "dhcp6_parser.cc"
    break;

  case 222: // password: "password" $@37 ":" "constant string"
#line 886 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1697 "dhcp6_parser.cc"
    break;

  case 223: // $@38: %empty
#line 892 "dhcp6_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1706 "dhcp6_parser.cc"
    break;

  case 224: // host: "host" $@38 ":" "constant string"
#line 895 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1716 "dhcp6_parser.cc"
    break;

  case 225: // port: "port" ":" "integer"
#line 901 "dhcp6_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1726 "dhcp6_parser.cc"
    break;

  case 226: // $@39: %empty
#line 907 "dhcp6_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1735 "dhcp6_parser.cc"
    break;

  case 227: // name: "name" $@39 ":" "constant string"
#line 910 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1745 "dhcp6_parser.cc"
    break;

  case 228: // persist: "persist" ":" "boolean"
#line 916 "dhcp6_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 229: // lfc_interval: "lfc-interval" ":" "integer"
#line 922 "dhcp6_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1765 "dhcp6_parser.cc"
    break;

  case 230: // readonly: "readonly" ":" "boolean"
#line 928 "dhcp6_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1775 "dhcp6_parser.cc"
    break;

  case 231: // connect_timeout: "connect-timeout" ":" "integer"
#line 934 "dhcp6_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1785 "dhcp6_parser.cc"
    break;

  case 232: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 940 "dhcp6_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1795 "dhcp6_parser.cc"
    break;

  case 233: // max_row_errors: "max-row-errors" ":" "integer"
#line 946 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1805 "dhcp6_parser.cc"
    break;

  case 234: // request_timeout: "request-timeout" ":" "integer"
#line 952 "dhcp6_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1815 "dhcp6_parser.cc"
    break;

  case 235: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 958 "dhcp6_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 236: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 964 "dhcp6_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1835 "dhcp6_parser.cc"
    break;

  case 237: // $@40: %empty
#line 970 "dhcp6_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1844 "dhcp6_parser.cc"
    break;

  case 238: // contact_points: "contact-points" $@40 ":" "constant string"
#line 973 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1854 "dhcp6_parser.cc"
    break;

  case 239: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 979 "dhcp6_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1864 "dhcp6_parser.cc"
    break;

  case 240: // $@41: %empty
#line 985 "dhcp6_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1873 "dhcp6_parser.cc"
    break;

  case 241: // keyspace: "keyspace" $@41 ":" "constant string"
#line 988 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc"
    break;

  case 242: // $@42: %empty
#line 994 "dhcp6_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1892 "dhcp6_parser.cc"
    break;

  case 243: // consistency: "consistency" $@42 ":" "constant string"
#line 997 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1902 "dhcp6_parser.cc"
    break;

  case 244: // $@43: %empty
#line 1003 "dhcp6_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1911 "dhcp6_parser.cc"
    break;

  case 245: // serial_consistency: "serial-consistency" $@43 ":" "constant string"
#line 1006 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1921 "dhcp6_parser.cc"
    break;

  case 246: // $@44: %empty
#line 1012 "dhcp6_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1933 "dhcp6_parser.cc"
    break;

  case 247: // sanity_checks: "sanity-checks" $@44 ":" "{" sanity_checks_params "}"
#line 1018 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1942 "dhcp6_parser.cc"
    break;

  case 251: // $@45: %empty
#line 1028 "dhcp6_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1951 "dhcp6_parser.cc"
    break;

  case 252: // lease_checks: "lease-checks" $@45 ":" "constant string"
#line 1031 "dhcp6_parser.yy"
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

  case 253: // $@46: %empty
#line 1047 "dhcp6_parser.yy"
                         {
    ctx.unique("mac-sources", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 254: // mac_sources: "mac-sources" $@46 ":" "[" mac_sources_list "]"
#line 1053 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1992 "dhcp6_parser.cc"
    break;

  case 259: // duid_id: "duid"
#line 1066 "dhcp6_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2001 "dhcp6_parser.cc"
    break;

  case 260: // string_id: "constant string"
#line 1071 "dhcp6_parser.yy"
                   {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2010 "dhcp6_parser.cc"
    break;

  case 261: // $@47: %empty
#line 1076 "dhcp6_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2022 "dhcp6_parser.cc"
    break;

  case 262: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1082 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2031 "dhcp6_parser.cc"
    break;

  case 268: // hw_address_id: "hw-address"
#line 1096 "dhcp6_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2040 "dhcp6_parser.cc"
    break;

  case 269: // flex_id: "flex-id"
#line 1101 "dhcp6_parser.yy"
                  {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2049 "dhcp6_parser.cc"
    break;

  case 270: // $@48: %empty
#line 1108 "dhcp6_parser.yy"
                                               {
    ctx.unique("relay-supplied-options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2061 "dhcp6_parser.cc"
    break;

  case 271: // relay_supplied_options: "relay-supplied-options" $@48 ":" "[" list_content "]"
#line 1114 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2070 "dhcp6_parser.cc"
    break;

  case 272: // $@49: %empty
#line 1121 "dhcp6_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2082 "dhcp6_parser.cc"
    break;

  case 273: // dhcp_multi_threading: "multi-threading" $@49 ":" "{" multi_threading_params "}"
#line 1127 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 282: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1146 "dhcp6_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2103 "dhcp6_parser.cc"
    break;

  case 283: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1152 "dhcp6_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2113 "dhcp6_parser.cc"
    break;

  case 284: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1158 "dhcp6_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2123 "dhcp6_parser.cc"
    break;

  case 285: // $@50: %empty
#line 1164 "dhcp6_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2135 "dhcp6_parser.cc"
    break;

  case 286: // hooks_libraries: "hooks-libraries" $@50 ":" "[" hooks_libraries_list "]"
#line 1170 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2144 "dhcp6_parser.cc"
    break;

  case 291: // $@51: %empty
#line 1183 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2154 "dhcp6_parser.cc"
    break;

  case 292: // hooks_library: "{" $@51 hooks_params "}"
#line 1187 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 293: // $@52: %empty
#line 1193 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2174 "dhcp6_parser.cc"
    break;

  case 294: // sub_hooks_library: "{" $@52 hooks_params "}"
#line 1197 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2184 "dhcp6_parser.cc"
    break;

  case 300: // $@53: %empty
#line 1212 "dhcp6_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2193 "dhcp6_parser.cc"
    break;

  case 301: // library: "library" $@53 ":" "constant string"
#line 1215 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2203 "dhcp6_parser.cc"
    break;

  case 302: // $@54: %empty
#line 1221 "dhcp6_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2212 "dhcp6_parser.cc"
    break;

  case 303: // parameters: "parameters" $@54 ":" map_value
#line 1224 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 304: // $@55: %empty
#line 1230 "dhcp6_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2233 "dhcp6_parser.cc"
    break;

  case 305: // expired_leases_processing: "expired-leases-processing" $@55 ":" "{" expired_leases_params "}"
#line 1236 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2243 "dhcp6_parser.cc"
    break;

  case 314: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1254 "dhcp6_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2253 "dhcp6_parser.cc"
    break;

  case 315: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1260 "dhcp6_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2263 "dhcp6_parser.cc"
    break;

  case 316: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1266 "dhcp6_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2273 "dhcp6_parser.cc"
    break;

  case 317: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1272 "dhcp6_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2283 "dhcp6_parser.cc"
    break;

  case 318: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1278 "dhcp6_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2293 "dhcp6_parser.cc"
    break;

  case 319: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1284 "dhcp6_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2303 "dhcp6_parser.cc"
    break;

  case 320: // $@56: %empty
#line 1293 "dhcp6_parser.yy"
                      {
    ctx.unique("subnet6", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2315 "dhcp6_parser.cc"
    break;

  case 321: // subnet6_list: "subnet6" $@56 ":" "[" subnet6_list_content "]"
#line 1299 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2324 "dhcp6_parser.cc"
    break;

  case 326: // $@57: %empty
#line 1319 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2334 "dhcp6_parser.cc"
    break;

  case 327: // subnet6: "{" $@57 subnet6_params "}"
#line 1323 "dhcp6_parser.yy"
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

  case 328: // $@58: %empty
#line 1345 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2370 "dhcp6_parser.cc"
    break;

  case 329: // sub_subnet6: "{" $@58 subnet6_params "}"
#line 1349 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2380 "dhcp6_parser.cc"
    break;

  case 371: // $@59: %empty
#line 1402 "dhcp6_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2389 "dhcp6_parser.cc"
    break;

  case 372: // subnet: "subnet" $@59 ":" "constant string"
#line 1405 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2399 "dhcp6_parser.cc"
    break;

  case 373: // $@60: %empty
#line 1411 "dhcp6_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2408 "dhcp6_parser.cc"
    break;

  case 374: // interface: "interface" $@60 ":" "constant string"
#line 1414 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2418 "dhcp6_parser.cc"
    break;

  case 375: // $@61: %empty
#line 1420 "dhcp6_parser.yy"
                           {
    ctx.unique("interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2427 "dhcp6_parser.cc"
    break;

  case 376: // interface_id: "interface-id" $@61 ":" "constant string"
#line 1423 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2437 "dhcp6_parser.cc"
    break;

  case 377: // $@62: %empty
#line 1429 "dhcp6_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2446 "dhcp6_parser.cc"
    break;

  case 378: // client_class: "client-class" $@62 ":" "constant string"
#line 1432 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2456 "dhcp6_parser.cc"
    break;

  case 379: // $@63: %empty
#line 1438 "dhcp6_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2468 "dhcp6_parser.cc"
    break;

  case 380: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1444 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2477 "dhcp6_parser.cc"
    break;

  case 381: // $@64: %empty
#line 1449 "dhcp6_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2486 "dhcp6_parser.cc"
    break;

  case 382: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1452 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2495 "dhcp6_parser.cc"
    break;

  case 383: // hr_mode: "disabled"
#line 1457 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2501 "dhcp6_parser.cc"
    break;

  case 384: // hr_mode: "out-of-pool"
#line 1458 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2507 "dhcp6_parser.cc"
    break;

  case 385: // hr_mode: "global"
#line 1459 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2513 "dhcp6_parser.cc"
    break;

  case 386: // hr_mode: "all"
#line 1460 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2519 "dhcp6_parser.cc"
    break;

  case 387: // id: "id" ":" "integer"
#line 1463 "dhcp6_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2529 "dhcp6_parser.cc"
    break;

  case 388: // rapid_commit: "rapid-commit" ":" "boolean"
#line 1469 "dhcp6_parser.yy"
                                         {
    ctx.unique("rapid-commit", ctx.loc2pos(yystack_[2].location));
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2539 "dhcp6_parser.cc"
    break;

  case 389: // $@65: %empty
#line 1477 "dhcp6_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2551 "dhcp6_parser.cc"
    break;

  case 390: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1483 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2560 "dhcp6_parser.cc"
    break;

  case 395: // $@66: %empty
#line 1498 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2570 "dhcp6_parser.cc"
    break;

  case 396: // shared_network: "{" $@66 shared_network_params "}"
#line 1502 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2578 "dhcp6_parser.cc"
    break;

  case 435: // $@67: %empty
#line 1552 "dhcp6_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2590 "dhcp6_parser.cc"
    break;

  case 436: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1558 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2599 "dhcp6_parser.cc"
    break;

  case 437: // $@68: %empty
#line 1566 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2608 "dhcp6_parser.cc"
    break;

  case 438: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1569 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2616 "dhcp6_parser.cc"
    break;

  case 443: // $@69: %empty
#line 1585 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2626 "dhcp6_parser.cc"
    break;

  case 444: // option_def_entry: "{" $@69 option_def_params "}"
#line 1589 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 445: // $@70: %empty
#line 1600 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2648 "dhcp6_parser.cc"
    break;

  case 446: // sub_option_def: "{" $@70 option_def_params "}"
#line 1604 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2660 "dhcp6_parser.cc"
    break;

  case 462: // code: "code" ":" "integer"
#line 1636 "dhcp6_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2670 "dhcp6_parser.cc"
    break;

  case 464: // $@71: %empty
#line 1644 "dhcp6_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2679 "dhcp6_parser.cc"
    break;

  case 465: // option_def_type: "type" $@71 ":" "constant string"
#line 1647 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2689 "dhcp6_parser.cc"
    break;

  case 466: // $@72: %empty
#line 1653 "dhcp6_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2698 "dhcp6_parser.cc"
    break;

  case 467: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1656 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2708 "dhcp6_parser.cc"
    break;

  case 468: // $@73: %empty
#line 1662 "dhcp6_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2717 "dhcp6_parser.cc"
    break;

  case 469: // space: "space" $@73 ":" "constant string"
#line 1665 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2727 "dhcp6_parser.cc"
    break;

  case 471: // $@74: %empty
#line 1673 "dhcp6_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2736 "dhcp6_parser.cc"
    break;

  case 472: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1676 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2746 "dhcp6_parser.cc"
    break;

  case 473: // option_def_array: "array" ":" "boolean"
#line 1682 "dhcp6_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2756 "dhcp6_parser.cc"
    break;

  case 474: // $@75: %empty
#line 1692 "dhcp6_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2768 "dhcp6_parser.cc"
    break;

  case 475: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1698 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2777 "dhcp6_parser.cc"
    break;

  case 480: // $@76: %empty
#line 1717 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2787 "dhcp6_parser.cc"
    break;

  case 481: // option_data_entry: "{" $@76 option_data_params "}"
#line 1721 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2796 "dhcp6_parser.cc"
    break;

  case 482: // $@77: %empty
#line 1729 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2806 "dhcp6_parser.cc"
    break;

  case 483: // sub_option_data: "{" $@77 option_data_params "}"
#line 1733 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2815 "dhcp6_parser.cc"
    break;

  case 498: // $@78: %empty
#line 1766 "dhcp6_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2824 "dhcp6_parser.cc"
    break;

  case 499: // option_data_data: "data" $@78 ":" "constant string"
#line 1769 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2834 "dhcp6_parser.cc"
    break;

  case 502: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1779 "dhcp6_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2844 "dhcp6_parser.cc"
    break;

  case 503: // option_data_always_send: "always-send" ":" "boolean"
#line 1785 "dhcp6_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2854 "dhcp6_parser.cc"
    break;

  case 504: // $@79: %empty
#line 1794 "dhcp6_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2866 "dhcp6_parser.cc"
    break;

  case 505: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1800 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 510: // $@80: %empty
#line 1815 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 511: // pool_list_entry: "{" $@80 pool_params "}"
#line 1819 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2895 "dhcp6_parser.cc"
    break;

  case 512: // $@81: %empty
#line 1825 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 513: // sub_pool6: "{" $@81 pool_params "}"
#line 1829 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2915 "dhcp6_parser.cc"
    break;

  case 523: // $@82: %empty
#line 1848 "dhcp6_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2924 "dhcp6_parser.cc"
    break;

  case 524: // pool_entry: "pool" $@82 ":" "constant string"
#line 1851 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2934 "dhcp6_parser.cc"
    break;

  case 525: // $@83: %empty
#line 1857 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2942 "dhcp6_parser.cc"
    break;

  case 526: // user_context: "user-context" $@83 ":" map_value
#line 1859 "dhcp6_parser.yy"
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
#line 2969 "dhcp6_parser.cc"
    break;

  case 527: // $@84: %empty
#line 1882 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2977 "dhcp6_parser.cc"
    break;

  case 528: // comment: "comment" $@84 ":" "constant string"
#line 1884 "dhcp6_parser.yy"
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
#line 3006 "dhcp6_parser.cc"
    break;

  case 529: // $@85: %empty
#line 1912 "dhcp6_parser.yy"
                        {
    ctx.unique("pd-pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 3018 "dhcp6_parser.cc"
    break;

  case 530: // pd_pools_list: "pd-pools" $@85 ":" "[" pd_pools_list_content "]"
#line 1918 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3027 "dhcp6_parser.cc"
    break;

  case 535: // $@86: %empty
#line 1933 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3037 "dhcp6_parser.cc"
    break;

  case 536: // pd_pool_entry: "{" $@86 pd_pool_params "}"
#line 1937 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3049 "dhcp6_parser.cc"
    break;

  case 537: // $@87: %empty
#line 1945 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3059 "dhcp6_parser.cc"
    break;

  case 538: // sub_pd_pool: "{" $@87 pd_pool_params "}"
#line 1949 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3071 "dhcp6_parser.cc"
    break;

  case 552: // $@88: %empty
#line 1974 "dhcp6_parser.yy"
                  {
    ctx.unique("prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3080 "dhcp6_parser.cc"
    break;

  case 553: // pd_prefix: "prefix" $@88 ":" "constant string"
#line 1977 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 3090 "dhcp6_parser.cc"
    break;

  case 554: // pd_prefix_len: "prefix-len" ":" "integer"
#line 1983 "dhcp6_parser.yy"
                                        {
    ctx.unique("prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 3100 "dhcp6_parser.cc"
    break;

  case 555: // $@89: %empty
#line 1989 "dhcp6_parser.yy"
                                 {
    ctx.unique("excluded-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3109 "dhcp6_parser.cc"
    break;

  case 556: // excluded_prefix: "excluded-prefix" $@89 ":" "constant string"
#line 1992 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 3119 "dhcp6_parser.cc"
    break;

  case 557: // excluded_prefix_len: "excluded-prefix-len" ":" "integer"
#line 1998 "dhcp6_parser.yy"
                                                       {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 3129 "dhcp6_parser.cc"
    break;

  case 558: // pd_delegated_len: "delegated-len" ":" "integer"
#line 2004 "dhcp6_parser.yy"
                                              {
    ctx.unique("delegated-len", ctx.loc2pos(yystack_[2].location));
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 3139 "dhcp6_parser.cc"
    break;

  case 559: // $@90: %empty
#line 2013 "dhcp6_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3151 "dhcp6_parser.cc"
    break;

  case 560: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2019 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3160 "dhcp6_parser.cc"
    break;

  case 565: // $@91: %empty
#line 2032 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3170 "dhcp6_parser.cc"
    break;

  case 566: // reservation: "{" $@91 reservation_params "}"
#line 2036 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 567: // $@92: %empty
#line 2041 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3189 "dhcp6_parser.cc"
    break;

  case 568: // sub_reservation: "{" $@92 reservation_params "}"
#line 2045 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3198 "dhcp6_parser.cc"
    break;

  case 584: // $@93: %empty
#line 2072 "dhcp6_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3210 "dhcp6_parser.cc"
    break;

  case 585: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2078 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3219 "dhcp6_parser.cc"
    break;

  case 586: // $@94: %empty
#line 2083 "dhcp6_parser.yy"
                   {
    ctx.unique("prefixes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3231 "dhcp6_parser.cc"
    break;

  case 587: // prefixes: "prefixes" $@94 ":" list_strings
#line 2089 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3240 "dhcp6_parser.cc"
    break;

  case 588: // $@95: %empty
#line 2094 "dhcp6_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3249 "dhcp6_parser.cc"
    break;

  case 589: // duid: "duid" $@95 ":" "constant string"
#line 2097 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3259 "dhcp6_parser.cc"
    break;

  case 590: // $@96: %empty
#line 2103 "dhcp6_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3268 "dhcp6_parser.cc"
    break;

  case 591: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2106 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3278 "dhcp6_parser.cc"
    break;

  case 592: // $@97: %empty
#line 2112 "dhcp6_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3287 "dhcp6_parser.cc"
    break;

  case 593: // hostname: "hostname" $@97 ":" "constant string"
#line 2115 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3297 "dhcp6_parser.cc"
    break;

  case 594: // $@98: %empty
#line 2121 "dhcp6_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3306 "dhcp6_parser.cc"
    break;

  case 595: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2124 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3316 "dhcp6_parser.cc"
    break;

  case 596: // $@99: %empty
#line 2130 "dhcp6_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3328 "dhcp6_parser.cc"
    break;

  case 597: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2136 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3337 "dhcp6_parser.cc"
    break;

  case 598: // $@100: %empty
#line 2144 "dhcp6_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3349 "dhcp6_parser.cc"
    break;

  case 599: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2150 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3358 "dhcp6_parser.cc"
    break;

  case 602: // $@101: %empty
#line 2159 "dhcp6_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3367 "dhcp6_parser.cc"
    break;

  case 603: // ip_address: "ip-address" $@101 ":" "constant string"
#line 2162 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3377 "dhcp6_parser.cc"
    break;

  case 604: // $@102: %empty
#line 2171 "dhcp6_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3389 "dhcp6_parser.cc"
    break;

  case 605: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2177 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3398 "dhcp6_parser.cc"
    break;

  case 608: // $@103: %empty
#line 2186 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3408 "dhcp6_parser.cc"
    break;

  case 609: // client_class_entry: "{" $@103 client_class_params "}"
#line 2190 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3418 "dhcp6_parser.cc"
    break;

  case 622: // $@104: %empty
#line 2215 "dhcp6_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3427 "dhcp6_parser.cc"
    break;

  case 623: // client_class_test: "test" $@104 ":" "constant string"
#line 2218 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3437 "dhcp6_parser.cc"
    break;

  case 624: // only_if_required: "only-if-required" ":" "boolean"
#line 2224 "dhcp6_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3447 "dhcp6_parser.cc"
    break;

  case 625: // $@105: %empty
#line 2233 "dhcp6_parser.yy"
                     {
    ctx.unique("server-id", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3459 "dhcp6_parser.cc"
    break;

  case 626: // server_id: "server-id" $@105 ":" "{" server_id_params "}"
#line 2239 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3470 "dhcp6_parser.cc"
    break;

  case 638: // $@106: %empty
#line 2261 "dhcp6_parser.yy"
                     {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DUID_TYPE);
}
#line 3479 "dhcp6_parser.cc"
    break;

  case 639: // server_id_type: "type" $@106 ":" duid_type
#line 2264 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3488 "dhcp6_parser.cc"
    break;

  case 640: // duid_type: "LLT"
#line 2269 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3494 "dhcp6_parser.cc"
    break;

  case 641: // duid_type: "EN"
#line 2270 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3500 "dhcp6_parser.cc"
    break;

  case 642: // duid_type: "LL"
#line 2271 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3506 "dhcp6_parser.cc"
    break;

  case 643: // htype: "htype" ":" "integer"
#line 2274 "dhcp6_parser.yy"
                           {
    ctx.unique("htype", ctx.loc2pos(yystack_[2].location));
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3516 "dhcp6_parser.cc"
    break;

  case 644: // $@107: %empty
#line 2280 "dhcp6_parser.yy"
                       {
    ctx.unique("identifier", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3525 "dhcp6_parser.cc"
    break;

  case 645: // identifier: "identifier" $@107 ":" "constant string"
#line 2283 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3535 "dhcp6_parser.cc"
    break;

  case 646: // time: "time" ":" "integer"
#line 2289 "dhcp6_parser.yy"
                         {
    ctx.unique("time", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3545 "dhcp6_parser.cc"
    break;

  case 647: // enterprise_id: "enterprise-id" ":" "integer"
#line 2295 "dhcp6_parser.yy"
                                           {
    ctx.unique("enterprise-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3555 "dhcp6_parser.cc"
    break;

  case 648: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2303 "dhcp6_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3565 "dhcp6_parser.cc"
    break;

  case 649: // $@108: %empty
#line 2311 "dhcp6_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3577 "dhcp6_parser.cc"
    break;

  case 650: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2317 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3586 "dhcp6_parser.cc"
    break;

  case 658: // $@109: %empty
#line 2333 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3595 "dhcp6_parser.cc"
    break;

  case 659: // socket_type: "socket-type" $@109 ":" "constant string"
#line 2336 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3605 "dhcp6_parser.cc"
    break;

  case 660: // $@110: %empty
#line 2342 "dhcp6_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3614 "dhcp6_parser.cc"
    break;

  case 661: // socket_name: "socket-name" $@110 ":" "constant string"
#line 2345 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3624 "dhcp6_parser.cc"
    break;

  case 662: // $@111: %empty
#line 2354 "dhcp6_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3636 "dhcp6_parser.cc"
    break;

  case 663: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2360 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3647 "dhcp6_parser.cc"
    break;

  case 672: // enable_queue: "enable-queue" ":" "boolean"
#line 2379 "dhcp6_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3657 "dhcp6_parser.cc"
    break;

  case 673: // $@112: %empty
#line 2385 "dhcp6_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3666 "dhcp6_parser.cc"
    break;

  case 674: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2388 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3676 "dhcp6_parser.cc"
    break;

  case 675: // capacity: "capacity" ":" "integer"
#line 2394 "dhcp6_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3686 "dhcp6_parser.cc"
    break;

  case 676: // $@113: %empty
#line 2400 "dhcp6_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3695 "dhcp6_parser.cc"
    break;

  case 677: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2403 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3704 "dhcp6_parser.cc"
    break;

  case 678: // $@114: %empty
#line 2410 "dhcp6_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3716 "dhcp6_parser.cc"
    break;

  case 679: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2416 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3727 "dhcp6_parser.cc"
    break;

  case 680: // $@115: %empty
#line 2423 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3737 "dhcp6_parser.cc"
    break;

  case 681: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2427 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3747 "dhcp6_parser.cc"
    break;

  case 702: // enable_updates: "enable-updates" ":" "boolean"
#line 2457 "dhcp6_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 703: // $@116: %empty
#line 2464 "dhcp6_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3766 "dhcp6_parser.cc"
    break;

  case 704: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2467 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3776 "dhcp6_parser.cc"
    break;

  case 705: // $@117: %empty
#line 2473 "dhcp6_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 706: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2476 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3795 "dhcp6_parser.cc"
    break;

  case 707: // server_port: "server-port" ":" "integer"
#line 2482 "dhcp6_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3805 "dhcp6_parser.cc"
    break;

  case 708: // $@118: %empty
#line 2488 "dhcp6_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 709: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2491 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 710: // sender_port: "sender-port" ":" "integer"
#line 2497 "dhcp6_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 711: // max_queue_size: "max-queue-size" ":" "integer"
#line 2503 "dhcp6_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3844 "dhcp6_parser.cc"
    break;

  case 712: // $@119: %empty
#line 2509 "dhcp6_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3853 "dhcp6_parser.cc"
    break;

  case 713: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2512 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3862 "dhcp6_parser.cc"
    break;

  case 714: // ncr_protocol_value: "UDP"
#line 2518 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3868 "dhcp6_parser.cc"
    break;

  case 715: // ncr_protocol_value: "TCP"
#line 2519 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3874 "dhcp6_parser.cc"
    break;

  case 716: // $@120: %empty
#line 2522 "dhcp6_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 717: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2525 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3893 "dhcp6_parser.cc"
    break;

  case 718: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2532 "dhcp6_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3903 "dhcp6_parser.cc"
    break;

  case 719: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2539 "dhcp6_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3913 "dhcp6_parser.cc"
    break;

  case 720: // $@121: %empty
#line 2546 "dhcp6_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3922 "dhcp6_parser.cc"
    break;

  case 721: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2549 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3931 "dhcp6_parser.cc"
    break;

  case 722: // $@122: %empty
#line 2555 "dhcp6_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3940 "dhcp6_parser.cc"
    break;

  case 723: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2558 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3950 "dhcp6_parser.cc"
    break;

  case 724: // $@123: %empty
#line 2565 "dhcp6_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3959 "dhcp6_parser.cc"
    break;

  case 725: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2568 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3969 "dhcp6_parser.cc"
    break;

  case 726: // $@124: %empty
#line 2575 "dhcp6_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3978 "dhcp6_parser.cc"
    break;

  case 727: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2578 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3988 "dhcp6_parser.cc"
    break;

  case 728: // $@125: %empty
#line 2587 "dhcp6_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4000 "dhcp6_parser.cc"
    break;

  case 729: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2593 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4010 "dhcp6_parser.cc"
    break;

  case 730: // $@126: %empty
#line 2599 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4020 "dhcp6_parser.cc"
    break;

  case 731: // sub_config_control: "{" $@126 config_control_params "}"
#line 2603 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4029 "dhcp6_parser.cc"
    break;

  case 736: // $@127: %empty
#line 2618 "dhcp6_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4041 "dhcp6_parser.cc"
    break;

  case 737: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2624 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4050 "dhcp6_parser.cc"
    break;

  case 738: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2629 "dhcp6_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4060 "dhcp6_parser.cc"
    break;

  case 739: // $@128: %empty
#line 2637 "dhcp6_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4072 "dhcp6_parser.cc"
    break;

  case 740: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2643 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4081 "dhcp6_parser.cc"
    break;

  case 743: // $@129: %empty
#line 2655 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4091 "dhcp6_parser.cc"
    break;

  case 744: // logger_entry: "{" $@129 logger_params "}"
#line 2659 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4099 "dhcp6_parser.cc"
    break;

  case 754: // debuglevel: "debuglevel" ":" "integer"
#line 2676 "dhcp6_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4109 "dhcp6_parser.cc"
    break;

  case 755: // $@130: %empty
#line 2682 "dhcp6_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4118 "dhcp6_parser.cc"
    break;

  case 756: // severity: "severity" $@130 ":" "constant string"
#line 2685 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4128 "dhcp6_parser.cc"
    break;

  case 757: // $@131: %empty
#line 2691 "dhcp6_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4140 "dhcp6_parser.cc"
    break;

  case 758: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2697 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4149 "dhcp6_parser.cc"
    break;

  case 761: // $@132: %empty
#line 2706 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4159 "dhcp6_parser.cc"
    break;

  case 762: // output_entry: "{" $@132 output_params_list "}"
#line 2710 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4167 "dhcp6_parser.cc"
    break;

  case 770: // $@133: %empty
#line 2725 "dhcp6_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4176 "dhcp6_parser.cc"
    break;

  case 771: // output: "output" $@133 ":" "constant string"
#line 2728 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4186 "dhcp6_parser.cc"
    break;

  case 772: // flush: "flush" ":" "boolean"
#line 2734 "dhcp6_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4196 "dhcp6_parser.cc"
    break;

  case 773: // maxsize: "maxsize" ":" "integer"
#line 2740 "dhcp6_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4206 "dhcp6_parser.cc"
    break;

  case 774: // maxver: "maxver" ":" "integer"
#line 2746 "dhcp6_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4216 "dhcp6_parser.cc"
    break;

  case 775: // $@134: %empty
#line 2752 "dhcp6_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4225 "dhcp6_parser.cc"
    break;

  case 776: // pattern: "pattern" $@134 ":" "constant string"
#line 2755 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4235 "dhcp6_parser.cc"
    break;


#line 4239 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -944;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     186,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,    37,    33,    44,    62,    64,
      87,    95,    99,   103,   107,   116,   118,   147,   148,   205,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,    33,    -4,
     203,   115,    39,   499,    10,   235,   222,   151,   117,    67,
     -74,   605,    71,  -944,   223,   225,   234,   233,   247,  -944,
     299,  -944,  -944,  -944,  -944,  -944,  -944,   263,   304,   312,
     322,   330,   341,   363,   384,   390,   391,   406,   407,   409,
     410,  -944,   412,   413,   420,   424,   426,  -944,  -944,  -944,
     428,   438,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,   444,  -944,
    -944,  -944,  -944,  -944,  -944,   448,  -944,   449,  -944,    51,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,   452,  -944,
      54,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,   458,   460,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
      75,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,   101,  -944,  -944,  -944,  -944,  -944,   463,  -944,
     464,   465,  -944,  -944,  -944,  -944,  -944,  -944,   109,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,   377,   294,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,   379,  -944,  -944,   468,
    -944,  -944,  -944,   469,  -944,  -944,   470,   473,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,   480,   484,  -944,  -944,  -944,  -944,   481,   488,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,   150,  -944,  -944,  -944,   489,  -944,  -944,   490,  -944,
     491,   492,  -944,  -944,   494,   496,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,   206,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,   497,   207,  -944,  -944,  -944,  -944,    33,    33,  -944,
     307,   504,  -944,   506,   508,   509,   511,   516,   519,   326,
     328,   329,   332,   333,   334,   336,   337,   355,   340,   357,
     358,   360,   369,   525,   370,   372,   371,   373,   374,   534,
     535,   569,   375,   376,   574,   575,   577,   579,   580,   581,
     582,   583,   592,   593,   594,   595,   596,   597,   599,   600,
     415,   602,   604,   608,   609,   611,   612,   408,   613,  -944,
     115,  -944,   615,   419,    39,  -944,   618,   619,   620,   621,
     622,   429,   430,   623,   625,   626,   499,  -944,   628,    10,
    -944,   629,   435,   631,   437,   442,   235,  -944,   633,   639,
     640,   641,   642,   643,   644,  -944,   222,  -944,   645,   646,
     453,   647,   649,   655,   459,  -944,   117,   657,   462,   466,
    -944,    67,   660,   661,    14,  -944,   467,   662,   665,   471,
     669,   475,   476,   672,   674,   478,   479,   692,   703,   711,
     712,   605,  -944,   713,   520,    71,  -944,  -944,  -944,   714,
     485,   522,   715,   716,   717,   718,   723,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,   523,  -944,  -944,  -944,  -944,  -944,    55,   533,   536,
    -944,  -944,   730,   731,   732,   733,   540,   382,   734,   736,
     737,   738,   739,   742,   744,   745,   746,   747,  -944,   748,
     763,   764,   765,   546,   553,  -944,   768,  -944,   769,  -944,
    -944,   770,   771,   554,   584,   585,  -944,  -944,   769,   586,
     772,  -944,   587,  -944,   588,  -944,   589,  -944,  -944,  -944,
     769,   769,   769,   590,   591,   598,   601,  -944,   603,   606,
    -944,   607,   610,   614,  -944,  -944,   616,  -944,  -944,  -944,
     617,   733,  -944,  -944,   624,   627,  -944,   630,  -944,  -944,
     -19,   635,  -944,  -944,    55,   632,   634,   636,  -944,   775,
    -944,  -944,    33,   115,  -944,    71,    39,   242,   242,   774,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,   783,
     784,   785,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
     786,   -76,    33,   290,   688,   788,   790,   791,    73,   228,
     -46,    42,   202,   605,  -944,  -944,   793,  -944,  -944,   799,
     800,  -944,  -944,  -944,  -944,  -944,   -52,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,   774,  -944,   227,   239,
     245,  -944,  -944,  -944,  -944,   807,   809,   812,   813,   814,
    -944,   815,   816,  -944,  -944,  -944,   817,   819,   820,   822,
    -944,   291,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,   292,  -944,   821,   826,  -944,  -944,   825,
     830,  -944,  -944,   831,   833,  -944,  -944,   832,   836,  -944,
    -944,   834,   838,  -944,  -944,  -944,    57,  -944,  -944,  -944,
     837,  -944,  -944,  -944,   187,  -944,  -944,  -944,  -944,   293,
    -944,  -944,  -944,   254,  -944,  -944,   839,   841,  -944,  -944,
     840,   844,  -944,   845,   846,   847,   848,   849,   850,   302,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,   851,
     852,   853,  -944,  -944,  -944,  -944,   324,  -944,  -944,  -944,
    -944,  -944,  -944,   854,   855,   856,  -944,   325,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,   339,
    -944,  -944,  -944,   857,  -944,   858,  -944,  -944,  -944,   350,
    -944,  -944,  -944,  -944,  -944,   351,  -944,   258,  -944,   650,
    -944,   859,   860,  -944,  -944,   861,   863,  -944,  -944,  -944,
     862,  -944,   865,  -944,  -944,  -944,   864,   868,   869,   870,
     670,   663,   676,   675,   678,   874,   680,   681,   877,   878,
     879,   685,   686,   687,   690,   242,  -944,  -944,   242,  -944,
     774,   499,  -944,   783,   117,  -944,   784,    67,  -944,   785,
     637,  -944,   786,   -76,  -944,  -944,   290,  -944,   882,   688,
    -944,   259,   788,  -944,   222,  -944,   790,   -74,  -944,   791,
     693,   695,   696,   699,   706,   708,    73,  -944,   883,   887,
     709,   724,   725,   228,  -944,   735,   726,   740,   -46,  -944,
     913,   941,    42,  -944,   750,   960,   777,   966,   202,  -944,
    -944,   214,   793,  -944,  -944,   967,   974,    10,  -944,   799,
     235,  -944,   800,   976,  -944,  -944,   414,   794,   805,   808,
    -944,  -944,  -944,  -944,  -944,   818,  -944,  -944,   823,   827,
     828,  -944,  -944,  -944,  -944,  -944,   352,  -944,   353,  -944,
     999,  -944,  1004,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,   354,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,   829,  -944,  -944,   980,  -944,
    -944,  -944,  -944,  -944,  1006,  1014,  -944,  -944,  -944,  -944,
    -944,  1010,  -944,   381,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,   289,   835,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,   843,   866,  -944,  -944,   867,  -944,    33,  -944,
    -944,  1016,  -944,  -944,  -944,  -944,  -944,   383,  -944,  -944,
    -944,  -944,  -944,  -944,   871,   393,  -944,   399,  -944,   872,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,   637,  -944,  -944,  1019,
     873,  -944,   259,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  1020,   880,  1025,   214,  -944,  -944,
    -944,  -944,  -944,  -944,   875,  -944,  -944,  1027,  -944,   884,
    -944,  -944,  1023,  -944,  -944,   338,  -944,   -32,  1023,  -944,
    -944,  1030,  1031,  1032,  -944,   401,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  1033,   876,   881,   885,  1034,   -32,  -944,
     888,  -944,  -944,  -944,   889,  -944,  -944,  -944
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    62,     7,   166,     9,   328,    11,
     512,    13,   537,    15,   567,    17,   437,    19,   445,    21,
     482,    23,   293,    25,   680,    27,   730,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   569,     0,   447,   484,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    60,
       0,   123,   728,   164,   178,   180,   182,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   161,     0,     0,     0,     0,     0,   142,   149,   151,
       0,     0,   320,   435,   474,   525,   527,   381,   389,   253,
     270,   261,   246,   604,   559,   285,   304,   625,     0,   272,
     649,   662,   678,   154,   156,     0,   739,     0,   122,     0,
      64,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     102,   103,   104,   105,   106,    75,   110,   111,   112,   113,
     114,   115,   116,   108,   109,   117,   118,   119,   100,   121,
      78,    79,    80,    81,    97,    82,    84,    83,   120,    88,
      89,    76,   101,    77,    86,    87,    95,    96,    98,    85,
      90,    91,    92,    93,    94,    99,   107,   175,     0,   174,
       0,   168,   170,   171,   172,   173,   504,   529,   371,   373,
     375,     0,     0,   379,   377,   598,   370,   332,   333,   334,
     335,   336,   337,   338,   339,   355,   356,   357,   358,   359,
     362,   363,   364,   365,   366,   367,   368,   360,   361,   369,
       0,   330,   343,   344,   345,   348,   349,   351,   346,   347,
     340,   341,   353,   354,   342,   350,   352,   523,   522,   518,
     519,   517,     0,   514,   516,   520,   521,   552,     0,   555,
       0,     0,   551,   545,   546,   544,   549,   550,     0,   539,
     541,   542,   547,   548,   543,   596,   584,   586,   588,   590,
     592,   594,   583,   580,   581,   582,     0,   570,   571,   575,
     576,   573,   577,   578,   579,   574,     0,   464,   226,     0,
     468,   466,   471,     0,   460,   461,     0,   448,   449,   451,
     463,   452,   453,   454,   470,   455,   456,   457,   458,   459,
     498,     0,     0,   496,   497,   500,   501,     0,   485,   486,
     488,   489,   490,   491,   492,   493,   494,   495,   300,   302,
     297,     0,   295,   298,   299,     0,   703,   705,     0,   708,
       0,     0,   712,   716,     0,     0,   720,   722,   724,   726,
     701,   699,   700,     0,   682,   684,   696,   685,   686,   687,
     688,   689,   690,   691,   692,   693,   694,   695,   697,   698,
     736,     0,     0,   732,   734,   735,    46,     0,     0,    39,
       0,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
       0,    63,     0,     0,     0,   167,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   329,     0,     0,
     513,     0,     0,     0,     0,     0,     0,   538,     0,     0,
       0,     0,     0,     0,     0,   568,     0,   438,     0,     0,
       0,     0,     0,     0,     0,   446,     0,     0,     0,     0,
     483,     0,     0,     0,     0,   294,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   681,     0,     0,     0,   731,    50,    43,     0,
       0,     0,     0,     0,     0,     0,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,     0,   159,   160,   139,   140,   141,     0,     0,     0,
     153,   158,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   648,     0,
       0,     0,     0,     0,     0,   163,     0,    65,     0,   177,
     169,     0,     0,     0,     0,     0,   387,   388,     0,     0,
       0,   331,     0,   515,     0,   554,     0,   557,   558,   540,
       0,     0,     0,     0,     0,     0,     0,   572,     0,     0,
     462,     0,     0,     0,   473,   450,     0,   502,   503,   487,
       0,     0,   296,   702,     0,     0,   707,     0,   710,   711,
       0,     0,   718,   719,     0,     0,     0,     0,   683,     0,
     738,   733,     0,     0,   124,     0,     0,     0,     0,   184,
     162,   144,   145,   146,   147,   148,   143,   150,   152,   322,
     439,   476,    40,   526,   528,   383,   384,   385,   386,   382,
     391,     0,    47,     0,     0,     0,   561,   287,     0,     0,
       0,     0,     0,     0,   155,   157,     0,    51,   176,   506,
     531,   372,   374,   376,   380,   378,     0,   524,   553,   556,
     597,   585,   587,   589,   591,   593,   595,   465,   227,   469,
     467,   472,   499,   301,   303,   704,   706,   709,   714,   715,
     713,   717,   721,   723,   725,   727,   184,    44,     0,     0,
       0,   213,   219,   221,   223,     0,     0,     0,     0,     0,
     237,     0,     0,   240,   242,   244,     0,     0,     0,     0,
     212,     0,   190,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   204,   211,   205,   206,   207,   202,   203,
     208,   209,   210,     0,   188,     0,   185,   186,   326,     0,
     323,   324,   443,     0,   440,   441,   480,     0,   477,   478,
     395,     0,   392,   393,   259,   260,     0,   255,   257,   258,
       0,   268,   269,   265,     0,   263,   266,   267,   251,     0,
     248,   250,   608,     0,   606,   565,     0,   562,   563,   291,
       0,   288,   289,     0,     0,     0,     0,     0,     0,     0,
     306,   308,   309,   310,   311,   312,   313,   638,   644,     0,
       0,     0,   637,   634,   635,   636,     0,   627,   629,   632,
     630,   631,   633,     0,     0,     0,   281,     0,   274,   276,
     277,   278,   279,   280,   658,   660,   657,   655,   656,     0,
     651,   653,   654,     0,   673,     0,   676,   669,   670,     0,
     664,   666,   667,   668,   671,     0,   743,     0,   741,    53,
     510,     0,   507,   508,   535,     0,   532,   533,   602,   601,
       0,   600,     0,    61,   729,   165,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,   181,     0,   183,
       0,     0,   321,     0,   447,   436,     0,   484,   475,     0,
       0,   390,     0,     0,   254,   271,     0,   262,     0,     0,
     247,   610,     0,   605,   569,   560,     0,     0,   286,     0,
       0,     0,     0,     0,     0,     0,     0,   305,     0,     0,
       0,     0,     0,     0,   626,     0,     0,     0,     0,   273,
       0,     0,     0,   650,     0,     0,     0,     0,     0,   663,
     679,     0,     0,   740,    55,     0,    54,     0,   505,     0,
       0,   530,     0,     0,   599,   737,     0,     0,     0,     0,
     225,   228,   229,   230,   231,     0,   239,   232,     0,     0,
       0,   234,   235,   236,   233,   191,     0,   187,     0,   325,
       0,   442,     0,   479,   434,   410,   411,   412,   414,   415,
     416,   403,   404,   419,   420,   421,   422,   423,   426,   427,
     428,   429,   430,   431,   432,   424,   425,   433,   399,   400,
     401,   402,   408,   409,   407,   413,     0,   397,   405,   417,
     418,   406,   394,   256,   264,     0,   249,   622,     0,   620,
     621,   617,   618,   619,     0,   611,   612,   614,   615,   616,
     607,     0,   564,     0,   290,   314,   315,   316,   317,   318,
     319,   307,     0,     0,   643,   646,   647,   628,   282,   283,
     284,   275,     0,     0,   652,   672,     0,   675,     0,   665,
     757,     0,   755,   753,   747,   751,   752,     0,   745,   749,
     750,   748,   742,    52,     0,     0,   509,     0,   534,     0,
     215,   216,   217,   218,   214,   220,   222,   224,   238,   241,
     243,   245,   189,   327,   444,   481,     0,   396,   252,     0,
       0,   609,     0,   566,   292,   640,   641,   642,   639,   645,
     659,   661,   674,   677,     0,     0,     0,     0,   744,    56,
     511,   536,   603,   398,     0,   624,   613,     0,   754,     0,
     746,   623,     0,   756,   761,     0,   759,     0,     0,   758,
     770,     0,     0,     0,   775,     0,   763,   765,   766,   767,
     768,   769,   760,     0,     0,     0,     0,     0,     0,   762,
       0,   772,   773,   774,     0,   764,   771,   776
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,   -10,  -944,  -544,  -944,
     191,  -944,  -944,  -944,  -944,   342,  -944,  -565,  -944,  -944,
    -944,   -71,  -944,  -944,  -944,  -944,  -944,  -944,   366,   572,
    -944,  -944,   -59,   -43,   -42,   -40,   -39,   -28,   -27,   -26,
     -23,   -21,   -15,    -9,    -3,  -944,    -1,    17,    18,    20,
    -944,   385,    25,  -944,    28,  -944,    30,    32,  -944,    35,
    -944,    38,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,   378,   571,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,   295,  -944,    86,  -944,  -656,    92,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,   -67,  -944,
    -694,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,    69,  -944,  -944,  -944,  -944,  -944,    77,  -678,  -944,
    -944,  -944,  -944,    76,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,    47,  -944,  -944,  -944,  -944,  -944,  -944,  -944,    68,
    -944,  -944,  -944,    66,   532,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,    63,  -944,  -944,  -944,  -944,  -944,  -944,  -943,
    -944,  -944,  -944,    97,  -944,  -944,  -944,   100,   576,  -944,
    -944,  -942,  -944,  -941,  -944,    41,  -944,    45,  -944,    40,
    -944,  -944,  -944,  -935,  -944,  -944,  -944,  -944,    91,  -944,
    -944,  -128,   989,  -944,  -944,  -944,  -944,  -944,   110,  -944,
    -944,  -944,   114,  -944,   551,  -944,   -66,  -944,  -944,  -944,
    -944,  -944,   -47,  -944,  -944,  -944,  -944,  -944,    13,  -944,
    -944,  -944,   112,  -944,  -944,  -944,   121,  -944,   562,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
      56,  -944,  -944,  -944,    65,   652,  -944,  -944,   -55,  -944,
       1,  -944,  -944,  -944,  -944,  -944,    58,  -944,  -944,  -944,
      59,   638,  -944,  -944,  -944,  -944,  -944,  -944,  -944,   -57,
    -944,  -944,  -944,   105,  -944,  -944,  -944,   111,  -944,   648,
     367,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -934,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,   119,  -944,  -944,  -944,   -98,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,    93,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,    85,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,    80,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,   386,   559,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,  -944,
    -944,  -944,  -944,  -944,  -944,  -944,  -944,   427,   558,  -944,
    -944,  -944,  -944,  -944,  -944,    82,  -944,  -944,  -102,  -944,
    -944,  -944,  -944,  -944,  -944,  -122,  -944,  -944,  -141,  -944,
    -944,  -944,  -944,  -944,  -944,  -944
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     693,    87,    88,    41,    68,    84,    85,   718,   919,  1025,
    1026,   780,    43,    70,    90,   411,    45,    71,   149,   150,
     151,   413,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     439,   686,   170,   440,   171,   441,   172,   173,   465,   174,
     466,   175,   176,   177,   178,   433,   179,   180,   415,    47,
      72,   210,   211,   212,   472,   213,   181,   416,   182,   417,
     183,   418,   805,   806,   807,   958,   781,   782,   783,   936,
    1174,   784,   937,   785,   938,   786,   939,   787,   788,   509,
     789,   790,   791,   792,   793,   794,   795,   796,   797,   798,
     945,   799,   800,   948,   801,   949,   802,   950,   184,   454,
     839,   840,   841,   978,   185,   451,   826,   827,   828,   829,
     186,   453,   834,   835,   836,   837,   187,   452,   188,   461,
     887,   888,   889,   890,   891,   189,   457,   850,   851,   852,
     987,    63,    80,   361,   362,   363,   522,   364,   523,   190,
     458,   859,   860,   861,   862,   863,   864,   865,   866,   191,
     444,   809,   810,   811,   961,    49,    73,   250,   251,   252,
     478,   253,   479,   254,   480,   255,   484,   256,   483,   192,
     449,   699,   258,   259,   193,   450,   821,   822,   823,   970,
    1096,  1097,   194,   445,    57,    77,   813,   814,   815,   964,
      59,    78,   326,   327,   328,   329,   330,   331,   332,   508,
     333,   512,   334,   511,   335,   336,   513,   337,   195,   446,
     817,   818,   819,   967,    61,    79,   347,   348,   349,   350,
     351,   517,   352,   353,   354,   355,   261,   476,   921,   922,
     923,  1027,    51,    74,   272,   273,   274,   488,   196,   447,
     197,   448,   264,   477,   925,   926,   927,  1030,    53,    75,
     288,   289,   290,   491,   291,   292,   493,   293,   294,   198,
     456,   846,   847,   848,   984,    55,    76,   306,   307,   308,
     309,   499,   310,   500,   311,   501,   312,   502,   313,   503,
     314,   504,   315,   498,   266,   485,   930,   931,  1033,   199,
     455,   843,   844,   981,  1114,  1115,  1116,  1117,  1118,  1189,
    1119,   200,   459,   876,   877,   878,   998,  1198,   879,   880,
     999,   881,   882,   201,   202,   462,   899,   900,   901,  1010,
     902,  1011,   203,   463,   909,   910,   911,   912,  1015,   913,
     914,  1017,   204,   464,    65,    81,   383,   384,   385,   386,
     527,   387,   528,   388,   389,   530,   390,   391,   392,   533,
     750,   393,   534,   394,   395,   396,   537,   397,   538,   398,
     539,   399,   540,   205,   414,    67,    82,   402,   403,   404,
     543,   405,   206,   468,   917,   918,  1021,  1157,  1158,  1159,
    1160,  1206,  1161,  1204,  1225,  1226,  1227,  1235,  1236,  1237,
    1243,  1238,  1239,  1240,  1241,  1247
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     148,   209,   226,   268,   282,   302,    38,   324,   343,   360,
     380,   325,   344,   345,   227,   873,   265,   214,   262,   275,
     286,   304,   803,   338,   356,   833,   381,  1089,  1090,  1091,
     228,   229,   346,   230,   231,  1095,  1101,    30,    31,   824,
      32,   692,    33,   125,   126,   232,   233,   234,   358,   359,
     235,    42,   236,   724,   470,   207,   208,   474,   237,   471,
     973,   296,   475,   974,   238,   730,   731,   732,   928,    44,
     239,    46,   240,   215,   263,   276,   287,   305,   486,   339,
     357,   124,   382,   487,   400,   401,   260,   271,   285,   303,
     241,   242,   267,   243,    48,   883,   884,   885,   244,   125,
     126,   245,    50,   246,   489,   247,    52,   692,   248,   490,
      54,   249,   496,   257,    56,   269,   283,   497,   223,   270,
     284,   224,   825,    58,   147,    60,    91,    92,   125,   126,
      93,   125,   126,    94,    95,    96,   358,   359,   317,   318,
     340,   319,   320,   341,   342,  1230,   748,   749,  1231,  1232,
    1233,  1234,   147,   524,    62,    64,   125,   126,   525,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   894,   895,   318,
     976,   319,   320,   977,    86,   321,   322,   323,   853,   854,
     855,   856,   857,   858,   125,   126,   125,   126,   147,   541,
     545,   127,    66,    89,   542,   546,   128,   129,   130,   131,
     132,   123,   133,   681,   682,   683,   684,   134,   407,   406,
     470,    34,    35,    36,    37,   933,   135,   147,   408,   136,
     147,   409,   545,  1089,  1090,  1091,   137,   934,   474,   867,
     410,  1095,  1101,   935,   138,   139,   685,   982,   766,   140,
     983,  1022,   141,   761,  1023,   147,   142,   419,   762,   763,
     764,   765,   766,   767,   768,   769,   770,   771,   772,   773,
     774,   775,   776,   777,   778,   779,   318,   143,   144,   145,
     146,   125,   126,   124,   955,   955,   979,   506,   833,   956,
     957,   980,  1056,   125,   126,   996,   124,   412,   420,   873,
     997,   125,   126,   147,   318,   147,   421,   125,   126,   277,
     278,   279,   280,   281,   125,   126,   422,  1003,  1008,   295,
     124,   318,  1004,  1009,   423,   296,   297,   298,   299,   300,
     301,  1228,  1012,   223,  1229,   424,   224,  1013,   125,   126,
     903,   904,   905,  1018,   541,   955,   486,  1186,  1019,  1020,
    1182,  1183,  1187,   868,   869,   870,   871,   425,  1107,  1108,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,   524,   505,  1207,   507,   426,  1194,
    1150,  1208,  1151,  1152,   427,   428,   489,   547,   548,   148,
     906,  1210,   496,   209,  1248,   824,   831,  1211,   832,  1249,
     429,   430,   147,   431,   432,   226,   434,   435,   268,   214,
     147,  1195,  1196,  1197,   436,   282,   147,   227,   437,   265,
     438,   262,   442,   147,   275,   302,  1170,  1171,  1172,  1173,
     147,   286,   443,   228,   229,   324,   230,   231,   460,   325,
     343,   304,   467,   469,   344,   345,   473,   147,   232,   233,
     234,   338,   481,   235,   482,   236,   356,   492,   494,   495,
     380,   237,   510,   514,   346,   215,   516,   238,   515,   695,
     696,   697,   698,   239,   518,   240,   381,   263,   519,   520,
     276,   521,   673,   526,   529,   531,   532,   287,   535,   260,
     536,   544,   271,   241,   242,   549,   243,   305,   550,   285,
     551,   244,   552,   553,   245,   554,   246,   339,   247,   303,
     555,   248,   357,   556,   249,   557,   257,   558,   559,   571,
     269,   560,   561,   562,   270,   563,   564,   283,   577,   578,
     566,   284,   382,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   565,   567,   568,   569,
     114,   115,   116,   117,   118,   119,   120,   121,   570,   572,
     124,   573,   574,   579,   575,   576,   580,   581,   582,   583,
     216,   584,   217,   585,   586,   587,   588,   589,   125,   126,
     218,   219,   220,   221,   222,   127,   590,   591,   592,   593,
     594,   595,   148,   596,   597,   209,   599,   223,   600,   605,
     224,   134,   601,   602,   598,   603,   604,   606,   225,   608,
     609,   214,   611,   612,   613,   614,   615,   618,   616,   619,
     620,   617,   622,   624,   625,   626,   627,   630,   872,   886,
     896,   628,   380,   631,   632,   633,   634,   635,   636,   638,
     639,   641,   640,   642,   874,   892,   897,   907,   381,   643,
     644,   646,   757,   647,   650,   651,   654,   648,   653,   655,
     656,   143,   144,   657,   658,   659,   660,   215,   661,   662,
     663,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   125,   126,   664,   147,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   665,   124,   318,
     875,   893,   898,   908,   382,   666,   667,   669,   672,   670,
     674,   680,   675,   676,   677,   678,   125,   126,   679,   219,
     220,   687,   222,   127,   688,   689,   690,   691,   694,   700,
      32,   701,   702,   703,   714,   223,   704,   705,   224,   706,
     707,   715,   721,   708,   709,   710,   225,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     711,   712,   713,   716,   717,   719,   720,   378,   379,   726,
     756,   804,   722,   723,   725,   727,   728,   729,   733,   734,
     808,   812,   816,   820,   838,   842,   735,   845,   849,   736,
     916,   737,   751,   147,   738,   739,   920,   924,   740,   143,
     144,   940,   741,   941,   742,   743,   942,   943,   944,   946,
     947,   951,   745,   952,   953,   746,   954,   959,   747,   960,
     753,   962,   754,   963,   755,   147,   966,   965,   968,   969,
     971,   972,   744,   975,   986,   985,   988,   989,  1024,   990,
     991,   992,   993,   994,   995,  1000,  1001,  1002,  1005,  1006,
    1007,  1014,  1016,  1029,  1041,  1028,  1032,  1031,  1036,  1040,
    1034,  1035,  1037,  1038,  1039,  1042,  1043,  1044,  1045,  1046,
    1047,  1048,  1049,  1050,  1051,  1052,  1105,  1132,  1053,  1054,
     226,  1133,  1125,   324,  1126,  1127,   343,   325,  1128,  1064,
     344,   345,   227,  1088,   265,  1129,   262,  1130,  1134,   338,
    1109,  1065,   356,   302,  1110,  1099,   360,  1142,   228,   229,
     346,   230,   231,  1135,  1136,  1139,  1112,  1066,  1067,   304,
    1068,  1069,   872,   232,   233,   234,  1138,   886,   235,  1140,
     236,   896,  1070,  1071,  1072,  1143,   237,  1073,   874,  1074,
    1153,  1145,   238,   892,  1154,  1075,   268,   897,   239,   282,
     240,  1076,   263,   907,  1146,   339,  1155,  1077,   357,  1078,
    1148,  1100,   275,  1163,   260,   286,  1147,  1164,   241,   242,
    1169,   243,  1113,  1098,  1190,   305,   244,  1079,  1080,   245,
    1081,   246,  1175,   247,  1111,  1082,   248,   303,  1083,   249,
    1084,   257,  1085,  1176,   875,  1086,  1177,  1184,  1087,   893,
    1094,  1092,  1185,   898,  1191,  1093,  1178,  1192,  1193,   908,
    1205,  1179,  1156,  1214,  1217,  1180,  1181,  1188,   276,  1219,
    1224,   287,  1222,  1199,  1244,  1245,  1246,  1250,  1254,   758,
     271,  1200,   607,   285,   830,   610,  1057,  1055,  1106,   752,
    1103,   932,  1104,  1123,   760,  1141,   652,  1124,  1213,  1131,
    1059,  1058,   621,  1102,  1201,  1202,   316,   645,   269,  1209,
    1212,   283,   270,  1221,  1215,   284,  1061,  1251,  1060,  1218,
    1252,  1063,  1223,   649,  1253,  1166,  1256,  1257,  1062,  1167,
    1168,  1122,  1165,   929,  1216,  1121,  1137,  1144,  1149,   915,
     668,  1120,   759,   671,  1162,  1220,  1242,  1255,     0,     0,
       0,     0,     0,     0,     0,  1064,     0,     0,     0,  1088,
       0,  1109,     0,     0,     0,  1110,     0,  1065,     0,     0,
       0,  1099,     0,     0,   629,     0,  1153,  1112,  1203,     0,
    1154,   623,     0,  1066,  1067,     0,  1068,  1069,     0,     0,
       0,     0,  1155,     0,   637,     0,     0,     0,  1070,  1071,
    1072,     0,     0,  1073,     0,  1074,     0,     0,     0,     0,
       0,  1075,     0,     0,     0,     0,     0,  1076,     0,     0,
       0,     0,     0,  1077,     0,  1078,     0,  1100,     0,     0,
       0,     0,     0,  1113,     0,     0,     0,     0,     0,  1098,
       0,     0,     0,  1079,  1080,  1111,  1081,     0,  1156,     0,
       0,  1082,     0,     0,  1083,     0,  1084,     0,  1085,     0,
       0,  1086,     0,     0,  1087,     0,  1094,  1092,     0,     0,
       0,  1093
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    78,    79,    79,    73,   709,    73,    72,    73,    74,
      75,    76,   678,    78,    79,   703,    81,   970,   970,   970,
      73,    73,    79,    73,    73,   970,   970,     0,     5,   115,
       7,   585,     9,    89,    90,    73,    73,    73,   122,   123,
      73,     7,    73,   618,     3,    16,    17,     3,    73,     8,
       3,   113,     8,     6,    73,   630,   631,   632,   120,     7,
      73,     7,    73,    72,    73,    74,    75,    76,     3,    78,
      79,    71,    81,     8,    13,    14,    73,    74,    75,    76,
      73,    73,    82,    73,     7,   141,   142,   143,    73,    89,
      90,    73,     7,    73,     3,    73,     7,   651,    73,     8,
       7,    73,     3,    73,     7,    74,    75,     8,   108,    74,
      75,   111,   198,     7,   198,     7,    11,    12,    89,    90,
      15,    89,    90,    18,    19,    20,   122,   123,    21,    72,
      73,    74,    75,    76,    77,   177,   165,   166,   180,   181,
     182,   183,   198,     3,     7,     7,    89,    90,     8,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,   145,   146,    72,
       3,    74,    75,     6,   198,    78,    79,    80,   125,   126,
     127,   128,   129,   130,    89,    90,    89,    90,   198,     3,
       3,    96,     7,    10,     8,     8,   101,   102,   103,   104,
     105,    70,   107,   168,   169,   170,   171,   112,     3,     6,
       3,   198,   199,   200,   201,     8,   121,   198,     4,   124,
     198,     8,     3,  1186,  1186,  1186,   131,     8,     3,    21,
       3,  1186,  1186,     8,   139,   140,   201,     3,    30,   144,
       6,     3,   147,    21,     6,   198,   151,     4,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    72,   172,   173,   174,
     175,    89,    90,    71,     3,     3,     3,     3,   976,     8,
       8,     8,   958,    89,    90,     3,    71,     8,     4,  1003,
       8,    89,    90,   198,    72,   198,     4,    89,    90,    84,
      85,    86,    87,    88,    89,    90,     4,     3,     3,   107,
      71,    72,     8,     8,     4,   113,   114,   115,   116,   117,
     118,     3,     3,   108,     6,     4,   111,     8,    89,    90,
     148,   149,   150,     3,     3,     3,     3,     3,     8,     8,
       8,     8,     8,   135,   136,   137,   138,     4,   109,   110,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,     3,     8,     3,     8,     4,     8,
     176,     8,   178,   179,     4,     4,     3,   407,   408,   470,
     198,     8,     3,   474,     3,   115,   116,     8,   118,     8,
       4,     4,   198,     4,     4,   486,     4,     4,   489,   474,
     198,   132,   133,   134,     4,   496,   198,   486,     4,   486,
       4,   486,     4,   198,   489,   506,    22,    23,    24,    25,
     198,   496,     4,   486,   486,   516,   486,   486,     4,   516,
     521,   506,     4,     4,   521,   521,     4,   198,   486,   486,
     486,   516,     4,   486,     4,   486,   521,     4,     4,     4,
     541,   486,     4,     4,   521,   474,     3,   486,     8,    97,
      98,    99,   100,   486,     4,   486,   541,   486,     4,     8,
     489,     3,     7,     4,     4,     4,     4,   496,     4,   486,
       4,     4,   489,   486,   486,   198,   486,   506,     4,   496,
       4,   486,     4,     4,   486,     4,   486,   516,   486,   506,
       4,   486,   521,     4,   486,   199,   486,   199,   199,     4,
     489,   199,   199,   199,   489,   199,   199,   496,     4,     4,
     200,   496,   541,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,   201,   200,   200,   199,
      61,    62,    63,    64,    65,    66,    67,    68,   199,   199,
      71,   199,   201,     4,   201,   201,   201,   201,     4,     4,
      81,     4,    83,     4,     4,     4,     4,     4,    89,    90,
      91,    92,    93,    94,    95,    96,     4,     4,     4,     4,
       4,     4,   673,     4,     4,   676,     4,   108,     4,   201,
     111,   112,     4,     4,   199,     4,     4,     4,   119,     4,
     201,   676,     4,     4,     4,     4,     4,     4,   199,     4,
       4,   201,     4,     4,   199,     4,   199,     4,   709,   710,
     711,   199,   713,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   199,     4,   709,   710,   711,   712,   713,     4,
     201,     4,   672,   201,     4,     4,     4,   201,   201,     4,
     199,   172,   173,     4,   199,   199,     4,   676,     4,   201,
     201,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    89,    90,     4,   198,    61,    62,
      63,    64,    65,    66,    67,    68,    69,     4,    71,    72,
     709,   710,   711,   712,   713,     4,     4,     4,     4,   199,
     198,   198,     7,     7,     7,     7,    89,    90,     5,    92,
      93,   198,    95,    96,   198,     5,     5,     5,   198,     5,
       7,     5,     5,     5,   198,   108,     7,     5,   111,     5,
       5,   198,   198,     7,     7,     7,   119,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
       7,     7,     7,     5,     5,     5,     5,   172,   173,     7,
       5,     7,   198,   198,   198,   198,   198,   198,   198,   198,
       7,     7,     7,     7,   106,     7,   198,     7,     7,   198,
       7,   198,   167,   198,   198,   198,     7,     7,   198,   172,
     173,     4,   198,     4,   198,   198,     4,     4,     4,     4,
       4,     4,   198,     4,     4,   198,     4,     6,   198,     3,
     198,     6,   198,     3,   198,   198,     3,     6,     6,     3,
       6,     3,   651,     6,     3,     6,     6,     3,   198,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   201,     6,     3,     6,     4,   199,
       8,     6,     4,     4,     4,   199,   201,   199,     4,   199,
     199,     4,     4,     4,   199,   199,     4,     4,   201,   199,
     961,     4,   199,   964,   199,   199,   967,   964,   199,   970,
     967,   967,   961,   970,   961,   199,   961,   199,   199,   964,
     981,   970,   967,   984,   981,   970,   987,     4,   961,   961,
     967,   961,   961,   199,   199,   199,   981,   970,   970,   984,
     970,   970,  1003,   961,   961,   961,   201,  1008,   961,   199,
     961,  1012,   970,   970,   970,     4,   961,   970,  1003,   970,
    1021,   201,   961,  1008,  1021,   970,  1027,  1012,   961,  1030,
     961,   970,   961,  1018,     4,   964,  1021,   970,   967,   970,
       4,   970,  1027,     6,   961,  1030,   199,     3,   961,   961,
       4,   961,   981,   970,     4,   984,   961,   970,   970,   961,
     970,   961,   198,   961,   981,   970,   961,   984,   970,   961,
     970,   961,   970,   198,  1003,   970,   198,     8,   970,  1008,
     970,   970,     8,  1012,     8,   970,   198,     3,     8,  1018,
       4,   198,  1021,     4,     4,   198,   198,   198,  1027,     4,
       7,  1030,     5,   198,     4,     4,     4,     4,     4,   673,
    1027,   198,   470,  1030,   702,   474,   960,   955,   979,   664,
     973,   756,   976,   987,   676,  1008,   524,   989,  1186,   996,
     963,   961,   486,   972,   198,   198,    77,   516,  1027,   198,
     198,  1030,  1027,   198,   201,  1030,   966,   201,   964,   199,
     199,   969,   198,   521,   199,  1029,   198,   198,   967,  1030,
    1032,   986,  1027,   726,  1192,   984,  1003,  1012,  1018,   713,
     541,   982,   675,   545,  1022,  1207,  1228,  1248,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1186,    -1,    -1,    -1,  1186,
      -1,  1192,    -1,    -1,    -1,  1192,    -1,  1186,    -1,    -1,
      -1,  1186,    -1,    -1,   496,    -1,  1207,  1192,  1148,    -1,
    1207,   489,    -1,  1186,  1186,    -1,  1186,  1186,    -1,    -1,
      -1,    -1,  1207,    -1,   506,    -1,    -1,    -1,  1186,  1186,
    1186,    -1,    -1,  1186,    -1,  1186,    -1,    -1,    -1,    -1,
      -1,  1186,    -1,    -1,    -1,    -1,    -1,  1186,    -1,    -1,
      -1,    -1,    -1,  1186,    -1,  1186,    -1,  1186,    -1,    -1,
      -1,    -1,    -1,  1192,    -1,    -1,    -1,    -1,    -1,  1186,
      -1,    -1,    -1,  1186,  1186,  1192,  1186,    -1,  1207,    -1,
      -1,  1186,    -1,    -1,  1186,    -1,  1186,    -1,  1186,    -1,
      -1,  1186,    -1,    -1,  1186,    -1,  1186,  1186,    -1,    -1,
      -1,  1186
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
       0,     5,     7,     9,   198,   199,   200,   201,   218,   219,
     220,   225,     7,   234,     7,   238,     7,   281,     7,   387,
       7,   464,     7,   480,     7,   497,     7,   416,     7,   422,
       7,   446,     7,   363,     7,   566,     7,   597,   226,   221,
     235,   239,   282,   388,   465,   481,   498,   417,   423,   447,
     364,   567,   598,   218,   227,   228,   198,   223,   224,    10,
     236,    11,    12,    15,    18,    19,    20,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    89,    90,    96,   101,   102,
     103,   104,   105,   107,   112,   121,   124,   131,   139,   140,
     144,   147,   151,   172,   173,   174,   175,   198,   233,   240,
     241,   242,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     264,   266,   268,   269,   271,   273,   274,   275,   276,   278,
     279,   288,   290,   292,   330,   336,   342,   348,   350,   357,
     371,   381,   401,   406,   414,   440,   470,   472,   491,   521,
     533,   545,   546,   554,   564,   595,   604,    16,    17,   233,
     283,   284,   285,   287,   470,   472,    81,    83,    91,    92,
      93,    94,    95,   108,   111,   119,   233,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     258,   259,   260,   261,   264,   266,   268,   269,   271,   273,
     389,   390,   391,   393,   395,   397,   399,   401,   404,   405,
     440,   458,   470,   472,   474,   491,   516,    82,   233,   397,
     399,   440,   466,   467,   468,   470,   472,    84,    85,    86,
      87,    88,   233,   397,   399,   440,   470,   472,   482,   483,
     484,   486,   487,   489,   490,   107,   113,   114,   115,   116,
     117,   118,   233,   440,   470,   472,   499,   500,   501,   502,
     504,   506,   508,   510,   512,   514,   414,    21,    72,    74,
      75,    78,    79,    80,   233,   310,   424,   425,   426,   427,
     428,   429,   430,   432,   434,   436,   437,   439,   470,   472,
      73,    76,    77,   233,   310,   428,   434,   448,   449,   450,
     451,   452,   454,   455,   456,   457,   470,   472,   122,   123,
     233,   365,   366,   367,   369,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   172,   173,
     233,   470,   472,   568,   569,   570,   571,   573,   575,   576,
     578,   579,   580,   583,   585,   586,   587,   589,   591,   593,
      13,    14,   599,   600,   601,   603,     6,     3,     4,     8,
       3,   237,     8,   243,   596,   280,   289,   291,   293,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   277,     4,     4,     4,     4,     4,   262,
     265,   267,     4,     4,   382,   415,   441,   471,   473,   402,
     407,   337,   349,   343,   331,   522,   492,   358,   372,   534,
       4,   351,   547,   555,   565,   270,   272,     4,   605,     4,
       3,     8,   286,     4,     3,     8,   459,   475,   392,   394,
     396,     4,     4,   400,   398,   517,     3,     8,   469,     3,
       8,   485,     4,   488,     4,     4,     3,     8,   515,   503,
     505,   507,   509,   511,   513,     8,     3,     8,   431,   311,
       4,   435,   433,   438,     4,     8,     3,   453,     4,     4,
       8,     3,   368,   370,     3,     8,     4,   572,   574,     4,
     577,     4,     4,   581,   584,     4,     4,   588,   590,   592,
     594,     3,     8,   602,     4,     3,     8,   218,   218,   198,
       4,     4,     4,     4,     4,     4,     4,   199,   199,   199,
     199,   199,   199,   199,   199,   201,   200,   200,   200,   199,
     199,     4,   199,   199,   201,   201,   201,     4,     4,     4,
     201,   201,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   199,     4,
       4,     4,     4,     4,     4,   201,     4,   241,     4,   201,
     284,     4,     4,     4,     4,     4,   199,   201,     4,     4,
       4,   390,     4,   467,     4,   199,     4,   199,   199,   483,
       4,     4,     4,     4,     4,     4,     4,   501,     4,     4,
     199,     4,     4,     4,   201,   426,     4,   201,   201,   450,
       4,     4,   366,   201,     4,     4,   199,     4,   199,   199,
       4,     4,   201,   201,     4,     4,     4,     4,   569,     4,
     199,   600,     4,     7,   198,     7,     7,     7,     7,     5,
     198,   168,   169,   170,   171,   201,   263,   198,   198,     5,
       5,     5,   220,   222,   198,    97,    98,    99,   100,   403,
       5,     5,     5,     5,     7,     5,     5,     5,     7,     7,
       7,     7,     7,     7,   198,   198,     5,     5,   229,     5,
       5,   198,   198,   198,   229,   198,     7,   198,   198,   198,
     229,   229,   229,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   222,   198,   198,   198,   165,   166,
     582,   167,   263,   198,   198,   198,     5,   218,   240,   599,
     283,    21,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
     233,   298,   299,   300,   303,   305,   307,   309,   310,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   323,
     324,   326,   328,   298,     7,   294,   295,   296,     7,   383,
     384,   385,     7,   418,   419,   420,     7,   442,   443,   444,
       7,   408,   409,   410,   115,   198,   338,   339,   340,   341,
     227,   116,   118,   340,   344,   345,   346,   347,   106,   332,
     333,   334,     7,   523,   524,     7,   493,   494,   495,     7,
     359,   360,   361,   125,   126,   127,   128,   129,   130,   373,
     374,   375,   376,   377,   378,   379,   380,    21,   135,   136,
     137,   138,   233,   312,   470,   472,   535,   536,   537,   540,
     541,   543,   544,   141,   142,   143,   233,   352,   353,   354,
     355,   356,   470,   472,   145,   146,   233,   470,   472,   548,
     549,   550,   552,   148,   149,   150,   198,   470,   472,   556,
     557,   558,   559,   561,   562,   568,     7,   606,   607,   230,
       7,   460,   461,   462,     7,   476,   477,   478,   120,   502,
     518,   519,   294,     8,     8,     8,   301,   304,   306,   308,
       4,     4,     4,     4,     4,   322,     4,     4,   325,   327,
     329,     4,     4,     4,     4,     3,     8,     8,   297,     6,
       3,   386,     6,     3,   421,     6,     3,   445,     6,     3,
     411,     6,     3,     3,     6,     6,     3,     6,   335,     3,
       8,   525,     3,     6,   496,     6,     3,   362,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   538,   542,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     551,   553,     3,     8,     4,   560,     4,   563,     3,     8,
       8,   608,     3,     6,   198,   231,   232,   463,     6,     3,
     479,     6,     3,   520,     8,     6,     4,     4,     4,     4,
     199,   201,   199,   201,   199,     4,   199,   199,     4,     4,
       4,   199,   199,   201,   199,   299,   298,   296,   389,   385,
     424,   420,   448,   444,   233,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   258,   259,
     260,   261,   264,   266,   268,   269,   271,   273,   310,   381,
     393,   395,   397,   399,   401,   405,   412,   413,   440,   470,
     472,   516,   410,   339,   345,     4,   333,   109,   110,   233,
     310,   440,   470,   472,   526,   527,   528,   529,   530,   532,
     524,   499,   495,   365,   361,   199,   199,   199,   199,   199,
     199,   374,     4,     4,   199,   199,   199,   536,   201,   199,
     199,   353,     4,     4,   549,   201,     4,   199,     4,   557,
     176,   178,   179,   233,   310,   470,   472,   609,   610,   611,
     612,   614,   607,     6,     3,   466,   462,   482,   478,     4,
      22,    23,    24,    25,   302,   198,   198,   198,   198,   198,
     198,   198,     8,     8,     8,     8,     3,     8,   198,   531,
       4,     8,     3,     8,     8,   132,   133,   134,   539,   198,
     198,   198,   198,   218,   615,     4,   613,     3,     8,   198,
       8,     8,   198,   413,     4,   201,   528,     4,   199,     4,
     610,   198,     5,   198,     7,   616,   617,   618,     3,     6,
     177,   180,   181,   182,   183,   619,   620,   621,   623,   624,
     625,   626,   617,   622,     4,     4,     4,   627,     3,     8,
       4,   201,   199,   199,     4,   620,   198,   198
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   202,   204,   203,   205,   203,   206,   203,   207,   203,
     208,   203,   209,   203,   210,   203,   211,   203,   212,   203,
     213,   203,   214,   203,   215,   203,   216,   203,   217,   203,
     218,   218,   218,   218,   218,   218,   218,   219,   221,   220,
     222,   223,   223,   224,   224,   226,   225,   227,   227,   228,
     228,   230,   229,   231,   231,   232,   232,   233,   235,   234,
     237,   236,   239,   238,   240,   240,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   243,   242,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   262,   261,   263,   263,   263,   263,   263,   265,
     264,   267,   266,   268,   270,   269,   272,   271,   273,   274,
     275,   277,   276,   278,   280,   279,   282,   281,   283,   283,
     284,   284,   284,   284,   284,   286,   285,   287,   289,   288,
     291,   290,   293,   292,   294,   294,   295,   295,   297,   296,
     298,   298,   299,   299,   299,   299,   299,   299,   299,   299,
     299,   299,   299,   299,   299,   299,   299,   299,   299,   299,
     299,   299,   299,   301,   300,   302,   302,   302,   302,   304,
     303,   306,   305,   308,   307,   309,   311,   310,   312,   313,
     314,   315,   316,   317,   318,   319,   320,   322,   321,   323,
     325,   324,   327,   326,   329,   328,   331,   330,   332,   332,
     333,   335,   334,   337,   336,   338,   338,   339,   339,   340,
     341,   343,   342,   344,   344,   345,   345,   345,   346,   347,
     349,   348,   351,   350,   352,   352,   353,   353,   353,   353,
     353,   353,   354,   355,   356,   358,   357,   359,   359,   360,
     360,   362,   361,   364,   363,   365,   365,   365,   366,   366,
     368,   367,   370,   369,   372,   371,   373,   373,   374,   374,
     374,   374,   374,   374,   375,   376,   377,   378,   379,   380,
     382,   381,   383,   383,   384,   384,   386,   385,   388,   387,
     389,   389,   390,   390,   390,   390,   390,   390,   390,   390,
     390,   390,   390,   390,   390,   390,   390,   390,   390,   390,
     390,   390,   390,   390,   390,   390,   390,   390,   390,   390,
     390,   390,   390,   390,   390,   390,   390,   390,   390,   390,
     390,   392,   391,   394,   393,   396,   395,   398,   397,   400,
     399,   402,   401,   403,   403,   403,   403,   404,   405,   407,
     406,   408,   408,   409,   409,   411,   410,   412,   412,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   415,   414,   417,   416,   418,
     418,   419,   419,   421,   420,   423,   422,   424,   424,   425,
     425,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   427,   428,   429,   431,   430,   433,   432,   435,   434,
     436,   438,   437,   439,   441,   440,   442,   442,   443,   443,
     445,   444,   447,   446,   448,   448,   449,   449,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   451,   453,   452,
     454,   455,   456,   457,   459,   458,   460,   460,   461,   461,
     463,   462,   465,   464,   466,   466,   467,   467,   467,   467,
     467,   467,   467,   469,   468,   471,   470,   473,   472,   475,
     474,   476,   476,   477,   477,   479,   478,   481,   480,   482,
     482,   483,   483,   483,   483,   483,   483,   483,   483,   483,
     483,   483,   485,   484,   486,   488,   487,   489,   490,   492,
     491,   493,   493,   494,   494,   496,   495,   498,   497,   499,
     499,   500,   500,   501,   501,   501,   501,   501,   501,   501,
     501,   501,   501,   501,   503,   502,   505,   504,   507,   506,
     509,   508,   511,   510,   513,   512,   515,   514,   517,   516,
     518,   518,   520,   519,   522,   521,   523,   523,   525,   524,
     526,   526,   527,   527,   528,   528,   528,   528,   528,   528,
     528,   529,   531,   530,   532,   534,   533,   535,   535,   536,
     536,   536,   536,   536,   536,   536,   536,   536,   538,   537,
     539,   539,   539,   540,   542,   541,   543,   544,   545,   547,
     546,   548,   548,   549,   549,   549,   549,   549,   551,   550,
     553,   552,   555,   554,   556,   556,   557,   557,   557,   557,
     557,   557,   558,   560,   559,   561,   563,   562,   565,   564,
     567,   566,   568,   568,   569,   569,   569,   569,   569,   569,
     569,   569,   569,   569,   569,   569,   569,   569,   569,   569,
     569,   569,   570,   572,   571,   574,   573,   575,   577,   576,
     578,   579,   581,   580,   582,   582,   584,   583,   585,   586,
     588,   587,   590,   589,   592,   591,   594,   593,   596,   595,
     598,   597,   599,   599,   600,   600,   602,   601,   603,   605,
     604,   606,   606,   608,   607,   609,   609,   610,   610,   610,
     610,   610,   610,   610,   611,   613,   612,   615,   614,   616,
     616,   618,   617,   619,   619,   620,   620,   620,   620,   620,
     622,   621,   623,   624,   625,   627,   626
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
       1,     1,     1,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     3,     0,     4,     0,     4,     3,     3,
       3,     0,     4,     3,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     0,     6,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     3,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     6,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     1,     0,     4,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     3,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     0,     6,     3,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4
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
       0,   287,   287,   287,   288,   288,   289,   289,   290,   290,
     291,   291,   292,   292,   293,   293,   294,   294,   295,   295,
     296,   296,   297,   297,   298,   298,   299,   299,   300,   300,
     308,   309,   310,   311,   312,   313,   314,   317,   322,   322,
     333,   336,   337,   340,   345,   353,   353,   360,   361,   364,
     368,   375,   375,   382,   383,   386,   390,   401,   410,   410,
     425,   425,   442,   442,   451,   452,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   516,   516,   525,   531,   537,   543,   549,
     555,   561,   567,   573,   579,   585,   591,   597,   603,   609,
     615,   621,   627,   627,   636,   639,   642,   645,   648,   654,
     654,   663,   663,   672,   678,   678,   687,   687,   696,   702,
     708,   714,   714,   723,   729,   729,   741,   741,   750,   751,
     754,   755,   756,   757,   758,   761,   761,   772,   778,   778,
     791,   791,   804,   804,   815,   816,   819,   820,   823,   823,
     833,   834,   837,   838,   839,   840,   841,   842,   843,   844,
     845,   846,   847,   848,   849,   850,   851,   852,   853,   854,
     855,   856,   857,   860,   860,   868,   869,   870,   871,   874,
     874,   883,   883,   892,   892,   901,   907,   907,   916,   922,
     928,   934,   940,   946,   952,   958,   964,   970,   970,   979,
     985,   985,   994,   994,  1003,  1003,  1012,  1012,  1023,  1024,
    1026,  1028,  1028,  1047,  1047,  1058,  1059,  1062,  1063,  1066,
    1071,  1076,  1076,  1087,  1088,  1091,  1092,  1093,  1096,  1101,
    1108,  1108,  1121,  1121,  1134,  1135,  1138,  1139,  1140,  1141,
    1142,  1143,  1146,  1152,  1158,  1164,  1164,  1175,  1176,  1179,
    1180,  1183,  1183,  1193,  1193,  1203,  1204,  1205,  1208,  1209,
    1212,  1212,  1221,  1221,  1230,  1230,  1242,  1243,  1246,  1247,
    1248,  1249,  1250,  1251,  1254,  1260,  1266,  1272,  1278,  1284,
    1293,  1293,  1307,  1308,  1311,  1312,  1319,  1319,  1345,  1345,
    1356,  1357,  1361,  1362,  1363,  1364,  1365,  1366,  1367,  1368,
    1369,  1370,  1371,  1372,  1373,  1374,  1375,  1376,  1377,  1378,
    1379,  1380,  1381,  1382,  1383,  1384,  1385,  1386,  1387,  1388,
    1389,  1390,  1391,  1392,  1393,  1394,  1395,  1396,  1397,  1398,
    1399,  1402,  1402,  1411,  1411,  1420,  1420,  1429,  1429,  1438,
    1438,  1449,  1449,  1457,  1458,  1459,  1460,  1463,  1469,  1477,
    1477,  1489,  1490,  1494,  1495,  1498,  1498,  1506,  1507,  1510,
    1511,  1512,  1513,  1514,  1515,  1516,  1517,  1518,  1519,  1520,
    1521,  1522,  1523,  1524,  1525,  1526,  1527,  1528,  1529,  1530,
    1531,  1532,  1533,  1534,  1535,  1536,  1537,  1538,  1539,  1540,
    1541,  1542,  1543,  1544,  1545,  1552,  1552,  1566,  1566,  1575,
    1576,  1579,  1580,  1585,  1585,  1600,  1600,  1614,  1615,  1618,
    1619,  1622,  1623,  1624,  1625,  1626,  1627,  1628,  1629,  1630,
    1631,  1634,  1636,  1642,  1644,  1644,  1653,  1653,  1662,  1662,
    1671,  1673,  1673,  1682,  1692,  1692,  1705,  1706,  1711,  1712,
    1717,  1717,  1729,  1729,  1741,  1742,  1747,  1748,  1753,  1754,
    1755,  1756,  1757,  1758,  1759,  1760,  1761,  1764,  1766,  1766,
    1775,  1777,  1779,  1785,  1794,  1794,  1807,  1808,  1811,  1812,
    1815,  1815,  1825,  1825,  1835,  1836,  1839,  1840,  1841,  1842,
    1843,  1844,  1845,  1848,  1848,  1857,  1857,  1882,  1882,  1912,
    1912,  1925,  1926,  1929,  1930,  1933,  1933,  1945,  1945,  1957,
    1958,  1961,  1962,  1963,  1964,  1965,  1966,  1967,  1968,  1969,
    1970,  1971,  1974,  1974,  1983,  1989,  1989,  1998,  2004,  2013,
    2013,  2024,  2025,  2028,  2029,  2032,  2032,  2041,  2041,  2050,
    2051,  2054,  2055,  2059,  2060,  2061,  2062,  2063,  2064,  2065,
    2066,  2067,  2068,  2069,  2072,  2072,  2083,  2083,  2094,  2094,
    2103,  2103,  2112,  2112,  2121,  2121,  2130,  2130,  2144,  2144,
    2155,  2156,  2159,  2159,  2171,  2171,  2182,  2183,  2186,  2186,
    2196,  2197,  2200,  2201,  2204,  2205,  2206,  2207,  2208,  2209,
    2210,  2213,  2215,  2215,  2224,  2233,  2233,  2246,  2247,  2250,
    2251,  2252,  2253,  2254,  2255,  2256,  2257,  2258,  2261,  2261,
    2269,  2270,  2271,  2274,  2280,  2280,  2289,  2295,  2303,  2311,
    2311,  2322,  2323,  2326,  2327,  2328,  2329,  2330,  2333,  2333,
    2342,  2342,  2354,  2354,  2367,  2368,  2371,  2372,  2373,  2374,
    2375,  2376,  2379,  2385,  2385,  2394,  2400,  2400,  2410,  2410,
    2423,  2423,  2433,  2434,  2437,  2438,  2439,  2440,  2441,  2442,
    2443,  2444,  2445,  2446,  2447,  2448,  2449,  2450,  2451,  2452,
    2453,  2454,  2457,  2464,  2464,  2473,  2473,  2482,  2488,  2488,
    2497,  2503,  2509,  2509,  2518,  2519,  2522,  2522,  2532,  2539,
    2546,  2546,  2555,  2555,  2565,  2565,  2575,  2575,  2587,  2587,
    2599,  2599,  2609,  2610,  2614,  2615,  2618,  2618,  2629,  2637,
    2637,  2650,  2651,  2655,  2655,  2663,  2664,  2667,  2668,  2669,
    2670,  2671,  2672,  2673,  2676,  2682,  2682,  2691,  2691,  2702,
    2703,  2706,  2706,  2714,  2715,  2718,  2719,  2720,  2721,  2722,
    2725,  2725,  2734,  2740,  2746,  2752,  2752
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
#line 5796 "dhcp6_parser.cc"

#line 2761 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
