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
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 295 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 295 "dhcp4_parser.yy"
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
#line 304 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 305 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 306 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 307 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 308 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 309 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 310 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 311 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 312 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 313 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 314 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 315 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 316 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 324 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 325 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 326 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 327 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 328 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 329 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 330 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 333 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 338 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 343 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 349 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 356 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 361 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 367 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 372 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 375 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 383 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 387 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 391 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 397 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 399 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 408 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 412 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 416 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 426 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 435 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 440 "dhcp4_parser.yy"
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
#line 450 "dhcp4_parser.yy"
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
#line 459 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 467 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 473 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 477 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 484 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 135: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 558 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 136: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 564 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 137: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 570 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 138: // renew_timer: "renew-timer" ":" "integer"
#line 576 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 139: // rebind_timer: "rebind-timer" ":" "integer"
#line 582 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 140: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 588 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 141: // t1_percent: "t1-percent" ":" "floating point"
#line 594 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 142: // t2_percent: "t2-percent" ":" "floating point"
#line 600 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 143: // cache_threshold: "cache-threshold" ":" "floating point"
#line 606 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 144: // cache_max_age: "cache-max-age" ":" "integer"
#line 612 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 145: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 618 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 146: // $@20: %empty
#line 624 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 147: // server_tag: "server-tag" $@20 ":" "constant string"
#line 627 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 148: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 633 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 149: // $@21: %empty
#line 639 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1269 "dhcp4_parser.cc"
    break;

  case 150: // allocator: "allocator" $@21 ":" "constant string"
#line 642 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 151: // echo_client_id: "echo-client-id" ":" "boolean"
#line 648 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1289 "dhcp4_parser.cc"
    break;

  case 152: // match_client_id: "match-client-id" ":" "boolean"
#line 654 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1299 "dhcp4_parser.cc"
    break;

  case 153: // authoritative: "authoritative" ":" "boolean"
#line 660 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1309 "dhcp4_parser.cc"
    break;

  case 154: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 666 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1319 "dhcp4_parser.cc"
    break;

  case 155: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 672 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 156: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 678 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1339 "dhcp4_parser.cc"
    break;

  case 157: // $@22: %empty
#line 684 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1348 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 687 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "when-present"
#line 693 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1365 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "never"
#line 696 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1373 "dhcp4_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "always"
#line 699 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-not-present"
#line 702 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "boolean"
#line 705 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1398 "dhcp4_parser.cc"
    break;

  case 164: // $@23: %empty
#line 711 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 165: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 714 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 166: // $@24: %empty
#line 720 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp4_parser.cc"
    break;

  case 167: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 723 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1436 "dhcp4_parser.cc"
    break;

  case 168: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 729 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 169: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 735 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 170: // $@25: %empty
#line 741 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 171: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 744 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 172: // $@26: %empty
#line 750 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1484 "dhcp4_parser.cc"
    break;

  case 173: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 753 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 174: // store_extended_info: "store-extended-info" ":" "boolean"
#line 759 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1504 "dhcp4_parser.cc"
    break;

  case 175: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 765 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1514 "dhcp4_parser.cc"
    break;

  case 176: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 771 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 177: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 777 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 178: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 783 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 179: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 789 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1554 "dhcp4_parser.cc"
    break;

  case 180: // $@27: %empty
#line 795 "dhcp4_parser.yy"
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
#line 801 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 184: // interfaces_config_params: interfaces_config_params ","
#line 809 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1584 "dhcp4_parser.cc"
    break;

  case 195: // $@28: %empty
#line 826 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 196: // sub_interfaces4: "{" $@28 interfaces_config_params "}"
#line 830 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1603 "dhcp4_parser.cc"
    break;

  case 197: // $@29: %empty
#line 835 "dhcp4_parser.yy"
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
#line 841 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 199: // $@30: %empty
#line 846 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1633 "dhcp4_parser.cc"
    break;

  case 200: // dhcp_socket_type: "dhcp-socket-type" $@30 ":" socket_type
#line 849 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1642 "dhcp4_parser.cc"
    break;

  case 201: // socket_type: "raw"
#line 854 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1648 "dhcp4_parser.cc"
    break;

  case 202: // socket_type: "udp"
#line 855 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1654 "dhcp4_parser.cc"
    break;

  case 203: // $@31: %empty
#line 858 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1663 "dhcp4_parser.cc"
    break;

  case 204: // outbound_interface: "outbound-interface" $@31 ":" outbound_interface_value
#line 861 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc"
    break;

  case 205: // outbound_interface_value: "same-as-inbound"
#line 866 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1680 "dhcp4_parser.cc"
    break;

  case 206: // outbound_interface_value: "use-routing"
#line 868 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1688 "dhcp4_parser.cc"
    break;

  case 207: // re_detect: "re-detect" ":" "boolean"
#line 872 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1698 "dhcp4_parser.cc"
    break;

  case 208: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 878 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1708 "dhcp4_parser.cc"
    break;

  case 209: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 884 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 210: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 890 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 211: // $@32: %empty
#line 896 "dhcp4_parser.yy"
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
#line 902 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1751 "dhcp4_parser.cc"
    break;

  case 213: // $@33: %empty
#line 909 "dhcp4_parser.yy"
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
#line 915 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 217: // sanity_checks_params: sanity_checks_params ","
#line 922 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1780 "dhcp4_parser.cc"
    break;

  case 220: // $@34: %empty
#line 931 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc"
    break;

  case 221: // lease_checks: "lease-checks" $@34 ":" "constant string"
#line 934 "dhcp4_parser.yy"
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
#line 950 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 223: // extended_info_checks: "extended-info-checks" $@35 ":" "constant string"
#line 953 "dhcp4_parser.yy"
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
#line 968 "dhcp4_parser.yy"
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
#line 974 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1860 "dhcp4_parser.cc"
    break;

  case 226: // $@37: %empty
#line 981 "dhcp4_parser.yy"
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
#line 987 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 232: // not_empty_database_list: not_empty_database_list ","
#line 998 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1889 "dhcp4_parser.cc"
    break;

  case 233: // $@38: %empty
#line 1003 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1899 "dhcp4_parser.cc"
    break;

  case 234: // database: "{" $@38 database_map_params "}"
#line 1007 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1909 "dhcp4_parser.cc"
    break;

  case 237: // database_map_params: database_map_params ","
#line 1015 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1917 "dhcp4_parser.cc"
    break;

  case 260: // $@39: %empty
#line 1044 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 261: // database_type: "type" $@39 ":" db_type
#line 1047 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1935 "dhcp4_parser.cc"
    break;

  case 262: // db_type: "memfile"
#line 1052 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1941 "dhcp4_parser.cc"
    break;

  case 263: // db_type: "mysql"
#line 1053 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1947 "dhcp4_parser.cc"
    break;

  case 264: // db_type: "postgresql"
#line 1054 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1953 "dhcp4_parser.cc"
    break;

  case 265: // $@40: %empty
#line 1057 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 266: // user: "user" $@40 ":" "constant string"
#line 1060 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 267: // $@41: %empty
#line 1066 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 268: // password: "password" $@41 ":" "constant string"
#line 1069 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1075 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2000 "dhcp4_parser.cc"
    break;

  case 270: // host: "host" $@42 ":" "constant string"
#line 1078 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 271: // port: "port" ":" "integer"
#line 1084 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 272: // $@43: %empty
#line 1090 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp4_parser.cc"
    break;

  case 273: // name: "name" $@43 ":" "constant string"
#line 1093 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2039 "dhcp4_parser.cc"
    break;

  case 274: // persist: "persist" ":" "boolean"
#line 1099 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2049 "dhcp4_parser.cc"
    break;

  case 275: // lfc_interval: "lfc-interval" ":" "integer"
#line 1105 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 276: // readonly: "readonly" ":" "boolean"
#line 1111 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 277: // connect_timeout: "connect-timeout" ":" "integer"
#line 1117 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 278: // read_timeout: "read-timeout" ":" "integer"
#line 1123 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 279: // write_timeout: "write-timeout" ":" "integer"
#line 1129 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 280: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1135 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 281: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1141 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2119 "dhcp4_parser.cc"
    break;

  case 282: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1147 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2129 "dhcp4_parser.cc"
    break;

  case 283: // $@44: %empty
#line 1153 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2138 "dhcp4_parser.cc"
    break;

  case 284: // on_fail: "on-fail" $@44 ":" on_fail_mode
#line 1156 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2147 "dhcp4_parser.cc"
    break;

  case 285: // on_fail_mode: "stop-retry-exit"
#line 1161 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2153 "dhcp4_parser.cc"
    break;

  case 286: // on_fail_mode: "serve-retry-exit"
#line 1162 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2159 "dhcp4_parser.cc"
    break;

  case 287: // on_fail_mode: "serve-retry-continue"
#line 1163 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2165 "dhcp4_parser.cc"
    break;

  case 288: // max_row_errors: "max-row-errors" ":" "integer"
#line 1166 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2175 "dhcp4_parser.cc"
    break;

  case 289: // $@45: %empty
#line 1172 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2184 "dhcp4_parser.cc"
    break;

  case 290: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1175 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2194 "dhcp4_parser.cc"
    break;

  case 291: // $@46: %empty
#line 1181 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp4_parser.cc"
    break;

  case 292: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1184 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc"
    break;

  case 293: // $@47: %empty
#line 1190 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2222 "dhcp4_parser.cc"
    break;

  case 294: // key_file: "key-file" $@47 ":" "constant string"
#line 1193 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2232 "dhcp4_parser.cc"
    break;

  case 295: // $@48: %empty
#line 1199 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2241 "dhcp4_parser.cc"
    break;

  case 296: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1202 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 297: // $@49: %empty
#line 1208 "dhcp4_parser.yy"
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
#line 1214 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2272 "dhcp4_parser.cc"
    break;

  case 301: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1221 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2280 "dhcp4_parser.cc"
    break;

  case 307: // duid_id: "duid"
#line 1233 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2289 "dhcp4_parser.cc"
    break;

  case 308: // hw_address_id: "hw-address"
#line 1238 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2298 "dhcp4_parser.cc"
    break;

  case 309: // circuit_id: "circuit-id"
#line 1243 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 310: // client_id: "client-id"
#line 1248 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2316 "dhcp4_parser.cc"
    break;

  case 311: // flex_id: "flex-id"
#line 1253 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2325 "dhcp4_parser.cc"
    break;

  case 312: // $@50: %empty
#line 1260 "dhcp4_parser.yy"
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
#line 1266 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2348 "dhcp4_parser.cc"
    break;

  case 316: // multi_threading_params: multi_threading_params ","
#line 1275 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2356 "dhcp4_parser.cc"
    break;

  case 323: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1288 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 324: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1294 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 325: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1300 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 326: // $@51: %empty
#line 1306 "dhcp4_parser.yy"
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
#line 1312 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2407 "dhcp4_parser.cc"
    break;

  case 332: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1323 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2415 "dhcp4_parser.cc"
    break;

  case 333: // $@52: %empty
#line 1328 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 334: // hooks_library: "{" $@52 hooks_params "}"
#line 1332 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 335: // $@53: %empty
#line 1338 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 336: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1342 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2455 "dhcp4_parser.cc"
    break;

  case 339: // hooks_params: hooks_params ","
#line 1350 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2463 "dhcp4_parser.cc"
    break;

  case 343: // $@54: %empty
#line 1360 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc"
    break;

  case 344: // library: "library" $@54 ":" "constant string"
#line 1363 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 345: // $@55: %empty
#line 1369 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 346: // parameters: "parameters" $@55 ":" map_value
#line 1372 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc"
    break;

  case 347: // $@56: %empty
#line 1378 "dhcp4_parser.yy"
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
#line 1384 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2522 "dhcp4_parser.cc"
    break;

  case 351: // expired_leases_params: expired_leases_params ","
