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
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 285 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 285 "dhcp4_parser.yy"
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
#line 294 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 295 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 296 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 297 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 298 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 299 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 300 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 301 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 302 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 303 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 304 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 305 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 306 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 314 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 315 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 316 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 317 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 318 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 319 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 320 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 323 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 328 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 333 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 339 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 346 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 351 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 357 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 362 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 365 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 373 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 377 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 381 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 387 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 389 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 398 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 402 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 406 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 416 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 425 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 430 "dhcp4_parser.yy"
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
#line 440 "dhcp4_parser.yy"
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
#line 449 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 457 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 463 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 467 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 474 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 132: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 545 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 133: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 551 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 134: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 557 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 135: // renew_timer: "renew-timer" ":" "integer"
#line 563 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 136: // rebind_timer: "rebind-timer" ":" "integer"
#line 569 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 137: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 575 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 138: // t1_percent: "t1-percent" ":" "floating point"
#line 581 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 139: // t2_percent: "t2-percent" ":" "floating point"
#line 587 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 140: // cache_threshold: "cache-threshold" ":" "floating point"
#line 593 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 141: // cache_max_age: "cache-max-age" ":" "integer"
#line 599 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 142: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 605 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 143: // $@20: %empty
#line 611 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 144: // server_tag: "server-tag" $@20 ":" "constant string"
#line 614 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 145: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 620 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 146: // echo_client_id: "echo-client-id" ":" "boolean"
#line 626 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1270 "dhcp4_parser.cc"
    break;

  case 147: // match_client_id: "match-client-id" ":" "boolean"
#line 632 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1280 "dhcp4_parser.cc"
    break;

  case 148: // authoritative: "authoritative" ":" "boolean"
#line 638 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1290 "dhcp4_parser.cc"
    break;

  case 149: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 644 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1300 "dhcp4_parser.cc"
    break;

  case 150: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 650 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1310 "dhcp4_parser.cc"
    break;

  case 151: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 656 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1320 "dhcp4_parser.cc"
    break;

  case 152: // $@21: %empty
#line 662 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 153: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 665 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1338 "dhcp4_parser.cc"
    break;

  case 154: // ddns_replace_client_name_value: "when-present"
#line 671 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1346 "dhcp4_parser.cc"
    break;

  case 155: // ddns_replace_client_name_value: "never"
#line 674 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1354 "dhcp4_parser.cc"
    break;

  case 156: // ddns_replace_client_name_value: "always"
#line 677 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1362 "dhcp4_parser.cc"
    break;

  case 157: // ddns_replace_client_name_value: "when-not-present"
#line 680 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1370 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "boolean"
#line 683 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1379 "dhcp4_parser.cc"
    break;

  case 159: // $@22: %empty
#line 689 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1388 "dhcp4_parser.cc"
    break;

  case 160: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 692 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1398 "dhcp4_parser.cc"
    break;

  case 161: // $@23: %empty
#line 698 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 162: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 701 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 163: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 707 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1427 "dhcp4_parser.cc"
    break;

  case 164: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 713 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1437 "dhcp4_parser.cc"
    break;

  case 165: // $@24: %empty
#line 719 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 166: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 722 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 167: // $@25: %empty
#line 728 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 168: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 731 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 169: // store_extended_info: "store-extended-info" ":" "boolean"
#line 737 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 170: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 743 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1495 "dhcp4_parser.cc"
    break;

  case 171: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 749 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 172: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 755 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 173: // $@26: %empty
#line 761 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1527 "dhcp4_parser.cc"
    break;

  case 174: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 767 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1537 "dhcp4_parser.cc"
    break;

  case 177: // interfaces_config_params: interfaces_config_params ","
#line 775 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1545 "dhcp4_parser.cc"
    break;

  case 185: // $@27: %empty
#line 789 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 186: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 793 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 187: // $@28: %empty
#line 798 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 188: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 804 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1585 "dhcp4_parser.cc"
    break;

  case 189: // $@29: %empty
#line 809 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 190: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 812 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1603 "dhcp4_parser.cc"
    break;

  case 191: // socket_type: "raw"
#line 817 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1609 "dhcp4_parser.cc"
    break;

  case 192: // socket_type: "udp"
#line 818 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1615 "dhcp4_parser.cc"
    break;

  case 193: // $@30: %empty
#line 821 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 194: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 824 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1633 "dhcp4_parser.cc"
    break;

  case 195: // outbound_interface_value: "same-as-inbound"
#line 829 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1641 "dhcp4_parser.cc"
    break;

  case 196: // outbound_interface_value: "use-routing"
#line 831 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1649 "dhcp4_parser.cc"
    break;

  case 197: // re_detect: "re-detect" ":" "boolean"
#line 835 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1659 "dhcp4_parser.cc"
    break;

  case 198: // $@31: %empty
#line 842 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1671 "dhcp4_parser.cc"
    break;

  case 199: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 848 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1682 "dhcp4_parser.cc"
    break;

  case 200: // $@32: %empty
#line 855 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1694 "dhcp4_parser.cc"
    break;

  case 201: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 861 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1703 "dhcp4_parser.cc"
    break;

  case 204: // sanity_checks_params: sanity_checks_params ","
#line 868 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1711 "dhcp4_parser.cc"
    break;

  case 206: // $@33: %empty
#line 875 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1720 "dhcp4_parser.cc"
    break;

  case 207: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 878 "dhcp4_parser.yy"
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
#line 1740 "dhcp4_parser.cc"
    break;

  case 208: // $@34: %empty
#line 894 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1752 "dhcp4_parser.cc"
    break;

  case 209: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 900 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 210: // $@35: %empty
#line 907 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1775 "dhcp4_parser.cc"
    break;

  case 211: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 913 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1784 "dhcp4_parser.cc"
    break;

  case 216: // not_empty_database_list: not_empty_database_list ","
#line 924 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1792 "dhcp4_parser.cc"
    break;

  case 217: // $@36: %empty
#line 929 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1802 "dhcp4_parser.cc"
    break;

  case 218: // database: "{" $@36 database_map_params "}"
#line 933 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1812 "dhcp4_parser.cc"
    break;

  case 221: // database_map_params: database_map_params ","
#line 941 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1820 "dhcp4_parser.cc"
    break;

  case 244: // $@37: %empty
#line 970 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1829 "dhcp4_parser.cc"
    break;

  case 245: // database_type: "type" $@37 ":" db_type
#line 973 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1838 "dhcp4_parser.cc"
    break;

  case 246: // db_type: "memfile"
#line 978 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1844 "dhcp4_parser.cc"
    break;

  case 247: // db_type: "mysql"
#line 979 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1850 "dhcp4_parser.cc"
    break;

  case 248: // db_type: "postgresql"
#line 980 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1856 "dhcp4_parser.cc"
    break;

  case 249: // db_type: "cql"
#line 981 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1862 "dhcp4_parser.cc"
    break;

  case 250: // $@38: %empty
#line 984 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1871 "dhcp4_parser.cc"
    break;

  case 251: // user: "user" $@38 ":" "constant string"
#line 987 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 252: // $@39: %empty
#line 993 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1890 "dhcp4_parser.cc"
    break;

  case 253: // password: "password" $@39 ":" "constant string"
#line 996 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1900 "dhcp4_parser.cc"
    break;

  case 254: // $@40: %empty
#line 1002 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1909 "dhcp4_parser.cc"
    break;

  case 255: // host: "host" $@40 ":" "constant string"
#line 1005 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1919 "dhcp4_parser.cc"
    break;

  case 256: // port: "port" ":" "integer"
#line 1011 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1929 "dhcp4_parser.cc"
    break;

  case 257: // $@41: %empty
#line 1017 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1938 "dhcp4_parser.cc"
    break;

  case 258: // name: "name" $@41 ":" "constant string"
#line 1020 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1948 "dhcp4_parser.cc"
    break;

  case 259: // persist: "persist" ":" "boolean"
#line 1026 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1958 "dhcp4_parser.cc"
    break;

  case 260: // lfc_interval: "lfc-interval" ":" "integer"
#line 1032 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1968 "dhcp4_parser.cc"
    break;

  case 261: // readonly: "readonly" ":" "boolean"
#line 1038 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1978 "dhcp4_parser.cc"
    break;

  case 262: // connect_timeout: "connect-timeout" ":" "integer"
#line 1044 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1988 "dhcp4_parser.cc"
    break;

  case 263: // request_timeout: "request-timeout" ":" "integer"
#line 1050 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1998 "dhcp4_parser.cc"
    break;

  case 264: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1056 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 2008 "dhcp4_parser.cc"
    break;

  case 265: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1062 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 2018 "dhcp4_parser.cc"
    break;

  case 266: // $@42: %empty
#line 1068 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp4_parser.cc"
    break;

  case 267: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1071 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 2037 "dhcp4_parser.cc"
    break;

  case 268: // $@43: %empty
#line 1077 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2046 "dhcp4_parser.cc"
    break;

  case 269: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1080 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 2056 "dhcp4_parser.cc"
    break;

  case 270: // $@44: %empty
#line 1086 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2065 "dhcp4_parser.cc"
    break;

  case 271: // consistency: "consistency" $@44 ":" "constant string"
#line 1089 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 2075 "dhcp4_parser.cc"
    break;

  case 272: // $@45: %empty
#line 1095 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2084 "dhcp4_parser.cc"
    break;

  case 273: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1098 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2094 "dhcp4_parser.cc"
    break;

  case 274: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1104 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2104 "dhcp4_parser.cc"
    break;

  case 275: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1110 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2114 "dhcp4_parser.cc"
    break;

  case 276: // $@46: %empty
#line 1116 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2123 "dhcp4_parser.cc"
    break;

  case 277: // on_fail: "on-fail" $@46 ":" on_fail_mode
#line 1119 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2132 "dhcp4_parser.cc"
    break;

  case 278: // on_fail_mode: "stop-retry-exit"
#line 1124 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2138 "dhcp4_parser.cc"
    break;

  case 279: // on_fail_mode: "serve-retry-exit"
#line 1125 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2144 "dhcp4_parser.cc"
    break;

  case 280: // on_fail_mode: "serve-retry-continue"
#line 1126 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2150 "dhcp4_parser.cc"
    break;

  case 281: // max_row_errors: "max-row-errors" ":" "integer"
#line 1129 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2160 "dhcp4_parser.cc"
    break;

  case 282: // $@47: %empty
#line 1136 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2172 "dhcp4_parser.cc"
    break;

  case 283: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1142 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2181 "dhcp4_parser.cc"
    break;

  case 286: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1149 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2189 "dhcp4_parser.cc"
    break;

  case 292: // duid_id: "duid"
#line 1161 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2198 "dhcp4_parser.cc"
    break;

  case 293: // hw_address_id: "hw-address"
#line 1166 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2207 "dhcp4_parser.cc"
    break;

  case 294: // circuit_id: "circuit-id"
#line 1171 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2216 "dhcp4_parser.cc"
    break;

  case 295: // client_id: "client-id"
#line 1176 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2225 "dhcp4_parser.cc"
    break;

  case 296: // flex_id: "flex-id"
#line 1181 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2234 "dhcp4_parser.cc"
    break;

  case 297: // $@48: %empty
#line 1188 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2246 "dhcp4_parser.cc"
    break;

  case 298: // dhcp_multi_threading: "multi-threading" $@48 ":" "{" multi_threading_params "}"
#line 1194 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2257 "dhcp4_parser.cc"
    break;

  case 301: // multi_threading_params: multi_threading_params ","
#line 1203 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2265 "dhcp4_parser.cc"
    break;

  case 308: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1216 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2275 "dhcp4_parser.cc"
    break;

  case 309: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1222 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2285 "dhcp4_parser.cc"
    break;

  case 310: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1228 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2295 "dhcp4_parser.cc"
    break;

  case 311: // $@49: %empty
#line 1234 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 312: // hooks_libraries: "hooks-libraries" $@49 ":" "[" hooks_libraries_list "]"
#line 1240 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2316 "dhcp4_parser.cc"
    break;

  case 317: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1251 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2324 "dhcp4_parser.cc"
    break;

  case 318: // $@50: %empty
#line 1256 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2334 "dhcp4_parser.cc"
    break;

  case 319: // hooks_library: "{" $@50 hooks_params "}"
#line 1260 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2344 "dhcp4_parser.cc"
    break;

  case 320: // $@51: %empty
