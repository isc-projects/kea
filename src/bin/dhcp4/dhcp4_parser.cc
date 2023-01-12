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
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 293 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 293 "dhcp4_parser.yy"
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
#line 302 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 303 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 304 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 305 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 306 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 307 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 308 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 309 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 310 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 311 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 312 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 313 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 314 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 322 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 323 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 324 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 325 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 326 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 327 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 328 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 331 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 336 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 341 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 347 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 354 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 359 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 365 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 370 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 373 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 381 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 385 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 389 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 395 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 397 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 406 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 410 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 414 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 424 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 433 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 438 "dhcp4_parser.yy"
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
#line 448 "dhcp4_parser.yy"
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
#line 457 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 465 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 471 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 475 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 482 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 135: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 556 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 136: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 562 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 137: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 568 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 138: // renew_timer: "renew-timer" ":" "integer"
#line 574 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 139: // rebind_timer: "rebind-timer" ":" "integer"
#line 580 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 140: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 586 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 141: // t1_percent: "t1-percent" ":" "floating point"
#line 592 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 142: // t2_percent: "t2-percent" ":" "floating point"
#line 598 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 143: // cache_threshold: "cache-threshold" ":" "floating point"
#line 604 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 144: // cache_max_age: "cache-max-age" ":" "integer"
#line 610 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 145: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 616 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 146: // $@20: %empty
#line 622 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 147: // server_tag: "server-tag" $@20 ":" "constant string"
#line 625 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 148: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 631 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 149: // $@21: %empty
#line 637 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1269 "dhcp4_parser.cc"
    break;

  case 150: // allocator: "allocator" $@21 ":" "constant string"
#line 640 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 151: // echo_client_id: "echo-client-id" ":" "boolean"
#line 646 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1289 "dhcp4_parser.cc"
    break;

  case 152: // match_client_id: "match-client-id" ":" "boolean"
#line 652 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1299 "dhcp4_parser.cc"
    break;

  case 153: // authoritative: "authoritative" ":" "boolean"
#line 658 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1309 "dhcp4_parser.cc"
    break;

  case 154: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 664 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1319 "dhcp4_parser.cc"
    break;

  case 155: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 670 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 156: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 676 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1339 "dhcp4_parser.cc"
    break;

  case 157: // $@22: %empty
#line 682 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1348 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 685 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "when-present"
#line 691 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1365 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "never"
#line 694 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1373 "dhcp4_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "always"
#line 697 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "when-not-present"
#line 700 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "boolean"
#line 703 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1398 "dhcp4_parser.cc"
    break;

  case 164: // $@23: %empty
#line 709 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 165: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 712 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 166: // $@24: %empty
#line 718 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp4_parser.cc"
    break;

  case 167: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 721 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1436 "dhcp4_parser.cc"
    break;

  case 168: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 727 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 169: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 733 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 170: // $@25: %empty
#line 739 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 171: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 742 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 172: // $@26: %empty
#line 748 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1484 "dhcp4_parser.cc"
    break;

  case 173: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 751 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 174: // store_extended_info: "store-extended-info" ":" "boolean"
#line 757 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1504 "dhcp4_parser.cc"
    break;

  case 175: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 763 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1514 "dhcp4_parser.cc"
    break;

  case 176: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 769 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 177: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 775 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 178: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 781 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 179: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 787 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1554 "dhcp4_parser.cc"
    break;

  case 180: // $@27: %empty
#line 793 "dhcp4_parser.yy"
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
#line 799 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 184: // interfaces_config_params: interfaces_config_params ","
#line 807 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1584 "dhcp4_parser.cc"
    break;

  case 195: // $@28: %empty
#line 824 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 196: // sub_interfaces4: "{" $@28 interfaces_config_params "}"
#line 828 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1603 "dhcp4_parser.cc"
    break;

  case 197: // $@29: %empty
#line 833 "dhcp4_parser.yy"
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
#line 839 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1624 "dhcp4_parser.cc"
    break;

  case 199: // $@30: %empty
#line 844 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1633 "dhcp4_parser.cc"
    break;

  case 200: // dhcp_socket_type: "dhcp-socket-type" $@30 ":" socket_type
#line 847 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1642 "dhcp4_parser.cc"
    break;

  case 201: // socket_type: "raw"
#line 852 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1648 "dhcp4_parser.cc"
    break;

  case 202: // socket_type: "udp"
#line 853 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1654 "dhcp4_parser.cc"
    break;

  case 203: // $@31: %empty
#line 856 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1663 "dhcp4_parser.cc"
    break;

  case 204: // outbound_interface: "outbound-interface" $@31 ":" outbound_interface_value
#line 859 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1672 "dhcp4_parser.cc"
    break;

  case 205: // outbound_interface_value: "same-as-inbound"
#line 864 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1680 "dhcp4_parser.cc"
    break;

  case 206: // outbound_interface_value: "use-routing"
#line 866 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1688 "dhcp4_parser.cc"
    break;

  case 207: // re_detect: "re-detect" ":" "boolean"
#line 870 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1698 "dhcp4_parser.cc"
    break;

  case 208: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 876 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1708 "dhcp4_parser.cc"
    break;

  case 209: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 882 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 210: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 888 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 211: // $@32: %empty
#line 894 "dhcp4_parser.yy"
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
#line 900 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1751 "dhcp4_parser.cc"
    break;

  case 213: // $@33: %empty
#line 907 "dhcp4_parser.yy"
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
#line 913 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 217: // sanity_checks_params: sanity_checks_params ","
#line 920 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1780 "dhcp4_parser.cc"
    break;

  case 220: // $@34: %empty
#line 929 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1789 "dhcp4_parser.cc"
    break;

  case 221: // lease_checks: "lease-checks" $@34 ":" "constant string"
#line 932 "dhcp4_parser.yy"
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
#line 948 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1818 "dhcp4_parser.cc"
    break;

  case 223: // extended_info_checks: "extended-info-checks" $@35 ":" "constant string"
#line 951 "dhcp4_parser.yy"
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
#line 966 "dhcp4_parser.yy"
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
#line 972 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1860 "dhcp4_parser.cc"
    break;

  case 226: // $@37: %empty
#line 979 "dhcp4_parser.yy"
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
#line 985 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1881 "dhcp4_parser.cc"
    break;

  case 232: // not_empty_database_list: not_empty_database_list ","
#line 996 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1889 "dhcp4_parser.cc"
    break;

  case 233: // $@38: %empty
#line 1001 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1899 "dhcp4_parser.cc"
    break;

  case 234: // database: "{" $@38 database_map_params "}"
#line 1005 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1909 "dhcp4_parser.cc"
    break;

  case 237: // database_map_params: database_map_params ","
#line 1013 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1917 "dhcp4_parser.cc"
    break;

  case 260: // $@39: %empty
#line 1042 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 261: // database_type: "type" $@39 ":" db_type
#line 1045 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1935 "dhcp4_parser.cc"
    break;

  case 262: // db_type: "memfile"
#line 1050 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1941 "dhcp4_parser.cc"
    break;

  case 263: // db_type: "mysql"
#line 1051 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1947 "dhcp4_parser.cc"
    break;

  case 264: // db_type: "postgresql"
#line 1052 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1953 "dhcp4_parser.cc"
    break;

  case 265: // $@40: %empty
#line 1055 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 266: // user: "user" $@40 ":" "constant string"
#line 1058 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 267: // $@41: %empty
#line 1064 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 268: // password: "password" $@41 ":" "constant string"
#line 1067 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 269: // $@42: %empty
#line 1073 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2000 "dhcp4_parser.cc"
    break;

  case 270: // host: "host" $@42 ":" "constant string"
#line 1076 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 271: // port: "port" ":" "integer"
#line 1082 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 272: // $@43: %empty
#line 1088 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp4_parser.cc"
    break;

  case 273: // name: "name" $@43 ":" "constant string"
#line 1091 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2039 "dhcp4_parser.cc"
    break;

  case 274: // persist: "persist" ":" "boolean"
#line 1097 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2049 "dhcp4_parser.cc"
    break;

  case 275: // lfc_interval: "lfc-interval" ":" "integer"
#line 1103 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 276: // readonly: "readonly" ":" "boolean"
#line 1109 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 277: // connect_timeout: "connect-timeout" ":" "integer"
#line 1115 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 278: // read_timeout: "read-timeout" ":" "integer"
#line 1121 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 279: // write_timeout: "write-timeout" ":" "integer"
#line 1127 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 280: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1133 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 281: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1139 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2119 "dhcp4_parser.cc"
    break;

  case 282: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1145 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2129 "dhcp4_parser.cc"
    break;

  case 283: // $@44: %empty
#line 1151 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2138 "dhcp4_parser.cc"
    break;

  case 284: // on_fail: "on-fail" $@44 ":" on_fail_mode
#line 1154 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2147 "dhcp4_parser.cc"
    break;

  case 285: // on_fail_mode: "stop-retry-exit"
#line 1159 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2153 "dhcp4_parser.cc"
    break;

  case 286: // on_fail_mode: "serve-retry-exit"
#line 1160 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2159 "dhcp4_parser.cc"
    break;

  case 287: // on_fail_mode: "serve-retry-continue"
#line 1161 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2165 "dhcp4_parser.cc"
    break;

  case 288: // max_row_errors: "max-row-errors" ":" "integer"
#line 1164 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2175 "dhcp4_parser.cc"
    break;

  case 289: // $@45: %empty
#line 1170 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2184 "dhcp4_parser.cc"
    break;

  case 290: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1173 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2194 "dhcp4_parser.cc"
    break;

  case 291: // $@46: %empty
#line 1179 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2203 "dhcp4_parser.cc"
    break;

  case 292: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1182 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2213 "dhcp4_parser.cc"
    break;

  case 293: // $@47: %empty
#line 1188 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2222 "dhcp4_parser.cc"
    break;

  case 294: // key_file: "key-file" $@47 ":" "constant string"
#line 1191 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2232 "dhcp4_parser.cc"
    break;

  case 295: // $@48: %empty
#line 1197 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2241 "dhcp4_parser.cc"
    break;

  case 296: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1200 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 297: // $@49: %empty
#line 1206 "dhcp4_parser.yy"
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
#line 1212 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2272 "dhcp4_parser.cc"
    break;

  case 301: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1219 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2280 "dhcp4_parser.cc"
    break;

  case 307: // duid_id: "duid"
#line 1231 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2289 "dhcp4_parser.cc"
    break;

  case 308: // hw_address_id: "hw-address"
#line 1236 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2298 "dhcp4_parser.cc"
    break;

  case 309: // circuit_id: "circuit-id"
#line 1241 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 310: // client_id: "client-id"
#line 1246 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2316 "dhcp4_parser.cc"
    break;

  case 311: // flex_id: "flex-id"
#line 1251 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2325 "dhcp4_parser.cc"
    break;

  case 312: // $@50: %empty
#line 1258 "dhcp4_parser.yy"
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
#line 1264 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2348 "dhcp4_parser.cc"
    break;

  case 316: // multi_threading_params: multi_threading_params ","
#line 1273 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2356 "dhcp4_parser.cc"
    break;

  case 323: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1286 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2366 "dhcp4_parser.cc"
    break;

  case 324: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1292 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 325: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1298 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 326: // $@51: %empty
