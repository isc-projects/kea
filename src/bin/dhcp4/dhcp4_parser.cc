// A Bison parser, made by GNU Bison 3.7.5.

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
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 281 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 281 "dhcp4_parser.yy"
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
#line 290 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 291 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 292 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 293 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 294 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 295 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 296 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 297 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 298 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 299 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 300 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 301 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 302 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 310 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 311 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 312 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 313 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 314 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 315 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 316 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 319 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 324 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 329 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 335 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 342 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 347 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // $@15: %empty
#line 355 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 941 "dhcp4_parser.cc"
    break;

  case 44: // list_generic: "[" $@15 list_content "]"
#line 358 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 949 "dhcp4_parser.cc"
    break;

  case 47: // not_empty_list: value
#line 366 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 958 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: not_empty_list "," value
#line 370 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 967 "dhcp4_parser.cc"
    break;

  case 49: // $@16: %empty
#line 377 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // list_strings: "[" $@16 list_strings_content "]"
#line 379 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 984 "dhcp4_parser.cc"
    break;

  case 53: // not_empty_list_strings: "constant string"
#line 388 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 993 "dhcp4_parser.cc"
    break;

  case 54: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 392 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1002 "dhcp4_parser.cc"
    break;

  case 55: // unknown_map_entry: "constant string" ":"
#line 403 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1013 "dhcp4_parser.cc"
    break;

  case 56: // $@17: %empty
#line 412 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1024 "dhcp4_parser.cc"
    break;

  case 57: // syntax_map: "{" $@17 global_object "}"
#line 417 "dhcp4_parser.yy"
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
#line 427 "dhcp4_parser.yy"
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
#line 436 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1062 "dhcp4_parser.cc"
    break;

  case 60: // $@19: %empty
#line 444 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1072 "dhcp4_parser.cc"
    break;

  case 61: // sub_dhcp4: "{" $@19 global_params "}"
#line 448 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1081 "dhcp4_parser.cc"
    break;

  case 124: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 521 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1091 "dhcp4_parser.cc"
    break;

  case 125: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 527 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1101 "dhcp4_parser.cc"
    break;

  case 126: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 533 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1111 "dhcp4_parser.cc"
    break;

  case 127: // renew_timer: "renew-timer" ":" "integer"
#line 539 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 128: // rebind_timer: "rebind-timer" ":" "integer"
#line 545 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 129: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 551 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 130: // t1_percent: "t1-percent" ":" "floating point"
#line 557 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 131: // t2_percent: "t2-percent" ":" "floating point"
#line 563 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 132: // cache_threshold: "cache-threshold" ":" "floating point"
#line 569 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 133: // cache_max_age: "cache-max-age" ":" "integer"
#line 575 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 134: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 581 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 135: // $@20: %empty
#line 587 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1200 "dhcp4_parser.cc"
    break;

  case 136: // server_tag: "server-tag" $@20 ":" "constant string"
#line 590 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1210 "dhcp4_parser.cc"
    break;

  case 137: // echo_client_id: "echo-client-id" ":" "boolean"
#line 596 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1220 "dhcp4_parser.cc"
    break;

  case 138: // match_client_id: "match-client-id" ":" "boolean"
#line 602 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1230 "dhcp4_parser.cc"
    break;

  case 139: // authoritative: "authoritative" ":" "boolean"
#line 608 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 140: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 614 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 141: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 620 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 142: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 626 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1270 "dhcp4_parser.cc"
    break;

  case 143: // $@21: %empty
#line 632 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 144: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 635 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1288 "dhcp4_parser.cc"
    break;

  case 145: // ddns_replace_client_name_value: "when-present"
#line 641 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1296 "dhcp4_parser.cc"
    break;

  case 146: // ddns_replace_client_name_value: "never"
#line 644 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1304 "dhcp4_parser.cc"
    break;

  case 147: // ddns_replace_client_name_value: "always"
#line 647 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1312 "dhcp4_parser.cc"
    break;

  case 148: // ddns_replace_client_name_value: "when-not-present"
#line 650 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1320 "dhcp4_parser.cc"
    break;

  case 149: // ddns_replace_client_name_value: "boolean"
#line 653 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1329 "dhcp4_parser.cc"
    break;

  case 150: // $@22: %empty
#line 659 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1338 "dhcp4_parser.cc"
    break;

  case 151: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 662 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1348 "dhcp4_parser.cc"
    break;

  case 152: // $@23: %empty
#line 668 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1357 "dhcp4_parser.cc"
    break;

  case 153: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 671 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1367 "dhcp4_parser.cc"
    break;

  case 154: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 677 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1377 "dhcp4_parser.cc"
    break;

  case 155: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 683 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1387 "dhcp4_parser.cc"
    break;

  case 156: // $@24: %empty
#line 689 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1396 "dhcp4_parser.cc"
    break;

  case 157: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 692 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1406 "dhcp4_parser.cc"
    break;

  case 158: // $@25: %empty
#line 698 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1415 "dhcp4_parser.cc"
    break;

  case 159: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 701 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1425 "dhcp4_parser.cc"
    break;

  case 160: // store_extended_info: "store-extended-info" ":" "boolean"
#line 707 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1435 "dhcp4_parser.cc"
    break;

  case 161: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 713 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1445 "dhcp4_parser.cc"
    break;

  case 162: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 719 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1455 "dhcp4_parser.cc"
    break;

  case 163: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 725 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 164: // $@26: %empty
#line 731 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1477 "dhcp4_parser.cc"
    break;

  case 165: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 737 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1487 "dhcp4_parser.cc"
    break;

  case 175: // $@27: %empty
#line 756 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1497 "dhcp4_parser.cc"
    break;

  case 176: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 760 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1506 "dhcp4_parser.cc"
    break;

  case 177: // $@28: %empty
#line 765 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1518 "dhcp4_parser.cc"
    break;

  case 178: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 771 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1527 "dhcp4_parser.cc"
    break;

  case 179: // $@29: %empty
#line 776 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 180: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 779 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1545 "dhcp4_parser.cc"
    break;

  case 181: // socket_type: "raw"
#line 784 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1551 "dhcp4_parser.cc"
    break;

  case 182: // socket_type: "udp"
#line 785 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1557 "dhcp4_parser.cc"
    break;

  case 183: // $@30: %empty
#line 788 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 184: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 791 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1575 "dhcp4_parser.cc"
    break;

  case 185: // outbound_interface_value: "same-as-inbound"
#line 796 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1583 "dhcp4_parser.cc"
    break;

  case 186: // outbound_interface_value: "use-routing"
#line 798 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1591 "dhcp4_parser.cc"
    break;

  case 187: // re_detect: "re-detect" ":" "boolean"
#line 802 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1601 "dhcp4_parser.cc"
    break;

  case 188: // $@31: %empty
#line 809 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1613 "dhcp4_parser.cc"
    break;

  case 189: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 815 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 190: // $@32: %empty
#line 822 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1636 "dhcp4_parser.cc"
    break;

  case 191: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 828 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 195: // $@33: %empty
#line 838 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 196: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 841 "dhcp4_parser.yy"
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
#line 1674 "dhcp4_parser.cc"
    break;

  case 197: // $@34: %empty
#line 857 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1686 "dhcp4_parser.cc"
    break;

  case 198: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 863 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1697 "dhcp4_parser.cc"
    break;

  case 199: // $@35: %empty
#line 870 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1709 "dhcp4_parser.cc"
    break;

  case 200: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 876 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 205: // $@36: %empty
#line 889 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 206: // database: "{" $@36 database_map_params "}"
#line 893 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 231: // $@37: %empty
#line 927 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1747 "dhcp4_parser.cc"
    break;

  case 232: // database_type: "type" $@37 ":" db_type
#line 930 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1756 "dhcp4_parser.cc"
    break;

  case 233: // db_type: "memfile"
#line 935 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1762 "dhcp4_parser.cc"
    break;

  case 234: // db_type: "mysql"
#line 936 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1768 "dhcp4_parser.cc"
    break;

  case 235: // db_type: "postgresql"
#line 937 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1774 "dhcp4_parser.cc"
    break;

  case 236: // db_type: "cql"
#line 938 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1780 "dhcp4_parser.cc"
    break;

  case 237: // $@38: %empty
#line 941 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc"
    break;

  case 238: // user: "user" $@38 ":" "constant string"
#line 944 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1799 "dhcp4_parser.cc"
    break;

  case 239: // $@39: %empty
#line 950 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1808 "dhcp4_parser.cc"
    break;

  case 240: // password: "password" $@39 ":" "constant string"
#line 953 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 241: // $@40: %empty
#line 959 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1827 "dhcp4_parser.cc"
    break;

  case 242: // host: "host" $@40 ":" "constant string"
#line 962 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1837 "dhcp4_parser.cc"
    break;

  case 243: // port: "port" ":" "integer"
#line 968 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1847 "dhcp4_parser.cc"
    break;

  case 244: // $@41: %empty
#line 974 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1856 "dhcp4_parser.cc"
    break;

  case 245: // name: "name" $@41 ":" "constant string"
#line 977 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1866 "dhcp4_parser.cc"
    break;

  case 246: // persist: "persist" ":" "boolean"
#line 983 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1876 "dhcp4_parser.cc"
    break;

  case 247: // lfc_interval: "lfc-interval" ":" "integer"
#line 989 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1886 "dhcp4_parser.cc"
    break;

  case 248: // readonly: "readonly" ":" "boolean"
#line 995 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1896 "dhcp4_parser.cc"
    break;

  case 249: // connect_timeout: "connect-timeout" ":" "integer"
#line 1001 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1906 "dhcp4_parser.cc"
    break;

  case 250: // request_timeout: "request-timeout" ":" "integer"
#line 1007 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1916 "dhcp4_parser.cc"
    break;

  case 251: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 1013 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 252: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 1019 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1936 "dhcp4_parser.cc"
    break;

  case 253: // $@42: %empty
#line 1025 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1945 "dhcp4_parser.cc"
    break;

  case 254: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1028 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1955 "dhcp4_parser.cc"
    break;

  case 255: // $@43: %empty
#line 1034 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1964 "dhcp4_parser.cc"
    break;

  case 256: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1037 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1974 "dhcp4_parser.cc"
    break;

  case 257: // $@44: %empty
#line 1043 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp4_parser.cc"
    break;

  case 258: // consistency: "consistency" $@44 ":" "constant string"
#line 1046 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1993 "dhcp4_parser.cc"
    break;

  case 259: // $@45: %empty
#line 1052 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2002 "dhcp4_parser.cc"
    break;

  case 260: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1055 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 2012 "dhcp4_parser.cc"
    break;

  case 261: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1061 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2022 "dhcp4_parser.cc"
    break;

  case 262: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1067 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2032 "dhcp4_parser.cc"
    break;

  case 263: // $@46: %empty
#line 1073 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2041 "dhcp4_parser.cc"
    break;

  case 264: // on_fail: "on-fail" $@46 ":" on_fail_mode
#line 1076 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 265: // on_fail_mode: "stop-retry-exit"
#line 1081 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2056 "dhcp4_parser.cc"
    break;

  case 266: // on_fail_mode: "serve-retry-exit"
#line 1082 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2062 "dhcp4_parser.cc"
    break;

  case 267: // on_fail_mode: "serve-retry-continue"
#line 1083 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2068 "dhcp4_parser.cc"
    break;

  case 268: // max_row_errors: "max-row-errors" ":" "integer"
