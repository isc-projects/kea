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
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 288 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 288 "dhcp4_parser.yy"
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
#line 297 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 298 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 299 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 300 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 301 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 302 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 303 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 304 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 305 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 306 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 307 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 308 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 309 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 317 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 318 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 319 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 320 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 321 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 322 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 323 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 326 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 331 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 336 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 342 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 349 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 354 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 360 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 365 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 368 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 376 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 380 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 384 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 390 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 392 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 401 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 405 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 409 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 419 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 428 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 433 "dhcp4_parser.yy"
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
#line 443 "dhcp4_parser.yy"
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
#line 452 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 460 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 466 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 470 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 477 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 134: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 550 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 135: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 556 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 136: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 562 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 137: // renew_timer: "renew-timer" ":" "integer"
#line 568 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 138: // rebind_timer: "rebind-timer" ":" "integer"
#line 574 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 139: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 580 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 140: // t1_percent: "t1-percent" ":" "floating point"
#line 586 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 141: // t2_percent: "t2-percent" ":" "floating point"
#line 592 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 142: // cache_threshold: "cache-threshold" ":" "floating point"
#line 598 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 143: // cache_max_age: "cache-max-age" ":" "integer"
#line 604 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 144: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 610 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 145: // $@20: %empty
#line 616 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 146: // server_tag: "server-tag" $@20 ":" "constant string"
#line 619 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 147: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 625 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 148: // echo_client_id: "echo-client-id" ":" "boolean"
#line 631 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1270 "dhcp4_parser.cc"
    break;

  case 149: // match_client_id: "match-client-id" ":" "boolean"
#line 637 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1280 "dhcp4_parser.cc"
    break;

  case 150: // authoritative: "authoritative" ":" "boolean"
#line 643 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1290 "dhcp4_parser.cc"
    break;

  case 151: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 649 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1300 "dhcp4_parser.cc"
    break;

  case 152: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 655 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1310 "dhcp4_parser.cc"
    break;

  case 153: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 661 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1320 "dhcp4_parser.cc"
    break;

  case 154: // $@21: %empty
#line 667 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 155: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 670 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1338 "dhcp4_parser.cc"
    break;

  case 156: // ddns_replace_client_name_value: "when-present"
#line 676 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1346 "dhcp4_parser.cc"
    break;

  case 157: // ddns_replace_client_name_value: "never"
#line 679 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1354 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "always"
#line 682 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1362 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "when-not-present"
#line 685 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1370 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "boolean"
#line 688 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1379 "dhcp4_parser.cc"
    break;

  case 161: // $@22: %empty
#line 694 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1388 "dhcp4_parser.cc"
    break;

  case 162: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 697 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1398 "dhcp4_parser.cc"
    break;

  case 163: // $@23: %empty
#line 703 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 164: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 706 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 165: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 712 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1427 "dhcp4_parser.cc"
    break;

  case 166: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 718 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1437 "dhcp4_parser.cc"
    break;

  case 167: // $@24: %empty
#line 724 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 168: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 727 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 169: // $@25: %empty
#line 733 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 170: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 736 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 171: // store_extended_info: "store-extended-info" ":" "boolean"
#line 742 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 172: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 748 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1495 "dhcp4_parser.cc"
    break;

  case 173: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 754 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 174: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 760 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 175: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 766 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 176: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 772 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1535 "dhcp4_parser.cc"
    break;

  case 177: // $@26: %empty
#line 778 "dhcp4_parser.yy"
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
#line 784 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1557 "dhcp4_parser.cc"
    break;

  case 181: // interfaces_config_params: interfaces_config_params ","
#line 792 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1565 "dhcp4_parser.cc"
    break;

  case 192: // $@27: %empty
#line 809 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1575 "dhcp4_parser.cc"
    break;

  case 193: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 813 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 194: // $@28: %empty
#line 818 "dhcp4_parser.yy"
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
#line 824 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1605 "dhcp4_parser.cc"
    break;

  case 196: // $@29: %empty
#line 829 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 197: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 832 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1623 "dhcp4_parser.cc"
    break;

  case 198: // socket_type: "raw"
#line 837 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1629 "dhcp4_parser.cc"
    break;

  case 199: // socket_type: "udp"
#line 838 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1635 "dhcp4_parser.cc"
    break;

  case 200: // $@30: %empty
#line 841 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 201: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 844 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1653 "dhcp4_parser.cc"
    break;

  case 202: // outbound_interface_value: "same-as-inbound"
#line 849 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1661 "dhcp4_parser.cc"
    break;

  case 203: // outbound_interface_value: "use-routing"
#line 851 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1669 "dhcp4_parser.cc"
    break;

  case 204: // re_detect: "re-detect" ":" "boolean"
#line 855 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1679 "dhcp4_parser.cc"
    break;

  case 205: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 861 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1689 "dhcp4_parser.cc"
    break;

  case 206: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 867 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1699 "dhcp4_parser.cc"
    break;

  case 207: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 873 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1709 "dhcp4_parser.cc"
    break;

  case 208: // $@31: %empty
#line 879 "dhcp4_parser.yy"
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
#line 885 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1732 "dhcp4_parser.cc"
    break;

  case 210: // $@32: %empty
#line 892 "dhcp4_parser.yy"
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
#line 898 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1753 "dhcp4_parser.cc"
    break;

  case 214: // sanity_checks_params: sanity_checks_params ","
#line 905 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1761 "dhcp4_parser.cc"
    break;

  case 217: // $@33: %empty
#line 914 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1770 "dhcp4_parser.cc"
    break;

  case 218: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 917 "dhcp4_parser.yy"
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
#line 933 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1799 "dhcp4_parser.cc"
    break;

  case 220: // extended_info_checks: "extended-info-checks" $@34 ":" "constant string"
#line 936 "dhcp4_parser.yy"
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
#line 951 "dhcp4_parser.yy"
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
#line 957 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1841 "dhcp4_parser.cc"
    break;

  case 223: // $@36: %empty
#line 964 "dhcp4_parser.yy"
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
#line 970 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1862 "dhcp4_parser.cc"
    break;

  case 229: // not_empty_database_list: not_empty_database_list ","
#line 981 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1870 "dhcp4_parser.cc"
    break;

  case 230: // $@37: %empty
#line 986 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1880 "dhcp4_parser.cc"
    break;

  case 231: // database: "{" $@37 database_map_params "}"
#line 990 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1890 "dhcp4_parser.cc"
    break;

  case 234: // database_map_params: database_map_params ","
#line 998 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1898 "dhcp4_parser.cc"
    break;

  case 254: // $@38: %empty
#line 1024 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1907 "dhcp4_parser.cc"
    break;

  case 255: // database_type: "type" $@38 ":" db_type
#line 1027 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1916 "dhcp4_parser.cc"
    break;

  case 256: // db_type: "memfile"
#line 1032 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1922 "dhcp4_parser.cc"
    break;

  case 257: // db_type: "mysql"
#line 1033 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1928 "dhcp4_parser.cc"
    break;

  case 258: // db_type: "postgresql"
#line 1034 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1934 "dhcp4_parser.cc"
    break;

  case 259: // $@39: %empty
#line 1037 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1943 "dhcp4_parser.cc"
    break;

  case 260: // user: "user" $@39 ":" "constant string"
#line 1040 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 261: // $@40: %empty
#line 1046 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 262: // password: "password" $@40 ":" "constant string"
#line 1049 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 263: // $@41: %empty
#line 1055 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 264: // host: "host" $@41 ":" "constant string"
#line 1058 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 265: // port: "port" ":" "integer"
#line 1064 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 266: // $@42: %empty
#line 1070 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 267: // name: "name" $@42 ":" "constant string"
#line 1073 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 268: // persist: "persist" ":" "boolean"
#line 1079 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2030 "dhcp4_parser.cc"
    break;

  case 269: // lfc_interval: "lfc-interval" ":" "integer"
#line 1085 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2040 "dhcp4_parser.cc"
    break;

  case 270: // readonly: "readonly" ":" "boolean"
#line 1091 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 271: // connect_timeout: "connect-timeout" ":" "integer"
#line 1097 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2060 "dhcp4_parser.cc"
    break;

  case 272: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1103 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2070 "dhcp4_parser.cc"
    break;

  case 273: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1109 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2080 "dhcp4_parser.cc"
    break;

  case 274: // $@43: %empty
#line 1115 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 275: // on_fail: "on-fail" $@43 ":" on_fail_mode
#line 1118 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2098 "dhcp4_parser.cc"
    break;

  case 276: // on_fail_mode: "stop-retry-exit"
#line 1123 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2104 "dhcp4_parser.cc"
    break;

  case 277: // on_fail_mode: "serve-retry-exit"
#line 1124 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2110 "dhcp4_parser.cc"
    break;

  case 278: // on_fail_mode: "serve-retry-continue"
#line 1125 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2116 "dhcp4_parser.cc"
    break;

  case 279: // max_row_errors: "max-row-errors" ":" "integer"
#line 1128 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2126 "dhcp4_parser.cc"
    break;

  case 280: // $@44: %empty
#line 1134 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2135 "dhcp4_parser.cc"
    break;

  case 281: // trust_anchor: "trust-anchor" $@44 ":" "constant string"
#line 1137 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2145 "dhcp4_parser.cc"
    break;

  case 282: // $@45: %empty
#line 1143 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2154 "dhcp4_parser.cc"
    break;

  case 283: // cert_file: "cert-file" $@45 ":" "constant string"
#line 1146 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2164 "dhcp4_parser.cc"
    break;

  case 284: // $@46: %empty
#line 1152 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 285: // key_file: "key-file" $@46 ":" "constant string"
#line 1155 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2183 "dhcp4_parser.cc"
    break;

  case 286: // $@47: %empty
#line 1161 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 287: // cipher_list: "cipher-list" $@47 ":" "constant string"
#line 1164 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 288: // $@48: %empty
#line 1170 "dhcp4_parser.yy"
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
#line 1176 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2223 "dhcp4_parser.cc"
    break;

  case 292: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1183 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2231 "dhcp4_parser.cc"
    break;

  case 298: // duid_id: "duid"
#line 1195 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2240 "dhcp4_parser.cc"
    break;

  case 299: // hw_address_id: "hw-address"
#line 1200 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2249 "dhcp4_parser.cc"
    break;

  case 300: // circuit_id: "circuit-id"
#line 1205 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2258 "dhcp4_parser.cc"
    break;

  case 301: // client_id: "client-id"
#line 1210 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2267 "dhcp4_parser.cc"
    break;

  case 302: // flex_id: "flex-id"
#line 1215 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2276 "dhcp4_parser.cc"
    break;

  case 303: // $@49: %empty
#line 1222 "dhcp4_parser.yy"
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
#line 1228 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2299 "dhcp4_parser.cc"
    break;

  case 307: // multi_threading_params: multi_threading_params ","
#line 1237 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2307 "dhcp4_parser.cc"
    break;

  case 314: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1250 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2317 "dhcp4_parser.cc"
    break;

  case 315: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1256 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2327 "dhcp4_parser.cc"
    break;

  case 316: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1262 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2337 "dhcp4_parser.cc"
    break;

  case 317: // $@50: %empty
#line 1268 "dhcp4_parser.yy"
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
#line 1274 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2358 "dhcp4_parser.cc"
    break;

  case 323: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1285 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2366 "dhcp4_parser.cc"
    break;

  case 324: // $@51: %empty