#line 1266 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2354 "dhcp4_parser.cc"
    break;

  case 321: // sub_hooks_library: "{" $@51 hooks_params "}"
#line 1270 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2364 "dhcp4_parser.cc"
    break;

  case 324: // hooks_params: hooks_params ","
#line 1278 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2372 "dhcp4_parser.cc"
    break;

  case 328: // $@52: %empty
#line 1288 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2381 "dhcp4_parser.cc"
    break;

  case 329: // library: "library" $@52 ":" "constant string"
#line 1291 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2391 "dhcp4_parser.cc"
    break;

  case 330: // $@53: %empty
#line 1297 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2400 "dhcp4_parser.cc"
    break;

  case 331: // parameters: "parameters" $@53 ":" map_value
#line 1300 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2409 "dhcp4_parser.cc"
    break;

  case 332: // $@54: %empty
#line 1306 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2421 "dhcp4_parser.cc"
    break;

  case 333: // expired_leases_processing: "expired-leases-processing" $@54 ":" "{" expired_leases_params "}"
#line 1312 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2431 "dhcp4_parser.cc"
    break;

  case 336: // expired_leases_params: expired_leases_params ","
#line 1320 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2439 "dhcp4_parser.cc"
    break;

  case 343: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1333 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2449 "dhcp4_parser.cc"
    break;

  case 344: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1339 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2459 "dhcp4_parser.cc"
    break;

  case 345: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1345 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2469 "dhcp4_parser.cc"
    break;

  case 346: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1351 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2479 "dhcp4_parser.cc"
    break;

  case 347: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1357 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2489 "dhcp4_parser.cc"
    break;

  case 348: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1363 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2499 "dhcp4_parser.cc"
    break;

  case 349: // $@55: %empty
#line 1372 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2511 "dhcp4_parser.cc"
    break;

  case 350: // subnet4_list: "subnet4" $@55 ":" "[" subnet4_list_content "]"
#line 1378 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2520 "dhcp4_parser.cc"
    break;

  case 355: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1392 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2528 "dhcp4_parser.cc"
    break;

  case 356: // $@56: %empty
#line 1401 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2538 "dhcp4_parser.cc"
    break;

  case 357: // subnet4: "{" $@56 subnet4_params "}"
#line 1405 "dhcp4_parser.yy"
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
#line 2564 "dhcp4_parser.cc"
    break;

  case 358: // $@57: %empty
#line 1427 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2574 "dhcp4_parser.cc"
    break;

  case 359: // sub_subnet4: "{" $@57 subnet4_params "}"
#line 1431 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2584 "dhcp4_parser.cc"
    break;

  case 362: // subnet4_params: subnet4_params ","
#line 1440 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2592 "dhcp4_parser.cc"
    break;

  case 408: // $@58: %empty
#line 1493 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2601 "dhcp4_parser.cc"
    break;

  case 409: // subnet: "subnet" $@58 ":" "constant string"
#line 1496 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2611 "dhcp4_parser.cc"
    break;

  case 410: // $@59: %empty
#line 1502 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2620 "dhcp4_parser.cc"
    break;

  case 411: // subnet_4o6_interface: "4o6-interface" $@59 ":" "constant string"
#line 1505 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2630 "dhcp4_parser.cc"
    break;

  case 412: // $@60: %empty
#line 1511 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2639 "dhcp4_parser.cc"
    break;

  case 413: // subnet_4o6_interface_id: "4o6-interface-id" $@60 ":" "constant string"
#line 1514 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2649 "dhcp4_parser.cc"
    break;

  case 414: // $@61: %empty
#line 1520 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2658 "dhcp4_parser.cc"
    break;

  case 415: // subnet_4o6_subnet: "4o6-subnet" $@61 ":" "constant string"
#line 1523 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2668 "dhcp4_parser.cc"
    break;

  case 416: // $@62: %empty
#line 1529 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2677 "dhcp4_parser.cc"
    break;

  case 417: // interface: "interface" $@62 ":" "constant string"
#line 1532 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2687 "dhcp4_parser.cc"
    break;

  case 418: // $@63: %empty
#line 1538 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp4_parser.cc"
    break;

  case 419: // client_class: "client-class" $@63 ":" "constant string"
#line 1541 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2706 "dhcp4_parser.cc"
    break;

  case 420: // $@64: %empty
#line 1547 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2718 "dhcp4_parser.cc"
    break;

  case 421: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1553 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2727 "dhcp4_parser.cc"
    break;

  case 422: // reservations_global: "reservations-global" ":" "boolean"
#line 1558 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2737 "dhcp4_parser.cc"
    break;

  case 423: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1564 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2747 "dhcp4_parser.cc"
    break;

  case 424: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1570 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2757 "dhcp4_parser.cc"
    break;

  case 425: // $@65: %empty
#line 1576 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2766 "dhcp4_parser.cc"
    break;

  case 426: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1579 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2775 "dhcp4_parser.cc"
    break;

  case 427: // hr_mode: "disabled"
#line 1584 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2781 "dhcp4_parser.cc"
    break;

  case 428: // hr_mode: "out-of-pool"
#line 1585 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2787 "dhcp4_parser.cc"
    break;

  case 429: // hr_mode: "global"
#line 1586 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2793 "dhcp4_parser.cc"
    break;

  case 430: // hr_mode: "all"
#line 1587 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2799 "dhcp4_parser.cc"
    break;

  case 431: // id: "id" ":" "integer"
#line 1590 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2809 "dhcp4_parser.cc"
    break;

  case 432: // $@66: %empty
#line 1598 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 433: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1604 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2830 "dhcp4_parser.cc"
    break;

  case 438: // shared_networks_list: shared_networks_list ","
#line 1617 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2838 "dhcp4_parser.cc"
    break;

  case 439: // $@67: %empty
#line 1622 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2848 "dhcp4_parser.cc"
    break;

  case 440: // shared_network: "{" $@67 shared_network_params "}"
#line 1626 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2856 "dhcp4_parser.cc"
    break;

  case 443: // shared_network_params: shared_network_params ","
#line 1632 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2864 "dhcp4_parser.cc"
    break;

  case 484: // $@68: %empty
#line 1683 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2876 "dhcp4_parser.cc"
    break;

  case 485: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1689 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2885 "dhcp4_parser.cc"
    break;

  case 486: // $@69: %empty
#line 1697 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2894 "dhcp4_parser.cc"
    break;

  case 487: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1700 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2902 "dhcp4_parser.cc"
    break;

  case 492: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1712 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2910 "dhcp4_parser.cc"
    break;

  case 493: // $@70: %empty
#line 1719 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2920 "dhcp4_parser.cc"
    break;

  case 494: // option_def_entry: "{" $@70 option_def_params "}"
#line 1723 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 495: // $@71: %empty
#line 1734 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 496: // sub_option_def: "{" $@71 option_def_params "}"
#line 1738 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2954 "dhcp4_parser.cc"
    break;

  case 501: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1754 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2962 "dhcp4_parser.cc"
    break;

  case 513: // code: "code" ":" "integer"
#line 1773 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2972 "dhcp4_parser.cc"
    break;

  case 515: // $@72: %empty
#line 1781 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2981 "dhcp4_parser.cc"
    break;

  case 516: // option_def_type: "type" $@72 ":" "constant string"
#line 1784 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2991 "dhcp4_parser.cc"
    break;

  case 517: // $@73: %empty
#line 1790 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3000 "dhcp4_parser.cc"
    break;

  case 518: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1793 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3010 "dhcp4_parser.cc"
    break;

  case 519: // $@74: %empty
#line 1799 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3019 "dhcp4_parser.cc"
    break;

  case 520: // space: "space" $@74 ":" "constant string"
#line 1802 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3029 "dhcp4_parser.cc"
    break;

  case 522: // $@75: %empty
#line 1810 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3038 "dhcp4_parser.cc"
    break;

  case 523: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1813 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3048 "dhcp4_parser.cc"
    break;

  case 524: // option_def_array: "array" ":" "boolean"
#line 1819 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3058 "dhcp4_parser.cc"
    break;

  case 525: // $@76: %empty
#line 1829 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3070 "dhcp4_parser.cc"
    break;

  case 526: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1835 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3079 "dhcp4_parser.cc"
    break;

  case 531: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1850 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3087 "dhcp4_parser.cc"
    break;

  case 532: // $@77: %empty
#line 1857 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3097 "dhcp4_parser.cc"
    break;

  case 533: // option_data_entry: "{" $@77 option_data_params "}"
#line 1861 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3106 "dhcp4_parser.cc"
    break;

  case 534: // $@78: %empty
#line 1869 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3116 "dhcp4_parser.cc"
    break;

  case 535: // sub_option_data: "{" $@78 option_data_params "}"
#line 1873 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3125 "dhcp4_parser.cc"
    break;

  case 540: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1889 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3133 "dhcp4_parser.cc"
    break;

  case 551: // $@79: %empty
#line 1909 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3142 "dhcp4_parser.cc"
    break;

  case 552: // option_data_data: "data" $@79 ":" "constant string"
#line 1912 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3152 "dhcp4_parser.cc"
    break;

  case 555: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1922 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3162 "dhcp4_parser.cc"
    break;

  case 556: // option_data_always_send: "always-send" ":" "boolean"
#line 1928 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3172 "dhcp4_parser.cc"
    break;

  case 557: // $@80: %empty
#line 1937 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3184 "dhcp4_parser.cc"
    break;

  case 558: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1943 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3193 "dhcp4_parser.cc"
    break;

  case 563: // not_empty_pools_list: not_empty_pools_list ","
#line 1956 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3201 "dhcp4_parser.cc"
    break;

  case 564: // $@81: %empty
#line 1961 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3211 "dhcp4_parser.cc"
    break;

  case 565: // pool_list_entry: "{" $@81 pool_params "}"
#line 1965 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3221 "dhcp4_parser.cc"
    break;

  case 566: // $@82: %empty
#line 1971 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3231 "dhcp4_parser.cc"
    break;

  case 567: // sub_pool4: "{" $@82 pool_params "}"
#line 1975 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3241 "dhcp4_parser.cc"
    break;

  case 570: // pool_params: pool_params ","
#line 1983 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3249 "dhcp4_parser.cc"
    break;

  case 578: // $@83: %empty
#line 1997 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3258 "dhcp4_parser.cc"
    break;

  case 579: // pool_entry: "pool" $@83 ":" "constant string"
#line 2000 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3268 "dhcp4_parser.cc"
    break;

  case 580: // $@84: %empty
#line 2006 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3276 "dhcp4_parser.cc"
    break;

  case 581: // user_context: "user-context" $@84 ":" map_value
#line 2008 "dhcp4_parser.yy"
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
#line 3303 "dhcp4_parser.cc"
    break;

  case 582: // $@85: %empty
#line 2031 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3311 "dhcp4_parser.cc"
    break;

  case 583: // comment: "comment" $@85 ":" "constant string"
#line 2033 "dhcp4_parser.yy"
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
#line 3340 "dhcp4_parser.cc"
    break;

  case 584: // $@86: %empty
#line 2061 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3352 "dhcp4_parser.cc"
    break;

  case 585: // reservations: "reservations" $@86 ":" "[" reservations_list "]"
#line 2067 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3361 "dhcp4_parser.cc"
    break;

  case 590: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2078 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3369 "dhcp4_parser.cc"
    break;

  case 591: // $@87: %empty
#line 2083 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3379 "dhcp4_parser.cc"
    break;

  case 592: // reservation: "{" $@87 reservation_params "}"
#line 2087 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3388 "dhcp4_parser.cc"
    break;

  case 593: // $@88: %empty
#line 2092 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3398 "dhcp4_parser.cc"
    break;

  case 594: // sub_reservation: "{" $@88 reservation_params "}"
#line 2096 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3407 "dhcp4_parser.cc"
    break;

  case 599: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2107 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3415 "dhcp4_parser.cc"
    break;

  case 615: // $@89: %empty
#line 2130 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3424 "dhcp4_parser.cc"
    break;

  case 616: // next_server: "next-server" $@89 ":" "constant string"
#line 2133 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3434 "dhcp4_parser.cc"
    break;

  case 617: // $@90: %empty
#line 2139 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3443 "dhcp4_parser.cc"
    break;

  case 618: // server_hostname: "server-hostname" $@90 ":" "constant string"