#line 1086 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2078 "dhcp4_parser.cc"
    break;

  case 269: // $@47: %empty
#line 1093 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2090 "dhcp4_parser.cc"
    break;

  case 270: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1099 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 278: // duid_id: "duid"
#line 1115 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2108 "dhcp4_parser.cc"
    break;

  case 279: // hw_address_id: "hw-address"
#line 1120 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2117 "dhcp4_parser.cc"
    break;

  case 280: // circuit_id: "circuit-id"
#line 1125 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2126 "dhcp4_parser.cc"
    break;

  case 281: // client_id: "client-id"
#line 1130 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2135 "dhcp4_parser.cc"
    break;

  case 282: // flex_id: "flex-id"
#line 1135 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2144 "dhcp4_parser.cc"
    break;

  case 283: // $@48: %empty
#line 1142 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2156 "dhcp4_parser.cc"
    break;

  case 284: // dhcp_multi_threading: "multi-threading" $@48 ":" "{" multi_threading_params "}"
#line 1148 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2167 "dhcp4_parser.cc"
    break;

  case 293: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1167 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2177 "dhcp4_parser.cc"
    break;

  case 294: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1173 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2187 "dhcp4_parser.cc"
    break;

  case 295: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1179 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2197 "dhcp4_parser.cc"
    break;

  case 296: // $@49: %empty
#line 1185 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 297: // hooks_libraries: "hooks-libraries" $@49 ":" "[" hooks_libraries_list "]"
#line 1191 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2218 "dhcp4_parser.cc"
    break;

  case 302: // $@50: %empty
#line 1204 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2228 "dhcp4_parser.cc"
    break;

  case 303: // hooks_library: "{" $@50 hooks_params "}"
#line 1208 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2238 "dhcp4_parser.cc"
    break;

  case 304: // $@51: %empty
#line 1214 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2248 "dhcp4_parser.cc"
    break;

  case 305: // sub_hooks_library: "{" $@51 hooks_params "}"
#line 1218 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2258 "dhcp4_parser.cc"
    break;

  case 311: // $@52: %empty
#line 1233 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2267 "dhcp4_parser.cc"
    break;

  case 312: // library: "library" $@52 ":" "constant string"
#line 1236 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2277 "dhcp4_parser.cc"
    break;

  case 313: // $@53: %empty
#line 1242 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2286 "dhcp4_parser.cc"
    break;

  case 314: // parameters: "parameters" $@53 ":" map_value
#line 1245 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2295 "dhcp4_parser.cc"
    break;

  case 315: // $@54: %empty
#line 1251 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 316: // expired_leases_processing: "expired-leases-processing" $@54 ":" "{" expired_leases_params "}"
#line 1257 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2317 "dhcp4_parser.cc"
    break;

  case 325: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1275 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2327 "dhcp4_parser.cc"
    break;

  case 326: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1281 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2337 "dhcp4_parser.cc"
    break;

  case 327: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1287 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 328: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1293 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 329: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1299 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2367 "dhcp4_parser.cc"
    break;

  case 330: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1305 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2377 "dhcp4_parser.cc"
    break;

  case 331: // $@55: %empty
#line 1314 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2389 "dhcp4_parser.cc"
    break;

  case 332: // subnet4_list: "subnet4" $@55 ":" "[" subnet4_list_content "]"
#line 1320 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 337: // $@56: %empty
#line 1340 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2408 "dhcp4_parser.cc"
    break;

  case 338: // subnet4: "{" $@56 subnet4_params "}"
#line 1344 "dhcp4_parser.yy"
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
#line 2434 "dhcp4_parser.cc"
    break;

  case 339: // $@57: %empty
#line 1366 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2444 "dhcp4_parser.cc"
    break;

  case 340: // sub_subnet4: "{" $@57 subnet4_params "}"
#line 1370 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2454 "dhcp4_parser.cc"
    break;

  case 388: // $@58: %empty
#line 1429 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2463 "dhcp4_parser.cc"
    break;

  case 389: // subnet: "subnet" $@58 ":" "constant string"
#line 1432 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 390: // $@59: %empty
#line 1438 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 391: // subnet_4o6_interface: "4o6-interface" $@59 ":" "constant string"
#line 1441 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 392: // $@60: %empty
#line 1447 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 393: // subnet_4o6_interface_id: "4o6-interface-id" $@60 ":" "constant string"
#line 1450 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2511 "dhcp4_parser.cc"
    break;

  case 394: // $@61: %empty
#line 1456 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2520 "dhcp4_parser.cc"
    break;

  case 395: // subnet_4o6_subnet: "4o6-subnet" $@61 ":" "constant string"
#line 1459 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2530 "dhcp4_parser.cc"
    break;

  case 396: // $@62: %empty
#line 1465 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2539 "dhcp4_parser.cc"
    break;

  case 397: // interface: "interface" $@62 ":" "constant string"
#line 1468 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2549 "dhcp4_parser.cc"
    break;

  case 398: // $@63: %empty
#line 1474 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2558 "dhcp4_parser.cc"
    break;

  case 399: // client_class: "client-class" $@63 ":" "constant string"
#line 1477 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2568 "dhcp4_parser.cc"
    break;

  case 400: // $@64: %empty
#line 1483 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 401: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1489 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2589 "dhcp4_parser.cc"
    break;

  case 402: // reservations_global: "reservations-global" ":" "boolean"
#line 1494 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 403: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1500 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2609 "dhcp4_parser.cc"
    break;

  case 404: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1506 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2619 "dhcp4_parser.cc"
    break;

  case 405: // $@65: %empty
#line 1512 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2628 "dhcp4_parser.cc"
    break;

  case 406: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1515 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2637 "dhcp4_parser.cc"
    break;

  case 407: // hr_mode: "disabled"
#line 1520 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2643 "dhcp4_parser.cc"
    break;

  case 408: // hr_mode: "out-of-pool"
#line 1521 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2649 "dhcp4_parser.cc"
    break;

  case 409: // hr_mode: "global"
#line 1522 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2655 "dhcp4_parser.cc"
    break;

  case 410: // hr_mode: "all"
#line 1523 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2661 "dhcp4_parser.cc"
    break;

  case 411: // id: "id" ":" "integer"
#line 1526 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2671 "dhcp4_parser.cc"
    break;

  case 412: // $@66: %empty
#line 1534 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 413: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1540 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 418: // $@67: %empty
#line 1555 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 419: // shared_network: "{" $@67 shared_network_params "}"
#line 1559 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2710 "dhcp4_parser.cc"
    break;

  case 462: // $@68: %empty
#line 1613 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 463: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1619 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2731 "dhcp4_parser.cc"
    break;

  case 464: // $@69: %empty
#line 1627 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2740 "dhcp4_parser.cc"
    break;

  case 465: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1630 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2748 "dhcp4_parser.cc"
    break;

  case 470: // $@70: %empty
#line 1646 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2758 "dhcp4_parser.cc"
    break;

  case 471: // option_def_entry: "{" $@70 option_def_params "}"
#line 1650 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2770 "dhcp4_parser.cc"
    break;

  case 472: // $@71: %empty
#line 1661 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2780 "dhcp4_parser.cc"
    break;

  case 473: // sub_option_def: "{" $@71 option_def_params "}"
#line 1665 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 489: // code: "code" ":" "integer"
#line 1697 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 491: // $@72: %empty
#line 1705 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2811 "dhcp4_parser.cc"
    break;

  case 492: // option_def_type: "type" $@72 ":" "constant string"
#line 1708 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 493: // $@73: %empty
#line 1714 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2830 "dhcp4_parser.cc"
    break;

  case 494: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1717 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2840 "dhcp4_parser.cc"
    break;

  case 495: // $@74: %empty
#line 1723 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2849 "dhcp4_parser.cc"
    break;

  case 496: // space: "space" $@74 ":" "constant string"
#line 1726 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2859 "dhcp4_parser.cc"
    break;

  case 498: // $@75: %empty
#line 1734 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2868 "dhcp4_parser.cc"
    break;

  case 499: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1737 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2878 "dhcp4_parser.cc"
    break;

  case 500: // option_def_array: "array" ":" "boolean"
#line 1743 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2888 "dhcp4_parser.cc"
    break;

  case 501: // $@76: %empty
#line 1753 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 502: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1759 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 507: // $@77: %empty
#line 1778 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2919 "dhcp4_parser.cc"
    break;

  case 508: // option_data_entry: "{" $@77 option_data_params "}"
#line 1782 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2928 "dhcp4_parser.cc"
    break;

  case 509: // $@78: %empty
#line 1790 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2938 "dhcp4_parser.cc"
    break;

  case 510: // sub_option_data: "{" $@78 option_data_params "}"
#line 1794 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 525: // $@79: %empty
#line 1827 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2956 "dhcp4_parser.cc"
    break;

  case 526: // option_data_data: "data" $@79 ":" "constant string"
#line 1830 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2966 "dhcp4_parser.cc"
    break;

  case 529: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1840 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 530: // option_data_always_send: "always-send" ":" "boolean"
#line 1846 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2986 "dhcp4_parser.cc"
    break;

  case 531: // $@80: %empty
#line 1855 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2998 "dhcp4_parser.cc"
    break;

  case 532: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1861 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3007 "dhcp4_parser.cc"
    break;

  case 537: // $@81: %empty
#line 1876 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3017 "dhcp4_parser.cc"
    break;

  case 538: // pool_list_entry: "{" $@81 pool_params "}"
#line 1880 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3027 "dhcp4_parser.cc"
    break;

  case 539: // $@82: %empty
#line 1886 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3037 "dhcp4_parser.cc"
    break;

  case 540: // sub_pool4: "{" $@82 pool_params "}"
#line 1890 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3047 "dhcp4_parser.cc"
    break;

  case 550: // $@83: %empty
#line 1909 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3056 "dhcp4_parser.cc"
    break;

  case 551: // pool_entry: "pool" $@83 ":" "constant string"
#line 1912 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3066 "dhcp4_parser.cc"
    break;

  case 552: // $@84: %empty
#line 1918 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3074 "dhcp4_parser.cc"
    break;

  case 553: // user_context: "user-context" $@84 ":" map_value
#line 1920 "dhcp4_parser.yy"
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
#line 3101 "dhcp4_parser.cc"
    break;

  case 554: // $@85: %empty
#line 1943 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3109 "dhcp4_parser.cc"
    break;

  case 555: // comment: "comment" $@85 ":" "constant string"
#line 1945 "dhcp4_parser.yy"
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
#line 3138 "dhcp4_parser.cc"
    break;

  case 556: // $@86: %empty
#line 1973 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3150 "dhcp4_parser.cc"
    break;

  case 557: // reservations: "reservations" $@86 ":" "[" reservations_list "]"
#line 1979 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3159 "dhcp4_parser.cc"
    break;

  case 562: // $@87: %empty
#line 1992 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3169 "dhcp4_parser.cc"
    break;

  case 563: // reservation: "{" $@87 reservation_params "}"
#line 1996 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3178 "dhcp4_parser.cc"
    break;

  case 564: // $@88: %empty
#line 2001 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 565: // sub_reservation: "{" $@88 reservation_params "}"
#line 2005 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 585: // $@89: %empty
#line 2036 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 586: // next_server: "next-server" $@89 ":" "constant string"
#line 2039 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 587: // $@90: %empty
#line 2045 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 588: // server_hostname: "server-hostname" $@90 ":" "constant string"
#line 2048 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3235 "dhcp4_parser.cc"
    break;

  case 589: // $@91: %empty
