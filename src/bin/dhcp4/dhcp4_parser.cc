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
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 289 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 289 "dhcp4_parser.yy"
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
#line 298 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 299 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 300 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 301 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 302 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 303 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 304 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 305 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 306 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 307 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 308 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 309 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 310 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 318 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 319 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 320 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 321 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 322 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 323 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 324 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 327 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 332 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 337 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 343 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 350 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 355 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 361 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 366 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 369 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 377 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 381 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 385 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 391 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 393 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 402 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 406 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 410 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 420 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 429 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 434 "dhcp4_parser.yy"
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
#line 444 "dhcp4_parser.yy"
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
#line 453 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 461 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 467 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 471 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 478 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 134: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 551 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 135: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 557 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 136: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 563 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 137: // renew_timer: "renew-timer" ":" "integer"
#line 569 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 138: // rebind_timer: "rebind-timer" ":" "integer"
#line 575 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 139: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 581 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 140: // t1_percent: "t1-percent" ":" "floating point"
#line 587 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 141: // t2_percent: "t2-percent" ":" "floating point"
#line 593 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 142: // cache_threshold: "cache-threshold" ":" "floating point"
#line 599 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 143: // cache_max_age: "cache-max-age" ":" "integer"
#line 605 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 144: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 611 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 145: // $@20: %empty
#line 617 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 146: // server_tag: "server-tag" $@20 ":" "constant string"
#line 620 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 147: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 626 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 148: // echo_client_id: "echo-client-id" ":" "boolean"
#line 632 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1270 "dhcp4_parser.cc"
    break;

  case 149: // match_client_id: "match-client-id" ":" "boolean"
#line 638 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1280 "dhcp4_parser.cc"
    break;

  case 150: // authoritative: "authoritative" ":" "boolean"
#line 644 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1290 "dhcp4_parser.cc"
    break;

  case 151: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 650 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1300 "dhcp4_parser.cc"
    break;

  case 152: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 656 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1310 "dhcp4_parser.cc"
    break;

  case 153: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 662 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1320 "dhcp4_parser.cc"
    break;

  case 154: // $@21: %empty
#line 668 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 155: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 671 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1338 "dhcp4_parser.cc"
    break;

  case 156: // ddns_replace_client_name_value: "when-present"
#line 677 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1346 "dhcp4_parser.cc"
    break;

  case 157: // ddns_replace_client_name_value: "never"
#line 680 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1354 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "always"
#line 683 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1362 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "when-not-present"
#line 686 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1370 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "boolean"
#line 689 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1379 "dhcp4_parser.cc"
    break;

  case 161: // $@22: %empty
#line 695 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1388 "dhcp4_parser.cc"
    break;

  case 162: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 698 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1398 "dhcp4_parser.cc"
    break;

  case 163: // $@23: %empty
#line 704 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 164: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 707 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 165: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 713 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1427 "dhcp4_parser.cc"
    break;

  case 166: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 719 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1437 "dhcp4_parser.cc"
    break;

  case 167: // $@24: %empty
#line 725 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 168: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 728 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 169: // $@25: %empty
#line 734 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 170: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 737 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 171: // store_extended_info: "store-extended-info" ":" "boolean"
#line 743 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 172: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 749 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1495 "dhcp4_parser.cc"
    break;

  case 173: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 755 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 174: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 761 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 175: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 767 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 176: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 773 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1535 "dhcp4_parser.cc"
    break;

  case 177: // $@26: %empty
#line 779 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1547 "dhcp4_parser.cc"
    break;

  case 178: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 785 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1557 "dhcp4_parser.cc"
    break;

  case 181: // interfaces_config_params: interfaces_config_params ","
#line 793 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1565 "dhcp4_parser.cc"
    break;

  case 192: // $@27: %empty
#line 810 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1575 "dhcp4_parser.cc"
    break;

  case 193: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 814 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 194: // $@28: %empty
#line 819 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1596 "dhcp4_parser.cc"
    break;

  case 195: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 825 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1605 "dhcp4_parser.cc"
    break;

  case 196: // $@29: %empty
#line 830 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 197: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 833 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1623 "dhcp4_parser.cc"
    break;

  case 198: // socket_type: "raw"
#line 838 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1629 "dhcp4_parser.cc"
    break;

  case 199: // socket_type: "udp"
#line 839 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1635 "dhcp4_parser.cc"
    break;

  case 200: // $@30: %empty
#line 842 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 201: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 845 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1653 "dhcp4_parser.cc"
    break;

  case 202: // outbound_interface_value: "same-as-inbound"
#line 850 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1661 "dhcp4_parser.cc"
    break;

  case 203: // outbound_interface_value: "use-routing"
#line 852 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1669 "dhcp4_parser.cc"
    break;

  case 204: // re_detect: "re-detect" ":" "boolean"
#line 856 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1679 "dhcp4_parser.cc"
    break;

  case 205: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 862 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1689 "dhcp4_parser.cc"
    break;

  case 206: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 868 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1699 "dhcp4_parser.cc"
    break;

  case 207: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 874 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1709 "dhcp4_parser.cc"
    break;

  case 208: // $@31: %empty
#line 880 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1721 "dhcp4_parser.cc"
    break;

  case 209: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 886 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1732 "dhcp4_parser.cc"
    break;

  case 210: // $@32: %empty
#line 893 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1744 "dhcp4_parser.cc"
    break;

  case 211: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 899 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1753 "dhcp4_parser.cc"
    break;

  case 214: // sanity_checks_params: sanity_checks_params ","
#line 906 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1761 "dhcp4_parser.cc"
    break;

  case 217: // $@33: %empty
#line 915 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1770 "dhcp4_parser.cc"
    break;

  case 218: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 918 "dhcp4_parser.yy"
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
#line 1790 "dhcp4_parser.cc"
    break;

  case 219: // $@34: %empty
#line 934 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1799 "dhcp4_parser.cc"
    break;

  case 220: // extended_info_checks: "extended-info-checks" $@34 ":" "constant string"
#line 937 "dhcp4_parser.yy"
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
#line 1818 "dhcp4_parser.cc"
    break;

  case 221: // $@35: %empty
#line 952 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1830 "dhcp4_parser.cc"
    break;

  case 222: // hosts_database: "hosts-database" $@35 ":" "{" database_map_params "}"
#line 958 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1841 "dhcp4_parser.cc"
    break;

  case 223: // $@36: %empty
#line 965 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1853 "dhcp4_parser.cc"
    break;

  case 224: // hosts_databases: "hosts-databases" $@36 ":" "[" database_list "]"
#line 971 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1862 "dhcp4_parser.cc"
    break;

  case 229: // not_empty_database_list: not_empty_database_list ","
#line 982 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1870 "dhcp4_parser.cc"
    break;

  case 230: // $@37: %empty
#line 987 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1880 "dhcp4_parser.cc"
    break;

  case 231: // database: "{" $@37 database_map_params "}"
#line 991 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1890 "dhcp4_parser.cc"
    break;

  case 234: // database_map_params: database_map_params ","
#line 999 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1898 "dhcp4_parser.cc"
    break;

  case 254: // $@38: %empty
#line 1025 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1907 "dhcp4_parser.cc"
    break;

  case 255: // database_type: "type" $@38 ":" db_type
#line 1028 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1916 "dhcp4_parser.cc"
    break;

  case 256: // db_type: "memfile"
#line 1033 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1922 "dhcp4_parser.cc"
    break;

  case 257: // db_type: "mysql"
#line 1034 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1928 "dhcp4_parser.cc"
    break;

  case 258: // db_type: "postgresql"
#line 1035 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1934 "dhcp4_parser.cc"
    break;

  case 259: // $@39: %empty
#line 1038 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1943 "dhcp4_parser.cc"
    break;

  case 260: // user: "user" $@39 ":" "constant string"
#line 1041 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 261: // $@40: %empty
#line 1047 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 262: // password: "password" $@40 ":" "constant string"
#line 1050 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 263: // $@41: %empty
#line 1056 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 264: // host: "host" $@41 ":" "constant string"
#line 1059 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 265: // port: "port" ":" "integer"
#line 1065 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 266: // $@42: %empty
#line 1071 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 267: // name: "name" $@42 ":" "constant string"
#line 1074 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 268: // persist: "persist" ":" "boolean"
#line 1080 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2030 "dhcp4_parser.cc"
    break;

  case 269: // lfc_interval: "lfc-interval" ":" "integer"
#line 1086 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2040 "dhcp4_parser.cc"
    break;

  case 270: // readonly: "readonly" ":" "boolean"
#line 1092 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 271: // connect_timeout: "connect-timeout" ":" "integer"
#line 1098 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2060 "dhcp4_parser.cc"
    break;

  case 272: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1104 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2070 "dhcp4_parser.cc"
    break;

  case 273: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1110 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2080 "dhcp4_parser.cc"
    break;

  case 274: // $@43: %empty
#line 1116 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 275: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1119 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2098 "dhcp4_parser.cc"
    break;

  case 276: // on_fail_mode: "stop-retry-exit"
#line 1124 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2104 "dhcp4_parser.cc"
    break;

  case 277: // on_fail_mode: "serve-retry-exit"
#line 1125 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2110 "dhcp4_parser.cc"
    break;

  case 278: // on_fail_mode: "serve-retry-continue"
#line 1126 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2116 "dhcp4_parser.cc"
    break;

  case 279: // max_row_errors: "max-row-errors" ":" "integer"
#line 1129 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2126 "dhcp4_parser.cc"
    break;

  case 280: // $@44: %empty
#line 1135 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2135 "dhcp4_parser.cc"
    break;

  case 281: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1138 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2145 "dhcp4_parser.cc"
    break;

  case 282: // $@45: %empty
#line 1144 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2154 "dhcp4_parser.cc"
    break;

  case 283: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1147 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2164 "dhcp4_parser.cc"
    break;

  case 284: // $@46: %empty
#line 1153 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 285: // key_file: "key-file" $@46 ":" "constant string"
#line 1156 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2183 "dhcp4_parser.cc"
    break;

  case 286: // $@47: %empty
#line 1162 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 287: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1165 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 288: // $@48: %empty
#line 1171 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2214 "dhcp4_parser.cc"
    break;

  case 289: // host_reservation_identifiers: "host-reservation-identifiers" $@48 ":" "[" host_reservation_identifiers_list "]"
#line 1177 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2223 "dhcp4_parser.cc"
    break;

  case 292: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1184 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2231 "dhcp4_parser.cc"
    break;

  case 298: // duid_id: "duid"
#line 1196 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2240 "dhcp4_parser.cc"
    break;

  case 299: // hw_address_id: "hw-address"
#line 1201 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2249 "dhcp4_parser.cc"
    break;

  case 300: // circuit_id: "circuit-id"
#line 1206 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2258 "dhcp4_parser.cc"
    break;

  case 301: // client_id: "client-id"
#line 1211 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2267 "dhcp4_parser.cc"
    break;

  case 302: // flex_id: "flex-id"
#line 1216 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2276 "dhcp4_parser.cc"
    break;

  case 303: // $@49: %empty
#line 1223 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2288 "dhcp4_parser.cc"
    break;

  case 304: // dhcp_multi_threading: "multi-threading" $@49 ":" "{" multi_threading_params "}"
#line 1229 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2299 "dhcp4_parser.cc"
    break;

  case 307: // multi_threading_params: multi_threading_params ","
#line 1238 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2307 "dhcp4_parser.cc"
    break;

  case 314: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1251 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2317 "dhcp4_parser.cc"
    break;

  case 315: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1257 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2327 "dhcp4_parser.cc"
    break;

  case 316: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1263 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2337 "dhcp4_parser.cc"
    break;

  case 317: // $@50: %empty
#line 1269 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2349 "dhcp4_parser.cc"
    break;

  case 318: // hooks_libraries: "hooks-libraries" $@50 ":" "[" hooks_libraries_list "]"
#line 1275 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2358 "dhcp4_parser.cc"
    break;

  case 323: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1286 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2366 "dhcp4_parser.cc"
    break;

  case 324: // $@51: %empty
#line 1291 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 325: // hooks_library: "{" $@51 hooks_params "}"
#line 1295 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 326: // $@52: %empty
#line 1301 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2396 "dhcp4_parser.cc"
    break;

  case 327: // sub_hooks_library: "{" $@52 hooks_params "}"
#line 1305 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 330: // hooks_params: hooks_params ","
#line 1313 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2414 "dhcp4_parser.cc"
    break;

  case 334: // $@53: %empty
#line 1323 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2423 "dhcp4_parser.cc"
    break;

  case 335: // library: "library" $@53 ":" "constant string"
#line 1326 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2433 "dhcp4_parser.cc"
    break;

  case 336: // $@54: %empty
#line 1332 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2442 "dhcp4_parser.cc"
    break;

  case 337: // parameters: "parameters" $@54 ":" map_value
#line 1335 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2451 "dhcp4_parser.cc"
    break;

  case 338: // $@55: %empty