#line 1290 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 325: // hooks_library: "{" $@51 hooks_params "}"
#line 1294 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 326: // $@52: %empty
#line 1300 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2396 "dhcp4_parser.cc"
    break;

  case 327: // sub_hooks_library: "{" $@52 hooks_params "}"
#line 1304 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 330: // hooks_params: hooks_params ","
#line 1312 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2414 "dhcp4_parser.cc"
    break;

  case 334: // $@53: %empty
#line 1322 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2423 "dhcp4_parser.cc"
    break;

  case 335: // library: "library" $@53 ":" "constant string"
#line 1325 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2433 "dhcp4_parser.cc"
    break;

  case 336: // $@54: %empty
#line 1331 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2442 "dhcp4_parser.cc"
    break;

  case 337: // parameters: "parameters" $@54 ":" map_value
#line 1334 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2451 "dhcp4_parser.cc"
    break;

  case 338: // $@55: %empty
#line 1340 "dhcp4_parser.yy"
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
#line 1346 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 342: // expired_leases_params: expired_leases_params ","
#line 1354 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2481 "dhcp4_parser.cc"
    break;

  case 349: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1367 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 350: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1373 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 351: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1379 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2511 "dhcp4_parser.cc"
    break;

  case 352: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1385 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2521 "dhcp4_parser.cc"
    break;

  case 353: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1391 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2531 "dhcp4_parser.cc"
    break;

  case 354: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1397 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2541 "dhcp4_parser.cc"
    break;

  case 355: // $@56: %empty
#line 1406 "dhcp4_parser.yy"
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
#line 1412 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2562 "dhcp4_parser.cc"
    break;

  case 361: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1426 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2570 "dhcp4_parser.cc"
    break;

  case 362: // $@57: %empty
#line 1435 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 363: // subnet4: "{" $@57 subnet4_params "}"
#line 1439 "dhcp4_parser.yy"
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
#line 1461 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2616 "dhcp4_parser.cc"
    break;

  case 365: // sub_subnet4: "{" $@58 subnet4_params "}"
#line 1465 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2626 "dhcp4_parser.cc"
    break;

  case 368: // subnet4_params: subnet4_params ","
#line 1474 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2634 "dhcp4_parser.cc"
    break;

  case 414: // $@59: %empty
#line 1527 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2643 "dhcp4_parser.cc"
    break;

  case 415: // subnet: "subnet" $@59 ":" "constant string"
#line 1530 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2653 "dhcp4_parser.cc"
    break;

  case 416: // $@60: %empty
#line 1536 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2662 "dhcp4_parser.cc"
    break;

  case 417: // subnet_4o6_interface: "4o6-interface" $@60 ":" "constant string"
#line 1539 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2672 "dhcp4_parser.cc"
    break;

  case 418: // $@61: %empty
#line 1545 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2681 "dhcp4_parser.cc"
    break;

  case 419: // subnet_4o6_interface_id: "4o6-interface-id" $@61 ":" "constant string"
#line 1548 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2691 "dhcp4_parser.cc"
    break;

  case 420: // $@62: %empty
#line 1554 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2700 "dhcp4_parser.cc"
    break;

  case 421: // subnet_4o6_subnet: "4o6-subnet" $@62 ":" "constant string"
#line 1557 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2710 "dhcp4_parser.cc"
    break;

  case 422: // $@63: %empty
#line 1563 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp4_parser.cc"
    break;

  case 423: // interface: "interface" $@63 ":" "constant string"
#line 1566 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2729 "dhcp4_parser.cc"
    break;

  case 424: // $@64: %empty
#line 1572 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2738 "dhcp4_parser.cc"
    break;

  case 425: // client_class: "client-class" $@64 ":" "constant string"
#line 1575 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2748 "dhcp4_parser.cc"
    break;

  case 426: // $@65: %empty
#line 1581 "dhcp4_parser.yy"
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
#line 1587 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2769 "dhcp4_parser.cc"
    break;

  case 428: // reservations_global: "reservations-global" ":" "boolean"
#line 1592 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2779 "dhcp4_parser.cc"
    break;

  case 429: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1598 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2789 "dhcp4_parser.cc"
    break;

  case 430: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1604 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2799 "dhcp4_parser.cc"
    break;

  case 431: // $@66: %empty
#line 1610 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2808 "dhcp4_parser.cc"
    break;

  case 432: // reservation_mode: "reservation-mode" $@66 ":" hr_mode
#line 1613 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2817 "dhcp4_parser.cc"
    break;

  case 433: // hr_mode: "disabled"
#line 1618 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2823 "dhcp4_parser.cc"
    break;

  case 434: // hr_mode: "out-of-pool"
#line 1619 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2829 "dhcp4_parser.cc"
    break;

  case 435: // hr_mode: "global"
#line 1620 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2835 "dhcp4_parser.cc"
    break;

  case 436: // hr_mode: "all"
#line 1621 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2841 "dhcp4_parser.cc"
    break;

  case 437: // id: "id" ":" "integer"
#line 1624 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2851 "dhcp4_parser.cc"
    break;

  case 438: // $@67: %empty
#line 1632 "dhcp4_parser.yy"
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
#line 1638 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2872 "dhcp4_parser.cc"
    break;

  case 444: // shared_networks_list: shared_networks_list ","
#line 1651 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2880 "dhcp4_parser.cc"
    break;

  case 445: // $@68: %empty
#line 1656 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 446: // shared_network: "{" $@68 shared_network_params "}"
#line 1660 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2898 "dhcp4_parser.cc"
    break;

  case 449: // shared_network_params: shared_network_params ","
#line 1666 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2906 "dhcp4_parser.cc"
    break;

  case 490: // $@69: %empty
#line 1717 "dhcp4_parser.yy"
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
#line 1723 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2927 "dhcp4_parser.cc"
    break;

  case 492: // $@70: %empty
#line 1731 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2936 "dhcp4_parser.cc"
    break;

  case 493: // sub_option_def_list: "{" $@70 option_def_list "}"
#line 1734 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2944 "dhcp4_parser.cc"
    break;

  case 498: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1746 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2952 "dhcp4_parser.cc"
    break;

  case 499: // $@71: %empty
#line 1753 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2962 "dhcp4_parser.cc"
    break;

  case 500: // option_def_entry: "{" $@71 option_def_params "}"
#line 1757 "dhcp4_parser.yy"
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
#line 1768 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2984 "dhcp4_parser.cc"
    break;

  case 502: // sub_option_def: "{" $@72 option_def_params "}"
#line 1772 "dhcp4_parser.yy"
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
#line 1788 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3004 "dhcp4_parser.cc"
    break;

  case 519: // code: "code" ":" "integer"
#line 1807 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3014 "dhcp4_parser.cc"
    break;

  case 521: // $@73: %empty
#line 1815 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3023 "dhcp4_parser.cc"
    break;

  case 522: // option_def_type: "type" $@73 ":" "constant string"
#line 1818 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3033 "dhcp4_parser.cc"
    break;

  case 523: // $@74: %empty
#line 1824 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3042 "dhcp4_parser.cc"
    break;

  case 524: // option_def_record_types: "record-types" $@74 ":" "constant string"
#line 1827 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 525: // $@75: %empty
#line 1833 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3061 "dhcp4_parser.cc"
    break;

  case 526: // space: "space" $@75 ":" "constant string"
#line 1836 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3071 "dhcp4_parser.cc"
    break;

  case 528: // $@76: %empty
#line 1844 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3080 "dhcp4_parser.cc"
    break;

  case 529: // option_def_encapsulate: "encapsulate" $@76 ":" "constant string"
#line 1847 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 530: // option_def_array: "array" ":" "boolean"
#line 1853 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3100 "dhcp4_parser.cc"
    break;

  case 531: // $@77: %empty
#line 1863 "dhcp4_parser.yy"
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
#line 1869 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 537: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1884 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3129 "dhcp4_parser.cc"
    break;

  case 538: // $@78: %empty
#line 1891 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 539: // option_data_entry: "{" $@78 option_data_params "}"
#line 1895 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3148 "dhcp4_parser.cc"
    break;

  case 540: // $@79: %empty
#line 1903 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3158 "dhcp4_parser.cc"
    break;

  case 541: // sub_option_data: "{" $@79 option_data_params "}"
#line 1907 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3167 "dhcp4_parser.cc"
    break;

  case 546: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1923 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3175 "dhcp4_parser.cc"
    break;

  case 557: // $@80: %empty
#line 1943 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3184 "dhcp4_parser.cc"
    break;

  case 558: // option_data_data: "data" $@80 ":" "constant string"
#line 1946 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3194 "dhcp4_parser.cc"
    break;

  case 561: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1956 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3204 "dhcp4_parser.cc"
    break;

  case 562: // option_data_always_send: "always-send" ":" "boolean"
#line 1962 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 563: // $@81: %empty
#line 1971 "dhcp4_parser.yy"
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
#line 1977 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3235 "dhcp4_parser.cc"
    break;

  case 569: // not_empty_pools_list: not_empty_pools_list ","
#line 1990 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3243 "dhcp4_parser.cc"
    break;

  case 570: // $@82: %empty
#line 1995 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3253 "dhcp4_parser.cc"
    break;

  case 571: // pool_list_entry: "{" $@82 pool_params "}"
#line 1999 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 572: // $@83: %empty
#line 2005 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 573: // sub_pool4: "{" $@83 pool_params "}"
#line 2009 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 576: // pool_params: pool_params ","
#line 2017 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3291 "dhcp4_parser.cc"
    break;

  case 584: // $@84: %empty
#line 2031 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3300 "dhcp4_parser.cc"
    break;

  case 585: // pool_entry: "pool" $@84 ":" "constant string"
#line 2034 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3310 "dhcp4_parser.cc"
    break;

  case 586: // $@85: %empty
#line 2040 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp4_parser.cc"
    break;

  case 587: // user_context: "user-context" $@85 ":" map_value
#line 2042 "dhcp4_parser.yy"
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
#line 2065 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3353 "dhcp4_parser.cc"
    break;

  case 589: // comment: "comment" $@86 ":" "constant string"
#line 2067 "dhcp4_parser.yy"
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
#line 2095 "dhcp4_parser.yy"
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
#line 2101 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3403 "dhcp4_parser.cc"
    break;

  case 596: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2112 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3411 "dhcp4_parser.cc"
    break;

  case 597: // $@88: %empty
#line 2117 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3421 "dhcp4_parser.cc"
    break;

  case 598: // reservation: "{" $@88 reservation_params "}"
#line 2121 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3430 "dhcp4_parser.cc"
    break;

  case 599: // $@89: %empty
#line 2126 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3440 "dhcp4_parser.cc"
    break;

  case 600: // sub_reservation: "{" $@89 reservation_params "}"
#line 2130 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3449 "dhcp4_parser.cc"
    break;

  case 605: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2141 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3457 "dhcp4_parser.cc"
    break;

  case 621: // $@90: %empty
#line 2164 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3466 "dhcp4_parser.cc"
    break;

  case 622: // next_server: "next-server" $@90 ":" "constant string"
#line 2167 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3476 "dhcp4_parser.cc"
    break;

  case 623: // $@91: %empty
#line 2173 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3485 "dhcp4_parser.cc"
    break;

  case 624: // server_hostname: "server-hostname" $@91 ":" "constant string"
#line 2176 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3495 "dhcp4_parser.cc"
    break;

  case 625: // $@92: %empty
#line 2182 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3504 "dhcp4_parser.cc"
    break;

  case 626: // boot_file_name: "boot-file-name" $@92 ":" "constant string"
#line 2185 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3514 "dhcp4_parser.cc"
    break;

  case 627: // $@93: %empty