#line 2142 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3453 "dhcp4_parser.cc"
    break;

  case 619: // $@91: %empty
#line 2148 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3462 "dhcp4_parser.cc"
    break;

  case 620: // boot_file_name: "boot-file-name" $@91 ":" "constant string"
#line 2151 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3472 "dhcp4_parser.cc"
    break;

  case 621: // $@92: %empty
#line 2157 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3481 "dhcp4_parser.cc"
    break;

  case 622: // ip_address: "ip-address" $@92 ":" "constant string"
#line 2160 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3491 "dhcp4_parser.cc"
    break;

  case 623: // $@93: %empty
#line 2166 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3503 "dhcp4_parser.cc"
    break;

  case 624: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2172 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3512 "dhcp4_parser.cc"
    break;

  case 625: // $@94: %empty
#line 2177 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3521 "dhcp4_parser.cc"
    break;

  case 626: // duid: "duid" $@94 ":" "constant string"
#line 2180 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3531 "dhcp4_parser.cc"
    break;

  case 627: // $@95: %empty
#line 2186 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3540 "dhcp4_parser.cc"
    break;

  case 628: // hw_address: "hw-address" $@95 ":" "constant string"
#line 2189 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3550 "dhcp4_parser.cc"
    break;

  case 629: // $@96: %empty
#line 2195 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3559 "dhcp4_parser.cc"
    break;

  case 630: // client_id_value: "client-id" $@96 ":" "constant string"
#line 2198 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3569 "dhcp4_parser.cc"
    break;

  case 631: // $@97: %empty
#line 2204 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3578 "dhcp4_parser.cc"
    break;

  case 632: // circuit_id_value: "circuit-id" $@97 ":" "constant string"
#line 2207 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3588 "dhcp4_parser.cc"
    break;

  case 633: // $@98: %empty
#line 2213 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3597 "dhcp4_parser.cc"
    break;

  case 634: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2216 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3607 "dhcp4_parser.cc"
    break;

  case 635: // $@99: %empty
#line 2222 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3616 "dhcp4_parser.cc"
    break;

  case 636: // hostname: "hostname" $@99 ":" "constant string"
#line 2225 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3626 "dhcp4_parser.cc"
    break;

  case 637: // $@100: %empty
#line 2231 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3638 "dhcp4_parser.cc"
    break;

  case 638: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2237 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3647 "dhcp4_parser.cc"
    break;

  case 639: // $@101: %empty
#line 2245 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3659 "dhcp4_parser.cc"
    break;

  case 640: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2251 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3668 "dhcp4_parser.cc"
    break;

  case 643: // $@102: %empty
#line 2263 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3680 "dhcp4_parser.cc"
    break;

  case 644: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2269 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3689 "dhcp4_parser.cc"
    break;

  case 647: // client_classes_list: client_classes_list ","
#line 2276 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3697 "dhcp4_parser.cc"
    break;

  case 648: // $@103: %empty
#line 2281 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3707 "dhcp4_parser.cc"
    break;

  case 649: // client_class_entry: "{" $@103 client_class_params "}"
#line 2285 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3717 "dhcp4_parser.cc"
    break;

  case 654: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2297 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3725 "dhcp4_parser.cc"
    break;

  case 670: // $@104: %empty
#line 2320 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3734 "dhcp4_parser.cc"
    break;

  case 671: // client_class_test: "test" $@104 ":" "constant string"
#line 2323 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3744 "dhcp4_parser.cc"
    break;

  case 672: // only_if_required: "only-if-required" ":" "boolean"
#line 2329 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3754 "dhcp4_parser.cc"
    break;

  case 673: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2337 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3764 "dhcp4_parser.cc"
    break;

  case 674: // $@105: %empty
#line 2345 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3776 "dhcp4_parser.cc"
    break;

  case 675: // control_socket: "control-socket" $@105 ":" "{" control_socket_params "}"
#line 2351 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3785 "dhcp4_parser.cc"
    break;

  case 678: // control_socket_params: control_socket_params ","
#line 2358 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3793 "dhcp4_parser.cc"
    break;

  case 684: // $@106: %empty
#line 2370 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3802 "dhcp4_parser.cc"
    break;

  case 685: // control_socket_type: "socket-type" $@106 ":" "constant string"
#line 2373 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3812 "dhcp4_parser.cc"
    break;

  case 686: // $@107: %empty
#line 2379 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3821 "dhcp4_parser.cc"
    break;

  case 687: // control_socket_name: "socket-name" $@107 ":" "constant string"
#line 2382 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3831 "dhcp4_parser.cc"
    break;

  case 688: // $@108: %empty
#line 2391 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3843 "dhcp4_parser.cc"
    break;

  case 689: // dhcp_queue_control: "dhcp-queue-control" $@108 ":" "{" queue_control_params "}"
#line 2397 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3854 "dhcp4_parser.cc"
    break;

  case 692: // queue_control_params: queue_control_params ","
#line 2406 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3862 "dhcp4_parser.cc"
    break;

  case 699: // enable_queue: "enable-queue" ":" "boolean"
#line 2419 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3872 "dhcp4_parser.cc"
    break;

  case 700: // $@109: %empty
#line 2425 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3881 "dhcp4_parser.cc"
    break;

  case 701: // queue_type: "queue-type" $@109 ":" "constant string"
#line 2428 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3891 "dhcp4_parser.cc"
    break;

  case 702: // capacity: "capacity" ":" "integer"
#line 2434 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3901 "dhcp4_parser.cc"
    break;

  case 703: // $@110: %empty
#line 2440 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 704: // arbitrary_map_entry: "constant string" $@110 ":" value
#line 2443 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3919 "dhcp4_parser.cc"
    break;

  case 705: // $@111: %empty
#line 2450 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3931 "dhcp4_parser.cc"
    break;

  case 706: // dhcp_ddns: "dhcp-ddns" $@111 ":" "{" dhcp_ddns_params "}"
#line 2456 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3942 "dhcp4_parser.cc"
    break;

  case 707: // $@112: %empty
#line 2463 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3952 "dhcp4_parser.cc"
    break;

  case 708: // sub_dhcp_ddns: "{" $@112 dhcp_ddns_params "}"
#line 2467 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3962 "dhcp4_parser.cc"
    break;

  case 711: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2475 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3970 "dhcp4_parser.cc"
    break;

  case 730: // enable_updates: "enable-updates" ":" "boolean"
#line 2500 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3980 "dhcp4_parser.cc"
    break;

  case 731: // $@113: %empty
#line 2506 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3989 "dhcp4_parser.cc"
    break;

  case 732: // server_ip: "server-ip" $@113 ":" "constant string"
#line 2509 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3999 "dhcp4_parser.cc"
    break;

  case 733: // server_port: "server-port" ":" "integer"
#line 2515 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4009 "dhcp4_parser.cc"
    break;

  case 734: // $@114: %empty
#line 2521 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4018 "dhcp4_parser.cc"
    break;

  case 735: // sender_ip: "sender-ip" $@114 ":" "constant string"
#line 2524 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4028 "dhcp4_parser.cc"
    break;

  case 736: // sender_port: "sender-port" ":" "integer"
#line 2530 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4038 "dhcp4_parser.cc"
    break;

  case 737: // max_queue_size: "max-queue-size" ":" "integer"
#line 2536 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4048 "dhcp4_parser.cc"
    break;

  case 738: // $@115: %empty
#line 2542 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4057 "dhcp4_parser.cc"
    break;

  case 739: // ncr_protocol: "ncr-protocol" $@115 ":" ncr_protocol_value
#line 2545 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4066 "dhcp4_parser.cc"
    break;

  case 740: // ncr_protocol_value: "udp"
#line 2551 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4072 "dhcp4_parser.cc"
    break;

  case 741: // ncr_protocol_value: "tcp"
#line 2552 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4078 "dhcp4_parser.cc"
    break;

  case 742: // $@116: %empty
#line 2555 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4087 "dhcp4_parser.cc"
    break;

  case 743: // ncr_format: "ncr-format" $@116 ":" "JSON"
#line 2558 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4097 "dhcp4_parser.cc"
    break;

  case 744: // $@117: %empty
#line 2565 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4106 "dhcp4_parser.cc"
    break;

  case 745: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2568 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4116 "dhcp4_parser.cc"
    break;

  case 746: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2575 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4126 "dhcp4_parser.cc"
    break;

  case 747: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2582 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4136 "dhcp4_parser.cc"
    break;

  case 748: // $@118: %empty
#line 2589 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4145 "dhcp4_parser.cc"
    break;

  case 749: // dep_replace_client_name: "replace-client-name" $@118 ":" ddns_replace_client_name_value
#line 2592 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4154 "dhcp4_parser.cc"
    break;

  case 750: // $@119: %empty
#line 2598 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4163 "dhcp4_parser.cc"
    break;

  case 751: // dep_generated_prefix: "generated-prefix" $@119 ":" "constant string"
#line 2601 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4173 "dhcp4_parser.cc"
    break;

  case 752: // $@120: %empty
#line 2608 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4182 "dhcp4_parser.cc"
    break;

  case 753: // dep_hostname_char_set: "hostname-char-set" $@120 ":" "constant string"
#line 2611 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4192 "dhcp4_parser.cc"
    break;

  case 754: // $@121: %empty
#line 2618 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4201 "dhcp4_parser.cc"
    break;

  case 755: // dep_hostname_char_replacement: "hostname-char-replacement" $@121 ":" "constant string"
#line 2621 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4211 "dhcp4_parser.cc"
    break;

  case 756: // $@122: %empty
#line 2630 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4223 "dhcp4_parser.cc"
    break;

  case 757: // config_control: "config-control" $@122 ":" "{" config_control_params "}"
#line 2636 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4233 "dhcp4_parser.cc"
    break;

  case 758: // $@123: %empty
#line 2642 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4243 "dhcp4_parser.cc"
    break;

  case 759: // sub_config_control: "{" $@123 config_control_params "}"
#line 2646 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4252 "dhcp4_parser.cc"
    break;

  case 762: // config_control_params: config_control_params ","
#line 2654 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4260 "dhcp4_parser.cc"
    break;

  case 765: // $@124: %empty
#line 2664 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4272 "dhcp4_parser.cc"
    break;

  case 766: // config_databases: "config-databases" $@124 ":" "[" database_list "]"
#line 2670 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4281 "dhcp4_parser.cc"
    break;

  case 767: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2675 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4291 "dhcp4_parser.cc"
    break;

  case 768: // $@125: %empty
#line 2683 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4303 "dhcp4_parser.cc"
    break;

  case 769: // loggers: "loggers" $@125 ":" "[" loggers_entries "]"
#line 2689 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4312 "dhcp4_parser.cc"
    break;

  case 772: // loggers_entries: loggers_entries ","
#line 2698 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4320 "dhcp4_parser.cc"
    break;

  case 773: // $@126: %empty
#line 2704 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4330 "dhcp4_parser.cc"
    break;

  case 774: // logger_entry: "{" $@126 logger_params "}"
#line 2708 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4338 "dhcp4_parser.cc"
    break;

  case 777: // logger_params: logger_params ","
#line 2714 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4346 "dhcp4_parser.cc"
    break;

  case 785: // debuglevel: "debuglevel" ":" "integer"
#line 2728 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4356 "dhcp4_parser.cc"
    break;

  case 786: // $@127: %empty
#line 2734 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4365 "dhcp4_parser.cc"
    break;

  case 787: // severity: "severity" $@127 ":" "constant string"
#line 2737 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4375 "dhcp4_parser.cc"
    break;

  case 788: // $@128: %empty
#line 2743 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4387 "dhcp4_parser.cc"
    break;

  case 789: // output_options_list: "output_options" $@128 ":" "[" output_options_list_content "]"
#line 2749 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4396 "dhcp4_parser.cc"
    break;

  case 792: // output_options_list_content: output_options_list_content ","
#line 2756 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4404 "dhcp4_parser.cc"
    break;

  case 793: // $@129: %empty
#line 2761 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4414 "dhcp4_parser.cc"
    break;

  case 794: // output_entry: "{" $@129 output_params_list "}"
#line 2765 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4422 "dhcp4_parser.cc"
    break;

  case 797: // output_params_list: output_params_list ","
#line 2771 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4430 "dhcp4_parser.cc"
    break;

  case 803: // $@130: %empty
#line 2783 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4439 "dhcp4_parser.cc"
    break;

  case 804: // output: "output" $@130 ":" "constant string"
