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
#define yylex   parser4_lex



#include "dhcp4_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy"

#include <dhcp4/parser_context.h>

#line 52 "dhcp4_parser.cc"


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
#if PARSER4_DEBUG

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

#else // !PARSER4_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy"
namespace isc { namespace dhcp {
#line 145 "dhcp4_parser.cc"

  /// Build a parser object.
  Dhcp4Parser::Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg)
#if PARSER4_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp4Parser::~Dhcp4Parser ()
  {}

  Dhcp4Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  Dhcp4Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Dhcp4Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Dhcp4Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp4Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
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

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
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
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
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

  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
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
  Dhcp4Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER4_DEBUG
  template <typename Base>
  void
  Dhcp4Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 284 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 480 "dhcp4_parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  Dhcp4Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Dhcp4Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if PARSER4_DEBUG
  std::ostream&
  Dhcp4Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp4Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp4Parser::debug_level_type
  Dhcp4Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp4Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER4_DEBUG

  Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp4Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp4Parser::operator() ()
  {
    return parse ();
  }

  int
  Dhcp4Parser::parse ()
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
      case symbol_kind::S_socket_type: // socket_type
      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
      case symbol_kind::S_db_type: // db_type
      case symbol_kind::S_on_fail_mode: // on_fail_mode
      case symbol_kind::S_hr_mode: // hr_mode
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
#line 293 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 294 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 295 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 296 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 297 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 298 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 299 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 300 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 301 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 302 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 303 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 304 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 305 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 313 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 314 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 315 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 316 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 317 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 318 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 319 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 322 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 327 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 332 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 338 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 345 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 350 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // $@15: %empty
#line 358 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 941 "dhcp4_parser.cc"
    break;

  case 44: // list_generic: "[" $@15 list_content "]"
#line 361 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 949 "dhcp4_parser.cc"
    break;

  case 47: // not_empty_list: value
#line 369 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 958 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: not_empty_list "," value
#line 373 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 967 "dhcp4_parser.cc"
    break;

  case 49: // $@16: %empty
#line 380 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // list_strings: "[" $@16 list_strings_content "]"
#line 382 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 984 "dhcp4_parser.cc"
    break;

  case 53: // not_empty_list_strings: "constant string"
#line 391 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 993 "dhcp4_parser.cc"
    break;

  case 54: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 395 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1002 "dhcp4_parser.cc"
    break;

  case 55: // unknown_map_entry: "constant string" ":"
#line 406 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1013 "dhcp4_parser.cc"
    break;

  case 56: // $@17: %empty
#line 415 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1024 "dhcp4_parser.cc"
    break;