#line 1304 "dhcp4_parser.yy"
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
#line 1310 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2407 "dhcp4_parser.cc"
    break;

  case 332: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1321 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2415 "dhcp4_parser.cc"
    break;

  case 333: // $@52: %empty
#line 1326 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 334: // hooks_library: "{" $@52 hooks_params "}"
#line 1330 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 335: // $@53: %empty
#line 1336 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 336: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1340 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2455 "dhcp4_parser.cc"
    break;

  case 339: // hooks_params: hooks_params ","
#line 1348 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2463 "dhcp4_parser.cc"
    break;

  case 343: // $@54: %empty
#line 1358 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc"
    break;

  case 344: // library: "library" $@54 ":" "constant string"
#line 1361 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 345: // $@55: %empty
#line 1367 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 346: // parameters: "parameters" $@55 ":" map_value
#line 1370 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2500 "dhcp4_parser.cc"
    break;

  case 347: // $@56: %empty
#line 1376 "dhcp4_parser.yy"
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
#line 1382 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2522 "dhcp4_parser.cc"
    break;

  case 351: // expired_leases_params: expired_leases_params ","
#line 1390 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2530 "dhcp4_parser.cc"
    break;

  case 358: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1403 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2540 "dhcp4_parser.cc"
    break;

  case 359: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1409 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 360: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1415 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2560 "dhcp4_parser.cc"
    break;

  case 361: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1421 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2570 "dhcp4_parser.cc"
    break;

  case 362: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1427 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 363: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1433 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 364: // $@57: %empty
#line 1442 "dhcp4_parser.yy"
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
#line 1448 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2611 "dhcp4_parser.cc"
    break;

  case 370: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1462 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2619 "dhcp4_parser.cc"
    break;

  case 371: // $@58: %empty
#line 1471 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2629 "dhcp4_parser.cc"
    break;

  case 372: // subnet4: "{" $@58 subnet4_params "}"
#line 1475 "dhcp4_parser.yy"
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
#line 1497 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2665 "dhcp4_parser.cc"
    break;

  case 374: // sub_subnet4: "{" $@59 subnet4_params "}"
#line 1501 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2675 "dhcp4_parser.cc"
    break;

  case 377: // subnet4_params: subnet4_params ","
#line 1510 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2683 "dhcp4_parser.cc"
    break;

  case 424: // $@60: %empty
#line 1564 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 425: // subnet: "subnet" $@60 ":" "constant string"
#line 1567 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 426: // $@61: %empty
#line 1573 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2711 "dhcp4_parser.cc"
    break;

  case 427: // subnet_4o6_interface: "4o6-interface" $@61 ":" "constant string"
#line 1576 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 428: // $@62: %empty
#line 1582 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2730 "dhcp4_parser.cc"
    break;

  case 429: // subnet_4o6_interface_id: "4o6-interface-id" $@62 ":" "constant string"
#line 1585 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2740 "dhcp4_parser.cc"
    break;

  case 430: // $@63: %empty
#line 1591 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2749 "dhcp4_parser.cc"
    break;

  case 431: // subnet_4o6_subnet: "4o6-subnet" $@63 ":" "constant string"
#line 1594 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2759 "dhcp4_parser.cc"
    break;

  case 432: // $@64: %empty
#line 1600 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2768 "dhcp4_parser.cc"
    break;

  case 433: // interface: "interface" $@64 ":" "constant string"
#line 1603 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2778 "dhcp4_parser.cc"
    break;

  case 434: // $@65: %empty
#line 1609 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2787 "dhcp4_parser.cc"
    break;

  case 435: // client_class: "client-class" $@65 ":" "constant string"
#line 1612 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2797 "dhcp4_parser.cc"
    break;

  case 436: // $@66: %empty
#line 1618 "dhcp4_parser.yy"
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
#line 1624 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2818 "dhcp4_parser.cc"
    break;

  case 438: // reservations_global: "reservations-global" ":" "boolean"
#line 1629 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2828 "dhcp4_parser.cc"
    break;

  case 439: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1635 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2838 "dhcp4_parser.cc"
    break;

  case 440: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1641 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2848 "dhcp4_parser.cc"
    break;

  case 441: // $@67: %empty
#line 1647 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2857 "dhcp4_parser.cc"
    break;

  case 442: // reservation_mode: "reservation-mode" $@67 ":" hr_mode
#line 1650 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2866 "dhcp4_parser.cc"
    break;

  case 443: // hr_mode: "disabled"
#line 1655 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2872 "dhcp4_parser.cc"
    break;

  case 444: // hr_mode: "out-of-pool"
#line 1656 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2878 "dhcp4_parser.cc"
    break;

  case 445: // hr_mode: "global"
#line 1657 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2884 "dhcp4_parser.cc"
    break;

  case 446: // hr_mode: "all"
#line 1658 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2890 "dhcp4_parser.cc"
    break;

  case 447: // id: "id" ":" "integer"
#line 1661 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 448: // $@68: %empty
#line 1669 "dhcp4_parser.yy"
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
#line 1675 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2921 "dhcp4_parser.cc"
    break;

  case 454: // shared_networks_list: shared_networks_list ","
#line 1688 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2929 "dhcp4_parser.cc"
    break;

  case 455: // $@69: %empty
#line 1693 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2939 "dhcp4_parser.cc"
    break;

  case 456: // shared_network: "{" $@69 shared_network_params "}"
#line 1697 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 459: // shared_network_params: shared_network_params ","
#line 1703 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2955 "dhcp4_parser.cc"
    break;

  case 501: // $@70: %empty
#line 1755 "dhcp4_parser.yy"
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
#line 1761 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 503: // $@71: %empty
#line 1769 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2985 "dhcp4_parser.cc"
    break;

  case 504: // sub_option_def_list: "{" $@71 option_def_list "}"
#line 1772 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2993 "dhcp4_parser.cc"
    break;

  case 509: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1784 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3001 "dhcp4_parser.cc"
    break;

  case 510: // $@72: %empty
#line 1791 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3011 "dhcp4_parser.cc"
    break;

  case 511: // option_def_entry: "{" $@72 option_def_params "}"
#line 1795 "dhcp4_parser.yy"
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
#line 1806 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3033 "dhcp4_parser.cc"
    break;

  case 513: // sub_option_def: "{" $@73 option_def_params "}"
#line 1810 "dhcp4_parser.yy"
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
#line 1826 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3053 "dhcp4_parser.cc"
    break;

  case 530: // code: "code" ":" "integer"
#line 1845 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 532: // $@74: %empty
#line 1853 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 533: // option_def_type: "type" $@74 ":" "constant string"
#line 1856 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3082 "dhcp4_parser.cc"
    break;

  case 534: // $@75: %empty
#line 1862 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3091 "dhcp4_parser.cc"
    break;

  case 535: // option_def_record_types: "record-types" $@75 ":" "constant string"
#line 1865 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 536: // $@76: %empty
#line 1871 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3110 "dhcp4_parser.cc"
    break;

  case 537: // space: "space" $@76 ":" "constant string"
#line 1874 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3120 "dhcp4_parser.cc"
    break;

  case 539: // $@77: %empty
#line 1882 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3129 "dhcp4_parser.cc"
    break;

  case 540: // option_def_encapsulate: "encapsulate" $@77 ":" "constant string"
#line 1885 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 541: // option_def_array: "array" ":" "boolean"
#line 1891 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 542: // $@78: %empty
#line 1901 "dhcp4_parser.yy"
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
#line 1907 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3170 "dhcp4_parser.cc"
    break;

  case 548: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1922 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3178 "dhcp4_parser.cc"
    break;

  case 549: // $@79: %empty
#line 1929 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 550: // option_data_entry: "{" $@79 option_data_params "}"
#line 1933 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 551: // $@80: %empty
#line 1941 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3207 "dhcp4_parser.cc"
    break;

  case 552: // sub_option_data: "{" $@80 option_data_params "}"
#line 1945 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 557: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1961 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3224 "dhcp4_parser.cc"
    break;

  case 568: // $@81: %empty
#line 1981 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3233 "dhcp4_parser.cc"
    break;

  case 569: // option_data_data: "data" $@81 ":" "constant string"
#line 1984 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3243 "dhcp4_parser.cc"
    break;

  case 572: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1994 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3253 "dhcp4_parser.cc"
    break;

  case 573: // option_data_always_send: "always-send" ":" "boolean"
#line 2000 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 574: // $@82: %empty
#line 2009 "dhcp4_parser.yy"
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
#line 2015 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3284 "dhcp4_parser.cc"
    break;

  case 580: // not_empty_pools_list: not_empty_pools_list ","
#line 2028 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3292 "dhcp4_parser.cc"
    break;

  case 581: // $@83: %empty
#line 2033 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3302 "dhcp4_parser.cc"
    break;

  case 582: // pool_list_entry: "{" $@83 pool_params "}"
#line 2037 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 583: // $@84: %empty
#line 2043 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 584: // sub_pool4: "{" $@84 pool_params "}"
#line 2047 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 587: // pool_params: pool_params ","
#line 2055 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3340 "dhcp4_parser.cc"
    break;

  case 595: // $@85: %empty
#line 2069 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3349 "dhcp4_parser.cc"
    break;

  case 596: // pool_entry: "pool" $@85 ":" "constant string"
#line 2072 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3359 "dhcp4_parser.cc"
    break;

  case 597: // $@86: %empty
#line 2078 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3367 "dhcp4_parser.cc"
    break;

  case 598: // user_context: "user-context" $@86 ":" map_value
#line 2080 "dhcp4_parser.yy"
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
#line 2103 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3402 "dhcp4_parser.cc"
    break;

  case 600: // comment: "comment" $@87 ":" "constant string"
#line 2105 "dhcp4_parser.yy"
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
#line 2133 "dhcp4_parser.yy"
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
#line 2139 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3452 "dhcp4_parser.cc"
    break;

  case 607: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2150 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3460 "dhcp4_parser.cc"
    break;

  case 608: // $@89: %empty
#line 2155 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3470 "dhcp4_parser.cc"
    break;

  case 609: // reservation: "{" $@89 reservation_params "}"
#line 2159 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3479 "dhcp4_parser.cc"
    break;

  case 610: // $@90: %empty
#line 2164 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3489 "dhcp4_parser.cc"
    break;

  case 611: // sub_reservation: "{" $@90 reservation_params "}"
#line 2168 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3498 "dhcp4_parser.cc"
    break;

  case 616: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2179 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3506 "dhcp4_parser.cc"
    break;

  case 632: // $@91: %empty
#line 2202 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3515 "dhcp4_parser.cc"
    break;

  case 633: // next_server: "next-server" $@91 ":" "constant string"
#line 2205 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 634: // $@92: %empty
#line 2211 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3534 "dhcp4_parser.cc"
    break;

  case 635: // server_hostname: "server-hostname" $@92 ":" "constant string"
#line 2214 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3544 "dhcp4_parser.cc"
    break;

  case 636: // $@93: %empty
#line 2220 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3553 "dhcp4_parser.cc"
    break;

  case 637: // boot_file_name: "boot-file-name" $@93 ":" "constant string"
#line 2223 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 638: // $@94: %empty
#line 2229 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3572 "dhcp4_parser.cc"
    break;

  case 639: // ip_address: "ip-address" $@94 ":" "constant string"
