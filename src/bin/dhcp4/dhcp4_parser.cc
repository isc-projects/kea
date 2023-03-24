// A Bison parser, made by GNU Bison 3.8.2.

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

  /*---------.
  | symbol.  |
  `---------*/



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
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 298 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 298 "dhcp4_parser.yy"
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
  Dhcp4Parser::yypop_ (int n) YY_NOEXCEPT
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
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp4Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
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
#line 307 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 308 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 309 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 310 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 311 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 312 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 313 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 314 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 315 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 316 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 317 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 318 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 319 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 327 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 328 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 329 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 330 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 331 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 332 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 333 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 336 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 341 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 346 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 352 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 359 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 364 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 370 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 375 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 378 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 386 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 390 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 394 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 400 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 402 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 411 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 415 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 419 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 429 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 438 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 443 "dhcp4_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1061 "dhcp4_parser.cc"
    break;

  case 61: // $@18: %empty
#line 453 "dhcp4_parser.yy"
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
#line 1076 "dhcp4_parser.cc"
    break;

  case 62: // global_object: "Dhcp4" $@18 ":" "{" global_params "}"
#line 462 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 470 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 476 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 480 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 487 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 137: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 563 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 138: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 569 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 139: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 575 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 140: // renew_timer: "renew-timer" ":" "integer"
#line 581 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 141: // rebind_timer: "rebind-timer" ":" "integer"
#line 587 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 142: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 593 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 143: // t1_percent: "t1-percent" ":" "floating point"
#line 599 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 144: // t2_percent: "t2-percent" ":" "floating point"
#line 605 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 145: // cache_threshold: "cache-threshold" ":" "floating point"
#line 611 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 146: // cache_max_age: "cache-max-age" ":" "integer"
#line 617 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 147: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 623 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 148: // $@20: %empty
#line 629 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 149: // server_tag: "server-tag" $@20 ":" "constant string"
#line 632 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 150: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 638 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 151: // $@21: %empty
#line 644 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1269 "dhcp4_parser.cc"
    break;

  case 152: // allocator: "allocator" $@21 ":" "constant string"
#line 647 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 153: // echo_client_id: "echo-client-id" ":" "boolean"
#line 653 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1289 "dhcp4_parser.cc"
    break;

  case 154: // match_client_id: "match-client-id" ":" "boolean"
#line 659 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1299 "dhcp4_parser.cc"
    break;

  case 155: // authoritative: "authoritative" ":" "boolean"
#line 665 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1309 "dhcp4_parser.cc"
    break;

  case 156: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 671 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1319 "dhcp4_parser.cc"
    break;

  case 157: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 677 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 158: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 683 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1339 "dhcp4_parser.cc"
    break;

  case 159: // $@22: %empty
#line 689 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1348 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 692 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "when-present"
#line 698 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1365 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "never"
#line 701 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1373 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "always"
#line 704 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "when-not-present"
#line 707 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 165: // ddns_replace_client_name_value: "boolean"
#line 710 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1398 "dhcp4_parser.cc"
    break;

  case 166: // $@23: %empty
#line 716 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 167: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 719 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 168: // $@24: %empty
#line 725 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp4_parser.cc"
    break;

  case 169: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 728 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1436 "dhcp4_parser.cc"
    break;

  case 170: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 734 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 171: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 740 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 172: // ddns_ttl_percent: "ddns-ttl-percent" ":" "floating point"
#line 746 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr ttl(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
}
#line 1466 "dhcp4_parser.cc"
    break;

  case 173: // $@25: %empty
#line 752 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 174: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 755 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 175: // $@26: %empty
#line 761 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 176: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 764 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1504 "dhcp4_parser.cc"
    break;

  case 177: // store_extended_info: "store-extended-info" ":" "boolean"
#line 770 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1514 "dhcp4_parser.cc"
    break;

  case 178: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 776 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 179: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 782 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 180: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 788 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 181: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 794 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1554 "dhcp4_parser.cc"
    break;

  case 182: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 800 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 183: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 806 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 184: // $@27: %empty
#line 812 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 185: // interfaces_config: "interfaces-config" $@27 ":" "{" interfaces_config_params "}"
#line 818 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 188: // interfaces_config_params: interfaces_config_params ","
#line 826 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1604 "dhcp4_parser.cc"
    break;

  case 199: // $@28: %empty
#line 843 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 200: // sub_interfaces4: "{" $@28 interfaces_config_params "}"
#line 847 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1623 "dhcp4_parser.cc"
    break;

  case 201: // $@29: %empty
#line 852 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1635 "dhcp4_parser.cc"
    break;

  case 202: // interfaces_list: "interfaces" $@29 ":" list_strings
#line 858 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 203: // $@30: %empty
#line 863 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1653 "dhcp4_parser.cc"
    break;

  case 204: // dhcp_socket_type: "dhcp-socket-type" $@30 ":" socket_type
#line 866 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1662 "dhcp4_parser.cc"
    break;

  case 205: // socket_type: "raw"
#line 871 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1668 "dhcp4_parser.cc"
    break;

  case 206: // socket_type: "udp"
#line 872 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1674 "dhcp4_parser.cc"
    break;

  case 207: // $@31: %empty
#line 875 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1683 "dhcp4_parser.cc"
    break;

  case 208: // outbound_interface: "outbound-interface" $@31 ":" outbound_interface_value
#line 878 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1692 "dhcp4_parser.cc"
    break;

  case 209: // outbound_interface_value: "same-as-inbound"
#line 883 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1700 "dhcp4_parser.cc"
    break;

  case 210: // outbound_interface_value: "use-routing"
#line 885 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1708 "dhcp4_parser.cc"
    break;

  case 211: // re_detect: "re-detect" ":" "boolean"
#line 889 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 212: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 895 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 213: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 901 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 214: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 907 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1748 "dhcp4_parser.cc"
    break;

  case 215: // $@32: %empty
#line 913 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1760 "dhcp4_parser.cc"
    break;

  case 216: // lease_database: "lease-database" $@32 ":" "{" database_map_params "}"
#line 919 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1771 "dhcp4_parser.cc"
    break;

  case 217: // $@33: %empty
#line 926 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1783 "dhcp4_parser.cc"
    break;

  case 218: // sanity_checks: "sanity-checks" $@33 ":" "{" sanity_checks_params "}"
#line 932 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1792 "dhcp4_parser.cc"
    break;

  case 221: // sanity_checks_params: sanity_checks_params ","
#line 939 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1800 "dhcp4_parser.cc"
    break;

  case 224: // $@34: %empty
#line 948 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1809 "dhcp4_parser.cc"
    break;

  case 225: // lease_checks: "lease-checks" $@34 ":" "constant string"
#line 951 "dhcp4_parser.yy"
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
#line 1829 "dhcp4_parser.cc"
    break;

  case 226: // $@35: %empty
#line 967 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1838 "dhcp4_parser.cc"
    break;

  case 227: // extended_info_checks: "extended-info-checks" $@35 ":" "constant string"
#line 970 "dhcp4_parser.yy"
               {

    if ( (string(yystack_[0].value.as < std::string > ()) == "none") ||
         (string(yystack_[0].value.as < std::string > ()) == "fix") ||
         (string(yystack_[0].value.as < std::string > ()) == "strict") ||
         (string(yystack_[0].value.as < std::string > ()) == "pedantic")) {
        ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("extended-info-checks", user);
        ctx.leave();
    } else {
        error(yystack_[0].location, "Unsupported 'extended-info-checks value: " + string(yystack_[0].value.as < std::string > ()) +
              ", supported values are: none, fix, strict, pedantic");
    }
}
#line 1857 "dhcp4_parser.cc"
    break;

  case 228: // $@36: %empty
#line 985 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1869 "dhcp4_parser.cc"
    break;

  case 229: // hosts_database: "hosts-database" $@36 ":" "{" database_map_params "}"
#line 991 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1880 "dhcp4_parser.cc"
    break;

  case 230: // $@37: %empty
#line 998 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1892 "dhcp4_parser.cc"
    break;

  case 231: // hosts_databases: "hosts-databases" $@37 ":" "[" database_list "]"
#line 1004 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1901 "dhcp4_parser.cc"
    break;

  case 236: // not_empty_database_list: not_empty_database_list ","
#line 1015 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1909 "dhcp4_parser.cc"
    break;

  case 237: // $@38: %empty
#line 1020 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1919 "dhcp4_parser.cc"
    break;

  case 238: // database: "{" $@38 database_map_params "}"
#line 1024 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1929 "dhcp4_parser.cc"
    break;

  case 241: // database_map_params: database_map_params ","
#line 1032 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1937 "dhcp4_parser.cc"
    break;

  case 264: // $@39: %empty
#line 1061 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1946 "dhcp4_parser.cc"
    break;

  case 265: // database_type: "type" $@39 ":" db_type
#line 1064 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1955 "dhcp4_parser.cc"
    break;

  case 266: // db_type: "memfile"
#line 1069 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1961 "dhcp4_parser.cc"
    break;

  case 267: // db_type: "mysql"
#line 1070 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1967 "dhcp4_parser.cc"
    break;

  case 268: // db_type: "postgresql"
#line 1071 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1973 "dhcp4_parser.cc"
    break;

  case 269: // $@40: %empty
#line 1074 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1982 "dhcp4_parser.cc"
    break;

  case 270: // user: "user" $@40 ":" "constant string"
#line 1077 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1992 "dhcp4_parser.cc"
    break;

  case 271: // $@41: %empty
#line 1083 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 272: // password: "password" $@41 ":" "constant string"
#line 1086 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 273: // $@42: %empty
#line 1092 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 274: // host: "host" $@42 ":" "constant string"
#line 1095 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2030 "dhcp4_parser.cc"
    break;

  case 275: // port: "port" ":" "integer"
#line 1101 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2040 "dhcp4_parser.cc"
    break;

  case 276: // $@43: %empty
#line 1107 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2049 "dhcp4_parser.cc"
    break;

  case 277: // name: "name" $@43 ":" "constant string"
#line 1110 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 278: // persist: "persist" ":" "boolean"
#line 1116 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 279: // lfc_interval: "lfc-interval" ":" "integer"
#line 1122 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 280: // readonly: "readonly" ":" "boolean"
#line 1128 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 281: // connect_timeout: "connect-timeout" ":" "integer"
#line 1134 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 282: // read_timeout: "read-timeout" ":" "integer"
#line 1140 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 283: // write_timeout: "write-timeout" ":" "integer"
#line 1146 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2119 "dhcp4_parser.cc"
    break;

  case 284: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1152 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2129 "dhcp4_parser.cc"
    break;

  case 285: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1158 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2139 "dhcp4_parser.cc"
    break;

  case 286: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1164 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2149 "dhcp4_parser.cc"
    break;

  case 287: // $@44: %empty
#line 1170 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2158 "dhcp4_parser.cc"
    break;

  case 288: // on_fail: "on-fail" $@44 ":" on_fail_mode
#line 1173 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2167 "dhcp4_parser.cc"
    break;

  case 289: // on_fail_mode: "stop-retry-exit"
#line 1178 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2173 "dhcp4_parser.cc"
    break;

  case 290: // on_fail_mode: "serve-retry-exit"
#line 1179 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2179 "dhcp4_parser.cc"
    break;

  case 291: // on_fail_mode: "serve-retry-continue"
#line 1180 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2185 "dhcp4_parser.cc"
    break;

  case 292: // max_row_errors: "max-row-errors" ":" "integer"
#line 1183 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2195 "dhcp4_parser.cc"
    break;

  case 293: // $@45: %empty
#line 1189 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2204 "dhcp4_parser.cc"
    break;

  case 294: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1192 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2214 "dhcp4_parser.cc"
    break;

  case 295: // $@46: %empty
#line 1198 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2223 "dhcp4_parser.cc"
    break;

  case 296: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1201 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2233 "dhcp4_parser.cc"
    break;

  case 297: // $@47: %empty
#line 1207 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2242 "dhcp4_parser.cc"
    break;

  case 298: // key_file: "key-file" $@47 ":" "constant string"
#line 1210 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2252 "dhcp4_parser.cc"
    break;

  case 299: // $@48: %empty
#line 1216 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2261 "dhcp4_parser.cc"
    break;

  case 300: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1219 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2271 "dhcp4_parser.cc"
    break;

  case 301: // $@49: %empty
#line 1225 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2283 "dhcp4_parser.cc"
    break;

  case 302: // host_reservation_identifiers: "host-reservation-identifiers" $@49 ":" "[" host_reservation_identifiers_list "]"
#line 1231 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2292 "dhcp4_parser.cc"
    break;

  case 305: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1238 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2300 "dhcp4_parser.cc"
    break;

  case 311: // duid_id: "duid"
#line 1250 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2309 "dhcp4_parser.cc"
    break;

  case 312: // hw_address_id: "hw-address"
#line 1255 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2318 "dhcp4_parser.cc"
    break;

  case 313: // circuit_id: "circuit-id"
#line 1260 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2327 "dhcp4_parser.cc"
    break;

  case 314: // client_id: "client-id"
#line 1265 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2336 "dhcp4_parser.cc"
    break;

  case 315: // flex_id: "flex-id"
#line 1270 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2345 "dhcp4_parser.cc"
    break;

  case 316: // $@50: %empty
#line 1277 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 317: // dhcp_multi_threading: "multi-threading" $@50 ":" "{" multi_threading_params "}"
#line 1283 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2368 "dhcp4_parser.cc"
    break;

  case 320: // multi_threading_params: multi_threading_params ","
