// A Bison parser, made by GNU Bison 3.7.6.

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
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 290 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 290 "dhcp4_parser.yy"
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
#line 299 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 300 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 301 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 302 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 303 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 304 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 305 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 306 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 307 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 308 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 309 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 310 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 311 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 319 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 320 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 321 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 322 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 323 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 324 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 325 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 328 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 333 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 338 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 344 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 351 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 356 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 362 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 367 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 370 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 378 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 382 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 386 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 392 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 394 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 403 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 407 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 411 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 421 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 430 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 435 "dhcp4_parser.yy"
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
#line 445 "dhcp4_parser.yy"
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
#line 454 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 462 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 468 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 472 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 479 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 135: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 553 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 136: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 559 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 137: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 565 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 138: // renew_timer: "renew-timer" ":" "integer"
#line 571 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 139: // rebind_timer: "rebind-timer" ":" "integer"
#line 577 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 140: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 583 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 141: // t1_percent: "t1-percent" ":" "floating point"
#line 589 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 142: // t2_percent: "t2-percent" ":" "floating point"
#line 595 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 143: // cache_threshold: "cache-threshold" ":" "floating point"
#line 601 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 144: // cache_max_age: "cache-max-age" ":" "integer"
#line 607 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 145: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 613 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 146: // $@20: %empty
#line 619 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 147: // server_tag: "server-tag" $@20 ":" "constant string"
#line 622 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 148: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 628 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 149: // $@21: %empty
#line 634 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1269 "dhcp4_parser.cc"
    break;

  case 150: // allocator: "allocator" $@21 ":" "constant string"
#line 637 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 151: // echo_client_id: "echo-client-id" ":" "boolean"
#line 643 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1289 "dhcp4_parser.cc"
    break;

  case 152: // match_client_id: "match-client-id" ":" "boolean"
#line 649 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1299 "dhcp4_parser.cc"
    break;

  case 153: // authoritative: "authoritative" ":" "boolean"
#line 655 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1309 "dhcp4_parser.cc"
    break;

  case 154: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 661 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1319 "dhcp4_parser.cc"
    break;

  case 155: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 667 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 156: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 673 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1339 "dhcp4_parser.cc"
    break;

  case 157: // $@22: %empty
#line 679 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1348 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 682 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "when-present"
#line 688 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1365 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "never"
#line 691 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1373 "dhcp4_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "always"
#line 694 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-not-present"
#line 697 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "boolean"
#line 700 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1398 "dhcp4_parser.cc"
    break;

  case 164: // $@23: %empty
#line 706 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 165: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 709 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 166: // $@24: %empty
#line 715 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp4_parser.cc"
    break;

  case 167: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 718 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1436 "dhcp4_parser.cc"
    break;

  case 168: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 724 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 169: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 730 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 170: // $@25: %empty
#line 736 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 171: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 739 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 172: // $@26: %empty
#line 745 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1484 "dhcp4_parser.cc"
    break;

  case 173: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 748 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 174: // store_extended_info: "store-extended-info" ":" "boolean"
#line 754 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1504 "dhcp4_parser.cc"
    break;

  case 175: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 760 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1514 "dhcp4_parser.cc"
    break;

  case 176: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 766 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 177: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 772 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 178: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 778 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 179: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 784 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1554 "dhcp4_parser.cc"
    break;

  case 180: // $@27: %empty
#line 790 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 181: // interfaces_config: "interfaces-config" $@27 ":" "{" interfaces_config_params "}"
#line 796 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 184: // interfaces_config_params: interfaces_config_params ","
#line 804 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1584 "dhcp4_parser.cc"
    break;

  case 195: // $@28: %empty
#line 821 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 196: // sub_interfaces4: "{" $@28 interfaces_config_params "}"
#line 825 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1603 "dhcp4_parser.cc"
    break;

  case 197: // $@29: %empty
#line 830 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 198: // interfaces_list: "interfaces" $@29 ":" list_strings
#line 836 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 199: // $@30: %empty
#line 841 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1633 "dhcp4_parser.cc"
    break;

  case 200: // dhcp_socket_type: "dhcp-socket-type" $@30 ":" socket_type
#line 844 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1642 "dhcp4_parser.cc"
    break;

  case 201: // socket_type: "raw"
#line 849 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1648 "dhcp4_parser.cc"
    break;

  case 202: // socket_type: "udp"
#line 850 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1654 "dhcp4_parser.cc"
    break;

  case 203: // $@31: %empty
#line 853 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1663 "dhcp4_parser.cc"
    break;

  case 204: // outbound_interface: "outbound-interface" $@31 ":" outbound_interface_value
#line 856 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc"
    break;

  case 205: // outbound_interface_value: "same-as-inbound"
#line 861 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1680 "dhcp4_parser.cc"
    break;

  case 206: // outbound_interface_value: "use-routing"
#line 863 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1688 "dhcp4_parser.cc"
    break;

  case 207: // re_detect: "re-detect" ":" "boolean"
#line 867 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1698 "dhcp4_parser.cc"
    break;

  case 208: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 873 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1708 "dhcp4_parser.cc"
    break;

  case 209: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 879 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 210: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 885 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 211: // $@32: %empty
#line 891 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1740 "dhcp4_parser.cc"
    break;

  case 212: // lease_database: "lease-database" $@32 ":" "{" database_map_params "}"
#line 897 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1751 "dhcp4_parser.cc"
    break;

  case 213: // $@33: %empty
#line 904 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 214: // sanity_checks: "sanity-checks" $@33 ":" "{" sanity_checks_params "}"
#line 910 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 217: // sanity_checks_params: sanity_checks_params ","
#line 917 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1780 "dhcp4_parser.cc"
    break;

  case 220: // $@34: %empty
#line 926 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc"
    break;

  case 221: // lease_checks: "lease-checks" $@34 ":" "constant string"
#line 929 "dhcp4_parser.yy"
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
#line 1809 "dhcp4_parser.cc"
    break;

  case 222: // $@35: %empty
#line 945 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 223: // extended_info_checks: "extended-info-checks" $@35 ":" "constant string"
#line 948 "dhcp4_parser.yy"
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
#line 1837 "dhcp4_parser.cc"
    break;

  case 224: // $@36: %empty
#line 963 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1849 "dhcp4_parser.cc"
    break;

  case 225: // hosts_database: "hosts-database" $@36 ":" "{" database_map_params "}"
#line 969 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1860 "dhcp4_parser.cc"
    break;

  case 226: // $@37: %empty
#line 976 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1872 "dhcp4_parser.cc"
    break;

  case 227: // hosts_databases: "hosts-databases" $@37 ":" "[" database_list "]"
#line 982 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 232: // not_empty_database_list: not_empty_database_list ","
#line 993 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1889 "dhcp4_parser.cc"
    break;

  case 233: // $@38: %empty
#line 998 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1899 "dhcp4_parser.cc"
    break;

  case 234: // database: "{" $@38 database_map_params "}"
#line 1002 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1909 "dhcp4_parser.cc"
    break;

  case 237: // database_map_params: database_map_params ","
#line 1010 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1917 "dhcp4_parser.cc"
    break;

  case 257: // $@39: %empty
#line 1036 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 258: // database_type: "type" $@39 ":" db_type
#line 1039 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1935 "dhcp4_parser.cc"
    break;

  case 259: // db_type: "memfile"
#line 1044 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1941 "dhcp4_parser.cc"
    break;

  case 260: // db_type: "mysql"
#line 1045 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1947 "dhcp4_parser.cc"
    break;

  case 261: // db_type: "postgresql"
#line 1046 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1953 "dhcp4_parser.cc"
    break;

  case 262: // $@40: %empty
#line 1049 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 263: // user: "user" $@40 ":" "constant string"
#line 1052 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 264: // $@41: %empty
#line 1058 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 265: // password: "password" $@41 ":" "constant string"
#line 1061 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 266: // $@42: %empty
#line 1067 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2000 "dhcp4_parser.cc"
    break;

  case 267: // host: "host" $@42 ":" "constant string"
#line 1070 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 268: // port: "port" ":" "integer"
#line 1076 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 269: // $@43: %empty
#line 1082 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp4_parser.cc"
    break;

  case 270: // name: "name" $@43 ":" "constant string"
#line 1085 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2039 "dhcp4_parser.cc"
    break;

  case 271: // persist: "persist" ":" "boolean"
#line 1091 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2049 "dhcp4_parser.cc"
    break;

  case 272: // lfc_interval: "lfc-interval" ":" "integer"
#line 1097 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 273: // readonly: "readonly" ":" "boolean"
#line 1103 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 274: // connect_timeout: "connect-timeout" ":" "integer"
#line 1109 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 275: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1115 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 276: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1121 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 277: // $@44: %empty
#line 1127 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2108 "dhcp4_parser.cc"
    break;

  case 278: // on_fail: "on-fail" $@44 ":" on_fail_mode
#line 1130 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2117 "dhcp4_parser.cc"
    break;

  case 279: // on_fail_mode: "stop-retry-exit"
#line 1135 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2123 "dhcp4_parser.cc"
    break;

  case 280: // on_fail_mode: "serve-retry-exit"
#line 1136 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2129 "dhcp4_parser.cc"
    break;

  case 281: // on_fail_mode: "serve-retry-continue"
#line 1137 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2135 "dhcp4_parser.cc"
    break;

  case 282: // max_row_errors: "max-row-errors" ":" "integer"
#line 1140 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2145 "dhcp4_parser.cc"
    break;

  case 283: // $@45: %empty
#line 1146 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2154 "dhcp4_parser.cc"
    break;

  case 284: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1149 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2164 "dhcp4_parser.cc"
    break;

  case 285: // $@46: %empty
#line 1155 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 286: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1158 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2183 "dhcp4_parser.cc"
    break;

  case 287: // $@47: %empty
#line 1164 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 288: // key_file: "key-file" $@47 ":" "constant string"
#line 1167 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 289: // $@48: %empty
#line 1173 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2211 "dhcp4_parser.cc"
    break;

  case 290: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1176 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2221 "dhcp4_parser.cc"
    break;

  case 291: // $@49: %empty
#line 1182 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2233 "dhcp4_parser.cc"
    break;

  case 292: // host_reservation_identifiers: "host-reservation-identifiers" $@49 ":" "[" host_reservation_identifiers_list "]"
#line 1188 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2242 "dhcp4_parser.cc"
    break;

  case 295: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1195 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2250 "dhcp4_parser.cc"
    break;

  case 301: // duid_id: "duid"
#line 1207 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2259 "dhcp4_parser.cc"
    break;

  case 302: // hw_address_id: "hw-address"
#line 1212 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2268 "dhcp4_parser.cc"
    break;

  case 303: // circuit_id: "circuit-id"
#line 1217 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2277 "dhcp4_parser.cc"
    break;

  case 304: // client_id: "client-id"
#line 1222 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2286 "dhcp4_parser.cc"
    break;

  case 305: // flex_id: "flex-id"
#line 1227 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2295 "dhcp4_parser.cc"
    break;

  case 306: // $@50: %empty
#line 1234 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 307: // dhcp_multi_threading: "multi-threading" $@50 ":" "{" multi_threading_params "}"
#line 1240 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2318 "dhcp4_parser.cc"
    break;

  case 310: // multi_threading_params: multi_threading_params ","
#line 1249 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2326 "dhcp4_parser.cc"
    break;

  case 317: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1262 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2336 "dhcp4_parser.cc"
    break;

  case 318: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1268 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2346 "dhcp4_parser.cc"
    break;

  case 319: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1274 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2356 "dhcp4_parser.cc"
    break;

  case 320: // $@51: %empty
#line 1280 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2368 "dhcp4_parser.cc"
    break;

  case 321: // hooks_libraries: "hooks-libraries" $@51 ":" "[" hooks_libraries_list "]"
#line 1286 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2377 "dhcp4_parser.cc"
    break;

  case 326: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1297 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2385 "dhcp4_parser.cc"
    break;

  case 327: // $@52: %empty
#line 1302 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2395 "dhcp4_parser.cc"
    break;

  case 328: // hooks_library: "{" $@52 hooks_params "}"
#line 1306 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2405 "dhcp4_parser.cc"
    break;

  case 329: // $@53: %empty
#line 1312 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2415 "dhcp4_parser.cc"
    break;

  case 330: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1316 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 333: // hooks_params: hooks_params ","
#line 1324 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2433 "dhcp4_parser.cc"
    break;

  case 337: // $@54: %empty
#line 1334 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2442 "dhcp4_parser.cc"
    break;

  case 338: // library: "library" $@54 ":" "constant string"
#line 1337 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2452 "dhcp4_parser.cc"
    break;

  case 339: // $@55: %empty