#line 2786 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4449 "dhcp4_parser.cc"
    break;

  case 805: // flush: "flush" ":" "boolean"
#line 2792 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4459 "dhcp4_parser.cc"
    break;

  case 806: // maxsize: "maxsize" ":" "integer"
#line 2798 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4469 "dhcp4_parser.cc"
    break;

  case 807: // maxver: "maxver" ":" "integer"
#line 2804 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4479 "dhcp4_parser.cc"
    break;

  case 808: // $@131: %empty
#line 2810 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4488 "dhcp4_parser.cc"
    break;

  case 809: // pattern: "pattern" $@131 ":" "constant string"
#line 2813 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4498 "dhcp4_parser.cc"
    break;

  case 810: // $@132: %empty
#line 2819 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4510 "dhcp4_parser.cc"
    break;

  case 811: // compatibility: "compatibility" $@132 ":" "{" compatibility_params "}"
#line 2825 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4519 "dhcp4_parser.cc"
    break;

  case 814: // compatibility_params: compatibility_params ","
#line 2832 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4527 "dhcp4_parser.cc"
    break;

  case 817: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2841 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4537 "dhcp4_parser.cc"
    break;


#line 4541 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -960;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     383,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,    24,    38,    26,    41,    48,    60,
      62,    92,    96,    98,   134,   136,   169,   171,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,    38,  -130,    66,   186,    71,   614,
      21,    78,   -10,    87,   219,  -106,    -3,   116,  -960,    83,
     114,   131,   179,   193,  -960,    56,  -960,  -960,  -960,  -960,
     203,   206,   223,  -960,  -960,  -960,  -960,  -960,  -960,   234,
     242,   279,   283,   315,   333,   354,   371,   373,   374,   381,
    -960,   382,   384,   400,   401,   409,  -960,  -960,  -960,   425,
     433,   434,  -960,  -960,  -960,   435,  -960,  -960,  -960,  -960,
     437,   439,   443,  -960,  -960,  -960,  -960,  -960,   444,  -960,
    -960,  -960,  -960,  -960,  -960,   446,  -960,  -960,   447,  -960,
      67,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,   448,  -960,   110,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,   449,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
     128,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,   162,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,   191,   218,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,   215,
    -960,  -960,   451,  -960,  -960,  -960,   457,  -960,  -960,   323,
     412,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,   462,   463,  -960,  -960,  -960,  -960,
     460,   414,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,   165,  -960,  -960,  -960,   465,  -960,
    -960,   467,  -960,   468,   469,  -960,  -960,   474,   476,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,   217,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,   477,   221,  -960,  -960,  -960,  -960,
      38,    38,  -960,   282,   482,  -960,  -960,   483,   486,   487,
     290,   293,   294,   495,   498,   500,   501,   502,   504,   307,
     308,   309,   310,   313,   317,   314,   320,   321,   325,   326,
     512,   329,   331,   330,   332,   335,   521,   525,   531,   337,
     341,   342,   545,   548,   549,   355,   552,   555,   559,   563,
     364,   380,   385,   565,   581,   582,   583,   584,   388,   587,
     588,   589,   590,   591,   592,   393,   594,   595,  -960,   186,
    -960,   596,   597,   598,   399,    71,  -960,   600,   601,   602,
     603,   604,   605,   408,   607,   608,   610,   614,  -960,   612,
      21,  -960,   613,   615,   616,   617,   618,   619,   620,   622,
    -960,    78,  -960,   623,   624,   416,   625,   626,   628,   429,
    -960,    87,   630,   431,   432,  -960,   219,   633,   634,   103,
    -960,   441,   635,   642,   445,   644,   452,   453,   647,   649,
     454,   455,   653,   656,   657,   658,    -3,  -960,   659,   470,
     116,  -960,  -960,  -960,   660,   662,   663,   664,   666,  -960,
    -960,  -960,   484,   485,   497,   680,   681,   697,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,   503,
    -960,  -960,  -960,  -960,  -960,  -120,   505,   506,  -960,  -960,
    -960,   700,   707,   708,  -960,   709,   716,   515,   195,  -960,
    -960,  -960,   719,   720,   721,   725,   724,  -960,   726,   727,
     730,   731,   538,   539,  -960,   736,   735,  -960,   739,   226,
     296,  -960,  -960,   544,   546,   547,   741,   550,   551,  -960,
     739,   553,   742,  -960,   554,  -960,   739,   556,   557,   558,
     560,   561,   562,   564,  -960,   566,   567,  -960,   568,   569,
     570,  -960,  -960,   571,  -960,  -960,  -960,   572,   716,  -960,
    -960,   573,   574,  -960,   575,  -960,  -960,    20,   609,  -960,
    -960,  -120,   576,   578,   579,  -960,   745,  -960,  -960,    38,
     186,   116,    71,   729,  -960,  -960,  -960,   350,   350,   749,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,   753,
     757,   759,   774,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,   107,   775,   776,   777,   205,   235,    44,    -7,    -3,
    -960,  -960,   778,  -143,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,   779,  -960,  -960,  -960,  -960,
     150,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,   749,
    -960,   268,   270,   274,  -960,   312,  -960,  -960,  -960,  -960,
    -960,  -960,   783,   786,   787,   788,   789,  -960,  -960,  -960,
    -960,   790,   791,  -960,   792,   793,   794,   795,  -960,   324,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,   327,  -960,   796,   797,  -960,  -960,   798,   800,
    -960,  -960,   799,   803,  -960,  -960,   801,   805,  -960,  -960,
     804,   806,  -960,  -960,  -960,  -960,  -960,  -960,    36,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,    82,  -960,  -960,   807,
     808,  -960,  -960,   810,   809,  -960,   813,   814,   815,   816,
     817,   818,   346,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
     819,   820,   821,  -960,   347,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,   356,  -960,  -960,  -960,
     822,  -960,   823,  -960,  -960,  -960,   362,  -960,  -960,  -960,
    -960,  -960,   365,  -960,   163,  -960,   824,  -960,   366,  -960,
    -960,   629,  -960,   825,   811,  -960,  -960,  -960,  -960,   826,
     827,  -960,  -960,  -960,   828,   729,  -960,   831,   832,   833,
     834,   599,   636,   627,   637,   640,   835,   839,   840,   841,
     645,   646,   842,   648,   650,   651,   652,   350,  -960,  -960,
     350,  -960,   749,   614,  -960,   753,    87,  -960,   757,   219,
    -960,   759,  1230,  -960,   774,   107,  -960,   263,   775,  -960,
      78,  -960,   776,  -106,  -960,   777,   654,   655,   661,   665,
     667,   668,   205,  -960,   669,   670,   672,   235,  -960,   845,
     847,    44,  -960,   671,   849,   674,   854,    -7,  -960,  -960,
     244,   778,  -960,   673,  -143,  -960,  -960,   853,   857,    21,
    -960,   779,   858,  -960,  -960,   677,  -960,   260,   678,   679,
     682,  -960,  -960,  -960,  -960,  -960,   683,   684,   685,   686,
    -960,  -960,    95,  -960,  -960,  -960,  -960,  -960,   368,  -960,
     403,  -960,   856,  -960,   860,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,   411,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,   861,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,   863,   878,  -960,  -960,  -960,  -960,
    -960,   874,  -960,   413,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,   687,   688,  -960,  -960,
     689,  -960,    38,  -960,  -960,   862,  -960,  -960,  -960,  -960,
    -960,   420,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
     690,   423,  -960,   739,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  1230,  -960,   888,   691,  -960,
     263,  -960,  -960,  -960,  -960,  -960,  -960,   889,   692,   893,
     244,  -960,  -960,  -960,  -960,  -960,   699,  -960,  -960,   896,
    -960,   702,  -960,  -960,   891,  -960,  -960,   183,  -960,  -102,
     891,  -960,  -960,   900,   905,   907,  -960,   424,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,   910,   715,   718,   733,   934,
    -102,  -960,   740,  -960,  -960,  -960,   752,  -960,  -960,  -960
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   185,     9,   358,    11,   566,    13,
     593,    15,   486,    17,   495,    19,   534,    21,   320,    23,
     707,    25,   758,    27,    46,    39,     0,     0,     0,     0,
       0,   595,     0,   497,   536,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   756,   173,   200,
       0,     0,     0,   615,   617,   619,   198,   208,   210,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     143,     0,     0,     0,     0,     0,   152,   159,   161,     0,
       0,     0,   349,   484,   525,     0,   432,   580,   582,   425,
       0,     0,     0,   282,   643,   584,   311,   332,     0,   297,
     674,   688,   705,   165,   167,     0,   768,   810,     0,   131,
       0,    67,    70,    71,    72,    73,    74,   108,   109,   110,
     111,   112,    75,   103,   130,    92,    93,    94,   116,   117,
     118,   119,   120,   121,   122,   123,   114,   115,   124,   125,
     126,   128,    78,    79,   100,    80,    81,    82,   127,    86,
      87,    76,   105,   106,   107,   104,    77,    84,    85,    98,
      99,   101,    95,    96,    97,    83,    88,    89,    90,    91,
     102,   113,   129,   187,   189,   193,     0,   184,     0,   175,
     178,   179,   180,   181,   182,   183,   410,   412,   414,   557,
     408,   416,     0,   420,   418,   639,   407,   363,   364,   365,
     366,   367,   391,   392,   393,   394,   395,   381,   382,   396,
     397,   398,   399,   400,   401,   402,   403,   404,   405,   406,
       0,   360,   370,   386,   387,   388,   371,   373,   374,   377,
     378,   379,   376,   372,   368,   369,   389,   390,   375,   383,
     384,   385,   380,   578,   577,   573,   574,   572,     0,   568,
     571,   575,   576,   637,   625,   627,   631,   629,   635,   633,
     621,   614,   608,   612,   613,     0,   596,   597,   609,   610,
     611,   605,   600,   606,   602,   603,   604,   607,   601,     0,
     515,   257,     0,   519,   517,   522,     0,   511,   512,     0,
     498,   499,   502,   514,   503,   504,   505,   521,   506,   507,
     508,   509,   510,   551,     0,     0,   549,   550,   553,   554,
       0,   537,   538,   541,   542,   543,   544,   545,   546,   547,
     548,   328,   330,   325,     0,   322,   326,   327,     0,   744,
     731,     0,   734,     0,     0,   738,   742,     0,     0,   748,
     750,   752,   754,   729,   727,   728,     0,   709,   712,   713,
     714,   715,   716,   717,   718,   719,   724,   720,   721,   722,
     723,   725,   726,   765,     0,     0,   760,   763,   764,    45,
      50,     0,    37,    43,     0,    64,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    69,
      66,     0,     0,     0,     0,   177,   186,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   362,   359,     0,
     570,   567,     0,     0,     0,     0,     0,     0,     0,     0,
     594,   599,   487,     0,     0,     0,     0,     0,     0,     0,
     496,   501,     0,     0,     0,   535,   540,     0,     0,   324,
     321,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   711,   708,     0,     0,
     762,   759,    49,    41,     0,     0,     0,     0,     0,   146,
     147,   148,     0,     0,     0,     0,     0,     0,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,     0,
     170,   171,   149,   150,   151,     0,     0,     0,   163,   164,
     169,     0,     0,     0,   145,     0,     0,     0,     0,   422,
     423,   424,     0,     0,     0,     0,     0,   673,     0,     0,
       0,     0,     0,     0,   172,     0,     0,    68,     0,     0,
       0,   197,   176,     0,     0,     0,     0,     0,     0,   431,
       0,     0,     0,   361,     0,   569,     0,     0,     0,     0,
       0,     0,     0,     0,   598,     0,     0,   513,     0,     0,
       0,   524,   500,     0,   555,   556,   539,     0,     0,   323,
     730,     0,     0,   733,     0,   736,   737,     0,     0,   746,
     747,     0,     0,     0,     0,   710,     0,   767,   761,     0,
       0,     0,     0,     0,   616,   618,   620,     0,     0,   212,
     144,   154,   155,   156,   157,   158,   153,   160,   162,   351,
     488,   527,   434,    38,   581,   583,   427,   428,   429,   430,
     426,     0,     0,   586,   313,     0,     0,     0,     0,     0,
     166,   168,     0,     0,    51,   188,   191,   192,   190,   195,
     196,   194,   411,   413,   415,   559,   409,   417,   421,   419,
       0,   579,   638,   626,   628,   632,   630,   636,   634,   622,
     516,   258,   520,   518,   523,   552,   329,   331,   745,   732,
     735,   740,   741,   739,   743,   749,   751,   753,   755,   212,
      42,     0,     0,     0,   206,     0,   202,   205,   244,   250,
     252,   254,     0,     0,     0,     0,     0,   266,   268,   270,
     272,     0,     0,   276,     0,     0,     0,     0,   243,     0,
     219,   222,   223,   224,   225,   226,   227,   228,   229,   230,
     231,   236,   237,   238,   232,   239,   240,   241,   233,   234,
     235,   242,     0,   217,     0,   213,   214,   356,     0,   352,
     353,   493,     0,   489,   490,   532,     0,   528,   529,   439,
       0,   435,   436,   292,   293,   294,   295,   296,     0,   284,
     287,   288,   289,   290,   291,   648,     0,   645,   591,     0,
     587,   588,   318,     0,   314,   315,     0,     0,     0,     0,
       0,     0,     0,   334,   337,   338,   339,   340,   341,   342,
       0,     0,     0,   307,     0,   299,   302,   303,   304,   305,
     306,   684,   686,   683,   681,   682,     0,   676,   679,   680,
       0,   700,     0,   703,   696,   697,     0,   690,   693,   694,
     695,   698,     0,   773,     0,   770,     0,   816,     0,   812,
     815,    53,   564,     0,   560,   561,   623,   641,   642,     0,
       0,    62,   757,   174,     0,   204,   201,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   221,   199,   209,
       0,   211,   216,     0,   350,   355,   497,   485,   492,   536,
     526,   531,     0,   433,   438,   286,   283,   650,   647,   644,
     595,   585,   590,     0,   312,   317,     0,     0,     0,     0,
       0,     0,   336,   333,     0,     0,     0,   301,   298,     0,
       0,   678,   675,     0,     0,     0,     0,   692,   689,   706,
       0,   772,   769,     0,   814,   811,    55,     0,    54,     0,
     558,   563,     0,   640,   766,     0,   203,     0,     0,     0,
       0,   256,   259,   260,   261,   262,     0,     0,     0,     0,
     274,   275,     0,   263,   264,   265,   281,   220,     0,   215,
       0,   354,     0,   491,     0,   530,   483,   462,   463,   464,
     447,   448,   467,   468,   469,   470,   471,   450,   451,   472,
     473,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     444,   445,   446,   460,   461,   457,   458,   459,   456,     0,
     441,   449,   465,   466,   452,   453,   454,   455,   437,   285,
     670,     0,   665,   666,   667,   668,   669,   658,   659,   663,
     664,   660,   661,   662,     0,   651,   652,   655,   656,   657,
     646,     0,   589,     0,   316,   343,   344,   345,   346,   347,
     348,   335,   308,   309,   310,   300,     0,     0,   677,   699,
       0,   702,     0,   691,   788,     0,   786,   784,   778,   782,
     783,     0,   775,   780,   781,   779,   771,   817,   813,    52,
      57,     0,   562,     0,   207,   246,   247,   248,   249,   245,
     251,   253,   255,   267,   269,   271,   273,   278,   279,   280,
     277,   218,   357,   494,   533,   443,   440,     0,     0,   649,
     654,   592,   319,   685,   687,   701,   704,     0,     0,     0,
     777,   774,    56,   565,   624,   442,     0,   672,   653,     0,
     785,     0,   776,   671,     0,   787,   793,     0,   790,     0,
     792,   789,   803,     0,     0,     0,   808,     0,   795,   798,
     799,   800,   801,   802,   791,     0,     0,     0,     0,     0,
     797,   794,     0,   805,   806,   807,     0,   796,   804,   809
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,   -54,  -960,  -547,  -960,   305,
    -960,  -960,  -960,  -960,  -960,  -960,  -599,  -960,  -960,  -960,
     -67,  -960,  -960,  -960,  -960,  -960,  -960,  -960,   181,   491,
       4,    10,    23,   -40,   -23,   -12,    22,    25,    29,    33,
    -960,  -960,  -960,  -960,  -960,    35,    40,    43,    45,    46,
      47,  -960,   300,    50,  -960,    51,  -960,    53,    57,    58,
    -960,    61,  -960,    63,  -960,  -960,  -960,  -960,  -960,   292,
     493,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,    55,  -960,  -960,
    -960,  -960,  -960,  -960,   210,  -960,    42,  -960,  -676,    34,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
     -33,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,    59,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,    49,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,    54,  -960,  -960,  -960,    72,   509,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,    52,  -960,  -960,  -960,
    -960,  -960,  -960,  -959,  -960,  -960,  -960,    80,  -960,  -960,
    -960,    84,   577,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -957,  -960,   -65,  -960,    70,  -960,    64,    65,    68,
      69,  -960,  -960,  -960,  -960,  -960,  -960,  -960,    74,  -960,
    -960,  -142,   -46,  -960,  -960,  -960,  -960,  -960,    81,  -960,
    -960,  -960,    85,  -960,   529,  -960,   -63,  -960,  -960,  -960,
    -960,  -960,   -42,  -960,  -960,  -960,  -960,  -960,   -35,  -960,
    -960,  -960,    86,  -960,  -960,  -960,    89,  -960,   526,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
      32,  -960,  -960,  -960,    37,   580,  -960,  -960,   -51,  -960,
      -8,  -960,   -39,  -960,  -960,  -960,    77,  -960,  -960,  -960,
      88,  -960,   543,   -55,  -960,   -15,  -960,     3,  -960,   322,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -951,  -960,  -960,
    -960,  -960,  -960,    91,  -960,  -960,  -960,  -129,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,    75,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,    76,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,   344,   514,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,   386,   516,  -960,  -960,
    -960,  -960,  -960,  -960,    73,  -960,  -960,  -136,  -960,  -960,
    -960,  -960,  -960,  -960,  -155,  -960,  -960,  -170,  -960,  -960,
    -960,  -960,  -960,  -960,  -960,  -960,  -960,  -960,    79,  -960
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   704,
      82,    83,    39,    64,    79,    80,   725,   921,  1017,  1018,
     798,    41,    66,    85,   414,    86,    43,    67,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   440,   164,   165,   166,   167,   168,   169,   170,
     171,   446,   696,   172,   447,   173,   448,   174,   175,   176,
     473,   177,   474,   178,   179,   180,   181,   182,   418,   218,
     219,    45,    68,   220,   481,   221,   482,   728,   222,   483,
     731,   223,   183,   426,   184,   419,   775,   776,   777,   934,
     185,   427,   186,   428,   824,   825,   826,   960,   799,   800,
     801,   937,  1169,   802,   938,   803,   939,   804,   940,   805,
     806,   514,   807,   808,   809,   810,   811,   812,   813,   814,
     946,   815,   947,   816,   948,   817,   949,   818,   819,   820,
     952,  1180,   821,   187,   463,   848,   849,   850,   851,   852,
     853,   854,   188,   469,   884,   885,   886,   887,   888,   189,
     466,   863,   864,   865,   983,    59,    75,   364,   365,   366,
     527,   367,   528,   190,   467,   872,   873,   874,   875,   876,
     877,   878,   879,   191,   452,   828,   829,   830,   963,    47,
      69,   260,   261,   262,   491,   263,   487,   264,   488,   265,
     489,   266,   492,   267,   495,   268,   494,   192,   193,   194,
     195,   459,   710,   273,   196,   456,   840,   841,   842,   972,
    1089,  1090,   197,   453,    53,    72,   832,   833,   834,   966,
      55,    73,   329,   330,   331,   332,   333,   334,   335,   513,
     336,   517,   337,   516,   338,   339,   518,   340,   198,   454,
     836,   837,   838,   969,    57,    74,   350,   351,   352,   353,
     354,   522,   355,   356,   357,   358,   275,   490,   923,   924,
     925,  1019,    49,    70,   288,   289,   290,   499,   199,   457,
     200,   458,   201,   465,   859,   860,   861,   980,    51,    71,
     305,   306,   307,   202,   423,   203,   424,   204,   425,   311,
     509,   928,  1022,   312,   503,   313,   504,   314,   506,   315,
     505,   316,   508,   317,   507,   318,   502,   282,   496,   929,
     205,   464,   856,   857,   977,  1114,  1115,  1116,  1117,  1118,
    1187,  1119,   206,   207,   470,   896,   897,   898,   999,   899,
    1000,   208,   471,   906,   907,   908,   909,  1004,   910,   911,
    1006,   209,   472,    61,    76,   386,   387,   388,   389,   533,
     390,   391,   535,   392,   393,   394,   538,   763,   395,   539,
     396,   532,   397,   398,   399,   542,   400,   543,   401,   544,
     402,   545,   210,   417,    63,    77,   405,   406,   407,   548,
     408,   211,   476,   914,   915,  1010,  1151,  1152,  1153,  1154,
    1199,  1155,  1197,  1217,  1218,  1219,  1227,  1228,  1229,  1235,
    1230,  1231,  1232,  1233,  1239,   212,   477,   918,   919,   920
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     149,   217,   236,   284,   301,   285,   327,   346,   363,   383,
      78,   348,   822,  1081,   279,  1082,   308,   224,   276,   291,
     303,  1097,   341,   359,    28,   384,   319,   361,   362,   240,
     278,   738,   349,    40,   274,   287,   302,   742,   761,   975,
     328,   347,   976,    29,   916,    30,   241,    31,    42,   703,
     691,   692,   693,   694,   280,    44,   309,   242,   148,   415,
     225,   277,   292,   304,   416,   342,   360,    46,   385,    48,
     479,    81,   281,   237,   310,   480,    84,  1222,   123,   238,
    1223,  1224,  1225,  1226,   695,   978,   213,   214,   979,   409,
     215,   243,   239,   216,   244,   148,   127,   128,   245,    50,
     127,   128,   246,    52,   247,    54,    93,    94,    95,   248,
     124,   703,   249,   485,   250,   251,   252,   410,   486,   253,
     254,   320,   255,   283,   127,   128,   256,   257,   403,   404,
     258,   497,   259,   269,   270,   411,   498,   271,   272,   233,
     286,    56,   234,    58,   900,   901,   902,   127,   128,  1177,
    1178,  1179,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   500,  1011,   124,   529,  1012,
     501,   381,   382,   530,   127,   128,    60,   321,    62,   322,
     323,   127,   128,   324,   325,   326,  1220,   412,   762,  1221,
     127,   128,   891,   892,   903,   293,   413,    87,   148,   510,
      88,   294,   295,   296,   297,   298,   299,   420,   300,    89,
     421,    90,    91,    92,    93,    94,    95,    96,    97,    98,
     546,   511,   148,   512,   550,   547,  1081,   422,  1082,   551,
     843,   844,   845,   846,  1097,   847,   361,   362,   429,    32,
      33,    34,    35,   726,   727,   148,   430,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   479,   148,   550,   123,   124,   931,   485,   932,   148,
     300,   926,   933,   431,  1048,   125,   126,   432,   148,   127,
     128,    93,    94,    95,   129,  1165,  1166,  1167,  1168,   130,
     131,   132,   133,   134,   706,   707,   708,   709,   135,   321,
     343,   322,   323,   344,   345,   935,   729,   730,   136,   433,
     936,   137,   127,   128,    99,   100,   101,   957,   138,   139,
     957,   520,   958,   140,   321,   959,   141,   434,   127,   128,
     142,   866,   867,   868,   869,   870,   871,   127,   128,   992,
     997,   123,   124,   321,   993,   998,   552,   553,   435,  1001,
     143,   144,   145,   146,  1002,  1007,   127,   128,   546,  1014,
    1008,   957,   147,  1009,  1015,   436,  1181,   437,   438,   880,
     881,   882,  1100,  1101,   778,   439,   441,   148,   442,   779,
     780,   781,   782,   783,   784,   785,   786,   787,   788,   789,
     790,   791,   792,   793,   443,   444,   497,   794,   795,   796,
     797,  1182,   149,   445,  1185,   521,   529,   526,   217,  1186,
     148,  1192,  1144,  1200,  1145,  1146,   500,  1240,  1201,   449,
     236,  1203,  1241,   284,   224,   285,   148,   450,   451,   455,
     321,   460,   279,   461,   301,   148,   276,   462,   468,   291,
     475,   478,   484,   493,   327,   515,   308,   240,   278,   346,
     303,   519,   274,   348,   148,   287,   523,   524,   525,   531,
     341,   534,   536,   537,   241,   359,   302,   225,   540,   383,
     541,   549,   280,   554,   349,   242,   555,   556,   328,   277,
     557,   558,   292,   347,   559,   384,   309,   560,   561,   562,
     281,   237,   563,   304,   564,   565,   566,   238,   567,   568,
     569,   570,   571,   342,   310,   572,   579,   574,   360,   243,
     239,   573,   244,   575,   576,   585,   245,   577,   578,   586,
     246,   580,   247,   581,   582,   587,   583,   248,   385,   584,
     249,   588,   250,   251,   252,   589,   590,   253,   254,   591,
     255,   148,   592,   593,   256,   257,   595,   594,   258,   596,
     259,   269,   270,   597,  1204,   271,   272,   598,   599,   602,
     286,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   600,   603,   604,   605,   606,   601,
     607,   608,   609,   610,   611,   612,   613,   614,   615,   616,
     618,   619,   620,   621,   623,   624,   625,   626,   627,   628,
     629,   630,   631,   149,   632,   217,   634,   636,   647,   637,
     638,   639,   640,   641,   642,   770,   643,   645,   646,   648,
     649,   224,   650,   651,   653,   654,   655,   657,   658,   661,
      91,    92,    93,    94,    95,   660,   662,   663,   664,   883,
     893,   667,   383,   668,   665,   666,   917,   671,   669,   670,
     672,   673,   674,   676,   679,   889,   894,   904,   384,   680,
     681,   682,   677,   683,   225,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   684,   685,   687,   688,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   686,   226,
     227,   228,   689,   124,   690,   699,   697,   698,   890,   895,
     905,   385,   700,   701,   702,   229,   705,   127,   128,   230,
     231,   232,   129,    30,   711,   712,   713,   130,   131,   132,
     714,   715,   233,   716,   717,   234,   135,   718,   719,   720,
     721,   722,   723,   235,   724,   732,   735,   733,   734,   740,
     769,   736,   737,   774,   739,   741,   823,   743,   744,   745,
     827,   746,   747,   748,   831,   749,   835,   750,   751,   752,
     753,   754,   755,   756,   758,   759,   760,   766,   764,   767,
     768,   839,   855,   858,   862,   913,   922,   941,   143,   144,
     942,   943,   944,   945,   950,   951,   953,   954,   955,   956,
     962,  1031,   961,   965,   964,   967,   968,   970,   971,   974,
     973,   982,   985,   981,  1021,   148,   984,   986,   987,   988,
     989,   990,   991,   994,   995,   996,  1003,  1005,  1013,  1033,
    1016,  1020,  1025,  1024,  1023,  1027,  1028,  1029,  1030,  1036,
    1032,  1034,  1035,  1037,  1038,  1039,  1042,  1040,  1041,  1136,
    1043,  1137,  1044,  1140,  1046,  1045,  1125,  1126,  1142,  1159,
    1160,   771,  1163,  1127,  1183,  1188,  1198,  1128,  1184,  1129,
    1130,  1189,  1133,  1132,  1134,  1139,  1141,  1157,  1164,  1170,
    1171,  1190,  1191,  1172,  1173,  1174,  1175,  1176,  1193,  1194,
    1195,  1202,  1206,  1209,  1210,  1207,   236,  1211,  1216,   327,
    1213,  1214,   346,  1215,  1236,  1056,   348,  1083,   279,  1237,
    1102,  1238,   276,   301,  1242,   341,   363,  1094,   359,  1243,
    1244,  1092,  1111,   240,   278,   308,  1109,   349,   274,   303,
     883,  1107,  1060,   328,   893,  1245,   347,  1091,  1246,  1080,
     241,  1248,  1108,  1147,  1106,   302,   889,   917,   280,  1061,
     894,   242,   284,  1249,   285,   277,   904,  1095,   342,  1149,
    1062,   360,  1112,   757,  1093,   309,   281,   237,   291,  1110,
     617,   765,   304,   238,   773,  1096,  1057,  1148,   622,   930,
    1113,  1103,  1058,   310,   287,   243,   239,  1104,   244,   890,
    1026,  1047,   245,   895,  1063,  1059,   246,  1064,   247,   905,
    1105,  1065,  1150,   248,  1049,  1066,   249,  1067,   250,   251,
     252,   292,  1068,   253,   254,  1069,   255,  1070,  1071,  1072,
     256,   257,  1073,  1074,   258,  1075,   259,   269,   270,  1076,
    1077,   271,   272,  1078,  1099,  1079,  1085,  1086,   659,  1124,
    1087,  1088,  1084,  1205,  1131,  1051,  1135,  1050,  1098,  1053,
     652,  1052,   656,  1162,   644,  1123,  1161,  1055,  1054,  1122,
     675,  1208,   927,   912,  1212,  1234,   678,   772,  1121,  1120,
    1247,     0,     0,     0,   633,     0,  1138,     0,     0,     0,
     635,     0,     0,  1143,  1156,     0,     0,     0,  1196,   286,
       0,     0,     0,  1158,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1056,     0,
    1083,     0,     0,  1102,     0,     0,     0,     0,     0,     0,
    1094,     0,     0,  1147,  1092,  1111,     0,     0,     0,  1109,
       0,     0,     0,     0,  1107,  1060,     0,     0,     0,  1149,
    1091,     0,  1080,     0,     0,  1108,     0,  1106,     0,     0,
       0,     0,  1061,     0,     0,     0,     0,  1148,     0,     0,
    1095,     0,     0,  1062,     0,  1112,     0,  1093,     0,     0,
       0,     0,  1110,     0,     0,     0,     0,     0,  1096,  1057,
       0,     0,  1150,  1113,  1103,  1058,     0,     0,     0,     0,
    1104,     0,     0,     0,     0,     0,     0,  1063,  1059,     0,
    1064,     0,     0,  1105,  1065,     0,     0,     0,  1066,     0,
    1067,     0,     0,     0,     0,  1068,     0,     0,  1069,     0,
    1070,  1071,  1072,     0,     0,  1073,  1074,     0,  1075,     0,
       0,     0,  1076,  1077,     0,     0,  1078,     0,  1079,  1085,
    1086,     0,     0,  1087,  1088,  1084,    91,    92,    93,    94,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,     0,     0,     0,     0,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,     0,     0,     0,     0,   124,
     321,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   127,   128,     0,   231,     0,   129,     0,
       0,     0,     0,   130,   131,   132,     0,     0,   233,     0,
       0,   234,     0,     0,     0,     0,     0,     0,     0,   235,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   143,   144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   148
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,    74,   688,   972,    69,   972,    71,    68,    69,    70,
      71,   972,    73,    74,     0,    76,    72,   133,   134,    69,
      69,   630,    74,     7,    69,    70,    71,   636,    18,     3,
      73,    74,     6,     5,   187,     7,    69,     9,     7,   596,
     170,   171,   172,   173,    69,     7,    71,    69,   201,     3,
      68,    69,    70,    71,     8,    73,    74,     7,    76,     7,
       3,   201,    69,    69,    71,     8,    10,   179,    88,    69,
     182,   183,   184,   185,   204,     3,    15,    16,     6,     6,
      19,    69,    69,    22,    69,   201,   103,   104,    69,     7,
     103,   104,    69,     7,    69,     7,    28,    29,    30,    69,
      89,   658,    69,     3,    69,    69,    69,     3,     8,    69,
      69,    34,    69,   102,   103,   104,    69,    69,    12,    13,
      69,     3,    69,    69,    69,     4,     8,    69,    69,   118,
      70,     7,   121,     7,   151,   152,   153,   103,   104,    54,
      55,    56,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,     3,     3,    89,     3,     6,
       8,   174,   175,     8,   103,   104,     7,    90,     7,    92,
      93,   103,   104,    96,    97,    98,     3,     8,   168,     6,
     103,   104,   148,   149,   201,   117,     3,    11,   201,     8,
      14,   123,   124,   125,   126,   127,   128,     4,   130,    23,
       4,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       3,     3,   201,     8,     3,     8,  1185,     4,  1185,     8,
     123,   124,   125,   126,  1185,   128,   133,   134,     4,   201,
     202,   203,   204,    17,    18,   201,     4,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,     3,   201,     3,    88,    89,     8,     3,     8,   201,
     130,   131,     8,     4,   960,    99,   100,     4,   201,   103,
     104,    28,    29,    30,   108,    35,    36,    37,    38,   113,
     114,   115,   116,   117,   109,   110,   111,   112,   122,    90,
      91,    92,    93,    94,    95,     3,    20,    21,   132,     4,
       8,   135,   103,   104,    61,    62,    63,     3,   142,   143,
       3,     8,     8,   147,    90,     8,   150,     4,   103,   104,
     154,   136,   137,   138,   139,   140,   141,   103,   104,     3,
       3,    88,    89,    90,     8,     8,   410,   411,     4,     3,
     174,   175,   176,   177,     8,     3,   103,   104,     3,     3,
       8,     3,   186,     8,     8,     4,     8,     4,     4,   144,
     145,   146,   119,   120,    34,     4,     4,   201,     4,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,     4,     4,     3,    57,    58,    59,
      60,     8,   479,     4,     3,     3,     3,     3,   485,     8,
     201,     8,   178,     3,   180,   181,     3,     3,     8,     4,
     497,     8,     8,   500,   485,   500,   201,     4,     4,     4,
      90,     4,   497,     4,   511,   201,   497,     4,     4,   500,
       4,     4,     4,     4,   521,     4,   511,   497,   497,   526,
     511,     4,   497,   526,   201,   500,     4,     4,     8,     4,
     521,     4,     4,     4,   497,   526,   511,   485,     4,   546,
       4,     4,   497,   201,   526,   497,     4,     4,   521,   497,
       4,     4,   500,   526,   204,   546,   511,   204,   204,     4,
     497,   497,     4,   511,     4,     4,     4,   497,     4,   202,
     202,   202,   202,   521,   511,   202,     4,   203,   526,   497,
     497,   204,   497,   203,   203,     4,   497,   202,   202,     4,
     497,   202,   497,   202,   204,     4,   204,   497,   546,   204,
     497,   204,   497,   497,   497,   204,   204,   497,   497,     4,
     497,   201,     4,     4,   497,   497,     4,   202,   497,     4,
     497,   497,   497,     4,  1163,   497,   497,     4,   204,     4,
     500,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   204,     4,     4,     4,     4,   204,
     202,     4,     4,     4,     4,     4,     4,   204,     4,     4,
       4,     4,     4,   204,     4,     4,     4,     4,     4,     4,
     202,     4,     4,   680,     4,   682,     4,     4,   202,     4,
       4,     4,     4,     4,     4,   679,     4,     4,     4,     4,
       4,   682,     4,   204,     4,   204,   204,     4,     4,     4,
      26,    27,    28,    29,    30,   204,     4,   202,     4,   716,
     717,     4,   719,     4,   202,   202,   723,     4,   204,   204,
       4,     4,     4,     4,     4,   716,   717,   718,   719,     7,
       7,     7,   202,     7,   682,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,   201,   201,     7,     7,    75,
      76,    77,    78,    79,    80,    81,    82,    83,   201,    85,
      86,    87,     5,    89,   201,     5,   201,   201,   716,   717,
     718,   719,     5,     5,     5,   101,   201,   103,   104,   105,
     106,   107,   108,     7,     5,     5,     5,   113,   114,   115,
       5,     7,   118,     7,     7,   121,   122,     7,     7,   201,
     201,     5,     7,   129,     5,   201,     5,   201,   201,     7,
       5,   201,   201,    24,   201,   201,     7,   201,   201,   201,
       7,   201,   201,   201,     7,   201,     7,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   169,   201,
     201,     7,     7,     7,     7,     7,     7,     4,   174,   175,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   202,     6,     3,     6,     6,     3,     6,     3,     3,
       6,     3,     3,     6,     3,   201,     6,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   202,
     201,     6,     4,     6,     8,     4,     4,     4,     4,     4,
     204,   204,   202,     4,     4,     4,     4,   202,   202,     4,
     202,     4,   202,     4,   202,   204,   202,   202,     4,     6,
       3,   680,     4,   202,     8,     4,     4,   202,     8,   202,
     202,     8,   202,   204,   202,   204,   202,   204,   201,   201,
     201,     3,     8,   201,   201,   201,   201,   201,   201,   201,
     201,   201,     4,     4,   202,   204,   963,     4,     7,   966,
     201,     5,   969,   201,     4,   972,   969,   972,   963,     4,
     977,     4,   963,   980,     4,   966,   983,   972,   969,   204,
     202,   972,   977,   963,   963,   980,   977,   969,   963,   980,
     997,   977,   972,   966,  1001,   202,   969,   972,     4,   972,
     963,   201,   977,  1010,   977,   980,   997,  1014,   963,   972,
    1001,   963,  1019,   201,  1019,   963,  1007,   972,   966,  1010,
     972,   969,   977,   658,   972,   980,   963,   963,  1019,   977,
     479,   671,   980,   963,   682,   972,   972,  1010,   485,   769,
     977,   977,   972,   980,  1019,   963,   963,   977,   963,   997,
     935,   957,   963,  1001,   972,   972,   963,   972,   963,  1007,
     977,   972,  1010,   963,   962,   972,   963,   972,   963,   963,
     963,  1019,   972,   963,   963,   972,   963,   972,   972,   972,
     963,   963,   972,   972,   963,   972,   963,   963,   963,   972,
     972,   963,   963,   972,   975,   972,   972,   972,   529,   985,
     972,   972,   972,  1185,   992,   965,   997,   963,   974,   968,
     521,   966,   526,  1021,   511,   983,  1019,   971,   969,   982,
     546,  1190,   740,   719,  1200,  1220,   550,   681,   980,   978,
    1240,    -1,    -1,    -1,   497,    -1,  1001,    -1,    -1,    -1,
     500,    -1,    -1,  1007,  1011,    -1,    -1,    -1,  1142,  1019,
      -1,    -1,    -1,  1014,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1185,    -1,
    1185,    -1,    -1,  1190,    -1,    -1,    -1,    -1,    -1,    -1,
    1185,    -1,    -1,  1200,  1185,  1190,    -1,    -1,    -1,  1190,
      -1,    -1,    -1,    -1,  1190,  1185,    -1,    -1,    -1,  1200,
    1185,    -1,  1185,    -1,    -1,  1190,    -1,  1190,    -1,    -1,
      -1,    -1,  1185,    -1,    -1,    -1,    -1,  1200,    -1,    -1,
    1185,    -1,    -1,  1185,    -1,  1190,    -1,  1185,    -1,    -1,
      -1,    -1,  1190,    -1,    -1,    -1,    -1,    -1,  1185,  1185,
      -1,    -1,  1200,  1190,  1190,  1185,    -1,    -1,    -1,    -1,
    1190,    -1,    -1,    -1,    -1,    -1,    -1,  1185,  1185,    -1,
    1185,    -1,    -1,  1190,  1185,    -1,    -1,    -1,  1185,    -1,
    1185,    -1,    -1,    -1,    -1,  1185,    -1,    -1,  1185,    -1,
    1185,  1185,  1185,    -1,    -1,  1185,  1185,    -1,  1185,    -1,
      -1,    -1,  1185,  1185,    -1,    -1,  1185,    -1,  1185,  1185,
    1185,    -1,    -1,  1185,  1185,  1185,    26,    27,    28,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    -1,    -1,    -1,    -1,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   103,   104,    -1,   106,    -1,   108,    -1,
      -1,    -1,    -1,   113,   114,   115,    -1,    -1,   118,    -1,
      -1,   121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   174,   175,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   201
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,     0,     5,
       7,     9,   201,   202,   203,   204,   220,   221,   222,   227,
       7,   236,     7,   241,     7,   286,     7,   394,     7,   477,
       7,   493,     7,   429,     7,   435,     7,   459,     7,   370,
       7,   558,     7,   589,   228,   223,   237,   242,   287,   395,
     478,   494,   430,   436,   460,   371,   559,   590,   220,   229,
     230,   201,   225,   226,    10,   238,   240,    11,    14,    23,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    88,    89,    99,   100,   103,   104,   108,
     113,   114,   115,   116,   117,   122,   132,   135,   142,   143,
     147,   150,   154,   174,   175,   176,   177,   186,   201,   235,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   258,   259,   260,   261,   262,   263,
     264,   265,   268,   270,   272,   273,   274,   276,   278,   279,
     280,   281,   282,   297,   299,   305,   307,   348,   357,   364,
     378,   388,   412,   413,   414,   415,   419,   427,   453,   483,
     485,   487,   498,   500,   502,   525,   537,   538,   546,   556,
     587,   596,   620,    15,    16,    19,    22,   235,   284,   285,
     288,   290,   293,   296,   483,   485,    85,    86,    87,   101,
     105,   106,   107,   118,   121,   129,   235,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   260,   261,   262,
     263,   264,   265,   268,   270,   272,   273,   274,   276,   278,
     396,   397,   398,   400,   402,   404,   406,   408,   410,   412,
     413,   414,   415,   418,   453,   471,   483,   485,   487,   498,
     500,   502,   522,   102,   235,   408,   410,   453,   479,   480,
     481,   483,   485,   117,   123,   124,   125,   126,   127,   128,
     130,   235,   453,   483,   485,   495,   496,   497,   498,   500,
     502,   504,   508,   510,   512,   514,   516,   518,   520,   427,
      34,    90,    92,    93,    96,    97,    98,   235,   325,   437,
     438,   439,   440,   441,   442,   443,   445,   447,   449,   450,
     452,   483,   485,    91,    94,    95,   235,   325,   441,   447,
     461,   462,   463,   464,   465,   467,   468,   469,   470,   483,
     485,   133,   134,   235,   372,   373,   374,   376,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   174,   175,   235,   483,   485,   560,   561,   562,   563,
     565,   566,   568,   569,   570,   573,   575,   577,   578,   579,
     581,   583,   585,    12,    13,   591,   592,   593,   595,     6,
       3,     4,     8,     3,   239,     3,     8,   588,   283,   300,
       4,     4,     4,   499,   501,   503,   298,   306,   308,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     257,     4,     4,     4,     4,     4,   266,   269,   271,     4,
       4,     4,   389,   428,   454,     4,   420,   484,   486,   416,
       4,     4,     4,   349,   526,   488,   365,   379,     4,   358,
     539,   547,   557,   275,   277,     4,   597,   621,     4,     3,
       8,   289,   291,   294,     4,     3,     8,   401,   403,   405,
     472,   399,   407,     4,   411,   409,   523,     3,     8,   482,
       3,     8,   521,   509,   511,   515,   513,   519,   517,   505,
       8,     3,     8,   444,   326,     4,   448,   446,   451,     4,
       8,     3,   466,     4,     4,     8,     3,   375,   377,     3,
       8,     4,   576,   564,     4,   567,     4,     4,   571,   574,
       4,     4,   580,   582,   584,   586,     3,     8,   594,     4,
       3,     8,   220,   220,   201,     4,     4,     4,     4,   204,
     204,   204,     4,     4,     4,     4,     4,     4,   202,   202,
     202,   202,   202,   204,   203,   203,   203,   202,   202,     4,
     202,   202,   204,   204,   204,     4,     4,     4,   204,   204,
     204,     4,     4,     4,   202,     4,     4,     4,     4,   204,
     204,   204,     4,     4,     4,     4,     4,   202,     4,     4,
       4,     4,     4,     4,   204,     4,     4,   244,     4,     4,
       4,   204,   285,     4,     4,     4,     4,     4,     4,   202,
       4,     4,     4,   397,     4,   480,     4,     4,     4,     4,
       4,     4,     4,     4,   497,     4,     4,   202,     4,     4,
       4,   204,   439,     4,   204,   204,   463,     4,     4,   373,
     204,     4,     4,   202,     4,   202,   202,     4,     4,   204,
     204,     4,     4,     4,     4,   561,     4,   202,   592,     4,
       7,     7,     7,     7,   201,   201,   201,     7,     7,     5,
     201,   170,   171,   172,   173,   204,   267,   201,   201,     5,
       5,     5,     5,   222,   224,   201,   109,   110,   111,   112,
     417,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     201,   201,     5,     7,     5,   231,    17,    18,   292,    20,
      21,   295,   201,   201,   201,     5,   201,   201,   231,   201,
       7,   201,   231,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   224,   201,   201,
     201,    18,   168,   572,   169,   267,   201,   201,   201,     5,
     220,   243,   591,   284,    24,   301,   302,   303,    34,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    57,    58,    59,    60,   235,   313,
     314,   315,   318,   320,   322,   324,   325,   327,   328,   329,
     330,   331,   332,   333,   334,   336,   338,   340,   342,   343,
     344,   347,   313,     7,   309,   310,   311,     7,   390,   391,
     392,     7,   431,   432,   433,     7,   455,   456,   457,     7,
     421,   422,   423,   123,   124,   125,   126,   128,   350,   351,
     352,   353,   354,   355,   356,     7,   527,   528,     7,   489,
     490,   491,     7,   366,   367,   368,   136,   137,   138,   139,
     140,   141,   380,   381,   382,   383,   384,   385,   386,   387,
     144,   145,   146,   235,   359,   360,   361,   362,   363,   483,
     485,   148,   149,   235,   483,   485,   540,   541,   542,   544,
     151,   152,   153,   201,   483,   485,   548,   549,   550,   551,
     553,   554,   560,     7,   598,   599,   187,   235,   622,   623,
     624,   232,     7,   473,   474,   475,   131,   504,   506,   524,
     309,     8,     8,     8,   304,     3,     8,   316,   319,   321,
     323,     4,     4,     4,     4,     4,   335,   337,   339,   341,
       4,     4,   345,     4,     4,     4,     4,     3,     8,     8,
     312,     6,     3,   393,     6,     3,   434,     6,     3,   458,
       6,     3,   424,     6,     3,     3,     6,   529,     3,     6,
     492,     6,     3,   369,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   543,
     545,     3,     8,     4,   552,     4,   555,     3,     8,     8,
     600,     3,     6,     4,     3,     8,   201,   233,   234,   476,
       6,     3,   507,     8,     6,     4,   302,     4,     4,     4,
       4,   202,   204,   202,   204,   202,     4,     4,     4,     4,
     202,   202,     4,   202,   202,   204,   202,   314,   313,   311,
     396,   392,   437,   433,   461,   457,   235,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   260,   261,   262,
     263,   264,   265,   268,   270,   272,   273,   274,   276,   278,
     325,   388,   406,   408,   410,   412,   413,   414,   415,   425,
     426,   453,   483,   485,   498,   500,   502,   522,   423,   351,
     119,   120,   235,   245,   246,   247,   325,   427,   453,   483,
     485,   498,   500,   502,   530,   531,   532,   533,   534,   536,
     528,   495,   491,   372,   368,   202,   202,   202,   202,   202,
     202,   381,   204,   202,   202,   360,     4,     4,   541,   204,
       4,   202,     4,   549,   178,   180,   181,   235,   325,   483,
     485,   601,   602,   603,   604,   606,   599,   204,   623,     6,
       3,   479,   475,     4,   201,    35,    36,    37,    38,   317,
     201,   201,   201,   201,   201,   201,   201,    54,    55,    56,
     346,     8,     8,     8,     8,     3,     8,   535,     4,     8,
       3,     8,     8,   201,   201,   201,   220,   607,     4,   605,
       3,     8,   201,     8,   231,   426,     4,   204,   532,     4,
     202,     4,   602,   201,     5,   201,     7,   608,   609,   610,
       3,     6,   179,   182,   183,   184,   185,   611,   612,   613,
     615,   616,   617,   618,   609,   614,     4,     4,     4,   619,
       3,     8,     4,   204,   202,   202,     4,   612,   201,   201
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   205,   207,   206,   208,   206,   209,   206,   210,   206,
     211,   206,   212,   206,   213,   206,   214,   206,   215,   206,
     216,   206,   217,   206,   218,   206,   219,   206,   220,   220,
     220,   220,   220,   220,   220,   221,   223,   222,   224,   225,
     225,   226,   226,   226,   228,   227,   229,   229,   230,   230,
     230,   232,   231,   233,   233,   234,   234,   234,   235,   237,
     236,   239,   238,   238,   240,   242,   241,   243,   243,   243,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   244,   244,   244,   244,   244,   244,   244,   244,
     244,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   257,   256,   258,   259,   260,   261,   262,
     263,   264,   266,   265,   267,   267,   267,   267,   267,   269,
     268,   271,   270,   272,   273,   275,   274,   277,   276,   278,
     279,   280,   281,   283,   282,   284,   284,   284,   285,   285,
     285,   285,   285,   285,   285,   287,   286,   289,   288,   291,
     290,   292,   292,   294,   293,   295,   295,   296,   298,   297,
     300,   299,   301,   301,   301,   302,   304,   303,   306,   305,
     308,   307,   309,   309,   310,   310,   310,   312,   311,   313,
     313,   313,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   316,   315,   317,   317,   317,   317,
     319,   318,   321,   320,   323,   322,   324,   326,   325,   327,
     328,   329,   330,   331,   332,   333,   335,   334,   337,   336,
     339,   338,   341,   340,   342,   343,   345,   344,   346,   346,
     346,   347,   349,   348,   350,   350,   350,   351,   351,   351,
     351,   351,   352,   353,   354,   355,   356,   358,   357,   359,
     359,   359,   360,   360,   360,   360,   360,   360,   361,   362,
     363,   365,   364,   366,   366,   367,   367,   367,   369,   368,
     371,   370,   372,   372,   372,   372,   373,   373,   375,   374,
     377,   376,   379,   378,   380,   380,   380,   381,   381,   381,
     381,   381,   381,   382,   383,   384,   385,   386,   387,   389,
     388,   390,   390,   391,   391,   391,   393,   392,   395,   394,
     396,   396,   396,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   397,   397,
     397,   397,   397,   397,   397,   397,   397,   397,   399,   398,
     401,   400,   403,   402,   405,   404,   407,   406,   409,   408,
     411,   410,   412,   413,   414,   416,   415,   417,   417,   417,
     417,   418,   420,   419,   421,   421,   422,   422,   422,   424,
     423,   425,   425,   425,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   426,   426,   426,   426,   426,   426,
     426,   426,   426,   426,   428,   427,   430,   429,   431,   431,
     432,   432,   432,   434,   433,   436,   435,   437,   437,   438,
     438,   438,   439,   439,   439,   439,   439,   439,   439,   439,
     439,   439,   440,   441,   442,   444,   443,   446,   445,   448,
     447,   449,   451,   450,   452,   454,   453,   455,   455,   456,
     456,   456,   458,   457,   460,   459,   461,   461,   462,   462,
     462,   463,   463,   463,   463,   463,   463,   463,   463,   463,
     464,   466,   465,   467,   468,   469,   470,   472,   471,   473,
     473,   474,   474,   474,   476,   475,   478,   477,   479,   479,
     479,   480,   480,   480,   480,   480,   480,   480,   482,   481,
     484,   483,   486,   485,   488,   487,   489,   489,   490,   490,
     490,   492,   491,   494,   493,   495,   495,   496,   496,   496,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   497,
     497,   497,   497,   497,   497,   499,   498,   501,   500,   503,
     502,   505,   504,   507,   506,   509,   508,   511,   510,   513,
     512,   515,   514,   517,   516,   519,   518,   521,   520,   523,
     522,   524,   524,   526,   525,   527,   527,   527,   529,   528,
     530,   530,   531,   531,   531,   532,   532,   532,   532,   532,
     532,   532,   532,   532,   532,   532,   532,   532,   532,   533,
     535,   534,   536,   537,   539,   538,   540,   540,   540,   541,
     541,   541,   541,   541,   543,   542,   545,   544,   547,   546,
     548,   548,   548,   549,   549,   549,   549,   549,   549,   550,
     552,   551,   553,   555,   554,   557,   556,   559,   558,   560,
     560,   560,   561,   561,   561,   561,   561,   561,   561,   561,
     561,   561,   561,   561,   561,   561,   561,   561,   561,   561,
     562,   564,   563,   565,   567,   566,   568,   569,   571,   570,
     572,   572,   574,   573,   576,   575,   577,   578,   580,   579,
     582,   581,   584,   583,   586,   585,   588,   587,   590,   589,
     591,   591,   591,   592,   592,   594,   593,   595,   597,   596,
     598,   598,   598,   600,   599,   601,   601,   601,   602,   602,
     602,   602,   602,   602,   602,   603,   605,   604,   607,   606,
     608,   608,   608,   610,   609,   611,   611,   611,   612,   612,
     612,   612,   612,   614,   613,   615,   616,   617,   619,   618,
     621,   620,   622,   622,   622,   623,   623,   624
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
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     4,     0,     4,     3,
       3,     3,     3,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     6,     1,     3,     2,     1,     0,     4,     0,     6,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     0,     4,     1,     1,
       1,     3,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     1,     0,     6,     1,     3,     2,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     2,     1,     1,     0,     6,     3,     0,     6,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     0,     6,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     3
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
  "\"encapsulate\"", "\"array\"", "\"parked-packet-limit\"",
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"id\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"global\"",
  "\"all\"", "\"reservations-global\"", "\"reservations-in-subnet\"",
  "\"reservations-out-of-pool\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"require-client-classes\"", "\"test\"",
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
  "global_object", "$@18", "global_object_comma", "sub_dhcp4", "$@19",
  "global_params", "global_param", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "server_tag", "$@20",
  "parked_packet_limit", "echo_client_id", "match_client_id",
  "authoritative", "ddns_send_updates", "ddns_override_no_update",
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
       0,   294,   294,   294,   295,   295,   296,   296,   297,   297,
     298,   298,   299,   299,   300,   300,   301,   301,   302,   302,
     303,   303,   304,   304,   305,   305,   306,   306,   314,   315,
     316,   317,   318,   319,   320,   323,   328,   328,   339,   342,
     343,   346,   351,   357,   362,   362,   369,   370,   373,   377,
     381,   387,   387,   394,   395,   398,   402,   406,   416,   425,
     425,   440,   440,   454,   457,   463,   463,   472,   473,   474,
     481,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   545,   551,   557,   563,   569,   575,   581,   587,
     593,   599,   605,   611,   611,   620,   626,   632,   638,   644,
     650,   656,   662,   662,   671,   674,   677,   680,   683,   689,
     689,   698,   698,   707,   713,   719,   719,   728,   728,   737,
     743,   749,   755,   761,   761,   773,   774,   775,   780,   781,
     782,   783,   784,   785,   786,   789,   789,   798,   798,   809,
     809,   817,   818,   821,   821,   829,   831,   835,   842,   842,
     855,   855,   866,   867,   868,   873,   875,   875,   894,   894,
     907,   907,   918,   919,   922,   923,   924,   929,   929,   939,
     940,   941,   946,   947,   948,   949,   950,   951,   952,   953,
     954,   955,   956,   957,   958,   959,   960,   961,   962,   963,
     964,   965,   966,   967,   970,   970,   978,   979,   980,   981,
     984,   984,   993,   993,  1002,  1002,  1011,  1017,  1017,  1026,
    1032,  1038,  1044,  1050,  1056,  1062,  1068,  1068,  1077,  1077,
    1086,  1086,  1095,  1095,  1104,  1110,  1116,  1116,  1124,  1125,
    1126,  1129,  1136,  1136,  1147,  1148,  1149,  1154,  1155,  1156,
    1157,  1158,  1161,  1166,  1171,  1176,  1181,  1188,  1188,  1201,
    1202,  1203,  1208,  1209,  1210,  1211,  1212,  1213,  1216,  1222,
    1228,  1234,  1234,  1245,  1246,  1249,  1250,  1251,  1256,  1256,
    1266,  1266,  1276,  1277,  1278,  1281,  1284,  1285,  1288,  1288,
    1297,  1297,  1306,  1306,  1318,  1319,  1320,  1325,  1326,  1327,
    1328,  1329,  1330,  1333,  1339,  1345,  1351,  1357,  1363,  1372,
    1372,  1386,  1387,  1390,  1391,  1392,  1401,  1401,  1427,  1427,
    1438,  1439,  1440,  1446,  1447,  1448,  1449,  1450,  1451,  1452,
    1453,  1454,  1455,  1456,  1457,  1458,  1459,  1460,  1461,  1462,
    1463,  1464,  1465,  1466,  1467,  1468,  1469,  1470,  1471,  1472,
    1473,  1474,  1475,  1476,  1477,  1478,  1479,  1480,  1481,  1482,
    1483,  1484,  1485,  1486,  1487,  1488,  1489,  1490,  1493,  1493,
    1502,  1502,  1511,  1511,  1520,  1520,  1529,  1529,  1538,  1538,
    1547,  1547,  1558,  1564,  1570,  1576,  1576,  1584,  1585,  1586,
    1587,  1590,  1598,  1598,  1610,  1611,  1615,  1616,  1617,  1622,
    1622,  1630,  1631,  1632,  1637,  1638,  1639,  1640,  1641,  1642,
    1643,  1644,  1645,  1646,  1647,  1648,  1649,  1650,  1651,  1652,
    1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,  1662,
    1663,  1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,
    1673,  1674,  1675,  1676,  1683,  1683,  1697,  1697,  1706,  1707,
    1710,  1711,  1712,  1719,  1719,  1734,  1734,  1748,  1749,  1752,
    1753,  1754,  1759,  1760,  1761,  1762,  1763,  1764,  1765,  1766,
    1767,  1768,  1771,  1773,  1779,  1781,  1781,  1790,  1790,  1799,
    1799,  1808,  1810,  1810,  1819,  1829,  1829,  1842,  1843,  1848,
    1849,  1850,  1857,  1857,  1869,  1869,  1881,  1882,  1887,  1888,
    1889,  1896,  1897,  1898,  1899,  1900,  1901,  1902,  1903,  1904,
    1907,  1909,  1909,  1918,  1920,  1922,  1928,  1937,  1937,  1950,
    1951,  1954,  1955,  1956,  1961,  1961,  1971,  1971,  1981,  1982,
    1983,  1988,  1989,  1990,  1991,  1992,  1993,  1994,  1997,  1997,
    2006,  2006,  2031,  2031,  2061,  2061,  2072,  2073,  2076,  2077,
    2078,  2083,  2083,  2092,  2092,  2101,  2102,  2105,  2106,  2107,
    2113,  2114,  2115,  2116,  2117,  2118,  2119,  2120,  2121,  2122,
    2123,  2124,  2125,  2126,  2127,  2130,  2130,  2139,  2139,  2148,
    2148,  2157,  2157,  2166,  2166,  2177,  2177,  2186,  2186,  2195,
    2195,  2204,  2204,  2213,  2213,  2222,  2222,  2231,  2231,  2245,
    2245,  2256,  2257,  2263,  2263,  2274,  2275,  2276,  2281,  2281,
    2291,  2292,  2295,  2296,  2297,  2302,  2303,  2304,  2305,  2306,
    2307,  2308,  2309,  2310,  2311,  2312,  2313,  2314,  2315,  2318,
    2320,  2320,  2329,  2337,  2345,  2345,  2356,  2357,  2358,  2363,
    2364,  2365,  2366,  2367,  2370,  2370,  2379,  2379,  2391,  2391,
    2404,  2405,  2406,  2411,  2412,  2413,  2414,  2415,  2416,  2419,
    2425,  2425,  2434,  2440,  2440,  2450,  2450,  2463,  2463,  2473,
    2474,  2475,  2480,  2481,  2482,  2483,  2484,  2485,  2486,  2487,
    2488,  2489,  2490,  2491,  2492,  2493,  2494,  2495,  2496,  2497,
    2500,  2506,  2506,  2515,  2521,  2521,  2530,  2536,  2542,  2542,
    2551,  2552,  2555,  2555,  2565,  2565,  2575,  2582,  2589,  2589,
    2598,  2598,  2608,  2608,  2618,  2618,  2630,  2630,  2642,  2642,
    2652,  2653,  2654,  2660,  2661,  2664,  2664,  2675,  2683,  2683,
    2696,  2697,  2698,  2704,  2704,  2712,  2713,  2714,  2719,  2720,
    2721,  2722,  2723,  2724,  2725,  2728,  2734,  2734,  2743,  2743,
    2754,  2755,  2756,  2761,  2761,  2769,  2770,  2771,  2776,  2777,
    2778,  2779,  2780,  2783,  2783,  2792,  2798,  2804,  2810,  2810,
    2819,  2819,  2830,  2831,  2832,  2837,  2838,  2841
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
#line 6150 "dhcp4_parser.cc"

#line 2847 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