#line 1292 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2376 "dhcp4_parser.cc"
    break;

  case 327: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1305 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 328: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1311 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2396 "dhcp4_parser.cc"
    break;

  case 329: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1317 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 330: // $@51: %empty
#line 1323 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2418 "dhcp4_parser.cc"
    break;

  case 331: // hooks_libraries: "hooks-libraries" $@51 ":" "[" hooks_libraries_list "]"
#line 1329 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2427 "dhcp4_parser.cc"
    break;

  case 336: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1340 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2435 "dhcp4_parser.cc"
    break;

  case 337: // $@52: %empty
#line 1345 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 338: // hooks_library: "{" $@52 hooks_params "}"
#line 1349 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2455 "dhcp4_parser.cc"
    break;

  case 339: // $@53: %empty
#line 1355 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2465 "dhcp4_parser.cc"
    break;

  case 340: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1359 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2475 "dhcp4_parser.cc"
    break;

  case 343: // hooks_params: hooks_params ","
#line 1367 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2483 "dhcp4_parser.cc"
    break;

  case 347: // $@54: %empty
#line 1377 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 348: // library: "library" $@54 ":" "constant string"
#line 1380 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2502 "dhcp4_parser.cc"
    break;

  case 349: // $@55: %empty
#line 1386 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2511 "dhcp4_parser.cc"
    break;

  case 350: // parameters: "parameters" $@55 ":" map_value
#line 1389 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc"
    break;

  case 351: // $@56: %empty
#line 1395 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2532 "dhcp4_parser.cc"
    break;

  case 352: // expired_leases_processing: "expired-leases-processing" $@56 ":" "{" expired_leases_params "}"
#line 1401 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2542 "dhcp4_parser.cc"
    break;

  case 355: // expired_leases_params: expired_leases_params ","
#line 1409 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2550 "dhcp4_parser.cc"
    break;

  case 362: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1422 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2560 "dhcp4_parser.cc"
    break;

  case 363: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1428 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2570 "dhcp4_parser.cc"
    break;

  case 364: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1434 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 365: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1440 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 366: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1446 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2600 "dhcp4_parser.cc"
    break;

  case 367: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1452 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2610 "dhcp4_parser.cc"
    break;

  case 368: // $@57: %empty
#line 1461 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2622 "dhcp4_parser.cc"
    break;

  case 369: // subnet4_list: "subnet4" $@57 ":" "[" subnet4_list_content "]"
#line 1467 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2631 "dhcp4_parser.cc"
    break;

  case 374: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1481 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2639 "dhcp4_parser.cc"
    break;

  case 375: // $@58: %empty
#line 1490 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2649 "dhcp4_parser.cc"
    break;

  case 376: // subnet4: "{" $@58 subnet4_params "}"
#line 1494 "dhcp4_parser.yy"
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
#line 2675 "dhcp4_parser.cc"
    break;

  case 377: // $@59: %empty
#line 1516 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2685 "dhcp4_parser.cc"
    break;

  case 378: // sub_subnet4: "{" $@59 subnet4_params "}"
#line 1520 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2695 "dhcp4_parser.cc"
    break;

  case 381: // subnet4_params: subnet4_params ","
#line 1529 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2703 "dhcp4_parser.cc"
    break;

  case 430: // $@60: %empty
#line 1585 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 431: // subnet: "subnet" $@60 ":" "constant string"
#line 1588 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 432: // $@61: %empty
#line 1594 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2731 "dhcp4_parser.cc"
    break;

  case 433: // subnet_4o6_interface: "4o6-interface" $@61 ":" "constant string"
#line 1597 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2741 "dhcp4_parser.cc"
    break;

  case 434: // $@62: %empty
#line 1603 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2750 "dhcp4_parser.cc"
    break;

  case 435: // subnet_4o6_interface_id: "4o6-interface-id" $@62 ":" "constant string"
#line 1606 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2760 "dhcp4_parser.cc"
    break;

  case 436: // $@63: %empty
#line 1612 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2769 "dhcp4_parser.cc"
    break;

  case 437: // subnet_4o6_subnet: "4o6-subnet" $@63 ":" "constant string"
#line 1615 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2779 "dhcp4_parser.cc"
    break;

  case 438: // $@64: %empty
#line 1621 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2788 "dhcp4_parser.cc"
    break;

  case 439: // interface: "interface" $@64 ":" "constant string"
#line 1624 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2798 "dhcp4_parser.cc"
    break;

  case 440: // $@65: %empty
#line 1630 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2807 "dhcp4_parser.cc"
    break;

  case 441: // client_class: "client-class" $@65 ":" "constant string"
#line 1633 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2817 "dhcp4_parser.cc"
    break;

  case 442: // $@66: %empty
#line 1639 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2829 "dhcp4_parser.cc"
    break;

  case 443: // require_client_classes: "require-client-classes" $@66 ":" list_strings
#line 1645 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2838 "dhcp4_parser.cc"
    break;

  case 444: // reservations_global: "reservations-global" ":" "boolean"
#line 1650 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2848 "dhcp4_parser.cc"
    break;

  case 445: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1656 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2858 "dhcp4_parser.cc"
    break;

  case 446: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1662 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2868 "dhcp4_parser.cc"
    break;

  case 447: // $@67: %empty
#line 1668 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2877 "dhcp4_parser.cc"
    break;

  case 448: // reservation_mode: "reservation-mode" $@67 ":" hr_mode
#line 1671 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2886 "dhcp4_parser.cc"
    break;

  case 449: // hr_mode: "disabled"
#line 1676 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2892 "dhcp4_parser.cc"
    break;

  case 450: // hr_mode: "out-of-pool"
#line 1677 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2898 "dhcp4_parser.cc"
    break;

  case 451: // hr_mode: "global"
#line 1678 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2904 "dhcp4_parser.cc"
    break;

  case 452: // hr_mode: "all"
#line 1679 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2910 "dhcp4_parser.cc"
    break;

  case 453: // id: "id" ":" "integer"
#line 1682 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2920 "dhcp4_parser.cc"
    break;

  case 454: // $@68: %empty
#line 1690 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 455: // shared_networks: "shared-networks" $@68 ":" "[" shared_networks_content "]"
#line 1696 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2941 "dhcp4_parser.cc"
    break;

  case 460: // shared_networks_list: shared_networks_list ","
#line 1709 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2949 "dhcp4_parser.cc"
    break;

  case 461: // $@69: %empty
#line 1714 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2959 "dhcp4_parser.cc"
    break;

  case 462: // shared_network: "{" $@69 shared_network_params "}"
#line 1718 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2967 "dhcp4_parser.cc"
    break;

  case 465: // shared_network_params: shared_network_params ","
#line 1724 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2975 "dhcp4_parser.cc"
    break;

  case 509: // $@70: %empty
#line 1778 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2987 "dhcp4_parser.cc"
    break;

  case 510: // option_def_list: "option-def" $@70 ":" "[" option_def_list_content "]"
#line 1784 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2996 "dhcp4_parser.cc"
    break;

  case 511: // $@71: %empty
#line 1792 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3005 "dhcp4_parser.cc"
    break;

  case 512: // sub_option_def_list: "{" $@71 option_def_list "}"
#line 1795 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3013 "dhcp4_parser.cc"
    break;

  case 517: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1807 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3021 "dhcp4_parser.cc"
    break;

  case 518: // $@72: %empty
#line 1814 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3031 "dhcp4_parser.cc"
    break;

  case 519: // option_def_entry: "{" $@72 option_def_params "}"
#line 1818 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 520: // $@73: %empty
#line 1829 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3053 "dhcp4_parser.cc"
    break;

  case 521: // sub_option_def: "{" $@73 option_def_params "}"
#line 1833 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3065 "dhcp4_parser.cc"
    break;

  case 526: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1849 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3073 "dhcp4_parser.cc"
    break;

  case 538: // code: "code" ":" "integer"
#line 1868 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3083 "dhcp4_parser.cc"
    break;

  case 540: // $@74: %empty
#line 1876 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3092 "dhcp4_parser.cc"
    break;

  case 541: // option_def_type: "type" $@74 ":" "constant string"
#line 1879 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3102 "dhcp4_parser.cc"
    break;

  case 542: // $@75: %empty
#line 1885 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3111 "dhcp4_parser.cc"
    break;

  case 543: // option_def_record_types: "record-types" $@75 ":" "constant string"
#line 1888 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 544: // $@76: %empty
#line 1894 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3130 "dhcp4_parser.cc"
    break;

  case 545: // space: "space" $@76 ":" "constant string"
#line 1897 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3140 "dhcp4_parser.cc"
    break;

  case 547: // $@77: %empty
#line 1905 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 548: // option_def_encapsulate: "encapsulate" $@77 ":" "constant string"
#line 1908 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3159 "dhcp4_parser.cc"
    break;

  case 549: // option_def_array: "array" ":" "boolean"
#line 1914 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3169 "dhcp4_parser.cc"
    break;

  case 550: // $@78: %empty
#line 1924 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3181 "dhcp4_parser.cc"
    break;

  case 551: // option_data_list: "option-data" $@78 ":" "[" option_data_list_content "]"
#line 1930 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3190 "dhcp4_parser.cc"
    break;

  case 556: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1945 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3198 "dhcp4_parser.cc"
    break;

  case 557: // $@79: %empty
#line 1952 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3208 "dhcp4_parser.cc"
    break;

  case 558: // option_data_entry: "{" $@79 option_data_params "}"
#line 1956 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3217 "dhcp4_parser.cc"
    break;

  case 559: // $@80: %empty
#line 1964 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3227 "dhcp4_parser.cc"
    break;

  case 560: // sub_option_data: "{" $@80 option_data_params "}"
#line 1968 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3236 "dhcp4_parser.cc"
    break;

  case 565: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1984 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3244 "dhcp4_parser.cc"
    break;

  case 577: // $@81: %empty
#line 2005 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3253 "dhcp4_parser.cc"
    break;

  case 578: // option_data_data: "data" $@81 ":" "constant string"
#line 2008 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 581: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2018 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 582: // option_data_always_send: "always-send" ":" "boolean"
#line 2024 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 583: // option_data_never_send: "never-send" ":" "boolean"
#line 2030 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3293 "dhcp4_parser.cc"
    break;

  case 584: // $@82: %empty
#line 2039 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3305 "dhcp4_parser.cc"
    break;

  case 585: // pools_list: "pools" $@82 ":" "[" pools_list_content "]"
#line 2045 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3314 "dhcp4_parser.cc"
    break;

  case 590: // not_empty_pools_list: not_empty_pools_list ","
#line 2058 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3322 "dhcp4_parser.cc"
    break;

  case 591: // $@83: %empty
#line 2063 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 592: // pool_list_entry: "{" $@83 pool_params "}"
#line 2067 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 593: // $@84: %empty
#line 2073 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3352 "dhcp4_parser.cc"
    break;

  case 594: // sub_pool4: "{" $@84 pool_params "}"
#line 2077 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3362 "dhcp4_parser.cc"
    break;

  case 597: // pool_params: pool_params ","
#line 2085 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3370 "dhcp4_parser.cc"
    break;

  case 605: // $@85: %empty
#line 2099 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3379 "dhcp4_parser.cc"
    break;

  case 606: // pool_entry: "pool" $@85 ":" "constant string"
#line 2102 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3389 "dhcp4_parser.cc"
    break;

  case 607: // $@86: %empty
#line 2108 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3397 "dhcp4_parser.cc"
    break;

  case 608: // user_context: "user-context" $@86 ":" map_value
#line 2110 "dhcp4_parser.yy"
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
#line 3424 "dhcp4_parser.cc"
    break;

  case 609: // $@87: %empty
#line 2133 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3432 "dhcp4_parser.cc"
    break;

  case 610: // comment: "comment" $@87 ":" "constant string"
#line 2135 "dhcp4_parser.yy"
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
#line 3461 "dhcp4_parser.cc"
    break;

  case 611: // $@88: %empty
#line 2163 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 612: // reservations: "reservations" $@88 ":" "[" reservations_list "]"
#line 2169 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3482 "dhcp4_parser.cc"
    break;

  case 617: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2180 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3490 "dhcp4_parser.cc"
    break;

  case 618: // $@89: %empty
#line 2185 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3500 "dhcp4_parser.cc"
    break;

  case 619: // reservation: "{" $@89 reservation_params "}"
#line 2189 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3509 "dhcp4_parser.cc"
    break;

  case 620: // $@90: %empty
#line 2194 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3519 "dhcp4_parser.cc"
    break;

  case 621: // sub_reservation: "{" $@90 reservation_params "}"
#line 2198 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3528 "dhcp4_parser.cc"
    break;

  case 626: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2209 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3536 "dhcp4_parser.cc"
    break;

  case 642: // $@91: %empty
#line 2232 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 643: // next_server: "next-server" $@91 ":" "constant string"
#line 2235 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3555 "dhcp4_parser.cc"
    break;

  case 644: // $@92: %empty
#line 2241 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3564 "dhcp4_parser.cc"
    break;

  case 645: // server_hostname: "server-hostname" $@92 ":" "constant string"
#line 2244 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3574 "dhcp4_parser.cc"
    break;

  case 646: // $@93: %empty
#line 2250 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3583 "dhcp4_parser.cc"
    break;

  case 647: // boot_file_name: "boot-file-name" $@93 ":" "constant string"
#line 2253 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3593 "dhcp4_parser.cc"
    break;

  case 648: // $@94: %empty
