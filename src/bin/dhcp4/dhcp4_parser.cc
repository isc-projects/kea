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

  case 132: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 549 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 133: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 555 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 134: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 561 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 135: // renew_timer: "renew-timer" ":" "integer"
#line 567 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 136: // rebind_timer: "rebind-timer" ":" "integer"
#line 573 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 137: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 579 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 138: // t1_percent: "t1-percent" ":" "floating point"
#line 585 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 139: // t2_percent: "t2-percent" ":" "floating point"
#line 591 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 140: // cache_threshold: "cache-threshold" ":" "floating point"
#line 597 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 141: // cache_max_age: "cache-max-age" ":" "integer"
#line 603 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 142: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 609 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 143: // $@20: %empty
#line 615 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 144: // server_tag: "server-tag" $@20 ":" "constant string"
#line 618 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 145: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 624 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 146: // echo_client_id: "echo-client-id" ":" "boolean"
#line 630 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1270 "dhcp4_parser.cc"
    break;

  case 147: // match_client_id: "match-client-id" ":" "boolean"
#line 636 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1280 "dhcp4_parser.cc"
    break;

  case 148: // authoritative: "authoritative" ":" "boolean"
#line 642 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1290 "dhcp4_parser.cc"
    break;

  case 149: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 648 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1300 "dhcp4_parser.cc"
    break;

  case 150: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 654 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1310 "dhcp4_parser.cc"
    break;

  case 151: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 660 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1320 "dhcp4_parser.cc"
    break;

  case 152: // $@21: %empty
#line 666 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 153: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 669 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1338 "dhcp4_parser.cc"
    break;

  case 154: // ddns_replace_client_name_value: "when-present"
#line 675 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1346 "dhcp4_parser.cc"
    break;

  case 155: // ddns_replace_client_name_value: "never"
#line 678 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1354 "dhcp4_parser.cc"
    break;

  case 156: // ddns_replace_client_name_value: "always"
#line 681 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1362 "dhcp4_parser.cc"
    break;

  case 157: // ddns_replace_client_name_value: "when-not-present"
#line 684 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1370 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "boolean"
#line 687 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1379 "dhcp4_parser.cc"
    break;

  case 159: // $@22: %empty
#line 693 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1388 "dhcp4_parser.cc"
    break;

  case 160: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 696 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1398 "dhcp4_parser.cc"
    break;

  case 161: // $@23: %empty
#line 702 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 162: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 705 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 163: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 711 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1427 "dhcp4_parser.cc"
    break;

  case 164: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 717 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1437 "dhcp4_parser.cc"
    break;

  case 165: // $@24: %empty
#line 723 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 166: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 726 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 167: // $@25: %empty
#line 732 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 168: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 735 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 169: // store_extended_info: "store-extended-info" ":" "boolean"
#line 741 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 170: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 747 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1495 "dhcp4_parser.cc"
    break;

  case 171: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 753 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 172: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 759 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 173: // $@26: %empty
#line 765 "dhcp4_parser.yy"
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
#line 771 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1537 "dhcp4_parser.cc"
    break;

  case 177: // interfaces_config_params: interfaces_config_params ","
#line 779 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1545 "dhcp4_parser.cc"
    break;

  case 185: // $@27: %empty
#line 793 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 186: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 797 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 187: // $@28: %empty
#line 802 "dhcp4_parser.yy"
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
#line 808 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1585 "dhcp4_parser.cc"
    break;

  case 189: // $@29: %empty
#line 813 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 190: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 816 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1603 "dhcp4_parser.cc"
    break;

  case 191: // socket_type: "raw"
#line 821 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1609 "dhcp4_parser.cc"
    break;

  case 192: // socket_type: "udp"
#line 822 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1615 "dhcp4_parser.cc"
    break;

  case 193: // $@30: %empty
#line 825 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 194: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 828 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1633 "dhcp4_parser.cc"
    break;

  case 195: // outbound_interface_value: "same-as-inbound"
#line 833 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1641 "dhcp4_parser.cc"
    break;

  case 196: // outbound_interface_value: "use-routing"
#line 835 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1649 "dhcp4_parser.cc"
    break;

  case 197: // re_detect: "re-detect" ":" "boolean"
#line 839 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1659 "dhcp4_parser.cc"
    break;

  case 198: // $@31: %empty
#line 846 "dhcp4_parser.yy"
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
#line 852 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1682 "dhcp4_parser.cc"
    break;

  case 200: // $@32: %empty
#line 859 "dhcp4_parser.yy"
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
#line 865 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1703 "dhcp4_parser.cc"
    break;

  case 204: // sanity_checks_params: sanity_checks_params ","
#line 872 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1711 "dhcp4_parser.cc"
    break;

  case 206: // $@33: %empty
#line 879 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1720 "dhcp4_parser.cc"
    break;

  case 207: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 882 "dhcp4_parser.yy"
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
#line 898 "dhcp4_parser.yy"
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
#line 904 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 210: // $@35: %empty
#line 911 "dhcp4_parser.yy"
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
#line 917 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1784 "dhcp4_parser.cc"
    break;

  case 216: // not_empty_database_list: not_empty_database_list ","
#line 928 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1792 "dhcp4_parser.cc"
    break;

  case 217: // $@36: %empty
#line 933 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1802 "dhcp4_parser.cc"
    break;

  case 218: // database: "{" $@36 database_map_params "}"
#line 937 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1812 "dhcp4_parser.cc"
    break;

  case 221: // database_map_params: database_map_params ","
#line 945 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1820 "dhcp4_parser.cc"
    break;

  case 248: // $@37: %empty
#line 978 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1829 "dhcp4_parser.cc"
    break;

  case 249: // database_type: "type" $@37 ":" db_type
#line 981 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1838 "dhcp4_parser.cc"
    break;

  case 250: // db_type: "memfile"
#line 986 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1844 "dhcp4_parser.cc"
    break;

  case 251: // db_type: "mysql"
#line 987 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1850 "dhcp4_parser.cc"
    break;

  case 252: // db_type: "postgresql"
#line 988 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1856 "dhcp4_parser.cc"
    break;

  case 253: // db_type: "cql"
#line 989 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1862 "dhcp4_parser.cc"
    break;

  case 254: // $@38: %empty
#line 992 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1871 "dhcp4_parser.cc"
    break;

  case 255: // user: "user" $@38 ":" "constant string"
#line 995 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 256: // $@39: %empty
#line 1001 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1890 "dhcp4_parser.cc"
    break;

  case 257: // password: "password" $@39 ":" "constant string"
#line 1004 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1900 "dhcp4_parser.cc"
    break;

  case 258: // $@40: %empty
#line 1010 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1909 "dhcp4_parser.cc"
    break;

  case 259: // host: "host" $@40 ":" "constant string"
#line 1013 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1919 "dhcp4_parser.cc"
    break;

  case 260: // port: "port" ":" "integer"
#line 1019 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1929 "dhcp4_parser.cc"
    break;

  case 261: // $@41: %empty
#line 1025 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1938 "dhcp4_parser.cc"
    break;

  case 262: // name: "name" $@41 ":" "constant string"
#line 1028 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1948 "dhcp4_parser.cc"
    break;

  case 263: // persist: "persist" ":" "boolean"
#line 1034 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1958 "dhcp4_parser.cc"
    break;

  case 264: // lfc_interval: "lfc-interval" ":" "integer"
#line 1040 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1968 "dhcp4_parser.cc"
    break;

  case 265: // readonly: "readonly" ":" "boolean"
#line 1046 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1978 "dhcp4_parser.cc"
    break;

  case 266: // connect_timeout: "connect-timeout" ":" "integer"
#line 1052 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1988 "dhcp4_parser.cc"
    break;

  case 267: // request_timeout: "request-timeout" ":" "integer"
#line 1058 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1998 "dhcp4_parser.cc"
    break;

  case 268: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1064 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 2008 "dhcp4_parser.cc"
    break;

  case 269: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1070 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 2018 "dhcp4_parser.cc"
    break;

  case 270: // $@42: %empty
#line 1076 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2027 "dhcp4_parser.cc"
    break;

  case 271: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1079 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 2037 "dhcp4_parser.cc"
    break;

  case 272: // $@43: %empty
#line 1085 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2046 "dhcp4_parser.cc"
    break;

  case 273: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1088 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 2056 "dhcp4_parser.cc"
    break;

  case 274: // $@44: %empty
#line 1094 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2065 "dhcp4_parser.cc"
    break;

  case 275: // consistency: "consistency" $@44 ":" "constant string"
#line 1097 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 2075 "dhcp4_parser.cc"
    break;

  case 276: // $@45: %empty
#line 1103 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2084 "dhcp4_parser.cc"
    break;

  case 277: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1106 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2094 "dhcp4_parser.cc"
    break;

  case 278: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1112 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2104 "dhcp4_parser.cc"
    break;

  case 279: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1118 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2114 "dhcp4_parser.cc"
    break;

  case 280: // $@46: %empty
#line 1124 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2123 "dhcp4_parser.cc"
    break;

  case 281: // on_fail: "on-fail" $@46 ":" on_fail_mode
#line 1127 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2132 "dhcp4_parser.cc"
    break;

  case 282: // on_fail_mode: "stop-retry-exit"
#line 1132 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2138 "dhcp4_parser.cc"
    break;

  case 283: // on_fail_mode: "serve-retry-exit"
#line 1133 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2144 "dhcp4_parser.cc"
    break;

  case 284: // on_fail_mode: "serve-retry-continue"
#line 1134 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2150 "dhcp4_parser.cc"
    break;

  case 285: // max_row_errors: "max-row-errors" ":" "integer"
#line 1137 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2160 "dhcp4_parser.cc"
    break;

  case 286: // $@47: %empty
#line 1143 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2169 "dhcp4_parser.cc"
    break;

  case 287: // trust_anchor: "trust-anchor" $@47 ":" "constant string"
#line 1146 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2179 "dhcp4_parser.cc"
    break;

  case 288: // $@48: %empty
#line 1152 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2188 "dhcp4_parser.cc"
    break;

  case 289: // cert_file: "cert-file" $@48 ":" "constant string"
#line 1155 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2198 "dhcp4_parser.cc"
    break;

  case 290: // $@49: %empty
#line 1161 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2207 "dhcp4_parser.cc"
    break;

  case 291: // key_file: "key-file" $@49 ":" "constant string"
#line 1164 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2217 "dhcp4_parser.cc"
    break;

  case 292: // $@50: %empty
#line 1170 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2226 "dhcp4_parser.cc"
    break;

  case 293: // cipher_list: "cipher-list" $@50 ":" "constant string"
#line 1173 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2236 "dhcp4_parser.cc"
    break;

  case 294: // $@51: %empty
#line 1179 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2248 "dhcp4_parser.cc"
    break;

  case 295: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1185 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2257 "dhcp4_parser.cc"
    break;

  case 298: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1192 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2265 "dhcp4_parser.cc"
    break;

  case 304: // duid_id: "duid"
#line 1204 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2274 "dhcp4_parser.cc"
    break;

  case 305: // hw_address_id: "hw-address"
#line 1209 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2283 "dhcp4_parser.cc"
    break;

  case 306: // circuit_id: "circuit-id"
#line 1214 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2292 "dhcp4_parser.cc"
    break;

  case 307: // client_id: "client-id"
#line 1219 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2301 "dhcp4_parser.cc"
    break;

  case 308: // flex_id: "flex-id"
#line 1224 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2310 "dhcp4_parser.cc"
    break;

  case 309: // $@52: %empty
#line 1231 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2322 "dhcp4_parser.cc"
    break;

  case 310: // dhcp_multi_threading: "multi-threading" $@52 ":" "{" multi_threading_params "}"
#line 1237 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2333 "dhcp4_parser.cc"
    break;

  case 313: // multi_threading_params: multi_threading_params ","
#line 1246 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2341 "dhcp4_parser.cc"
    break;

  case 320: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1259 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 321: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1265 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2361 "dhcp4_parser.cc"
    break;

  case 322: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1271 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2371 "dhcp4_parser.cc"
    break;

  case 323: // $@53: %empty
#line 1277 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2383 "dhcp4_parser.cc"
    break;

  case 324: // hooks_libraries: "hooks-libraries" $@53 ":" "[" hooks_libraries_list "]"
#line 1283 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2392 "dhcp4_parser.cc"
    break;

  case 329: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1294 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2400 "dhcp4_parser.cc"
    break;

  case 330: // $@54: %empty
