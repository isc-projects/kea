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
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 294 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 294 "dhcp4_parser.yy"
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
#line 303 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 304 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 305 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 306 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 307 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 308 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 309 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 310 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 311 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 312 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 313 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 314 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 315 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 323 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 324 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 325 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 326 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 327 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 328 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 329 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 332 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 337 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 342 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 348 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 355 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 360 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 366 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 371 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 374 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 382 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 386 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 390 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 396 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 398 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 407 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 411 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 415 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 425 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 434 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 439 "dhcp4_parser.yy"
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
#line 449 "dhcp4_parser.yy"
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
#line 458 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 466 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 472 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 476 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 483 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 135: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 557 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 136: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 563 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 137: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 569 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 138: // renew_timer: "renew-timer" ":" "integer"
#line 575 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 139: // rebind_timer: "rebind-timer" ":" "integer"
#line 581 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 140: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 587 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 141: // t1_percent: "t1-percent" ":" "floating point"
#line 593 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 142: // t2_percent: "t2-percent" ":" "floating point"
#line 599 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 143: // cache_threshold: "cache-threshold" ":" "floating point"
#line 605 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 144: // cache_max_age: "cache-max-age" ":" "integer"
#line 611 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 145: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 617 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 146: // $@20: %empty
#line 623 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 147: // server_tag: "server-tag" $@20 ":" "constant string"
#line 626 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 148: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 632 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 149: // $@21: %empty
#line 638 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1269 "dhcp4_parser.cc"
    break;

  case 150: // allocator: "allocator" $@21 ":" "constant string"
#line 641 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 151: // echo_client_id: "echo-client-id" ":" "boolean"
#line 647 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1289 "dhcp4_parser.cc"
    break;

  case 152: // match_client_id: "match-client-id" ":" "boolean"
#line 653 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1299 "dhcp4_parser.cc"
    break;

  case 153: // authoritative: "authoritative" ":" "boolean"
#line 659 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1309 "dhcp4_parser.cc"
    break;

  case 154: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 665 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1319 "dhcp4_parser.cc"
    break;

  case 155: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 671 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 156: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 677 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1339 "dhcp4_parser.cc"
    break;

  case 157: // $@22: %empty
#line 683 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1348 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 686 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "when-present"
#line 692 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1365 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "never"
#line 695 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1373 "dhcp4_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "always"
#line 698 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-not-present"
#line 701 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "boolean"
#line 704 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1398 "dhcp4_parser.cc"
    break;

  case 164: // $@23: %empty
#line 710 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 165: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 713 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 166: // $@24: %empty
#line 719 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp4_parser.cc"
    break;

  case 167: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 722 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1436 "dhcp4_parser.cc"
    break;

  case 168: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 728 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 169: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 734 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 170: // $@25: %empty
#line 740 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 171: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 743 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 172: // $@26: %empty
#line 749 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1484 "dhcp4_parser.cc"
    break;

  case 173: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 752 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 174: // store_extended_info: "store-extended-info" ":" "boolean"
#line 758 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1504 "dhcp4_parser.cc"
    break;

  case 175: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 764 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1514 "dhcp4_parser.cc"
    break;

  case 176: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 770 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 177: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 776 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 178: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 782 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 179: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 788 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1554 "dhcp4_parser.cc"
    break;

  case 180: // $@27: %empty
#line 794 "dhcp4_parser.yy"
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
#line 800 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 184: // interfaces_config_params: interfaces_config_params ","
#line 808 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1584 "dhcp4_parser.cc"
    break;

  case 195: // $@28: %empty
#line 825 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 196: // sub_interfaces4: "{" $@28 interfaces_config_params "}"
#line 829 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1603 "dhcp4_parser.cc"
    break;

  case 197: // $@29: %empty
#line 834 "dhcp4_parser.yy"
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
#line 840 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 199: // $@30: %empty
#line 845 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1633 "dhcp4_parser.cc"
    break;

  case 200: // dhcp_socket_type: "dhcp-socket-type" $@30 ":" socket_type
#line 848 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1642 "dhcp4_parser.cc"
    break;

  case 201: // socket_type: "raw"
#line 853 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1648 "dhcp4_parser.cc"
    break;

  case 202: // socket_type: "udp"
#line 854 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1654 "dhcp4_parser.cc"
    break;

  case 203: // $@31: %empty
#line 857 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1663 "dhcp4_parser.cc"
    break;

  case 204: // outbound_interface: "outbound-interface" $@31 ":" outbound_interface_value
#line 860 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc"
    break;

  case 205: // outbound_interface_value: "same-as-inbound"
#line 865 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1680 "dhcp4_parser.cc"
    break;

  case 206: // outbound_interface_value: "use-routing"
#line 867 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1688 "dhcp4_parser.cc"
    break;

  case 207: // re_detect: "re-detect" ":" "boolean"
#line 871 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1698 "dhcp4_parser.cc"
    break;

  case 208: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 877 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1708 "dhcp4_parser.cc"
    break;

  case 209: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 883 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 210: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 889 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 211: // $@32: %empty
#line 895 "dhcp4_parser.yy"
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
#line 901 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1751 "dhcp4_parser.cc"
    break;

  case 213: // $@33: %empty
#line 908 "dhcp4_parser.yy"
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
#line 914 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 217: // sanity_checks_params: sanity_checks_params ","
#line 921 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1780 "dhcp4_parser.cc"
    break;

  case 220: // $@34: %empty
#line 930 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc"
    break;

  case 221: // lease_checks: "lease-checks" $@34 ":" "constant string"
#line 933 "dhcp4_parser.yy"
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
#line 949 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 223: // extended_info_checks: "extended-info-checks" $@35 ":" "constant string"
#line 952 "dhcp4_parser.yy"
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
#line 967 "dhcp4_parser.yy"
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
#line 973 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1860 "dhcp4_parser.cc"
    break;

  case 226: // $@37: %empty
#line 980 "dhcp4_parser.yy"
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
#line 986 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 232: // not_empty_database_list: not_empty_database_list ","
#line 997 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1889 "dhcp4_parser.cc"
    break;

  case 233: // $@38: %empty
#line 1002 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1899 "dhcp4_parser.cc"
    break;

  case 234: // database: "{" $@38 database_map_params "}"
#line 1006 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1909 "dhcp4_parser.cc"
    break;

  case 237: // database_map_params: database_map_params ","
#line 1014 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1917 "dhcp4_parser.cc"
    break;

  case 260: // $@39: %empty
#line 1043 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 261: // database_type: "type" $@39 ":" db_type
#line 1046 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1935 "dhcp4_parser.cc"
    break;

  case 262: // db_type: "memfile"
#line 1051 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1941 "dhcp4_parser.cc"
    break;

  case 263: // db_type: "mysql"
#line 1052 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1947 "dhcp4_parser.cc"
    break;

  case 264: // db_type: "postgresql"
#line 1053 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1953 "dhcp4_parser.cc"
    break;

  case 265: // $@40: %empty
#line 1056 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 266: // user: "user" $@40 ":" "constant string"
#line 1059 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 267: // $@41: %empty
#line 1065 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 268: // password: "password" $@41 ":" "constant string"
#line 1068 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1074 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2000 "dhcp4_parser.cc"
    break;

  case 270: // host: "host" $@42 ":" "constant string"
#line 1077 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 271: // port: "port" ":" "integer"
#line 1083 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 272: // $@43: %empty
#line 1089 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp4_parser.cc"
    break;

  case 273: // name: "name" $@43 ":" "constant string"
#line 1092 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2039 "dhcp4_parser.cc"
    break;

  case 274: // persist: "persist" ":" "boolean"
#line 1098 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2049 "dhcp4_parser.cc"
    break;

  case 275: // lfc_interval: "lfc-interval" ":" "integer"
#line 1104 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 276: // readonly: "readonly" ":" "boolean"
#line 1110 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 277: // connect_timeout: "connect-timeout" ":" "integer"
#line 1116 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 278: // read_timeout: "read-timeout" ":" "integer"
#line 1122 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 279: // write_timeout: "write-timeout" ":" "integer"
#line 1128 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 280: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1134 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 281: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1140 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2119 "dhcp4_parser.cc"
    break;

  case 282: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1146 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2129 "dhcp4_parser.cc"
    break;

  case 283: // $@44: %empty
#line 1152 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2138 "dhcp4_parser.cc"
    break;

  case 284: // on_fail: "on-fail" $@44 ":" on_fail_mode
#line 1155 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2147 "dhcp4_parser.cc"
    break;

  case 285: // on_fail_mode: "stop-retry-exit"
#line 1160 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2153 "dhcp4_parser.cc"
    break;

  case 286: // on_fail_mode: "serve-retry-exit"
#line 1161 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2159 "dhcp4_parser.cc"
    break;

  case 287: // on_fail_mode: "serve-retry-continue"
#line 1162 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2165 "dhcp4_parser.cc"
    break;

  case 288: // max_row_errors: "max-row-errors" ":" "integer"
#line 1165 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2175 "dhcp4_parser.cc"
    break;

  case 289: // $@45: %empty
#line 1171 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2184 "dhcp4_parser.cc"
    break;

  case 290: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1174 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2194 "dhcp4_parser.cc"
    break;

  case 291: // $@46: %empty
#line 1180 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp4_parser.cc"
    break;

  case 292: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1183 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc"
    break;

  case 293: // $@47: %empty
#line 1189 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2222 "dhcp4_parser.cc"
    break;

  case 294: // key_file: "key-file" $@47 ":" "constant string"
#line 1192 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2232 "dhcp4_parser.cc"
    break;

  case 295: // $@48: %empty
#line 1198 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2241 "dhcp4_parser.cc"
    break;

  case 296: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1201 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 297: // $@49: %empty
#line 1207 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2263 "dhcp4_parser.cc"
    break;

  case 298: // host_reservation_identifiers: "host-reservation-identifiers" $@49 ":" "[" host_reservation_identifiers_list "]"
#line 1213 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2272 "dhcp4_parser.cc"
    break;

  case 301: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1220 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2280 "dhcp4_parser.cc"
    break;

  case 307: // duid_id: "duid"
#line 1232 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2289 "dhcp4_parser.cc"
    break;

  case 308: // hw_address_id: "hw-address"
#line 1237 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2298 "dhcp4_parser.cc"
    break;

  case 309: // circuit_id: "circuit-id"
#line 1242 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 310: // client_id: "client-id"
#line 1247 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2316 "dhcp4_parser.cc"
    break;

  case 311: // flex_id: "flex-id"
#line 1252 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2325 "dhcp4_parser.cc"
    break;

  case 312: // $@50: %empty
#line 1259 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2337 "dhcp4_parser.cc"
    break;

  case 313: // dhcp_multi_threading: "multi-threading" $@50 ":" "{" multi_threading_params "}"
#line 1265 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2348 "dhcp4_parser.cc"
    break;

  case 316: // multi_threading_params: multi_threading_params ","
#line 1274 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2356 "dhcp4_parser.cc"
    break;

  case 323: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1287 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 324: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1293 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 325: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1299 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 326: // $@51: %empty
#line 1305 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 327: // hooks_libraries: "hooks-libraries" $@51 ":" "[" hooks_libraries_list "]"
#line 1311 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2407 "dhcp4_parser.cc"
    break;

  case 332: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1322 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2415 "dhcp4_parser.cc"
    break;

  case 333: // $@52: %empty
#line 1327 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 334: // hooks_library: "{" $@52 hooks_params "}"
#line 1331 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 335: // $@53: %empty
#line 1337 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 336: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1341 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2455 "dhcp4_parser.cc"
    break;

  case 339: // hooks_params: hooks_params ","
#line 1349 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2463 "dhcp4_parser.cc"
    break;

  case 343: // $@54: %empty
#line 1359 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc"
    break;

  case 344: // library: "library" $@54 ":" "constant string"
#line 1362 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 345: // $@55: %empty
#line 1368 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 346: // parameters: "parameters" $@55 ":" map_value
#line 1371 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc"
    break;

  case 347: // $@56: %empty
#line 1377 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2512 "dhcp4_parser.cc"
    break;

  case 348: // expired_leases_processing: "expired-leases-processing" $@56 ":" "{" expired_leases_params "}"