#line 2191 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3523 "dhcp4_parser.cc"
    break;

  case 628: // ip_address: "ip-address" $@93 ":" "constant string"
#line 2194 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3533 "dhcp4_parser.cc"
    break;

  case 629: // $@94: %empty
#line 2200 "dhcp4_parser.yy"
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
#line 2206 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 631: // $@95: %empty
#line 2211 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 632: // duid: "duid" $@95 ":" "constant string"
#line 2214 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 633: // $@96: %empty
#line 2220 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 634: // hw_address: "hw-address" $@96 ":" "constant string"
#line 2223 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 635: // $@97: %empty
#line 2229 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3601 "dhcp4_parser.cc"
    break;

  case 636: // client_id_value: "client-id" $@97 ":" "constant string"
#line 2232 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 637: // $@98: %empty
#line 2238 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3620 "dhcp4_parser.cc"
    break;

  case 638: // circuit_id_value: "circuit-id" $@98 ":" "constant string"
#line 2241 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3630 "dhcp4_parser.cc"
    break;

  case 639: // $@99: %empty
#line 2247 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3639 "dhcp4_parser.cc"
    break;

  case 640: // flex_id_value: "flex-id" $@99 ":" "constant string"
#line 2250 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3649 "dhcp4_parser.cc"
    break;

  case 641: // $@100: %empty
#line 2256 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3658 "dhcp4_parser.cc"
    break;

  case 642: // hostname: "hostname" $@100 ":" "constant string"
#line 2259 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3668 "dhcp4_parser.cc"
    break;

  case 643: // $@101: %empty
#line 2265 "dhcp4_parser.yy"
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
#line 2271 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3689 "dhcp4_parser.cc"
    break;

  case 645: // $@102: %empty
#line 2279 "dhcp4_parser.yy"
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
#line 2285 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3710 "dhcp4_parser.cc"
    break;

  case 649: // $@103: %empty
#line 2297 "dhcp4_parser.yy"
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
#line 2303 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3731 "dhcp4_parser.cc"
    break;

  case 653: // client_classes_list: client_classes_list ","
#line 2310 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3739 "dhcp4_parser.cc"
    break;

  case 654: // $@104: %empty
#line 2315 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3749 "dhcp4_parser.cc"
    break;

  case 655: // client_class_entry: "{" $@104 client_class_params "}"
#line 2319 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3759 "dhcp4_parser.cc"
    break;

  case 660: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2331 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3767 "dhcp4_parser.cc"
    break;

  case 676: // $@105: %empty
#line 2354 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3776 "dhcp4_parser.cc"
    break;

  case 677: // client_class_test: "test" $@105 ":" "constant string"
#line 2357 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3786 "dhcp4_parser.cc"
    break;

  case 678: // only_if_required: "only-if-required" ":" "boolean"
#line 2363 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3796 "dhcp4_parser.cc"
    break;

  case 679: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2371 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3806 "dhcp4_parser.cc"
    break;

  case 680: // $@106: %empty
#line 2379 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3818 "dhcp4_parser.cc"
    break;

  case 681: // control_socket: "control-socket" $@106 ":" "{" control_socket_params "}"
#line 2385 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3827 "dhcp4_parser.cc"
    break;

  case 684: // control_socket_params: control_socket_params ","
#line 2392 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3835 "dhcp4_parser.cc"
    break;

  case 690: // $@107: %empty
#line 2404 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 691: // control_socket_type: "socket-type" $@107 ":" "constant string"
#line 2407 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3854 "dhcp4_parser.cc"
    break;

  case 692: // $@108: %empty
#line 2413 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 693: // control_socket_name: "socket-name" $@108 ":" "constant string"
#line 2416 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3873 "dhcp4_parser.cc"
    break;

  case 694: // $@109: %empty
#line 2425 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3885 "dhcp4_parser.cc"
    break;

  case 695: // dhcp_queue_control: "dhcp-queue-control" $@109 ":" "{" queue_control_params "}"
#line 2431 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3896 "dhcp4_parser.cc"
    break;

  case 698: // queue_control_params: queue_control_params ","
#line 2440 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3904 "dhcp4_parser.cc"
    break;

  case 705: // enable_queue: "enable-queue" ":" "boolean"
#line 2453 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3914 "dhcp4_parser.cc"
    break;

  case 706: // $@110: %empty
#line 2459 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3923 "dhcp4_parser.cc"
    break;

  case 707: // queue_type: "queue-type" $@110 ":" "constant string"
#line 2462 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3933 "dhcp4_parser.cc"
    break;

  case 708: // capacity: "capacity" ":" "integer"
#line 2468 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3943 "dhcp4_parser.cc"
    break;

  case 709: // $@111: %empty
#line 2474 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3952 "dhcp4_parser.cc"
    break;

  case 710: // arbitrary_map_entry: "constant string" $@111 ":" value
#line 2477 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3961 "dhcp4_parser.cc"
    break;

  case 711: // $@112: %empty
#line 2484 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3973 "dhcp4_parser.cc"
    break;

  case 712: // dhcp_ddns: "dhcp-ddns" $@112 ":" "{" dhcp_ddns_params "}"
#line 2490 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3984 "dhcp4_parser.cc"
    break;

  case 713: // $@113: %empty
#line 2497 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3994 "dhcp4_parser.cc"
    break;

  case 714: // sub_dhcp_ddns: "{" $@113 dhcp_ddns_params "}"
#line 2501 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4004 "dhcp4_parser.cc"
    break;

  case 717: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2509 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4012 "dhcp4_parser.cc"
    break;

  case 736: // enable_updates: "enable-updates" ":" "boolean"
#line 2534 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4022 "dhcp4_parser.cc"
    break;

  case 737: // $@114: %empty
#line 2540 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4031 "dhcp4_parser.cc"
    break;

  case 738: // server_ip: "server-ip" $@114 ":" "constant string"
#line 2543 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 739: // server_port: "server-port" ":" "integer"
#line 2549 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4051 "dhcp4_parser.cc"
    break;

  case 740: // $@115: %empty
#line 2555 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4060 "dhcp4_parser.cc"
    break;

  case 741: // sender_ip: "sender-ip" $@115 ":" "constant string"
#line 2558 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4070 "dhcp4_parser.cc"
    break;

  case 742: // sender_port: "sender-port" ":" "integer"
#line 2564 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4080 "dhcp4_parser.cc"
    break;

  case 743: // max_queue_size: "max-queue-size" ":" "integer"
#line 2570 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4090 "dhcp4_parser.cc"
    break;

  case 744: // $@116: %empty
#line 2576 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4099 "dhcp4_parser.cc"
    break;

  case 745: // ncr_protocol: "ncr-protocol" $@116 ":" ncr_protocol_value
#line 2579 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4108 "dhcp4_parser.cc"
    break;

  case 746: // ncr_protocol_value: "udp"
#line 2585 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4114 "dhcp4_parser.cc"
    break;

  case 747: // ncr_protocol_value: "tcp"
#line 2586 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4120 "dhcp4_parser.cc"
    break;

  case 748: // $@117: %empty
#line 2589 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4129 "dhcp4_parser.cc"
    break;

  case 749: // ncr_format: "ncr-format" $@117 ":" "JSON"
#line 2592 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4139 "dhcp4_parser.cc"
    break;

  case 750: // $@118: %empty
#line 2599 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4148 "dhcp4_parser.cc"
    break;

  case 751: // dep_qualifying_suffix: "qualifying-suffix" $@118 ":" "constant string"
#line 2602 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4158 "dhcp4_parser.cc"
    break;

  case 752: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2609 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4168 "dhcp4_parser.cc"
    break;

  case 753: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2616 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4178 "dhcp4_parser.cc"
    break;

  case 754: // $@119: %empty
#line 2623 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4187 "dhcp4_parser.cc"
    break;

  case 755: // dep_replace_client_name: "replace-client-name" $@119 ":" ddns_replace_client_name_value
#line 2626 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4196 "dhcp4_parser.cc"
    break;

  case 756: // $@120: %empty
#line 2632 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4205 "dhcp4_parser.cc"
    break;

  case 757: // dep_generated_prefix: "generated-prefix" $@120 ":" "constant string"
#line 2635 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4215 "dhcp4_parser.cc"
    break;

  case 758: // $@121: %empty
#line 2642 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4224 "dhcp4_parser.cc"
    break;

  case 759: // dep_hostname_char_set: "hostname-char-set" $@121 ":" "constant string"
#line 2645 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4234 "dhcp4_parser.cc"
    break;

  case 760: // $@122: %empty
#line 2652 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4243 "dhcp4_parser.cc"
    break;

  case 761: // dep_hostname_char_replacement: "hostname-char-replacement" $@122 ":" "constant string"
#line 2655 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4253 "dhcp4_parser.cc"
    break;

  case 762: // $@123: %empty
#line 2664 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4265 "dhcp4_parser.cc"
    break;

  case 763: // config_control: "config-control" $@123 ":" "{" config_control_params "}"
#line 2670 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4275 "dhcp4_parser.cc"
    break;

  case 764: // $@124: %empty
#line 2676 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4285 "dhcp4_parser.cc"
    break;

  case 765: // sub_config_control: "{" $@124 config_control_params "}"
#line 2680 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4294 "dhcp4_parser.cc"
    break;

  case 768: // config_control_params: config_control_params ","
#line 2688 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4302 "dhcp4_parser.cc"
    break;

  case 771: // $@125: %empty
#line 2698 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4314 "dhcp4_parser.cc"
    break;

  case 772: // config_databases: "config-databases" $@125 ":" "[" database_list "]"
#line 2704 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4323 "dhcp4_parser.cc"
    break;

  case 773: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2709 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4333 "dhcp4_parser.cc"
    break;

  case 774: // $@126: %empty
#line 2717 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4345 "dhcp4_parser.cc"
    break;

  case 775: // loggers: "loggers" $@126 ":" "[" loggers_entries "]"
#line 2723 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4354 "dhcp4_parser.cc"
    break;

  case 778: // loggers_entries: loggers_entries ","
#line 2732 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4362 "dhcp4_parser.cc"
    break;

  case 779: // $@127: %empty
#line 2738 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4372 "dhcp4_parser.cc"
    break;

  case 780: // logger_entry: "{" $@127 logger_params "}"
#line 2742 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4380 "dhcp4_parser.cc"
    break;

  case 783: // logger_params: logger_params ","
#line 2748 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4388 "dhcp4_parser.cc"
    break;

  case 791: // debuglevel: "debuglevel" ":" "integer"
#line 2762 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4398 "dhcp4_parser.cc"
    break;

  case 792: // $@128: %empty
#line 2768 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4407 "dhcp4_parser.cc"
    break;

  case 793: // severity: "severity" $@128 ":" "constant string"
#line 2771 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4417 "dhcp4_parser.cc"
    break;

  case 794: // $@129: %empty
#line 2777 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4429 "dhcp4_parser.cc"
    break;

  case 795: // output_options_list: "output_options" $@129 ":" "[" output_options_list_content "]"
#line 2783 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4438 "dhcp4_parser.cc"
    break;

  case 798: // output_options_list_content: output_options_list_content ","
#line 2790 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4446 "dhcp4_parser.cc"
    break;

  case 799: // $@130: %empty
#line 2795 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4456 "dhcp4_parser.cc"
    break;

  case 800: // output_entry: "{" $@130 output_params_list "}"
#line 2799 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4464 "dhcp4_parser.cc"
    break;

  case 803: // output_params_list: output_params_list ","
#line 2805 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4472 "dhcp4_parser.cc"
    break;

  case 809: // $@131: %empty