#line 1299 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2410 "dhcp4_parser.cc"
    break;

  case 331: // hooks_library: "{" $@54 hooks_params "}"
#line 1303 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2420 "dhcp4_parser.cc"
    break;

  case 332: // $@55: %empty
#line 1309 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2430 "dhcp4_parser.cc"
    break;

  case 333: // sub_hooks_library: "{" $@55 hooks_params "}"
#line 1313 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2440 "dhcp4_parser.cc"
    break;

  case 336: // hooks_params: hooks_params ","
#line 1321 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2448 "dhcp4_parser.cc"
    break;

  case 340: // $@56: %empty
#line 1331 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2457 "dhcp4_parser.cc"
    break;

  case 341: // library: "library" $@56 ":" "constant string"
#line 1334 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2467 "dhcp4_parser.cc"
    break;

  case 342: // $@57: %empty
#line 1340 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2476 "dhcp4_parser.cc"
    break;

  case 343: // parameters: "parameters" $@57 ":" map_value
#line 1343 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2485 "dhcp4_parser.cc"
    break;

  case 344: // $@58: %empty
#line 1349 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2497 "dhcp4_parser.cc"
    break;

  case 345: // expired_leases_processing: "expired-leases-processing" $@58 ":" "{" expired_leases_params "}"
#line 1355 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2507 "dhcp4_parser.cc"
    break;

  case 348: // expired_leases_params: expired_leases_params ","
#line 1363 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2515 "dhcp4_parser.cc"
    break;

  case 355: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1376 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2525 "dhcp4_parser.cc"
    break;

  case 356: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1382 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2535 "dhcp4_parser.cc"
    break;

  case 357: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1388 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2545 "dhcp4_parser.cc"
    break;

  case 358: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1394 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2555 "dhcp4_parser.cc"
    break;

  case 359: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1400 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 360: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1406 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2575 "dhcp4_parser.cc"
    break;

  case 361: // $@59: %empty
#line 1415 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2587 "dhcp4_parser.cc"
    break;

  case 362: // subnet4_list: "subnet4" $@59 ":" "[" subnet4_list_content "]"
#line 1421 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2596 "dhcp4_parser.cc"
    break;

  case 367: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1435 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2604 "dhcp4_parser.cc"
    break;

  case 368: // $@60: %empty
#line 1444 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2614 "dhcp4_parser.cc"
    break;

  case 369: // subnet4: "{" $@60 subnet4_params "}"
#line 1448 "dhcp4_parser.yy"
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
#line 2640 "dhcp4_parser.cc"
    break;

  case 370: // $@61: %empty
#line 1470 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2650 "dhcp4_parser.cc"
    break;

  case 371: // sub_subnet4: "{" $@61 subnet4_params "}"
#line 1474 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2660 "dhcp4_parser.cc"
    break;

  case 374: // subnet4_params: subnet4_params ","
#line 1483 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2668 "dhcp4_parser.cc"
    break;

  case 420: // $@62: %empty
#line 1536 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2677 "dhcp4_parser.cc"
    break;

  case 421: // subnet: "subnet" $@62 ":" "constant string"
#line 1539 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2687 "dhcp4_parser.cc"
    break;

  case 422: // $@63: %empty
#line 1545 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2696 "dhcp4_parser.cc"
    break;

  case 423: // subnet_4o6_interface: "4o6-interface" $@63 ":" "constant string"
#line 1548 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2706 "dhcp4_parser.cc"
    break;

  case 424: // $@64: %empty
#line 1554 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2715 "dhcp4_parser.cc"
    break;

  case 425: // subnet_4o6_interface_id: "4o6-interface-id" $@64 ":" "constant string"
#line 1557 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2725 "dhcp4_parser.cc"
    break;

  case 426: // $@65: %empty
#line 1563 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2734 "dhcp4_parser.cc"
    break;

  case 427: // subnet_4o6_subnet: "4o6-subnet" $@65 ":" "constant string"
#line 1566 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2744 "dhcp4_parser.cc"
    break;

  case 428: // $@66: %empty
#line 1572 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2753 "dhcp4_parser.cc"
    break;

  case 429: // interface: "interface" $@66 ":" "constant string"
#line 1575 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2763 "dhcp4_parser.cc"
    break;

  case 430: // $@67: %empty
#line 1581 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2772 "dhcp4_parser.cc"
    break;

  case 431: // client_class: "client-class" $@67 ":" "constant string"
#line 1584 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2782 "dhcp4_parser.cc"
    break;

  case 432: // $@68: %empty
#line 1590 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2794 "dhcp4_parser.cc"
    break;

  case 433: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1596 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2803 "dhcp4_parser.cc"
    break;

  case 434: // reservations_global: "reservations-global" ":" "boolean"
#line 1601 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2813 "dhcp4_parser.cc"
    break;

  case 435: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1607 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 436: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1613 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2833 "dhcp4_parser.cc"
    break;

  case 437: // $@69: %empty
#line 1619 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2842 "dhcp4_parser.cc"
    break;

  case 438: // reservation_mode: "reservation-mode" $@69 ":" hr_mode
#line 1622 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2851 "dhcp4_parser.cc"
    break;

  case 439: // hr_mode: "disabled"
#line 1627 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2857 "dhcp4_parser.cc"
    break;

  case 440: // hr_mode: "out-of-pool"
#line 1628 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2863 "dhcp4_parser.cc"
    break;

  case 441: // hr_mode: "global"
#line 1629 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2869 "dhcp4_parser.cc"
    break;

  case 442: // hr_mode: "all"
#line 1630 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2875 "dhcp4_parser.cc"
    break;

  case 443: // id: "id" ":" "integer"
#line 1633 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2885 "dhcp4_parser.cc"
    break;

  case 444: // $@70: %empty
#line 1641 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2897 "dhcp4_parser.cc"
    break;

  case 445: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1647 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2906 "dhcp4_parser.cc"
    break;

  case 450: // shared_networks_list: shared_networks_list ","
#line 1660 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2914 "dhcp4_parser.cc"
    break;

  case 451: // $@71: %empty
#line 1665 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2924 "dhcp4_parser.cc"
    break;

  case 452: // shared_network: "{" $@71 shared_network_params "}"
#line 1669 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 455: // shared_network_params: shared_network_params ","
#line 1675 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2940 "dhcp4_parser.cc"
    break;

  case 496: // $@72: %empty
#line 1726 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2952 "dhcp4_parser.cc"
    break;

  case 497: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1732 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2961 "dhcp4_parser.cc"
    break;

  case 498: // $@73: %empty
#line 1740 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2970 "dhcp4_parser.cc"
    break;

  case 499: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1743 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2978 "dhcp4_parser.cc"
    break;

  case 504: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1755 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2986 "dhcp4_parser.cc"
    break;

  case 505: // $@74: %empty
#line 1762 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2996 "dhcp4_parser.cc"
    break;

  case 506: // option_def_entry: "{" $@74 option_def_params "}"
#line 1766 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3008 "dhcp4_parser.cc"
    break;

  case 507: // $@75: %empty
#line 1777 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 508: // sub_option_def: "{" $@75 option_def_params "}"
#line 1781 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3030 "dhcp4_parser.cc"
    break;

  case 513: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1797 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3038 "dhcp4_parser.cc"
    break;

  case 525: // code: "code" ":" "integer"
#line 1816 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3048 "dhcp4_parser.cc"
    break;

  case 527: // $@76: %empty
#line 1824 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3057 "dhcp4_parser.cc"
    break;

  case 528: // option_def_type: "type" $@76 ":" "constant string"
#line 1827 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3067 "dhcp4_parser.cc"
    break;

  case 529: // $@77: %empty
#line 1833 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3076 "dhcp4_parser.cc"
    break;

  case 530: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1836 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3086 "dhcp4_parser.cc"
    break;

  case 531: // $@78: %empty
#line 1842 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3095 "dhcp4_parser.cc"
    break;

  case 532: // space: "space" $@78 ":" "constant string"
#line 1845 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3105 "dhcp4_parser.cc"
    break;

  case 534: // $@79: %empty
#line 1853 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3114 "dhcp4_parser.cc"
    break;

  case 535: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1856 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3124 "dhcp4_parser.cc"
    break;

  case 536: // option_def_array: "array" ":" "boolean"
#line 1862 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3134 "dhcp4_parser.cc"
    break;

  case 537: // $@80: %empty
#line 1872 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3146 "dhcp4_parser.cc"
    break;

  case 538: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 1878 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3155 "dhcp4_parser.cc"
    break;

  case 543: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1893 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3163 "dhcp4_parser.cc"
    break;

  case 544: // $@81: %empty
#line 1900 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3173 "dhcp4_parser.cc"
    break;

  case 545: // option_data_entry: "{" $@81 option_data_params "}"
#line 1904 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3182 "dhcp4_parser.cc"
    break;

  case 546: // $@82: %empty
#line 1912 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3192 "dhcp4_parser.cc"
    break;

  case 547: // sub_option_data: "{" $@82 option_data_params "}"
#line 1916 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3201 "dhcp4_parser.cc"
    break;

  case 552: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1932 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3209 "dhcp4_parser.cc"
    break;

  case 563: // $@83: %empty
#line 1952 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3218 "dhcp4_parser.cc"
    break;

  case 564: // option_data_data: "data" $@83 ":" "constant string"
#line 1955 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3228 "dhcp4_parser.cc"
    break;

  case 567: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1965 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3238 "dhcp4_parser.cc"
    break;

  case 568: // option_data_always_send: "always-send" ":" "boolean"
#line 1971 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3248 "dhcp4_parser.cc"
    break;

  case 569: // $@84: %empty
#line 1980 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3260 "dhcp4_parser.cc"
    break;

  case 570: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 1986 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3269 "dhcp4_parser.cc"
    break;

  case 575: // not_empty_pools_list: not_empty_pools_list ","
#line 1999 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3277 "dhcp4_parser.cc"
    break;

  case 576: // $@85: %empty
#line 2004 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3287 "dhcp4_parser.cc"
    break;

  case 577: // pool_list_entry: "{" $@85 pool_params "}"
#line 2008 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3297 "dhcp4_parser.cc"
    break;

  case 578: // $@86: %empty
#line 2014 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3307 "dhcp4_parser.cc"
    break;

  case 579: // sub_pool4: "{" $@86 pool_params "}"
#line 2018 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3317 "dhcp4_parser.cc"
    break;

  case 582: // pool_params: pool_params ","
#line 2026 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3325 "dhcp4_parser.cc"
    break;

  case 590: // $@87: %empty
#line 2040 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3334 "dhcp4_parser.cc"
    break;

  case 591: // pool_entry: "pool" $@87 ":" "constant string"
#line 2043 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3344 "dhcp4_parser.cc"
    break;

  case 592: // $@88: %empty
#line 2049 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3352 "dhcp4_parser.cc"
    break;

  case 593: // user_context: "user-context" $@88 ":" map_value
#line 2051 "dhcp4_parser.yy"
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
#line 3379 "dhcp4_parser.cc"
    break;

  case 594: // $@89: %empty
#line 2074 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3387 "dhcp4_parser.cc"
    break;

  case 595: // comment: "comment" $@89 ":" "constant string"
#line 2076 "dhcp4_parser.yy"
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
#line 3416 "dhcp4_parser.cc"
    break;

  case 596: // $@90: %empty
#line 2104 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3428 "dhcp4_parser.cc"
    break;

  case 597: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2110 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3437 "dhcp4_parser.cc"
    break;

  case 602: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2121 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3445 "dhcp4_parser.cc"
    break;

  case 603: // $@91: %empty
#line 2126 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3455 "dhcp4_parser.cc"
    break;

  case 604: // reservation: "{" $@91 reservation_params "}"
#line 2130 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3464 "dhcp4_parser.cc"
    break;

  case 605: // $@92: %empty
#line 2135 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3474 "dhcp4_parser.cc"
    break;

  case 606: // sub_reservation: "{" $@92 reservation_params "}"
#line 2139 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3483 "dhcp4_parser.cc"
    break;

  case 611: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2150 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3491 "dhcp4_parser.cc"
    break;

  case 627: // $@93: %empty
#line 2173 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3500 "dhcp4_parser.cc"
    break;

  case 628: // next_server: "next-server" $@93 ":" "constant string"
#line 2176 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3510 "dhcp4_parser.cc"
    break;

  case 629: // $@94: %empty
#line 2182 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3519 "dhcp4_parser.cc"
    break;

  case 630: // server_hostname: "server-hostname" $@94 ":" "constant string"