#line 1343 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2461 "dhcp4_parser.cc"
    break;

  case 340: // parameters: "parameters" $@55 ":" map_value
#line 1346 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2470 "dhcp4_parser.cc"
    break;

  case 341: // $@56: %empty
#line 1352 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 342: // expired_leases_processing: "expired-leases-processing" $@56 ":" "{" expired_leases_params "}"
#line 1358 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 345: // expired_leases_params: expired_leases_params ","
#line 1366 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2500 "dhcp4_parser.cc"
    break;

  case 352: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1379 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2510 "dhcp4_parser.cc"
    break;

  case 353: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1385 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2520 "dhcp4_parser.cc"
    break;

  case 354: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1391 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2530 "dhcp4_parser.cc"
    break;

  case 355: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1397 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2540 "dhcp4_parser.cc"
    break;

  case 356: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1403 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 357: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1409 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2560 "dhcp4_parser.cc"
    break;

  case 358: // $@57: %empty
#line 1418 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2572 "dhcp4_parser.cc"
    break;

  case 359: // subnet4_list: "subnet4" $@57 ":" "[" subnet4_list_content "]"
#line 1424 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2581 "dhcp4_parser.cc"
    break;

  case 364: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1438 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2589 "dhcp4_parser.cc"
    break;

  case 365: // $@58: %empty
#line 1447 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 366: // subnet4: "{" $@58 subnet4_params "}"
#line 1451 "dhcp4_parser.yy"
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
#line 2625 "dhcp4_parser.cc"
    break;

  case 367: // $@59: %empty
#line 1473 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2635 "dhcp4_parser.cc"
    break;

  case 368: // sub_subnet4: "{" $@59 subnet4_params "}"
#line 1477 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2645 "dhcp4_parser.cc"
    break;

  case 371: // subnet4_params: subnet4_params ","
#line 1486 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2653 "dhcp4_parser.cc"
    break;

  case 418: // $@60: %empty
#line 1540 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2662 "dhcp4_parser.cc"
    break;

  case 419: // subnet: "subnet" $@60 ":" "constant string"
#line 1543 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2672 "dhcp4_parser.cc"
    break;

  case 420: // $@61: %empty
#line 1549 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2681 "dhcp4_parser.cc"
    break;

  case 421: // subnet_4o6_interface: "4o6-interface" $@61 ":" "constant string"
#line 1552 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2691 "dhcp4_parser.cc"
    break;

  case 422: // $@62: %empty
#line 1558 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2700 "dhcp4_parser.cc"
    break;

  case 423: // subnet_4o6_interface_id: "4o6-interface-id" $@62 ":" "constant string"
#line 1561 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2710 "dhcp4_parser.cc"
    break;

  case 424: // $@63: %empty
#line 1567 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2719 "dhcp4_parser.cc"
    break;

  case 425: // subnet_4o6_subnet: "4o6-subnet" $@63 ":" "constant string"
#line 1570 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2729 "dhcp4_parser.cc"
    break;

  case 426: // $@64: %empty
#line 1576 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2738 "dhcp4_parser.cc"
    break;

  case 427: // interface: "interface" $@64 ":" "constant string"
#line 1579 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2748 "dhcp4_parser.cc"
    break;

  case 428: // $@65: %empty
#line 1585 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2757 "dhcp4_parser.cc"
    break;

  case 429: // client_class: "client-class" $@65 ":" "constant string"
#line 1588 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2767 "dhcp4_parser.cc"
    break;

  case 430: // $@66: %empty
#line 1594 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2779 "dhcp4_parser.cc"
    break;

  case 431: // require_client_classes: "require-client-classes" $@66 ":" list_strings
#line 1600 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2788 "dhcp4_parser.cc"
    break;

  case 432: // reservations_global: "reservations-global" ":" "boolean"
#line 1605 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2798 "dhcp4_parser.cc"
    break;

  case 433: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1611 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2808 "dhcp4_parser.cc"
    break;

  case 434: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1617 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2818 "dhcp4_parser.cc"
    break;

  case 435: // $@67: %empty
#line 1623 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2827 "dhcp4_parser.cc"
    break;

  case 436: // reservation_mode: "reservation-mode" $@67 ":" hr_mode
#line 1626 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2836 "dhcp4_parser.cc"
    break;

  case 437: // hr_mode: "disabled"
#line 1631 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2842 "dhcp4_parser.cc"
    break;

  case 438: // hr_mode: "out-of-pool"
#line 1632 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2848 "dhcp4_parser.cc"
    break;

  case 439: // hr_mode: "global"
#line 1633 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2854 "dhcp4_parser.cc"
    break;

  case 440: // hr_mode: "all"
#line 1634 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2860 "dhcp4_parser.cc"
    break;

  case 441: // id: "id" ":" "integer"
#line 1637 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2870 "dhcp4_parser.cc"
    break;

  case 442: // $@68: %empty
#line 1645 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2882 "dhcp4_parser.cc"
    break;

  case 443: // shared_networks: "shared-networks" $@68 ":" "[" shared_networks_content "]"
#line 1651 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2891 "dhcp4_parser.cc"
    break;

  case 448: // shared_networks_list: shared_networks_list ","
#line 1664 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2899 "dhcp4_parser.cc"
    break;

  case 449: // $@69: %empty
#line 1669 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 450: // shared_network: "{" $@69 shared_network_params "}"
#line 1673 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2917 "dhcp4_parser.cc"
    break;

  case 453: // shared_network_params: shared_network_params ","
#line 1679 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2925 "dhcp4_parser.cc"
    break;

  case 495: // $@70: %empty
#line 1731 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2937 "dhcp4_parser.cc"
    break;

  case 496: // option_def_list: "option-def" $@70 ":" "[" option_def_list_content "]"
#line 1737 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2946 "dhcp4_parser.cc"
    break;

  case 497: // $@71: %empty
#line 1745 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2955 "dhcp4_parser.cc"
    break;

  case 498: // sub_option_def_list: "{" $@71 option_def_list "}"
#line 1748 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2963 "dhcp4_parser.cc"
    break;

  case 503: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1760 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2971 "dhcp4_parser.cc"
    break;

  case 504: // $@72: %empty
#line 1767 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2981 "dhcp4_parser.cc"
    break;

  case 505: // option_def_entry: "{" $@72 option_def_params "}"
#line 1771 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2993 "dhcp4_parser.cc"
    break;

  case 506: // $@73: %empty
#line 1782 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3003 "dhcp4_parser.cc"
    break;

  case 507: // sub_option_def: "{" $@73 option_def_params "}"
#line 1786 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3015 "dhcp4_parser.cc"
    break;

  case 512: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1802 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3023 "dhcp4_parser.cc"
    break;

  case 524: // code: "code" ":" "integer"
#line 1821 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3033 "dhcp4_parser.cc"
    break;

  case 526: // $@74: %empty
#line 1829 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3042 "dhcp4_parser.cc"
    break;

  case 527: // option_def_type: "type" $@74 ":" "constant string"
#line 1832 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 528: // $@75: %empty
#line 1838 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3061 "dhcp4_parser.cc"
    break;

  case 529: // option_def_record_types: "record-types" $@75 ":" "constant string"
#line 1841 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3071 "dhcp4_parser.cc"
    break;

  case 530: // $@76: %empty
#line 1847 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3080 "dhcp4_parser.cc"
    break;

  case 531: // space: "space" $@76 ":" "constant string"
#line 1850 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 533: // $@77: %empty
#line 1858 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3099 "dhcp4_parser.cc"
    break;

  case 534: // option_def_encapsulate: "encapsulate" $@77 ":" "constant string"
#line 1861 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3109 "dhcp4_parser.cc"
    break;

  case 535: // option_def_array: "array" ":" "boolean"
#line 1867 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3119 "dhcp4_parser.cc"
    break;

  case 536: // $@78: %empty
#line 1877 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3131 "dhcp4_parser.cc"
    break;

  case 537: // option_data_list: "option-data" $@78 ":" "[" option_data_list_content "]"
#line 1883 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3140 "dhcp4_parser.cc"
    break;

  case 542: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1898 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3148 "dhcp4_parser.cc"
    break;

  case 543: // $@79: %empty
#line 1905 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3158 "dhcp4_parser.cc"
    break;

  case 544: // option_data_entry: "{" $@79 option_data_params "}"
#line 1909 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3167 "dhcp4_parser.cc"
    break;

  case 545: // $@80: %empty
#line 1917 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3177 "dhcp4_parser.cc"
    break;

  case 546: // sub_option_data: "{" $@80 option_data_params "}"
#line 1921 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 551: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1937 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3194 "dhcp4_parser.cc"
    break;

  case 562: // $@81: %empty
#line 1957 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3203 "dhcp4_parser.cc"
    break;

  case 563: // option_data_data: "data" $@81 ":" "constant string"
#line 1960 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3213 "dhcp4_parser.cc"
    break;

  case 566: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1970 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3223 "dhcp4_parser.cc"
    break;

  case 567: // option_data_always_send: "always-send" ":" "boolean"
#line 1976 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 568: // $@82: %empty
#line 1985 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3245 "dhcp4_parser.cc"
    break;

  case 569: // pools_list: "pools" $@82 ":" "[" pools_list_content "]"
#line 1991 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 574: // not_empty_pools_list: not_empty_pools_list ","
#line 2004 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3262 "dhcp4_parser.cc"
    break;

  case 575: // $@83: %empty
#line 2009 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3272 "dhcp4_parser.cc"
    break;

  case 576: // pool_list_entry: "{" $@83 pool_params "}"
#line 2013 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3282 "dhcp4_parser.cc"
    break;

  case 577: // $@84: %empty
#line 2019 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3292 "dhcp4_parser.cc"
    break;

  case 578: // sub_pool4: "{" $@84 pool_params "}"
#line 2023 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3302 "dhcp4_parser.cc"
    break;

  case 581: // pool_params: pool_params ","
#line 2031 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3310 "dhcp4_parser.cc"
    break;

  case 589: // $@85: %empty
#line 2045 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3319 "dhcp4_parser.cc"
    break;

  case 590: // pool_entry: "pool" $@85 ":" "constant string"
#line 2048 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3329 "dhcp4_parser.cc"
    break;

  case 591: // $@86: %empty
#line 2054 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3337 "dhcp4_parser.cc"
    break;

  case 592: // user_context: "user-context" $@86 ":" map_value
#line 2056 "dhcp4_parser.yy"
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
#line 3364 "dhcp4_parser.cc"
    break;

  case 593: // $@87: %empty
#line 2079 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3372 "dhcp4_parser.cc"
    break;

  case 594: // comment: "comment" $@87 ":" "constant string"
#line 2081 "dhcp4_parser.yy"
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
#line 3401 "dhcp4_parser.cc"
    break;

  case 595: // $@88: %empty
#line 2109 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3413 "dhcp4_parser.cc"
    break;

  case 596: // reservations: "reservations" $@88 ":" "[" reservations_list "]"
#line 2115 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3422 "dhcp4_parser.cc"
    break;

  case 601: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2126 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3430 "dhcp4_parser.cc"
    break;

  case 602: // $@89: %empty
#line 2131 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3440 "dhcp4_parser.cc"
    break;

  case 603: // reservation: "{" $@89 reservation_params "}"
#line 2135 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3449 "dhcp4_parser.cc"
    break;

  case 604: // $@90: %empty
#line 2140 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3459 "dhcp4_parser.cc"
    break;

  case 605: // sub_reservation: "{" $@90 reservation_params "}"
#line 2144 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3468 "dhcp4_parser.cc"
    break;

  case 610: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2155 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3476 "dhcp4_parser.cc"
    break;

  case 626: // $@91: %empty
#line 2178 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3485 "dhcp4_parser.cc"
    break;

  case 627: // next_server: "next-server" $@91 ":" "constant string"
#line 2181 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3495 "dhcp4_parser.cc"
    break;

  case 628: // $@92: %empty
#line 2187 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3504 "dhcp4_parser.cc"
    break;

  case 629: // server_hostname: "server-hostname" $@92 ":" "constant string"
#line 2190 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3514 "dhcp4_parser.cc"
    break;

  case 630: // $@93: %empty
#line 2196 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3523 "dhcp4_parser.cc"
    break;

  case 631: // boot_file_name: "boot-file-name" $@93 ":" "constant string"
#line 2199 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3533 "dhcp4_parser.cc"
    break;

  case 632: // $@94: %empty
#line 2205 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3542 "dhcp4_parser.cc"
    break;

  case 633: // ip_address: "ip-address" $@94 ":" "constant string"
#line 2208 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3552 "dhcp4_parser.cc"
    break;

  case 634: // $@95: %empty