#line 2817 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4481 "dhcp4_parser.cc"
    break;

  case 810: // output: "output" $@131 ":" "constant string"
#line 2820 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4491 "dhcp4_parser.cc"
    break;

  case 811: // flush: "flush" ":" "boolean"
#line 2826 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4501 "dhcp4_parser.cc"
    break;

  case 812: // maxsize: "maxsize" ":" "integer"
#line 2832 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4511 "dhcp4_parser.cc"
    break;

  case 813: // maxver: "maxver" ":" "integer"
#line 2838 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4521 "dhcp4_parser.cc"
    break;

  case 814: // $@132: %empty
#line 2844 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4530 "dhcp4_parser.cc"
    break;

  case 815: // pattern: "pattern" $@132 ":" "constant string"
#line 2847 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4540 "dhcp4_parser.cc"
    break;

  case 816: // $@133: %empty
#line 2853 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4552 "dhcp4_parser.cc"
    break;

  case 817: // compatibility: "compatibility" $@133 ":" "{" compatibility_params "}"
#line 2859 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4561 "dhcp4_parser.cc"
    break;

  case 820: // compatibility_params: compatibility_params ","
#line 2866 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4569 "dhcp4_parser.cc"
    break;

  case 824: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2876 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4579 "dhcp4_parser.cc"
    break;

  case 825: // ignore-rai-link-selection: "ignore-rai-link-selection" ":" "boolean"
#line 2882 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4589 "dhcp4_parser.cc"
    break;


