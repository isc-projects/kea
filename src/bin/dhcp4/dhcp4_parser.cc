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

  case 43: // $@15: %empty
#line 359 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 941 "dhcp4_parser.cc"
    break;

  case 44: // list_generic: "[" $@15 list_content "]"
#line 362 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 949 "dhcp4_parser.cc"
    break;

  case 47: // not_empty_list: value
#line 370 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 958 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: not_empty_list "," value
#line 374 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 967 "dhcp4_parser.cc"
    break;

  case 49: // $@16: %empty
#line 381 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // list_strings: "[" $@16 list_strings_content "]"
#line 383 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 984 "dhcp4_parser.cc"
    break;

  case 53: // not_empty_list_strings: "constant string"
#line 392 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 993 "dhcp4_parser.cc"
    break;

  case 54: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 396 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1002 "dhcp4_parser.cc"
    break;

  case 55: // unknown_map_entry: "constant string" ":"
#line 407 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1013 "dhcp4_parser.cc"
    break;

  case 56: // $@17: %empty
#line 416 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1024 "dhcp4_parser.cc"
    break;

  case 57: // syntax_map: "{" $@17 global_object "}"
#line 421 "dhcp4_parser.yy"
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
#line 431 "dhcp4_parser.yy"
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
#line 440 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp4_parser.cc"
    break;

  case 60: // $@19: %empty
#line 448 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1072 "dhcp4_parser.cc"
    break;

  case 61: // sub_dhcp4: "{" $@19 global_params "}"
#line 452 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1081 "dhcp4_parser.cc"
    break;

  case 126: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 527 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1091 "dhcp4_parser.cc"
    break;

  case 127: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 533 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1101 "dhcp4_parser.cc"
    break;

  case 128: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 539 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1111 "dhcp4_parser.cc"
    break;

  case 129: // renew_timer: "renew-timer" ":" "integer"
#line 545 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 130: // rebind_timer: "rebind-timer" ":" "integer"
#line 551 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 131: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 557 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 132: // t1_percent: "t1-percent" ":" "floating point"
#line 563 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 133: // t2_percent: "t2-percent" ":" "floating point"
#line 569 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 134: // cache_threshold: "cache-threshold" ":" "floating point"
#line 575 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 135: // cache_max_age: "cache-max-age" ":" "integer"
#line 581 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 136: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 587 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 137: // $@20: %empty
#line 593 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1200 "dhcp4_parser.cc"
    break;

  case 138: // server_tag: "server-tag" $@20 ":" "constant string"
#line 596 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1210 "dhcp4_parser.cc"
    break;

  case 139: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 602 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1220 "dhcp4_parser.cc"
    break;

  case 140: // echo_client_id: "echo-client-id" ":" "boolean"
#line 608 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1230 "dhcp4_parser.cc"
    break;

  case 141: // match_client_id: "match-client-id" ":" "boolean"
#line 614 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 142: // authoritative: "authoritative" ":" "boolean"
#line 620 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 143: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 626 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 144: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 632 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1270 "dhcp4_parser.cc"
    break;

  case 145: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 638 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1280 "dhcp4_parser.cc"
    break;

  case 146: // $@21: %empty
#line 644 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1289 "dhcp4_parser.cc"
    break;

  case 147: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 647 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1298 "dhcp4_parser.cc"
    break;

  case 148: // ddns_replace_client_name_value: "when-present"
#line 653 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1306 "dhcp4_parser.cc"
    break;

  case 149: // ddns_replace_client_name_value: "never"
#line 656 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1314 "dhcp4_parser.cc"
    break;

  case 150: // ddns_replace_client_name_value: "always"
#line 659 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1322 "dhcp4_parser.cc"
    break;

  case 151: // ddns_replace_client_name_value: "when-not-present"
#line 662 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1330 "dhcp4_parser.cc"
    break;

  case 152: // ddns_replace_client_name_value: "boolean"
#line 665 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1339 "dhcp4_parser.cc"
    break;

  case 153: // $@22: %empty
#line 671 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1348 "dhcp4_parser.cc"
    break;

  case 154: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 674 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1358 "dhcp4_parser.cc"
    break;

  case 155: // $@23: %empty
#line 680 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1367 "dhcp4_parser.cc"
    break;

  case 156: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 683 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1377 "dhcp4_parser.cc"
    break;

  case 157: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 689 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1387 "dhcp4_parser.cc"
    break;

  case 158: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 695 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1397 "dhcp4_parser.cc"
    break;

  case 159: // $@24: %empty
#line 701 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1406 "dhcp4_parser.cc"
    break;

  case 160: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 704 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1416 "dhcp4_parser.cc"
    break;

  case 161: // $@25: %empty
#line 710 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1425 "dhcp4_parser.cc"
    break;

  case 162: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 713 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1435 "dhcp4_parser.cc"
    break;

  case 163: // store_extended_info: "store-extended-info" ":" "boolean"
#line 719 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1445 "dhcp4_parser.cc"
    break;

  case 164: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 725 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1455 "dhcp4_parser.cc"
    break;

  case 165: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 731 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 166: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 737 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 167: // $@26: %empty
#line 743 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1487 "dhcp4_parser.cc"
    break;

  case 168: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 749 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1497 "dhcp4_parser.cc"
    break;

  case 178: // $@27: %empty
#line 768 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1507 "dhcp4_parser.cc"
    break;

  case 179: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 772 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1516 "dhcp4_parser.cc"
    break;

  case 180: // $@28: %empty
#line 777 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1528 "dhcp4_parser.cc"
    break;

  case 181: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 783 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1537 "dhcp4_parser.cc"
    break;

  case 182: // $@29: %empty
#line 788 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1546 "dhcp4_parser.cc"
    break;

  case 183: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 791 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 184: // socket_type: "raw"
#line 796 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1561 "dhcp4_parser.cc"
    break;

  case 185: // socket_type: "udp"
#line 797 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1567 "dhcp4_parser.cc"
    break;

  case 186: // $@30: %empty
#line 800 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 187: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 803 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1585 "dhcp4_parser.cc"
    break;

  case 188: // outbound_interface_value: "same-as-inbound"
#line 808 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1593 "dhcp4_parser.cc"
    break;

  case 189: // outbound_interface_value: "use-routing"
#line 810 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1601 "dhcp4_parser.cc"
    break;

  case 190: // re_detect: "re-detect" ":" "boolean"
#line 814 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1611 "dhcp4_parser.cc"
    break;

  case 191: // $@31: %empty
#line 821 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1623 "dhcp4_parser.cc"
    break;

  case 192: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 827 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 193: // $@32: %empty
#line 834 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1646 "dhcp4_parser.cc"
    break;

  case 194: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 840 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 198: // $@33: %empty
#line 850 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1664 "dhcp4_parser.cc"
    break;

  case 199: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 853 "dhcp4_parser.yy"
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
#line 1684 "dhcp4_parser.cc"
    break;

  case 200: // $@34: %empty
#line 869 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1696 "dhcp4_parser.cc"
    break;

  case 201: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 875 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1707 "dhcp4_parser.cc"
    break;

  case 202: // $@35: %empty
#line 882 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1719 "dhcp4_parser.cc"
    break;

  case 203: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 888 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 208: // $@36: %empty
#line 901 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 209: // database: "{" $@36 database_map_params "}"
#line 905 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1748 "dhcp4_parser.cc"
    break;

  case 234: // $@37: %empty
#line 939 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1757 "dhcp4_parser.cc"
    break;

  case 235: // database_type: "type" $@37 ":" db_type
#line 942 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1766 "dhcp4_parser.cc"
    break;

  case 236: // db_type: "memfile"
#line 947 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1772 "dhcp4_parser.cc"
    break;

  case 237: // db_type: "mysql"
#line 948 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1778 "dhcp4_parser.cc"
    break;

  case 238: // db_type: "postgresql"
#line 949 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1784 "dhcp4_parser.cc"
    break;

  case 239: // db_type: "cql"
#line 950 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1790 "dhcp4_parser.cc"
    break;

  case 240: // $@38: %empty
#line 953 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1799 "dhcp4_parser.cc"
    break;

  case 241: // user: "user" $@38 ":" "constant string"
#line 956 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1809 "dhcp4_parser.cc"
    break;

  case 242: // $@39: %empty
#line 962 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 243: // password: "password" $@39 ":" "constant string"
#line 965 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1828 "dhcp4_parser.cc"
    break;

  case 244: // $@40: %empty
#line 971 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1837 "dhcp4_parser.cc"
    break;

  case 245: // host: "host" $@40 ":" "constant string"
#line 974 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1847 "dhcp4_parser.cc"
    break;

  case 246: // port: "port" ":" "integer"
#line 980 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1857 "dhcp4_parser.cc"
    break;

  case 247: // $@41: %empty
#line 986 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1866 "dhcp4_parser.cc"
    break;

  case 248: // name: "name" $@41 ":" "constant string"
#line 989 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1876 "dhcp4_parser.cc"
    break;

  case 249: // persist: "persist" ":" "boolean"
#line 995 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1886 "dhcp4_parser.cc"
    break;

  case 250: // lfc_interval: "lfc-interval" ":" "integer"
#line 1001 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1896 "dhcp4_parser.cc"
    break;

  case 251: // readonly: "readonly" ":" "boolean"
#line 1007 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1906 "dhcp4_parser.cc"
    break;

  case 252: // connect_timeout: "connect-timeout" ":" "integer"
#line 1013 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1916 "dhcp4_parser.cc"
    break;

  case 253: // request_timeout: "request-timeout" ":" "integer"
#line 1019 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 254: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1025 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1936 "dhcp4_parser.cc"
    break;

  case 255: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1031 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1946 "dhcp4_parser.cc"
    break;

  case 256: // $@42: %empty
#line 1037 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1955 "dhcp4_parser.cc"
    break;

  case 257: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1040 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1965 "dhcp4_parser.cc"
    break;

  case 258: // $@43: %empty
#line 1046 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1974 "dhcp4_parser.cc"
    break;

  case 259: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1049 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1984 "dhcp4_parser.cc"
    break;

  case 260: // $@44: %empty
#line 1055 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1993 "dhcp4_parser.cc"
    break;

  case 261: // consistency: "consistency" $@44 ":" "constant string"
#line 1058 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 2003 "dhcp4_parser.cc"
    break;

  case 262: // $@45: %empty
#line 1064 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2012 "dhcp4_parser.cc"
    break;

  case 263: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1067 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2022 "dhcp4_parser.cc"
    break;

  case 264: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1073 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2032 "dhcp4_parser.cc"
    break;

  case 265: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1079 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2042 "dhcp4_parser.cc"
    break;

  case 266: // $@46: %empty
#line 1085 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2051 "dhcp4_parser.cc"
    break;

  case 267: // on_fail: "on-fail" $@46 ":" on_fail_mode
#line 1088 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2060 "dhcp4_parser.cc"
    break;

  case 268: // on_fail_mode: "stop-retry-exit"
#line 1093 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2066 "dhcp4_parser.cc"
    break;

  case 269: // on_fail_mode: "serve-retry-exit"
#line 1094 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2072 "dhcp4_parser.cc"
    break;

  case 270: // on_fail_mode: "serve-retry-continue"
#line 1095 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2078 "dhcp4_parser.cc"
    break;

  case 271: // max_row_errors: "max-row-errors" ":" "integer"
#line 1098 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2088 "dhcp4_parser.cc"
    break;

  case 272: // $@47: %empty
#line 1105 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 273: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1111 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 281: // duid_id: "duid"
#line 1127 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2118 "dhcp4_parser.cc"
    break;

  case 282: // hw_address_id: "hw-address"
#line 1132 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2127 "dhcp4_parser.cc"
    break;

  case 283: // circuit_id: "circuit-id"
