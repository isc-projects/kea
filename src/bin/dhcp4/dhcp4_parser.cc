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

  case 133: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 551 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 134: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 557 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 135: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 563 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 136: // renew_timer: "renew-timer" ":" "integer"
#line 569 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 137: // rebind_timer: "rebind-timer" ":" "integer"
#line 575 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 138: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 581 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 139: // t1_percent: "t1-percent" ":" "floating point"
#line 587 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 140: // t2_percent: "t2-percent" ":" "floating point"
#line 593 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 141: // cache_threshold: "cache-threshold" ":" "floating point"
#line 599 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 142: // cache_max_age: "cache-max-age" ":" "integer"
#line 605 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 143: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 611 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 144: // $@20: %empty
#line 617 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 145: // server_tag: "server-tag" $@20 ":" "constant string"
#line 620 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 146: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 626 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 147: // echo_client_id: "echo-client-id" ":" "boolean"
#line 632 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1270 "dhcp4_parser.cc"
    break;

  case 148: // match_client_id: "match-client-id" ":" "boolean"
#line 638 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1280 "dhcp4_parser.cc"
    break;

  case 149: // authoritative: "authoritative" ":" "boolean"
#line 644 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1290 "dhcp4_parser.cc"
    break;

  case 150: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 650 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1300 "dhcp4_parser.cc"
    break;

  case 151: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 656 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1310 "dhcp4_parser.cc"
    break;

  case 152: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 662 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1320 "dhcp4_parser.cc"
    break;

  case 153: // $@21: %empty
#line 668 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 154: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 671 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1338 "dhcp4_parser.cc"
    break;

  case 155: // ddns_replace_client_name_value: "when-present"
#line 677 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1346 "dhcp4_parser.cc"
    break;

  case 156: // ddns_replace_client_name_value: "never"
#line 680 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1354 "dhcp4_parser.cc"
    break;

  case 157: // ddns_replace_client_name_value: "always"
#line 683 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1362 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "when-not-present"
#line 686 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1370 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "boolean"
#line 689 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1379 "dhcp4_parser.cc"
    break;

  case 160: // $@22: %empty
#line 695 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1388 "dhcp4_parser.cc"
    break;

  case 161: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 698 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1398 "dhcp4_parser.cc"
    break;

  case 162: // $@23: %empty
#line 704 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 163: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 707 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 164: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 713 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1427 "dhcp4_parser.cc"
    break;

  case 165: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 719 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1437 "dhcp4_parser.cc"
    break;

  case 166: // $@24: %empty
#line 725 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 167: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 728 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 168: // $@25: %empty
#line 734 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 169: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 737 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 170: // store_extended_info: "store-extended-info" ":" "boolean"
#line 743 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 171: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 749 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1495 "dhcp4_parser.cc"
    break;

  case 172: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 755 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 173: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 761 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 174: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 767 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 175: // $@26: %empty
#line 773 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1537 "dhcp4_parser.cc"
    break;

  case 176: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 779 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1547 "dhcp4_parser.cc"
    break;

  case 179: // interfaces_config_params: interfaces_config_params ","
#line 787 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1555 "dhcp4_parser.cc"
    break;

  case 187: // $@27: %empty
#line 801 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1565 "dhcp4_parser.cc"
    break;

  case 188: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 805 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 189: // $@28: %empty
#line 810 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 190: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 816 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1595 "dhcp4_parser.cc"
    break;

  case 191: // $@29: %empty
#line 821 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 192: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 824 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1613 "dhcp4_parser.cc"
    break;

  case 193: // socket_type: "raw"
#line 829 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1619 "dhcp4_parser.cc"
    break;

  case 194: // socket_type: "udp"
#line 830 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1625 "dhcp4_parser.cc"
    break;

  case 195: // $@30: %empty
#line 833 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 196: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 836 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1643 "dhcp4_parser.cc"
    break;

  case 197: // outbound_interface_value: "same-as-inbound"
#line 841 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1651 "dhcp4_parser.cc"
    break;

  case 198: // outbound_interface_value: "use-routing"
#line 843 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1659 "dhcp4_parser.cc"
    break;

  case 199: // re_detect: "re-detect" ":" "boolean"
#line 847 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1669 "dhcp4_parser.cc"
    break;

  case 200: // $@31: %empty
#line 854 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1681 "dhcp4_parser.cc"
    break;

  case 201: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 860 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1692 "dhcp4_parser.cc"
    break;

  case 202: // $@32: %empty
#line 867 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1704 "dhcp4_parser.cc"
    break;

  case 203: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 873 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1713 "dhcp4_parser.cc"
    break;

  case 206: // sanity_checks_params: sanity_checks_params ","
#line 880 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1721 "dhcp4_parser.cc"
    break;

  case 208: // $@33: %empty
#line 887 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1730 "dhcp4_parser.cc"
    break;

  case 209: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 890 "dhcp4_parser.yy"
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
#line 1750 "dhcp4_parser.cc"
    break;

  case 210: // $@34: %empty
#line 906 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1762 "dhcp4_parser.cc"
    break;

  case 211: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 912 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1773 "dhcp4_parser.cc"
    break;

  case 212: // $@35: %empty
#line 919 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1785 "dhcp4_parser.cc"
    break;

  case 213: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 925 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1794 "dhcp4_parser.cc"
    break;

  case 218: // not_empty_database_list: not_empty_database_list ","
#line 936 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1802 "dhcp4_parser.cc"
    break;

  case 219: // $@36: %empty
#line 941 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1812 "dhcp4_parser.cc"
    break;

  case 220: // database: "{" $@36 database_map_params "}"
#line 945 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1822 "dhcp4_parser.cc"
    break;

  case 223: // database_map_params: database_map_params ","
#line 953 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1830 "dhcp4_parser.cc"
    break;

  case 250: // $@37: %empty
#line 986 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1839 "dhcp4_parser.cc"
    break;

  case 251: // database_type: "type" $@37 ":" db_type
#line 989 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1848 "dhcp4_parser.cc"
    break;

  case 252: // db_type: "memfile"
#line 994 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1854 "dhcp4_parser.cc"
    break;

  case 253: // db_type: "mysql"
#line 995 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1860 "dhcp4_parser.cc"
    break;

  case 254: // db_type: "postgresql"
#line 996 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1866 "dhcp4_parser.cc"
    break;

  case 255: // db_type: "cql"
#line 997 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1872 "dhcp4_parser.cc"
    break;

  case 256: // $@38: %empty
#line 1000 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 257: // user: "user" $@38 ":" "constant string"
#line 1003 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1891 "dhcp4_parser.cc"
    break;

  case 258: // $@39: %empty
#line 1009 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1900 "dhcp4_parser.cc"
    break;

  case 259: // password: "password" $@39 ":" "constant string"
#line 1012 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1910 "dhcp4_parser.cc"
    break;

  case 260: // $@40: %empty
#line 1018 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1919 "dhcp4_parser.cc"
    break;

  case 261: // host: "host" $@40 ":" "constant string"
#line 1021 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1929 "dhcp4_parser.cc"
    break;

  case 262: // port: "port" ":" "integer"
#line 1027 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1939 "dhcp4_parser.cc"
    break;

  case 263: // $@41: %empty
#line 1033 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1948 "dhcp4_parser.cc"
    break;

  case 264: // name: "name" $@41 ":" "constant string"
#line 1036 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1958 "dhcp4_parser.cc"
    break;

  case 265: // persist: "persist" ":" "boolean"
#line 1042 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1968 "dhcp4_parser.cc"
    break;

  case 266: // lfc_interval: "lfc-interval" ":" "integer"
#line 1048 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1978 "dhcp4_parser.cc"
    break;

  case 267: // readonly: "readonly" ":" "boolean"
#line 1054 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1988 "dhcp4_parser.cc"
    break;

  case 268: // connect_timeout: "connect-timeout" ":" "integer"
#line 1060 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1998 "dhcp4_parser.cc"
    break;

  case 269: // request_timeout: "request-timeout" ":" "integer"
#line 1066 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 2008 "dhcp4_parser.cc"
    break;

  case 270: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1072 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 2018 "dhcp4_parser.cc"
    break;

  case 271: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1078 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 2028 "dhcp4_parser.cc"
    break;

  case 272: // $@42: %empty
#line 1084 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2037 "dhcp4_parser.cc"
    break;

  case 273: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1087 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 2047 "dhcp4_parser.cc"
    break;

  case 274: // $@43: %empty
#line 1093 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2056 "dhcp4_parser.cc"
    break;

  case 275: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1096 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 2066 "dhcp4_parser.cc"
    break;

  case 276: // $@44: %empty
#line 1102 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp4_parser.cc"
    break;

  case 277: // consistency: "consistency" $@44 ":" "constant string"
#line 1105 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 2085 "dhcp4_parser.cc"
    break;

  case 278: // $@45: %empty
#line 1111 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2094 "dhcp4_parser.cc"
    break;

  case 279: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1114 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2104 "dhcp4_parser.cc"
    break;

  case 280: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1120 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2114 "dhcp4_parser.cc"
    break;

  case 281: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1126 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2124 "dhcp4_parser.cc"
    break;

  case 282: // $@46: %empty
#line 1132 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2133 "dhcp4_parser.cc"
    break;

  case 283: // on_fail: "on-fail" $@46 ":" on_fail_mode
#line 1135 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2142 "dhcp4_parser.cc"
    break;

  case 284: // on_fail_mode: "stop-retry-exit"
#line 1140 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2148 "dhcp4_parser.cc"
    break;

  case 285: // on_fail_mode: "serve-retry-exit"
#line 1141 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2154 "dhcp4_parser.cc"
    break;

  case 286: // on_fail_mode: "serve-retry-continue"
#line 1142 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2160 "dhcp4_parser.cc"
    break;

  case 287: // max_row_errors: "max-row-errors" ":" "integer"
#line 1145 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2170 "dhcp4_parser.cc"
    break;

  case 288: // $@47: %empty
#line 1151 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2179 "dhcp4_parser.cc"
    break;

  case 289: // trust_anchor: "trust-anchor" $@47 ":" "constant string"
#line 1154 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2189 "dhcp4_parser.cc"
    break;

  case 290: // $@48: %empty
#line 1160 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2198 "dhcp4_parser.cc"
    break;

  case 291: // cert_file: "cert-file" $@48 ":" "constant string"
#line 1163 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2208 "dhcp4_parser.cc"
    break;

  case 292: // $@49: %empty
#line 1169 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2217 "dhcp4_parser.cc"
    break;

  case 293: // key_file: "key-file" $@49 ":" "constant string"
#line 1172 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2227 "dhcp4_parser.cc"
    break;

  case 294: // $@50: %empty
#line 1178 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2236 "dhcp4_parser.cc"
    break;

  case 295: // cipher_list: "cipher-list" $@50 ":" "constant string"
#line 1181 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2246 "dhcp4_parser.cc"
    break;

  case 296: // $@51: %empty
#line 1187 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2258 "dhcp4_parser.cc"
    break;

  case 297: // host_reservation_identifiers: "host-reservation-identifiers" $@51 ":" "[" host_reservation_identifiers_list "]"
#line 1193 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2267 "dhcp4_parser.cc"
    break;

  case 300: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1200 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2275 "dhcp4_parser.cc"
    break;

  case 306: // duid_id: "duid"
#line 1212 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2284 "dhcp4_parser.cc"
    break;

  case 307: // hw_address_id: "hw-address"
#line 1217 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2293 "dhcp4_parser.cc"
    break;

  case 308: // circuit_id: "circuit-id"
#line 1222 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2302 "dhcp4_parser.cc"
    break;

  case 309: // client_id: "client-id"
#line 1227 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2311 "dhcp4_parser.cc"
    break;

  case 310: // flex_id: "flex-id"
#line 1232 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2320 "dhcp4_parser.cc"
    break;

  case 311: // $@52: %empty
#line 1239 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2332 "dhcp4_parser.cc"
    break;

  case 312: // dhcp_multi_threading: "multi-threading" $@52 ":" "{" multi_threading_params "}"
#line 1245 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2343 "dhcp4_parser.cc"
    break;

  case 315: // multi_threading_params: multi_threading_params ","
#line 1254 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2351 "dhcp4_parser.cc"
    break;

  case 322: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1267 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2361 "dhcp4_parser.cc"
    break;

  case 323: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1273 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2371 "dhcp4_parser.cc"
    break;

  case 324: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1279 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2381 "dhcp4_parser.cc"
    break;

  case 325: // $@53: %empty