#line 1392 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2530 "dhcp4_parser.cc"
    break;

  case 358: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1405 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2540 "dhcp4_parser.cc"
    break;

  case 359: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1411 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 360: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1417 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2560 "dhcp4_parser.cc"
    break;

  case 361: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1423 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2570 "dhcp4_parser.cc"
    break;

  case 362: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1429 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 363: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1435 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 364: // $@57: %empty
#line 1444 "dhcp4_parser.yy"
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
#line 1450 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2611 "dhcp4_parser.cc"
    break;

  case 370: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1464 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2619 "dhcp4_parser.cc"
    break;

  case 371: // $@58: %empty
#line 1473 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2629 "dhcp4_parser.cc"
    break;

  case 372: // subnet4: "{" $@58 subnet4_params "}"
#line 1477 "dhcp4_parser.yy"
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
#line 1499 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2665 "dhcp4_parser.cc"
    break;

  case 374: // sub_subnet4: "{" $@59 subnet4_params "}"
#line 1503 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2675 "dhcp4_parser.cc"
    break;

  case 377: // subnet4_params: subnet4_params ","
#line 1512 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2683 "dhcp4_parser.cc"
    break;

  case 424: // $@60: %empty
#line 1566 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 425: // subnet: "subnet" $@60 ":" "constant string"
#line 1569 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 426: // $@61: %empty
#line 1575 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2711 "dhcp4_parser.cc"
    break;

  case 427: // subnet_4o6_interface: "4o6-interface" $@61 ":" "constant string"
#line 1578 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 428: // $@62: %empty
#line 1584 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2730 "dhcp4_parser.cc"
    break;

  case 429: // subnet_4o6_interface_id: "4o6-interface-id" $@62 ":" "constant string"
#line 1587 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2740 "dhcp4_parser.cc"
    break;

  case 430: // $@63: %empty
#line 1593 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2749 "dhcp4_parser.cc"
    break;

  case 431: // subnet_4o6_subnet: "4o6-subnet" $@63 ":" "constant string"
#line 1596 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2759 "dhcp4_parser.cc"
    break;

  case 432: // $@64: %empty
#line 1602 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2768 "dhcp4_parser.cc"
    break;

  case 433: // interface: "interface" $@64 ":" "constant string"
#line 1605 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2778 "dhcp4_parser.cc"
    break;

  case 434: // $@65: %empty
#line 1611 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2787 "dhcp4_parser.cc"
    break;

  case 435: // client_class: "client-class" $@65 ":" "constant string"
#line 1614 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2797 "dhcp4_parser.cc"
    break;

  case 436: // $@66: %empty
#line 1620 "dhcp4_parser.yy"
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
#line 1626 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2818 "dhcp4_parser.cc"
    break;

  case 438: // reservations_global: "reservations-global" ":" "boolean"
#line 1631 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2828 "dhcp4_parser.cc"
    break;

  case 439: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1637 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2838 "dhcp4_parser.cc"
    break;

  case 440: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1643 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2848 "dhcp4_parser.cc"
    break;

  case 441: // $@67: %empty
#line 1649 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2857 "dhcp4_parser.cc"
    break;

  case 442: // reservation_mode: "reservation-mode" $@67 ":" hr_mode
#line 1652 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2866 "dhcp4_parser.cc"
    break;

  case 443: // hr_mode: "disabled"
#line 1657 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2872 "dhcp4_parser.cc"
    break;

  case 444: // hr_mode: "out-of-pool"
#line 1658 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2878 "dhcp4_parser.cc"
    break;

  case 445: // hr_mode: "global"
#line 1659 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2884 "dhcp4_parser.cc"
    break;

  case 446: // hr_mode: "all"
#line 1660 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2890 "dhcp4_parser.cc"
    break;

  case 447: // id: "id" ":" "integer"
#line 1663 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 448: // $@68: %empty
#line 1671 "dhcp4_parser.yy"
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
#line 1677 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2921 "dhcp4_parser.cc"
    break;

  case 454: // shared_networks_list: shared_networks_list ","
#line 1690 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2929 "dhcp4_parser.cc"
    break;

  case 455: // $@69: %empty
#line 1695 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2939 "dhcp4_parser.cc"
    break;

  case 456: // shared_network: "{" $@69 shared_network_params "}"
#line 1699 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 459: // shared_network_params: shared_network_params ","
#line 1705 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2955 "dhcp4_parser.cc"
    break;

  case 501: // $@70: %empty
#line 1757 "dhcp4_parser.yy"
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
#line 1763 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 503: // $@71: %empty
#line 1771 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2985 "dhcp4_parser.cc"
    break;

  case 504: // sub_option_def_list: "{" $@71 option_def_list "}"
#line 1774 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2993 "dhcp4_parser.cc"
    break;

  case 509: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1786 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3001 "dhcp4_parser.cc"
    break;

  case 510: // $@72: %empty
#line 1793 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3011 "dhcp4_parser.cc"
    break;

  case 511: // option_def_entry: "{" $@72 option_def_params "}"
#line 1797 "dhcp4_parser.yy"
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
#line 1808 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3033 "dhcp4_parser.cc"
    break;

  case 513: // sub_option_def: "{" $@73 option_def_params "}"
#line 1812 "dhcp4_parser.yy"
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
#line 1828 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3053 "dhcp4_parser.cc"
    break;

  case 530: // code: "code" ":" "integer"
#line 1847 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 532: // $@74: %empty
#line 1855 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 533: // option_def_type: "type" $@74 ":" "constant string"
#line 1858 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3082 "dhcp4_parser.cc"
    break;

  case 534: // $@75: %empty
#line 1864 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3091 "dhcp4_parser.cc"
    break;

  case 535: // option_def_record_types: "record-types" $@75 ":" "constant string"
#line 1867 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 536: // $@76: %empty
#line 1873 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3110 "dhcp4_parser.cc"
    break;

  case 537: // space: "space" $@76 ":" "constant string"
#line 1876 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3120 "dhcp4_parser.cc"
    break;

  case 539: // $@77: %empty
#line 1884 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3129 "dhcp4_parser.cc"
    break;

  case 540: // option_def_encapsulate: "encapsulate" $@77 ":" "constant string"
#line 1887 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 541: // option_def_array: "array" ":" "boolean"
#line 1893 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 542: // $@78: %empty
#line 1903 "dhcp4_parser.yy"
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
#line 1909 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3170 "dhcp4_parser.cc"
    break;

  case 548: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1924 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3178 "dhcp4_parser.cc"
    break;

  case 549: // $@79: %empty
#line 1931 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 550: // option_data_entry: "{" $@79 option_data_params "}"
#line 1935 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 551: // $@80: %empty
#line 1943 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3207 "dhcp4_parser.cc"
    break;

  case 552: // sub_option_data: "{" $@80 option_data_params "}"
#line 1947 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 557: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1963 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3224 "dhcp4_parser.cc"
    break;

  case 569: // $@81: %empty
#line 1984 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 570: // option_data_data: "data" $@81 ":" "constant string"
#line 1987 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3243 "dhcp4_parser.cc"
    break;

  case 573: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1997 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3253 "dhcp4_parser.cc"
    break;

  case 574: // option_data_always_send: "always-send" ":" "boolean"
#line 2003 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 575: // option_data_never_send: "never-send" ":" "boolean"
#line 2009 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 576: // $@82: %empty
#line 2018 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3285 "dhcp4_parser.cc"
    break;

  case 577: // pools_list: "pools" $@82 ":" "[" pools_list_content "]"
#line 2024 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3294 "dhcp4_parser.cc"
    break;

  case 582: // not_empty_pools_list: not_empty_pools_list ","
#line 2037 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3302 "dhcp4_parser.cc"
    break;

  case 583: // $@83: %empty
#line 2042 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 584: // pool_list_entry: "{" $@83 pool_params "}"
#line 2046 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 585: // $@84: %empty
#line 2052 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 586: // sub_pool4: "{" $@84 pool_params "}"
#line 2056 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 589: // pool_params: pool_params ","
#line 2064 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3350 "dhcp4_parser.cc"
    break;

  case 597: // $@85: %empty
#line 2078 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3359 "dhcp4_parser.cc"
    break;

  case 598: // pool_entry: "pool" $@85 ":" "constant string"
#line 2081 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3369 "dhcp4_parser.cc"
    break;

  case 599: // $@86: %empty
#line 2087 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3377 "dhcp4_parser.cc"
    break;

  case 600: // user_context: "user-context" $@86 ":" map_value
#line 2089 "dhcp4_parser.yy"
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
#line 3404 "dhcp4_parser.cc"
    break;

  case 601: // $@87: %empty
#line 2112 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3412 "dhcp4_parser.cc"
    break;

  case 602: // comment: "comment" $@87 ":" "constant string"
#line 2114 "dhcp4_parser.yy"
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
#line 3441 "dhcp4_parser.cc"
    break;

  case 603: // $@88: %empty
#line 2142 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3453 "dhcp4_parser.cc"
    break;

  case 604: // reservations: "reservations" $@88 ":" "[" reservations_list "]"
#line 2148 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3462 "dhcp4_parser.cc"
    break;

  case 609: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2159 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3470 "dhcp4_parser.cc"
    break;

  case 610: // $@89: %empty
#line 2164 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3480 "dhcp4_parser.cc"
    break;

  case 611: // reservation: "{" $@89 reservation_params "}"
#line 2168 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3489 "dhcp4_parser.cc"
    break;

  case 612: // $@90: %empty
#line 2173 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3499 "dhcp4_parser.cc"
    break;

  case 613: // sub_reservation: "{" $@90 reservation_params "}"
#line 2177 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3508 "dhcp4_parser.cc"
    break;

  case 618: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2188 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3516 "dhcp4_parser.cc"
    break;

  case 634: // $@91: %empty
#line 2211 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 635: // next_server: "next-server" $@91 ":" "constant string"
#line 2214 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 636: // $@92: %empty
#line 2220 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3544 "dhcp4_parser.cc"
    break;

  case 637: // server_hostname: "server-hostname" $@92 ":" "constant string"
#line 2223 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 638: // $@93: %empty
#line 2229 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 639: // boot_file_name: "boot-file-name" $@93 ":" "constant string"
#line 2232 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 640: // $@94: %empty
#line 2238 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 641: // ip_address: "ip-address" $@94 ":" "constant string"
#line 2241 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 642: // $@95: %empty
#line 2247 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3604 "dhcp4_parser.cc"
    break;

  case 643: // ip_addresses: "ip-addresses" $@95 ":" list_strings
#line 2253 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3613 "dhcp4_parser.cc"
    break;

  case 644: // $@96: %empty
#line 2258 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 645: // duid: "duid" $@96 ":" "constant string"
#line 2261 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3632 "dhcp4_parser.cc"
    break;

  case 646: // $@97: %empty
#line 2267 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 647: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2270 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3651 "dhcp4_parser.cc"
    break;

  case 648: // $@98: %empty
#line 2276 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3660 "dhcp4_parser.cc"
    break;

  case 649: // client_id_value: "client-id" $@98 ":" "constant string"
#line 2279 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3670 "dhcp4_parser.cc"
    break;

  case 650: // $@99: %empty
#line 2285 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3679 "dhcp4_parser.cc"
    break;

  case 651: // circuit_id_value: "circuit-id" $@99 ":" "constant string"
#line 2288 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3689 "dhcp4_parser.cc"
    break;

  case 652: // $@100: %empty
#line 2294 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3698 "dhcp4_parser.cc"
    break;

  case 653: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2297 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3708 "dhcp4_parser.cc"
    break;

  case 654: // $@101: %empty
#line 2303 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3717 "dhcp4_parser.cc"
    break;

  case 655: // hostname: "hostname" $@101 ":" "constant string"
#line 2306 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3727 "dhcp4_parser.cc"
    break;

  case 656: // $@102: %empty
#line 2312 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3739 "dhcp4_parser.cc"
    break;

  case 657: // reservation_client_classes: "client-classes" $@102 ":" list_strings
#line 2318 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3748 "dhcp4_parser.cc"
    break;

  case 658: // $@103: %empty