#line 2054 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3244 "dhcp4_parser.cc"
    break;

  case 590: // boot_file_name: "boot-file-name" $@91 ":" "constant string"
#line 2057 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 591: // $@92: %empty
#line 2063 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 592: // ip_address: "ip-address" $@92 ":" "constant string"
#line 2066 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 593: // $@93: %empty
#line 2072 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3285 "dhcp4_parser.cc"
    break;

  case 594: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2078 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3294 "dhcp4_parser.cc"
    break;

  case 595: // $@94: %empty
#line 2083 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 596: // duid: "duid" $@94 ":" "constant string"
#line 2086 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3313 "dhcp4_parser.cc"
    break;

  case 597: // $@95: %empty
#line 2092 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 598: // hw_address: "hw-address" $@95 ":" "constant string"
#line 2095 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 599: // $@96: %empty
#line 2101 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3341 "dhcp4_parser.cc"
    break;

  case 600: // client_id_value: "client-id" $@96 ":" "constant string"
#line 2104 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3351 "dhcp4_parser.cc"
    break;

  case 601: // $@97: %empty
#line 2110 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3360 "dhcp4_parser.cc"
    break;

  case 602: // circuit_id_value: "circuit-id" $@97 ":" "constant string"
#line 2113 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3370 "dhcp4_parser.cc"
    break;

  case 603: // $@98: %empty
#line 2119 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3379 "dhcp4_parser.cc"
    break;

  case 604: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2122 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3389 "dhcp4_parser.cc"
    break;

  case 605: // $@99: %empty
#line 2128 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3398 "dhcp4_parser.cc"
    break;

  case 606: // hostname: "hostname" $@99 ":" "constant string"
#line 2131 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3408 "dhcp4_parser.cc"
    break;

  case 607: // $@100: %empty
#line 2137 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3420 "dhcp4_parser.cc"
    break;

  case 608: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2143 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3429 "dhcp4_parser.cc"
    break;

  case 609: // $@101: %empty
#line 2151 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3441 "dhcp4_parser.cc"
    break;

  case 610: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2157 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3450 "dhcp4_parser.cc"
    break;

  case 613: // $@102: %empty
#line 2169 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3462 "dhcp4_parser.cc"
    break;

  case 614: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2175 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3471 "dhcp4_parser.cc"
    break;

  case 617: // $@103: %empty
#line 2184 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3481 "dhcp4_parser.cc"
    break;

  case 618: // client_class_entry: "{" $@103 client_class_params "}"
#line 2188 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3491 "dhcp4_parser.cc"
    break;

  case 638: // $@104: %empty
#line 2220 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3500 "dhcp4_parser.cc"
    break;

  case 639: // client_class_test: "test" $@104 ":" "constant string"
#line 2223 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3510 "dhcp4_parser.cc"
    break;

  case 640: // only_if_required: "only-if-required" ":" "boolean"
#line 2229 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3520 "dhcp4_parser.cc"
    break;

  case 641: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2237 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3530 "dhcp4_parser.cc"
    break;

  case 642: // $@105: %empty
#line 2245 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3542 "dhcp4_parser.cc"
    break;

  case 643: // control_socket: "control-socket" $@105 ":" "{" control_socket_params "}"
#line 2251 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3551 "dhcp4_parser.cc"
    break;

  case 651: // $@106: %empty
#line 2267 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3560 "dhcp4_parser.cc"
    break;

  case 652: // control_socket_type: "socket-type" $@106 ":" "constant string"
#line 2270 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3570 "dhcp4_parser.cc"
    break;

  case 653: // $@107: %empty
#line 2276 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3579 "dhcp4_parser.cc"
    break;

  case 654: // control_socket_name: "socket-name" $@107 ":" "constant string"
#line 2279 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3589 "dhcp4_parser.cc"
    break;

  case 655: // $@108: %empty
#line 2288 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3601 "dhcp4_parser.cc"
    break;

  case 656: // dhcp_queue_control: "dhcp-queue-control" $@108 ":" "{" queue_control_params "}"
#line 2294 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 665: // enable_queue: "enable-queue" ":" "boolean"
#line 2313 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 666: // $@109: %empty
#line 2319 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3631 "dhcp4_parser.cc"
    break;

  case 667: // queue_type: "queue-type" $@109 ":" "constant string"
#line 2322 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 668: // capacity: "capacity" ":" "integer"
#line 2328 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3651 "dhcp4_parser.cc"
    break;

  case 669: // $@110: %empty
#line 2334 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3660 "dhcp4_parser.cc"
    break;

  case 670: // arbitrary_map_entry: "constant string" $@110 ":" value
#line 2337 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3669 "dhcp4_parser.cc"
    break;

  case 671: // $@111: %empty
#line 2344 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3681 "dhcp4_parser.cc"
    break;

  case 672: // dhcp_ddns: "dhcp-ddns" $@111 ":" "{" dhcp_ddns_params "}"
#line 2350 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3692 "dhcp4_parser.cc"
    break;

  case 673: // $@112: %empty
#line 2357 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 674: // sub_dhcp_ddns: "{" $@112 dhcp_ddns_params "}"
#line 2361 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3712 "dhcp4_parser.cc"
    break;

  case 695: // enable_updates: "enable-updates" ":" "boolean"
#line 2391 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 696: // $@113: %empty
#line 2397 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3731 "dhcp4_parser.cc"
    break;

  case 697: // server_ip: "server-ip" $@113 ":" "constant string"
#line 2400 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 698: // server_port: "server-port" ":" "integer"
#line 2406 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 699: // $@114: %empty
#line 2412 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 700: // sender_ip: "sender-ip" $@114 ":" "constant string"
#line 2415 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3770 "dhcp4_parser.cc"
    break;

  case 701: // sender_port: "sender-port" ":" "integer"
#line 2421 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 702: // max_queue_size: "max-queue-size" ":" "integer"
#line 2427 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3790 "dhcp4_parser.cc"
    break;

  case 703: // $@115: %empty
#line 2433 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3799 "dhcp4_parser.cc"
    break;

  case 704: // ncr_protocol: "ncr-protocol" $@115 ":" ncr_protocol_value
#line 2436 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 705: // ncr_protocol_value: "udp"
#line 2442 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3814 "dhcp4_parser.cc"
    break;

  case 706: // ncr_protocol_value: "tcp"
#line 2443 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3820 "dhcp4_parser.cc"
    break;

  case 707: // $@116: %empty
#line 2446 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3829 "dhcp4_parser.cc"
    break;

  case 708: // ncr_format: "ncr-format" $@116 ":" "JSON"
#line 2449 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3839 "dhcp4_parser.cc"
    break;

  case 709: // $@117: %empty
#line 2456 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3848 "dhcp4_parser.cc"
    break;

  case 710: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2459 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 711: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2466 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3868 "dhcp4_parser.cc"
    break;

  case 712: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2473 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3878 "dhcp4_parser.cc"
    break;

  case 713: // $@118: %empty
#line 2480 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3887 "dhcp4_parser.cc"
    break;

  case 714: // dep_replace_client_name: "replace-client-name" $@118 ":" ddns_replace_client_name_value
#line 2483 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3896 "dhcp4_parser.cc"
    break;

  case 715: // $@119: %empty
#line 2489 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3905 "dhcp4_parser.cc"
    break;

  case 716: // dep_generated_prefix: "generated-prefix" $@119 ":" "constant string"
#line 2492 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3915 "dhcp4_parser.cc"
    break;

  case 717: // $@120: %empty
#line 2499 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3924 "dhcp4_parser.cc"
    break;

  case 718: // dep_hostname_char_set: "hostname-char-set" $@120 ":" "constant string"
#line 2502 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3934 "dhcp4_parser.cc"
    break;

  case 719: // $@121: %empty
#line 2509 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3943 "dhcp4_parser.cc"
    break;

  case 720: // dep_hostname_char_replacement: "hostname-char-replacement" $@121 ":" "constant string"
#line 2512 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3953 "dhcp4_parser.cc"
    break;

  case 721: // $@122: %empty
#line 2521 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3965 "dhcp4_parser.cc"
    break;

  case 722: // config_control: "config-control" $@122 ":" "{" config_control_params "}"
#line 2527 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3975 "dhcp4_parser.cc"
    break;

  case 723: // $@123: %empty
#line 2533 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3985 "dhcp4_parser.cc"
    break;

  case 724: // sub_config_control: "{" $@123 config_control_params "}"
#line 2537 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3994 "dhcp4_parser.cc"
    break;

  case 729: // $@124: %empty
#line 2552 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4006 "dhcp4_parser.cc"
    break;

  case 730: // config_databases: "config-databases" $@124 ":" "[" database_list "]"
#line 2558 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4015 "dhcp4_parser.cc"
    break;

  case 731: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2563 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4025 "dhcp4_parser.cc"
    break;

  case 732: // $@125: %empty
#line 2571 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4037 "dhcp4_parser.cc"
    break;

  case 733: // loggers: "loggers" $@125 ":" "[" loggers_entries "]"
#line 2577 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4046 "dhcp4_parser.cc"
    break;

  case 736: // $@126: %empty
#line 2589 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4056 "dhcp4_parser.cc"
    break;

  case 737: // logger_entry: "{" $@126 logger_params "}"
#line 2593 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4064 "dhcp4_parser.cc"
    break;

  case 747: // debuglevel: "debuglevel" ":" "integer"
#line 2610 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4074 "dhcp4_parser.cc"
    break;

  case 748: // $@127: %empty
#line 2616 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4083 "dhcp4_parser.cc"
    break;

  case 749: // severity: "severity" $@127 ":" "constant string"
#line 2619 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4093 "dhcp4_parser.cc"
    break;

  case 750: // $@128: %empty
#line 2625 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4105 "dhcp4_parser.cc"
    break;

  case 751: // output_options_list: "output_options" $@128 ":" "[" output_options_list_content "]"
#line 2631 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4114 "dhcp4_parser.cc"
    break;

  case 754: // $@129: %empty
#line 2640 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4124 "dhcp4_parser.cc"
    break;

  case 755: // output_entry: "{" $@129 output_params_list "}"
#line 2644 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4132 "dhcp4_parser.cc"
    break;

  case 763: // $@130: %empty
#line 2659 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4141 "dhcp4_parser.cc"
    break;

  case 764: // output: "output" $@130 ":" "constant string"
#line 2662 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4151 "dhcp4_parser.cc"
    break;

  case 765: // flush: "flush" ":" "boolean"
#line 2668 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4161 "dhcp4_parser.cc"
    break;

  case 766: // maxsize: "maxsize" ":" "integer"
#line 2674 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4171 "dhcp4_parser.cc"
    break;

  case 767: // maxver: "maxver" ":" "integer"
#line 2680 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4181 "dhcp4_parser.cc"
    break;

  case 768: // $@131: %empty
#line 2686 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4190 "dhcp4_parser.cc"
    break;

  case 769: // pattern: "pattern" $@131 ":" "constant string"
#line 2689 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4200 "dhcp4_parser.cc"
    break;