#line 1383 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2522 "dhcp4_parser.cc"
    break;

  case 351: // expired_leases_params: expired_leases_params ","
#line 1391 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2530 "dhcp4_parser.cc"
    break;

  case 358: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1404 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2540 "dhcp4_parser.cc"
    break;

  case 359: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1410 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 360: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1416 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2560 "dhcp4_parser.cc"
    break;

  case 361: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1422 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2570 "dhcp4_parser.cc"
    break;

  case 362: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1428 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 363: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1434 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 364: // $@57: %empty
#line 1443 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2602 "dhcp4_parser.cc"
    break;

  case 365: // subnet4_list: "subnet4" $@57 ":" "[" subnet4_list_content "]"
#line 1449 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2611 "dhcp4_parser.cc"
    break;

  case 370: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1463 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2619 "dhcp4_parser.cc"
    break;

  case 371: // $@58: %empty
#line 1472 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2629 "dhcp4_parser.cc"
    break;

  case 372: // subnet4: "{" $@58 subnet4_params "}"
#line 1476 "dhcp4_parser.yy"
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
#line 2655 "dhcp4_parser.cc"
    break;

  case 373: // $@59: %empty
#line 1498 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2665 "dhcp4_parser.cc"
    break;

  case 374: // sub_subnet4: "{" $@59 subnet4_params "}"
#line 1502 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2675 "dhcp4_parser.cc"
    break;

  case 377: // subnet4_params: subnet4_params ","
#line 1511 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2683 "dhcp4_parser.cc"
    break;

  case 424: // $@60: %empty
#line 1565 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 425: // subnet: "subnet" $@60 ":" "constant string"
#line 1568 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 426: // $@61: %empty
#line 1574 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2711 "dhcp4_parser.cc"
    break;

  case 427: // subnet_4o6_interface: "4o6-interface" $@61 ":" "constant string"
#line 1577 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 428: // $@62: %empty
#line 1583 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2730 "dhcp4_parser.cc"
    break;

  case 429: // subnet_4o6_interface_id: "4o6-interface-id" $@62 ":" "constant string"
#line 1586 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2740 "dhcp4_parser.cc"
    break;

  case 430: // $@63: %empty
#line 1592 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2749 "dhcp4_parser.cc"
    break;

  case 431: // subnet_4o6_subnet: "4o6-subnet" $@63 ":" "constant string"
#line 1595 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2759 "dhcp4_parser.cc"
    break;

  case 432: // $@64: %empty
#line 1601 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2768 "dhcp4_parser.cc"
    break;

  case 433: // interface: "interface" $@64 ":" "constant string"
#line 1604 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2778 "dhcp4_parser.cc"
    break;

  case 434: // $@65: %empty
#line 1610 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2787 "dhcp4_parser.cc"
    break;

  case 435: // client_class: "client-class" $@65 ":" "constant string"
#line 1613 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2797 "dhcp4_parser.cc"
    break;

  case 436: // $@66: %empty
#line 1619 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2809 "dhcp4_parser.cc"
    break;

  case 437: // require_client_classes: "require-client-classes" $@66 ":" list_strings
#line 1625 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2818 "dhcp4_parser.cc"
    break;

  case 438: // reservations_global: "reservations-global" ":" "boolean"
#line 1630 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2828 "dhcp4_parser.cc"
    break;

  case 439: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1636 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2838 "dhcp4_parser.cc"
    break;

  case 440: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1642 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2848 "dhcp4_parser.cc"
    break;

  case 441: // $@67: %empty
#line 1648 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2857 "dhcp4_parser.cc"
    break;

  case 442: // reservation_mode: "reservation-mode" $@67 ":" hr_mode
#line 1651 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2866 "dhcp4_parser.cc"
    break;

  case 443: // hr_mode: "disabled"
#line 1656 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2872 "dhcp4_parser.cc"
    break;

  case 444: // hr_mode: "out-of-pool"
#line 1657 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2878 "dhcp4_parser.cc"
    break;

  case 445: // hr_mode: "global"
#line 1658 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2884 "dhcp4_parser.cc"
    break;

  case 446: // hr_mode: "all"
#line 1659 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2890 "dhcp4_parser.cc"
    break;

  case 447: // id: "id" ":" "integer"
#line 1662 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 448: // $@68: %empty
#line 1670 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2912 "dhcp4_parser.cc"
    break;

  case 449: // shared_networks: "shared-networks" $@68 ":" "[" shared_networks_content "]"
#line 1676 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2921 "dhcp4_parser.cc"
    break;

  case 454: // shared_networks_list: shared_networks_list ","
#line 1689 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2929 "dhcp4_parser.cc"
    break;

  case 455: // $@69: %empty
#line 1694 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2939 "dhcp4_parser.cc"
    break;

  case 456: // shared_network: "{" $@69 shared_network_params "}"
#line 1698 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 459: // shared_network_params: shared_network_params ","
#line 1704 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2955 "dhcp4_parser.cc"
    break;

  case 501: // $@70: %empty
#line 1756 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2967 "dhcp4_parser.cc"
    break;

  case 502: // option_def_list: "option-def" $@70 ":" "[" option_def_list_content "]"
#line 1762 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 503: // $@71: %empty
#line 1770 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2985 "dhcp4_parser.cc"
    break;

  case 504: // sub_option_def_list: "{" $@71 option_def_list "}"
#line 1773 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2993 "dhcp4_parser.cc"
    break;

  case 509: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1785 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3001 "dhcp4_parser.cc"
    break;

  case 510: // $@72: %empty
#line 1792 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3011 "dhcp4_parser.cc"
    break;

  case 511: // option_def_entry: "{" $@72 option_def_params "}"
#line 1796 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3023 "dhcp4_parser.cc"
    break;

  case 512: // $@73: %empty
#line 1807 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3033 "dhcp4_parser.cc"
    break;

  case 513: // sub_option_def: "{" $@73 option_def_params "}"
#line 1811 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3045 "dhcp4_parser.cc"
    break;

  case 518: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1827 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3053 "dhcp4_parser.cc"
    break;

  case 530: // code: "code" ":" "integer"
#line 1846 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 532: // $@74: %empty
#line 1854 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 533: // option_def_type: "type" $@74 ":" "constant string"
#line 1857 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3082 "dhcp4_parser.cc"
    break;

  case 534: // $@75: %empty
#line 1863 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3091 "dhcp4_parser.cc"
    break;

  case 535: // option_def_record_types: "record-types" $@75 ":" "constant string"
#line 1866 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 536: // $@76: %empty
#line 1872 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3110 "dhcp4_parser.cc"
    break;

  case 537: // space: "space" $@76 ":" "constant string"
#line 1875 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3120 "dhcp4_parser.cc"
    break;

  case 539: // $@77: %empty
#line 1883 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3129 "dhcp4_parser.cc"
    break;

  case 540: // option_def_encapsulate: "encapsulate" $@77 ":" "constant string"
#line 1886 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 541: // option_def_array: "array" ":" "boolean"
#line 1892 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 542: // $@78: %empty
#line 1902 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3161 "dhcp4_parser.cc"
    break;

  case 543: // option_data_list: "option-data" $@78 ":" "[" option_data_list_content "]"
#line 1908 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3170 "dhcp4_parser.cc"
    break;

  case 548: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1923 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3178 "dhcp4_parser.cc"
    break;

  case 549: // $@79: %empty
#line 1930 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 550: // option_data_entry: "{" $@79 option_data_params "}"
#line 1934 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 551: // $@80: %empty
#line 1942 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3207 "dhcp4_parser.cc"
    break;

  case 552: // sub_option_data: "{" $@80 option_data_params "}"
#line 1946 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 557: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1962 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3224 "dhcp4_parser.cc"
    break;

  case 568: // $@81: %empty
#line 1982 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 569: // option_data_data: "data" $@81 ":" "constant string"
#line 1985 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3243 "dhcp4_parser.cc"
    break;

  case 572: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1995 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3253 "dhcp4_parser.cc"
    break;

  case 573: // option_data_always_send: "always-send" ":" "boolean"
#line 2001 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 574: // $@82: %empty
#line 2010 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3275 "dhcp4_parser.cc"
    break;

  case 575: // pools_list: "pools" $@82 ":" "[" pools_list_content "]"
#line 2016 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 580: // not_empty_pools_list: not_empty_pools_list ","
#line 2029 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3292 "dhcp4_parser.cc"
    break;

  case 581: // $@83: %empty
#line 2034 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3302 "dhcp4_parser.cc"
    break;

  case 582: // pool_list_entry: "{" $@83 pool_params "}"
#line 2038 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 583: // $@84: %empty
#line 2044 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 584: // sub_pool4: "{" $@84 pool_params "}"
#line 2048 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 587: // pool_params: pool_params ","
#line 2056 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3340 "dhcp4_parser.cc"
    break;

  case 595: // $@85: %empty
#line 2070 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3349 "dhcp4_parser.cc"
    break;

  case 596: // pool_entry: "pool" $@85 ":" "constant string"
#line 2073 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3359 "dhcp4_parser.cc"
    break;

  case 597: // $@86: %empty
#line 2079 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3367 "dhcp4_parser.cc"
    break;

  case 598: // user_context: "user-context" $@86 ":" map_value
#line 2081 "dhcp4_parser.yy"
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
#line 3394 "dhcp4_parser.cc"
    break;

  case 599: // $@87: %empty
#line 2104 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3402 "dhcp4_parser.cc"
    break;

  case 600: // comment: "comment" $@87 ":" "constant string"
#line 2106 "dhcp4_parser.yy"
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
#line 3431 "dhcp4_parser.cc"
    break;

  case 601: // $@88: %empty
#line 2134 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3443 "dhcp4_parser.cc"
    break;

  case 602: // reservations: "reservations" $@88 ":" "[" reservations_list "]"
#line 2140 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3452 "dhcp4_parser.cc"
    break;

  case 607: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2151 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3460 "dhcp4_parser.cc"
    break;

  case 608: // $@89: %empty
#line 2156 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3470 "dhcp4_parser.cc"
    break;

  case 609: // reservation: "{" $@89 reservation_params "}"
#line 2160 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3479 "dhcp4_parser.cc"
    break;

  case 610: // $@90: %empty
#line 2165 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3489 "dhcp4_parser.cc"
    break;

  case 611: // sub_reservation: "{" $@90 reservation_params "}"
#line 2169 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3498 "dhcp4_parser.cc"
    break;

  case 616: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2180 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3506 "dhcp4_parser.cc"
    break;

  case 632: // $@91: %empty
#line 2203 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3515 "dhcp4_parser.cc"
    break;

  case 633: // next_server: "next-server" $@91 ":" "constant string"
#line 2206 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 634: // $@92: %empty
#line 2212 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3534 "dhcp4_parser.cc"
    break;

  case 635: // server_hostname: "server-hostname" $@92 ":" "constant string"
#line 2215 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3544 "dhcp4_parser.cc"
    break;

  case 636: // $@93: %empty
#line 2221 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3553 "dhcp4_parser.cc"
    break;

  case 637: // boot_file_name: "boot-file-name" $@93 ":" "constant string"
#line 2224 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 638: // $@94: %empty
#line 2230 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3572 "dhcp4_parser.cc"
    break;

  case 639: // ip_address: "ip-address" $@94 ":" "constant string"
#line 2233 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 640: // $@95: %empty
#line 2239 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3594 "dhcp4_parser.cc"
    break;

  case 641: // ip_addresses: "ip-addresses" $@95 ":" list_strings
#line 2245 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3603 "dhcp4_parser.cc"
    break;

  case 642: // $@96: %empty
#line 2250 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 643: // duid: "duid" $@96 ":" "constant string"
#line 2253 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 644: // $@97: %empty
#line 2259 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3631 "dhcp4_parser.cc"
    break;

  case 645: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2262 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 646: // $@98: %empty
#line 2268 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3650 "dhcp4_parser.cc"
    break;

  case 647: // client_id_value: "client-id" $@98 ":" "constant string"
#line 2271 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3660 "dhcp4_parser.cc"
    break;

  case 648: // $@99: %empty
#line 2277 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3669 "dhcp4_parser.cc"
    break;

  case 649: // circuit_id_value: "circuit-id" $@99 ":" "constant string"