#line 2232 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 640: // $@95: %empty
#line 2238 "dhcp4_parser.yy"
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
#line 2244 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3603 "dhcp4_parser.cc"
    break;

  case 642: // $@96: %empty
#line 2249 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 643: // duid: "duid" $@96 ":" "constant string"
#line 2252 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 644: // $@97: %empty
#line 2258 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3631 "dhcp4_parser.cc"
    break;

  case 645: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2261 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 646: // $@98: %empty
#line 2267 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3650 "dhcp4_parser.cc"
    break;

  case 647: // client_id_value: "client-id" $@98 ":" "constant string"
#line 2270 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3660 "dhcp4_parser.cc"
    break;

  case 648: // $@99: %empty
#line 2276 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3669 "dhcp4_parser.cc"
    break;

  case 649: // circuit_id_value: "circuit-id" $@99 ":" "constant string"
#line 2279 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3679 "dhcp4_parser.cc"
    break;

  case 650: // $@100: %empty
#line 2285 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3688 "dhcp4_parser.cc"
    break;

  case 651: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2288 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3698 "dhcp4_parser.cc"
    break;

  case 652: // $@101: %empty
#line 2294 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3707 "dhcp4_parser.cc"
    break;

  case 653: // hostname: "hostname" $@101 ":" "constant string"
#line 2297 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3717 "dhcp4_parser.cc"
    break;

  case 654: // $@102: %empty
#line 2303 "dhcp4_parser.yy"
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
#line 2309 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3738 "dhcp4_parser.cc"
    break;

  case 656: // $@103: %empty
#line 2317 "dhcp4_parser.yy"
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
#line 2323 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3759 "dhcp4_parser.cc"
    break;

  case 660: // $@104: %empty
#line 2335 "dhcp4_parser.yy"
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
#line 2341 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3780 "dhcp4_parser.cc"
    break;

  case 664: // client_classes_list: client_classes_list ","
#line 2348 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3788 "dhcp4_parser.cc"
    break;

  case 665: // $@105: %empty
#line 2353 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3798 "dhcp4_parser.cc"
    break;

  case 666: // client_class_entry: "{" $@105 client_class_params "}"
#line 2357 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 671: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2369 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3816 "dhcp4_parser.cc"
    break;

  case 688: // $@106: %empty
#line 2393 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3825 "dhcp4_parser.cc"
    break;

  case 689: // client_class_test: "test" $@106 ":" "constant string"
#line 2396 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3835 "dhcp4_parser.cc"
    break;

  case 690: // $@107: %empty
#line 2402 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 691: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2405 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3854 "dhcp4_parser.cc"
    break;

  case 692: // only_if_required: "only-if-required" ":" "boolean"
#line 2411 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3864 "dhcp4_parser.cc"
    break;

  case 693: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2419 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3874 "dhcp4_parser.cc"
    break;

  case 694: // $@108: %empty
#line 2427 "dhcp4_parser.yy"
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
#line 2433 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3895 "dhcp4_parser.cc"
    break;

  case 698: // control_socket_params: control_socket_params ","
#line 2440 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3903 "dhcp4_parser.cc"
    break;

  case 704: // $@109: %empty
#line 2452 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3912 "dhcp4_parser.cc"
    break;

  case 705: // control_socket_type: "socket-type" $@109 ":" "constant string"
#line 2455 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3922 "dhcp4_parser.cc"
    break;

  case 706: // $@110: %empty
#line 2461 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3931 "dhcp4_parser.cc"
    break;

  case 707: // control_socket_name: "socket-name" $@110 ":" "constant string"
#line 2464 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3941 "dhcp4_parser.cc"
    break;

  case 708: // $@111: %empty
#line 2473 "dhcp4_parser.yy"
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
#line 2479 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3964 "dhcp4_parser.cc"
    break;

  case 712: // queue_control_params: queue_control_params ","
#line 2488 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3972 "dhcp4_parser.cc"
    break;

  case 719: // enable_queue: "enable-queue" ":" "boolean"
#line 2501 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3982 "dhcp4_parser.cc"
    break;

  case 720: // $@112: %empty
#line 2507 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3991 "dhcp4_parser.cc"
    break;

  case 721: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2510 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4001 "dhcp4_parser.cc"
    break;

  case 722: // capacity: "capacity" ":" "integer"
#line 2516 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4011 "dhcp4_parser.cc"
    break;

  case 723: // $@113: %empty
#line 2522 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4020 "dhcp4_parser.cc"
    break;

  case 724: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2525 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4029 "dhcp4_parser.cc"
    break;

  case 725: // $@114: %empty
#line 2532 "dhcp4_parser.yy"
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
#line 2538 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4052 "dhcp4_parser.cc"
    break;

  case 727: // $@115: %empty
#line 2545 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4062 "dhcp4_parser.cc"
    break;

  case 728: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2549 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4072 "dhcp4_parser.cc"
    break;

  case 731: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2557 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4080 "dhcp4_parser.cc"
    break;

  case 750: // enable_updates: "enable-updates" ":" "boolean"
#line 2582 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4090 "dhcp4_parser.cc"
    break;

  case 751: // $@116: %empty
#line 2588 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4099 "dhcp4_parser.cc"
    break;

  case 752: // server_ip: "server-ip" $@116 ":" "constant string"
#line 2591 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4109 "dhcp4_parser.cc"
    break;

  case 753: // server_port: "server-port" ":" "integer"
#line 2597 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4119 "dhcp4_parser.cc"
    break;

  case 754: // $@117: %empty
#line 2603 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4128 "dhcp4_parser.cc"
    break;

  case 755: // sender_ip: "sender-ip" $@117 ":" "constant string"
#line 2606 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4138 "dhcp4_parser.cc"
    break;

  case 756: // sender_port: "sender-port" ":" "integer"
#line 2612 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4148 "dhcp4_parser.cc"
    break;

  case 757: // max_queue_size: "max-queue-size" ":" "integer"
#line 2618 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4158 "dhcp4_parser.cc"
    break;

  case 758: // $@118: %empty
#line 2624 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4167 "dhcp4_parser.cc"
    break;

  case 759: // ncr_protocol: "ncr-protocol" $@118 ":" ncr_protocol_value
#line 2627 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4176 "dhcp4_parser.cc"
    break;

  case 760: // ncr_protocol_value: "udp"
#line 2633 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4182 "dhcp4_parser.cc"
    break;

  case 761: // ncr_protocol_value: "tcp"
#line 2634 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4188 "dhcp4_parser.cc"
    break;

  case 762: // $@119: %empty
#line 2637 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4197 "dhcp4_parser.cc"
    break;

  case 763: // ncr_format: "ncr-format" $@119 ":" "JSON"
#line 2640 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4207 "dhcp4_parser.cc"
    break;

  case 764: // $@120: %empty
#line 2647 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4216 "dhcp4_parser.cc"
    break;

  case 765: // dep_qualifying_suffix: "qualifying-suffix" $@120 ":" "constant string"
#line 2650 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4226 "dhcp4_parser.cc"
    break;

  case 766: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2657 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4236 "dhcp4_parser.cc"
    break;

  case 767: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2664 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4246 "dhcp4_parser.cc"
    break;

  case 768: // $@121: %empty
#line 2671 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4255 "dhcp4_parser.cc"
    break;

  case 769: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2674 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4264 "dhcp4_parser.cc"
    break;

  case 770: // $@122: %empty
#line 2680 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4273 "dhcp4_parser.cc"
    break;

  case 771: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2683 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4283 "dhcp4_parser.cc"
    break;

  case 772: // $@123: %empty
#line 2690 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4292 "dhcp4_parser.cc"
    break;

  case 773: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2693 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4302 "dhcp4_parser.cc"
    break;

  case 774: // $@124: %empty
#line 2700 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4311 "dhcp4_parser.cc"
    break;

  case 775: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2703 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4321 "dhcp4_parser.cc"
    break;

  case 776: // $@125: %empty
#line 2712 "dhcp4_parser.yy"
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
#line 2718 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4343 "dhcp4_parser.cc"
    break;

  case 778: // $@126: %empty
#line 2724 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4353 "dhcp4_parser.cc"
    break;

  case 779: // sub_config_control: "{" $@126 config_control_params "}"
#line 2728 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4362 "dhcp4_parser.cc"
    break;

  case 782: // config_control_params: config_control_params ","
#line 2736 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4370 "dhcp4_parser.cc"
    break;

  case 785: // $@127: %empty
#line 2746 "dhcp4_parser.yy"
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
#line 2752 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4391 "dhcp4_parser.cc"
    break;

  case 787: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2757 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4401 "dhcp4_parser.cc"
    break;

  case 788: // $@128: %empty
#line 2765 "dhcp4_parser.yy"
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
#line 2771 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4422 "dhcp4_parser.cc"
    break;

  case 792: // loggers_entries: loggers_entries ","
#line 2780 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4430 "dhcp4_parser.cc"
    break;

  case 793: // $@129: %empty
#line 2786 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4440 "dhcp4_parser.cc"
    break;

  case 794: // logger_entry: "{" $@129 logger_params "}"
#line 2790 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4448 "dhcp4_parser.cc"
    break;

  case 797: // logger_params: logger_params ","
#line 2796 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4456 "dhcp4_parser.cc"
    break;

  case 805: // debuglevel: "debuglevel" ":" "integer"
#line 2810 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4466 "dhcp4_parser.cc"
    break;

  case 806: // $@130: %empty
#line 2816 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4475 "dhcp4_parser.cc"
    break;

  case 807: // severity: "severity" $@130 ":" "constant string"
#line 2819 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4485 "dhcp4_parser.cc"
    break;

  case 808: // $@131: %empty
#line 2825 "dhcp4_parser.yy"
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
#line 2831 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4506 "dhcp4_parser.cc"
    break;

  case 812: // output_options_list_content: output_options_list_content ","
#line 2838 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4514 "dhcp4_parser.cc"
    break;

  case 813: // $@132: %empty
#line 2843 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4524 "dhcp4_parser.cc"
    break;

  case 814: // output_entry: "{" $@132 output_params_list "}"
#line 2847 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4532 "dhcp4_parser.cc"
    break;

  case 817: // output_params_list: output_params_list ","
#line 2853 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4540 "dhcp4_parser.cc"
    break;

  case 823: // $@133: %empty
#line 2865 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4549 "dhcp4_parser.cc"
    break;

  case 824: // output: "output" $@133 ":" "constant string"
#line 2868 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4559 "dhcp4_parser.cc"
    break;

  case 825: // flush: "flush" ":" "boolean"
#line 2874 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4569 "dhcp4_parser.cc"
    break;

  case 826: // maxsize: "maxsize" ":" "integer"
#line 2880 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4579 "dhcp4_parser.cc"
    break;

  case 827: // maxver: "maxver" ":" "integer"
#line 2886 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4589 "dhcp4_parser.cc"
    break;

  case 828: // $@134: %empty
#line 2892 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4598 "dhcp4_parser.cc"
    break;

  case 829: // pattern: "pattern" $@134 ":" "constant string"
#line 2895 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4608 "dhcp4_parser.cc"
    break;

  case 830: // $@135: %empty
#line 2901 "dhcp4_parser.yy"
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
#line 2907 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4629 "dhcp4_parser.cc"
    break;

  case 834: // compatibility_params: compatibility_params ","