  case 57: // syntax_map: "{" $@17 global_object "}"
#line 420 "dhcp4_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 58: // $@18: %empty
#line 430 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    // Prevent against duplicate.
    ctx.unique("Dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1052 "dhcp4_parser.cc"
    break;

  case 59: // global_object: "Dhcp4" $@18 ":" "{" global_params "}"
#line 439 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp4_parser.cc"
    break;

  case 60: // $@19: %empty
#line 447 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1072 "dhcp4_parser.cc"
    break;

  case 61: // sub_dhcp4: "{" $@19 global_params "}"
#line 451 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1081 "dhcp4_parser.cc"
    break;

  case 125: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 525 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1091 "dhcp4_parser.cc"
    break;

  case 126: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 531 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1101 "dhcp4_parser.cc"
    break;

  case 127: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 537 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1111 "dhcp4_parser.cc"
    break;

  case 128: // renew_timer: "renew-timer" ":" "integer"
#line 543 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 129: // rebind_timer: "rebind-timer" ":" "integer"
#line 549 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 130: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 555 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 131: // t1_percent: "t1-percent" ":" "floating point"
#line 561 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 132: // t2_percent: "t2-percent" ":" "floating point"
#line 567 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 133: // cache_threshold: "cache-threshold" ":" "floating point"
#line 573 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 134: // cache_max_age: "cache-max-age" ":" "integer"
#line 579 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 135: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 585 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 136: // $@20: %empty
#line 591 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1200 "dhcp4_parser.cc"
    break;

  case 137: // server_tag: "server-tag" $@20 ":" "constant string"
#line 594 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1210 "dhcp4_parser.cc"
    break;

  case 138: // echo_client_id: "echo-client-id" ":" "boolean"
#line 600 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1220 "dhcp4_parser.cc"
    break;

  case 139: // match_client_id: "match-client-id" ":" "boolean"
#line 606 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1230 "dhcp4_parser.cc"
    break;

  case 140: // authoritative: "authoritative" ":" "boolean"
#line 612 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 141: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 618 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 142: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 624 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 143: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 630 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1270 "dhcp4_parser.cc"
    break;

  case 144: // $@21: %empty
#line 636 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 145: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 639 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1288 "dhcp4_parser.cc"
    break;

  case 146: // ddns_replace_client_name_value: "when-present"
#line 645 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1296 "dhcp4_parser.cc"
    break;

  case 147: // ddns_replace_client_name_value: "never"
#line 648 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1304 "dhcp4_parser.cc"
    break;

  case 148: // ddns_replace_client_name_value: "always"
#line 651 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1312 "dhcp4_parser.cc"
    break;

  case 149: // ddns_replace_client_name_value: "when-not-present"
#line 654 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1320 "dhcp4_parser.cc"
    break;

  case 150: // ddns_replace_client_name_value: "boolean"
#line 657 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1329 "dhcp4_parser.cc"
    break;

  case 151: // $@22: %empty
#line 663 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp4_parser.cc"
    break;

  case 152: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 666 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1348 "dhcp4_parser.cc"
    break;

  case 153: // $@23: %empty
#line 672 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1357 "dhcp4_parser.cc"
    break;

  case 154: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 675 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1367 "dhcp4_parser.cc"
    break;

  case 155: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 681 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1377 "dhcp4_parser.cc"
    break;

  case 156: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 687 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1387 "dhcp4_parser.cc"
    break;

  case 157: // $@24: %empty
#line 693 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1396 "dhcp4_parser.cc"
    break;

  case 158: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 696 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1406 "dhcp4_parser.cc"
    break;

  case 159: // $@25: %empty
#line 702 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1415 "dhcp4_parser.cc"
    break;

  case 160: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 705 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1425 "dhcp4_parser.cc"
    break;

  case 161: // store_extended_info: "store-extended-info" ":" "boolean"
#line 711 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1435 "dhcp4_parser.cc"
    break;

  case 162: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 717 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1445 "dhcp4_parser.cc"
    break;

  case 163: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 723 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1455 "dhcp4_parser.cc"
    break;

  case 164: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 729 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 165: // $@26: %empty
#line 735 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1477 "dhcp4_parser.cc"
    break;

  case 166: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 741 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1487 "dhcp4_parser.cc"
    break;

  case 176: // $@27: %empty
#line 760 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1497 "dhcp4_parser.cc"
    break;

  case 177: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 764 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1506 "dhcp4_parser.cc"
    break;

  case 178: // $@28: %empty
#line 769 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1518 "dhcp4_parser.cc"
    break;

  case 179: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 775 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1527 "dhcp4_parser.cc"
    break;

  case 180: // $@29: %empty
#line 780 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 181: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 783 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 182: // socket_type: "raw"
#line 788 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1551 "dhcp4_parser.cc"
    break;

  case 183: // socket_type: "udp"
#line 789 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1557 "dhcp4_parser.cc"
    break;

  case 184: // $@30: %empty
#line 792 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 185: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 795 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1575 "dhcp4_parser.cc"
    break;

  case 186: // outbound_interface_value: "same-as-inbound"
#line 800 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1583 "dhcp4_parser.cc"
    break;

  case 187: // outbound_interface_value: "use-routing"
#line 802 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1591 "dhcp4_parser.cc"
    break;

  case 188: // re_detect: "re-detect" ":" "boolean"
#line 806 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1601 "dhcp4_parser.cc"
    break;

  case 189: // $@31: %empty
#line 813 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1613 "dhcp4_parser.cc"
    break;

  case 190: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 819 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 191: // $@32: %empty
#line 826 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1636 "dhcp4_parser.cc"
    break;

  case 192: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 832 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 196: // $@33: %empty
#line 842 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 197: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 845 "dhcp4_parser.yy"
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
#line 1674 "dhcp4_parser.cc"
    break;

  case 198: // $@34: %empty
#line 861 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1686 "dhcp4_parser.cc"
    break;

  case 199: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 867 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1697 "dhcp4_parser.cc"
    break;

  case 200: // $@35: %empty
#line 874 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1709 "dhcp4_parser.cc"
    break;

  case 201: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 880 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 206: // $@36: %empty
#line 893 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 207: // database: "{" $@36 database_map_params "}"
#line 897 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 232: // $@37: %empty
#line 931 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1747 "dhcp4_parser.cc"
    break;

  case 233: // database_type: "type" $@37 ":" db_type
#line 934 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1756 "dhcp4_parser.cc"
    break;

  case 234: // db_type: "memfile"
#line 939 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1762 "dhcp4_parser.cc"
    break;

  case 235: // db_type: "mysql"
#line 940 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1768 "dhcp4_parser.cc"
    break;

  case 236: // db_type: "postgresql"
#line 941 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1774 "dhcp4_parser.cc"
    break;

  case 237: // db_type: "cql"
#line 942 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1780 "dhcp4_parser.cc"
    break;

  case 238: // $@38: %empty
#line 945 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc"
    break;

  case 239: // user: "user" $@38 ":" "constant string"
#line 948 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1799 "dhcp4_parser.cc"
    break;

  case 240: // $@39: %empty
#line 954 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1808 "dhcp4_parser.cc"
    break;

  case 241: // password: "password" $@39 ":" "constant string"
#line 957 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 242: // $@40: %empty
#line 963 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1827 "dhcp4_parser.cc"
    break;

  case 243: // host: "host" $@40 ":" "constant string"
#line 966 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1837 "dhcp4_parser.cc"
    break;

  case 244: // port: "port" ":" "integer"
#line 972 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1847 "dhcp4_parser.cc"
    break;

  case 245: // $@41: %empty
#line 978 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1856 "dhcp4_parser.cc"
    break;

  case 246: // name: "name" $@41 ":" "constant string"
#line 981 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc"
    break;

  case 247: // persist: "persist" ":" "boolean"
#line 987 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1876 "dhcp4_parser.cc"
    break;

  case 248: // lfc_interval: "lfc-interval" ":" "integer"
#line 993 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1886 "dhcp4_parser.cc"
    break;

  case 249: // readonly: "readonly" ":" "boolean"
#line 999 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1896 "dhcp4_parser.cc"
    break;

  case 250: // connect_timeout: "connect-timeout" ":" "integer"
#line 1005 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1906 "dhcp4_parser.cc"
    break;

  case 251: // request_timeout: "request-timeout" ":" "integer"
#line 1011 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1916 "dhcp4_parser.cc"
    break;

  case 252: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1017 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 253: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1023 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1936 "dhcp4_parser.cc"
    break;

  case 254: // $@42: %empty
#line 1029 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1945 "dhcp4_parser.cc"
    break;

  case 255: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1032 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1955 "dhcp4_parser.cc"
    break;

  case 256: // $@43: %empty
#line 1038 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1964 "dhcp4_parser.cc"
    break;

  case 257: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1041 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1974 "dhcp4_parser.cc"
    break;

  case 258: // $@44: %empty
#line 1047 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp4_parser.cc"
    break;

  case 259: // consistency: "consistency" $@44 ":" "constant string"
#line 1050 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1993 "dhcp4_parser.cc"
    break;

  case 260: // $@45: %empty
#line 1056 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2002 "dhcp4_parser.cc"
    break;

  case 261: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1059 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2012 "dhcp4_parser.cc"
    break;

  case 262: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1065 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2022 "dhcp4_parser.cc"
    break;

  case 263: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1071 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2032 "dhcp4_parser.cc"
    break;

  case 264: // $@46: %empty
#line 1077 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2041 "dhcp4_parser.cc"
    break;

  case 265: // on_fail: "on-fail" $@46 ":" on_fail_mode
#line 1080 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 266: // on_fail_mode: "stop-retry-exit"
#line 1085 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2056 "dhcp4_parser.cc"
    break;

  case 267: // on_fail_mode: "serve-retry-exit"
#line 1086 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2062 "dhcp4_parser.cc"
    break;

  case 268: // on_fail_mode: "serve-retry-continue"
#line 1087 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2068 "dhcp4_parser.cc"
    break;

  case 269: // max_row_errors: "max-row-errors" ":" "integer"
#line 1090 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2078 "dhcp4_parser.cc"
    break;

  case 270: // $@47: %empty
#line 1097 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2090 "dhcp4_parser.cc"
    break;

  case 271: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1103 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 279: // duid_id: "duid"
#line 1119 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2108 "dhcp4_parser.cc"
    break;

  case 280: // hw_address_id: "hw-address"
#line 1124 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2117 "dhcp4_parser.cc"
    break;

  case 281: // circuit_id: "circuit-id"
#line 1129 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2126 "dhcp4_parser.cc"
    break;

  case 282: // client_id: "client-id"
#line 1134 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2135 "dhcp4_parser.cc"
    break;

  case 283: // flex_id: "flex-id"
#line 1139 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 284: // $@48: %empty
#line 1146 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2156 "dhcp4_parser.cc"
    break;

  case 285: // dhcp_multi_threading: "multi-threading" $@48 ":" "{" multi_threading_params "}"
#line 1152 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2167 "dhcp4_parser.cc"
    break;

  case 294: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1171 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2177 "dhcp4_parser.cc"
    break;

  case 295: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1177 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2187 "dhcp4_parser.cc"
    break;

  case 296: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1183 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2197 "dhcp4_parser.cc"
    break;

  case 297: // $@49: %empty
#line 1189 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 298: // hooks_libraries: "hooks-libraries" $@49 ":" "[" hooks_libraries_list "]"
#line 1195 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2218 "dhcp4_parser.cc"
    break;

  case 303: // $@50: %empty
#line 1208 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2228 "dhcp4_parser.cc"
    break;

  case 304: // hooks_library: "{" $@50 hooks_params "}"
#line 1212 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2238 "dhcp4_parser.cc"
    break;

  case 305: // $@51: %empty
#line 1218 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2248 "dhcp4_parser.cc"
    break;

  case 306: // sub_hooks_library: "{" $@51 hooks_params "}"
#line 1222 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2258 "dhcp4_parser.cc"
    break;

  case 312: // $@52: %empty
#line 1237 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2267 "dhcp4_parser.cc"
    break;

  case 313: // library: "library" $@52 ":" "constant string"
#line 1240 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2277 "dhcp4_parser.cc"
    break;

  case 314: // $@53: %empty
#line 1246 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2286 "dhcp4_parser.cc"
    break;

  case 315: // parameters: "parameters" $@53 ":" map_value
#line 1249 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2295 "dhcp4_parser.cc"
    break;

  case 316: // $@54: %empty
#line 1255 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 317: // expired_leases_processing: "expired-leases-processing" $@54 ":" "{" expired_leases_params "}"
#line 1261 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2317 "dhcp4_parser.cc"
    break;

  case 326: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1279 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2327 "dhcp4_parser.cc"
    break;

  case 327: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1285 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2337 "dhcp4_parser.cc"
    break;

  case 328: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1291 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 329: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1297 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 330: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1303 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2367 "dhcp4_parser.cc"
    break;

  case 331: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1309 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2377 "dhcp4_parser.cc"
    break;

  case 332: // $@55: %empty
#line 1318 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2389 "dhcp4_parser.cc"
    break;

  case 333: // subnet4_list: "subnet4" $@55 ":" "[" subnet4_list_content "]"
#line 1324 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 338: // $@56: %empty
#line 1344 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp4_parser.cc"
    break;

  case 339: // subnet4: "{" $@56 subnet4_params "}"
#line 1348 "dhcp4_parser.yy"
                                {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp4) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2434 "dhcp4_parser.cc"
    break;

  case 340: // $@57: %empty
#line 1370 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2444 "dhcp4_parser.cc"
    break;

  case 341: // sub_subnet4: "{" $@57 subnet4_params "}"
#line 1374 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2454 "dhcp4_parser.cc"
    break;

  case 389: // $@58: %empty
#line 1433 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2463 "dhcp4_parser.cc"
    break;

  case 390: // subnet: "subnet" $@58 ":" "constant string"
#line 1436 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 391: // $@59: %empty
#line 1442 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 392: // subnet_4o6_interface: "4o6-interface" $@59 ":" "constant string"
#line 1445 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 393: // $@60: %empty
#line 1451 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 394: // subnet_4o6_interface_id: "4o6-interface-id" $@60 ":" "constant string"
#line 1454 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2511 "dhcp4_parser.cc"
    break;

  case 395: // $@61: %empty
#line 1460 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2520 "dhcp4_parser.cc"
    break;

  case 396: // subnet_4o6_subnet: "4o6-subnet" $@61 ":" "constant string"
#line 1463 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2530 "dhcp4_parser.cc"
    break;

  case 397: // $@62: %empty
#line 1469 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2539 "dhcp4_parser.cc"
    break;

  case 398: // interface: "interface" $@62 ":" "constant string"
#line 1472 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2549 "dhcp4_parser.cc"
    break;

  case 399: // $@63: %empty
#line 1478 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2558 "dhcp4_parser.cc"
    break;

  case 400: // client_class: "client-class" $@63 ":" "constant string"
#line 1481 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2568 "dhcp4_parser.cc"
    break;

  case 401: // $@64: %empty
#line 1487 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 402: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1493 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp4_parser.cc"
    break;

  case 403: // reservations_global: "reservations-global" ":" "boolean"
#line 1498 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 404: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1504 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2609 "dhcp4_parser.cc"
    break;

  case 405: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1510 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2619 "dhcp4_parser.cc"
    break;

  case 406: // $@65: %empty
#line 1516 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2628 "dhcp4_parser.cc"
    break;

  case 407: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1519 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2637 "dhcp4_parser.cc"
    break;

  case 408: // hr_mode: "disabled"
#line 1524 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2643 "dhcp4_parser.cc"
    break;

  case 409: // hr_mode: "out-of-pool"
#line 1525 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2649 "dhcp4_parser.cc"
    break;

  case 410: // hr_mode: "global"
#line 1526 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2655 "dhcp4_parser.cc"
    break;

  case 411: // hr_mode: "all"
#line 1527 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2661 "dhcp4_parser.cc"
    break;

  case 412: // id: "id" ":" "integer"
#line 1530 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2671 "dhcp4_parser.cc"
    break;

  case 413: // $@66: %empty
#line 1538 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 414: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1544 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 419: // $@67: %empty
#line 1559 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 420: // shared_network: "{" $@67 shared_network_params "}"
#line 1563 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2710 "dhcp4_parser.cc"
    break;

  case 463: // $@68: %empty
#line 1617 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 464: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1623 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2731 "dhcp4_parser.cc"
    break;

  case 465: // $@69: %empty
#line 1631 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2740 "dhcp4_parser.cc"
    break;

  case 466: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1634 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2748 "dhcp4_parser.cc"
    break;

  case 471: // $@70: %empty
#line 1650 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2758 "dhcp4_parser.cc"
    break;

  case 472: // option_def_entry: "{" $@70 option_def_params "}"
#line 1654 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2770 "dhcp4_parser.cc"
    break;

  case 473: // $@71: %empty
#line 1665 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2780 "dhcp4_parser.cc"
    break;

  case 474: // sub_option_def: "{" $@71 option_def_params "}"
#line 1669 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 490: // code: "code" ":" "integer"
#line 1701 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 492: // $@72: %empty
#line 1709 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp4_parser.cc"
    break;

  case 493: // option_def_type: "type" $@72 ":" "constant string"
#line 1712 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 494: // $@73: %empty
#line 1718 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2830 "dhcp4_parser.cc"
    break;

  case 495: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1721 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2840 "dhcp4_parser.cc"
    break;

  case 496: // $@74: %empty
#line 1727 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp4_parser.cc"
    break;

  case 497: // space: "space" $@74 ":" "constant string"
#line 1730 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2859 "dhcp4_parser.cc"
    break;

  case 499: // $@75: %empty
#line 1738 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2868 "dhcp4_parser.cc"
    break;

  case 500: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1741 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2878 "dhcp4_parser.cc"
    break;

  case 501: // option_def_array: "array" ":" "boolean"
#line 1747 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2888 "dhcp4_parser.cc"
    break;

  case 502: // $@76: %empty
#line 1757 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 503: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1763 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 508: // $@77: %empty
#line 1782 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2919 "dhcp4_parser.cc"
    break;

  case 509: // option_data_entry: "{" $@77 option_data_params "}"
#line 1786 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2928 "dhcp4_parser.cc"
    break;

  case 510: // $@78: %empty
#line 1794 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2938 "dhcp4_parser.cc"
    break;

  case 511: // sub_option_data: "{" $@78 option_data_params "}"
#line 1798 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 526: // $@79: %empty
#line 1831 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2956 "dhcp4_parser.cc"
    break;

  case 527: // option_data_data: "data" $@79 ":" "constant string"
#line 1834 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2966 "dhcp4_parser.cc"
    break;

  case 530: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1844 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 531: // option_data_always_send: "always-send" ":" "boolean"
#line 1850 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2986 "dhcp4_parser.cc"
    break;

  case 532: // $@80: %empty
#line 1859 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2998 "dhcp4_parser.cc"
    break;

  case 533: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1865 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3007 "dhcp4_parser.cc"
    break;

  case 538: // $@81: %empty
#line 1880 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3017 "dhcp4_parser.cc"
    break;

  case 539: // pool_list_entry: "{" $@81 pool_params "}"
#line 1884 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3027 "dhcp4_parser.cc"
    break;

  case 540: // $@82: %empty
#line 1890 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3037 "dhcp4_parser.cc"
    break;

  case 541: // sub_pool4: "{" $@82 pool_params "}"
#line 1894 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3047 "dhcp4_parser.cc"
    break;

  case 551: // $@83: %empty
#line 1913 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3056 "dhcp4_parser.cc"
    break;

  case 552: // pool_entry: "pool" $@83 ":" "constant string"
#line 1916 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3066 "dhcp4_parser.cc"
    break;

  case 553: // $@84: %empty
#line 1922 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3074 "dhcp4_parser.cc"
    break;

  case 554: // user_context: "user-context" $@84 ":" map_value
#line 1924 "dhcp4_parser.yy"
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
#line 3101 "dhcp4_parser.cc"
    break;

  case 555: // $@85: %empty
#line 1947 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3109 "dhcp4_parser.cc"
    break;

  case 556: // comment: "comment" $@85 ":" "constant string"
#line 1949 "dhcp4_parser.yy"
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
#line 3138 "dhcp4_parser.cc"
    break;

  case 557: // $@86: %empty
#line 1977 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3150 "dhcp4_parser.cc"
    break;

  case 558: // reservations: "reservations" $@86 ":" "[" reservations_list "]"
#line 1983 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3159 "dhcp4_parser.cc"
    break;

  case 563: // $@87: %empty
#line 1996 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3169 "dhcp4_parser.cc"
    break;

  case 564: // reservation: "{" $@87 reservation_params "}"
#line 2000 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3178 "dhcp4_parser.cc"
    break;

  case 565: // $@88: %empty
#line 2005 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 566: // sub_reservation: "{" $@88 reservation_params "}"
#line 2009 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 586: // $@89: %empty
#line 2040 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 587: // next_server: "next-server" $@89 ":" "constant string"
#line 2043 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 588: // $@90: %empty
#line 2049 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 589: // server_hostname: "server-hostname" $@90 ":" "constant string"
#line 2052 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3235 "dhcp4_parser.cc"
    break;

  case 590: // $@91: %empty
#line 2058 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3244 "dhcp4_parser.cc"
    break;

  case 591: // boot_file_name: "boot-file-name" $@91 ":" "constant string"
#line 2061 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 592: // $@92: %empty
#line 2067 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 593: // ip_address: "ip-address" $@92 ":" "constant string"
#line 2070 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 594: // $@93: %empty
#line 2076 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3285 "dhcp4_parser.cc"
    break;

  case 595: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2082 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3294 "dhcp4_parser.cc"
    break;

  case 596: // $@94: %empty
#line 2087 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 597: // duid: "duid" $@94 ":" "constant string"
#line 2090 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3313 "dhcp4_parser.cc"
    break;

  case 598: // $@95: %empty
#line 2096 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 599: // hw_address: "hw-address" $@95 ":" "constant string"
#line 2099 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 600: // $@96: %empty
#line 2105 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3341 "dhcp4_parser.cc"
    break;

  case 601: // client_id_value: "client-id" $@96 ":" "constant string"
#line 2108 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3351 "dhcp4_parser.cc"
    break;

  case 602: // $@97: %empty
#line 2114 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3360 "dhcp4_parser.cc"
    break;

  case 603: // circuit_id_value: "circuit-id" $@97 ":" "constant string"
#line 2117 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3370 "dhcp4_parser.cc"
    break;

  case 604: // $@98: %empty
#line 2123 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3379 "dhcp4_parser.cc"
    break;

  case 605: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2126 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3389 "dhcp4_parser.cc"
    break;

  case 606: // $@99: %empty
#line 2132 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3398 "dhcp4_parser.cc"
    break;

  case 607: // hostname: "hostname" $@99 ":" "constant string"
#line 2135 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3408 "dhcp4_parser.cc"
    break;

  case 608: // $@100: %empty
#line 2141 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3420 "dhcp4_parser.cc"
    break;

  case 609: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2147 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3429 "dhcp4_parser.cc"
    break;

  case 610: // $@101: %empty
#line 2155 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3441 "dhcp4_parser.cc"
    break;

  case 611: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2161 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3450 "dhcp4_parser.cc"
    break;

  case 614: // $@102: %empty
#line 2173 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3462 "dhcp4_parser.cc"
    break;

  case 615: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2179 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3471 "dhcp4_parser.cc"
    break;

  case 618: // $@103: %empty
#line 2188 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3481 "dhcp4_parser.cc"
    break;

  case 619: // client_class_entry: "{" $@103 client_class_params "}"
#line 2192 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3491 "dhcp4_parser.cc"
    break;

  case 639: // $@104: %empty
#line 2224 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3500 "dhcp4_parser.cc"
    break;

  case 640: // client_class_test: "test" $@104 ":" "constant string"
#line 2227 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3510 "dhcp4_parser.cc"
    break;

  case 641: // only_if_required: "only-if-required" ":" "boolean"
#line 2233 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3520 "dhcp4_parser.cc"
    break;

  case 642: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2241 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3530 "dhcp4_parser.cc"
    break;

  case 643: // $@105: %empty
#line 2249 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3542 "dhcp4_parser.cc"
    break;

  case 644: // control_socket: "control-socket" $@105 ":" "{" control_socket_params "}"
#line 2255 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3551 "dhcp4_parser.cc"
    break;

  case 652: // $@106: %empty
#line 2271 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3560 "dhcp4_parser.cc"
    break;

  case 653: // control_socket_type: "socket-type" $@106 ":" "constant string"
#line 2274 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3570 "dhcp4_parser.cc"
    break;

  case 654: // $@107: %empty
#line 2280 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3579 "dhcp4_parser.cc"
    break;

  case 655: // control_socket_name: "socket-name" $@107 ":" "constant string"
#line 2283 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3589 "dhcp4_parser.cc"
    break;

  case 656: // $@108: %empty
#line 2292 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3601 "dhcp4_parser.cc"
    break;

  case 657: // dhcp_queue_control: "dhcp-queue-control" $@108 ":" "{" queue_control_params "}"
#line 2298 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 666: // enable_queue: "enable-queue" ":" "boolean"
#line 2317 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 667: // $@109: %empty
#line 2323 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3631 "dhcp4_parser.cc"
    break;

  case 668: // queue_type: "queue-type" $@109 ":" "constant string"
#line 2326 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 669: // capacity: "capacity" ":" "integer"
#line 2332 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3651 "dhcp4_parser.cc"
    break;

  case 670: // $@110: %empty
#line 2338 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3660 "dhcp4_parser.cc"
    break;

  case 671: // arbitrary_map_entry: "constant string" $@110 ":" value
#line 2341 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3669 "dhcp4_parser.cc"
    break;

  case 672: // $@111: %empty
#line 2348 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3681 "dhcp4_parser.cc"
    break;

  case 673: // dhcp_ddns: "dhcp-ddns" $@111 ":" "{" dhcp_ddns_params "}"
#line 2354 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3692 "dhcp4_parser.cc"
    break;

  case 674: // $@112: %empty
#line 2361 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 675: // sub_dhcp_ddns: "{" $@112 dhcp_ddns_params "}"
#line 2365 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 696: // enable_updates: "enable-updates" ":" "boolean"
#line 2395 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 697: // $@113: %empty
#line 2401 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3731 "dhcp4_parser.cc"
    break;

  case 698: // server_ip: "server-ip" $@113 ":" "constant string"
#line 2404 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 699: // server_port: "server-port" ":" "integer"
#line 2410 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 700: // $@114: %empty
#line 2416 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 701: // sender_ip: "sender-ip" $@114 ":" "constant string"
#line 2419 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3770 "dhcp4_parser.cc"
    break;

  case 702: // sender_port: "sender-port" ":" "integer"
#line 2425 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 703: // max_queue_size: "max-queue-size" ":" "integer"
#line 2431 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3790 "dhcp4_parser.cc"
    break;

  case 704: // $@115: %empty
#line 2437 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3799 "dhcp4_parser.cc"
    break;

  case 705: // ncr_protocol: "ncr-protocol" $@115 ":" ncr_protocol_value
#line 2440 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 706: // ncr_protocol_value: "udp"
#line 2446 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3814 "dhcp4_parser.cc"
    break;

  case 707: // ncr_protocol_value: "tcp"
#line 2447 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3820 "dhcp4_parser.cc"
    break;

  case 708: // $@116: %empty
#line 2450 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3829 "dhcp4_parser.cc"
    break;

  case 709: // ncr_format: "ncr-format" $@116 ":" "JSON"
#line 2453 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3839 "dhcp4_parser.cc"
    break;

  case 710: // $@117: %empty
#line 2460 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3848 "dhcp4_parser.cc"
    break;

  case 711: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2463 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 712: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2470 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3868 "dhcp4_parser.cc"
    break;

  case 713: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2477 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3878 "dhcp4_parser.cc"
    break;

  case 714: // $@118: %empty
#line 2484 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3887 "dhcp4_parser.cc"
    break;

  case 715: // dep_replace_client_name: "replace-client-name" $@118 ":" ddns_replace_client_name_value
#line 2487 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3896 "dhcp4_parser.cc"
    break;

  case 716: // $@119: %empty
#line 2493 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3905 "dhcp4_parser.cc"
    break;

  case 717: // dep_generated_prefix: "generated-prefix" $@119 ":" "constant string"
#line 2496 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3915 "dhcp4_parser.cc"
    break;

  case 718: // $@120: %empty
#line 2503 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3924 "dhcp4_parser.cc"
    break;

  case 719: // dep_hostname_char_set: "hostname-char-set" $@120 ":" "constant string"
#line 2506 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3934 "dhcp4_parser.cc"
    break;

  case 720: // $@121: %empty
#line 2513 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3943 "dhcp4_parser.cc"
    break;

  case 721: // dep_hostname_char_replacement: "hostname-char-replacement" $@121 ":" "constant string"
#line 2516 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3953 "dhcp4_parser.cc"
    break;

  case 722: // $@122: %empty
#line 2525 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3965 "dhcp4_parser.cc"
    break;

  case 723: // config_control: "config-control" $@122 ":" "{" config_control_params "}"
#line 2531 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3975 "dhcp4_parser.cc"
    break;

  case 724: // $@123: %empty
#line 2537 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3985 "dhcp4_parser.cc"
    break;

  case 725: // sub_config_control: "{" $@123 config_control_params "}"
#line 2541 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3994 "dhcp4_parser.cc"
    break;

  case 730: // $@124: %empty
#line 2556 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4006 "dhcp4_parser.cc"
    break;

  case 731: // config_databases: "config-databases" $@124 ":" "[" database_list "]"
#line 2562 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4015 "dhcp4_parser.cc"
    break;

  case 732: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2567 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4025 "dhcp4_parser.cc"
    break;

  case 733: // $@125: %empty
#line 2575 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4037 "dhcp4_parser.cc"
    break;

  case 734: // loggers: "loggers" $@125 ":" "[" loggers_entries "]"
#line 2581 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4046 "dhcp4_parser.cc"
    break;

  case 737: // $@126: %empty
#line 2593 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4056 "dhcp4_parser.cc"
    break;

  case 738: // logger_entry: "{" $@126 logger_params "}"
#line 2597 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4064 "dhcp4_parser.cc"
    break;

  case 748: // debuglevel: "debuglevel" ":" "integer"
#line 2614 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4074 "dhcp4_parser.cc"
    break;

  case 749: // $@127: %empty
#line 2620 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4083 "dhcp4_parser.cc"
    break;

  case 750: // severity: "severity" $@127 ":" "constant string"
#line 2623 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4093 "dhcp4_parser.cc"
    break;

  case 751: // $@128: %empty
#line 2629 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4105 "dhcp4_parser.cc"
    break;

  case 752: // output_options_list: "output_options" $@128 ":" "[" output_options_list_content "]"
#line 2635 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4114 "dhcp4_parser.cc"
    break;

  case 755: // $@129: %empty
#line 2644 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4124 "dhcp4_parser.cc"
    break;

  case 756: // output_entry: "{" $@129 output_params_list "}"
#line 2648 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4132 "dhcp4_parser.cc"
    break;

  case 764: // $@130: %empty
#line 2663 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4141 "dhcp4_parser.cc"
    break;

  case 765: // output: "output" $@130 ":" "constant string"
#line 2666 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4151 "dhcp4_parser.cc"
    break;

  case 766: // flush: "flush" ":" "boolean"
#line 2672 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4161 "dhcp4_parser.cc"
    break;

  case 767: // maxsize: "maxsize" ":" "integer"
#line 2678 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4171 "dhcp4_parser.cc"
    break;

  case 768: // maxver: "maxver" ":" "integer"
#line 2684 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4181 "dhcp4_parser.cc"
    break;

  case 769: // $@131: %empty
#line 2690 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4190 "dhcp4_parser.cc"
    break;

  case 770: // pattern: "pattern" $@131 ":" "constant string"
#line 2693 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4200 "dhcp4_parser.cc"
    break;

  case 771: // $@132: %empty
#line 2699 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4212 "dhcp4_parser.cc"
    break;

  case 772: // compatibility: "compatibility" $@132 ":" "{" compatibility_params "}"
#line 2705 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4221 "dhcp4_parser.cc"
    break;

  case 777: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2718 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4231 "dhcp4_parser.cc"
    break;


#line 4235 "dhcp4_parser.cc"

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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp4Parser::yytnamerr_ (const char *yystr)
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
  Dhcp4Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Dhcp4Parser::context.
  Dhcp4Parser::context::context (const Dhcp4Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Dhcp4Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  Dhcp4Parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  Dhcp4Parser::yysyntax_error_ (const context& yyctx) const
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


  const short Dhcp4Parser::yypact_ninf_ = -954;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     404,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,    28,    42,    30,    38,    41,    60,
      98,   110,   114,   124,   128,   163,   171,   177,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,    42,  -150,    87,   186,    71,   608,
      90,   266,     1,    79,   130,   -90,   416,   147,  -954,   101,
     193,   204,   230,   227,  -954,   231,  -954,  -954,  -954,   268,
     269,   276,  -954,  -954,  -954,  -954,  -954,  -954,   302,   308,
     318,   329,   342,   345,   352,   353,   360,   371,   372,  -954,
     379,   381,   383,   392,   396,  -954,  -954,  -954,   408,   410,
     411,  -954,  -954,  -954,  -954,  -954,  -954,  -954,   412,   413,
     414,  -954,  -954,  -954,  -954,  -954,   415,  -954,  -954,  -954,
    -954,  -954,  -954,   417,  -954,  -954,   419,  -954,    56,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,   420,  -954,   100,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,   422,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,   103,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,   115,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,   275,   312,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,   340,  -954,  -954,   423,
    -954,  -954,  -954,   427,  -954,  -954,   369,   395,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,   428,   429,  -954,  -954,  -954,  -954,   426,   432,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,   121,  -954,  -954,  -954,   434,  -954,  -954,   436,  -954,
     438,   439,  -954,  -954,   441,   442,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,   158,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,   443,   182,  -954,  -954,  -954,  -954,    42,    42,  -954,
    -147,   446,  -954,   452,   455,   457,   217,   233,   259,   459,
     460,   463,   464,   469,   471,   277,   280,   281,   284,   285,
     273,   287,   290,   291,   293,   296,   495,   299,   300,   301,
     303,   304,   499,   501,   506,   309,   317,   319,   507,   512,
     519,   520,   522,   524,   525,   327,   328,   331,   532,   536,
     537,   540,   542,   346,   547,   548,   550,   554,   555,   558,
     361,   559,   562,  -954,   186,  -954,   563,   564,   565,   380,
      71,  -954,   580,   581,   582,   583,   584,   600,   405,   601,
     604,   606,   608,  -954,   607,    90,  -954,   609,   610,   611,
     613,   614,   616,   617,   618,  -954,   266,  -954,   619,   620,
     425,   623,   624,   625,   409,  -954,    79,   626,   430,   437,
    -954,   130,   627,   628,    73,  -954,   444,   635,   637,   447,
     638,   448,   450,   641,   648,   451,   453,   649,   651,   653,
     654,   416,  -954,   659,   465,   147,  -954,  -954,  -954,   660,
     658,   672,   673,   674,  -954,  -954,  -954,   467,   482,   492,
     689,   691,   694,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,   500,  -954,  -954,  -954,  -954,  -954,
      32,   509,   516,  -954,  -954,  -954,   696,   701,   702,   712,
     711,   523,   295,  -954,  -954,  -954,   714,   719,   721,   722,
     723,  -954,   724,   725,   726,   727,   535,   538,  -954,   732,
     733,  -954,   734,   150,   207,  -954,  -954,   541,   543,   544,
     737,   545,   546,  -954,   734,   549,   740,  -954,   551,  -954,
     734,   552,   553,   556,   557,   560,   561,   566,  -954,   567,
     568,  -954,   569,   570,   571,  -954,  -954,   572,  -954,  -954,
    -954,   573,   711,  -954,  -954,   574,   575,  -954,   576,  -954,
    -954,    13,   586,  -954,  -954,    32,   577,   578,   579,  -954,
     743,  -954,  -954,    42,   186,   147,    71,   731,  -954,  -954,
    -954,   105,   105,   751,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,   752,   755,   756,   757,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,   -47,   758,   773,   776,   205,
      -2,   -64,   222,   416,  -954,  -954,   777,  -142,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,   778,
    -954,  -954,  -954,  -954,   -48,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,   751,  -954,   191,   226,   228,  -954,   238,
    -954,  -954,  -954,  -954,  -954,  -954,   746,   782,   783,   784,
     785,  -954,  -954,  -954,  -954,   786,   787,  -954,   788,   789,
     790,   791,  -954,   278,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,   279,  -954,   792,   793,
    -954,  -954,   794,   796,  -954,  -954,   795,   799,  -954,  -954,
     797,   801,  -954,  -954,   800,   802,  -954,  -954,  -954,  -954,
    -954,  -954,    49,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
      82,  -954,  -954,   803,   804,  -954,  -954,   805,   807,  -954,
     808,   809,   810,   811,   812,   813,   289,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,   814,   815,   816,  -954,   305,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
     311,  -954,  -954,  -954,   817,  -954,   818,  -954,  -954,  -954,
     313,  -954,  -954,  -954,  -954,  -954,   315,  -954,    93,  -954,
     819,  -954,   323,  -954,  -954,   597,  -954,   820,   821,  -954,
    -954,  -954,  -954,   822,   823,  -954,  -954,  -954,   824,   731,
    -954,   827,   828,   829,   830,   634,   622,   636,   633,   639,
     834,   835,   837,   838,   642,   643,   841,   645,   646,   647,
     650,   105,  -954,  -954,   105,  -954,   751,   608,  -954,   752,
      79,  -954,   755,   130,  -954,   756,  1224,  -954,   757,   -47,
    -954,   248,   758,  -954,   266,  -954,   773,   -90,  -954,   776,
     652,   655,   656,   657,   661,   662,   205,  -954,   663,   664,
     666,    -2,  -954,   844,   845,   -64,  -954,   665,   848,   668,
     850,   222,  -954,  -954,   201,   777,  -954,   667,  -142,  -954,
    -954,   849,   856,    90,  -954,   778,   857,  -954,  -954,   671,
    -954,   373,   675,   676,   677,  -954,  -954,  -954,  -954,  -954,
     678,   679,   680,   681,  -954,  -954,    15,  -954,  -954,  -954,
    -954,  -954,   326,  -954,   344,  -954,   852,  -954,   864,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,   355,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,   860,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,   865,   871,
    -954,  -954,  -954,  -954,  -954,   874,  -954,   362,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
     683,   684,  -954,  -954,   685,  -954,    42,  -954,  -954,   882,
    -954,  -954,  -954,  -954,  -954,   376,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,   687,   391,  -954,   734,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  1224,
    -954,   884,   686,  -954,   248,  -954,  -954,  -954,  -954,  -954,
    -954,   887,   693,   888,   201,  -954,  -954,  -954,  -954,  -954,
     695,  -954,  -954,   892,  -954,   698,  -954,  -954,   896,  -954,
    -954,   122,  -954,     5,   896,  -954,  -954,   901,   904,   909,
    -954,   394,  -954,  -954,  -954,  -954,  -954,  -954,  -954,   910,
     729,   728,   763,   931,     5,  -954,   747,  -954,  -954,  -954,
     765,  -954,  -954,  -954
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   176,     9,   340,    11,   540,    13,
     565,    15,   465,    17,   473,    19,   510,    21,   305,    23,
     674,    25,   724,    27,    45,    39,     0,     0,     0,     0,
       0,   567,     0,   475,   512,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   722,   165,   191,     0,
       0,     0,   586,   588,   590,   189,   198,   200,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   136,
       0,     0,     0,     0,     0,   144,   151,   153,     0,     0,
       0,   332,   463,   502,   413,   553,   555,   406,     0,     0,
       0,   270,   614,   557,   297,   316,     0,   284,   643,   656,
     672,   157,   159,     0,   733,   771,     0,   124,     0,    62,
      64,    65,    66,    67,    68,   102,   103,   104,   105,   106,
      69,    97,    86,    87,    88,   110,   111,   112,   113,   114,
     115,   116,   117,   108,   109,   118,   119,   120,   122,    72,
      73,    94,    74,    75,    76,   121,    80,    81,    70,    99,
     100,   101,    98,    71,    78,    79,    92,    93,    95,    89,
      90,    91,    77,    82,    83,    84,    85,    96,   107,   123,
     178,   180,   184,     0,   175,     0,   167,   169,   170,   171,
     172,   173,   174,   391,   393,   395,   532,   389,   397,     0,
     401,   399,   610,   388,   344,   345,   346,   347,   348,   372,
     373,   374,   375,   376,   362,   363,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,   387,     0,   342,   351,
     367,   368,   369,   352,   354,   355,   358,   359,   360,   357,
     353,   349,   350,   370,   371,   356,   364,   365,   366,   361,
     551,   550,   546,   547,   545,     0,   542,   544,   548,   549,
     608,   596,   598,   602,   600,   606,   604,   592,   585,   579,
     583,   584,     0,   568,   569,   580,   581,   582,   576,   571,
     577,   573,   574,   575,   578,   572,     0,   492,   245,     0,
     496,   494,   499,     0,   488,   489,     0,   476,   477,   479,
     491,   480,   481,   482,   498,   483,   484,   485,   486,   487,
     526,     0,     0,   524,   525,   528,   529,     0,   513,   514,
     516,   517,   518,   519,   520,   521,   522,   523,   312,   314,
     309,     0,   307,   310,   311,     0,   710,   697,     0,   700,
       0,     0,   704,   708,     0,     0,   714,   716,   718,   720,
     695,   693,   694,     0,   676,   678,   679,   680,   681,   682,
     683,   684,   685,   690,   686,   687,   688,   689,   691,   692,
     730,     0,     0,   726,   728,   729,    44,     0,     0,    37,
       0,     0,    57,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    55,     0,    61,     0,     0,     0,     0,
       0,   177,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   341,     0,     0,   541,     0,     0,     0,
       0,     0,     0,     0,     0,   566,     0,   466,     0,     0,
       0,     0,     0,     0,     0,   474,     0,     0,     0,     0,
     511,     0,     0,     0,     0,   306,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   675,     0,     0,     0,   725,    48,    41,     0,
       0,     0,     0,     0,   138,   139,   140,     0,     0,     0,
       0,     0,     0,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,     0,   162,   163,   141,   142,   143,
       0,     0,     0,   155,   156,   161,     0,     0,     0,     0,
       0,     0,     0,   403,   404,   405,     0,     0,     0,     0,
       0,   642,     0,     0,     0,     0,     0,     0,   164,     0,
       0,    63,     0,     0,     0,   188,   168,     0,     0,     0,
       0,     0,     0,   412,     0,     0,     0,   343,     0,   543,
       0,     0,     0,     0,     0,     0,     0,     0,   570,     0,
       0,   490,     0,     0,     0,   501,   478,     0,   530,   531,
     515,     0,     0,   308,   696,     0,     0,   699,     0,   702,
     703,     0,     0,   712,   713,     0,     0,     0,     0,   677,
       0,   732,   727,     0,     0,     0,     0,     0,   587,   589,
     591,     0,     0,   202,   137,   146,   147,   148,   149,   150,
     145,   152,   154,   334,   467,   504,   415,    38,   554,   556,
     408,   409,   410,   411,   407,     0,     0,   559,   299,     0,
       0,     0,     0,     0,   158,   160,     0,     0,    49,   179,
     182,   183,   181,   186,   187,   185,   392,   394,   396,   534,
     390,   398,   402,   400,     0,   552,   609,   597,   599,   603,
     601,   607,   605,   593,   493,   246,   497,   495,   500,   527,
     313,   315,   711,   698,   701,   706,   707,   705,   709,   715,
     717,   719,   721,   202,    42,     0,     0,     0,   196,     0,
     193,   195,   232,   238,   240,   242,     0,     0,     0,     0,
       0,   254,   256,   258,   260,     0,     0,   264,     0,     0,
       0,     0,   231,     0,   208,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   224,   225,   226,   220,   227,
     228,   229,   221,   222,   223,   230,     0,   206,     0,   203,
     204,   338,     0,   335,   336,   471,     0,   468,   469,   508,
       0,   505,   506,   419,     0,   416,   417,   279,   280,   281,
     282,   283,     0,   272,   274,   275,   276,   277,   278,   618,
       0,   616,   563,     0,   560,   561,   303,     0,   300,   301,
       0,     0,     0,     0,     0,     0,     0,   318,   320,   321,
     322,   323,   324,   325,     0,     0,     0,   293,     0,   286,
     288,   289,   290,   291,   292,   652,   654,   651,   649,   650,
       0,   645,   647,   648,     0,   667,     0,   670,   663,   664,
       0,   658,   660,   661,   662,   665,     0,   737,     0,   735,
       0,   776,     0,   773,   775,    51,   538,     0,   535,   536,
     594,   612,   613,     0,     0,    59,   723,   166,     0,     0,
     192,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   190,   199,     0,   201,     0,     0,   333,     0,
     475,   464,     0,   512,   503,     0,     0,   414,     0,     0,
     271,   620,     0,   615,   567,   558,     0,     0,   298,     0,
       0,     0,     0,     0,     0,     0,     0,   317,     0,     0,
       0,     0,   285,     0,     0,     0,   644,     0,     0,     0,
       0,     0,   657,   673,     0,     0,   734,     0,     0,   772,
      53,     0,    52,     0,   533,     0,     0,   611,   731,     0,
     194,     0,     0,     0,     0,   244,   247,   248,   249,   250,
       0,     0,     0,     0,   262,   263,     0,   251,   252,   253,
     269,   209,     0,   205,     0,   337,     0,   470,     0,   507,
     462,   441,   442,   443,   426,   427,   446,   447,   448,   449,
     450,   429,   430,   451,   452,   453,   454,   455,   456,   457,
     458,   459,   460,   461,   423,   424,   425,   439,   440,   436,
     437,   438,   435,     0,   421,   428,   444,   445,   431,   432,
     433,   434,   418,   273,   639,     0,   634,   635,   636,   637,
     638,   627,   628,   632,   633,   629,   630,   631,     0,   621,
     622,   624,   625,   626,   617,     0,   562,     0,   302,   326,
     327,   328,   329,   330,   331,   319,   294,   295,   296,   287,
       0,     0,   646,   666,     0,   669,     0,   659,   751,     0,
     749,   747,   741,   745,   746,     0,   739,   743,   744,   742,
     736,   777,   774,    50,     0,     0,   537,     0,   197,   234,
     235,   236,   237,   233,   239,   241,   243,   255,   257,   259,
     261,   266,   267,   268,   265,   207,   339,   472,   509,     0,
     420,     0,     0,   619,     0,   564,   304,   653,   655,   668,
     671,     0,     0,     0,     0,   738,    54,   539,   595,   422,
       0,   641,   623,     0,   748,     0,   740,   640,     0,   750,
     755,     0,   753,     0,     0,   752,   764,     0,     0,     0,
     769,     0,   757,   759,   760,   761,   762,   763,   754,     0,
       0,     0,     0,     0,     0,   756,     0,   766,   767,   768,
       0,   758,   765,   770
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,   -54,  -954,  -557,  -954,   175,
    -954,  -954,  -954,  -954,  -954,  -954,  -609,  -954,  -954,  -954,
     -67,  -954,  -954,  -954,  -954,  -954,  -954,   283,   494,     4,
      10,    23,   -40,   -23,   -12,    22,    25,    29,    33,  -954,
    -954,  -954,  -954,    35,    40,    43,    45,    46,    47,  -954,
     307,    50,  -954,    51,  -954,    53,    57,    58,  -954,    61,
    -954,    63,  -954,  -954,  -954,  -954,  -954,   297,   504,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,    99,  -954,  -954,  -954,  -954,
    -954,  -954,   235,  -954,    76,  -954,  -670,    34,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,   -33,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,    72,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,    48,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,    54,  -954,  -954,  -954,    66,   513,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,    52,  -954,  -954,  -954,  -954,  -954,
    -954,  -953,  -954,  -954,  -954,    81,  -954,  -954,  -954,    85,
     585,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -942,
    -954,   -65,  -954,    70,  -954,    64,    65,    68,    69,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,    77,  -954,  -954,  -135,
     -46,  -954,  -954,  -954,  -954,  -954,    84,  -954,  -954,  -954,
      88,  -954,   531,  -954,   -63,  -954,  -954,  -954,  -954,  -954,
     -42,  -954,  -954,  -954,  -954,  -954,   -35,  -954,  -954,  -954,
      86,  -954,  -954,  -954,    89,  -954,   528,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,    39,  -954,
    -954,  -954,    37,   589,  -954,  -954,   -51,  -954,    -8,  -954,
     -39,  -954,  -954,  -954,    80,  -954,  -954,  -954,    83,  -954,
     587,   -55,  -954,   -15,  -954,     3,  -954,   321,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -939,  -954,  -954,  -954,  -954,
    -954,    91,  -954,  -954,  -954,  -131,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,    67,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,    59,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,   348,   517,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,   384,   521,  -954,  -954,  -954,  -954,
    -954,  -954,    62,  -954,  -954,  -130,  -954,  -954,  -954,  -954,
    -954,  -954,  -149,  -954,  -954,  -166,  -954,  -954,  -954,  -954,
    -954,  -954,  -954,  -954,  -954,  -954,    78,  -954
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   698,
      82,    83,    39,    64,    79,    80,   719,   915,  1011,  1012,
     792,    41,    66,    85,   411,    43,    67,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   436,   162,   163,   164,   165,   166,   167,   168,   442,
     690,   169,   443,   170,   444,   171,   172,   173,   468,   174,
     469,   175,   176,   177,   178,   179,   414,   215,   216,    45,
      68,   217,   476,   218,   477,   722,   219,   478,   725,   220,
     180,   422,   181,   415,   769,   770,   771,   928,   182,   423,
     183,   424,   818,   819,   820,   954,   793,   794,   795,   931,
    1163,   796,   932,   797,   933,   798,   934,   799,   800,   509,
     801,   802,   803,   804,   805,   806,   807,   808,   940,   809,
     941,   810,   942,   811,   943,   812,   813,   814,   946,  1174,
     815,   184,   458,   842,   843,   844,   845,   846,   847,   848,
     185,   464,   878,   879,   880,   881,   882,   186,   461,   857,
     858,   859,   977,    59,    75,   361,   362,   363,   522,   364,
     523,   187,   462,   866,   867,   868,   869,   870,   871,   872,
     873,   188,   448,   822,   823,   824,   957,    47,    69,   257,
     258,   259,   486,   260,   482,   261,   483,   262,   484,   263,
     487,   264,   490,   265,   489,   189,   190,   191,   192,   454,
     704,   270,   193,   451,   834,   835,   836,   966,  1083,  1084,
     194,   449,    53,    72,   826,   827,   828,   960,    55,    73,
     326,   327,   328,   329,   330,   331,   332,   508,   333,   512,
     334,   511,   335,   336,   513,   337,   195,   450,   830,   831,
     832,   963,    57,    74,   347,   348,   349,   350,   351,   517,
     352,   353,   354,   355,   272,   485,   917,   918,   919,  1013,
      49,    70,   285,   286,   287,   494,   196,   452,   197,   453,
     198,   460,   853,   854,   855,   974,    51,    71,   302,   303,
     304,   199,   419,   200,   420,   201,   421,   308,   504,   922,
    1016,   309,   498,   310,   499,   311,   501,   312,   500,   313,
     503,   314,   502,   315,   497,   279,   491,   923,   202,   459,
     850,   851,   971,  1108,  1109,  1110,  1111,  1112,  1181,  1113,
     203,   204,   465,   890,   891,   892,   993,   893,   994,   205,
     466,   900,   901,   902,   903,   998,   904,   905,  1000,   206,
     467,    61,    76,   383,   384,   385,   386,   528,   387,   388,
     530,   389,   390,   391,   533,   757,   392,   534,   393,   527,
     394,   395,   396,   537,   397,   538,   398,   539,   399,   540,
     207,   413,    63,    77,   402,   403,   404,   543,   405,   208,
     471,   908,   909,  1004,  1145,  1146,  1147,  1148,  1193,  1149,
    1191,  1211,  1212,  1213,  1221,  1222,  1223,  1229,  1224,  1225,
    1226,  1227,  1233,   209,   472,   912,   913,   914
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     147,   214,   233,   281,   298,   282,   324,   343,   360,   380,
      78,   345,   816,  1075,   276,   732,   305,   221,   273,   288,
     300,   736,   338,   356,  1076,   381,   316,  1091,    28,   237,
     275,   755,   346,   697,   271,   284,   299,    40,   125,   126,
     325,   344,   358,   359,   910,    42,   238,    29,    44,    30,
      81,    31,   969,   549,   277,   970,   306,   239,   146,   474,
     222,   274,   289,   301,   475,   339,   357,    46,   382,  1171,
    1172,  1173,   278,   234,   307,   837,   838,   839,   840,   235,
     841,   297,   920,   885,   886,   972,   210,   211,   973,   122,
     212,   240,   236,   213,   241,   697,  1005,    84,   242,  1006,
     125,   126,   243,   480,   244,    48,   492,   406,   481,   245,
     146,   493,   246,   317,   247,   248,   249,    50,   495,   250,
     251,    52,   252,   496,   524,  1214,   253,   254,  1215,   525,
     255,    54,   256,   266,   267,    56,   146,   268,   269,   772,
     283,   874,   875,   876,   773,   774,   775,   776,   777,   778,
     779,   780,   781,   782,   783,   784,   785,   786,   787,   400,
     401,   541,   788,   789,   790,   791,   542,   720,   721,   318,
      58,   319,   320,   125,   126,   321,   322,   323,    60,   123,
     756,   125,   126,  1216,    62,   545,  1217,  1218,  1219,  1220,
     546,   280,   125,   126,   474,   318,   407,    86,   146,   925,
      87,   685,   686,   687,   688,   358,   359,   230,   408,    88,
     231,    89,    90,    91,    92,    93,    94,    95,    96,    97,
     318,   340,   319,   320,   341,   342,  1075,   723,   724,   545,
     410,   480,   125,   126,   926,   689,   927,  1076,   409,   412,
    1091,   929,    32,    33,    34,    35,   930,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   146,   416,   417,   122,   123,    92,    93,    94,   146,
     418,   951,   951,   505,  1042,   124,   952,   953,   125,   126,
     146,   318,   986,   127,    92,    93,    94,   987,   128,   129,
     130,   131,   132,   125,   126,   146,   425,   133,   991,    98,
      99,   100,   426,   992,   995,   506,  1001,   134,   541,   996,
     135,  1002,   427,  1003,   125,   126,  1008,   136,   137,   951,
     146,  1009,   138,   428,  1175,   139,   122,   123,   318,   140,
     860,   861,   862,   863,   864,   865,   429,   492,   507,   430,
     125,   126,  1176,   547,   548,   123,   431,   432,  1179,   141,
     142,   143,   144,  1180,   433,   524,  1094,  1095,   125,   126,
    1186,   145,   894,   895,   896,   434,   435,   515,  1138,  1194,
    1139,  1140,   290,   437,  1195,   438,   146,   439,   291,   292,
     293,   294,   295,   296,   495,   297,   440,  1234,   516,  1197,
     441,   146,  1235,   700,   701,   702,   703,   147,  1159,  1160,
    1161,  1162,   445,   214,   446,   447,   455,   456,   457,   463,
     554,   470,   897,   473,   479,   233,   488,   510,   281,   221,
     282,   514,   518,   519,   520,   521,   555,   276,   526,   298,
     529,   273,   531,   532,   288,   535,   536,   544,   146,   324,
     550,   305,   237,   275,   343,   300,   551,   271,   345,   552,
     284,   553,   556,   557,   558,   338,   146,   559,   560,   238,
     356,   299,   222,   561,   380,   562,   568,   277,   563,   346,
     239,   564,   565,   325,   274,   566,   567,   289,   344,   569,
     381,   306,   570,   571,   572,   278,   234,   573,   301,   574,
     575,   576,   235,   580,   577,   581,   578,   579,   339,   307,
     582,   586,   583,   357,   240,   236,   587,   241,   125,   126,
     584,   242,   585,   588,   589,   243,   590,   244,   591,   592,
     593,   594,   245,   382,   595,   246,   596,   247,   248,   249,
     597,   598,   250,   251,   599,   252,   600,   601,  1198,   253,
     254,   602,   603,   255,   604,   256,   266,   267,   605,   606,
     268,   269,   607,   609,   608,   283,   610,   612,   613,   614,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   615,   617,   618,   619,   620,   621,   378,
     379,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   622,   624,   623,   147,   625,   214,
     626,   628,   645,   630,   631,   632,   146,   633,   634,   764,
     635,   636,   637,   639,   640,   221,   641,   642,   643,   644,
     647,   651,   652,   648,    90,    91,    92,    93,    94,   655,
     649,   656,   658,   877,   887,   661,   380,   654,   657,   659,
     911,   660,   662,   665,   663,   666,   664,   667,   668,   883,
     888,   898,   381,   670,   673,   674,   671,   678,   222,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   675,
     676,   677,   679,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   680,   223,   224,   225,   681,   123,   682,   683,
     684,   693,   884,   889,   899,   382,   694,   695,   226,   691,
     125,   126,   227,   228,   229,   127,   692,   696,    30,   705,
     128,   129,   130,   699,   706,   230,   707,   708,   231,   133,
     709,   710,   711,   712,   713,   714,   232,   716,   715,   718,
     717,   726,   729,   727,   728,   730,   731,   734,   763,   733,
     935,   735,   737,   738,   758,   768,   739,   740,   817,   821,
     741,   742,   825,   829,   833,   849,   743,   744,   745,   746,
     747,   748,   749,   750,   752,   753,   754,   760,   761,   762,
     852,   141,   142,   856,   907,   916,   936,   937,   938,   939,
     944,   945,   947,   948,   949,   950,   956,  1010,   955,   959,
     958,   961,   962,   964,   965,   968,   967,   976,   146,   975,
     979,   978,   980,   981,   982,   983,   984,   985,   988,   989,
     990,   997,   999,  1007,  1015,  1026,  1014,   751,  1019,  1018,
    1017,  1021,  1022,  1023,  1024,  1025,  1028,  1027,  1030,  1031,
    1029,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1130,  1131,
    1039,  1040,  1134,  1119,  1136,  1153,  1120,  1121,  1122,  1154,
    1177,  1157,  1123,  1124,  1182,  1127,  1126,  1128,  1133,  1135,
    1151,  1158,  1178,  1183,  1184,  1164,  1165,  1166,  1167,  1168,
    1169,  1170,  1185,  1187,  1188,  1189,  1192,  1196,  1200,  1201,
     233,  1203,  1205,   324,  1204,  1207,   343,  1208,  1209,  1050,
     345,  1077,   276,  1210,  1096,  1230,   273,   298,  1231,   338,
     360,  1088,   356,  1232,  1236,  1086,  1105,   237,   275,   305,
    1103,   346,   271,   300,   877,  1101,  1054,   325,   887,  1238,
     344,  1085,  1237,  1074,   238,  1240,  1102,  1141,  1100,   299,
     883,   911,   277,  1055,   888,   239,   281,  1242,   282,   274,
     898,  1089,   339,  1143,  1056,   357,  1106,   765,  1087,   306,
     278,   234,   288,  1104,  1239,  1243,   301,   235,   611,  1090,
    1051,  1142,   759,   767,  1107,  1097,  1052,   307,   284,   240,
     236,  1098,   241,   884,   616,  1041,   242,   889,  1057,  1053,
     243,  1058,   244,   899,  1099,  1059,  1144,   245,   924,  1060,
     246,  1061,   247,   248,   249,   289,  1062,   250,   251,  1063,
     252,  1064,  1065,  1066,   253,   254,  1067,  1068,   255,  1069,
     256,   266,   267,  1070,  1071,   268,   269,  1072,  1020,  1073,
    1079,  1080,  1043,  1118,  1081,  1082,  1078,   653,  1125,  1129,
    1045,  1093,  1044,  1117,  1199,  1092,  1047,   646,  1046,   650,
    1155,  1049,  1048,  1202,  1156,   921,  1116,  1115,   669,   766,
    1137,   906,  1132,  1114,  1206,  1228,   672,  1150,  1241,     0,
       0,     0,     0,     0,     0,     0,     0,   627,     0,     0,
       0,     0,  1190,   283,   629,     0,  1152,     0,     0,     0,
       0,     0,     0,   638,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1050,     0,  1077,     0,     0,  1096,     0,     0,
       0,     0,     0,     0,  1088,     0,     0,  1141,  1086,  1105,
       0,     0,     0,  1103,     0,     0,     0,     0,  1101,  1054,
       0,     0,     0,  1143,  1085,     0,  1074,     0,     0,  1102,
       0,  1100,     0,     0,     0,     0,  1055,     0,     0,     0,
       0,  1142,     0,     0,  1089,     0,     0,  1056,     0,  1106,
       0,  1087,     0,     0,     0,     0,  1104,     0,     0,     0,
       0,     0,  1090,  1051,     0,     0,  1144,  1107,  1097,  1052,
       0,     0,     0,     0,  1098,     0,     0,     0,     0,     0,
       0,  1057,  1053,     0,  1058,     0,     0,  1099,  1059,     0,
       0,     0,  1060,     0,  1061,     0,     0,     0,     0,  1062,
       0,     0,  1063,     0,  1064,  1065,  1066,     0,     0,  1067,
    1068,     0,  1069,     0,     0,     0,  1070,  1071,     0,     0,
    1072,     0,  1073,  1079,  1080,     0,     0,  1081,  1082,  1078,
      90,    91,    92,    93,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,     0,     0,     0,     0,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,   123,   318,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   125,   126,     0,   228,
       0,   127,     0,     0,     0,     0,   128,   129,   130,     0,
       0,   230,     0,     0,   231,     0,     0,     0,     0,     0,
       0,     0,   232,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   141,   142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   146
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,    74,   682,   966,    69,   624,    71,    68,    69,    70,
      71,   630,    73,    74,   966,    76,    72,   966,     0,    69,
      69,    18,    74,   590,    69,    70,    71,     7,   102,   103,
      73,    74,   132,   133,   186,     7,    69,     5,     7,     7,
     200,     9,     3,   200,    69,     6,    71,    69,   200,     3,
      68,    69,    70,    71,     8,    73,    74,     7,    76,    54,
      55,    56,    69,    69,    71,   122,   123,   124,   125,    69,
     127,   129,   130,   147,   148,     3,    15,    16,     6,    88,
      19,    69,    69,    22,    69,   652,     3,    10,    69,     6,
     102,   103,    69,     3,    69,     7,     3,     6,     8,    69,
     200,     8,    69,    34,    69,    69,    69,     7,     3,    69,
      69,     7,    69,     8,     3,     3,    69,    69,     6,     8,
      69,     7,    69,    69,    69,     7,   200,    69,    69,    34,
      70,   143,   144,   145,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    12,
      13,     3,    57,    58,    59,    60,     8,    17,    18,    90,
       7,    92,    93,   102,   103,    96,    97,    98,     7,    89,
     167,   102,   103,   178,     7,     3,   181,   182,   183,   184,
       8,   101,   102,   103,     3,    90,     3,    11,   200,     8,
      14,   169,   170,   171,   172,   132,   133,   117,     4,    23,
     120,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      90,    91,    92,    93,    94,    95,  1179,    20,    21,     3,
       3,     3,   102,   103,     8,   203,     8,  1179,     8,     8,
    1179,     3,   200,   201,   202,   203,     8,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,   200,     4,     4,    88,    89,    28,    29,    30,   200,
       4,     3,     3,     8,   954,    99,     8,     8,   102,   103,
     200,    90,     3,   107,    28,    29,    30,     8,   112,   113,
     114,   115,   116,   102,   103,   200,     4,   121,     3,    61,
      62,    63,     4,     8,     3,     3,     3,   131,     3,     8,
     134,     8,     4,     8,   102,   103,     3,   141,   142,     3,
     200,     8,   146,     4,     8,   149,    88,    89,    90,   153,
     135,   136,   137,   138,   139,   140,     4,     3,     8,     4,
     102,   103,     8,   407,   408,    89,     4,     4,     3,   173,
     174,   175,   176,     8,     4,     3,   118,   119,   102,   103,
       8,   185,   150,   151,   152,     4,     4,     8,   177,     3,
     179,   180,   116,     4,     8,     4,   200,     4,   122,   123,
     124,   125,   126,   127,     3,   129,     4,     3,     3,     8,
       4,   200,     8,   108,   109,   110,   111,   474,    35,    36,
      37,    38,     4,   480,     4,     4,     4,     4,     4,     4,
     203,     4,   200,     4,     4,   492,     4,     4,   495,   480,
     495,     4,     4,     4,     8,     3,   203,   492,     4,   506,
       4,   492,     4,     4,   495,     4,     4,     4,   200,   516,
       4,   506,   492,   492,   521,   506,     4,   492,   521,     4,
     495,     4,   203,     4,     4,   516,   200,     4,     4,   492,
     521,   506,   480,     4,   541,     4,   203,   492,   201,   521,
     492,   201,   201,   516,   492,   201,   201,   495,   521,   202,
     541,   506,   202,   202,   201,   492,   492,   201,   506,     4,
     201,   201,   492,     4,   203,     4,   203,   203,   516,   506,
       4,     4,   203,   521,   492,   492,     4,   492,   102,   103,
     203,   492,   203,     4,     4,   492,     4,   492,     4,     4,
     203,   203,   492,   541,   203,   492,     4,   492,   492,   492,
       4,     4,   492,   492,     4,   492,     4,   201,  1157,   492,
     492,     4,     4,   492,     4,   492,   492,   492,     4,     4,
     492,   492,     4,     4,   203,   495,     4,     4,     4,     4,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   203,     4,     4,     4,     4,     4,   173,
     174,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,     4,     4,   201,   674,     4,   676,
       4,     4,   203,     4,     4,     4,   200,     4,     4,   673,
       4,     4,     4,     4,     4,   676,   201,     4,     4,     4,
       4,     4,     4,   203,    26,    27,    28,    29,    30,     4,
     203,     4,     4,   710,   711,     4,   713,   203,   201,   201,
     717,   201,     4,     4,   203,     4,   203,     4,     4,   710,
     711,   712,   713,     4,     4,     7,   201,   200,   676,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,     7,
       7,     7,   200,    75,    76,    77,    78,    79,    80,    81,
      82,    83,   200,    85,    86,    87,     7,    89,     7,     5,
     200,     5,   710,   711,   712,   713,     5,     5,   100,   200,
     102,   103,   104,   105,   106,   107,   200,     5,     7,     5,
     112,   113,   114,   200,     5,   117,     5,     5,   120,   121,
       7,     7,     7,     7,     7,   200,   128,     5,   200,     5,
       7,   200,     5,   200,   200,   200,   200,     7,     5,   200,
       4,   200,   200,   200,   168,    24,   200,   200,     7,     7,
     200,   200,     7,     7,     7,     7,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
       7,   173,   174,     7,     7,     7,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,   200,     6,     3,
       6,     6,     3,     6,     3,     3,     6,     3,   200,     6,
       3,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   203,     6,   652,     4,     6,
       8,     4,     4,     4,     4,   201,   203,   201,     4,     4,
     201,     4,     4,   201,   201,     4,   201,   201,     4,     4,
     203,   201,     4,   201,     4,     6,   201,   201,   201,     3,
       8,     4,   201,   201,     4,   201,   203,   201,   203,   201,
     203,   200,     8,     8,     3,   200,   200,   200,   200,   200,
     200,   200,     8,   200,   200,   200,     4,   200,     4,   203,
     957,     4,     4,   960,   201,   200,   963,     5,   200,   966,
     963,   966,   957,     7,   971,     4,   957,   974,     4,   960,
     977,   966,   963,     4,     4,   966,   971,   957,   957,   974,
     971,   963,   957,   974,   991,   971,   966,   960,   995,   201,
     963,   966,   203,   966,   957,     4,   971,  1004,   971,   974,
     991,  1008,   957,   966,   995,   957,  1013,   200,  1013,   957,
    1001,   966,   960,  1004,   966,   963,   971,   674,   966,   974,
     957,   957,  1013,   971,   201,   200,   974,   957,   474,   966,
     966,  1004,   665,   676,   971,   971,   966,   974,  1013,   957,
     957,   971,   957,   991,   480,   951,   957,   995,   966,   966,
     957,   966,   957,  1001,   971,   966,  1004,   957,   763,   966,
     957,   966,   957,   957,   957,  1013,   966,   957,   957,   966,
     957,   966,   966,   966,   957,   957,   966,   966,   957,   966,
     957,   957,   957,   966,   966,   957,   957,   966,   929,   966,
     966,   966,   956,   979,   966,   966,   966,   524,   986,   991,
     959,   969,   957,   977,  1179,   968,   962,   516,   960,   521,
    1013,   965,   963,  1184,  1015,   734,   976,   974,   541,   675,
    1001,   713,   995,   972,  1194,  1214,   545,  1005,  1234,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   492,    -1,    -1,
      -1,    -1,  1136,  1013,   495,    -1,  1008,    -1,    -1,    -1,
      -1,    -1,    -1,   506,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1179,    -1,  1179,    -1,    -1,  1184,    -1,    -1,
      -1,    -1,    -1,    -1,  1179,    -1,    -1,  1194,  1179,  1184,
      -1,    -1,    -1,  1184,    -1,    -1,    -1,    -1,  1184,  1179,
      -1,    -1,    -1,  1194,  1179,    -1,  1179,    -1,    -1,  1184,
      -1,  1184,    -1,    -1,    -1,    -1,  1179,    -1,    -1,    -1,
      -1,  1194,    -1,    -1,  1179,    -1,    -1,  1179,    -1,  1184,
      -1,  1179,    -1,    -1,    -1,    -1,  1184,    -1,    -1,    -1,
      -1,    -1,  1179,  1179,    -1,    -1,  1194,  1184,  1184,  1179,
      -1,    -1,    -1,    -1,  1184,    -1,    -1,    -1,    -1,    -1,
      -1,  1179,  1179,    -1,  1179,    -1,    -1,  1184,  1179,    -1,
      -1,    -1,  1179,    -1,  1179,    -1,    -1,    -1,    -1,  1179,
      -1,    -1,  1179,    -1,  1179,  1179,  1179,    -1,    -1,  1179,
    1179,    -1,  1179,    -1,    -1,    -1,  1179,  1179,    -1,    -1,
    1179,    -1,  1179,  1179,  1179,    -1,    -1,  1179,  1179,  1179,
      26,    27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    89,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,    -1,   105,
      -1,   107,    -1,    -1,    -1,    -1,   112,   113,   114,    -1,
      -1,   117,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   173,   174,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   200
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,     0,     5,
       7,     9,   200,   201,   202,   203,   219,   220,   221,   226,
       7,   235,     7,   239,     7,   283,     7,   391,     7,   474,
       7,   490,     7,   426,     7,   432,     7,   456,     7,   367,
       7,   555,     7,   586,   227,   222,   236,   240,   284,   392,
     475,   491,   427,   433,   457,   368,   556,   587,   219,   228,
     229,   200,   224,   225,    10,   237,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    88,    89,    99,   102,   103,   107,   112,   113,
     114,   115,   116,   121,   131,   134,   141,   142,   146,   149,
     153,   173,   174,   175,   176,   185,   200,   234,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   256,   257,   258,   259,   260,   261,   262,   265,
     267,   269,   270,   271,   273,   275,   276,   277,   278,   279,
     294,   296,   302,   304,   345,   354,   361,   375,   385,   409,
     410,   411,   412,   416,   424,   450,   480,   482,   484,   495,
     497,   499,   522,   534,   535,   543,   553,   584,   593,   617,
      15,    16,    19,    22,   234,   281,   282,   285,   287,   290,
     293,   480,   482,    85,    86,    87,   100,   104,   105,   106,
     117,   120,   128,   234,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   257,   258,   259,   260,   261,   262,
     265,   267,   269,   270,   271,   273,   275,   393,   394,   395,
     397,   399,   401,   403,   405,   407,   409,   410,   411,   412,
     415,   450,   468,   480,   482,   484,   495,   497,   499,   519,
     101,   234,   405,   407,   450,   476,   477,   478,   480,   482,
     116,   122,   123,   124,   125,   126,   127,   129,   234,   450,
     480,   482,   492,   493,   494,   495,   497,   499,   501,   505,
     507,   509,   511,   513,   515,   517,   424,    34,    90,    92,
      93,    96,    97,    98,   234,   322,   434,   435,   436,   437,
     438,   439,   440,   442,   444,   446,   447,   449,   480,   482,
      91,    94,    95,   234,   322,   438,   444,   458,   459,   460,
     461,   462,   464,   465,   466,   467,   480,   482,   132,   133,
     234,   369,   370,   371,   373,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   173,   174,
     234,   480,   482,   557,   558,   559,   560,   562,   563,   565,
     566,   567,   570,   572,   574,   575,   576,   578,   580,   582,
      12,    13,   588,   589,   590,   592,     6,     3,     4,     8,
       3,   238,     8,   585,   280,   297,     4,     4,     4,   496,
     498,   500,   295,   303,   305,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   255,     4,     4,     4,
       4,     4,   263,   266,   268,     4,     4,     4,   386,   425,
     451,   417,   481,   483,   413,     4,     4,     4,   346,   523,
     485,   362,   376,     4,   355,   536,   544,   554,   272,   274,
       4,   594,   618,     4,     3,     8,   286,   288,   291,     4,
       3,     8,   398,   400,   402,   469,   396,   404,     4,   408,
     406,   520,     3,     8,   479,     3,     8,   518,   506,   508,
     512,   510,   516,   514,   502,     8,     3,     8,   441,   323,
       4,   445,   443,   448,     4,     8,     3,   463,     4,     4,
       8,     3,   372,   374,     3,     8,     4,   573,   561,     4,
     564,     4,     4,   568,   571,     4,     4,   577,   579,   581,
     583,     3,     8,   591,     4,     3,     8,   219,   219,   200,
       4,     4,     4,     4,   203,   203,   203,     4,     4,     4,
       4,     4,     4,   201,   201,   201,   201,   201,   203,   202,
     202,   202,   201,   201,     4,   201,   201,   203,   203,   203,
       4,     4,     4,   203,   203,   203,     4,     4,     4,     4,
       4,     4,     4,   203,   203,   203,     4,     4,     4,     4,
       4,   201,     4,     4,     4,     4,     4,     4,   203,     4,
       4,   242,     4,     4,     4,   203,   282,     4,     4,     4,
       4,     4,     4,   201,     4,     4,     4,   394,     4,   477,
       4,     4,     4,     4,     4,     4,     4,     4,   494,     4,
       4,   201,     4,     4,     4,   203,   436,     4,   203,   203,
     460,     4,     4,   370,   203,     4,     4,   201,     4,   201,
     201,     4,     4,   203,   203,     4,     4,     4,     4,   558,
       4,   201,   589,     4,     7,     7,     7,     7,   200,   200,
     200,     7,     7,     5,   200,   169,   170,   171,   172,   203,
     264,   200,   200,     5,     5,     5,     5,   221,   223,   200,
     108,   109,   110,   111,   414,     5,     5,     5,     5,     7,
       7,     7,     7,     7,   200,   200,     5,     7,     5,   230,
      17,    18,   289,    20,    21,   292,   200,   200,   200,     5,
     200,   200,   230,   200,     7,   200,   230,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   223,   200,   200,   200,    18,   167,   569,   168,   264,
     200,   200,   200,     5,   219,   241,   588,   281,    24,   298,
     299,   300,    34,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    57,    58,
      59,    60,   234,   310,   311,   312,   315,   317,   319,   321,
     322,   324,   325,   326,   327,   328,   329,   330,   331,   333,
     335,   337,   339,   340,   341,   344,   310,     7,   306,   307,
     308,     7,   387,   388,   389,     7,   428,   429,   430,     7,
     452,   453,   454,     7,   418,   419,   420,   122,   123,   124,
     125,   127,   347,   348,   349,   350,   351,   352,   353,     7,
     524,   525,     7,   486,   487,   488,     7,   363,   364,   365,
     135,   136,   137,   138,   139,   140,   377,   378,   379,   380,
     381,   382,   383,   384,   143,   144,   145,   234,   356,   357,
     358,   359,   360,   480,   482,   147,   148,   234,   480,   482,
     537,   538,   539,   541,   150,   151,   152,   200,   480,   482,
     545,   546,   547,   548,   550,   551,   557,     7,   595,   596,
     186,   234,   619,   620,   621,   231,     7,   470,   471,   472,
     130,   501,   503,   521,   306,     8,     8,     8,   301,     3,
       8,   313,   316,   318,   320,     4,     4,     4,     4,     4,
     332,   334,   336,   338,     4,     4,   342,     4,     4,     4,
       4,     3,     8,     8,   309,     6,     3,   390,     6,     3,
     431,     6,     3,   455,     6,     3,   421,     6,     3,     3,
       6,   526,     3,     6,   489,     6,     3,   366,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   540,   542,     3,     8,     4,   549,     4,
     552,     3,     8,     8,   597,     3,     6,     4,     3,     8,
     200,   232,   233,   473,     6,     3,   504,     8,     6,     4,
     299,     4,     4,     4,     4,   201,   203,   201,   203,   201,
       4,     4,     4,     4,   201,   201,     4,   201,   201,   203,
     201,   311,   310,   308,   393,   389,   434,   430,   458,   454,
     234,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   257,   258,   259,   260,   261,   262,   265,   267,   269,
     270,   271,   273,   275,   322,   385,   403,   405,   407,   409,
     410,   411,   412,   422,   423,   450,   480,   482,   495,   497,
     499,   519,   420,   348,   118,   119,   234,   243,   244,   245,
     322,   424,   450,   480,   482,   495,   497,   499,   527,   528,
     529,   530,   531,   533,   525,   492,   488,   369,   365,   201,
     201,   201,   201,   201,   201,   378,   203,   201,   201,   357,
       4,     4,   538,   203,     4,   201,     4,   546,   177,   179,
     180,   234,   322,   480,   482,   598,   599,   600,   601,   603,
     596,   203,   620,     6,     3,   476,   472,     4,   200,    35,
      36,    37,    38,   314,   200,   200,   200,   200,   200,   200,
     200,    54,    55,    56,   343,     8,     8,     8,     8,     3,
       8,   532,     4,     8,     3,     8,     8,   200,   200,   200,
     219,   604,     4,   602,     3,     8,   200,     8,   230,   423,
       4,   203,   529,     4,   201,     4,   599,   200,     5,   200,
       7,   605,   606,   607,     3,     6,   178,   181,   182,   183,
     184,   608,   609,   610,   612,   613,   614,   615,   606,   611,
       4,     4,     4,   616,     3,     8,     4,   203,   201,   201,
       4,   609,   200,   200
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   204,   206,   205,   207,   205,   208,   205,   209,   205,
     210,   205,   211,   205,   212,   205,   213,   205,   214,   205,
     215,   205,   216,   205,   217,   205,   218,   205,   219,   219,
     219,   219,   219,   219,   219,   220,   222,   221,   223,   224,
     224,   225,   225,   227,   226,   228,   228,   229,   229,   231,
     230,   232,   232,   233,   233,   234,   236,   235,   238,   237,
     240,   239,   241,   241,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   255,   254,   256,   257,
     258,   259,   260,   261,   263,   262,   264,   264,   264,   264,
     264,   266,   265,   268,   267,   269,   270,   272,   271,   274,
     273,   275,   276,   277,   278,   280,   279,   281,   281,   282,
     282,   282,   282,   282,   282,   282,   284,   283,   286,   285,
     288,   287,   289,   289,   291,   290,   292,   292,   293,   295,
     294,   297,   296,   298,   298,   299,   301,   300,   303,   302,
     305,   304,   306,   306,   307,   307,   309,   308,   310,   310,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   313,   312,   314,   314,   314,   314,   316,   315,
     318,   317,   320,   319,   321,   323,   322,   324,   325,   326,
     327,   328,   329,   330,   332,   331,   334,   333,   336,   335,
     338,   337,   339,   340,   342,   341,   343,   343,   343,   344,
     346,   345,   347,   347,   348,   348,   348,   348,   348,   349,
     350,   351,   352,   353,   355,   354,   356,   356,   357,   357,
     357,   357,   357,   357,   358,   359,   360,   362,   361,   363,
     363,   364,   364,   366,   365,   368,   367,   369,   369,   369,
     370,   370,   372,   371,   374,   373,   376,   375,   377,   377,
     378,   378,   378,   378,   378,   378,   379,   380,   381,   382,
     383,   384,   386,   385,   387,   387,   388,   388,   390,   389,
     392,   391,   393,   393,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   396,
     395,   398,   397,   400,   399,   402,   401,   404,   403,   406,
     405,   408,   407,   409,   410,   411,   413,   412,   414,   414,
     414,   414,   415,   417,   416,   418,   418,   419,   419,   421,
     420,   422,   422,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   425,   424,   427,   426,   428,   428,   429,
     429,   431,   430,   433,   432,   434,   434,   435,   435,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   437,
     438,   439,   441,   440,   443,   442,   445,   444,   446,   448,
     447,   449,   451,   450,   452,   452,   453,   453,   455,   454,
     457,   456,   458,   458,   459,   459,   460,   460,   460,   460,
     460,   460,   460,   460,   460,   461,   463,   462,   464,   465,
     466,   467,   469,   468,   470,   470,   471,   471,   473,   472,
     475,   474,   476,   476,   477,   477,   477,   477,   477,   477,
     477,   479,   478,   481,   480,   483,   482,   485,   484,   486,
     486,   487,   487,   489,   488,   491,   490,   492,   492,   493,
     493,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   496,   495,   498,   497,
     500,   499,   502,   501,   504,   503,   506,   505,   508,   507,
     510,   509,   512,   511,   514,   513,   516,   515,   518,   517,
     520,   519,   521,   521,   523,   522,   524,   524,   526,   525,
     527,   527,   528,   528,   529,   529,   529,   529,   529,   529,
     529,   529,   529,   529,   529,   529,   529,   529,   530,   532,
     531,   533,   534,   536,   535,   537,   537,   538,   538,   538,
     538,   538,   540,   539,   542,   541,   544,   543,   545,   545,
     546,   546,   546,   546,   546,   546,   547,   549,   548,   550,
     552,   551,   554,   553,   556,   555,   557,   557,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   559,   561,   560,   562,
     564,   563,   565,   566,   568,   567,   569,   569,   571,   570,
     573,   572,   574,   575,   577,   576,   579,   578,   581,   580,
     583,   582,   585,   584,   587,   586,   588,   588,   589,   589,
     591,   590,   592,   594,   593,   595,   595,   597,   596,   598,
     598,   599,   599,   599,   599,   599,   599,   599,   600,   602,
     601,   604,   603,   605,   605,   607,   606,   608,   608,   609,
     609,   609,   609,   609,   611,   610,   612,   613,   614,   616,
     615,   618,   617,   619,   619,   620,   620,   621
  };

  const signed char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     4,     0,
       4,     3,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     1,     1,     0,     4,     1,     1,     3,     0,
       6,     0,     6,     1,     3,     1,     0,     4,     0,     6,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     0,     4,     1,     1,     1,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     1,     0,     6,     1,     3,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       0,     6,     3,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     0,     6,     1,     3,     1,     1,     3
  };


#if PARSER4_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"config-control\"", "\"config-databases\"",
  "\"config-fetch-wait-time\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"dhcp-socket-type\"", "\"raw\"", "\"udp\"", "\"outbound-interface\"",
  "\"same-as-inbound\"", "\"use-routing\"", "\"re-detect\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"authoritative\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"lease-database\"",
  "\"hosts-database\"", "\"hosts-databases\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"consistency\"", "\"serial-consistency\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"cache-threshold\"", "\"cache-max-age\"",
  "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"store-extended-info\"", "\"subnet4\"", "\"4o6-interface\"",
  "\"4o6-interface-id\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"id\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"reservations-global\"",
  "\"reservations-in-subnet\"", "\"reservations-out-of-pool\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"",
  "\"ip-reservations-unique\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"compatibility\"",
  "\"lenient-option-parsing\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_object", "$@18", "sub_dhcp4", "$@19", "global_params",
  "global_param", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "server_tag", "$@20",
  "echo_client_id", "match_client_id", "authoritative",
  "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@21",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@22",
  "ddns_qualifying_suffix", "$@23", "ddns_update_on_renew",
  "ddns_use_conflict_resolution", "hostname_char_set", "$@24",
  "hostname_char_replacement", "$@25", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "ip_reservations_unique", "interfaces_config", "$@26",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@27", "interfaces_list", "$@28", "dhcp_socket_type", "$@29",
  "socket_type", "outbound_interface", "$@30", "outbound_interface_value",
  "re_detect", "lease_database", "$@31", "sanity_checks", "$@32",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@33",
  "hosts_database", "$@34", "hosts_databases", "$@35", "database_list",
  "not_empty_database_list", "database", "$@36", "database_map_params",
  "database_map_param", "database_type", "$@37", "db_type", "user", "$@38",
  "password", "$@39", "host", "$@40", "port", "name", "$@41", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@42", "keyspace",
  "$@43", "consistency", "$@44", "serial_consistency", "$@45",
  "max_reconnect_tries", "reconnect_wait_time", "on_fail", "$@46",
  "on_fail_mode", "max_row_errors", "host_reservation_identifiers", "$@47",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@48", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@49", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@50",
  "sub_hooks_library", "$@51", "hooks_params", "hooks_param", "library",
  "$@52", "parameters", "$@53", "expired_leases_processing", "$@54",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@55",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@56",
  "sub_subnet4", "$@57", "subnet4_params", "subnet4_param", "subnet",
  "$@58", "subnet_4o6_interface", "$@59", "subnet_4o6_interface_id",
  "$@60", "subnet_4o6_subnet", "$@61", "interface", "$@62", "client_class",
  "$@63", "require_client_classes", "$@64", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@65", "hr_mode", "id", "shared_networks", "$@66",
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
  "not_empty_pools_list", "pool_list_entry", "$@81", "sub_pool4", "$@82",
  "pool_params", "pool_param", "pool_entry", "$@83", "user_context",
  "$@84", "comment", "$@85", "reservations", "$@86", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@87", "sub_reservation",
  "$@88", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@89", "server_hostname", "$@90",
  "boot_file_name", "$@91", "ip_address", "$@92", "ip_addresses", "$@93",
  "duid", "$@94", "hw_address", "$@95", "client_id_value", "$@96",
  "circuit_id_value", "$@97", "flex_id_value", "$@98", "hostname", "$@99",
  "reservation_client_classes", "$@100", "relay", "$@101", "relay_map",
  "client_classes", "$@102", "client_classes_list", "client_class_entry",
  "$@103", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@104",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@105",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@106", "control_socket_name", "$@107", "dhcp_queue_control", "$@108",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@109", "capacity", "arbitrary_map_entry", "$@110",
  "dhcp_ddns", "$@111", "sub_dhcp_ddns", "$@112", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@113", "server_port",
  "sender_ip", "$@114", "sender_port", "max_queue_size", "ncr_protocol",
  "$@115", "ncr_protocol_value", "ncr_format", "$@116",
  "dep_qualifying_suffix", "$@117", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@118",
  "dep_generated_prefix", "$@119", "dep_hostname_char_set", "$@120",
  "dep_hostname_char_replacement", "$@121", "config_control", "$@122",
  "sub_config_control", "$@123", "config_control_params",
  "config_control_param", "config_databases", "$@124",
  "config_fetch_wait_time", "loggers", "$@125", "loggers_entries",
  "logger_entry", "$@126", "logger_params", "logger_param", "debuglevel",
  "severity", "$@127", "output_options_list", "$@128",
  "output_options_list_content", "output_entry", "$@129",
  "output_params_list", "output_params", "output", "$@130", "flush",
  "maxsize", "maxver", "pattern", "$@131", "compatibility", "$@132",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   293,   293,   293,   294,   294,   295,   295,   296,   296,
     297,   297,   298,   298,   299,   299,   300,   300,   301,   301,
     302,   302,   303,   303,   304,   304,   305,   305,   313,   314,
     315,   316,   317,   318,   319,   322,   327,   327,   338,   341,
     342,   345,   350,   358,   358,   365,   366,   369,   373,   380,
     380,   387,   388,   391,   395,   406,   415,   415,   430,   430,
     447,   447,   456,   457,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   517,
     518,   519,   520,   521,   522,   525,   531,   537,   543,   549,
     555,   561,   567,   573,   579,   585,   591,   591,   600,   606,
     612,   618,   624,   630,   636,   636,   645,   648,   651,   654,
     657,   663,   663,   672,   672,   681,   687,   693,   693,   702,
     702,   711,   717,   723,   729,   735,   735,   747,   748,   751,
     752,   753,   754,   755,   756,   757,   760,   760,   769,   769,
     780,   780,   788,   789,   792,   792,   800,   802,   806,   813,
     813,   826,   826,   837,   838,   840,   842,   842,   861,   861,
     874,   874,   885,   886,   889,   890,   893,   893,   903,   904,
     907,   908,   909,   910,   911,   912,   913,   914,   915,   916,
     917,   918,   919,   920,   921,   922,   923,   924,   925,   926,
     927,   928,   931,   931,   939,   940,   941,   942,   945,   945,
     954,   954,   963,   963,   972,   978,   978,   987,   993,   999,
    1005,  1011,  1017,  1023,  1029,  1029,  1038,  1038,  1047,  1047,
    1056,  1056,  1065,  1071,  1077,  1077,  1085,  1086,  1087,  1090,
    1097,  1097,  1108,  1109,  1112,  1113,  1114,  1115,  1116,  1119,
    1124,  1129,  1134,  1139,  1146,  1146,  1159,  1160,  1163,  1164,
    1165,  1166,  1167,  1168,  1171,  1177,  1183,  1189,  1189,  1200,
    1201,  1204,  1205,  1208,  1208,  1218,  1218,  1228,  1229,  1230,
    1233,  1234,  1237,  1237,  1246,  1246,  1255,  1255,  1267,  1268,
    1271,  1272,  1273,  1274,  1275,  1276,  1279,  1285,  1291,  1297,
    1303,  1309,  1318,  1318,  1332,  1333,  1336,  1337,  1344,  1344,
    1370,  1370,  1381,  1382,  1386,  1387,  1388,  1389,  1390,  1391,
    1392,  1393,  1394,  1395,  1396,  1397,  1398,  1399,  1400,  1401,
    1402,  1403,  1404,  1405,  1406,  1407,  1408,  1409,  1410,  1411,
    1412,  1413,  1414,  1415,  1416,  1417,  1418,  1419,  1420,  1421,
    1422,  1423,  1424,  1425,  1426,  1427,  1428,  1429,  1430,  1433,
    1433,  1442,  1442,  1451,  1451,  1460,  1460,  1469,  1469,  1478,
    1478,  1487,  1487,  1498,  1504,  1510,  1516,  1516,  1524,  1525,
    1526,  1527,  1530,  1538,  1538,  1550,  1551,  1555,  1556,  1559,
    1559,  1567,  1568,  1571,  1572,  1573,  1574,  1575,  1576,  1577,
    1578,  1579,  1580,  1581,  1582,  1583,  1584,  1585,  1586,  1587,
    1588,  1589,  1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,
    1598,  1599,  1600,  1601,  1602,  1603,  1604,  1605,  1606,  1607,
    1608,  1609,  1610,  1617,  1617,  1631,  1631,  1640,  1641,  1644,
    1645,  1650,  1650,  1665,  1665,  1679,  1680,  1683,  1684,  1687,
    1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,  1696,  1699,
    1701,  1707,  1709,  1709,  1718,  1718,  1727,  1727,  1736,  1738,
    1738,  1747,  1757,  1757,  1770,  1771,  1776,  1777,  1782,  1782,
    1794,  1794,  1806,  1807,  1812,  1813,  1818,  1819,  1820,  1821,
    1822,  1823,  1824,  1825,  1826,  1829,  1831,  1831,  1840,  1842,
    1844,  1850,  1859,  1859,  1872,  1873,  1876,  1877,  1880,  1880,
    1890,  1890,  1900,  1901,  1904,  1905,  1906,  1907,  1908,  1909,
    1910,  1913,  1913,  1922,  1922,  1947,  1947,  1977,  1977,  1988,
    1989,  1992,  1993,  1996,  1996,  2005,  2005,  2014,  2015,  2018,
    2019,  2023,  2024,  2025,  2026,  2027,  2028,  2029,  2030,  2031,
    2032,  2033,  2034,  2035,  2036,  2037,  2040,  2040,  2049,  2049,
    2058,  2058,  2067,  2067,  2076,  2076,  2087,  2087,  2096,  2096,
    2105,  2105,  2114,  2114,  2123,  2123,  2132,  2132,  2141,  2141,
    2155,  2155,  2166,  2167,  2173,  2173,  2184,  2185,  2188,  2188,
    2198,  2199,  2202,  2203,  2206,  2207,  2208,  2209,  2210,  2211,
    2212,  2213,  2214,  2215,  2216,  2217,  2218,  2219,  2222,  2224,
    2224,  2233,  2241,  2249,  2249,  2260,  2261,  2264,  2265,  2266,
    2267,  2268,  2271,  2271,  2280,  2280,  2292,  2292,  2305,  2306,
    2309,  2310,  2311,  2312,  2313,  2314,  2317,  2323,  2323,  2332,
    2338,  2338,  2348,  2348,  2361,  2361,  2371,  2372,  2375,  2376,
    2377,  2378,  2379,  2380,  2381,  2382,  2383,  2384,  2385,  2386,
    2387,  2388,  2389,  2390,  2391,  2392,  2395,  2401,  2401,  2410,
    2416,  2416,  2425,  2431,  2437,  2437,  2446,  2447,  2450,  2450,
    2460,  2460,  2470,  2477,  2484,  2484,  2493,  2493,  2503,  2503,
    2513,  2513,  2525,  2525,  2537,  2537,  2547,  2548,  2552,  2553,
    2556,  2556,  2567,  2575,  2575,  2588,  2589,  2593,  2593,  2601,
    2602,  2605,  2606,  2607,  2608,  2609,  2610,  2611,  2614,  2620,
    2620,  2629,  2629,  2640,  2641,  2644,  2644,  2652,  2653,  2656,
    2657,  2658,  2659,  2660,  2663,  2663,  2672,  2678,  2684,  2690,
    2690,  2699,  2699,  2710,  2711,  2714,  2715,  2718
  };

  void
  Dhcp4Parser::yy_stack_print_ () const
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
  Dhcp4Parser::yy_reduce_print_ (int yyrule) const
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
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy"
} } // isc::dhcp
#line 5826 "dhcp4_parser.cc"

#line 2724 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