#line 2280 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3679 "dhcp4_parser.cc"
    break;

  case 650: // $@100: %empty
#line 2286 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3688 "dhcp4_parser.cc"
    break;

  case 651: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2289 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3698 "dhcp4_parser.cc"
    break;

  case 652: // $@101: %empty
#line 2295 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3707 "dhcp4_parser.cc"
    break;

  case 653: // hostname: "hostname" $@101 ":" "constant string"
#line 2298 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3717 "dhcp4_parser.cc"
    break;

  case 654: // $@102: %empty
#line 2304 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3729 "dhcp4_parser.cc"
    break;

  case 655: // reservation_client_classes: "client-classes" $@102 ":" list_strings
#line 2310 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3738 "dhcp4_parser.cc"
    break;

  case 656: // $@103: %empty
#line 2318 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3750 "dhcp4_parser.cc"
    break;

  case 657: // relay: "relay" $@103 ":" "{" relay_map "}"
#line 2324 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3759 "dhcp4_parser.cc"
    break;

  case 660: // $@104: %empty
#line 2336 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3771 "dhcp4_parser.cc"
    break;

  case 661: // client_classes: "client-classes" $@104 ":" "[" client_classes_list "]"
#line 2342 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 664: // client_classes_list: client_classes_list ","
#line 2349 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3788 "dhcp4_parser.cc"
    break;

  case 665: // $@105: %empty
#line 2354 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3798 "dhcp4_parser.cc"
    break;

  case 666: // client_class_entry: "{" $@105 client_class_params "}"
#line 2358 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 671: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2370 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3816 "dhcp4_parser.cc"
    break;

  case 688: // $@106: %empty
#line 2394 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3825 "dhcp4_parser.cc"
    break;

  case 689: // client_class_test: "test" $@106 ":" "constant string"
#line 2397 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3835 "dhcp4_parser.cc"
    break;

  case 690: // $@107: %empty
#line 2403 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 691: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2406 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3854 "dhcp4_parser.cc"
    break;

  case 692: // only_if_required: "only-if-required" ":" "boolean"
#line 2412 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3864 "dhcp4_parser.cc"
    break;

  case 693: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2420 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3874 "dhcp4_parser.cc"
    break;

  case 694: // $@108: %empty
#line 2428 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3886 "dhcp4_parser.cc"
    break;

  case 695: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2434 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3895 "dhcp4_parser.cc"
    break;

  case 698: // control_socket_params: control_socket_params ","
#line 2441 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3903 "dhcp4_parser.cc"
    break;

  case 704: // $@109: %empty
#line 2453 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3912 "dhcp4_parser.cc"
    break;

  case 705: // control_socket_type: "socket-type" $@109 ":" "constant string"
#line 2456 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3922 "dhcp4_parser.cc"
    break;

  case 706: // $@110: %empty
#line 2462 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3931 "dhcp4_parser.cc"
    break;

  case 707: // control_socket_name: "socket-name" $@110 ":" "constant string"
#line 2465 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3941 "dhcp4_parser.cc"
    break;

  case 708: // $@111: %empty
#line 2474 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3953 "dhcp4_parser.cc"
    break;

  case 709: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2480 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3964 "dhcp4_parser.cc"
    break;

  case 712: // queue_control_params: queue_control_params ","
#line 2489 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3972 "dhcp4_parser.cc"
    break;

  case 719: // enable_queue: "enable-queue" ":" "boolean"
#line 2502 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3982 "dhcp4_parser.cc"
    break;

  case 720: // $@112: %empty
#line 2508 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3991 "dhcp4_parser.cc"
    break;

  case 721: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2511 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4001 "dhcp4_parser.cc"
    break;

  case 722: // capacity: "capacity" ":" "integer"
#line 2517 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4011 "dhcp4_parser.cc"
    break;

  case 723: // $@113: %empty
#line 2523 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4020 "dhcp4_parser.cc"
    break;

  case 724: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2526 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4029 "dhcp4_parser.cc"
    break;

  case 725: // $@114: %empty
#line 2533 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4041 "dhcp4_parser.cc"
    break;

  case 726: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2539 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4052 "dhcp4_parser.cc"
    break;

  case 727: // $@115: %empty
#line 2546 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4062 "dhcp4_parser.cc"
    break;

  case 728: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2550 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4072 "dhcp4_parser.cc"
    break;

  case 731: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2558 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4080 "dhcp4_parser.cc"
    break;

  case 750: // enable_updates: "enable-updates" ":" "boolean"
#line 2583 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4090 "dhcp4_parser.cc"
    break;

  case 751: // $@116: %empty
#line 2589 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4099 "dhcp4_parser.cc"
    break;

  case 752: // server_ip: "server-ip" $@116 ":" "constant string"
#line 2592 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4109 "dhcp4_parser.cc"
    break;

  case 753: // server_port: "server-port" ":" "integer"
#line 2598 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4119 "dhcp4_parser.cc"
    break;

  case 754: // $@117: %empty
#line 2604 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4128 "dhcp4_parser.cc"
    break;

  case 755: // sender_ip: "sender-ip" $@117 ":" "constant string"
#line 2607 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4138 "dhcp4_parser.cc"
    break;

  case 756: // sender_port: "sender-port" ":" "integer"
#line 2613 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4148 "dhcp4_parser.cc"
    break;

  case 757: // max_queue_size: "max-queue-size" ":" "integer"
#line 2619 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4158 "dhcp4_parser.cc"
    break;

  case 758: // $@118: %empty
#line 2625 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4167 "dhcp4_parser.cc"
    break;

  case 759: // ncr_protocol: "ncr-protocol" $@118 ":" ncr_protocol_value
#line 2628 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4176 "dhcp4_parser.cc"
    break;

  case 760: // ncr_protocol_value: "udp"
#line 2634 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4182 "dhcp4_parser.cc"
    break;

  case 761: // ncr_protocol_value: "tcp"
#line 2635 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4188 "dhcp4_parser.cc"
    break;

  case 762: // $@119: %empty
#line 2638 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4197 "dhcp4_parser.cc"
    break;

  case 763: // ncr_format: "ncr-format" $@119 ":" "JSON"
#line 2641 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4207 "dhcp4_parser.cc"
    break;

  case 764: // $@120: %empty
#line 2648 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4216 "dhcp4_parser.cc"
    break;

  case 765: // dep_qualifying_suffix: "qualifying-suffix" $@120 ":" "constant string"
#line 2651 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4226 "dhcp4_parser.cc"
    break;

  case 766: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2658 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4236 "dhcp4_parser.cc"
    break;

  case 767: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2665 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4246 "dhcp4_parser.cc"
    break;

  case 768: // $@121: %empty
#line 2672 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4255 "dhcp4_parser.cc"
    break;

  case 769: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2675 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4264 "dhcp4_parser.cc"
    break;

  case 770: // $@122: %empty
#line 2681 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4273 "dhcp4_parser.cc"
    break;

  case 771: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2684 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4283 "dhcp4_parser.cc"
    break;

  case 772: // $@123: %empty
#line 2691 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4292 "dhcp4_parser.cc"
    break;

  case 773: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2694 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4302 "dhcp4_parser.cc"
    break;

  case 774: // $@124: %empty
#line 2701 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4311 "dhcp4_parser.cc"
    break;

  case 775: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2704 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4321 "dhcp4_parser.cc"
    break;

  case 776: // $@125: %empty
#line 2713 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4333 "dhcp4_parser.cc"
    break;

  case 777: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2719 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4343 "dhcp4_parser.cc"
    break;

  case 778: // $@126: %empty
#line 2725 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4353 "dhcp4_parser.cc"
    break;

  case 779: // sub_config_control: "{" $@126 config_control_params "}"
#line 2729 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4362 "dhcp4_parser.cc"
    break;

  case 782: // config_control_params: config_control_params ","
#line 2737 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4370 "dhcp4_parser.cc"
    break;

  case 785: // $@127: %empty
#line 2747 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4382 "dhcp4_parser.cc"
    break;

  case 786: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2753 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4391 "dhcp4_parser.cc"
    break;

  case 787: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2758 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4401 "dhcp4_parser.cc"
    break;

  case 788: // $@128: %empty
#line 2766 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4413 "dhcp4_parser.cc"
    break;

  case 789: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2772 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4422 "dhcp4_parser.cc"
    break;

  case 792: // loggers_entries: loggers_entries ","
#line 2781 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4430 "dhcp4_parser.cc"
    break;

  case 793: // $@129: %empty
#line 2787 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4440 "dhcp4_parser.cc"
    break;

  case 794: // logger_entry: "{" $@129 logger_params "}"
#line 2791 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4448 "dhcp4_parser.cc"
    break;

  case 797: // logger_params: logger_params ","
#line 2797 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4456 "dhcp4_parser.cc"
    break;

  case 805: // debuglevel: "debuglevel" ":" "integer"
#line 2811 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4466 "dhcp4_parser.cc"
    break;

  case 806: // $@130: %empty
#line 2817 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4475 "dhcp4_parser.cc"
    break;

  case 807: // severity: "severity" $@130 ":" "constant string"
#line 2820 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4485 "dhcp4_parser.cc"
    break;

  case 808: // $@131: %empty
#line 2826 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4497 "dhcp4_parser.cc"
    break;

  case 809: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2832 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4506 "dhcp4_parser.cc"
    break;

  case 812: // output_options_list_content: output_options_list_content ","
#line 2839 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4514 "dhcp4_parser.cc"
    break;

  case 813: // $@132: %empty
#line 2844 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4524 "dhcp4_parser.cc"
    break;

  case 814: // output_entry: "{" $@132 output_params_list "}"
#line 2848 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4532 "dhcp4_parser.cc"
    break;

  case 817: // output_params_list: output_params_list ","
#line 2854 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4540 "dhcp4_parser.cc"
    break;

  case 823: // $@133: %empty
#line 2866 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4549 "dhcp4_parser.cc"
    break;

  case 824: // output: "output" $@133 ":" "constant string"
#line 2869 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4559 "dhcp4_parser.cc"
    break;

  case 825: // flush: "flush" ":" "boolean"
#line 2875 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4569 "dhcp4_parser.cc"
    break;

  case 826: // maxsize: "maxsize" ":" "integer"
#line 2881 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4579 "dhcp4_parser.cc"
    break;

  case 827: // maxver: "maxver" ":" "integer"
#line 2887 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4589 "dhcp4_parser.cc"
    break;

  case 828: // $@134: %empty
#line 2893 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4598 "dhcp4_parser.cc"
    break;

  case 829: // pattern: "pattern" $@134 ":" "constant string"
#line 2896 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4608 "dhcp4_parser.cc"
    break;

  case 830: // $@135: %empty
#line 2902 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4620 "dhcp4_parser.cc"
    break;

  case 831: // compatibility: "compatibility" $@135 ":" "{" compatibility_params "}"
#line 2908 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4629 "dhcp4_parser.cc"
    break;

  case 834: // compatibility_params: compatibility_params ","
#line 2915 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4637 "dhcp4_parser.cc"
    break;

  case 839: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2926 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4647 "dhcp4_parser.cc"
    break;

  case 840: // ignore-rai-link-selection: "ignore-rai-link-selection" ":" "boolean"
#line 2932 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4657 "dhcp4_parser.cc"
    break;

  case 841: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 2938 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4667 "dhcp4_parser.cc"
    break;