#line 2914 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4637 "dhcp4_parser.cc"
    break;

  case 838: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2924 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4647 "dhcp4_parser.cc"
    break;

  case 839: // ignore-rai-link-selection: "ignore-rai-link-selection" ":" "boolean"
#line 2930 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4657 "dhcp4_parser.cc"
    break;


#line 4661 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -989;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     417,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,    22,    44,    28,    62,    65,    67,
      78,    88,   127,   131,   146,   160,   191,   238,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,    44,  -159,    54,   140,   133,   679,
      -6,   236,   175,    85,   178,  -101,   432,    32,  -989,   139,
     286,   293,   299,   305,  -989,    49,  -989,  -989,  -989,  -989,
     313,   314,   321,  -989,  -989,  -989,  -989,  -989,  -989,   334,
     335,   346,   366,   375,   376,   377,   378,   379,   380,   381,
    -989,   382,   384,   385,   386,   387,  -989,  -989,  -989,   406,
     408,   414,  -989,  -989,  -989,   415,  -989,  -989,  -989,  -989,
    -989,   416,   418,   419,  -989,  -989,  -989,  -989,  -989,   420,
    -989,  -989,  -989,  -989,  -989,  -989,   421,   422,   423,  -989,
    -989,   425,  -989,    51,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,   426,   427,   428,   429,  -989,    72,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,   430,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,   107,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,   118,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,   413,   433,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,   431,  -989,  -989,   434,  -989,  -989,  -989,   436,
    -989,  -989,   435,   438,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,   440,   442,  -989,
    -989,  -989,  -989,   443,   439,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,   125,  -989,  -989,
    -989,   444,  -989,  -989,   446,  -989,   449,   451,  -989,  -989,
     452,   453,  -989,  -989,  -989,  -989,  -989,  -989,  -989,   128,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,   454,   138,  -989,
    -989,  -989,  -989,    44,    44,  -989,   226,   456,  -989,  -989,
     458,   461,   462,   255,   257,   258,   468,   472,   476,   477,
     479,   480,   277,   278,   281,   282,   284,   285,   291,   295,
     300,   289,   302,   504,   304,   308,   303,   307,   309,   505,
     506,   518,   316,   317,   319,   522,   526,   528,   324,   529,
     537,   540,   541,   543,   336,   339,   340,   545,   546,   551,
     553,   556,   351,   561,   563,   564,   566,   569,   574,   368,
     369,   371,   581,   582,  -989,   140,  -989,   586,   587,   601,
     394,   395,   398,   399,   133,  -989,   606,   622,   623,   624,
     625,   626,   424,   627,   628,   629,   679,  -989,   631,    -6,
    -989,   632,   633,   635,   638,   639,   640,   641,   642,  -989,
     236,  -989,   643,   644,   441,   645,   646,   648,   445,  -989,
      85,   650,   447,   448,  -989,   178,   651,   652,   -25,  -989,
     455,   654,   657,   459,   659,   460,   463,   660,   661,   465,
     467,   662,   664,   667,   668,   432,  -989,   670,   470,    32,
    -989,  -989,  -989,   677,   676,   678,   680,   681,  -989,  -989,
    -989,   475,   481,   482,   682,   685,   688,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,   485,  -989,
    -989,  -989,  -989,  -989,   -94,   486,   487,  -989,  -989,  -989,
     696,   697,   698,  -989,   496,   701,   700,   499,   149,  -989,
    -989,  -989,   709,   710,   711,   712,   713,  -989,   714,   715,
     716,   717,   509,   510,  -989,  -989,  -989,   720,   719,  -989,
     722,   183,   209,  -989,  -989,  -989,  -989,  -989,   519,   520,
     521,   726,   523,   524,  -989,   722,   525,   728,  -989,   527,
    -989,   722,   544,   547,   557,   565,   567,   568,   570,  -989,
     571,   572,  -989,   576,   583,   584,  -989,  -989,   585,  -989,
    -989,  -989,   590,   700,  -989,  -989,   591,   593,  -989,   594,
    -989,  -989,    14,   512,  -989,  -989,   -94,   595,   598,   599,
    -989,   732,  -989,  -989,    44,   140,    32,   133,   254,  -989,
    -989,  -989,   354,   354,   731,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,   747,   748,   763,  -989,   765,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,    31,   766,   768,
     771,   170,   -46,   -10,   202,   432,  -989,  -989,   776,  -154,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,   788,  -989,  -989,  -989,  -989,   101,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,   731,  -989,   180,   186,   187,
    -989,  -989,   188,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
     805,   806,   807,   808,   810,   811,   812,   813,   814,   815,
    -989,   816,  -989,  -989,  -989,  -989,  -989,   194,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
     225,  -989,   817,   818,  -989,  -989,   819,   821,  -989,  -989,
     820,   824,  -989,  -989,   822,   826,  -989,  -989,   825,   827,
    -989,  -989,  -989,  -989,  -989,  -989,    57,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,   144,  -989,  -989,   828,   829,  -989,
    -989,   830,   832,  -989,   833,   834,   835,   836,   837,   838,
     243,  -989,  -989,  -989,  -989,  -989,  -989,  -989,   839,   840,
     841,  -989,   275,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,   276,  -989,  -989,  -989,   842,  -989,
     843,  -989,  -989,  -989,   288,  -989,  -989,  -989,  -989,  -989,
     290,  -989,   162,  -989,   844,   845,  -989,   297,  -989,  -989,
    -989,   613,  -989,   846,   847,  -989,  -989,  -989,  -989,   848,
     849,  -989,  -989,  -989,   850,   853,   254,  -989,   856,   857,
     858,   859,   655,   621,   656,   658,   663,   665,   666,   669,
     671,   672,   860,   673,   863,   864,   865,   867,   354,  -989,
    -989,   354,  -989,   731,   679,  -989,   747,    85,  -989,   748,
     178,  -989,   763,  1266,  -989,   765,    31,  -989,   270,   766,
    -989,   236,  -989,   768,  -101,  -989,   771,   674,   675,   683,
     684,   686,   687,   170,  -989,   689,   690,   692,   -46,  -989,
     868,   870,   -10,  -989,   691,   873,   694,   874,   202,  -989,
    -989,   142,   776,  -989,   693,   695,  -154,  -989,  -989,   880,
     877,    -6,  -989,   788,   883,  -989,  -989,   699,   702,  -989,
     315,   703,   704,   705,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,   318,  -989,   706,   707,   708,   723,
    -989,   298,  -989,   323,  -989,   881,  -989,   882,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,   329,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,   887,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,   884,
     892,  -989,  -989,  -989,  -989,  -989,  -989,   890,  -989,   337,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,   734,   741,  -989,  -989,   753,  -989,    44,  -989,
    -989,   895,  -989,  -989,  -989,  -989,  -989,   338,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,   760,   344,  -989,
     722,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  1266,  -989,   902,   905,   745,  -989,   270,  -989,
    -989,  -989,  -989,  -989,  -989,   906,   718,   914,   142,  -989,
    -989,  -989,  -989,  -989,   761,   780,  -989,  -989,   915,  -989,
     783,  -989,  -989,  -989,   912,  -989,  -989,   176,  -989,   -99,
     912,  -989,  -989,   917,   918,   919,  -989,   345,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,   920,   787,   721,   725,   921,
     -99,  -989,   795,  -989,  -989,  -989,   798,  -989,  -989,  -989
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
       0,   793,     0,   790,     0,     0,   837,     0,   832,   835,
     836,    53,   581,     0,   577,   578,   640,   658,   659,     0,
       0,    62,   777,   181,     0,     0,   217,   214,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   237,   212,
     225,     0,   227,   232,     0,   365,   370,   514,   502,   509,
     553,   543,   548,     0,   449,   454,   301,   298,   667,   664,
     661,   612,   602,   607,     0,   327,   332,     0,     0,     0,
       0,     0,     0,   351,   348,     0,     0,     0,   316,   313,
       0,     0,   698,   695,     0,     0,     0,     0,   712,   709,
     726,     0,   792,   789,     0,     0,   834,   831,    55,     0,
      54,     0,   575,   580,     0,   657,   786,     0,     0,   216,
       0,     0,     0,     0,   271,   274,   275,   276,   277,   278,
     279,   280,   281,   282,     0,   288,     0,     0,     0,     0,
     236,     0,   231,     0,   369,     0,   508,     0,   547,   500,
     478,   479,   480,   463,   464,   483,   484,   485,   486,   487,
     499,   466,   467,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   460,   461,   462,   476,   477,   473,
     474,   475,   472,     0,   457,   465,   481,   482,   468,   469,
     470,   471,   453,   300,   688,   690,     0,   683,   684,   685,
     686,   687,   676,   677,   681,   682,   678,   679,   680,     0,
     668,   669,   672,   673,   674,   675,   663,     0,   606,     0,
     331,   358,   359,   360,   361,   362,   363,   350,   323,   324,
     325,   315,     0,     0,   697,   719,     0,   722,     0,   711,
     808,     0,   806,   804,   798,   802,   803,     0,   795,   800,
     801,   799,   791,   838,   839,   833,    52,    57,     0,   579,
       0,   221,   223,   262,   263,   264,   261,   266,   268,   270,
     285,   286,   287,   284,   290,   292,   294,   296,   234,   372,
     511,   550,   459,   456,     0,     0,     0,   666,   671,   609,
     334,   705,   707,   721,   724,     0,     0,     0,   797,   794,
      56,   582,   641,   458,     0,     0,   692,   670,     0,   805,
       0,   796,   689,   691,     0,   807,   813,     0,   810,     0,
     812,   809,   823,     0,     0,     0,   828,     0,   815,   818,
     819,   820,   821,   822,   811,     0,     0,     0,     0,     0,
     817,   814,     0,   825,   826,   827,     0,   816,   824,   829
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,   -51,  -989,  -589,  -989,   168,
    -989,  -989,  -989,  -989,  -989,  -989,  -625,  -989,  -989,  -989,
     -67,  -989,  -989,  -989,  -989,  -989,  -989,  -989,   148,   514,
     -26,     9,    19,   -52,   -30,   -27,     7,    20,    27,    30,
    -989,  -989,  -989,  -989,    37,  -989,  -989,    38,    40,    42,
      43,    48,    50,  -989,   230,    53,  -989,    55,  -989,    56,
      58,    60,  -989,    61,  -989,    63,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,   222,   471,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,     6,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,   220,  -989,    25,  -989,  -701,    80,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,   -63,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,    33,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,    -8,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,    10,  -989,  -989,  -989,    59,   530,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,    47,  -989,  -989,  -989,  -989,
    -989,  -989,  -988,  -989,  -989,  -989,    79,  -989,  -989,  -989,
      83,   573,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -984,  -989,   -65,  -989,    69,  -989,    66,    68,    71,    73,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,    74,  -989,  -989,
    -142,   -54,  -989,  -989,  -989,  -989,  -989,    82,  -989,  -989,
    -989,    86,  -989,   542,  -989,   -41,  -989,  -989,  -989,  -989,
    -989,   -40,  -989,  -989,  -989,  -989,  -989,   -23,  -989,  -989,
    -989,    84,  -989,  -989,  -989,    87,  -989,   539,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,    35,
    -989,  -989,  -989,    34,   575,  -989,  -989,   -45,  -989,    -3,
    -989,   -48,  -989,  -989,  -989,    77,  -989,  -989,  -989,    81,
    -989,   577,   -55,  -989,   -13,  -989,     8,  -989,   325,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -983,  -989,  -989,  -989,
    -989,  -989,    89,  -989,  -989,  -989,  -135,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,    64,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,    70,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,   350,   532,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,   393,   531,  -989,
    -989,  -989,  -989,  -989,  -989,    75,  -989,  -989,  -137,  -989,
    -989,  -989,  -989,  -989,  -989,  -158,  -989,  -989,  -177,  -989,
    -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,  -989,    76,
    -989,  -989
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   730,
      82,    83,    39,    64,    79,    80,   751,   951,  1049,  1050,
     826,    41,    66,    85,   427,    86,    43,    67,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   453,   167,   168,   469,   169,   170,   171,   172,
     173,   174,   175,   459,   721,   176,   460,   177,   461,   178,
     179,   180,   487,   181,   488,   182,   183,   184,   185,   186,
     187,   188,   431,   227,   228,    45,    68,   229,   497,   230,
     498,   754,   231,   499,   757,   232,   233,   234,   235,   189,
     439,   190,   432,   802,   803,   804,   964,   805,   965,   191,
     440,   192,   441,   852,   853,   854,   991,   827,   828,   829,
     968,  1206,   830,   969,   831,   970,   832,   971,   833,   834,
     533,   835,   836,   837,   838,   839,   840,   841,   842,   843,
     844,   982,  1213,   845,   846,   984,   847,   985,   848,   986,
     849,   987,   193,   477,   876,   877,   878,   879,   880,   881,
     882,   194,   483,   912,   913,   914,   915,   916,   195,   480,
     891,   892,   893,  1014,    59,    75,   377,   378,   379,   546,
     380,   547,   196,   481,   900,   901,   902,   903,   904,   905,
     906,   907,   197,   465,   856,   857,   858,   994,    47,    69,
     273,   274,   275,   510,   276,   506,   277,   507,   278,   508,
     279,   511,   280,   514,   281,   513,   198,   199,   200,   201,
     473,   736,   286,   202,   470,   868,   869,   870,  1003,  1123,
    1124,   203,   466,    53,    72,   860,   861,   862,   997,    55,
      73,   342,   343,   344,   345,   346,   347,   348,   532,   349,
     536,   350,   535,   351,   352,   537,   353,   204,   467,   864,
     865,   866,  1000,    57,    74,   363,   364,   365,   366,   367,
     541,   368,   369,   370,   371,   288,   509,   953,   954,   955,
    1051,    49,    70,   301,   302,   303,   518,   205,   471,   206,
     472,   207,   479,   887,   888,   889,  1011,    51,    71,   318,
     319,   320,   208,   436,   209,   437,   210,   438,   324,   528,
     958,  1054,   325,   522,   326,   523,   327,   525,   328,   524,
     329,   527,   330,   526,   331,   521,   295,   515,   959,   211,
     478,   884,   885,  1008,  1149,  1150,  1151,  1152,  1153,  1224,
    1154,  1225,  1155,   212,   213,   484,   924,   925,   926,  1030,
     927,  1031,   214,   485,   934,   935,   936,   937,  1035,   938,
     939,  1037,   215,   486,    61,    76,   399,   400,   401,   402,
     552,   403,   404,   554,   405,   406,   407,   557,   789,   408,
     558,   409,   551,   410,   411,   412,   561,   413,   562,   414,
     563,   415,   564,   216,   430,    63,    77,   418,   419,   420,
     567,   421,   217,   492,   942,   943,  1041,  1187,  1188,  1189,
    1190,  1237,  1191,  1235,  1257,  1258,  1259,  1267,  1268,  1269,
    1275,  1270,  1271,  1272,  1273,  1279,   218,   493,   947,   948,
     949,   950
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     152,   226,   248,   297,   314,   298,   340,   359,   376,   396,
     341,   360,   850,    78,   292,  1115,   321,   252,   332,  1116,
    1131,   291,    28,   236,   289,   304,   316,   729,   354,   372,
     764,   397,   787,   361,   362,    40,   768,   374,   375,   253,
     944,   945,   254,   249,   416,   417,   287,   300,   315,    29,
      81,    30,   428,    31,   495,   151,   293,   429,   322,   496,
    1006,   128,   129,  1007,    84,   237,   290,   305,   317,    42,
     355,   373,    44,   398,    46,   504,   255,   294,   250,   323,
     505,   716,   717,   718,   719,    48,   124,  1262,   251,   256,
    1263,  1264,  1265,  1266,   729,    50,   257,   128,   129,   258,
     296,   128,   129,   908,   909,   910,   259,   260,   151,   261,
     516,   262,   263,   374,   375,   517,   245,   264,   720,   265,
     246,   519,   266,   333,   267,   268,   520,   269,   548,   270,
     271,   565,   272,   549,    52,   282,   566,   283,    54,   299,
     284,   569,   285,   919,   920,   422,   570,  1009,   219,   220,
    1010,    87,   221,    56,    88,   222,   223,   224,   225,   871,
     872,   873,   874,   151,   875,  1042,    89,    58,  1043,    90,
      91,    92,    93,    94,    95,    96,    97,    98,   334,  1260,
     335,   336,  1261,   495,   337,   338,   339,   788,   961,   569,
     504,   966,   128,   129,   962,   963,   967,   988,    60,   151,
     752,   753,   989,   151,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   988,   755,
     756,   123,   124,   990,  1115,   334,   313,   956,  1116,  1131,
     128,   129,   125,   126,   127,    62,  1023,   128,   129,   128,
     129,  1024,   130,    32,    33,    34,    35,   131,   132,   133,
     134,   135,   732,   733,   734,   735,   123,   136,    93,    94,
      95,   334,   356,   335,   336,   357,   358,   137,  1028,  1032,
     138,   800,   801,  1029,  1033,   128,   129,   139,   140,   423,
    1081,  1038,   141,   565,   151,   142,  1039,   424,  1040,   143,
    1046,   988,    93,    94,    95,  1047,  1218,   425,   426,   128,
     129,   894,   895,   896,   897,   898,   899,   433,   434,   144,
     145,   146,   147,   148,   149,   435,   516,  1180,   124,  1181,
    1182,  1219,  1222,   150,    99,   100,   101,  1223,   442,   443,
     548,  1238,   151,   128,   129,  1230,  1239,   519,  1280,   151,
     444,   151,  1241,  1281,  1203,  1204,  1205,   306,   928,   929,
     930,   123,   124,   334,   307,   308,   309,   310,   311,   312,
     445,   313,   571,   572,  1210,  1211,  1212,   128,   129,   446,
     447,   448,   449,   450,   451,   452,   454,   151,   455,   456,
     457,   458,   806,  1134,  1135,  1136,   807,   808,   809,   810,
     811,   812,   813,   814,   815,   816,   817,   818,   819,   820,
     462,   931,   463,   821,   822,   823,   824,   825,   464,   468,
     474,   529,   475,   476,   482,   489,   490,   491,   152,   494,
     500,   501,   502,   503,   512,   573,   530,   226,   534,   531,
     538,   540,   545,   539,   542,   151,   543,   334,   550,   248,
     553,   544,   297,   555,   298,   556,   559,   560,   568,   236,
     574,   292,   575,   314,   252,   576,   577,   578,   291,   579,
     580,   289,   581,   340,   304,   321,   582,   341,   359,   151,
     583,   584,   360,   585,   586,   316,   253,   587,   588,   254,
     249,   589,   590,   287,   591,   354,   300,   592,   396,   596,
     372,   237,   593,   293,   361,   362,   594,   315,   598,   604,
     605,   595,   597,   290,   599,   601,   305,   322,   600,   602,
     397,   603,   606,   255,   294,   250,   610,   317,   607,   608,
     611,   609,   612,   614,   613,   251,   256,   355,   323,   128,
     129,   615,   373,   257,   616,   617,   258,   618,   619,   622,
     623,   620,   621,   259,   260,   624,   261,   625,   262,   263,
     626,   627,   398,   151,   264,   628,   265,   629,   630,   266,
     631,   267,   268,   632,   269,  1242,   270,   271,   633,   272,
     634,   635,   282,   636,   283,   637,   638,   284,   299,   285,
     640,   641,   381,   382,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   642,   643,   644,   645,   646,
     648,   394,   395,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   649,   650,   651,   652,
     653,   655,   656,   657,   654,   659,   661,   662,   152,   663,
     226,   151,   664,   665,   666,   667,   668,   670,   671,   673,
     674,   672,   675,   796,   678,   682,   683,   676,   686,   679,
     680,   687,   236,   689,   692,   693,   696,   685,   697,   688,
     690,   698,   699,   691,   701,   911,   921,   694,   396,   695,
     702,   704,   946,   705,   709,   706,   790,   707,   708,   712,
     710,   711,   713,   714,   715,   722,   723,   917,   922,   932,
     397,   724,   725,   726,   237,   727,   728,    30,   731,    91,
      92,    93,    94,    95,   737,   738,   739,   740,   746,   747,
     741,   742,   743,   744,   745,   748,   749,   750,   758,   759,
     760,   761,   762,   763,   765,   766,   767,   795,   851,   918,
     923,   933,   398,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   769,   855,   859,   770,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   771,   238,   239,   240,
     863,   124,   867,   883,   772,   886,   773,   774,   890,   775,
     776,   777,   126,   941,   241,   778,   128,   129,   242,   243,
     244,   130,   779,   780,   781,   952,   131,   132,   133,   782,
     784,   245,   785,   786,   792,   246,   136,   793,   794,   972,
     973,   974,   975,   247,   976,   977,   978,   979,   980,   981,
     983,   993,  1048,   992,   996,   995,   998,   999,  1001,  1002,
    1005,  1004,  1013,  1065,  1012,  1016,  1015,  1017,  1018,  1019,
    1020,  1021,  1022,  1025,  1026,  1027,  1034,  1036,  1044,  1045,
    1053,   783,  1052,   797,  1057,  1056,  1055,  1058,   144,   145,
    1060,  1061,  1062,  1063,  1074,  1064,  1066,  1076,  1077,  1078,
    1067,  1079,  1172,  1068,  1173,  1069,  1070,  1176,  1178,  1071,
    1197,  1072,  1073,  1075,  1161,  1162,  1196,  1200,   151,  1220,
    1221,  1226,  1227,  1163,  1164,  1228,  1165,  1166,  1229,  1236,
    1169,  1168,  1170,  1175,  1177,  1193,  1244,  1194,  1201,  1245,
    1248,  1202,  1207,  1208,  1209,  1214,  1215,  1216,  1250,  1256,
    1254,  1276,  1277,  1278,  1282,  1286,   791,   248,  1249,   799,
     340,  1284,  1217,   359,   341,  1285,  1089,   360,  1117,   292,
    1114,  1137,   252,  1231,   314,  1141,   291,   376,  1128,   289,
    1232,  1093,   354,  1146,  1142,   372,   321,  1246,  1126,   361,
     362,   911,  1233,  1144,   253,   921,   316,   254,   249,  1240,
    1252,   287,  1059,  1094,  1183,   647,  1095,  1090,  1184,   946,
    1125,   293,  1138,   917,   297,  1143,   298,   922,   315,  1253,
    1129,   290,  1255,   932,   355,  1147,  1185,   373,   322,  1283,
    1127,   255,   294,   250,  1288,  1145,   304,  1289,   317,   639,
    1096,  1130,  1091,   251,   256,   960,  1148,  1139,  1082,   323,
    1171,   257,  1092,  1097,   258,   918,  1160,  1140,   300,   923,
    1098,   259,   260,  1099,   261,   933,   262,   263,  1186,  1133,
    1100,  1101,   264,  1102,   265,  1103,  1104,   266,   305,   267,
     268,  1105,   269,  1106,   270,   271,  1107,   272,  1108,  1109,
     282,  1110,   283,  1111,  1112,   284,  1113,   285,  1080,  1119,
    1167,  1120,  1118,  1159,  1121,  1084,  1122,  1083,   684,  1132,
    1243,  1086,   677,  1085,   681,  1198,  1088,  1087,  1199,   658,
    1158,   957,  1157,  1247,   660,   940,  1174,   700,  1156,   798,
     703,  1251,  1274,  1287,     0,     0,     0,   669,  1179,     0,
       0,     0,     0,     0,     0,     0,     0,  1192,     0,     0,
     299,     0,  1195,     0,     0,     0,     0,  1234,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1089,     0,  1117,     0,  1114,
       0,  1137,     0,     0,     0,  1141,     0,  1128,     0,     0,
    1093,  1183,     0,  1146,  1142,  1184,     0,  1126,     0,     0,
       0,     0,     0,  1144,     0,     0,     0,     0,     0,     0,
       0,     0,  1094,  1185,     0,  1095,  1090,     0,     0,  1125,
       0,     0,  1138,     0,     0,  1143,     0,     0,     0,  1129,
       0,     0,     0,     0,     0,  1147,     0,     0,     0,  1127,
       0,     0,     0,     0,     0,  1145,     0,     0,     0,  1096,
    1130,  1091,     0,     0,     0,  1186,  1148,  1139,     0,     0,
       0,  1092,  1097,     0,     0,     0,     0,  1140,     0,  1098,
       0,     0,  1099,     0,     0,     0,     0,     0,     0,  1100,
    1101,     0,  1102,     0,  1103,  1104,     0,     0,     0,     0,
    1105,     0,  1106,     0,     0,  1107,     0,  1108,  1109,     0,
    1110,     0,  1111,  1112,     0,  1113,     0,     0,  1119,     0,
    1120,  1118,     0,  1121,     0,  1122,    91,    92,    93,    94,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
       0,     0,     0,     0,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,     0,     0,     0,     0,   124,   334,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   126,
       0,     0,     0,   128,   129,     0,   243,     0,   130,     0,
       0,     0,     0,   131,   132,   133,     0,     0,   245,     0,
       0,     0,   246,     0,     0,     0,     0,     0,     0,     0,
     247,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   144,   145,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   151
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,   713,    64,    69,  1003,    71,    69,    72,  1003,
    1003,    69,     0,    68,    69,    70,    71,   616,    73,    74,
     655,    76,    18,    74,    74,     7,   661,   138,   139,    69,
     194,   195,    69,    69,    12,    13,    69,    70,    71,     5,
     209,     7,     3,     9,     3,   209,    69,     8,    71,     8,
       3,   107,   108,     6,    10,    68,    69,    70,    71,     7,
      73,    74,     7,    76,     7,     3,    69,    69,    69,    71,
       8,   175,   176,   177,   178,     7,    92,   186,    69,    69,
     189,   190,   191,   192,   683,     7,    69,   107,   108,    69,
     106,   107,   108,   149,   150,   151,    69,    69,   209,    69,
       3,    69,    69,   138,   139,     8,   122,    69,   212,    69,
     126,     3,    69,    38,    69,    69,     8,    69,     3,    69,
      69,     3,    69,     8,     7,    69,     8,    69,     7,    70,
      69,     3,    69,   153,   154,     6,     8,     3,    15,    16,
       6,    11,    19,     7,    14,    22,    23,    24,    25,   128,
     129,   130,   131,   209,   133,     3,    26,     7,     6,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    93,     3,
      95,    96,     6,     3,    99,   100,   101,   173,     8,     3,
       3,     3,   107,   108,     8,     8,     8,     3,     7,   209,
      17,    18,     8,   209,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,     3,    20,
      21,    91,    92,     8,  1222,    93,   135,   136,  1222,  1222,
     107,   108,   102,   103,   104,     7,     3,   107,   108,   107,
     108,     8,   112,   209,   210,   211,   212,   117,   118,   119,
     120,   121,   113,   114,   115,   116,    91,   127,    32,    33,
      34,    93,    94,    95,    96,    97,    98,   137,     3,     3,
     140,    27,    28,     8,     8,   107,   108,   147,   148,     3,
     991,     3,   152,     3,   209,   155,     8,     4,     8,   159,
       3,     3,    32,    33,    34,     8,     8,     8,     3,   107,
     108,   141,   142,   143,   144,   145,   146,     4,     4,   179,
     180,   181,   182,   183,   184,     4,     3,   185,    92,   187,
     188,     8,     3,   193,    64,    65,    66,     8,     4,     4,
       3,     3,   209,   107,   108,     8,     8,     3,     3,   209,
       4,   209,     8,     8,    39,    40,    41,   121,   156,   157,
     158,    91,    92,    93,   128,   129,   130,   131,   132,   133,
       4,   135,   423,   424,    56,    57,    58,   107,   108,     4,
       4,     4,     4,     4,     4,     4,     4,   209,     4,     4,
       4,     4,    38,   123,   124,   125,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
       4,   209,     4,    59,    60,    61,    62,    63,     4,     4,
       4,     8,     4,     4,     4,     4,     4,     4,   495,     4,
       4,     4,     4,     4,     4,   209,     3,   504,     4,     8,
       4,     3,     3,     8,     4,   209,     4,    93,     4,   516,
       4,     8,   519,     4,   519,     4,     4,     4,     4,   504,
       4,   516,     4,   530,   516,     4,     4,   212,   516,   212,
     212,   516,     4,   540,   519,   530,     4,   540,   545,   209,
       4,     4,   545,     4,     4,   530,   516,   210,   210,   516,
     516,   210,   210,   516,   210,   540,   519,   212,   565,   210,
     545,   504,   211,   516,   545,   545,   211,   530,     4,     4,
       4,   211,   210,   516,   210,   212,   519,   530,   210,   212,
     565,   212,     4,   516,   516,   516,     4,   530,   212,   212,
       4,   212,     4,     4,   210,   516,   516,   540,   530,   107,
     108,     4,   545,   516,     4,     4,   516,     4,   212,     4,
       4,   212,   212,   516,   516,     4,   516,     4,   516,   516,
       4,   210,   565,   209,   516,     4,   516,     4,     4,   516,
       4,   516,   516,     4,   516,  1200,   516,   516,     4,   516,
     212,   212,   516,   212,   516,     4,     4,   516,   519,   516,
       4,     4,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,     4,   212,   212,   210,   210,
       4,   179,   180,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,     4,     4,     4,     4,
       4,     4,     4,     4,   210,     4,     4,     4,   705,     4,
     707,   209,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   210,     4,   704,     4,     4,     4,   212,     4,   212,
     212,     4,   707,     4,     4,     4,     4,   212,     4,   210,
     210,     4,     4,   210,     4,   742,   743,   212,   745,   212,
     210,     4,   749,     7,   209,     7,   174,     7,     7,     7,
     209,   209,     7,     5,   209,   209,   209,   742,   743,   744,
     745,     5,     5,     5,   707,   209,     5,     7,   209,    30,
      31,    32,    33,    34,     5,     5,     5,     5,   209,   209,
       7,     7,     7,     7,     7,     5,     7,     5,   209,   209,
     209,     5,   209,   209,   209,     7,   209,     5,     7,   742,
     743,   744,   745,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,   209,     7,     7,   209,    78,    79,    80,
      81,    82,    83,    84,    85,    86,   209,    88,    89,    90,
       7,    92,     7,     7,   209,     7,   209,   209,     7,   209,
     209,   209,   103,     7,   105,   209,   107,   108,   109,   110,
     111,   112,   209,   209,   209,     7,   117,   118,   119,   209,
     209,   122,   209,   209,   209,   126,   127,   209,   209,     4,
       4,     4,     4,   134,     4,     4,     4,     4,     4,     4,
       4,     3,   209,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     3,   212,     6,     3,     6,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   683,     6,   705,     4,     6,     8,     4,   179,   180,
       4,     4,     4,     4,     4,   210,   210,     4,     4,     4,
     212,     4,     4,   210,     4,   210,   210,     4,     4,   210,
       3,   210,   210,   210,   210,   210,     6,     4,   209,     8,
       8,     4,     8,   210,   210,     3,   210,   210,     8,     4,
     210,   212,   210,   212,   210,   212,     4,   212,   209,     4,
       4,   209,   209,   209,   209,   209,   209,   209,     4,     7,
       5,     4,     4,     4,     4,     4,   696,   994,   210,   707,
     997,   210,   209,  1000,   997,   210,  1003,  1000,  1003,   994,
    1003,  1008,   994,   209,  1011,  1008,   994,  1014,  1003,   994,
     209,  1003,   997,  1008,  1008,  1000,  1011,   212,  1003,  1000,
    1000,  1028,   209,  1008,   994,  1032,  1011,   994,   994,   209,
     209,   994,   966,  1003,  1041,   504,  1003,  1003,  1041,  1046,
    1003,   994,  1008,  1028,  1051,  1008,  1051,  1032,  1011,   209,
    1003,   994,   209,  1038,   997,  1008,  1041,  1000,  1011,   212,
    1003,   994,   994,   994,   209,  1008,  1051,   209,  1011,   495,
    1003,  1003,  1003,   994,   994,   795,  1008,  1008,   993,  1011,
    1028,   994,  1003,  1003,   994,  1028,  1016,  1008,  1051,  1032,
    1003,   994,   994,  1003,   994,  1038,   994,   994,  1041,  1006,
    1003,  1003,   994,  1003,   994,  1003,  1003,   994,  1051,   994,
     994,  1003,   994,  1003,   994,   994,  1003,   994,  1003,  1003,
     994,  1003,   994,  1003,  1003,   994,  1003,   994,   988,  1003,
    1023,  1003,  1003,  1014,  1003,   996,  1003,   994,   548,  1005,
    1222,   999,   540,   997,   545,  1051,  1002,  1000,  1053,   516,
    1013,   766,  1011,  1228,   519,   745,  1032,   565,  1009,   706,
     569,  1238,  1260,  1280,    -1,    -1,    -1,   530,  1038,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1042,    -1,    -1,
    1051,    -1,  1046,    -1,    -1,    -1,    -1,  1178,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1222,    -1,  1222,    -1,  1222,
      -1,  1228,    -1,    -1,    -1,  1228,    -1,  1222,    -1,    -1,
    1222,  1238,    -1,  1228,  1228,  1238,    -1,  1222,    -1,    -1,
      -1,    -1,    -1,  1228,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1222,  1238,    -1,  1222,  1222,    -1,    -1,  1222,
      -1,    -1,  1228,    -1,    -1,  1228,    -1,    -1,    -1,  1222,
      -1,    -1,    -1,    -1,    -1,  1228,    -1,    -1,    -1,  1222,
      -1,    -1,    -1,    -1,    -1,  1228,    -1,    -1,    -1,  1222,
    1222,  1222,    -1,    -1,    -1,  1238,  1228,  1228,    -1,    -1,
      -1,  1222,  1222,    -1,    -1,    -1,    -1,  1228,    -1,  1222,
      -1,    -1,  1222,    -1,    -1,    -1,    -1,    -1,    -1,  1222,
    1222,    -1,  1222,    -1,  1222,  1222,    -1,    -1,    -1,    -1,
    1222,    -1,  1222,    -1,    -1,  1222,    -1,  1222,  1222,    -1,
    1222,    -1,  1222,  1222,    -1,  1222,    -1,    -1,  1222,    -1,
    1222,  1222,    -1,  1222,    -1,  1222,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    92,    93,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103,
      -1,    -1,    -1,   107,   108,    -1,   110,    -1,   112,    -1,
      -1,    -1,    -1,   117,   118,   119,    -1,    -1,   122,    -1,
      -1,    -1,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     134,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   179,   180,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   209
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,     0,     5,
       7,     9,   209,   210,   211,   212,   228,   229,   230,   235,
       7,   244,     7,   249,     7,   298,     7,   411,     7,   494,
       7,   510,     7,   446,     7,   452,     7,   476,     7,   387,
       7,   577,     7,   608,   236,   231,   245,   250,   299,   412,
     495,   511,   447,   453,   477,   388,   578,   609,   228,   237,
     238,   209,   233,   234,    10,   246,   248,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    91,    92,   102,   103,   104,   107,   108,
     112,   117,   118,   119,   120,   121,   127,   137,   140,   147,
     148,   152,   155,   159,   179,   180,   181,   182,   183,   184,
     193,   209,   243,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   266,   267,   269,
     270,   271,   272,   273,   274,   275,   278,   280,   282,   283,
     284,   286,   288,   289,   290,   291,   292,   293,   294,   312,
     314,   322,   324,   365,   374,   381,   395,   405,   429,   430,
     431,   432,   436,   444,   470,   500,   502,   504,   515,   517,
     519,   542,   556,   557,   565,   575,   606,   615,   639,    15,
      16,    19,    22,    23,    24,    25,   243,   296,   297,   300,
     302,   305,   308,   309,   310,   311,   500,   502,    88,    89,
      90,   105,   109,   110,   111,   122,   126,   134,   243,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   267,
     270,   271,   272,   273,   274,   275,   278,   280,   282,   283,
     284,   286,   288,   413,   414,   415,   417,   419,   421,   423,
     425,   427,   429,   430,   431,   432,   435,   470,   488,   500,
     502,   504,   515,   517,   519,   539,   106,   243,   425,   427,
     470,   496,   497,   498,   500,   502,   121,   128,   129,   130,
     131,   132,   133,   135,   243,   470,   500,   502,   512,   513,
     514,   515,   517,   519,   521,   525,   527,   529,   531,   533,
     535,   537,   444,    38,    93,    95,    96,    99,   100,   101,
     243,   342,   454,   455,   456,   457,   458,   459,   460,   462,
     464,   466,   467,   469,   500,   502,    94,    97,    98,   243,
     342,   458,   464,   478,   479,   480,   481,   482,   484,   485,
     486,   487,   500,   502,   138,   139,   243,   389,   390,   391,
     393,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   179,   180,   243,   500,   502,   579,
     580,   581,   582,   584,   585,   587,   588,   589,   592,   594,
     596,   597,   598,   600,   602,   604,    12,    13,   610,   611,
     612,   614,     6,     3,     4,     8,     3,   247,     3,     8,
     607,   295,   315,     4,     4,     4,   516,   518,   520,   313,
     323,   325,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   265,     4,     4,     4,     4,     4,   276,
     279,   281,     4,     4,     4,   406,   445,   471,     4,   268,
     437,   501,   503,   433,     4,     4,     4,   366,   543,   505,
     382,   396,     4,   375,   558,   566,   576,   285,   287,     4,
       4,     4,   616,   640,     4,     3,     8,   301,   303,   306,
       4,     4,     4,     4,     3,     8,   418,   420,   422,   489,
     416,   424,     4,   428,   426,   540,     3,     8,   499,     3,
       8,   538,   526,   528,   532,   530,   536,   534,   522,     8,
       3,     8,   461,   343,     4,   465,   463,   468,     4,     8,
       3,   483,     4,     4,     8,     3,   392,   394,     3,     8,
       4,   595,   583,     4,   586,     4,     4,   590,   593,     4,
       4,   599,   601,   603,   605,     3,     8,   613,     4,     3,
       8,   228,   228,   209,     4,     4,     4,     4,   212,   212,
     212,     4,     4,     4,     4,     4,     4,   210,   210,   210,
     210,   210,   212,   211,   211,   211,   210,   210,     4,   210,
     210,   212,   212,   212,     4,     4,     4,   212,   212,   212,
       4,     4,     4,   210,     4,     4,     4,     4,     4,   212,
     212,   212,     4,     4,     4,     4,     4,   210,     4,     4,
       4,     4,     4,     4,   212,   212,   212,     4,     4,   252,
       4,     4,     4,   212,   212,   210,   210,   297,     4,     4,
       4,     4,     4,     4,   210,     4,     4,     4,   414,     4,
     497,     4,     4,     4,     4,     4,     4,     4,     4,   514,
       4,     4,   210,     4,     4,     4,   212,   456,     4,   212,
     212,   480,     4,     4,   390,   212,     4,     4,   210,     4,
     210,   210,     4,     4,   212,   212,     4,     4,     4,     4,
     580,     4,   210,   611,     4,     7,     7,     7,     7,   209,
     209,   209,     7,     7,     5,   209,   175,   176,   177,   178,
     212,   277,   209,   209,     5,     5,     5,   209,     5,   230,
     232,   209,   113,   114,   115,   116,   434,     5,     5,     5,
       5,     7,     7,     7,     7,     7,   209,   209,     5,     7,
       5,   239,    17,    18,   304,    20,    21,   307,   209,   209,
     209,     5,   209,   209,   239,   209,     7,   209,   239,   209,
     209,   209,   209,   209,   209,   209,   209,   209,   209,   209,
     209,   209,   209,   232,   209,   209,   209,    18,   173,   591,
     174,   277,   209,   209,   209,     5,   228,   251,   610,   296,
      27,    28,   316,   317,   318,   320,    38,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    59,    60,    61,    62,    63,   243,   330,   331,   332,
     335,   337,   339,   341,   342,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   356,   357,   359,   361,   363,
     330,     7,   326,   327,   328,     7,   407,   408,   409,     7,
     448,   449,   450,     7,   472,   473,   474,     7,   438,   439,
     440,   128,   129,   130,   131,   133,   367,   368,   369,   370,
     371,   372,   373,     7,   544,   545,     7,   506,   507,   508,
       7,   383,   384,   385,   141,   142,   143,   144,   145,   146,
     397,   398,   399,   400,   401,   402,   403,   404,   149,   150,
     151,   243,   376,   377,   378,   379,   380,   500,   502,   153,
     154,   243,   500,   502,   559,   560,   561,   563,   156,   157,
     158,   209,   500,   502,   567,   568,   569,   570,   572,   573,
     579,     7,   617,   618,   194,   195,   243,   641,   642,   643,
     644,   240,     7,   490,   491,   492,   136,   521,   523,   541,
     326,     8,     8,     8,   319,   321,     3,     8,   333,   336,
     338,   340,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   354,     4,   358,   360,   362,   364,     3,     8,
       8,   329,     6,     3,   410,     6,     3,   451,     6,     3,
     475,     6,     3,   441,     6,     3,     3,     6,   546,     3,
       6,   509,     6,     3,   386,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     562,   564,     3,     8,     4,   571,     4,   574,     3,     8,
       8,   619,     3,     6,     4,     4,     3,     8,   209,   241,
     242,   493,     6,     3,   524,     8,     6,     4,     4,   317,
       4,     4,     4,     4,   210,   212,   210,   212,   210,   210,
     210,   210,   210,   210,     4,   210,     4,     4,     4,     4,
     331,   330,   328,   413,   409,   454,   450,   478,   474,   243,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     267,   270,   271,   272,   273,   274,   275,   278,   280,   282,
     283,   284,   286,   288,   342,   405,   423,   425,   427,   429,
     430,   431,   432,   442,   443,   470,   500,   502,   515,   517,
     519,   539,   440,   368,   123,   124,   125,   243,   253,   254,
     255,   342,   444,   470,   500,   502,   515,   517,   519,   547,
     548,   549,   550,   551,   553,   555,   545,   512,   508,   389,
     385,   210,   210,   210,   210,   210,   210,   398,   212,   210,
     210,   377,     4,     4,   560,   212,     4,   210,     4,   568,
     185,   187,   188,   243,   342,   500,   502,   620,   621,   622,
     623,   625,   618,   212,   212,   642,     6,     3,   496,   492,
       4,   209,   209,    39,    40,    41,   334,   209,   209,   209,
      56,    57,    58,   355,   209,   209,   209,   209,     8,     8,
       8,     8,     3,     8,   552,   554,     4,     8,     3,     8,
       8,   209,   209,   209,   228,   626,     4,   624,     3,     8,
     209,     8,   239,   443,     4,     4,   212,   549,     4,   210,
       4,   621,   209,   209,     5,   209,     7,   627,   628,   629,
       3,     6,   186,   189,   190,   191,   192,   630,   631,   632,
     634,   635,   636,   637,   628,   633,     4,     4,     4,   638,
       3,     8,     4,   212,   210,   210,     4,   631,   209,   209
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   213,   215,   214,   216,   214,   217,   214,   218,   214,
     219,   214,   220,   214,   221,   214,   222,   214,   223,   214,
     224,   214,   225,   214,   226,   214,   227,   214,   228,   228,
     228,   228,   228,   228,   228,   229,   231,   230,   232,   233,
     233,   234,   234,   234,   236,   235,   237,   237,   238,   238,
     238,   240,   239,   241,   241,   242,   242,   242,   243,   245,
     244,   247,   246,   246,   248,   250,   249,   251,   251,   251,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   252,   252,   252,   252,   252,
     252,   252,   252,   252,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   265,   264,   266,   268,
     267,   269,   270,   271,   272,   273,   274,   276,   275,   277,
     277,   277,   277,   277,   279,   278,   281,   280,   282,   283,
     285,   284,   287,   286,   288,   289,   290,   291,   292,   293,
     295,   294,   296,   296,   296,   297,   297,   297,   297,   297,
     297,   297,   297,   297,   297,   299,   298,   301,   300,   303,
     302,   304,   304,   306,   305,   307,   307,   308,   309,   310,
     311,   313,   312,   315,   314,   316,   316,   316,   317,   317,
     319,   318,   321,   320,   323,   322,   325,   324,   326,   326,
     327,   327,   327,   329,   328,   330,   330,   330,   331,   331,
     331,   331,   331,   331,   331,   331,   331,   331,   331,   331,
     331,   331,   331,   331,   331,   331,   331,   331,   331,   331,
     333,   332,   334,   334,   334,   336,   335,   338,   337,   340,
     339,   341,   343,   342,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   354,   353,   355,   355,   355,   356,   358,
     357,   360,   359,   362,   361,   364,   363,   366,   365,   367,
     367,   367,   368,   368,   368,   368,   368,   369,   370,   371,
     372,   373,   375,   374,   376,   376,   376,   377,   377,   377,
     377,   377,   377,   378,   379,   380,   382,   381,   383,   383,
     384,   384,   384,   386,   385,   388,   387,   389,   389,   389,
     389,   390,   390,   392,   391,   394,   393,   396,   395,   397,
     397,   397,   398,   398,   398,   398,   398,   398,   399,   400,
     401,   402,   403,   404,   406,   405,   407,   407,   408,   408,
     408,   410,   409,   412,   411,   413,   413,   413,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   416,   415,   418,   417,   420,   419,
     422,   421,   424,   423,   426,   425,   428,   427,   429,   430,
     431,   433,   432,   434,   434,   434,   434,   435,   437,   436,
     438,   438,   439,   439,   439,   441,   440,   442,   442,   442,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   443,   443,
     443,   445,   444,   447,   446,   448,   448,   449,   449,   449,
     451,   450,   453,   452,   454,   454,   455,   455,   455,   456,
     456,   456,   456,   456,   456,   456,   456,   456,   456,   457,
     458,   459,   461,   460,   463,   462,   465,   464,   466,   468,
     467,   469,   471,   470,   472,   472,   473,   473,   473,   475,
     474,   477,   476,   478,   478,   479,   479,   479,   480,   480,
     480,   480,   480,   480,   480,   480,   480,   481,   483,   482,
     484,   485,   486,   487,   489,   488,   490,   490,   491,   491,
     491,   493,   492,   495,   494,   496,   496,   496,   497,   497,
     497,   497,   497,   497,   497,   499,   498,   501,   500,   503,
     502,   505,   504,   506,   506,   507,   507,   507,   509,   508,
     511,   510,   512,   512,   513,   513,   513,   514,   514,   514,
     514,   514,   514,   514,   514,   514,   514,   514,   514,   514,
     514,   514,   516,   515,   518,   517,   520,   519,   522,   521,
     524,   523,   526,   525,   528,   527,   530,   529,   532,   531,
     534,   533,   536,   535,   538,   537,   540,   539,   541,   541,
     543,   542,   544,   544,   544,   546,   545,   547,   547,   548,
     548,   548,   549,   549,   549,   549,   549,   549,   549,   549,
     549,   549,   549,   549,   549,   549,   549,   550,   552,   551,
     554,   553,   555,   556,   558,   557,   559,   559,   559,   560,
     560,   560,   560,   560,   562,   561,   564,   563,   566,   565,
     567,   567,   567,   568,   568,   568,   568,   568,   568,   569,
     571,   570,   572,   574,   573,   576,   575,   578,   577,   579,
     579,   579,   580,   580,   580,   580,   580,   580,   580,   580,
     580,   580,   580,   580,   580,   580,   580,   580,   580,   580,
     581,   583,   582,   584,   586,   585,   587,   588,   590,   589,
     591,   591,   593,   592,   595,   594,   596,   597,   599,   598,
     601,   600,   603,   602,   605,   604,   607,   606,   609,   608,
     610,   610,   610,   611,   611,   613,   612,   614,   616,   615,
     617,   617,   617,   619,   618,   620,   620,   620,   621,   621,
     621,   621,   621,   621,   621,   622,   624,   623,   626,   625,
     627,   627,   627,   629,   628,   630,   630,   630,   631,   631,
     631,   631,   631,   633,   632,   634,   635,   636,   638,   637,
     640,   639,   641,   641,   641,   642,   642,   642,   643,   644
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
       0,     6,     1,     3,     2,     1,     1,     1,     3,     3
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
  "ignore-rai-link-selection", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   302,   302,   302,   303,   303,   304,   304,   305,   305,
     306,   306,   307,   307,   308,   308,   309,   309,   310,   310,
     311,   311,   312,   312,   313,   313,   314,   314,   322,   323,
     324,   325,   326,   327,   328,   331,   336,   336,   347,   350,
     351,   354,   359,   365,   370,   370,   377,   378,   381,   385,
     389,   395,   395,   402,   403,   406,   410,   414,   424,   433,
     433,   448,   448,   462,   465,   471,   471,   480,   481,   482,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   543,   544,   545,   546,   547,   548,
     549,   550,   551,   552,   553,   556,   562,   568,   574,   580,
     586,   592,   598,   604,   610,   616,   622,   622,   631,   637,
     637,   646,   652,   658,   664,   670,   676,   682,   682,   691,
     694,   697,   700,   703,   709,   709,   718,   718,   727,   733,
     739,   739,   748,   748,   757,   763,   769,   775,   781,   787,
     793,   793,   805,   806,   807,   812,   813,   814,   815,   816,
     817,   818,   819,   820,   821,   824,   824,   833,   833,   844,
     844,   852,   853,   856,   856,   864,   866,   870,   876,   882,
     888,   894,   894,   907,   907,   918,   919,   920,   925,   926,
     929,   929,   948,   948,   966,   966,   979,   979,   990,   991,
     994,   995,   996,  1001,  1001,  1011,  1012,  1013,  1018,  1019,
    1020,  1021,  1022,  1023,  1024,  1025,  1026,  1027,  1028,  1029,
    1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,  1039,
    1042,  1042,  1050,  1051,  1052,  1055,  1055,  1064,  1064,  1073,
    1073,  1082,  1088,  1088,  1097,  1103,  1109,  1115,  1121,  1127,
    1133,  1139,  1145,  1151,  1151,  1159,  1160,  1161,  1164,  1170,
    1170,  1179,  1179,  1188,  1188,  1197,  1197,  1206,  1206,  1217,
    1218,  1219,  1224,  1225,  1226,  1227,  1228,  1231,  1236,  1241,
    1246,  1251,  1258,  1258,  1271,  1272,  1273,  1278,  1279,  1280,
    1281,  1282,  1283,  1286,  1292,  1298,  1304,  1304,  1315,  1316,
    1319,  1320,  1321,  1326,  1326,  1336,  1336,  1346,  1347,  1348,
    1351,  1354,  1355,  1358,  1358,  1367,  1367,  1376,  1376,  1388,
    1389,  1390,  1395,  1396,  1397,  1398,  1399,  1400,  1403,  1409,
    1415,  1421,  1427,  1433,  1442,  1442,  1456,  1457,  1460,  1461,
    1462,  1471,  1471,  1497,  1497,  1508,  1509,  1510,  1516,  1517,
    1518,  1519,  1520,  1521,  1522,  1523,  1524,  1525,  1526,  1527,
    1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,  1536,  1537,
    1538,  1539,  1540,  1541,  1542,  1543,  1544,  1545,  1546,  1547,
    1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,  1556,  1557,
    1558,  1559,  1560,  1561,  1564,  1564,  1573,  1573,  1582,  1582,
    1591,  1591,  1600,  1600,  1609,  1609,  1618,  1618,  1629,  1635,
    1641,  1647,  1647,  1655,  1656,  1657,  1658,  1661,  1669,  1669,
    1681,  1682,  1686,  1687,  1688,  1693,  1693,  1701,  1702,  1703,
    1708,  1709,  1710,  1711,  1712,  1713,  1714,  1715,  1716,  1717,
    1718,  1719,  1720,  1721,  1722,  1723,  1724,  1725,  1726,  1727,
    1728,  1729,  1730,  1731,  1732,  1733,  1734,  1735,  1736,  1737,
    1738,  1739,  1740,  1741,  1742,  1743,  1744,  1745,  1746,  1747,
    1748,  1755,  1755,  1769,  1769,  1778,  1779,  1782,  1783,  1784,
    1791,  1791,  1806,  1806,  1820,  1821,  1824,  1825,  1826,  1831,
    1832,  1833,  1834,  1835,  1836,  1837,  1838,  1839,  1840,  1843,
    1845,  1851,  1853,  1853,  1862,  1862,  1871,  1871,  1880,  1882,
    1882,  1891,  1901,  1901,  1914,  1915,  1920,  1921,  1922,  1929,
    1929,  1941,  1941,  1953,  1954,  1959,  1960,  1961,  1968,  1969,
    1970,  1971,  1972,  1973,  1974,  1975,  1976,  1979,  1981,  1981,
    1990,  1992,  1994,  2000,  2009,  2009,  2022,  2023,  2026,  2027,
    2028,  2033,  2033,  2043,  2043,  2053,  2054,  2055,  2060,  2061,
    2062,  2063,  2064,  2065,  2066,  2069,  2069,  2078,  2078,  2103,
    2103,  2133,  2133,  2144,  2145,  2148,  2149,  2150,  2155,  2155,
    2164,  2164,  2173,  2174,  2177,  2178,  2179,  2185,  2186,  2187,
    2188,  2189,  2190,  2191,  2192,  2193,  2194,  2195,  2196,  2197,
    2198,  2199,  2202,  2202,  2211,  2211,  2220,  2220,  2229,  2229,
    2238,  2238,  2249,  2249,  2258,  2258,  2267,  2267,  2276,  2276,
    2285,  2285,  2294,  2294,  2303,  2303,  2317,  2317,  2328,  2329,
    2335,  2335,  2346,  2347,  2348,  2353,  2353,  2363,  2364,  2367,
    2368,  2369,  2374,  2375,  2376,  2377,  2378,  2379,  2380,  2381,
    2382,  2383,  2384,  2385,  2386,  2387,  2388,  2391,  2393,  2393,
    2402,  2402,  2411,  2419,  2427,  2427,  2438,  2439,  2440,  2445,
    2446,  2447,  2448,  2449,  2452,  2452,  2461,  2461,  2473,  2473,
    2486,  2487,  2488,  2493,  2494,  2495,  2496,  2497,  2498,  2501,
    2507,  2507,  2516,  2522,  2522,  2532,  2532,  2545,  2545,  2555,
    2556,  2557,  2562,  2563,  2564,  2565,  2566,  2567,  2568,  2569,
    2570,  2571,  2572,  2573,  2574,  2575,  2576,  2577,  2578,  2579,
    2582,  2588,  2588,  2597,  2603,  2603,  2612,  2618,  2624,  2624,
    2633,  2634,  2637,  2637,  2647,  2647,  2657,  2664,  2671,  2671,
    2680,  2680,  2690,  2690,  2700,  2700,  2712,  2712,  2724,  2724,
    2734,  2735,  2736,  2742,  2743,  2746,  2746,  2757,  2765,  2765,
    2778,  2779,  2780,  2786,  2786,  2794,  2795,  2796,  2801,  2802,
    2803,  2804,  2805,  2806,  2807,  2810,  2816,  2816,  2825,  2825,
    2836,  2837,  2838,  2843,  2843,  2851,  2852,  2853,  2858,  2859,
    2860,  2861,  2862,  2865,  2865,  2874,  2880,  2886,  2892,  2892,
    2901,  2901,  2912,  2913,  2914,  2919,  2920,  2921,  2924,  2930
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
#line 6310 "dhcp4_parser.cc"

#line 2936 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
