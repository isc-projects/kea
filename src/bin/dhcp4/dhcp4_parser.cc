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

  case 216: // $@33: %empty
#line 913 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1770 "dhcp4_parser.cc"
    break;

  case 217: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 916 "dhcp4_parser.yy"
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

  case 218: // $@34: %empty
#line 932 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1802 "dhcp4_parser.cc"
    break;

  case 219: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 938 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1813 "dhcp4_parser.cc"
    break;

  case 220: // $@35: %empty
#line 945 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1825 "dhcp4_parser.cc"
    break;

  case 221: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 951 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1834 "dhcp4_parser.cc"
    break;

  case 226: // not_empty_database_list: not_empty_database_list ","
#line 962 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1842 "dhcp4_parser.cc"
    break;

  case 227: // $@36: %empty
#line 967 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1852 "dhcp4_parser.cc"
    break;

  case 228: // database: "{" $@36 database_map_params "}"
#line 971 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1862 "dhcp4_parser.cc"
    break;

  case 231: // database_map_params: database_map_params ","
#line 979 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1870 "dhcp4_parser.cc"
    break;

  case 254: // $@37: %empty
#line 1008 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1879 "dhcp4_parser.cc"
    break;

  case 255: // database_type: "type" $@37 ":" db_type
#line 1011 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1888 "dhcp4_parser.cc"
    break;

  case 256: // db_type: "memfile"
#line 1016 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1894 "dhcp4_parser.cc"
    break;

  case 257: // db_type: "mysql"
#line 1017 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1900 "dhcp4_parser.cc"
    break;

  case 258: // db_type: "postgresql"
#line 1018 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1906 "dhcp4_parser.cc"
    break;

  case 259: // $@38: %empty
#line 1021 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1915 "dhcp4_parser.cc"
    break;

  case 260: // user: "user" $@38 ":" "constant string"
#line 1024 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1925 "dhcp4_parser.cc"
    break;

  case 261: // $@39: %empty
#line 1030 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1934 "dhcp4_parser.cc"
    break;

  case 262: // password: "password" $@39 ":" "constant string"
#line 1033 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1944 "dhcp4_parser.cc"
    break;

  case 263: // $@40: %empty
#line 1039 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 264: // host: "host" $@40 ":" "constant string"
#line 1042 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc"
    break;

  case 265: // port: "port" ":" "integer"
#line 1048 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1973 "dhcp4_parser.cc"
    break;

  case 266: // $@41: %empty
#line 1054 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1982 "dhcp4_parser.cc"
    break;

  case 267: // name: "name" $@41 ":" "constant string"
#line 1057 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1992 "dhcp4_parser.cc"
    break;

  case 268: // persist: "persist" ":" "boolean"
#line 1063 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2002 "dhcp4_parser.cc"
    break;

  case 269: // lfc_interval: "lfc-interval" ":" "integer"
#line 1069 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2012 "dhcp4_parser.cc"
    break;

  case 270: // readonly: "readonly" ":" "boolean"
#line 1075 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2022 "dhcp4_parser.cc"
    break;

  case 271: // connect_timeout: "connect-timeout" ":" "integer"
#line 1081 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2032 "dhcp4_parser.cc"
    break;

  case 272: // read_timeout: "read-timeout" ":" "integer"
#line 1087 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2042 "dhcp4_parser.cc"
    break;

  case 273: // write_timeout: "write-timeout" ":" "integer"
#line 1093 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2052 "dhcp4_parser.cc"
    break;

  case 274: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1099 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2062 "dhcp4_parser.cc"
    break;

  case 275: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1105 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2072 "dhcp4_parser.cc"
    break;

  case 276: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1111 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2082 "dhcp4_parser.cc"
    break;

  case 277: // $@42: %empty
#line 1117 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2091 "dhcp4_parser.cc"
    break;

  case 278: // on_fail: "on-fail" $@42 ":" on_fail_mode
#line 1120 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 279: // on_fail_mode: "stop-retry-exit"
#line 1125 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2106 "dhcp4_parser.cc"
    break;

  case 280: // on_fail_mode: "serve-retry-exit"
#line 1126 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2112 "dhcp4_parser.cc"
    break;

  case 281: // on_fail_mode: "serve-retry-continue"
#line 1127 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2118 "dhcp4_parser.cc"
    break;

  case 282: // max_row_errors: "max-row-errors" ":" "integer"
#line 1130 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2128 "dhcp4_parser.cc"
    break;

  case 283: // $@43: %empty
#line 1136 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2137 "dhcp4_parser.cc"
    break;

  case 284: // trust_anchor: "trust-anchor" $@43 ":" "constant string"
#line 1139 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2147 "dhcp4_parser.cc"
    break;

  case 285: // $@44: %empty
#line 1145 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2156 "dhcp4_parser.cc"
    break;

  case 286: // cert_file: "cert-file" $@44 ":" "constant string"
#line 1148 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2166 "dhcp4_parser.cc"
    break;

  case 287: // $@45: %empty
#line 1154 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2175 "dhcp4_parser.cc"
    break;

  case 288: // key_file: "key-file" $@45 ":" "constant string"
#line 1157 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2185 "dhcp4_parser.cc"
    break;

  case 289: // $@46: %empty
#line 1163 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp4_parser.cc"
    break;

  case 290: // cipher_list: "cipher-list" $@46 ":" "constant string"
#line 1166 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2204 "dhcp4_parser.cc"
    break;

  case 291: // $@47: %empty
#line 1172 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2216 "dhcp4_parser.cc"
    break;

  case 292: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1178 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2225 "dhcp4_parser.cc"
    break;

  case 295: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1185 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2233 "dhcp4_parser.cc"
    break;

  case 301: // duid_id: "duid"
#line 1197 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2242 "dhcp4_parser.cc"
    break;

  case 302: // hw_address_id: "hw-address"
#line 1202 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 303: // circuit_id: "circuit-id"
#line 1207 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2260 "dhcp4_parser.cc"
    break;

  case 304: // client_id: "client-id"
#line 1212 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2269 "dhcp4_parser.cc"
    break;

  case 305: // flex_id: "flex-id"
#line 1217 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2278 "dhcp4_parser.cc"
    break;

  case 306: // $@48: %empty
#line 1224 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2290 "dhcp4_parser.cc"
    break;

  case 307: // dhcp_multi_threading: "multi-threading" $@48 ":" "{" multi_threading_params "}"
#line 1230 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2301 "dhcp4_parser.cc"
    break;

  case 310: // multi_threading_params: multi_threading_params ","
#line 1239 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2309 "dhcp4_parser.cc"
    break;

  case 317: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1252 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2319 "dhcp4_parser.cc"
    break;

  case 318: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1258 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2329 "dhcp4_parser.cc"
    break;

  case 319: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1264 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2339 "dhcp4_parser.cc"
    break;

  case 320: // $@49: %empty
#line 1270 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 321: // hooks_libraries: "hooks-libraries" $@49 ":" "[" hooks_libraries_list "]"
#line 1276 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2360 "dhcp4_parser.cc"
    break;

  case 326: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1287 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2368 "dhcp4_parser.cc"
    break;

  case 327: // $@50: %empty
#line 1292 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2378 "dhcp4_parser.cc"
    break;

  case 328: // hooks_library: "{" $@50 hooks_params "}"
#line 1296 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2388 "dhcp4_parser.cc"
    break;

  case 329: // $@51: %empty
#line 1302 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 330: // sub_hooks_library: "{" $@51 hooks_params "}"
#line 1306 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2408 "dhcp4_parser.cc"
    break;

  case 333: // hooks_params: hooks_params ","
#line 1314 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2416 "dhcp4_parser.cc"
    break;

  case 337: // $@52: %empty
#line 1324 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 338: // library: "library" $@52 ":" "constant string"
#line 1327 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 339: // $@53: %empty
#line 1333 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2444 "dhcp4_parser.cc"
    break;

  case 340: // parameters: "parameters" $@53 ":" map_value
#line 1336 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2453 "dhcp4_parser.cc"
    break;

  case 341: // $@54: %empty
#line 1342 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2465 "dhcp4_parser.cc"
    break;

  case 342: // expired_leases_processing: "expired-leases-processing" $@54 ":" "{" expired_leases_params "}"
#line 1348 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2475 "dhcp4_parser.cc"
    break;

  case 345: // expired_leases_params: expired_leases_params ","
#line 1356 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2483 "dhcp4_parser.cc"
    break;

  case 352: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1369 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2493 "dhcp4_parser.cc"
    break;

  case 353: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1375 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2503 "dhcp4_parser.cc"
    break;

  case 354: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1381 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2513 "dhcp4_parser.cc"
    break;

  case 355: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1387 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2523 "dhcp4_parser.cc"
    break;

  case 356: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1393 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2533 "dhcp4_parser.cc"
    break;

  case 357: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1399 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2543 "dhcp4_parser.cc"
    break;

  case 358: // $@55: %empty
#line 1408 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2555 "dhcp4_parser.cc"
    break;

  case 359: // subnet4_list: "subnet4" $@55 ":" "[" subnet4_list_content "]"
#line 1414 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2564 "dhcp4_parser.cc"
    break;

  case 364: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1428 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2572 "dhcp4_parser.cc"
    break;

  case 365: // $@56: %empty
#line 1437 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2582 "dhcp4_parser.cc"
    break;

  case 366: // subnet4: "{" $@56 subnet4_params "}"
#line 1441 "dhcp4_parser.yy"
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
#line 2608 "dhcp4_parser.cc"
    break;

  case 367: // $@57: %empty
#line 1463 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2618 "dhcp4_parser.cc"
    break;

  case 368: // sub_subnet4: "{" $@57 subnet4_params "}"
#line 1467 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2628 "dhcp4_parser.cc"
    break;

  case 371: // subnet4_params: subnet4_params ","
#line 1476 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2636 "dhcp4_parser.cc"
    break;

  case 417: // $@58: %empty
#line 1529 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2645 "dhcp4_parser.cc"
    break;

  case 418: // subnet: "subnet" $@58 ":" "constant string"
#line 1532 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2655 "dhcp4_parser.cc"
    break;

  case 419: // $@59: %empty
#line 1538 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2664 "dhcp4_parser.cc"
    break;

  case 420: // subnet_4o6_interface: "4o6-interface" $@59 ":" "constant string"
#line 1541 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2674 "dhcp4_parser.cc"
    break;

  case 421: // $@60: %empty
#line 1547 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 422: // subnet_4o6_interface_id: "4o6-interface-id" $@60 ":" "constant string"
#line 1550 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2693 "dhcp4_parser.cc"
    break;

  case 423: // $@61: %empty
#line 1556 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 424: // subnet_4o6_subnet: "4o6-subnet" $@61 ":" "constant string"
#line 1559 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 425: // $@62: %empty
#line 1565 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 426: // interface: "interface" $@62 ":" "constant string"
#line 1568 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2731 "dhcp4_parser.cc"
    break;

  case 427: // $@63: %empty
#line 1574 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp4_parser.cc"
    break;

  case 428: // client_class: "client-class" $@63 ":" "constant string"
#line 1577 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2750 "dhcp4_parser.cc"
    break;

  case 429: // $@64: %empty