#line 4671 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -990;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     421,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,    51,    23,    59,    63,    69,    81,
      92,    96,   107,   121,   170,   269,   280,   281,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,    23,  -161,    64,   137,    85,   638,
     216,   233,   -34,    83,   175,   -83,   437,    22,  -990,    75,
     123,    88,   145,   247,  -990,    77,  -990,  -990,  -990,  -990,
     286,   293,   294,  -990,  -990,  -990,  -990,  -990,  -990,   309,
     311,   322,   323,   324,   331,   332,   333,   345,   352,   363,
    -990,   365,   366,   382,   383,   403,  -990,  -990,  -990,   404,
     405,   415,  -990,  -990,  -990,   419,  -990,  -990,  -990,  -990,
    -990,   420,   423,   425,  -990,  -990,  -990,  -990,  -990,   426,
    -990,  -990,  -990,  -990,  -990,  -990,   427,   428,   429,  -990,
    -990,   430,  -990,    94,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,   431,   432,   434,   435,  -990,   112,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,   436,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,   135,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,   146,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,   347,   350,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,   372,  -990,  -990,   438,  -990,  -990,  -990,   441,
    -990,  -990,   410,   422,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,   442,   443,  -990,
    -990,  -990,  -990,   433,   445,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,   149,  -990,  -990,
    -990,   446,  -990,  -990,   447,  -990,   449,   452,  -990,  -990,
     453,   454,  -990,  -990,  -990,  -990,  -990,  -990,  -990,   152,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,   455,   172,  -990,
    -990,  -990,  -990,    23,    23,  -990,   250,   457,  -990,  -990,
     460,   462,   464,   256,   258,   259,   471,   472,   475,   476,
     479,   481,   276,   277,   279,   282,   284,   288,   292,   295,
     297,   300,   303,   488,   306,   310,   307,   312,   313,   490,
     501,   502,   314,   315,   317,   519,   520,   527,   327,   529,
     530,   533,   535,   542,   334,   335,   337,   545,   547,   550,
     551,   552,   346,   558,   563,   564,   565,   569,   570,   362,
     367,   377,   575,   581,  -990,   137,  -990,   582,   583,   587,
     379,   397,   384,   385,    85,  -990,   607,   608,   609,   610,
     611,   627,   424,   628,   629,   630,   638,  -990,   632,   216,
    -990,   633,   635,   637,   639,   640,   641,   642,   644,  -990,
     233,  -990,   645,   646,   440,   649,   650,   651,   444,  -990,
      83,   652,   448,   450,  -990,   175,   655,   656,   -76,  -990,
     451,   658,   661,   456,   662,   463,   468,   669,   676,   470,
     473,   677,   680,   681,   683,   437,  -990,   684,   478,    22,
    -990,  -990,  -990,   686,   685,   690,   691,   692,  -990,  -990,
    -990,   491,   515,   521,   693,   722,   727,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,   523,  -990,
    -990,  -990,  -990,  -990,  -117,   524,   525,  -990,  -990,  -990,
     731,   732,   733,  -990,   532,   734,   737,   541,    84,  -990,
    -990,  -990,   735,   747,   748,   749,   751,  -990,   752,   754,
     755,   756,   556,   557,  -990,  -990,  -990,   763,   762,  -990,
     765,   122,   232,  -990,  -990,  -990,  -990,  -990,   561,   566,
     567,   768,   568,   571,  -990,   765,   572,   767,  -990,   573,
    -990,   765,   574,   576,   577,   578,   579,   580,   584,  -990,
     585,   586,  -990,   588,   589,   590,  -990,  -990,   591,  -990,
    -990,  -990,   592,   737,  -990,  -990,   593,   594,  -990,   595,
    -990,  -990,    15,   517,  -990,  -990,  -117,   596,   597,   598,
    -990,   770,  -990,  -990,    23,   137,    22,    85,   215,  -990,
    -990,  -990,   351,   351,   772,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,   773,   778,   784,  -990,   785,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,   181,   786,   790,
     802,   161,   -60,   -21,    38,   437,  -990,  -990,   803,  -127,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,   804,  -990,  -990,  -990,  -990,   127,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,   772,  -990,   222,   223,   224,
    -990,  -990,   243,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
     808,   809,   810,   811,   812,   815,   816,   817,   818,   819,
    -990,   820,  -990,  -990,  -990,  -990,  -990,   283,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
     326,  -990,   636,   822,  -990,  -990,   821,   823,  -990,  -990,
     824,   825,  -990,  -990,   826,   828,  -990,  -990,   827,   831,
    -990,  -990,  -990,  -990,  -990,  -990,    39,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,   119,  -990,  -990,   829,   833,  -990,
    -990,   832,   834,  -990,   835,   836,   837,   838,   839,   840,
     336,  -990,  -990,  -990,  -990,  -990,  -990,  -990,   841,   842,
     843,  -990,   340,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,   342,  -990,  -990,  -990,   845,  -990,
     846,  -990,  -990,  -990,   343,  -990,  -990,  -990,  -990,  -990,
     349,  -990,   158,  -990,   847,   848,   849,  -990,   370,  -990,
    -990,  -990,  -990,   619,  -990,   850,   851,  -990,  -990,  -990,
    -990,   852,   853,  -990,  -990,  -990,   854,   857,   215,  -990,
     858,   859,   860,   861,   657,   653,   659,   654,   660,   663,
     664,   665,   666,   667,   865,   668,   868,   869,   876,   877,
     351,  -990,  -990,   351,  -990,   772,   638,  -990,   773,    83,
    -990,   778,   175,  -990,   784,  1275,  -990,   785,   181,  -990,
     267,   786,  -990,   233,  -990,   790,   -83,  -990,   802,   671,
     672,   673,   674,   675,   678,   161,  -990,   679,   682,   687,
     -60,  -990,   883,   884,   -21,  -990,   688,   886,   689,   887,
      38,  -990,  -990,   -29,   803,  -990,   694,   695,   696,  -127,
    -990,  -990,   888,   892,   216,  -990,   804,   893,  -990,  -990,
     647,   700,  -990,   220,   701,   702,   703,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,   129,  -990,   704,
     705,   706,   707,  -990,   373,  -990,   374,  -990,   891,  -990,
     894,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,   376,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,   899,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,   896,   902,  -990,  -990,  -990,  -990,  -990,  -990,
     898,  -990,   380,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,   708,   709,  -990,  -990,   710,
    -990,    23,  -990,  -990,   917,  -990,  -990,  -990,  -990,  -990,
     412,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,   712,   413,  -990,   765,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  1275,  -990,   919,   920,
     713,  -990,   267,  -990,  -990,  -990,  -990,  -990,  -990,   921,
     716,   924,   -29,  -990,  -990,  -990,  -990,  -990,   720,   721,
    -990,  -990,   928,  -990,   724,  -990,  -990,  -990,   889,  -990,
    -990,   159,  -990,    89,   889,  -990,  -990,   932,   933,   940,
    -990,   414,  -990,  -990,  -990,  -990,  -990,  -990,  -990,   948,
     741,   744,   746,   954,    89,  -990,   750,  -990,  -990,  -990,
     760,  -990,  -990,  -990
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   195,     9,   373,    11,   583,    13,
     610,    15,   503,    17,   512,    19,   551,    21,   335,    23,
     727,    25,   778,    27,    46,    39,     0,     0,     0,     0,
       0,   612,     0,   514,   553,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   776,   180,   213,
       0,     0,     0,   632,   634,   636,   211,   224,   226,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,     0,     0,     0,     0,     0,   157,   164,   166,     0,
       0,     0,   364,   501,   542,     0,   149,   448,   597,   599,
     441,     0,     0,     0,   297,   660,   601,   326,   347,     0,
     312,   694,   708,   725,   170,   172,     0,     0,     0,   788,
     830,     0,   134,     0,    67,    70,    71,    72,    73,    74,
     108,   109,   110,   111,   112,    75,   103,   132,   133,    92,
      93,    94,   116,   117,   118,   119,   120,   121,   122,   123,
     114,   115,   124,   125,   126,   128,   129,   130,    78,    79,
     100,    80,    81,    82,   127,    86,    87,    76,   105,   106,
     107,   104,    77,    84,    85,    98,    99,   101,    95,    96,
      97,    83,    88,    89,    90,    91,   102,   113,   131,   197,
     199,   203,     0,     0,     0,     0,   194,     0,   182,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   426,   428,
     430,   574,   424,   432,     0,   436,   434,   656,   423,   378,
     379,   380,   381,   382,   406,   407,   408,   409,   410,   422,
     396,   397,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,     0,   375,   385,   401,   402,   403,   386,
     388,   389,   392,   393,   394,   391,   387,   383,   384,   404,
     405,   390,   398,   399,   400,   395,   595,   594,   590,   591,
     589,     0,   585,   588,   592,   593,   654,   642,   644,   648,
     646,   652,   650,   638,   631,   625,   629,   630,     0,   613,
     614,   626,   627,   628,   622,   617,   623,   619,   620,   621,
     624,   618,     0,   532,   272,     0,   536,   534,   539,     0,
     528,   529,     0,   515,   516,   519,   531,   520,   521,   522,
     538,   523,   524,   525,   526,   527,   568,     0,     0,   566,
     567,   570,   571,     0,   554,   555,   558,   559,   560,   561,
     562,   563,   564,   565,   343,   345,   340,     0,   337,   341,
     342,     0,   764,   751,     0,   754,     0,     0,   758,   762,
       0,     0,   768,   770,   772,   774,   749,   747,   748,     0,
     729,   732,   733,   734,   735,   736,   737,   738,   739,   744,
     740,   741,   742,   743,   745,   746,   785,     0,     0,   780,
     783,   784,    45,    50,     0,    37,    43,     0,    64,    60,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,    69,    66,     0,     0,     0,
       0,     0,     0,     0,   184,   196,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   377,   374,     0,   587,
     584,     0,     0,     0,     0,     0,     0,     0,     0,   611,
     616,   504,     0,     0,     0,     0,     0,     0,     0,   513,
     518,     0,     0,     0,   552,   557,     0,     0,   339,   336,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   731,   728,     0,     0,   782,
     779,    49,    41,     0,     0,     0,     0,     0,   151,   152,
     153,     0,     0,     0,     0,     0,     0,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,     0,   175,
     176,   154,   155,   156,     0,     0,     0,   168,   169,   174,
       0,     0,     0,   148,     0,     0,     0,     0,     0,   438,
     439,   440,     0,     0,     0,     0,     0,   693,     0,     0,
       0,     0,     0,     0,   177,   178,   179,     0,     0,    68,
       0,     0,     0,   207,   208,   209,   210,   183,     0,     0,
       0,     0,     0,     0,   447,     0,     0,     0,   376,     0,
     586,     0,     0,     0,     0,     0,     0,     0,     0,   615,
       0,     0,   530,     0,     0,     0,   541,   517,     0,   572,
     573,   556,     0,     0,   338,   750,     0,     0,   753,     0,
     756,   757,     0,     0,   766,   767,     0,     0,     0,     0,
     730,     0,   787,   781,     0,     0,     0,     0,     0,   633,
     635,   637,     0,     0,   228,   147,   159,   160,   161,   162,
     163,   158,   165,   167,   366,   505,   544,   150,   450,    38,
     598,   600,   443,   444,   445,   446,   442,     0,     0,   603,
     328,     0,     0,     0,     0,     0,   171,   173,     0,     0,
      51,   198,   201,   202,   200,   205,   206,   204,   427,   429,
     431,   576,   425,   433,   437,   435,     0,   596,   655,   643,
     645,   649,   647,   653,   651,   639,   533,   273,   537,   535,
     540,   569,   344,   346,   765,   752,   755,   760,   761,   759,
     763,   769,   771,   773,   775,   228,    42,     0,     0,     0,
     220,   222,     0,   215,   218,   219,   260,   265,   267,   269,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     283,     0,   289,   291,   293,   295,   259,     0,   235,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
       0,   233,     0,   229,   230,   371,     0,   367,   368,   510,
       0,   506,   507,   549,     0,   545,   546,   455,     0,   451,
     452,   307,   308,   309,   310,   311,     0,   299,   302,   303,
     304,   305,   306,   665,     0,   662,   608,     0,   604,   605,
     333,     0,   329,   330,     0,     0,     0,     0,     0,     0,
       0,   349,   352,   353,   354,   355,   356,   357,     0,     0,
       0,   322,     0,   314,   317,   318,   319,   320,   321,   704,
     706,   703,   701,   702,     0,   696,   699,   700,     0,   720,
       0,   723,   716,   717,     0,   710,   713,   714,   715,   718,
       0,   793,     0,   790,     0,     0,     0,   838,     0,   832,
     835,   836,   837,    53,   581,     0,   577,   578,   640,   658,
     659,     0,     0,    62,   777,   181,     0,     0,   217,   214,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     237,   212,   225,     0,   227,   232,     0,   365,   370,   514,
     502,   509,   553,   543,   548,     0,   449,   454,   301,   298,
     667,   664,   661,   612,   602,   607,     0,   327,   332,     0,
       0,     0,     0,     0,     0,   351,   348,     0,     0,     0,
     316,   313,     0,     0,   698,   695,     0,     0,     0,     0,
     712,   709,   726,     0,   792,   789,     0,     0,     0,   834,
     831,    55,     0,    54,     0,   575,   580,     0,   657,   786,
       0,     0,   216,     0,     0,     0,     0,   271,   274,   275,
     276,   277,   278,   279,   280,   281,   282,     0,   288,     0,
       0,     0,     0,   236,     0,   231,     0,   369,     0,   508,
       0,   547,   500,   478,   479,   480,   463,   464,   483,   484,
     485,   486,   487,   499,   466,   467,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   460,   461,   462,
     476,   477,   473,   474,   475,   472,     0,   457,   465,   481,
     482,   468,   469,   470,   471,   453,   300,   688,   690,     0,
     683,   684,   685,   686,   687,   676,   677,   681,   682,   678,
     679,   680,     0,   668,   669,   672,   673,   674,   675,   663,
       0,   606,     0,   331,   358,   359,   360,   361,   362,   363,
     350,   323,   324,   325,   315,     0,     0,   697,   719,     0,
     722,     0,   711,   808,     0,   806,   804,   798,   802,   803,
       0,   795,   800,   801,   799,   791,   839,   840,   841,   833,
      52,    57,     0,   579,     0,   221,   223,   262,   263,   264,
     261,   266,   268,   270,   285,   286,   287,   284,   290,   292,
     294,   296,   234,   372,   511,   550,   459,   456,     0,     0,
       0,   666,   671,   609,   334,   705,   707,   721,   724,     0,
       0,     0,   797,   794,    56,   582,   641,   458,     0,     0,
     692,   670,     0,   805,     0,   796,   689,   691,     0,   807,
     813,     0,   810,     0,   812,   809,   823,     0,     0,     0,
     828,     0,   815,   818,   819,   820,   821,   822,   811,     0,
       0,     0,     0,     0,   817,   814,     0,   825,   826,   827,
       0,   816,   824,   829
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,   -52,  -990,  -585,  -990,   291,
    -990,  -990,  -990,  -990,  -990,  -990,  -632,  -990,  -990,  -990,
     -67,  -990,  -990,  -990,  -990,  -990,  -990,  -990,   150,   483,
      24,    25,    26,   -54,   -19,    -4,     3,    36,    37,    42,
    -990,  -990,  -990,  -990,    43,  -990,  -990,    44,    47,    48,
      49,    50,    54,  -990,   263,    55,  -990,    60,  -990,    61,
      62,    65,  -990,    66,  -990,    67,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,   264,   480,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,    27,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,   195,  -990,     8,  -990,  -699,     7,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,   -37,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,     9,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,   -16,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,    10,  -990,  -990,  -990,    11,   477,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,    56,  -990,  -990,  -990,  -990,
    -990,  -990,  -989,  -990,  -990,  -990,    82,  -990,  -990,  -990,
      79,   560,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -988,  -990,   -65,  -990,    74,  -990,    68,    72,    73,    78,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,    80,  -990,  -990,
    -144,   -62,  -990,  -990,  -990,  -990,  -990,    87,  -990,  -990,
    -990,    86,  -990,   544,  -990,   -63,  -990,  -990,  -990,  -990,
    -990,   -61,  -990,  -990,  -990,  -990,  -990,   -17,  -990,  -990,
    -990,    90,  -990,  -990,  -990,    91,  -990,   546,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,    30,
    -990,  -990,  -990,    35,   599,  -990,  -990,   -49,  -990,   -30,
    -990,   -51,  -990,  -990,  -990,    93,  -990,  -990,  -990,    97,
    -990,   562,     2,  -990,     6,  -990,    13,  -990,   329,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -979,  -990,  -990,  -990,
    -990,  -990,    95,  -990,  -990,  -990,  -142,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,    70,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,    57,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,   353,   531,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,   393,   534,  -990,
    -990,  -990,  -990,  -990,  -990,    58,  -990,  -990,  -141,  -990,
    -990,  -990,  -990,  -990,  -990,  -164,  -990,  -990,  -179,  -990,
    -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,  -990,    71,
    -990,  -990,  -990
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   730,
      82,    83,    39,    64,    79,    80,   751,   953,  1052,  1053,
     826,    41,    66,    85,   427,    86,    43,    67,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   453,   167,   168,   469,   169,   170,   171,   172,
     173,   174,   175,   459,   721,   176,   460,   177,   461,   178,
     179,   180,   487,   181,   488,   182,   183,   184,   185,   186,
     187,   188,   431,   227,   228,    45,    68,   229,   497,   230,
     498,   754,   231,   499,   757,   232,   233,   234,   235,   189,
     439,   190,   432,   802,   803,   804,   966,   805,   967,   191,
     440,   192,   441,   852,   853,   854,   993,   827,   828,   829,
     970,  1210,   830,   971,   831,   972,   832,   973,   833,   834,
     533,   835,   836,   837,   838,   839,   840,   841,   842,   843,
     844,   984,  1217,   845,   846,   986,   847,   987,   848,   988,
     849,   989,   193,   477,   876,   877,   878,   879,   880,   881,
     882,   194,   483,   912,   913,   914,   915,   916,   195,   480,
     891,   892,   893,  1016,    59,    75,   377,   378,   379,   546,
     380,   547,   196,   481,   900,   901,   902,   903,   904,   905,
     906,   907,   197,   465,   856,   857,   858,   996,    47,    69,
     273,   274,   275,   510,   276,   506,   277,   507,   278,   508,
     279,   511,   280,   514,   281,   513,   198,   199,   200,   201,
     473,   736,   286,   202,   470,   868,   869,   870,  1005,  1126,
    1127,   203,   466,    53,    72,   860,   861,   862,   999,    55,
      73,   342,   343,   344,   345,   346,   347,   348,   532,   349,
     536,   350,   535,   351,   352,   537,   353,   204,   467,   864,
     865,   866,  1002,    57,    74,   363,   364,   365,   366,   367,
     541,   368,   369,   370,   371,   288,   509,   955,   956,   957,
    1054,    49,    70,   301,   302,   303,   518,   205,   471,   206,
     472,   207,   479,   887,   888,   889,  1013,    51,    71,   318,
     319,   320,   208,   436,   209,   437,   210,   438,   324,   528,
     960,  1057,   325,   522,   326,   523,   327,   525,   328,   524,
     329,   527,   330,   526,   331,   521,   295,   515,   961,   211,
     478,   884,   885,  1010,  1152,  1153,  1154,  1155,  1156,  1228,
    1157,  1229,  1158,   212,   213,   484,   924,   925,   926,  1032,
     927,  1033,   214,   485,   934,   935,   936,   937,  1037,   938,
     939,  1039,   215,   486,    61,    76,   399,   400,   401,   402,
     552,   403,   404,   554,   405,   406,   407,   557,   789,   408,
     558,   409,   551,   410,   411,   412,   561,   413,   562,   414,
     563,   415,   564,   216,   430,    63,    77,   418,   419,   420,
     567,   421,   217,   492,   942,   943,  1043,  1190,  1191,  1192,
    1193,  1241,  1194,  1239,  1261,  1262,  1263,  1271,  1272,  1273,
    1279,  1274,  1275,  1276,  1277,  1283,   218,   493,   948,   949,
     950,   951,   952
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     152,   226,   248,   297,   314,   298,   340,   359,   376,   396,
     332,   361,    78,   362,   850,   252,  1118,  1119,   291,   236,
     289,   304,   316,   764,   354,   372,  1134,   397,    29,   768,
      30,   729,    31,   787,   416,   417,   341,   360,   237,   290,
     305,   317,  1008,   355,   373,  1009,   398,   128,   129,    81,
     253,    28,   287,   300,   315,   374,   375,   123,   716,   717,
     718,   719,   374,   375,   334,   254,    40,   944,   945,   946,
      42,   292,   255,   321,    84,   293,    44,   322,   128,   129,
     428,   422,   294,   151,   323,   429,   128,   129,    46,   908,
     909,   910,   424,   249,   250,   251,   720,   495,   729,    48,
     219,   220,   496,    50,   221,   256,   257,   222,   223,   224,
     225,   258,   259,   260,    52,   504,   261,   262,   263,   264,
     505,   333,  1011,   265,   266,  1012,   423,   151,    54,   267,
     268,   269,   919,   920,   270,   271,   272,   282,   516,   752,
     753,   283,   284,   517,   299,   128,   129,   285,    87,   519,
     151,    88,   548,   425,   520,   565,  1183,   549,  1184,  1185,
     566,  1044,  1264,    89,  1045,  1265,    90,    91,    92,    93,
      94,    95,    96,    97,    98,   569,   334,    56,   335,   336,
     570,   151,   337,   338,   339,  1214,  1215,  1216,   788,   151,
     128,   129,   128,   129,   928,   929,   930,   732,   733,   734,
     735,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   495,   569,   504,   123,   124,
     963,   964,   965,    32,    33,    34,    35,  1118,  1119,   125,
     126,   127,   800,   801,   128,   129,   968,  1134,   931,   130,
     426,   969,   755,   756,   131,   132,   133,   134,   135,  1207,
    1208,  1209,   313,   958,   136,    93,    94,    95,   334,   356,
     335,   336,   357,   358,   137,  1266,    58,   138,  1267,  1268,
    1269,  1270,   128,   129,   139,   140,   990,    60,    62,   141,
     433,   991,   142,   151,  1084,   151,   143,   434,   435,    93,
      94,    95,   894,   895,   896,   897,   898,   899,   124,   871,
     872,   873,   874,   442,   875,   443,   144,   145,   146,   147,
     148,   149,   296,   128,   129,   124,   444,   445,   446,   990,
     150,    99,   100,   101,   992,   447,   448,   449,   245,  1025,
     128,   129,   246,  1030,  1026,  1034,  1040,   151,  1031,   450,
    1035,  1041,   565,   530,   306,   529,   451,  1042,   123,   124,
     334,   307,   308,   309,   310,   311,   312,   452,   313,   454,
     455,   571,   572,  1049,   128,   129,   990,   516,  1050,  1226,
     531,  1222,  1223,   548,  1227,   151,   456,   457,  1234,   806,
    1137,  1138,  1139,   807,   808,   809,   810,   811,   812,   813,
     814,   815,   816,   817,   818,   819,   820,   458,   462,   463,
     821,   822,   823,   824,   825,  1242,   519,  1284,   539,   464,
    1243,  1245,  1285,   468,   474,   540,   151,   475,   152,   476,
     482,   489,   490,   491,   494,   500,   501,   226,   502,   503,
     512,   544,   534,   151,   334,   538,   542,   543,   545,   248,
     550,   553,   297,   555,   298,   236,   556,   559,   560,   568,
     573,   574,   252,   314,   575,   291,   576,   289,   577,   578,
     304,   579,   580,   340,   237,   581,   582,   151,   359,   583,
     584,   316,   361,   585,   362,   586,   290,   587,   588,   305,
     589,   354,   598,   590,   604,   591,   372,   253,   396,   287,
     317,   592,   300,   341,   593,   605,   606,   594,   360,   595,
     355,   596,   254,   315,   597,   373,   397,   599,   292,   255,
     601,   600,   293,   610,   611,   602,   603,   607,   608,   294,
     609,   612,   321,   614,   615,   398,   322,   616,   613,   617,
     249,   250,   251,   323,   128,   129,   618,   619,   620,   622,
     621,   623,   256,   257,   624,   625,   626,   627,   258,   259,
     260,   151,   628,   261,   262,   263,   264,   629,   630,   631,
     265,   266,  1246,   632,   633,   634,   267,   268,   269,   637,
     635,   270,   271,   272,   282,   638,   640,   641,   283,   284,
     636,   642,   643,   299,   285,   645,   646,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
     644,   648,   649,   650,   651,   652,   394,   395,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   653,   655,   656,   657,   654,   659,   661,   152,   662,
     226,   663,   994,   664,   665,   666,   667,   151,   668,   670,
     671,   672,   796,   673,   674,   675,   678,   676,   236,   682,
     683,   679,   686,   680,   685,   687,   689,   688,    91,    92,
      93,    94,    95,   692,   690,   911,   921,   237,   396,   691,
     693,   696,   947,   694,   697,   698,   695,   699,   701,   702,
     704,   790,   705,   917,   922,   932,   397,   706,   707,   708,
     712,   709,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   918,   923,   933,   398,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   710,   238,   239,   240,   713,
     124,   711,   714,   715,   722,   723,   724,   725,   726,   728,
     737,   126,   727,   241,    30,   128,   129,   242,   243,   244,
     130,   731,   738,   739,   740,   131,   132,   133,   741,   742,
     245,   743,   744,   745,   246,   136,   746,   747,   748,   749,
     750,   758,   247,   761,   766,   795,   759,   760,   762,   851,
     855,   763,   765,   767,   769,   859,   770,   771,   772,   773,
     774,   863,   867,   883,   775,   776,   777,   886,   778,   779,
     780,   781,   782,   784,   785,   786,   792,   793,   794,   890,
     941,   954,   974,   975,   976,   977,   978,   144,   145,   979,
     980,   981,   982,   983,   985,   995,   998,   997,  1001,  1051,
    1000,  1004,  1003,  1006,  1007,  1014,  1015,  1018,  1017,  1019,
    1020,  1021,  1022,  1023,  1024,  1027,  1028,  1029,   151,  1036,
    1038,  1046,  1047,  1048,  1056,   797,  1055,  1205,  1060,  1059,
    1058,  1061,  1063,  1064,  1065,  1066,  1068,  1070,  1067,  1077,
    1069,  1071,  1079,  1080,  1072,  1073,  1074,  1075,  1076,  1078,
    1081,  1082,  1164,  1165,  1166,  1167,  1168,  1175,  1176,  1169,
    1179,  1181,  1171,  1172,  1200,  1201,  1260,  1204,  1173,  1224,
    1180,  1178,  1225,  1230,  1231,  1232,  1233,  1196,  1197,  1198,
    1206,  1211,  1212,  1213,  1218,  1219,  1220,  1221,  1235,  1236,
    1237,  1240,  1244,  1248,  1249,  1252,  1250,  1253,  1254,   248,
    1256,  1257,   340,  1258,  1259,   359,  1280,  1281,  1092,   361,
    1120,   362,   252,  1140,  1282,   291,   314,   289,  1145,   376,
     354,  1096,  1286,   372,  1287,  1288,  1129,  1289,  1290,   791,
    1292,  1147,   341,   911,   316,   360,   290,   921,  1117,   355,
    1293,   799,   373,  1144,   783,  1130,  1186,   253,   639,   287,
    1148,   917,   947,   317,   647,   922,  1097,   297,  1128,   298,
     962,   932,   254,  1146,  1188,  1062,   315,  1083,   292,   255,
     918,  1098,   293,  1085,   923,   304,  1187,  1131,  1099,   294,
     933,  1132,  1149,  1189,  1174,   321,  1150,  1136,  1133,   322,
     249,   250,   251,  1151,   305,   684,   323,  1162,  1163,  1093,
    1094,  1095,   256,   257,  1141,  1142,  1143,   300,   258,   259,
     260,  1100,  1101,   261,   262,   263,   264,  1102,  1103,  1104,
     265,   266,  1105,  1106,  1107,  1108,   267,   268,   269,  1109,
    1110,   270,   271,   272,   282,  1111,  1112,  1113,   283,   284,
    1114,  1115,  1116,  1122,   285,  1086,   658,  1123,  1124,  1121,
    1087,  1170,  1247,  1125,   677,  1088,  1203,  1135,  1089,  1202,
    1251,   681,   669,  1090,  1091,   959,   700,  1182,   940,   798,
    1278,  1255,  1195,   703,  1177,  1291,  1159,     0,  1161,     0,
    1160,     0,     0,     0,     0,     0,     0,     0,   660,     0,
    1199,     0,     0,     0,     0,     0,     0,     0,   299,  1238,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1092,
       0,  1120,     0,     0,     0,  1140,     0,     0,     0,     0,
    1145,     0,  1096,     0,     0,  1186,     0,  1129,     0,     0,
       0,     0,     0,  1147,     0,     0,     0,     0,     0,  1117,
       0,     0,     0,  1188,     0,  1144,  1130,     0,     0,     0,
       0,     0,  1148,     0,     0,  1187,     0,  1097,     0,  1128,
       0,     0,  1189,     0,     0,  1146,     0,     0,     0,     0,
       0,     0,  1098,     0,     0,     0,     0,     0,  1131,  1099,
       0,     0,  1132,     0,  1149,     0,     0,     0,  1150,  1133,
       0,     0,     0,     0,     0,  1151,     0,     0,     0,     0,
    1093,  1094,  1095,     0,     0,     0,  1141,  1142,  1143,     0,
       0,     0,  1100,  1101,     0,     0,     0,     0,  1102,  1103,
    1104,     0,     0,  1105,  1106,  1107,  1108,     0,     0,     0,
    1109,  1110,     0,     0,     0,     0,  1111,  1112,  1113,     0,
       0,  1114,  1115,  1116,  1122,     0,     0,     0,  1123,  1124,
    1121,     0,     0,     0,  1125,    91,    92,    93,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,     0,
       0,     0,     0,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,     0,     0,     0,     0,   124,   334,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   126,     0,
       0,     0,   128,   129,     0,   243,     0,   130,     0,     0,
       0,     0,   131,   132,   133,     0,     0,   245,     0,     0,
       0,   246,     0,     0,     0,     0,     0,     0,     0,   247,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   144,   145,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   151
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      72,    74,    64,    74,   713,    69,  1005,  1005,    69,    68,
      69,    70,    71,   655,    73,    74,  1005,    76,     5,   661,
       7,   616,     9,    18,    12,    13,    73,    74,    68,    69,
      70,    71,     3,    73,    74,     6,    76,   107,   108,   210,
      69,     0,    69,    70,    71,   138,   139,    91,   175,   176,
     177,   178,   138,   139,    93,    69,     7,   194,   195,   196,
       7,    69,    69,    71,    10,    69,     7,    71,   107,   108,
       3,     6,    69,   210,    71,     8,   107,   108,     7,   149,
     150,   151,     4,    69,    69,    69,   213,     3,   683,     7,
      15,    16,     8,     7,    19,    69,    69,    22,    23,    24,
      25,    69,    69,    69,     7,     3,    69,    69,    69,    69,
       8,    38,     3,    69,    69,     6,     3,   210,     7,    69,
      69,    69,   153,   154,    69,    69,    69,    69,     3,    17,
      18,    69,    69,     8,    70,   107,   108,    69,    11,     3,
     210,    14,     3,     8,     8,     3,   185,     8,   187,   188,
       8,     3,     3,    26,     6,     6,    29,    30,    31,    32,
      33,    34,    35,    36,    37,     3,    93,     7,    95,    96,
       8,   210,    99,   100,   101,    56,    57,    58,   173,   210,
     107,   108,   107,   108,   156,   157,   158,   113,   114,   115,
     116,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,     3,     3,     3,    91,    92,
       8,     8,     8,   210,   211,   212,   213,  1226,  1226,   102,
     103,   104,    27,    28,   107,   108,     3,  1226,   210,   112,
       3,     8,    20,    21,   117,   118,   119,   120,   121,    39,
      40,    41,   135,   136,   127,    32,    33,    34,    93,    94,
      95,    96,    97,    98,   137,   186,     7,   140,   189,   190,
     191,   192,   107,   108,   147,   148,     3,     7,     7,   152,
       4,     8,   155,   210,   993,   210,   159,     4,     4,    32,
      33,    34,   141,   142,   143,   144,   145,   146,    92,   128,
     129,   130,   131,     4,   133,     4,   179,   180,   181,   182,
     183,   184,   106,   107,   108,    92,     4,     4,     4,     3,
     193,    64,    65,    66,     8,     4,     4,     4,   122,     3,
     107,   108,   126,     3,     8,     3,     3,   210,     8,     4,
       8,     8,     3,     3,   121,     8,     4,     8,    91,    92,
      93,   128,   129,   130,   131,   132,   133,     4,   135,     4,
       4,   423,   424,     3,   107,   108,     3,     3,     8,     3,
       8,     8,     8,     3,     8,   210,     4,     4,     8,    38,
     123,   124,   125,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,     4,     4,     4,
      59,    60,    61,    62,    63,     3,     3,     3,     8,     4,
       8,     8,     8,     4,     4,     3,   210,     4,   495,     4,
       4,     4,     4,     4,     4,     4,     4,   504,     4,     4,
       4,     8,     4,   210,    93,     4,     4,     4,     3,   516,
       4,     4,   519,     4,   519,   504,     4,     4,     4,     4,
     210,     4,   516,   530,     4,   516,     4,   516,     4,   213,
     519,   213,   213,   540,   504,     4,     4,   210,   545,     4,
       4,   530,   545,     4,   545,     4,   516,   211,   211,   519,
     211,   540,     4,   211,     4,   211,   545,   516,   565,   516,
     530,   213,   519,   540,   212,     4,     4,   212,   545,   212,
     540,   211,   516,   530,   211,   545,   565,   211,   516,   516,
     213,   211,   516,     4,     4,   213,   213,   213,   213,   516,
     213,     4,   530,     4,     4,   565,   530,     4,   211,     4,
     516,   516,   516,   530,   107,   108,     4,   213,   213,     4,
     213,     4,   516,   516,     4,     4,     4,   211,   516,   516,
     516,   210,     4,   516,   516,   516,   516,     4,     4,     4,
     516,   516,  1204,     4,     4,   213,   516,   516,   516,     4,
     213,   516,   516,   516,   516,     4,     4,     4,   516,   516,
     213,     4,   213,   519,   516,   211,   211,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     213,     4,     4,     4,     4,     4,   179,   180,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,     4,     4,     4,     4,   211,     4,     4,   705,     4,
     707,     4,     6,     4,     4,     4,     4,   210,     4,     4,
       4,   211,   704,     4,     4,     4,     4,   213,   707,     4,
       4,   213,     4,   213,   213,     4,     4,   211,    30,    31,
      32,    33,    34,     4,   211,   742,   743,   707,   745,   211,
       4,     4,   749,   213,     4,     4,   213,     4,     4,   211,
       4,   174,     7,   742,   743,   744,   745,     7,     7,     7,
       7,   210,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,   742,   743,   744,   745,    78,    79,    80,    81,
      82,    83,    84,    85,    86,   210,    88,    89,    90,     7,
      92,   210,     5,   210,   210,   210,     5,     5,     5,     5,
       5,   103,   210,   105,     7,   107,   108,   109,   110,   111,
     112,   210,     5,     5,     5,   117,   118,   119,     7,     7,
     122,     7,     7,     7,   126,   127,   210,   210,     5,     7,
       5,   210,   134,     5,     7,     5,   210,   210,   210,     7,
       7,   210,   210,   210,   210,     7,   210,   210,   210,   210,
     210,     7,     7,     7,   210,   210,   210,     7,   210,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,     7,
       7,     7,     4,     4,     4,     4,     4,   179,   180,     4,
       4,     4,     4,     4,     4,     3,     3,     6,     3,   210,
       6,     3,     6,     6,     3,     6,     3,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   210,     4,
       4,     4,     4,     4,     3,   705,     6,   210,     4,     6,
       8,     4,     4,     4,     4,     4,   213,   213,   211,     4,
     211,   211,     4,     4,   211,   211,   211,   211,   211,   211,
       4,     4,   211,   211,   211,   211,   211,     4,     4,   211,
       4,     4,   213,   211,     6,     3,     7,     4,   211,     8,
     211,   213,     8,     4,     8,     3,     8,   213,   213,   213,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,     4,   210,     4,     4,     4,   213,   211,     4,   996,
     210,   210,   999,     5,   210,  1002,     4,     4,  1005,  1002,
    1005,  1002,   996,  1010,     4,   996,  1013,   996,  1010,  1016,
     999,  1005,     4,  1002,   213,   211,  1005,   211,     4,   696,
     210,  1010,   999,  1030,  1013,  1002,   996,  1034,  1005,   999,
     210,   707,  1002,  1010,   683,  1005,  1043,   996,   495,   996,
    1010,  1030,  1049,  1013,   504,  1034,  1005,  1054,  1005,  1054,
     795,  1040,   996,  1010,  1043,   968,  1013,   990,   996,   996,
    1030,  1005,   996,   995,  1034,  1054,  1043,  1005,  1005,   996,
    1040,  1005,  1010,  1043,  1030,  1013,  1010,  1008,  1005,  1013,
     996,   996,   996,  1010,  1054,   548,  1013,  1016,  1018,  1005,
    1005,  1005,   996,   996,  1010,  1010,  1010,  1054,   996,   996,
     996,  1005,  1005,   996,   996,   996,   996,  1005,  1005,  1005,
     996,   996,  1005,  1005,  1005,  1005,   996,   996,   996,  1005,
    1005,   996,   996,   996,   996,  1005,  1005,  1005,   996,   996,
    1005,  1005,  1005,  1005,   996,   996,   516,  1005,  1005,  1005,
     998,  1025,  1226,  1005,   540,   999,  1056,  1007,  1001,  1054,
    1232,   545,   530,  1002,  1004,   766,   565,  1040,   745,   706,
    1264,  1242,  1044,   569,  1034,  1284,  1011,    -1,  1015,    -1,
    1013,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   519,    -1,
    1049,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1054,  1181,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1226,
      -1,  1226,    -1,    -1,    -1,  1232,    -1,    -1,    -1,    -1,
    1232,    -1,  1226,    -1,    -1,  1242,    -1,  1226,    -1,    -1,
      -1,    -1,    -1,  1232,    -1,    -1,    -1,    -1,    -1,  1226,
      -1,    -1,    -1,  1242,    -1,  1232,  1226,    -1,    -1,    -1,
      -1,    -1,  1232,    -1,    -1,  1242,    -1,  1226,    -1,  1226,
      -1,    -1,  1242,    -1,    -1,  1232,    -1,    -1,    -1,    -1,
      -1,    -1,  1226,    -1,    -1,    -1,    -1,    -1,  1226,  1226,
      -1,    -1,  1226,    -1,  1232,    -1,    -1,    -1,  1232,  1226,
      -1,    -1,    -1,    -1,    -1,  1232,    -1,    -1,    -1,    -1,
    1226,  1226,  1226,    -1,    -1,    -1,  1232,  1232,  1232,    -1,
      -1,    -1,  1226,  1226,    -1,    -1,    -1,    -1,  1226,  1226,
    1226,    -1,    -1,  1226,  1226,  1226,  1226,    -1,    -1,    -1,
    1226,  1226,    -1,    -1,    -1,    -1,  1226,  1226,  1226,    -1,
      -1,  1226,  1226,  1226,  1226,    -1,    -1,    -1,  1226,  1226,
    1226,    -1,    -1,    -1,  1226,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    -1,    -1,    -1,    -1,    92,    93,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,
      -1,    -1,   107,   108,    -1,   110,    -1,   112,    -1,    -1,
      -1,    -1,   117,   118,   119,    -1,    -1,   122,    -1,    -1,
      -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   134,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   179,   180,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   210
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   215,   216,   217,   218,   219,   220,
     221,   222,   223,   224,   225,   226,   227,   228,     0,     5,
       7,     9,   210,   211,   212,   213,   229,   230,   231,   236,
       7,   245,     7,   250,     7,   299,     7,   412,     7,   495,
       7,   511,     7,   447,     7,   453,     7,   477,     7,   388,
       7,   578,     7,   609,   237,   232,   246,   251,   300,   413,
     496,   512,   448,   454,   478,   389,   579,   610,   229,   238,
     239,   210,   234,   235,    10,   247,   249,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    91,    92,   102,   103,   104,   107,   108,
     112,   117,   118,   119,   120,   121,   127,   137,   140,   147,
     148,   152,   155,   159,   179,   180,   181,   182,   183,   184,
     193,   210,   244,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   267,   268,   270,
     271,   272,   273,   274,   275,   276,   279,   281,   283,   284,
     285,   287,   289,   290,   291,   292,   293,   294,   295,   313,
     315,   323,   325,   366,   375,   382,   396,   406,   430,   431,
     432,   433,   437,   445,   471,   501,   503,   505,   516,   518,
     520,   543,   557,   558,   566,   576,   607,   616,   640,    15,
      16,    19,    22,    23,    24,    25,   244,   297,   298,   301,
     303,   306,   309,   310,   311,   312,   501,   503,    88,    89,
      90,   105,   109,   110,   111,   122,   126,   134,   244,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   268,
     271,   272,   273,   274,   275,   276,   279,   281,   283,   284,
     285,   287,   289,   414,   415,   416,   418,   420,   422,   424,
     426,   428,   430,   431,   432,   433,   436,   471,   489,   501,
     503,   505,   516,   518,   520,   540,   106,   244,   426,   428,
     471,   497,   498,   499,   501,   503,   121,   128,   129,   130,
     131,   132,   133,   135,   244,   471,   501,   503,   513,   514,
     515,   516,   518,   520,   522,   526,   528,   530,   532,   534,
     536,   538,   445,    38,    93,    95,    96,    99,   100,   101,
     244,   343,   455,   456,   457,   458,   459,   460,   461,   463,
     465,   467,   468,   470,   501,   503,    94,    97,    98,   244,
     343,   459,   465,   479,   480,   481,   482,   483,   485,   486,
     487,   488,   501,   503,   138,   139,   244,   390,   391,   392,
     394,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   179,   180,   244,   501,   503,   580,
     581,   582,   583,   585,   586,   588,   589,   590,   593,   595,
     597,   598,   599,   601,   603,   605,    12,    13,   611,   612,
     613,   615,     6,     3,     4,     8,     3,   248,     3,     8,
     608,   296,   316,     4,     4,     4,   517,   519,   521,   314,
     324,   326,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   266,     4,     4,     4,     4,     4,   277,
     280,   282,     4,     4,     4,   407,   446,   472,     4,   269,
     438,   502,   504,   434,     4,     4,     4,   367,   544,   506,
     383,   397,     4,   376,   559,   567,   577,   286,   288,     4,
       4,     4,   617,   641,     4,     3,     8,   302,   304,   307,
       4,     4,     4,     4,     3,     8,   419,   421,   423,   490,
     417,   425,     4,   429,   427,   541,     3,     8,   500,     3,
       8,   539,   527,   529,   533,   531,   537,   535,   523,     8,
       3,     8,   462,   344,     4,   466,   464,   469,     4,     8,
       3,   484,     4,     4,     8,     3,   393,   395,     3,     8,
       4,   596,   584,     4,   587,     4,     4,   591,   594,     4,
       4,   600,   602,   604,   606,     3,     8,   614,     4,     3,
       8,   229,   229,   210,     4,     4,     4,     4,   213,   213,
     213,     4,     4,     4,     4,     4,     4,   211,   211,   211,
     211,   211,   213,   212,   212,   212,   211,   211,     4,   211,
     211,   213,   213,   213,     4,     4,     4,   213,   213,   213,
       4,     4,     4,   211,     4,     4,     4,     4,     4,   213,
     213,   213,     4,     4,     4,     4,     4,   211,     4,     4,
       4,     4,     4,     4,   213,   213,   213,     4,     4,   253,
       4,     4,     4,   213,   213,   211,   211,   298,     4,     4,
       4,     4,     4,     4,   211,     4,     4,     4,   415,     4,
     498,     4,     4,     4,     4,     4,     4,     4,     4,   515,
       4,     4,   211,     4,     4,     4,   213,   457,     4,   213,
     213,   481,     4,     4,   391,   213,     4,     4,   211,     4,
     211,   211,     4,     4,   213,   213,     4,     4,     4,     4,
     581,     4,   211,   612,     4,     7,     7,     7,     7,   210,
     210,   210,     7,     7,     5,   210,   175,   176,   177,   178,
     213,   278,   210,   210,     5,     5,     5,   210,     5,   231,
     233,   210,   113,   114,   115,   116,   435,     5,     5,     5,
       5,     7,     7,     7,     7,     7,   210,   210,     5,     7,
       5,   240,    17,    18,   305,    20,    21,   308,   210,   210,
     210,     5,   210,   210,   240,   210,     7,   210,   240,   210,
     210,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   233,   210,   210,   210,    18,   173,   592,
     174,   278,   210,   210,   210,     5,   229,   252,   611,   297,
      27,    28,   317,   318,   319,   321,    38,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    59,    60,    61,    62,    63,   244,   331,   332,   333,
     336,   338,   340,   342,   343,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   357,   358,   360,   362,   364,
     331,     7,   327,   328,   329,     7,   408,   409,   410,     7,
     449,   450,   451,     7,   473,   474,   475,     7,   439,   440,
     441,   128,   129,   130,   131,   133,   368,   369,   370,   371,
     372,   373,   374,     7,   545,   546,     7,   507,   508,   509,
       7,   384,   385,   386,   141,   142,   143,   144,   145,   146,
     398,   399,   400,   401,   402,   403,   404,   405,   149,   150,
     151,   244,   377,   378,   379,   380,   381,   501,   503,   153,
     154,   244,   501,   503,   560,   561,   562,   564,   156,   157,
     158,   210,   501,   503,   568,   569,   570,   571,   573,   574,
     580,     7,   618,   619,   194,   195,   196,   244,   642,   643,
     644,   645,   646,   241,     7,   491,   492,   493,   136,   522,
     524,   542,   327,     8,     8,     8,   320,   322,     3,     8,
     334,   337,   339,   341,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   355,     4,   359,   361,   363,   365,
       3,     8,     8,   330,     6,     3,   411,     6,     3,   452,
       6,     3,   476,     6,     3,   442,     6,     3,     3,     6,
     547,     3,     6,   510,     6,     3,   387,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,     4,     4,     4,
       3,     8,   563,   565,     3,     8,     4,   572,     4,   575,
       3,     8,     8,   620,     3,     6,     4,     4,     4,     3,
       8,   210,   242,   243,   494,     6,     3,   525,     8,     6,
       4,     4,   318,     4,     4,     4,     4,   211,   213,   211,
     213,   211,   211,   211,   211,   211,   211,     4,   211,     4,
       4,     4,     4,   332,   331,   329,   414,   410,   455,   451,
     479,   475,   244,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   268,   271,   272,   273,   274,   275,   276,
     279,   281,   283,   284,   285,   287,   289,   343,   406,   424,
     426,   428,   430,   431,   432,   433,   443,   444,   471,   501,
     503,   516,   518,   520,   540,   441,   369,   123,   124,   125,
     244,   254,   255,   256,   343,   445,   471,   501,   503,   516,
     518,   520,   548,   549,   550,   551,   552,   554,   556,   546,
     513,   509,   390,   386,   211,   211,   211,   211,   211,   211,
     399,   213,   211,   211,   378,     4,     4,   561,   213,     4,
     211,     4,   569,   185,   187,   188,   244,   343,   501,   503,
     621,   622,   623,   624,   626,   619,   213,   213,   213,   643,
       6,     3,   497,   493,     4,   210,   210,    39,    40,    41,
     335,   210,   210,   210,    56,    57,    58,   356,   210,   210,
     210,   210,     8,     8,     8,     8,     3,     8,   553,   555,
       4,     8,     3,     8,     8,   210,   210,   210,   229,   627,
       4,   625,     3,     8,   210,     8,   240,   444,     4,     4,
     213,   550,     4,   211,     4,   622,   210,   210,     5,   210,
       7,   628,   629,   630,     3,     6,   186,   189,   190,   191,
     192,   631,   632,   633,   635,   636,   637,   638,   629,   634,
       4,     4,     4,   639,     3,     8,     4,   213,   211,   211,
       4,   632,   210,   210
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   214,   216,   215,   217,   215,   218,   215,   219,   215,
     220,   215,   221,   215,   222,   215,   223,   215,   224,   215,
     225,   215,   226,   215,   227,   215,   228,   215,   229,   229,
     229,   229,   229,   229,   229,   230,   232,   231,   233,   234,
     234,   235,   235,   235,   237,   236,   238,   238,   239,   239,
     239,   241,   240,   242,   242,   243,   243,   243,   244,   246,
     245,   248,   247,   247,   249,   251,   250,   252,   252,   252,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   266,   265,   267,   269,
     268,   270,   271,   272,   273,   274,   275,   277,   276,   278,
     278,   278,   278,   278,   280,   279,   282,   281,   283,   284,
     286,   285,   288,   287,   289,   290,   291,   292,   293,   294,
     296,   295,   297,   297,   297,   298,   298,   298,   298,   298,
     298,   298,   298,   298,   298,   300,   299,   302,   301,   304,
     303,   305,   305,   307,   306,   308,   308,   309,   310,   311,
     312,   314,   313,   316,   315,   317,   317,   317,   318,   318,
     320,   319,   322,   321,   324,   323,   326,   325,   327,   327,
     328,   328,   328,   330,   329,   331,   331,   331,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     334,   333,   335,   335,   335,   337,   336,   339,   338,   341,
     340,   342,   344,   343,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   355,   354,   356,   356,   356,   357,   359,
     358,   361,   360,   363,   362,   365,   364,   367,   366,   368,
     368,   368,   369,   369,   369,   369,   369,   370,   371,   372,
     373,   374,   376,   375,   377,   377,   377,   378,   378,   378,
     378,   378,   378,   379,   380,   381,   383,   382,   384,   384,
     385,   385,   385,   387,   386,   389,   388,   390,   390,   390,
     390,   391,   391,   393,   392,   395,   394,   397,   396,   398,
     398,   398,   399,   399,   399,   399,   399,   399,   400,   401,
     402,   403,   404,   405,   407,   406,   408,   408,   409,   409,
     409,   411,   410,   413,   412,   414,   414,   414,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   417,   416,   419,   418,   421,   420,
     423,   422,   425,   424,   427,   426,   429,   428,   430,   431,
     432,   434,   433,   435,   435,   435,   435,   436,   438,   437,
     439,   439,   440,   440,   440,   442,   441,   443,   443,   443,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   444,   444,   444,   444,
     444,   446,   445,   448,   447,   449,   449,   450,   450,   450,
     452,   451,   454,   453,   455,   455,   456,   456,   456,   457,
     457,   457,   457,   457,   457,   457,   457,   457,   457,   458,
     459,   460,   462,   461,   464,   463,   466,   465,   467,   469,
     468,   470,   472,   471,   473,   473,   474,   474,   474,   476,
     475,   478,   477,   479,   479,   480,   480,   480,   481,   481,
     481,   481,   481,   481,   481,   481,   481,   482,   484,   483,
     485,   486,   487,   488,   490,   489,   491,   491,   492,   492,
     492,   494,   493,   496,   495,   497,   497,   497,   498,   498,
     498,   498,   498,   498,   498,   500,   499,   502,   501,   504,
     503,   506,   505,   507,   507,   508,   508,   508,   510,   509,
     512,   511,   513,   513,   514,   514,   514,   515,   515,   515,
     515,   515,   515,   515,   515,   515,   515,   515,   515,   515,
     515,   515,   517,   516,   519,   518,   521,   520,   523,   522,
     525,   524,   527,   526,   529,   528,   531,   530,   533,   532,
     535,   534,   537,   536,   539,   538,   541,   540,   542,   542,
     544,   543,   545,   545,   545,   547,   546,   548,   548,   549,
     549,   549,   550,   550,   550,   550,   550,   550,   550,   550,
     550,   550,   550,   550,   550,   550,   550,   551,   553,   552,
     555,   554,   556,   557,   559,   558,   560,   560,   560,   561,
     561,   561,   561,   561,   563,   562,   565,   564,   567,   566,
     568,   568,   568,   569,   569,   569,   569,   569,   569,   570,
     572,   571,   573,   575,   574,   577,   576,   579,   578,   580,
     580,   580,   581,   581,   581,   581,   581,   581,   581,   581,
     581,   581,   581,   581,   581,   581,   581,   581,   581,   581,
     582,   584,   583,   585,   587,   586,   588,   589,   591,   590,
     592,   592,   594,   593,   596,   595,   597,   598,   600,   599,
     602,   601,   604,   603,   606,   605,   608,   607,   610,   609,
     611,   611,   611,   612,   612,   614,   613,   615,   617,   616,
     618,   618,   618,   620,   619,   621,   621,   621,   622,   622,
     622,   622,   622,   622,   622,   623,   625,   624,   627,   626,
     628,   628,   628,   630,   629,   631,   631,   631,   632,   632,
     632,   632,   632,   634,   633,   635,   636,   637,   639,   638,
     641,   640,   642,   642,   642,   643,   643,   643,   643,   644,
     645,   646
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
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
       1,     0,     6,     0,     4,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
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
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
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
       0,     6,     1,     3,     2,     1,     1,     1,     1,     3,
       3,     3
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
  "\"connect-timeout\"", "\"read-timeout\"", "\"write-timeout\"",
  "\"tcp-user-timeout\"", "\"max-reconnect-tries\"",
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
  "\"exclude-first-last-24\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
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
  "ignore-rai-link-selection", "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   303,   303,   303,   304,   304,   305,   305,   306,   306,
     307,   307,   308,   308,   309,   309,   310,   310,   311,   311,
     312,   312,   313,   313,   314,   314,   315,   315,   323,   324,
     325,   326,   327,   328,   329,   332,   337,   337,   348,   351,
     352,   355,   360,   366,   371,   371,   378,   379,   382,   386,
     390,   396,   396,   403,   404,   407,   411,   415,   425,   434,
     434,   449,   449,   463,   466,   472,   472,   481,   482,   483,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     520,   521,   522,   523,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   557,   563,   569,   575,   581,
     587,   593,   599,   605,   611,   617,   623,   623,   632,   638,
     638,   647,   653,   659,   665,   671,   677,   683,   683,   692,
     695,   698,   701,   704,   710,   710,   719,   719,   728,   734,
     740,   740,   749,   749,   758,   764,   770,   776,   782,   788,
     794,   794,   806,   807,   808,   813,   814,   815,   816,   817,
     818,   819,   820,   821,   822,   825,   825,   834,   834,   845,
     845,   853,   854,   857,   857,   865,   867,   871,   877,   883,
     889,   895,   895,   908,   908,   919,   920,   921,   926,   927,
     930,   930,   949,   949,   967,   967,   980,   980,   991,   992,
     995,   996,   997,  1002,  1002,  1012,  1013,  1014,  1019,  1020,
    1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,
    1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,  1040,
    1043,  1043,  1051,  1052,  1053,  1056,  1056,  1065,  1065,  1074,
    1074,  1083,  1089,  1089,  1098,  1104,  1110,  1116,  1122,  1128,
    1134,  1140,  1146,  1152,  1152,  1160,  1161,  1162,  1165,  1171,
    1171,  1180,  1180,  1189,  1189,  1198,  1198,  1207,  1207,  1218,
    1219,  1220,  1225,  1226,  1227,  1228,  1229,  1232,  1237,  1242,
    1247,  1252,  1259,  1259,  1272,  1273,  1274,  1279,  1280,  1281,
    1282,  1283,  1284,  1287,  1293,  1299,  1305,  1305,  1316,  1317,
    1320,  1321,  1322,  1327,  1327,  1337,  1337,  1347,  1348,  1349,
    1352,  1355,  1356,  1359,  1359,  1368,  1368,  1377,  1377,  1389,
    1390,  1391,  1396,  1397,  1398,  1399,  1400,  1401,  1404,  1410,
    1416,  1422,  1428,  1434,  1443,  1443,  1457,  1458,  1461,  1462,
    1463,  1472,  1472,  1498,  1498,  1509,  1510,  1511,  1517,  1518,
    1519,  1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,  1528,
    1529,  1530,  1531,  1532,  1533,  1534,  1535,  1536,  1537,  1538,
    1539,  1540,  1541,  1542,  1543,  1544,  1545,  1546,  1547,  1548,
    1549,  1550,  1551,  1552,  1553,  1554,  1555,  1556,  1557,  1558,
    1559,  1560,  1561,  1562,  1565,  1565,  1574,  1574,  1583,  1583,
    1592,  1592,  1601,  1601,  1610,  1610,  1619,  1619,  1630,  1636,
    1642,  1648,  1648,  1656,  1657,  1658,  1659,  1662,  1670,  1670,
    1682,  1683,  1687,  1688,  1689,  1694,  1694,  1702,  1703,  1704,
    1709,  1710,  1711,  1712,  1713,  1714,  1715,  1716,  1717,  1718,
    1719,  1720,  1721,  1722,  1723,  1724,  1725,  1726,  1727,  1728,
    1729,  1730,  1731,  1732,  1733,  1734,  1735,  1736,  1737,  1738,
    1739,  1740,  1741,  1742,  1743,  1744,  1745,  1746,  1747,  1748,
    1749,  1756,  1756,  1770,  1770,  1779,  1780,  1783,  1784,  1785,
    1792,  1792,  1807,  1807,  1821,  1822,  1825,  1826,  1827,  1832,
    1833,  1834,  1835,  1836,  1837,  1838,  1839,  1840,  1841,  1844,
    1846,  1852,  1854,  1854,  1863,  1863,  1872,  1872,  1881,  1883,
    1883,  1892,  1902,  1902,  1915,  1916,  1921,  1922,  1923,  1930,
    1930,  1942,  1942,  1954,  1955,  1960,  1961,  1962,  1969,  1970,
    1971,  1972,  1973,  1974,  1975,  1976,  1977,  1980,  1982,  1982,
    1991,  1993,  1995,  2001,  2010,  2010,  2023,  2024,  2027,  2028,
    2029,  2034,  2034,  2044,  2044,  2054,  2055,  2056,  2061,  2062,
    2063,  2064,  2065,  2066,  2067,  2070,  2070,  2079,  2079,  2104,
    2104,  2134,  2134,  2145,  2146,  2149,  2150,  2151,  2156,  2156,
    2165,  2165,  2174,  2175,  2178,  2179,  2180,  2186,  2187,  2188,
    2189,  2190,  2191,  2192,  2193,  2194,  2195,  2196,  2197,  2198,
    2199,  2200,  2203,  2203,  2212,  2212,  2221,  2221,  2230,  2230,
    2239,  2239,  2250,  2250,  2259,  2259,  2268,  2268,  2277,  2277,
    2286,  2286,  2295,  2295,  2304,  2304,  2318,  2318,  2329,  2330,
    2336,  2336,  2347,  2348,  2349,  2354,  2354,  2364,  2365,  2368,
    2369,  2370,  2375,  2376,  2377,  2378,  2379,  2380,  2381,  2382,
    2383,  2384,  2385,  2386,  2387,  2388,  2389,  2392,  2394,  2394,
    2403,  2403,  2412,  2420,  2428,  2428,  2439,  2440,  2441,  2446,
    2447,  2448,  2449,  2450,  2453,  2453,  2462,  2462,  2474,  2474,
    2487,  2488,  2489,  2494,  2495,  2496,  2497,  2498,  2499,  2502,
    2508,  2508,  2517,  2523,  2523,  2533,  2533,  2546,  2546,  2556,
    2557,  2558,  2563,  2564,  2565,  2566,  2567,  2568,  2569,  2570,
    2571,  2572,  2573,  2574,  2575,  2576,  2577,  2578,  2579,  2580,
    2583,  2589,  2589,  2598,  2604,  2604,  2613,  2619,  2625,  2625,
    2634,  2635,  2638,  2638,  2648,  2648,  2658,  2665,  2672,  2672,
    2681,  2681,  2691,  2691,  2701,  2701,  2713,  2713,  2725,  2725,
    2735,  2736,  2737,  2743,  2744,  2747,  2747,  2758,  2766,  2766,
    2779,  2780,  2781,  2787,  2787,  2795,  2796,  2797,  2802,  2803,
    2804,  2805,  2806,  2807,  2808,  2811,  2817,  2817,  2826,  2826,
    2837,  2838,  2839,  2844,  2844,  2852,  2853,  2854,  2859,  2860,
    2861,  2862,  2863,  2866,  2866,  2875,  2881,  2887,  2893,  2893,
    2902,  2902,  2913,  2914,  2915,  2920,  2921,  2922,  2923,  2926,
    2932,  2938
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
#line 6329 "dhcp4_parser.cc"

#line 2944 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