#line 1137 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2136 "dhcp4_parser.cc"
    break;

  case 284: // client_id: "client-id"
#line 1142 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2145 "dhcp4_parser.cc"
    break;

  case 285: // flex_id: "flex-id"
#line 1147 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2154 "dhcp4_parser.cc"
    break;

  case 286: // $@48: %empty
#line 1154 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2166 "dhcp4_parser.cc"
    break;

  case 287: // dhcp_multi_threading: "multi-threading" $@48 ":" "{" multi_threading_params "}"
#line 1160 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2177 "dhcp4_parser.cc"
    break;

  case 296: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1179 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2187 "dhcp4_parser.cc"
    break;

  case 297: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1185 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2197 "dhcp4_parser.cc"
    break;

  case 298: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1191 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2207 "dhcp4_parser.cc"
    break;

  case 299: // $@49: %empty
#line 1197 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2219 "dhcp4_parser.cc"
    break;

  case 300: // hooks_libraries: "hooks-libraries" $@49 ":" "[" hooks_libraries_list "]"
#line 1203 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2228 "dhcp4_parser.cc"
    break;

  case 305: // $@50: %empty
#line 1216 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2238 "dhcp4_parser.cc"
    break;

  case 306: // hooks_library: "{" $@50 hooks_params "}"
#line 1220 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2248 "dhcp4_parser.cc"
    break;

  case 307: // $@51: %empty
#line 1226 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2258 "dhcp4_parser.cc"
    break;

  case 308: // sub_hooks_library: "{" $@51 hooks_params "}"
#line 1230 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2268 "dhcp4_parser.cc"
    break;

  case 314: // $@52: %empty
#line 1245 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2277 "dhcp4_parser.cc"
    break;

  case 315: // library: "library" $@52 ":" "constant string"
#line 1248 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2287 "dhcp4_parser.cc"
    break;

  case 316: // $@53: %empty
#line 1254 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2296 "dhcp4_parser.cc"
    break;

  case 317: // parameters: "parameters" $@53 ":" map_value
#line 1257 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2305 "dhcp4_parser.cc"
    break;

  case 318: // $@54: %empty
#line 1263 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2317 "dhcp4_parser.cc"
    break;

  case 319: // expired_leases_processing: "expired-leases-processing" $@54 ":" "{" expired_leases_params "}"
#line 1269 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2327 "dhcp4_parser.cc"
    break;

  case 328: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1287 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2337 "dhcp4_parser.cc"
    break;

  case 329: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1293 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 330: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1299 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 331: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1305 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2367 "dhcp4_parser.cc"
    break;

  case 332: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1311 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2377 "dhcp4_parser.cc"
    break;

  case 333: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1317 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2387 "dhcp4_parser.cc"
    break;

  case 334: // $@55: %empty
#line 1326 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2399 "dhcp4_parser.cc"
    break;

  case 335: // subnet4_list: "subnet4" $@55 ":" "[" subnet4_list_content "]"
#line 1332 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2408 "dhcp4_parser.cc"
    break;

  case 340: // $@56: %empty
#line 1352 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2418 "dhcp4_parser.cc"
    break;

  case 341: // subnet4: "{" $@56 subnet4_params "}"
#line 1356 "dhcp4_parser.yy"
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
#line 2444 "dhcp4_parser.cc"
    break;

  case 342: // $@57: %empty
#line 1378 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2454 "dhcp4_parser.cc"
    break;

  case 343: // sub_subnet4: "{" $@57 subnet4_params "}"
#line 1382 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2464 "dhcp4_parser.cc"
    break;

  case 391: // $@58: %empty
#line 1441 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 392: // subnet: "subnet" $@58 ":" "constant string"
#line 1444 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2483 "dhcp4_parser.cc"
    break;

  case 393: // $@59: %empty
#line 1450 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 394: // subnet_4o6_interface: "4o6-interface" $@59 ":" "constant string"
#line 1453 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2502 "dhcp4_parser.cc"
    break;

  case 395: // $@60: %empty
#line 1459 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2511 "dhcp4_parser.cc"
    break;

  case 396: // subnet_4o6_interface_id: "4o6-interface-id" $@60 ":" "constant string"
#line 1462 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2521 "dhcp4_parser.cc"
    break;

  case 397: // $@61: %empty
#line 1468 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2530 "dhcp4_parser.cc"
    break;

  case 398: // subnet_4o6_subnet: "4o6-subnet" $@61 ":" "constant string"
#line 1471 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2540 "dhcp4_parser.cc"
    break;

  case 399: // $@62: %empty
#line 1477 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2549 "dhcp4_parser.cc"
    break;

  case 400: // interface: "interface" $@62 ":" "constant string"
#line 1480 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2559 "dhcp4_parser.cc"
    break;

  case 401: // $@63: %empty
#line 1486 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2568 "dhcp4_parser.cc"
    break;

  case 402: // client_class: "client-class" $@63 ":" "constant string"
#line 1489 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2578 "dhcp4_parser.cc"
    break;

  case 403: // $@64: %empty
#line 1495 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 404: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1501 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 405: // reservations_global: "reservations-global" ":" "boolean"
#line 1506 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2609 "dhcp4_parser.cc"
    break;

  case 406: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1512 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2619 "dhcp4_parser.cc"
    break;

  case 407: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1518 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2629 "dhcp4_parser.cc"
    break;

  case 408: // $@65: %empty
#line 1524 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2638 "dhcp4_parser.cc"
    break;

  case 409: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1527 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2647 "dhcp4_parser.cc"
    break;

  case 410: // hr_mode: "disabled"
#line 1532 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2653 "dhcp4_parser.cc"
    break;

  case 411: // hr_mode: "out-of-pool"
#line 1533 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2659 "dhcp4_parser.cc"
    break;

  case 412: // hr_mode: "global"
#line 1534 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2665 "dhcp4_parser.cc"
    break;

  case 413: // hr_mode: "all"
#line 1535 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2671 "dhcp4_parser.cc"
    break;

  case 414: // id: "id" ":" "integer"
#line 1538 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2681 "dhcp4_parser.cc"
    break;

  case 415: // $@66: %empty
#line 1546 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 416: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1552 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 421: // $@67: %empty
#line 1567 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 422: // shared_network: "{" $@67 shared_network_params "}"
#line 1571 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2720 "dhcp4_parser.cc"
    break;

  case 465: // $@68: %empty
#line 1625 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2732 "dhcp4_parser.cc"
    break;

  case 466: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1631 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2741 "dhcp4_parser.cc"
    break;

  case 467: // $@69: %empty
#line 1639 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2750 "dhcp4_parser.cc"
    break;

  case 468: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1642 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2758 "dhcp4_parser.cc"
    break;

  case 473: // $@70: %empty
#line 1658 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2768 "dhcp4_parser.cc"
    break;

  case 474: // option_def_entry: "{" $@70 option_def_params "}"
#line 1662 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2780 "dhcp4_parser.cc"
    break;

  case 475: // $@71: %empty
#line 1673 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2790 "dhcp4_parser.cc"
    break;

  case 476: // sub_option_def: "{" $@71 option_def_params "}"
#line 1677 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 492: // code: "code" ":" "integer"
#line 1709 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2812 "dhcp4_parser.cc"
    break;

  case 494: // $@72: %empty
#line 1717 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 495: // option_def_type: "type" $@72 ":" "constant string"
#line 1720 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2831 "dhcp4_parser.cc"
    break;

  case 496: // $@73: %empty
#line 1726 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2840 "dhcp4_parser.cc"
    break;

  case 497: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1729 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2850 "dhcp4_parser.cc"
    break;

  case 498: // $@74: %empty
#line 1735 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2859 "dhcp4_parser.cc"
    break;

  case 499: // space: "space" $@74 ":" "constant string"
#line 1738 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2869 "dhcp4_parser.cc"
    break;

  case 501: // $@75: %empty
#line 1746 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2878 "dhcp4_parser.cc"
    break;

  case 502: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1749 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2888 "dhcp4_parser.cc"
    break;

  case 503: // option_def_array: "array" ":" "boolean"
#line 1755 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2898 "dhcp4_parser.cc"
    break;

  case 504: // $@76: %empty
#line 1765 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2910 "dhcp4_parser.cc"
    break;

  case 505: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1771 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2919 "dhcp4_parser.cc"
    break;

  case 510: // $@77: %empty
#line 1790 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2929 "dhcp4_parser.cc"
    break;

  case 511: // option_data_entry: "{" $@77 option_data_params "}"
#line 1794 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2938 "dhcp4_parser.cc"
    break;

  case 512: // $@78: %empty
#line 1802 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2948 "dhcp4_parser.cc"
    break;

  case 513: // sub_option_data: "{" $@78 option_data_params "}"
#line 1806 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2957 "dhcp4_parser.cc"
    break;

  case 528: // $@79: %empty
#line 1839 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2966 "dhcp4_parser.cc"
    break;

  case 529: // option_data_data: "data" $@79 ":" "constant string"
#line 1842 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 532: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1852 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2986 "dhcp4_parser.cc"
    break;

  case 533: // option_data_always_send: "always-send" ":" "boolean"
#line 1858 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2996 "dhcp4_parser.cc"
    break;

  case 534: // $@80: %empty
#line 1867 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3008 "dhcp4_parser.cc"
    break;

  case 535: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1873 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3017 "dhcp4_parser.cc"
    break;

  case 540: // $@81: %empty
#line 1888 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3027 "dhcp4_parser.cc"
    break;

  case 541: // pool_list_entry: "{" $@81 pool_params "}"
#line 1892 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3037 "dhcp4_parser.cc"
    break;

  case 542: // $@82: %empty
#line 1898 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3047 "dhcp4_parser.cc"
    break;

  case 543: // sub_pool4: "{" $@82 pool_params "}"
#line 1902 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3057 "dhcp4_parser.cc"
    break;

  case 553: // $@83: %empty
#line 1921 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3066 "dhcp4_parser.cc"
    break;

  case 554: // pool_entry: "pool" $@83 ":" "constant string"
#line 1924 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3076 "dhcp4_parser.cc"
    break;

  case 555: // $@84: %empty
#line 1930 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3084 "dhcp4_parser.cc"
    break;

  case 556: // user_context: "user-context" $@84 ":" map_value
#line 1932 "dhcp4_parser.yy"
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
#line 3111 "dhcp4_parser.cc"
    break;

  case 557: // $@85: %empty
#line 1955 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3119 "dhcp4_parser.cc"
    break;

  case 558: // comment: "comment" $@85 ":" "constant string"
#line 1957 "dhcp4_parser.yy"
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
#line 3148 "dhcp4_parser.cc"
    break;

  case 559: // $@86: %empty
#line 1985 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3160 "dhcp4_parser.cc"
    break;

  case 560: // reservations: "reservations" $@86 ":" "[" reservations_list "]"
#line 1991 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3169 "dhcp4_parser.cc"
    break;

  case 565: // $@87: %empty
#line 2004 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3179 "dhcp4_parser.cc"
    break;

  case 566: // reservation: "{" $@87 reservation_params "}"
#line 2008 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 567: // $@88: %empty
#line 2013 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3198 "dhcp4_parser.cc"
    break;

  case 568: // sub_reservation: "{" $@88 reservation_params "}"
#line 2017 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3207 "dhcp4_parser.cc"
    break;

  case 588: // $@89: %empty
#line 2048 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 589: // next_server: "next-server" $@89 ":" "constant string"
#line 2051 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3226 "dhcp4_parser.cc"
    break;

  case 590: // $@90: %empty
#line 2057 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3235 "dhcp4_parser.cc"
    break;

  case 591: // server_hostname: "server-hostname" $@90 ":" "constant string"
#line 2060 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3245 "dhcp4_parser.cc"
    break;

  case 592: // $@91: %empty