#line 2185 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3529 "dhcp4_parser.cc"
    break;

  case 631: // $@95: %empty
#line 2191 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3538 "dhcp4_parser.cc"
    break;

  case 632: // boot_file_name: "boot-file-name" $@95 ":" "constant string"
#line 2194 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3548 "dhcp4_parser.cc"
    break;

  case 633: // $@96: %empty
#line 2200 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3557 "dhcp4_parser.cc"
    break;

  case 634: // ip_address: "ip-address" $@96 ":" "constant string"
#line 2203 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3567 "dhcp4_parser.cc"
    break;

  case 635: // $@97: %empty
#line 2209 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3579 "dhcp4_parser.cc"
    break;

  case 636: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2215 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3588 "dhcp4_parser.cc"
    break;

  case 637: // $@98: %empty
#line 2220 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3597 "dhcp4_parser.cc"
    break;

  case 638: // duid: "duid" $@98 ":" "constant string"
#line 2223 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3607 "dhcp4_parser.cc"
    break;

  case 639: // $@99: %empty
#line 2229 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3616 "dhcp4_parser.cc"
    break;

  case 640: // hw_address: "hw-address" $@99 ":" "constant string"
#line 2232 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3626 "dhcp4_parser.cc"
    break;

  case 641: // $@100: %empty
#line 2238 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3635 "dhcp4_parser.cc"
    break;

  case 642: // client_id_value: "client-id" $@100 ":" "constant string"
#line 2241 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3645 "dhcp4_parser.cc"
    break;

  case 643: // $@101: %empty
#line 2247 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3654 "dhcp4_parser.cc"
    break;

  case 644: // circuit_id_value: "circuit-id" $@101 ":" "constant string"
#line 2250 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3664 "dhcp4_parser.cc"
    break;

  case 645: // $@102: %empty
#line 2256 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3673 "dhcp4_parser.cc"
    break;

  case 646: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2259 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 647: // $@103: %empty
#line 2265 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3692 "dhcp4_parser.cc"
    break;

  case 648: // hostname: "hostname" $@103 ":" "constant string"
#line 2268 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 649: // $@104: %empty
#line 2274 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3714 "dhcp4_parser.cc"
    break;

  case 650: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2280 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3723 "dhcp4_parser.cc"
    break;

  case 651: // $@105: %empty
#line 2288 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3735 "dhcp4_parser.cc"
    break;

  case 652: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2294 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3744 "dhcp4_parser.cc"
    break;

  case 655: // $@106: %empty
#line 2306 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3756 "dhcp4_parser.cc"
    break;

  case 656: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2312 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3765 "dhcp4_parser.cc"
    break;

  case 659: // client_classes_list: client_classes_list ","
#line 2319 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3773 "dhcp4_parser.cc"
    break;

  case 660: // $@107: %empty
#line 2324 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3783 "dhcp4_parser.cc"
    break;

  case 661: // client_class_entry: "{" $@107 client_class_params "}"
#line 2328 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3793 "dhcp4_parser.cc"
    break;

  case 666: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2340 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3801 "dhcp4_parser.cc"
    break;

  case 682: // $@108: %empty
#line 2363 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3810 "dhcp4_parser.cc"
    break;

  case 683: // client_class_test: "test" $@108 ":" "constant string"
#line 2366 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3820 "dhcp4_parser.cc"
    break;

  case 684: // only_if_required: "only-if-required" ":" "boolean"
#line 2372 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3830 "dhcp4_parser.cc"
    break;

  case 685: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2380 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3840 "dhcp4_parser.cc"
    break;

  case 686: // $@109: %empty
#line 2388 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3852 "dhcp4_parser.cc"
    break;

  case 687: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2394 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3861 "dhcp4_parser.cc"
    break;

  case 690: // control_socket_params: control_socket_params ","
#line 2401 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3869 "dhcp4_parser.cc"
    break;

  case 696: // $@110: %empty
#line 2413 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3878 "dhcp4_parser.cc"
    break;

  case 697: // control_socket_type: "socket-type" $@110 ":" "constant string"
#line 2416 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3888 "dhcp4_parser.cc"
    break;

  case 698: // $@111: %empty
#line 2422 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3897 "dhcp4_parser.cc"
    break;

  case 699: // control_socket_name: "socket-name" $@111 ":" "constant string"
#line 2425 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3907 "dhcp4_parser.cc"
    break;

  case 700: // $@112: %empty
#line 2434 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3919 "dhcp4_parser.cc"
    break;

  case 701: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2440 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3930 "dhcp4_parser.cc"
    break;

  case 704: // queue_control_params: queue_control_params ","
#line 2449 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3938 "dhcp4_parser.cc"
    break;

  case 711: // enable_queue: "enable-queue" ":" "boolean"
#line 2462 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3948 "dhcp4_parser.cc"
    break;

  case 712: // $@113: %empty
#line 2468 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3957 "dhcp4_parser.cc"
    break;

  case 713: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2471 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3967 "dhcp4_parser.cc"
    break;

  case 714: // capacity: "capacity" ":" "integer"
#line 2477 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3977 "dhcp4_parser.cc"
    break;

  case 715: // $@114: %empty
#line 2483 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3986 "dhcp4_parser.cc"
    break;

  case 716: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2486 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3995 "dhcp4_parser.cc"
    break;

  case 717: // $@115: %empty
#line 2493 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4007 "dhcp4_parser.cc"
    break;

  case 718: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2499 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4018 "dhcp4_parser.cc"
    break;

  case 719: // $@116: %empty
#line 2506 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4028 "dhcp4_parser.cc"
    break;

  case 720: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2510 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4038 "dhcp4_parser.cc"
    break;

  case 723: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2518 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4046 "dhcp4_parser.cc"
    break;

  case 742: // enable_updates: "enable-updates" ":" "boolean"
#line 2543 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4056 "dhcp4_parser.cc"
    break;

  case 743: // $@117: %empty
#line 2549 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4065 "dhcp4_parser.cc"
    break;

  case 744: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2552 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4075 "dhcp4_parser.cc"
    break;

  case 745: // server_port: "server-port" ":" "integer"
#line 2558 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4085 "dhcp4_parser.cc"
    break;

  case 746: // $@118: %empty
#line 2564 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4094 "dhcp4_parser.cc"
    break;

  case 747: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2567 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4104 "dhcp4_parser.cc"
    break;

  case 748: // sender_port: "sender-port" ":" "integer"
#line 2573 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4114 "dhcp4_parser.cc"
    break;

  case 749: // max_queue_size: "max-queue-size" ":" "integer"
#line 2579 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4124 "dhcp4_parser.cc"
    break;

  case 750: // $@119: %empty
#line 2585 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4133 "dhcp4_parser.cc"
    break;

  case 751: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2588 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4142 "dhcp4_parser.cc"
    break;

  case 752: // ncr_protocol_value: "udp"
#line 2594 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4148 "dhcp4_parser.cc"
    break;

  case 753: // ncr_protocol_value: "tcp"
#line 2595 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4154 "dhcp4_parser.cc"
    break;

  case 754: // $@120: %empty
#line 2598 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4163 "dhcp4_parser.cc"
    break;

  case 755: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2601 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4173 "dhcp4_parser.cc"
    break;

  case 756: // $@121: %empty
#line 2608 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4182 "dhcp4_parser.cc"
    break;

  case 757: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2611 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4192 "dhcp4_parser.cc"
    break;

  case 758: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2618 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4202 "dhcp4_parser.cc"
    break;

  case 759: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2625 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4212 "dhcp4_parser.cc"
    break;

  case 760: // $@122: %empty
#line 2632 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4221 "dhcp4_parser.cc"
    break;

  case 761: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2635 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4230 "dhcp4_parser.cc"
    break;

  case 762: // $@123: %empty
#line 2641 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4239 "dhcp4_parser.cc"
    break;

  case 763: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2644 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4249 "dhcp4_parser.cc"
    break;

  case 764: // $@124: %empty
#line 2651 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4258 "dhcp4_parser.cc"
    break;

  case 765: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2654 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4268 "dhcp4_parser.cc"
    break;

  case 766: // $@125: %empty
#line 2661 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4277 "dhcp4_parser.cc"
    break;

  case 767: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2664 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4287 "dhcp4_parser.cc"
    break;

  case 768: // $@126: %empty
#line 2673 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4299 "dhcp4_parser.cc"
    break;

  case 769: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2679 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4309 "dhcp4_parser.cc"
    break;

  case 770: // $@127: %empty
#line 2685 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4319 "dhcp4_parser.cc"
    break;

  case 771: // sub_config_control: "{" $@127 config_control_params "}"
#line 2689 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4328 "dhcp4_parser.cc"
    break;

  case 774: // config_control_params: config_control_params ","
#line 2697 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4336 "dhcp4_parser.cc"
    break;

  case 777: // $@128: %empty
#line 2707 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4348 "dhcp4_parser.cc"
    break;

  case 778: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2713 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4357 "dhcp4_parser.cc"
    break;

  case 779: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2718 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4367 "dhcp4_parser.cc"
    break;

  case 780: // $@129: %empty
#line 2726 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4379 "dhcp4_parser.cc"
    break;

  case 781: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2732 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4388 "dhcp4_parser.cc"
    break;

  case 784: // loggers_entries: loggers_entries ","
#line 2741 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4396 "dhcp4_parser.cc"
    break;

  case 785: // $@130: %empty
#line 2747 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4406 "dhcp4_parser.cc"
    break;

  case 786: // logger_entry: "{" $@130 logger_params "}"
#line 2751 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4414 "dhcp4_parser.cc"
    break;

  case 789: // logger_params: logger_params ","
#line 2757 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4422 "dhcp4_parser.cc"
    break;

  case 797: // debuglevel: "debuglevel" ":" "integer"
#line 2771 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4432 "dhcp4_parser.cc"
    break;

  case 798: // $@131: %empty
#line 2777 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4441 "dhcp4_parser.cc"
    break;

  case 799: // severity: "severity" $@131 ":" "constant string"
#line 2780 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4451 "dhcp4_parser.cc"
    break;

  case 800: // $@132: %empty
#line 2786 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4463 "dhcp4_parser.cc"
    break;

  case 801: // output_options_list: "output_options" $@132 ":" "[" output_options_list_content "]"
#line 2792 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4472 "dhcp4_parser.cc"
    break;

  case 804: // output_options_list_content: output_options_list_content ","
#line 2799 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4480 "dhcp4_parser.cc"
    break;

  case 805: // $@133: %empty
#line 2804 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4490 "dhcp4_parser.cc"
    break;

  case 806: // output_entry: "{" $@133 output_params_list "}"
#line 2808 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4498 "dhcp4_parser.cc"
    break;

  case 809: // output_params_list: output_params_list ","
#line 2814 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4506 "dhcp4_parser.cc"
    break;

  case 815: // $@134: %empty
#line 2826 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4515 "dhcp4_parser.cc"
    break;

  case 816: // output: "output" $@134 ":" "constant string"
#line 2829 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4525 "dhcp4_parser.cc"
    break;

  case 817: // flush: "flush" ":" "boolean"
#line 2835 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4535 "dhcp4_parser.cc"
    break;

  case 818: // maxsize: "maxsize" ":" "integer"
#line 2841 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4545 "dhcp4_parser.cc"
    break;

  case 819: // maxver: "maxver" ":" "integer"
#line 2847 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4555 "dhcp4_parser.cc"
    break;

  case 820: // $@135: %empty
#line 2853 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4564 "dhcp4_parser.cc"
    break;

  case 821: // pattern: "pattern" $@135 ":" "constant string"
#line 2856 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4574 "dhcp4_parser.cc"
    break;

  case 822: // $@136: %empty
#line 2862 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4586 "dhcp4_parser.cc"
    break;

  case 823: // compatibility: "compatibility" $@136 ":" "{" compatibility_params "}"
#line 2868 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4595 "dhcp4_parser.cc"
    break;

  case 826: // compatibility_params: compatibility_params ","
#line 2875 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4603 "dhcp4_parser.cc"
    break;

  case 829: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2884 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4613 "dhcp4_parser.cc"
    break;