#line 2326 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 659: // relay: "relay" $@103 ":" "{" relay_map "}"
#line 2332 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3769 "dhcp4_parser.cc"
    break;

  case 662: // $@104: %empty
#line 2344 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3781 "dhcp4_parser.cc"
    break;

  case 663: // client_classes: "client-classes" $@104 ":" "[" client_classes_list "]"
#line 2350 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3790 "dhcp4_parser.cc"
    break;

  case 666: // client_classes_list: client_classes_list ","
#line 2357 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3798 "dhcp4_parser.cc"
    break;

  case 667: // $@105: %empty
#line 2362 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 668: // client_class_entry: "{" $@105 client_class_params "}"
#line 2366 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3818 "dhcp4_parser.cc"
    break;

  case 673: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2378 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3826 "dhcp4_parser.cc"
    break;

  case 690: // $@106: %empty
#line 2402 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3835 "dhcp4_parser.cc"
    break;

  case 691: // client_class_test: "test" $@106 ":" "constant string"
#line 2405 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3845 "dhcp4_parser.cc"
    break;

  case 692: // $@107: %empty
#line 2411 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3854 "dhcp4_parser.cc"
    break;

  case 693: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2414 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3864 "dhcp4_parser.cc"
    break;

  case 694: // only_if_required: "only-if-required" ":" "boolean"
#line 2420 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3874 "dhcp4_parser.cc"
    break;

  case 695: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2428 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3884 "dhcp4_parser.cc"
    break;

  case 696: // $@108: %empty
#line 2436 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3896 "dhcp4_parser.cc"
    break;

  case 697: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2442 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3905 "dhcp4_parser.cc"
    break;

  case 700: // control_socket_params: control_socket_params ","
#line 2449 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3913 "dhcp4_parser.cc"
    break;

  case 706: // $@109: %empty
#line 2461 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3922 "dhcp4_parser.cc"
    break;

  case 707: // control_socket_type: "socket-type" $@109 ":" "constant string"
#line 2464 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3932 "dhcp4_parser.cc"
    break;

  case 708: // $@110: %empty
#line 2470 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3941 "dhcp4_parser.cc"
    break;

  case 709: // control_socket_name: "socket-name" $@110 ":" "constant string"
#line 2473 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3951 "dhcp4_parser.cc"
    break;

  case 710: // $@111: %empty
#line 2482 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3963 "dhcp4_parser.cc"
    break;

  case 711: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2488 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3974 "dhcp4_parser.cc"
    break;

  case 714: // queue_control_params: queue_control_params ","
#line 2497 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3982 "dhcp4_parser.cc"
    break;

  case 721: // enable_queue: "enable-queue" ":" "boolean"
#line 2510 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3992 "dhcp4_parser.cc"
    break;

  case 722: // $@112: %empty
#line 2516 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4001 "dhcp4_parser.cc"
    break;

  case 723: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2519 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4011 "dhcp4_parser.cc"
    break;

  case 724: // capacity: "capacity" ":" "integer"
#line 2525 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4021 "dhcp4_parser.cc"
    break;

  case 725: // $@113: %empty
#line 2531 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4030 "dhcp4_parser.cc"
    break;

  case 726: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2534 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4039 "dhcp4_parser.cc"
    break;

  case 727: // $@114: %empty
#line 2541 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4051 "dhcp4_parser.cc"
    break;

  case 728: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2547 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4062 "dhcp4_parser.cc"
    break;

  case 729: // $@115: %empty
#line 2554 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4072 "dhcp4_parser.cc"
    break;

  case 730: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2558 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4082 "dhcp4_parser.cc"
    break;

  case 733: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2566 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4090 "dhcp4_parser.cc"
    break;

  case 752: // enable_updates: "enable-updates" ":" "boolean"
#line 2591 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4100 "dhcp4_parser.cc"
    break;

  case 753: // $@116: %empty
#line 2597 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4109 "dhcp4_parser.cc"
    break;

  case 754: // server_ip: "server-ip" $@116 ":" "constant string"
#line 2600 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4119 "dhcp4_parser.cc"
    break;

  case 755: // server_port: "server-port" ":" "integer"
#line 2606 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4129 "dhcp4_parser.cc"
    break;

  case 756: // $@117: %empty
#line 2612 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4138 "dhcp4_parser.cc"
    break;

  case 757: // sender_ip: "sender-ip" $@117 ":" "constant string"
#line 2615 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4148 "dhcp4_parser.cc"
    break;

  case 758: // sender_port: "sender-port" ":" "integer"
#line 2621 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4158 "dhcp4_parser.cc"
    break;

  case 759: // max_queue_size: "max-queue-size" ":" "integer"
#line 2627 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4168 "dhcp4_parser.cc"
    break;

  case 760: // $@118: %empty
#line 2633 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4177 "dhcp4_parser.cc"
    break;

  case 761: // ncr_protocol: "ncr-protocol" $@118 ":" ncr_protocol_value
#line 2636 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4186 "dhcp4_parser.cc"
    break;

  case 762: // ncr_protocol_value: "udp"
#line 2642 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4192 "dhcp4_parser.cc"
    break;

  case 763: // ncr_protocol_value: "tcp"
#line 2643 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4198 "dhcp4_parser.cc"
    break;

  case 764: // $@119: %empty
#line 2646 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4207 "dhcp4_parser.cc"
    break;

  case 765: // ncr_format: "ncr-format" $@119 ":" "JSON"
#line 2649 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4217 "dhcp4_parser.cc"
    break;

  case 766: // $@120: %empty
#line 2656 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4226 "dhcp4_parser.cc"
    break;

  case 767: // dep_qualifying_suffix: "qualifying-suffix" $@120 ":" "constant string"
#line 2659 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4236 "dhcp4_parser.cc"
    break;

  case 768: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2666 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4246 "dhcp4_parser.cc"
    break;

  case 769: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2673 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4256 "dhcp4_parser.cc"
    break;

  case 770: // $@121: %empty
#line 2680 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4265 "dhcp4_parser.cc"
    break;

  case 771: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2683 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4274 "dhcp4_parser.cc"
    break;

  case 772: // $@122: %empty
#line 2689 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4283 "dhcp4_parser.cc"
    break;

  case 773: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2692 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4293 "dhcp4_parser.cc"
    break;

  case 774: // $@123: %empty
#line 2699 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4302 "dhcp4_parser.cc"
    break;

  case 775: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2702 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4312 "dhcp4_parser.cc"
    break;

  case 776: // $@124: %empty
#line 2709 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4321 "dhcp4_parser.cc"
    break;

  case 777: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2712 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4331 "dhcp4_parser.cc"
    break;

  case 778: // $@125: %empty
#line 2721 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4343 "dhcp4_parser.cc"
    break;

  case 779: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2727 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4353 "dhcp4_parser.cc"
    break;

  case 780: // $@126: %empty
#line 2733 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4363 "dhcp4_parser.cc"
    break;

  case 781: // sub_config_control: "{" $@126 config_control_params "}"
#line 2737 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4372 "dhcp4_parser.cc"
    break;

  case 784: // config_control_params: config_control_params ","
#line 2745 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4380 "dhcp4_parser.cc"
    break;

  case 787: // $@127: %empty
#line 2755 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4392 "dhcp4_parser.cc"
    break;

  case 788: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2761 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4401 "dhcp4_parser.cc"
    break;

  case 789: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2766 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4411 "dhcp4_parser.cc"
    break;

  case 790: // $@128: %empty
#line 2774 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4423 "dhcp4_parser.cc"
    break;

  case 791: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2780 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4432 "dhcp4_parser.cc"
    break;

  case 794: // loggers_entries: loggers_entries ","
#line 2789 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4440 "dhcp4_parser.cc"
    break;

  case 795: // $@129: %empty
#line 2795 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4450 "dhcp4_parser.cc"
    break;

  case 796: // logger_entry: "{" $@129 logger_params "}"
#line 2799 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4458 "dhcp4_parser.cc"
    break;

  case 799: // logger_params: logger_params ","
#line 2805 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4466 "dhcp4_parser.cc"
    break;

  case 807: // debuglevel: "debuglevel" ":" "integer"
#line 2819 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4476 "dhcp4_parser.cc"
    break;

  case 808: // $@130: %empty
#line 2825 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4485 "dhcp4_parser.cc"
    break;

  case 809: // severity: "severity" $@130 ":" "constant string"
#line 2828 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4495 "dhcp4_parser.cc"
    break;

  case 810: // $@131: %empty
#line 2834 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4507 "dhcp4_parser.cc"
    break;

  case 811: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2840 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4516 "dhcp4_parser.cc"
    break;

  case 814: // output_options_list_content: output_options_list_content ","
#line 2847 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4524 "dhcp4_parser.cc"
    break;

  case 815: // $@132: %empty
#line 2852 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4534 "dhcp4_parser.cc"
    break;

  case 816: // output_entry: "{" $@132 output_params_list "}"
#line 2856 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4542 "dhcp4_parser.cc"
    break;

  case 819: // output_params_list: output_params_list ","
#line 2862 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4550 "dhcp4_parser.cc"
    break;

  case 825: // $@133: %empty
#line 2874 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4559 "dhcp4_parser.cc"
    break;

  case 826: // output: "output" $@133 ":" "constant string"
#line 2877 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4569 "dhcp4_parser.cc"
    break;

  case 827: // flush: "flush" ":" "boolean"
#line 2883 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4579 "dhcp4_parser.cc"
    break;

  case 828: // maxsize: "maxsize" ":" "integer"
#line 2889 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4589 "dhcp4_parser.cc"
    break;

  case 829: // maxver: "maxver" ":" "integer"
#line 2895 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4599 "dhcp4_parser.cc"
    break;

  case 830: // $@134: %empty
#line 2901 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4608 "dhcp4_parser.cc"
    break;

  case 831: // pattern: "pattern" $@134 ":" "constant string"
#line 2904 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4618 "dhcp4_parser.cc"
    break;

  case 832: // $@135: %empty
#line 2910 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4630 "dhcp4_parser.cc"
    break;

  case 833: // compatibility: "compatibility" $@135 ":" "{" compatibility_params "}"
#line 2916 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4639 "dhcp4_parser.cc"
    break;

  case 836: // compatibility_params: compatibility_params ","
#line 2923 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4647 "dhcp4_parser.cc"
    break;

  case 841: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2934 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4657 "dhcp4_parser.cc"
    break;

  case 842: // ignore-rai-link-selection: "ignore-rai-link-selection" ":" "boolean"
#line 2940 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4667 "dhcp4_parser.cc"
    break;

  case 843: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 2946 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4677 "dhcp4_parser.cc"
    break;