#line 2259 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3602 "dhcp4_parser.cc"
    break;

  case 649: // ip_address: "ip-address" $@94 ":" "constant string"
#line 2262 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 650: // $@95: %empty
#line 2268 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3624 "dhcp4_parser.cc"
    break;

  case 651: // ip_addresses: "ip-addresses" $@95 ":" list_strings
#line 2274 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3633 "dhcp4_parser.cc"
    break;

  case 652: // $@96: %empty
#line 2279 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3642 "dhcp4_parser.cc"
    break;

  case 653: // duid: "duid" $@96 ":" "constant string"
#line 2282 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3652 "dhcp4_parser.cc"
    break;

  case 654: // $@97: %empty
#line 2288 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3661 "dhcp4_parser.cc"
    break;

  case 655: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2291 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3671 "dhcp4_parser.cc"
    break;

  case 656: // $@98: %empty
#line 2297 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3680 "dhcp4_parser.cc"
    break;

  case 657: // client_id_value: "client-id" $@98 ":" "constant string"
#line 2300 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3690 "dhcp4_parser.cc"
    break;

  case 658: // $@99: %empty
#line 2306 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3699 "dhcp4_parser.cc"
    break;

  case 659: // circuit_id_value: "circuit-id" $@99 ":" "constant string"
#line 2309 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3709 "dhcp4_parser.cc"
    break;

  case 660: // $@100: %empty
#line 2315 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3718 "dhcp4_parser.cc"
    break;

  case 661: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2318 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3728 "dhcp4_parser.cc"
    break;

  case 662: // $@101: %empty
#line 2324 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3737 "dhcp4_parser.cc"
    break;

  case 663: // hostname: "hostname" $@101 ":" "constant string"
#line 2327 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3747 "dhcp4_parser.cc"
    break;

  case 664: // $@102: %empty
#line 2333 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3759 "dhcp4_parser.cc"
    break;

  case 665: // reservation_client_classes: "client-classes" $@102 ":" list_strings
#line 2339 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3768 "dhcp4_parser.cc"
    break;

  case 666: // $@103: %empty
#line 2347 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 667: // relay: "relay" $@103 ":" "{" relay_map "}"
#line 2353 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3789 "dhcp4_parser.cc"
    break;

  case 670: // $@104: %empty
#line 2365 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3801 "dhcp4_parser.cc"
    break;

  case 671: // client_classes: "client-classes" $@104 ":" "[" client_classes_list "]"
#line 2371 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3810 "dhcp4_parser.cc"
    break;

  case 674: // client_classes_list: client_classes_list ","
#line 2378 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3818 "dhcp4_parser.cc"
    break;

  case 675: // $@105: %empty
#line 2383 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3828 "dhcp4_parser.cc"
    break;

  case 676: // client_class_entry: "{" $@105 client_class_params "}"
#line 2387 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3838 "dhcp4_parser.cc"
    break;

  case 681: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2399 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3846 "dhcp4_parser.cc"
    break;

  case 699: // $@106: %empty
#line 2424 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3855 "dhcp4_parser.cc"
    break;

  case 700: // client_class_test: "test" $@106 ":" "constant string"
#line 2427 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3865 "dhcp4_parser.cc"
    break;

  case 701: // $@107: %empty
#line 2433 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3874 "dhcp4_parser.cc"
    break;

  case 702: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2436 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3884 "dhcp4_parser.cc"
    break;

  case 703: // only_if_required: "only-if-required" ":" "boolean"
#line 2442 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3894 "dhcp4_parser.cc"
    break;

  case 704: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2450 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3904 "dhcp4_parser.cc"
    break;

  case 705: // $@108: %empty
#line 2458 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3916 "dhcp4_parser.cc"
    break;

  case 706: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2464 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3925 "dhcp4_parser.cc"
    break;

  case 709: // control_socket_params: control_socket_params ","
#line 2471 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3933 "dhcp4_parser.cc"
    break;

  case 715: // $@109: %empty
#line 2483 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3942 "dhcp4_parser.cc"
    break;

  case 716: // control_socket_type: "socket-type" $@109 ":" "constant string"
#line 2486 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3952 "dhcp4_parser.cc"
    break;

  case 717: // $@110: %empty
#line 2492 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3961 "dhcp4_parser.cc"
    break;

  case 718: // control_socket_name: "socket-name" $@110 ":" "constant string"
#line 2495 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3971 "dhcp4_parser.cc"
    break;

  case 719: // $@111: %empty
#line 2504 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3983 "dhcp4_parser.cc"
    break;

  case 720: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2510 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3994 "dhcp4_parser.cc"
    break;

  case 723: // queue_control_params: queue_control_params ","
#line 2519 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4002 "dhcp4_parser.cc"
    break;

  case 730: // enable_queue: "enable-queue" ":" "boolean"
#line 2532 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4012 "dhcp4_parser.cc"
    break;

  case 731: // $@112: %empty
#line 2538 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4021 "dhcp4_parser.cc"
    break;

  case 732: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2541 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4031 "dhcp4_parser.cc"
    break;

  case 733: // capacity: "capacity" ":" "integer"
#line 2547 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 734: // $@113: %empty
#line 2553 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4050 "dhcp4_parser.cc"
    break;

  case 735: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2556 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4059 "dhcp4_parser.cc"
    break;

  case 736: // $@114: %empty
#line 2563 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4071 "dhcp4_parser.cc"
    break;

  case 737: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2569 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4082 "dhcp4_parser.cc"
    break;

  case 738: // $@115: %empty
#line 2576 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4092 "dhcp4_parser.cc"
    break;

  case 739: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2580 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4102 "dhcp4_parser.cc"
    break;

  case 742: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2588 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4110 "dhcp4_parser.cc"
    break;

  case 761: // enable_updates: "enable-updates" ":" "boolean"
#line 2613 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4120 "dhcp4_parser.cc"
    break;

  case 762: // $@116: %empty
#line 2619 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4129 "dhcp4_parser.cc"
    break;

  case 763: // server_ip: "server-ip" $@116 ":" "constant string"
#line 2622 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4139 "dhcp4_parser.cc"
    break;

  case 764: // server_port: "server-port" ":" "integer"
#line 2628 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4149 "dhcp4_parser.cc"
    break;

  case 765: // $@117: %empty
#line 2634 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4158 "dhcp4_parser.cc"
    break;

  case 766: // sender_ip: "sender-ip" $@117 ":" "constant string"
#line 2637 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4168 "dhcp4_parser.cc"
    break;

  case 767: // sender_port: "sender-port" ":" "integer"
#line 2643 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4178 "dhcp4_parser.cc"
    break;

  case 768: // max_queue_size: "max-queue-size" ":" "integer"
#line 2649 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4188 "dhcp4_parser.cc"
    break;

  case 769: // $@118: %empty
#line 2655 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4197 "dhcp4_parser.cc"
    break;

  case 770: // ncr_protocol: "ncr-protocol" $@118 ":" ncr_protocol_value
#line 2658 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4206 "dhcp4_parser.cc"
    break;

  case 771: // ncr_protocol_value: "udp"
#line 2664 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4212 "dhcp4_parser.cc"
    break;

  case 772: // ncr_protocol_value: "tcp"
#line 2665 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4218 "dhcp4_parser.cc"
    break;

  case 773: // $@119: %empty
#line 2668 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4227 "dhcp4_parser.cc"
    break;

  case 774: // ncr_format: "ncr-format" $@119 ":" "JSON"
#line 2671 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4237 "dhcp4_parser.cc"
    break;

  case 775: // $@120: %empty
#line 2678 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4246 "dhcp4_parser.cc"
    break;

  case 776: // dep_qualifying_suffix: "qualifying-suffix" $@120 ":" "constant string"
#line 2681 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4256 "dhcp4_parser.cc"
    break;

  case 777: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2688 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4266 "dhcp4_parser.cc"
    break;

  case 778: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2695 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4276 "dhcp4_parser.cc"
    break;

  case 779: // $@121: %empty
#line 2702 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4285 "dhcp4_parser.cc"
    break;

  case 780: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2705 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4294 "dhcp4_parser.cc"
    break;

  case 781: // $@122: %empty
#line 2711 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4303 "dhcp4_parser.cc"
    break;

  case 782: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2714 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4313 "dhcp4_parser.cc"
    break;

  case 783: // $@123: %empty
#line 2721 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4322 "dhcp4_parser.cc"
    break;

  case 784: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2724 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4332 "dhcp4_parser.cc"
    break;

  case 785: // $@124: %empty
#line 2731 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4341 "dhcp4_parser.cc"
    break;

  case 786: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2734 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4351 "dhcp4_parser.cc"
    break;

  case 787: // $@125: %empty
#line 2743 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4363 "dhcp4_parser.cc"
    break;

  case 788: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2749 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4373 "dhcp4_parser.cc"
    break;

  case 789: // $@126: %empty
#line 2755 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4383 "dhcp4_parser.cc"
    break;

  case 790: // sub_config_control: "{" $@126 config_control_params "}"
#line 2759 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4392 "dhcp4_parser.cc"
    break;

  case 793: // config_control_params: config_control_params ","
#line 2767 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4400 "dhcp4_parser.cc"
    break;

  case 796: // $@127: %empty
#line 2777 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4412 "dhcp4_parser.cc"
    break;

  case 797: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2783 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4421 "dhcp4_parser.cc"
    break;

  case 798: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2788 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4431 "dhcp4_parser.cc"
    break;

  case 799: // $@128: %empty
#line 2796 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4443 "dhcp4_parser.cc"
    break;

  case 800: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2802 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4452 "dhcp4_parser.cc"
    break;

  case 803: // loggers_entries: loggers_entries ","
#line 2811 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4460 "dhcp4_parser.cc"
    break;

  case 804: // $@129: %empty
#line 2817 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4470 "dhcp4_parser.cc"
    break;

  case 805: // logger_entry: "{" $@129 logger_params "}"
#line 2821 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4478 "dhcp4_parser.cc"
    break;

  case 808: // logger_params: logger_params ","
#line 2827 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4486 "dhcp4_parser.cc"
    break;

  case 816: // debuglevel: "debuglevel" ":" "integer"
#line 2841 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4496 "dhcp4_parser.cc"
    break;

  case 817: // $@130: %empty
#line 2847 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4505 "dhcp4_parser.cc"
    break;

  case 818: // severity: "severity" $@130 ":" "constant string"
#line 2850 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4515 "dhcp4_parser.cc"
    break;

  case 819: // $@131: %empty
#line 2856 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4527 "dhcp4_parser.cc"
    break;

  case 820: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2862 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4536 "dhcp4_parser.cc"
    break;

  case 823: // output_options_list_content: output_options_list_content ","
#line 2869 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4544 "dhcp4_parser.cc"
    break;

  case 824: // $@132: %empty
#line 2874 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4554 "dhcp4_parser.cc"
    break;

  case 825: // output_entry: "{" $@132 output_params_list "}"
#line 2878 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4562 "dhcp4_parser.cc"
    break;

  case 828: // output_params_list: output_params_list ","
#line 2884 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4570 "dhcp4_parser.cc"
    break;

  case 834: // $@133: %empty
#line 2896 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4579 "dhcp4_parser.cc"
    break;

  case 835: // output: "output" $@133 ":" "constant string"
#line 2899 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4589 "dhcp4_parser.cc"
    break;

  case 836: // flush: "flush" ":" "boolean"
#line 2905 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4599 "dhcp4_parser.cc"
    break;

  case 837: // maxsize: "maxsize" ":" "integer"
#line 2911 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4609 "dhcp4_parser.cc"
    break;

  case 838: // maxver: "maxver" ":" "integer"
#line 2917 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4619 "dhcp4_parser.cc"
    break;

  case 839: // $@134: %empty
#line 2923 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4628 "dhcp4_parser.cc"
    break;

  case 840: // pattern: "pattern" $@134 ":" "constant string"
#line 2926 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4638 "dhcp4_parser.cc"
    break;

  case 841: // $@135: %empty
#line 2932 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4650 "dhcp4_parser.cc"
    break;

  case 842: // compatibility: "compatibility" $@135 ":" "{" compatibility_params "}"
#line 2938 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4659 "dhcp4_parser.cc"
    break;

  case 845: // compatibility_params: compatibility_params ","
#line 2945 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4667 "dhcp4_parser.cc"
    break;

  case 851: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2957 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4677 "dhcp4_parser.cc"
    break;

  case 852: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 2963 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4687 "dhcp4_parser.cc"
    break;

  case 853: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 2969 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4697 "dhcp4_parser.cc"
    break;

  case 854: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 2975 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4707 "dhcp4_parser.cc"
    break;