#line 4617 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -972;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     553,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,    71,    44,    41,    60,    62,    82,
      86,    96,   114,   124,   167,   183,   201,   280,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,    44,  -147,    89,   190,    28,   610,
     197,    48,   155,    95,   -11,  -100,   693,   112,  -972,   111,
     251,   284,   281,   292,  -972,    56,  -972,  -972,  -972,  -972,
     295,   309,   323,  -972,  -972,  -972,  -972,  -972,  -972,   324,
     326,   327,   348,   368,   369,   370,   371,   372,   373,   374,
    -972,   375,   377,   378,   379,   380,  -972,  -972,  -972,   381,
     382,   383,  -972,  -972,  -972,   384,  -972,  -972,  -972,  -972,
     386,   387,   388,  -972,  -972,  -972,  -972,  -972,   389,  -972,
    -972,  -972,  -972,  -972,  -972,   390,  -972,  -972,   392,  -972,
      67,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,   393,  -972,    92,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,   394,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
      98,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,   110,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,   331,   396,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,   395,
    -972,  -972,   397,  -972,  -972,  -972,   400,  -972,  -972,   398,
     402,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,   403,   404,  -972,  -972,  -972,  -972,
     401,   407,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,   120,  -972,  -972,  -972,   409,  -972,
    -972,   410,  -972,   412,   413,  -972,  -972,   415,   416,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,   146,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,   417,   160,  -972,  -972,  -972,  -972,
      44,    44,  -972,   195,   418,  -972,  -972,   419,   420,   421,
     203,   218,   219,   424,   425,   427,   428,   432,   433,   233,
     234,   235,   237,   239,   230,   241,   243,   244,   246,   249,
     443,   255,   258,   245,   259,   260,   462,   465,   467,   264,
     265,   270,   476,   477,   479,   285,   482,   483,   486,   490,
     289,   290,   291,   498,   500,   501,   502,   504,   303,   506,
     507,   508,   511,   512,   513,   313,   519,   520,  -972,   190,
    -972,   521,   523,   524,   321,    28,  -972,   527,   529,   530,
     531,   532,   535,   340,   537,   541,   545,   610,  -972,   547,
     197,  -972,   548,   549,   552,   555,   559,   563,   564,   565,
    -972,    48,  -972,   567,   568,   351,   570,   571,   572,   385,
    -972,    95,   573,   399,   406,  -972,   -11,   590,   591,   -27,
    -972,   408,   600,   601,   405,   602,   411,   414,   604,   605,
     422,   426,   606,   608,   614,   615,   693,  -972,   617,   423,
     112,  -972,  -972,  -972,   618,   616,   619,   620,   621,  -972,
    -972,  -972,   430,   436,   437,   625,   636,   639,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,   440,
    -972,  -972,  -972,  -972,  -972,   -10,   441,   442,  -972,  -972,
    -972,   643,   646,   648,  -972,   649,   650,   450,   247,  -972,
    -972,  -972,   653,   654,   655,   656,   657,  -972,   662,   663,
     664,   665,   457,   458,  -972,   668,   678,  -972,   681,   133,
     179,  -972,  -972,   493,   497,   499,   682,   509,   518,  -972,
     681,   525,   698,  -972,   526,  -972,   681,   528,   554,   556,
     557,   558,   560,   561,  -972,   562,   566,  -972,   569,   581,
     582,  -972,  -972,   597,  -972,  -972,  -972,   598,   650,  -972,
    -972,   603,   607,  -972,   609,  -972,  -972,    15,   451,  -972,
    -972,   -10,   611,   612,   622,  -972,   683,  -972,  -972,    44,
     190,   112,    28,   688,  -972,  -972,  -972,   539,   539,   699,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,   700,
     706,   709,   717,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,   100,   718,   719,   727,    17,   184,     0,   210,   693,
    -972,  -972,   735,  -160,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,   751,  -972,  -972,  -972,  -972,
      72,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,   699,
    -972,   178,   185,   206,  -972,   228,  -972,  -972,  -972,  -972,
    -972,  -972,   756,   760,   764,   765,   766,  -972,  -972,  -972,
    -972,   768,   769,  -972,   771,   802,   803,   805,  -972,  -972,
    -972,  -972,  -972,   232,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
     236,  -972,   804,   808,  -972,  -972,   807,   817,  -972,  -972,
     816,   821,  -972,  -972,   819,   823,  -972,  -972,   825,   829,
    -972,  -972,  -972,  -972,  -972,  -972,    36,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,    49,  -972,  -972,   828,   832,  -972,
    -972,   831,   835,  -972,   836,   837,   838,   839,   841,   842,
     276,  -972,  -972,  -972,  -972,  -972,  -972,  -972,   843,   844,
     845,  -972,   277,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,   278,  -972,  -972,  -972,   846,  -972,
     847,  -972,  -972,  -972,   298,  -972,  -972,  -972,  -972,  -972,
     317,  -972,   240,  -972,   861,  -972,   335,  -972,  -972,   634,
    -972,   860,   864,  -972,  -972,  -972,  -972,   862,   863,  -972,
    -972,  -972,   869,   688,  -972,   870,   871,   872,   873,   672,
     660,   673,   674,   675,   876,   879,   880,   881,   680,   685,
     883,   686,   687,   689,   690,   884,   890,   891,   895,   539,
    -972,  -972,   539,  -972,   699,   610,  -972,   700,    95,  -972,
     706,   -11,  -972,   709,   711,  -972,   717,   100,  -972,   118,
     718,  -972,    48,  -972,   719,  -100,  -972,   727,   694,   695,
     696,   697,   701,   703,    17,  -972,   702,   707,   715,   184,
    -972,   900,   901,     0,  -972,   704,   902,   720,   911,   210,
    -972,  -972,   130,   735,  -972,   723,  -160,  -972,  -972,   917,
     929,   197,  -972,   751,   943,  -972,  -972,   745,  -972,   135,
     748,   770,   777,  -972,  -972,  -972,  -972,  -972,   778,   781,
     785,   786,  -972,  -972,    26,  -972,  -972,  -972,  -972,   797,
     798,   811,   850,  -972,   337,  -972,   339,  -972,   957,  -972,
    1038,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,   343,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  1046,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    1043,  1053,  -972,  -972,  -972,  -972,  -972,  1049,  -972,   346,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,   853,   854,  -972,  -972,   855,  -972,    44,  -972,
    -972,  1057,  -972,  -972,  -972,  -972,  -972,   347,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,   857,   350,  -972,   681,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,   711,  -972,  1059,   856,  -972,
     118,  -972,  -972,  -972,  -972,  -972,  -972,  1061,   865,  1062,
     130,  -972,  -972,  -972,  -972,  -972,   867,  -972,  -972,  1063,
    -972,   868,  -972,  -972,  1060,  -972,  -972,   318,  -972,   -44,
    1060,  -972,  -972,  1065,  1066,  1070,  -972,   356,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  1071,   874,   875,   877,  1072,
     -44,  -972,   882,  -972,  -972,  -972,   885,  -972,  -972,  -972
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   185,     9,   370,    11,   578,    13,
     605,    15,   498,    17,   507,    19,   546,    21,   332,    23,
     719,    25,   770,    27,    46,    39,     0,     0,     0,     0,
       0,   607,     0,   509,   548,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   768,   173,   200,
       0,     0,     0,   627,   629,   631,   198,   208,   210,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     143,     0,     0,     0,     0,     0,   152,   159,   161,     0,
       0,     0,   361,   496,   537,     0,   444,   592,   594,   437,
       0,     0,     0,   294,   655,   596,   323,   344,     0,   309,
     686,   700,   717,   165,   167,     0,   780,   822,     0,   131,
       0,    67,    70,    71,    72,    73,    74,   108,   109,   110,
     111,   112,    75,   103,   130,    92,    93,    94,   116,   117,
     118,   119,   120,   121,   122,   123,   114,   115,   124,   125,
     126,   128,    78,    79,   100,    80,    81,    82,   127,    86,
      87,    76,   105,   106,   107,   104,    77,    84,    85,    98,
      99,   101,    95,    96,    97,    83,    88,    89,    90,    91,
     102,   113,   129,   187,   189,   193,     0,   184,     0,   175,
     178,   179,   180,   181,   182,   183,   422,   424,   426,   569,
     420,   428,     0,   432,   430,   651,   419,   375,   376,   377,
     378,   379,   403,   404,   405,   406,   407,   393,   394,   408,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
       0,   372,   382,   398,   399,   400,   383,   385,   386,   389,
     390,   391,   388,   384,   380,   381,   401,   402,   387,   395,
     396,   397,   392,   590,   589,   585,   586,   584,     0,   580,
     583,   587,   588,   649,   637,   639,   643,   641,   647,   645,
     633,   626,   620,   624,   625,     0,   608,   609,   621,   622,
     623,   617,   612,   618,   614,   615,   616,   619,   613,     0,
     527,   261,     0,   531,   529,   534,     0,   523,   524,     0,
     510,   511,   514,   526,   515,   516,   517,   533,   518,   519,
     520,   521,   522,   563,     0,     0,   561,   562,   565,   566,
       0,   549,   550,   553,   554,   555,   556,   557,   558,   559,
     560,   340,   342,   337,     0,   334,   338,   339,     0,   756,
     743,     0,   746,     0,     0,   750,   754,     0,     0,   760,
     762,   764,   766,   741,   739,   740,     0,   721,   724,   725,
     726,   727,   728,   729,   730,   731,   736,   732,   733,   734,
     735,   737,   738,   777,     0,     0,   772,   775,   776,    45,
      50,     0,    37,    43,     0,    64,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    69,
      66,     0,     0,     0,     0,   177,   186,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   374,   371,     0,
     582,   579,     0,     0,     0,     0,     0,     0,     0,     0,
     606,   611,   499,     0,     0,     0,     0,     0,     0,     0,
     508,   513,     0,     0,     0,   547,   552,     0,     0,   336,
     333,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   723,   720,     0,     0,
     774,   771,    49,    41,     0,     0,     0,     0,     0,   146,
     147,   148,     0,     0,     0,     0,     0,     0,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,     0,
     170,   171,   149,   150,   151,     0,     0,     0,   163,   164,
     169,     0,     0,     0,   145,     0,     0,     0,     0,   434,
     435,   436,     0,     0,     0,     0,     0,   685,     0,     0,
       0,     0,     0,     0,   172,     0,     0,    68,     0,     0,
       0,   197,   176,     0,     0,     0,     0,     0,     0,   443,
       0,     0,     0,   373,     0,   581,     0,     0,     0,     0,
       0,     0,     0,     0,   610,     0,     0,   525,     0,     0,
       0,   536,   512,     0,   567,   568,   551,     0,     0,   335,
     742,     0,     0,   745,     0,   748,   749,     0,     0,   758,
     759,     0,     0,     0,     0,   722,     0,   779,   773,     0,
       0,     0,     0,     0,   628,   630,   632,     0,     0,   212,
     144,   154,   155,   156,   157,   158,   153,   160,   162,   363,
     500,   539,   446,    38,   593,   595,   439,   440,   441,   442,
     438,     0,     0,   598,   325,     0,     0,     0,     0,     0,
     166,   168,     0,     0,    51,   188,   191,   192,   190,   195,
     196,   194,   423,   425,   427,   571,   421,   429,   433,   431,
       0,   591,   650,   638,   640,   644,   642,   648,   646,   634,
     528,   262,   532,   530,   535,   564,   341,   343,   757,   744,
     747,   752,   753,   751,   755,   761,   763,   765,   767,   212,
      42,     0,     0,     0,   206,     0,   202,   205,   248,   254,
     256,   258,     0,     0,     0,     0,     0,   270,   272,   274,
     276,     0,     0,   280,     0,     0,     0,     0,   286,   288,
     290,   292,   247,     0,   219,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   236,   237,   238,   232,   239,
     240,   241,   233,   234,   235,   242,   243,   244,   245,   246,
       0,   217,     0,   213,   214,   368,     0,   364,   365,   505,
       0,   501,   502,   544,     0,   540,   541,   451,     0,   447,
     448,   304,   305,   306,   307,   308,     0,   296,   299,   300,
     301,   302,   303,   660,     0,   657,   603,     0,   599,   600,
     330,     0,   326,   327,     0,     0,     0,     0,     0,     0,
       0,   346,   349,   350,   351,   352,   353,   354,     0,     0,
       0,   319,     0,   311,   314,   315,   316,   317,   318,   696,
     698,   695,   693,   694,     0,   688,   691,   692,     0,   712,
       0,   715,   708,   709,     0,   702,   705,   706,   707,   710,
       0,   785,     0,   782,     0,   828,     0,   824,   827,    53,
     576,     0,   572,   573,   635,   653,   654,     0,     0,    62,
     769,   174,     0,   204,   201,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   221,
     199,   209,     0,   211,   216,     0,   362,   367,   509,   497,
     504,   548,   538,   543,     0,   445,   450,   298,   295,   662,
     659,   656,   607,   597,   602,     0,   324,   329,     0,     0,
       0,     0,     0,     0,   348,   345,     0,     0,     0,   313,
     310,     0,     0,   690,   687,     0,     0,     0,     0,   704,
     701,   718,     0,   784,   781,     0,   826,   823,    55,     0,
      54,     0,   570,   575,     0,   652,   778,     0,   203,     0,
       0,     0,     0,   260,   263,   264,   265,   266,     0,     0,
       0,     0,   278,   279,     0,   267,   268,   269,   285,     0,
       0,     0,     0,   220,     0,   215,     0,   366,     0,   503,
       0,   542,   495,   474,   475,   476,   459,   460,   479,   480,
     481,   482,   483,   462,   463,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   456,   457,   458,   472,
     473,   469,   470,   471,   468,     0,   453,   461,   477,   478,
     464,   465,   466,   467,   449,   297,   682,     0,   677,   678,
     679,   680,   681,   670,   671,   675,   676,   672,   673,   674,
       0,   663,   664,   667,   668,   669,   658,     0,   601,     0,
     328,   355,   356,   357,   358,   359,   360,   347,   320,   321,
     322,   312,     0,     0,   689,   711,     0,   714,     0,   703,
     800,     0,   798,   796,   790,   794,   795,     0,   787,   792,
     793,   791,   783,   829,   825,    52,    57,     0,   574,     0,
     207,   250,   251,   252,   253,   249,   255,   257,   259,   271,
     273,   275,   277,   282,   283,   284,   281,   287,   289,   291,
     293,   218,   369,   506,   545,   455,   452,     0,     0,   661,
     666,   604,   331,   697,   699,   713,   716,     0,     0,     0,
     789,   786,    56,   577,   636,   454,     0,   684,   665,     0,
     797,     0,   788,   683,     0,   799,   805,     0,   802,     0,
     804,   801,   815,     0,     0,     0,   820,     0,   807,   810,
     811,   812,   813,   814,   803,     0,     0,     0,     0,     0,
     809,   806,     0,   817,   818,   819,     0,   808,   816,   821
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,   -54,  -972,  -568,  -972,   431,
    -972,  -972,  -972,  -972,  -972,  -972,  -615,  -972,  -972,  -972,
     -67,  -972,  -972,  -972,  -972,  -972,  -972,  -972,   429,   599,
       4,    10,    23,   -40,   -23,   -12,    22,    25,    29,    33,
    -972,  -972,  -972,  -972,  -972,    35,    40,    43,    45,    46,
      47,  -972,   434,    50,  -972,    51,  -972,    53,    57,    58,
    -972,    61,  -972,    63,  -972,  -972,  -972,  -972,  -972,   435,
     592,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,   136,  -972,  -972,
    -972,  -972,  -972,  -972,   311,  -972,   117,  -972,  -676,   115,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
     -33,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,    99,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,    76,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,    91,  -972,  -972,  -972,    97,   574,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,    90,  -972,  -972,  -972,  -972,  -972,
    -972,  -971,  -972,  -972,  -972,   116,  -972,  -972,  -972,   121,
     613,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -960,
    -972,   -65,  -972,    70,  -972,    64,    65,    68,    69,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,   109,  -972,  -972,  -108,
     -46,  -972,  -972,  -972,  -972,  -972,   119,  -972,  -972,  -972,
     122,  -972,   577,  -972,   -63,  -972,  -972,  -972,  -972,  -972,
     -42,  -972,  -972,  -972,  -972,  -972,   -35,  -972,  -972,  -972,
     123,  -972,  -972,  -972,   126,  -972,   576,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,    75,  -972,
    -972,  -972,    80,   623,  -972,  -972,   -51,  -972,    -8,  -972,
     -39,  -972,  -972,  -972,   125,  -972,  -972,  -972,   128,  -972,
     624,   -55,  -972,   -15,  -972,     3,  -972,   376,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -957,  -972,  -972,  -972,  -972,
    -972,   131,  -972,  -972,  -972,   -98,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,   101,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,    94,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,   438,   578,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,   444,   579,  -972,  -972,  -972,  -972,
    -972,  -972,   103,  -972,  -972,  -105,  -972,  -972,  -972,  -972,
    -972,  -972,  -122,  -972,  -972,  -138,  -972,  -972,  -972,  -972,
    -972,  -972,  -972,  -972,  -972,  -972,   102,  -972
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   704,
      82,    83,    39,    64,    79,    80,   725,   929,  1029,  1030,
     802,    41,    66,    85,   414,    86,    43,    67,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   440,   164,   165,   166,   167,   168,   169,   170,
     171,   446,   696,   172,   447,   173,   448,   174,   175,   176,
     473,   177,   474,   178,   179,   180,   181,   182,   418,   218,
     219,    45,    68,   220,   481,   221,   482,   728,   222,   483,
     731,   223,   183,   426,   184,   419,   775,   776,   777,   942,
     185,   427,   186,   428,   832,   833,   834,   972,   803,   804,
     805,   945,  1185,   806,   946,   807,   947,   808,   948,   809,
     810,   514,   811,   812,   813,   814,   815,   816,   817,   818,
     954,   819,   955,   820,   956,   821,   957,   822,   823,   824,
     960,  1196,   825,   826,   965,   827,   966,   828,   967,   829,
     968,   187,   463,   856,   857,   858,   859,   860,   861,   862,
     188,   469,   892,   893,   894,   895,   896,   189,   466,   871,
     872,   873,   995,    59,    75,   364,   365,   366,   527,   367,
     528,   190,   467,   880,   881,   882,   883,   884,   885,   886,
     887,   191,   452,   836,   837,   838,   975,    47,    69,   260,
     261,   262,   491,   263,   487,   264,   488,   265,   489,   266,
     492,   267,   495,   268,   494,   192,   193,   194,   195,   459,
     710,   273,   196,   456,   848,   849,   850,   984,  1105,  1106,
     197,   453,    53,    72,   840,   841,   842,   978,    55,    73,
     329,   330,   331,   332,   333,   334,   335,   513,   336,   517,
     337,   516,   338,   339,   518,   340,   198,   454,   844,   845,
     846,   981,    57,    74,   350,   351,   352,   353,   354,   522,
     355,   356,   357,   358,   275,   490,   931,   932,   933,  1031,
      49,    70,   288,   289,   290,   499,   199,   457,   200,   458,
     201,   465,   867,   868,   869,   992,    51,    71,   305,   306,
     307,   202,   423,   203,   424,   204,   425,   311,   509,   936,
    1034,   312,   503,   313,   504,   314,   506,   315,   505,   316,
     508,   317,   507,   318,   502,   282,   496,   937,   205,   464,
     864,   865,   989,  1130,  1131,  1132,  1133,  1134,  1207,  1135,
     206,   207,   470,   904,   905,   906,  1011,   907,  1012,   208,
     471,   914,   915,   916,   917,  1016,   918,   919,  1018,   209,
     472,    61,    76,   386,   387,   388,   389,   533,   390,   391,
     535,   392,   393,   394,   538,   763,   395,   539,   396,   532,
     397,   398,   399,   542,   400,   543,   401,   544,   402,   545,
     210,   417,    63,    77,   405,   406,   407,   548,   408,   211,
     476,   922,   923,  1022,  1167,  1168,  1169,  1170,  1219,  1171,
    1217,  1237,  1238,  1239,  1247,  1248,  1249,  1255,  1250,  1251,
    1252,  1253,  1259,   212,   477,   926,   927,   928
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     149,   217,   236,   284,   301,   285,   327,   346,   363,   383,
      78,   348,   830,  1097,   279,   738,   308,   224,   276,   291,
     303,   742,   341,   359,  1098,   384,   319,  1113,   703,   240,
     278,   924,   349,   761,   274,   287,   302,   361,   362,   987,
     328,   347,   988,   213,   214,   148,   241,   215,    40,    29,
     216,    30,   990,    31,   280,   991,   309,   242,    81,   415,
     225,   277,   292,   304,   416,   342,   360,    42,   385,    44,
     479,    28,   281,   237,   310,   480,    93,    94,    95,   238,
    1193,  1194,  1195,   321,   343,   322,   323,   344,   345,    46,
     703,   243,   239,    48,   244,   485,   127,   128,   245,    84,
     486,   497,   246,    50,   247,   148,   498,   127,   128,   248,
     361,   362,   249,   500,   250,   251,   252,   409,   501,   253,
     254,    52,   255,   529,   403,   404,   256,   257,   530,   320,
     258,    54,   259,   269,   270,   127,   128,   271,   272,  1242,
     286,   124,  1243,  1244,  1245,  1246,    93,    94,    95,   546,
     726,   727,   899,   900,   547,   127,   128,   874,   875,   876,
     877,   878,   879,   550,   691,   692,   693,   694,   551,   293,
    1181,  1182,  1183,  1184,    56,   294,   295,   296,   297,   298,
     299,   479,   300,    99,   100,   101,   939,   762,   550,   321,
      58,   322,   323,   940,   148,   324,   325,   326,   695,   729,
     730,    87,   127,   128,    88,   148,   300,   934,    60,   485,
     123,   124,   321,    89,   941,    90,    91,    92,    93,    94,
      95,    96,    97,    98,   321,   127,   128,   851,   852,   853,
     854,   943,   855,   148,  1097,   969,   944,   127,   128,   969,
     970,  1116,  1117,  1023,   971,  1098,  1024,   123,  1113,    32,
      33,    34,    35,   148,   410,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,  1004,
    1009,  1013,   123,   124,  1005,  1010,  1014,    62,   411,   412,
     124,   127,   128,   125,   126,   413,  1064,   127,   128,   420,
     148,  1019,   129,   283,   127,   128,  1020,   130,   131,   132,
     133,   134,  1160,   421,  1161,  1162,   135,   127,   128,   233,
     546,  1240,   234,   148,  1241,  1021,   136,   422,   429,   137,
     430,   431,   888,   889,   890,   148,   138,   139,  1026,   510,
     969,   140,   497,  1027,   141,  1201,  1205,  1202,   142,   529,
    1220,  1206,   432,   500,  1212,  1221,   552,   553,  1223,  1260,
     706,   707,   708,   709,  1261,   908,   909,   910,   143,   144,
     145,   146,   433,   434,   435,   436,   437,   438,   439,   441,
     147,   442,   443,   444,   445,   449,   450,   451,   455,   148,
     460,   461,   462,   468,   475,   148,   478,   484,   493,   511,
     554,   515,   148,   512,   519,   521,   520,   523,   524,   525,
     526,   559,   149,   531,   534,   911,   536,   537,   217,   540,
     541,   549,   555,   556,   557,   558,   560,   561,   562,   563,
     236,   564,   565,   284,   224,   285,   566,   567,   573,   568,
     569,   570,   279,   571,   301,   572,   276,   579,   574,   291,
     575,   576,   577,   582,   327,   578,   308,   240,   278,   346,
     303,   580,   274,   348,   581,   287,   585,   583,   584,   586,
     341,   587,   588,   589,   241,   359,   302,   225,   590,   383,
     591,   592,   280,   593,   349,   242,   595,   596,   328,   277,
     597,   594,   292,   347,   598,   384,   309,   599,   600,   601,
     281,   237,   602,   304,   603,   604,   605,   238,   606,   607,
     608,   609,   610,   342,   310,   611,   612,   613,   360,   243,
     239,   614,   244,   615,   616,   618,   245,   619,   620,   621,
     246,   623,   247,   624,   625,   626,   627,   248,   385,   628,
     249,   630,   250,   251,   252,   631,   629,   253,   254,   632,
     255,   634,   636,   637,   256,   257,   638,   647,   258,   639,
     259,   269,   270,   640,  1224,   271,   272,   641,   642,   643,
     286,   645,   646,   778,   648,   649,   650,   653,   779,   780,
     781,   782,   783,   784,   785,   786,   787,   788,   789,   790,
     791,   792,   793,   651,   657,   658,   794,   795,   796,   797,
     798,   799,   800,   801,   661,   662,   664,   654,   667,   668,
     671,   663,   672,   149,   655,   217,   660,   665,   673,   674,
     666,   676,   679,   680,   764,   770,   681,   682,   683,   677,
     669,   224,   687,   321,   670,   684,    91,    92,    93,    94,
      95,   685,   686,   688,   689,   690,   697,   698,   699,   891,
     901,   700,   383,   701,   702,   705,   925,    30,   711,   712,
     713,   714,   720,   721,   715,   897,   902,   912,   384,   716,
     717,   718,   719,   722,   225,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   723,   724,   735,   769,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   732,   226,
     227,   228,   733,   124,   734,   740,   831,   835,   898,   903,
     913,   385,   774,   839,   736,   229,   843,   127,   128,   230,
     231,   232,   129,   737,   847,   863,   866,   130,   131,   132,
     739,   741,   233,   743,   870,   234,   135,    91,    92,    93,
      94,    95,   921,   235,   148,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,   930,   744,
     949,   745,   746,   747,   950,   748,   749,   750,   951,   952,
     953,   751,   958,   959,   752,   961,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   753,   754,   143,   144,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     127,   128,   755,   756,   124,   321,   962,   963,   758,   964,
     973,   974,   759,   976,   760,   148,   766,   767,   127,   128,
     977,   231,   979,   129,   980,   982,   983,   768,   130,   131,
     132,   985,   986,   233,   993,   994,   234,   996,   997,  1028,
     998,   999,  1000,  1001,   235,  1002,  1003,  1006,  1007,  1008,
    1015,  1017,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,  1025,  1032,  1033,  1044,  1036,
    1035,   381,   382,  1037,  1039,  1040,  1041,  1042,  1043,  1045,
    1048,  1047,  1046,  1049,  1050,  1051,  1052,  1054,  1059,   143,
     144,  1053,  1055,  1056,  1060,  1061,  1058,  1057,   148,  1062,
    1141,  1142,  1143,  1144,  1152,  1153,  1156,  1145,   236,  1146,
    1148,   327,  1155,  1149,   346,  1158,   148,  1072,   348,  1099,
     279,  1150,  1118,  1175,   276,   301,  1157,   341,   363,  1110,
     359,  1173,  1176,  1108,  1127,   240,   278,   308,  1125,   349,
     274,   303,   891,  1123,  1076,   328,   901,  1179,   347,  1107,
    1180,  1096,   241,  1186,  1124,  1163,  1122,   302,   897,   925,
     280,  1077,   902,   242,   284,  1203,   285,   277,   912,  1111,
     342,  1165,  1078,   360,  1128,  1187,  1109,   309,   281,   237,
     291,  1126,  1188,  1189,   304,   238,  1190,  1112,  1073,  1164,
    1191,  1192,  1129,  1119,  1074,   310,   287,   243,   239,  1120,
     244,   898,  1197,  1198,   245,   903,  1079,  1075,   246,  1080,
     247,   913,  1121,  1081,  1166,   248,  1199,  1082,   249,  1083,
     250,   251,   252,   292,  1084,   253,   254,  1085,   255,  1086,
    1087,  1088,   256,   257,  1089,  1090,   258,  1091,   259,   269,
     270,  1092,  1093,   271,   272,  1094,  1204,  1095,  1101,  1102,
    1208,  1209,  1103,  1104,  1100,  1200,  1210,  1211,  1213,  1214,
    1215,  1218,  1222,  1226,  1227,  1229,  1231,  1236,  1234,  1256,
    1257,  1230,  1233,  1235,  1258,  1262,  1266,   622,   617,  1038,
     938,  1264,  1263,  1265,  1063,  1151,  1115,  1268,  1140,   757,
    1269,  1065,  1139,  1067,  1147,  1114,  1066,  1225,   652,  1069,
    1068,   286,   656,   659,  1216,   765,  1071,  1070,  1178,   771,
     633,  1177,  1228,  1159,  1154,  1232,   935,   773,  1254,  1138,
    1137,  1136,  1267,   635,   675,   772,  1172,     0,  1174,   678,
       0,     0,     0,     0,     0,   644,     0,     0,  1072,     0,
    1099,     0,     0,  1118,     0,     0,     0,     0,     0,     0,
    1110,     0,     0,  1163,  1108,  1127,     0,   920,     0,  1125,
       0,     0,     0,     0,  1123,  1076,     0,     0,     0,  1165,
    1107,     0,  1096,     0,     0,  1124,     0,  1122,     0,     0,
       0,     0,  1077,     0,     0,     0,     0,  1164,     0,     0,
    1111,     0,     0,  1078,     0,  1128,     0,  1109,     0,     0,
       0,     0,  1126,     0,     0,     0,     0,     0,  1112,  1073,
       0,     0,  1166,  1129,  1119,  1074,     0,     0,     0,     0,
    1120,     0,     0,     0,     0,     0,     0,  1079,  1075,     0,
    1080,     0,     0,  1121,  1081,     0,     0,     0,  1082,     0,
    1083,     0,     0,     0,     0,  1084,     0,     0,  1085,     0,
    1086,  1087,  1088,     0,     0,  1089,  1090,     0,  1091,     0,
       0,     0,  1092,  1093,     0,     0,  1094,     0,  1095,  1101,
    1102,     0,     0,  1103,  1104,  1100
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,    74,   688,   984,    69,   630,    71,    68,    69,    70,
      71,   636,    73,    74,   984,    76,    72,   984,   596,    69,
      69,   191,    74,    18,    69,    70,    71,   137,   138,     3,
      73,    74,     6,    15,    16,   205,    69,    19,     7,     5,
      22,     7,     3,     9,    69,     6,    71,    69,   205,     3,
      68,    69,    70,    71,     8,    73,    74,     7,    76,     7,
       3,     0,    69,    69,    71,     8,    28,    29,    30,    69,
      54,    55,    56,    94,    95,    96,    97,    98,    99,     7,
     658,    69,    69,     7,    69,     3,   107,   108,    69,    10,
       8,     3,    69,     7,    69,   205,     8,   107,   108,    69,
     137,   138,    69,     3,    69,    69,    69,     6,     8,    69,
      69,     7,    69,     3,    12,    13,    69,    69,     8,    34,
      69,     7,    69,    69,    69,   107,   108,    69,    69,   183,
      70,    93,   186,   187,   188,   189,    28,    29,    30,     3,
      17,    18,   152,   153,     8,   107,   108,   140,   141,   142,
     143,   144,   145,     3,   174,   175,   176,   177,     8,   121,
      35,    36,    37,    38,     7,   127,   128,   129,   130,   131,
     132,     3,   134,    65,    66,    67,     8,   172,     3,    94,
       7,    96,    97,     8,   205,   100,   101,   102,   208,    20,
      21,    11,   107,   108,    14,   205,   134,   135,     7,     3,
      92,    93,    94,    23,     8,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    94,   107,   108,   127,   128,   129,
     130,     3,   132,   205,  1205,     3,     8,   107,   108,     3,
       8,   123,   124,     3,     8,  1205,     6,    92,  1205,   205,
     206,   207,   208,   205,     3,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,     3,
       3,     3,    92,    93,     8,     8,     8,     7,     4,     8,
      93,   107,   108,   103,   104,     3,   972,   107,   108,     4,
     205,     3,   112,   106,   107,   108,     8,   117,   118,   119,
     120,   121,   182,     4,   184,   185,   126,   107,   108,   122,
       3,     3,   125,   205,     6,     8,   136,     4,     4,   139,
       4,     4,   148,   149,   150,   205,   146,   147,     3,     8,
       3,   151,     3,     8,   154,     8,     3,     8,   158,     3,
       3,     8,     4,     3,     8,     8,   410,   411,     8,     3,
     113,   114,   115,   116,     8,   155,   156,   157,   178,   179,
     180,   181,     4,     4,     4,     4,     4,     4,     4,     4,
     190,     4,     4,     4,     4,     4,     4,     4,     4,   205,
       4,     4,     4,     4,     4,   205,     4,     4,     4,     3,
     205,     4,   205,     8,     4,     3,     8,     4,     4,     8,
       3,   208,   479,     4,     4,   205,     4,     4,   485,     4,
       4,     4,     4,     4,     4,     4,   208,   208,     4,     4,
     497,     4,     4,   500,   485,   500,     4,     4,   208,   206,
     206,   206,   497,   206,   511,   206,   497,     4,   207,   500,
     207,   207,   206,   208,   521,   206,   511,   497,   497,   526,
     511,   206,   497,   526,   206,   500,     4,   208,   208,     4,
     521,     4,   208,   208,   497,   526,   511,   485,   208,   546,
       4,     4,   497,     4,   526,   497,     4,     4,   521,   497,
       4,   206,   500,   526,     4,   546,   511,   208,   208,   208,
     497,   497,     4,   511,     4,     4,     4,   497,     4,   206,
       4,     4,     4,   521,   511,     4,     4,     4,   526,   497,
     497,   208,   497,     4,     4,     4,   497,     4,     4,   208,
     497,     4,   497,     4,     4,     4,     4,   497,   546,     4,
     497,     4,   497,   497,   497,     4,   206,   497,   497,     4,
     497,     4,     4,     4,   497,   497,     4,   206,   497,     4,
     497,   497,   497,     4,  1179,   497,   497,     4,     4,     4,
     500,     4,     4,    34,     4,     4,     4,     4,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,   208,     4,     4,    57,    58,    59,    60,
      61,    62,    63,    64,     4,     4,     4,   208,     4,     4,
       4,   206,     4,   680,   208,   682,   208,   206,     4,     4,
     206,     4,     4,     7,   173,   679,     7,     7,     7,   206,
     208,   682,     7,    94,   208,   205,    26,    27,    28,    29,
      30,   205,   205,     7,     5,   205,   205,   205,     5,   716,
     717,     5,   719,     5,     5,   205,   723,     7,     5,     5,
       5,     5,   205,   205,     7,   716,   717,   718,   719,     7,
       7,     7,     7,     5,   682,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,     7,     5,     5,     5,    79,
      80,    81,    82,    83,    84,    85,    86,    87,   205,    89,
      90,    91,   205,    93,   205,     7,     7,     7,   716,   717,
     718,   719,    24,     7,   205,   105,     7,   107,   108,   109,
     110,   111,   112,   205,     7,     7,     7,   117,   118,   119,
     205,   205,   122,   205,     7,   125,   126,    26,    27,    28,
      29,    30,     7,   133,   205,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,     7,   205,
       4,   205,   205,   205,     4,   205,   205,   205,     4,     4,
       4,   205,     4,     4,   205,     4,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,   205,   205,   178,   179,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
     107,   108,   205,   205,    93,    94,     4,     4,   205,     4,
       6,     3,   205,     6,   205,   205,   205,   205,   107,   108,
       3,   110,     6,   112,     3,     6,     3,   205,   117,   118,
     119,     6,     3,   122,     6,     3,   125,     6,     3,   205,
       4,     4,     4,     4,   133,     4,     4,     4,     4,     4,
       4,     4,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,     4,     6,     3,   208,     6,
       8,   178,   179,     4,     4,     4,     4,     4,   206,   206,
       4,   206,   208,     4,     4,     4,   206,     4,     4,   178,
     179,   206,   206,   206,     4,     4,   206,   208,   205,     4,
     206,   206,   206,   206,     4,     4,     4,   206,   975,   206,
     208,   978,   208,   206,   981,     4,   205,   984,   981,   984,
     975,   206,   989,     6,   975,   992,   206,   978,   995,   984,
     981,   208,     3,   984,   989,   975,   975,   992,   989,   981,
     975,   992,  1009,   989,   984,   978,  1013,     4,   981,   984,
     205,   984,   975,   205,   989,  1022,   989,   992,  1009,  1026,
     975,   984,  1013,   975,  1031,     8,  1031,   975,  1019,   984,
     978,  1022,   984,   981,   989,   205,   984,   992,   975,   975,
    1031,   989,   205,   205,   992,   975,   205,   984,   984,  1022,
     205,   205,   989,   989,   984,   992,  1031,   975,   975,   989,
     975,  1009,   205,   205,   975,  1013,   984,   984,   975,   984,
     975,  1019,   989,   984,  1022,   975,   205,   984,   975,   984,
     975,   975,   975,  1031,   984,   975,   975,   984,   975,   984,
     984,   984,   975,   975,   984,   984,   975,   984,   975,   975,
     975,   984,   984,   975,   975,   984,     8,   984,   984,   984,
       4,     8,   984,   984,   984,   205,     3,     8,   205,   205,
     205,     4,   205,     4,   208,     4,     4,     7,     5,     4,
       4,   206,   205,   205,     4,     4,     4,   485,   479,   943,
     769,   206,   208,   206,   969,  1009,   987,   205,   997,   658,
     205,   974,   995,   977,  1004,   986,   975,  1205,   521,   980,
     978,  1031,   526,   529,  1158,   671,   983,   981,  1033,   680,
     497,  1031,  1210,  1019,  1013,  1220,   740,   682,  1240,   994,
     992,   990,  1260,   500,   546,   681,  1023,    -1,  1026,   550,
      -1,    -1,    -1,    -1,    -1,   511,    -1,    -1,  1205,    -1,
    1205,    -1,    -1,  1210,    -1,    -1,    -1,    -1,    -1,    -1,
    1205,    -1,    -1,  1220,  1205,  1210,    -1,   719,    -1,  1210,
      -1,    -1,    -1,    -1,  1210,  1205,    -1,    -1,    -1,  1220,
    1205,    -1,  1205,    -1,    -1,  1210,    -1,  1210,    -1,    -1,
      -1,    -1,  1205,    -1,    -1,    -1,    -1,  1220,    -1,    -1,
    1205,    -1,    -1,  1205,    -1,  1210,    -1,  1205,    -1,    -1,
      -1,    -1,  1210,    -1,    -1,    -1,    -1,    -1,  1205,  1205,
      -1,    -1,  1220,  1210,  1210,  1205,    -1,    -1,    -1,    -1,
    1210,    -1,    -1,    -1,    -1,    -1,    -1,  1205,  1205,    -1,
    1205,    -1,    -1,  1210,  1205,    -1,    -1,    -1,  1205,    -1,
    1205,    -1,    -1,    -1,    -1,  1205,    -1,    -1,  1205,    -1,
    1205,  1205,  1205,    -1,    -1,  1205,  1205,    -1,  1205,    -1,
      -1,    -1,  1205,  1205,    -1,    -1,  1205,    -1,  1205,  1205,
    1205,    -1,    -1,  1205,  1205,  1205
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,     0,     5,
       7,     9,   205,   206,   207,   208,   224,   225,   226,   231,
       7,   240,     7,   245,     7,   290,     7,   406,     7,   489,
       7,   505,     7,   441,     7,   447,     7,   471,     7,   382,
       7,   570,     7,   601,   232,   227,   241,   246,   291,   407,
     490,   506,   442,   448,   472,   383,   571,   602,   224,   233,
     234,   205,   229,   230,    10,   242,   244,    11,    14,    23,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    92,    93,   103,   104,   107,   108,   112,
     117,   118,   119,   120,   121,   126,   136,   139,   146,   147,
     151,   154,   158,   178,   179,   180,   181,   190,   205,   239,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   262,   263,   264,   265,   266,   267,
     268,   269,   272,   274,   276,   277,   278,   280,   282,   283,
     284,   285,   286,   301,   303,   309,   311,   360,   369,   376,
     390,   400,   424,   425,   426,   427,   431,   439,   465,   495,
     497,   499,   510,   512,   514,   537,   549,   550,   558,   568,
     599,   608,   632,    15,    16,    19,    22,   239,   288,   289,
     292,   294,   297,   300,   495,   497,    89,    90,    91,   105,
     109,   110,   111,   122,   125,   133,   239,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   264,   265,   266,
     267,   268,   269,   272,   274,   276,   277,   278,   280,   282,
     408,   409,   410,   412,   414,   416,   418,   420,   422,   424,
     425,   426,   427,   430,   465,   483,   495,   497,   499,   510,
     512,   514,   534,   106,   239,   420,   422,   465,   491,   492,
     493,   495,   497,   121,   127,   128,   129,   130,   131,   132,
     134,   239,   465,   495,   497,   507,   508,   509,   510,   512,
     514,   516,   520,   522,   524,   526,   528,   530,   532,   439,
      34,    94,    96,    97,   100,   101,   102,   239,   329,   449,
     450,   451,   452,   453,   454,   455,   457,   459,   461,   462,
     464,   495,   497,    95,    98,    99,   239,   329,   453,   459,
     473,   474,   475,   476,   477,   479,   480,   481,   482,   495,
     497,   137,   138,   239,   384,   385,   386,   388,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   178,   179,   239,   495,   497,   572,   573,   574,   575,
     577,   578,   580,   581,   582,   585,   587,   589,   590,   591,
     593,   595,   597,    12,    13,   603,   604,   605,   607,     6,
       3,     4,     8,     3,   243,     3,     8,   600,   287,   304,
       4,     4,     4,   511,   513,   515,   302,   310,   312,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     261,     4,     4,     4,     4,     4,   270,   273,   275,     4,
       4,     4,   401,   440,   466,     4,   432,   496,   498,   428,
       4,     4,     4,   361,   538,   500,   377,   391,     4,   370,
     551,   559,   569,   279,   281,     4,   609,   633,     4,     3,
       8,   293,   295,   298,     4,     3,     8,   413,   415,   417,
     484,   411,   419,     4,   423,   421,   535,     3,     8,   494,
       3,     8,   533,   521,   523,   527,   525,   531,   529,   517,
       8,     3,     8,   456,   330,     4,   460,   458,   463,     4,
       8,     3,   478,     4,     4,     8,     3,   387,   389,     3,
       8,     4,   588,   576,     4,   579,     4,     4,   583,   586,
       4,     4,   592,   594,   596,   598,     3,     8,   606,     4,
       3,     8,   224,   224,   205,     4,     4,     4,     4,   208,
     208,   208,     4,     4,     4,     4,     4,     4,   206,   206,
     206,   206,   206,   208,   207,   207,   207,   206,   206,     4,
     206,   206,   208,   208,   208,     4,     4,     4,   208,   208,
     208,     4,     4,     4,   206,     4,     4,     4,     4,   208,
     208,   208,     4,     4,     4,     4,     4,   206,     4,     4,
       4,     4,     4,     4,   208,     4,     4,   248,     4,     4,
       4,   208,   289,     4,     4,     4,     4,     4,     4,   206,
       4,     4,     4,   409,     4,   492,     4,     4,     4,     4,
       4,     4,     4,     4,   509,     4,     4,   206,     4,     4,
       4,   208,   451,     4,   208,   208,   475,     4,     4,   385,
     208,     4,     4,   206,     4,   206,   206,     4,     4,   208,
     208,     4,     4,     4,     4,   573,     4,   206,   604,     4,
       7,     7,     7,     7,   205,   205,   205,     7,     7,     5,
     205,   174,   175,   176,   177,   208,   271,   205,   205,     5,
       5,     5,     5,   226,   228,   205,   113,   114,   115,   116,
     429,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     205,   205,     5,     7,     5,   235,    17,    18,   296,    20,
      21,   299,   205,   205,   205,     5,   205,   205,   235,   205,
       7,   205,   235,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   228,   205,   205,
     205,    18,   172,   584,   173,   271,   205,   205,   205,     5,
     224,   247,   603,   288,    24,   305,   306,   307,    34,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    57,    58,    59,    60,    61,    62,
      63,    64,   239,   317,   318,   319,   322,   324,   326,   328,
     329,   331,   332,   333,   334,   335,   336,   337,   338,   340,
     342,   344,   346,   347,   348,   351,   352,   354,   356,   358,
     317,     7,   313,   314,   315,     7,   402,   403,   404,     7,
     443,   444,   445,     7,   467,   468,   469,     7,   433,   434,
     435,   127,   128,   129,   130,   132,   362,   363,   364,   365,
     366,   367,   368,     7,   539,   540,     7,   501,   502,   503,
       7,   378,   379,   380,   140,   141,   142,   143,   144,   145,
     392,   393,   394,   395,   396,   397,   398,   399,   148,   149,
     150,   239,   371,   372,   373,   374,   375,   495,   497,   152,
     153,   239,   495,   497,   552,   553,   554,   556,   155,   156,
     157,   205,   495,   497,   560,   561,   562,   563,   565,   566,
     572,     7,   610,   611,   191,   239,   634,   635,   636,   236,
       7,   485,   486,   487,   135,   516,   518,   536,   313,     8,
       8,     8,   308,     3,     8,   320,   323,   325,   327,     4,
       4,     4,     4,     4,   339,   341,   343,   345,     4,     4,
     349,     4,     4,     4,     4,   353,   355,   357,   359,     3,
       8,     8,   316,     6,     3,   405,     6,     3,   446,     6,
       3,   470,     6,     3,   436,     6,     3,     3,     6,   541,
       3,     6,   504,     6,     3,   381,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   555,   557,     3,     8,     4,   564,     4,   567,     3,
       8,     8,   612,     3,     6,     4,     3,     8,   205,   237,
     238,   488,     6,     3,   519,     8,     6,     4,   306,     4,
       4,     4,     4,   206,   208,   206,   208,   206,     4,     4,
       4,     4,   206,   206,     4,   206,   206,   208,   206,     4,
       4,     4,     4,   318,   317,   315,   408,   404,   449,   445,
     473,   469,   239,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   264,   265,   266,   267,   268,   269,   272,
     274,   276,   277,   278,   280,   282,   329,   400,   418,   420,
     422,   424,   425,   426,   427,   437,   438,   465,   495,   497,
     510,   512,   514,   534,   435,   363,   123,   124,   239,   249,
     250,   251,   329,   439,   465,   495,   497,   510,   512,   514,
     542,   543,   544,   545,   546,   548,   540,   507,   503,   384,
     380,   206,   206,   206,   206,   206,   206,   393,   208,   206,
     206,   372,     4,     4,   553,   208,     4,   206,     4,   561,
     182,   184,   185,   239,   329,   495,   497,   613,   614,   615,
     616,   618,   611,   208,   635,     6,     3,   491,   487,     4,
     205,    35,    36,    37,    38,   321,   205,   205,   205,   205,
     205,   205,   205,    54,    55,    56,   350,   205,   205,   205,
     205,     8,     8,     8,     8,     3,     8,   547,     4,     8,
       3,     8,     8,   205,   205,   205,   224,   619,     4,   617,
       3,     8,   205,     8,   235,   438,     4,   208,   544,     4,
     206,     4,   614,   205,     5,   205,     7,   620,   621,   622,
       3,     6,   183,   186,   187,   188,   189,   623,   624,   625,
     627,   628,   629,   630,   621,   626,     4,     4,     4,   631,
       3,     8,     4,   208,   206,   206,     4,   624,   205,   205
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
     248,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   261,   260,   262,   263,   264,   265,   266,
     267,   268,   270,   269,   271,   271,   271,   271,   271,   273,
     272,   275,   274,   276,   277,   279,   278,   281,   280,   282,
     283,   284,   285,   287,   286,   288,   288,   288,   289,   289,
     289,   289,   289,   289,   289,   291,   290,   293,   292,   295,
     294,   296,   296,   298,   297,   299,   299,   300,   302,   301,
     304,   303,   305,   305,   305,   306,   308,   307,   310,   309,
     312,   311,   313,   313,   314,   314,   314,   316,   315,   317,
     317,   317,   318,   318,   318,   318,   318,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   320,   319,
     321,   321,   321,   321,   323,   322,   325,   324,   327,   326,
     328,   330,   329,   331,   332,   333,   334,   335,   336,   337,
     339,   338,   341,   340,   343,   342,   345,   344,   346,   347,
     349,   348,   350,   350,   350,   351,   353,   352,   355,   354,
     357,   356,   359,   358,   361,   360,   362,   362,   362,   363,
     363,   363,   363,   363,   364,   365,   366,   367,   368,   370,
     369,   371,   371,   371,   372,   372,   372,   372,   372,   372,
     373,   374,   375,   377,   376,   378,   378,   379,   379,   379,
     381,   380,   383,   382,   384,   384,   384,   384,   385,   385,
     387,   386,   389,   388,   391,   390,   392,   392,   392,   393,
     393,   393,   393,   393,   393,   394,   395,   396,   397,   398,
     399,   401,   400,   402,   402,   403,   403,   403,   405,   404,
     407,   406,   408,   408,   408,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   409,   409,   409,   409,
     409,   409,   409,   409,   409,   409,   409,   409,   409,   409,
     411,   410,   413,   412,   415,   414,   417,   416,   419,   418,
     421,   420,   423,   422,   424,   425,   426,   428,   427,   429,
     429,   429,   429,   430,   432,   431,   433,   433,   434,   434,
     434,   436,   435,   437,   437,   437,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   438,   438,   438,   438,
     438,   438,   438,   438,   438,   438,   440,   439,   442,   441,
     443,   443,   444,   444,   444,   446,   445,   448,   447,   449,
     449,   450,   450,   450,   451,   451,   451,   451,   451,   451,
     451,   451,   451,   451,   452,   453,   454,   456,   455,   458,
     457,   460,   459,   461,   463,   462,   464,   466,   465,   467,
     467,   468,   468,   468,   470,   469,   472,   471,   473,   473,
     474,   474,   474,   475,   475,   475,   475,   475,   475,   475,
     475,   475,   476,   478,   477,   479,   480,   481,   482,   484,
     483,   485,   485,   486,   486,   486,   488,   487,   490,   489,
     491,   491,   491,   492,   492,   492,   492,   492,   492,   492,
     494,   493,   496,   495,   498,   497,   500,   499,   501,   501,
     502,   502,   502,   504,   503,   506,   505,   507,   507,   508,
     508,   508,   509,   509,   509,   509,   509,   509,   509,   509,
     509,   509,   509,   509,   509,   509,   509,   511,   510,   513,
     512,   515,   514,   517,   516,   519,   518,   521,   520,   523,
     522,   525,   524,   527,   526,   529,   528,   531,   530,   533,
     532,   535,   534,   536,   536,   538,   537,   539,   539,   539,
     541,   540,   542,   542,   543,   543,   543,   544,   544,   544,
     544,   544,   544,   544,   544,   544,   544,   544,   544,   544,
     544,   545,   547,   546,   548,   549,   551,   550,   552,   552,
     552,   553,   553,   553,   553,   553,   555,   554,   557,   556,
     559,   558,   560,   560,   560,   561,   561,   561,   561,   561,
     561,   562,   564,   563,   565,   567,   566,   569,   568,   571,
     570,   572,   572,   572,   573,   573,   573,   573,   573,   573,
     573,   573,   573,   573,   573,   573,   573,   573,   573,   573,
     573,   573,   574,   576,   575,   577,   579,   578,   580,   581,
     583,   582,   584,   584,   586,   585,   588,   587,   589,   590,
     592,   591,   594,   593,   596,   595,   598,   597,   600,   599,
     602,   601,   603,   603,   603,   604,   604,   606,   605,   607,
     609,   608,   610,   610,   610,   612,   611,   613,   613,   613,
     614,   614,   614,   614,   614,   614,   614,   615,   617,   616,
     619,   618,   620,   620,   620,   622,   621,   623,   623,   623,
     624,   624,   624,   624,   624,   626,   625,   627,   628,   629,
     631,   630,   633,   632,   634,   634,   634,   635,   635,   636
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       0,     4,     1,     1,     1,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     6,     1,     3,     2,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     0,     6,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     0,     6,     3,
       0,     6,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     3
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
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"trust-anchor\"",
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
  "on_fail_mode", "max_row_errors", "trust_anchor", "$@47", "cert_file",
  "$@48", "key_file", "$@49", "cipher_list", "$@50",
  "host_reservation_identifiers", "$@51",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@52", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@53", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@54",
  "sub_hooks_library", "$@55", "hooks_params", "hooks_param", "library",
  "$@56", "parameters", "$@57", "expired_leases_processing", "$@58",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@59",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@60",
  "sub_subnet4", "$@61", "subnet4_params", "subnet4_param", "subnet",
  "$@62", "subnet_4o6_interface", "$@63", "subnet_4o6_interface_id",
  "$@64", "subnet_4o6_subnet", "$@65", "interface", "$@66", "client_class",
  "$@67", "require_client_classes", "$@68", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@69", "hr_mode", "id", "shared_networks", "$@70",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@71", "shared_network_params", "shared_network_param",
  "option_def_list", "$@72", "sub_option_def_list", "$@73",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@74", "sub_option_def", "$@75",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@76",
  "option_def_record_types", "$@77", "space", "$@78", "option_def_space",
  "option_def_encapsulate", "$@79", "option_def_array", "option_data_list",
  "$@80", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@81", "sub_option_data", "$@82",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@83",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@84", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@85", "sub_pool4", "$@86",
  "pool_params", "pool_param", "pool_entry", "$@87", "user_context",
  "$@88", "comment", "$@89", "reservations", "$@90", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@91", "sub_reservation",
  "$@92", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@93", "server_hostname", "$@94",
  "boot_file_name", "$@95", "ip_address", "$@96", "ip_addresses", "$@97",
  "duid", "$@98", "hw_address", "$@99", "client_id_value", "$@100",
  "circuit_id_value", "$@101", "flex_id_value", "$@102", "hostname",
  "$@103", "reservation_client_classes", "$@104", "relay", "$@105",
  "relay_map", "client_classes", "$@106", "client_classes_list",
  "client_class_entry", "$@107", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@108", "only_if_required",
  "dhcp4o6_port", "control_socket", "$@109", "control_socket_params",
  "control_socket_param", "control_socket_type", "$@110",
  "control_socket_name", "$@111", "dhcp_queue_control", "$@112",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@113", "capacity", "arbitrary_map_entry", "$@114",
  "dhcp_ddns", "$@115", "sub_dhcp_ddns", "$@116", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@117", "server_port",
  "sender_ip", "$@118", "sender_port", "max_queue_size", "ncr_protocol",
  "$@119", "ncr_protocol_value", "ncr_format", "$@120",
  "dep_qualifying_suffix", "$@121", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@122",
  "dep_generated_prefix", "$@123", "dep_hostname_char_set", "$@124",
  "dep_hostname_char_replacement", "$@125", "config_control", "$@126",
  "sub_config_control", "$@127", "config_control_params",
  "config_control_param", "config_databases", "$@128",
  "config_fetch_wait_time", "loggers", "$@129", "loggers_entries",
  "logger_entry", "$@130", "logger_params", "logger_param", "debuglevel",
  "severity", "$@131", "output_options_list", "$@132",
  "output_options_list_content", "output_entry", "$@133",
  "output_params_list", "output_params", "output", "$@134", "flush",
  "maxsize", "maxver", "pattern", "$@135", "compatibility", "$@136",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
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
     545,   546,   549,   555,   561,   567,   573,   579,   585,   591,
     597,   603,   609,   615,   615,   624,   630,   636,   642,   648,
     654,   660,   666,   666,   675,   678,   681,   684,   687,   693,
     693,   702,   702,   711,   717,   723,   723,   732,   732,   741,
     747,   753,   759,   765,   765,   777,   778,   779,   784,   785,
     786,   787,   788,   789,   790,   793,   793,   802,   802,   813,
     813,   821,   822,   825,   825,   833,   835,   839,   846,   846,
     859,   859,   870,   871,   872,   877,   879,   879,   898,   898,
     911,   911,   922,   923,   926,   927,   928,   933,   933,   943,
     944,   945,   950,   951,   952,   953,   954,   955,   956,   957,
     958,   959,   960,   961,   962,   963,   964,   965,   966,   967,
     968,   969,   970,   971,   972,   973,   974,   975,   978,   978,
     986,   987,   988,   989,   992,   992,  1001,  1001,  1010,  1010,
    1019,  1025,  1025,  1034,  1040,  1046,  1052,  1058,  1064,  1070,
    1076,  1076,  1085,  1085,  1094,  1094,  1103,  1103,  1112,  1118,
    1124,  1124,  1132,  1133,  1134,  1137,  1143,  1143,  1152,  1152,
    1161,  1161,  1170,  1170,  1179,  1179,  1190,  1191,  1192,  1197,
    1198,  1199,  1200,  1201,  1204,  1209,  1214,  1219,  1224,  1231,
    1231,  1244,  1245,  1246,  1251,  1252,  1253,  1254,  1255,  1256,
    1259,  1265,  1271,  1277,  1277,  1288,  1289,  1292,  1293,  1294,
    1299,  1299,  1309,  1309,  1319,  1320,  1321,  1324,  1327,  1328,
    1331,  1331,  1340,  1340,  1349,  1349,  1361,  1362,  1363,  1368,
    1369,  1370,  1371,  1372,  1373,  1376,  1382,  1388,  1394,  1400,
    1406,  1415,  1415,  1429,  1430,  1433,  1434,  1435,  1444,  1444,
    1470,  1470,  1481,  1482,  1483,  1489,  1490,  1491,  1492,  1493,
    1494,  1495,  1496,  1497,  1498,  1499,  1500,  1501,  1502,  1503,
    1504,  1505,  1506,  1507,  1508,  1509,  1510,  1511,  1512,  1513,
    1514,  1515,  1516,  1517,  1518,  1519,  1520,  1521,  1522,  1523,
    1524,  1525,  1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,
    1536,  1536,  1545,  1545,  1554,  1554,  1563,  1563,  1572,  1572,
    1581,  1581,  1590,  1590,  1601,  1607,  1613,  1619,  1619,  1627,
    1628,  1629,  1630,  1633,  1641,  1641,  1653,  1654,  1658,  1659,
    1660,  1665,  1665,  1673,  1674,  1675,  1680,  1681,  1682,  1683,
    1684,  1685,  1686,  1687,  1688,  1689,  1690,  1691,  1692,  1693,
    1694,  1695,  1696,  1697,  1698,  1699,  1700,  1701,  1702,  1703,
    1704,  1705,  1706,  1707,  1708,  1709,  1710,  1711,  1712,  1713,
    1714,  1715,  1716,  1717,  1718,  1719,  1726,  1726,  1740,  1740,
    1749,  1750,  1753,  1754,  1755,  1762,  1762,  1777,  1777,  1791,
    1792,  1795,  1796,  1797,  1802,  1803,  1804,  1805,  1806,  1807,
    1808,  1809,  1810,  1811,  1814,  1816,  1822,  1824,  1824,  1833,
    1833,  1842,  1842,  1851,  1853,  1853,  1862,  1872,  1872,  1885,
    1886,  1891,  1892,  1893,  1900,  1900,  1912,  1912,  1924,  1925,
    1930,  1931,  1932,  1939,  1940,  1941,  1942,  1943,  1944,  1945,
    1946,  1947,  1950,  1952,  1952,  1961,  1963,  1965,  1971,  1980,
    1980,  1993,  1994,  1997,  1998,  1999,  2004,  2004,  2014,  2014,
    2024,  2025,  2026,  2031,  2032,  2033,  2034,  2035,  2036,  2037,
    2040,  2040,  2049,  2049,  2074,  2074,  2104,  2104,  2115,  2116,
    2119,  2120,  2121,  2126,  2126,  2135,  2135,  2144,  2145,  2148,
    2149,  2150,  2156,  2157,  2158,  2159,  2160,  2161,  2162,  2163,
    2164,  2165,  2166,  2167,  2168,  2169,  2170,  2173,  2173,  2182,
    2182,  2191,  2191,  2200,  2200,  2209,  2209,  2220,  2220,  2229,
    2229,  2238,  2238,  2247,  2247,  2256,  2256,  2265,  2265,  2274,
    2274,  2288,  2288,  2299,  2300,  2306,  2306,  2317,  2318,  2319,
    2324,  2324,  2334,  2335,  2338,  2339,  2340,  2345,  2346,  2347,
    2348,  2349,  2350,  2351,  2352,  2353,  2354,  2355,  2356,  2357,
    2358,  2361,  2363,  2363,  2372,  2380,  2388,  2388,  2399,  2400,
    2401,  2406,  2407,  2408,  2409,  2410,  2413,  2413,  2422,  2422,
    2434,  2434,  2447,  2448,  2449,  2454,  2455,  2456,  2457,  2458,
    2459,  2462,  2468,  2468,  2477,  2483,  2483,  2493,  2493,  2506,
    2506,  2516,  2517,  2518,  2523,  2524,  2525,  2526,  2527,  2528,
    2529,  2530,  2531,  2532,  2533,  2534,  2535,  2536,  2537,  2538,
    2539,  2540,  2543,  2549,  2549,  2558,  2564,  2564,  2573,  2579,
    2585,  2585,  2594,  2595,  2598,  2598,  2608,  2608,  2618,  2625,
    2632,  2632,  2641,  2641,  2651,  2651,  2661,  2661,  2673,  2673,
    2685,  2685,  2695,  2696,  2697,  2703,  2704,  2707,  2707,  2718,
    2726,  2726,  2739,  2740,  2741,  2747,  2747,  2755,  2756,  2757,
    2762,  2763,  2764,  2765,  2766,  2767,  2768,  2771,  2777,  2777,
    2786,  2786,  2797,  2798,  2799,  2804,  2804,  2812,  2813,  2814,
    2819,  2820,  2821,  2822,  2823,  2826,  2826,  2835,  2841,  2847,
    2853,  2853,  2862,  2862,  2873,  2874,  2875,  2880,  2881,  2884
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
#line 6209 "dhcp4_parser.cc"

#line 2890 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