#line 2214 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3564 "dhcp4_parser.cc"
    break;

  case 635: // ip_addresses: "ip-addresses" $@95 ":" list_strings
#line 2220 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 636: // $@96: %empty
#line 2225 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 637: // duid: "duid" $@96 ":" "constant string"
#line 2228 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 638: // $@97: %empty
#line 2234 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3601 "dhcp4_parser.cc"
    break;

  case 639: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2237 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 640: // $@98: %empty
#line 2243 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3620 "dhcp4_parser.cc"
    break;

  case 641: // client_id_value: "client-id" $@98 ":" "constant string"
#line 2246 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3630 "dhcp4_parser.cc"
    break;

  case 642: // $@99: %empty
#line 2252 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3639 "dhcp4_parser.cc"
    break;

  case 643: // circuit_id_value: "circuit-id" $@99 ":" "constant string"
#line 2255 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3649 "dhcp4_parser.cc"
    break;

  case 644: // $@100: %empty
#line 2261 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3658 "dhcp4_parser.cc"
    break;

  case 645: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2264 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3668 "dhcp4_parser.cc"
    break;

  case 646: // $@101: %empty
#line 2270 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3677 "dhcp4_parser.cc"
    break;

  case 647: // hostname: "hostname" $@101 ":" "constant string"
#line 2273 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3687 "dhcp4_parser.cc"
    break;

  case 648: // $@102: %empty
#line 2279 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3699 "dhcp4_parser.cc"
    break;

  case 649: // reservation_client_classes: "client-classes" $@102 ":" list_strings
#line 2285 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3708 "dhcp4_parser.cc"
    break;

  case 650: // $@103: %empty
#line 2293 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3720 "dhcp4_parser.cc"
    break;

  case 651: // relay: "relay" $@103 ":" "{" relay_map "}"
#line 2299 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3729 "dhcp4_parser.cc"
    break;

  case 654: // $@104: %empty
#line 2311 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 655: // client_classes: "client-classes" $@104 ":" "[" client_classes_list "]"
#line 2317 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3750 "dhcp4_parser.cc"
    break;

  case 658: // client_classes_list: client_classes_list ","
#line 2324 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3758 "dhcp4_parser.cc"
    break;

  case 659: // $@105: %empty
#line 2329 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3768 "dhcp4_parser.cc"
    break;

  case 660: // client_class_entry: "{" $@105 client_class_params "}"
#line 2333 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3778 "dhcp4_parser.cc"
    break;

  case 665: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2345 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3786 "dhcp4_parser.cc"
    break;

  case 682: // $@106: %empty
#line 2369 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3795 "dhcp4_parser.cc"
    break;

  case 683: // client_class_test: "test" $@106 ":" "constant string"
#line 2372 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3805 "dhcp4_parser.cc"
    break;

  case 684: // $@107: %empty
#line 2378 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3814 "dhcp4_parser.cc"
    break;

  case 685: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2381 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3824 "dhcp4_parser.cc"
    break;

  case 686: // only_if_required: "only-if-required" ":" "boolean"
#line 2387 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3834 "dhcp4_parser.cc"
    break;

  case 687: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2395 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 688: // $@108: %empty
#line 2403 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3856 "dhcp4_parser.cc"
    break;

  case 689: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2409 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3865 "dhcp4_parser.cc"
    break;

  case 692: // control_socket_params: control_socket_params ","
#line 2416 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3873 "dhcp4_parser.cc"
    break;

  case 698: // $@109: %empty
#line 2428 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3882 "dhcp4_parser.cc"
    break;

  case 699: // control_socket_type: "socket-type" $@109 ":" "constant string"
#line 2431 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3892 "dhcp4_parser.cc"
    break;

  case 700: // $@110: %empty
#line 2437 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3901 "dhcp4_parser.cc"
    break;

  case 701: // control_socket_name: "socket-name" $@110 ":" "constant string"
#line 2440 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3911 "dhcp4_parser.cc"
    break;

  case 702: // $@111: %empty
#line 2449 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3923 "dhcp4_parser.cc"
    break;

  case 703: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2455 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3934 "dhcp4_parser.cc"
    break;

  case 706: // queue_control_params: queue_control_params ","
#line 2464 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3942 "dhcp4_parser.cc"
    break;

  case 713: // enable_queue: "enable-queue" ":" "boolean"
#line 2477 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3952 "dhcp4_parser.cc"
    break;

  case 714: // $@112: %empty
#line 2483 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3961 "dhcp4_parser.cc"
    break;

  case 715: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2486 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3971 "dhcp4_parser.cc"
    break;

  case 716: // capacity: "capacity" ":" "integer"
#line 2492 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3981 "dhcp4_parser.cc"
    break;

  case 717: // $@113: %empty
#line 2498 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3990 "dhcp4_parser.cc"
    break;

  case 718: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2501 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3999 "dhcp4_parser.cc"
    break;

  case 719: // $@114: %empty
#line 2508 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4011 "dhcp4_parser.cc"
    break;

  case 720: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2514 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4022 "dhcp4_parser.cc"
    break;

  case 721: // $@115: %empty
#line 2521 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4032 "dhcp4_parser.cc"
    break;

  case 722: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2525 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4042 "dhcp4_parser.cc"
    break;

  case 725: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2533 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4050 "dhcp4_parser.cc"
    break;

  case 744: // enable_updates: "enable-updates" ":" "boolean"
#line 2558 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4060 "dhcp4_parser.cc"
    break;

  case 745: // $@116: %empty
#line 2564 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4069 "dhcp4_parser.cc"
    break;

  case 746: // server_ip: "server-ip" $@116 ":" "constant string"
#line 2567 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4079 "dhcp4_parser.cc"
    break;

  case 747: // server_port: "server-port" ":" "integer"
#line 2573 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4089 "dhcp4_parser.cc"
    break;

  case 748: // $@117: %empty
#line 2579 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4098 "dhcp4_parser.cc"
    break;

  case 749: // sender_ip: "sender-ip" $@117 ":" "constant string"
#line 2582 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4108 "dhcp4_parser.cc"
    break;

  case 750: // sender_port: "sender-port" ":" "integer"
#line 2588 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4118 "dhcp4_parser.cc"
    break;

  case 751: // max_queue_size: "max-queue-size" ":" "integer"
#line 2594 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4128 "dhcp4_parser.cc"
    break;

  case 752: // $@118: %empty
#line 2600 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4137 "dhcp4_parser.cc"
    break;

  case 753: // ncr_protocol: "ncr-protocol" $@118 ":" ncr_protocol_value
#line 2603 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4146 "dhcp4_parser.cc"
    break;

  case 754: // ncr_protocol_value: "udp"
#line 2609 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4152 "dhcp4_parser.cc"
    break;

  case 755: // ncr_protocol_value: "tcp"
#line 2610 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4158 "dhcp4_parser.cc"
    break;

  case 756: // $@119: %empty
#line 2613 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4167 "dhcp4_parser.cc"
    break;

  case 757: // ncr_format: "ncr-format" $@119 ":" "JSON"
#line 2616 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4177 "dhcp4_parser.cc"
    break;

  case 758: // $@120: %empty
#line 2623 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4186 "dhcp4_parser.cc"
    break;

  case 759: // dep_qualifying_suffix: "qualifying-suffix" $@120 ":" "constant string"
#line 2626 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4196 "dhcp4_parser.cc"
    break;

  case 760: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2633 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4206 "dhcp4_parser.cc"
    break;

  case 761: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2640 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4216 "dhcp4_parser.cc"
    break;

  case 762: // $@121: %empty
#line 2647 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4225 "dhcp4_parser.cc"
    break;

  case 763: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2650 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4234 "dhcp4_parser.cc"
    break;

  case 764: // $@122: %empty
#line 2656 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4243 "dhcp4_parser.cc"
    break;

  case 765: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2659 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4253 "dhcp4_parser.cc"
    break;

  case 766: // $@123: %empty
#line 2666 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4262 "dhcp4_parser.cc"
    break;

  case 767: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2669 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4272 "dhcp4_parser.cc"
    break;

  case 768: // $@124: %empty
#line 2676 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4281 "dhcp4_parser.cc"
    break;

  case 769: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2679 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4291 "dhcp4_parser.cc"
    break;

  case 770: // $@125: %empty
#line 2688 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4303 "dhcp4_parser.cc"
    break;

  case 771: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2694 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4313 "dhcp4_parser.cc"
    break;

  case 772: // $@126: %empty
#line 2700 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4323 "dhcp4_parser.cc"
    break;

  case 773: // sub_config_control: "{" $@126 config_control_params "}"
#line 2704 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4332 "dhcp4_parser.cc"
    break;

  case 776: // config_control_params: config_control_params ","
#line 2712 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4340 "dhcp4_parser.cc"
    break;

  case 779: // $@127: %empty
#line 2722 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4352 "dhcp4_parser.cc"
    break;

  case 780: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2728 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4361 "dhcp4_parser.cc"
    break;

  case 781: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2733 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4371 "dhcp4_parser.cc"
    break;

  case 782: // $@128: %empty
#line 2741 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4383 "dhcp4_parser.cc"
    break;

  case 783: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2747 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4392 "dhcp4_parser.cc"
    break;

  case 786: // loggers_entries: loggers_entries ","
#line 2756 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4400 "dhcp4_parser.cc"
    break;

  case 787: // $@129: %empty
#line 2762 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4410 "dhcp4_parser.cc"
    break;

  case 788: // logger_entry: "{" $@129 logger_params "}"
#line 2766 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4418 "dhcp4_parser.cc"
    break;

  case 791: // logger_params: logger_params ","
#line 2772 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4426 "dhcp4_parser.cc"
    break;

  case 799: // debuglevel: "debuglevel" ":" "integer"
#line 2786 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4436 "dhcp4_parser.cc"
    break;

  case 800: // $@130: %empty
#line 2792 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4445 "dhcp4_parser.cc"
    break;

  case 801: // severity: "severity" $@130 ":" "constant string"
#line 2795 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4455 "dhcp4_parser.cc"
    break;

  case 802: // $@131: %empty
#line 2801 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4467 "dhcp4_parser.cc"
    break;

  case 803: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2807 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4476 "dhcp4_parser.cc"
    break;

  case 806: // output_options_list_content: output_options_list_content ","
#line 2814 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4484 "dhcp4_parser.cc"
    break;

  case 807: // $@132: %empty
#line 2819 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4494 "dhcp4_parser.cc"
    break;

  case 808: // output_entry: "{" $@132 output_params_list "}"
#line 2823 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4502 "dhcp4_parser.cc"
    break;

  case 811: // output_params_list: output_params_list ","
#line 2829 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4510 "dhcp4_parser.cc"
    break;

  case 817: // $@133: %empty
#line 2841 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4519 "dhcp4_parser.cc"
    break;

  case 818: // output: "output" $@133 ":" "constant string"
#line 2844 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4529 "dhcp4_parser.cc"
    break;

  case 819: // flush: "flush" ":" "boolean"
#line 2850 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4539 "dhcp4_parser.cc"
    break;

  case 820: // maxsize: "maxsize" ":" "integer"
#line 2856 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4549 "dhcp4_parser.cc"
    break;

  case 821: // maxver: "maxver" ":" "integer"
#line 2862 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4559 "dhcp4_parser.cc"
    break;

  case 822: // $@134: %empty
#line 2868 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4568 "dhcp4_parser.cc"
    break;

  case 823: // pattern: "pattern" $@134 ":" "constant string"
#line 2871 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4578 "dhcp4_parser.cc"
    break;

  case 824: // $@135: %empty
#line 2877 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4590 "dhcp4_parser.cc"
    break;

  case 825: // compatibility: "compatibility" $@135 ":" "{" compatibility_params "}"
#line 2883 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4599 "dhcp4_parser.cc"
    break;

  case 828: // compatibility_params: compatibility_params ","
#line 2890 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4607 "dhcp4_parser.cc"
    break;

  case 832: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2900 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4617 "dhcp4_parser.cc"
    break;

  case 833: // ignore-rai-link-selection: "ignore-rai-link-selection" ":" "boolean"
#line 2906 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4627 "dhcp4_parser.cc"
    break;