#line 1285 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2393 "dhcp4_parser.cc"
    break;

  case 326: // hooks_libraries: "hooks-libraries" $@53 ":" "[" hooks_libraries_list "]"
#line 1291 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2402 "dhcp4_parser.cc"
    break;

  case 331: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1302 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2410 "dhcp4_parser.cc"
    break;

  case 332: // $@54: %empty
#line 1307 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2420 "dhcp4_parser.cc"
    break;

  case 333: // hooks_library: "{" $@54 hooks_params "}"
#line 1311 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2430 "dhcp4_parser.cc"
    break;

  case 334: // $@55: %empty
#line 1317 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2440 "dhcp4_parser.cc"
    break;

  case 335: // sub_hooks_library: "{" $@55 hooks_params "}"
#line 1321 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2450 "dhcp4_parser.cc"
    break;

  case 338: // hooks_params: hooks_params ","
#line 1329 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2458 "dhcp4_parser.cc"
    break;

  case 342: // $@56: %empty
#line 1339 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2467 "dhcp4_parser.cc"
    break;

  case 343: // library: "library" $@56 ":" "constant string"
#line 1342 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2477 "dhcp4_parser.cc"
    break;

  case 344: // $@57: %empty
#line 1348 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2486 "dhcp4_parser.cc"
    break;

  case 345: // parameters: "parameters" $@57 ":" map_value
#line 1351 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2495 "dhcp4_parser.cc"
    break;

  case 346: // $@58: %empty
#line 1357 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2507 "dhcp4_parser.cc"
    break;

  case 347: // expired_leases_processing: "expired-leases-processing" $@58 ":" "{" expired_leases_params "}"
#line 1363 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2517 "dhcp4_parser.cc"
    break;

  case 350: // expired_leases_params: expired_leases_params ","
#line 1371 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2525 "dhcp4_parser.cc"
    break;

  case 357: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1384 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2535 "dhcp4_parser.cc"
    break;

  case 358: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1390 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2545 "dhcp4_parser.cc"
    break;

  case 359: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1396 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2555 "dhcp4_parser.cc"
    break;

  case 360: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1402 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 361: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1408 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2575 "dhcp4_parser.cc"
    break;

  case 362: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1414 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2585 "dhcp4_parser.cc"
    break;

  case 363: // $@59: %empty
#line 1423 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2597 "dhcp4_parser.cc"
    break;

  case 364: // subnet4_list: "subnet4" $@59 ":" "[" subnet4_list_content "]"
#line 1429 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2606 "dhcp4_parser.cc"
    break;

  case 369: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1443 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2614 "dhcp4_parser.cc"
    break;

  case 370: // $@60: %empty
#line 1452 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2624 "dhcp4_parser.cc"
    break;

  case 371: // subnet4: "{" $@60 subnet4_params "}"
#line 1456 "dhcp4_parser.yy"
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
#line 2650 "dhcp4_parser.cc"
    break;

  case 372: // $@61: %empty
#line 1478 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2660 "dhcp4_parser.cc"
    break;

  case 373: // sub_subnet4: "{" $@61 subnet4_params "}"
#line 1482 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2670 "dhcp4_parser.cc"
    break;

  case 376: // subnet4_params: subnet4_params ","
#line 1491 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2678 "dhcp4_parser.cc"
    break;

  case 422: // $@62: %empty
#line 1544 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2687 "dhcp4_parser.cc"
    break;

  case 423: // subnet: "subnet" $@62 ":" "constant string"
#line 1547 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2697 "dhcp4_parser.cc"
    break;

  case 424: // $@63: %empty
#line 1553 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2706 "dhcp4_parser.cc"
    break;

  case 425: // subnet_4o6_interface: "4o6-interface" $@63 ":" "constant string"
#line 1556 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2716 "dhcp4_parser.cc"
    break;

  case 426: // $@64: %empty
#line 1562 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2725 "dhcp4_parser.cc"
    break;

  case 427: // subnet_4o6_interface_id: "4o6-interface-id" $@64 ":" "constant string"
#line 1565 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2735 "dhcp4_parser.cc"
    break;

  case 428: // $@65: %empty
#line 1571 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2744 "dhcp4_parser.cc"
    break;

  case 429: // subnet_4o6_subnet: "4o6-subnet" $@65 ":" "constant string"
#line 1574 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2754 "dhcp4_parser.cc"
    break;

  case 430: // $@66: %empty
#line 1580 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2763 "dhcp4_parser.cc"
    break;

  case 431: // interface: "interface" $@66 ":" "constant string"
#line 1583 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2773 "dhcp4_parser.cc"
    break;

  case 432: // $@67: %empty
#line 1589 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2782 "dhcp4_parser.cc"
    break;

  case 433: // client_class: "client-class" $@67 ":" "constant string"
#line 1592 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 434: // $@68: %empty
#line 1598 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2804 "dhcp4_parser.cc"
    break;

  case 435: // require_client_classes: "require-client-classes" $@68 ":" list_strings
#line 1604 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2813 "dhcp4_parser.cc"
    break;

  case 436: // reservations_global: "reservations-global" ":" "boolean"
#line 1609 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 437: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1615 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2833 "dhcp4_parser.cc"
    break;

  case 438: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1621 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2843 "dhcp4_parser.cc"
    break;

  case 439: // $@69: %empty
#line 1627 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2852 "dhcp4_parser.cc"
    break;

  case 440: // reservation_mode: "reservation-mode" $@69 ":" hr_mode
#line 1630 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2861 "dhcp4_parser.cc"
    break;

  case 441: // hr_mode: "disabled"
#line 1635 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2867 "dhcp4_parser.cc"
    break;

  case 442: // hr_mode: "out-of-pool"
#line 1636 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2873 "dhcp4_parser.cc"
    break;

  case 443: // hr_mode: "global"
#line 1637 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2879 "dhcp4_parser.cc"
    break;

  case 444: // hr_mode: "all"
#line 1638 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2885 "dhcp4_parser.cc"
    break;

  case 445: // id: "id" ":" "integer"
#line 1641 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2895 "dhcp4_parser.cc"
    break;

  case 446: // $@70: %empty
#line 1649 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2907 "dhcp4_parser.cc"
    break;

  case 447: // shared_networks: "shared-networks" $@70 ":" "[" shared_networks_content "]"
#line 1655 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2916 "dhcp4_parser.cc"
    break;

  case 452: // shared_networks_list: shared_networks_list ","
#line 1668 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2924 "dhcp4_parser.cc"
    break;

  case 453: // $@71: %empty
#line 1673 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2934 "dhcp4_parser.cc"
    break;

  case 454: // shared_network: "{" $@71 shared_network_params "}"
#line 1677 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 457: // shared_network_params: shared_network_params ","
#line 1683 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2950 "dhcp4_parser.cc"
    break;

  case 498: // $@72: %empty
#line 1734 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2962 "dhcp4_parser.cc"
    break;

  case 499: // option_def_list: "option-def" $@72 ":" "[" option_def_list_content "]"
#line 1740 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2971 "dhcp4_parser.cc"
    break;

  case 500: // $@73: %empty
#line 1748 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2980 "dhcp4_parser.cc"
    break;

  case 501: // sub_option_def_list: "{" $@73 option_def_list "}"
#line 1751 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2988 "dhcp4_parser.cc"
    break;

  case 506: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1763 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2996 "dhcp4_parser.cc"
    break;

  case 507: // $@74: %empty
#line 1770 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3006 "dhcp4_parser.cc"
    break;

  case 508: // option_def_entry: "{" $@74 option_def_params "}"
#line 1774 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 509: // $@75: %empty
#line 1785 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3028 "dhcp4_parser.cc"
    break;

  case 510: // sub_option_def: "{" $@75 option_def_params "}"
#line 1789 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3040 "dhcp4_parser.cc"
    break;

  case 515: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1805 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3048 "dhcp4_parser.cc"
    break;

  case 527: // code: "code" ":" "integer"
#line 1824 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3058 "dhcp4_parser.cc"
    break;

  case 529: // $@76: %empty
#line 1832 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3067 "dhcp4_parser.cc"
    break;

  case 530: // option_def_type: "type" $@76 ":" "constant string"
#line 1835 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3077 "dhcp4_parser.cc"
    break;

  case 531: // $@77: %empty
#line 1841 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3086 "dhcp4_parser.cc"
    break;

  case 532: // option_def_record_types: "record-types" $@77 ":" "constant string"
#line 1844 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3096 "dhcp4_parser.cc"
    break;

  case 533: // $@78: %empty
#line 1850 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3105 "dhcp4_parser.cc"
    break;

  case 534: // space: "space" $@78 ":" "constant string"
#line 1853 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3115 "dhcp4_parser.cc"
    break;

  case 536: // $@79: %empty
#line 1861 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3124 "dhcp4_parser.cc"
    break;

  case 537: // option_def_encapsulate: "encapsulate" $@79 ":" "constant string"
#line 1864 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3134 "dhcp4_parser.cc"
    break;

  case 538: // option_def_array: "array" ":" "boolean"
#line 1870 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3144 "dhcp4_parser.cc"
    break;

  case 539: // $@80: %empty
#line 1880 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3156 "dhcp4_parser.cc"
    break;

  case 540: // option_data_list: "option-data" $@80 ":" "[" option_data_list_content "]"
#line 1886 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3165 "dhcp4_parser.cc"
    break;

  case 545: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1901 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3173 "dhcp4_parser.cc"
    break;

  case 546: // $@81: %empty
#line 1908 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3183 "dhcp4_parser.cc"
    break;

  case 547: // option_data_entry: "{" $@81 option_data_params "}"
#line 1912 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3192 "dhcp4_parser.cc"
    break;

  case 548: // $@82: %empty
#line 1920 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3202 "dhcp4_parser.cc"
    break;

  case 549: // sub_option_data: "{" $@82 option_data_params "}"
#line 1924 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3211 "dhcp4_parser.cc"
    break;

  case 554: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1940 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3219 "dhcp4_parser.cc"
    break;

  case 565: // $@83: %empty
#line 1960 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3228 "dhcp4_parser.cc"
    break;

  case 566: // option_data_data: "data" $@83 ":" "constant string"
#line 1963 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3238 "dhcp4_parser.cc"
    break;

  case 569: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1973 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3248 "dhcp4_parser.cc"
    break;

  case 570: // option_data_always_send: "always-send" ":" "boolean"
#line 1979 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3258 "dhcp4_parser.cc"
    break;

  case 571: // $@84: %empty
#line 1988 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3270 "dhcp4_parser.cc"
    break;

  case 572: // pools_list: "pools" $@84 ":" "[" pools_list_content "]"
#line 1994 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3279 "dhcp4_parser.cc"
    break;

  case 577: // not_empty_pools_list: not_empty_pools_list ","
#line 2007 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3287 "dhcp4_parser.cc"
    break;

  case 578: // $@85: %empty
#line 2012 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3297 "dhcp4_parser.cc"
    break;

  case 579: // pool_list_entry: "{" $@85 pool_params "}"
#line 2016 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3307 "dhcp4_parser.cc"
    break;

  case 580: // $@86: %empty
#line 2022 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3317 "dhcp4_parser.cc"
    break;

  case 581: // sub_pool4: "{" $@86 pool_params "}"
#line 2026 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3327 "dhcp4_parser.cc"
    break;

  case 584: // pool_params: pool_params ","
#line 2034 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3335 "dhcp4_parser.cc"
    break;

  case 592: // $@87: %empty
#line 2048 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3344 "dhcp4_parser.cc"
    break;

  case 593: // pool_entry: "pool" $@87 ":" "constant string"
#line 2051 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3354 "dhcp4_parser.cc"
    break;

  case 594: // $@88: %empty
#line 2057 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3362 "dhcp4_parser.cc"
    break;

  case 595: // user_context: "user-context" $@88 ":" map_value
#line 2059 "dhcp4_parser.yy"
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
#line 3389 "dhcp4_parser.cc"
    break;

  case 596: // $@89: %empty
#line 2082 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3397 "dhcp4_parser.cc"
    break;

  case 597: // comment: "comment" $@89 ":" "constant string"
#line 2084 "dhcp4_parser.yy"
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
#line 3426 "dhcp4_parser.cc"
    break;

  case 598: // $@90: %empty
#line 2112 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3438 "dhcp4_parser.cc"
    break;

  case 599: // reservations: "reservations" $@90 ":" "[" reservations_list "]"
#line 2118 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3447 "dhcp4_parser.cc"
    break;

  case 604: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2129 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3455 "dhcp4_parser.cc"
    break;

  case 605: // $@91: %empty