#line 1583 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 430: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1589 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 431: // reservations_global: "reservations-global" ":" "boolean"
#line 1594 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 432: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1600 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2791 "dhcp4_parser.cc"
    break;

  case 433: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1606 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2801 "dhcp4_parser.cc"
    break;

  case 434: // $@65: %empty
#line 1612 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2810 "dhcp4_parser.cc"
    break;

  case 435: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1615 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2819 "dhcp4_parser.cc"
    break;

  case 436: // hr_mode: "disabled"
#line 1620 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2825 "dhcp4_parser.cc"
    break;

  case 437: // hr_mode: "out-of-pool"
#line 1621 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2831 "dhcp4_parser.cc"
    break;

  case 438: // hr_mode: "global"
#line 1622 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2837 "dhcp4_parser.cc"
    break;

  case 439: // hr_mode: "all"
#line 1623 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2843 "dhcp4_parser.cc"
    break;

  case 440: // id: "id" ":" "integer"
#line 1626 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2853 "dhcp4_parser.cc"
    break;

  case 441: // $@66: %empty
#line 1634 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2865 "dhcp4_parser.cc"
    break;

  case 442: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1640 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2874 "dhcp4_parser.cc"
    break;

  case 447: // shared_networks_list: shared_networks_list ","
#line 1653 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2882 "dhcp4_parser.cc"
    break;

  case 448: // $@67: %empty
#line 1658 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2892 "dhcp4_parser.cc"
    break;

  case 449: // shared_network: "{" $@67 shared_network_params "}"
#line 1662 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 452: // shared_network_params: shared_network_params ","
#line 1668 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2908 "dhcp4_parser.cc"
    break;

  case 493: // $@68: %empty
#line 1719 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2920 "dhcp4_parser.cc"
    break;

  case 494: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1725 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2929 "dhcp4_parser.cc"
    break;

  case 495: // $@69: %empty
#line 1733 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2938 "dhcp4_parser.cc"
    break;

  case 496: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1736 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2946 "dhcp4_parser.cc"
    break;

  case 501: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1748 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2954 "dhcp4_parser.cc"
    break;

  case 502: // $@70: %empty
#line 1755 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2964 "dhcp4_parser.cc"
    break;

  case 503: // option_def_entry: "{" $@70 option_def_params "}"
#line 1759 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 504: // $@71: %empty
#line 1770 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2986 "dhcp4_parser.cc"
    break;

  case 505: // sub_option_def: "{" $@71 option_def_params "}"
#line 1774 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2998 "dhcp4_parser.cc"
    break;

  case 510: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1790 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3006 "dhcp4_parser.cc"
    break;

  case 522: // code: "code" ":" "integer"
#line 1809 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3016 "dhcp4_parser.cc"
    break;

  case 524: // $@72: %empty
#line 1817 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3025 "dhcp4_parser.cc"
    break;

  case 525: // option_def_type: "type" $@72 ":" "constant string"
#line 1820 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3035 "dhcp4_parser.cc"
    break;

  case 526: // $@73: %empty
#line 1826 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3044 "dhcp4_parser.cc"
    break;

  case 527: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1829 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3054 "dhcp4_parser.cc"
    break;

  case 528: // $@74: %empty
#line 1835 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 529: // space: "space" $@74 ":" "constant string"
#line 1838 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3073 "dhcp4_parser.cc"
    break;

  case 531: // $@75: %empty
#line 1846 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3082 "dhcp4_parser.cc"
    break;

  case 532: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1849 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3092 "dhcp4_parser.cc"
    break;

  case 533: // option_def_array: "array" ":" "boolean"
#line 1855 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3102 "dhcp4_parser.cc"
    break;

  case 534: // $@76: %empty
#line 1865 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3114 "dhcp4_parser.cc"
    break;

  case 535: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1871 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3123 "dhcp4_parser.cc"
    break;

  case 540: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1886 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3131 "dhcp4_parser.cc"
    break;

  case 541: // $@77: %empty
#line 1893 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3141 "dhcp4_parser.cc"
    break;

  case 542: // option_data_entry: "{" $@77 option_data_params "}"
#line 1897 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3150 "dhcp4_parser.cc"
    break;

  case 543: // $@78: %empty
#line 1905 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3160 "dhcp4_parser.cc"
    break;

  case 544: // sub_option_data: "{" $@78 option_data_params "}"
#line 1909 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3169 "dhcp4_parser.cc"
    break;

  case 549: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1925 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3177 "dhcp4_parser.cc"
    break;

  case 560: // $@79: %empty
#line 1945 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 561: // option_data_data: "data" $@79 ":" "constant string"
#line 1948 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3196 "dhcp4_parser.cc"
    break;

  case 564: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1958 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 565: // option_data_always_send: "always-send" ":" "boolean"
#line 1964 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 566: // $@80: %empty
#line 1973 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3228 "dhcp4_parser.cc"
    break;

  case 567: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1979 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3237 "dhcp4_parser.cc"
    break;

  case 572: // not_empty_pools_list: not_empty_pools_list ","
#line 1992 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3245 "dhcp4_parser.cc"
    break;

  case 573: // $@81: %empty
#line 1997 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3255 "dhcp4_parser.cc"
    break;

  case 574: // pool_list_entry: "{" $@81 pool_params "}"
#line 2001 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3265 "dhcp4_parser.cc"
    break;

  case 575: // $@82: %empty
#line 2007 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3275 "dhcp4_parser.cc"
    break;

  case 576: // sub_pool4: "{" $@82 pool_params "}"
#line 2011 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3285 "dhcp4_parser.cc"
    break;

  case 579: // pool_params: pool_params ","
#line 2019 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3293 "dhcp4_parser.cc"
    break;

  case 587: // $@83: %empty
#line 2033 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3302 "dhcp4_parser.cc"
    break;

  case 588: // pool_entry: "pool" $@83 ":" "constant string"
#line 2036 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 589: // $@84: %empty
#line 2042 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3320 "dhcp4_parser.cc"
    break;

  case 590: // user_context: "user-context" $@84 ":" map_value
#line 2044 "dhcp4_parser.yy"
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
#line 3347 "dhcp4_parser.cc"
    break;

  case 591: // $@85: %empty
#line 2067 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3355 "dhcp4_parser.cc"
    break;

  case 592: // comment: "comment" $@85 ":" "constant string"
#line 2069 "dhcp4_parser.yy"
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
#line 3384 "dhcp4_parser.cc"
    break;

  case 593: // $@86: %empty
#line 2097 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3396 "dhcp4_parser.cc"
    break;

  case 594: // reservations: "reservations" $@86 ":" "[" reservations_list "]"
#line 2103 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3405 "dhcp4_parser.cc"
    break;

  case 599: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2114 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3413 "dhcp4_parser.cc"
    break;

  case 600: // $@87: %empty
#line 2119 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3423 "dhcp4_parser.cc"
    break;

  case 601: // reservation: "{" $@87 reservation_params "}"
#line 2123 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3432 "dhcp4_parser.cc"
    break;

  case 602: // $@88: %empty
#line 2128 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3442 "dhcp4_parser.cc"
    break;

  case 603: // sub_reservation: "{" $@88 reservation_params "}"
#line 2132 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3451 "dhcp4_parser.cc"
    break;

  case 608: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2143 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3459 "dhcp4_parser.cc"
    break;

  case 624: // $@89: %empty
#line 2166 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3468 "dhcp4_parser.cc"
    break;

  case 625: // next_server: "next-server" $@89 ":" "constant string"
#line 2169 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3478 "dhcp4_parser.cc"
    break;

  case 626: // $@90: %empty
#line 2175 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3487 "dhcp4_parser.cc"
    break;

  case 627: // server_hostname: "server-hostname" $@90 ":" "constant string"
#line 2178 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3497 "dhcp4_parser.cc"
    break;

  case 628: // $@91: %empty
#line 2184 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3506 "dhcp4_parser.cc"
    break;

  case 629: // boot_file_name: "boot-file-name" $@91 ":" "constant string"
#line 2187 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3516 "dhcp4_parser.cc"
    break;

  case 630: // $@92: %empty
#line 2193 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 631: // ip_address: "ip-address" $@92 ":" "constant string"
#line 2196 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 632: // $@93: %empty
#line 2202 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3547 "dhcp4_parser.cc"
    break;

  case 633: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2208 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3556 "dhcp4_parser.cc"
    break;

  case 634: // $@94: %empty
#line 2213 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 635: // duid: "duid" $@94 ":" "constant string"
#line 2216 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3575 "dhcp4_parser.cc"
    break;

  case 636: // $@95: %empty
#line 2222 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3584 "dhcp4_parser.cc"
    break;

  case 637: // hw_address: "hw-address" $@95 ":" "constant string"
#line 2225 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3594 "dhcp4_parser.cc"
    break;

  case 638: // $@96: %empty
#line 2231 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3603 "dhcp4_parser.cc"
    break;

  case 639: // client_id_value: "client-id" $@96 ":" "constant string"
#line 2234 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3613 "dhcp4_parser.cc"
    break;

  case 640: // $@97: %empty
#line 2240 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 641: // circuit_id_value: "circuit-id" $@97 ":" "constant string"
#line 2243 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3632 "dhcp4_parser.cc"
    break;

  case 642: // $@98: %empty
#line 2249 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 643: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2252 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3651 "dhcp4_parser.cc"
    break;

  case 644: // $@99: %empty
#line 2258 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3660 "dhcp4_parser.cc"
    break;

  case 645: // hostname: "hostname" $@99 ":" "constant string"
#line 2261 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3670 "dhcp4_parser.cc"
    break;

  case 646: // $@100: %empty
#line 2267 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3682 "dhcp4_parser.cc"
    break;

  case 647: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2273 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3691 "dhcp4_parser.cc"
    break;

  case 648: // $@101: %empty
#line 2281 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3703 "dhcp4_parser.cc"
    break;

  case 649: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2287 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 652: // $@102: %empty
#line 2299 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3724 "dhcp4_parser.cc"
    break;

  case 653: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2305 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 656: // client_classes_list: client_classes_list ","
#line 2312 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3741 "dhcp4_parser.cc"
    break;

  case 657: // $@103: %empty
#line 2317 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 658: // client_class_entry: "{" $@103 client_class_params "}"
#line 2321 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3761 "dhcp4_parser.cc"
    break;

  case 663: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2333 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3769 "dhcp4_parser.cc"
    break;

  case 679: // $@104: %empty
#line 2356 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3778 "dhcp4_parser.cc"
    break;

  case 680: // client_class_test: "test" $@104 ":" "constant string"
#line 2359 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3788 "dhcp4_parser.cc"
    break;

  case 681: // only_if_required: "only-if-required" ":" "boolean"
#line 2365 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3798 "dhcp4_parser.cc"
    break;

  case 682: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2373 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 683: // $@105: %empty
#line 2381 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3820 "dhcp4_parser.cc"
    break;

  case 684: // control_socket: "control-socket" $@105 ":" "{" control_socket_params "}"
#line 2387 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3829 "dhcp4_parser.cc"
    break;

  case 687: // control_socket_params: control_socket_params ","
#line 2394 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3837 "dhcp4_parser.cc"
    break;

  case 693: // $@106: %empty
#line 2406 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3846 "dhcp4_parser.cc"
    break;

  case 694: // control_socket_type: "socket-type" $@106 ":" "constant string"
#line 2409 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3856 "dhcp4_parser.cc"
    break;

  case 695: // $@107: %empty