#line 4593 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -962;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     419,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,    48,    40,    37,    53,   105,   112,
     115,   127,   147,   149,   159,   169,   207,   211,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,    40,  -150,    61,   116,   146,   322,
     -37,   554,   -25,   215,   118,   -61,   434,   151,  -962,    80,
      96,   101,   219,   239,  -962,    30,  -962,  -962,  -962,  -962,
     250,   274,   276,  -962,  -962,  -962,  -962,  -962,  -962,   285,
     298,   310,   317,   326,   347,   359,   392,   402,   406,   412,
    -962,   413,   414,   416,   417,   418,  -962,  -962,  -962,   427,
     428,   430,  -962,  -962,  -962,   435,  -962,  -962,  -962,  -962,
     437,   438,   442,  -962,  -962,  -962,  -962,  -962,   443,  -962,
    -962,  -962,  -962,  -962,  -962,   449,   452,   456,  -962,  -962,
     458,  -962,    32,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
     459,   461,   462,   463,  -962,    43,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,   464,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
      47,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,    75,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,   352,   467,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,   471,
    -962,  -962,   476,  -962,  -962,  -962,   479,  -962,  -962,   481,
     489,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,   491,   497,  -962,  -962,  -962,  -962,
     494,   501,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,    85,  -962,  -962,  -962,   502,  -962,
    -962,   503,  -962,   504,   505,  -962,  -962,   509,   511,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,    86,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,   512,    93,  -962,  -962,  -962,  -962,
      40,    40,  -962,   234,   513,  -962,  -962,   514,   515,   516,
     314,   324,   325,   523,   524,   530,   531,   532,   535,   120,
     336,   337,   342,   343,   345,   299,   348,   349,   354,   355,
     553,   360,   362,   363,   365,   366,   558,   571,   573,   371,
     373,   376,   580,   581,   598,   398,   600,   601,   602,   603,
     420,   421,   422,   619,   620,   621,   622,   626,   426,   628,
     632,   633,   635,   636,   637,   439,   441,   445,   638,   640,
    -962,   116,  -962,   641,   645,   646,   446,   447,   429,   450,
     146,  -962,   652,   655,   661,   662,   663,   664,   468,   670,
     671,   679,   322,  -962,   685,   -37,  -962,   697,   698,   699,
     700,   711,   712,   713,   714,  -962,   554,  -962,   717,   718,
     518,   724,   725,   726,   525,  -962,   215,   727,   528,   533,
    -962,   118,   733,   735,   135,  -962,   534,   738,   742,   542,
     745,   545,   547,   749,   750,   548,   549,   753,   756,   757,
     758,   434,  -962,   759,   559,   151,  -962,  -962,  -962,   761,
     760,   762,   763,   764,  -962,  -962,  -962,   562,   564,   568,
     766,   767,   770,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,   572,  -962,  -962,  -962,  -962,  -962,
     -96,   574,   575,  -962,  -962,  -962,   772,   775,   776,  -962,
     777,   778,   579,    63,  -962,  -962,  -962,   779,   781,   782,
     783,   784,  -962,   785,   786,   787,   788,   585,   586,  -962,
    -962,  -962,   791,   790,  -962,   793,   353,   357,  -962,  -962,
    -962,  -962,  -962,   595,   596,   597,   797,   599,   604,  -962,
     793,   605,   799,  -962,   606,  -962,   793,   607,   608,   609,
     610,   611,   612,   613,  -962,   614,   615,  -962,   616,   617,
     618,  -962,  -962,   623,  -962,  -962,  -962,   624,   778,  -962,
    -962,   625,   627,  -962,   629,  -962,  -962,    35,   654,  -962,
    -962,   -96,   631,   634,   639,  -962,   802,  -962,  -962,    40,
     116,   151,   146,   385,  -962,  -962,  -962,   289,   289,   817,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,   818,
     819,   823,   825,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,   111,   829,   830,   832,   160,    13,   161,   122,   434,
    -962,  -962,   833,   -98,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,   834,  -962,  -962,  -962,  -962,
     284,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,   817,
    -962,   106,   121,   129,  -962,  -962,   132,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,   838,   840,   841,   842,   843,   844,
     845,  -962,   846,  -962,  -962,  -962,  -962,  -962,   152,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,   198,  -962,
     847,   848,  -962,  -962,   849,   851,  -962,  -962,   850,   854,
    -962,  -962,   852,   856,  -962,  -962,   855,   857,  -962,  -962,
    -962,  -962,  -962,  -962,    79,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,    92,  -962,  -962,   858,   859,  -962,  -962,   860,
     862,  -962,   863,   864,   865,   866,   867,   868,   199,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,   869,   870,   871,  -962,
     220,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,   249,  -962,  -962,  -962,   872,  -962,   873,  -962,
    -962,  -962,   252,  -962,  -962,  -962,  -962,  -962,   253,  -962,
     138,  -962,   874,   875,  -962,   259,  -962,  -962,  -962,   648,
    -962,   876,   877,  -962,  -962,  -962,  -962,   878,   879,  -962,
    -962,  -962,   880,   883,   385,  -962,   884,   885,   886,   887,
     658,   674,   678,   686,   687,   689,   690,   892,   692,   894,
     895,   896,   897,   289,  -962,  -962,   289,  -962,   817,   322,
    -962,   818,   215,  -962,   819,   118,  -962,   823,   630,  -962,
     825,   111,  -962,   254,   829,  -962,   554,  -962,   830,   -61,
    -962,   832,   701,   702,   703,   704,   705,   706,   160,  -962,
     695,   708,   709,    13,  -962,   899,   900,   161,  -962,   710,
     901,   715,   912,   122,  -962,  -962,   272,   833,  -962,   720,
     729,   -98,  -962,  -962,   934,   949,   -37,  -962,   834,   951,
    -962,  -962,   773,   792,  -962,   341,   811,   861,   881,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,   340,  -962,   882,   888,
     889,   890,  -962,   268,  -962,   269,  -962,   953,  -962,   966,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,   320,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,   976,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,   974,
     954,  -962,  -962,  -962,  -962,  -962,   975,  -962,   321,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,   891,   893,  -962,  -962,   898,  -962,    40,  -962,  -962,
     982,  -962,  -962,  -962,  -962,  -962,   356,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,   902,   358,  -962,   793,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,   630,  -962,   987,   853,  -962,   254,  -962,  -962,  -962,
    -962,  -962,  -962,   990,   903,  1047,   272,  -962,  -962,  -962,
    -962,  -962,   905,  -962,  -962,  1048,  -962,   906,  -962,  -962,
    1049,  -962,  -962,   300,  -962,    98,  1049,  -962,  -962,  1050,
    1055,  1057,  -962,   364,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  1058,   904,   907,   908,  1059,    98,  -962,   910,  -962,
    -962,  -962,   911,  -962,  -962,  -962
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
     713,    25,   764,    27,    46,    39,     0,     0,     0,     0,
       0,   601,     0,   503,   542,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   762,   177,   210,
       0,     0,     0,   621,   623,   625,   208,   221,   223,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,     0,     0,     0,     0,   154,   161,   163,     0,
       0,     0,   355,   490,   531,     0,   438,   586,   588,   431,
       0,     0,     0,   288,   649,   590,   317,   338,     0,   303,
     680,   694,   711,   167,   169,     0,     0,     0,   774,   816,
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
     554,   334,   336,   331,     0,   328,   332,   333,     0,   750,
     737,     0,   740,     0,     0,   744,   748,     0,     0,   754,
     756,   758,   760,   735,   733,   734,     0,   715,   718,   719,
     720,   721,   722,   723,   724,   725,   730,   726,   727,   728,
     729,   731,   732,   771,     0,     0,   766,   769,   770,    45,
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
       0,   717,   714,     0,     0,   768,   765,    49,    41,     0,
       0,     0,     0,     0,   148,   149,   150,     0,     0,     0,
       0,     0,     0,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,   172,   173,   151,   152,   153,
       0,     0,     0,   165,   166,   171,     0,     0,     0,   147,
       0,     0,     0,     0,   428,   429,   430,     0,     0,     0,
       0,     0,   679,     0,     0,     0,     0,     0,     0,   174,
     175,   176,     0,     0,    68,     0,     0,     0,   204,   205,
     206,   207,   180,     0,     0,     0,     0,     0,     0,   437,
       0,     0,     0,   367,     0,   575,     0,     0,     0,     0,
       0,     0,     0,     0,   604,     0,     0,   519,     0,     0,
       0,   530,   506,     0,   561,   562,   545,     0,     0,   329,
     736,     0,     0,   739,     0,   742,   743,     0,     0,   752,
     753,     0,     0,     0,     0,   716,     0,   773,   767,     0,
       0,     0,     0,     0,   622,   624,   626,     0,     0,   225,
     146,   156,   157,   158,   159,   160,   155,   162,   164,   357,
     494,   533,   440,    38,   587,   589,   433,   434,   435,   436,
     432,     0,     0,   592,   319,     0,     0,     0,     0,     0,
     168,   170,     0,     0,    51,   195,   198,   199,   197,   202,
     203,   201,   417,   419,   421,   565,   415,   423,   427,   425,
       0,   585,   644,   632,   634,   638,   636,   642,   640,   628,
     522,   267,   526,   524,   529,   558,   335,   337,   751,   738,
     741,   746,   747,   745,   749,   755,   757,   759,   761,   225,
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
       0,   305,   308,   309,   310,   311,   312,   690,   692,   689,
     687,   688,     0,   682,   685,   686,     0,   706,     0,   709,
     702,   703,     0,   696,   699,   700,   701,   704,     0,   779,
       0,   776,     0,     0,   823,     0,   818,   821,   822,    53,
     570,     0,   566,   567,   629,   647,   648,     0,     0,    62,
     763,   178,     0,     0,   214,   211,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   234,   209,   222,     0,   224,   229,     0,
     356,   361,   503,   491,   498,   542,   532,   537,     0,   439,
     444,   292,   289,   656,   653,   650,   601,   591,   596,     0,
     318,   323,     0,     0,     0,     0,     0,     0,   342,   339,
       0,     0,     0,   307,   304,     0,     0,   684,   681,     0,
       0,     0,     0,   698,   695,   712,     0,   778,   775,     0,
       0,   820,   817,    55,     0,    54,     0,   564,   569,     0,
     646,   772,     0,     0,   213,     0,     0,     0,     0,   265,
     268,   269,   270,   271,   272,   273,     0,   279,     0,     0,
       0,     0,   233,     0,   228,     0,   360,     0,   497,     0,
     536,   489,   468,   469,   470,   453,   454,   473,   474,   475,
     476,   477,   456,   457,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,   450,   451,   452,   466,   467,
     463,   464,   465,   462,     0,   447,   455,   471,   472,   458,
     459,   460,   461,   443,   291,   676,     0,   671,   672,   673,
     674,   675,   664,   665,   669,   670,   666,   667,   668,     0,
     657,   658,   661,   662,   663,   652,     0,   595,     0,   322,
     349,   350,   351,   352,   353,   354,   341,   314,   315,   316,
     306,     0,     0,   683,   705,     0,   708,     0,   697,   794,
       0,   792,   790,   784,   788,   789,     0,   781,   786,   787,
     785,   777,   824,   825,   819,    52,    57,     0,   568,     0,
     218,   220,   256,   257,   258,   255,   260,   262,   264,   276,
     277,   278,   275,   281,   283,   285,   287,   231,   363,   500,
     539,   449,   446,     0,     0,   655,   660,   598,   325,   691,
     693,   707,   710,     0,     0,     0,   783,   780,    56,   571,
     630,   448,     0,   678,   659,     0,   791,     0,   782,   677,
       0,   793,   799,     0,   796,     0,   798,   795,   809,     0,
       0,     0,   814,     0,   801,   804,   805,   806,   807,   808,
     797,     0,     0,     0,     0,     0,   803,   800,     0,   811,
     812,   813,     0,   802,   810,   815
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,   -52,  -962,  -574,  -962,   386,
    -962,  -962,  -962,  -962,  -962,  -962,  -635,  -962,  -962,  -962,
     -67,  -962,  -962,  -962,  -962,  -962,  -962,  -962,   367,   577,
       0,    10,    11,   -30,    18,    21,    28,    31,    33,    34,
    -962,  -962,  -962,  -962,  -962,    38,    39,    41,    44,    46,
      49,  -962,   375,    51,  -962,    52,  -962,    54,    56,    57,
    -962,    59,  -962,    62,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,   368,   569,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,   117,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,   283,  -962,    95,  -962,  -695,   102,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,   -63,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
      83,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,    65,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,    76,  -962,  -962,
    -962,    77,   536,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
      71,  -962,  -962,  -962,  -962,  -962,  -962,  -961,  -962,  -962,
    -962,   100,  -962,  -962,  -962,   103,   576,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -960,  -962,   -65,  -962,   -34,
    -962,    64,    67,    69,    70,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,    94,  -962,  -962,  -118,   -46,  -962,  -962,  -962,
    -962,  -962,   107,  -962,  -962,  -962,   108,  -962,   551,  -962,
     -50,  -962,  -962,  -962,  -962,  -962,   -42,  -962,  -962,  -962,
    -962,  -962,   -28,  -962,  -962,  -962,   109,  -962,  -962,  -962,
     104,  -962,   557,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,    66,  -962,  -962,  -962,    81,   584,
    -962,  -962,   -51,  -962,   -12,  -962,   -35,  -962,  -962,  -962,
     123,  -962,  -962,  -962,   124,  -962,   590,   -55,  -962,   -40,
    -962,    -1,  -962,   369,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -958,  -962,  -962,  -962,  -962,  -962,   113,  -962,  -962,
    -962,  -106,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
      84,  -962,  -962,  -962,  -962,  -962,  -962,  -962,    99,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,   379,
     563,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
     424,   538,  -962,  -962,  -962,  -962,  -962,  -962,   110,  -962,
    -962,   -97,  -962,  -962,  -962,  -962,  -962,  -962,  -113,  -962,
    -962,  -130,  -962,  -962,  -962,  -962,  -962,  -962,  -962,  -962,
    -962,  -962,    97,  -962,  -962
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
     438,   840,   841,   842,   976,   818,   819,   820,   956,  1185,
     821,   957,   822,   958,   823,   959,   824,   825,   529,   826,
     827,   828,   829,   830,   831,   832,   967,  1192,   833,   834,
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
     517,   292,   511,   947,   209,   474,   872,   873,   993,  1129,
    1130,  1131,  1132,  1133,  1203,  1134,   210,   211,   480,   912,
     913,   914,  1015,   915,  1016,   212,   481,   922,   923,   924,
     925,  1020,   926,   927,  1022,   213,   482,    61,    76,   396,
     397,   398,   399,   548,   400,   401,   550,   402,   403,   404,
     553,   783,   405,   554,   406,   547,   407,   408,   409,   557,
     410,   558,   411,   559,   412,   560,   214,   427,    63,    77,
     415,   416,   417,   563,   418,   215,   488,   930,   931,  1026,
    1166,  1167,  1168,  1169,  1215,  1170,  1213,  1233,  1234,  1235,
    1243,  1244,  1245,  1251,  1246,  1247,  1248,  1249,  1255,   216,
     489,   935,   936,   937,   938
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     151,   224,   246,   294,   311,   295,   337,   356,   373,   393,
     338,   357,    78,   838,   289,   758,   318,   234,   286,   301,
     313,   762,   351,   369,   358,   394,   329,  1096,  1097,   290,
    1112,   319,   359,   425,   288,   491,   296,   723,   426,   250,
     492,   284,   297,   312,    40,    29,   500,    30,    28,    31,
     512,   501,   124,   781,    81,   513,   235,   287,   302,   314,
      42,   352,   370,   123,   395,   293,   127,   128,   291,   247,
     320,    84,   371,   372,   711,   712,   713,   714,   515,   248,
     249,   243,   991,   516,   244,   992,   419,   251,   544,   561,
     252,   932,   933,   545,   562,   994,   565,   253,   995,   420,
     254,   566,   255,   256,   723,   421,   150,   257,   258,   491,
     259,   715,    44,   260,   949,   261,   127,   128,   262,    46,
     263,   264,    48,   265,   565,   266,   267,    87,   268,   950,
      88,   269,   500,   279,    50,   954,   280,   951,   281,   282,
     955,  1027,    89,   150,  1028,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    52,   973,    54,   896,   897,   898,
     974,   217,   218,   413,   414,   219,    56,   150,   220,   221,
     222,   223,   726,   727,   728,   729,    58,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   973,  1008,   782,   123,   124,   975,  1009,   331,   353,
     332,   333,   354,   355,    60,   125,   126,   150,    62,   127,
     128,   127,   128,  1013,   129,   127,   128,   422,  1014,   130,
     131,   132,   133,   134,   859,   860,   861,   862,   135,   863,
    1096,  1097,   423,  1112,    32,    33,    34,    35,   136,   127,
     128,   137,  1017,   330,   430,  1023,   561,  1018,   138,   139,
    1024,  1025,  1031,   140,   127,   128,   141,  1032,   371,   372,
     142,   973,   512,   916,   917,   918,  1197,  1198,   431,  1238,
     432,  1063,  1239,  1240,  1241,  1242,    93,    94,    95,   439,
     143,   144,   145,   146,   147,   148,   882,   883,   884,   885,
     886,   887,   440,  1236,   149,   331,  1237,   332,   333,   907,
     908,   334,   335,   336,   441,    99,   100,   101,   127,   128,
     150,   442,   150,  1201,   544,   583,   919,   800,  1202,  1208,
     443,   801,   802,   803,   804,   805,   806,   807,   808,   809,
     810,   811,   123,   124,   331,   812,   813,   814,   815,   816,
     150,   444,    91,    92,    93,    94,    95,   127,   128,  1216,
     525,   515,   331,   445,  1217,   150,  1219,  1256,   567,   568,
     746,   747,  1257,  1115,  1116,   127,   128,   749,   750,   331,
    1182,  1183,  1184,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,  1189,  1190,  1191,   446,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   447,   236,   237,   238,
     448,   124,   794,   795,   310,   944,   449,   451,   452,   150,
     453,   454,   455,   239,   151,   127,   128,   240,   241,   242,
     129,   459,   460,   224,   461,   130,   131,   132,   569,   465,
     243,   470,   471,   244,   135,   246,   472,   478,   294,   234,
     295,   245,  1159,   485,  1160,  1161,   486,   289,   150,   311,
     487,   286,   490,   496,   301,   497,   498,   499,   508,   337,
     526,   318,   290,   338,   356,   313,   150,   288,   357,   527,
     530,   296,   250,   534,   284,   351,   319,   297,   235,   535,
     369,   358,   536,   150,   393,   538,   143,   144,   312,   359,
     287,   539,   540,   302,   541,   589,   546,   549,   551,   552,
     394,   291,   247,   555,   314,   556,   564,   570,   571,   572,
     573,   574,   248,   249,   352,   320,   150,   577,   578,   370,
     251,   575,   576,   252,   579,   580,   581,   127,   128,   582,
     253,   584,   585,   254,  1220,   255,   256,   586,   587,   395,
     257,   258,   588,   259,   590,   591,   260,   594,   261,   592,
     593,   262,   600,   263,   264,   595,   265,   596,   266,   267,
     597,   268,   598,   599,   269,   601,   279,   602,   603,   280,
     604,   281,   282,   605,   606,   607,    93,    94,    95,   378,
     379,   380,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   608,   609,   610,   611,   612,   613,   391,   392,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   617,   618,   619,   620,   614,   615,   616,
     621,   622,   623,   151,   640,   224,   624,   625,   150,   626,
     627,   628,   632,   124,   633,   635,   629,   790,   630,   636,
     637,   234,   631,   638,   639,   641,   643,   127,   128,   644,
      91,    92,    93,    94,    95,   645,   646,   647,   648,   899,
     909,   303,   393,   649,   650,   651,   934,   304,   305,   306,
     307,   308,   309,   652,   310,   905,   910,   920,   394,   654,
     235,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   656,   657,   658,   659,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   660,   661,   662,   663,   124,
     331,   665,   666,   667,   906,   911,   921,   395,   668,   669,
     670,   673,   671,   127,   128,   674,   241,   677,   129,   678,
     675,   680,   681,   130,   131,   132,   682,   683,   243,   684,
     685,   244,   686,   687,   688,   689,   690,   691,   150,   245,
     692,   693,   694,   696,   697,   699,   704,   700,   705,   701,
     702,   703,   706,   707,   708,   709,   710,   719,   717,   718,
     720,   721,   722,   725,   731,    30,   732,   733,   734,   740,
     741,   735,   736,   737,   738,   739,   742,   743,   744,   752,
     753,   754,   755,   756,   143,   144,   760,   789,   757,   759,
     761,   763,   764,   765,   766,   767,   768,   769,   770,   771,
     772,   773,   774,   784,   839,   843,   847,   775,   776,   778,
     851,   779,   855,   780,   150,   786,   871,   874,   787,   878,
     929,   940,   960,   788,   961,   962,   963,   964,   965,   966,
     968,   978,  1033,   977,   981,   980,   983,   984,   986,   987,
     990,   989,   998,  1049,   997,  1001,  1000,  1002,  1003,  1004,
    1005,  1006,  1007,  1010,  1011,  1012,  1019,  1021,  1029,  1030,
    1038,  1050,  1037,  1051,  1042,  1041,  1040,  1043,  1045,  1046,
    1047,  1048,  1053,  1052,  1054,  1055,  1056,  1057,  1058,  1059,
    1060,  1061,  1147,  1151,  1152,  1155,  1140,  1141,  1142,  1143,
    1144,  1145,   246,  1148,  1149,   337,  1157,  1154,   356,   338,
    1156,  1071,   357,  1098,   289,  1095,  1117,  1172,   286,   311,
    1121,   351,   373,  1109,   369,   358,  1173,  1107,  1126,   290,
    1175,   318,  1124,   359,   288,   313,   899,  1122,  1110,   250,
     909,   284,  1176,  1127,  1099,  1179,   319,  1206,  1075,  1162,
    1106,  1199,   905,  1163,   934,  1123,   910,   287,   312,   294,
     352,   295,   920,   370,  1200,  1164,  1108,  1180,   291,   247,
    1204,  1125,  1205,  1207,   314,   301,  1214,  1111,  1072,   248,
     249,  1222,  1128,  1118,  1225,   320,  1181,   251,  1073,  1074,
     252,   906,   296,  1119,  1120,   911,  1076,   253,   297,  1077,
     254,   921,   255,   256,  1165,  1186,  1078,   257,   258,  1079,
     259,  1080,  1081,   260,   302,   261,  1082,  1083,   262,  1084,
     263,   264,  1085,   265,  1086,   266,   267,  1087,   268,  1088,
    1089,   269,  1090,   279,  1091,  1092,   280,  1093,   281,   282,
    1094,  1227,  1100,  1230,  1252,  1101,  1232,  1102,  1103,  1253,
    1223,  1254,  1258,  1262,   777,  1187,   785,   791,   634,   642,
     793,  1044,   948,  1064,  1114,  1062,  1138,  1139,  1150,  1146,
     679,  1066,  1065,  1221,  1113,  1188,  1193,   672,   653,  1069,
    1067,  1068,  1194,  1195,  1196,  1209,  1070,  1210,   676,   655,
    1224,  1153,  1211,   698,  1178,  1212,  1218,  1135,  1226,  1229,
    1231,  1259,  1260,  1261,  1264,  1265,   664,  1177,   928,  1228,
    1136,  1137,  1158,  1250,   695,   792,  1263,     0,  1174,   945,
       0,     0,     0,     0,  1071,     0,  1098,  1171,  1095,  1117,
       0,     0,     0,  1121,     0,     0,  1109,     0,     0,  1162,
    1107,  1126,     0,  1163,     0,  1124,     0,     0,     0,     0,
    1122,  1110,     0,     0,     0,  1164,  1127,  1099,     0,     0,
       0,  1075,     0,  1106,     0,     0,     0,     0,  1123,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1108,
       0,     0,     0,     0,  1125,     0,     0,     0,     0,     0,
    1111,  1072,     0,     0,  1165,  1128,  1118,     0,     0,     0,
       0,  1073,  1074,     0,     0,     0,  1119,  1120,     0,  1076,
       0,     0,  1077,     0,     0,     0,     0,     0,     0,  1078,
       0,     0,  1079,     0,  1080,  1081,     0,     0,     0,  1082,
    1083,     0,  1084,     0,     0,  1085,     0,  1086,     0,     0,
    1087,     0,  1088,  1089,     0,  1090,     0,  1091,  1092,     0,
    1093,     0,     0,  1094,     0,  1100,     0,     0,  1101,     0,
    1102,  1103
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   708,    69,   650,    71,    68,    69,    70,
      71,   656,    73,    74,    74,    76,    72,   988,   988,    69,
     988,    71,    74,     3,    69,     3,    70,   611,     8,    69,
       8,    69,    70,    71,     7,     5,     3,     7,     0,     9,
       3,     8,    89,    18,   204,     8,    68,    69,    70,    71,
       7,    73,    74,    88,    76,   102,   103,   104,    69,    69,
      71,    10,   133,   134,   170,   171,   172,   173,     3,    69,
      69,   118,     3,     8,   121,     6,     6,    69,     3,     3,
      69,   189,   190,     8,     8,     3,     3,    69,     6,     3,
      69,     8,    69,    69,   678,     4,   204,    69,    69,     3,
      69,   207,     7,    69,     8,    69,   103,   104,    69,     7,
      69,    69,     7,    69,     3,    69,    69,    11,    69,     8,
      14,    69,     3,    69,     7,     3,    69,     8,    69,    69,
       8,     3,    26,   204,     6,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     7,     3,     7,   144,   145,   146,
       8,    15,    16,    12,    13,    19,     7,   204,    22,    23,
      24,    25,   109,   110,   111,   112,     7,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,     3,     3,   168,    88,    89,     8,     8,    90,    91,
      92,    93,    94,    95,     7,    99,   100,   204,     7,   103,
     104,   103,   104,     3,   108,   103,   104,     8,     8,   113,
     114,   115,   116,   117,   123,   124,   125,   126,   122,   128,
    1201,  1201,     3,  1201,   204,   205,   206,   207,   132,   103,
     104,   135,     3,    38,     4,     3,     3,     8,   142,   143,
       8,     8,     3,   147,   103,   104,   150,     8,   133,   134,
     154,     3,     3,   151,   152,   153,     8,     8,     4,   181,
       4,   976,   184,   185,   186,   187,    32,    33,    34,     4,
     174,   175,   176,   177,   178,   179,   136,   137,   138,   139,
     140,   141,     4,     3,   188,    90,     6,    92,    93,   148,
     149,    96,    97,    98,     4,    61,    62,    63,   103,   104,
     204,     4,   204,     3,     3,   205,   204,    38,     8,     8,
       4,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    88,    89,    90,    56,    57,    58,    59,    60,
     204,     4,    30,    31,    32,    33,    34,   103,   104,     3,
       8,     3,    90,     4,     8,   204,     8,     3,   420,   421,
      17,    18,     8,   119,   120,   103,   104,    20,    21,    90,
      39,    40,    41,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    53,    54,    55,     4,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     4,    85,    86,    87,
       4,    89,    27,    28,   130,   131,     4,     4,     4,   204,
       4,     4,     4,   101,   491,   103,   104,   105,   106,   107,
     108,     4,     4,   500,     4,   113,   114,   115,   204,     4,
     118,     4,     4,   121,   122,   512,     4,     4,   515,   500,
     515,   129,   180,     4,   182,   183,     4,   512,   204,   526,
       4,   512,     4,     4,   515,     4,     4,     4,     4,   536,
       3,   526,   512,   536,   541,   526,   204,   512,   541,     8,
       4,   515,   512,     4,   512,   536,   526,   515,   500,     8,
     541,   541,     3,   204,   561,     4,   174,   175,   526,   541,
     512,     4,     8,   515,     3,   206,     4,     4,     4,     4,
     561,   512,   512,     4,   526,     4,     4,     4,     4,     4,
       4,   207,   512,   512,   536,   526,   204,     4,     4,   541,
     512,   207,   207,   512,     4,     4,     4,   103,   104,     4,
     512,   205,   205,   512,  1179,   512,   512,   205,   205,   561,
     512,   512,   207,   512,   206,   206,   512,     4,   512,   205,
     205,   512,     4,   512,   512,   205,   512,   205,   512,   512,
     207,   512,   207,   207,   512,     4,   512,     4,   207,   512,
     207,   512,   512,   207,     4,     4,    32,    33,    34,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,     4,   205,     4,     4,     4,     4,   174,   175,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,     4,     4,     4,     4,   207,   207,   207,
       4,   205,     4,   700,   205,   702,     4,     4,   204,     4,
       4,     4,     4,    89,     4,     4,   207,   699,   207,     4,
       4,   702,   207,   207,   207,   205,     4,   103,   104,     4,
      30,    31,    32,    33,    34,     4,     4,     4,     4,   736,
     737,   117,   739,   205,     4,     4,   743,   123,   124,   125,
     126,   127,   128,     4,   130,   736,   737,   738,   739,     4,
     702,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,     4,     4,     4,     4,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,     4,     4,     4,     4,    89,
      90,     4,     4,   205,   736,   737,   738,   739,     4,     4,
       4,     4,   207,   103,   104,   207,   106,     4,   108,     4,
     207,   207,     4,   113,   114,   115,     4,   205,   118,     4,
     205,   121,   205,     4,     4,   207,   207,     4,   204,   129,
       4,     4,     4,     4,   205,     4,   204,     7,   204,     7,
       7,     7,   204,     7,     7,     5,   204,     5,   204,   204,
       5,     5,     5,   204,     5,     7,     5,     5,     5,   204,
     204,     7,     7,     7,     7,     7,     5,     7,     5,   204,
     204,   204,     5,   204,   174,   175,     7,     5,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   169,     7,     7,     7,   204,   204,   204,
       7,   204,     7,   204,   204,   204,     7,     7,   204,     7,
       7,     7,     4,   204,     4,     4,     4,     4,     4,     4,
       4,     3,   204,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     3,   205,     6,     3,     6,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   207,     6,   205,     4,     6,     8,     4,     4,     4,
       4,     4,   205,   207,   205,   205,     4,   205,     4,     4,
       4,     4,   207,     4,     4,     4,   205,   205,   205,   205,
     205,   205,   979,   205,   205,   982,     4,   207,   985,   982,
     205,   988,   985,   988,   979,   988,   993,   207,   979,   996,
     993,   982,   999,   988,   985,   985,   207,   988,   993,   979,
       6,   996,   993,   985,   979,   996,  1013,   993,   988,   979,
    1017,   979,     3,   993,   988,     4,   996,     3,   988,  1026,
     988,     8,  1013,  1026,  1031,   993,  1017,   979,   996,  1036,
     982,  1036,  1023,   985,     8,  1026,   988,   204,   979,   979,
       4,   993,     8,     8,   996,  1036,     4,   988,   988,   979,
     979,     4,   993,   993,     4,   996,   204,   979,   988,   988,
     979,  1013,  1036,   993,   993,  1017,   988,   979,  1036,   988,
     979,  1023,   979,   979,  1026,   204,   988,   979,   979,   988,
     979,   988,   988,   979,  1036,   979,   988,   988,   979,   988,
     979,   979,   988,   979,   988,   979,   979,   988,   979,   988,
     988,   979,   988,   979,   988,   988,   979,   988,   979,   979,
     988,     4,   988,     5,     4,   988,     7,   988,   988,     4,
     207,     4,     4,     4,   678,   204,   691,   700,   491,   500,
     702,   954,   789,   978,   991,   973,   999,  1001,  1013,  1008,
     544,   981,   979,  1201,   990,   204,   204,   536,   512,   985,
     982,   984,   204,   204,   204,   204,   987,   204,   541,   515,
    1206,  1017,   204,   565,  1038,  1157,   204,   994,   205,   204,
     204,   207,   205,   205,   204,   204,   526,  1036,   739,  1216,
     996,   998,  1023,  1236,   561,   701,  1256,    -1,  1031,   760,
      -1,    -1,    -1,    -1,  1201,    -1,  1201,  1027,  1201,  1206,
      -1,    -1,    -1,  1206,    -1,    -1,  1201,    -1,    -1,  1216,
    1201,  1206,    -1,  1216,    -1,  1206,    -1,    -1,    -1,    -1,
    1206,  1201,    -1,    -1,    -1,  1216,  1206,  1201,    -1,    -1,
      -1,  1201,    -1,  1201,    -1,    -1,    -1,    -1,  1206,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1201,
      -1,    -1,    -1,    -1,  1206,    -1,    -1,    -1,    -1,    -1,
    1201,  1201,    -1,    -1,  1216,  1206,  1206,    -1,    -1,    -1,
      -1,  1201,  1201,    -1,    -1,    -1,  1206,  1206,    -1,  1201,
      -1,    -1,  1201,    -1,    -1,    -1,    -1,    -1,    -1,  1201,
      -1,    -1,  1201,    -1,  1201,  1201,    -1,    -1,    -1,  1201,
    1201,    -1,  1201,    -1,    -1,  1201,    -1,  1201,    -1,    -1,
    1201,    -1,  1201,  1201,    -1,  1201,    -1,  1201,  1201,    -1,
    1201,    -1,    -1,  1201,    -1,  1201,    -1,    -1,  1201,    -1,
    1201,  1201
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,     0,     5,
       7,     9,   204,   205,   206,   207,   223,   224,   225,   230,
       7,   239,     7,   244,     7,   291,     7,   401,     7,   484,
       7,   500,     7,   436,     7,   442,     7,   466,     7,   377,
       7,   565,     7,   596,   231,   226,   240,   245,   292,   402,
     485,   501,   437,   443,   467,   378,   566,   597,   223,   232,
     233,   204,   228,   229,    10,   241,   243,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    88,    89,    99,   100,   103,   104,   108,
     113,   114,   115,   116,   117,   122,   132,   135,   142,   143,
     147,   150,   154,   174,   175,   176,   177,   178,   179,   188,
     204,   238,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   261,   262,   263,   264,
     265,   266,   267,   268,   271,   273,   275,   276,   277,   279,
     281,   282,   283,   284,   285,   286,   287,   305,   307,   315,
     317,   355,   364,   371,   385,   395,   419,   420,   421,   422,
     426,   434,   460,   490,   492,   494,   505,   507,   509,   532,
     544,   545,   553,   563,   594,   603,   627,    15,    16,    19,
      22,    23,    24,    25,   238,   289,   290,   293,   295,   298,
     301,   302,   303,   304,   490,   492,    85,    86,    87,   101,
     105,   106,   107,   118,   121,   129,   238,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   263,   264,   265,
     266,   267,   268,   271,   273,   275,   276,   277,   279,   281,
     403,   404,   405,   407,   409,   411,   413,   415,   417,   419,
     420,   421,   422,   425,   460,   478,   490,   492,   494,   505,
     507,   509,   529,   102,   238,   415,   417,   460,   486,   487,
     488,   490,   492,   117,   123,   124,   125,   126,   127,   128,
     130,   238,   460,   490,   492,   502,   503,   504,   505,   507,
     509,   511,   515,   517,   519,   521,   523,   525,   527,   434,
      38,    90,    92,    93,    96,    97,    98,   238,   335,   444,
     445,   446,   447,   448,   449,   450,   452,   454,   456,   457,
     459,   490,   492,    91,    94,    95,   238,   335,   448,   454,
     468,   469,   470,   471,   472,   474,   475,   476,   477,   490,
     492,   133,   134,   238,   379,   380,   381,   383,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   174,   175,   238,   490,   492,   567,   568,   569,   570,
     572,   573,   575,   576,   577,   580,   582,   584,   585,   586,
     588,   590,   592,    12,    13,   598,   599,   600,   602,     6,
       3,     4,     8,     3,   242,     3,     8,   595,   288,   308,
       4,     4,     4,   506,   508,   510,   306,   316,   318,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     260,     4,     4,     4,     4,     4,   269,   272,   274,     4,
       4,     4,   396,   435,   461,     4,   427,   491,   493,   423,
       4,     4,     4,   356,   533,   495,   372,   386,     4,   365,
     546,   554,   564,   278,   280,     4,     4,     4,   604,   628,
       4,     3,     8,   294,   296,   299,     4,     4,     4,     4,
       3,     8,   408,   410,   412,   479,   406,   414,     4,   418,
     416,   530,     3,     8,   489,     3,     8,   528,   516,   518,
     522,   520,   526,   524,   512,     8,     3,     8,   451,   336,
       4,   455,   453,   458,     4,     8,     3,   473,     4,     4,
       8,     3,   382,   384,     3,     8,     4,   583,   571,     4,
     574,     4,     4,   578,   581,     4,     4,   587,   589,   591,
     593,     3,     8,   601,     4,     3,     8,   223,   223,   204,
       4,     4,     4,     4,   207,   207,   207,     4,     4,     4,
       4,     4,     4,   205,   205,   205,   205,   205,   207,   206,
     206,   206,   205,   205,     4,   205,   205,   207,   207,   207,
       4,     4,     4,   207,   207,   207,     4,     4,     4,   205,
       4,     4,     4,     4,   207,   207,   207,     4,     4,     4,
       4,     4,   205,     4,     4,     4,     4,     4,     4,   207,
     207,   207,     4,     4,   247,     4,     4,     4,   207,   207,
     205,   205,   290,     4,     4,     4,     4,     4,     4,   205,
       4,     4,     4,   404,     4,   487,     4,     4,     4,     4,
       4,     4,     4,     4,   504,     4,     4,   205,     4,     4,
       4,   207,   446,     4,   207,   207,   470,     4,     4,   380,
     207,     4,     4,   205,     4,   205,   205,     4,     4,   207,
     207,     4,     4,     4,     4,   568,     4,   205,   599,     4,
       7,     7,     7,     7,   204,   204,   204,     7,     7,     5,
     204,   170,   171,   172,   173,   207,   270,   204,   204,     5,
       5,     5,     5,   225,   227,   204,   109,   110,   111,   112,
     424,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     204,   204,     5,     7,     5,   234,    17,    18,   297,    20,
      21,   300,   204,   204,   204,     5,   204,   204,   234,   204,
       7,   204,   234,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   227,   204,   204,
     204,    18,   168,   579,   169,   270,   204,   204,   204,     5,
     223,   246,   598,   289,    27,    28,   309,   310,   311,   313,
      38,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    56,    57,    58,    59,    60,   238,   323,   324,
     325,   328,   330,   332,   334,   335,   337,   338,   339,   340,
     341,   342,   343,   346,   347,   349,   351,   353,   323,     7,
     319,   320,   321,     7,   397,   398,   399,     7,   438,   439,
     440,     7,   462,   463,   464,     7,   428,   429,   430,   123,
     124,   125,   126,   128,   357,   358,   359,   360,   361,   362,
     363,     7,   534,   535,     7,   496,   497,   498,     7,   373,
     374,   375,   136,   137,   138,   139,   140,   141,   387,   388,
     389,   390,   391,   392,   393,   394,   144,   145,   146,   238,
     366,   367,   368,   369,   370,   490,   492,   148,   149,   238,
     490,   492,   547,   548,   549,   551,   151,   152,   153,   204,
     490,   492,   555,   556,   557,   558,   560,   561,   567,     7,
     605,   606,   189,   190,   238,   629,   630,   631,   632,   235,
       7,   480,   481,   482,   131,   511,   513,   531,   319,     8,
       8,     8,   312,   314,     3,     8,   326,   329,   331,   333,
       4,     4,     4,     4,     4,     4,     4,   344,     4,   348,
     350,   352,   354,     3,     8,     8,   322,     6,     3,   400,
       6,     3,   441,     6,     3,   465,     6,     3,   431,     6,
       3,     3,     6,   536,     3,     6,   499,     6,     3,   376,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   550,   552,     3,     8,     4,
     559,     4,   562,     3,     8,     8,   607,     3,     6,     4,
       4,     3,     8,   204,   236,   237,   483,     6,     3,   514,
       8,     6,     4,     4,   310,     4,     4,     4,     4,   205,
     207,   205,   207,   205,   205,   205,     4,   205,     4,     4,
       4,     4,   324,   323,   321,   403,   399,   444,   440,   468,
     464,   238,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   263,   264,   265,   266,   267,   268,   271,   273,
     275,   276,   277,   279,   281,   335,   395,   413,   415,   417,
     419,   420,   421,   422,   432,   433,   460,   490,   492,   505,
     507,   509,   529,   430,   358,   119,   120,   238,   248,   249,
     250,   335,   434,   460,   490,   492,   505,   507,   509,   537,
     538,   539,   540,   541,   543,   535,   502,   498,   379,   375,
     205,   205,   205,   205,   205,   205,   388,   207,   205,   205,
     367,     4,     4,   548,   207,     4,   205,     4,   556,   180,
     182,   183,   238,   335,   490,   492,   608,   609,   610,   611,
     613,   606,   207,   207,   630,     6,     3,   486,   482,     4,
     204,   204,    39,    40,    41,   327,   204,   204,   204,    53,
      54,    55,   345,   204,   204,   204,   204,     8,     8,     8,
       8,     3,     8,   542,     4,     8,     3,     8,     8,   204,
     204,   204,   223,   614,     4,   612,     3,     8,   204,     8,
     234,   433,     4,   207,   539,     4,   205,     4,   609,   204,
       5,   204,     7,   615,   616,   617,     3,     6,   181,   184,
     185,   186,   187,   618,   619,   620,   622,   623,   624,   625,
     616,   621,     4,     4,     4,   626,     3,     8,     4,   207,
     205,   205,     4,   619,   204,   204
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   208,   210,   209,   211,   209,   212,   209,   213,   209,
     214,   209,   215,   209,   216,   209,   217,   209,   218,   209,
     219,   209,   220,   209,   221,   209,   222,   209,   223,   223,
     223,   223,   223,   223,   223,   224,   226,   225,   227,   228,
     228,   229,   229,   229,   231,   230,   232,   232,   233,   233,
     233,   235,   234,   236,   236,   237,   237,   237,   238,   240,
     239,   242,   241,   241,   243,   245,   244,   246,   246,   246,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   260,   259,   261,   262,   263,
     264,   265,   266,   267,   269,   268,   270,   270,   270,   270,
     270,   272,   271,   274,   273,   275,   276,   278,   277,   280,
     279,   281,   282,   283,   284,   285,   286,   288,   287,   289,
     289,   289,   290,   290,   290,   290,   290,   290,   290,   290,
     290,   290,   292,   291,   294,   293,   296,   295,   297,   297,
     299,   298,   300,   300,   301,   302,   303,   304,   306,   305,
     308,   307,   309,   309,   309,   310,   310,   312,   311,   314,
     313,   316,   315,   318,   317,   319,   319,   320,   320,   320,
     322,   321,   323,   323,   323,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   324,   324,   324,   324,   324,   324,
     324,   324,   324,   324,   326,   325,   327,   327,   327,   329,
     328,   331,   330,   333,   332,   334,   336,   335,   337,   338,
     339,   340,   341,   342,   344,   343,   345,   345,   345,   346,
     348,   347,   350,   349,   352,   351,   354,   353,   356,   355,
     357,   357,   357,   358,   358,   358,   358,   358,   359,   360,
     361,   362,   363,   365,   364,   366,   366,   366,   367,   367,
     367,   367,   367,   367,   368,   369,   370,   372,   371,   373,
     373,   374,   374,   374,   376,   375,   378,   377,   379,   379,
     379,   379,   380,   380,   382,   381,   384,   383,   386,   385,
     387,   387,   387,   388,   388,   388,   388,   388,   388,   389,
     390,   391,   392,   393,   394,   396,   395,   397,   397,   398,
     398,   398,   400,   399,   402,   401,   403,   403,   403,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   406,   405,   408,   407,   410,   409,
     412,   411,   414,   413,   416,   415,   418,   417,   419,   420,
     421,   423,   422,   424,   424,   424,   424,   425,   427,   426,
     428,   428,   429,   429,   429,   431,   430,   432,   432,   432,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     435,   434,   437,   436,   438,   438,   439,   439,   439,   441,
     440,   443,   442,   444,   444,   445,   445,   445,   446,   446,
     446,   446,   446,   446,   446,   446,   446,   446,   447,   448,
     449,   451,   450,   453,   452,   455,   454,   456,   458,   457,
     459,   461,   460,   462,   462,   463,   463,   463,   465,   464,
     467,   466,   468,   468,   469,   469,   469,   470,   470,   470,
     470,   470,   470,   470,   470,   470,   471,   473,   472,   474,
     475,   476,   477,   479,   478,   480,   480,   481,   481,   481,
     483,   482,   485,   484,   486,   486,   486,   487,   487,   487,
     487,   487,   487,   487,   489,   488,   491,   490,   493,   492,
     495,   494,   496,   496,   497,   497,   497,   499,   498,   501,
     500,   502,   502,   503,   503,   503,   504,   504,   504,   504,
     504,   504,   504,   504,   504,   504,   504,   504,   504,   504,
     504,   506,   505,   508,   507,   510,   509,   512,   511,   514,
     513,   516,   515,   518,   517,   520,   519,   522,   521,   524,
     523,   526,   525,   528,   527,   530,   529,   531,   531,   533,
     532,   534,   534,   534,   536,   535,   537,   537,   538,   538,
     538,   539,   539,   539,   539,   539,   539,   539,   539,   539,
     539,   539,   539,   539,   539,   540,   542,   541,   543,   544,
     546,   545,   547,   547,   547,   548,   548,   548,   548,   548,
     550,   549,   552,   551,   554,   553,   555,   555,   555,   556,
     556,   556,   556,   556,   556,   557,   559,   558,   560,   562,
     561,   564,   563,   566,   565,   567,   567,   567,   568,   568,
     568,   568,   568,   568,   568,   568,   568,   568,   568,   568,
     568,   568,   568,   568,   568,   568,   569,   571,   570,   572,
     574,   573,   575,   576,   578,   577,   579,   579,   581,   580,
     583,   582,   584,   585,   587,   586,   589,   588,   591,   590,
     593,   592,   595,   594,   597,   596,   598,   598,   598,   599,
     599,   601,   600,   602,   604,   603,   605,   605,   605,   607,
     606,   608,   608,   608,   609,   609,   609,   609,   609,   609,
     609,   610,   612,   611,   614,   613,   615,   615,   615,   617,
     616,   618,   618,   618,   619,   619,   619,   619,   619,   621,
     620,   622,   623,   624,   626,   625,   628,   627,   629,   629,
     629,   630,   630,   630,   631,   632
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
       1,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     0,     6,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     2,     1,
       1,     0,     6,     3,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     3,     3
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
  "only_if_required", "dhcp4o6_port", "control_socket", "$@106",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@107", "control_socket_name", "$@108", "dhcp_queue_control", "$@109",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@110", "capacity", "arbitrary_map_entry", "$@111",
  "dhcp_ddns", "$@112", "sub_dhcp_ddns", "$@113", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@114", "server_port",
  "sender_ip", "$@115", "sender_port", "max_queue_size", "ncr_protocol",
  "$@116", "ncr_protocol_value", "ncr_format", "$@117",
  "dep_qualifying_suffix", "$@118", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@119",
  "dep_generated_prefix", "$@120", "dep_hostname_char_set", "$@121",
  "dep_hostname_char_replacement", "$@122", "config_control", "$@123",
  "sub_config_control", "$@124", "config_control_params",
  "config_control_param", "config_databases", "$@125",
  "config_fetch_wait_time", "loggers", "$@126", "loggers_entries",
  "logger_entry", "$@127", "logger_params", "logger_param", "debuglevel",
  "severity", "$@128", "output_options_list", "$@129",
  "output_options_list_content", "output_entry", "$@130",
  "output_params_list", "output_params", "output", "$@131", "flush",
  "maxsize", "maxver", "pattern", "$@132", "compatibility", "$@133",
  "compatibility_params", "compatibility_param", "lenient_option_parsing",
  "ignore-rai-link-selection", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   297,   297,   297,   298,   298,   299,   299,   300,   300,
     301,   301,   302,   302,   303,   303,   304,   304,   305,   305,
     306,   306,   307,   307,   308,   308,   309,   309,   317,   318,
     319,   320,   321,   322,   323,   326,   331,   331,   342,   345,
     346,   349,   354,   360,   365,   365,   372,   373,   376,   380,
     384,   390,   390,   397,   398,   401,   405,   409,   419,   428,
     428,   443,   443,   457,   460,   466,   466,   475,   476,   477,
     484,   485,   486,   487,   488,   489,   490,   491,   492,   493,
     494,   495,   496,   497,   498,   499,   500,   501,   502,   503,
     504,   505,   506,   507,   508,   509,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   519,   520,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   531,   532,   533,
     534,   535,   536,   537,   538,   539,   540,   541,   542,   543,
     544,   545,   546,   547,   550,   556,   562,   568,   574,   580,
     586,   592,   598,   604,   610,   616,   616,   625,   631,   637,
     643,   649,   655,   661,   667,   667,   676,   679,   682,   685,
     688,   694,   694,   703,   703,   712,   718,   724,   724,   733,
     733,   742,   748,   754,   760,   766,   772,   778,   778,   790,
     791,   792,   797,   798,   799,   800,   801,   802,   803,   804,
     805,   806,   809,   809,   818,   818,   829,   829,   837,   838,
     841,   841,   849,   851,   855,   861,   867,   873,   879,   879,
     892,   892,   903,   904,   905,   910,   911,   914,   914,   933,
     933,   951,   951,   964,   964,   975,   976,   979,   980,   981,
     986,   986,   996,   997,   998,  1003,  1004,  1005,  1006,  1007,
    1008,  1009,  1010,  1011,  1012,  1013,  1014,  1015,  1016,  1017,
    1018,  1019,  1020,  1021,  1024,  1024,  1032,  1033,  1034,  1037,
    1037,  1046,  1046,  1055,  1055,  1064,  1070,  1070,  1079,  1085,
    1091,  1097,  1103,  1109,  1115,  1115,  1123,  1124,  1125,  1128,
    1134,  1134,  1143,  1143,  1152,  1152,  1161,  1161,  1170,  1170,
    1181,  1182,  1183,  1188,  1189,  1190,  1191,  1192,  1195,  1200,
    1205,  1210,  1215,  1222,  1222,  1235,  1236,  1237,  1242,  1243,
    1244,  1245,  1246,  1247,  1250,  1256,  1262,  1268,  1268,  1279,
    1280,  1283,  1284,  1285,  1290,  1290,  1300,  1300,  1310,  1311,
    1312,  1315,  1318,  1319,  1322,  1322,  1331,  1331,  1340,  1340,
    1352,  1353,  1354,  1359,  1360,  1361,  1362,  1363,  1364,  1367,
    1373,  1379,  1385,  1391,  1397,  1406,  1406,  1420,  1421,  1424,
    1425,  1426,  1435,  1435,  1461,  1461,  1472,  1473,  1474,  1480,
    1481,  1482,  1483,  1484,  1485,  1486,  1487,  1488,  1489,  1490,
    1491,  1492,  1493,  1494,  1495,  1496,  1497,  1498,  1499,  1500,
    1501,  1502,  1503,  1504,  1505,  1506,  1507,  1508,  1509,  1510,
    1511,  1512,  1513,  1514,  1515,  1516,  1517,  1518,  1519,  1520,
    1521,  1522,  1523,  1524,  1527,  1527,  1536,  1536,  1545,  1545,
    1554,  1554,  1563,  1563,  1572,  1572,  1581,  1581,  1592,  1598,
    1604,  1610,  1610,  1618,  1619,  1620,  1621,  1624,  1632,  1632,
    1644,  1645,  1649,  1650,  1651,  1656,  1656,  1664,  1665,  1666,
    1671,  1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,
    1681,  1682,  1683,  1684,  1685,  1686,  1687,  1688,  1689,  1690,
    1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,  1700,
    1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,  1710,
    1717,  1717,  1731,  1731,  1740,  1741,  1744,  1745,  1746,  1753,
    1753,  1768,  1768,  1782,  1783,  1786,  1787,  1788,  1793,  1794,
    1795,  1796,  1797,  1798,  1799,  1800,  1801,  1802,  1805,  1807,
    1813,  1815,  1815,  1824,  1824,  1833,  1833,  1842,  1844,  1844,
    1853,  1863,  1863,  1876,  1877,  1882,  1883,  1884,  1891,  1891,
    1903,  1903,  1915,  1916,  1921,  1922,  1923,  1930,  1931,  1932,
    1933,  1934,  1935,  1936,  1937,  1938,  1941,  1943,  1943,  1952,
    1954,  1956,  1962,  1971,  1971,  1984,  1985,  1988,  1989,  1990,
    1995,  1995,  2005,  2005,  2015,  2016,  2017,  2022,  2023,  2024,
    2025,  2026,  2027,  2028,  2031,  2031,  2040,  2040,  2065,  2065,
    2095,  2095,  2106,  2107,  2110,  2111,  2112,  2117,  2117,  2126,
    2126,  2135,  2136,  2139,  2140,  2141,  2147,  2148,  2149,  2150,
    2151,  2152,  2153,  2154,  2155,  2156,  2157,  2158,  2159,  2160,
    2161,  2164,  2164,  2173,  2173,  2182,  2182,  2191,  2191,  2200,
    2200,  2211,  2211,  2220,  2220,  2229,  2229,  2238,  2238,  2247,
    2247,  2256,  2256,  2265,  2265,  2279,  2279,  2290,  2291,  2297,
    2297,  2308,  2309,  2310,  2315,  2315,  2325,  2326,  2329,  2330,
    2331,  2336,  2337,  2338,  2339,  2340,  2341,  2342,  2343,  2344,
    2345,  2346,  2347,  2348,  2349,  2352,  2354,  2354,  2363,  2371,
    2379,  2379,  2390,  2391,  2392,  2397,  2398,  2399,  2400,  2401,
    2404,  2404,  2413,  2413,  2425,  2425,  2438,  2439,  2440,  2445,
    2446,  2447,  2448,  2449,  2450,  2453,  2459,  2459,  2468,  2474,
    2474,  2484,  2484,  2497,  2497,  2507,  2508,  2509,  2514,  2515,
    2516,  2517,  2518,  2519,  2520,  2521,  2522,  2523,  2524,  2525,
    2526,  2527,  2528,  2529,  2530,  2531,  2534,  2540,  2540,  2549,
    2555,  2555,  2564,  2570,  2576,  2576,  2585,  2586,  2589,  2589,
    2599,  2599,  2609,  2616,  2623,  2623,  2632,  2632,  2642,  2642,
    2652,  2652,  2664,  2664,  2676,  2676,  2686,  2687,  2688,  2694,
    2695,  2698,  2698,  2709,  2717,  2717,  2730,  2731,  2732,  2738,
    2738,  2746,  2747,  2748,  2753,  2754,  2755,  2756,  2757,  2758,
    2759,  2762,  2768,  2768,  2777,  2777,  2788,  2789,  2790,  2795,
    2795,  2803,  2804,  2805,  2810,  2811,  2812,  2813,  2814,  2817,
    2817,  2826,  2832,  2838,  2844,  2844,  2853,  2853,  2864,  2865,
    2866,  2871,  2872,  2873,  2876,  2882
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
#line 6187 "dhcp4_parser.cc"

#line 2888 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