#line 2066 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 593: // boot_file_name: "boot-file-name" $@91 ":" "constant string"
#line 2069 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3264 "dhcp4_parser.cc"
    break;

  case 594: // $@92: %empty
#line 2075 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 595: // ip_address: "ip-address" $@92 ":" "constant string"
#line 2078 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 596: // $@93: %empty
#line 2084 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3295 "dhcp4_parser.cc"
    break;

  case 597: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2090 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3304 "dhcp4_parser.cc"
    break;

  case 598: // $@94: %empty
#line 2095 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3313 "dhcp4_parser.cc"
    break;

  case 599: // duid: "duid" $@94 ":" "constant string"
#line 2098 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3323 "dhcp4_parser.cc"
    break;

  case 600: // $@95: %empty
#line 2104 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 601: // hw_address: "hw-address" $@95 ":" "constant string"
#line 2107 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 602: // $@96: %empty
#line 2113 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3351 "dhcp4_parser.cc"
    break;

  case 603: // client_id_value: "client-id" $@96 ":" "constant string"
#line 2116 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3361 "dhcp4_parser.cc"
    break;

  case 604: // $@97: %empty
#line 2122 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3370 "dhcp4_parser.cc"
    break;

  case 605: // circuit_id_value: "circuit-id" $@97 ":" "constant string"
#line 2125 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3380 "dhcp4_parser.cc"
    break;

  case 606: // $@98: %empty
#line 2131 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3389 "dhcp4_parser.cc"
    break;

  case 607: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2134 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3399 "dhcp4_parser.cc"
    break;

  case 608: // $@99: %empty
#line 2140 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3408 "dhcp4_parser.cc"
    break;

  case 609: // hostname: "hostname" $@99 ":" "constant string"
#line 2143 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3418 "dhcp4_parser.cc"
    break;

  case 610: // $@100: %empty
#line 2149 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3430 "dhcp4_parser.cc"
    break;

  case 611: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2155 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3439 "dhcp4_parser.cc"
    break;

  case 612: // $@101: %empty
#line 2163 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3451 "dhcp4_parser.cc"
    break;

  case 613: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2169 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3460 "dhcp4_parser.cc"
    break;

  case 616: // $@102: %empty
#line 2181 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3472 "dhcp4_parser.cc"
    break;

  case 617: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2187 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3481 "dhcp4_parser.cc"
    break;

  case 620: // $@103: %empty
#line 2196 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3491 "dhcp4_parser.cc"
    break;

  case 621: // client_class_entry: "{" $@103 client_class_params "}"
#line 2200 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3501 "dhcp4_parser.cc"
    break;

  case 641: // $@104: %empty
#line 2232 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3510 "dhcp4_parser.cc"
    break;

  case 642: // client_class_test: "test" $@104 ":" "constant string"
#line 2235 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3520 "dhcp4_parser.cc"
    break;

  case 643: // only_if_required: "only-if-required" ":" "boolean"
#line 2241 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3530 "dhcp4_parser.cc"
    break;

  case 644: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2249 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3540 "dhcp4_parser.cc"
    break;

  case 645: // $@105: %empty
#line 2257 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3552 "dhcp4_parser.cc"
    break;

  case 646: // control_socket: "control-socket" $@105 ":" "{" control_socket_params "}"
#line 2263 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3561 "dhcp4_parser.cc"
    break;

  case 654: // $@106: %empty
#line 2279 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3570 "dhcp4_parser.cc"
    break;

  case 655: // control_socket_type: "socket-type" $@106 ":" "constant string"
#line 2282 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3580 "dhcp4_parser.cc"
    break;

  case 656: // $@107: %empty
#line 2288 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3589 "dhcp4_parser.cc"
    break;

  case 657: // control_socket_name: "socket-name" $@107 ":" "constant string"
#line 2291 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3599 "dhcp4_parser.cc"
    break;

  case 658: // $@108: %empty
#line 2300 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 659: // dhcp_queue_control: "dhcp-queue-control" $@108 ":" "{" queue_control_params "}"
#line 2306 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 668: // enable_queue: "enable-queue" ":" "boolean"
#line 2325 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3632 "dhcp4_parser.cc"
    break;

  case 669: // $@109: %empty
#line 2331 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 670: // queue_type: "queue-type" $@109 ":" "constant string"
#line 2334 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3651 "dhcp4_parser.cc"
    break;

  case 671: // capacity: "capacity" ":" "integer"
#line 2340 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3661 "dhcp4_parser.cc"
    break;

  case 672: // $@110: %empty
#line 2346 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3670 "dhcp4_parser.cc"
    break;

  case 673: // arbitrary_map_entry: "constant string" $@110 ":" value
#line 2349 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3679 "dhcp4_parser.cc"
    break;

  case 674: // $@111: %empty
#line 2356 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3691 "dhcp4_parser.cc"
    break;

  case 675: // dhcp_ddns: "dhcp-ddns" $@111 ":" "{" dhcp_ddns_params "}"
#line 2362 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 676: // $@112: %empty
#line 2369 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 677: // sub_dhcp_ddns: "{" $@112 dhcp_ddns_params "}"
#line 2373 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 698: // enable_updates: "enable-updates" ":" "boolean"
#line 2403 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 699: // $@113: %empty
#line 2409 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 700: // server_ip: "server-ip" $@113 ":" "constant string"
#line 2412 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 701: // server_port: "server-port" ":" "integer"
#line 2418 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3761 "dhcp4_parser.cc"
    break;

  case 702: // $@114: %empty
#line 2424 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3770 "dhcp4_parser.cc"
    break;

  case 703: // sender_ip: "sender-ip" $@114 ":" "constant string"
#line 2427 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 704: // sender_port: "sender-port" ":" "integer"
#line 2433 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3790 "dhcp4_parser.cc"
    break;

  case 705: // max_queue_size: "max-queue-size" ":" "integer"
#line 2439 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3800 "dhcp4_parser.cc"
    break;

  case 706: // $@115: %empty
#line 2445 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3809 "dhcp4_parser.cc"
    break;

  case 707: // ncr_protocol: "ncr-protocol" $@115 ":" ncr_protocol_value
#line 2448 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3818 "dhcp4_parser.cc"
    break;

  case 708: // ncr_protocol_value: "udp"
#line 2454 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3824 "dhcp4_parser.cc"
    break;

  case 709: // ncr_protocol_value: "tcp"
#line 2455 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3830 "dhcp4_parser.cc"
    break;

  case 710: // $@116: %empty
#line 2458 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3839 "dhcp4_parser.cc"
    break;

  case 711: // ncr_format: "ncr-format" $@116 ":" "JSON"
#line 2461 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3849 "dhcp4_parser.cc"
    break;

  case 712: // $@117: %empty
#line 2468 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 713: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2471 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3868 "dhcp4_parser.cc"
    break;

  case 714: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2478 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3878 "dhcp4_parser.cc"
    break;

  case 715: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2485 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3888 "dhcp4_parser.cc"
    break;

  case 716: // $@118: %empty
#line 2492 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3897 "dhcp4_parser.cc"
    break;

  case 717: // dep_replace_client_name: "replace-client-name" $@118 ":" ddns_replace_client_name_value
#line 2495 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3906 "dhcp4_parser.cc"
    break;

  case 718: // $@119: %empty
#line 2501 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3915 "dhcp4_parser.cc"
    break;

  case 719: // dep_generated_prefix: "generated-prefix" $@119 ":" "constant string"
#line 2504 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3925 "dhcp4_parser.cc"
    break;

  case 720: // $@120: %empty
#line 2511 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3934 "dhcp4_parser.cc"
    break;

  case 721: // dep_hostname_char_set: "hostname-char-set" $@120 ":" "constant string"
#line 2514 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3944 "dhcp4_parser.cc"
    break;

  case 722: // $@121: %empty
#line 2521 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3953 "dhcp4_parser.cc"
    break;

  case 723: // dep_hostname_char_replacement: "hostname-char-replacement" $@121 ":" "constant string"
#line 2524 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3963 "dhcp4_parser.cc"
    break;

  case 724: // $@122: %empty
#line 2533 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3975 "dhcp4_parser.cc"
    break;

  case 725: // config_control: "config-control" $@122 ":" "{" config_control_params "}"
#line 2539 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3985 "dhcp4_parser.cc"
    break;

  case 726: // $@123: %empty
#line 2545 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3995 "dhcp4_parser.cc"
    break;

  case 727: // sub_config_control: "{" $@123 config_control_params "}"
#line 2549 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4004 "dhcp4_parser.cc"
    break;

  case 732: // $@124: %empty
#line 2564 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4016 "dhcp4_parser.cc"
    break;

  case 733: // config_databases: "config-databases" $@124 ":" "[" database_list "]"
#line 2570 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4025 "dhcp4_parser.cc"
    break;

  case 734: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2575 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4035 "dhcp4_parser.cc"
    break;

  case 735: // $@125: %empty
#line 2583 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4047 "dhcp4_parser.cc"
    break;

  case 736: // loggers: "loggers" $@125 ":" "[" loggers_entries "]"
#line 2589 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4056 "dhcp4_parser.cc"
    break;

  case 739: // $@126: %empty
#line 2601 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4066 "dhcp4_parser.cc"
    break;

  case 740: // logger_entry: "{" $@126 logger_params "}"
#line 2605 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4074 "dhcp4_parser.cc"
    break;

  case 750: // debuglevel: "debuglevel" ":" "integer"
#line 2622 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4084 "dhcp4_parser.cc"
    break;

  case 751: // $@127: %empty
#line 2628 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4093 "dhcp4_parser.cc"
    break;

  case 752: // severity: "severity" $@127 ":" "constant string"
#line 2631 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4103 "dhcp4_parser.cc"
    break;

  case 753: // $@128: %empty
#line 2637 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4115 "dhcp4_parser.cc"
    break;

  case 754: // output_options_list: "output_options" $@128 ":" "[" output_options_list_content "]"
#line 2643 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4124 "dhcp4_parser.cc"
    break;

  case 757: // $@129: %empty
#line 2652 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4134 "dhcp4_parser.cc"
    break;

  case 758: // output_entry: "{" $@129 output_params_list "}"
#line 2656 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4142 "dhcp4_parser.cc"
    break;

  case 766: // $@130: %empty
#line 2671 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4151 "dhcp4_parser.cc"
    break;

  case 767: // output: "output" $@130 ":" "constant string"
#line 2674 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4161 "dhcp4_parser.cc"
    break;

  case 768: // flush: "flush" ":" "boolean"
#line 2680 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4171 "dhcp4_parser.cc"
    break;

  case 769: // maxsize: "maxsize" ":" "integer"
#line 2686 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4181 "dhcp4_parser.cc"
    break;

  case 770: // maxver: "maxver" ":" "integer"
#line 2692 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4191 "dhcp4_parser.cc"
    break;

  case 771: // $@131: %empty
#line 2698 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4200 "dhcp4_parser.cc"
    break;

  case 772: // pattern: "pattern" $@131 ":" "constant string"
#line 2701 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4210 "dhcp4_parser.cc"
    break;

  case 773: // $@132: %empty
#line 2707 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4222 "dhcp4_parser.cc"
    break;

  case 774: // compatibility: "compatibility" $@132 ":" "{" compatibility_params "}"
#line 2713 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4231 "dhcp4_parser.cc"
    break;

  case 779: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2726 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4241 "dhcp4_parser.cc"
    break;