#line 2415 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3865 "dhcp4_parser.cc"
    break;

  case 696: // control_socket_name: "socket-name" $@107 ":" "constant string"
#line 2418 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3875 "dhcp4_parser.cc"
    break;

  case 697: // $@108: %empty
#line 2427 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3887 "dhcp4_parser.cc"
    break;

  case 698: // dhcp_queue_control: "dhcp-queue-control" $@108 ":" "{" queue_control_params "}"
#line 2433 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3898 "dhcp4_parser.cc"
    break;

  case 701: // queue_control_params: queue_control_params ","
#line 2442 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3906 "dhcp4_parser.cc"
    break;

  case 708: // enable_queue: "enable-queue" ":" "boolean"
#line 2455 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3916 "dhcp4_parser.cc"
    break;

  case 709: // $@109: %empty
#line 2461 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3925 "dhcp4_parser.cc"
    break;

  case 710: // queue_type: "queue-type" $@109 ":" "constant string"
#line 2464 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3935 "dhcp4_parser.cc"
    break;

  case 711: // capacity: "capacity" ":" "integer"
#line 2470 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3945 "dhcp4_parser.cc"
    break;

  case 712: // $@110: %empty
#line 2476 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3954 "dhcp4_parser.cc"
    break;

  case 713: // arbitrary_map_entry: "constant string" $@110 ":" value
#line 2479 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3963 "dhcp4_parser.cc"
    break;

  case 714: // $@111: %empty
#line 2486 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3975 "dhcp4_parser.cc"
    break;

  case 715: // dhcp_ddns: "dhcp-ddns" $@111 ":" "{" dhcp_ddns_params "}"
#line 2492 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3986 "dhcp4_parser.cc"
    break;

  case 716: // $@112: %empty
#line 2499 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3996 "dhcp4_parser.cc"
    break;

  case 717: // sub_dhcp_ddns: "{" $@112 dhcp_ddns_params "}"
#line 2503 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4006 "dhcp4_parser.cc"
    break;

  case 720: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2511 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4014 "dhcp4_parser.cc"
    break;

  case 739: // enable_updates: "enable-updates" ":" "boolean"
#line 2536 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4024 "dhcp4_parser.cc"
    break;

  case 740: // $@113: %empty
#line 2542 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4033 "dhcp4_parser.cc"
    break;

  case 741: // server_ip: "server-ip" $@113 ":" "constant string"
#line 2545 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4043 "dhcp4_parser.cc"
    break;

  case 742: // server_port: "server-port" ":" "integer"
#line 2551 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4053 "dhcp4_parser.cc"
    break;

  case 743: // $@114: %empty
#line 2557 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4062 "dhcp4_parser.cc"
    break;

  case 744: // sender_ip: "sender-ip" $@114 ":" "constant string"
#line 2560 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4072 "dhcp4_parser.cc"
    break;

  case 745: // sender_port: "sender-port" ":" "integer"
#line 2566 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4082 "dhcp4_parser.cc"
    break;

  case 746: // max_queue_size: "max-queue-size" ":" "integer"
#line 2572 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4092 "dhcp4_parser.cc"
    break;

  case 747: // $@115: %empty
#line 2578 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4101 "dhcp4_parser.cc"
    break;

  case 748: // ncr_protocol: "ncr-protocol" $@115 ":" ncr_protocol_value
#line 2581 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4110 "dhcp4_parser.cc"
    break;

  case 749: // ncr_protocol_value: "udp"
#line 2587 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4116 "dhcp4_parser.cc"
    break;

  case 750: // ncr_protocol_value: "tcp"
#line 2588 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4122 "dhcp4_parser.cc"
    break;

  case 751: // $@116: %empty
#line 2591 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4131 "dhcp4_parser.cc"
    break;

  case 752: // ncr_format: "ncr-format" $@116 ":" "JSON"
#line 2594 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4141 "dhcp4_parser.cc"
    break;

  case 753: // $@117: %empty
#line 2601 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4150 "dhcp4_parser.cc"
    break;

  case 754: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2604 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4160 "dhcp4_parser.cc"
    break;

  case 755: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2611 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4170 "dhcp4_parser.cc"
    break;

  case 756: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2618 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4180 "dhcp4_parser.cc"
    break;

  case 757: // $@118: %empty
#line 2625 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4189 "dhcp4_parser.cc"
    break;

  case 758: // dep_replace_client_name: "replace-client-name" $@118 ":" ddns_replace_client_name_value
#line 2628 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4198 "dhcp4_parser.cc"
    break;

  case 759: // $@119: %empty
#line 2634 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4207 "dhcp4_parser.cc"
    break;

  case 760: // dep_generated_prefix: "generated-prefix" $@119 ":" "constant string"
#line 2637 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4217 "dhcp4_parser.cc"
    break;

  case 761: // $@120: %empty
#line 2644 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4226 "dhcp4_parser.cc"
    break;

  case 762: // dep_hostname_char_set: "hostname-char-set" $@120 ":" "constant string"
#line 2647 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4236 "dhcp4_parser.cc"
    break;

  case 763: // $@121: %empty
#line 2654 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4245 "dhcp4_parser.cc"
    break;

  case 764: // dep_hostname_char_replacement: "hostname-char-replacement" $@121 ":" "constant string"
#line 2657 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4255 "dhcp4_parser.cc"
    break;

  case 765: // $@122: %empty
#line 2666 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4267 "dhcp4_parser.cc"
    break;

  case 766: // config_control: "config-control" $@122 ":" "{" config_control_params "}"
#line 2672 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4277 "dhcp4_parser.cc"
    break;

  case 767: // $@123: %empty
#line 2678 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4287 "dhcp4_parser.cc"
    break;

  case 768: // sub_config_control: "{" $@123 config_control_params "}"
#line 2682 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4296 "dhcp4_parser.cc"
    break;

  case 771: // config_control_params: config_control_params ","
#line 2690 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4304 "dhcp4_parser.cc"
    break;

  case 774: // $@124: %empty
#line 2700 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4316 "dhcp4_parser.cc"
    break;

  case 775: // config_databases: "config-databases" $@124 ":" "[" database_list "]"
#line 2706 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4325 "dhcp4_parser.cc"
    break;

  case 776: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2711 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4335 "dhcp4_parser.cc"
    break;

  case 777: // $@125: %empty
#line 2719 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4347 "dhcp4_parser.cc"
    break;

  case 778: // loggers: "loggers" $@125 ":" "[" loggers_entries "]"
#line 2725 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4356 "dhcp4_parser.cc"
    break;

  case 781: // loggers_entries: loggers_entries ","
#line 2734 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4364 "dhcp4_parser.cc"
    break;

  case 782: // $@126: %empty
#line 2740 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4374 "dhcp4_parser.cc"
    break;

  case 783: // logger_entry: "{" $@126 logger_params "}"
#line 2744 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4382 "dhcp4_parser.cc"
    break;

  case 786: // logger_params: logger_params ","
#line 2750 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4390 "dhcp4_parser.cc"
    break;

  case 794: // debuglevel: "debuglevel" ":" "integer"
#line 2764 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4400 "dhcp4_parser.cc"
    break;

  case 795: // $@127: %empty
#line 2770 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4409 "dhcp4_parser.cc"
    break;

  case 796: // severity: "severity" $@127 ":" "constant string"
#line 2773 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4419 "dhcp4_parser.cc"
    break;

  case 797: // $@128: %empty
#line 2779 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4431 "dhcp4_parser.cc"
    break;

  case 798: // output_options_list: "output_options" $@128 ":" "[" output_options_list_content "]"
#line 2785 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4440 "dhcp4_parser.cc"
    break;

  case 801: // output_options_list_content: output_options_list_content ","
#line 2792 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4448 "dhcp4_parser.cc"
    break;

  case 802: // $@129: %empty
#line 2797 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4458 "dhcp4_parser.cc"
    break;

  case 803: // output_entry: "{" $@129 output_params_list "}"
#line 2801 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4466 "dhcp4_parser.cc"
    break;

  case 806: // output_params_list: output_params_list ","
#line 2807 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4474 "dhcp4_parser.cc"
    break;

  case 812: // $@130: %empty
#line 2819 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4483 "dhcp4_parser.cc"
    break;

  case 813: // output: "output" $@130 ":" "constant string"
#line 2822 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4493 "dhcp4_parser.cc"
    break;

  case 814: // flush: "flush" ":" "boolean"
#line 2828 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4503 "dhcp4_parser.cc"
    break;

  case 815: // maxsize: "maxsize" ":" "integer"
#line 2834 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4513 "dhcp4_parser.cc"
    break;

  case 816: // maxver: "maxver" ":" "integer"
#line 2840 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4523 "dhcp4_parser.cc"
    break;

  case 817: // $@131: %empty
#line 2846 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4532 "dhcp4_parser.cc"
    break;

  case 818: // pattern: "pattern" $@131 ":" "constant string"
#line 2849 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4542 "dhcp4_parser.cc"
    break;

  case 819: // $@132: %empty
#line 2855 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4554 "dhcp4_parser.cc"
    break;

  case 820: // compatibility: "compatibility" $@132 ":" "{" compatibility_params "}"
#line 2861 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4563 "dhcp4_parser.cc"
    break;

  case 823: // compatibility_params: compatibility_params ","
#line 2868 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4571 "dhcp4_parser.cc"
    break;

  case 826: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2877 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4581 "dhcp4_parser.cc"
    break;