#line 2134 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3465 "dhcp4_parser.cc"
    break;

  case 606: // reservation: "{" $@91 reservation_params "}"
#line 2138 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3474 "dhcp4_parser.cc"
    break;

  case 607: // $@92: %empty
#line 2143 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3484 "dhcp4_parser.cc"
    break;

  case 608: // sub_reservation: "{" $@92 reservation_params "}"
#line 2147 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3493 "dhcp4_parser.cc"
    break;

  case 613: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2158 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3501 "dhcp4_parser.cc"
    break;

  case 629: // $@93: %empty
#line 2181 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3510 "dhcp4_parser.cc"
    break;

  case 630: // next_server: "next-server" $@93 ":" "constant string"
#line 2184 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3520 "dhcp4_parser.cc"
    break;

  case 631: // $@94: %empty
#line 2190 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3529 "dhcp4_parser.cc"
    break;

  case 632: // server_hostname: "server-hostname" $@94 ":" "constant string"
#line 2193 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3539 "dhcp4_parser.cc"
    break;

  case 633: // $@95: %empty
#line 2199 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3548 "dhcp4_parser.cc"
    break;

  case 634: // boot_file_name: "boot-file-name" $@95 ":" "constant string"
#line 2202 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3558 "dhcp4_parser.cc"
    break;

  case 635: // $@96: %empty
#line 2208 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3567 "dhcp4_parser.cc"
    break;

  case 636: // ip_address: "ip-address" $@96 ":" "constant string"
#line 2211 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3577 "dhcp4_parser.cc"
    break;

  case 637: // $@97: %empty
#line 2217 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3589 "dhcp4_parser.cc"
    break;

  case 638: // ip_addresses: "ip-addresses" $@97 ":" list_strings
#line 2223 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3598 "dhcp4_parser.cc"
    break;

  case 639: // $@98: %empty
#line 2228 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3607 "dhcp4_parser.cc"
    break;

  case 640: // duid: "duid" $@98 ":" "constant string"
#line 2231 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3617 "dhcp4_parser.cc"
    break;

  case 641: // $@99: %empty
#line 2237 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3626 "dhcp4_parser.cc"
    break;

  case 642: // hw_address: "hw-address" $@99 ":" "constant string"
#line 2240 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3636 "dhcp4_parser.cc"
    break;

  case 643: // $@100: %empty
#line 2246 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3645 "dhcp4_parser.cc"
    break;

  case 644: // client_id_value: "client-id" $@100 ":" "constant string"
#line 2249 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3655 "dhcp4_parser.cc"
    break;

  case 645: // $@101: %empty
#line 2255 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3664 "dhcp4_parser.cc"
    break;

  case 646: // circuit_id_value: "circuit-id" $@101 ":" "constant string"
#line 2258 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3674 "dhcp4_parser.cc"
    break;

  case 647: // $@102: %empty
#line 2264 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 648: // flex_id_value: "flex-id" $@102 ":" "constant string"
#line 2267 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3693 "dhcp4_parser.cc"
    break;

  case 649: // $@103: %empty
#line 2273 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 650: // hostname: "hostname" $@103 ":" "constant string"
#line 2276 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 651: // $@104: %empty
#line 2282 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3724 "dhcp4_parser.cc"
    break;

  case 652: // reservation_client_classes: "client-classes" $@104 ":" list_strings
#line 2288 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 653: // $@105: %empty
#line 2296 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3745 "dhcp4_parser.cc"
    break;

  case 654: // relay: "relay" $@105 ":" "{" relay_map "}"
#line 2302 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3754 "dhcp4_parser.cc"
    break;

  case 657: // $@106: %empty
#line 2314 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3766 "dhcp4_parser.cc"
    break;

  case 658: // client_classes: "client-classes" $@106 ":" "[" client_classes_list "]"
#line 2320 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3775 "dhcp4_parser.cc"
    break;

  case 661: // client_classes_list: client_classes_list ","
#line 2327 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3783 "dhcp4_parser.cc"
    break;

  case 662: // $@107: %empty
#line 2332 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3793 "dhcp4_parser.cc"
    break;

  case 663: // client_class_entry: "{" $@107 client_class_params "}"
#line 2336 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3803 "dhcp4_parser.cc"
    break;

  case 668: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2348 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3811 "dhcp4_parser.cc"
    break;

  case 684: // $@108: %empty
#line 2371 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3820 "dhcp4_parser.cc"
    break;

  case 685: // client_class_test: "test" $@108 ":" "constant string"
#line 2374 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3830 "dhcp4_parser.cc"
    break;

  case 686: // only_if_required: "only-if-required" ":" "boolean"
#line 2380 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3840 "dhcp4_parser.cc"
    break;

  case 687: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2388 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3850 "dhcp4_parser.cc"
    break;

  case 688: // $@109: %empty
#line 2396 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3862 "dhcp4_parser.cc"
    break;

  case 689: // control_socket: "control-socket" $@109 ":" "{" control_socket_params "}"
#line 2402 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3871 "dhcp4_parser.cc"
    break;

  case 692: // control_socket_params: control_socket_params ","
#line 2409 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3879 "dhcp4_parser.cc"
    break;

  case 698: // $@110: %empty
#line 2421 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3888 "dhcp4_parser.cc"
    break;

  case 699: // control_socket_type: "socket-type" $@110 ":" "constant string"
#line 2424 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3898 "dhcp4_parser.cc"
    break;

  case 700: // $@111: %empty
#line 2430 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3907 "dhcp4_parser.cc"
    break;

  case 701: // control_socket_name: "socket-name" $@111 ":" "constant string"
#line 2433 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3917 "dhcp4_parser.cc"
    break;

  case 702: // $@112: %empty
#line 2442 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3929 "dhcp4_parser.cc"
    break;

  case 703: // dhcp_queue_control: "dhcp-queue-control" $@112 ":" "{" queue_control_params "}"
#line 2448 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3940 "dhcp4_parser.cc"
    break;

  case 706: // queue_control_params: queue_control_params ","
#line 2457 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3948 "dhcp4_parser.cc"
    break;

  case 713: // enable_queue: "enable-queue" ":" "boolean"
#line 2470 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3958 "dhcp4_parser.cc"
    break;

  case 714: // $@113: %empty
#line 2476 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3967 "dhcp4_parser.cc"
    break;

  case 715: // queue_type: "queue-type" $@113 ":" "constant string"
#line 2479 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3977 "dhcp4_parser.cc"
    break;

  case 716: // capacity: "capacity" ":" "integer"
#line 2485 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3987 "dhcp4_parser.cc"
    break;

  case 717: // $@114: %empty
#line 2491 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3996 "dhcp4_parser.cc"
    break;

  case 718: // arbitrary_map_entry: "constant string" $@114 ":" value
#line 2494 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4005 "dhcp4_parser.cc"
    break;

  case 719: // $@115: %empty
#line 2501 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4017 "dhcp4_parser.cc"
    break;

  case 720: // dhcp_ddns: "dhcp-ddns" $@115 ":" "{" dhcp_ddns_params "}"
#line 2507 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4028 "dhcp4_parser.cc"
    break;

  case 721: // $@116: %empty
#line 2514 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4038 "dhcp4_parser.cc"
    break;

  case 722: // sub_dhcp_ddns: "{" $@116 dhcp_ddns_params "}"
#line 2518 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4048 "dhcp4_parser.cc"
    break;

  case 725: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2526 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4056 "dhcp4_parser.cc"
    break;

  case 744: // enable_updates: "enable-updates" ":" "boolean"
#line 2551 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4066 "dhcp4_parser.cc"
    break;

  case 745: // $@117: %empty
#line 2557 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4075 "dhcp4_parser.cc"
    break;

  case 746: // server_ip: "server-ip" $@117 ":" "constant string"
#line 2560 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4085 "dhcp4_parser.cc"
    break;

  case 747: // server_port: "server-port" ":" "integer"
#line 2566 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4095 "dhcp4_parser.cc"
    break;

  case 748: // $@118: %empty
#line 2572 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4104 "dhcp4_parser.cc"
    break;

  case 749: // sender_ip: "sender-ip" $@118 ":" "constant string"
#line 2575 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4114 "dhcp4_parser.cc"
    break;

  case 750: // sender_port: "sender-port" ":" "integer"
#line 2581 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4124 "dhcp4_parser.cc"
    break;

  case 751: // max_queue_size: "max-queue-size" ":" "integer"
#line 2587 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4134 "dhcp4_parser.cc"
    break;

  case 752: // $@119: %empty
#line 2593 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4143 "dhcp4_parser.cc"
    break;

  case 753: // ncr_protocol: "ncr-protocol" $@119 ":" ncr_protocol_value
#line 2596 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4152 "dhcp4_parser.cc"
    break;

  case 754: // ncr_protocol_value: "udp"
#line 2602 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4158 "dhcp4_parser.cc"
    break;

  case 755: // ncr_protocol_value: "tcp"
#line 2603 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4164 "dhcp4_parser.cc"
    break;

  case 756: // $@120: %empty
#line 2606 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4173 "dhcp4_parser.cc"
    break;

  case 757: // ncr_format: "ncr-format" $@120 ":" "JSON"
#line 2609 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4183 "dhcp4_parser.cc"
    break;

  case 758: // $@121: %empty
#line 2616 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4192 "dhcp4_parser.cc"
    break;

  case 759: // dep_qualifying_suffix: "qualifying-suffix" $@121 ":" "constant string"
#line 2619 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4202 "dhcp4_parser.cc"
    break;

  case 760: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2626 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4212 "dhcp4_parser.cc"
    break;

  case 761: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2633 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4222 "dhcp4_parser.cc"
    break;

  case 762: // $@122: %empty
#line 2640 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4231 "dhcp4_parser.cc"
    break;

  case 763: // dep_replace_client_name: "replace-client-name" $@122 ":" ddns_replace_client_name_value
#line 2643 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4240 "dhcp4_parser.cc"
    break;

  case 764: // $@123: %empty
#line 2649 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4249 "dhcp4_parser.cc"
    break;

  case 765: // dep_generated_prefix: "generated-prefix" $@123 ":" "constant string"
#line 2652 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4259 "dhcp4_parser.cc"
    break;

  case 766: // $@124: %empty
#line 2659 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4268 "dhcp4_parser.cc"
    break;

  case 767: // dep_hostname_char_set: "hostname-char-set" $@124 ":" "constant string"
#line 2662 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4278 "dhcp4_parser.cc"
    break;

  case 768: // $@125: %empty
#line 2669 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4287 "dhcp4_parser.cc"
    break;

  case 769: // dep_hostname_char_replacement: "hostname-char-replacement" $@125 ":" "constant string"
#line 2672 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4297 "dhcp4_parser.cc"
    break;

  case 770: // $@126: %empty
#line 2681 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4309 "dhcp4_parser.cc"
    break;

  case 771: // config_control: "config-control" $@126 ":" "{" config_control_params "}"
#line 2687 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4319 "dhcp4_parser.cc"
    break;

  case 772: // $@127: %empty
#line 2693 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4329 "dhcp4_parser.cc"
    break;

  case 773: // sub_config_control: "{" $@127 config_control_params "}"
#line 2697 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4338 "dhcp4_parser.cc"
    break;

  case 776: // config_control_params: config_control_params ","
#line 2705 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4346 "dhcp4_parser.cc"
    break;

  case 779: // $@128: %empty
#line 2715 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4358 "dhcp4_parser.cc"
    break;

  case 780: // config_databases: "config-databases" $@128 ":" "[" database_list "]"
#line 2721 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4367 "dhcp4_parser.cc"
    break;

  case 781: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2726 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4377 "dhcp4_parser.cc"
    break;

  case 782: // $@129: %empty
#line 2734 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4389 "dhcp4_parser.cc"
    break;

  case 783: // loggers: "loggers" $@129 ":" "[" loggers_entries "]"
#line 2740 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4398 "dhcp4_parser.cc"
    break;

  case 786: // loggers_entries: loggers_entries ","
#line 2749 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4406 "dhcp4_parser.cc"
    break;

  case 787: // $@130: %empty
#line 2755 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4416 "dhcp4_parser.cc"
    break;

  case 788: // logger_entry: "{" $@130 logger_params "}"
#line 2759 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4424 "dhcp4_parser.cc"
    break;

  case 791: // logger_params: logger_params ","
#line 2765 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4432 "dhcp4_parser.cc"
    break;

  case 799: // debuglevel: "debuglevel" ":" "integer"
#line 2779 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4442 "dhcp4_parser.cc"
    break;

  case 800: // $@131: %empty
#line 2785 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4451 "dhcp4_parser.cc"
    break;

  case 801: // severity: "severity" $@131 ":" "constant string"