#line 1341 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2463 "dhcp4_parser.cc"
    break;

  case 339: // expired_leases_processing: "expired-leases-processing" $@55 ":" "{" expired_leases_params "}"
#line 1347 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 342: // expired_leases_params: expired_leases_params ","
#line 1355 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2481 "dhcp4_parser.cc"
    break;

  case 349: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1368 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 350: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1374 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 351: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1380 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2511 "dhcp4_parser.cc"
    break;

  case 352: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1386 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2521 "dhcp4_parser.cc"
    break;

  case 353: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1392 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2531 "dhcp4_parser.cc"
    break;

  case 354: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1398 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2541 "dhcp4_parser.cc"
    break;

  case 355: // $@56: %empty
#line 1407 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2553 "dhcp4_parser.cc"
    break;

  case 356: // subnet4_list: "subnet4" $@56 ":" "[" subnet4_list_content "]"
#line 1413 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2562 "dhcp4_parser.cc"
    break;

  case 361: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1427 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2570 "dhcp4_parser.cc"
    break;

  case 362: // $@57: %empty
#line 1436 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 363: // subnet4: "{" $@57 subnet4_params "}"
#line 1440 "dhcp4_parser.yy"
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
#line 2606 "dhcp4_parser.cc"
    break;

  case 364: // $@58: %empty
#line 1462 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2616 "dhcp4_parser.cc"
    break;

  case 365: // sub_subnet4: "{" $@58 subnet4_params "}"
#line 1466 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2626 "dhcp4_parser.cc"
    break;

  case 368: // subnet4_params: subnet4_params ","
#line 1475 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2634 "dhcp4_parser.cc"
    break;

  case 414: // $@59: %empty
#line 1528 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2643 "dhcp4_parser.cc"
    break;

  case 415: // subnet: "subnet" $@59 ":" "constant string"
#line 1531 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2653 "dhcp4_parser.cc"
    break;

  case 416: // $@60: %empty
#line 1537 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2662 "dhcp4_parser.cc"
    break;

  case 417: // subnet_4o6_interface: "4o6-interface" $@60 ":" "constant string"
#line 1540 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2672 "dhcp4_parser.cc"
    break;

  case 418: // $@61: %empty
#line 1546 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2681 "dhcp4_parser.cc"
    break;

  case 419: // subnet_4o6_interface_id: "4o6-interface-id" $@61 ":" "constant string"
#line 1549 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2691 "dhcp4_parser.cc"
    break;

  case 420: // $@62: %empty
#line 1555 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2700 "dhcp4_parser.cc"
    break;

  case 421: // subnet_4o6_subnet: "4o6-subnet" $@62 ":" "constant string"
#line 1558 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2710 "dhcp4_parser.cc"
    break;

  case 422: // $@63: %empty
#line 1564 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp4_parser.cc"
    break;

  case 423: // interface: "interface" $@63 ":" "constant string"
#line 1567 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2729 "dhcp4_parser.cc"
    break;

  case 424: // $@64: %empty
#line 1573 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2738 "dhcp4_parser.cc"
    break;

  case 425: // client_class: "client-class" $@64 ":" "constant string"
#line 1576 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2748 "dhcp4_parser.cc"
    break;

  case 426: // $@65: %empty
#line 1582 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2760 "dhcp4_parser.cc"
    break;

  case 427: // require_client_classes: "require-client-classes" $@65 ":" list_strings
#line 1588 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2769 "dhcp4_parser.cc"
    break;

  case 428: // reservations_global: "reservations-global" ":" "boolean"
#line 1593 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2779 "dhcp4_parser.cc"
    break;

  case 429: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1599 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2789 "dhcp4_parser.cc"
    break;

  case 430: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1605 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2799 "dhcp4_parser.cc"
    break;

  case 431: // $@66: %empty
#line 1611 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2808 "dhcp4_parser.cc"
    break;

  case 432: // reservation_mode: "reservation-mode" $@66 ":" hr_mode
#line 1614 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2817 "dhcp4_parser.cc"
    break;

  case 433: // hr_mode: "disabled"
#line 1619 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2823 "dhcp4_parser.cc"
    break;

  case 434: // hr_mode: "out-of-pool"
#line 1620 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2829 "dhcp4_parser.cc"
    break;

  case 435: // hr_mode: "global"
#line 1621 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2835 "dhcp4_parser.cc"
    break;

  case 436: // hr_mode: "all"
#line 1622 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2841 "dhcp4_parser.cc"
    break;

  case 437: // id: "id" ":" "integer"
#line 1625 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2851 "dhcp4_parser.cc"
    break;

  case 438: // $@67: %empty
#line 1633 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2863 "dhcp4_parser.cc"
    break;

  case 439: // shared_networks: "shared-networks" $@67 ":" "[" shared_networks_content "]"
#line 1639 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2872 "dhcp4_parser.cc"
    break;

  case 444: // shared_networks_list: shared_networks_list ","
#line 1652 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2880 "dhcp4_parser.cc"
    break;

  case 445: // $@68: %empty
#line 1657 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 446: // shared_network: "{" $@68 shared_network_params "}"
#line 1661 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2898 "dhcp4_parser.cc"
    break;

  case 449: // shared_network_params: shared_network_params ","
#line 1667 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2906 "dhcp4_parser.cc"
    break;

  case 490: // $@69: %empty
#line 1718 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2918 "dhcp4_parser.cc"
    break;

  case 491: // option_def_list: "option-def" $@69 ":" "[" option_def_list_content "]"
#line 1724 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2927 "dhcp4_parser.cc"
    break;

  case 492: // $@70: %empty
#line 1732 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2936 "dhcp4_parser.cc"
    break;

  case 493: // sub_option_def_list: "{" $@70 option_def_list "}"
#line 1735 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2944 "dhcp4_parser.cc"
    break;

  case 498: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1747 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2952 "dhcp4_parser.cc"
    break;

  case 499: // $@71: %empty
#line 1754 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2962 "dhcp4_parser.cc"
    break;

  case 500: // option_def_entry: "{" $@71 option_def_params "}"
#line 1758 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2974 "dhcp4_parser.cc"
    break;

  case 501: // $@72: %empty
#line 1769 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2984 "dhcp4_parser.cc"
    break;

  case 502: // sub_option_def: "{" $@72 option_def_params "}"
#line 1773 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2996 "dhcp4_parser.cc"
    break;

  case 507: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1789 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3004 "dhcp4_parser.cc"
    break;

  case 519: // code: "code" ":" "integer"
#line 1808 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3014 "dhcp4_parser.cc"
    break;

  case 521: // $@73: %empty
#line 1816 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3023 "dhcp4_parser.cc"
    break;

  case 522: // option_def_type: "type" $@73 ":" "constant string"
#line 1819 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3033 "dhcp4_parser.cc"
    break;

  case 523: // $@74: %empty
#line 1825 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3042 "dhcp4_parser.cc"
    break;

  case 524: // option_def_record_types: "record-types" $@74 ":" "constant string"
#line 1828 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 525: // $@75: %empty
#line 1834 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3061 "dhcp4_parser.cc"
    break;

  case 526: // space: "space" $@75 ":" "constant string"
#line 1837 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3071 "dhcp4_parser.cc"
    break;

  case 528: // $@76: %empty
#line 1845 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3080 "dhcp4_parser.cc"
    break;

  case 529: // option_def_encapsulate: "encapsulate" $@76 ":" "constant string"
#line 1848 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 530: // option_def_array: "array" ":" "boolean"
#line 1854 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3100 "dhcp4_parser.cc"
    break;

  case 531: // $@77: %empty
#line 1864 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3112 "dhcp4_parser.cc"
    break;

  case 532: // option_data_list: "option-data" $@77 ":" "[" option_data_list_content "]"
#line 1870 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 537: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1885 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3129 "dhcp4_parser.cc"
    break;

  case 538: // $@78: %empty
#line 1892 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 539: // option_data_entry: "{" $@78 option_data_params "}"
#line 1896 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3148 "dhcp4_parser.cc"
    break;

  case 540: // $@79: %empty
#line 1904 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3158 "dhcp4_parser.cc"
    break;

  case 541: // sub_option_data: "{" $@79 option_data_params "}"
#line 1908 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3167 "dhcp4_parser.cc"
    break;

  case 546: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1924 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3175 "dhcp4_parser.cc"
    break;

  case 557: // $@80: %empty
#line 1944 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3184 "dhcp4_parser.cc"
    break;

  case 558: // option_data_data: "data" $@80 ":" "constant string"
#line 1947 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3194 "dhcp4_parser.cc"
    break;

  case 561: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1957 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3204 "dhcp4_parser.cc"
    break;

  case 562: // option_data_always_send: "always-send" ":" "boolean"
#line 1963 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 563: // $@81: %empty
#line 1972 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3226 "dhcp4_parser.cc"
    break;

  case 564: // pools_list: "pools" $@81 ":" "[" pools_list_content "]"
#line 1978 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3235 "dhcp4_parser.cc"
    break;

  case 569: // not_empty_pools_list: not_empty_pools_list ","
#line 1991 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3243 "dhcp4_parser.cc"
    break;

  case 570: // $@82: %empty
#line 1996 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3253 "dhcp4_parser.cc"
    break;

  case 571: // pool_list_entry: "{" $@82 pool_params "}"
#line 2000 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 572: // $@83: %empty
#line 2006 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 573: // sub_pool4: "{" $@83 pool_params "}"
#line 2010 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 576: // pool_params: pool_params ","
#line 2018 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3291 "dhcp4_parser.cc"
    break;

  case 584: // $@84: %empty
#line 2032 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3300 "dhcp4_parser.cc"
    break;

  case 585: // pool_entry: "pool" $@84 ":" "constant string"
#line 2035 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3310 "dhcp4_parser.cc"
    break;

  case 586: // $@85: %empty
#line 2041 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp4_parser.cc"
    break;

  case 587: // user_context: "user-context" $@85 ":" map_value
#line 2043 "dhcp4_parser.yy"
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
#line 3345 "dhcp4_parser.cc"
    break;

  case 588: // $@86: %empty
#line 2066 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3353 "dhcp4_parser.cc"
    break;

  case 589: // comment: "comment" $@86 ":" "constant string"
#line 2068 "dhcp4_parser.yy"
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
#line 3382 "dhcp4_parser.cc"
    break;

  case 590: // $@87: %empty
#line 2096 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3394 "dhcp4_parser.cc"
    break;

  case 591: // reservations: "reservations" $@87 ":" "[" reservations_list "]"
#line 2102 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3403 "dhcp4_parser.cc"
    break;

  case 596: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2113 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3411 "dhcp4_parser.cc"
    break;

  case 597: // $@88: %empty
#line 2118 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3421 "dhcp4_parser.cc"
    break;

  case 598: // reservation: "{" $@88 reservation_params "}"
#line 2122 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3430 "dhcp4_parser.cc"
    break;

  case 599: // $@89: %empty
#line 2127 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3440 "dhcp4_parser.cc"
    break;

  case 600: // sub_reservation: "{" $@89 reservation_params "}"
#line 2131 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3449 "dhcp4_parser.cc"
    break;

  case 605: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2142 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3457 "dhcp4_parser.cc"
    break;

  case 621: // $@90: %empty
#line 2165 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3466 "dhcp4_parser.cc"
    break;

  case 622: // next_server: "next-server" $@90 ":" "constant string"
#line 2168 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3476 "dhcp4_parser.cc"
    break;

  case 623: // $@91: %empty
#line 2174 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3485 "dhcp4_parser.cc"
    break;

  case 624: // server_hostname: "server-hostname" $@91 ":" "constant string"
#line 2177 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3495 "dhcp4_parser.cc"
    break;

  case 625: // $@92: %empty
#line 2183 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3504 "dhcp4_parser.cc"
    break;

  case 626: // boot_file_name: "boot-file-name" $@92 ":" "constant string"
#line 2186 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3514 "dhcp4_parser.cc"
    break;

  case 627: // $@93: %empty
#line 2192 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3523 "dhcp4_parser.cc"
    break;

  case 628: // ip_address: "ip-address" $@93 ":" "constant string"
#line 2195 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3533 "dhcp4_parser.cc"
    break;

  case 629: // $@94: %empty
#line 2201 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 630: // ip_addresses: "ip-addresses" $@94 ":" list_strings
#line 2207 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 631: // $@95: %empty
#line 2212 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 632: // duid: "duid" $@95 ":" "constant string"
#line 2215 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 633: // $@96: %empty
#line 2221 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 634: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2224 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 635: // $@97: %empty
#line 2230 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3601 "dhcp4_parser.cc"
    break;

  case 636: // client_id_value: "client-id" $@97 ":" "constant string"
#line 2233 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 637: // $@98: %empty
#line 2239 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3620 "dhcp4_parser.cc"
    break;

  case 638: // circuit_id_value: "circuit-id" $@98 ":" "constant string"