#line 4585 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -980;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     152,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,    71,    38,    26,    75,    82,   110,
     114,   146,   148,   185,   187,   198,   204,   231,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,    38,  -155,   115,   184,   126,   632,
     -53,    74,   186,    76,    -9,   -87,   433,    98,  -980,   129,
     144,   276,   279,   288,  -980,    34,  -980,  -980,  -980,  -980,
     289,   322,   334,  -980,  -980,  -980,  -980,  -980,  -980,   369,
     375,   381,   384,   386,   387,   388,   389,   390,   391,   392,
    -980,   393,   397,   412,   413,   414,  -980,  -980,  -980,   421,
     422,   423,  -980,  -980,  -980,   424,  -980,  -980,  -980,  -980,
     425,   426,   427,  -980,  -980,  -980,  -980,  -980,   428,  -980,
    -980,  -980,  -980,  -980,  -980,   430,   431,   432,  -980,  -980,
     434,  -980,    36,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
     435,   436,   437,   438,  -980,    72,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,   439,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
      73,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   100,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,   429,   441,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   443,
    -980,  -980,   442,  -980,  -980,  -980,   448,  -980,  -980,   446,
     444,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   451,   452,  -980,  -980,  -980,  -980,
     450,   457,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   120,  -980,  -980,  -980,   458,  -980,
    -980,   459,  -980,   461,   462,  -980,  -980,   463,   464,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,   121,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   466,   128,  -980,  -980,  -980,  -980,
      38,    38,  -980,   271,   475,  -980,  -980,   477,   478,   480,
     280,   285,   287,   482,   483,   492,   494,   497,   498,   299,
     300,   303,   306,   307,   309,   312,   313,   314,   308,   318,
     519,   320,   321,   323,   324,   328,   521,   526,   536,   335,
     336,   338,   538,   545,   546,   345,   550,   552,   556,   557,
     356,   359,   360,   567,   568,   570,   574,   575,   376,   579,
     580,   582,   583,   584,   585,   395,   396,   398,   601,   603,
    -980,   184,  -980,   604,   607,   608,   405,   406,   409,   410,
     126,  -980,   613,   614,   615,   616,   617,   618,   417,   620,
     621,   622,   632,  -980,   623,   -53,  -980,   624,   625,   626,
     627,   628,   630,   633,   635,  -980,    74,  -980,   636,   637,
     440,   638,   639,   640,   445,  -980,    76,   643,   447,   449,
    -980,    -9,   644,   645,    24,  -980,   460,   646,   648,   453,
     650,   454,   465,   652,   654,   467,   469,   662,   663,   669,
     670,   433,  -980,   674,   473,    98,  -980,  -980,  -980,   676,
     629,   675,   677,   682,  -980,  -980,  -980,   476,   485,   486,
     685,   686,   678,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   500,  -980,  -980,  -980,  -980,  -980,
     -11,   501,   502,  -980,  -980,  -980,   703,   713,   717,  -980,
     719,   718,   522,   193,  -980,  -980,  -980,   721,   727,   728,
     729,   736,  -980,   737,   738,   739,   743,   531,   548,  -980,
    -980,  -980,   746,   747,  -980,   752,   211,   220,  -980,  -980,
    -980,  -980,  -980,   553,   554,   555,   756,   564,   565,  -980,
     752,   566,   755,  -980,   569,  -980,   752,   571,   572,   573,
     576,   577,   578,   581,  -980,   586,   587,  -980,   588,   589,
     590,  -980,  -980,   591,  -980,  -980,  -980,   592,   718,  -980,
    -980,   605,   606,  -980,   619,  -980,  -980,    13,   602,  -980,
    -980,   -11,   631,   634,   641,  -980,   767,  -980,  -980,    38,
     184,    98,   126,   748,  -980,  -980,  -980,   361,   361,   772,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   773,
     777,   778,   780,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,   250,   781,   782,   783,   174,   -47,    83,   118,   433,
    -980,  -980,   815,  -136,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,   816,  -980,  -980,  -980,  -980,
     239,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   772,
    -980,   136,   164,   170,  -980,   182,  -980,  -980,  -980,  -980,
    -980,  -980,   821,   824,   825,   826,   827,   828,   829,   830,
     831,   834,  -980,   838,  -980,  -980,  -980,  -980,  -980,   183,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,   218,  -980,   841,   845,  -980,  -980,   843,   850,
    -980,  -980,   848,   853,  -980,  -980,   851,   856,  -980,  -980,
     854,   858,  -980,  -980,  -980,  -980,  -980,  -980,    87,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,   140,  -980,  -980,   857,
     859,  -980,  -980,   861,   862,  -980,   840,   860,   864,   865,
     866,   867,   219,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
     868,   869,   870,  -980,   227,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,   234,  -980,  -980,  -980,
     871,  -980,   872,  -980,  -980,  -980,   274,  -980,  -980,  -980,
    -980,  -980,   275,  -980,   163,  -980,   873,  -980,   316,  -980,
    -980,   673,  -980,   874,   876,  -980,  -980,  -980,  -980,   875,
     878,  -980,  -980,  -980,   877,   748,  -980,   881,   882,   883,
     884,   683,   684,   687,   688,   689,   691,   692,   693,   694,
     695,   886,   696,   887,   890,   899,   900,   361,  -980,  -980,
     361,  -980,   772,   632,  -980,   773,    76,  -980,   777,    -9,
    -980,   778,   735,  -980,   780,   250,  -980,   278,   781,  -980,
      74,  -980,   782,   -87,  -980,   783,   699,   700,   701,   702,
     704,   707,   174,  -980,   706,   709,   711,   -47,  -980,   905,
     914,    83,  -980,   712,   917,   723,   919,   118,  -980,  -980,
     -28,   815,  -980,   716,  -136,  -980,  -980,   925,   879,   -53,
    -980,   816,   930,  -980,  -980,   734,  -980,   169,   750,   753,
     768,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,   302,  -980,   785,   786,   789,   793,  -980,   317,  -980,
     319,  -980,   953,  -980,   975,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   327,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,   995,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  1002,  1008,  -980,  -980,  -980,  -980,
    -980,  1016,  -980,   329,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,   849,   863,  -980,  -980,
     880,  -980,    38,  -980,  -980,  1054,  -980,  -980,  -980,  -980,
    -980,   331,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
     885,   378,  -980,   752,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   735,  -980,  1055,   855,  -980,   278,
    -980,  -980,  -980,  -980,  -980,  -980,  1060,   888,  1061,   -28,
    -980,  -980,  -980,  -980,  -980,   891,  -980,  -980,  1062,  -980,
     892,  -980,  -980,  1059,  -980,  -980,   181,  -980,   109,  1059,
    -980,  -980,  1065,  1066,  1067,  -980,   379,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  1068,   893,   889,   894,  1069,   109,
    -980,   897,  -980,  -980,  -980,   898,  -980,  -980,  -980
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   192,     9,   367,    11,   575,    13,
     602,    15,   495,    17,   504,    19,   543,    21,   329,    23,
     716,    25,   767,    27,    46,    39,     0,     0,     0,     0,
       0,   604,     0,   506,   545,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   765,   177,   210,
       0,     0,     0,   624,   626,   628,   208,   218,   220,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,     0,     0,     0,     0,   154,   161,   163,     0,
       0,     0,   358,   493,   534,     0,   441,   589,   591,   434,
       0,     0,     0,   291,   652,   593,   320,   341,     0,   306,
     683,   697,   714,   167,   169,     0,     0,     0,   777,   819,
       0,   133,     0,    67,    70,    71,    72,    73,    74,   108,
     109,   110,   111,   112,    75,   103,   132,    92,    93,    94,
     116,   117,   118,   119,   120,   121,   122,   123,   114,   115,
     124,   125,   126,   128,   129,   130,    78,    79,   100,    80,
      81,    82,   127,    86,    87,    76,   105,   106,   107,   104,
      77,    84,    85,    98,    99,   101,    95,    96,    97,    83,
      88,    89,    90,    91,   102,   113,   131,   194,   196,   200,
       0,     0,     0,     0,   191,     0,   179,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   419,   421,   423,   566,
     417,   425,     0,   429,   427,   648,   416,   372,   373,   374,
     375,   376,   400,   401,   402,   403,   404,   390,   391,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
       0,   369,   379,   395,   396,   397,   380,   382,   383,   386,
     387,   388,   385,   381,   377,   378,   398,   399,   384,   392,
     393,   394,   389,   587,   586,   582,   583,   581,     0,   577,
     580,   584,   585,   646,   634,   636,   640,   638,   644,   642,
     630,   623,   617,   621,   622,     0,   605,   606,   618,   619,
     620,   614,   609,   615,   611,   612,   613,   616,   610,     0,
     524,   266,     0,   528,   526,   531,     0,   520,   521,     0,
     507,   508,   511,   523,   512,   513,   514,   530,   515,   516,
     517,   518,   519,   560,     0,     0,   558,   559,   562,   563,
       0,   546,   547,   550,   551,   552,   553,   554,   555,   556,
     557,   337,   339,   334,     0,   331,   335,   336,     0,   753,
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
       0,     0,   371,   368,     0,   579,   576,     0,     0,     0,
       0,     0,     0,     0,     0,   603,   608,   496,     0,     0,
       0,     0,     0,     0,     0,   505,   510,     0,     0,     0,
     544,   549,     0,     0,   333,   330,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   720,   717,     0,     0,   771,   768,    49,    41,     0,
       0,     0,     0,     0,   148,   149,   150,     0,     0,     0,
       0,     0,     0,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,   172,   173,   151,   152,   153,
       0,     0,     0,   165,   166,   171,     0,     0,     0,   147,
       0,     0,     0,     0,   431,   432,   433,     0,     0,     0,
       0,     0,   682,     0,     0,     0,     0,     0,     0,   174,
     175,   176,     0,     0,    68,     0,     0,     0,   204,   205,
     206,   207,   180,     0,     0,     0,     0,     0,     0,   440,
       0,     0,     0,   370,     0,   578,     0,     0,     0,     0,
       0,     0,     0,     0,   607,     0,     0,   522,     0,     0,
       0,   533,   509,     0,   564,   565,   548,     0,     0,   332,
     739,     0,     0,   742,     0,   745,   746,     0,     0,   755,
     756,     0,     0,     0,     0,   719,     0,   776,   770,     0,
       0,     0,     0,     0,   625,   627,   629,     0,     0,   222,
     146,   156,   157,   158,   159,   160,   155,   162,   164,   360,
     497,   536,   443,    38,   590,   592,   436,   437,   438,   439,
     435,     0,     0,   595,   322,     0,     0,     0,     0,     0,
     168,   170,     0,     0,    51,   195,   198,   199,   197,   202,
     203,   201,   420,   422,   424,   568,   418,   426,   430,   428,
       0,   588,   647,   635,   637,   641,   639,   645,   643,   631,
     525,   267,   529,   527,   532,   561,   338,   340,   754,   741,
     744,   749,   750,   748,   752,   758,   760,   762,   764,   222,
      42,     0,     0,     0,   216,     0,   212,   215,   254,   259,
     261,   263,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   277,     0,   283,   285,   287,   289,   253,     0,
     229,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,     0,   227,     0,   223,   224,   365,     0,   361,
     362,   502,     0,   498,   499,   541,     0,   537,   538,   448,
       0,   444,   445,   301,   302,   303,   304,   305,     0,   293,
     296,   297,   298,   299,   300,   657,     0,   654,   600,     0,
     596,   597,   327,     0,   323,   324,     0,     0,     0,     0,
       0,     0,     0,   343,   346,   347,   348,   349,   350,   351,
       0,     0,     0,   316,     0,   308,   311,   312,   313,   314,
     315,   693,   695,   692,   690,   691,     0,   685,   688,   689,
       0,   709,     0,   712,   705,   706,     0,   699,   702,   703,
     704,   707,     0,   782,     0,   779,     0,   825,     0,   821,
     824,    53,   573,     0,   569,   570,   632,   650,   651,     0,
       0,    62,   766,   178,     0,   214,   211,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   231,   209,   219,
       0,   221,   226,     0,   359,   364,   506,   494,   501,   545,
     535,   540,     0,   442,   447,   295,   292,   659,   656,   653,
     604,   594,   599,     0,   321,   326,     0,     0,     0,     0,
       0,     0,   345,   342,     0,     0,     0,   310,   307,     0,
       0,   687,   684,     0,     0,     0,     0,   701,   698,   715,
       0,   781,   778,     0,   823,   820,    55,     0,    54,     0,
     567,   572,     0,   649,   775,     0,   213,     0,     0,     0,
       0,   265,   268,   269,   270,   271,   272,   273,   274,   275,
     276,     0,   282,     0,     0,     0,     0,   230,     0,   225,
       0,   363,     0,   500,     0,   539,   492,   471,   472,   473,
     456,   457,   476,   477,   478,   479,   480,   459,   460,   481,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     453,   454,   455,   469,   470,   466,   467,   468,   465,     0,
     450,   458,   474,   475,   461,   462,   463,   464,   446,   294,
     679,     0,   674,   675,   676,   677,   678,   667,   668,   672,
     673,   669,   670,   671,     0,   660,   661,   664,   665,   666,
     655,     0,   598,     0,   325,   352,   353,   354,   355,   356,
     357,   344,   317,   318,   319,   309,     0,     0,   686,   708,
       0,   711,     0,   700,   797,     0,   795,   793,   787,   791,
     792,     0,   784,   789,   790,   788,   780,   826,   822,    52,
      57,     0,   571,     0,   217,   256,   257,   258,   255,   260,
     262,   264,   279,   280,   281,   278,   284,   286,   288,   290,
     228,   366,   503,   542,   452,   449,     0,     0,   658,   663,
     601,   328,   694,   696,   710,   713,     0,     0,     0,   786,
     783,    56,   574,   633,   451,     0,   681,   662,     0,   794,
       0,   785,   680,     0,   796,   802,     0,   799,     0,   801,
     798,   812,     0,     0,     0,   817,     0,   804,   807,   808,
     809,   810,   811,   800,     0,     0,     0,     0,     0,   806,
     803,     0,   814,   815,   816,     0,   805,   813,   818
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,   -54,  -980,  -583,  -980,   399,
    -980,  -980,  -980,  -980,  -980,  -980,  -635,  -980,  -980,  -980,
     -67,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   374,   593,
       4,    10,    23,   -40,   -23,   -12,    22,    25,    29,    33,
    -980,  -980,  -980,  -980,  -980,    35,    40,    43,    45,    46,
      47,  -980,   385,    50,  -980,    51,  -980,    53,    57,    58,
    -980,    61,  -980,    63,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,   373,   598,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,   123,  -980,  -980,  -980,  -980,  -980,  -980,   290,
    -980,    99,  -980,  -696,   103,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,   -33,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,    88,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
      89,  -980,  -980,  -980,  -980,  -980,  -980,  -980,    77,  -980,
    -980,  -980,    84,   542,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,    79,  -980,  -980,  -980,  -980,  -980,  -980,  -979,  -980,
    -980,  -980,   104,  -980,  -980,  -980,   105,   595,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -968,  -980,   -65,  -980,
      70,  -980,    64,    65,    68,    69,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,   111,  -980,  -980,  -112,   -46,  -980,  -980,
    -980,  -980,  -980,   116,  -980,  -980,  -980,   107,  -980,   563,
    -980,   -63,  -980,  -980,  -980,  -980,  -980,   -42,  -980,  -980,
    -980,  -980,  -980,   -35,  -980,  -980,  -980,   119,  -980,  -980,
    -980,   122,  -980,   594,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,    78,  -980,  -980,  -980,    81,
     597,  -980,  -980,   -51,  -980,    -8,  -980,   -39,  -980,  -980,
    -980,   112,  -980,  -980,  -980,   113,  -980,   596,   -55,  -980,
     -15,  -980,     3,  -980,   355,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -965,  -980,  -980,  -980,  -980,  -980,   125,  -980,
    -980,  -980,   -93,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,    96,  -980,  -980,  -980,  -980,  -980,  -980,  -980,    91,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
     382,   599,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,   455,   559,  -980,  -980,  -980,  -980,  -980,  -980,    94,
    -980,  -980,   -92,  -980,  -980,  -980,  -980,  -980,  -980,  -113,
    -980,  -980,  -131,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,    95,  -980
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   724,
      82,    83,    39,    64,    79,    80,   745,   941,  1037,  1038,
     818,    41,    66,    85,   424,    86,    43,    67,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   450,   166,   167,   168,   169,   170,   171,   172,
     173,   456,   716,   174,   457,   175,   458,   176,   177,   178,
     483,   179,   484,   180,   181,   182,   183,   184,   185,   186,
     428,   225,   226,    45,    68,   227,   493,   228,   494,   748,
     229,   495,   751,   230,   231,   232,   233,   187,   436,   188,
     429,   795,   796,   797,   954,   189,   437,   190,   438,   844,
     845,   846,   980,   819,   820,   821,   957,  1188,   822,   958,
     823,   959,   824,   960,   825,   826,   529,   827,   828,   829,
     830,   831,   832,   833,   834,   835,   836,   971,  1195,   837,
     838,   973,   839,   974,   840,   975,   841,   976,   191,   473,
     868,   869,   870,   871,   872,   873,   874,   192,   479,   904,
     905,   906,   907,   908,   193,   476,   883,   884,   885,  1003,
      59,    75,   374,   375,   376,   542,   377,   543,   194,   477,
     892,   893,   894,   895,   896,   897,   898,   899,   195,   462,
     848,   849,   850,   983,    47,    69,   270,   271,   272,   506,
     273,   502,   274,   503,   275,   504,   276,   507,   277,   510,
     278,   509,   196,   197,   198,   199,   469,   730,   283,   200,
     466,   860,   861,   862,   992,  1109,  1110,   201,   463,    53,
      72,   852,   853,   854,   986,    55,    73,   339,   340,   341,
     342,   343,   344,   345,   528,   346,   532,   347,   531,   348,
     349,   533,   350,   202,   464,   856,   857,   858,   989,    57,
      74,   360,   361,   362,   363,   364,   537,   365,   366,   367,
     368,   285,   505,   943,   944,   945,  1039,    49,    70,   298,
     299,   300,   514,   203,   467,   204,   468,   205,   475,   879,
     880,   881,  1000,    51,    71,   315,   316,   317,   206,   433,
     207,   434,   208,   435,   321,   524,   948,  1042,   322,   518,
     323,   519,   324,   521,   325,   520,   326,   523,   327,   522,
     328,   517,   292,   511,   949,   209,   474,   876,   877,   997,
    1134,  1135,  1136,  1137,  1138,  1206,  1139,   210,   211,   480,
     916,   917,   918,  1019,   919,  1020,   212,   481,   926,   927,
     928,   929,  1024,   930,   931,  1026,   213,   482,    61,    76,
     396,   397,   398,   399,   548,   400,   401,   550,   402,   403,
     404,   553,   783,   405,   554,   406,   547,   407,   408,   409,
     557,   410,   558,   411,   559,   412,   560,   214,   427,    63,
      77,   415,   416,   417,   563,   418,   215,   488,   934,   935,
    1030,  1171,  1172,  1173,  1174,  1218,  1175,  1216,  1236,  1237,
    1238,  1246,  1247,  1248,  1254,  1249,  1250,  1251,  1252,  1258,
     216,   489,   938,   939,   940
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     151,   224,   246,   294,   311,   295,   337,   356,   373,   393,
      78,   358,   842,  1101,   289,   758,   318,   234,   286,   301,
     313,   762,   351,   369,  1102,   394,   329,  1117,   723,   250,
     288,   781,   359,    40,   284,   297,   312,   425,   124,   491,
     338,   357,   426,    29,   492,    30,   251,    31,   371,   372,
      81,   293,   127,   128,   290,   936,   319,   252,   127,   128,
     235,   287,   302,   314,   331,   352,   370,   243,   395,   150,
     244,    28,   291,   247,   320,   500,   512,   127,   128,   248,
     501,   513,    42,   331,   353,   332,   333,   354,   355,    44,
     995,   253,   249,   996,   254,   723,   127,   128,   255,   900,
     901,   902,   256,   515,   257,    93,    94,    95,   516,   258,
     413,   414,   259,   330,   260,   261,   262,    46,   150,   263,
     264,    48,   265,   544,   561,    84,   266,   267,   545,   562,
     268,   565,   269,   279,   280,   419,   566,   281,   282,   491,
     296,   217,   218,   998,   951,   219,   999,   420,   220,   221,
     222,   223,   150,    50,  1164,    52,  1165,  1166,   150,   371,
     372,   711,   712,   713,   714,   124,  1031,   565,   331,  1032,
     332,   333,   952,   500,   334,   335,   336,   150,   953,   127,
     128,   127,   128,   782,  1239,   955,   977,  1240,   127,   128,
     956,   978,    54,   303,    56,    87,   150,   715,    88,   304,
     305,   306,   307,   308,   309,    58,   310,  1185,  1186,  1187,
      89,    60,    90,    91,    92,    93,    94,    95,    96,    97,
      98,   977,  1012,   127,   128,  1101,   979,  1013,   746,   747,
    1017,   127,   128,   911,   912,  1018,  1102,  1021,    62,  1117,
     749,   750,  1022,    32,    33,    34,    35,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   920,   921,   922,   123,   124,   123,  1027,   561,   150,
     421,   150,  1028,  1029,  1068,   125,   126,   422,   150,   127,
     128,   423,  1241,   430,   129,  1242,  1243,  1244,  1245,   130,
     131,   132,   133,   134,   726,   727,   728,   729,   135,    93,
      94,    95,   886,   887,   888,   889,   890,   891,   136,  1034,
     977,   137,   512,   923,  1035,  1200,   431,  1201,   138,   139,
    1204,   150,   544,   140,  1219,  1205,   141,  1211,   432,  1220,
     142,    99,   100,   101,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,  1192,  1193,  1194,
     143,   144,   145,   146,   147,   148,   567,   568,   123,   124,
     331,   310,   946,   439,   149,   863,   864,   865,   866,   440,
     867,   515,  1259,   127,   128,   441,  1222,  1260,   442,   150,
     443,   444,   445,   446,   447,   448,   449,   451,   798,  1120,
    1121,   452,   799,   800,   801,   802,   803,   804,   805,   806,
     807,   808,   809,   810,   811,   812,   453,   454,   455,   813,
     814,   815,   816,   817,   151,   459,   460,   461,   465,   470,
     471,   472,   478,   224,   485,   486,   487,   525,   490,   496,
     497,   498,   499,   508,   526,   246,   530,   536,   294,   234,
     295,   527,   534,   331,   535,   538,   539,   289,   540,   311,
     541,   286,   546,   549,   301,   551,   552,   555,   556,   337,
     564,   318,   250,   288,   356,   313,   569,   284,   358,   570,
     297,   571,   572,   150,   573,   351,   577,   578,   574,   251,
     369,   312,   235,   575,   393,   576,   579,   290,   580,   359,
     252,   581,   582,   338,   287,   583,   584,   302,   357,   585,
     394,   319,   586,   587,   592,   291,   247,   588,   314,   589,
     590,   591,   248,   594,   593,   600,   595,   596,   352,   320,
     601,   597,   598,   370,   253,   249,   599,   254,   127,   128,
     602,   255,   606,   603,   604,   256,   605,   257,  1223,   607,
     608,   609,   258,   395,   610,   259,   611,   260,   261,   262,
     612,   613,   263,   264,   614,   265,   150,   615,   616,   266,
     267,   617,   618,   268,   619,   269,   279,   280,   620,   621,
     281,   282,   622,   623,   624,   296,   625,   626,   627,   628,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   390,   629,   630,   632,   631,   633,   635,   391,
     392,   636,   637,   638,   639,   640,   641,   643,   644,   645,
     646,   647,   648,   649,   650,   651,   652,   654,   656,   657,
     658,   659,   660,   151,   661,   224,   700,   662,   150,   663,
     665,   666,   668,   669,   670,   790,   667,   673,   677,   678,
     681,   234,   682,   671,   684,   674,   687,   675,   688,   683,
     685,    91,    92,    93,    94,    95,   691,   692,   680,   903,
     913,   686,   393,   693,   694,   689,   937,   690,   696,   697,
     699,   704,   701,   709,   702,   909,   914,   924,   394,   703,
     705,   706,   707,   708,   235,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   710,   717,   718,   719,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   720,   236,
     237,   238,   721,   124,   722,    30,   731,   725,   910,   915,
     925,   395,   732,   733,   734,   239,   740,   127,   128,   240,
     241,   242,   129,   735,   736,   737,   738,   130,   131,   132,
     739,   742,   243,   741,   743,   244,   135,   744,   752,   753,
     754,   755,   760,   245,    91,    92,    93,    94,    95,   756,
     757,   759,   789,   784,   761,   794,   763,   764,   765,   843,
     847,   766,   767,   768,   851,   855,   769,   859,   875,   878,
     882,   770,   771,   772,   773,   774,   775,   776,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   143,   144,
     778,   779,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   933,   942,   780,   961,   124,   331,   962,   963,
     964,   965,   966,   967,   968,   969,   786,   150,   970,   787,
     127,   128,   972,   241,  1006,   129,   788,   981,   982,   984,
     130,   131,   132,   985,   987,   243,   988,   990,   244,   991,
     993,   994,  1002,  1001,  1007,  1005,   245,  1004,  1008,  1009,
    1010,  1011,  1014,  1015,  1016,  1023,  1025,  1033,  1036,  1041,
    1040,  1045,  1180,  1043,  1044,  1047,  1048,  1049,  1050,  1051,
    1061,  1063,  1052,  1053,  1064,  1055,  1054,  1056,  1057,  1058,
    1059,  1060,  1062,  1065,  1066,  1145,  1146,  1147,  1148,  1156,
    1149,   143,   144,  1150,  1152,  1153,   246,  1154,  1157,   337,
    1159,  1160,   356,  1162,  1177,  1076,   358,  1103,   289,  1161,
    1122,  1179,   286,   311,  1183,   351,   373,  1114,   369,  1184,
     150,  1112,  1131,   250,   288,   318,  1129,   359,   284,   313,
     903,  1127,  1080,   338,   913,  1189,   357,  1111,  1190,  1100,
     251,  1202,  1128,  1167,  1126,   312,   909,   937,   290,  1081,
     914,   252,   294,  1191,   295,   287,   924,  1115,   352,  1169,
    1082,   370,  1132,  1203,  1113,   319,   291,   247,   301,  1130,
    1196,  1197,   314,   248,  1198,  1116,  1077,  1168,  1199,  1207,
    1133,  1123,  1078,   320,   297,   253,   249,  1124,   254,   910,
    1208,  1209,   255,   915,  1083,  1079,   256,  1084,   257,   925,
    1125,  1085,  1170,   258,  1210,  1086,   259,  1087,   260,   261,
     262,   302,  1088,   263,   264,  1089,   265,  1090,  1091,  1092,
     266,   267,  1093,  1094,   268,  1095,   269,   279,   280,  1096,
    1097,   281,   282,  1098,  1212,  1099,  1105,  1106,  1217,  1225,
    1107,  1108,  1104,  1226,  1228,  1230,  1235,  1233,  1213,  1255,
    1256,  1257,  1261,  1265,   791,   793,   785,   777,  1046,   950,
    1067,  1069,  1144,  1119,   634,  1214,   679,  1143,  1070,  1071,
    1221,  1151,  1224,  1072,  1229,  1263,  1232,  1234,   642,   672,
    1264,  1262,  1267,  1268,  1073,  1118,  1155,   653,  1215,   296,
    1075,  1074,   655,  1141,  1142,   947,  1227,  1158,  1163,  1182,
    1181,   932,   664,  1140,   698,  1176,  1253,  1231,  1266,  1178,
       0,     0,     0,     0,     0,   676,     0,  1076,     0,  1103,
       0,     0,  1122,     0,     0,     0,     0,     0,     0,  1114,
       0,     0,  1167,  1112,  1131,     0,   792,     0,  1129,     0,
     695,     0,     0,  1127,  1080,     0,     0,     0,  1169,  1111,
       0,  1100,     0,     0,  1128,     0,  1126,     0,     0,     0,
       0,  1081,     0,     0,     0,     0,  1168,     0,     0,  1115,
       0,     0,  1082,     0,  1132,     0,  1113,     0,     0,     0,
       0,  1130,     0,     0,     0,     0,     0,  1116,  1077,     0,
       0,  1170,  1133,  1123,  1078,     0,     0,     0,     0,  1124,
       0,     0,     0,     0,     0,     0,  1083,  1079,     0,  1084,
       0,     0,  1125,  1085,     0,     0,     0,  1086,     0,  1087,
       0,     0,     0,     0,  1088,     0,     0,  1089,     0,  1090,
    1091,  1092,     0,     0,  1093,  1094,     0,  1095,     0,     0,
       0,  1096,  1097,     0,     0,  1098,     0,  1099,  1105,  1106,
       0,     0,  1107,  1108,  1104
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,    74,   708,   992,    69,   650,    71,    68,    69,    70,
      71,   656,    73,    74,   992,    76,    72,   992,   611,    69,
      69,    18,    74,     7,    69,    70,    71,     3,    91,     3,
      73,    74,     8,     5,     8,     7,    69,     9,   135,   136,
     205,   104,   105,   106,    69,   191,    71,    69,   105,   106,
      68,    69,    70,    71,    92,    73,    74,   120,    76,   205,
     123,     0,    69,    69,    71,     3,     3,   105,   106,    69,
       8,     8,     7,    92,    93,    94,    95,    96,    97,     7,
       3,    69,    69,     6,    69,   678,   105,   106,    69,   146,
     147,   148,    69,     3,    69,    31,    32,    33,     8,    69,
      12,    13,    69,    37,    69,    69,    69,     7,   205,    69,
      69,     7,    69,     3,     3,    10,    69,    69,     8,     8,
      69,     3,    69,    69,    69,     6,     8,    69,    69,     3,
      70,    15,    16,     3,     8,    19,     6,     3,    22,    23,
      24,    25,   205,     7,   182,     7,   184,   185,   205,   135,
     136,   172,   173,   174,   175,    91,     3,     3,    92,     6,
      94,    95,     8,     3,    98,    99,   100,   205,     8,   105,
     106,   105,   106,   170,     3,     3,     3,     6,   105,   106,
       8,     8,     7,   119,     7,    11,   205,   208,    14,   125,
     126,   127,   128,   129,   130,     7,   132,    38,    39,    40,
      26,     7,    28,    29,    30,    31,    32,    33,    34,    35,
      36,     3,     3,   105,   106,  1204,     8,     8,    17,    18,
       3,   105,   106,   150,   151,     8,  1204,     3,     7,  1204,
      20,    21,     8,   205,   206,   207,   208,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,   153,   154,   155,    90,    91,    90,     3,     3,   205,
       4,   205,     8,     8,   980,   101,   102,     8,   205,   105,
     106,     3,   183,     4,   110,   186,   187,   188,   189,   115,
     116,   117,   118,   119,   111,   112,   113,   114,   124,    31,
      32,    33,   138,   139,   140,   141,   142,   143,   134,     3,
       3,   137,     3,   205,     8,     8,     4,     8,   144,   145,
       3,   205,     3,   149,     3,     8,   152,     8,     4,     8,
     156,    63,    64,    65,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,    55,    56,    57,
     176,   177,   178,   179,   180,   181,   420,   421,    90,    91,
      92,   132,   133,     4,   190,   125,   126,   127,   128,     4,
     130,     3,     3,   105,   106,     4,     8,     8,     4,   205,
       4,     4,     4,     4,     4,     4,     4,     4,    37,   121,
     122,     4,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,     4,     4,     4,    58,
      59,    60,    61,    62,   491,     4,     4,     4,     4,     4,
       4,     4,     4,   500,     4,     4,     4,     8,     4,     4,
       4,     4,     4,     4,     3,   512,     4,     3,   515,   500,
     515,     8,     4,    92,     8,     4,     4,   512,     8,   526,
       3,   512,     4,     4,   515,     4,     4,     4,     4,   536,
       4,   526,   512,   512,   541,   526,   205,   512,   541,     4,
     515,     4,     4,   205,     4,   536,     4,     4,   208,   512,
     541,   526,   500,   208,   561,   208,     4,   512,     4,   541,
     512,     4,     4,   536,   512,   206,   206,   515,   541,   206,
     561,   526,   206,   206,   206,   512,   512,   208,   526,   207,
     207,   207,   512,     4,   206,     4,   206,   206,   536,   526,
       4,   208,   208,   541,   512,   512,   208,   512,   105,   106,
       4,   512,     4,   208,   208,   512,   208,   512,  1183,     4,
       4,   206,   512,   561,     4,   512,     4,   512,   512,   512,
       4,     4,   512,   512,   208,   512,   205,   208,   208,   512,
     512,     4,     4,   512,     4,   512,   512,   512,     4,     4,
     512,   512,   206,     4,     4,   515,     4,     4,     4,     4,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   208,   208,     4,   208,     4,     4,   176,
     177,     4,     4,   208,   208,   206,   206,     4,     4,     4,
       4,     4,     4,   206,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   700,     4,   702,     7,     4,   205,     4,
       4,     4,     4,     4,     4,   699,   206,     4,     4,     4,
       4,   702,     4,   208,     4,   208,     4,   208,     4,   206,
     206,    29,    30,    31,    32,    33,     4,     4,   208,   736,
     737,   206,   739,     4,     4,   208,   743,   208,     4,   206,
       4,   205,     7,     5,     7,   736,   737,   738,   739,     7,
     205,   205,     7,     7,   702,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,   205,   205,   205,     5,    77,
      78,    79,    80,    81,    82,    83,    84,    85,     5,    87,
      88,    89,     5,    91,     5,     7,     5,   205,   736,   737,
     738,   739,     5,     5,     5,   103,   205,   105,   106,   107,
     108,   109,   110,     7,     7,     7,     7,   115,   116,   117,
       7,     5,   120,   205,     7,   123,   124,     5,   205,   205,
     205,     5,     7,   131,    29,    30,    31,    32,    33,   205,
     205,   205,     5,   171,   205,    27,   205,   205,   205,     7,
       7,   205,   205,   205,     7,     7,   205,     7,     7,     7,
       7,   205,   205,   205,   205,   205,   205,   205,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,   176,   177,
     205,   205,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,     7,     7,   205,     4,    91,    92,     4,     4,
       4,     4,     4,     4,     4,     4,   205,   205,     4,   205,
     105,   106,     4,   108,     4,   110,   205,     6,     3,     6,
     115,   116,   117,     3,     6,   120,     3,     6,   123,     3,
       6,     3,     3,     6,     4,     3,   131,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   205,     3,
       6,     4,     3,     8,     6,     4,     4,     4,     4,   206,
       4,     4,   208,   206,     4,   206,   208,   206,   206,   206,
     206,   206,   206,     4,     4,   206,   206,   206,   206,     4,
     206,   176,   177,   206,   208,   206,   983,   206,     4,   986,
     208,     4,   989,     4,   208,   992,   989,   992,   983,   206,
     997,     6,   983,  1000,     4,   986,  1003,   992,   989,   205,
     205,   992,   997,   983,   983,  1000,   997,   989,   983,  1000,
    1017,   997,   992,   986,  1021,   205,   989,   992,   205,   992,
     983,     8,   997,  1030,   997,  1000,  1017,  1034,   983,   992,
    1021,   983,  1039,   205,  1039,   983,  1027,   992,   986,  1030,
     992,   989,   997,     8,   992,  1000,   983,   983,  1039,   997,
     205,   205,  1000,   983,   205,   992,   992,  1030,   205,     4,
     997,   997,   992,  1000,  1039,   983,   983,   997,   983,  1017,
       8,     3,   983,  1021,   992,   992,   983,   992,   983,  1027,
     997,   992,  1030,   983,     8,   992,   983,   992,   983,   983,
     983,  1039,   992,   983,   983,   992,   983,   992,   992,   992,
     983,   983,   992,   992,   983,   992,   983,   983,   983,   992,
     992,   983,   983,   992,   205,   992,   992,   992,     4,     4,
     992,   992,   992,   208,     4,     4,     7,     5,   205,     4,
       4,     4,     4,     4,   700,   702,   691,   678,   955,   789,
     977,   982,  1005,   995,   491,   205,   544,  1003,   983,   985,
     205,  1012,  1204,   986,   206,   206,   205,   205,   500,   536,
     206,   208,   205,   205,   988,   994,  1017,   512,  1162,  1039,
     991,   989,   515,  1000,  1002,   760,  1209,  1021,  1027,  1041,
    1039,   739,   526,   998,   565,  1031,  1239,  1219,  1259,  1034,
      -1,    -1,    -1,    -1,    -1,   541,    -1,  1204,    -1,  1204,
      -1,    -1,  1209,    -1,    -1,    -1,    -1,    -1,    -1,  1204,
      -1,    -1,  1219,  1204,  1209,    -1,   701,    -1,  1209,    -1,
     561,    -1,    -1,  1209,  1204,    -1,    -1,    -1,  1219,  1204,
      -1,  1204,    -1,    -1,  1209,    -1,  1209,    -1,    -1,    -1,
      -1,  1204,    -1,    -1,    -1,    -1,  1219,    -1,    -1,  1204,
      -1,    -1,  1204,    -1,  1209,    -1,  1204,    -1,    -1,    -1,
      -1,  1209,    -1,    -1,    -1,    -1,    -1,  1204,  1204,    -1,
      -1,  1219,  1209,  1209,  1204,    -1,    -1,    -1,    -1,  1209,
      -1,    -1,    -1,    -1,    -1,    -1,  1204,  1204,    -1,  1204,
      -1,    -1,  1209,  1204,    -1,    -1,    -1,  1204,    -1,  1204,
      -1,    -1,    -1,    -1,  1204,    -1,    -1,  1204,    -1,  1204,
    1204,  1204,    -1,    -1,  1204,  1204,    -1,  1204,    -1,    -1,
      -1,  1204,  1204,    -1,    -1,  1204,    -1,  1204,  1204,  1204,
      -1,    -1,  1204,  1204,  1204
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,     0,     5,
       7,     9,   205,   206,   207,   208,   224,   225,   226,   231,
       7,   240,     7,   245,     7,   292,     7,   403,     7,   486,
       7,   502,     7,   438,     7,   444,     7,   468,     7,   379,
       7,   567,     7,   598,   232,   227,   241,   246,   293,   404,
     487,   503,   439,   445,   469,   380,   568,   599,   224,   233,
     234,   205,   229,   230,    10,   242,   244,    11,    14,    26,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    90,    91,   101,   102,   105,   106,   110,
     115,   116,   117,   118,   119,   124,   134,   137,   144,   145,
     149,   152,   156,   176,   177,   178,   179,   180,   181,   190,
     205,   239,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   262,   263,   264,   265,
     266,   267,   268,   269,   272,   274,   276,   277,   278,   280,
     282,   283,   284,   285,   286,   287,   288,   306,   308,   314,
     316,   357,   366,   373,   387,   397,   421,   422,   423,   424,
     428,   436,   462,   492,   494,   496,   507,   509,   511,   534,
     546,   547,   555,   565,   596,   605,   629,    15,    16,    19,
      22,    23,    24,    25,   239,   290,   291,   294,   296,   299,
     302,   303,   304,   305,   492,   494,    87,    88,    89,   103,
     107,   108,   109,   120,   123,   131,   239,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   264,   265,   266,
     267,   268,   269,   272,   274,   276,   277,   278,   280,   282,
     405,   406,   407,   409,   411,   413,   415,   417,   419,   421,
     422,   423,   424,   427,   462,   480,   492,   494,   496,   507,
     509,   511,   531,   104,   239,   417,   419,   462,   488,   489,
     490,   492,   494,   119,   125,   126,   127,   128,   129,   130,
     132,   239,   462,   492,   494,   504,   505,   506,   507,   509,
     511,   513,   517,   519,   521,   523,   525,   527,   529,   436,
      37,    92,    94,    95,    98,    99,   100,   239,   334,   446,
     447,   448,   449,   450,   451,   452,   454,   456,   458,   459,
     461,   492,   494,    93,    96,    97,   239,   334,   450,   456,
     470,   471,   472,   473,   474,   476,   477,   478,   479,   492,
     494,   135,   136,   239,   381,   382,   383,   385,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   176,   177,   239,   492,   494,   569,   570,   571,   572,
     574,   575,   577,   578,   579,   582,   584,   586,   587,   588,
     590,   592,   594,    12,    13,   600,   601,   602,   604,     6,
       3,     4,     8,     3,   243,     3,     8,   597,   289,   309,
       4,     4,     4,   508,   510,   512,   307,   315,   317,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     261,     4,     4,     4,     4,     4,   270,   273,   275,     4,
       4,     4,   398,   437,   463,     4,   429,   493,   495,   425,
       4,     4,     4,   358,   535,   497,   374,   388,     4,   367,
     548,   556,   566,   279,   281,     4,     4,     4,   606,   630,
       4,     3,     8,   295,   297,   300,     4,     4,     4,     4,
       3,     8,   410,   412,   414,   481,   408,   416,     4,   420,
     418,   532,     3,     8,   491,     3,     8,   530,   518,   520,
     524,   522,   528,   526,   514,     8,     3,     8,   453,   335,
       4,   457,   455,   460,     4,     8,     3,   475,     4,     4,
       8,     3,   384,   386,     3,     8,     4,   585,   573,     4,
     576,     4,     4,   580,   583,     4,     4,   589,   591,   593,
     595,     3,     8,   603,     4,     3,     8,   224,   224,   205,
       4,     4,     4,     4,   208,   208,   208,     4,     4,     4,
       4,     4,     4,   206,   206,   206,   206,   206,   208,   207,
     207,   207,   206,   206,     4,   206,   206,   208,   208,   208,
       4,     4,     4,   208,   208,   208,     4,     4,     4,   206,
       4,     4,     4,     4,   208,   208,   208,     4,     4,     4,
       4,     4,   206,     4,     4,     4,     4,     4,     4,   208,
     208,   208,     4,     4,   248,     4,     4,     4,   208,   208,
     206,   206,   291,     4,     4,     4,     4,     4,     4,   206,
       4,     4,     4,   406,     4,   489,     4,     4,     4,     4,
       4,     4,     4,     4,   506,     4,     4,   206,     4,     4,
       4,   208,   448,     4,   208,   208,   472,     4,     4,   382,
     208,     4,     4,   206,     4,   206,   206,     4,     4,   208,
     208,     4,     4,     4,     4,   570,     4,   206,   601,     4,
       7,     7,     7,     7,   205,   205,   205,     7,     7,     5,
     205,   172,   173,   174,   175,   208,   271,   205,   205,     5,
       5,     5,     5,   226,   228,   205,   111,   112,   113,   114,
     426,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     205,   205,     5,     7,     5,   235,    17,    18,   298,    20,
      21,   301,   205,   205,   205,     5,   205,   205,   235,   205,
       7,   205,   235,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   228,   205,   205,
     205,    18,   170,   581,   171,   271,   205,   205,   205,     5,
     224,   247,   600,   290,    27,   310,   311,   312,    37,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    58,    59,    60,    61,    62,   239,   322,
     323,   324,   327,   329,   331,   333,   334,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   348,   349,   351,
     353,   355,   322,     7,   318,   319,   320,     7,   399,   400,
     401,     7,   440,   441,   442,     7,   464,   465,   466,     7,
     430,   431,   432,   125,   126,   127,   128,   130,   359,   360,
     361,   362,   363,   364,   365,     7,   536,   537,     7,   498,
     499,   500,     7,   375,   376,   377,   138,   139,   140,   141,
     142,   143,   389,   390,   391,   392,   393,   394,   395,   396,
     146,   147,   148,   239,   368,   369,   370,   371,   372,   492,
     494,   150,   151,   239,   492,   494,   549,   550,   551,   553,
     153,   154,   155,   205,   492,   494,   557,   558,   559,   560,
     562,   563,   569,     7,   607,   608,   191,   239,   631,   632,
     633,   236,     7,   482,   483,   484,   133,   513,   515,   533,
     318,     8,     8,     8,   313,     3,     8,   325,   328,   330,
     332,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   346,     4,   350,   352,   354,   356,     3,     8,     8,
     321,     6,     3,   402,     6,     3,   443,     6,     3,   467,
       6,     3,   433,     6,     3,     3,     6,   538,     3,     6,
     501,     6,     3,   378,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   552,
     554,     3,     8,     4,   561,     4,   564,     3,     8,     8,
     609,     3,     6,     4,     3,     8,   205,   237,   238,   485,
       6,     3,   516,     8,     6,     4,   311,     4,     4,     4,
       4,   206,   208,   206,   208,   206,   206,   206,   206,   206,
     206,     4,   206,     4,     4,     4,     4,   323,   322,   320,
     405,   401,   446,   442,   470,   466,   239,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   264,   265,   266,
     267,   268,   269,   272,   274,   276,   277,   278,   280,   282,
     334,   397,   415,   417,   419,   421,   422,   423,   424,   434,
     435,   462,   492,   494,   507,   509,   511,   531,   432,   360,
     121,   122,   239,   249,   250,   251,   334,   436,   462,   492,
     494,   507,   509,   511,   539,   540,   541,   542,   543,   545,
     537,   504,   500,   381,   377,   206,   206,   206,   206,   206,
     206,   390,   208,   206,   206,   369,     4,     4,   550,   208,
       4,   206,     4,   558,   182,   184,   185,   239,   334,   492,
     494,   610,   611,   612,   613,   615,   608,   208,   632,     6,
       3,   488,   484,     4,   205,    38,    39,    40,   326,   205,
     205,   205,    55,    56,    57,   347,   205,   205,   205,   205,
       8,     8,     8,     8,     3,     8,   544,     4,     8,     3,
       8,     8,   205,   205,   205,   224,   616,     4,   614,     3,
       8,   205,     8,   235,   435,     4,   208,   541,     4,   206,
       4,   611,   205,     5,   205,     7,   617,   618,   619,     3,
       6,   183,   186,   187,   188,   189,   620,   621,   622,   624,
     625,   626,   627,   618,   623,     4,     4,     4,   628,     3,
       8,     4,   208,   206,   206,     4,   621,   205,   205
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
     309,   308,   310,   310,   310,   311,   313,   312,   315,   314,
     317,   316,   318,   318,   319,   319,   319,   321,   320,   322,
     322,   322,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   323,   323,   323,   323,   323,   323,
     323,   323,   323,   323,   325,   324,   326,   326,   326,   328,
     327,   330,   329,   332,   331,   333,   335,   334,   336,   337,
     338,   339,   340,   341,   342,   343,   344,   346,   345,   347,
     347,   347,   348,   350,   349,   352,   351,   354,   353,   356,
     355,   358,   357,   359,   359,   359,   360,   360,   360,   360,
     360,   361,   362,   363,   364,   365,   367,   366,   368,   368,
     368,   369,   369,   369,   369,   369,   369,   370,   371,   372,
     374,   373,   375,   375,   376,   376,   376,   378,   377,   380,
     379,   381,   381,   381,   381,   382,   382,   384,   383,   386,
     385,   388,   387,   389,   389,   389,   390,   390,   390,   390,
     390,   390,   391,   392,   393,   394,   395,   396,   398,   397,
     399,   399,   400,   400,   400,   402,   401,   404,   403,   405,
     405,   405,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   408,   407,   410,
     409,   412,   411,   414,   413,   416,   415,   418,   417,   420,
     419,   421,   422,   423,   425,   424,   426,   426,   426,   426,
     427,   429,   428,   430,   430,   431,   431,   431,   433,   432,
     434,   434,   434,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   437,   436,   439,   438,   440,   440,   441,
     441,   441,   443,   442,   445,   444,   446,   446,   447,   447,
     447,   448,   448,   448,   448,   448,   448,   448,   448,   448,
     448,   449,   450,   451,   453,   452,   455,   454,   457,   456,
     458,   460,   459,   461,   463,   462,   464,   464,   465,   465,
     465,   467,   466,   469,   468,   470,   470,   471,   471,   471,
     472,   472,   472,   472,   472,   472,   472,   472,   472,   473,
     475,   474,   476,   477,   478,   479,   481,   480,   482,   482,
     483,   483,   483,   485,   484,   487,   486,   488,   488,   488,
     489,   489,   489,   489,   489,   489,   489,   491,   490,   493,
     492,   495,   494,   497,   496,   498,   498,   499,   499,   499,
     501,   500,   503,   502,   504,   504,   505,   505,   505,   506,
     506,   506,   506,   506,   506,   506,   506,   506,   506,   506,
     506,   506,   506,   506,   508,   507,   510,   509,   512,   511,
     514,   513,   516,   515,   518,   517,   520,   519,   522,   521,
     524,   523,   526,   525,   528,   527,   530,   529,   532,   531,
     533,   533,   535,   534,   536,   536,   536,   538,   537,   539,
     539,   540,   540,   540,   541,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   542,   544,
     543,   545,   546,   548,   547,   549,   549,   549,   550,   550,
     550,   550,   550,   552,   551,   554,   553,   556,   555,   557,
     557,   557,   558,   558,   558,   558,   558,   558,   559,   561,
     560,   562,   564,   563,   566,   565,   568,   567,   569,   569,
     569,   570,   570,   570,   570,   570,   570,   570,   570,   570,
     570,   570,   570,   570,   570,   570,   570,   570,   570,   571,
     573,   572,   574,   576,   575,   577,   578,   580,   579,   581,
     581,   583,   582,   585,   584,   586,   587,   589,   588,   591,
     590,   593,   592,   595,   594,   597,   596,   599,   598,   600,
     600,   600,   601,   601,   603,   602,   604,   606,   605,   607,
     607,   607,   609,   608,   610,   610,   610,   611,   611,   611,
     611,   611,   611,   611,   612,   614,   613,   616,   615,   617,
     617,   617,   619,   618,   620,   620,   620,   621,   621,   621,
     621,   621,   623,   622,   624,   625,   626,   628,   627,   630,
     629,   631,   631,   631,   632,   632,   633
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
       0,     6,     1,     3,     2,     1,     0,     4,     0,     6,
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
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     4,     0,     4,     0,     4,
       1,     0,     4,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     0,     1,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       1,     1,     0,     6,     1,     3,     2,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
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
       6,     1,     3,     2,     1,     1,     3
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
  "\"lease-checks\"", "\"echo-client-id\"", "\"match-client-id\"",
  "\"authoritative\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"user\"", "\"password\"", "\"host\"", "\"port\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
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
  "\"early-global-reservations-lookup\"", "\"ip-reservations-unique\"",
  "\"reservations-lookup-first\"", "\"loggers\"", "\"output_options\"",
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
  "early_global_reservations_lookup", "ip_reservations_unique",
  "reservations_lookup_first", "interfaces_config", "$@26",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@27", "interfaces_list", "$@28", "dhcp_socket_type", "$@29",
  "socket_type", "outbound_interface", "$@30", "outbound_interface_value",
  "re_detect", "service_sockets_require_all",
  "service_sockets_retry_wait_time", "service_sockets_max_retries",
  "lease_database", "$@31", "sanity_checks", "$@32",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@33",
  "hosts_database", "$@34", "hosts_databases", "$@35", "database_list",
  "not_empty_database_list", "database", "$@36", "database_map_params",
  "database_map_param", "database_type", "$@37", "db_type", "user", "$@38",
  "password", "$@39", "host", "$@40", "port", "name", "$@41", "persist",
  "lfc_interval", "readonly", "connect_timeout", "read_timeout",
  "write_timeout", "tcp_user_timeout", "max_reconnect_tries",
  "reconnect_wait_time", "on_fail", "$@42", "on_fail_mode",
  "max_row_errors", "trust_anchor", "$@43", "cert_file", "$@44",
  "key_file", "$@45", "cipher_list", "$@46",
  "host_reservation_identifiers", "$@47",
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
     893,   893,   904,   905,   906,   911,   913,   913,   932,   932,
     945,   945,   956,   957,   960,   961,   962,   967,   967,   977,
     978,   979,   984,   985,   986,   987,   988,   989,   990,   991,
     992,   993,   994,   995,   996,   997,   998,   999,  1000,  1001,
    1002,  1003,  1004,  1005,  1008,  1008,  1016,  1017,  1018,  1021,
    1021,  1030,  1030,  1039,  1039,  1048,  1054,  1054,  1063,  1069,
    1075,  1081,  1087,  1093,  1099,  1105,  1111,  1117,  1117,  1125,
    1126,  1127,  1130,  1136,  1136,  1145,  1145,  1154,  1154,  1163,
    1163,  1172,  1172,  1183,  1184,  1185,  1190,  1191,  1192,  1193,
    1194,  1197,  1202,  1207,  1212,  1217,  1224,  1224,  1237,  1238,
    1239,  1244,  1245,  1246,  1247,  1248,  1249,  1252,  1258,  1264,
    1270,  1270,  1281,  1282,  1285,  1286,  1287,  1292,  1292,  1302,
    1302,  1312,  1313,  1314,  1317,  1320,  1321,  1324,  1324,  1333,
    1333,  1342,  1342,  1354,  1355,  1356,  1361,  1362,  1363,  1364,
    1365,  1366,  1369,  1375,  1381,  1387,  1393,  1399,  1408,  1408,
    1422,  1423,  1426,  1427,  1428,  1437,  1437,  1463,  1463,  1474,
    1475,  1476,  1482,  1483,  1484,  1485,  1486,  1487,  1488,  1489,
    1490,  1491,  1492,  1493,  1494,  1495,  1496,  1497,  1498,  1499,
    1500,  1501,  1502,  1503,  1504,  1505,  1506,  1507,  1508,  1509,
    1510,  1511,  1512,  1513,  1514,  1515,  1516,  1517,  1518,  1519,
    1520,  1521,  1522,  1523,  1524,  1525,  1526,  1529,  1529,  1538,
    1538,  1547,  1547,  1556,  1556,  1565,  1565,  1574,  1574,  1583,
    1583,  1594,  1600,  1606,  1612,  1612,  1620,  1621,  1622,  1623,
    1626,  1634,  1634,  1646,  1647,  1651,  1652,  1653,  1658,  1658,
    1666,  1667,  1668,  1673,  1674,  1675,  1676,  1677,  1678,  1679,
    1680,  1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,
    1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,
    1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,
    1710,  1711,  1712,  1719,  1719,  1733,  1733,  1742,  1743,  1746,
    1747,  1748,  1755,  1755,  1770,  1770,  1784,  1785,  1788,  1789,
    1790,  1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,  1803,
    1804,  1807,  1809,  1815,  1817,  1817,  1826,  1826,  1835,  1835,
    1844,  1846,  1846,  1855,  1865,  1865,  1878,  1879,  1884,  1885,
    1886,  1893,  1893,  1905,  1905,  1917,  1918,  1923,  1924,  1925,
    1932,  1933,  1934,  1935,  1936,  1937,  1938,  1939,  1940,  1943,
    1945,  1945,  1954,  1956,  1958,  1964,  1973,  1973,  1986,  1987,
    1990,  1991,  1992,  1997,  1997,  2007,  2007,  2017,  2018,  2019,
    2024,  2025,  2026,  2027,  2028,  2029,  2030,  2033,  2033,  2042,
    2042,  2067,  2067,  2097,  2097,  2108,  2109,  2112,  2113,  2114,
    2119,  2119,  2128,  2128,  2137,  2138,  2141,  2142,  2143,  2149,
    2150,  2151,  2152,  2153,  2154,  2155,  2156,  2157,  2158,  2159,
    2160,  2161,  2162,  2163,  2166,  2166,  2175,  2175,  2184,  2184,
    2193,  2193,  2202,  2202,  2213,  2213,  2222,  2222,  2231,  2231,
    2240,  2240,  2249,  2249,  2258,  2258,  2267,  2267,  2281,  2281,
    2292,  2293,  2299,  2299,  2310,  2311,  2312,  2317,  2317,  2327,
    2328,  2331,  2332,  2333,  2338,  2339,  2340,  2341,  2342,  2343,
    2344,  2345,  2346,  2347,  2348,  2349,  2350,  2351,  2354,  2356,
    2356,  2365,  2373,  2381,  2381,  2392,  2393,  2394,  2399,  2400,
    2401,  2402,  2403,  2406,  2406,  2415,  2415,  2427,  2427,  2440,
    2441,  2442,  2447,  2448,  2449,  2450,  2451,  2452,  2455,  2461,
    2461,  2470,  2476,  2476,  2486,  2486,  2499,  2499,  2509,  2510,
    2511,  2516,  2517,  2518,  2519,  2520,  2521,  2522,  2523,  2524,
    2525,  2526,  2527,  2528,  2529,  2530,  2531,  2532,  2533,  2536,
    2542,  2542,  2551,  2557,  2557,  2566,  2572,  2578,  2578,  2587,
    2588,  2591,  2591,  2601,  2601,  2611,  2618,  2625,  2625,  2634,
    2634,  2644,  2644,  2654,  2654,  2666,  2666,  2678,  2678,  2688,
    2689,  2690,  2696,  2697,  2700,  2700,  2711,  2719,  2719,  2732,
    2733,  2734,  2740,  2740,  2748,  2749,  2750,  2755,  2756,  2757,
    2758,  2759,  2760,  2761,  2764,  2770,  2770,  2779,  2779,  2790,
    2791,  2792,  2797,  2797,  2805,  2806,  2807,  2812,  2813,  2814,
    2815,  2816,  2819,  2819,  2828,  2834,  2840,  2846,  2846,  2855,
    2855,  2866,  2867,  2868,  2873,  2874,  2877
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
#line 6179 "dhcp4_parser.cc"

#line 2883 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