#line 2788 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4461 "dhcp4_parser.cc"
    break;

  case 802: // $@132: %empty
#line 2794 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4473 "dhcp4_parser.cc"
    break;

  case 803: // output_options_list: "output_options" $@132 ":" "[" output_options_list_content "]"
#line 2800 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4482 "dhcp4_parser.cc"
    break;

  case 806: // output_options_list_content: output_options_list_content ","
#line 2807 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4490 "dhcp4_parser.cc"
    break;

  case 807: // $@133: %empty
#line 2812 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4500 "dhcp4_parser.cc"
    break;

  case 808: // output_entry: "{" $@133 output_params_list "}"
#line 2816 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4508 "dhcp4_parser.cc"
    break;

  case 811: // output_params_list: output_params_list ","
#line 2822 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4516 "dhcp4_parser.cc"
    break;

  case 817: // $@134: %empty
#line 2834 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4525 "dhcp4_parser.cc"
    break;

  case 818: // output: "output" $@134 ":" "constant string"
#line 2837 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4535 "dhcp4_parser.cc"
    break;

  case 819: // flush: "flush" ":" "boolean"
#line 2843 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4545 "dhcp4_parser.cc"
    break;

  case 820: // maxsize: "maxsize" ":" "integer"
#line 2849 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4555 "dhcp4_parser.cc"
    break;

  case 821: // maxver: "maxver" ":" "integer"
#line 2855 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4565 "dhcp4_parser.cc"
    break;

  case 822: // $@135: %empty
#line 2861 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4574 "dhcp4_parser.cc"
    break;

  case 823: // pattern: "pattern" $@135 ":" "constant string"
#line 2864 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4584 "dhcp4_parser.cc"
    break;

  case 824: // $@136: %empty
#line 2870 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4596 "dhcp4_parser.cc"
    break;

  case 825: // compatibility: "compatibility" $@136 ":" "{" compatibility_params "}"
#line 2876 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4605 "dhcp4_parser.cc"
    break;

  case 828: // compatibility_params: compatibility_params ","
#line 2883 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4613 "dhcp4_parser.cc"
    break;

  case 831: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2892 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4623 "dhcp4_parser.cc"
    break;