#line 4711 "dhcp4_parser.cc"

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

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
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


  const short Dhcp4Parser::yypact_ninf_ = -1006;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     195, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006,    38,    41,    40,    42,    50,    66,
      86,    94,   100,   108,   115,   136,   158,   178, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006,    41,  -160,   163,   199,    87,   647,
      93,    46,    82,    97,   267,   -89,   446,   211, -1006,    56,
     130,    61,   181,   190, -1006,    48, -1006, -1006, -1006, -1006,
      79,   192,   205, -1006, -1006, -1006,   216, -1006, -1006, -1006,
     249,   298,   311,   312,   320,   324,   333,   340,   351,   367,
     369, -1006,   383,   384,   408,   425,   426, -1006, -1006, -1006,
     427,   439,   442,   444, -1006, -1006, -1006,   445, -1006, -1006,
   -1006, -1006, -1006,   447,   448,   449, -1006, -1006, -1006, -1006,
   -1006,   450, -1006, -1006, -1006, -1006, -1006, -1006,   451,   452,
     453, -1006, -1006,   454, -1006,    78, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006,   456,   457,   459,   462,
   -1006,    88, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   464, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   111,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006,   127, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006,   283,   387, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   362, -1006,
   -1006,   465, -1006, -1006, -1006,   466, -1006, -1006,   402,   438,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006,   467,   470,   474, -1006, -1006, -1006, -1006,
     476,   479, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,   144, -1006, -1006, -1006,   481,
   -1006, -1006,   482, -1006,   483,   484, -1006, -1006,   486,   490,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006,   168, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,   493,   180, -1006, -1006, -1006,
   -1006,    41,    41, -1006,   236,   498, -1006, -1006,   502,   504,
     506,   295,   296,   301,   511,   513,   516,   306,   518,   519,
     520,   313,   316,   317,   318,   319,   308,   321,   322,   325,
     329,   330,   531,   332,   336,   331,   341,   342,   532,   546,
     550,   343,   346,   352,   347,   557,   563,   567,   357,   570,
     571,   572,   575,   578,   373,   375,   376,   585,   590,   593,
     596,   600,   390,   603,   604,   618,   619,   620,   621,   409,
     410,   413,   627,   628, -1006,   199, -1006,   629,   630,   631,
     419,   420,   423,   424,    87, -1006,   636,   637,   638,   639,
     640,   641,   431,   643,   644,   645,   647, -1006,   646,    93,
   -1006,   649,   651,   652,   653,   654,   655,   657,   658, -1006,
      46, -1006,   659,   660,   455,   661,   663,   664,   458, -1006,
      97,   665,   468,   469,   471, -1006,   267,   667,   669,   -74,
   -1006,   477,   670,   672,   472,   679,   478,   480,   680,   687,
     485,   487,   693,   694,   695,   696,   446, -1006,   697,   488,
     211, -1006, -1006, -1006,   701,   699,   715,   716,   717, -1006,
   -1006, -1006,   522,   526,   528, -1006,   718,   736,   739, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
     536, -1006, -1006, -1006, -1006, -1006,   155,   537,   538, -1006,
   -1006, -1006, -1006,   740,   749,   751, -1006,   549,   759,   758,
     552,   122, -1006, -1006, -1006,   765,   766,   768,   769,   771,
   -1006,   772,   773,   774,   775,   561,   569, -1006, -1006, -1006,
     780,   779, -1006,   782,   194,   206, -1006, -1006, -1006, -1006,
   -1006,   574,   576,   577,   784,   579,   580, -1006,   782,   581,
     785, -1006,   582, -1006,   782,   583,   584,   586,   587,   588,
     589,   591, -1006,   592,   594, -1006,   595,   597,   598, -1006,
   -1006,   599, -1006, -1006, -1006, -1006,   601,   758, -1006, -1006,
     602,   605, -1006,   606, -1006, -1006,    14,   622, -1006, -1006,
     155,   607,   608,   609, -1006,   799, -1006, -1006,    41,   199,
     211,    87,   223, -1006, -1006, -1006,   372,   372,   800, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   803,   807,
     810, -1006,   811, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006,    83,   817,   818,   819,    99,   -77,    49,     7,   446,
   -1006, -1006,   820,  -110, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,   821, -1006, -1006, -1006, -1006,
     123, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   800,
   -1006,   183,   251,   286, -1006, -1006,   287, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006,   827,   828,   829,   830,   831,   838,
     839,   840,   841,   842, -1006,   843, -1006, -1006, -1006, -1006,
   -1006,   300, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006,   309, -1006,   844,   648, -1006, -1006,
     845,   846, -1006, -1006,   847,   849, -1006, -1006,   848,   852,
   -1006, -1006,   850,   854, -1006, -1006, -1006, -1006, -1006, -1006,
      34, -1006, -1006, -1006, -1006, -1006, -1006, -1006,    91, -1006,
   -1006,   853,   855, -1006, -1006,   856,   857, -1006,   859,   860,
     861,   862,   863,   864,   310, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006,   865,   866,   877, -1006,   335, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   337, -1006,
   -1006, -1006,   878, -1006,   879, -1006, -1006, -1006,   338, -1006,
   -1006, -1006, -1006, -1006,   344, -1006,   126, -1006,   880,   892,
     893,   894, -1006,   345, -1006, -1006, -1006, -1006, -1006,   634,
   -1006,   896,   900, -1006, -1006, -1006, -1006,   891,   898, -1006,
   -1006, -1006,   901,   902,   223, -1006,   903,   904,   905,   906,
     698,   703,   700,   705,   708,   709,   710,   714,   719,   721,
     907,   722,   910,   914,   926,   928,   372, -1006, -1006,   372,
   -1006,   800,   647, -1006,   803,    97, -1006,   807,   267, -1006,
     810,   806, -1006,   811,    83, -1006,   265,   817, -1006,    46,
   -1006,   818,   -89, -1006,   819,   723,   724,   725,   726,   727,
     729,    99, -1006,   730,   731,   734,   -77, -1006,   929,   946,
      49, -1006,   735,   949,   745,   967,     7, -1006, -1006,   -40,
     820, -1006,   757,   792,   796,   809,  -110, -1006, -1006,   969,
     987,    93, -1006,   821,  1013, -1006, -1006,   813,   816, -1006,
     113,   881,   885,   886, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006,   268, -1006,   888,   889,   890,   895,
   -1006,   348, -1006,   366, -1006,  1015, -1006,  1023, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,   386, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,  1029, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006,  1035,  1050, -1006, -1006, -1006, -1006, -1006, -1006,
    1046, -1006,   406, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,   897,   899, -1006, -1006,   908,
   -1006,    41, -1006, -1006,  1101, -1006, -1006, -1006, -1006, -1006,
     434, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006,   909,   436, -1006,   782, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006,   806, -1006,  1102,
    1103,   911, -1006,   265, -1006, -1006, -1006, -1006, -1006, -1006,
    1104,   912,  1106,   -40, -1006, -1006, -1006, -1006, -1006,   915,
     916, -1006, -1006,  1107, -1006,   917, -1006, -1006, -1006,  1108,
   -1006, -1006,   166, -1006,   -31,  1108, -1006, -1006,  1110,  1112,
    1113, -1006,   437, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
    1114,   918,   919,   921,  1115,   -31, -1006,   923, -1006, -1006,
   -1006,   924, -1006, -1006, -1006
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   199,     9,   377,    11,   593,    13,
     620,    15,   511,    17,   520,    19,   559,    21,   339,    23,
     738,    25,   789,    27,    46,    39,     0,     0,     0,     0,
       0,   622,     0,   522,   561,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   787,   184,   217,
       0,     0,     0,   642,   644,   646,     0,   215,   228,   230,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   148,     0,     0,     0,     0,     0,   159,   166,   168,
       0,     0,     0,     0,   368,   509,   550,     0,   151,   454,
     607,   609,   447,     0,     0,     0,   301,   670,   611,   330,
     351,     0,   316,   705,   719,   736,   173,   175,     0,     0,
       0,   799,   841,     0,   136,     0,    67,    70,    71,    72,
      73,    74,   108,   109,   110,   111,   112,    75,   103,   133,
     134,    92,    93,    94,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   114,   115,   125,   126,   127,   129,   130,
     131,   135,    78,    79,   100,    80,    81,    82,   128,    86,
      87,    76,   105,   106,   107,   104,    77,    84,    85,    98,
      99,   101,    95,    96,    97,    83,    88,    89,    90,    91,
     102,   113,   132,   201,   203,   207,     0,     0,     0,     0,
     198,     0,   186,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   432,   434,   436,   584,   430,   438,     0,   442,
     440,   666,   429,   382,   383,   384,   385,   386,   410,   411,
     412,   413,   414,   427,   400,   401,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,   428,     0,
     379,   389,   405,   406,   407,   390,   392,   393,   396,   397,
     398,   395,   391,   387,   388,   408,   409,   394,   402,   403,
     404,   399,   605,   604,   600,   601,   599,     0,   595,   598,
     602,   603,   664,   652,   654,   658,   656,   662,   660,   648,
     641,   635,   639,   640,     0,   623,   624,   636,   637,   638,
     632,   627,   633,   629,   630,   631,   634,   628,     0,   540,
     276,     0,   544,   542,   547,     0,   536,   537,     0,   523,
     524,   527,   539,   528,   529,   530,   546,   531,   532,   533,
     534,   535,   577,     0,     0,     0,   575,   576,   579,   580,
       0,   562,   563,   566,   567,   568,   569,   570,   571,   572,
     573,   574,   347,   349,   344,     0,   341,   345,   346,     0,
     775,   762,     0,   765,     0,     0,   769,   773,     0,     0,
     779,   781,   783,   785,   760,   758,   759,     0,   740,   743,
     744,   745,   746,   747,   748,   749,   750,   755,   751,   752,
     753,   754,   756,   757,   796,     0,     0,   791,   794,   795,
      45,    50,     0,    37,    43,     0,    64,    60,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,    69,    66,     0,     0,     0,
       0,     0,     0,     0,   188,   200,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   381,   378,     0,   597,
     594,     0,     0,     0,     0,     0,     0,     0,     0,   621,
     626,   512,     0,     0,     0,     0,     0,     0,     0,   521,
     526,     0,     0,     0,     0,   560,   565,     0,     0,   343,
     340,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   742,   739,     0,     0,
     793,   790,    49,    41,     0,     0,     0,     0,     0,   153,
     154,   155,     0,     0,     0,   183,     0,     0,     0,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
       0,   178,   179,   156,   157,   158,     0,     0,     0,   170,
     171,   172,   177,     0,     0,     0,   150,     0,     0,     0,
       0,     0,   444,   445,   446,     0,     0,     0,     0,     0,
     704,     0,     0,     0,     0,     0,     0,   180,   181,   182,
       0,     0,    68,     0,     0,     0,   211,   212,   213,   214,
     187,     0,     0,     0,     0,     0,     0,   453,     0,     0,
       0,   380,     0,   596,     0,     0,     0,     0,     0,     0,
       0,     0,   625,     0,     0,   538,     0,     0,     0,   549,
     525,     0,   581,   582,   583,   564,     0,     0,   342,   761,
       0,     0,   764,     0,   767,   768,     0,     0,   777,   778,
       0,     0,     0,     0,   741,     0,   798,   792,     0,     0,
       0,     0,     0,   643,   645,   647,     0,     0,   232,   149,
     161,   162,   163,   164,   165,   160,   167,   169,   370,   513,
     552,   152,   456,    38,   608,   610,   449,   450,   451,   452,
     448,     0,     0,   613,   332,     0,     0,     0,     0,     0,
     174,   176,     0,     0,    51,   202,   205,   206,   204,   209,
     210,   208,   433,   435,   437,   586,   431,   439,   443,   441,
       0,   606,   665,   653,   655,   659,   657,   663,   661,   649,
     541,   277,   545,   543,   548,   578,   348,   350,   776,   763,
     766,   771,   772,   770,   774,   780,   782,   784,   786,   232,
      42,     0,     0,     0,   224,   226,     0,   219,   222,   223,
     264,   269,   271,   273,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   287,     0,   293,   295,   297,   299,
     263,     0,   239,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,     0,   237,     0,   233,   234,   375,
       0,   371,   372,   518,     0,   514,   515,   557,     0,   553,
     554,   461,     0,   457,   458,   311,   312,   313,   314,   315,
       0,   303,   306,   307,   308,   309,   310,   675,     0,   672,
     618,     0,   614,   615,   337,     0,   333,   334,     0,     0,
       0,     0,     0,     0,     0,   353,   356,   357,   358,   359,
     360,   361,     0,     0,     0,   326,     0,   318,   321,   322,
     323,   324,   325,   715,   717,   714,   712,   713,     0,   707,
     710,   711,     0,   731,     0,   734,   727,   728,     0,   721,
     724,   725,   726,   729,     0,   804,     0,   801,     0,     0,
       0,     0,   850,     0,   843,   846,   847,   848,   849,    53,
     591,     0,   587,   588,   650,   668,   669,     0,     0,    62,
     788,   185,     0,     0,   221,   218,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   241,   216,   229,     0,
     231,   236,     0,   369,   374,   522,   510,   517,   561,   551,
     556,     0,   455,   460,   305,   302,   677,   674,   671,   622,
     612,   617,     0,   331,   336,     0,     0,     0,     0,     0,
       0,   355,   352,     0,     0,     0,   320,   317,     0,     0,
     709,   706,     0,     0,     0,     0,   723,   720,   737,     0,
     803,   800,     0,     0,     0,     0,   845,   842,    55,     0,
      54,     0,   585,   590,     0,   667,   797,     0,     0,   220,
       0,     0,     0,     0,   275,   278,   279,   280,   281,   282,
     283,   284,   285,   286,     0,   292,     0,     0,     0,     0,
     240,     0,   235,     0,   373,     0,   516,     0,   555,   508,
     484,   485,   486,   469,   470,   489,   490,   491,   492,   493,
     506,   472,   473,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   507,   466,   467,   468,   482,
     483,   479,   480,   481,   478,     0,   463,   471,   487,   488,
     474,   475,   476,   477,   459,   304,   699,   701,     0,   693,
     694,   695,   696,   697,   698,   686,   687,   691,   692,   688,
     689,   690,     0,   678,   679,   682,   683,   684,   685,   673,
       0,   616,     0,   335,   362,   363,   364,   365,   366,   367,
     354,   327,   328,   329,   319,     0,     0,   708,   730,     0,
     733,     0,   722,   819,     0,   817,   815,   809,   813,   814,
       0,   806,   811,   812,   810,   802,   851,   852,   853,   854,
     844,    52,    57,     0,   589,     0,   225,   227,   266,   267,
     268,   265,   270,   272,   274,   289,   290,   291,   288,   294,
     296,   298,   300,   238,   376,   519,   558,   465,   462,     0,
       0,     0,   676,   681,   619,   338,   716,   718,   732,   735,
       0,     0,     0,   808,   805,    56,   592,   651,   464,     0,
       0,   703,   680,     0,   816,     0,   807,   700,   702,     0,
     818,   824,     0,   821,     0,   823,   820,   834,     0,     0,
       0,   839,     0,   826,   829,   830,   831,   832,   833,   822,
       0,     0,     0,     0,     0,   828,   825,     0,   836,   837,
     838,     0,   827,   835,   840
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,   -52, -1006,  -598, -1006,   428,
   -1006, -1006, -1006, -1006, -1006, -1006,  -638, -1006, -1006, -1006,
     -67, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   401,   616,
     -30,   -28,    26,   -54,   -34,   -27,     0,    16,    23,    39,
   -1006, -1006, -1006, -1006,    44, -1006, -1006,    47,    51,    52,
      54,    55,    57, -1006,   414,    58, -1006,    59, -1006,    62,
      65,    69,    70, -1006,    72, -1006,    73, -1006, -1006, -1006,
   -1006, -1006,    36, -1006, -1006,   405,   625, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006,   148, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006,   334, -1006,   129, -1006,  -713,
     135, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006,   -45, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006,   109, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006,    96, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006,   110, -1006, -1006, -1006,   114,   610,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006,   104, -1006, -1006,
   -1006, -1006, -1006, -1006, -1005, -1006, -1006, -1006,   133, -1006,
   -1006, -1006,   138,   626, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006,  -998, -1006,   -65, -1006,   -53, -1006,    75,    76,
      77,    80, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   125,
   -1006, -1006,   -96,   -62, -1006, -1006, -1006, -1006, -1006,   137,
   -1006, -1006, -1006,   140, -1006,   611, -1006,   -63, -1006, -1006,
   -1006, -1006, -1006,   -61, -1006, -1006, -1006, -1006, -1006,   -26,
   -1006, -1006, -1006,   139, -1006, -1006, -1006,   142, -1006,   612,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006,    84, -1006, -1006, -1006,    85,   624, -1006, -1006,
     -49, -1006,   -10, -1006,   -51, -1006, -1006, -1006,   131, -1006,
   -1006, -1006,   134, -1006,   632,     3, -1006,    13, -1006,    29,
   -1006,   378, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,  -995,
   -1006, -1006, -1006, -1006, -1006,   143, -1006, -1006, -1006,   -88,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
     116, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   117, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,   412,
     613, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
     461,   615, -1006, -1006, -1006, -1006, -1006, -1006,   107, -1006,
   -1006,   -99, -1006, -1006, -1006, -1006, -1006, -1006,  -111, -1006,
   -1006,  -130, -1006, -1006, -1006, -1006, -1006, -1006, -1006, -1006,
   -1006, -1006,   112, -1006, -1006, -1006, -1006
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   744,
      82,    83,    39,    64,    79,    80,   765,   969,  1069,  1070,
     840,    41,    66,    85,   435,    86,    43,    67,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   462,   169,   170,   479,   171,   172,   173,   174,
     175,   176,   177,   468,   735,   178,   469,   179,   470,   180,
     181,   182,   183,   497,   184,   498,   185,   186,   187,   188,
     189,   190,   191,   192,   439,   231,   232,    45,    68,   233,
     507,   234,   508,   768,   235,   509,   771,   236,   237,   238,
     239,   193,   448,   194,   440,   816,   817,   818,   982,   819,
     983,   195,   449,   196,   450,   866,   867,   868,  1009,   841,
     842,   843,   986,  1231,   844,   987,   845,   988,   846,   989,
     847,   848,   543,   849,   850,   851,   852,   853,   854,   855,
     856,   857,   858,  1000,  1238,   859,   860,  1002,   861,  1003,
     862,  1004,   863,  1005,   197,   487,   890,   891,   892,   893,
     894,   895,   896,   198,   493,   926,   927,   928,   929,   930,
     199,   490,   905,   906,   907,  1032,    59,    75,   385,   386,
     387,   557,   388,   558,   200,   491,   914,   915,   916,   917,
     918,   919,   920,   921,   201,   475,   870,   871,   872,  1012,
      47,    69,   279,   280,   281,   520,   282,   516,   283,   517,
     284,   518,   285,   521,   286,   524,   287,   523,   202,   203,
     204,   205,   483,   750,   292,   206,   480,   882,   883,   884,
    1021,  1145,  1146,   207,   476,    53,    72,   874,   875,   876,
    1015,    55,    73,   348,   349,   350,   351,   352,   353,   354,
     542,   355,   546,   356,   545,   357,   358,   547,   359,   208,
     477,   878,   879,   880,  1018,    57,    74,   370,   371,   372,
     373,   374,   551,   375,   376,   377,   378,   379,   294,   519,
     971,   972,   973,  1071,    49,    70,   307,   308,   309,   528,
     209,   481,   210,   482,   211,   489,   901,   902,   903,  1029,
      51,    71,   324,   325,   326,   212,   444,   213,   445,   214,
     446,   330,   538,   976,  1074,   331,   532,   332,   533,   333,
     535,   334,   534,   335,   537,   336,   536,   337,   531,   301,
     525,   977,   215,   488,   898,   899,  1026,  1172,  1173,  1174,
    1175,  1176,  1249,  1177,  1250,  1178,   216,   217,   494,   938,
     939,   940,  1048,   941,  1049,   218,   495,   948,   949,   950,
     951,  1053,   952,   953,  1055,   219,   496,    61,    76,   407,
     408,   409,   410,   563,   411,   412,   565,   413,   414,   415,
     568,   803,   416,   569,   417,   562,   418,   419,   420,   572,
     421,   573,   422,   574,   423,   575,   220,   438,    63,    77,
     426,   427,   428,   578,   429,   221,   502,   956,   957,  1059,
    1210,  1211,  1212,  1213,  1262,  1214,  1260,  1282,  1283,  1284,
    1292,  1293,  1294,  1300,  1295,  1296,  1297,  1298,  1304,   222,
     503,   963,   964,   965,   966,   967,   968
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     154,   230,   252,   303,   320,   304,   346,   366,   384,   404,
     338,   368,    78,   369,   864,   256,  1137,   305,   297,   240,
     295,   310,   322,  1138,   360,   380,  1153,   405,   347,   367,
     778,   743,   801,   130,   131,   257,   782,  1024,    28,   253,
    1025,   254,   258,   293,   306,   321,    29,    40,    30,    42,
      31,   436,   382,   383,    81,   340,   437,    44,   241,   296,
     311,   323,   430,   361,   381,   432,   406,   382,   383,   259,
     130,   131,   298,    46,   327,   922,   923,   924,    93,    94,
      95,   505,   299,   441,   328,   260,   506,   958,   959,   960,
     961,   514,   261,    48,  1027,   255,   515,  1028,   300,   743,
     329,    50,   223,   224,   153,   278,   225,    52,   262,   226,
     227,   228,   229,   263,   526,    54,   264,   130,   131,   527,
     265,   266,    56,   267,   268,   153,   269,   270,   271,  1060,
     529,   272,  1061,   431,   273,   530,   339,   153,   274,   275,
     126,   276,   277,    58,   288,   289,   290,   559,  1203,   291,
    1204,  1205,   560,  1228,  1229,  1230,   130,   131,  1287,   130,
     131,  1288,  1289,  1290,  1291,    60,   942,   943,   944,  1285,
     312,   576,  1286,    84,   153,   125,   577,   313,   314,   315,
     316,   317,   318,   580,   319,    62,   505,   126,   581,   433,
     802,   979,   340,   434,   341,   342,   442,   130,   131,   343,
     344,   345,   302,   130,   131,   933,   934,   130,   131,   443,
      87,   766,   767,    88,   885,   886,   887,   888,   249,   889,
     447,   945,   250,   424,   425,    89,   769,   770,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   746,   747,
     748,   749,  1137,   908,   909,   910,   911,   912,   913,  1138,
     814,   815,  1153,   451,   580,    32,    33,    34,    35,   980,
     153,   319,   974,   153,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   514,
     984,   539,   125,   126,   981,   985,  1101,    93,    94,    95,
      96,   153,   452,  1006,   127,   128,   129,   153,  1007,   130,
     131,   153,  1006,  1041,   132,   453,   454,  1008,  1042,   133,
     134,   135,   136,   137,   455,  1235,  1236,  1237,   456,   138,
     100,   101,   102,   730,   731,   732,   733,   457,  1046,   139,
    1050,  1056,   140,  1047,   458,  1051,  1057,   576,  1066,   141,
     142,  1006,  1058,  1067,   143,   459,  1243,   144,   125,   126,
     340,   145,   340,   362,   341,   342,   363,   364,   365,   526,
     541,   460,   734,   461,  1244,   130,   131,   130,   131,   582,
     583,   146,   147,   148,   149,   150,   151,   463,   464,  1247,
     540,  1156,  1157,  1158,  1248,   152,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,   559,
     549,   820,   465,   153,  1255,   821,   822,   823,   824,   825,
     826,   827,   828,   829,   830,   831,   832,   833,   834,   466,
     467,   471,   835,   836,   837,   838,   839,  1263,   154,   529,
    1305,   550,  1264,   472,  1266,  1306,   473,   230,   474,   478,
     584,   484,   485,   486,   492,   499,   500,   501,   504,   252,
     510,   511,   303,   512,   304,   240,   513,   340,   522,   544,
     548,   552,   256,   320,   553,   297,   305,   295,   554,   153,
     310,   153,   556,   346,   555,   561,   564,   566,   567,   366,
     570,   322,   257,   368,   571,   369,   253,   579,   254,   258,
     293,   360,   585,   306,   241,   347,   586,   380,   587,   404,
     588,   367,   589,   590,   321,   592,   296,   593,   591,   311,
     594,   595,   596,   597,   598,   604,   259,   405,   599,   298,
     323,   600,   601,   602,   603,   610,   616,   605,   606,   299,
     361,   607,   260,   327,   608,   609,   381,   611,   613,   261,
     617,   612,   255,   328,   618,   300,   130,   131,   614,   615,
     619,   623,   278,   620,   622,   262,   406,   624,   621,   329,
     263,   625,   626,   264,   627,   628,   629,   265,   266,   630,
     267,   268,   631,   269,   270,   271,   153,  1267,   272,   635,
     632,   273,   633,   634,   636,   274,   275,   637,   276,   277,
     638,   288,   289,   290,   639,   640,   291,   641,   642,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   643,   644,   645,   646,   647,   648,   402,   403,
     649,   650,   651,   653,   654,   655,   656,   657,   658,   659,
     661,   662,   663,   664,   665,   666,   667,   668,   669,   670,
     672,  1011,   154,   674,   230,   675,   676,   677,   678,   679,
     153,   680,   681,   683,   684,   686,   810,   687,   688,   691,
     685,   696,   240,   697,   700,   689,   701,    91,    92,    93,
      94,    95,    96,   703,   706,   692,   693,   702,   694,   925,
     935,   707,   404,   704,   699,   705,   962,   710,   711,   712,
     713,   715,   708,   716,   709,   718,   719,   931,   936,   946,
     405,   241,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   720,   721,   722,   726,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   723,   242,   243,   244,
     724,   126,   725,   727,   728,   738,   932,   937,   947,   406,
     729,   736,   737,   128,   739,   245,   740,   130,   131,   246,
     247,   248,   132,   741,   742,    30,   745,   133,   134,   135,
     751,   752,   249,   753,   754,   760,   250,   138,   755,   756,
     757,   758,   759,   761,   251,   762,   763,   764,   772,   775,
     773,   774,   780,   776,   777,   779,   781,   783,   784,   804,
     785,   786,   787,   788,   809,   789,   790,   865,   791,   792,
     869,   793,   794,   795,   873,   796,   798,   877,   881,   799,
     800,   806,   807,   808,   897,   900,   904,   955,   970,   146,
     147,   990,   991,   992,   993,   994,    91,    92,    93,    94,
      95,    96,   995,   996,   997,   998,   999,  1001,  1068,  1014,
    1010,  1013,  1017,  1016,  1019,  1020,  1022,  1023,  1031,  1030,
    1034,   153,  1033,  1035,  1036,  1037,  1038,  1039,  1040,  1043,
    1044,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,  1045,  1052,  1054,  1062,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,  1063,  1064,  1065,  1075,
     126,   340,  1072,  1073,  1076,  1077,  1078,  1080,  1081,  1082,
    1083,  1094,   128,  1084,  1096,  1086,   130,   131,  1097,   247,
    1085,   132,  1087,  1088,  1089,  1090,   133,   134,   135,  1091,
    1098,   249,  1099,  1195,  1092,   250,  1093,  1095,  1184,  1185,
    1186,  1187,  1188,   251,  1189,   252,  1192,  1191,   346,  1193,
    1196,   366,  1198,  1199,  1109,   368,  1139,   369,   256,  1159,
    1200,   297,   320,   295,  1165,   384,   360,  1113,  1140,   380,
     347,  1201,  1148,   367,  1216,  1221,  1136,  1167,   257,   925,
     322,  1164,   253,   935,   254,   258,   293,  1114,   146,   147,
    1222,  1110,  1206,  1111,  1115,  1147,  1160,   931,  1161,   962,
    1166,   936,   296,   321,   303,   361,   304,   946,   381,  1217,
    1208,  1149,   259,  1218,  1207,   298,  1168,  1225,   305,   323,
     153,  1116,   310,  1245,  1150,   299,  1219,  1226,   260,  1169,
    1227,  1246,   327,  1251,  1151,   261,   932,  1117,   255,  1170,
     937,   300,   328,  1252,  1118,   306,   947,  1112,   278,  1209,
    1152,   262,  1162,  1253,  1254,  1171,   263,  1135,   329,   264,
    1119,   311,  1163,   265,   266,  1120,   267,   268,  1121,   269,
     270,   271,  1122,  1123,   272,  1124,  1125,   273,  1126,  1127,
    1128,   274,   275,  1129,   276,   277,  1130,   288,   289,   290,
    1131,  1132,   291,  1133,  1134,  1232,  1141,  1142,  1143,  1233,
    1234,  1144,  1239,  1240,  1241,  1261,  1269,  1270,  1273,  1242,
    1275,  1256,  1279,  1257,  1301,  1281,  1302,  1303,  1307,  1311,
     811,   652,  1258,  1265,   805,   797,   813,  1274,  1271,  1277,
    1278,  1280,  1079,  1155,  1309,  1308,  1310,  1313,  1314,   660,
    1102,  1100,  1194,   978,  1183,  1190,  1182,  1104,  1154,  1259,
    1103,  1268,   671,   673,  1106,  1105,  1223,  1224,   975,  1108,
    1107,   690,  1181,  1180,  1276,  1272,  1197,  1215,   695,   698,
    1179,   954,   682,  1202,  1299,  1312,     0,     0,  1220,     0,
    1109,   812,  1139,     0,     0,     0,  1159,     0,     0,   714,
       0,  1165,     0,  1113,  1140,   717,  1206,     0,  1148,     0,
       0,     0,  1136,     0,  1167,     0,     0,     0,  1164,     0,
       0,     0,     0,  1114,  1208,     0,     0,  1110,  1207,  1111,
    1115,  1147,     0,  1160,     0,  1161,     0,  1166,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1149,     0,     0,
       0,     0,     0,  1168,     0,     0,     0,  1116,     0,     0,
    1150,     0,     0,  1209,     0,     0,  1169,     0,     0,     0,
    1151,     0,     0,  1117,     0,     0,  1170,     0,     0,     0,
    1118,     0,     0,  1112,     0,     0,  1152,     0,     0,  1162,
       0,     0,  1171,  1135,     0,     0,  1119,     0,     0,  1163,
       0,  1120,     0,     0,  1121,     0,     0,     0,  1122,  1123,
       0,  1124,  1125,     0,  1126,  1127,  1128,     0,     0,  1129,
       0,     0,  1130,     0,     0,     0,  1131,  1132,     0,  1133,
    1134,     0,  1141,  1142,  1143,     0,     0,  1144
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      72,    74,    64,    74,   727,    69,  1021,    70,    69,    68,
      69,    70,    71,  1021,    73,    74,  1021,    76,    73,    74,
     668,   629,    18,   110,   111,    69,   674,     3,     0,    69,
       6,    69,    69,    69,    70,    71,     5,     7,     7,     7,
       9,     3,   141,   142,   214,    95,     8,     7,    68,    69,
      70,    71,     6,    73,    74,     4,    76,   141,   142,    69,
     110,   111,    69,     7,    71,   152,   153,   154,    32,    33,
      34,     3,    69,     4,    71,    69,     8,   197,   198,   199,
     200,     3,    69,     7,     3,    69,     8,     6,    69,   697,
      71,     7,    15,    16,   214,    69,    19,     7,    69,    22,
      23,    24,    25,    69,     3,     7,    69,   110,   111,     8,
      69,    69,     7,    69,    69,   214,    69,    69,    69,     3,
       3,    69,     6,     3,    69,     8,    39,   214,    69,    69,
      94,    69,    69,     7,    69,    69,    69,     3,   188,    69,
     190,   191,     8,    40,    41,    42,   110,   111,   189,   110,
     111,   192,   193,   194,   195,     7,   159,   160,   161,     3,
     124,     3,     6,    10,   214,    93,     8,   131,   132,   133,
     134,   135,   136,     3,   138,     7,     3,    94,     8,     8,
     176,     8,    95,     3,    97,    98,     4,   110,   111,   102,
     103,   104,   109,   110,   111,   156,   157,   110,   111,     4,
      11,    17,    18,    14,   131,   132,   133,   134,   125,   136,
       4,   214,   129,    12,    13,    26,    20,    21,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,   116,   117,
     118,   119,  1247,   144,   145,   146,   147,   148,   149,  1247,
      27,    28,  1247,     4,     3,   214,   215,   216,   217,     8,
     214,   138,   139,   214,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,     3,
       3,     8,    93,    94,     8,     8,  1009,    32,    33,    34,
      35,   214,     4,     3,   105,   106,   107,   214,     8,   110,
     111,   214,     3,     3,   115,     4,     4,     8,     8,   120,
     121,   122,   123,   124,     4,    57,    58,    59,     4,   130,
      65,    66,    67,   178,   179,   180,   181,     4,     3,   140,
       3,     3,   143,     8,     4,     8,     8,     3,     3,   150,
     151,     3,     8,     8,   155,     4,     8,   158,    93,    94,
      95,   162,    95,    96,    97,    98,    99,   100,   101,     3,
       8,     4,   217,     4,     8,   110,   111,   110,   111,   431,
     432,   182,   183,   184,   185,   186,   187,     4,     4,     3,
       3,   126,   127,   128,     8,   196,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,     3,
       8,    39,     4,   214,     8,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,     4,
       4,     4,    60,    61,    62,    63,    64,     3,   505,     3,
       3,     3,     8,     4,     8,     8,     4,   514,     4,     4,
     214,     4,     4,     4,     4,     4,     4,     4,     4,   526,
       4,     4,   529,     4,   529,   514,     4,    95,     4,     4,
       4,     4,   526,   540,     4,   526,   529,   526,     4,   214,
     529,   214,     3,   550,     8,     4,     4,     4,     4,   556,
       4,   540,   526,   556,     4,   556,   526,     4,   526,   526,
     526,   550,     4,   529,   514,   550,     4,   556,     4,   576,
       4,   556,   217,   217,   540,     4,   526,     4,   217,   529,
       4,   215,     4,     4,     4,   217,   526,   576,   215,   526,
     540,   215,   215,   215,   215,     4,     4,   216,   216,   526,
     550,   216,   526,   540,   215,   215,   556,   215,   217,   526,
       4,   215,   526,   540,     4,   526,   110,   111,   217,   217,
     217,     4,   526,   217,   217,   526,   576,     4,   216,   540,
     526,     4,   215,   526,     4,     4,     4,   526,   526,     4,
     526,   526,     4,   526,   526,   526,   214,  1225,   526,     4,
     217,   526,   217,   217,     4,   526,   526,     4,   526,   526,
       4,   526,   526,   526,     4,   215,   526,     4,     4,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,     4,     4,     4,     4,   217,   217,   182,   183,
     217,     4,     4,     4,     4,     4,   217,   217,   215,   215,
       4,     4,     4,     4,     4,     4,   215,     4,     4,     4,
       4,     3,   719,     4,   721,     4,     4,     4,     4,     4,
     214,     4,     4,     4,     4,     4,   718,     4,     4,     4,
     215,     4,   721,     4,     4,   217,     4,    30,    31,    32,
      33,    34,    35,     4,     4,   217,   217,   215,   217,   756,
     757,     4,   759,   215,   217,   215,   763,     4,     4,     4,
       4,     4,   217,   215,   217,     4,     7,   756,   757,   758,
     759,   721,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,     7,     7,     7,     7,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,   214,    90,    91,    92,
     214,    94,   214,     7,     5,     5,   756,   757,   758,   759,
     214,   214,   214,   106,     5,   108,     5,   110,   111,   112,
     113,   114,   115,   214,     5,     7,   214,   120,   121,   122,
       5,     5,   125,     5,     5,   214,   129,   130,     7,     7,
       7,     7,     7,   214,   137,     5,     7,     5,   214,     5,
     214,   214,     7,   214,   214,   214,   214,   214,   214,   177,
     214,   214,   214,   214,     5,   214,   214,     7,   214,   214,
       7,   214,   214,   214,     7,   214,   214,     7,     7,   214,
     214,   214,   214,   214,     7,     7,     7,     7,     7,   182,
     183,     4,     4,     4,     4,     4,    30,    31,    32,    33,
      34,    35,     4,     4,     4,     4,     4,     4,   214,     3,
       6,     6,     3,     6,     6,     3,     6,     3,     3,     6,
       3,   214,     6,     4,     4,     4,     4,     4,     4,     4,
       4,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,     4,     4,     4,     4,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     4,     4,     4,     8,
      94,    95,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,   106,   215,     4,   215,   110,   111,     4,   113,
     217,   115,   217,   215,   215,   215,   120,   121,   122,   215,
       4,   125,     4,     4,   215,   129,   215,   215,   215,   215,
     215,   215,   215,   137,   215,  1012,   215,   217,  1015,   215,
       4,  1018,   217,     4,  1021,  1018,  1021,  1018,  1012,  1026,
     215,  1012,  1029,  1012,  1026,  1032,  1015,  1021,  1021,  1018,
    1015,     4,  1021,  1018,   217,     6,  1021,  1026,  1012,  1046,
    1029,  1026,  1012,  1050,  1012,  1012,  1012,  1021,   182,   183,
       3,  1021,  1059,  1021,  1021,  1021,  1026,  1046,  1026,  1066,
    1026,  1050,  1012,  1029,  1071,  1015,  1071,  1056,  1018,   217,
    1059,  1021,  1012,   217,  1059,  1012,  1026,     4,  1071,  1029,
     214,  1021,  1071,     8,  1021,  1012,   217,   214,  1012,  1026,
     214,     8,  1029,     4,  1021,  1012,  1046,  1021,  1012,  1026,
    1050,  1012,  1029,     8,  1021,  1071,  1056,  1021,  1012,  1059,
    1021,  1012,  1026,     3,     8,  1026,  1012,  1021,  1029,  1012,
    1021,  1071,  1026,  1012,  1012,  1021,  1012,  1012,  1021,  1012,
    1012,  1012,  1021,  1021,  1012,  1021,  1021,  1012,  1021,  1021,
    1021,  1012,  1012,  1021,  1012,  1012,  1021,  1012,  1012,  1012,
    1021,  1021,  1012,  1021,  1021,   214,  1021,  1021,  1021,   214,
     214,  1021,   214,   214,   214,     4,     4,     4,     4,   214,
       4,   214,     5,   214,     4,     7,     4,     4,     4,     4,
     719,   505,   214,   214,   710,   697,   721,   215,   217,   214,
     214,   214,   984,  1024,   215,   217,   215,   214,   214,   514,
    1011,  1006,  1046,   809,  1034,  1041,  1032,  1014,  1023,  1201,
    1012,  1247,   526,   529,  1017,  1015,  1071,  1073,   780,  1020,
    1018,   550,  1031,  1029,  1263,  1253,  1050,  1060,   556,   559,
    1027,   759,   540,  1056,  1285,  1305,    -1,    -1,  1066,    -1,
    1247,   720,  1247,    -1,    -1,    -1,  1253,    -1,    -1,   576,
      -1,  1253,    -1,  1247,  1247,   580,  1263,    -1,  1247,    -1,
      -1,    -1,  1247,    -1,  1253,    -1,    -1,    -1,  1253,    -1,
      -1,    -1,    -1,  1247,  1263,    -1,    -1,  1247,  1263,  1247,
    1247,  1247,    -1,  1253,    -1,  1253,    -1,  1253,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1247,    -1,    -1,
      -1,    -1,    -1,  1253,    -1,    -1,    -1,  1247,    -1,    -1,
    1247,    -1,    -1,  1263,    -1,    -1,  1253,    -1,    -1,    -1,
    1247,    -1,    -1,  1247,    -1,    -1,  1253,    -1,    -1,    -1,
    1247,    -1,    -1,  1247,    -1,    -1,  1247,    -1,    -1,  1253,
      -1,    -1,  1253,  1247,    -1,    -1,  1247,    -1,    -1,  1253,
      -1,  1247,    -1,    -1,  1247,    -1,    -1,    -1,  1247,  1247,
      -1,  1247,  1247,    -1,  1247,  1247,  1247,    -1,    -1,  1247,
      -1,    -1,  1247,    -1,    -1,    -1,  1247,  1247,    -1,  1247,
    1247,    -1,  1247,  1247,  1247,    -1,    -1,  1247
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,     0,     5,
       7,     9,   214,   215,   216,   217,   233,   234,   235,   240,
       7,   249,     7,   254,     7,   305,     7,   418,     7,   502,
       7,   518,     7,   453,     7,   459,     7,   483,     7,   394,
       7,   585,     7,   616,   241,   236,   250,   255,   306,   419,
     503,   519,   454,   460,   484,   395,   586,   617,   233,   242,
     243,   214,   238,   239,    10,   251,   253,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    93,    94,   105,   106,   107,
     110,   111,   115,   120,   121,   122,   123,   124,   130,   140,
     143,   150,   151,   155,   158,   162,   182,   183,   184,   185,
     186,   187,   196,   214,   248,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   271,
     272,   274,   275,   276,   277,   278,   279,   280,   283,   285,
     287,   288,   289,   290,   292,   294,   295,   296,   297,   298,
     299,   300,   301,   319,   321,   329,   331,   372,   381,   388,
     402,   412,   436,   437,   438,   439,   443,   451,   477,   508,
     510,   512,   523,   525,   527,   550,   564,   565,   573,   583,
     614,   623,   647,    15,    16,    19,    22,    23,    24,    25,
     248,   303,   304,   307,   309,   312,   315,   316,   317,   318,
     508,   510,    90,    91,    92,   108,   112,   113,   114,   125,
     129,   137,   248,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   272,   275,   276,   277,   278,   279,   280,
     283,   285,   287,   288,   289,   290,   292,   294,   300,   420,
     421,   422,   424,   426,   428,   430,   432,   434,   436,   437,
     438,   439,   442,   477,   496,   508,   510,   512,   523,   525,
     527,   547,   109,   248,   432,   434,   477,   504,   505,   506,
     508,   510,   124,   131,   132,   133,   134,   135,   136,   138,
     248,   477,   508,   510,   520,   521,   522,   523,   525,   527,
     529,   533,   535,   537,   539,   541,   543,   545,   451,    39,
      95,    97,    98,   102,   103,   104,   248,   349,   461,   462,
     463,   464,   465,   466,   467,   469,   471,   473,   474,   476,
     508,   510,    96,    99,   100,   101,   248,   349,   465,   471,
     485,   486,   487,   488,   489,   491,   492,   493,   494,   495,
     508,   510,   141,   142,   248,   396,   397,   398,   400,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   182,   183,   248,   508,   510,   587,   588,   589,
     590,   592,   593,   595,   596,   597,   600,   602,   604,   605,
     606,   608,   610,   612,    12,    13,   618,   619,   620,   622,
       6,     3,     4,     8,     3,   252,     3,     8,   615,   302,
     322,     4,     4,     4,   524,   526,   528,     4,   320,   330,
     332,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   270,     4,     4,     4,     4,     4,   281,   284,
     286,     4,     4,     4,     4,   413,   452,   478,     4,   273,
     444,   509,   511,   440,     4,     4,     4,   373,   551,   513,
     389,   403,     4,   382,   566,   574,   584,   291,   293,     4,
       4,     4,   624,   648,     4,     3,     8,   308,   310,   313,
       4,     4,     4,     4,     3,     8,   425,   427,   429,   497,
     423,   431,     4,   435,   433,   548,     3,     8,   507,     3,
       8,   546,   534,   536,   540,   538,   544,   542,   530,     8,
       3,     8,   468,   350,     4,   472,   470,   475,     4,     8,
       3,   490,     4,     4,     4,     8,     3,   399,   401,     3,
       8,     4,   603,   591,     4,   594,     4,     4,   598,   601,
       4,     4,   607,   609,   611,   613,     3,     8,   621,     4,
       3,     8,   233,   233,   214,     4,     4,     4,     4,   217,
     217,   217,     4,     4,     4,   215,     4,     4,     4,   215,
     215,   215,   215,   215,   217,   216,   216,   216,   215,   215,
       4,   215,   215,   217,   217,   217,     4,     4,     4,   217,
     217,   216,   217,     4,     4,     4,   215,     4,     4,     4,
       4,     4,   217,   217,   217,     4,     4,     4,     4,     4,
     215,     4,     4,     4,     4,     4,     4,   217,   217,   217,
       4,     4,   257,     4,     4,     4,   217,   217,   215,   215,
     304,     4,     4,     4,     4,     4,     4,   215,     4,     4,
       4,   421,     4,   505,     4,     4,     4,     4,     4,     4,
       4,     4,   522,     4,     4,   215,     4,     4,     4,   217,
     463,     4,   217,   217,   217,   487,     4,     4,   397,   217,
       4,     4,   215,     4,   215,   215,     4,     4,   217,   217,
       4,     4,     4,     4,   588,     4,   215,   619,     4,     7,
       7,     7,     7,   214,   214,   214,     7,     7,     5,   214,
     178,   179,   180,   181,   217,   282,   214,   214,     5,     5,
       5,   214,     5,   235,   237,   214,   116,   117,   118,   119,
     441,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     214,   214,     5,     7,     5,   244,    17,    18,   311,    20,
      21,   314,   214,   214,   214,     5,   214,   214,   244,   214,
       7,   214,   244,   214,   214,   214,   214,   214,   214,   214,
     214,   214,   214,   214,   214,   214,   214,   237,   214,   214,
     214,    18,   176,   599,   177,   282,   214,   214,   214,     5,
     233,   256,   618,   303,    27,    28,   323,   324,   325,   327,
      39,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    60,    61,    62,    63,    64,
     248,   337,   338,   339,   342,   344,   346,   348,   349,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   363,
     364,   366,   368,   370,   337,     7,   333,   334,   335,     7,
     414,   415,   416,     7,   455,   456,   457,     7,   479,   480,
     481,     7,   445,   446,   447,   131,   132,   133,   134,   136,
     374,   375,   376,   377,   378,   379,   380,     7,   552,   553,
       7,   514,   515,   516,     7,   390,   391,   392,   144,   145,
     146,   147,   148,   149,   404,   405,   406,   407,   408,   409,
     410,   411,   152,   153,   154,   248,   383,   384,   385,   386,
     387,   508,   510,   156,   157,   248,   508,   510,   567,   568,
     569,   571,   159,   160,   161,   214,   508,   510,   575,   576,
     577,   578,   580,   581,   587,     7,   625,   626,   197,   198,
     199,   200,   248,   649,   650,   651,   652,   653,   654,   245,
       7,   498,   499,   500,   139,   529,   531,   549,   333,     8,
       8,     8,   326,   328,     3,     8,   340,   343,   345,   347,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     361,     4,   365,   367,   369,   371,     3,     8,     8,   336,
       6,     3,   417,     6,     3,   458,     6,     3,   482,     6,
       3,   448,     6,     3,     3,     6,   554,     3,     6,   517,
       6,     3,   393,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,     4,     4,     4,     3,     8,   570,   572,
       3,     8,     4,   579,     4,   582,     3,     8,     8,   627,
       3,     6,     4,     4,     4,     4,     3,     8,   214,   246,
     247,   501,     6,     3,   532,     8,     6,     4,     4,   324,
       4,     4,     4,     4,   215,   217,   215,   217,   215,   215,
     215,   215,   215,   215,     4,   215,     4,     4,     4,     4,
     338,   337,   335,   420,   416,   461,   457,   485,   481,   248,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     272,   275,   276,   277,   278,   279,   280,   283,   285,   287,
     288,   289,   290,   292,   294,   300,   349,   412,   430,   432,
     434,   436,   437,   438,   439,   449,   450,   477,   508,   510,
     523,   525,   527,   547,   447,   375,   126,   127,   128,   248,
     258,   259,   260,   300,   349,   451,   477,   508,   510,   523,
     525,   527,   555,   556,   557,   558,   559,   561,   563,   553,
     520,   516,   396,   392,   215,   215,   215,   215,   215,   215,
     405,   217,   215,   215,   384,     4,     4,   568,   217,     4,
     215,     4,   576,   188,   190,   191,   248,   349,   508,   510,
     628,   629,   630,   631,   633,   626,   217,   217,   217,   217,
     650,     6,     3,   504,   500,     4,   214,   214,    40,    41,
      42,   341,   214,   214,   214,    57,    58,    59,   362,   214,
     214,   214,   214,     8,     8,     8,     8,     3,     8,   560,
     562,     4,     8,     3,     8,     8,   214,   214,   214,   233,
     634,     4,   632,     3,     8,   214,     8,   244,   450,     4,
       4,   217,   557,     4,   215,     4,   629,   214,   214,     5,
     214,     7,   635,   636,   637,     3,     6,   189,   192,   193,
     194,   195,   638,   639,   640,   642,   643,   644,   645,   636,
     641,     4,     4,     4,   646,     3,     8,     4,   217,   215,
     215,     4,   639,   214,   214
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   218,   220,   219,   221,   219,   222,   219,   223,   219,
     224,   219,   225,   219,   226,   219,   227,   219,   228,   219,
     229,   219,   230,   219,   231,   219,   232,   219,   233,   233,
     233,   233,   233,   233,   233,   234,   236,   235,   237,   238,
     238,   239,   239,   239,   241,   240,   242,   242,   243,   243,
     243,   245,   244,   246,   246,   247,   247,   247,   248,   250,
     249,   252,   251,   251,   253,   255,   254,   256,   256,   256,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     257,   257,   257,   257,   257,   257,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   270,   269,
     271,   273,   272,   274,   275,   276,   277,   278,   279,   281,
     280,   282,   282,   282,   282,   282,   284,   283,   286,   285,
     287,   288,   289,   291,   290,   293,   292,   294,   295,   296,
     297,   298,   299,   300,   302,   301,   303,   303,   303,   304,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   306,
     305,   308,   307,   310,   309,   311,   311,   313,   312,   314,
     314,   315,   316,   317,   318,   320,   319,   322,   321,   323,
     323,   323,   324,   324,   326,   325,   328,   327,   330,   329,
     332,   331,   333,   333,   334,   334,   334,   336,   335,   337,
     337,   337,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   338,   338,   338,   338,   338,   338,
     338,   338,   338,   338,   340,   339,   341,   341,   341,   343,
     342,   345,   344,   347,   346,   348,   350,   349,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   361,   360,   362,
     362,   362,   363,   365,   364,   367,   366,   369,   368,   371,
     370,   373,   372,   374,   374,   374,   375,   375,   375,   375,
     375,   376,   377,   378,   379,   380,   382,   381,   383,   383,
     383,   384,   384,   384,   384,   384,   384,   385,   386,   387,
     389,   388,   390,   390,   391,   391,   391,   393,   392,   395,
     394,   396,   396,   396,   396,   397,   397,   399,   398,   401,
     400,   403,   402,   404,   404,   404,   405,   405,   405,   405,
     405,   405,   406,   407,   408,   409,   410,   411,   413,   412,
     414,   414,   415,   415,   415,   417,   416,   419,   418,   420,
     420,   420,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     423,   422,   425,   424,   427,   426,   429,   428,   431,   430,
     433,   432,   435,   434,   436,   437,   438,   440,   439,   441,
     441,   441,   441,   442,   444,   443,   445,   445,   446,   446,
     446,   448,   447,   449,   449,   449,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   452,
     451,   454,   453,   455,   455,   456,   456,   456,   458,   457,
     460,   459,   461,   461,   462,   462,   462,   463,   463,   463,
     463,   463,   463,   463,   463,   463,   463,   464,   465,   466,
     468,   467,   470,   469,   472,   471,   473,   475,   474,   476,
     478,   477,   479,   479,   480,   480,   480,   482,   481,   484,
     483,   485,   485,   486,   486,   486,   487,   487,   487,   487,
     487,   487,   487,   487,   487,   487,   488,   490,   489,   491,
     492,   493,   494,   495,   497,   496,   498,   498,   499,   499,
     499,   501,   500,   503,   502,   504,   504,   504,   505,   505,
     505,   505,   505,   505,   505,   507,   506,   509,   508,   511,
     510,   513,   512,   514,   514,   515,   515,   515,   517,   516,
     519,   518,   520,   520,   521,   521,   521,   522,   522,   522,
     522,   522,   522,   522,   522,   522,   522,   522,   522,   522,
     522,   522,   524,   523,   526,   525,   528,   527,   530,   529,
     532,   531,   534,   533,   536,   535,   538,   537,   540,   539,
     542,   541,   544,   543,   546,   545,   548,   547,   549,   549,
     551,   550,   552,   552,   552,   554,   553,   555,   555,   556,
     556,   556,   557,   557,   557,   557,   557,   557,   557,   557,
     557,   557,   557,   557,   557,   557,   557,   557,   558,   560,
     559,   562,   561,   563,   564,   566,   565,   567,   567,   567,
     568,   568,   568,   568,   568,   570,   569,   572,   571,   574,
     573,   575,   575,   575,   576,   576,   576,   576,   576,   576,
     577,   579,   578,   580,   582,   581,   584,   583,   586,   585,
     587,   587,   587,   588,   588,   588,   588,   588,   588,   588,
     588,   588,   588,   588,   588,   588,   588,   588,   588,   588,
     588,   589,   591,   590,   592,   594,   593,   595,   596,   598,
     597,   599,   599,   601,   600,   603,   602,   604,   605,   607,
     606,   609,   608,   611,   610,   613,   612,   615,   614,   617,
     616,   618,   618,   618,   619,   619,   621,   620,   622,   624,
     623,   625,   625,   625,   627,   626,   628,   628,   628,   629,
     629,   629,   629,   629,   629,   629,   630,   632,   631,   634,
     633,   635,   635,   635,   637,   636,   638,   638,   638,   639,
     639,   639,   639,   639,   641,   640,   642,   643,   644,   646,
     645,   648,   647,   649,   649,   649,   650,   650,   650,   650,
     650,   651,   652,   653,   654
  };

  const signed char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     2,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     0,     1,     1,     3,     2,     2,     0,
       4,     0,     6,     1,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       3,     3,     3,     0,     4,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     1,     1,     0,     4,     1,
       1,     3,     3,     3,     3,     0,     6,     0,     6,     1,
       3,     2,     1,     1,     0,     4,     0,     4,     0,     6,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     1,
       1,     1,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     1,
       0,     6,     1,     3,     2,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     0,     6,     3,     0,
       6,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     2,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     3,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     3,     3,     3,     3
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
  "\"service-sockets-require-all\"", "\"service-sockets-retry-wait-time\"",
  "\"service-sockets-max-retries\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"extended-info-checks\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"authoritative\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"offer-lifetime\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"user\"",
  "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"read-timeout\"", "\"write-timeout\"", "\"tcp-user-timeout\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"max-row-errors\"", "\"trust-anchor\"",
  "\"cert-file\"", "\"key-file\"", "\"cipher-list\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"cache-threshold\"", "\"cache-max-age\"",
  "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"ddns-ttl-percent\"", "\"store-extended-info\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"never-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"parked-packet-limit\"", "\"allocator\"", "\"shared-networks\"",
  "\"pools\"", "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"id\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"reservations-global\"",
  "\"reservations-in-subnet\"", "\"reservations-out-of-pool\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"template-test\"",
  "\"only-if-required\"", "\"client-class\"", "\"reservations\"",
  "\"duid\"", "\"hw-address\"", "\"circuit-id\"", "\"client-id\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"ip-addresses\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
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
  "\"early-global-reservations-lookup\"", "\"ip-reservations-unique\"",
  "\"reservations-lookup-first\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"compatibility\"",
  "\"lenient-option-parsing\"", "\"ignore-dhcp-server-identifier\"",
  "\"ignore-rai-link-selection\"", "\"exclude-first-last-24\"",
  "TOPLEVEL_JSON", "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4",
  "SUB_SUBNET4", "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_CONFIG_CONTROL", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "value", "sub_json", "map2", "$@14", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_object", "$@18", "global_object_comma", "sub_dhcp4", "$@19",
  "global_params", "global_param", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "server_tag", "$@20",
  "parked_packet_limit", "allocator", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "ddns_ttl_percent", "hostname_char_set", "$@25",
  "hostname_char_replacement", "$@26", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "early_global_reservations_lookup", "ip_reservations_unique",
  "reservations_lookup_first", "offer_lifetime", "interfaces_config",
  "$@27", "interfaces_config_params", "interfaces_config_param",
  "sub_interfaces4", "$@28", "interfaces_list", "$@29", "dhcp_socket_type",
  "$@30", "socket_type", "outbound_interface", "$@31",
  "outbound_interface_value", "re_detect", "service_sockets_require_all",
  "service_sockets_retry_wait_time", "service_sockets_max_retries",
  "lease_database", "$@32", "sanity_checks", "$@33",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@34",
  "extended_info_checks", "$@35", "hosts_database", "$@36",
  "hosts_databases", "$@37", "database_list", "not_empty_database_list",
  "database", "$@38", "database_map_params", "database_map_param",
  "database_type", "$@39", "db_type", "user", "$@40", "password", "$@41",
  "host", "$@42", "port", "name", "$@43", "persist", "lfc_interval",
  "readonly", "connect_timeout", "read_timeout", "write_timeout",
  "tcp_user_timeout", "max_reconnect_tries", "reconnect_wait_time",
  "on_fail", "$@44", "on_fail_mode", "max_row_errors", "trust_anchor",
  "$@45", "cert_file", "$@46", "key_file", "$@47", "cipher_list", "$@48",
  "host_reservation_identifiers", "$@49",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@50", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@51", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@52",
  "sub_hooks_library", "$@53", "hooks_params", "hooks_param", "library",
  "$@54", "parameters", "$@55", "expired_leases_processing", "$@56",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@57",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@58",
  "sub_subnet4", "$@59", "subnet4_params", "subnet4_param", "subnet",
  "$@60", "subnet_4o6_interface", "$@61", "subnet_4o6_interface_id",
  "$@62", "subnet_4o6_subnet", "$@63", "interface", "$@64", "client_class",
  "$@65", "require_client_classes", "$@66", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@67", "hr_mode", "id", "shared_networks", "$@68",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@69", "shared_network_params", "shared_network_param",
  "option_def_list", "$@70", "sub_option_def_list", "$@71",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@72", "sub_option_def", "$@73",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@74",
  "option_def_record_types", "$@75", "space", "$@76", "option_def_space",
  "option_def_encapsulate", "$@77", "option_def_array", "option_data_list",
  "$@78", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@79", "sub_option_data", "$@80",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@81",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "option_data_never_send", "pools_list",
  "$@82", "pools_list_content", "not_empty_pools_list", "pool_list_entry",
  "$@83", "sub_pool4", "$@84", "pool_params", "pool_param", "pool_entry",
  "$@85", "user_context", "$@86", "comment", "$@87", "reservations",
  "$@88", "reservations_list", "not_empty_reservations_list",
  "reservation", "$@89", "sub_reservation", "$@90", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "next_server",
  "$@91", "server_hostname", "$@92", "boot_file_name", "$@93",
  "ip_address", "$@94", "ip_addresses", "$@95", "duid", "$@96",
  "hw_address", "$@97", "client_id_value", "$@98", "circuit_id_value",
  "$@99", "flex_id_value", "$@100", "hostname", "$@101",
  "reservation_client_classes", "$@102", "relay", "$@103", "relay_map",
  "client_classes", "$@104", "client_classes_list", "client_class_entry",
  "$@105", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@106",
  "client_class_template_test", "$@107", "only_if_required",
  "dhcp4o6_port", "control_socket", "$@108", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@109",
  "control_socket_name", "$@110", "dhcp_queue_control", "$@111",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@112", "capacity", "arbitrary_map_entry", "$@113",
  "dhcp_ddns", "$@114", "sub_dhcp_ddns", "$@115", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@116", "server_port",
  "sender_ip", "$@117", "sender_port", "max_queue_size", "ncr_protocol",
  "$@118", "ncr_protocol_value", "ncr_format", "$@119",
  "dep_qualifying_suffix", "$@120", "dep_override_no_update",
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
  "maxsize", "maxver", "pattern", "$@134", "compatibility", "$@135",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   307,   307,   307,   308,   308,   309,   309,   310,   310,
     311,   311,   312,   312,   313,   313,   314,   314,   315,   315,
     316,   316,   317,   317,   318,   318,   319,   319,   327,   328,
     329,   330,   331,   332,   333,   336,   341,   341,   352,   355,
     356,   359,   364,   370,   375,   375,   382,   383,   386,   390,
     394,   400,   400,   407,   408,   411,   415,   419,   429,   438,
     438,   453,   453,   467,   470,   476,   476,   485,   486,   487,
     494,   495,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   563,   569,   575,
     581,   587,   593,   599,   605,   611,   617,   623,   629,   629,
     638,   644,   644,   653,   659,   665,   671,   677,   683,   689,
     689,   698,   701,   704,   707,   710,   716,   716,   725,   725,
     734,   740,   746,   752,   752,   761,   761,   770,   776,   782,
     788,   794,   800,   806,   812,   812,   824,   825,   826,   831,
     832,   833,   834,   835,   836,   837,   838,   839,   840,   843,
     843,   852,   852,   863,   863,   871,   872,   875,   875,   883,
     885,   889,   895,   901,   907,   913,   913,   926,   926,   937,
     938,   939,   944,   945,   948,   948,   967,   967,   985,   985,
     998,   998,  1009,  1010,  1013,  1014,  1015,  1020,  1020,  1030,
    1031,  1032,  1037,  1038,  1039,  1040,  1041,  1042,  1043,  1044,
    1045,  1046,  1047,  1048,  1049,  1050,  1051,  1052,  1053,  1054,
    1055,  1056,  1057,  1058,  1061,  1061,  1069,  1070,  1071,  1074,
    1074,  1083,  1083,  1092,  1092,  1101,  1107,  1107,  1116,  1122,
    1128,  1134,  1140,  1146,  1152,  1158,  1164,  1170,  1170,  1178,
    1179,  1180,  1183,  1189,  1189,  1198,  1198,  1207,  1207,  1216,
    1216,  1225,  1225,  1236,  1237,  1238,  1243,  1244,  1245,  1246,
    1247,  1250,  1255,  1260,  1265,  1270,  1277,  1277,  1290,  1291,
    1292,  1297,  1298,  1299,  1300,  1301,  1302,  1305,  1311,  1317,
    1323,  1323,  1334,  1335,  1338,  1339,  1340,  1345,  1345,  1355,
    1355,  1365,  1366,  1367,  1370,  1373,  1374,  1377,  1377,  1386,
    1386,  1395,  1395,  1407,  1408,  1409,  1414,  1415,  1416,  1417,
    1418,  1419,  1422,  1428,  1434,  1440,  1446,  1452,  1461,  1461,
    1475,  1476,  1479,  1480,  1481,  1490,  1490,  1516,  1516,  1527,
    1528,  1529,  1535,  1536,  1537,  1538,  1539,  1540,  1541,  1542,
    1543,  1544,  1545,  1546,  1547,  1548,  1549,  1550,  1551,  1552,
    1553,  1554,  1555,  1556,  1557,  1558,  1559,  1560,  1561,  1562,
    1563,  1564,  1565,  1566,  1567,  1568,  1569,  1570,  1571,  1572,
    1573,  1574,  1575,  1576,  1577,  1578,  1579,  1580,  1581,  1582,
    1585,  1585,  1594,  1594,  1603,  1603,  1612,  1612,  1621,  1621,
    1630,  1630,  1639,  1639,  1650,  1656,  1662,  1668,  1668,  1676,
    1677,  1678,  1679,  1682,  1690,  1690,  1702,  1703,  1707,  1708,
    1709,  1714,  1714,  1722,  1723,  1724,  1729,  1730,  1731,  1732,
    1733,  1734,  1735,  1736,  1737,  1738,  1739,  1740,  1741,  1742,
    1743,  1744,  1745,  1746,  1747,  1748,  1749,  1750,  1751,  1752,
    1753,  1754,  1755,  1756,  1757,  1758,  1759,  1760,  1761,  1762,
    1763,  1764,  1765,  1766,  1767,  1768,  1769,  1770,  1771,  1778,
    1778,  1792,  1792,  1801,  1802,  1805,  1806,  1807,  1814,  1814,
    1829,  1829,  1843,  1844,  1847,  1848,  1849,  1854,  1855,  1856,
    1857,  1858,  1859,  1860,  1861,  1862,  1863,  1866,  1868,  1874,
    1876,  1876,  1885,  1885,  1894,  1894,  1903,  1905,  1905,  1914,
    1924,  1924,  1937,  1938,  1943,  1944,  1945,  1952,  1952,  1964,
    1964,  1976,  1977,  1982,  1983,  1984,  1991,  1992,  1993,  1994,
    1995,  1996,  1997,  1998,  1999,  2000,  2003,  2005,  2005,  2014,
    2016,  2018,  2024,  2030,  2039,  2039,  2052,  2053,  2056,  2057,
    2058,  2063,  2063,  2073,  2073,  2083,  2084,  2085,  2090,  2091,
    2092,  2093,  2094,  2095,  2096,  2099,  2099,  2108,  2108,  2133,
    2133,  2163,  2163,  2174,  2175,  2178,  2179,  2180,  2185,  2185,
    2194,  2194,  2203,  2204,  2207,  2208,  2209,  2215,  2216,  2217,
    2218,  2219,  2220,  2221,  2222,  2223,  2224,  2225,  2226,  2227,
    2228,  2229,  2232,  2232,  2241,  2241,  2250,  2250,  2259,  2259,
    2268,  2268,  2279,  2279,  2288,  2288,  2297,  2297,  2306,  2306,
    2315,  2315,  2324,  2324,  2333,  2333,  2347,  2347,  2358,  2359,
    2365,  2365,  2376,  2377,  2378,  2383,  2383,  2393,  2394,  2397,
    2398,  2399,  2404,  2405,  2406,  2407,  2408,  2409,  2410,  2411,
    2412,  2413,  2414,  2415,  2416,  2417,  2418,  2419,  2422,  2424,
    2424,  2433,  2433,  2442,  2450,  2458,  2458,  2469,  2470,  2471,
    2476,  2477,  2478,  2479,  2480,  2483,  2483,  2492,  2492,  2504,
    2504,  2517,  2518,  2519,  2524,  2525,  2526,  2527,  2528,  2529,
    2532,  2538,  2538,  2547,  2553,  2553,  2563,  2563,  2576,  2576,
    2586,  2587,  2588,  2593,  2594,  2595,  2596,  2597,  2598,  2599,
    2600,  2601,  2602,  2603,  2604,  2605,  2606,  2607,  2608,  2609,
    2610,  2613,  2619,  2619,  2628,  2634,  2634,  2643,  2649,  2655,
    2655,  2664,  2665,  2668,  2668,  2678,  2678,  2688,  2695,  2702,
    2702,  2711,  2711,  2721,  2721,  2731,  2731,  2743,  2743,  2755,
    2755,  2765,  2766,  2767,  2773,  2774,  2777,  2777,  2788,  2796,
    2796,  2809,  2810,  2811,  2817,  2817,  2825,  2826,  2827,  2832,
    2833,  2834,  2835,  2836,  2837,  2838,  2841,  2847,  2847,  2856,
    2856,  2867,  2868,  2869,  2874,  2874,  2882,  2883,  2884,  2889,
    2890,  2891,  2892,  2893,  2896,  2896,  2905,  2911,  2917,  2923,
    2923,  2932,  2932,  2943,  2944,  2945,  2950,  2951,  2952,  2953,
    2954,  2957,  2963,  2969,  2975
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
#line 6349 "dhcp4_parser.cc"

#line 2981 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