#line 2242 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3630 "dhcp4_parser.cc"
    break;

  case 639: // $@99: %empty
#line 2248 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3639 "dhcp4_parser.cc"
    break;

  case 640: // flex_id_value: "flex-id" $@99 ":" "constant string"
#line 2251 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3649 "dhcp4_parser.cc"
    break;

  case 641: // $@100: %empty
#line 2257 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3658 "dhcp4_parser.cc"
    break;

  case 642: // hostname: "hostname" $@100 ":" "constant string"
#line 2260 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3668 "dhcp4_parser.cc"
    break;

  case 643: // $@101: %empty
#line 2266 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3680 "dhcp4_parser.cc"
    break;

  case 644: // reservation_client_classes: "client-classes" $@101 ":" list_strings
#line 2272 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3689 "dhcp4_parser.cc"
    break;

  case 645: // $@102: %empty
#line 2280 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3701 "dhcp4_parser.cc"
    break;

  case 646: // relay: "relay" $@102 ":" "{" relay_map "}"
#line 2286 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3710 "dhcp4_parser.cc"
    break;

  case 649: // $@103: %empty
#line 2298 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 650: // client_classes: "client-classes" $@103 ":" "[" client_classes_list "]"
#line 2304 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3731 "dhcp4_parser.cc"
    break;

  case 653: // client_classes_list: client_classes_list ","
#line 2311 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3739 "dhcp4_parser.cc"
    break;

  case 654: // $@104: %empty
#line 2316 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3749 "dhcp4_parser.cc"
    break;

  case 655: // client_class_entry: "{" $@104 client_class_params "}"
#line 2320 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3759 "dhcp4_parser.cc"
    break;

  case 660: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2332 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3767 "dhcp4_parser.cc"
    break;

  case 677: // $@105: %empty
#line 2356 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3776 "dhcp4_parser.cc"
    break;

  case 678: // client_class_test: "test" $@105 ":" "constant string"
#line 2359 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3786 "dhcp4_parser.cc"
    break;

  case 679: // $@106: %empty
#line 2365 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3795 "dhcp4_parser.cc"
    break;

  case 680: // client_class_template_test: "template-test" $@106 ":" "constant string"
#line 2368 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3805 "dhcp4_parser.cc"
    break;

  case 681: // only_if_required: "only-if-required" ":" "boolean"
#line 2374 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 682: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2382 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3825 "dhcp4_parser.cc"
    break;

  case 683: // $@107: %empty
#line 2390 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3837 "dhcp4_parser.cc"
    break;

  case 684: // control_socket: "control-socket" $@107 ":" "{" control_socket_params "}"
#line 2396 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3846 "dhcp4_parser.cc"
    break;

  case 687: // control_socket_params: control_socket_params ","
#line 2403 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3854 "dhcp4_parser.cc"
    break;

  case 693: // $@108: %empty
#line 2415 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 694: // control_socket_type: "socket-type" $@108 ":" "constant string"
#line 2418 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3873 "dhcp4_parser.cc"
    break;

  case 695: // $@109: %empty
#line 2424 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3882 "dhcp4_parser.cc"
    break;

  case 696: // control_socket_name: "socket-name" $@109 ":" "constant string"
#line 2427 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3892 "dhcp4_parser.cc"
    break;

  case 697: // $@110: %empty
#line 2436 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3904 "dhcp4_parser.cc"
    break;

  case 698: // dhcp_queue_control: "dhcp-queue-control" $@110 ":" "{" queue_control_params "}"
#line 2442 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3915 "dhcp4_parser.cc"
    break;

  case 701: // queue_control_params: queue_control_params ","
#line 2451 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3923 "dhcp4_parser.cc"
    break;

  case 708: // enable_queue: "enable-queue" ":" "boolean"
#line 2464 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3933 "dhcp4_parser.cc"
    break;

  case 709: // $@111: %empty
#line 2470 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3942 "dhcp4_parser.cc"
    break;

  case 710: // queue_type: "queue-type" $@111 ":" "constant string"
#line 2473 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3952 "dhcp4_parser.cc"
    break;

  case 711: // capacity: "capacity" ":" "integer"
#line 2479 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3962 "dhcp4_parser.cc"
    break;

  case 712: // $@112: %empty
#line 2485 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3971 "dhcp4_parser.cc"
    break;

  case 713: // arbitrary_map_entry: "constant string" $@112 ":" value
#line 2488 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3980 "dhcp4_parser.cc"
    break;

  case 714: // $@113: %empty
#line 2495 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3992 "dhcp4_parser.cc"
    break;

  case 715: // dhcp_ddns: "dhcp-ddns" $@113 ":" "{" dhcp_ddns_params "}"
#line 2501 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4003 "dhcp4_parser.cc"
    break;

  case 716: // $@114: %empty
#line 2508 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4013 "dhcp4_parser.cc"
    break;

  case 717: // sub_dhcp_ddns: "{" $@114 dhcp_ddns_params "}"
#line 2512 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4023 "dhcp4_parser.cc"
    break;

  case 720: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2520 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4031 "dhcp4_parser.cc"
    break;

  case 739: // enable_updates: "enable-updates" ":" "boolean"
#line 2545 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 740: // $@115: %empty
#line 2551 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4050 "dhcp4_parser.cc"
    break;

  case 741: // server_ip: "server-ip" $@115 ":" "constant string"
#line 2554 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4060 "dhcp4_parser.cc"
    break;

  case 742: // server_port: "server-port" ":" "integer"
#line 2560 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4070 "dhcp4_parser.cc"
    break;

  case 743: // $@116: %empty
#line 2566 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4079 "dhcp4_parser.cc"
    break;

  case 744: // sender_ip: "sender-ip" $@116 ":" "constant string"
#line 2569 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4089 "dhcp4_parser.cc"
    break;

  case 745: // sender_port: "sender-port" ":" "integer"
#line 2575 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4099 "dhcp4_parser.cc"
    break;

  case 746: // max_queue_size: "max-queue-size" ":" "integer"
#line 2581 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4109 "dhcp4_parser.cc"
    break;

  case 747: // $@117: %empty
#line 2587 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4118 "dhcp4_parser.cc"
    break;

  case 748: // ncr_protocol: "ncr-protocol" $@117 ":" ncr_protocol_value
#line 2590 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4127 "dhcp4_parser.cc"
    break;

  case 749: // ncr_protocol_value: "udp"
#line 2596 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4133 "dhcp4_parser.cc"
    break;

  case 750: // ncr_protocol_value: "tcp"
#line 2597 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4139 "dhcp4_parser.cc"
    break;

  case 751: // $@118: %empty
#line 2600 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4148 "dhcp4_parser.cc"
    break;

  case 752: // ncr_format: "ncr-format" $@118 ":" "JSON"
#line 2603 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4158 "dhcp4_parser.cc"
    break;

  case 753: // $@119: %empty
#line 2610 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4167 "dhcp4_parser.cc"
    break;

  case 754: // dep_qualifying_suffix: "qualifying-suffix" $@119 ":" "constant string"
#line 2613 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4177 "dhcp4_parser.cc"
    break;

  case 755: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2620 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4187 "dhcp4_parser.cc"
    break;

  case 756: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2627 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4197 "dhcp4_parser.cc"
    break;

  case 757: // $@120: %empty
#line 2634 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4206 "dhcp4_parser.cc"
    break;

  case 758: // dep_replace_client_name: "replace-client-name" $@120 ":" ddns_replace_client_name_value
#line 2637 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4215 "dhcp4_parser.cc"
    break;

  case 759: // $@121: %empty
#line 2643 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4224 "dhcp4_parser.cc"
    break;

  case 760: // dep_generated_prefix: "generated-prefix" $@121 ":" "constant string"
#line 2646 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4234 "dhcp4_parser.cc"
    break;

  case 761: // $@122: %empty
#line 2653 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4243 "dhcp4_parser.cc"
    break;

  case 762: // dep_hostname_char_set: "hostname-char-set" $@122 ":" "constant string"
#line 2656 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4253 "dhcp4_parser.cc"
    break;

  case 763: // $@123: %empty
#line 2663 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4262 "dhcp4_parser.cc"
    break;

  case 764: // dep_hostname_char_replacement: "hostname-char-replacement" $@123 ":" "constant string"
#line 2666 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4272 "dhcp4_parser.cc"
    break;

  case 765: // $@124: %empty
#line 2675 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4284 "dhcp4_parser.cc"
    break;

  case 766: // config_control: "config-control" $@124 ":" "{" config_control_params "}"
#line 2681 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4294 "dhcp4_parser.cc"
    break;

  case 767: // $@125: %empty
#line 2687 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4304 "dhcp4_parser.cc"
    break;

  case 768: // sub_config_control: "{" $@125 config_control_params "}"
#line 2691 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4313 "dhcp4_parser.cc"
    break;

  case 771: // config_control_params: config_control_params ","
#line 2699 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4321 "dhcp4_parser.cc"
    break;

  case 774: // $@126: %empty
#line 2709 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4333 "dhcp4_parser.cc"
    break;

  case 775: // config_databases: "config-databases" $@126 ":" "[" database_list "]"
#line 2715 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4342 "dhcp4_parser.cc"
    break;

  case 776: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2720 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4352 "dhcp4_parser.cc"
    break;

  case 777: // $@127: %empty
#line 2728 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4364 "dhcp4_parser.cc"
    break;

  case 778: // loggers: "loggers" $@127 ":" "[" loggers_entries "]"
#line 2734 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4373 "dhcp4_parser.cc"
    break;

  case 781: // loggers_entries: loggers_entries ","
#line 2743 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4381 "dhcp4_parser.cc"
    break;

  case 782: // $@128: %empty
#line 2749 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4391 "dhcp4_parser.cc"
    break;

  case 783: // logger_entry: "{" $@128 logger_params "}"
#line 2753 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4399 "dhcp4_parser.cc"
    break;

  case 786: // logger_params: logger_params ","
#line 2759 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4407 "dhcp4_parser.cc"
    break;

  case 794: // debuglevel: "debuglevel" ":" "integer"
#line 2773 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4417 "dhcp4_parser.cc"
    break;

  case 795: // $@129: %empty
#line 2779 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4426 "dhcp4_parser.cc"
    break;

  case 796: // severity: "severity" $@129 ":" "constant string"
#line 2782 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4436 "dhcp4_parser.cc"
    break;

  case 797: // $@130: %empty
#line 2788 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4448 "dhcp4_parser.cc"
    break;

  case 798: // output_options_list: "output_options" $@130 ":" "[" output_options_list_content "]"
#line 2794 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4457 "dhcp4_parser.cc"
    break;

  case 801: // output_options_list_content: output_options_list_content ","
#line 2801 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4465 "dhcp4_parser.cc"
    break;

  case 802: // $@131: %empty
#line 2806 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4475 "dhcp4_parser.cc"
    break;

  case 803: // output_entry: "{" $@131 output_params_list "}"
#line 2810 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4483 "dhcp4_parser.cc"
    break;

  case 806: // output_params_list: output_params_list ","
#line 2816 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4491 "dhcp4_parser.cc"
    break;

  case 812: // $@132: %empty
#line 2828 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4500 "dhcp4_parser.cc"
    break;

  case 813: // output: "output" $@132 ":" "constant string"
#line 2831 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4510 "dhcp4_parser.cc"
    break;

  case 814: // flush: "flush" ":" "boolean"
#line 2837 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4520 "dhcp4_parser.cc"
    break;

  case 815: // maxsize: "maxsize" ":" "integer"
#line 2843 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4530 "dhcp4_parser.cc"
    break;

  case 816: // maxver: "maxver" ":" "integer"
#line 2849 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4540 "dhcp4_parser.cc"
    break;

  case 817: // $@133: %empty
#line 2855 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4549 "dhcp4_parser.cc"
    break;

  case 818: // pattern: "pattern" $@133 ":" "constant string"
#line 2858 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4559 "dhcp4_parser.cc"
    break;

  case 819: // $@134: %empty
#line 2864 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4571 "dhcp4_parser.cc"
    break;

  case 820: // compatibility: "compatibility" $@134 ":" "{" compatibility_params "}"
#line 2870 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4580 "dhcp4_parser.cc"
    break;

  case 823: // compatibility_params: compatibility_params ","
#line 2877 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4588 "dhcp4_parser.cc"
    break;

  case 827: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2887 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4598 "dhcp4_parser.cc"
    break;

  case 828: // ignore-rai-link-selection: "ignore-rai-link-selection" ":" "boolean"
#line 2893 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4608 "dhcp4_parser.cc"
    break;