#line 4204 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -942;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     615,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,    43,    41,    54,    82,   111,   139,
     141,   190,   192,   209,   245,   267,   271,   274,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,    41,  -161,    56,   112,    68,   601,
     203,   174,    16,    59,   115,  -102,   589,    27,  -942,   106,
     126,   118,   212,   269,  -942,   283,  -942,  -942,  -942,   289,
     290,   291,  -942,  -942,  -942,  -942,  -942,  -942,   304,   307,
     308,   314,   315,   317,   327,   328,   340,   347,   348,  -942,
     351,   355,   356,   367,   369,  -942,  -942,  -942,   370,   387,
     388,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   392,   393,
     394,  -942,  -942,  -942,  -942,  -942,   395,  -942,  -942,  -942,
    -942,  -942,  -942,   396,  -942,   402,  -942,    39,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,   404,  -942,    78,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,   405,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,    89,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,    97,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
     334,   412,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,   408,  -942,  -942,   414,  -942,  -942,
    -942,   415,  -942,  -942,   413,   420,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   425,
     426,  -942,  -942,  -942,  -942,   416,   428,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,    99,
    -942,  -942,  -942,   429,  -942,  -942,   431,  -942,   433,   435,
    -942,  -942,   436,   438,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,   107,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   439,
     122,  -942,  -942,  -942,  -942,    41,    41,  -942,   234,   440,
    -942,   441,   443,   449,   255,   257,   258,   456,   459,   465,
     466,   468,   471,   278,   280,   284,   285,   286,   279,   293,
     294,   295,   287,   292,   493,   302,   305,   298,   311,   312,
     501,   502,   505,   313,   316,   319,   512,   518,   520,   521,
     524,   527,   528,   329,   341,   344,   531,   542,   544,   545,
     546,   354,   551,   552,   553,   555,   557,   576,   380,   578,
    -942,   112,  -942,   583,   584,   585,   389,    68,  -942,   587,
     588,   590,   594,   595,   596,   403,   597,   600,   602,   601,
    -942,   603,   203,  -942,   604,   605,   606,   607,   608,   609,
     610,   611,  -942,   174,  -942,   614,   616,   427,   621,   628,
     629,   418,  -942,    59,   630,   434,   437,  -942,   115,   637,
     639,   -81,  -942,   444,   640,   642,   448,   644,   450,   451,
     647,   650,   458,   472,   656,   668,   670,   671,   589,  -942,
     681,   490,    27,  -942,  -942,  -942,   689,   586,   687,   692,
     693,  -942,  -942,  -942,   504,   511,   513,   703,   705,   533,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,   519,  -942,  -942,  -942,  -942,  -942,  -116,   522,   525,
    -942,  -942,  -942,   711,   714,   720,   721,   723,   529,   239,
    -942,  -942,  -942,   726,   728,   729,   730,   731,  -942,   732,
     733,   734,   735,   530,   538,  -942,   751,  -942,   752,   195,
     148,  -942,  -942,   539,   560,   561,   755,   563,   566,  -942,
     752,   567,   759,  -942,   569,  -942,   752,   570,   571,   572,
     573,   574,   575,   579,  -942,   580,   581,  -942,   582,   591,
     592,  -942,  -942,   593,  -942,  -942,  -942,   598,   723,  -942,
    -942,   599,   617,  -942,   618,  -942,  -942,    31,   613,  -942,
    -942,  -116,   619,   620,   622,  -942,   771,  -942,  -942,    41,
     112,    27,    68,   758,  -942,  -942,  -942,   526,   526,   776,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   777,
     778,   779,   781,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,   -50,   785,   786,   787,   199,   213,   135,   119,   589,
    -942,  -942,   788,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,   791,  -942,  -942,  -942,  -942,   101,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   776,  -942,
     125,   150,   151,  -942,   164,  -942,  -942,  -942,  -942,  -942,
    -942,   809,   810,   815,   817,   818,  -942,  -942,  -942,  -942,
     819,   820,  -942,   821,   822,   823,   824,  -942,   226,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,   241,  -942,   825,   826,  -942,  -942,   827,   829,  -942,
    -942,   828,   832,  -942,  -942,   830,   834,  -942,  -942,   833,
     835,  -942,  -942,  -942,  -942,  -942,  -942,    61,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,    76,  -942,  -942,   836,   837,
    -942,  -942,   838,   840,  -942,   841,   842,   843,   844,   845,
     846,   242,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   847,
     848,   849,  -942,   248,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,   252,  -942,  -942,  -942,   850,
    -942,   851,  -942,  -942,  -942,   256,  -942,  -942,  -942,  -942,
    -942,   259,  -942,   105,  -942,   632,  -942,   852,   853,  -942,
    -942,  -942,  -942,   854,   855,  -942,  -942,  -942,   856,   758,
    -942,   859,   860,   861,   862,   658,   666,   660,   667,   672,
     865,   866,   868,   869,   675,   676,   872,   678,   679,   680,
     683,   526,  -942,  -942,   526,  -942,   776,   601,  -942,   777,
      59,  -942,   778,   115,  -942,   779,   300,  -942,   781,   -50,
    -942,   534,   785,  -942,   174,  -942,   786,  -102,  -942,   787,
     685,   686,   696,   704,   709,   725,   199,  -942,   719,   739,
     742,   213,  -942,   875,   884,   135,  -942,   724,   900,   745,
     947,   119,  -942,  -942,   145,   788,  -942,  -942,   946,   956,
     203,  -942,   791,  1009,  -942,  -942,   643,  -942,   350,   762,
     831,   839,  -942,  -942,  -942,  -942,  -942,   857,   858,   863,
     864,  -942,  -942,   339,  -942,  -942,  -942,  -942,  -942,   265,
    -942,   272,  -942,  1007,  -942,  1008,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
     281,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  1013,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  1012,  1020,  -942,  -942,  -942,
    -942,  -942,  1016,  -942,   299,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,   867,   870,  -942,
    -942,   871,  -942,    41,  -942,  -942,  1021,  -942,  -942,  -942,
    -942,  -942,   306,  -942,  -942,  -942,  -942,  -942,  -942,   874,
     337,  -942,   752,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,   300,  -942,  1022,   873,  -942,   534,
    -942,  -942,  -942,  -942,  -942,  -942,  1023,   876,  1024,   145,
    -942,  -942,  -942,  -942,  -942,   878,  -942,  -942,  1025,  -942,
     879,  -942,  -942,  1026,  -942,  -942,   144,  -942,   -18,  1026,
    -942,  -942,  1027,  1028,  1030,  -942,   338,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  1031,   877,   880,   881,  1032,   -18,
    -942,   883,  -942,  -942,  -942,   885,  -942,  -942,  -942
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   175,     9,   339,    11,   539,    13,
     564,    15,   464,    17,   472,    19,   509,    21,   304,    23,
     673,    25,   723,    27,    45,    39,     0,     0,     0,     0,
       0,   566,     0,   474,   511,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   721,   164,   190,     0,
       0,     0,   585,   587,   589,   188,   197,   199,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
       0,     0,     0,     0,     0,   143,   150,   152,     0,     0,
       0,   331,   462,   501,   412,   552,   554,   405,     0,     0,
       0,   269,   613,   556,   296,   315,     0,   283,   642,   655,
     671,   156,   158,     0,   732,     0,   123,     0,    62,    64,
      65,    66,    67,    68,   102,   103,   104,   105,   106,    69,
      97,    86,    87,    88,   110,   111,   112,   113,   114,   115,
     116,   117,   108,   109,   118,   119,   120,   122,    72,    73,
      94,    74,    75,    76,   121,    80,    81,    70,    99,   100,
     101,    98,    71,    78,    79,    92,    93,    95,    89,    90,
      91,    77,    82,    83,    84,    85,    96,   107,   177,   179,
     183,     0,   174,     0,   166,   168,   169,   170,   171,   172,
     173,   390,   392,   394,   531,   388,   396,     0,   400,   398,
     609,   387,   343,   344,   345,   346,   347,   371,   372,   373,
     374,   375,   361,   362,   376,   377,   378,   379,   380,   381,
     382,   383,   384,   385,   386,     0,   341,   350,   366,   367,
     368,   351,   353,   354,   357,   358,   359,   356,   352,   348,
     349,   369,   370,   355,   363,   364,   365,   360,   550,   549,
     545,   546,   544,     0,   541,   543,   547,   548,   607,   595,
     597,   601,   599,   605,   603,   591,   584,   578,   582,   583,
       0,   567,   568,   579,   580,   581,   575,   570,   576,   572,
     573,   574,   577,   571,     0,   491,   244,     0,   495,   493,
     498,     0,   487,   488,     0,   475,   476,   478,   490,   479,
     480,   481,   497,   482,   483,   484,   485,   486,   525,     0,
       0,   523,   524,   527,   528,     0,   512,   513,   515,   516,
     517,   518,   519,   520,   521,   522,   311,   313,   308,     0,
     306,   309,   310,     0,   709,   696,     0,   699,     0,     0,
     703,   707,     0,     0,   713,   715,   717,   719,   694,   692,
     693,     0,   675,   677,   678,   679,   680,   681,   682,   683,
     684,   689,   685,   686,   687,   688,   690,   691,   729,     0,
       0,   725,   727,   728,    44,     0,     0,    37,     0,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,     0,    61,     0,     0,     0,     0,     0,   176,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     340,     0,     0,   540,     0,     0,     0,     0,     0,     0,
       0,     0,   565,     0,   465,     0,     0,     0,     0,     0,
       0,     0,   473,     0,     0,     0,     0,   510,     0,     0,
       0,     0,   305,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   674,
       0,     0,     0,   724,    48,    41,     0,     0,     0,     0,
       0,   137,   138,   139,     0,     0,     0,     0,     0,     0,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,     0,   161,   162,   140,   141,   142,     0,     0,     0,
     154,   155,   160,     0,     0,     0,     0,     0,     0,     0,
     402,   403,   404,     0,     0,     0,     0,     0,   641,     0,
       0,     0,     0,     0,     0,   163,     0,    63,     0,     0,
       0,   187,   167,     0,     0,     0,     0,     0,     0,   411,
       0,     0,     0,   342,     0,   542,     0,     0,     0,     0,
       0,     0,     0,     0,   569,     0,     0,   489,     0,     0,
       0,   500,   477,     0,   529,   530,   514,     0,     0,   307,
     695,     0,     0,   698,     0,   701,   702,     0,     0,   711,
     712,     0,     0,     0,     0,   676,     0,   731,   726,     0,
       0,     0,     0,     0,   586,   588,   590,     0,     0,   201,
     136,   145,   146,   147,   148,   149,   144,   151,   153,   333,
     466,   503,   414,    38,   553,   555,   407,   408,   409,   410,
     406,     0,     0,   558,   298,     0,     0,     0,     0,     0,
     157,   159,     0,    49,   178,   181,   182,   180,   185,   186,
     184,   391,   393,   395,   533,   389,   397,   401,   399,     0,
     551,   608,   596,   598,   602,   600,   606,   604,   592,   492,
     245,   496,   494,   499,   526,   312,   314,   710,   697,   700,
     705,   706,   704,   708,   714,   716,   718,   720,   201,    42,
       0,     0,     0,   195,     0,   192,   194,   231,   237,   239,
     241,     0,     0,     0,     0,     0,   253,   255,   257,   259,
       0,     0,   263,     0,     0,     0,     0,   230,     0,   207,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     223,   224,   225,   219,   226,   227,   228,   220,   221,   222,
     229,     0,   205,     0,   202,   203,   337,     0,   334,   335,
     470,     0,   467,   468,   507,     0,   504,   505,   418,     0,
     415,   416,   278,   279,   280,   281,   282,     0,   271,   273,
     274,   275,   276,   277,   617,     0,   615,   562,     0,   559,
     560,   302,     0,   299,   300,     0,     0,     0,     0,     0,
       0,     0,   317,   319,   320,   321,   322,   323,   324,     0,
       0,     0,   292,     0,   285,   287,   288,   289,   290,   291,
     651,   653,   650,   648,   649,     0,   644,   646,   647,     0,
     666,     0,   669,   662,   663,     0,   657,   659,   660,   661,
     664,     0,   736,     0,   734,    51,   537,     0,   534,   535,
     593,   611,   612,     0,     0,    59,   722,   165,     0,     0,
     191,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   189,   198,     0,   200,     0,     0,   332,     0,
     474,   463,     0,   511,   502,     0,     0,   413,     0,     0,
     270,   619,     0,   614,   566,   557,     0,     0,   297,     0,
       0,     0,     0,     0,     0,     0,     0,   316,     0,     0,
       0,     0,   284,     0,     0,     0,   643,     0,     0,     0,
       0,     0,   656,   672,     0,     0,   733,    53,     0,    52,
       0,   532,     0,     0,   610,   730,     0,   193,     0,     0,
       0,     0,   243,   246,   247,   248,   249,     0,     0,     0,
       0,   261,   262,     0,   250,   251,   252,   268,   208,     0,
     204,     0,   336,     0,   469,     0,   506,   461,   440,   441,
     442,   425,   426,   445,   446,   447,   448,   449,   428,   429,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   422,   423,   424,   438,   439,   435,   436,   437,   434,
       0,   420,   427,   443,   444,   430,   431,   432,   433,   417,
     272,   638,     0,   633,   634,   635,   636,   637,   626,   627,
     631,   632,   628,   629,   630,     0,   620,   621,   623,   624,
     625,   616,     0,   561,     0,   301,   325,   326,   327,   328,
     329,   330,   318,   293,   294,   295,   286,     0,     0,   645,
     665,     0,   668,     0,   658,   750,     0,   748,   746,   740,
     744,   745,     0,   738,   742,   743,   741,   735,    50,     0,
       0,   536,     0,   196,   233,   234,   235,   236,   232,   238,
     240,   242,   254,   256,   258,   260,   265,   266,   267,   264,
     206,   338,   471,   508,     0,   419,     0,     0,   618,     0,
     563,   303,   652,   654,   667,   670,     0,     0,     0,     0,
     737,    54,   538,   594,   421,     0,   640,   622,     0,   747,
       0,   739,   639,     0,   749,   754,     0,   752,     0,     0,
     751,   763,     0,     0,     0,   768,     0,   756,   758,   759,
     760,   761,   762,   753,     0,     0,     0,     0,     0,     0,
     755,     0,   765,   766,   767,     0,   757,   764,   769
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,   -52,  -942,  -554,  -942,   390,
    -942,  -942,  -942,  -942,  -942,  -942,  -599,  -942,  -942,  -942,
     -67,  -942,  -942,  -942,  -942,  -942,  -942,   371,   568,   -24,
       1,    11,   -40,   -28,    -1,    19,    22,    26,    29,  -942,
    -942,  -942,  -942,    30,    32,    34,    37,    40,    44,  -942,
     379,    45,  -942,    47,  -942,    48,    50,    51,  -942,    52,
    -942,    55,  -942,  -942,  -942,  -942,  -942,   372,   565,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,   124,  -942,  -942,  -942,  -942,
    -942,  -942,   288,  -942,   102,  -942,  -665,   104,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,   -63,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,    88,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,    69,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,    80,  -942,  -942,  -942,    84,   532,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,    81,  -942,  -942,  -942,  -942,  -942,
    -942,  -941,  -942,  -942,  -942,   103,  -942,  -942,  -942,   113,
     626,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -932,
    -942,   -65,  -942,    66,  -942,    58,    62,    63,    65,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,    96,  -942,  -942,  -106,
     -46,  -942,  -942,  -942,  -942,  -942,   121,  -942,  -942,  -942,
     109,  -942,   550,  -942,   -42,  -942,  -942,  -942,  -942,  -942,
     -36,  -942,  -942,  -942,  -942,  -942,   -35,  -942,  -942,  -942,
     127,  -942,  -942,  -942,   114,  -942,   577,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,    83,  -942,
    -942,  -942,    64,   612,  -942,  -942,   -51,  -942,   -11,  -942,
     -25,  -942,  -942,  -942,   120,  -942,  -942,  -942,   123,  -942,
     623,   -55,  -942,     0,  -942,     7,  -942,   359,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -928,  -942,  -942,  -942,  -942,
    -942,   108,  -942,  -942,  -942,   -85,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,   132,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,    98,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,   381,   554,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,  -942,
    -942,  -942,  -942,  -942,   422,   549,  -942,  -942,  -942,  -942,
    -942,  -942,   110,  -942,  -942,   -83,  -942,  -942,  -942,  -942,
    -942,  -942,  -105,  -942,  -942,  -121,  -942,  -942,  -942,  -942,
    -942,  -942,  -942
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   694,
      82,    83,    39,    64,    79,    80,   714,   905,   998,   999,
     787,    41,    66,    85,   409,    43,    67,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   434,   161,   162,   163,   164,   165,   166,   167,   440,
     686,   168,   441,   169,   442,   170,   171,   172,   466,   173,
     467,   174,   175,   176,   177,   178,   412,   213,   214,    45,
      68,   215,   473,   216,   474,   717,   217,   475,   720,   218,
     179,   420,   180,   413,   764,   765,   766,   918,   181,   421,
     182,   422,   813,   814,   815,   944,   788,   789,   790,   921,
    1148,   791,   922,   792,   923,   793,   924,   794,   795,   506,
     796,   797,   798,   799,   800,   801,   802,   803,   930,   804,
     931,   805,   932,   806,   933,   807,   808,   809,   936,  1159,
     810,   183,   456,   837,   838,   839,   840,   841,   842,   843,
     184,   462,   873,   874,   875,   876,   877,   185,   459,   852,
     853,   854,   967,    59,    75,   359,   360,   361,   519,   362,
     520,   186,   460,   861,   862,   863,   864,   865,   866,   867,
     868,   187,   446,   817,   818,   819,   947,    47,    69,   255,
     256,   257,   483,   258,   479,   259,   480,   260,   481,   261,
     484,   262,   487,   263,   486,   188,   189,   190,   191,   452,
     700,   268,   192,   449,   829,   830,   831,   956,  1070,  1071,
     193,   447,    53,    72,   821,   822,   823,   950,    55,    73,
     324,   325,   326,   327,   328,   329,   330,   505,   331,   509,
     332,   508,   333,   334,   510,   335,   194,   448,   825,   826,
     827,   953,    57,    74,   345,   346,   347,   348,   349,   514,
     350,   351,   352,   353,   270,   482,   907,   908,   909,  1000,
      49,    70,   283,   284,   285,   491,   195,   450,   196,   451,
     197,   458,   848,   849,   850,   964,    51,    71,   300,   301,
     302,   198,   417,   199,   418,   200,   419,   306,   501,   912,
    1003,   307,   495,   308,   496,   309,   498,   310,   497,   311,
     500,   312,   499,   313,   494,   277,   488,   913,   201,   457,
     845,   846,   961,  1095,  1096,  1097,  1098,  1099,  1166,  1100,
     202,   203,   463,   885,   886,   887,   983,   888,   984,   204,
     464,   895,   896,   897,   898,   988,   899,   900,   990,   205,
     465,    61,    76,   381,   382,   383,   384,   525,   385,   386,
     527,   387,   388,   389,   530,   752,   390,   531,   391,   524,
     392,   393,   394,   534,   395,   535,   396,   536,   397,   537,
     206,   411,    63,    77,   400,   401,   402,   540,   403,   207,
     469,   903,   904,   994,  1132,  1133,  1134,  1135,  1178,  1136,
    1176,  1196,  1197,  1198,  1206,  1207,  1208,  1214,  1209,  1210,
    1211,  1212,  1218
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     146,   212,   231,   279,   296,   280,   322,   341,   358,   378,
     323,   342,    78,   811,   274,  1062,   303,   219,   271,   286,
     298,   727,   336,   354,  1063,   379,   314,   731,  1078,   235,
     356,   357,   343,   693,   269,   282,   297,    81,   344,   398,
     399,   236,   471,    28,   273,   232,    29,   472,    30,   750,
      31,   356,   357,   681,   682,   683,   684,   220,   272,   287,
     299,    40,   337,   355,   959,   380,    84,   960,   237,   275,
     233,   304,   832,   833,   834,   835,   276,   836,   305,   962,
     234,   477,   963,   208,   209,   685,   478,   210,   238,    42,
     211,   239,   489,   315,   693,   240,   145,   490,   241,   242,
     492,   243,   521,   244,   122,   493,   245,   522,   995,   246,
     538,   996,   404,   247,   248,   539,   249,   250,    44,   251,
     252,   253,   406,    86,   254,   542,    87,   264,   471,   405,
     543,   265,   266,   915,   267,    88,   281,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    46,  1199,    48,   316,
    1200,   317,   318,   542,   477,   319,   320,   321,   916,   917,
    1201,   125,   126,  1202,  1203,  1204,  1205,   919,   718,   719,
     125,   126,   920,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,    50,   751,    52,
     122,   123,    92,    93,    94,   316,   338,   317,   318,   339,
     340,   124,   715,   716,   125,   126,    54,   125,   126,   127,
     407,   125,   126,  1062,   128,   129,   130,   131,   132,   941,
     295,   910,  1063,   133,   942,   316,  1078,   125,   126,    32,
      33,    34,    35,   134,   941,   976,   135,   125,   126,   943,
     977,   981,    56,   136,   137,   985,   982,   145,   138,   991,
     986,   139,   538,   123,   992,   140,   145,   993,   941,   889,
     890,   891,   408,  1160,    58,   489,   125,   126,    60,  1029,
    1161,    62,   880,   881,  1164,   141,   142,   143,   144,  1165,
     288,   410,   123,   414,   415,   416,   289,   290,   291,   292,
     293,   294,   521,   295,   278,   125,   126,  1171,   423,  1179,
     145,   424,   425,   145,  1180,   125,   126,   892,   426,   427,
     228,   428,  1125,   229,  1126,  1127,    90,    91,    92,    93,
      94,   429,   430,   145,   855,   856,   857,   858,   859,   860,
     492,  1219,   502,   145,   431,  1182,  1220,   696,   697,   698,
     699,   432,   433,   544,   545,   435,   869,   870,   871,   436,
     437,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   438,   145,   439,   443,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,  1144,  1145,  1146,  1147,   123,
     316,   444,   445,  1156,  1157,  1158,   453,   454,   455,   461,
     468,   145,   125,   126,   146,   226,   470,   127,   476,   485,
     212,   145,   128,   129,   130,   503,   504,   228,   507,   511,
     229,   512,   231,   513,   517,   279,   219,   280,   230,   515,
     516,   518,   546,   523,   274,   526,   296,   528,   271,   529,
     532,   286,   533,   541,   547,   548,   322,   549,   303,   235,
     323,   341,   298,   550,   269,   342,   551,   282,   552,   553,
     554,   236,   336,   555,   273,   232,   220,   354,   297,   556,
     557,   378,   558,   141,   142,   559,   343,   560,   272,   561,
     565,   287,   344,   562,   563,   564,   569,   379,   237,   275,
     233,   570,   299,   566,   567,   568,   276,   571,   145,   574,
     234,   572,   337,   304,   573,   577,   578,   355,   238,   579,
     305,   239,   575,   576,   580,   240,   583,   581,   241,   242,
     582,   243,   584,   244,   585,   586,   245,   380,   587,   246,
     590,   588,   589,   247,   248,   593,   249,   250,   679,   251,
     252,   253,   591,  1183,   254,   592,   594,   264,   595,   596,
     597,   265,   266,   598,   267,   599,   600,   601,   281,   602,
     767,   603,    92,    93,    94,   768,   769,   770,   771,   772,
     773,   774,   775,   776,   777,   778,   779,   780,   781,   782,
     604,   605,   606,   783,   784,   785,   786,   608,   609,   610,
     611,   613,   614,   670,   615,    98,    99,   100,   616,   617,
     618,   620,   619,   146,   621,   212,   622,   624,   626,   627,
     628,   629,   630,   631,   632,   633,   316,   759,   635,   641,
     636,   219,   122,   123,   316,   638,   637,    90,    91,    92,
      93,    94,   639,   640,   643,   644,   125,   126,   645,   872,
     882,   647,   378,   648,   651,   650,   652,   653,   654,   655,
     656,   657,  1081,  1082,   658,   878,   883,   893,   379,   659,
     661,   220,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   662,   660,   663,   664,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   666,   221,   222,   223,   667,
     123,   125,   126,   669,   671,   879,   884,   894,   380,   672,
     673,   224,   674,   125,   126,   225,   226,   227,   127,   675,
     677,   676,   678,   128,   129,   130,   689,   680,   228,   690,
     687,   229,   133,   688,   145,   691,   692,   695,   710,   230,
      30,   701,   145,   702,   703,   704,   711,   721,   705,   706,
     707,   708,   709,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   712,   713,   722,   723,
     724,   725,   376,   377,   726,   728,   729,   730,   732,   733,
     734,   735,   736,   737,   141,   142,   758,   738,   739,   740,
     741,   753,   763,   812,   816,   820,   824,   145,   828,   742,
     743,   744,   844,   847,   851,   902,   745,   747,   906,   145,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   925,   926,   748,   749,   755,   756,   927,
     757,   928,   929,   934,   935,   937,   938,   939,   940,   946,
     997,   945,   949,   948,   951,   952,   954,   955,   958,   957,
     966,  1143,   965,   969,   968,   970,   971,   972,   973,   974,
     975,   978,   979,   980,   987,   989,  1002,  1012,  1001,  1014,
    1006,  1005,  1004,  1008,  1009,  1010,  1011,  1013,  1015,  1017,
    1018,  1016,  1019,  1020,  1021,  1022,  1023,  1024,  1025,  1117,
     231,  1026,  1027,   322,  1106,  1107,   341,   323,  1118,  1037,
     342,  1064,   274,  1061,  1083,  1108,   271,   296,  1087,   336,
     358,  1075,   354,  1109,  1121,  1073,  1092,   235,  1110,   303,
    1090,   343,   269,   298,   872,  1088,  1041,   344,   882,   236,
    1113,  1072,   273,   232,  1111,  1120,  1089,  1128,  1042,   297,
     878,  1129,  1038,   279,   883,   280,   272,  1084,  1114,   337,
     893,  1115,   355,  1130,  1122,  1074,   237,   275,   233,   286,
    1091,  1123,  1138,   299,   276,  1043,  1076,  1039,   234,  1139,
    1149,  1093,  1085,  1077,   304,   282,   238,  1040,  1094,   239,
     879,   305,  1086,   240,   884,  1044,   241,   242,  1045,   243,
     894,   244,  1046,  1131,   245,  1047,  1048,   246,  1049,   287,
    1050,   247,   248,  1051,   249,   250,  1052,   251,   252,   253,
    1053,  1054,   254,  1055,  1056,   264,  1057,  1058,  1059,   265,
     266,  1060,   267,  1142,  1066,  1162,  1163,  1167,  1067,  1068,
    1168,  1069,  1065,  1169,  1170,  1177,  1185,  1188,  1190,  1150,
    1193,  1215,  1216,  1195,  1217,  1221,  1225,  1151,   746,   607,
     754,   760,   612,  1007,   762,  1028,   914,  1080,  1030,  1105,
    1116,  1104,  1032,   649,  1079,  1152,  1153,  1112,  1184,  1033,
    1031,  1154,  1155,   642,  1140,  1172,   281,  1035,  1173,  1174,
    1101,  1175,  1181,  1034,  1186,  1189,  1192,  1194,  1222,  1223,
    1224,  1227,  1036,  1228,  1187,  1141,  1103,  1102,   911,  1124,
     901,   668,   665,   761,  1213,   646,  1191,  1037,  1226,  1064,
       0,  1061,  1083,     0,   625,  1137,  1087,     0,     0,  1075,
       0,     0,  1128,  1073,  1092,   623,  1129,  1119,  1090,     0,
       0,     0,     0,  1088,  1041,     0,   634,     0,  1130,  1072,
       0,     0,     0,     0,  1089,     0,  1042,     0,     0,     0,
    1038,     0,     0,     0,     0,  1084,     0,     0,     0,     0,
       0,     0,     0,  1074,     0,     0,     0,     0,  1091,     0,
       0,     0,     0,  1043,  1076,  1039,     0,     0,  1131,  1093,
    1085,  1077,     0,     0,     0,  1040,  1094,     0,     0,     0,
    1086,     0,     0,  1044,     0,     0,  1045,     0,     0,     0,
    1046,     0,     0,  1047,  1048,     0,  1049,     0,  1050,     0,
       0,  1051,     0,     0,  1052,     0,     0,     0,  1053,  1054,
       0,  1055,  1056,     0,  1057,  1058,  1059,     0,     0,  1060,
       0,     0,  1066,     0,     0,     0,  1067,  1068,     0,  1069,
    1065
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   678,    69,   956,    71,    68,    69,    70,
      71,   620,    73,    74,   956,    76,    72,   626,   956,    69,
     132,   133,    74,   587,    69,    70,    71,   198,    74,    12,
      13,    69,     3,     0,    69,    69,     5,     8,     7,    18,
       9,   132,   133,   169,   170,   171,   172,    68,    69,    70,
      71,     7,    73,    74,     3,    76,    10,     6,    69,    69,
      69,    71,   122,   123,   124,   125,    69,   127,    71,     3,
      69,     3,     6,    15,    16,   201,     8,    19,    69,     7,
      22,    69,     3,    34,   648,    69,   198,     8,    69,    69,
       3,    69,     3,    69,    88,     8,    69,     8,     3,    69,
       3,     6,     6,    69,    69,     8,    69,    69,     7,    69,
      69,    69,     4,    11,    69,     3,    14,    69,     3,     3,
       8,    69,    69,     8,    69,    23,    70,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     7,     3,     7,    90,
       6,    92,    93,     3,     3,    96,    97,    98,     8,     8,
     178,   102,   103,   181,   182,   183,   184,     3,    20,    21,
     102,   103,     8,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,     7,   167,     7,
      88,    89,    28,    29,    30,    90,    91,    92,    93,    94,
      95,    99,    17,    18,   102,   103,     7,   102,   103,   107,
       8,   102,   103,  1164,   112,   113,   114,   115,   116,     3,
     129,   130,  1164,   121,     8,    90,  1164,   102,   103,   198,
     199,   200,   201,   131,     3,     3,   134,   102,   103,     8,
       8,     3,     7,   141,   142,     3,     8,   198,   146,     3,
       8,   149,     3,    89,     8,   153,   198,     8,     3,   150,
     151,   152,     3,     8,     7,     3,   102,   103,     7,   944,
       8,     7,   147,   148,     3,   173,   174,   175,   176,     8,
     116,     8,    89,     4,     4,     4,   122,   123,   124,   125,
     126,   127,     3,   129,   101,   102,   103,     8,     4,     3,
     198,     4,     4,   198,     8,   102,   103,   198,     4,     4,
     117,     4,   177,   120,   179,   180,    26,    27,    28,    29,
      30,     4,     4,   198,   135,   136,   137,   138,   139,   140,
       3,     3,     8,   198,     4,     8,     8,   108,   109,   110,
     111,     4,     4,   405,   406,     4,   143,   144,   145,     4,
       4,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,     4,   198,     4,     4,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    35,    36,    37,    38,    89,
      90,     4,     4,    54,    55,    56,     4,     4,     4,     4,
       4,   198,   102,   103,   471,   105,     4,   107,     4,     4,
     477,   198,   112,   113,   114,     3,     8,   117,     4,     4,
     120,     8,   489,     3,     8,   492,   477,   492,   128,     4,
       4,     3,   198,     4,   489,     4,   503,     4,   489,     4,
       4,   492,     4,     4,     4,     4,   513,     4,   503,   489,
     513,   518,   503,     4,   489,   518,   201,   492,   201,   201,
       4,   489,   513,     4,   489,   489,   477,   518,   503,     4,
       4,   538,     4,   173,   174,     4,   518,   199,   489,   199,
     201,   492,   518,   199,   199,   199,   199,   538,   489,   489,
     489,   199,   503,   200,   200,   200,   489,     4,   198,   201,
     489,   199,   513,   503,   199,     4,     4,   518,   489,     4,
     503,   489,   201,   201,   201,   489,     4,   201,   489,   489,
     201,   489,     4,   489,     4,     4,   489,   538,     4,   489,
     201,     4,     4,   489,   489,     4,   489,   489,     5,   489,
     489,   489,   201,  1142,   489,   201,     4,   489,     4,     4,
       4,   489,   489,   199,   489,     4,     4,     4,   492,     4,
      34,     4,    28,    29,    30,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
       4,   201,     4,    57,    58,    59,    60,     4,     4,     4,
     201,     4,     4,     7,     4,    61,    62,    63,     4,     4,
       4,     4,   199,   670,     4,   672,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,    90,   669,     4,   201,
       4,   672,    88,    89,    90,     4,   199,    26,    27,    28,
      29,    30,     4,     4,     4,   201,   102,   103,   201,   706,
     707,     4,   709,     4,     4,   201,     4,   199,     4,   199,
     199,     4,   118,   119,     4,   706,   707,   708,   709,   201,
       4,   672,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,     4,   201,     4,     4,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     4,    85,    86,    87,   199,
      89,   102,   103,     4,     7,   706,   707,   708,   709,     7,
       7,   100,   198,   102,   103,   104,   105,   106,   107,   198,
       7,   198,     7,   112,   113,   114,     5,   198,   117,     5,
     198,   120,   121,   198,   198,     5,     5,   198,   198,   128,
       7,     5,   198,     5,     5,     5,   198,   198,     7,     7,
       7,     7,     7,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,     5,     5,   198,   198,
       5,   198,   173,   174,   198,   198,     7,   198,   198,   198,
     198,   198,   198,   198,   173,   174,     5,   198,   198,   198,
     198,   168,    24,     7,     7,     7,     7,   198,     7,   198,
     198,   198,     7,     7,     7,     7,   198,   198,     7,   198,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,     4,     4,   198,   198,   198,   198,     4,
     198,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     198,     6,     3,     6,     6,     3,     6,     3,     3,     6,
       3,   198,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     3,   199,     6,   199,
       4,     6,     8,     4,     4,     4,     4,   201,   201,     4,
       4,   199,     4,     4,   199,   199,     4,   199,   199,     4,
     947,   201,   199,   950,   199,   199,   953,   950,     4,   956,
     953,   956,   947,   956,   961,   199,   947,   964,   961,   950,
     967,   956,   953,   199,     4,   956,   961,   947,   199,   964,
     961,   953,   947,   964,   981,   961,   956,   953,   985,   947,
     201,   956,   947,   947,   199,   201,   961,   994,   956,   964,
     981,   994,   956,  1000,   985,  1000,   947,   961,   199,   950,
     991,   199,   953,   994,   199,   956,   947,   947,   947,  1000,
     961,     4,     6,   964,   947,   956,   956,   956,   947,     3,
     198,   961,   961,   956,   964,  1000,   947,   956,   961,   947,
     981,   964,   961,   947,   985,   956,   947,   947,   956,   947,
     991,   947,   956,   994,   947,   956,   956,   947,   956,  1000,
     956,   947,   947,   956,   947,   947,   956,   947,   947,   947,
     956,   956,   947,   956,   956,   947,   956,   956,   956,   947,
     947,   956,   947,     4,   956,     8,     8,     4,   956,   956,
       8,   956,   956,     3,     8,     4,     4,     4,     4,   198,
       5,     4,     4,     7,     4,     4,     4,   198,   648,   471,
     661,   670,   477,   919,   672,   941,   758,   959,   946,   969,
     981,   967,   949,   521,   958,   198,   198,   976,  1164,   950,
     947,   198,   198,   513,  1000,   198,  1000,   953,   198,   198,
     962,  1123,   198,   952,   201,   199,   198,   198,   201,   199,
     199,   198,   955,   198,  1169,  1002,   966,   964,   729,   991,
     709,   542,   538,   671,  1199,   518,  1179,  1164,  1219,  1164,
      -1,  1164,  1169,    -1,   492,   995,  1169,    -1,    -1,  1164,
      -1,    -1,  1179,  1164,  1169,   489,  1179,   985,  1169,    -1,
      -1,    -1,    -1,  1169,  1164,    -1,   503,    -1,  1179,  1164,
      -1,    -1,    -1,    -1,  1169,    -1,  1164,    -1,    -1,    -1,
    1164,    -1,    -1,    -1,    -1,  1169,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1164,    -1,    -1,    -1,    -1,  1169,    -1,
      -1,    -1,    -1,  1164,  1164,  1164,    -1,    -1,  1179,  1169,
    1169,  1164,    -1,    -1,    -1,  1164,  1169,    -1,    -1,    -1,
    1169,    -1,    -1,  1164,    -1,    -1,  1164,    -1,    -1,    -1,
    1164,    -1,    -1,  1164,  1164,    -1,  1164,    -1,  1164,    -1,
      -1,  1164,    -1,    -1,  1164,    -1,    -1,    -1,  1164,  1164,
      -1,  1164,  1164,    -1,  1164,  1164,  1164,    -1,    -1,  1164,
      -1,    -1,  1164,    -1,    -1,    -1,  1164,  1164,    -1,  1164,
    1164
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,     0,     5,
       7,     9,   198,   199,   200,   201,   217,   218,   219,   224,
       7,   233,     7,   237,     7,   281,     7,   389,     7,   472,
       7,   488,     7,   424,     7,   430,     7,   454,     7,   365,
       7,   553,     7,   584,   225,   220,   234,   238,   282,   390,
     473,   489,   425,   431,   455,   366,   554,   585,   217,   226,
     227,   198,   222,   223,    10,   235,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    88,    89,    99,   102,   103,   107,   112,   113,
     114,   115,   116,   121,   131,   134,   141,   142,   146,   149,
     153,   173,   174,   175,   176,   198,   232,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   254,   255,   256,   257,   258,   259,   260,   263,   265,
     267,   268,   269,   271,   273,   274,   275,   276,   277,   292,
     294,   300,   302,   343,   352,   359,   373,   383,   407,   408,
     409,   410,   414,   422,   448,   478,   480,   482,   493,   495,
     497,   520,   532,   533,   541,   551,   582,   591,    15,    16,
      19,    22,   232,   279,   280,   283,   285,   288,   291,   478,
     480,    85,    86,    87,   100,   104,   105,   106,   117,   120,
     128,   232,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   255,   256,   257,   258,   259,   260,   263,   265,
     267,   268,   269,   271,   273,   391,   392,   393,   395,   397,
     399,   401,   403,   405,   407,   408,   409,   410,   413,   448,
     466,   478,   480,   482,   493,   495,   497,   517,   101,   232,
     403,   405,   448,   474,   475,   476,   478,   480,   116,   122,
     123,   124,   125,   126,   127,   129,   232,   448,   478,   480,
     490,   491,   492,   493,   495,   497,   499,   503,   505,   507,
     509,   511,   513,   515,   422,    34,    90,    92,    93,    96,
      97,    98,   232,   320,   432,   433,   434,   435,   436,   437,
     438,   440,   442,   444,   445,   447,   478,   480,    91,    94,
      95,   232,   320,   436,   442,   456,   457,   458,   459,   460,
     462,   463,   464,   465,   478,   480,   132,   133,   232,   367,
     368,   369,   371,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   173,   174,   232,   478,
     480,   555,   556,   557,   558,   560,   561,   563,   564,   565,
     568,   570,   572,   573,   574,   576,   578,   580,    12,    13,
     586,   587,   588,   590,     6,     3,     4,     8,     3,   236,
       8,   583,   278,   295,     4,     4,     4,   494,   496,   498,
     293,   301,   303,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   253,     4,     4,     4,     4,     4,
     261,   264,   266,     4,     4,     4,   384,   423,   449,   415,
     479,   481,   411,     4,     4,     4,   344,   521,   483,   360,
     374,     4,   353,   534,   542,   552,   270,   272,     4,   592,
       4,     3,     8,   284,   286,   289,     4,     3,     8,   396,
     398,   400,   467,   394,   402,     4,   406,   404,   518,     3,
       8,   477,     3,     8,   516,   504,   506,   510,   508,   514,
     512,   500,     8,     3,     8,   439,   321,     4,   443,   441,
     446,     4,     8,     3,   461,     4,     4,     8,     3,   370,
     372,     3,     8,     4,   571,   559,     4,   562,     4,     4,
     566,   569,     4,     4,   575,   577,   579,   581,     3,     8,
     589,     4,     3,     8,   217,   217,   198,     4,     4,     4,
       4,   201,   201,   201,     4,     4,     4,     4,     4,     4,
     199,   199,   199,   199,   199,   201,   200,   200,   200,   199,
     199,     4,   199,   199,   201,   201,   201,     4,     4,     4,
     201,   201,   201,     4,     4,     4,     4,     4,     4,     4,
     201,   201,   201,     4,     4,     4,     4,     4,   199,     4,
       4,     4,     4,     4,     4,   201,     4,   240,     4,     4,
       4,   201,   280,     4,     4,     4,     4,     4,     4,   199,
       4,     4,     4,   392,     4,   475,     4,     4,     4,     4,
       4,     4,     4,     4,   492,     4,     4,   199,     4,     4,
       4,   201,   434,     4,   201,   201,   458,     4,     4,   368,
     201,     4,     4,   199,     4,   199,   199,     4,     4,   201,
     201,     4,     4,     4,     4,   556,     4,   199,   587,     4,
       7,     7,     7,     7,   198,   198,   198,     7,     7,     5,
     198,   169,   170,   171,   172,   201,   262,   198,   198,     5,
       5,     5,     5,   219,   221,   198,   108,   109,   110,   111,
     412,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     198,   198,     5,     5,   228,    17,    18,   287,    20,    21,
     290,   198,   198,   198,     5,   198,   198,   228,   198,     7,
     198,   228,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   221,   198,   198,   198,
      18,   167,   567,   168,   262,   198,   198,   198,     5,   217,
     239,   586,   279,    24,   296,   297,   298,    34,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    57,    58,    59,    60,   232,   308,   309,
     310,   313,   315,   317,   319,   320,   322,   323,   324,   325,
     326,   327,   328,   329,   331,   333,   335,   337,   338,   339,
     342,   308,     7,   304,   305,   306,     7,   385,   386,   387,
       7,   426,   427,   428,     7,   450,   451,   452,     7,   416,
     417,   418,   122,   123,   124,   125,   127,   345,   346,   347,
     348,   349,   350,   351,     7,   522,   523,     7,   484,   485,
     486,     7,   361,   362,   363,   135,   136,   137,   138,   139,
     140,   375,   376,   377,   378,   379,   380,   381,   382,   143,
     144,   145,   232,   354,   355,   356,   357,   358,   478,   480,
     147,   148,   232,   478,   480,   535,   536,   537,   539,   150,
     151,   152,   198,   478,   480,   543,   544,   545,   546,   548,
     549,   555,     7,   593,   594,   229,     7,   468,   469,   470,
     130,   499,   501,   519,   304,     8,     8,     8,   299,     3,
       8,   311,   314,   316,   318,     4,     4,     4,     4,     4,
     330,   332,   334,   336,     4,     4,   340,     4,     4,     4,
       4,     3,     8,     8,   307,     6,     3,   388,     6,     3,
     429,     6,     3,   453,     6,     3,   419,     6,     3,     3,
       6,   524,     3,     6,   487,     6,     3,   364,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   538,   540,     3,     8,     4,   547,     4,
     550,     3,     8,     8,   595,     3,     6,   198,   230,   231,
     471,     6,     3,   502,     8,     6,     4,   297,     4,     4,
       4,     4,   199,   201,   199,   201,   199,     4,     4,     4,
       4,   199,   199,     4,   199,   199,   201,   199,   309,   308,
     306,   391,   387,   432,   428,   456,   452,   232,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   255,   256,
     257,   258,   259,   260,   263,   265,   267,   268,   269,   271,
     273,   320,   383,   401,   403,   405,   407,   408,   409,   410,
     420,   421,   448,   478,   480,   493,   495,   497,   517,   418,
     346,   118,   119,   232,   241,   242,   243,   320,   422,   448,
     478,   480,   493,   495,   497,   525,   526,   527,   528,   529,
     531,   523,   490,   486,   367,   363,   199,   199,   199,   199,
     199,   199,   376,   201,   199,   199,   355,     4,     4,   536,
     201,     4,   199,     4,   544,   177,   179,   180,   232,   320,
     478,   480,   596,   597,   598,   599,   601,   594,     6,     3,
     474,   470,     4,   198,    35,    36,    37,    38,   312,   198,
     198,   198,   198,   198,   198,   198,    54,    55,    56,   341,
       8,     8,     8,     8,     3,     8,   530,     4,     8,     3,
       8,     8,   198,   198,   198,   217,   602,     4,   600,     3,
       8,   198,     8,   228,   421,     4,   201,   527,     4,   199,
       4,   597,   198,     5,   198,     7,   603,   604,   605,     3,
       6,   178,   181,   182,   183,   184,   606,   607,   608,   610,
     611,   612,   613,   604,   609,     4,     4,     4,   614,     3,
       8,     4,   201,   199,   199,     4,   607,   198,   198
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   202,   204,   203,   205,   203,   206,   203,   207,   203,
     208,   203,   209,   203,   210,   203,   211,   203,   212,   203,
     213,   203,   214,   203,   215,   203,   216,   203,   217,   217,
     217,   217,   217,   217,   217,   218,   220,   219,   221,   222,
     222,   223,   223,   225,   224,   226,   226,   227,   227,   229,
     228,   230,   230,   231,   231,   232,   234,   233,   236,   235,
     238,   237,   239,   239,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   253,   252,   254,   255,   256,
     257,   258,   259,   261,   260,   262,   262,   262,   262,   262,
     264,   263,   266,   265,   267,   268,   270,   269,   272,   271,
     273,   274,   275,   276,   278,   277,   279,   279,   280,   280,
     280,   280,   280,   280,   280,   282,   281,   284,   283,   286,
     285,   287,   287,   289,   288,   290,   290,   291,   293,   292,
     295,   294,   296,   296,   297,   299,   298,   301,   300,   303,
     302,   304,   304,   305,   305,   307,   306,   308,   308,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   311,   310,   312,   312,   312,   312,   314,   313,   316,
     315,   318,   317,   319,   321,   320,   322,   323,   324,   325,
     326,   327,   328,   330,   329,   332,   331,   334,   333,   336,
     335,   337,   338,   340,   339,   341,   341,   341,   342,   344,
     343,   345,   345,   346,   346,   346,   346,   346,   347,   348,
     349,   350,   351,   353,   352,   354,   354,   355,   355,   355,
     355,   355,   355,   356,   357,   358,   360,   359,   361,   361,
     362,   362,   364,   363,   366,   365,   367,   367,   367,   368,
     368,   370,   369,   372,   371,   374,   373,   375,   375,   376,
     376,   376,   376,   376,   376,   377,   378,   379,   380,   381,
     382,   384,   383,   385,   385,   386,   386,   388,   387,   390,
     389,   391,   391,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   394,   393,
     396,   395,   398,   397,   400,   399,   402,   401,   404,   403,
     406,   405,   407,   408,   409,   411,   410,   412,   412,   412,
     412,   413,   415,   414,   416,   416,   417,   417,   419,   418,
     420,   420,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   421,   421,   421,   421,   421,   421,   421,   421,
     421,   421,   423,   422,   425,   424,   426,   426,   427,   427,
     429,   428,   431,   430,   432,   432,   433,   433,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   435,   436,
     437,   439,   438,   441,   440,   443,   442,   444,   446,   445,
     447,   449,   448,   450,   450,   451,   451,   453,   452,   455,
     454,   456,   456,   457,   457,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   459,   461,   460,   462,   463,   464,
     465,   467,   466,   468,   468,   469,   469,   471,   470,   473,
     472,   474,   474,   475,   475,   475,   475,   475,   475,   475,
     477,   476,   479,   478,   481,   480,   483,   482,   484,   484,
     485,   485,   487,   486,   489,   488,   490,   490,   491,   491,
     492,   492,   492,   492,   492,   492,   492,   492,   492,   492,
     492,   492,   492,   492,   492,   494,   493,   496,   495,   498,
     497,   500,   499,   502,   501,   504,   503,   506,   505,   508,
     507,   510,   509,   512,   511,   514,   513,   516,   515,   518,
     517,   519,   519,   521,   520,   522,   522,   524,   523,   525,
     525,   526,   526,   527,   527,   527,   527,   527,   527,   527,
     527,   527,   527,   527,   527,   527,   527,   528,   530,   529,
     531,   532,   534,   533,   535,   535,   536,   536,   536,   536,
     536,   538,   537,   540,   539,   542,   541,   543,   543,   544,
     544,   544,   544,   544,   544,   545,   547,   546,   548,   550,
     549,   552,   551,   554,   553,   555,   555,   556,   556,   556,
     556,   556,   556,   556,   556,   556,   556,   556,   556,   556,
     556,   556,   556,   556,   556,   557,   559,   558,   560,   562,
     561,   563,   564,   566,   565,   567,   567,   569,   568,   571,
     570,   572,   573,   575,   574,   577,   576,   579,   578,   581,
     580,   583,   582,   585,   584,   586,   586,   587,   587,   589,
     588,   590,   592,   591,   593,   593,   595,   594,   596,   596,
     597,   597,   597,   597,   597,   597,   597,   598,   600,   599,
     602,   601,   603,   603,   605,   604,   606,   606,   607,   607,
     607,   607,   607,   609,   608,   610,   611,   612,   614,   613
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
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     4,     0,     4,
       3,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     6,     1,     3,     1,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     0,     4,     1,     1,     1,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     1,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     4,     3,     0,
       4,     3,     3,     0,     4,     1,     1,     0,     4,     0,
       4,     3,     3,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     0,
       6,     3,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     0,     4
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
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"id\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"reservations-global\"",
  "\"reservations-in-subnet\"", "\"reservations-out-of-pool\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
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
  "\"ip-reservations-unique\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
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
  "global_object", "$@18", "sub_dhcp4", "$@19", "global_params",
  "global_param", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "server_tag", "$@20",
  "echo_client_id", "match_client_id", "authoritative",
  "ddns_send_updates", "ddns_override_no_update",
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
  "maxsize", "maxver", "pattern", "$@131", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   290,   290,   290,   291,   291,   292,   292,   293,   293,
     294,   294,   295,   295,   296,   296,   297,   297,   298,   298,
     299,   299,   300,   300,   301,   301,   302,   302,   310,   311,
     312,   313,   314,   315,   316,   319,   324,   324,   335,   338,
     339,   342,   347,   355,   355,   362,   363,   366,   370,   377,
     377,   384,   385,   388,   392,   403,   412,   412,   427,   427,
     444,   444,   453,   454,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   521,   527,   533,   539,   545,   551,
     557,   563,   569,   575,   581,   587,   587,   596,   602,   608,
     614,   620,   626,   632,   632,   641,   644,   647,   650,   653,
     659,   659,   668,   668,   677,   683,   689,   689,   698,   698,
     707,   713,   719,   725,   731,   731,   743,   744,   747,   748,
     749,   750,   751,   752,   753,   756,   756,   765,   765,   776,
     776,   784,   785,   788,   788,   796,   798,   802,   809,   809,
     822,   822,   833,   834,   836,   838,   838,   857,   857,   870,
     870,   881,   882,   885,   886,   889,   889,   899,   900,   903,
     904,   905,   906,   907,   908,   909,   910,   911,   912,   913,
     914,   915,   916,   917,   918,   919,   920,   921,   922,   923,
     924,   927,   927,   935,   936,   937,   938,   941,   941,   950,
     950,   959,   959,   968,   974,   974,   983,   989,   995,  1001,
    1007,  1013,  1019,  1025,  1025,  1034,  1034,  1043,  1043,  1052,
    1052,  1061,  1067,  1073,  1073,  1081,  1082,  1083,  1086,  1093,
    1093,  1104,  1105,  1108,  1109,  1110,  1111,  1112,  1115,  1120,
    1125,  1130,  1135,  1142,  1142,  1155,  1156,  1159,  1160,  1161,
    1162,  1163,  1164,  1167,  1173,  1179,  1185,  1185,  1196,  1197,
    1200,  1201,  1204,  1204,  1214,  1214,  1224,  1225,  1226,  1229,
    1230,  1233,  1233,  1242,  1242,  1251,  1251,  1263,  1264,  1267,
    1268,  1269,  1270,  1271,  1272,  1275,  1281,  1287,  1293,  1299,
    1305,  1314,  1314,  1328,  1329,  1332,  1333,  1340,  1340,  1366,
    1366,  1377,  1378,  1382,  1383,  1384,  1385,  1386,  1387,  1388,
    1389,  1390,  1391,  1392,  1393,  1394,  1395,  1396,  1397,  1398,
    1399,  1400,  1401,  1402,  1403,  1404,  1405,  1406,  1407,  1408,
    1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,  1418,
    1419,  1420,  1421,  1422,  1423,  1424,  1425,  1426,  1429,  1429,
    1438,  1438,  1447,  1447,  1456,  1456,  1465,  1465,  1474,  1474,
    1483,  1483,  1494,  1500,  1506,  1512,  1512,  1520,  1521,  1522,
    1523,  1526,  1534,  1534,  1546,  1547,  1551,  1552,  1555,  1555,
    1563,  1564,  1567,  1568,  1569,  1570,  1571,  1572,  1573,  1574,
    1575,  1576,  1577,  1578,  1579,  1580,  1581,  1582,  1583,  1584,
    1585,  1586,  1587,  1588,  1589,  1590,  1591,  1592,  1593,  1594,
    1595,  1596,  1597,  1598,  1599,  1600,  1601,  1602,  1603,  1604,
    1605,  1606,  1613,  1613,  1627,  1627,  1636,  1637,  1640,  1641,
    1646,  1646,  1661,  1661,  1675,  1676,  1679,  1680,  1683,  1684,
    1685,  1686,  1687,  1688,  1689,  1690,  1691,  1692,  1695,  1697,
    1703,  1705,  1705,  1714,  1714,  1723,  1723,  1732,  1734,  1734,
    1743,  1753,  1753,  1766,  1767,  1772,  1773,  1778,  1778,  1790,
    1790,  1802,  1803,  1808,  1809,  1814,  1815,  1816,  1817,  1818,
    1819,  1820,  1821,  1822,  1825,  1827,  1827,  1836,  1838,  1840,
    1846,  1855,  1855,  1868,  1869,  1872,  1873,  1876,  1876,  1886,
    1886,  1896,  1897,  1900,  1901,  1902,  1903,  1904,  1905,  1906,
    1909,  1909,  1918,  1918,  1943,  1943,  1973,  1973,  1984,  1985,
    1988,  1989,  1992,  1992,  2001,  2001,  2010,  2011,  2014,  2015,
    2019,  2020,  2021,  2022,  2023,  2024,  2025,  2026,  2027,  2028,
    2029,  2030,  2031,  2032,  2033,  2036,  2036,  2045,  2045,  2054,
    2054,  2063,  2063,  2072,  2072,  2083,  2083,  2092,  2092,  2101,
    2101,  2110,  2110,  2119,  2119,  2128,  2128,  2137,  2137,  2151,
    2151,  2162,  2163,  2169,  2169,  2180,  2181,  2184,  2184,  2194,
    2195,  2198,  2199,  2202,  2203,  2204,  2205,  2206,  2207,  2208,
    2209,  2210,  2211,  2212,  2213,  2214,  2215,  2218,  2220,  2220,
    2229,  2237,  2245,  2245,  2256,  2257,  2260,  2261,  2262,  2263,
    2264,  2267,  2267,  2276,  2276,  2288,  2288,  2301,  2302,  2305,
    2306,  2307,  2308,  2309,  2310,  2313,  2319,  2319,  2328,  2334,
    2334,  2344,  2344,  2357,  2357,  2367,  2368,  2371,  2372,  2373,
    2374,  2375,  2376,  2377,  2378,  2379,  2380,  2381,  2382,  2383,
    2384,  2385,  2386,  2387,  2388,  2391,  2397,  2397,  2406,  2412,
    2412,  2421,  2427,  2433,  2433,  2442,  2443,  2446,  2446,  2456,
    2456,  2466,  2473,  2480,  2480,  2489,  2489,  2499,  2499,  2509,
    2509,  2521,  2521,  2533,  2533,  2543,  2544,  2548,  2549,  2552,
    2552,  2563,  2571,  2571,  2584,  2585,  2589,  2589,  2597,  2598,
    2601,  2602,  2603,  2604,  2605,  2606,  2607,  2610,  2616,  2616,
    2625,  2625,  2636,  2637,  2640,  2640,  2648,  2649,  2652,  2653,
    2654,  2655,  2656,  2659,  2659,  2668,  2674,  2680,  2686,  2686
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
#line 5746 "dhcp4_parser.cc"

#line 2695 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