#line 4245 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -958;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     204,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,    31,    38,    48,    60,    74,    78,
      80,    90,    99,   114,   132,   157,   189,   200,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,    38,  -130,   107,   183,    67,   612,
     190,   247,    11,    89,   249,   -96,   418,   116,  -958,   129,
     177,   184,   213,   220,  -958,   221,  -958,  -958,  -958,   232,
     285,   291,  -958,  -958,  -958,  -958,  -958,  -958,   306,   317,
     327,   331,   334,   372,   385,   401,   402,   413,   414,  -958,
     415,   417,   419,   420,   421,  -958,  -958,  -958,   422,   423,
     425,  -958,  -958,  -958,   426,  -958,  -958,  -958,  -958,   430,
     431,   432,  -958,  -958,  -958,  -958,  -958,   433,  -958,  -958,
    -958,  -958,  -958,  -958,   434,  -958,  -958,   435,  -958,    56,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,   437,  -958,    85,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,   439,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,    92,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,    93,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,   266,   278,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   312,  -958,
    -958,   441,  -958,  -958,  -958,   442,  -958,  -958,   443,   446,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,   449,   455,  -958,  -958,  -958,  -958,   454,
     461,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,   100,  -958,  -958,  -958,   462,  -958,  -958,
     463,  -958,   465,   466,  -958,  -958,   467,   472,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,   110,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,   474,   128,  -958,  -958,  -958,  -958,    38,
      38,  -958,   264,   475,  -958,   477,   480,   481,   218,   284,
     288,   485,   491,   492,   493,   496,   498,   301,   302,   304,
     305,   307,   310,   322,   323,   328,   308,   311,   504,   313,
     321,   315,   325,   329,   523,   528,   530,   333,   335,   339,
     540,   543,   545,   348,   547,   551,   553,   557,   358,   361,
     362,   563,   565,   566,   567,   568,   384,   583,   584,   585,
     586,   587,   590,   391,   592,   593,  -958,   183,  -958,   594,
     595,   596,   397,    67,  -958,   598,   599,   600,   601,   602,
     603,   407,   604,   606,   608,   612,  -958,   610,   190,  -958,
     611,   613,   614,   616,   617,   618,   620,   621,  -958,   247,
    -958,   622,   623,   428,   624,   627,   628,   429,  -958,    89,
     630,   440,   445,  -958,   249,   631,   632,   -85,  -958,   447,
     633,   639,   444,   641,   450,   451,   651,   652,   453,   456,
     654,   655,   657,   658,   418,  -958,   663,   468,   116,  -958,
    -958,  -958,   664,   609,   662,   676,   677,  -958,  -958,  -958,
     470,   484,   495,   679,   693,   697,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,   502,  -958,  -958,
    -958,  -958,  -958,  -120,   503,   509,  -958,  -958,  -958,   700,
     706,   707,  -958,   709,   714,   521,   236,  -958,  -958,  -958,
     718,   719,   723,   724,   725,  -958,   728,   729,   730,   731,
     538,   539,  -958,   726,   735,  -958,   738,    52,   142,  -958,
    -958,   544,   546,   548,   739,   549,   550,  -958,   738,   552,
     741,  -958,   554,  -958,   738,   555,   556,   558,   559,   560,
     561,   562,  -958,   564,   569,  -958,   570,   571,   572,  -958,
    -958,   573,  -958,  -958,  -958,   574,   714,  -958,  -958,   575,
     576,  -958,   577,  -958,  -958,    15,   589,  -958,  -958,  -120,
     578,   579,   580,  -958,   747,  -958,  -958,    38,   183,   116,
      67,   722,  -958,  -958,  -958,   108,   108,   757,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,   759,   760,   761,
     762,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   -48,
     775,   776,   777,   242,    87,   121,   210,   418,  -958,  -958,
     778,  -143,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,   781,  -958,  -958,  -958,  -958,   173,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,   757,  -958,   138,
     181,   192,  -958,   235,  -958,  -958,  -958,  -958,  -958,  -958,
     750,   785,   786,   787,   788,  -958,  -958,  -958,  -958,   789,
     790,  -958,   791,   792,   793,   794,  -958,   270,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
     277,  -958,   795,   796,  -958,  -958,   797,   799,  -958,  -958,
     798,   802,  -958,  -958,   800,   804,  -958,  -958,   803,   805,
    -958,  -958,  -958,  -958,  -958,  -958,    36,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,   104,  -958,  -958,   806,   807,  -958,
    -958,   808,   812,  -958,   813,   814,   815,   816,   817,   818,
     298,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   819,   820,
     821,  -958,   299,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,   309,  -958,  -958,  -958,   822,  -958,
     823,  -958,  -958,  -958,   316,  -958,  -958,  -958,  -958,  -958,
     320,  -958,   214,  -958,   824,  -958,   324,  -958,  -958,   615,
    -958,   825,   826,  -958,  -958,  -958,  -958,   827,   828,  -958,
    -958,  -958,   829,   722,  -958,   832,   833,   834,   835,   638,
     607,   640,   626,   642,   837,   839,   841,   842,   645,   646,
     845,   648,   649,   650,   653,   108,  -958,  -958,   108,  -958,
     757,   612,  -958,   759,    89,  -958,   760,   249,  -958,   761,
    1228,  -958,   762,   -48,  -958,   115,   775,  -958,   247,  -958,
     776,   -96,  -958,   777,   656,   659,   660,   661,   665,   666,
     242,  -958,   667,   668,   670,    87,  -958,   848,   849,   121,
    -958,   669,   852,   672,   853,   210,  -958,  -958,    21,   778,
    -958,   671,  -143,  -958,  -958,   854,   856,   190,  -958,   781,
     860,  -958,  -958,   675,  -958,   330,   678,   680,   681,  -958,
    -958,  -958,  -958,  -958,   682,   683,   684,   685,  -958,  -958,
     332,  -958,  -958,  -958,  -958,  -958,   326,  -958,   346,  -958,
     857,  -958,   858,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,   382,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   865,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,   869,   875,  -958,  -958,  -958,  -958,  -958,   872,
    -958,   404,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,   686,   687,  -958,  -958,   688,  -958,
      38,  -958,  -958,   886,  -958,  -958,  -958,  -958,  -958,   405,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   690,   406,
    -958,   738,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  1228,  -958,   888,   689,  -958,   115,  -958,
    -958,  -958,  -958,  -958,  -958,   891,   694,   894,    21,  -958,
    -958,  -958,  -958,  -958,   698,  -958,  -958,   896,  -958,   701,
    -958,  -958,   900,  -958,  -958,   224,  -958,   -10,   900,  -958,
    -958,   905,   908,   913,  -958,   412,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,   914,   732,   737,   749,   929,   -10,  -958,
     767,  -958,  -958,  -958,   768,  -958,  -958,  -958
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   178,     9,   342,    11,   542,    13,
     567,    15,   467,    17,   475,    19,   512,    21,   307,    23,
     676,    25,   726,    27,    45,    39,     0,     0,     0,     0,
       0,   569,     0,   477,   514,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   724,   167,   193,     0,
       0,     0,   588,   590,   592,   191,   200,   202,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
       0,     0,     0,     0,     0,   146,   153,   155,     0,     0,
       0,   334,   465,   504,     0,   415,   555,   557,   408,     0,
       0,     0,   272,   616,   559,   299,   318,     0,   286,   645,
     658,   674,   159,   161,     0,   735,   773,     0,   125,     0,
      62,    64,    65,    66,    67,    68,   102,   103,   104,   105,
     106,    69,    97,   124,    86,    87,    88,   110,   111,   112,
     113,   114,   115,   116,   117,   108,   109,   118,   119,   120,
     122,    72,    73,    94,    74,    75,    76,   121,    80,    81,
      70,    99,   100,   101,    98,    71,    78,    79,    92,    93,
      95,    89,    90,    91,    77,    82,    83,    84,    85,    96,
     107,   123,   180,   182,   186,     0,   177,     0,   169,   171,
     172,   173,   174,   175,   176,   393,   395,   397,   534,   391,
     399,     0,   403,   401,   612,   390,   346,   347,   348,   349,
     350,   374,   375,   376,   377,   378,   364,   365,   379,   380,
     381,   382,   383,   384,   385,   386,   387,   388,   389,     0,
     344,   353,   369,   370,   371,   354,   356,   357,   360,   361,
     362,   359,   355,   351,   352,   372,   373,   358,   366,   367,
     368,   363,   553,   552,   548,   549,   547,     0,   544,   546,
     550,   551,   610,   598,   600,   604,   602,   608,   606,   594,
     587,   581,   585,   586,     0,   570,   571,   582,   583,   584,
     578,   573,   579,   575,   576,   577,   580,   574,     0,   494,
     247,     0,   498,   496,   501,     0,   490,   491,     0,   478,
     479,   481,   493,   482,   483,   484,   500,   485,   486,   487,
     488,   489,   528,     0,     0,   526,   527,   530,   531,     0,
     515,   516,   518,   519,   520,   521,   522,   523,   524,   525,
     314,   316,   311,     0,   309,   312,   313,     0,   712,   699,
       0,   702,     0,     0,   706,   710,     0,     0,   716,   718,
     720,   722,   697,   695,   696,     0,   678,   680,   681,   682,
     683,   684,   685,   686,   687,   692,   688,   689,   690,   691,
     693,   694,   732,     0,     0,   728,   730,   731,    44,     0,
       0,    37,     0,     0,    57,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    55,     0,    61,     0,
       0,     0,     0,     0,   179,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   343,     0,     0,   543,
       0,     0,     0,     0,     0,     0,     0,     0,   568,     0,
     468,     0,     0,     0,     0,     0,     0,     0,   476,     0,
       0,     0,     0,   513,     0,     0,     0,     0,   308,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   677,     0,     0,     0,   727,
      48,    41,     0,     0,     0,     0,     0,   140,   141,   142,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,     0,   164,   165,
     143,   144,   145,     0,     0,     0,   157,   158,   163,     0,
       0,     0,   139,     0,     0,     0,     0,   405,   406,   407,
       0,     0,     0,     0,     0,   644,     0,     0,     0,     0,
       0,     0,   166,     0,     0,    63,     0,     0,     0,   190,
     170,     0,     0,     0,     0,     0,     0,   414,     0,     0,
       0,   345,     0,   545,     0,     0,     0,     0,     0,     0,
       0,     0,   572,     0,     0,   492,     0,     0,     0,   503,
     480,     0,   532,   533,   517,     0,     0,   310,   698,     0,
       0,   701,     0,   704,   705,     0,     0,   714,   715,     0,
       0,     0,     0,   679,     0,   734,   729,     0,     0,     0,
       0,     0,   589,   591,   593,     0,     0,   204,   138,   148,
     149,   150,   151,   152,   147,   154,   156,   336,   469,   506,
     417,    38,   556,   558,   410,   411,   412,   413,   409,     0,
       0,   561,   301,     0,     0,     0,     0,     0,   160,   162,
       0,     0,    49,   181,   184,   185,   183,   188,   189,   187,
     394,   396,   398,   536,   392,   400,   404,   402,     0,   554,
     611,   599,   601,   605,   603,   609,   607,   595,   495,   248,
     499,   497,   502,   529,   315,   317,   713,   700,   703,   708,
     709,   707,   711,   717,   719,   721,   723,   204,    42,     0,
       0,     0,   198,     0,   195,   197,   234,   240,   242,   244,
       0,     0,     0,     0,     0,   256,   258,   260,   262,     0,
       0,   266,     0,     0,     0,     0,   233,     0,   210,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   226,
     227,   228,   222,   229,   230,   231,   223,   224,   225,   232,
       0,   208,     0,   205,   206,   340,     0,   337,   338,   473,
       0,   470,   471,   510,     0,   507,   508,   421,     0,   418,
     419,   281,   282,   283,   284,   285,     0,   274,   276,   277,
     278,   279,   280,   620,     0,   618,   565,     0,   562,   563,
     305,     0,   302,   303,     0,     0,     0,     0,     0,     0,
       0,   320,   322,   323,   324,   325,   326,   327,     0,     0,
       0,   295,     0,   288,   290,   291,   292,   293,   294,   654,
     656,   653,   651,   652,     0,   647,   649,   650,     0,   669,
       0,   672,   665,   666,     0,   660,   662,   663,   664,   667,
       0,   739,     0,   737,     0,   778,     0,   775,   777,    51,
     540,     0,   537,   538,   596,   614,   615,     0,     0,    59,
     725,   168,     0,     0,   194,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   192,   201,     0,   203,
       0,     0,   335,     0,   477,   466,     0,   514,   505,     0,
       0,   416,     0,     0,   273,   622,     0,   617,   569,   560,
       0,     0,   300,     0,     0,     0,     0,     0,     0,     0,
       0,   319,     0,     0,     0,     0,   287,     0,     0,     0,
     646,     0,     0,     0,     0,     0,   659,   675,     0,     0,
     736,     0,     0,   774,    53,     0,    52,     0,   535,     0,
       0,   613,   733,     0,   196,     0,     0,     0,     0,   246,
     249,   250,   251,   252,     0,     0,     0,     0,   264,   265,
       0,   253,   254,   255,   271,   211,     0,   207,     0,   339,
       0,   472,     0,   509,   464,   443,   444,   445,   428,   429,
     448,   449,   450,   451,   452,   431,   432,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   425,   426,
     427,   441,   442,   438,   439,   440,   437,     0,   423,   430,
     446,   447,   433,   434,   435,   436,   420,   275,   641,     0,
     636,   637,   638,   639,   640,   629,   630,   634,   635,   631,
     632,   633,     0,   623,   624,   626,   627,   628,   619,     0,
     564,     0,   304,   328,   329,   330,   331,   332,   333,   321,
     296,   297,   298,   289,     0,     0,   648,   668,     0,   671,
       0,   661,   753,     0,   751,   749,   743,   747,   748,     0,
     741,   745,   746,   744,   738,   779,   776,    50,     0,     0,
     539,     0,   199,   236,   237,   238,   239,   235,   241,   243,
     245,   257,   259,   261,   263,   268,   269,   270,   267,   209,
     341,   474,   511,     0,   422,     0,     0,   621,     0,   566,
     306,   655,   657,   670,   673,     0,     0,     0,     0,   740,
      54,   541,   597,   424,     0,   643,   625,     0,   750,     0,
     742,   642,     0,   752,   757,     0,   755,     0,     0,   754,
     766,     0,     0,     0,   771,     0,   759,   761,   762,   763,
     764,   765,   756,     0,     0,     0,     0,     0,     0,   758,
       0,   768,   769,   770,     0,   760,   767,   772
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,   -54,  -958,  -566,  -958,   144,
    -958,  -958,  -958,  -958,  -958,  -958,  -607,  -958,  -958,  -958,
     -67,  -958,  -958,  -958,  -958,  -958,  -958,   154,   499,     4,
      10,    23,   -40,   -23,   -12,    22,    25,    29,    33,  -958,
    -958,  -958,  -958,  -958,    35,    40,    43,    45,    46,    47,
    -958,   292,    50,  -958,    51,  -958,    53,    57,    58,  -958,
      61,  -958,    63,  -958,  -958,  -958,  -958,  -958,   297,   489,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,    55,  -958,  -958,  -958,
    -958,  -958,  -958,   222,  -958,    42,  -958,  -674,    77,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,   -33,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,    71,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,    41,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,    54,  -958,  -958,  -958,    62,   514,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,    59,  -958,  -958,  -958,  -958,
    -958,  -958,  -957,  -958,  -958,  -958,    79,  -958,  -958,  -958,
      84,   581,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -955,  -958,   -65,  -958,    70,  -958,    64,    65,    68,    69,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,    75,  -958,  -958,
    -137,   -46,  -958,  -958,  -958,  -958,  -958,    82,  -958,  -958,
    -958,    86,  -958,   532,  -958,   -63,  -958,  -958,  -958,  -958,
    -958,   -42,  -958,  -958,  -958,  -958,  -958,   -35,  -958,  -958,
    -958,    83,  -958,  -958,  -958,    88,  -958,   529,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,    37,
    -958,  -958,  -958,    44,   582,  -958,  -958,   -51,  -958,    -8,
    -958,   -39,  -958,  -958,  -958,    91,  -958,  -958,  -958,    76,
    -958,   588,   -55,  -958,   -15,  -958,     3,  -958,   319,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -946,  -958,  -958,  -958,
    -958,  -958,    94,  -958,  -958,  -958,  -129,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,    66,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,    72,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,   341,   516,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,   383,   515,  -958,  -958,  -958,
    -958,  -958,  -958,    73,  -958,  -958,  -134,  -958,  -958,  -958,
    -958,  -958,  -958,  -152,  -958,  -958,  -171,  -958,  -958,  -958,
    -958,  -958,  -958,  -958,  -958,  -958,  -958,    81,  -958
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   702,
      82,    83,    39,    64,    79,    80,   723,   919,  1015,  1016,
     796,    41,    66,    85,   413,    43,    67,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   438,   163,   164,   165,   166,   167,   168,   169,   170,
     444,   694,   171,   445,   172,   446,   173,   174,   175,   471,
     176,   472,   177,   178,   179,   180,   181,   416,   217,   218,
      45,    68,   219,   479,   220,   480,   726,   221,   481,   729,
     222,   182,   424,   183,   417,   773,   774,   775,   932,   184,
     425,   185,   426,   822,   823,   824,   958,   797,   798,   799,
     935,  1167,   800,   936,   801,   937,   802,   938,   803,   804,
     512,   805,   806,   807,   808,   809,   810,   811,   812,   944,
     813,   945,   814,   946,   815,   947,   816,   817,   818,   950,
    1178,   819,   186,   461,   846,   847,   848,   849,   850,   851,
     852,   187,   467,   882,   883,   884,   885,   886,   188,   464,
     861,   862,   863,   981,    59,    75,   363,   364,   365,   525,
     366,   526,   189,   465,   870,   871,   872,   873,   874,   875,
     876,   877,   190,   450,   826,   827,   828,   961,    47,    69,
     259,   260,   261,   489,   262,   485,   263,   486,   264,   487,
     265,   490,   266,   493,   267,   492,   191,   192,   193,   194,
     457,   708,   272,   195,   454,   838,   839,   840,   970,  1087,
    1088,   196,   451,    53,    72,   830,   831,   832,   964,    55,
      73,   328,   329,   330,   331,   332,   333,   334,   511,   335,
     515,   336,   514,   337,   338,   516,   339,   197,   452,   834,
     835,   836,   967,    57,    74,   349,   350,   351,   352,   353,
     520,   354,   355,   356,   357,   274,   488,   921,   922,   923,
    1017,    49,    70,   287,   288,   289,   497,   198,   455,   199,
     456,   200,   463,   857,   858,   859,   978,    51,    71,   304,
     305,   306,   201,   421,   202,   422,   203,   423,   310,   507,
     926,  1020,   311,   501,   312,   502,   313,   504,   314,   503,
     315,   506,   316,   505,   317,   500,   281,   494,   927,   204,
     462,   854,   855,   975,  1112,  1113,  1114,  1115,  1116,  1185,
    1117,   205,   206,   468,   894,   895,   896,   997,   897,   998,
     207,   469,   904,   905,   906,   907,  1002,   908,   909,  1004,
     208,   470,    61,    76,   385,   386,   387,   388,   531,   389,
     390,   533,   391,   392,   393,   536,   761,   394,   537,   395,
     530,   396,   397,   398,   540,   399,   541,   400,   542,   401,
     543,   209,   415,    63,    77,   404,   405,   406,   546,   407,
     210,   474,   912,   913,  1008,  1149,  1150,  1151,  1152,  1197,
    1153,  1195,  1215,  1216,  1217,  1225,  1226,  1227,  1233,  1228,
    1229,  1230,  1231,  1237,   211,   475,   916,   917,   918
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     148,   216,   235,   283,   300,   284,   326,   345,   362,   382,
      78,   347,   820,  1079,   278,  1080,   307,   223,   275,   290,
     302,   736,   340,   358,  1095,   383,   318,   740,   701,   239,
     277,    28,   348,   759,   273,   286,   301,   360,   361,   973,
     327,   346,   974,    29,   914,    30,   240,    31,   360,   361,
     689,   690,   691,   692,   279,    40,   308,   241,   147,   477,
     224,   276,   291,   303,   478,   341,   359,    42,   384,   724,
     725,    81,   280,   236,   309,   841,   842,   843,   844,   237,
     845,    44,   212,   213,   693,    46,   214,    48,   483,   215,
     701,   242,   238,   484,   243,   495,   498,    50,   244,   122,
     496,   499,   245,   527,   246,   147,    52,   976,   528,   247,
     977,   320,   248,   544,   249,   250,   251,    84,   545,   252,
     253,    54,   254,   319,   126,   127,   255,   256,   402,   403,
     257,   548,   258,   268,   269,   408,   549,   270,   271,    56,
     285,   477,   776,    92,    93,    94,   929,   777,   778,   779,
     780,   781,   782,   783,   784,   785,   786,   787,   788,   789,
     790,   791,   727,   728,    58,   792,   793,   794,   795,  1220,
     126,   127,  1221,  1222,  1223,  1224,    98,    99,   100,   320,
     409,   321,   322,   760,   548,   323,   324,   325,   410,   930,
     126,   127,   126,   127,    86,   483,    60,    87,   320,  1142,
     931,  1143,  1144,   122,   123,   320,    88,    62,    89,    90,
      91,    92,    93,    94,    95,    96,    97,  1009,   126,   127,
    1010,   411,   147,   412,   126,   127,  1079,  1218,  1080,   414,
    1219,   878,   879,   880,  1098,  1099,   418,  1095,   933,    32,
      33,    34,    35,   934,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   147,   889,
     890,   122,   123,   955,   508,    92,    93,    94,   956,   123,
     955,   509,   124,   125,  1046,   957,   126,   127,   147,   419,
     147,   128,   282,   126,   127,   420,   129,   130,   131,   132,
     133,   990,   995,   299,   924,   134,   991,   996,   232,   147,
     427,   233,   999,   126,   127,   135,   147,  1000,   136,  1005,
     510,   428,   147,   544,  1006,   137,   138,  1012,  1007,   955,
     139,   429,  1013,   140,  1179,   430,   123,   141,   431,   320,
     342,   321,   322,   343,   344,   704,   705,   706,   707,   495,
     126,   127,   126,   127,  1180,   550,   551,   142,   143,   144,
     145,   898,   899,   900,   292,  1163,  1164,  1165,  1166,   146,
     293,   294,   295,   296,   297,   298,   432,   299,   864,   865,
     866,   867,   868,   869,   147,  1183,  1175,  1176,  1177,   433,
    1184,   147,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   434,   435,   527,  1198,   498,
     148,   901,  1190,  1199,  1201,  1238,   216,   436,   437,   439,
    1239,   440,   557,   441,   442,   443,   447,   448,   235,   449,
     453,   283,   223,   284,   458,   459,   460,   466,   473,   476,
     278,   482,   300,   491,   275,   513,   517,   290,   147,   519,
     147,   518,   326,   521,   307,   239,   277,   345,   302,   522,
     273,   347,   523,   286,   524,   552,   529,   532,   340,   534,
     535,   538,   240,   358,   301,   224,   539,   382,   547,   553,
     279,   554,   348,   241,   555,   556,   327,   276,   558,   560,
     291,   346,   559,   383,   308,   561,   562,   563,   280,   236,
     564,   303,   565,   566,   567,   237,   568,   569,   577,   570,
     575,   341,   309,   576,   571,   578,   359,   242,   238,   580,
     243,   126,   127,   579,   244,   572,   573,   583,   245,   581,
     246,   574,   584,   582,   585,   247,   384,   586,   248,   587,
     249,   250,   251,   588,   589,   252,   253,   590,   254,   591,
     592,   593,   255,   256,  1202,   594,   257,   595,   258,   268,
     269,   596,   597,   270,   271,   598,   599,   600,   285,   601,
     602,   603,   604,   367,   368,   369,   370,   371,   372,   373,
     374,   375,   376,   377,   378,   379,   605,   606,   607,   608,
     609,   610,   380,   381,   611,   612,   613,   614,   616,   617,
     618,   619,   621,   622,   623,   624,   625,   626,   628,   627,
     629,   148,   630,   216,   632,   634,   678,   635,   636,   147,
     637,   638,   639,   768,   640,   641,   643,   644,   646,   223,
     645,   647,   648,   649,   651,   655,   656,   659,    90,    91,
      92,    93,    94,   660,   652,   662,   661,   881,   891,   653,
     382,   658,   663,   664,   915,   665,   666,   667,   669,   670,
     668,   671,   672,   887,   892,   902,   383,   674,   677,   679,
     675,   682,   224,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   680,   681,   683,   685,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   684,   225,   226,   227,
     686,   123,   687,   688,   695,   697,   888,   893,   903,   384,
     696,   698,   699,   228,   700,   126,   127,   229,   230,   231,
     128,    30,   703,   709,   710,   129,   130,   131,   711,   712,
     232,   720,   713,   233,   134,   714,   715,   716,   717,   718,
     719,   234,   721,   722,   733,   730,   772,   731,   738,   732,
     734,   735,   767,   737,   939,   739,   741,   742,   762,   743,
     744,   745,   746,   747,   821,   748,   825,   829,   833,   837,
     749,   750,   751,   752,   753,   754,   756,   757,   758,   764,
     765,   766,   853,   856,   860,   911,   142,   143,   920,   940,
     941,   942,   943,   948,   949,   951,   952,   953,   954,   960,
     755,   959,   963,   962,   965,   966,   968,   969,   972,   971,
     980,  1030,   979,   147,   982,   983,  1014,   984,   985,   986,
     987,   988,   989,   992,   993,   994,  1001,  1003,  1011,  1019,
    1032,  1018,   769,  1023,  1022,  1021,  1025,  1026,  1027,  1028,
    1029,  1034,  1031,  1035,  1033,  1036,  1037,  1038,  1039,  1040,
    1041,  1042,  1134,  1135,  1043,  1044,  1138,  1140,  1123,  1158,
    1157,  1124,  1125,  1126,  1161,  1181,  1182,  1127,  1128,  1186,
    1131,  1130,  1132,  1137,  1139,  1155,  1162,  1187,  1188,  1168,
    1189,  1169,  1170,  1171,  1172,  1173,  1174,  1191,  1192,  1193,
    1196,  1200,  1204,  1205,   235,  1207,  1208,   326,  1209,  1211,
     345,  1212,  1213,  1054,   347,  1081,   278,  1214,  1100,  1234,
     275,   300,  1235,   340,   362,  1092,   358,  1236,  1240,  1090,
    1109,   239,   277,   307,  1107,   348,   273,   302,   881,  1105,
    1058,   327,   891,  1244,   346,  1089,  1241,  1078,   240,  1242,
    1106,  1145,  1104,   301,   887,   915,   279,  1059,   892,   241,
     283,  1243,   284,   276,   902,  1093,   341,  1147,  1060,   359,
    1110,   763,  1091,   308,   280,   236,   290,  1108,  1246,  1247,
     303,   237,   620,  1094,  1055,  1146,   615,   771,  1111,  1101,
    1056,   309,   286,   242,   238,  1102,   243,   888,  1024,   928,
     244,   893,  1061,  1057,   245,  1062,   246,   903,  1103,  1063,
    1148,   247,  1047,  1064,   248,  1065,   249,   250,   251,   291,
    1066,   252,   253,  1067,   254,  1068,  1069,  1070,   255,   256,
    1071,  1072,   257,  1073,   258,   268,   269,  1074,  1075,   270,
     271,  1076,  1045,  1077,  1083,  1084,  1133,  1122,  1085,  1086,
    1082,   657,  1049,  1121,  1097,  1048,  1203,  1096,  1051,  1129,
    1050,   650,  1053,   654,  1119,  1052,  1160,   925,   910,  1206,
     673,  1159,   770,   676,  1210,  1136,  1232,  1245,     0,     0,
    1118,  1120,     0,     0,     0,     0,   631,  1141,     0,     0,
     633,     0,  1154,     0,     0,     0,  1194,   285,     0,     0,
       0,     0,     0,  1156,     0,     0,     0,   642,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1054,     0,  1081,     0,
       0,  1100,     0,     0,     0,     0,     0,     0,  1092,     0,
       0,  1145,  1090,  1109,     0,     0,     0,  1107,     0,     0,
       0,     0,  1105,  1058,     0,     0,     0,  1147,  1089,     0,
    1078,     0,     0,  1106,     0,  1104,     0,     0,     0,     0,
    1059,     0,     0,     0,     0,  1146,     0,     0,  1093,     0,
       0,  1060,     0,  1110,     0,  1091,     0,     0,     0,     0,
    1108,     0,     0,     0,     0,     0,  1094,  1055,     0,     0,
    1148,  1111,  1101,  1056,     0,     0,     0,     0,  1102,     0,
       0,     0,     0,     0,     0,  1061,  1057,     0,  1062,     0,
       0,  1103,  1063,     0,     0,     0,  1064,     0,  1065,     0,
       0,     0,     0,  1066,     0,     0,  1067,     0,  1068,  1069,
    1070,     0,     0,  1071,  1072,     0,  1073,     0,     0,     0,
    1074,  1075,     0,     0,  1076,     0,  1077,  1083,  1084,     0,
       0,  1085,  1086,  1082,    90,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,     0,
       0,     0,     0,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,     0,     0,     0,     0,   123,   320,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,     0,   230,     0,   128,     0,     0,     0,
       0,   129,   130,   131,     0,     0,   232,     0,     0,   233,
       0,     0,     0,     0,     0,     0,     0,   234,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   142,   143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   147
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,    74,   686,   970,    69,   970,    71,    68,    69,    70,
      71,   628,    73,    74,   970,    76,    72,   634,   594,    69,
      69,     0,    74,    18,    69,    70,    71,   133,   134,     3,
      73,    74,     6,     5,   187,     7,    69,     9,   133,   134,
     170,   171,   172,   173,    69,     7,    71,    69,   201,     3,
      68,    69,    70,    71,     8,    73,    74,     7,    76,    17,
      18,   201,    69,    69,    71,   123,   124,   125,   126,    69,
     128,     7,    15,    16,   204,     7,    19,     7,     3,    22,
     656,    69,    69,     8,    69,     3,     3,     7,    69,    88,
       8,     8,    69,     3,    69,   201,     7,     3,     8,    69,
       6,    90,    69,     3,    69,    69,    69,    10,     8,    69,
      69,     7,    69,    34,   103,   104,    69,    69,    12,    13,
      69,     3,    69,    69,    69,     6,     8,    69,    69,     7,
      70,     3,    34,    28,    29,    30,     8,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    20,    21,     7,    57,    58,    59,    60,   179,
     103,   104,   182,   183,   184,   185,    61,    62,    63,    90,
       3,    92,    93,   168,     3,    96,    97,    98,     4,     8,
     103,   104,   103,   104,    11,     3,     7,    14,    90,   178,
       8,   180,   181,    88,    89,    90,    23,     7,    25,    26,
      27,    28,    29,    30,    31,    32,    33,     3,   103,   104,
       6,     8,   201,     3,   103,   104,  1183,     3,  1183,     8,
       6,   144,   145,   146,   119,   120,     4,  1183,     3,   201,
     202,   203,   204,     8,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,   201,   148,
     149,    88,    89,     3,     8,    28,    29,    30,     8,    89,
       3,     3,    99,   100,   958,     8,   103,   104,   201,     4,
     201,   108,   102,   103,   104,     4,   113,   114,   115,   116,
     117,     3,     3,   130,   131,   122,     8,     8,   118,   201,
       4,   121,     3,   103,   104,   132,   201,     8,   135,     3,
       8,     4,   201,     3,     8,   142,   143,     3,     8,     3,
     147,     4,     8,   150,     8,     4,    89,   154,     4,    90,
      91,    92,    93,    94,    95,   109,   110,   111,   112,     3,
     103,   104,   103,   104,     8,   409,   410,   174,   175,   176,
     177,   151,   152,   153,   117,    35,    36,    37,    38,   186,
     123,   124,   125,   126,   127,   128,     4,   130,   136,   137,
     138,   139,   140,   141,   201,     3,    54,    55,    56,     4,
       8,   201,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,     4,     4,     3,     3,     3,
     477,   201,     8,     8,     8,     3,   483,     4,     4,     4,
       8,     4,   204,     4,     4,     4,     4,     4,   495,     4,
       4,   498,   483,   498,     4,     4,     4,     4,     4,     4,
     495,     4,   509,     4,   495,     4,     4,   498,   201,     3,
     201,     8,   519,     4,   509,   495,   495,   524,   509,     4,
     495,   524,     8,   498,     3,   201,     4,     4,   519,     4,
       4,     4,   495,   524,   509,   483,     4,   544,     4,     4,
     495,     4,   524,   495,     4,     4,   519,   495,   204,     4,
     498,   524,   204,   544,   509,     4,     4,     4,   495,   495,
       4,   509,     4,   202,   202,   495,   202,   202,     4,   202,
     202,   519,   509,   202,   204,   202,   524,   495,   495,   204,
     495,   103,   104,   202,   495,   203,   203,     4,   495,   204,
     495,   203,     4,   204,     4,   495,   544,   204,   495,   204,
     495,   495,   495,   204,     4,   495,   495,     4,   495,     4,
     202,     4,   495,   495,  1161,     4,   495,     4,   495,   495,
     495,     4,   204,   495,   495,   204,   204,     4,   498,     4,
       4,     4,     4,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   202,     4,     4,     4,
       4,     4,   174,   175,     4,   204,     4,     4,     4,     4,
       4,   204,     4,     4,     4,     4,     4,     4,     4,   202,
       4,   678,     4,   680,     4,     4,     7,     4,     4,   201,
       4,     4,     4,   677,     4,     4,     4,     4,     4,   680,
     202,     4,     4,   204,     4,     4,     4,     4,    26,    27,
      28,    29,    30,     4,   204,     4,   202,   714,   715,   204,
     717,   204,   202,   202,   721,     4,     4,   204,     4,     4,
     204,     4,     4,   714,   715,   716,   717,     4,     4,     7,
     202,   201,   680,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,     7,     7,   201,     7,    75,    76,    77,
      78,    79,    80,    81,    82,    83,   201,    85,    86,    87,
       7,    89,     5,   201,   201,     5,   714,   715,   716,   717,
     201,     5,     5,   101,     5,   103,   104,   105,   106,   107,
     108,     7,   201,     5,     5,   113,   114,   115,     5,     5,
     118,     5,     7,   121,   122,     7,     7,     7,     7,   201,
     201,   129,     7,     5,     5,   201,    24,   201,     7,   201,
     201,   201,     5,   201,     4,   201,   201,   201,   169,   201,
     201,   201,   201,   201,     7,   201,     7,     7,     7,     7,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,     7,     7,     7,     7,   174,   175,     7,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     656,     6,     3,     6,     6,     3,     6,     3,     3,     6,
       3,   204,     6,   201,     6,     3,   201,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     204,     6,   678,     4,     6,     8,     4,     4,     4,     4,
     202,     4,   202,     4,   202,     4,     4,   202,   202,     4,
     202,   202,     4,     4,   204,   202,     4,     4,   202,     3,
       6,   202,   202,   202,     4,     8,     8,   202,   202,     4,
     202,   204,   202,   204,   202,   204,   201,     8,     3,   201,
       8,   201,   201,   201,   201,   201,   201,   201,   201,   201,
       4,   201,     4,   204,   961,     4,   202,   964,     4,   201,
     967,     5,   201,   970,   967,   970,   961,     7,   975,     4,
     961,   978,     4,   964,   981,   970,   967,     4,     4,   970,
     975,   961,   961,   978,   975,   967,   961,   978,   995,   975,
     970,   964,   999,     4,   967,   970,   204,   970,   961,   202,
     975,  1008,   975,   978,   995,  1012,   961,   970,   999,   961,
    1017,   202,  1017,   961,  1005,   970,   964,  1008,   970,   967,
     975,   669,   970,   978,   961,   961,  1017,   975,   201,   201,
     978,   961,   483,   970,   970,  1008,   477,   680,   975,   975,
     970,   978,  1017,   961,   961,   975,   961,   995,   933,   767,
     961,   999,   970,   970,   961,   970,   961,  1005,   975,   970,
    1008,   961,   960,   970,   961,   970,   961,   961,   961,  1017,
     970,   961,   961,   970,   961,   970,   970,   970,   961,   961,
     970,   970,   961,   970,   961,   961,   961,   970,   970,   961,
     961,   970,   955,   970,   970,   970,   995,   983,   970,   970,
     970,   527,   963,   981,   973,   961,  1183,   972,   966,   990,
     964,   519,   969,   524,   978,   967,  1019,   738,   717,  1188,
     544,  1017,   679,   548,  1198,   999,  1218,  1238,    -1,    -1,
     976,   980,    -1,    -1,    -1,    -1,   495,  1005,    -1,    -1,
     498,    -1,  1009,    -1,    -1,    -1,  1140,  1017,    -1,    -1,
      -1,    -1,    -1,  1012,    -1,    -1,    -1,   509,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1183,    -1,  1183,    -1,
      -1,  1188,    -1,    -1,    -1,    -1,    -1,    -1,  1183,    -1,
      -1,  1198,  1183,  1188,    -1,    -1,    -1,  1188,    -1,    -1,
      -1,    -1,  1188,  1183,    -1,    -1,    -1,  1198,  1183,    -1,
    1183,    -1,    -1,  1188,    -1,  1188,    -1,    -1,    -1,    -1,
    1183,    -1,    -1,    -1,    -1,  1198,    -1,    -1,  1183,    -1,
      -1,  1183,    -1,  1188,    -1,  1183,    -1,    -1,    -1,    -1,
    1188,    -1,    -1,    -1,    -1,    -1,  1183,  1183,    -1,    -1,
    1198,  1188,  1188,  1183,    -1,    -1,    -1,    -1,  1188,    -1,
      -1,    -1,    -1,    -1,    -1,  1183,  1183,    -1,  1183,    -1,
      -1,  1188,  1183,    -1,    -1,    -1,  1183,    -1,  1183,    -1,
      -1,    -1,    -1,  1183,    -1,    -1,  1183,    -1,  1183,  1183,
    1183,    -1,    -1,  1183,  1183,    -1,  1183,    -1,    -1,    -1,
    1183,  1183,    -1,    -1,  1183,    -1,  1183,  1183,  1183,    -1,
      -1,  1183,  1183,  1183,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    -1,    -1,    -1,    -1,    89,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   103,   104,    -1,   106,    -1,   108,    -1,    -1,    -1,
      -1,   113,   114,   115,    -1,    -1,   118,    -1,    -1,   121,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   201
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,     0,     5,
       7,     9,   201,   202,   203,   204,   220,   221,   222,   227,
       7,   236,     7,   240,     7,   285,     7,   393,     7,   476,
       7,   492,     7,   428,     7,   434,     7,   458,     7,   369,
       7,   557,     7,   588,   228,   223,   237,   241,   286,   394,
     477,   493,   429,   435,   459,   370,   558,   589,   220,   229,
     230,   201,   225,   226,    10,   238,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    88,    89,    99,   100,   103,   104,   108,   113,
     114,   115,   116,   117,   122,   132,   135,   142,   143,   147,
     150,   154,   174,   175,   176,   177,   186,   201,   235,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   257,   258,   259,   260,   261,   262,   263,
     264,   267,   269,   271,   272,   273,   275,   277,   278,   279,
     280,   281,   296,   298,   304,   306,   347,   356,   363,   377,
     387,   411,   412,   413,   414,   418,   426,   452,   482,   484,
     486,   497,   499,   501,   524,   536,   537,   545,   555,   586,
     595,   619,    15,    16,    19,    22,   235,   283,   284,   287,
     289,   292,   295,   482,   484,    85,    86,    87,   101,   105,
     106,   107,   118,   121,   129,   235,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   259,   260,   261,   262,
     263,   264,   267,   269,   271,   272,   273,   275,   277,   395,
     396,   397,   399,   401,   403,   405,   407,   409,   411,   412,
     413,   414,   417,   452,   470,   482,   484,   486,   497,   499,
     501,   521,   102,   235,   407,   409,   452,   478,   479,   480,
     482,   484,   117,   123,   124,   125,   126,   127,   128,   130,
     235,   452,   482,   484,   494,   495,   496,   497,   499,   501,
     503,   507,   509,   511,   513,   515,   517,   519,   426,    34,
      90,    92,    93,    96,    97,    98,   235,   324,   436,   437,
     438,   439,   440,   441,   442,   444,   446,   448,   449,   451,
     482,   484,    91,    94,    95,   235,   324,   440,   446,   460,
     461,   462,   463,   464,   466,   467,   468,   469,   482,   484,
     133,   134,   235,   371,   372,   373,   375,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     174,   175,   235,   482,   484,   559,   560,   561,   562,   564,
     565,   567,   568,   569,   572,   574,   576,   577,   578,   580,
     582,   584,    12,    13,   590,   591,   592,   594,     6,     3,
       4,     8,     3,   239,     8,   587,   282,   299,     4,     4,
       4,   498,   500,   502,   297,   305,   307,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   256,     4,
       4,     4,     4,     4,   265,   268,   270,     4,     4,     4,
     388,   427,   453,     4,   419,   483,   485,   415,     4,     4,
       4,   348,   525,   487,   364,   378,     4,   357,   538,   546,
     556,   274,   276,     4,   596,   620,     4,     3,     8,   288,
     290,   293,     4,     3,     8,   400,   402,   404,   471,   398,
     406,     4,   410,   408,   522,     3,     8,   481,     3,     8,
     520,   508,   510,   514,   512,   518,   516,   504,     8,     3,
       8,   443,   325,     4,   447,   445,   450,     4,     8,     3,
     465,     4,     4,     8,     3,   374,   376,     3,     8,     4,
     575,   563,     4,   566,     4,     4,   570,   573,     4,     4,
     579,   581,   583,   585,     3,     8,   593,     4,     3,     8,
     220,   220,   201,     4,     4,     4,     4,   204,   204,   204,
       4,     4,     4,     4,     4,     4,   202,   202,   202,   202,
     202,   204,   203,   203,   203,   202,   202,     4,   202,   202,
     204,   204,   204,     4,     4,     4,   204,   204,   204,     4,
       4,     4,   202,     4,     4,     4,     4,   204,   204,   204,
       4,     4,     4,     4,     4,   202,     4,     4,     4,     4,
       4,     4,   204,     4,     4,   243,     4,     4,     4,   204,
     284,     4,     4,     4,     4,     4,     4,   202,     4,     4,
       4,   396,     4,   479,     4,     4,     4,     4,     4,     4,
       4,     4,   496,     4,     4,   202,     4,     4,     4,   204,
     438,     4,   204,   204,   462,     4,     4,   372,   204,     4,
       4,   202,     4,   202,   202,     4,     4,   204,   204,     4,
       4,     4,     4,   560,     4,   202,   591,     4,     7,     7,
       7,     7,   201,   201,   201,     7,     7,     5,   201,   170,
     171,   172,   173,   204,   266,   201,   201,     5,     5,     5,
       5,   222,   224,   201,   109,   110,   111,   112,   416,     5,
       5,     5,     5,     7,     7,     7,     7,     7,   201,   201,
       5,     7,     5,   231,    17,    18,   291,    20,    21,   294,
     201,   201,   201,     5,   201,   201,   231,   201,     7,   201,
     231,   201,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   224,   201,   201,   201,    18,
     168,   571,   169,   266,   201,   201,   201,     5,   220,   242,
     590,   283,    24,   300,   301,   302,    34,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    57,    58,    59,    60,   235,   312,   313,   314,
     317,   319,   321,   323,   324,   326,   327,   328,   329,   330,
     331,   332,   333,   335,   337,   339,   341,   342,   343,   346,
     312,     7,   308,   309,   310,     7,   389,   390,   391,     7,
     430,   431,   432,     7,   454,   455,   456,     7,   420,   421,
     422,   123,   124,   125,   126,   128,   349,   350,   351,   352,
     353,   354,   355,     7,   526,   527,     7,   488,   489,   490,
       7,   365,   366,   367,   136,   137,   138,   139,   140,   141,
     379,   380,   381,   382,   383,   384,   385,   386,   144,   145,
     146,   235,   358,   359,   360,   361,   362,   482,   484,   148,
     149,   235,   482,   484,   539,   540,   541,   543,   151,   152,
     153,   201,   482,   484,   547,   548,   549,   550,   552,   553,
     559,     7,   597,   598,   187,   235,   621,   622,   623,   232,
       7,   472,   473,   474,   131,   503,   505,   523,   308,     8,
       8,     8,   303,     3,     8,   315,   318,   320,   322,     4,
       4,     4,     4,     4,   334,   336,   338,   340,     4,     4,
     344,     4,     4,     4,     4,     3,     8,     8,   311,     6,
       3,   392,     6,     3,   433,     6,     3,   457,     6,     3,
     423,     6,     3,     3,     6,   528,     3,     6,   491,     6,
       3,   368,     6,     3,     4,     4,     4,     4,     4,     4,
       3,     8,     4,     4,     4,     3,     8,   542,   544,     3,
       8,     4,   551,     4,   554,     3,     8,     8,   599,     3,
       6,     4,     3,     8,   201,   233,   234,   475,     6,     3,
     506,     8,     6,     4,   301,     4,     4,     4,     4,   202,
     204,   202,   204,   202,     4,     4,     4,     4,   202,   202,
       4,   202,   202,   204,   202,   313,   312,   310,   395,   391,
     436,   432,   460,   456,   235,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   259,   260,   261,   262,   263,
     264,   267,   269,   271,   272,   273,   275,   277,   324,   387,
     405,   407,   409,   411,   412,   413,   414,   424,   425,   452,
     482,   484,   497,   499,   501,   521,   422,   350,   119,   120,
     235,   244,   245,   246,   324,   426,   452,   482,   484,   497,
     499,   501,   529,   530,   531,   532,   533,   535,   527,   494,
     490,   371,   367,   202,   202,   202,   202,   202,   202,   380,
     204,   202,   202,   359,     4,     4,   540,   204,     4,   202,
       4,   548,   178,   180,   181,   235,   324,   482,   484,   600,
     601,   602,   603,   605,   598,   204,   622,     6,     3,   478,
     474,     4,   201,    35,    36,    37,    38,   316,   201,   201,
     201,   201,   201,   201,   201,    54,    55,    56,   345,     8,
       8,     8,     8,     3,     8,   534,     4,     8,     3,     8,
       8,   201,   201,   201,   220,   606,     4,   604,     3,     8,
     201,     8,   231,   425,     4,   204,   531,     4,   202,     4,
     601,   201,     5,   201,     7,   607,   608,   609,     3,     6,
     179,   182,   183,   184,   185,   610,   611,   612,   614,   615,
     616,   617,   608,   613,     4,     4,     4,   618,     3,     8,
       4,   204,   202,   202,     4,   611,   201,   201
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   205,   207,   206,   208,   206,   209,   206,   210,   206,
     211,   206,   212,   206,   213,   206,   214,   206,   215,   206,
     216,   206,   217,   206,   218,   206,   219,   206,   220,   220,
     220,   220,   220,   220,   220,   221,   223,   222,   224,   225,
     225,   226,   226,   228,   227,   229,   229,   230,   230,   232,
     231,   233,   233,   234,   234,   235,   237,   236,   239,   238,
     241,   240,   242,   242,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   256,   255,   257,
     258,   259,   260,   261,   262,   263,   265,   264,   266,   266,
     266,   266,   266,   268,   267,   270,   269,   271,   272,   274,
     273,   276,   275,   277,   278,   279,   280,   282,   281,   283,
     283,   284,   284,   284,   284,   284,   284,   284,   286,   285,
     288,   287,   290,   289,   291,   291,   293,   292,   294,   294,
     295,   297,   296,   299,   298,   300,   300,   301,   303,   302,
     305,   304,   307,   306,   308,   308,   309,   309,   311,   310,
     312,   312,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   313,   313,   313,   313,   313,   313,   313,
     313,   313,   313,   313,   315,   314,   316,   316,   316,   316,
     318,   317,   320,   319,   322,   321,   323,   325,   324,   326,
     327,   328,   329,   330,   331,   332,   334,   333,   336,   335,
     338,   337,   340,   339,   341,   342,   344,   343,   345,   345,
     345,   346,   348,   347,   349,   349,   350,   350,   350,   350,
     350,   351,   352,   353,   354,   355,   357,   356,   358,   358,
     359,   359,   359,   359,   359,   359,   360,   361,   362,   364,
     363,   365,   365,   366,   366,   368,   367,   370,   369,   371,
     371,   371,   372,   372,   374,   373,   376,   375,   378,   377,
     379,   379,   380,   380,   380,   380,   380,   380,   381,   382,
     383,   384,   385,   386,   388,   387,   389,   389,   390,   390,
     392,   391,   394,   393,   395,   395,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   398,   397,   400,   399,   402,   401,   404,   403,   406,
     405,   408,   407,   410,   409,   411,   412,   413,   415,   414,
     416,   416,   416,   416,   417,   419,   418,   420,   420,   421,
     421,   423,   422,   424,   424,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   425,   425,   425,   425,   425,
     425,   425,   425,   425,   425,   427,   426,   429,   428,   430,
     430,   431,   431,   433,   432,   435,   434,   436,   436,   437,
     437,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   439,   440,   441,   443,   442,   445,   444,   447,   446,
     448,   450,   449,   451,   453,   452,   454,   454,   455,   455,
     457,   456,   459,   458,   460,   460,   461,   461,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   463,   465,   464,
     466,   467,   468,   469,   471,   470,   472,   472,   473,   473,
     475,   474,   477,   476,   478,   478,   479,   479,   479,   479,
     479,   479,   479,   481,   480,   483,   482,   485,   484,   487,
     486,   488,   488,   489,   489,   491,   490,   493,   492,   494,
     494,   495,   495,   496,   496,   496,   496,   496,   496,   496,
     496,   496,   496,   496,   496,   496,   496,   496,   498,   497,
     500,   499,   502,   501,   504,   503,   506,   505,   508,   507,
     510,   509,   512,   511,   514,   513,   516,   515,   518,   517,
     520,   519,   522,   521,   523,   523,   525,   524,   526,   526,
     528,   527,   529,   529,   530,   530,   531,   531,   531,   531,
     531,   531,   531,   531,   531,   531,   531,   531,   531,   531,
     532,   534,   533,   535,   536,   538,   537,   539,   539,   540,
     540,   540,   540,   540,   542,   541,   544,   543,   546,   545,
     547,   547,   548,   548,   548,   548,   548,   548,   549,   551,
     550,   552,   554,   553,   556,   555,   558,   557,   559,   559,
     560,   560,   560,   560,   560,   560,   560,   560,   560,   560,
     560,   560,   560,   560,   560,   560,   560,   560,   561,   563,
     562,   564,   566,   565,   567,   568,   570,   569,   571,   571,
     573,   572,   575,   574,   576,   577,   579,   578,   581,   580,
     583,   582,   585,   584,   587,   586,   589,   588,   590,   590,
     591,   591,   593,   592,   594,   596,   595,   597,   597,   599,
     598,   600,   600,   601,   601,   601,   601,   601,   601,   601,
     602,   604,   603,   606,   605,   607,   607,   609,   608,   610,
     610,   611,   611,   611,   611,   611,   613,   612,   614,   615,
     616,   618,   617,   620,   619,   621,   621,   622,   622,   623
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
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     3,     3,     0,
       4,     0,     4,     3,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     1,     1,     0,     4,     1,     1,
       3,     0,     6,     0,     6,     1,     3,     1,     0,     4,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     0,     4,     1,     1,
       1,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
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
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     1,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     0,     6,     3,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     0,     6,     1,     3,     1,     1,     3
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
  "global_object", "$@18", "sub_dhcp4", "$@19", "global_params",
  "global_param", "valid_lifetime", "min_valid_lifetime",
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
     343,   346,   351,   359,   359,   366,   367,   370,   374,   381,
     381,   388,   389,   392,   396,   407,   416,   416,   431,   431,
     448,   448,   457,   458,   463,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   527,   533,   539,   545,
     551,   557,   563,   569,   575,   581,   587,   593,   593,   602,
     608,   614,   620,   626,   632,   638,   644,   644,   653,   656,
     659,   662,   665,   671,   671,   680,   680,   689,   695,   701,
     701,   710,   710,   719,   725,   731,   737,   743,   743,   755,
     756,   759,   760,   761,   762,   763,   764,   765,   768,   768,
     777,   777,   788,   788,   796,   797,   800,   800,   808,   810,
     814,   821,   821,   834,   834,   845,   846,   848,   850,   850,
     869,   869,   882,   882,   893,   894,   897,   898,   901,   901,
     911,   912,   915,   916,   917,   918,   919,   920,   921,   922,
     923,   924,   925,   926,   927,   928,   929,   930,   931,   932,
     933,   934,   935,   936,   939,   939,   947,   948,   949,   950,
     953,   953,   962,   962,   971,   971,   980,   986,   986,   995,
    1001,  1007,  1013,  1019,  1025,  1031,  1037,  1037,  1046,  1046,
    1055,  1055,  1064,  1064,  1073,  1079,  1085,  1085,  1093,  1094,
    1095,  1098,  1105,  1105,  1116,  1117,  1120,  1121,  1122,  1123,
    1124,  1127,  1132,  1137,  1142,  1147,  1154,  1154,  1167,  1168,
    1171,  1172,  1173,  1174,  1175,  1176,  1179,  1185,  1191,  1197,
    1197,  1208,  1209,  1212,  1213,  1216,  1216,  1226,  1226,  1236,
    1237,  1238,  1241,  1242,  1245,  1245,  1254,  1254,  1263,  1263,
    1275,  1276,  1279,  1280,  1281,  1282,  1283,  1284,  1287,  1293,
    1299,  1305,  1311,  1317,  1326,  1326,  1340,  1341,  1344,  1345,
    1352,  1352,  1378,  1378,  1389,  1390,  1394,  1395,  1396,  1397,
    1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,  1406,  1407,
    1408,  1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,
    1418,  1419,  1420,  1421,  1422,  1423,  1424,  1425,  1426,  1427,
    1428,  1429,  1430,  1431,  1432,  1433,  1434,  1435,  1436,  1437,
    1438,  1441,  1441,  1450,  1450,  1459,  1459,  1468,  1468,  1477,
    1477,  1486,  1486,  1495,  1495,  1506,  1512,  1518,  1524,  1524,
    1532,  1533,  1534,  1535,  1538,  1546,  1546,  1558,  1559,  1563,
    1564,  1567,  1567,  1575,  1576,  1579,  1580,  1581,  1582,  1583,
    1584,  1585,  1586,  1587,  1588,  1589,  1590,  1591,  1592,  1593,
    1594,  1595,  1596,  1597,  1598,  1599,  1600,  1601,  1602,  1603,
    1604,  1605,  1606,  1607,  1608,  1609,  1610,  1611,  1612,  1613,
    1614,  1615,  1616,  1617,  1618,  1625,  1625,  1639,  1639,  1648,
    1649,  1652,  1653,  1658,  1658,  1673,  1673,  1687,  1688,  1691,
    1692,  1695,  1696,  1697,  1698,  1699,  1700,  1701,  1702,  1703,
    1704,  1707,  1709,  1715,  1717,  1717,  1726,  1726,  1735,  1735,
    1744,  1746,  1746,  1755,  1765,  1765,  1778,  1779,  1784,  1785,
    1790,  1790,  1802,  1802,  1814,  1815,  1820,  1821,  1826,  1827,
    1828,  1829,  1830,  1831,  1832,  1833,  1834,  1837,  1839,  1839,
    1848,  1850,  1852,  1858,  1867,  1867,  1880,  1881,  1884,  1885,
    1888,  1888,  1898,  1898,  1908,  1909,  1912,  1913,  1914,  1915,
    1916,  1917,  1918,  1921,  1921,  1930,  1930,  1955,  1955,  1985,
    1985,  1996,  1997,  2000,  2001,  2004,  2004,  2013,  2013,  2022,
    2023,  2026,  2027,  2031,  2032,  2033,  2034,  2035,  2036,  2037,
    2038,  2039,  2040,  2041,  2042,  2043,  2044,  2045,  2048,  2048,
    2057,  2057,  2066,  2066,  2075,  2075,  2084,  2084,  2095,  2095,
    2104,  2104,  2113,  2113,  2122,  2122,  2131,  2131,  2140,  2140,
    2149,  2149,  2163,  2163,  2174,  2175,  2181,  2181,  2192,  2193,
    2196,  2196,  2206,  2207,  2210,  2211,  2214,  2215,  2216,  2217,
    2218,  2219,  2220,  2221,  2222,  2223,  2224,  2225,  2226,  2227,
    2230,  2232,  2232,  2241,  2249,  2257,  2257,  2268,  2269,  2272,
    2273,  2274,  2275,  2276,  2279,  2279,  2288,  2288,  2300,  2300,
    2313,  2314,  2317,  2318,  2319,  2320,  2321,  2322,  2325,  2331,
    2331,  2340,  2346,  2346,  2356,  2356,  2369,  2369,  2379,  2380,
    2383,  2384,  2385,  2386,  2387,  2388,  2389,  2390,  2391,  2392,
    2393,  2394,  2395,  2396,  2397,  2398,  2399,  2400,  2403,  2409,
    2409,  2418,  2424,  2424,  2433,  2439,  2445,  2445,  2454,  2455,
    2458,  2458,  2468,  2468,  2478,  2485,  2492,  2492,  2501,  2501,
    2511,  2511,  2521,  2521,  2533,  2533,  2545,  2545,  2555,  2556,
    2560,  2561,  2564,  2564,  2575,  2583,  2583,  2596,  2597,  2601,
    2601,  2609,  2610,  2613,  2614,  2615,  2616,  2617,  2618,  2619,
    2622,  2628,  2628,  2637,  2637,  2648,  2649,  2652,  2652,  2660,
    2661,  2664,  2665,  2666,  2667,  2668,  2671,  2671,  2680,  2686,
    2692,  2698,  2698,  2707,  2707,  2718,  2719,  2722,  2723,  2726
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
#line 5840 "dhcp4_parser.cc"

#line 2732 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