#line 4612 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -974;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     218,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,    54,    44,    15,    57,    65,    67,
      74,    78,    86,    88,   103,   113,   134,   136,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,    44,  -155,    94,   140,   123,   271,
      76,   278,    80,    -6,   175,   -97,   636,    32,  -974,   177,
     186,   187,   185,   197,  -974,    49,  -974,  -974,  -974,  -974,
     221,   243,   254,  -974,  -974,  -974,  -974,  -974,  -974,   292,
     296,   327,   340,   351,   361,   367,   369,   386,   404,   425,
    -974,   432,   433,   434,   435,   436,  -974,  -974,  -974,   437,
     438,   439,  -974,  -974,  -974,   440,  -974,  -974,  -974,  -974,
     445,   447,   448,  -974,  -974,  -974,  -974,  -974,   449,  -974,
    -974,  -974,  -974,  -974,  -974,   450,   452,   454,  -974,  -974,
     457,  -974,    72,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
     458,   459,   461,   462,  -974,    97,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,   464,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
     115,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,   118,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,   267,   283,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,   284,
    -974,  -974,   468,  -974,  -974,  -974,   471,  -974,  -974,   354,
     474,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,   475,   476,  -974,  -974,  -974,  -974,
     479,   481,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,   125,  -974,  -974,  -974,   484,  -974,
    -974,   486,  -974,   489,   491,  -974,  -974,   494,   498,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,   128,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,   500,   141,  -974,  -974,  -974,  -974,
      44,    44,  -974,   300,   502,  -974,  -974,   503,   504,   506,
     307,   309,   310,   507,   510,   518,   520,   521,   522,   321,
     322,   323,   329,   330,   332,   334,   336,   337,   331,   339,
     526,   341,   342,   338,   343,   345,   552,   553,   555,   355,
     363,   366,   560,   562,   565,   370,   573,   577,   578,   580,
     377,   378,   379,   584,   585,   586,   587,   588,   387,   590,
     591,   595,   596,   597,   598,   395,   396,   397,   602,   603,
    -974,   140,  -974,   604,   605,   607,   405,   426,   406,   430,
     123,  -974,   633,   634,   635,   637,   638,   639,   441,   640,
     641,   642,   271,  -974,   645,    76,  -974,   646,   647,   651,
     652,   654,   655,   656,   657,  -974,   278,  -974,   659,   660,
     460,   661,   667,   669,   466,  -974,    -6,   671,   469,   478,
    -974,   175,   683,   684,    47,  -974,   482,   685,   691,   490,
     693,   492,   495,   696,   698,   496,   497,   699,   702,   703,
     704,   636,  -974,   715,   514,    32,  -974,  -974,  -974,   717,
     734,   735,   736,   737,  -974,  -974,  -974,   517,   540,   541,
     740,   741,   744,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,   545,  -974,  -974,  -974,  -974,  -974,
     -58,   548,   550,  -974,  -974,  -974,   752,   753,   754,  -974,
     755,   757,   563,   288,  -974,  -974,  -974,   760,   762,   766,
     767,   768,  -974,   769,   772,   773,   774,   568,   569,  -974,
    -974,  -974,   777,   776,  -974,   779,   228,   286,  -974,  -974,
    -974,  -974,  -974,   581,   582,   583,   780,   600,   601,  -974,
     779,   608,   782,  -974,   609,  -974,   779,   610,   611,   612,
     613,   614,   615,   616,  -974,   617,   620,  -974,   621,   622,
     623,  -974,  -974,   624,  -974,  -974,  -974,   625,   757,  -974,
    -974,   626,   627,  -974,   628,  -974,  -974,    17,   470,  -974,
    -974,   -58,   629,   630,   631,  -974,   785,  -974,  -974,    44,
     140,    32,   123,   315,  -974,  -974,  -974,   572,   572,   784,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,   800,
     801,   802,   803,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,   135,   830,   831,   832,   184,   -44,    92,    84,   636,
    -974,  -974,   833,  -150,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,   835,  -974,  -974,  -974,  -974,
     303,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,   784,
    -974,   182,   189,   269,  -974,  -974,   279,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,   839,   840,   841,   842,   843,   844,
     845,  -974,   846,  -974,  -974,  -974,  -974,  -974,   282,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,   290,  -974,
     848,   849,  -974,  -974,   850,   852,  -974,  -974,   851,   855,
    -974,  -974,   853,   857,  -974,  -974,   856,   858,  -974,  -974,
    -974,  -974,  -974,  -974,   149,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,   161,  -974,  -974,   859,   860,  -974,  -974,   861,
     863,  -974,   847,   864,   865,   866,   867,   868,   291,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,   869,   870,   871,  -974,
     305,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,   306,  -974,  -974,  -974,   872,  -974,   873,  -974,
    -974,  -974,   356,  -974,  -974,  -974,  -974,  -974,   358,  -974,
     268,  -974,   874,   875,  -974,   360,  -974,  -974,  -974,   675,
    -974,   876,   878,  -974,  -974,  -974,  -974,   877,   880,  -974,
    -974,  -974,   879,   883,   315,  -974,   884,   885,   886,   887,
     658,   676,   686,   687,   688,   690,   692,   889,   694,   893,
     895,   897,   898,   572,  -974,  -974,   572,  -974,   784,   271,
    -974,   800,    -6,  -974,   801,   175,  -974,   802,   648,  -974,
     803,   135,  -974,   564,   830,  -974,   278,  -974,   831,   -97,
    -974,   832,   697,   700,   701,   705,   707,   708,   184,  -974,
     709,   710,   714,   -44,  -974,   900,   901,    92,  -974,   720,
     904,   729,   905,    84,  -974,  -974,   -21,   833,  -974,   739,
     746,  -150,  -974,  -974,   936,   907,    76,  -974,   835,   951,
    -974,  -974,   787,   789,  -974,    22,   795,   798,   806,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,   178,  -974,   819,   862,
     881,   882,  -974,   380,  -974,   384,  -974,   949,  -974,   952,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,   388,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,   970,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
     969,   981,  -974,  -974,  -974,  -974,  -974,  -974,   997,  -974,
     420,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,   888,   890,  -974,  -974,   891,  -974,    44,
    -974,  -974,   985,  -974,  -974,  -974,  -974,  -974,   422,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,   892,   423,
    -974,   779,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,   648,  -974,  1049,  1051,   854,  -974,   564,
    -974,  -974,  -974,  -974,  -974,  -974,  1053,   896,  1054,   -21,
    -974,  -974,  -974,  -974,  -974,   894,   899,  -974,  -974,  1055,
    -974,   902,  -974,  -974,  -974,  1056,  -974,  -974,   324,  -974,
     -29,  1056,  -974,  -974,  1057,  1060,  1061,  -974,   424,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  1062,   903,   906,   908,
    1064,   -29,  -974,   910,  -974,  -974,  -974,   911,  -974,  -974,
    -974
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   192,     9,   364,    11,   572,    13,
     599,    15,   492,    17,   501,    19,   540,    21,   326,    23,
     716,    25,   767,    27,    46,    39,     0,     0,     0,     0,
       0,   601,     0,   503,   542,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   765,   177,   210,
       0,     0,     0,   621,   623,   625,   208,   221,   223,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,     0,     0,     0,     0,   154,   161,   163,     0,
       0,     0,   355,   490,   531,     0,   438,   586,   588,   431,
       0,     0,     0,   288,   649,   590,   317,   338,     0,   303,
     683,   697,   714,   167,   169,     0,     0,     0,   777,   819,
       0,   133,     0,    67,    70,    71,    72,    73,    74,   108,
     109,   110,   111,   112,    75,   103,   132,    92,    93,    94,
     116,   117,   118,   119,   120,   121,   122,   123,   114,   115,
     124,   125,   126,   128,   129,   130,    78,    79,   100,    80,
      81,    82,   127,    86,    87,    76,   105,   106,   107,   104,
      77,    84,    85,    98,    99,   101,    95,    96,    97,    83,
      88,    89,    90,    91,   102,   113,   131,   194,   196,   200,
       0,     0,     0,     0,   191,     0,   179,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   416,   418,   420,   563,
     414,   422,     0,   426,   424,   645,   413,   369,   370,   371,
     372,   373,   397,   398,   399,   400,   401,   387,   388,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   411,   412,
       0,   366,   376,   392,   393,   394,   377,   379,   380,   383,
     384,   385,   382,   378,   374,   375,   395,   396,   381,   389,
     390,   391,   386,   584,   583,   579,   580,   578,     0,   574,
     577,   581,   582,   643,   631,   633,   637,   635,   641,   639,
     627,   620,   614,   618,   619,     0,   602,   603,   615,   616,
     617,   611,   606,   612,   608,   609,   610,   613,   607,     0,
     521,   266,     0,   525,   523,   528,     0,   517,   518,     0,
     504,   505,   508,   520,   509,   510,   511,   527,   512,   513,
     514,   515,   516,   557,     0,     0,   555,   556,   559,   560,
       0,   543,   544,   547,   548,   549,   550,   551,   552,   553,
     554,   334,   336,   331,     0,   328,   332,   333,     0,   753,
     740,     0,   743,     0,     0,   747,   751,     0,     0,   757,
     759,   761,   763,   738,   736,   737,     0,   718,   721,   722,
     723,   724,   725,   726,   727,   728,   733,   729,   730,   731,
     732,   734,   735,   774,     0,     0,   769,   772,   773,    45,
      50,     0,    37,    43,     0,    64,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    69,    66,     0,     0,     0,     0,     0,     0,     0,
     181,   193,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   368,   365,     0,   576,   573,     0,     0,     0,
       0,     0,     0,     0,     0,   600,   605,   493,     0,     0,
       0,     0,     0,     0,     0,   502,   507,     0,     0,     0,
     541,   546,     0,     0,   330,   327,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   720,   717,     0,     0,   771,   768,    49,    41,     0,
       0,     0,     0,     0,   148,   149,   150,     0,     0,     0,
       0,     0,     0,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,   172,   173,   151,   152,   153,
       0,     0,     0,   165,   166,   171,     0,     0,     0,   147,
       0,     0,     0,     0,   428,   429,   430,     0,     0,     0,
       0,     0,   682,     0,     0,     0,     0,     0,     0,   174,
     175,   176,     0,     0,    68,     0,     0,     0,   204,   205,
     206,   207,   180,     0,     0,     0,     0,     0,     0,   437,
       0,     0,     0,   367,     0,   575,     0,     0,     0,     0,
       0,     0,     0,     0,   604,     0,     0,   519,     0,     0,
       0,   530,   506,     0,   561,   562,   545,     0,     0,   329,
     739,     0,     0,   742,     0,   745,   746,     0,     0,   755,
     756,     0,     0,     0,     0,   719,     0,   776,   770,     0,
       0,     0,     0,     0,   622,   624,   626,     0,     0,   225,
     146,   156,   157,   158,   159,   160,   155,   162,   164,   357,
     494,   533,   440,    38,   587,   589,   433,   434,   435,   436,
     432,     0,     0,   592,   319,     0,     0,     0,     0,     0,
     168,   170,     0,     0,    51,   195,   198,   199,   197,   202,
     203,   201,   417,   419,   421,   565,   415,   423,   427,   425,
       0,   585,   644,   632,   634,   638,   636,   642,   640,   628,
     522,   267,   526,   524,   529,   558,   335,   337,   754,   741,
     744,   749,   750,   748,   752,   758,   760,   762,   764,   225,
      42,     0,     0,     0,   217,   219,     0,   212,   215,   216,
     254,   259,   261,   263,     0,     0,     0,     0,     0,     0,
       0,   274,     0,   280,   282,   284,   286,   253,     0,   232,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,     0,   230,
       0,   226,   227,   362,     0,   358,   359,   499,     0,   495,
     496,   538,     0,   534,   535,   445,     0,   441,   442,   298,
     299,   300,   301,   302,     0,   290,   293,   294,   295,   296,
     297,   654,     0,   651,   597,     0,   593,   594,   324,     0,
     320,   321,     0,     0,     0,     0,     0,     0,     0,   340,
     343,   344,   345,   346,   347,   348,     0,     0,     0,   313,
       0,   305,   308,   309,   310,   311,   312,   693,   695,   692,
     690,   691,     0,   685,   688,   689,     0,   709,     0,   712,
     705,   706,     0,   699,   702,   703,   704,   707,     0,   782,
       0,   779,     0,     0,   826,     0,   821,   824,   825,    53,
     570,     0,   566,   567,   629,   647,   648,     0,     0,    62,
     766,   178,     0,     0,   214,   211,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   209,   222,     0,   224,   229,     0,
     356,   361,   503,   491,   498,   542,   532,   537,     0,   439,
     444,   292,   289,   656,   653,   650,   601,   591,   596,     0,
     318,   323,     0,     0,     0,     0,     0,     0,   342,   339,
       0,     0,     0,   307,   304,     0,     0,   687,   684,     0,
       0,     0,     0,   701,   698,   715,     0,   781,   778,     0,
       0,   823,   820,    55,     0,    54,     0,   564,   569,     0,
     646,   775,     0,     0,   213,     0,     0,     0,     0,   265,
     268,   269,   270,   271,   272,   273,     0,   279,     0,     0,
       0,     0,   233,     0,   228,     0,   360,     0,   497,     0,
     536,   489,   468,   469,   470,   453,   454,   473,   474,   475,
     476,   477,   456,   457,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,   450,   451,   452,   466,   467,
     463,   464,   465,   462,     0,   447,   455,   471,   472,   458,
     459,   460,   461,   443,   291,   677,   679,     0,   672,   673,
     674,   675,   676,   665,   666,   670,   671,   667,   668,   669,
       0,   657,   658,   661,   662,   663,   664,   652,     0,   595,
       0,   322,   349,   350,   351,   352,   353,   354,   341,   314,
     315,   316,   306,     0,     0,   686,   708,     0,   711,     0,
     700,   797,     0,   795,   793,   787,   791,   792,     0,   784,
     789,   790,   788,   780,   827,   828,   822,    52,    57,     0,
     568,     0,   218,   220,   256,   257,   258,   255,   260,   262,
     264,   276,   277,   278,   275,   281,   283,   285,   287,   231,
     363,   500,   539,   449,   446,     0,     0,     0,   655,   660,
     598,   325,   694,   696,   710,   713,     0,     0,     0,   786,
     783,    56,   571,   630,   448,     0,     0,   681,   659,     0,
     794,     0,   785,   678,   680,     0,   796,   802,     0,   799,
       0,   801,   798,   812,     0,     0,     0,   817,     0,   804,
     807,   808,   809,   810,   811,   800,     0,     0,     0,     0,
       0,   806,   803,     0,   814,   815,   816,     0,   805,   813,
     818
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,   -51,  -974,  -584,  -974,   391,
    -974,  -974,  -974,  -974,  -974,  -974,  -620,  -974,  -974,  -974,
     -67,  -974,  -974,  -974,  -974,  -974,  -974,  -974,   371,   579,
     -26,     9,    19,   -52,   -30,   -27,     7,    20,    27,    30,
    -974,  -974,  -974,  -974,  -974,    37,    38,    40,    42,    43,
      48,  -974,   381,    50,  -974,    53,  -974,    55,    56,    58,
    -974,    60,  -974,    61,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,   372,   575,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,   119,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,   287,  -974,    99,  -974,  -696,   105,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,   -63,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
      89,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,    69,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,    82,  -974,  -974,
    -974,    85,   535,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
      73,  -974,  -974,  -974,  -974,  -974,  -974,  -973,  -974,  -974,
    -974,   104,  -974,  -974,  -974,   109,   589,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -969,  -974,   -65,  -974,    64,
    -974,    63,    66,    68,    71,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,   100,  -974,  -974,  -114,   -54,  -974,  -974,  -974,
    -974,  -974,   107,  -974,  -974,  -974,   110,  -974,   558,  -974,
     -41,  -974,  -974,  -974,  -974,  -974,   -40,  -974,  -974,  -974,
    -974,  -974,   -23,  -974,  -974,  -974,   111,  -974,  -974,  -974,
     120,  -974,   576,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,    75,  -974,  -974,  -974,    70,   594,
    -974,  -974,   -45,  -974,    -3,  -974,   -48,  -974,  -974,  -974,
     112,  -974,  -974,  -974,   122,  -974,   593,   -55,  -974,   -13,
    -974,     8,  -974,   362,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -968,  -974,  -974,  -974,  -974,  -974,   126,  -974,  -974,
    -974,  -106,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,   106,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
      98,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,   385,   566,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,   427,   561,  -974,  -974,  -974,  -974,  -974,  -974,
     102,  -974,  -974,   -94,  -974,  -974,  -974,  -974,  -974,  -974,
    -111,  -974,  -974,  -130,  -974,  -974,  -974,  -974,  -974,  -974,
    -974,  -974,  -974,  -974,   101,  -974,  -974
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   724,
      82,    83,    39,    64,    79,    80,   745,   939,  1034,  1035,
     817,    41,    66,    85,   424,    86,    43,    67,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   450,   166,   167,   168,   169,   170,   171,   172,
     173,   456,   716,   174,   457,   175,   458,   176,   177,   178,
     483,   179,   484,   180,   181,   182,   183,   184,   185,   186,
     428,   225,   226,    45,    68,   227,   493,   228,   494,   748,
     229,   495,   751,   230,   231,   232,   233,   187,   436,   188,
     429,   796,   797,   798,   952,   799,   953,   189,   437,   190,
     438,   840,   841,   842,   976,   818,   819,   820,   956,  1187,
     821,   957,   822,   958,   823,   959,   824,   825,   529,   826,
     827,   828,   829,   830,   831,   832,   967,  1194,   833,   834,
     969,   835,   970,   836,   971,   837,   972,   191,   473,   864,
     865,   866,   867,   868,   869,   870,   192,   479,   900,   901,
     902,   903,   904,   193,   476,   879,   880,   881,   999,    59,
      75,   374,   375,   376,   542,   377,   543,   194,   477,   888,
     889,   890,   891,   892,   893,   894,   895,   195,   462,   844,
     845,   846,   979,    47,    69,   270,   271,   272,   506,   273,
     502,   274,   503,   275,   504,   276,   507,   277,   510,   278,
     509,   196,   197,   198,   199,   469,   730,   283,   200,   466,
     856,   857,   858,   988,  1104,  1105,   201,   463,    53,    72,
     848,   849,   850,   982,    55,    73,   339,   340,   341,   342,
     343,   344,   345,   528,   346,   532,   347,   531,   348,   349,
     533,   350,   202,   464,   852,   853,   854,   985,    57,    74,
     360,   361,   362,   363,   364,   537,   365,   366,   367,   368,
     285,   505,   941,   942,   943,  1036,    49,    70,   298,   299,
     300,   514,   203,   467,   204,   468,   205,   475,   875,   876,
     877,   996,    51,    71,   315,   316,   317,   206,   433,   207,
     434,   208,   435,   321,   524,   946,  1039,   322,   518,   323,
     519,   324,   521,   325,   520,   326,   523,   327,   522,   328,
     517,   292,   511,   947,   209,   474,   872,   873,   993,  1130,
    1131,  1132,  1133,  1134,  1205,  1135,  1206,  1136,   210,   211,
     480,   912,   913,   914,  1015,   915,  1016,   212,   481,   922,
     923,   924,   925,  1020,   926,   927,  1022,   213,   482,    61,
      76,   396,   397,   398,   399,   548,   400,   401,   550,   402,
     403,   404,   553,   783,   405,   554,   406,   547,   407,   408,
     409,   557,   410,   558,   411,   559,   412,   560,   214,   427,
      63,    77,   415,   416,   417,   563,   418,   215,   488,   930,
     931,  1026,  1168,  1169,  1170,  1171,  1218,  1172,  1216,  1238,
    1239,  1240,  1248,  1249,  1250,  1256,  1251,  1252,  1253,  1254,
    1260,   216,   489,   935,   936,   937,   938
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     151,   224,   246,   294,   311,   295,   337,   356,   373,   393,
     338,   357,   838,    78,   289,  1096,   318,   250,   329,  1097,
    1112,   288,    40,   234,   286,   301,   313,   723,   351,   369,
     758,   394,   330,   358,   359,   781,   762,   371,   372,   251,
     932,   933,   252,   247,   413,   414,   284,   297,   312,    29,
      81,    30,   425,    31,    28,   150,   290,   426,   319,   127,
     128,  1184,  1185,  1186,    42,   235,   287,   302,   314,   331,
     352,   370,    44,   395,    46,   491,   253,   291,   248,   320,
     492,    48,   127,   128,   331,    50,   332,   333,   249,   254,
     334,   335,   336,    52,   723,    54,   255,   127,   128,   256,
     500,   896,   897,   898,    84,   501,   257,   258,   150,   259,
      56,   260,   261,   711,   712,   713,   714,   262,   512,   263,
      58,   515,   264,   513,   265,   266,   516,   267,   544,   268,
     269,   561,   279,   545,   296,   280,   562,   281,   217,   218,
     282,    60,   219,    62,   565,   220,   221,   222,   223,   566,
     715,    87,   991,  1243,    88,   992,  1244,  1245,  1246,  1247,
    1161,   150,  1162,  1163,   994,   124,    89,   995,   123,    90,
      91,    92,    93,    94,    95,    96,    97,    98,   293,   127,
     128,   371,   372,   419,   150,   491,   782,   127,   128,   420,
     949,   421,   565,   422,   243,   127,   128,   950,   244,   150,
     423,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   430,   127,   128,   123,   124,
    1096,  1191,  1192,  1193,  1097,  1112,   916,   917,   918,   125,
     126,   907,   908,   127,   128,   746,   747,   431,   129,    32,
      33,    34,    35,   130,   131,   132,   133,   134,   432,   859,
     860,   861,   862,   135,   863,   331,   353,   332,   333,   354,
     355,  1027,   500,   136,  1028,   525,   137,   951,   127,   128,
    1063,   150,   954,   138,   139,   973,   526,   955,   140,   919,
     974,   141,   527,   973,  1008,   142,   439,   150,   975,  1009,
     440,    91,    92,    93,    94,    95,   749,   750,  1013,  1017,
      93,    94,    95,  1014,  1018,   143,   144,   145,   146,   147,
     148,   882,   883,   884,   885,   886,   887,  1241,   150,   149,
    1242,   441,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   794,   795,   442,   150,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   443,   236,   237,   238,  1023,
     124,   561,   535,  1031,  1024,   444,  1025,   124,  1032,   567,
     568,   445,   239,   446,   127,   128,   240,   241,   242,   129,
     150,   127,   128,   973,   130,   131,   132,   512,  1199,   243,
     447,  1203,  1200,   244,   135,   303,  1204,   726,   727,   728,
     729,   245,   304,   305,   306,   307,   308,   309,   448,   310,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   544,   151,  1219,   515,  1261,  1211,   449,
    1220,  1222,  1262,   224,   310,   944,   451,   452,   453,   454,
     455,   459,   460,   461,   465,   246,   143,   144,   294,   470,
     295,   471,   472,   478,   485,   234,   486,   289,   487,   311,
     250,   490,   496,   497,   288,   498,   499,   286,   508,   337,
     301,   318,   530,   338,   356,   534,   150,   536,   357,   538,
     539,   313,   251,   150,   541,   252,   247,   540,   546,   284,
     549,   351,   297,   551,   393,   552,   369,   235,   555,   290,
     358,   359,   556,   312,   564,   569,   570,   571,   572,   287,
     573,   577,   302,   319,   578,   574,   394,   575,   576,   253,
     291,   248,   579,   314,   580,   581,   582,   583,   584,   585,
     594,   249,   254,   352,   320,   586,   587,   592,   370,   255,
     588,   589,   256,   590,   591,   593,   597,   595,   596,   257,
     258,   598,   259,   599,   260,   261,   600,   601,   395,   602,
     262,  1223,   263,   603,   606,   264,   607,   265,   266,   608,
     267,   604,   268,   269,   605,   279,   609,   610,   280,   296,
     281,   611,   612,   282,   613,   614,   615,   616,   617,   618,
     619,   620,   621,   622,   623,   624,    93,    94,    95,   625,
     626,   627,   628,   629,   630,   631,   632,   633,   635,   636,
     800,   637,   640,   638,   801,   802,   803,   804,   805,   806,
     807,   808,   809,   810,   811,    99,   100,   101,   812,   813,
     814,   815,   816,   151,   639,   224,   641,   643,   644,   645,
     784,   646,   647,   648,   650,   651,   652,   649,   790,   654,
     656,   657,   123,   124,   331,   658,   659,   234,   660,   661,
     662,   663,   331,   665,   666,   668,   667,   127,   128,   899,
     909,   669,   393,   670,   671,   673,   934,   674,    91,    92,
      93,    94,    95,  1115,  1116,  1117,   675,   677,   678,   681,
     680,   905,   910,   920,   394,   682,   683,   684,   685,   235,
     687,   686,   688,   691,   689,   690,   692,   693,   694,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   696,
     697,   699,   704,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   906,   911,   921,   395,   124,   331,   127,
     128,   700,   701,   702,   703,   705,   706,   707,   708,   709,
     710,   127,   128,   717,   241,   718,   129,   719,   720,   721,
     722,   130,   131,   132,    30,   731,   243,   732,   725,   150,
     244,   733,   734,   740,   741,   735,   736,   150,   245,   737,
     738,   739,   742,   743,   744,   755,   752,   753,   754,   760,
     789,   839,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   756,   757,   843,   847,   851,
     855,   391,   392,   759,   761,   763,   764,   765,   766,   767,
     768,   769,   770,   143,   144,   771,   772,   773,   774,   775,
     776,   778,   779,   780,   786,   787,   788,   871,   874,   878,
     929,   150,   940,   960,   961,   962,   963,   964,   965,   966,
     968,  1002,   978,   150,   977,   981,   980,   983,   984,   986,
     987,   990,   989,   998,  1049,   997,  1001,  1000,  1003,  1004,
    1005,  1006,  1007,  1010,  1011,  1012,  1019,  1021,  1029,  1030,
    1033,  1038,  1037,  1042,  1050,  1040,  1041,  1043,  1045,  1046,
    1047,  1048,  1051,  1056,  1053,  1052,  1054,  1058,  1055,  1059,
    1057,  1060,  1061,  1142,  1153,  1154,  1143,  1144,  1157,  1159,
    1178,  1145,   246,  1146,  1147,   337,  1150,  1149,   356,   338,
    1151,  1071,   357,  1098,   289,  1095,  1118,   250,  1156,   311,
    1122,   288,   373,  1109,   286,  1158,  1075,   351,  1127,  1123,
     369,   318,  1177,  1107,   358,   359,   899,  1174,  1125,   251,
     909,   313,   252,   247,  1175,  1181,   284,  1201,  1076,  1164,
    1202,  1077,  1072,  1165,   934,  1106,   290,  1119,   905,   294,
    1124,   295,   910,   312,  1207,  1110,   287,  1208,   920,   352,
    1128,  1166,   370,   319,  1209,  1108,   253,   291,   248,  1217,
    1126,   301,  1182,   314,  1183,  1078,  1111,  1073,   249,   254,
    1188,  1129,  1120,  1189,   320,  1210,   255,  1074,  1079,   256,
     906,  1190,  1121,   297,   911,  1080,   257,   258,  1081,   259,
     921,   260,   261,  1167,  1195,  1082,  1083,   262,  1084,   263,
    1085,  1086,   264,   302,   265,   266,  1087,   267,  1088,   268,
     269,  1089,   279,  1090,  1091,   280,  1092,   281,  1093,  1094,
     282,  1100,  1099,  1225,  1101,  1226,  1102,  1229,  1231,  1103,
    1235,  1257,  1227,  1237,  1258,  1259,  1263,  1196,  1267,   777,
     634,   791,   785,  1044,   793,   642,   948,  1064,  1062,   679,
    1114,  1148,  1152,  1141,  1140,  1066,  1197,  1198,  1065,  1224,
    1113,  1068,  1067,  1212,   672,  1213,  1214,  1221,  1070,  1233,
     296,   653,  1230,  1228,  1234,  1069,  1179,  1236,  1215,   655,
    1139,  1264,  1265,  1180,  1266,  1269,  1270,   676,  1138,   664,
    1137,  1160,   945,  1155,   928,  1232,   698,   695,   792,  1173,
    1255,  1268,  1176,     0,     0,     0,  1071,     0,  1098,     0,
    1095,     0,  1118,     0,     0,     0,  1122,     0,  1109,     0,
       0,  1075,  1164,     0,  1127,  1123,  1165,     0,  1107,     0,
       0,     0,     0,     0,  1125,     0,     0,     0,     0,     0,
       0,     0,     0,  1076,  1166,     0,  1077,  1072,     0,     0,
    1106,     0,     0,  1119,     0,     0,  1124,     0,     0,     0,
    1110,     0,     0,     0,     0,     0,  1128,     0,     0,     0,
    1108,     0,     0,     0,     0,     0,  1126,     0,     0,     0,
    1078,  1111,  1073,     0,     0,     0,  1167,  1129,  1120,     0,
       0,     0,  1074,  1079,     0,     0,     0,     0,  1121,     0,
    1080,     0,     0,  1081,     0,     0,     0,     0,     0,     0,
    1082,  1083,     0,  1084,     0,  1085,  1086,     0,     0,     0,
       0,  1087,     0,  1088,     0,     0,  1089,     0,  1090,  1091,
       0,  1092,     0,  1093,  1094,     0,  1100,  1099,     0,  1101,
       0,  1102,     0,     0,  1103
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,   708,    64,    69,   988,    71,    69,    72,   988,
     988,    69,     7,    68,    69,    70,    71,   611,    73,    74,
     650,    76,    38,    74,    74,    18,   656,   134,   135,    69,
     190,   191,    69,    69,    12,    13,    69,    70,    71,     5,
     205,     7,     3,     9,     0,   205,    69,     8,    71,   103,
     104,    39,    40,    41,     7,    68,    69,    70,    71,    90,
      73,    74,     7,    76,     7,     3,    69,    69,    69,    71,
       8,     7,   103,   104,    90,     7,    92,    93,    69,    69,
      96,    97,    98,     7,   678,     7,    69,   103,   104,    69,
       3,   145,   146,   147,    10,     8,    69,    69,   205,    69,
       7,    69,    69,   171,   172,   173,   174,    69,     3,    69,
       7,     3,    69,     8,    69,    69,     8,    69,     3,    69,
      69,     3,    69,     8,    70,    69,     8,    69,    15,    16,
      69,     7,    19,     7,     3,    22,    23,    24,    25,     8,
     208,    11,     3,   182,    14,     6,   185,   186,   187,   188,
     181,   205,   183,   184,     3,    89,    26,     6,    88,    29,
      30,    31,    32,    33,    34,    35,    36,    37,   102,   103,
     104,   134,   135,     6,   205,     3,   169,   103,   104,     3,
       8,     4,     3,     8,   118,   103,   104,     8,   122,   205,
       3,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,     4,   103,   104,    88,    89,
    1203,    53,    54,    55,  1203,  1203,   152,   153,   154,    99,
     100,   149,   150,   103,   104,    17,    18,     4,   108,   205,
     206,   207,   208,   113,   114,   115,   116,   117,     4,   124,
     125,   126,   127,   123,   129,    90,    91,    92,    93,    94,
      95,     3,     3,   133,     6,     8,   136,     8,   103,   104,
     976,   205,     3,   143,   144,     3,     3,     8,   148,   205,
       8,   151,     8,     3,     3,   155,     4,   205,     8,     8,
       4,    30,    31,    32,    33,    34,    20,    21,     3,     3,
      32,    33,    34,     8,     8,   175,   176,   177,   178,   179,
     180,   137,   138,   139,   140,   141,   142,     3,   205,   189,
       6,     4,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    27,    28,     4,   205,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     4,    85,    86,    87,     3,
      89,     3,     8,     3,     8,     4,     8,    89,     8,   420,
     421,     4,   101,     4,   103,   104,   105,   106,   107,   108,
     205,   103,   104,     3,   113,   114,   115,     3,     8,   118,
       4,     3,     8,   122,   123,   117,     8,   109,   110,   111,
     112,   130,   124,   125,   126,   127,   128,   129,     4,   131,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,     3,   491,     3,     3,     3,     8,     4,
       8,     8,     8,   500,   131,   132,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   512,   175,   176,   515,     4,
     515,     4,     4,     4,     4,   500,     4,   512,     4,   526,
     512,     4,     4,     4,   512,     4,     4,   512,     4,   536,
     515,   526,     4,   536,   541,     4,   205,     3,   541,     4,
       4,   526,   512,   205,     3,   512,   512,     8,     4,   512,
       4,   536,   515,     4,   561,     4,   541,   500,     4,   512,
     541,   541,     4,   526,     4,   205,     4,     4,     4,   512,
       4,     4,   515,   526,     4,   208,   561,   208,   208,   512,
     512,   512,     4,   526,     4,     4,     4,   206,   206,   206,
       4,   512,   512,   536,   526,   206,   206,   206,   541,   512,
     208,   207,   512,   207,   207,   206,   208,   206,   206,   512,
     512,   208,   512,   208,   512,   512,     4,     4,   561,     4,
     512,  1181,   512,   208,     4,   512,     4,   512,   512,     4,
     512,   208,   512,   512,   208,   512,   206,     4,   512,   515,
     512,     4,     4,   512,     4,   208,   208,   208,     4,     4,
       4,     4,     4,   206,     4,     4,    32,    33,    34,     4,
       4,     4,     4,   208,   208,   208,     4,     4,     4,     4,
      38,     4,   206,   208,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    61,    62,    63,    56,    57,
      58,    59,    60,   700,   208,   702,   206,     4,     4,     4,
     170,     4,     4,     4,     4,     4,     4,   206,   699,     4,
       4,     4,    88,    89,    90,     4,     4,   702,     4,     4,
       4,     4,    90,     4,     4,     4,   206,   103,   104,   736,
     737,     4,   739,     4,   208,     4,   743,   208,    30,    31,
      32,    33,    34,   119,   120,   121,   208,     4,     4,     4,
     208,   736,   737,   738,   739,     4,   206,     4,   206,   702,
       4,   206,     4,     4,   208,   208,     4,     4,     4,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,     4,
     206,     4,   205,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,   736,   737,   738,   739,    89,    90,   103,
     104,     7,     7,     7,     7,   205,   205,     7,     7,     5,
     205,   103,   104,   205,   106,   205,   108,     5,     5,     5,
       5,   113,   114,   115,     7,     5,   118,     5,   205,   205,
     122,     5,     5,   205,   205,     7,     7,   205,   130,     7,
       7,     7,     5,     7,     5,     5,   205,   205,   205,     7,
       5,     7,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   205,   205,     7,     7,     7,
       7,   175,   176,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   175,   176,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,     7,     7,     7,
       7,   205,     7,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   205,     6,     3,     6,     6,     3,     6,
       3,     3,     6,     3,   206,     6,     3,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     205,     3,     6,     4,   208,     8,     6,     4,     4,     4,
       4,     4,   206,     4,   206,   208,   206,     4,   206,     4,
     206,     4,     4,   206,     4,     4,   206,   206,     4,     4,
       3,   206,   979,   206,   206,   982,   206,   208,   985,   982,
     206,   988,   985,   988,   979,   988,   993,   979,   208,   996,
     993,   979,   999,   988,   979,   206,   988,   982,   993,   993,
     985,   996,     6,   988,   985,   985,  1013,   208,   993,   979,
    1017,   996,   979,   979,   208,     4,   979,     8,   988,  1026,
       8,   988,   988,  1026,  1031,   988,   979,   993,  1013,  1036,
     993,  1036,  1017,   996,     4,   988,   979,     8,  1023,   982,
     993,  1026,   985,   996,     3,   988,   979,   979,   979,     4,
     993,  1036,   205,   996,   205,   988,   988,   988,   979,   979,
     205,   993,   993,   205,   996,     8,   979,   988,   988,   979,
    1013,   205,   993,  1036,  1017,   988,   979,   979,   988,   979,
    1023,   979,   979,  1026,   205,   988,   988,   979,   988,   979,
     988,   988,   979,  1036,   979,   979,   988,   979,   988,   979,
     979,   988,   979,   988,   988,   979,   988,   979,   988,   988,
     979,   988,   988,     4,   988,     4,   988,     4,     4,   988,
       5,     4,   208,     7,     4,     4,     4,   205,     4,   678,
     491,   700,   691,   954,   702,   500,   789,   978,   973,   544,
     991,  1008,  1013,  1001,   999,   981,   205,   205,   979,  1203,
     990,   984,   982,   205,   536,   205,   205,   205,   987,   205,
    1036,   512,   206,  1209,   205,   985,  1036,   205,  1159,   515,
     998,   208,   206,  1038,   206,   205,   205,   541,   996,   526,
     994,  1023,   760,  1017,   739,  1219,   565,   561,   701,  1027,
    1241,  1261,  1031,    -1,    -1,    -1,  1203,    -1,  1203,    -1,
    1203,    -1,  1209,    -1,    -1,    -1,  1209,    -1,  1203,    -1,
      -1,  1203,  1219,    -1,  1209,  1209,  1219,    -1,  1203,    -1,
      -1,    -1,    -1,    -1,  1209,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1203,  1219,    -1,  1203,  1203,    -1,    -1,
    1203,    -1,    -1,  1209,    -1,    -1,  1209,    -1,    -1,    -1,
    1203,    -1,    -1,    -1,    -1,    -1,  1209,    -1,    -1,    -1,
    1203,    -1,    -1,    -1,    -1,    -1,  1209,    -1,    -1,    -1,
    1203,  1203,  1203,    -1,    -1,    -1,  1219,  1209,  1209,    -1,
      -1,    -1,  1203,  1203,    -1,    -1,    -1,    -1,  1209,    -1,
    1203,    -1,    -1,  1203,    -1,    -1,    -1,    -1,    -1,    -1,
    1203,  1203,    -1,  1203,    -1,  1203,  1203,    -1,    -1,    -1,
      -1,  1203,    -1,  1203,    -1,    -1,  1203,    -1,  1203,  1203,
      -1,  1203,    -1,  1203,  1203,    -1,  1203,  1203,    -1,  1203,
      -1,  1203,    -1,    -1,  1203
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,     0,     5,
       7,     9,   205,   206,   207,   208,   224,   225,   226,   231,
       7,   240,     7,   245,     7,   292,     7,   402,     7,   485,
       7,   501,     7,   437,     7,   443,     7,   467,     7,   378,
       7,   568,     7,   599,   232,   227,   241,   246,   293,   403,
     486,   502,   438,   444,   468,   379,   569,   600,   224,   233,
     234,   205,   229,   230,    10,   242,   244,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    88,    89,    99,   100,   103,   104,   108,
     113,   114,   115,   116,   117,   123,   133,   136,   143,   144,
     148,   151,   155,   175,   176,   177,   178,   179,   180,   189,
     205,   239,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   262,   263,   264,   265,
     266,   267,   268,   269,   272,   274,   276,   277,   278,   280,
     282,   283,   284,   285,   286,   287,   288,   306,   308,   316,
     318,   356,   365,   372,   386,   396,   420,   421,   422,   423,
     427,   435,   461,   491,   493,   495,   506,   508,   510,   533,
     547,   548,   556,   566,   597,   606,   630,    15,    16,    19,
      22,    23,    24,    25,   239,   290,   291,   294,   296,   299,
     302,   303,   304,   305,   491,   493,    85,    86,    87,   101,
     105,   106,   107,   118,   122,   130,   239,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   264,   265,   266,
     267,   268,   269,   272,   274,   276,   277,   278,   280,   282,
     404,   405,   406,   408,   410,   412,   414,   416,   418,   420,
     421,   422,   423,   426,   461,   479,   491,   493,   495,   506,
     508,   510,   530,   102,   239,   416,   418,   461,   487,   488,
     489,   491,   493,   117,   124,   125,   126,   127,   128,   129,
     131,   239,   461,   491,   493,   503,   504,   505,   506,   508,
     510,   512,   516,   518,   520,   522,   524,   526,   528,   435,
      38,    90,    92,    93,    96,    97,    98,   239,   336,   445,
     446,   447,   448,   449,   450,   451,   453,   455,   457,   458,
     460,   491,   493,    91,    94,    95,   239,   336,   449,   455,
     469,   470,   471,   472,   473,   475,   476,   477,   478,   491,
     493,   134,   135,   239,   380,   381,   382,   384,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   175,   176,   239,   491,   493,   570,   571,   572,   573,
     575,   576,   578,   579,   580,   583,   585,   587,   588,   589,
     591,   593,   595,    12,    13,   601,   602,   603,   605,     6,
       3,     4,     8,     3,   243,     3,     8,   598,   289,   309,
       4,     4,     4,   507,   509,   511,   307,   317,   319,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     261,     4,     4,     4,     4,     4,   270,   273,   275,     4,
       4,     4,   397,   436,   462,     4,   428,   492,   494,   424,
       4,     4,     4,   357,   534,   496,   373,   387,     4,   366,
     549,   557,   567,   279,   281,     4,     4,     4,   607,   631,
       4,     3,     8,   295,   297,   300,     4,     4,     4,     4,
       3,     8,   409,   411,   413,   480,   407,   415,     4,   419,
     417,   531,     3,     8,   490,     3,     8,   529,   517,   519,
     523,   521,   527,   525,   513,     8,     3,     8,   452,   337,
       4,   456,   454,   459,     4,     8,     3,   474,     4,     4,
       8,     3,   383,   385,     3,     8,     4,   586,   574,     4,
     577,     4,     4,   581,   584,     4,     4,   590,   592,   594,
     596,     3,     8,   604,     4,     3,     8,   224,   224,   205,
       4,     4,     4,     4,   208,   208,   208,     4,     4,     4,
       4,     4,     4,   206,   206,   206,   206,   206,   208,   207,
     207,   207,   206,   206,     4,   206,   206,   208,   208,   208,
       4,     4,     4,   208,   208,   208,     4,     4,     4,   206,
       4,     4,     4,     4,   208,   208,   208,     4,     4,     4,
       4,     4,   206,     4,     4,     4,     4,     4,     4,   208,
     208,   208,     4,     4,   248,     4,     4,     4,   208,   208,
     206,   206,   291,     4,     4,     4,     4,     4,     4,   206,
       4,     4,     4,   405,     4,   488,     4,     4,     4,     4,
       4,     4,     4,     4,   505,     4,     4,   206,     4,     4,
       4,   208,   447,     4,   208,   208,   471,     4,     4,   381,
     208,     4,     4,   206,     4,   206,   206,     4,     4,   208,
     208,     4,     4,     4,     4,   571,     4,   206,   602,     4,
       7,     7,     7,     7,   205,   205,   205,     7,     7,     5,
     205,   171,   172,   173,   174,   208,   271,   205,   205,     5,
       5,     5,     5,   226,   228,   205,   109,   110,   111,   112,
     425,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     205,   205,     5,     7,     5,   235,    17,    18,   298,    20,
      21,   301,   205,   205,   205,     5,   205,   205,   235,   205,
       7,   205,   235,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   228,   205,   205,
     205,    18,   169,   582,   170,   271,   205,   205,   205,     5,
     224,   247,   601,   290,    27,    28,   310,   311,   312,   314,
      38,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    56,    57,    58,    59,    60,   239,   324,   325,
     326,   329,   331,   333,   335,   336,   338,   339,   340,   341,
     342,   343,   344,   347,   348,   350,   352,   354,   324,     7,
     320,   321,   322,     7,   398,   399,   400,     7,   439,   440,
     441,     7,   463,   464,   465,     7,   429,   430,   431,   124,
     125,   126,   127,   129,   358,   359,   360,   361,   362,   363,
     364,     7,   535,   536,     7,   497,   498,   499,     7,   374,
     375,   376,   137,   138,   139,   140,   141,   142,   388,   389,
     390,   391,   392,   393,   394,   395,   145,   146,   147,   239,
     367,   368,   369,   370,   371,   491,   493,   149,   150,   239,
     491,   493,   550,   551,   552,   554,   152,   153,   154,   205,
     491,   493,   558,   559,   560,   561,   563,   564,   570,     7,
     608,   609,   190,   191,   239,   632,   633,   634,   635,   236,
       7,   481,   482,   483,   132,   512,   514,   532,   320,     8,
       8,     8,   313,   315,     3,     8,   327,   330,   332,   334,
       4,     4,     4,     4,     4,     4,     4,   345,     4,   349,
     351,   353,   355,     3,     8,     8,   323,     6,     3,   401,
       6,     3,   442,     6,     3,   466,     6,     3,   432,     6,
       3,     3,     6,   537,     3,     6,   500,     6,     3,   377,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   553,   555,     3,     8,     4,
     562,     4,   565,     3,     8,     8,   610,     3,     6,     4,
       4,     3,     8,   205,   237,   238,   484,     6,     3,   515,
       8,     6,     4,     4,   311,     4,     4,     4,     4,   206,
     208,   206,   208,   206,   206,   206,     4,   206,     4,     4,
       4,     4,   325,   324,   322,   404,   400,   445,   441,   469,
     465,   239,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   264,   265,   266,   267,   268,   269,   272,   274,
     276,   277,   278,   280,   282,   336,   396,   414,   416,   418,
     420,   421,   422,   423,   433,   434,   461,   491,   493,   506,
     508,   510,   530,   431,   359,   119,   120,   121,   239,   249,
     250,   251,   336,   435,   461,   491,   493,   506,   508,   510,
     538,   539,   540,   541,   542,   544,   546,   536,   503,   499,
     380,   376,   206,   206,   206,   206,   206,   206,   389,   208,
     206,   206,   368,     4,     4,   551,   208,     4,   206,     4,
     559,   181,   183,   184,   239,   336,   491,   493,   611,   612,
     613,   614,   616,   609,   208,   208,   633,     6,     3,   487,
     483,     4,   205,   205,    39,    40,    41,   328,   205,   205,
     205,    53,    54,    55,   346,   205,   205,   205,   205,     8,
       8,     8,     8,     3,     8,   543,   545,     4,     8,     3,
       8,     8,   205,   205,   205,   224,   617,     4,   615,     3,
       8,   205,     8,   235,   434,     4,     4,   208,   540,     4,
     206,     4,   612,   205,   205,     5,   205,     7,   618,   619,
     620,     3,     6,   182,   185,   186,   187,   188,   621,   622,
     623,   625,   626,   627,   628,   619,   624,     4,     4,     4,
     629,     3,     8,     4,   208,   206,   206,     4,   622,   205,
     205
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   209,   211,   210,   212,   210,   213,   210,   214,   210,
     215,   210,   216,   210,   217,   210,   218,   210,   219,   210,
     220,   210,   221,   210,   222,   210,   223,   210,   224,   224,
     224,   224,   224,   224,   224,   225,   227,   226,   228,   229,
     229,   230,   230,   230,   232,   231,   233,   233,   234,   234,
     234,   236,   235,   237,   237,   238,   238,   238,   239,   241,
     240,   243,   242,   242,   244,   246,   245,   247,   247,   247,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   261,   260,   262,   263,   264,
     265,   266,   267,   268,   270,   269,   271,   271,   271,   271,
     271,   273,   272,   275,   274,   276,   277,   279,   278,   281,
     280,   282,   283,   284,   285,   286,   287,   289,   288,   290,
     290,   290,   291,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   293,   292,   295,   294,   297,   296,   298,   298,
     300,   299,   301,   301,   302,   303,   304,   305,   307,   306,
     309,   308,   310,   310,   310,   311,   311,   313,   312,   315,
     314,   317,   316,   319,   318,   320,   320,   321,   321,   321,
     323,   322,   324,   324,   324,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   327,   326,   328,   328,   328,   330,
     329,   332,   331,   334,   333,   335,   337,   336,   338,   339,
     340,   341,   342,   343,   345,   344,   346,   346,   346,   347,
     349,   348,   351,   350,   353,   352,   355,   354,   357,   356,
     358,   358,   358,   359,   359,   359,   359,   359,   360,   361,
     362,   363,   364,   366,   365,   367,   367,   367,   368,   368,
     368,   368,   368,   368,   369,   370,   371,   373,   372,   374,
     374,   375,   375,   375,   377,   376,   379,   378,   380,   380,
     380,   380,   381,   381,   383,   382,   385,   384,   387,   386,
     388,   388,   388,   389,   389,   389,   389,   389,   389,   390,
     391,   392,   393,   394,   395,   397,   396,   398,   398,   399,
     399,   399,   401,   400,   403,   402,   404,   404,   404,   405,
     405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     405,   405,   405,   405,   407,   406,   409,   408,   411,   410,
     413,   412,   415,   414,   417,   416,   419,   418,   420,   421,
     422,   424,   423,   425,   425,   425,   425,   426,   428,   427,
     429,   429,   430,   430,   430,   432,   431,   433,   433,   433,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     436,   435,   438,   437,   439,   439,   440,   440,   440,   442,
     441,   444,   443,   445,   445,   446,   446,   446,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   448,   449,
     450,   452,   451,   454,   453,   456,   455,   457,   459,   458,
     460,   462,   461,   463,   463,   464,   464,   464,   466,   465,
     468,   467,   469,   469,   470,   470,   470,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   472,   474,   473,   475,
     476,   477,   478,   480,   479,   481,   481,   482,   482,   482,
     484,   483,   486,   485,   487,   487,   487,   488,   488,   488,
     488,   488,   488,   488,   490,   489,   492,   491,   494,   493,
     496,   495,   497,   497,   498,   498,   498,   500,   499,   502,
     501,   503,   503,   504,   504,   504,   505,   505,   505,   505,
     505,   505,   505,   505,   505,   505,   505,   505,   505,   505,
     505,   507,   506,   509,   508,   511,   510,   513,   512,   515,
     514,   517,   516,   519,   518,   521,   520,   523,   522,   525,
     524,   527,   526,   529,   528,   531,   530,   532,   532,   534,
     533,   535,   535,   535,   537,   536,   538,   538,   539,   539,
     539,   540,   540,   540,   540,   540,   540,   540,   540,   540,
     540,   540,   540,   540,   540,   540,   541,   543,   542,   545,
     544,   546,   547,   549,   548,   550,   550,   550,   551,   551,
     551,   551,   551,   553,   552,   555,   554,   557,   556,   558,
     558,   558,   559,   559,   559,   559,   559,   559,   560,   562,
     561,   563,   565,   564,   567,   566,   569,   568,   570,   570,
     570,   571,   571,   571,   571,   571,   571,   571,   571,   571,
     571,   571,   571,   571,   571,   571,   571,   571,   571,   572,
     574,   573,   575,   577,   576,   578,   579,   581,   580,   582,
     582,   584,   583,   586,   585,   587,   588,   590,   589,   592,
     591,   594,   593,   596,   595,   598,   597,   600,   599,   601,
     601,   601,   602,   602,   604,   603,   605,   607,   606,   608,
     608,   608,   610,   609,   611,   611,   611,   612,   612,   612,
     612,   612,   612,   612,   613,   615,   614,   617,   616,   618,
     618,   618,   620,   619,   621,   621,   621,   622,   622,   622,
     622,   622,   624,   623,   625,   626,   627,   629,   628,   631,
     630,   632,   632,   632,   633,   633,   633,   634,   635
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
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     4,     0,
       4,     3,     3,     3,     3,     3,     3,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     1,     1,
       0,     4,     1,     1,     3,     3,     3,     3,     0,     6,
       0,     6,     1,     3,     2,     1,     1,     0,     4,     0,
       4,     0,     6,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     1,     3,
       2,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     0,     4,     1,     1,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     1,     0,
       6,     1,     3,     2,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     3,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     2,     1,     1,     0,     6,     3,     0,     6,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     3,     3
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
  "\"server-hostname\"", "\"boot-file-name\"", "\"lease-database\"",
  "\"hosts-database\"", "\"hosts-databases\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"on-fail\"", "\"stop-retry-exit\"",
  "\"serve-retry-exit\"", "\"serve-retry-continue\"", "\"max-row-errors\"",
  "\"trust-anchor\"", "\"cert-file\"", "\"key-file\"", "\"cipher-list\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"cache-threshold\"",
  "\"cache-max-age\"", "\"decline-probation-period\"", "\"server-tag\"",
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
  "\"template-test\"", "\"only-if-required\"", "\"client-class\"",
  "\"reservations\"", "\"duid\"", "\"hw-address\"", "\"circuit-id\"",
  "\"client-id\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
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
  "\"early-global-reservations-lookup\"", "\"ip-reservations-unique\"",
  "\"reservations-lookup-first\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"compatibility\"",
  "\"lenient-option-parsing\"", "\"ignore-rai-link-selection\"",
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
  "parked_packet_limit", "echo_client_id", "match_client_id",
  "authoritative", "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@21",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@22",
  "ddns_qualifying_suffix", "$@23", "ddns_update_on_renew",
  "ddns_use_conflict_resolution", "hostname_char_set", "$@24",
  "hostname_char_replacement", "$@25", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "early_global_reservations_lookup", "ip_reservations_unique",
  "reservations_lookup_first", "interfaces_config", "$@26",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@27", "interfaces_list", "$@28", "dhcp_socket_type", "$@29",
  "socket_type", "outbound_interface", "$@30", "outbound_interface_value",
  "re_detect", "service_sockets_require_all",
  "service_sockets_retry_wait_time", "service_sockets_max_retries",
  "lease_database", "$@31", "sanity_checks", "$@32",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@33",
  "extended_info_checks", "$@34", "hosts_database", "$@35",
  "hosts_databases", "$@36", "database_list", "not_empty_database_list",
  "database", "$@37", "database_map_params", "database_map_param",
  "database_type", "$@38", "db_type", "user", "$@39", "password", "$@40",
  "host", "$@41", "port", "name", "$@42", "persist", "lfc_interval",
  "readonly", "connect_timeout", "max_reconnect_tries",
  "reconnect_wait_time", "on_fail", "$@43", "on_fail_mode",
  "max_row_errors", "trust_anchor", "$@44", "cert_file", "$@45",
  "key_file", "$@46", "cipher_list", "$@47",
  "host_reservation_identifiers", "$@48",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@49", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@50", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@51",
  "sub_hooks_library", "$@52", "hooks_params", "hooks_param", "library",
  "$@53", "parameters", "$@54", "expired_leases_processing", "$@55",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@56",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@57",
  "sub_subnet4", "$@58", "subnet4_params", "subnet4_param", "subnet",
  "$@59", "subnet_4o6_interface", "$@60", "subnet_4o6_interface_id",
  "$@61", "subnet_4o6_subnet", "$@62", "interface", "$@63", "client_class",
  "$@64", "require_client_classes", "$@65", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@66", "hr_mode", "id", "shared_networks", "$@67",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@68", "shared_network_params", "shared_network_param",
  "option_def_list", "$@69", "sub_option_def_list", "$@70",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@71", "sub_option_def", "$@72",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@73",
  "option_def_record_types", "$@74", "space", "$@75", "option_def_space",
  "option_def_encapsulate", "$@76", "option_def_array", "option_data_list",
  "$@77", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@78", "sub_option_data", "$@79",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@80",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@81", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@82", "sub_pool4", "$@83",
  "pool_params", "pool_param", "pool_entry", "$@84", "user_context",
  "$@85", "comment", "$@86", "reservations", "$@87", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@88", "sub_reservation",
  "$@89", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@90", "server_hostname", "$@91",
  "boot_file_name", "$@92", "ip_address", "$@93", "ip_addresses", "$@94",
  "duid", "$@95", "hw_address", "$@96", "client_id_value", "$@97",
  "circuit_id_value", "$@98", "flex_id_value", "$@99", "hostname", "$@100",
  "reservation_client_classes", "$@101", "relay", "$@102", "relay_map",
  "client_classes", "$@103", "client_classes_list", "client_class_entry",
  "$@104", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@105",
  "client_class_template_test", "$@106", "only_if_required",
  "dhcp4o6_port", "control_socket", "$@107", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@108",
  "control_socket_name", "$@109", "dhcp_queue_control", "$@110",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@111", "capacity", "arbitrary_map_entry", "$@112",
  "dhcp_ddns", "$@113", "sub_dhcp_ddns", "$@114", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@115", "server_port",
  "sender_ip", "$@116", "sender_port", "max_queue_size", "ncr_protocol",
  "$@117", "ncr_protocol_value", "ncr_format", "$@118",
  "dep_qualifying_suffix", "$@119", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@120",
  "dep_generated_prefix", "$@121", "dep_hostname_char_set", "$@122",
  "dep_hostname_char_replacement", "$@123", "config_control", "$@124",
  "sub_config_control", "$@125", "config_control_params",
  "config_control_param", "config_databases", "$@126",
  "config_fetch_wait_time", "loggers", "$@127", "loggers_entries",
  "logger_entry", "$@128", "logger_params", "logger_param", "debuglevel",
  "severity", "$@129", "output_options_list", "$@130",
  "output_options_list_content", "output_entry", "$@131",
  "output_params_list", "output_params", "output", "$@132", "flush",
  "maxsize", "maxver", "pattern", "$@133", "compatibility", "$@134",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore-rai-link-selection", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   298,   298,   298,   299,   299,   300,   300,   301,   301,
     302,   302,   303,   303,   304,   304,   305,   305,   306,   306,
     307,   307,   308,   308,   309,   309,   310,   310,   318,   319,
     320,   321,   322,   323,   324,   327,   332,   332,   343,   346,
     347,   350,   355,   361,   366,   366,   373,   374,   377,   381,
     385,   391,   391,   398,   399,   402,   406,   410,   420,   429,
     429,   444,   444,   458,   461,   467,   467,   476,   477,   478,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   551,   557,   563,   569,   575,   581,
     587,   593,   599,   605,   611,   617,   617,   626,   632,   638,
     644,   650,   656,   662,   668,   668,   677,   680,   683,   686,
     689,   695,   695,   704,   704,   713,   719,   725,   725,   734,
     734,   743,   749,   755,   761,   767,   773,   779,   779,   791,
     792,   793,   798,   799,   800,   801,   802,   803,   804,   805,
     806,   807,   810,   810,   819,   819,   830,   830,   838,   839,
     842,   842,   850,   852,   856,   862,   868,   874,   880,   880,
     893,   893,   904,   905,   906,   911,   912,   915,   915,   934,
     934,   952,   952,   965,   965,   976,   977,   980,   981,   982,
     987,   987,   997,   998,   999,  1004,  1005,  1006,  1007,  1008,
    1009,  1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,  1018,
    1019,  1020,  1021,  1022,  1025,  1025,  1033,  1034,  1035,  1038,
    1038,  1047,  1047,  1056,  1056,  1065,  1071,  1071,  1080,  1086,
    1092,  1098,  1104,  1110,  1116,  1116,  1124,  1125,  1126,  1129,
    1135,  1135,  1144,  1144,  1153,  1153,  1162,  1162,  1171,  1171,
    1182,  1183,  1184,  1189,  1190,  1191,  1192,  1193,  1196,  1201,
    1206,  1211,  1216,  1223,  1223,  1236,  1237,  1238,  1243,  1244,
    1245,  1246,  1247,  1248,  1251,  1257,  1263,  1269,  1269,  1280,
    1281,  1284,  1285,  1286,  1291,  1291,  1301,  1301,  1311,  1312,
    1313,  1316,  1319,  1320,  1323,  1323,  1332,  1332,  1341,  1341,
    1353,  1354,  1355,  1360,  1361,  1362,  1363,  1364,  1365,  1368,
    1374,  1380,  1386,  1392,  1398,  1407,  1407,  1421,  1422,  1425,
    1426,  1427,  1436,  1436,  1462,  1462,  1473,  1474,  1475,  1481,
    1482,  1483,  1484,  1485,  1486,  1487,  1488,  1489,  1490,  1491,
    1492,  1493,  1494,  1495,  1496,  1497,  1498,  1499,  1500,  1501,
    1502,  1503,  1504,  1505,  1506,  1507,  1508,  1509,  1510,  1511,
    1512,  1513,  1514,  1515,  1516,  1517,  1518,  1519,  1520,  1521,
    1522,  1523,  1524,  1525,  1528,  1528,  1537,  1537,  1546,  1546,
    1555,  1555,  1564,  1564,  1573,  1573,  1582,  1582,  1593,  1599,
    1605,  1611,  1611,  1619,  1620,  1621,  1622,  1625,  1633,  1633,
    1645,  1646,  1650,  1651,  1652,  1657,  1657,  1665,  1666,  1667,
    1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,  1681,
    1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,  1690,  1691,
    1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,  1700,  1701,
    1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,  1710,  1711,
    1718,  1718,  1732,  1732,  1741,  1742,  1745,  1746,  1747,  1754,
    1754,  1769,  1769,  1783,  1784,  1787,  1788,  1789,  1794,  1795,
    1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,  1806,  1808,
    1814,  1816,  1816,  1825,  1825,  1834,  1834,  1843,  1845,  1845,
    1854,  1864,  1864,  1877,  1878,  1883,  1884,  1885,  1892,  1892,
    1904,  1904,  1916,  1917,  1922,  1923,  1924,  1931,  1932,  1933,
    1934,  1935,  1936,  1937,  1938,  1939,  1942,  1944,  1944,  1953,
    1955,  1957,  1963,  1972,  1972,  1985,  1986,  1989,  1990,  1991,
    1996,  1996,  2006,  2006,  2016,  2017,  2018,  2023,  2024,  2025,
    2026,  2027,  2028,  2029,  2032,  2032,  2041,  2041,  2066,  2066,
    2096,  2096,  2107,  2108,  2111,  2112,  2113,  2118,  2118,  2127,
    2127,  2136,  2137,  2140,  2141,  2142,  2148,  2149,  2150,  2151,
    2152,  2153,  2154,  2155,  2156,  2157,  2158,  2159,  2160,  2161,
    2162,  2165,  2165,  2174,  2174,  2183,  2183,  2192,  2192,  2201,
    2201,  2212,  2212,  2221,  2221,  2230,  2230,  2239,  2239,  2248,
    2248,  2257,  2257,  2266,  2266,  2280,  2280,  2291,  2292,  2298,
    2298,  2309,  2310,  2311,  2316,  2316,  2326,  2327,  2330,  2331,
    2332,  2337,  2338,  2339,  2340,  2341,  2342,  2343,  2344,  2345,
    2346,  2347,  2348,  2349,  2350,  2351,  2354,  2356,  2356,  2365,
    2365,  2374,  2382,  2390,  2390,  2401,  2402,  2403,  2408,  2409,
    2410,  2411,  2412,  2415,  2415,  2424,  2424,  2436,  2436,  2449,
    2450,  2451,  2456,  2457,  2458,  2459,  2460,  2461,  2464,  2470,
    2470,  2479,  2485,  2485,  2495,  2495,  2508,  2508,  2518,  2519,
    2520,  2525,  2526,  2527,  2528,  2529,  2530,  2531,  2532,  2533,
    2534,  2535,  2536,  2537,  2538,  2539,  2540,  2541,  2542,  2545,
    2551,  2551,  2560,  2566,  2566,  2575,  2581,  2587,  2587,  2596,
    2597,  2600,  2600,  2610,  2610,  2620,  2627,  2634,  2634,  2643,
    2643,  2653,  2653,  2663,  2663,  2675,  2675,  2687,  2687,  2697,
    2698,  2699,  2705,  2706,  2709,  2709,  2720,  2728,  2728,  2741,
    2742,  2743,  2749,  2749,  2757,  2758,  2759,  2764,  2765,  2766,
    2767,  2768,  2769,  2770,  2773,  2779,  2779,  2788,  2788,  2799,
    2800,  2801,  2806,  2806,  2814,  2815,  2816,  2821,  2822,  2823,
    2824,  2825,  2828,  2828,  2837,  2843,  2849,  2855,  2855,  2864,
    2864,  2875,  2876,  2877,  2882,  2883,  2884,  2887,  2893
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
#line 6210 "dhcp4_parser.cc"

#line 2899 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