#line 4681 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -992;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     219,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,    36,    42,    43,    64,   130,   133,
     136,   143,   156,   162,   178,   204,   245,   255,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,    42,  -177,    35,   122,   149,   257,
     191,   490,   -43,   172,   300,  -108,   648,   102,  -992,    56,
      61,    54,    77,    72,  -992,    34,  -992,  -992,  -992,  -992,
      92,   100,   265,  -992,  -992,  -992,  -992,  -992,  -992,   291,
     313,   315,   330,   340,   346,   354,   358,   367,   374,   387,
    -992,   399,   400,   406,   407,   409,  -992,  -992,  -992,   429,
     430,   437,  -992,  -992,  -992,   438,  -992,  -992,  -992,  -992,
    -992,   439,   440,   441,  -992,  -992,  -992,  -992,  -992,   442,
    -992,  -992,  -992,  -992,  -992,  -992,   446,   448,   449,  -992,
    -992,   451,  -992,    71,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,   454,   455,   456,   458,  -992,    74,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,   459,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,    78,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,    80,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   139,   290,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,   382,  -992,  -992,   462,  -992,  -992,  -992,   463,
    -992,  -992,   428,   379,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,   466,   467,   469,
    -992,  -992,  -992,  -992,   470,   471,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,    89,
    -992,  -992,  -992,   473,  -992,  -992,   476,  -992,   478,   481,
    -992,  -992,   482,   485,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,    91,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   488,
      97,  -992,  -992,  -992,  -992,    42,    42,  -992,  -138,   492,
    -992,  -992,   494,   496,   500,   295,   299,   301,   501,   503,
     512,   516,   522,   523,   318,   319,   320,   321,   325,   327,
     322,   329,   331,   333,   336,   539,   337,   341,   338,   342,
     343,   556,   557,   559,   350,   357,   364,   564,   575,   581,
     377,   582,   586,   588,   589,   591,   388,   389,   390,   592,
     596,   597,   601,   602,   395,   604,   605,   606,   607,   609,
     610,   401,   402,   403,   614,   621,  -992,   122,  -992,   623,
     624,   625,   416,   417,   420,   421,   149,  -992,   630,   631,
     632,   633,   634,   635,   431,   636,   637,   641,   257,  -992,
     643,   191,  -992,   644,   645,   646,   647,   649,   650,   652,
     653,  -992,   490,  -992,   654,   655,   434,   656,   657,   659,
     450,  -992,   172,   661,   452,   453,   457,  -992,   300,   664,
     665,    27,  -992,   464,   666,   673,   472,   679,   475,   477,
     681,   684,   479,   480,   686,   687,   688,   691,   648,  -992,
     692,   491,   102,  -992,  -992,  -992,   698,   697,   723,   724,
     725,  -992,  -992,  -992,   525,   526,   527,   726,   732,   700,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,   529,  -992,  -992,  -992,  -992,  -992,  -124,   530,   531,
    -992,  -992,  -992,   739,   740,   742,  -992,   532,   743,   745,
     538,    67,  -992,  -992,  -992,   749,   753,   754,   758,   757,
    -992,   759,   760,   761,   763,   560,   561,  -992,  -992,  -992,
     768,   767,  -992,   770,   231,   311,  -992,  -992,  -992,  -992,
    -992,   567,   568,   583,   790,   585,   593,  -992,   770,   594,
     795,  -992,   595,  -992,   770,   613,   615,   616,   619,   622,
     626,   627,  -992,   628,   629,  -992,   638,   639,   640,  -992,
    -992,   651,  -992,  -992,  -992,  -992,   658,   745,  -992,  -992,
     660,   662,  -992,   663,  -992,  -992,    38,   667,  -992,  -992,
    -124,   668,   669,   670,  -992,   798,  -992,  -992,    42,   122,
     102,   149,   218,  -992,  -992,  -992,   738,   738,   800,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   801,   818,
     825,  -992,   827,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,    86,   828,   829,   834,   166,    10,    68,    21,   648,
    -992,  -992,   836,  -127,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,   837,  -992,  -992,  -992,  -992,
     140,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   800,
    -992,   104,   138,   141,  -992,  -992,   167,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,   841,   842,   843,   844,   848,   850,
     851,   852,   853,   854,  -992,   856,  -992,  -992,  -992,  -992,
    -992,   216,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,   225,  -992,   855,   860,  -992,  -992,
     858,   862,  -992,  -992,   861,   863,  -992,  -992,   864,   865,
    -992,  -992,   866,   872,  -992,  -992,  -992,  -992,  -992,  -992,
      57,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   105,  -992,
    -992,   870,   874,  -992,  -992,   876,   875,  -992,   879,   880,
     881,   882,   883,   884,   226,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,   885,   886,   887,  -992,   256,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   258,  -992,
    -992,  -992,   888,  -992,   889,  -992,  -992,  -992,   289,  -992,
    -992,  -992,  -992,  -992,   293,  -992,   119,  -992,   890,   891,
     892,  -992,   312,  -992,  -992,  -992,  -992,   689,  -992,   893,
     894,  -992,  -992,  -992,  -992,   895,   896,  -992,  -992,  -992,
     897,   900,   218,  -992,   901,   902,   903,   904,   699,   695,
     701,   696,   702,   703,   704,   705,   706,   707,   908,   708,
     917,   918,   919,   920,   738,  -992,  -992,   738,  -992,   800,
     257,  -992,   801,   172,  -992,   818,   300,  -992,   825,   642,
    -992,   827,    86,  -992,   323,   828,  -992,   490,  -992,   829,
    -108,  -992,   834,   713,   714,   715,   716,   717,   718,   166,
    -992,   720,   719,   728,    10,  -992,   928,   931,    68,  -992,
     727,   933,   744,   934,    21,  -992,  -992,   386,   836,  -992,
     748,   764,   769,  -127,  -992,  -992,   953,   960,   191,  -992,
     837,   968,  -992,  -992,   766,   771,  -992,   197,   783,   789,
     804,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,   228,  -992,   808,   812,   815,   819,  -992,   356,  -992,
     371,  -992,   966,  -992,   973,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
     378,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  1041,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  1069,  1077,  -992,  -992,
    -992,  -992,  -992,  -992,  1073,  -992,   397,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   873,
     877,  -992,  -992,   878,  -992,    42,  -992,  -992,  1082,  -992,
    -992,  -992,  -992,  -992,   398,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,   898,   404,  -992,   770,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
     642,  -992,  1083,  1086,   899,  -992,   323,  -992,  -992,  -992,
    -992,  -992,  -992,  1087,   905,  1088,   386,  -992,  -992,  -992,
    -992,  -992,   907,   909,  -992,  -992,  1089,  -992,   910,  -992,
    -992,  -992,  1090,  -992,  -992,   120,  -992,   161,  1090,  -992,
    -992,  1091,  1092,  1094,  -992,   432,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  1095,   911,   912,   914,  1096,   161,  -992,
     916,  -992,  -992,  -992,   922,  -992,  -992,  -992
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   195,     9,   373,    11,   585,    13,
     612,    15,   503,    17,   512,    19,   551,    21,   335,    23,
     729,    25,   780,    27,    46,    39,     0,     0,     0,     0,
       0,   614,     0,   514,   553,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   778,   180,   213,
       0,     0,     0,   634,   636,   638,   211,   224,   226,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     146,     0,     0,     0,     0,     0,   157,   164,   166,     0,
       0,     0,   364,   501,   542,     0,   149,   448,   599,   601,
     441,     0,     0,     0,   297,   662,   603,   326,   347,     0,
     312,   696,   710,   727,   170,   172,     0,     0,     0,   790,
     832,     0,   134,     0,    67,    70,    71,    72,    73,    74,
     108,   109,   110,   111,   112,    75,   103,   132,   133,    92,
      93,    94,   116,   117,   118,   119,   120,   121,   122,   123,
     114,   115,   124,   125,   126,   128,   129,   130,    78,    79,
     100,    80,    81,    82,   127,    86,    87,    76,   105,   106,
     107,   104,    77,    84,    85,    98,    99,   101,    95,    96,
      97,    83,    88,    89,    90,    91,   102,   113,   131,   197,
     199,   203,     0,     0,     0,     0,   194,     0,   182,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   426,   428,
     430,   576,   424,   432,     0,   436,   434,   658,   423,   378,
     379,   380,   381,   382,   406,   407,   408,   409,   410,   422,
     396,   397,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   420,   421,     0,   375,   385,   401,   402,   403,   386,
     388,   389,   392,   393,   394,   391,   387,   383,   384,   404,
     405,   390,   398,   399,   400,   395,   597,   596,   592,   593,
     591,     0,   587,   590,   594,   595,   656,   644,   646,   650,
     648,   654,   652,   640,   633,   627,   631,   632,     0,   615,
     616,   628,   629,   630,   624,   619,   625,   621,   622,   623,
     626,   620,     0,   532,   272,     0,   536,   534,   539,     0,
     528,   529,     0,   515,   516,   519,   531,   520,   521,   522,
     538,   523,   524,   525,   526,   527,   569,     0,     0,     0,
     567,   568,   571,   572,     0,   554,   555,   558,   559,   560,
     561,   562,   563,   564,   565,   566,   343,   345,   340,     0,
     337,   341,   342,     0,   766,   753,     0,   756,     0,     0,
     760,   764,     0,     0,   770,   772,   774,   776,   751,   749,
     750,     0,   731,   734,   735,   736,   737,   738,   739,   740,
     741,   746,   742,   743,   744,   745,   747,   748,   787,     0,
       0,   782,   785,   786,    45,    50,     0,    37,    43,     0,
      64,    60,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    69,    66,     0,
       0,     0,     0,     0,     0,     0,   184,   196,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   377,   374,
       0,   589,   586,     0,     0,     0,     0,     0,     0,     0,
       0,   613,   618,   504,     0,     0,     0,     0,     0,     0,
       0,   513,   518,     0,     0,     0,     0,   552,   557,     0,
       0,   339,   336,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   733,   730,
       0,     0,   784,   781,    49,    41,     0,     0,     0,     0,
       0,   151,   152,   153,     0,     0,     0,     0,     0,     0,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,     0,   175,   176,   154,   155,   156,     0,     0,     0,
     168,   169,   174,     0,     0,     0,   148,     0,     0,     0,
       0,     0,   438,   439,   440,     0,     0,     0,     0,     0,
     695,     0,     0,     0,     0,     0,     0,   177,   178,   179,
       0,     0,    68,     0,     0,     0,   207,   208,   209,   210,
     183,     0,     0,     0,     0,     0,     0,   447,     0,     0,
       0,   376,     0,   588,     0,     0,     0,     0,     0,     0,
       0,     0,   617,     0,     0,   530,     0,     0,     0,   541,
     517,     0,   573,   574,   575,   556,     0,     0,   338,   752,
       0,     0,   755,     0,   758,   759,     0,     0,   768,   769,
       0,     0,     0,     0,   732,     0,   789,   783,     0,     0,
       0,     0,     0,   635,   637,   639,     0,     0,   228,   147,
     159,   160,   161,   162,   163,   158,   165,   167,   366,   505,
     544,   150,   450,    38,   600,   602,   443,   444,   445,   446,
     442,     0,     0,   605,   328,     0,     0,     0,     0,     0,
     171,   173,     0,     0,    51,   198,   201,   202,   200,   205,
     206,   204,   427,   429,   431,   578,   425,   433,   437,   435,
       0,   598,   657,   645,   647,   651,   649,   655,   653,   641,
     533,   273,   537,   535,   540,   570,   344,   346,   767,   754,
     757,   762,   763,   761,   765,   771,   773,   775,   777,   228,
      42,     0,     0,     0,   220,   222,     0,   215,   218,   219,
     260,   265,   267,   269,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   283,     0,   289,   291,   293,   295,
     259,     0,   235,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,     0,   233,     0,   229,   230,   371,
       0,   367,   368,   510,     0,   506,   507,   549,     0,   545,
     546,   455,     0,   451,   452,   307,   308,   309,   310,   311,
       0,   299,   302,   303,   304,   305,   306,   667,     0,   664,
     610,     0,   606,   607,   333,     0,   329,   330,     0,     0,
       0,     0,     0,     0,     0,   349,   352,   353,   354,   355,
     356,   357,     0,     0,     0,   322,     0,   314,   317,   318,
     319,   320,   321,   706,   708,   705,   703,   704,     0,   698,
     701,   702,     0,   722,     0,   725,   718,   719,     0,   712,
     715,   716,   717,   720,     0,   795,     0,   792,     0,     0,
       0,   840,     0,   834,   837,   838,   839,    53,   583,     0,
     579,   580,   642,   660,   661,     0,     0,    62,   779,   181,
       0,     0,   217,   214,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   237,   212,   225,     0,   227,   232,
       0,   365,   370,   514,   502,   509,   553,   543,   548,     0,
     449,   454,   301,   298,   669,   666,   663,   614,   604,   609,
       0,   327,   332,     0,     0,     0,     0,     0,     0,   351,
     348,     0,     0,     0,   316,   313,     0,     0,   700,   697,
       0,     0,     0,     0,   714,   711,   728,     0,   794,   791,
       0,     0,     0,   836,   833,    55,     0,    54,     0,   577,
     582,     0,   659,   788,     0,     0,   216,     0,     0,     0,
       0,   271,   274,   275,   276,   277,   278,   279,   280,   281,
     282,     0,   288,     0,     0,     0,     0,   236,     0,   231,
       0,   369,     0,   508,     0,   547,   500,   478,   479,   480,
     463,   464,   483,   484,   485,   486,   487,   499,   466,   467,
     488,   489,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   460,   461,   462,   476,   477,   473,   474,   475,   472,
       0,   457,   465,   481,   482,   468,   469,   470,   471,   453,
     300,   690,   692,     0,   685,   686,   687,   688,   689,   678,
     679,   683,   684,   680,   681,   682,     0,   670,   671,   674,
     675,   676,   677,   665,     0,   608,     0,   331,   358,   359,
     360,   361,   362,   363,   350,   323,   324,   325,   315,     0,
       0,   699,   721,     0,   724,     0,   713,   810,     0,   808,
     806,   800,   804,   805,     0,   797,   802,   803,   801,   793,
     841,   842,   843,   835,    52,    57,     0,   581,     0,   221,
     223,   262,   263,   264,   261,   266,   268,   270,   285,   286,
     287,   284,   290,   292,   294,   296,   234,   372,   511,   550,
     459,   456,     0,     0,     0,   668,   673,   611,   334,   707,
     709,   723,   726,     0,     0,     0,   799,   796,    56,   584,
     643,   458,     0,     0,   694,   672,     0,   807,     0,   798,
     691,   693,     0,   809,   815,     0,   812,     0,   814,   811,
     825,     0,     0,     0,   830,     0,   817,   820,   821,   822,
     823,   824,   813,     0,     0,     0,     0,     0,   819,   816,
       0,   827,   828,   829,     0,   818,   826,   831
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,   -53,  -992,  -586,  -992,   -35,
    -992,  -992,  -992,  -992,  -992,  -992,  -641,  -992,  -992,  -992,
     -67,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   189,   608,
      -8,    11,    29,   -54,   -34,   -12,   -10,     3,    33,    37,
    -992,  -992,  -992,  -992,    40,  -992,  -992,    41,    44,    47,
      48,    51,    52,  -992,   393,    55,  -992,    58,  -992,    59,
      62,    63,  -992,    65,  -992,    66,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,   391,   598,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,   129,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,   304,  -992,   107,  -992,  -703,   113,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   -45,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,    96,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,    81,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,    88,  -992,  -992,  -992,    94,   565,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,    82,  -992,  -992,  -992,  -992,
    -992,  -992,  -991,  -992,  -992,  -992,   110,  -992,  -992,  -992,
     123,   611,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -983,  -992,   -65,  -992,    25,  -992,    69,    70,    73,    76,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,   108,  -992,  -992,
    -102,   -62,  -992,  -992,  -992,  -992,  -992,   117,  -992,  -992,
    -992,   127,  -992,   599,  -992,   -61,  -992,  -992,  -992,  -992,
    -992,   -58,  -992,  -992,  -992,  -992,  -992,    -4,  -992,  -992,
    -992,   126,  -992,  -992,  -992,   125,  -992,   587,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
      79,  -992,  -992,  -992,    84,   617,  -992,  -992,   -49,  -992,
     -30,  -992,   -57,  -992,  -992,  -992,   118,  -992,  -992,  -992,
     128,  -992,   612,     7,  -992,    18,  -992,    22,  -992,   366,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -979,  -992,  -992,
    -992,  -992,  -992,   131,  -992,  -992,  -992,   -96,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   109,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,    99,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,   405,   580,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,   443,   577,
    -992,  -992,  -992,  -992,  -992,  -992,   103,  -992,  -992,   -94,
    -992,  -992,  -992,  -992,  -992,  -992,  -118,  -992,  -992,  -133,
    -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,  -992,
     106,  -992,  -992,  -992
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   734,
      82,    83,    39,    64,    79,    80,   755,   957,  1056,  1057,
     830,    41,    66,    85,   429,    86,    43,    67,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   455,   167,   168,   471,   169,   170,   171,   172,
     173,   174,   175,   461,   725,   176,   462,   177,   463,   178,
     179,   180,   489,   181,   490,   182,   183,   184,   185,   186,
     187,   188,   433,   227,   228,    45,    68,   229,   499,   230,
     500,   758,   231,   501,   761,   232,   233,   234,   235,   189,
     441,   190,   434,   806,   807,   808,   970,   809,   971,   191,
     442,   192,   443,   856,   857,   858,   997,   831,   832,   833,
     974,  1214,   834,   975,   835,   976,   836,   977,   837,   838,
     535,   839,   840,   841,   842,   843,   844,   845,   846,   847,
     848,   988,  1221,   849,   850,   990,   851,   991,   852,   992,
     853,   993,   193,   479,   880,   881,   882,   883,   884,   885,
     886,   194,   485,   916,   917,   918,   919,   920,   195,   482,
     895,   896,   897,  1020,    59,    75,   379,   380,   381,   549,
     382,   550,   196,   483,   904,   905,   906,   907,   908,   909,
     910,   911,   197,   467,   860,   861,   862,  1000,    47,    69,
     273,   274,   275,   512,   276,   508,   277,   509,   278,   510,
     279,   513,   280,   516,   281,   515,   198,   199,   200,   201,
     475,   740,   286,   202,   472,   872,   873,   874,  1009,  1130,
    1131,   203,   468,    53,    72,   864,   865,   866,  1003,    55,
      73,   342,   343,   344,   345,   346,   347,   348,   534,   349,
     538,   350,   537,   351,   352,   539,   353,   204,   469,   868,
     869,   870,  1006,    57,    74,   364,   365,   366,   367,   368,
     543,   369,   370,   371,   372,   373,   288,   511,   959,   960,
     961,  1058,    49,    70,   301,   302,   303,   520,   205,   473,
     206,   474,   207,   481,   891,   892,   893,  1017,    51,    71,
     318,   319,   320,   208,   438,   209,   439,   210,   440,   324,
     530,   964,  1061,   325,   524,   326,   525,   327,   527,   328,
     526,   329,   529,   330,   528,   331,   523,   295,   517,   965,
     211,   480,   888,   889,  1014,  1156,  1157,  1158,  1159,  1160,
    1232,  1161,  1233,  1162,   212,   213,   486,   928,   929,   930,
    1036,   931,  1037,   214,   487,   938,   939,   940,   941,  1041,
     942,   943,  1043,   215,   488,    61,    76,   401,   402,   403,
     404,   555,   405,   406,   557,   407,   408,   409,   560,   793,
     410,   561,   411,   554,   412,   413,   414,   564,   415,   565,
     416,   566,   417,   567,   216,   432,    63,    77,   420,   421,
     422,   570,   423,   217,   494,   946,   947,  1047,  1194,  1195,
    1196,  1197,  1245,  1198,  1243,  1265,  1266,  1267,  1275,  1276,
    1277,  1283,  1278,  1279,  1280,  1281,  1287,   218,   495,   952,
     953,   954,   955,   956
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     152,   226,   248,   297,   314,   298,   340,   360,   378,   398,
     332,    78,   291,   362,   854,   252,   363,   768,  1122,   236,
     289,   304,   316,   772,   354,   374,  1123,   399,   341,   361,
    1138,   376,   377,   733,    81,   253,    28,   430,   237,   290,
     305,   317,   431,   355,   375,    84,   400,    29,   123,    30,
      40,    31,   720,   721,   722,   723,   791,   254,   426,   255,
    1012,   249,   424,  1013,   425,   287,   300,   315,   948,   949,
     950,    42,   256,   576,   497,   428,   292,   506,   321,   498,
     250,   518,   507,   521,   151,   427,   519,   293,   522,   322,
     724,   294,   551,   323,   568,   299,   435,   552,   251,   569,
     572,   733,   257,   151,   436,   573,   258,   497,  1015,   259,
     260,  1016,   967,   261,   418,   419,   262,   263,   128,   129,
     264,   265,  1048,  1268,   266,  1049,  1269,   267,   268,   128,
     129,   269,   270,    87,   271,   272,    88,    44,   282,   283,
      46,   572,   284,    48,   506,   285,   968,   531,    89,   969,
      50,    90,    91,    92,    93,    94,    95,    96,    97,    98,
     912,   913,   914,    52,   219,   220,   376,   377,   221,    54,
     972,   222,   223,   224,   225,   973,   128,   129,   932,   933,
     934,   736,   737,   738,   739,    56,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     333,    58,   792,   123,   124,   875,   876,   877,   878,   994,
     879,   151,   923,   924,   995,   125,   126,   127,   994,  1029,
     128,   129,   935,   996,  1030,   130,  1211,  1212,  1213,  1122,
     131,   132,   133,   134,   135,   804,   805,  1123,   756,   757,
     136,  1138,    60,    32,    33,    34,    35,   128,   129,  1034,
     137,  1038,    62,   138,  1035,   334,  1039,   335,   336,   437,
     139,   140,   337,   338,   339,   141,   313,   962,   142,   151,
     128,   129,   143,   124,  1218,  1219,  1220,    91,    92,    93,
      94,    95,  1044,   532,  1088,   444,   568,  1045,   296,   128,
     129,  1046,   144,   145,   146,   147,   148,   149,   898,   899,
     900,   901,   902,   903,   245,  1053,   150,   445,   246,   446,
    1054,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   759,   760,   151,   447,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   448,   238,   239,   240,  1270,   124,
     449,  1271,  1272,  1273,  1274,    93,    94,    95,   450,   994,
     151,   126,   451,   241,  1226,   128,   129,   242,   243,   244,
     130,   452,   574,   575,   518,   131,   132,   133,   453,  1227,
     245,  1230,   542,   151,   246,   136,  1231,    99,   100,   101,
     533,   454,   247,   334,   356,   335,   336,   357,   358,   359,
     551,  1246,   151,   456,   457,  1238,  1247,   521,   128,   129,
     458,   459,  1249,   460,   123,   124,   334,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     152,   128,   129,   464,   465,  1288,   541,   144,   145,   226,
    1289,   466,   470,   476,   477,   478,   484,  1141,  1142,  1143,
     491,   248,   492,   493,   297,   496,   298,   236,   502,   503,
     504,   291,   505,   514,   252,   314,   536,   540,   151,   289,
     544,   545,   304,   546,   548,   340,   237,   553,   547,   334,
     556,   360,   558,   316,   253,   559,   562,   362,   290,   563,
     363,   305,   571,   354,   128,   129,   577,   341,   578,   374,
     579,   398,   317,   361,   580,   584,   254,   585,   255,   581,
     249,   151,   355,   582,   287,   583,   586,   300,   375,   399,
     587,   256,    93,    94,    95,   292,   588,   589,   315,   250,
     590,   591,   592,   593,   151,   596,   293,   594,   400,   321,
     294,   595,   597,   601,   598,   599,   299,   251,   600,   602,
     322,   257,   604,   603,   323,   258,   605,   606,   259,   260,
     607,   608,   261,   609,   610,   262,   263,  1250,   613,   264,
     265,   611,  1187,   266,  1188,  1189,   267,   268,   612,   614,
     269,   270,   124,   271,   272,   615,   617,   282,   283,   616,
     618,   284,   619,   620,   285,   621,   625,   151,   128,   129,
     626,   627,   622,   623,   624,   628,   629,   630,   631,   632,
     633,   634,   306,   635,   636,   637,   638,   639,   640,   307,
     308,   309,   310,   311,   312,   641,   313,   643,   644,   645,
     646,   647,   648,   649,   651,   652,   653,   654,   655,   656,
     658,   659,   152,   657,   226,   660,   675,   662,   664,   665,
     666,   667,   787,   668,   669,   800,   670,   671,   673,   674,
     676,   677,   236,   678,   679,   681,   682,   683,   686,   687,
     690,   684,    91,    92,    93,    94,    95,   691,   689,   915,
     925,   237,   398,   693,   692,   696,   951,   694,   697,   695,
     700,   701,   702,   698,   699,   703,   705,   921,   926,   936,
     399,   151,   708,   706,   709,   718,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   922,   927,   937,   400,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     710,   711,   712,   716,   124,   334,   713,   714,   715,   717,
     719,   726,   727,   731,   728,   729,   126,   730,   732,   735,
     128,   129,    30,   243,   741,   130,   128,   129,   742,   743,
     131,   132,   133,   744,   745,   245,   746,   747,   748,   246,
     749,   750,   751,   752,   753,   754,   810,   247,   762,   763,
     811,   812,   813,   814,   815,   816,   817,   818,   819,   820,
     821,   822,   823,   824,   764,   765,   766,   825,   826,   827,
     828,   829,   770,   799,   767,   769,   771,   855,   859,   383,
     384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   144,   145,   773,   863,   774,   775,   396,   397,
     776,   334,   867,   777,   871,   887,   890,   778,   779,   780,
     781,   894,   794,   945,   958,   978,   979,   980,   981,   782,
     783,   784,   982,   151,   983,   984,   985,   986,   987,   151,
     989,   998,   785,   999,  1001,  1002,  1005,  1004,  1008,   786,
    1007,   788,  1010,   789,   790,  1011,  1018,  1019,  1022,   796,
     797,   798,  1021,  1023,  1024,  1025,  1026,  1027,  1028,  1031,
    1032,  1033,  1040,  1042,  1050,  1051,  1052,  1060,   801,  1059,
    1055,  1064,  1063,  1062,  1065,  1067,  1068,  1069,  1070,  1072,
    1074,  1071,  1081,  1073,  1075,  1076,  1077,  1078,  1079,  1080,
    1082,  1083,  1084,  1085,  1086,  1168,  1169,  1170,  1171,  1172,
    1173,  1176,  1179,   248,  1175,  1180,   340,  1183,  1185,   360,
    1177,  1182,  1096,   291,  1124,   362,   252,  1144,   363,   151,
     314,   289,  1149,   378,   354,  1100,  1184,   374,   341,  1204,
    1133,   361,  1200,  1205,  1121,  1151,   253,   915,   316,  1148,
     290,   925,  1208,   355,  1228,  1101,   375,  1209,  1201,  1134,
    1190,  1229,  1210,  1202,  1152,   921,   951,   317,   254,   926,
     255,   297,   249,   298,  1215,   936,   287,  1102,  1192,  1103,
    1216,  1097,  1191,   256,   922,  1132,  1145,   292,   927,   304,
    1150,   250,  1104,   315,   937,  1217,  1135,  1193,   293,  1222,
    1098,  1153,   294,  1223,   321,  1146,  1224,  1136,   305,   251,
    1225,  1137,  1154,   257,  1125,   322,  1155,   258,  1099,   323,
     259,   260,  1105,  1147,   261,  1234,  1106,   262,   263,  1107,
    1108,   264,   265,  1109,   300,   266,  1110,  1111,   267,   268,
    1112,  1113,   269,   270,  1114,   271,   272,  1115,  1116,   282,
     283,  1117,  1118,   284,  1119,  1120,   285,  1235,  1126,  1127,
    1236,  1237,  1128,   299,  1239,  1129,  1244,  1252,  1240,  1241,
    1253,  1256,  1258,   795,  1262,  1284,  1285,  1264,  1286,  1290,
    1294,  1066,   803,   966,   650,   642,  1089,  1087,  1140,  1248,
    1167,  1174,  1091,  1254,  1166,  1178,   688,  1257,  1260,  1139,
    1261,  1263,  1093,  1090,  1292,  1291,  1293,  1296,  1251,   661,
    1092,  1094,  1242,  1297,  1095,   685,   963,  1165,   663,  1207,
    1255,   680,  1206,  1186,   672,  1164,  1163,  1181,   704,   707,
    1282,  1199,  1259,   802,   944,  1295,     0,     0,     0,  1203,
       0,     0,     0,  1096,     0,  1124,     0,     0,     0,  1144,
       0,     0,     0,     0,  1149,     0,  1100,     0,     0,  1190,
       0,  1133,     0,     0,     0,  1121,     0,  1151,     0,     0,
       0,  1148,     0,     0,     0,     0,  1101,  1192,     0,     0,
    1134,  1191,     0,     0,     0,     0,  1152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1193,     0,  1102,     0,
    1103,     0,  1097,     0,     0,     0,  1132,     0,  1145,     0,
       0,     0,  1150,  1104,     0,     0,     0,  1135,     0,     0,
       0,  1098,     0,  1153,     0,     0,     0,  1146,  1136,     0,
       0,     0,  1137,     0,  1154,  1125,     0,     0,  1155,  1099,
       0,     0,     0,  1105,     0,  1147,     0,  1106,     0,     0,
    1107,  1108,     0,     0,  1109,     0,     0,  1110,  1111,     0,
       0,  1112,  1113,     0,     0,  1114,     0,     0,  1115,  1116,
       0,     0,  1117,  1118,     0,  1119,  1120,     0,     0,  1126,
    1127,     0,     0,  1128,     0,     0,  1129
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      72,    64,    69,    74,   717,    69,    74,   658,  1009,    68,
      69,    70,    71,   664,    73,    74,  1009,    76,    73,    74,
    1009,   139,   140,   619,   211,    69,     0,     3,    68,    69,
      70,    71,     8,    73,    74,    10,    76,     5,    91,     7,
       7,     9,   176,   177,   178,   179,    18,    69,     4,    69,
       3,    69,     6,     6,     3,    69,    70,    71,   195,   196,
     197,     7,    69,   211,     3,     3,    69,     3,    71,     8,
      69,     3,     8,     3,   211,     8,     8,    69,     8,    71,
     214,    69,     3,    71,     3,    70,     4,     8,    69,     8,
       3,   687,    69,   211,     4,     8,    69,     3,     3,    69,
      69,     6,     8,    69,    12,    13,    69,    69,   108,   109,
      69,    69,     3,     3,    69,     6,     6,    69,    69,   108,
     109,    69,    69,    11,    69,    69,    14,     7,    69,    69,
       7,     3,    69,     7,     3,    69,     8,     8,    26,     8,
       7,    29,    30,    31,    32,    33,    34,    35,    36,    37,
     150,   151,   152,     7,    15,    16,   139,   140,    19,     7,
       3,    22,    23,    24,    25,     8,   108,   109,   157,   158,
     159,   114,   115,   116,   117,     7,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      38,     7,   174,    91,    92,   129,   130,   131,   132,     3,
     134,   211,   154,   155,     8,   103,   104,   105,     3,     3,
     108,   109,   211,     8,     8,   113,    39,    40,    41,  1230,
     118,   119,   120,   121,   122,    27,    28,  1230,    17,    18,
     128,  1230,     7,   211,   212,   213,   214,   108,   109,     3,
     138,     3,     7,   141,     8,    93,     8,    95,    96,     4,
     148,   149,   100,   101,   102,   153,   136,   137,   156,   211,
     108,   109,   160,    92,    56,    57,    58,    30,    31,    32,
      33,    34,     3,     3,   997,     4,     3,     8,   107,   108,
     109,     8,   180,   181,   182,   183,   184,   185,   142,   143,
     144,   145,   146,   147,   123,     3,   194,     4,   127,     4,
       8,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    20,    21,   211,     4,    78,    79,    80,    81,    82,
      83,    84,    85,    86,     4,    88,    89,    90,   187,    92,
       4,   190,   191,   192,   193,    32,    33,    34,     4,     3,
     211,   104,     4,   106,     8,   108,   109,   110,   111,   112,
     113,     4,   425,   426,     3,   118,   119,   120,     4,     8,
     123,     3,     3,   211,   127,   128,     8,    64,    65,    66,
       8,     4,   135,    93,    94,    95,    96,    97,    98,    99,
       3,     3,   211,     4,     4,     8,     8,     3,   108,   109,
       4,     4,     8,     4,    91,    92,    93,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     497,   108,   109,     4,     4,     3,     8,   180,   181,   506,
       8,     4,     4,     4,     4,     4,     4,   124,   125,   126,
       4,   518,     4,     4,   521,     4,   521,   506,     4,     4,
       4,   518,     4,     4,   518,   532,     4,     4,   211,   518,
       4,     4,   521,     4,     3,   542,   506,     4,     8,    93,
       4,   548,     4,   532,   518,     4,     4,   548,   518,     4,
     548,   521,     4,   542,   108,   109,     4,   542,     4,   548,
       4,   568,   532,   548,     4,     4,   518,     4,   518,   214,
     518,   211,   542,   214,   518,   214,     4,   521,   548,   568,
       4,   518,    32,    33,    34,   518,     4,     4,   532,   518,
     212,   212,   212,   212,   211,   213,   518,   212,   568,   532,
     518,   214,   213,     4,   213,   212,   521,   518,   212,   212,
     532,   518,   214,   212,   532,   518,   214,   214,   518,   518,
       4,     4,   518,     4,   214,   518,   518,  1208,     4,   518,
     518,   214,   186,   518,   188,   189,   518,   518,   214,     4,
     518,   518,    92,   518,   518,     4,     4,   518,   518,   212,
       4,   518,     4,     4,   518,     4,     4,   211,   108,   109,
       4,     4,   214,   214,   214,     4,     4,   212,     4,     4,
       4,     4,   122,     4,     4,   214,   214,   214,     4,   129,
     130,   131,   132,   133,   134,     4,   136,     4,     4,     4,
     214,   214,   212,   212,     4,     4,     4,     4,     4,     4,
       4,     4,   709,   212,   711,     4,   212,     4,     4,     4,
       4,     4,   687,     4,     4,   708,     4,     4,     4,     4,
       4,     4,   711,     4,   214,     4,   214,   214,     4,     4,
       4,   214,    30,    31,    32,    33,    34,     4,   214,   746,
     747,   711,   749,     4,   212,     4,   753,   212,     4,   212,
       4,     4,     4,   214,   214,     4,     4,   746,   747,   748,
     749,   211,     4,   212,     7,     5,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,   746,   747,   748,   749,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
       7,     7,     7,     7,    92,    93,   211,   211,   211,     7,
     211,   211,   211,   211,     5,     5,   104,     5,     5,   211,
     108,   109,     7,   111,     5,   113,   108,   109,     5,     5,
     118,   119,   120,     5,     7,   123,     7,     7,     7,   127,
       7,   211,   211,     5,     7,     5,    38,   135,   211,   211,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,   211,     5,   211,    59,    60,    61,
      62,    63,     7,     5,   211,   211,   211,     7,     7,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   180,   181,   211,     7,   211,   211,   180,   181,
     211,    93,     7,   211,     7,     7,     7,   211,   211,   211,
     211,     7,   175,     7,     7,     4,     4,     4,     4,   211,
     211,   211,     4,   211,     4,     4,     4,     4,     4,   211,
       4,     6,   211,     3,     6,     3,     3,     6,     3,   211,
       6,   211,     6,   211,   211,     3,     6,     3,     3,   211,
     211,   211,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   709,     6,
     211,     4,     6,     8,     4,     4,     4,     4,     4,   214,
     214,   212,     4,   212,   212,   212,   212,   212,   212,   212,
     212,     4,     4,     4,     4,   212,   212,   212,   212,   212,
     212,   212,     4,  1000,   214,     4,  1003,     4,     4,  1006,
     212,   214,  1009,  1000,  1009,  1006,  1000,  1014,  1006,   211,
    1017,  1000,  1014,  1020,  1003,  1009,   212,  1006,  1003,     6,
    1009,  1006,   214,     3,  1009,  1014,  1000,  1034,  1017,  1014,
    1000,  1038,     4,  1003,     8,  1009,  1006,   211,   214,  1009,
    1047,     8,   211,   214,  1014,  1034,  1053,  1017,  1000,  1038,
    1000,  1058,  1000,  1058,   211,  1044,  1000,  1009,  1047,  1009,
     211,  1009,  1047,  1000,  1034,  1009,  1014,  1000,  1038,  1058,
    1014,  1000,  1009,  1017,  1044,   211,  1009,  1047,  1000,   211,
    1009,  1014,  1000,   211,  1017,  1014,   211,  1009,  1058,  1000,
     211,  1009,  1014,  1000,  1009,  1017,  1014,  1000,  1009,  1017,
    1000,  1000,  1009,  1014,  1000,     4,  1009,  1000,  1000,  1009,
    1009,  1000,  1000,  1009,  1058,  1000,  1009,  1009,  1000,  1000,
    1009,  1009,  1000,  1000,  1009,  1000,  1000,  1009,  1009,  1000,
    1000,  1009,  1009,  1000,  1009,  1009,  1000,     8,  1009,  1009,
       3,     8,  1009,  1058,   211,  1009,     4,     4,   211,   211,
       4,     4,     4,   700,     5,     4,     4,     7,     4,     4,
       4,   972,   711,   799,   506,   497,   999,   994,  1012,   211,
    1022,  1029,  1002,   214,  1020,  1034,   551,   212,   211,  1011,
     211,   211,  1005,  1000,   212,   214,   212,   211,  1230,   518,
    1003,  1006,  1185,   211,  1008,   548,   770,  1019,   521,  1060,
    1236,   542,  1058,  1044,   532,  1017,  1015,  1038,   568,   572,
    1268,  1048,  1246,   710,   749,  1288,    -1,    -1,    -1,  1053,
      -1,    -1,    -1,  1230,    -1,  1230,    -1,    -1,    -1,  1236,
      -1,    -1,    -1,    -1,  1236,    -1,  1230,    -1,    -1,  1246,
      -1,  1230,    -1,    -1,    -1,  1230,    -1,  1236,    -1,    -1,
      -1,  1236,    -1,    -1,    -1,    -1,  1230,  1246,    -1,    -1,
    1230,  1246,    -1,    -1,    -1,    -1,  1236,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1246,    -1,  1230,    -1,
    1230,    -1,  1230,    -1,    -1,    -1,  1230,    -1,  1236,    -1,
      -1,    -1,  1236,  1230,    -1,    -1,    -1,  1230,    -1,    -1,
      -1,  1230,    -1,  1236,    -1,    -1,    -1,  1236,  1230,    -1,
      -1,    -1,  1230,    -1,  1236,  1230,    -1,    -1,  1236,  1230,
      -1,    -1,    -1,  1230,    -1,  1236,    -1,  1230,    -1,    -1,
    1230,  1230,    -1,    -1,  1230,    -1,    -1,  1230,  1230,    -1,
      -1,  1230,  1230,    -1,    -1,  1230,    -1,    -1,  1230,  1230,
      -1,    -1,  1230,  1230,    -1,  1230,  1230,    -1,    -1,  1230,
    1230,    -1,    -1,  1230,    -1,    -1,  1230
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,     0,     5,
       7,     9,   211,   212,   213,   214,   230,   231,   232,   237,
       7,   246,     7,   251,     7,   300,     7,   413,     7,   497,
       7,   513,     7,   448,     7,   454,     7,   478,     7,   389,
       7,   580,     7,   611,   238,   233,   247,   252,   301,   414,
     498,   514,   449,   455,   479,   390,   581,   612,   230,   239,
     240,   211,   235,   236,    10,   248,   250,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    91,    92,   103,   104,   105,   108,   109,
     113,   118,   119,   120,   121,   122,   128,   138,   141,   148,
     149,   153,   156,   160,   180,   181,   182,   183,   184,   185,
     194,   211,   245,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   268,   269,   271,
     272,   273,   274,   275,   276,   277,   280,   282,   284,   285,
     286,   288,   290,   291,   292,   293,   294,   295,   296,   314,
     316,   324,   326,   367,   376,   383,   397,   407,   431,   432,
     433,   434,   438,   446,   472,   503,   505,   507,   518,   520,
     522,   545,   559,   560,   568,   578,   609,   618,   642,    15,
      16,    19,    22,    23,    24,    25,   245,   298,   299,   302,
     304,   307,   310,   311,   312,   313,   503,   505,    88,    89,
      90,   106,   110,   111,   112,   123,   127,   135,   245,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   269,
     272,   273,   274,   275,   276,   277,   280,   282,   284,   285,
     286,   288,   290,   415,   416,   417,   419,   421,   423,   425,
     427,   429,   431,   432,   433,   434,   437,   472,   491,   503,
     505,   507,   518,   520,   522,   542,   107,   245,   427,   429,
     472,   499,   500,   501,   503,   505,   122,   129,   130,   131,
     132,   133,   134,   136,   245,   472,   503,   505,   515,   516,
     517,   518,   520,   522,   524,   528,   530,   532,   534,   536,
     538,   540,   446,    38,    93,    95,    96,   100,   101,   102,
     245,   344,   456,   457,   458,   459,   460,   461,   462,   464,
     466,   468,   469,   471,   503,   505,    94,    97,    98,    99,
     245,   344,   460,   466,   480,   481,   482,   483,   484,   486,
     487,   488,   489,   490,   503,   505,   139,   140,   245,   391,
     392,   393,   395,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   180,   181,   245,   503,
     505,   582,   583,   584,   585,   587,   588,   590,   591,   592,
     595,   597,   599,   600,   601,   603,   605,   607,    12,    13,
     613,   614,   615,   617,     6,     3,     4,     8,     3,   249,
       3,     8,   610,   297,   317,     4,     4,     4,   519,   521,
     523,   315,   325,   327,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   267,     4,     4,     4,     4,
       4,   278,   281,   283,     4,     4,     4,   408,   447,   473,
       4,   270,   439,   504,   506,   435,     4,     4,     4,   368,
     546,   508,   384,   398,     4,   377,   561,   569,   579,   287,
     289,     4,     4,     4,   619,   643,     4,     3,     8,   303,
     305,   308,     4,     4,     4,     4,     3,     8,   420,   422,
     424,   492,   418,   426,     4,   430,   428,   543,     3,     8,
     502,     3,     8,   541,   529,   531,   535,   533,   539,   537,
     525,     8,     3,     8,   463,   345,     4,   467,   465,   470,
       4,     8,     3,   485,     4,     4,     4,     8,     3,   394,
     396,     3,     8,     4,   598,   586,     4,   589,     4,     4,
     593,   596,     4,     4,   602,   604,   606,   608,     3,     8,
     616,     4,     3,     8,   230,   230,   211,     4,     4,     4,
       4,   214,   214,   214,     4,     4,     4,     4,     4,     4,
     212,   212,   212,   212,   212,   214,   213,   213,   213,   212,
     212,     4,   212,   212,   214,   214,   214,     4,     4,     4,
     214,   214,   214,     4,     4,     4,   212,     4,     4,     4,
       4,     4,   214,   214,   214,     4,     4,     4,     4,     4,
     212,     4,     4,     4,     4,     4,     4,   214,   214,   214,
       4,     4,   254,     4,     4,     4,   214,   214,   212,   212,
     299,     4,     4,     4,     4,     4,     4,   212,     4,     4,
       4,   416,     4,   500,     4,     4,     4,     4,     4,     4,
       4,     4,   517,     4,     4,   212,     4,     4,     4,   214,
     458,     4,   214,   214,   214,   482,     4,     4,   392,   214,
       4,     4,   212,     4,   212,   212,     4,     4,   214,   214,
       4,     4,     4,     4,   583,     4,   212,   614,     4,     7,
       7,     7,     7,   211,   211,   211,     7,     7,     5,   211,
     176,   177,   178,   179,   214,   279,   211,   211,     5,     5,
       5,   211,     5,   232,   234,   211,   114,   115,   116,   117,
     436,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     211,   211,     5,     7,     5,   241,    17,    18,   306,    20,
      21,   309,   211,   211,   211,     5,   211,   211,   241,   211,
       7,   211,   241,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   234,   211,   211,
     211,    18,   174,   594,   175,   279,   211,   211,   211,     5,
     230,   253,   613,   298,    27,    28,   318,   319,   320,   322,
      38,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    59,    60,    61,    62,    63,
     245,   332,   333,   334,   337,   339,   341,   343,   344,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   358,
     359,   361,   363,   365,   332,     7,   328,   329,   330,     7,
     409,   410,   411,     7,   450,   451,   452,     7,   474,   475,
     476,     7,   440,   441,   442,   129,   130,   131,   132,   134,
     369,   370,   371,   372,   373,   374,   375,     7,   547,   548,
       7,   509,   510,   511,     7,   385,   386,   387,   142,   143,
     144,   145,   146,   147,   399,   400,   401,   402,   403,   404,
     405,   406,   150,   151,   152,   245,   378,   379,   380,   381,
     382,   503,   505,   154,   155,   245,   503,   505,   562,   563,
     564,   566,   157,   158,   159,   211,   503,   505,   570,   571,
     572,   573,   575,   576,   582,     7,   620,   621,   195,   196,
     197,   245,   644,   645,   646,   647,   648,   242,     7,   493,
     494,   495,   137,   524,   526,   544,   328,     8,     8,     8,
     321,   323,     3,     8,   335,   338,   340,   342,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   356,     4,
     360,   362,   364,   366,     3,     8,     8,   331,     6,     3,
     412,     6,     3,   453,     6,     3,   477,     6,     3,   443,
       6,     3,     3,     6,   549,     3,     6,   512,     6,     3,
     388,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,     4,     4,     4,     3,     8,   565,   567,     3,     8,
       4,   574,     4,   577,     3,     8,     8,   622,     3,     6,
       4,     4,     4,     3,     8,   211,   243,   244,   496,     6,
       3,   527,     8,     6,     4,     4,   319,     4,     4,     4,
       4,   212,   214,   212,   214,   212,   212,   212,   212,   212,
     212,     4,   212,     4,     4,     4,     4,   333,   332,   330,
     415,   411,   456,   452,   480,   476,   245,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   269,   272,   273,
     274,   275,   276,   277,   280,   282,   284,   285,   286,   288,
     290,   344,   407,   425,   427,   429,   431,   432,   433,   434,
     444,   445,   472,   503,   505,   518,   520,   522,   542,   442,
     370,   124,   125,   126,   245,   255,   256,   257,   344,   446,
     472,   503,   505,   518,   520,   522,   550,   551,   552,   553,
     554,   556,   558,   548,   515,   511,   391,   387,   212,   212,
     212,   212,   212,   212,   400,   214,   212,   212,   379,     4,
       4,   563,   214,     4,   212,     4,   571,   186,   188,   189,
     245,   344,   503,   505,   623,   624,   625,   626,   628,   621,
     214,   214,   214,   645,     6,     3,   499,   495,     4,   211,
     211,    39,    40,    41,   336,   211,   211,   211,    56,    57,
      58,   357,   211,   211,   211,   211,     8,     8,     8,     8,
       3,     8,   555,   557,     4,     8,     3,     8,     8,   211,
     211,   211,   230,   629,     4,   627,     3,     8,   211,     8,
     241,   445,     4,     4,   214,   552,     4,   212,     4,   624,
     211,   211,     5,   211,     7,   630,   631,   632,     3,     6,
     187,   190,   191,   192,   193,   633,   634,   635,   637,   638,
     639,   640,   631,   636,     4,     4,     4,   641,     3,     8,
       4,   214,   212,   212,     4,   634,   211,   211
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   215,   217,   216,   218,   216,   219,   216,   220,   216,
     221,   216,   222,   216,   223,   216,   224,   216,   225,   216,
     226,   216,   227,   216,   228,   216,   229,   216,   230,   230,
     230,   230,   230,   230,   230,   231,   233,   232,   234,   235,
     235,   236,   236,   236,   238,   237,   239,   239,   240,   240,
     240,   242,   241,   243,   243,   244,   244,   244,   245,   247,
     246,   249,   248,   248,   250,   252,   251,   253,   253,   253,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   254,   254,   254,   254,   254,
     254,   254,   254,   254,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   267,   266,   268,   270,
     269,   271,   272,   273,   274,   275,   276,   278,   277,   279,
     279,   279,   279,   279,   281,   280,   283,   282,   284,   285,
     287,   286,   289,   288,   290,   291,   292,   293,   294,   295,
     297,   296,   298,   298,   298,   299,   299,   299,   299,   299,
     299,   299,   299,   299,   299,   301,   300,   303,   302,   305,
     304,   306,   306,   308,   307,   309,   309,   310,   311,   312,
     313,   315,   314,   317,   316,   318,   318,   318,   319,   319,
     321,   320,   323,   322,   325,   324,   327,   326,   328,   328,
     329,   329,   329,   331,   330,   332,   332,   332,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     333,   333,   333,   333,   333,   333,   333,   333,   333,   333,
     335,   334,   336,   336,   336,   338,   337,   340,   339,   342,
     341,   343,   345,   344,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   356,   355,   357,   357,   357,   358,   360,
     359,   362,   361,   364,   363,   366,   365,   368,   367,   369,
     369,   369,   370,   370,   370,   370,   370,   371,   372,   373,
     374,   375,   377,   376,   378,   378,   378,   379,   379,   379,
     379,   379,   379,   380,   381,   382,   384,   383,   385,   385,
     386,   386,   386,   388,   387,   390,   389,   391,   391,   391,
     391,   392,   392,   394,   393,   396,   395,   398,   397,   399,
     399,   399,   400,   400,   400,   400,   400,   400,   401,   402,
     403,   404,   405,   406,   408,   407,   409,   409,   410,   410,
     410,   412,   411,   414,   413,   415,   415,   415,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   418,   417,   420,   419,   422,   421,
     424,   423,   426,   425,   428,   427,   430,   429,   431,   432,
     433,   435,   434,   436,   436,   436,   436,   437,   439,   438,
     440,   440,   441,   441,   441,   443,   442,   444,   444,   444,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     445,   445,   445,   445,   445,   445,   445,   445,   445,   445,
     445,   447,   446,   449,   448,   450,   450,   451,   451,   451,
     453,   452,   455,   454,   456,   456,   457,   457,   457,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   459,
     460,   461,   463,   462,   465,   464,   467,   466,   468,   470,
     469,   471,   473,   472,   474,   474,   475,   475,   475,   477,
     476,   479,   478,   480,   480,   481,   481,   481,   482,   482,
     482,   482,   482,   482,   482,   482,   482,   482,   483,   485,
     484,   486,   487,   488,   489,   490,   492,   491,   493,   493,
     494,   494,   494,   496,   495,   498,   497,   499,   499,   499,
     500,   500,   500,   500,   500,   500,   500,   502,   501,   504,
     503,   506,   505,   508,   507,   509,   509,   510,   510,   510,
     512,   511,   514,   513,   515,   515,   516,   516,   516,   517,
     517,   517,   517,   517,   517,   517,   517,   517,   517,   517,
     517,   517,   517,   517,   519,   518,   521,   520,   523,   522,
     525,   524,   527,   526,   529,   528,   531,   530,   533,   532,
     535,   534,   537,   536,   539,   538,   541,   540,   543,   542,
     544,   544,   546,   545,   547,   547,   547,   549,   548,   550,
     550,   551,   551,   551,   552,   552,   552,   552,   552,   552,
     552,   552,   552,   552,   552,   552,   552,   552,   552,   553,
     555,   554,   557,   556,   558,   559,   561,   560,   562,   562,
     562,   563,   563,   563,   563,   563,   565,   564,   567,   566,
     569,   568,   570,   570,   570,   571,   571,   571,   571,   571,
     571,   572,   574,   573,   575,   577,   576,   579,   578,   581,
     580,   582,   582,   582,   583,   583,   583,   583,   583,   583,
     583,   583,   583,   583,   583,   583,   583,   583,   583,   583,
     583,   583,   584,   586,   585,   587,   589,   588,   590,   591,
     593,   592,   594,   594,   596,   595,   598,   597,   599,   600,
     602,   601,   604,   603,   606,   605,   608,   607,   610,   609,
     612,   611,   613,   613,   613,   614,   614,   616,   615,   617,
     619,   618,   620,   620,   620,   622,   621,   623,   623,   623,
     624,   624,   624,   624,   624,   624,   624,   625,   627,   626,
     629,   628,   630,   630,   630,   632,   631,   633,   633,   633,
     634,   634,   634,   634,   634,   636,   635,   637,   638,   639,
     641,   640,   643,   642,   644,   644,   644,   645,   645,   645,
     645,   646,   647,   648
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     3,     0,     6,     0,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     6,     1,     3,
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
       0,     4,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     3,     3,     3
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
  "\"csv-format\"", "\"always-send\"", "\"never-send\"",
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
  "ignore-rai-link-selection", "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   304,   304,   304,   305,   305,   306,   306,   307,   307,
     308,   308,   309,   309,   310,   310,   311,   311,   312,   312,
     313,   313,   314,   314,   315,   315,   316,   316,   324,   325,
     326,   327,   328,   329,   330,   333,   338,   338,   349,   352,
     353,   356,   361,   367,   372,   372,   379,   380,   383,   387,
     391,   397,   397,   404,   405,   408,   412,   416,   426,   435,
     435,   450,   450,   464,   467,   473,   473,   482,   483,   484,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,   550,
     551,   552,   553,   554,   555,   558,   564,   570,   576,   582,
     588,   594,   600,   606,   612,   618,   624,   624,   633,   639,
     639,   648,   654,   660,   666,   672,   678,   684,   684,   693,
     696,   699,   702,   705,   711,   711,   720,   720,   729,   735,
     741,   741,   750,   750,   759,   765,   771,   777,   783,   789,
     795,   795,   807,   808,   809,   814,   815,   816,   817,   818,
     819,   820,   821,   822,   823,   826,   826,   835,   835,   846,
     846,   854,   855,   858,   858,   866,   868,   872,   878,   884,
     890,   896,   896,   909,   909,   920,   921,   922,   927,   928,
     931,   931,   950,   950,   968,   968,   981,   981,   992,   993,
     996,   997,   998,  1003,  1003,  1013,  1014,  1015,  1020,  1021,
    1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,
    1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,  1040,  1041,
    1044,  1044,  1052,  1053,  1054,  1057,  1057,  1066,  1066,  1075,
    1075,  1084,  1090,  1090,  1099,  1105,  1111,  1117,  1123,  1129,
    1135,  1141,  1147,  1153,  1153,  1161,  1162,  1163,  1166,  1172,
    1172,  1181,  1181,  1190,  1190,  1199,  1199,  1208,  1208,  1219,
    1220,  1221,  1226,  1227,  1228,  1229,  1230,  1233,  1238,  1243,
    1248,  1253,  1260,  1260,  1273,  1274,  1275,  1280,  1281,  1282,
    1283,  1284,  1285,  1288,  1294,  1300,  1306,  1306,  1317,  1318,
    1321,  1322,  1323,  1328,  1328,  1338,  1338,  1348,  1349,  1350,
    1353,  1356,  1357,  1360,  1360,  1369,  1369,  1378,  1378,  1390,
    1391,  1392,  1397,  1398,  1399,  1400,  1401,  1402,  1405,  1411,
    1417,  1423,  1429,  1435,  1444,  1444,  1458,  1459,  1462,  1463,
    1464,  1473,  1473,  1499,  1499,  1510,  1511,  1512,  1518,  1519,
    1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,  1528,  1529,
    1530,  1531,  1532,  1533,  1534,  1535,  1536,  1537,  1538,  1539,
    1540,  1541,  1542,  1543,  1544,  1545,  1546,  1547,  1548,  1549,
    1550,  1551,  1552,  1553,  1554,  1555,  1556,  1557,  1558,  1559,
    1560,  1561,  1562,  1563,  1566,  1566,  1575,  1575,  1584,  1584,
    1593,  1593,  1602,  1602,  1611,  1611,  1620,  1620,  1631,  1637,
    1643,  1649,  1649,  1657,  1658,  1659,  1660,  1663,  1671,  1671,
    1683,  1684,  1688,  1689,  1690,  1695,  1695,  1703,  1704,  1705,
    1710,  1711,  1712,  1713,  1714,  1715,  1716,  1717,  1718,  1719,
    1720,  1721,  1722,  1723,  1724,  1725,  1726,  1727,  1728,  1729,
    1730,  1731,  1732,  1733,  1734,  1735,  1736,  1737,  1738,  1739,
    1740,  1741,  1742,  1743,  1744,  1745,  1746,  1747,  1748,  1749,
    1750,  1757,  1757,  1771,  1771,  1780,  1781,  1784,  1785,  1786,
    1793,  1793,  1808,  1808,  1822,  1823,  1826,  1827,  1828,  1833,
    1834,  1835,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1845,
    1847,  1853,  1855,  1855,  1864,  1864,  1873,  1873,  1882,  1884,
    1884,  1893,  1903,  1903,  1916,  1917,  1922,  1923,  1924,  1931,
    1931,  1943,  1943,  1955,  1956,  1961,  1962,  1963,  1970,  1971,
    1972,  1973,  1974,  1975,  1976,  1977,  1978,  1979,  1982,  1984,
    1984,  1993,  1995,  1997,  2003,  2009,  2018,  2018,  2031,  2032,
    2035,  2036,  2037,  2042,  2042,  2052,  2052,  2062,  2063,  2064,
    2069,  2070,  2071,  2072,  2073,  2074,  2075,  2078,  2078,  2087,
    2087,  2112,  2112,  2142,  2142,  2153,  2154,  2157,  2158,  2159,
    2164,  2164,  2173,  2173,  2182,  2183,  2186,  2187,  2188,  2194,
    2195,  2196,  2197,  2198,  2199,  2200,  2201,  2202,  2203,  2204,
    2205,  2206,  2207,  2208,  2211,  2211,  2220,  2220,  2229,  2229,
    2238,  2238,  2247,  2247,  2258,  2258,  2267,  2267,  2276,  2276,
    2285,  2285,  2294,  2294,  2303,  2303,  2312,  2312,  2326,  2326,
    2337,  2338,  2344,  2344,  2355,  2356,  2357,  2362,  2362,  2372,
    2373,  2376,  2377,  2378,  2383,  2384,  2385,  2386,  2387,  2388,
    2389,  2390,  2391,  2392,  2393,  2394,  2395,  2396,  2397,  2400,
    2402,  2402,  2411,  2411,  2420,  2428,  2436,  2436,  2447,  2448,
    2449,  2454,  2455,  2456,  2457,  2458,  2461,  2461,  2470,  2470,
    2482,  2482,  2495,  2496,  2497,  2502,  2503,  2504,  2505,  2506,
    2507,  2510,  2516,  2516,  2525,  2531,  2531,  2541,  2541,  2554,
    2554,  2564,  2565,  2566,  2571,  2572,  2573,  2574,  2575,  2576,
    2577,  2578,  2579,  2580,  2581,  2582,  2583,  2584,  2585,  2586,
    2587,  2588,  2591,  2597,  2597,  2606,  2612,  2612,  2621,  2627,
    2633,  2633,  2642,  2643,  2646,  2646,  2656,  2656,  2666,  2673,
    2680,  2680,  2689,  2689,  2699,  2699,  2709,  2709,  2721,  2721,
    2733,  2733,  2743,  2744,  2745,  2751,  2752,  2755,  2755,  2766,
    2774,  2774,  2787,  2788,  2789,  2795,  2795,  2803,  2804,  2805,
    2810,  2811,  2812,  2813,  2814,  2815,  2816,  2819,  2825,  2825,
    2834,  2834,  2845,  2846,  2847,  2852,  2852,  2860,  2861,  2862,
    2867,  2868,  2869,  2870,  2871,  2874,  2874,  2883,  2889,  2895,
    2901,  2901,  2910,  2910,  2921,  2922,  2923,  2928,  2929,  2930,
    2931,  2934,  2940,  2946
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
#line 6303 "dhcp4_parser.cc"

#line 2952 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