#line 4631 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -980;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     219,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,    22,    44,    52,    65,    79,    94,
     103,   113,   127,   146,   154,   182,   184,   286,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,    44,  -156,    59,   140,   133,   682,
     221,   233,    57,    88,   -10,   -98,   435,    62,  -980,    91,
     144,   163,   218,   243,  -980,    24,  -980,  -980,  -980,  -980,
     293,   304,   319,  -980,  -980,  -980,  -980,  -980,  -980,   337,
     345,   353,   372,   373,   374,   375,   377,   380,   381,   386,
    -980,   387,   388,   401,   402,   421,  -980,  -980,  -980,   422,
     425,   426,  -980,  -980,  -980,   427,  -980,  -980,  -980,  -980,
    -980,   428,   429,   430,  -980,  -980,  -980,  -980,  -980,   431,
    -980,  -980,  -980,  -980,  -980,  -980,   432,   434,   436,  -980,
    -980,   438,  -980,    49,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,   439,   440,   441,   442,  -980,    84,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   443,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,    90,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,    97,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   445,   298,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,   447,  -980,  -980,   444,  -980,  -980,  -980,   446,
    -980,  -980,   448,   454,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,   456,   458,  -980,
    -980,  -980,  -980,   450,   462,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,   115,  -980,  -980,
    -980,   463,  -980,  -980,   465,  -980,   466,   472,  -980,  -980,
     475,   476,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   125,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,   477,   128,  -980,
    -980,  -980,  -980,    44,    44,  -980,   245,   479,  -980,  -980,
     480,   483,   484,   257,   282,   285,   488,   493,   495,   498,
     502,   504,   302,   303,   305,   307,   308,   309,   311,   314,
     318,   321,   322,   507,   323,   324,   312,   332,   335,   528,
     529,   530,   336,   338,   341,   544,   545,   547,   348,   548,
     556,   557,   561,   563,   359,   361,   364,   571,   574,   576,
     577,   579,   378,   582,   586,   587,   601,   602,   603,   399,
     400,   404,   606,   610,  -980,   140,  -980,   611,   612,   613,
     409,   410,   413,   414,   133,  -980,   618,   619,   620,   621,
     622,   623,   423,   624,   625,   627,   682,  -980,   628,   221,
    -980,   629,   630,   631,   632,   633,   635,   638,   639,  -980,
     233,  -980,   640,   641,   449,   642,   643,   644,   451,  -980,
      88,   645,   452,   455,  -980,   -10,   646,   647,    98,  -980,
     457,   648,   650,   460,   651,   461,   464,   653,   654,   468,
     470,   655,   659,   661,   665,   435,  -980,   666,   467,    62,
    -980,  -980,  -980,   668,   673,   674,   676,   677,  -980,  -980,
    -980,   481,   482,   485,   678,   679,   684,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   486,  -980,
    -980,  -980,  -980,  -980,   -59,   487,   489,  -980,  -980,  -980,
     685,   689,   691,  -980,   496,   696,   698,   497,   256,  -980,
    -980,  -980,   701,   702,   703,   704,   710,  -980,   711,   712,
     713,   714,   505,   516,  -980,  -980,  -980,   705,   716,  -980,
     719,   297,   313,  -980,  -980,  -980,  -980,  -980,   519,   520,
     521,   723,   523,   524,  -980,   719,   525,   725,  -980,   527,
    -980,   719,   531,   532,   549,   550,   560,   564,   566,  -980,
     567,   568,  -980,   569,   570,   572,  -980,  -980,   573,  -980,
    -980,  -980,   575,   698,  -980,  -980,   588,   589,  -980,   593,
    -980,  -980,    17,   565,  -980,  -980,   -59,   594,   596,   597,
    -980,   729,  -980,  -980,    44,   140,    62,   133,   325,  -980,
    -980,  -980,   351,   351,   728,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   746,   747,   770,  -980,   773,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,   179,   776,   778,
     785,   130,   -44,   -60,   158,   435,  -980,  -980,   786,  -151,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,   797,  -980,  -980,  -980,  -980,   242,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,   728,  -980,   135,   156,   157,
    -980,  -980,   160,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
     669,   803,   804,   805,   806,   807,   808,  -980,   810,  -980,
    -980,  -980,  -980,  -980,   180,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   187,  -980,   809,   813,  -980,  -980,
     811,   815,  -980,  -980,   814,   816,  -980,  -980,   817,   818,
    -980,  -980,   819,   821,  -980,  -980,  -980,  -980,  -980,  -980,
     138,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   176,  -980,
    -980,   820,   824,  -980,  -980,   822,   826,  -980,   827,   828,
     829,   830,   831,   832,   222,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,   833,   834,   835,  -980,   224,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   239,  -980,
    -980,  -980,   836,  -980,   837,  -980,  -980,  -980,   240,  -980,
    -980,  -980,  -980,  -980,   272,  -980,   273,  -980,   838,   839,
    -980,   275,  -980,  -980,  -980,   616,  -980,   840,   841,  -980,
    -980,  -980,  -980,   842,   843,  -980,  -980,  -980,   844,   847,
     325,  -980,   848,   849,   850,   851,   649,   636,   656,   652,
     657,   658,   660,   853,   662,   856,   858,   862,   864,   351,
    -980,  -980,   351,  -980,   728,   682,  -980,   746,    88,  -980,
     747,   -10,  -980,   770,  1254,  -980,   773,   179,  -980,   266,
     776,  -980,   233,  -980,   778,   -98,  -980,   785,   663,   664,
     667,   670,   671,   672,   130,  -980,   675,   680,   683,   -44,
    -980,   868,   869,   -60,  -980,   686,   871,   687,   872,   158,
    -980,  -980,   198,   786,  -980,   688,   690,  -151,  -980,  -980,
     874,   878,   221,  -980,   797,   879,  -980,  -980,   692,   694,
    -980,    23,   695,   697,   699,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,   206,  -980,   700,   706,   707,   708,  -980,   279,
    -980,   283,  -980,   877,  -980,   881,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,   287,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   882,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,   883,   889,  -980,
    -980,  -980,  -980,  -980,  -980,   885,  -980,   328,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
     709,   717,  -980,  -980,   720,  -980,    44,  -980,  -980,   892,
    -980,  -980,  -980,  -980,  -980,   339,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,   735,   340,  -980,   719,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    1254,  -980,   898,   900,   739,  -980,   266,  -980,  -980,  -980,
    -980,  -980,  -980,   903,   715,   904,   198,  -980,  -980,  -980,
    -980,  -980,   754,   755,  -980,  -980,   825,  -980,   757,  -980,
    -980,  -980,   875,  -980,  -980,   329,  -980,    11,   875,  -980,
    -980,   905,   906,   907,  -980,   342,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,   912,   744,   727,   759,   913,    11,  -980,
     774,  -980,  -980,  -980,   777,  -980,  -980,  -980
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   195,     9,   367,    11,   577,    13,
     604,    15,   497,    17,   506,    19,   545,    21,   329,    23,
     721,    25,   772,    27,    46,    39,     0,     0,     0,     0,
       0,   606,     0,   508,   547,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   770,   180,   213,
       0,     0,     0,   626,   628,   630,   211,   224,   226,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,     0,     0,     0,     0,     0,   157,   164,   166,     0,
       0,     0,   358,   495,   536,     0,   149,   442,   591,   593,
     435,     0,     0,     0,   291,   654,   595,   320,   341,     0,
     306,   688,   702,   719,   170,   172,     0,     0,     0,   782,
     824,     0,   134,     0,    67,    70,    71,    72,    73,    74,
     108,   109,   110,   111,   112,    75,   103,   132,   133,    92,
      93,    94,   116,   117,   118,   119,   120,   121,   122,   123,
     114,   115,   124,   125,   126,   128,   129,   130,    78,    79,
     100,    80,    81,    82,   127,    86,    87,    76,   105,   106,
     107,   104,    77,    84,    85,    98,    99,   101,    95,    96,
      97,    83,    88,    89,    90,    91,   102,   113,   131,   197,
     199,   203,     0,     0,     0,     0,   194,     0,   182,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   420,   422,
     424,   568,   418,   426,     0,   430,   428,   650,   417,   372,
     373,   374,   375,   376,   400,   401,   402,   403,   404,   415,
     390,   391,   405,   406,   407,   408,   409,   410,   411,   412,
     413,   414,   416,     0,   369,   379,   395,   396,   397,   380,
     382,   383,   386,   387,   388,   385,   381,   377,   378,   398,
     399,   384,   392,   393,   394,   389,   589,   588,   584,   585,
     583,     0,   579,   582,   586,   587,   648,   636,   638,   642,
     640,   646,   644,   632,   625,   619,   623,   624,     0,   607,
     608,   620,   621,   622,   616,   611,   617,   613,   614,   615,
     618,   612,     0,   526,   269,     0,   530,   528,   533,     0,
     522,   523,     0,   509,   510,   513,   525,   514,   515,   516,
     532,   517,   518,   519,   520,   521,   562,     0,     0,   560,
     561,   564,   565,     0,   548,   549,   552,   553,   554,   555,
     556,   557,   558,   559,   337,   339,   334,     0,   331,   335,
     336,     0,   758,   745,     0,   748,     0,     0,   752,   756,
       0,     0,   762,   764,   766,   768,   743,   741,   742,     0,
     723,   726,   727,   728,   729,   730,   731,   732,   733,   738,
     734,   735,   736,   737,   739,   740,   779,     0,     0,   774,
     777,   778,    45,    50,     0,    37,    43,     0,    64,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,    69,    66,     0,     0,     0,
       0,     0,     0,     0,   184,   196,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   371,   368,     0,   581,
     578,     0,     0,     0,     0,     0,     0,     0,     0,   605,
     610,   498,     0,     0,     0,     0,     0,     0,     0,   507,
     512,     0,     0,     0,   546,   551,     0,     0,   333,   330,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   725,   722,     0,     0,   776,
     773,    49,    41,     0,     0,     0,     0,     0,   151,   152,
     153,     0,     0,     0,     0,     0,     0,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,     0,   175,
     176,   154,   155,   156,     0,     0,     0,   168,   169,   174,
       0,     0,     0,   148,     0,     0,     0,     0,     0,   432,
     433,   434,     0,     0,     0,     0,     0,   687,     0,     0,
       0,     0,     0,     0,   177,   178,   179,     0,     0,    68,
       0,     0,     0,   207,   208,   209,   210,   183,     0,     0,
       0,     0,     0,     0,   441,     0,     0,     0,   370,     0,
     580,     0,     0,     0,     0,     0,     0,     0,     0,   609,
       0,     0,   524,     0,     0,     0,   535,   511,     0,   566,
     567,   550,     0,     0,   332,   744,     0,     0,   747,     0,
     750,   751,     0,     0,   760,   761,     0,     0,     0,     0,
     724,     0,   781,   775,     0,     0,     0,     0,     0,   627,
     629,   631,     0,     0,   228,   147,   159,   160,   161,   162,
     163,   158,   165,   167,   360,   499,   538,   150,   444,    38,
     592,   594,   437,   438,   439,   440,   436,     0,     0,   597,
     322,     0,     0,     0,     0,     0,   171,   173,     0,     0,
      51,   198,   201,   202,   200,   205,   206,   204,   421,   423,
     425,   570,   419,   427,   431,   429,     0,   590,   649,   637,
     639,   643,   641,   647,   645,   633,   527,   270,   531,   529,
     534,   563,   338,   340,   759,   746,   749,   754,   755,   753,
     757,   763,   765,   767,   769,   228,    42,     0,     0,     0,
     220,   222,     0,   215,   218,   219,   257,   262,   264,   266,
       0,     0,     0,     0,     0,     0,     0,   277,     0,   283,
     285,   287,   289,   256,     0,   235,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,     0,   233,     0,   229,   230,   365,
       0,   361,   362,   504,     0,   500,   501,   543,     0,   539,
     540,   449,     0,   445,   446,   301,   302,   303,   304,   305,
       0,   293,   296,   297,   298,   299,   300,   659,     0,   656,
     602,     0,   598,   599,   327,     0,   323,   324,     0,     0,
       0,     0,     0,     0,     0,   343,   346,   347,   348,   349,
     350,   351,     0,     0,     0,   316,     0,   308,   311,   312,
     313,   314,   315,   698,   700,   697,   695,   696,     0,   690,
     693,   694,     0,   714,     0,   717,   710,   711,     0,   704,
     707,   708,   709,   712,     0,   787,     0,   784,     0,     0,
     831,     0,   826,   829,   830,    53,   575,     0,   571,   572,
     634,   652,   653,     0,     0,    62,   771,   181,     0,     0,
     217,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   237,
     212,   225,     0,   227,   232,     0,   359,   364,   508,   496,
     503,   547,   537,   542,     0,   443,   448,   295,   292,   661,
     658,   655,   606,   596,   601,     0,   321,   326,     0,     0,
       0,     0,     0,     0,   345,   342,     0,     0,     0,   310,
     307,     0,     0,   692,   689,     0,     0,     0,     0,   706,
     703,   720,     0,   786,   783,     0,     0,   828,   825,    55,
       0,    54,     0,   569,   574,     0,   651,   780,     0,     0,
     216,     0,     0,     0,     0,   268,   271,   272,   273,   274,
     275,   276,     0,   282,     0,     0,     0,     0,   236,     0,
     231,     0,   363,     0,   502,     0,   541,   494,   472,   473,
     474,   457,   458,   477,   478,   479,   480,   481,   492,   460,
     461,   482,   483,   484,   485,   486,   487,   488,   489,   490,
     491,   493,   454,   455,   456,   470,   471,   467,   468,   469,
     466,     0,   451,   459,   475,   476,   462,   463,   464,   465,
     447,   294,   682,   684,     0,   677,   678,   679,   680,   681,
     670,   671,   675,   676,   672,   673,   674,     0,   662,   663,
     666,   667,   668,   669,   657,     0,   600,     0,   325,   352,
     353,   354,   355,   356,   357,   344,   317,   318,   319,   309,
       0,     0,   691,   713,     0,   716,     0,   705,   802,     0,
     800,   798,   792,   796,   797,     0,   789,   794,   795,   793,
     785,   832,   833,   827,    52,    57,     0,   573,     0,   221,
     223,   259,   260,   261,   258,   263,   265,   267,   279,   280,
     281,   278,   284,   286,   288,   290,   234,   366,   505,   544,
     453,   450,     0,     0,     0,   660,   665,   603,   328,   699,
     701,   715,   718,     0,     0,     0,   791,   788,    56,   576,
     635,   452,     0,     0,   686,   664,     0,   799,     0,   790,
     683,   685,     0,   801,   807,     0,   804,     0,   806,   803,
     817,     0,     0,     0,   822,     0,   809,   812,   813,   814,
     815,   816,   805,     0,     0,     0,     0,     0,   811,   808,
       0,   819,   820,   821,     0,   810,   818,   823
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,   -51,  -980,  -562,  -980,   164,
    -980,  -980,  -980,  -980,  -980,  -980,  -625,  -980,  -980,  -980,
     -67,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   214,   500,
     -26,     9,    19,   -52,   -30,   -27,     7,    20,    27,    30,
    -980,  -980,  -980,  -980,    37,  -980,  -980,    38,    40,    42,
      43,    48,    50,  -980,   294,    53,  -980,    55,  -980,    56,
      58,    60,  -980,    61,  -980,    63,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,   213,   494,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,    46,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,   205,  -980,    25,  -980,  -701,    32,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,   -63,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,    33,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,    -2,  -980,  -980,  -980,  -980,  -980,  -980,  -980,    54,
    -980,  -980,  -980,    64,   511,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,    67,  -980,  -980,  -980,  -980,  -980,  -980,  -979,
    -980,  -980,  -980,    77,  -980,  -980,  -980,    81,   552,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -975,  -980,   -65,
    -980,    69,  -980,    66,    68,    71,    73,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,    74,  -980,  -980,  -139,   -54,  -980,
    -980,  -980,  -980,  -980,    82,  -980,  -980,  -980,    85,  -980,
     534,  -980,   -41,  -980,  -980,  -980,  -980,  -980,   -40,  -980,
    -980,  -980,  -980,  -980,   -23,  -980,  -980,  -980,    83,  -980,
    -980,  -980,    86,  -980,   533,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,    31,  -980,  -980,  -980,
      41,   578,  -980,  -980,   -45,  -980,    -3,  -980,   -48,  -980,
    -980,  -980,    75,  -980,  -980,  -980,    78,  -980,   554,   -55,
    -980,   -13,  -980,     8,  -980,   316,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -974,  -980,  -980,  -980,  -980,  -980,    87,
    -980,  -980,  -980,  -131,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,    70,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,    72,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,   343,   526,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,   383,   517,  -980,  -980,  -980,  -980,
    -980,  -980,    76,  -980,  -980,  -136,  -980,  -980,  -980,  -980,
    -980,  -980,  -154,  -980,  -980,  -176,  -980,  -980,  -980,  -980,
    -980,  -980,  -980,  -980,  -980,  -980,    80,  -980,  -980
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   730,
      82,    83,    39,    64,    79,    80,   751,   945,  1040,  1041,
     823,    41,    66,    85,   427,    86,    43,    67,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   453,   167,   168,   469,   169,   170,   171,   172,
     173,   174,   175,   459,   721,   176,   460,   177,   461,   178,
     179,   180,   487,   181,   488,   182,   183,   184,   185,   186,
     187,   188,   431,   227,   228,    45,    68,   229,   497,   230,
     498,   754,   231,   499,   757,   232,   233,   234,   235,   189,
     439,   190,   432,   802,   803,   804,   958,   805,   959,   191,
     440,   192,   441,   846,   847,   848,   982,   824,   825,   826,
     962,  1194,   827,   963,   828,   964,   829,   965,   830,   831,
     533,   832,   833,   834,   835,   836,   837,   838,   973,  1201,
     839,   840,   975,   841,   976,   842,   977,   843,   978,   193,
     477,   870,   871,   872,   873,   874,   875,   876,   194,   483,
     906,   907,   908,   909,   910,   195,   480,   885,   886,   887,
    1005,    59,    75,   377,   378,   379,   546,   380,   547,   196,
     481,   894,   895,   896,   897,   898,   899,   900,   901,   197,
     465,   850,   851,   852,   985,    47,    69,   273,   274,   275,
     510,   276,   506,   277,   507,   278,   508,   279,   511,   280,
     514,   281,   513,   198,   199,   200,   201,   473,   736,   286,
     202,   470,   862,   863,   864,   994,  1111,  1112,   203,   466,
      53,    72,   854,   855,   856,   988,    55,    73,   342,   343,
     344,   345,   346,   347,   348,   532,   349,   536,   350,   535,
     351,   352,   537,   353,   204,   467,   858,   859,   860,   991,
      57,    74,   363,   364,   365,   366,   367,   541,   368,   369,
     370,   371,   288,   509,   947,   948,   949,  1042,    49,    70,
     301,   302,   303,   518,   205,   471,   206,   472,   207,   479,
     881,   882,   883,  1002,    51,    71,   318,   319,   320,   208,
     436,   209,   437,   210,   438,   324,   528,   952,  1045,   325,
     522,   326,   523,   327,   525,   328,   524,   329,   527,   330,
     526,   331,   521,   295,   515,   953,   211,   478,   878,   879,
     999,  1137,  1138,  1139,  1140,  1141,  1212,  1142,  1213,  1143,
     212,   213,   484,   918,   919,   920,  1021,   921,  1022,   214,
     485,   928,   929,   930,   931,  1026,   932,   933,  1028,   215,
     486,    61,    76,   399,   400,   401,   402,   552,   403,   404,
     554,   405,   406,   407,   557,   789,   408,   558,   409,   551,
     410,   411,   412,   561,   413,   562,   414,   563,   415,   564,
     216,   430,    63,    77,   418,   419,   420,   567,   421,   217,
     492,   936,   937,  1032,  1175,  1176,  1177,  1178,  1225,  1179,
    1223,  1245,  1246,  1247,  1255,  1256,  1257,  1263,  1258,  1259,
    1260,  1261,  1267,   218,   493,   941,   942,   943,   944
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     152,   226,   248,   297,   314,   298,   340,   359,   376,   396,
     341,   360,   844,    78,   292,  1103,   321,   252,   332,  1104,
    1119,   291,    28,   236,   289,   304,   316,   428,   354,   372,
     764,   397,   429,   361,   362,   787,   768,   374,   375,   253,
     938,   939,   254,   249,   128,   129,   287,   300,   315,    29,
      81,    30,   495,    31,   729,   151,   293,   496,   322,    40,
     128,   129,  1191,  1192,  1193,   237,   290,   305,   317,    84,
     355,   373,    42,   398,   416,   417,   255,   294,   250,   323,
     334,   356,   335,   336,   357,   358,    44,   504,   251,   256,
     913,   914,   505,   516,   128,   129,   257,   422,   517,   258,
     519,    46,   902,   903,   904,   520,   259,   260,   151,   261,
      48,   262,   263,   716,   717,   718,   719,   264,   548,   265,
      50,   729,   266,   549,   267,   268,   333,   269,   565,   270,
     271,   569,   272,   566,    52,   282,   570,   283,   495,   299,
     284,   997,   285,   955,   998,   123,   151,   423,   219,   220,
     720,    87,   221,    54,    88,   222,   223,   224,   225,   569,
     504,    56,   151,   960,   956,   957,    89,   424,   961,    90,
      91,    92,    93,    94,    95,    96,    97,    98,   334,  1000,
     335,   336,  1001,   979,   337,   338,   339,   788,   980,    58,
     979,    60,   128,   129,  1250,   981,   151,  1251,  1252,  1253,
    1254,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,  1014,   425,  1019,   123,   124,
    1015,  1103,  1020,   374,   375,  1104,  1119,   128,   129,   125,
     126,   127,  1023,  1029,   128,   129,   426,  1024,  1030,   130,
      32,    33,    34,    35,   131,   132,   133,   134,   135,  1198,
    1199,  1200,   128,   129,   136,    93,    94,    95,   888,   889,
     890,   891,   892,   893,   137,   565,  1033,   138,  1037,  1034,
    1031,  1069,   979,  1038,   139,   140,   516,  1206,   334,   141,
    1210,  1207,   142,    62,   151,  1211,   143,   433,    93,    94,
      95,   530,   128,   129,   865,   866,   867,   868,   434,   869,
     124,   922,   923,   924,   752,   753,   144,   145,   146,   147,
     148,   149,   124,   435,   296,   128,   129,    99,   100,   101,
     150,   548,  1248,   755,   756,  1249,  1218,   128,   129,   151,
     245,   442,  1226,   519,   246,  1268,   151,  1227,  1229,   443,
    1269,   306,   800,   801,   123,   124,   334,   444,   307,   308,
     309,   310,   311,   312,   925,   313,   732,   733,   734,   735,
     128,   129,   571,   572,   313,   950,   445,   446,   447,   448,
    1168,   449,  1169,  1170,   450,   451,  1122,  1123,  1124,   806,
     452,   454,   455,   807,   808,   809,   810,   811,   812,   813,
     814,   815,   816,   817,   151,   456,   457,   818,   819,   820,
     821,   822,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,   458,   462,   151,   152,   463,
     464,   468,   474,   475,   476,   482,   489,   226,   490,   151,
     491,   334,   494,   500,   501,   502,   503,   512,   534,   248,
     538,   573,   297,   529,   298,   531,   539,   540,   544,   236,
     542,   292,   543,   314,   252,   545,   578,   550,   291,   553,
     555,   289,   151,   340,   304,   321,   556,   341,   359,   559,
     560,   568,   360,   574,   575,   316,   253,   576,   577,   254,
     249,   579,   581,   287,   580,   354,   300,   582,   396,   583,
     372,   237,   584,   293,   361,   362,   585,   315,   586,   587,
     588,   598,   589,   290,   590,   591,   305,   322,   592,   593,
     397,   601,   594,   255,   294,   250,   595,   317,   596,   597,
     599,   600,   604,   605,   606,   251,   256,   355,   323,   128,
     129,   602,   373,   257,   603,   607,   258,   608,   610,   611,
     609,   612,   614,   259,   260,   613,   261,   151,   262,   263,
     615,   616,   398,  1230,   264,   617,   265,   618,   619,   266,
     620,   267,   268,   621,   269,   622,   270,   271,   623,   272,
     624,   625,   282,   626,   283,   627,   628,   284,   299,   285,
     629,   630,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   631,   632,   633,   634,   635,
     637,   394,   395,   636,   638,   640,   641,   642,   643,   644,
     645,   646,   648,   649,   650,   651,   652,   653,   655,   656,
     654,   657,   659,   661,   662,   663,   664,   665,   152,   666,
     226,   151,   667,   668,   670,   671,   673,   674,   675,   678,
     682,   683,   686,   796,   687,   689,   672,   692,   693,   696,
     676,   679,   236,   697,   680,   698,   685,   688,   690,   699,
     701,   691,   704,   966,   702,   905,   915,   694,   396,   695,
     705,   706,   940,   707,   708,   712,   713,   709,   710,   714,
     724,   711,   715,   722,   725,   723,   726,   911,   916,   926,
     397,   728,   727,   731,   237,    30,   737,   738,   739,   740,
     748,   746,    91,    92,    93,    94,    95,   741,   742,   743,
     744,   745,   747,   749,   750,   758,   759,   760,   761,   762,
     763,   765,   766,   767,   795,   845,   790,   769,   770,   912,
     917,   927,   398,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   849,   853,   771,   772,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   773,   238,   239,   240,
     774,   124,   775,   776,   777,   778,   779,   857,   780,   781,
     861,   782,   126,   877,   241,   880,   128,   129,   242,   243,
     244,   130,   884,   935,   784,   785,   131,   132,   133,   786,
     792,   245,   793,   794,   946,   246,   136,   967,   968,   969,
     970,   971,   972,   247,   974,   983,   984,   986,   987,   990,
     989,   993,  1039,   992,   996,   995,  1003,  1004,  1006,  1007,
    1242,  1008,  1009,  1010,  1011,  1012,  1013,  1016,  1017,  1018,
    1025,  1027,  1035,  1036,  1044,  1056,  1043,   783,  1048,  1047,
    1046,  1049,  1051,  1052,  1053,  1054,  1055,  1062,   144,   145,
    1064,  1058,  1065,  1057,  1059,  1060,  1066,  1061,  1067,  1063,
    1149,  1150,  1160,  1161,  1151,  1164,  1166,  1152,  1153,  1154,
    1184,  1185,  1244,  1188,  1156,  1208,  1214,  1157,   151,  1209,
    1158,  1215,  1216,  1217,  1165,  1163,  1224,  1181,  1189,  1182,
    1190,  1195,  1232,  1196,  1233,  1197,  1202,  1236,  1238,  1264,
    1265,  1266,  1203,  1204,  1205,  1219,  1270,  1274,   248,   797,
     799,   340,  1237,  1220,   359,   341,  1221,  1077,   360,  1105,
     292,  1102,  1125,   252,  1272,   314,  1129,   291,   376,  1116,
     289,  1228,  1081,   354,  1134,  1130,   372,   321,  1234,  1114,
     361,   362,   905,  1271,  1132,   253,   915,   316,   254,   249,
    1240,  1241,   287,  1243,  1082,  1171,  1273,  1083,  1078,  1172,
     940,  1113,   293,  1126,   911,   297,  1131,   298,   916,   315,
    1276,  1117,   290,  1277,   926,   355,  1135,  1173,   373,   322,
     791,  1115,   255,   294,   250,   639,  1133,   304,   647,   317,
     954,  1084,  1118,  1079,   251,   256,  1050,  1136,  1127,  1070,
     323,  1068,   257,  1080,  1085,   258,   912,  1159,  1128,   300,
     917,  1086,   259,   260,  1087,   261,   927,   262,   263,  1174,
    1121,  1088,  1089,   264,  1090,   265,  1091,  1092,   266,   305,
     267,   268,  1093,   269,  1094,   270,   271,  1095,   272,  1096,
    1097,   282,  1098,   283,  1099,  1100,   284,  1101,   285,   684,
    1107,  1148,  1108,  1106,  1072,  1109,  1071,  1110,   658,  1147,
    1120,  1231,  1074,  1073,   677,  1187,  1076,  1075,   681,  1146,
    1145,  1155,   951,  1186,   669,  1235,   703,  1144,   934,   798,
    1239,   700,  1275,  1162,  1262,     0,     0,   660,     0,     0,
       0,  1167,     0,     0,     0,     0,     0,     0,     0,  1180,
       0,   299,     0,     0,     0,  1222,     0,  1183,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1077,     0,  1105,     0,  1102,     0,  1125,
       0,     0,     0,  1129,     0,  1116,     0,     0,  1081,  1171,
       0,  1134,  1130,  1172,     0,  1114,     0,     0,     0,     0,
       0,  1132,     0,     0,     0,     0,     0,     0,     0,     0,
    1082,  1173,     0,  1083,  1078,     0,     0,  1113,     0,     0,
    1126,     0,     0,  1131,     0,     0,     0,  1117,     0,     0,
       0,     0,     0,  1135,     0,     0,     0,  1115,     0,     0,
       0,     0,     0,  1133,     0,     0,     0,  1084,  1118,  1079,
       0,     0,     0,  1174,  1136,  1127,     0,     0,     0,  1080,
    1085,     0,     0,     0,     0,  1128,     0,  1086,     0,     0,
    1087,     0,     0,     0,     0,     0,     0,  1088,  1089,     0,
    1090,     0,  1091,  1092,     0,     0,     0,     0,  1093,     0,
    1094,     0,     0,  1095,     0,  1096,  1097,     0,  1098,     0,
    1099,  1100,     0,  1101,     0,     0,  1107,     0,  1108,  1106,
       0,  1109,     0,  1110,    91,    92,    93,    94,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,     0,     0,     0,     0,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,     0,
       0,     0,     0,   124,   334,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   126,     0,     0,     0,   128,   129,
       0,   243,     0,   130,     0,     0,     0,     0,   131,   132,
     133,     0,     0,   245,     0,     0,     0,   246,     0,     0,
       0,     0,     0,     0,     0,   247,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     144,   145,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     151
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,   713,    64,    69,   994,    71,    69,    72,   994,
     994,    69,     0,    68,    69,    70,    71,     3,    73,    74,
     655,    76,     8,    74,    74,    18,   661,   135,   136,    69,
     191,   192,    69,    69,   104,   105,    69,    70,    71,     5,
     206,     7,     3,     9,   616,   206,    69,     8,    71,     7,
     104,   105,    39,    40,    41,    68,    69,    70,    71,    10,
      73,    74,     7,    76,    12,    13,    69,    69,    69,    71,
      90,    91,    92,    93,    94,    95,     7,     3,    69,    69,
     150,   151,     8,     3,   104,   105,    69,     6,     8,    69,
       3,     7,   146,   147,   148,     8,    69,    69,   206,    69,
       7,    69,    69,   172,   173,   174,   175,    69,     3,    69,
       7,   683,    69,     8,    69,    69,    38,    69,     3,    69,
      69,     3,    69,     8,     7,    69,     8,    69,     3,    70,
      69,     3,    69,     8,     6,    88,   206,     3,    15,    16,
     209,    11,    19,     7,    14,    22,    23,    24,    25,     3,
       3,     7,   206,     3,     8,     8,    26,     4,     8,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    90,     3,
      92,    93,     6,     3,    96,    97,    98,   170,     8,     7,
       3,     7,   104,   105,   183,     8,   206,   186,   187,   188,
     189,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,     3,     8,     3,    88,    89,
       8,  1210,     8,   135,   136,  1210,  1210,   104,   105,    99,
     100,   101,     3,     3,   104,   105,     3,     8,     8,   109,
     206,   207,   208,   209,   114,   115,   116,   117,   118,    53,
      54,    55,   104,   105,   124,    32,    33,    34,   138,   139,
     140,   141,   142,   143,   134,     3,     3,   137,     3,     6,
       8,   982,     3,     8,   144,   145,     3,     8,    90,   149,
       3,     8,   152,     7,   206,     8,   156,     4,    32,    33,
      34,     3,   104,   105,   125,   126,   127,   128,     4,   130,
      89,   153,   154,   155,    17,    18,   176,   177,   178,   179,
     180,   181,    89,     4,   103,   104,   105,    61,    62,    63,
     190,     3,     3,    20,    21,     6,     8,   104,   105,   206,
     119,     4,     3,     3,   123,     3,   206,     8,     8,     4,
       8,   118,    27,    28,    88,    89,    90,     4,   125,   126,
     127,   128,   129,   130,   206,   132,   110,   111,   112,   113,
     104,   105,   423,   424,   132,   133,     4,     4,     4,     4,
     182,     4,   184,   185,     4,     4,   120,   121,   122,    38,
       4,     4,     4,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,   206,     4,     4,    56,    57,    58,
      59,    60,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,     4,     4,   206,   495,     4,
       4,     4,     4,     4,     4,     4,     4,   504,     4,   206,
       4,    90,     4,     4,     4,     4,     4,     4,     4,   516,
       4,   206,   519,     8,   519,     8,     8,     3,     8,   504,
       4,   516,     4,   530,   516,     3,   209,     4,   516,     4,
       4,   516,   206,   540,   519,   530,     4,   540,   545,     4,
       4,     4,   545,     4,     4,   530,   516,     4,     4,   516,
     516,   209,     4,   516,   209,   540,   519,     4,   565,     4,
     545,   504,     4,   516,   545,   545,     4,   530,     4,   207,
     207,     4,   207,   516,   207,   207,   519,   530,   209,   208,
     565,   209,   208,   516,   516,   516,   208,   530,   207,   207,
     207,   207,     4,     4,     4,   516,   516,   540,   530,   104,
     105,   209,   545,   516,   209,   209,   516,   209,     4,     4,
     209,     4,     4,   516,   516,   207,   516,   206,   516,   516,
       4,     4,   565,  1188,   516,     4,   516,     4,   209,   516,
     209,   516,   516,   209,   516,     4,   516,   516,     4,   516,
       4,     4,   516,     4,   516,   207,     4,   516,   519,   516,
       4,     4,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,     4,     4,     4,   209,   209,
       4,   176,   177,   209,     4,     4,     4,     4,   209,   209,
     207,   207,     4,     4,     4,     4,     4,     4,     4,     4,
     207,     4,     4,     4,     4,     4,     4,     4,   705,     4,
     707,   206,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   704,     4,     4,   207,     4,     4,     4,
     209,   209,   707,     4,   209,     4,   209,   207,   207,     4,
       4,   207,     4,     4,   207,   742,   743,   209,   745,   209,
       7,     7,   749,     7,     7,     7,     7,   206,   206,     5,
       5,   206,   206,   206,     5,   206,     5,   742,   743,   744,
     745,     5,   206,   206,   707,     7,     5,     5,     5,     5,
       5,   206,    30,    31,    32,    33,    34,     7,     7,     7,
       7,     7,   206,     7,     5,   206,   206,   206,     5,   206,
     206,   206,     7,   206,     5,     7,   171,   206,   206,   742,
     743,   744,   745,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,     7,     7,   206,   206,    75,    76,    77,
      78,    79,    80,    81,    82,    83,   206,    85,    86,    87,
     206,    89,   206,   206,   206,   206,   206,     7,   206,   206,
       7,   206,   100,     7,   102,     7,   104,   105,   106,   107,
     108,   109,     7,     7,   206,   206,   114,   115,   116,   206,
     206,   119,   206,   206,     7,   123,   124,     4,     4,     4,
       4,     4,     4,   131,     4,     6,     3,     6,     3,     3,
       6,     3,   206,     6,     3,     6,     6,     3,     6,     3,
       5,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,   209,     6,   683,     4,     6,
       8,     4,     4,     4,     4,     4,   207,     4,   176,   177,
       4,   209,     4,   207,   207,   207,     4,   207,     4,   207,
     207,   207,     4,     4,   207,     4,     4,   207,   207,   207,
       6,     3,     7,     4,   209,     8,     4,   207,   206,     8,
     207,     8,     3,     8,   207,   209,     4,   209,   206,   209,
     206,   206,     4,   206,     4,   206,   206,     4,     4,     4,
       4,     4,   206,   206,   206,   206,     4,     4,   985,   705,
     707,   988,   207,   206,   991,   988,   206,   994,   991,   994,
     985,   994,   999,   985,   207,  1002,   999,   985,  1005,   994,
     985,   206,   994,   988,   999,   999,   991,  1002,   209,   994,
     991,   991,  1019,   209,   999,   985,  1023,  1002,   985,   985,
     206,   206,   985,   206,   994,  1032,   207,   994,   994,  1032,
    1037,   994,   985,   999,  1019,  1042,   999,  1042,  1023,  1002,
     206,   994,   985,   206,  1029,   988,   999,  1032,   991,  1002,
     696,   994,   985,   985,   985,   495,   999,  1042,   504,  1002,
     795,   994,   994,   994,   985,   985,   960,   999,   999,   984,
    1002,   979,   985,   994,   994,   985,  1019,  1019,   999,  1042,
    1023,   994,   985,   985,   994,   985,  1029,   985,   985,  1032,
     997,   994,   994,   985,   994,   985,   994,   994,   985,  1042,
     985,   985,   994,   985,   994,   985,   985,   994,   985,   994,
     994,   985,   994,   985,   994,   994,   985,   994,   985,   548,
     994,  1007,   994,   994,   987,   994,   985,   994,   516,  1005,
     996,  1210,   990,   988,   540,  1044,   993,   991,   545,  1004,
    1002,  1014,   766,  1042,   530,  1216,   569,  1000,   745,   706,
    1226,   565,  1268,  1023,  1248,    -1,    -1,   519,    -1,    -1,
      -1,  1029,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1033,
      -1,  1042,    -1,    -1,    -1,  1166,    -1,  1037,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1210,    -1,  1210,    -1,  1210,    -1,  1216,
      -1,    -1,    -1,  1216,    -1,  1210,    -1,    -1,  1210,  1226,
      -1,  1216,  1216,  1226,    -1,  1210,    -1,    -1,    -1,    -1,
      -1,  1216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1210,  1226,    -1,  1210,  1210,    -1,    -1,  1210,    -1,    -1,
    1216,    -1,    -1,  1216,    -1,    -1,    -1,  1210,    -1,    -1,
      -1,    -1,    -1,  1216,    -1,    -1,    -1,  1210,    -1,    -1,
      -1,    -1,    -1,  1216,    -1,    -1,    -1,  1210,  1210,  1210,
      -1,    -1,    -1,  1226,  1216,  1216,    -1,    -1,    -1,  1210,
    1210,    -1,    -1,    -1,    -1,  1216,    -1,  1210,    -1,    -1,
    1210,    -1,    -1,    -1,    -1,    -1,    -1,  1210,  1210,    -1,
    1210,    -1,  1210,  1210,    -1,    -1,    -1,    -1,  1210,    -1,
    1210,    -1,    -1,  1210,    -1,  1210,  1210,    -1,  1210,    -1,
    1210,  1210,    -1,  1210,    -1,    -1,  1210,    -1,  1210,  1210,
      -1,  1210,    -1,  1210,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    -1,
      -1,    -1,    -1,    89,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,    -1,    -1,    -1,   104,   105,
      -1,   107,    -1,   109,    -1,    -1,    -1,    -1,   114,   115,
     116,    -1,    -1,   119,    -1,    -1,    -1,   123,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   131,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     176,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     206
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,     0,     5,
       7,     9,   206,   207,   208,   209,   225,   226,   227,   232,
       7,   241,     7,   246,     7,   295,     7,   405,     7,   488,
       7,   504,     7,   440,     7,   446,     7,   470,     7,   381,
       7,   571,     7,   602,   233,   228,   242,   247,   296,   406,
     489,   505,   441,   447,   471,   382,   572,   603,   225,   234,
     235,   206,   230,   231,    10,   243,   245,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    88,    89,    99,   100,   101,   104,   105,
     109,   114,   115,   116,   117,   118,   124,   134,   137,   144,
     145,   149,   152,   156,   176,   177,   178,   179,   180,   181,
     190,   206,   240,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   263,   264,   266,
     267,   268,   269,   270,   271,   272,   275,   277,   279,   280,
     281,   283,   285,   286,   287,   288,   289,   290,   291,   309,
     311,   319,   321,   359,   368,   375,   389,   399,   423,   424,
     425,   426,   430,   438,   464,   494,   496,   498,   509,   511,
     513,   536,   550,   551,   559,   569,   600,   609,   633,    15,
      16,    19,    22,    23,    24,    25,   240,   293,   294,   297,
     299,   302,   305,   306,   307,   308,   494,   496,    85,    86,
      87,   102,   106,   107,   108,   119,   123,   131,   240,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   264,
     267,   268,   269,   270,   271,   272,   275,   277,   279,   280,
     281,   283,   285,   407,   408,   409,   411,   413,   415,   417,
     419,   421,   423,   424,   425,   426,   429,   464,   482,   494,
     496,   498,   509,   511,   513,   533,   103,   240,   419,   421,
     464,   490,   491,   492,   494,   496,   118,   125,   126,   127,
     128,   129,   130,   132,   240,   464,   494,   496,   506,   507,
     508,   509,   511,   513,   515,   519,   521,   523,   525,   527,
     529,   531,   438,    38,    90,    92,    93,    96,    97,    98,
     240,   339,   448,   449,   450,   451,   452,   453,   454,   456,
     458,   460,   461,   463,   494,   496,    91,    94,    95,   240,
     339,   452,   458,   472,   473,   474,   475,   476,   478,   479,
     480,   481,   494,   496,   135,   136,   240,   383,   384,   385,
     387,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   176,   177,   240,   494,   496,   573,
     574,   575,   576,   578,   579,   581,   582,   583,   586,   588,
     590,   591,   592,   594,   596,   598,    12,    13,   604,   605,
     606,   608,     6,     3,     4,     8,     3,   244,     3,     8,
     601,   292,   312,     4,     4,     4,   510,   512,   514,   310,
     320,   322,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   262,     4,     4,     4,     4,     4,   273,
     276,   278,     4,     4,     4,   400,   439,   465,     4,   265,
     431,   495,   497,   427,     4,     4,     4,   360,   537,   499,
     376,   390,     4,   369,   552,   560,   570,   282,   284,     4,
       4,     4,   610,   634,     4,     3,     8,   298,   300,   303,
       4,     4,     4,     4,     3,     8,   412,   414,   416,   483,
     410,   418,     4,   422,   420,   534,     3,     8,   493,     3,
       8,   532,   520,   522,   526,   524,   530,   528,   516,     8,
       3,     8,   455,   340,     4,   459,   457,   462,     4,     8,
       3,   477,     4,     4,     8,     3,   386,   388,     3,     8,
       4,   589,   577,     4,   580,     4,     4,   584,   587,     4,
       4,   593,   595,   597,   599,     3,     8,   607,     4,     3,
       8,   225,   225,   206,     4,     4,     4,     4,   209,   209,
     209,     4,     4,     4,     4,     4,     4,   207,   207,   207,
     207,   207,   209,   208,   208,   208,   207,   207,     4,   207,
     207,   209,   209,   209,     4,     4,     4,   209,   209,   209,
       4,     4,     4,   207,     4,     4,     4,     4,     4,   209,
     209,   209,     4,     4,     4,     4,     4,   207,     4,     4,
       4,     4,     4,     4,   209,   209,   209,     4,     4,   249,
       4,     4,     4,   209,   209,   207,   207,   294,     4,     4,
       4,     4,     4,     4,   207,     4,     4,     4,   408,     4,
     491,     4,     4,     4,     4,     4,     4,     4,     4,   508,
       4,     4,   207,     4,     4,     4,   209,   450,     4,   209,
     209,   474,     4,     4,   384,   209,     4,     4,   207,     4,
     207,   207,     4,     4,   209,   209,     4,     4,     4,     4,
     574,     4,   207,   605,     4,     7,     7,     7,     7,   206,
     206,   206,     7,     7,     5,   206,   172,   173,   174,   175,
     209,   274,   206,   206,     5,     5,     5,   206,     5,   227,
     229,   206,   110,   111,   112,   113,   428,     5,     5,     5,
       5,     7,     7,     7,     7,     7,   206,   206,     5,     7,
       5,   236,    17,    18,   301,    20,    21,   304,   206,   206,
     206,     5,   206,   206,   236,   206,     7,   206,   236,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   229,   206,   206,   206,    18,   170,   585,
     171,   274,   206,   206,   206,     5,   225,   248,   604,   293,
      27,    28,   313,   314,   315,   317,    38,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    56,    57,
      58,    59,    60,   240,   327,   328,   329,   332,   334,   336,
     338,   339,   341,   342,   343,   344,   345,   346,   347,   350,
     351,   353,   355,   357,   327,     7,   323,   324,   325,     7,
     401,   402,   403,     7,   442,   443,   444,     7,   466,   467,
     468,     7,   432,   433,   434,   125,   126,   127,   128,   130,
     361,   362,   363,   364,   365,   366,   367,     7,   538,   539,
       7,   500,   501,   502,     7,   377,   378,   379,   138,   139,
     140,   141,   142,   143,   391,   392,   393,   394,   395,   396,
     397,   398,   146,   147,   148,   240,   370,   371,   372,   373,
     374,   494,   496,   150,   151,   240,   494,   496,   553,   554,
     555,   557,   153,   154,   155,   206,   494,   496,   561,   562,
     563,   564,   566,   567,   573,     7,   611,   612,   191,   192,
     240,   635,   636,   637,   638,   237,     7,   484,   485,   486,
     133,   515,   517,   535,   323,     8,     8,     8,   316,   318,
       3,     8,   330,   333,   335,   337,     4,     4,     4,     4,
       4,     4,     4,   348,     4,   352,   354,   356,   358,     3,
       8,     8,   326,     6,     3,   404,     6,     3,   445,     6,
       3,   469,     6,     3,   435,     6,     3,     3,     6,   540,
       3,     6,   503,     6,     3,   380,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   556,   558,     3,     8,     4,   565,     4,   568,     3,
       8,     8,   613,     3,     6,     4,     4,     3,     8,   206,
     238,   239,   487,     6,     3,   518,     8,     6,     4,     4,
     314,     4,     4,     4,     4,   207,   209,   207,   209,   207,
     207,   207,     4,   207,     4,     4,     4,     4,   328,   327,
     325,   407,   403,   448,   444,   472,   468,   240,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   264,   267,
     268,   269,   270,   271,   272,   275,   277,   279,   280,   281,
     283,   285,   339,   399,   417,   419,   421,   423,   424,   425,
     426,   436,   437,   464,   494,   496,   509,   511,   513,   533,
     434,   362,   120,   121,   122,   240,   250,   251,   252,   339,
     438,   464,   494,   496,   509,   511,   513,   541,   542,   543,
     544,   545,   547,   549,   539,   506,   502,   383,   379,   207,
     207,   207,   207,   207,   207,   392,   209,   207,   207,   371,
       4,     4,   554,   209,     4,   207,     4,   562,   182,   184,
     185,   240,   339,   494,   496,   614,   615,   616,   617,   619,
     612,   209,   209,   636,     6,     3,   490,   486,     4,   206,
     206,    39,    40,    41,   331,   206,   206,   206,    53,    54,
      55,   349,   206,   206,   206,   206,     8,     8,     8,     8,
       3,     8,   546,   548,     4,     8,     3,     8,     8,   206,
     206,   206,   225,   620,     4,   618,     3,     8,   206,     8,
     236,   437,     4,     4,   209,   543,     4,   207,     4,   615,
     206,   206,     5,   206,     7,   621,   622,   623,     3,     6,
     183,   186,   187,   188,   189,   624,   625,   626,   628,   629,
     630,   631,   622,   627,     4,     4,     4,   632,     3,     8,
       4,   209,   207,   207,     4,   625,   206,   206
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   210,   212,   211,   213,   211,   214,   211,   215,   211,
     216,   211,   217,   211,   218,   211,   219,   211,   220,   211,
     221,   211,   222,   211,   223,   211,   224,   211,   225,   225,
     225,   225,   225,   225,   225,   226,   228,   227,   229,   230,
     230,   231,   231,   231,   233,   232,   234,   234,   235,   235,
     235,   237,   236,   238,   238,   239,   239,   239,   240,   242,
     241,   244,   243,   243,   245,   247,   246,   248,   248,   248,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   249,   249,   249,   249,   249,
     249,   249,   249,   249,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   262,   261,   263,   265,
     264,   266,   267,   268,   269,   270,   271,   273,   272,   274,
     274,   274,   274,   274,   276,   275,   278,   277,   279,   280,
     282,   281,   284,   283,   285,   286,   287,   288,   289,   290,
     292,   291,   293,   293,   293,   294,   294,   294,   294,   294,
     294,   294,   294,   294,   294,   296,   295,   298,   297,   300,
     299,   301,   301,   303,   302,   304,   304,   305,   306,   307,
     308,   310,   309,   312,   311,   313,   313,   313,   314,   314,
     316,   315,   318,   317,   320,   319,   322,   321,   323,   323,
     324,   324,   324,   326,   325,   327,   327,   327,   328,   328,
     328,   328,   328,   328,   328,   328,   328,   328,   328,   328,
     328,   328,   328,   328,   328,   328,   328,   330,   329,   331,
     331,   331,   333,   332,   335,   334,   337,   336,   338,   340,
     339,   341,   342,   343,   344,   345,   346,   348,   347,   349,
     349,   349,   350,   352,   351,   354,   353,   356,   355,   358,
     357,   360,   359,   361,   361,   361,   362,   362,   362,   362,
     362,   363,   364,   365,   366,   367,   369,   368,   370,   370,
     370,   371,   371,   371,   371,   371,   371,   372,   373,   374,
     376,   375,   377,   377,   378,   378,   378,   380,   379,   382,
     381,   383,   383,   383,   383,   384,   384,   386,   385,   388,
     387,   390,   389,   391,   391,   391,   392,   392,   392,   392,
     392,   392,   393,   394,   395,   396,   397,   398,   400,   399,
     401,   401,   402,   402,   402,   404,   403,   406,   405,   407,
     407,   407,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   408,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   410,   409,
     412,   411,   414,   413,   416,   415,   418,   417,   420,   419,
     422,   421,   423,   424,   425,   427,   426,   428,   428,   428,
     428,   429,   431,   430,   432,   432,   433,   433,   433,   435,
     434,   436,   436,   436,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   439,   438,   441,   440,   442,
     442,   443,   443,   443,   445,   444,   447,   446,   448,   448,
     449,   449,   449,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   451,   452,   453,   455,   454,   457,   456,
     459,   458,   460,   462,   461,   463,   465,   464,   466,   466,
     467,   467,   467,   469,   468,   471,   470,   472,   472,   473,
     473,   473,   474,   474,   474,   474,   474,   474,   474,   474,
     474,   475,   477,   476,   478,   479,   480,   481,   483,   482,
     484,   484,   485,   485,   485,   487,   486,   489,   488,   490,
     490,   490,   491,   491,   491,   491,   491,   491,   491,   493,
     492,   495,   494,   497,   496,   499,   498,   500,   500,   501,
     501,   501,   503,   502,   505,   504,   506,   506,   507,   507,
     507,   508,   508,   508,   508,   508,   508,   508,   508,   508,
     508,   508,   508,   508,   508,   508,   510,   509,   512,   511,
     514,   513,   516,   515,   518,   517,   520,   519,   522,   521,
     524,   523,   526,   525,   528,   527,   530,   529,   532,   531,
     534,   533,   535,   535,   537,   536,   538,   538,   538,   540,
     539,   541,   541,   542,   542,   542,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   544,   546,   545,   548,   547,   549,   550,   552,   551,
     553,   553,   553,   554,   554,   554,   554,   554,   556,   555,
     558,   557,   560,   559,   561,   561,   561,   562,   562,   562,
     562,   562,   562,   563,   565,   564,   566,   568,   567,   570,
     569,   572,   571,   573,   573,   573,   574,   574,   574,   574,
     574,   574,   574,   574,   574,   574,   574,   574,   574,   574,
     574,   574,   574,   574,   575,   577,   576,   578,   580,   579,
     581,   582,   584,   583,   585,   585,   587,   586,   589,   588,
     590,   591,   593,   592,   595,   594,   597,   596,   599,   598,
     601,   600,   603,   602,   604,   604,   604,   605,   605,   607,
     606,   608,   610,   609,   611,   611,   611,   613,   612,   614,
     614,   614,   615,   615,   615,   615,   615,   615,   615,   616,
     618,   617,   620,   619,   621,   621,   621,   623,   622,   624,
     624,   624,   625,   625,   625,   625,   625,   627,   626,   628,
     629,   630,   632,   631,   634,   633,   635,   635,   635,   636,
     636,   636,   637,   638
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
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     0,     4,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     4,     0,     4,     3,     3,     3,     3,     3,     3,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     3,     3,
       3,     0,     6,     0,     6,     1,     3,     2,     1,     1,
       0,     4,     0,     4,     0,     6,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     0,     4,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     0,     1,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     1,     0,     6,     1,     3,     2,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     3,     3,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     3,     0,     4,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       3,     3,     0,     4,     1,     1,     0,     4,     0,     4,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     2,     1,     1,     0,
       6,     3,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     2,     0,     4,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4,     0,     6,     1,     3,     2,     1,
       1,     1,     3,     3
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
  "\"allocator\"", "\"shared-networks\"", "\"pools\"", "\"pool\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"id\"", "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"",
  "\"global\"", "\"all\"", "\"reservations-global\"",
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
  "parked_packet_limit", "allocator", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "hostname_char_set", "$@25", "hostname_char_replacement", "$@26",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "early_global_reservations_lookup",
  "ip_reservations_unique", "reservations_lookup_first",
  "interfaces_config", "$@27", "interfaces_config_params",
  "interfaces_config_param", "sub_interfaces4", "$@28", "interfaces_list",
  "$@29", "dhcp_socket_type", "$@30", "socket_type", "outbound_interface",
  "$@31", "outbound_interface_value", "re_detect",
  "service_sockets_require_all", "service_sockets_retry_wait_time",
  "service_sockets_max_retries", "lease_database", "$@32", "sanity_checks",
  "$@33", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@34", "extended_info_checks", "$@35", "hosts_database", "$@36",
  "hosts_databases", "$@37", "database_list", "not_empty_database_list",
  "database", "$@38", "database_map_params", "database_map_param",
  "database_type", "$@39", "db_type", "user", "$@40", "password", "$@41",
  "host", "$@42", "port", "name", "$@43", "persist", "lfc_interval",
  "readonly", "connect_timeout", "max_reconnect_tries",
  "reconnect_wait_time", "on_fail", "$@44", "on_fail_mode",
  "max_row_errors", "trust_anchor", "$@45", "cert_file", "$@46",
  "key_file", "$@47", "cipher_list", "$@48",
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
  "option_data_always_send", "pools_list", "$@82", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@83", "sub_pool4", "$@84",
  "pool_params", "pool_param", "pool_entry", "$@85", "user_context",
  "$@86", "comment", "$@87", "reservations", "$@88", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@89", "sub_reservation",
  "$@90", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@91", "server_hostname", "$@92",
  "boot_file_name", "$@93", "ip_address", "$@94", "ip_addresses", "$@95",
  "duid", "$@96", "hw_address", "$@97", "client_id_value", "$@98",
  "circuit_id_value", "$@99", "flex_id_value", "$@100", "hostname",
  "$@101", "reservation_client_classes", "$@102", "relay", "$@103",
  "relay_map", "client_classes", "$@104", "client_classes_list",
  "client_class_entry", "$@105", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@106",
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
  "ignore-rai-link-selection", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   299,   299,   299,   300,   300,   301,   301,   302,   302,
     303,   303,   304,   304,   305,   305,   306,   306,   307,   307,
     308,   308,   309,   309,   310,   310,   311,   311,   319,   320,
     321,   322,   323,   324,   325,   328,   333,   333,   344,   347,
     348,   351,   356,   362,   367,   367,   374,   375,   378,   382,
     386,   392,   392,   399,   400,   403,   407,   411,   421,   430,
     430,   445,   445,   459,   462,   468,   468,   477,   478,   479,
     486,   487,   488,   489,   490,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   502,   503,   504,   505,
     506,   507,   508,   509,   510,   511,   512,   513,   514,   515,
     516,   517,   518,   519,   520,   521,   522,   523,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   538,   539,   540,   541,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   553,   559,   565,   571,   577,
     583,   589,   595,   601,   607,   613,   619,   619,   628,   634,
     634,   643,   649,   655,   661,   667,   673,   679,   679,   688,
     691,   694,   697,   700,   706,   706,   715,   715,   724,   730,
     736,   736,   745,   745,   754,   760,   766,   772,   778,   784,
     790,   790,   802,   803,   804,   809,   810,   811,   812,   813,
     814,   815,   816,   817,   818,   821,   821,   830,   830,   841,
     841,   849,   850,   853,   853,   861,   863,   867,   873,   879,
     885,   891,   891,   904,   904,   915,   916,   917,   922,   923,
     926,   926,   945,   945,   963,   963,   976,   976,   987,   988,
     991,   992,   993,   998,   998,  1008,  1009,  1010,  1015,  1016,
    1017,  1018,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1026,
    1027,  1028,  1029,  1030,  1031,  1032,  1033,  1036,  1036,  1044,
    1045,  1046,  1049,  1049,  1058,  1058,  1067,  1067,  1076,  1082,
    1082,  1091,  1097,  1103,  1109,  1115,  1121,  1127,  1127,  1135,
    1136,  1137,  1140,  1146,  1146,  1155,  1155,  1164,  1164,  1173,
    1173,  1182,  1182,  1193,  1194,  1195,  1200,  1201,  1202,  1203,
    1204,  1207,  1212,  1217,  1222,  1227,  1234,  1234,  1247,  1248,
    1249,  1254,  1255,  1256,  1257,  1258,  1259,  1262,  1268,  1274,
    1280,  1280,  1291,  1292,  1295,  1296,  1297,  1302,  1302,  1312,
    1312,  1322,  1323,  1324,  1327,  1330,  1331,  1334,  1334,  1343,
    1343,  1352,  1352,  1364,  1365,  1366,  1371,  1372,  1373,  1374,
    1375,  1376,  1379,  1385,  1391,  1397,  1403,  1409,  1418,  1418,
    1432,  1433,  1436,  1437,  1438,  1447,  1447,  1473,  1473,  1484,
    1485,  1486,  1492,  1493,  1494,  1495,  1496,  1497,  1498,  1499,
    1500,  1501,  1502,  1503,  1504,  1505,  1506,  1507,  1508,  1509,
    1510,  1511,  1512,  1513,  1514,  1515,  1516,  1517,  1518,  1519,
    1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,  1528,  1529,
    1530,  1531,  1532,  1533,  1534,  1535,  1536,  1537,  1540,  1540,
    1549,  1549,  1558,  1558,  1567,  1567,  1576,  1576,  1585,  1585,
    1594,  1594,  1605,  1611,  1617,  1623,  1623,  1631,  1632,  1633,
    1634,  1637,  1645,  1645,  1657,  1658,  1662,  1663,  1664,  1669,
    1669,  1677,  1678,  1679,  1684,  1685,  1686,  1687,  1688,  1689,
    1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,
    1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,
    1710,  1711,  1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,
    1720,  1721,  1722,  1723,  1724,  1731,  1731,  1745,  1745,  1754,
    1755,  1758,  1759,  1760,  1767,  1767,  1782,  1782,  1796,  1797,
    1800,  1801,  1802,  1807,  1808,  1809,  1810,  1811,  1812,  1813,
    1814,  1815,  1816,  1819,  1821,  1827,  1829,  1829,  1838,  1838,
    1847,  1847,  1856,  1858,  1858,  1867,  1877,  1877,  1890,  1891,
    1896,  1897,  1898,  1905,  1905,  1917,  1917,  1929,  1930,  1935,
    1936,  1937,  1944,  1945,  1946,  1947,  1948,  1949,  1950,  1951,
    1952,  1955,  1957,  1957,  1966,  1968,  1970,  1976,  1985,  1985,
    1998,  1999,  2002,  2003,  2004,  2009,  2009,  2019,  2019,  2029,
    2030,  2031,  2036,  2037,  2038,  2039,  2040,  2041,  2042,  2045,
    2045,  2054,  2054,  2079,  2079,  2109,  2109,  2120,  2121,  2124,
    2125,  2126,  2131,  2131,  2140,  2140,  2149,  2150,  2153,  2154,
    2155,  2161,  2162,  2163,  2164,  2165,  2166,  2167,  2168,  2169,
    2170,  2171,  2172,  2173,  2174,  2175,  2178,  2178,  2187,  2187,
    2196,  2196,  2205,  2205,  2214,  2214,  2225,  2225,  2234,  2234,
    2243,  2243,  2252,  2252,  2261,  2261,  2270,  2270,  2279,  2279,
    2293,  2293,  2304,  2305,  2311,  2311,  2322,  2323,  2324,  2329,
    2329,  2339,  2340,  2343,  2344,  2345,  2350,  2351,  2352,  2353,
    2354,  2355,  2356,  2357,  2358,  2359,  2360,  2361,  2362,  2363,
    2364,  2367,  2369,  2369,  2378,  2378,  2387,  2395,  2403,  2403,
    2414,  2415,  2416,  2421,  2422,  2423,  2424,  2425,  2428,  2428,
    2437,  2437,  2449,  2449,  2462,  2463,  2464,  2469,  2470,  2471,
    2472,  2473,  2474,  2477,  2483,  2483,  2492,  2498,  2498,  2508,
    2508,  2521,  2521,  2531,  2532,  2533,  2538,  2539,  2540,  2541,
    2542,  2543,  2544,  2545,  2546,  2547,  2548,  2549,  2550,  2551,
    2552,  2553,  2554,  2555,  2558,  2564,  2564,  2573,  2579,  2579,
    2588,  2594,  2600,  2600,  2609,  2610,  2613,  2613,  2623,  2623,
    2633,  2640,  2647,  2647,  2656,  2656,  2666,  2666,  2676,  2676,
    2688,  2688,  2700,  2700,  2710,  2711,  2712,  2718,  2719,  2722,
    2722,  2733,  2741,  2741,  2754,  2755,  2756,  2762,  2762,  2770,
    2771,  2772,  2777,  2778,  2779,  2780,  2781,  2782,  2783,  2786,
    2792,  2792,  2801,  2801,  2812,  2813,  2814,  2819,  2819,  2827,
    2828,  2829,  2834,  2835,  2836,  2837,  2838,  2841,  2841,  2850,
    2856,  2862,  2868,  2868,  2877,  2877,  2888,  2889,  2890,  2895,
    2896,  2897,  2900,  2906
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
#line 6269 "dhcp4_parser.cc"

#line 2912 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