#line 4627 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -976;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     193,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,    28,    42,    32,    41,    48,    60,
      73,    99,   118,   124,   128,   134,   138,   165,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,    42,  -156,    59,   135,    62,   614,
     151,   201,   -28,    77,   203,   -85,   601,   142,  -976,    91,
     114,    72,   174,   183,  -976,    67,  -976,  -976,  -976,  -976,
     220,   222,   265,  -976,  -976,  -976,  -976,  -976,  -976,   284,
     291,   308,   320,   321,   323,   332,   333,   334,   360,   362,
    -976,   364,   379,   395,   398,   399,  -976,  -976,  -976,   400,
     401,   402,  -976,  -976,  -976,   404,  -976,  -976,  -976,  -976,
     406,   407,   408,  -976,  -976,  -976,  -976,  -976,   409,  -976,
    -976,  -976,  -976,  -976,  -976,   410,   412,  -976,  -976,   413,
    -976,    87,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,   414,  -976,
     100,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,   415,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,   110,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
     120,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,   225,   275,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,   272,  -976,  -976,   416,  -976,  -976,  -976,   418,  -976,
    -976,   355,   420,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,   421,   422,  -976,  -976,
    -976,  -976,   419,   425,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,   121,  -976,  -976,  -976,
     426,  -976,  -976,   427,  -976,   428,   430,  -976,  -976,   431,
     435,  -976,  -976,  -976,  -976,  -976,  -976,  -976,   136,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,   436,   140,  -976,  -976,
    -976,  -976,    42,    42,  -976,  -135,   437,  -976,  -976,   438,
     439,   440,   215,   237,   239,   446,   447,   449,   450,   451,
     452,   251,   260,   262,   263,   264,   255,   221,   266,   268,
     279,   286,   468,   287,   290,   280,   281,   292,   471,   477,
     480,   293,   296,   298,   496,   504,   505,   304,   508,   509,
     510,   511,   309,   310,   311,   520,   522,   523,   524,   526,
     324,   528,   530,   532,   533,   534,   535,   335,   339,   538,
     545,  -976,   135,  -976,   548,   550,   551,   350,    62,  -976,
     552,   556,   558,   562,   563,   568,   367,   571,   587,   588,
     614,  -976,   589,   151,  -976,   598,   599,   600,   602,   603,
     604,   605,   606,  -976,   201,  -976,   607,   608,   411,   609,
     610,   611,   396,  -976,    77,   612,   417,   423,  -976,   203,
     616,   617,   125,  -976,   424,   618,   619,   429,   620,   432,
     441,   621,   623,   442,   443,   624,   626,   630,   633,   601,
    -976,   634,   448,   142,  -976,  -976,  -976,   641,   639,   640,
     642,   643,  -976,  -976,  -976,   453,   455,   456,   650,   651,
     658,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,   458,  -976,  -976,  -976,  -976,  -976,    16,   459,
     460,  -976,  -976,  -976,   662,   663,   668,  -976,   669,   670,
     469,   259,  -976,  -976,  -976,   671,   684,   685,   686,   695,
    -976,   699,   703,   704,   709,   486,   512,  -976,  -976,   712,
     713,  -976,   722,   274,   283,  -976,  -976,   529,   531,   536,
     723,   539,   540,  -976,   722,   542,   727,  -976,   543,  -976,
     722,   544,   546,   547,   567,   569,   570,   572,  -976,   575,
     576,  -976,   577,   578,   579,  -976,  -976,   580,  -976,  -976,
    -976,   581,   670,  -976,  -976,   582,   583,  -976,   584,  -976,
    -976,    15,   557,  -976,  -976,    16,   585,   613,   615,  -976,
     724,  -976,  -976,    42,   135,   142,    62,   714,  -976,  -976,
    -976,   537,   537,   734,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,   737,   744,   747,   767,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,   191,   770,   797,   798,    54,
     -49,   -64,   -70,   601,  -976,  -976,   799,  -161,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,   811,
    -976,  -976,  -976,  -976,   -52,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,   734,  -976,   173,   229,   232,  -976,   238,
    -976,  -976,  -976,  -976,  -976,  -976,   820,   821,   822,   823,
     824,  -976,  -976,  -976,  -976,   825,   826,  -976,   827,   828,
     829,   830,  -976,  -976,  -976,  -976,  -976,   257,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,   267,  -976,   832,   837,  -976,  -976,
     836,   840,  -976,  -976,   838,   842,  -976,  -976,   843,   847,
    -976,  -976,   846,   850,  -976,  -976,  -976,  -976,  -976,  -976,
      90,  -976,  -976,  -976,  -976,  -976,  -976,  -976,   104,  -976,
    -976,   849,   853,  -976,  -976,   851,   855,  -976,   831,   856,
     857,   859,   860,   861,   269,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,   862,   863,   864,  -976,   276,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,   282,  -976,
    -976,  -976,   865,  -976,   866,  -976,  -976,  -976,   331,  -976,
    -976,  -976,  -976,  -976,   337,  -976,   153,  -976,   867,  -976,
     343,  -976,  -976,   653,  -976,   868,   869,  -976,  -976,  -976,
    -976,   870,   871,  -976,  -976,  -976,   872,   714,  -976,   875,
     876,   877,   878,   666,   674,   677,   676,   679,   883,   884,
     885,   886,   687,   688,   887,   689,   690,   683,   691,   889,
     895,   896,   897,   537,  -976,  -976,   537,  -976,   734,   614,
    -976,   737,    77,  -976,   744,   203,  -976,   747,   729,  -976,
     767,   191,  -976,   277,   770,  -976,   201,  -976,   797,   -85,
    -976,   798,   696,   697,   698,   702,   706,   707,    54,  -976,
     693,   710,   718,   -49,  -976,   902,   906,   -64,  -976,   711,
     907,   720,   912,   -70,  -976,  -976,    81,   799,  -976,   721,
    -161,  -976,  -976,   913,   933,   151,  -976,   811,   947,  -976,
    -976,   748,  -976,   341,   751,   763,   773,  -976,  -976,  -976,
    -976,  -976,   780,   781,   784,   788,  -976,  -976,   326,  -976,
    -976,  -976,  -976,   789,   800,   801,   814,  -976,   344,  -976,
     345,  -976,  1042,  -976,  1046,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,   346,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  1051,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  1052,  1056,  -976,  -976,  -976,  -976,
    -976,  1053,  -976,   347,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,   858,   873,  -976,  -976,
     874,  -976,    42,  -976,  -976,  1058,  -976,  -976,  -976,  -976,
    -976,   353,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
     879,   357,  -976,   722,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,   729,
    -976,  1059,   880,  -976,   277,  -976,  -976,  -976,  -976,  -976,
    -976,  1061,   881,  1062,    81,  -976,  -976,  -976,  -976,  -976,
     888,  -976,  -976,  1063,  -976,   890,  -976,  -976,  1060,  -976,
    -976,   177,  -976,   -37,  1060,  -976,  -976,  1065,  1066,  1067,
    -976,   359,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  1068,
     882,   891,   892,  1069,   -37,  -976,   894,  -976,  -976,  -976,
     898,  -976,  -976,  -976
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   187,     9,   372,    11,   580,    13,
     607,    15,   500,    17,   509,    19,   548,    21,   334,    23,
     721,    25,   772,    27,    46,    39,     0,     0,     0,     0,
       0,   609,     0,   511,   550,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   770,   175,   202,
       0,     0,     0,   629,   631,   633,   200,   210,   212,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     144,     0,     0,     0,     0,     0,   153,   160,   162,     0,
       0,     0,   363,   498,   539,     0,   446,   594,   596,   439,
       0,     0,     0,   296,   657,   598,   325,   346,     0,   311,
     688,   702,   719,   166,   168,     0,     0,   782,   824,     0,
     132,     0,    67,    70,    71,    72,    73,    74,   108,   109,
     110,   111,   112,    75,   103,   131,    92,    93,    94,   116,
     117,   118,   119,   120,   121,   122,   123,   114,   115,   124,
     125,   126,   128,   129,    78,    79,   100,    80,    81,    82,
     127,    86,    87,    76,   105,   106,   107,   104,    77,    84,
      85,    98,    99,   101,    95,    96,    97,    83,    88,    89,
      90,    91,   102,   113,   130,   189,   191,   195,     0,   186,
       0,   177,   180,   181,   182,   183,   184,   185,   424,   426,
     428,   571,   422,   430,     0,   434,   432,   653,   421,   377,
     378,   379,   380,   381,   405,   406,   407,   408,   409,   395,
     396,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,     0,   374,   384,   400,   401,   402,   385,   387,
     388,   391,   392,   393,   390,   386,   382,   383,   403,   404,
     389,   397,   398,   399,   394,   592,   591,   587,   588,   586,
       0,   582,   585,   589,   590,   651,   639,   641,   645,   643,
     649,   647,   635,   628,   622,   626,   627,     0,   610,   611,
     623,   624,   625,   619,   614,   620,   616,   617,   618,   621,
     615,     0,   529,   263,     0,   533,   531,   536,     0,   525,
     526,     0,   512,   513,   516,   528,   517,   518,   519,   535,
     520,   521,   522,   523,   524,   565,     0,     0,   563,   564,
     567,   568,     0,   551,   552,   555,   556,   557,   558,   559,
     560,   561,   562,   342,   344,   339,     0,   336,   340,   341,
       0,   758,   745,     0,   748,     0,     0,   752,   756,     0,
       0,   762,   764,   766,   768,   743,   741,   742,     0,   723,
     726,   727,   728,   729,   730,   731,   732,   733,   738,   734,
     735,   736,   737,   739,   740,   779,     0,     0,   774,   777,
     778,    45,    50,     0,    37,    43,     0,    64,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,    69,    66,     0,     0,     0,     0,   179,   188,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     376,   373,     0,   584,   581,     0,     0,     0,     0,     0,
       0,     0,     0,   608,   613,   501,     0,     0,     0,     0,
       0,     0,     0,   510,   515,     0,     0,     0,   549,   554,
       0,     0,   338,   335,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   725,
     722,     0,     0,   776,   773,    49,    41,     0,     0,     0,
       0,     0,   147,   148,   149,     0,     0,     0,     0,     0,
       0,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,     0,   171,   172,   150,   151,   152,     0,     0,
       0,   164,   165,   170,     0,     0,     0,   146,     0,     0,
       0,     0,   436,   437,   438,     0,     0,     0,     0,     0,
     687,     0,     0,     0,     0,     0,     0,   173,   174,     0,
       0,    68,     0,     0,     0,   199,   178,     0,     0,     0,
       0,     0,     0,   445,     0,     0,     0,   375,     0,   583,
       0,     0,     0,     0,     0,     0,     0,     0,   612,     0,
       0,   527,     0,     0,     0,   538,   514,     0,   569,   570,
     553,     0,     0,   337,   744,     0,     0,   747,     0,   750,
     751,     0,     0,   760,   761,     0,     0,     0,     0,   724,
       0,   781,   775,     0,     0,     0,     0,     0,   630,   632,
     634,     0,     0,   214,   145,   155,   156,   157,   158,   159,
     154,   161,   163,   365,   502,   541,   448,    38,   595,   597,
     441,   442,   443,   444,   440,     0,     0,   600,   327,     0,
       0,     0,     0,     0,   167,   169,     0,     0,    51,   190,
     193,   194,   192,   197,   198,   196,   425,   427,   429,   573,
     423,   431,   435,   433,     0,   593,   652,   640,   642,   646,
     644,   650,   648,   636,   530,   264,   534,   532,   537,   566,
     343,   345,   759,   746,   749,   754,   755,   753,   757,   763,
     765,   767,   769,   214,    42,     0,     0,     0,   208,     0,
     204,   207,   250,   256,   258,   260,     0,     0,     0,     0,
       0,   272,   274,   276,   278,     0,     0,   282,     0,     0,
       0,     0,   288,   290,   292,   294,   249,     0,   221,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   238,
     239,   240,   234,   241,   242,   243,   235,   236,   237,   244,
     245,   246,   247,   248,     0,   219,     0,   215,   216,   370,
       0,   366,   367,   507,     0,   503,   504,   546,     0,   542,
     543,   453,     0,   449,   450,   306,   307,   308,   309,   310,
       0,   298,   301,   302,   303,   304,   305,   662,     0,   659,
     605,     0,   601,   602,   332,     0,   328,   329,     0,     0,
       0,     0,     0,     0,     0,   348,   351,   352,   353,   354,
     355,   356,     0,     0,     0,   321,     0,   313,   316,   317,
     318,   319,   320,   698,   700,   697,   695,   696,     0,   690,
     693,   694,     0,   714,     0,   717,   710,   711,     0,   704,
     707,   708,   709,   712,     0,   787,     0,   784,     0,   830,
       0,   826,   829,    53,   578,     0,   574,   575,   637,   655,
     656,     0,     0,    62,   771,   176,     0,   206,   203,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   223,   201,   211,     0,   213,   218,     0,
     364,   369,   511,   499,   506,   550,   540,   545,     0,   447,
     452,   300,   297,   664,   661,   658,   609,   599,   604,     0,
     326,   331,     0,     0,     0,     0,     0,     0,   350,   347,
       0,     0,     0,   315,   312,     0,     0,   692,   689,     0,
       0,     0,     0,   706,   703,   720,     0,   786,   783,     0,
     828,   825,    55,     0,    54,     0,   572,   577,     0,   654,
     780,     0,   205,     0,     0,     0,     0,   262,   265,   266,
     267,   268,     0,     0,     0,     0,   280,   281,     0,   269,
     270,   271,   287,     0,     0,     0,     0,   222,     0,   217,
       0,   368,     0,   505,     0,   544,   497,   476,   477,   478,
     461,   462,   481,   482,   483,   484,   485,   464,   465,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     458,   459,   460,   474,   475,   471,   472,   473,   470,     0,
     455,   463,   479,   480,   466,   467,   468,   469,   451,   299,
     684,     0,   679,   680,   681,   682,   683,   672,   673,   677,
     678,   674,   675,   676,     0,   665,   666,   669,   670,   671,
     660,     0,   603,     0,   330,   357,   358,   359,   360,   361,
     362,   349,   322,   323,   324,   314,     0,     0,   691,   713,
       0,   716,     0,   705,   802,     0,   800,   798,   792,   796,
     797,     0,   789,   794,   795,   793,   785,   831,   827,    52,
      57,     0,   576,     0,   209,   252,   253,   254,   255,   251,
     257,   259,   261,   273,   275,   277,   279,   284,   285,   286,
     283,   289,   291,   293,   295,   220,   371,   508,   547,   457,
     454,     0,     0,   663,   668,   606,   333,   699,   701,   715,
     718,     0,     0,     0,   791,   788,    56,   579,   638,   456,
       0,   686,   667,     0,   799,     0,   790,   685,     0,   801,
     807,     0,   804,     0,   806,   803,   817,     0,     0,     0,
     822,     0,   809,   812,   813,   814,   815,   816,   805,     0,
       0,     0,     0,     0,   811,   808,     0,   819,   820,   821,
       0,   810,   818,   823
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,   -54,  -976,  -557,  -976,   213,
    -976,  -976,  -976,  -976,  -976,  -976,  -613,  -976,  -976,  -976,
     -67,  -976,  -976,  -976,  -976,  -976,  -976,  -976,   390,   593,
       4,    10,    23,   -40,   -23,   -12,    22,    25,    29,    33,
    -976,  -976,  -976,  -976,  -976,    35,    40,    43,    45,    46,
      47,  -976,   403,    50,  -976,    51,  -976,    53,    57,    58,
    -976,    61,  -976,    63,  -976,  -976,  -976,  -976,  -976,  -976,
     391,   594,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,   129,  -976,
    -976,  -976,  -976,  -976,  -976,   313,  -976,   103,  -976,  -680,
     111,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,   -33,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,    92,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,    74,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,    89,  -976,  -976,  -976,    93,   561,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,    94,  -976,  -976,  -976,  -976,
    -976,  -976,  -975,  -976,  -976,  -976,   116,  -976,  -976,  -976,
     122,   595,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -973,  -976,   -65,  -976,    70,  -976,    64,    65,    68,    69,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,   113,  -976,  -976,
    -103,   -46,  -976,  -976,  -976,  -976,  -976,   123,  -976,  -976,
    -976,   127,  -976,   586,  -976,   -63,  -976,  -976,  -976,  -976,
    -976,   -42,  -976,  -976,  -976,  -976,  -976,   -35,  -976,  -976,
    -976,   126,  -976,  -976,  -976,   130,  -976,   590,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,    75,
    -976,  -976,  -976,    76,   622,  -976,  -976,   -51,  -976,    -8,
    -976,   -39,  -976,  -976,  -976,   119,  -976,  -976,  -976,   131,
    -976,   625,   -55,  -976,   -15,  -976,     3,  -976,   370,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -964,  -976,  -976,  -976,
    -976,  -976,   132,  -976,  -976,  -976,   -98,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,   101,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,    97,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,   405,   573,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,   444,   592,  -976,  -976,  -976,
    -976,  -976,  -976,    96,  -976,  -976,  -100,  -976,  -976,  -976,
    -976,  -976,  -976,  -123,  -976,  -976,  -134,  -976,  -976,  -976,
    -976,  -976,  -976,  -976,  -976,  -976,  -976,   102,  -976
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   708,
      82,    83,    39,    64,    79,    80,   729,   933,  1033,  1034,
     806,    41,    66,    85,   416,    86,    43,    67,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   442,   165,   166,   167,   168,   169,   170,   171,
     172,   448,   700,   173,   449,   174,   450,   175,   176,   177,
     475,   178,   476,   179,   180,   181,   182,   183,   184,   420,
     220,   221,    45,    68,   222,   484,   223,   485,   732,   224,
     486,   735,   225,   185,   428,   186,   421,   779,   780,   781,
     946,   187,   429,   188,   430,   836,   837,   838,   976,   807,
     808,   809,   949,  1189,   810,   950,   811,   951,   812,   952,
     813,   814,   517,   815,   816,   817,   818,   819,   820,   821,
     822,   958,   823,   959,   824,   960,   825,   961,   826,   827,
     828,   964,  1200,   829,   830,   969,   831,   970,   832,   971,
     833,   972,   189,   465,   860,   861,   862,   863,   864,   865,
     866,   190,   471,   896,   897,   898,   899,   900,   191,   468,
     875,   876,   877,   999,    59,    75,   366,   367,   368,   530,
     369,   531,   192,   469,   884,   885,   886,   887,   888,   889,
     890,   891,   193,   454,   840,   841,   842,   979,    47,    69,
     262,   263,   264,   494,   265,   490,   266,   491,   267,   492,
     268,   495,   269,   498,   270,   497,   194,   195,   196,   197,
     461,   714,   275,   198,   458,   852,   853,   854,   988,  1109,
    1110,   199,   455,    53,    72,   844,   845,   846,   982,    55,
      73,   331,   332,   333,   334,   335,   336,   337,   516,   338,
     520,   339,   519,   340,   341,   521,   342,   200,   456,   848,
     849,   850,   985,    57,    74,   352,   353,   354,   355,   356,
     525,   357,   358,   359,   360,   277,   493,   935,   936,   937,
    1035,    49,    70,   290,   291,   292,   502,   201,   459,   202,
     460,   203,   467,   871,   872,   873,   996,    51,    71,   307,
     308,   309,   204,   425,   205,   426,   206,   427,   313,   512,
     940,  1038,   314,   506,   315,   507,   316,   509,   317,   508,
     318,   511,   319,   510,   320,   505,   284,   499,   941,   207,
     466,   868,   869,   993,  1134,  1135,  1136,  1137,  1138,  1211,
    1139,   208,   209,   472,   908,   909,   910,  1015,   911,  1016,
     210,   473,   918,   919,   920,   921,  1020,   922,   923,  1022,
     211,   474,    61,    76,   388,   389,   390,   391,   536,   392,
     393,   538,   394,   395,   396,   541,   767,   397,   542,   398,
     535,   399,   400,   401,   545,   402,   546,   403,   547,   404,
     548,   212,   419,    63,    77,   407,   408,   409,   551,   410,
     213,   479,   926,   927,  1026,  1171,  1172,  1173,  1174,  1223,
    1175,  1221,  1241,  1242,  1243,  1251,  1252,  1253,  1259,  1254,
    1255,  1256,  1257,  1263,   214,   480,   930,   931,   932
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     150,   219,   238,   286,   303,   287,   329,   348,   365,   385,
      78,   350,   834,  1101,   281,  1102,   310,   226,   278,   293,
     305,   742,   343,   361,  1117,   386,   321,   746,    28,   242,
     280,   928,   351,   765,   276,   289,   304,   127,   128,    40,
     330,   349,   707,   127,   128,   149,   243,    29,    42,    30,
      81,    31,   363,   364,   282,    44,   311,   244,   127,   128,
     227,   279,   294,   306,   123,   344,   362,    46,   387,    84,
     417,   557,   283,   239,   312,   418,   413,   215,   216,   240,
      48,   217,   302,   938,   218,   912,   913,   914,   903,   904,
     482,   245,   241,   991,   246,   483,   992,   411,   247,   892,
     893,   894,   248,   488,   249,   707,    50,   994,   489,   250,
     995,   322,   251,   500,   252,   253,   254,   412,   501,   255,
     256,   149,   257,   503,   532,    52,   258,   259,   504,   533,
     260,    54,   261,   271,   272,    56,   915,   273,   274,   549,
     288,    58,   149,   553,   550,    60,    87,  1246,   554,    88,
    1247,  1248,  1249,  1250,   405,   406,  1027,   149,    89,  1028,
      90,    91,    92,    93,    94,    95,    96,    97,    98,   127,
     128,   323,    62,   324,   325,   323,   482,   326,   327,   328,
    1244,   943,   414,  1245,   127,   128,   415,   766,   127,   128,
     695,   696,   697,   698,   878,   879,   880,   881,   882,   883,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   422,   699,   423,   123,   124,    93,
      94,    95,   553,   513,  1101,   488,  1102,   944,   125,   126,
     945,   947,   127,   128,   124,  1117,   948,   129,    32,    33,
      34,    35,   130,   131,   132,   133,   134,   285,   127,   128,
     973,   135,   363,   364,  1164,   974,  1165,  1166,   149,   424,
     973,   136,  1008,   235,   137,   975,   236,  1009,   514,  1013,
     515,   138,   139,   149,  1014,  1017,   140,   149,   431,   141,
    1018,   730,   731,   142,   124,   432,  1068,   323,   345,   324,
     325,   346,   347,   733,   734,    93,    94,    95,   127,   128,
     127,   128,   433,   143,   144,   145,   146,   147,   855,   856,
     857,   858,   295,   859,   434,   435,   148,   436,   296,   297,
     298,   299,   300,   301,  1023,   302,   437,   438,   439,  1024,
     549,   149,    99,   100,   101,  1025,  1030,   973,   500,  1209,
     532,  1031,  1205,  1206,  1210,  1216,  1224,   149,   555,   556,
     503,  1225,  1264,   523,   440,  1227,   441,  1265,   443,   123,
     124,   323,   710,   711,   712,   713,  1185,  1186,  1187,  1188,
    1197,  1198,  1199,   444,   127,   128,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,   445,
    1120,  1121,   446,   447,   451,   452,   453,   149,   457,   149,
     462,   463,   464,   470,   477,   150,   478,   481,   487,   496,
     518,   219,   522,   524,   562,   526,   527,   528,   529,   577,
     534,   537,   539,   238,   540,   543,   286,   226,   287,   544,
     552,   558,   559,   560,   561,   281,   563,   303,   564,   278,
     565,   566,   293,   567,   568,   569,   570,   329,   571,   310,
     242,   280,   348,   305,   576,   276,   350,   572,   289,   573,
     574,   575,   582,   343,   578,   588,   579,   243,   361,   304,
     227,   589,   385,   149,   590,   282,   580,   351,   244,   585,
     586,   330,   279,   581,   583,   294,   349,   584,   386,   311,
     594,   587,   591,   283,   239,   592,   306,   593,   595,   596,
     240,   597,   598,   599,   600,   601,   344,   312,   602,   603,
     604,   362,   245,   241,   605,   246,   606,   607,   608,   247,
     609,   610,   611,   248,   612,   249,   613,   614,   615,   616,
     250,   387,   619,   251,   617,   252,   253,   254,   618,   620,
     255,   256,   622,   257,   623,   624,   627,   258,   259,   625,
     628,   260,   629,   261,   271,   272,   630,   631,   273,   274,
    1228,   782,   632,   288,   633,   634,   783,   784,   785,   786,
     787,   788,   789,   790,   791,   792,   793,   794,   795,   796,
     797,   635,   636,   638,   798,   799,   800,   801,   802,   803,
     804,   805,   640,   641,   642,   655,   643,   644,   645,   646,
     647,   649,   650,   652,   653,   654,   657,   150,   651,   219,
     661,   662,   665,   666,   668,   671,   658,   672,   675,   774,
     676,   323,   659,   664,   677,   226,   667,   678,   680,   669,
      91,    92,    93,    94,    95,   683,   684,   685,   670,   686,
     687,   673,   674,   895,   905,   681,   385,   691,   692,   688,
     929,   689,   690,   693,   694,   701,   702,   703,   704,   901,
     906,   916,   386,   705,   706,   709,   715,    30,   227,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   716,
     717,   718,   724,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   719,   228,   229,   230,   720,   124,   127,   128,
     721,   722,   902,   907,   917,   387,   723,   726,   725,   231,
     727,   127,   128,   232,   233,   234,   129,   728,   739,   773,
     768,   130,   131,   132,   744,   736,   235,   737,   778,   236,
     135,   835,   738,   149,   839,   740,   741,   237,   743,   745,
     747,   843,   748,   749,   847,    91,    92,    93,    94,    95,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
     380,   381,   382,   750,   851,   751,   752,   867,   753,   383,
     384,   754,   755,   756,   757,   758,   759,   760,   762,   763,
     764,   770,   143,   144,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   870,   874,   925,   149,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   934,   771,
     149,   772,   124,   323,   953,   954,   955,   956,   957,   962,
     963,   965,   966,   967,   968,  1002,   127,   128,   977,   233,
     978,   129,   980,   981,   983,   984,   130,   131,   132,   986,
     987,   235,   989,   990,   236,   997,   998,  1000,  1001,  1032,
    1003,  1004,   237,  1005,  1006,  1007,  1010,  1011,  1012,  1019,
    1021,  1029,  1037,  1047,  1036,   761,  1041,  1040,  1039,  1043,
    1044,  1045,  1046,  1048,  1049,  1050,  1051,  1052,  1053,  1054,
    1055,  1058,  1061,  1063,  1056,  1057,  1059,  1060,  1062,  1064,
    1065,  1066,  1152,  1145,  1146,  1147,  1156,   143,   144,  1148,
    1157,  1160,   238,  1149,  1150,   329,  1162,  1153,   348,  1179,
    1159,  1076,   350,  1103,   281,  1154,  1122,  1161,   278,   303,
    1177,   343,   365,  1114,   361,   149,  1180,  1112,  1131,   242,
     280,   310,  1129,   351,   276,   305,   895,  1127,  1080,   330,
     905,  1183,   349,  1111,  1184,  1100,   243,  1190,  1128,  1167,
    1126,   304,   901,   929,   282,  1081,   906,   244,   286,  1191,
     287,   279,   916,  1115,   344,  1169,  1082,   362,  1132,  1192,
    1113,   311,   283,   239,   293,  1130,  1193,  1194,   306,   240,
    1195,  1116,  1077,  1168,  1196,  1201,  1133,  1123,  1078,   312,
     289,   245,   241,  1124,   246,   902,  1202,  1203,   247,   907,
    1083,  1079,   248,  1084,   249,   917,  1125,  1085,  1170,   250,
    1204,  1086,   251,  1087,   252,   253,   254,   294,  1088,   255,
     256,  1089,   257,  1090,  1091,  1092,   258,   259,  1093,  1094,
     260,  1095,   261,   271,   272,  1096,  1097,   273,   274,  1098,
    1207,  1099,  1105,  1106,  1208,  1212,  1107,  1108,  1104,  1214,
    1213,  1215,  1222,  1230,  1217,  1233,  1235,  1240,  1238,  1260,
    1261,  1262,  1266,  1270,   775,   621,  1042,   777,   769,  1218,
    1219,  1069,   626,  1119,  1067,  1226,   942,  1155,  1234,  1231,
    1144,  1267,  1143,   663,  1237,   637,  1239,  1071,  1268,  1269,
    1272,  1070,  1151,  1118,  1273,   288,  1229,  1073,  1220,  1072,
     656,  1181,  1182,  1075,   939,  1074,  1232,  1142,  1158,   660,
    1163,  1258,   679,  1176,  1236,   639,  1140,  1141,   924,   776,
    1271,     0,  1178,     0,     0,     0,     0,     0,     0,   648,
       0,     0,  1076,     0,  1103,   682,     0,  1122,     0,     0,
       0,     0,     0,     0,  1114,     0,     0,  1167,  1112,  1131,
       0,     0,     0,  1129,     0,     0,     0,     0,  1127,  1080,
       0,     0,     0,  1169,  1111,     0,  1100,     0,     0,  1128,
       0,  1126,     0,     0,     0,     0,  1081,     0,     0,     0,
       0,  1168,     0,     0,  1115,     0,     0,  1082,     0,  1132,
       0,  1113,     0,     0,     0,     0,  1130,     0,     0,     0,
       0,     0,  1116,  1077,     0,     0,  1170,  1133,  1123,  1078,
       0,     0,     0,     0,  1124,     0,     0,     0,     0,     0,
       0,  1083,  1079,     0,  1084,     0,     0,  1125,  1085,     0,
       0,     0,  1086,     0,  1087,     0,     0,     0,     0,  1088,
       0,     0,  1089,     0,  1090,  1091,  1092,     0,     0,  1093,
    1094,     0,  1095,     0,     0,     0,  1096,  1097,     0,     0,
    1098,     0,  1099,  1105,  1106,     0,     0,  1107,  1108,  1104
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,    74,   692,   988,    69,   988,    71,    68,    69,    70,
      71,   634,    73,    74,   988,    76,    72,   640,     0,    69,
      69,   192,    74,    18,    69,    70,    71,   107,   108,     7,
      73,    74,   599,   107,   108,   206,    69,     5,     7,     7,
     206,     9,   137,   138,    69,     7,    71,    69,   107,   108,
      68,    69,    70,    71,    92,    73,    74,     7,    76,    10,
       3,   206,    69,    69,    71,     8,     4,    15,    16,    69,
       7,    19,   134,   135,    22,   155,   156,   157,   152,   153,
       3,    69,    69,     3,    69,     8,     6,     6,    69,   148,
     149,   150,    69,     3,    69,   662,     7,     3,     8,    69,
       6,    34,    69,     3,    69,    69,    69,     3,     8,    69,
      69,   206,    69,     3,     3,     7,    69,    69,     8,     8,
      69,     7,    69,    69,    69,     7,   206,    69,    69,     3,
      70,     7,   206,     3,     8,     7,    11,   184,     8,    14,
     187,   188,   189,   190,    12,    13,     3,   206,    23,     6,
      25,    26,    27,    28,    29,    30,    31,    32,    33,   107,
     108,    94,     7,    96,    97,    94,     3,   100,   101,   102,
       3,     8,     8,     6,   107,   108,     3,   172,   107,   108,
     174,   175,   176,   177,   140,   141,   142,   143,   144,   145,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,     4,   209,     4,    92,    93,    28,
      29,    30,     3,     8,  1209,     3,  1209,     8,   103,   104,
       8,     3,   107,   108,    93,  1209,     8,   112,   206,   207,
     208,   209,   117,   118,   119,   120,   121,   106,   107,   108,
       3,   126,   137,   138,   183,     8,   185,   186,   206,     4,
       3,   136,     3,   122,   139,     8,   125,     8,     3,     3,
       8,   146,   147,   206,     8,     3,   151,   206,     4,   154,
       8,    17,    18,   158,    93,     4,   976,    94,    95,    96,
      97,    98,    99,    20,    21,    28,    29,    30,   107,   108,
     107,   108,     4,   178,   179,   180,   181,   182,   127,   128,
     129,   130,   121,   132,     4,     4,   191,     4,   127,   128,
     129,   130,   131,   132,     3,   134,     4,     4,     4,     8,
       3,   206,    65,    66,    67,     8,     3,     3,     3,     3,
       3,     8,     8,     8,     8,     8,     3,   206,   412,   413,
       3,     8,     3,     8,     4,     8,     4,     8,     4,    92,
      93,    94,   113,   114,   115,   116,    35,    36,    37,    38,
      54,    55,    56,     4,   107,   108,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,     4,
     123,   124,     4,     4,     4,     4,     4,   206,     4,   206,
       4,     4,     4,     4,     4,   482,     4,     4,     4,     4,
       4,   488,     4,     3,   209,     4,     4,     8,     3,   208,
       4,     4,     4,   500,     4,     4,   503,   488,   503,     4,
       4,     4,     4,     4,     4,   500,   209,   514,   209,   500,
       4,     4,   503,     4,     4,     4,     4,   524,   207,   514,
     500,   500,   529,   514,   209,   500,   529,   207,   503,   207,
     207,   207,     4,   524,   208,     4,   208,   500,   529,   514,
     488,     4,   549,   206,     4,   500,   207,   529,   500,   209,
     209,   524,   500,   207,   207,   503,   529,   207,   549,   514,
       4,   209,   209,   500,   500,   209,   514,   209,     4,     4,
     500,   207,     4,     4,     4,     4,   524,   514,   209,   209,
     209,   529,   500,   500,     4,   500,     4,     4,     4,   500,
       4,   207,     4,   500,     4,   500,     4,     4,     4,     4,
     500,   549,     4,   500,   209,   500,   500,   500,   209,     4,
     500,   500,     4,   500,     4,     4,     4,   500,   500,   209,
       4,   500,     4,   500,   500,   500,     4,     4,   500,   500,
    1183,    34,     4,   503,   207,     4,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,     4,     4,     4,    57,    58,    59,    60,    61,    62,
      63,    64,     4,     4,     4,   209,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   684,   207,   686,
       4,     4,     4,     4,     4,     4,   209,     4,     4,   683,
       4,    94,   209,   209,     4,   686,   207,     4,     4,   207,
      26,    27,    28,    29,    30,     4,     7,     7,   207,     7,
       7,   209,   209,   720,   721,   207,   723,     7,     7,   206,
     727,   206,   206,     5,   206,   206,   206,     5,     5,   720,
     721,   722,   723,     5,     5,   206,     5,     7,   686,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,     5,
       5,     5,   206,    79,    80,    81,    82,    83,    84,    85,
      86,    87,     7,    89,    90,    91,     7,    93,   107,   108,
       7,     7,   720,   721,   722,   723,     7,     5,   206,   105,
       7,   107,   108,   109,   110,   111,   112,     5,     5,     5,
     173,   117,   118,   119,     7,   206,   122,   206,    24,   125,
     126,     7,   206,   206,     7,   206,   206,   133,   206,   206,
     206,     7,   206,   206,     7,    26,    27,    28,    29,    30,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   206,     7,   206,   206,     7,   206,   178,
     179,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   178,   179,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     7,     7,     7,   206,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,     7,   206,
     206,   206,    93,    94,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   107,   108,     6,   110,
       3,   112,     6,     3,     6,     3,   117,   118,   119,     6,
       3,   122,     6,     3,   125,     6,     3,     6,     3,   206,
       4,     4,   133,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     3,   207,     6,   662,     4,     6,     8,     4,
       4,     4,     4,   209,   207,   209,   207,     4,     4,     4,
       4,     4,   209,     4,   207,   207,   207,   207,   207,     4,
       4,     4,   209,   207,   207,   207,     4,   178,   179,   207,
       4,     4,   979,   207,   207,   982,     4,   207,   985,     6,
     209,   988,   985,   988,   979,   207,   993,   207,   979,   996,
     209,   982,   999,   988,   985,   206,     3,   988,   993,   979,
     979,   996,   993,   985,   979,   996,  1013,   993,   988,   982,
    1017,     4,   985,   988,   206,   988,   979,   206,   993,  1026,
     993,   996,  1013,  1030,   979,   988,  1017,   979,  1035,   206,
    1035,   979,  1023,   988,   982,  1026,   988,   985,   993,   206,
     988,   996,   979,   979,  1035,   993,   206,   206,   996,   979,
     206,   988,   988,  1026,   206,   206,   993,   993,   988,   996,
    1035,   979,   979,   993,   979,  1013,   206,   206,   979,  1017,
     988,   988,   979,   988,   979,  1023,   993,   988,  1026,   979,
     206,   988,   979,   988,   979,   979,   979,  1035,   988,   979,
     979,   988,   979,   988,   988,   988,   979,   979,   988,   988,
     979,   988,   979,   979,   979,   988,   988,   979,   979,   988,
       8,   988,   988,   988,     8,     4,   988,   988,   988,     3,
       8,     8,     4,     4,   206,     4,     4,     7,     5,     4,
       4,     4,     4,     4,   684,   482,   947,   686,   675,   206,
     206,   978,   488,   991,   973,   206,   773,  1013,   207,   209,
    1001,   209,   999,   532,   206,   500,   206,   981,   207,   207,
     206,   979,  1008,   990,   206,  1035,  1209,   984,  1162,   982,
     524,  1035,  1037,   987,   744,   985,  1214,   998,  1017,   529,
    1023,  1244,   549,  1027,  1224,   503,   994,   996,   723,   685,
    1264,    -1,  1030,    -1,    -1,    -1,    -1,    -1,    -1,   514,
      -1,    -1,  1209,    -1,  1209,   553,    -1,  1214,    -1,    -1,
      -1,    -1,    -1,    -1,  1209,    -1,    -1,  1224,  1209,  1214,
      -1,    -1,    -1,  1214,    -1,    -1,    -1,    -1,  1214,  1209,
      -1,    -1,    -1,  1224,  1209,    -1,  1209,    -1,    -1,  1214,
      -1,  1214,    -1,    -1,    -1,    -1,  1209,    -1,    -1,    -1,
      -1,  1224,    -1,    -1,  1209,    -1,    -1,  1209,    -1,  1214,
      -1,  1209,    -1,    -1,    -1,    -1,  1214,    -1,    -1,    -1,
      -1,    -1,  1209,  1209,    -1,    -1,  1224,  1214,  1214,  1209,
      -1,    -1,    -1,    -1,  1214,    -1,    -1,    -1,    -1,    -1,
      -1,  1209,  1209,    -1,  1209,    -1,    -1,  1214,  1209,    -1,
      -1,    -1,  1209,    -1,  1209,    -1,    -1,    -1,    -1,  1209,
      -1,    -1,  1209,    -1,  1209,  1209,  1209,    -1,    -1,  1209,
    1209,    -1,  1209,    -1,    -1,    -1,  1209,  1209,    -1,    -1,
    1209,    -1,  1209,  1209,  1209,    -1,    -1,  1209,  1209,  1209
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,     0,     5,
       7,     9,   206,   207,   208,   209,   225,   226,   227,   232,
       7,   241,     7,   246,     7,   292,     7,   408,     7,   491,
       7,   507,     7,   443,     7,   449,     7,   473,     7,   384,
       7,   572,     7,   603,   233,   228,   242,   247,   293,   409,
     492,   508,   444,   450,   474,   385,   573,   604,   225,   234,
     235,   206,   230,   231,    10,   243,   245,    11,    14,    23,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    92,    93,   103,   104,   107,   108,   112,
     117,   118,   119,   120,   121,   126,   136,   139,   146,   147,
     151,   154,   158,   178,   179,   180,   181,   182,   191,   206,
     240,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   263,   264,   265,   266,   267,
     268,   269,   270,   273,   275,   277,   278,   279,   281,   283,
     284,   285,   286,   287,   288,   303,   305,   311,   313,   362,
     371,   378,   392,   402,   426,   427,   428,   429,   433,   441,
     467,   497,   499,   501,   512,   514,   516,   539,   551,   552,
     560,   570,   601,   610,   634,    15,    16,    19,    22,   240,
     290,   291,   294,   296,   299,   302,   497,   499,    89,    90,
      91,   105,   109,   110,   111,   122,   125,   133,   240,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   265,
     266,   267,   268,   269,   270,   273,   275,   277,   278,   279,
     281,   283,   410,   411,   412,   414,   416,   418,   420,   422,
     424,   426,   427,   428,   429,   432,   467,   485,   497,   499,
     501,   512,   514,   516,   536,   106,   240,   422,   424,   467,
     493,   494,   495,   497,   499,   121,   127,   128,   129,   130,
     131,   132,   134,   240,   467,   497,   499,   509,   510,   511,
     512,   514,   516,   518,   522,   524,   526,   528,   530,   532,
     534,   441,    34,    94,    96,    97,   100,   101,   102,   240,
     331,   451,   452,   453,   454,   455,   456,   457,   459,   461,
     463,   464,   466,   497,   499,    95,    98,    99,   240,   331,
     455,   461,   475,   476,   477,   478,   479,   481,   482,   483,
     484,   497,   499,   137,   138,   240,   386,   387,   388,   390,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   178,   179,   240,   497,   499,   574,   575,
     576,   577,   579,   580,   582,   583,   584,   587,   589,   591,
     592,   593,   595,   597,   599,    12,    13,   605,   606,   607,
     609,     6,     3,     4,     8,     3,   244,     3,     8,   602,
     289,   306,     4,     4,     4,   513,   515,   517,   304,   312,
     314,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   262,     4,     4,     4,     4,     4,   271,   274,
     276,     4,     4,     4,   403,   442,   468,     4,   434,   498,
     500,   430,     4,     4,     4,   363,   540,   502,   379,   393,
       4,   372,   553,   561,   571,   280,   282,     4,     4,   611,
     635,     4,     3,     8,   295,   297,   300,     4,     3,     8,
     415,   417,   419,   486,   413,   421,     4,   425,   423,   537,
       3,     8,   496,     3,     8,   535,   523,   525,   529,   527,
     533,   531,   519,     8,     3,     8,   458,   332,     4,   462,
     460,   465,     4,     8,     3,   480,     4,     4,     8,     3,
     389,   391,     3,     8,     4,   590,   578,     4,   581,     4,
       4,   585,   588,     4,     4,   594,   596,   598,   600,     3,
       8,   608,     4,     3,     8,   225,   225,   206,     4,     4,
       4,     4,   209,   209,   209,     4,     4,     4,     4,     4,
       4,   207,   207,   207,   207,   207,   209,   208,   208,   208,
     207,   207,     4,   207,   207,   209,   209,   209,     4,     4,
       4,   209,   209,   209,     4,     4,     4,   207,     4,     4,
       4,     4,   209,   209,   209,     4,     4,     4,     4,     4,
     207,     4,     4,     4,     4,     4,     4,   209,   209,     4,
       4,   249,     4,     4,     4,   209,   291,     4,     4,     4,
       4,     4,     4,   207,     4,     4,     4,   411,     4,   494,
       4,     4,     4,     4,     4,     4,     4,     4,   511,     4,
       4,   207,     4,     4,     4,   209,   453,     4,   209,   209,
     477,     4,     4,   387,   209,     4,     4,   207,     4,   207,
     207,     4,     4,   209,   209,     4,     4,     4,     4,   575,
       4,   207,   606,     4,     7,     7,     7,     7,   206,   206,
     206,     7,     7,     5,   206,   174,   175,   176,   177,   209,
     272,   206,   206,     5,     5,     5,     5,   227,   229,   206,
     113,   114,   115,   116,   431,     5,     5,     5,     5,     7,
       7,     7,     7,     7,   206,   206,     5,     7,     5,   236,
      17,    18,   298,    20,    21,   301,   206,   206,   206,     5,
     206,   206,   236,   206,     7,   206,   236,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   229,   206,   206,   206,    18,   172,   586,   173,   272,
     206,   206,   206,     5,   225,   248,   605,   290,    24,   307,
     308,   309,    34,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    57,    58,
      59,    60,    61,    62,    63,    64,   240,   319,   320,   321,
     324,   326,   328,   330,   331,   333,   334,   335,   336,   337,
     338,   339,   340,   342,   344,   346,   348,   349,   350,   353,
     354,   356,   358,   360,   319,     7,   315,   316,   317,     7,
     404,   405,   406,     7,   445,   446,   447,     7,   469,   470,
     471,     7,   435,   436,   437,   127,   128,   129,   130,   132,
     364,   365,   366,   367,   368,   369,   370,     7,   541,   542,
       7,   503,   504,   505,     7,   380,   381,   382,   140,   141,
     142,   143,   144,   145,   394,   395,   396,   397,   398,   399,
     400,   401,   148,   149,   150,   240,   373,   374,   375,   376,
     377,   497,   499,   152,   153,   240,   497,   499,   554,   555,
     556,   558,   155,   156,   157,   206,   497,   499,   562,   563,
     564,   565,   567,   568,   574,     7,   612,   613,   192,   240,
     636,   637,   638,   237,     7,   487,   488,   489,   135,   518,
     520,   538,   315,     8,     8,     8,   310,     3,     8,   322,
     325,   327,   329,     4,     4,     4,     4,     4,   341,   343,
     345,   347,     4,     4,   351,     4,     4,     4,     4,   355,
     357,   359,   361,     3,     8,     8,   318,     6,     3,   407,
       6,     3,   448,     6,     3,   472,     6,     3,   438,     6,
       3,     3,     6,   543,     3,     6,   506,     6,     3,   383,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   557,   559,     3,     8,     4,
     566,     4,   569,     3,     8,     8,   614,     3,     6,     4,
       3,     8,   206,   238,   239,   490,     6,     3,   521,     8,
       6,     4,   308,     4,     4,     4,     4,   207,   209,   207,
     209,   207,     4,     4,     4,     4,   207,   207,     4,   207,
     207,   209,   207,     4,     4,     4,     4,   320,   319,   317,
     410,   406,   451,   447,   475,   471,   240,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   265,   266,   267,
     268,   269,   270,   273,   275,   277,   278,   279,   281,   283,
     331,   402,   420,   422,   424,   426,   427,   428,   429,   439,
     440,   467,   497,   499,   512,   514,   516,   536,   437,   365,
     123,   124,   240,   250,   251,   252,   331,   441,   467,   497,
     499,   512,   514,   516,   544,   545,   546,   547,   548,   550,
     542,   509,   505,   386,   382,   207,   207,   207,   207,   207,
     207,   395,   209,   207,   207,   374,     4,     4,   555,   209,
       4,   207,     4,   563,   183,   185,   186,   240,   331,   497,
     499,   615,   616,   617,   618,   620,   613,   209,   637,     6,
       3,   493,   489,     4,   206,    35,    36,    37,    38,   323,
     206,   206,   206,   206,   206,   206,   206,    54,    55,    56,
     352,   206,   206,   206,   206,     8,     8,     8,     8,     3,
       8,   549,     4,     8,     3,     8,     8,   206,   206,   206,
     225,   621,     4,   619,     3,     8,   206,     8,   236,   440,
       4,   209,   546,     4,   207,     4,   616,   206,     5,   206,
       7,   622,   623,   624,     3,     6,   184,   187,   188,   189,
     190,   625,   626,   627,   629,   630,   631,   632,   623,   628,
       4,     4,     4,   633,     3,     8,     4,   209,   207,   207,
       4,   626,   206,   206
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
     249,   249,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   262,   261,   263,   264,   265,   266,
     267,   268,   269,   271,   270,   272,   272,   272,   272,   272,
     274,   273,   276,   275,   277,   278,   280,   279,   282,   281,
     283,   284,   285,   286,   287,   289,   288,   290,   290,   290,
     291,   291,   291,   291,   291,   291,   291,   293,   292,   295,
     294,   297,   296,   298,   298,   300,   299,   301,   301,   302,
     304,   303,   306,   305,   307,   307,   307,   308,   310,   309,
     312,   311,   314,   313,   315,   315,   316,   316,   316,   318,
     317,   319,   319,   319,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     322,   321,   323,   323,   323,   323,   325,   324,   327,   326,
     329,   328,   330,   332,   331,   333,   334,   335,   336,   337,
     338,   339,   341,   340,   343,   342,   345,   344,   347,   346,
     348,   349,   351,   350,   352,   352,   352,   353,   355,   354,
     357,   356,   359,   358,   361,   360,   363,   362,   364,   364,
     364,   365,   365,   365,   365,   365,   366,   367,   368,   369,
     370,   372,   371,   373,   373,   373,   374,   374,   374,   374,
     374,   374,   375,   376,   377,   379,   378,   380,   380,   381,
     381,   381,   383,   382,   385,   384,   386,   386,   386,   386,
     387,   387,   389,   388,   391,   390,   393,   392,   394,   394,
     394,   395,   395,   395,   395,   395,   395,   396,   397,   398,
     399,   400,   401,   403,   402,   404,   404,   405,   405,   405,
     407,   406,   409,   408,   410,   410,   410,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   413,   412,   415,   414,   417,   416,   419,   418,
     421,   420,   423,   422,   425,   424,   426,   427,   428,   430,
     429,   431,   431,   431,   431,   432,   434,   433,   435,   435,
     436,   436,   436,   438,   437,   439,   439,   439,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   440,   440,
     440,   440,   440,   440,   440,   440,   440,   440,   442,   441,
     444,   443,   445,   445,   446,   446,   446,   448,   447,   450,
     449,   451,   451,   452,   452,   452,   453,   453,   453,   453,
     453,   453,   453,   453,   453,   453,   454,   455,   456,   458,
     457,   460,   459,   462,   461,   463,   465,   464,   466,   468,
     467,   469,   469,   470,   470,   470,   472,   471,   474,   473,
     475,   475,   476,   476,   476,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   478,   480,   479,   481,   482,   483,
     484,   486,   485,   487,   487,   488,   488,   488,   490,   489,
     492,   491,   493,   493,   493,   494,   494,   494,   494,   494,
     494,   494,   496,   495,   498,   497,   500,   499,   502,   501,
     503,   503,   504,   504,   504,   506,   505,   508,   507,   509,
     509,   510,   510,   510,   511,   511,   511,   511,   511,   511,
     511,   511,   511,   511,   511,   511,   511,   511,   511,   513,
     512,   515,   514,   517,   516,   519,   518,   521,   520,   523,
     522,   525,   524,   527,   526,   529,   528,   531,   530,   533,
     532,   535,   534,   537,   536,   538,   538,   540,   539,   541,
     541,   541,   543,   542,   544,   544,   545,   545,   545,   546,
     546,   546,   546,   546,   546,   546,   546,   546,   546,   546,
     546,   546,   546,   547,   549,   548,   550,   551,   553,   552,
     554,   554,   554,   555,   555,   555,   555,   555,   557,   556,
     559,   558,   561,   560,   562,   562,   562,   563,   563,   563,
     563,   563,   563,   564,   566,   565,   567,   569,   568,   571,
     570,   573,   572,   574,   574,   574,   575,   575,   575,   575,
     575,   575,   575,   575,   575,   575,   575,   575,   575,   575,
     575,   575,   575,   575,   576,   578,   577,   579,   581,   580,
     582,   583,   585,   584,   586,   586,   588,   587,   590,   589,
     591,   592,   594,   593,   596,   595,   598,   597,   600,   599,
     602,   601,   604,   603,   605,   605,   605,   606,   606,   608,
     607,   609,   611,   610,   612,   612,   612,   614,   613,   615,
     615,   615,   616,   616,   616,   616,   616,   616,   616,   617,
     619,   618,   621,   620,   622,   622,   622,   624,   623,   625,
     625,   625,   626,   626,   626,   626,   626,   628,   627,   629,
     630,   631,   633,   632,   635,   634,   636,   636,   636,   637,
     637,   638
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
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     4,     0,     4,
       3,     3,     3,     3,     3,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     1,     1,     0,     4,     1,     1,     3,
       0,     6,     0,     6,     1,     3,     2,     1,     0,     4,
       0,     6,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     0,     4,     1,     1,     1,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     0,     4,     1,     3,     2,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     0,     1,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     1,     0,     6,     1,
       3,     2,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     3,     0,     6,
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
       1,     3
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
  "\"ip-reservations-unique\"", "\"reservations-lookup-first\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"compatibility\"", "\"lenient-option-parsing\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4",
  "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
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
  "ip_reservations_unique", "reservations_lookup_first",
  "interfaces_config", "$@26", "interfaces_config_params",
  "interfaces_config_param", "sub_interfaces4", "$@27", "interfaces_list",
  "$@28", "dhcp_socket_type", "$@29", "socket_type", "outbound_interface",
  "$@30", "outbound_interface_value", "re_detect", "lease_database",
  "$@31", "sanity_checks", "$@32", "sanity_checks_params",
  "sanity_checks_param", "lease_checks", "$@33", "hosts_database", "$@34",
  "hosts_databases", "$@35", "database_list", "not_empty_database_list",
  "database", "$@36", "database_map_params", "database_map_param",
  "database_type", "$@37", "db_type", "user", "$@38", "password", "$@39",
  "host", "$@40", "port", "name", "$@41", "persist", "lfc_interval",
  "readonly", "connect_timeout", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@42", "keyspace", "$@43",
  "consistency", "$@44", "serial_consistency", "$@45",
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
     546,   547,   548,   551,   557,   563,   569,   575,   581,   587,
     593,   599,   605,   611,   617,   617,   626,   632,   638,   644,
     650,   656,   662,   668,   668,   677,   680,   683,   686,   689,
     695,   695,   704,   704,   713,   719,   725,   725,   734,   734,
     743,   749,   755,   761,   767,   773,   773,   785,   786,   787,
     792,   793,   794,   795,   796,   797,   798,   801,   801,   810,
     810,   821,   821,   829,   830,   833,   833,   841,   843,   847,
     854,   854,   867,   867,   878,   879,   880,   885,   887,   887,
     906,   906,   919,   919,   930,   931,   934,   935,   936,   941,
     941,   951,   952,   953,   958,   959,   960,   961,   962,   963,
     964,   965,   966,   967,   968,   969,   970,   971,   972,   973,
     974,   975,   976,   977,   978,   979,   980,   981,   982,   983,
     986,   986,   994,   995,   996,   997,  1000,  1000,  1009,  1009,
    1018,  1018,  1027,  1033,  1033,  1042,  1048,  1054,  1060,  1066,
    1072,  1078,  1084,  1084,  1093,  1093,  1102,  1102,  1111,  1111,
    1120,  1126,  1132,  1132,  1140,  1141,  1142,  1145,  1151,  1151,
    1160,  1160,  1169,  1169,  1178,  1178,  1187,  1187,  1198,  1199,
    1200,  1205,  1206,  1207,  1208,  1209,  1212,  1217,  1222,  1227,
    1232,  1239,  1239,  1252,  1253,  1254,  1259,  1260,  1261,  1262,
    1263,  1264,  1267,  1273,  1279,  1285,  1285,  1296,  1297,  1300,
    1301,  1302,  1307,  1307,  1317,  1317,  1327,  1328,  1329,  1332,
    1335,  1336,  1339,  1339,  1348,  1348,  1357,  1357,  1369,  1370,
    1371,  1376,  1377,  1378,  1379,  1380,  1381,  1384,  1390,  1396,
    1402,  1408,  1414,  1423,  1423,  1437,  1438,  1441,  1442,  1443,
    1452,  1452,  1478,  1478,  1489,  1490,  1491,  1497,  1498,  1499,
    1500,  1501,  1502,  1503,  1504,  1505,  1506,  1507,  1508,  1509,
    1510,  1511,  1512,  1513,  1514,  1515,  1516,  1517,  1518,  1519,
    1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,  1528,  1529,
    1530,  1531,  1532,  1533,  1534,  1535,  1536,  1537,  1538,  1539,
    1540,  1541,  1544,  1544,  1553,  1553,  1562,  1562,  1571,  1571,
    1580,  1580,  1589,  1589,  1598,  1598,  1609,  1615,  1621,  1627,
    1627,  1635,  1636,  1637,  1638,  1641,  1649,  1649,  1661,  1662,
    1666,  1667,  1668,  1673,  1673,  1681,  1682,  1683,  1688,  1689,
    1690,  1691,  1692,  1693,  1694,  1695,  1696,  1697,  1698,  1699,
    1700,  1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,
    1710,  1711,  1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,
    1720,  1721,  1722,  1723,  1724,  1725,  1726,  1727,  1734,  1734,
    1748,  1748,  1757,  1758,  1761,  1762,  1763,  1770,  1770,  1785,
    1785,  1799,  1800,  1803,  1804,  1805,  1810,  1811,  1812,  1813,
    1814,  1815,  1816,  1817,  1818,  1819,  1822,  1824,  1830,  1832,
    1832,  1841,  1841,  1850,  1850,  1859,  1861,  1861,  1870,  1880,
    1880,  1893,  1894,  1899,  1900,  1901,  1908,  1908,  1920,  1920,
    1932,  1933,  1938,  1939,  1940,  1947,  1948,  1949,  1950,  1951,
    1952,  1953,  1954,  1955,  1958,  1960,  1960,  1969,  1971,  1973,
    1979,  1988,  1988,  2001,  2002,  2005,  2006,  2007,  2012,  2012,
    2022,  2022,  2032,  2033,  2034,  2039,  2040,  2041,  2042,  2043,
    2044,  2045,  2048,  2048,  2057,  2057,  2082,  2082,  2112,  2112,
    2123,  2124,  2127,  2128,  2129,  2134,  2134,  2143,  2143,  2152,
    2153,  2156,  2157,  2158,  2164,  2165,  2166,  2167,  2168,  2169,
    2170,  2171,  2172,  2173,  2174,  2175,  2176,  2177,  2178,  2181,
    2181,  2190,  2190,  2199,  2199,  2208,  2208,  2217,  2217,  2228,
    2228,  2237,  2237,  2246,  2246,  2255,  2255,  2264,  2264,  2273,
    2273,  2282,  2282,  2296,  2296,  2307,  2308,  2314,  2314,  2325,
    2326,  2327,  2332,  2332,  2342,  2343,  2346,  2347,  2348,  2353,
    2354,  2355,  2356,  2357,  2358,  2359,  2360,  2361,  2362,  2363,
    2364,  2365,  2366,  2369,  2371,  2371,  2380,  2388,  2396,  2396,
    2407,  2408,  2409,  2414,  2415,  2416,  2417,  2418,  2421,  2421,
    2430,  2430,  2442,  2442,  2455,  2456,  2457,  2462,  2463,  2464,
    2465,  2466,  2467,  2470,  2476,  2476,  2485,  2491,  2491,  2501,
    2501,  2514,  2514,  2524,  2525,  2526,  2531,  2532,  2533,  2534,
    2535,  2536,  2537,  2538,  2539,  2540,  2541,  2542,  2543,  2544,
    2545,  2546,  2547,  2548,  2551,  2557,  2557,  2566,  2572,  2572,
    2581,  2587,  2593,  2593,  2602,  2603,  2606,  2606,  2616,  2616,
    2626,  2633,  2640,  2640,  2649,  2649,  2659,  2659,  2669,  2669,
    2681,  2681,  2693,  2693,  2703,  2704,  2705,  2711,  2712,  2715,
    2715,  2726,  2734,  2734,  2747,  2748,  2749,  2755,  2755,  2763,
    2764,  2765,  2770,  2771,  2772,  2773,  2774,  2775,  2776,  2779,
    2785,  2785,  2794,  2794,  2805,  2806,  2807,  2812,  2812,  2820,
    2821,  2822,  2827,  2828,  2829,  2830,  2831,  2834,  2834,  2843,
    2849,  2855,  2861,  2861,  2870,  2870,  2881,  2882,  2883,  2888,
    2889,  2892
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
#line 6226 "dhcp4_parser.cc"

#line 2898 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
