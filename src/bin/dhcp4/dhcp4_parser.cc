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
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 286 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 286 "dhcp4_parser.yy"
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
#line 295 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 296 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 297 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 298 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 299 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 300 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 301 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 302 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 303 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 304 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 305 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 306 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 307 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 315 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 316 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 317 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 318 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 319 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 320 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 321 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 324 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 329 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 334 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 340 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 347 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 352 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 358 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 363 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 366 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 374 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 378 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 382 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 388 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 390 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 399 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 403 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 407 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 417 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 426 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 431 "dhcp4_parser.yy"
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
#line 441 "dhcp4_parser.yy"
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
#line 450 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 458 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 464 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 468 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 475 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 134: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 548 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 135: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 554 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 136: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 560 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 137: // renew_timer: "renew-timer" ":" "integer"
#line 566 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 138: // rebind_timer: "rebind-timer" ":" "integer"
#line 572 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 139: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 578 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 140: // t1_percent: "t1-percent" ":" "floating point"
#line 584 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 141: // t2_percent: "t2-percent" ":" "floating point"
#line 590 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 142: // cache_threshold: "cache-threshold" ":" "floating point"
#line 596 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 143: // cache_max_age: "cache-max-age" ":" "integer"
#line 602 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 144: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 608 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 145: // $@20: %empty
#line 614 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 146: // server_tag: "server-tag" $@20 ":" "constant string"
#line 617 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 147: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 623 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 148: // echo_client_id: "echo-client-id" ":" "boolean"
#line 629 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1270 "dhcp4_parser.cc"
    break;

  case 149: // match_client_id: "match-client-id" ":" "boolean"
#line 635 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1280 "dhcp4_parser.cc"
    break;

  case 150: // authoritative: "authoritative" ":" "boolean"
#line 641 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1290 "dhcp4_parser.cc"
    break;

  case 151: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 647 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1300 "dhcp4_parser.cc"
    break;

  case 152: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 653 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1310 "dhcp4_parser.cc"
    break;

  case 153: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 659 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1320 "dhcp4_parser.cc"
    break;

  case 154: // $@21: %empty
#line 665 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 155: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 668 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1338 "dhcp4_parser.cc"
    break;

  case 156: // ddns_replace_client_name_value: "when-present"
#line 674 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1346 "dhcp4_parser.cc"
    break;

  case 157: // ddns_replace_client_name_value: "never"
#line 677 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1354 "dhcp4_parser.cc"
    break;

  case 158: // ddns_replace_client_name_value: "always"
#line 680 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1362 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name_value: "when-not-present"
#line 683 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1370 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "boolean"
#line 686 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1379 "dhcp4_parser.cc"
    break;

  case 161: // $@22: %empty
#line 692 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1388 "dhcp4_parser.cc"
    break;

  case 162: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 695 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1398 "dhcp4_parser.cc"
    break;

  case 163: // $@23: %empty
#line 701 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 164: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 704 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 165: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 710 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1427 "dhcp4_parser.cc"
    break;

  case 166: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 716 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1437 "dhcp4_parser.cc"
    break;

  case 167: // $@24: %empty
#line 722 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 168: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 725 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 169: // $@25: %empty
#line 731 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 170: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 734 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 171: // store_extended_info: "store-extended-info" ":" "boolean"
#line 740 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1485 "dhcp4_parser.cc"
    break;

  case 172: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 746 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1495 "dhcp4_parser.cc"
    break;

  case 173: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 752 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 174: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 758 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1515 "dhcp4_parser.cc"
    break;

  case 175: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 764 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1525 "dhcp4_parser.cc"
    break;

  case 176: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 770 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1535 "dhcp4_parser.cc"
    break;

  case 177: // $@26: %empty
#line 776 "dhcp4_parser.yy"
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
#line 782 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1557 "dhcp4_parser.cc"
    break;

  case 181: // interfaces_config_params: interfaces_config_params ","
#line 790 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1565 "dhcp4_parser.cc"
    break;

  case 192: // $@27: %empty
#line 807 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1575 "dhcp4_parser.cc"
    break;

  case 193: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 811 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1584 "dhcp4_parser.cc"
    break;

  case 194: // $@28: %empty
#line 816 "dhcp4_parser.yy"
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
#line 822 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1605 "dhcp4_parser.cc"
    break;

  case 196: // $@29: %empty
#line 827 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 197: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 830 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1623 "dhcp4_parser.cc"
    break;

  case 198: // socket_type: "raw"
#line 835 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1629 "dhcp4_parser.cc"
    break;

  case 199: // socket_type: "udp"
#line 836 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1635 "dhcp4_parser.cc"
    break;

  case 200: // $@30: %empty
#line 839 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1644 "dhcp4_parser.cc"
    break;

  case 201: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 842 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1653 "dhcp4_parser.cc"
    break;

  case 202: // outbound_interface_value: "same-as-inbound"
#line 847 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1661 "dhcp4_parser.cc"
    break;

  case 203: // outbound_interface_value: "use-routing"
#line 849 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1669 "dhcp4_parser.cc"
    break;

  case 204: // re_detect: "re-detect" ":" "boolean"
#line 853 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1679 "dhcp4_parser.cc"
    break;

  case 205: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 859 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1689 "dhcp4_parser.cc"
    break;

  case 206: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 865 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1699 "dhcp4_parser.cc"
    break;

  case 207: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 871 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1709 "dhcp4_parser.cc"
    break;

  case 208: // $@31: %empty
#line 877 "dhcp4_parser.yy"
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
#line 883 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1732 "dhcp4_parser.cc"
    break;

  case 210: // $@32: %empty
#line 890 "dhcp4_parser.yy"
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
#line 896 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1753 "dhcp4_parser.cc"
    break;

  case 214: // sanity_checks_params: sanity_checks_params ","
#line 903 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1761 "dhcp4_parser.cc"
    break;

  case 216: // $@33: %empty
#line 910 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1770 "dhcp4_parser.cc"
    break;

  case 217: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 913 "dhcp4_parser.yy"
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
#line 929 "dhcp4_parser.yy"
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
#line 935 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1813 "dhcp4_parser.cc"
    break;

  case 220: // $@35: %empty
#line 942 "dhcp4_parser.yy"
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
#line 948 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1834 "dhcp4_parser.cc"
    break;

  case 226: // not_empty_database_list: not_empty_database_list ","
#line 959 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1842 "dhcp4_parser.cc"
    break;

  case 227: // $@36: %empty
#line 964 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1852 "dhcp4_parser.cc"
    break;

  case 228: // database: "{" $@36 database_map_params "}"
#line 968 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1862 "dhcp4_parser.cc"
    break;

  case 231: // database_map_params: database_map_params ","
#line 976 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1870 "dhcp4_parser.cc"
    break;

  case 251: // $@37: %empty
#line 1002 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1879 "dhcp4_parser.cc"
    break;

  case 252: // database_type: "type" $@37 ":" db_type
#line 1005 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1888 "dhcp4_parser.cc"
    break;

  case 253: // db_type: "memfile"
#line 1010 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1894 "dhcp4_parser.cc"
    break;

  case 254: // db_type: "mysql"
#line 1011 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1900 "dhcp4_parser.cc"
    break;

  case 255: // db_type: "postgresql"
#line 1012 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1906 "dhcp4_parser.cc"
    break;

  case 256: // $@38: %empty
#line 1015 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1915 "dhcp4_parser.cc"
    break;

  case 257: // user: "user" $@38 ":" "constant string"
#line 1018 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1925 "dhcp4_parser.cc"
    break;

  case 258: // $@39: %empty
#line 1024 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1934 "dhcp4_parser.cc"
    break;

  case 259: // password: "password" $@39 ":" "constant string"
#line 1027 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1944 "dhcp4_parser.cc"
    break;

  case 260: // $@40: %empty
#line 1033 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 261: // host: "host" $@40 ":" "constant string"
#line 1036 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1963 "dhcp4_parser.cc"
    break;

  case 262: // port: "port" ":" "integer"
#line 1042 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1973 "dhcp4_parser.cc"
    break;

  case 263: // $@41: %empty
#line 1048 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1982 "dhcp4_parser.cc"
    break;

  case 264: // name: "name" $@41 ":" "constant string"
#line 1051 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1992 "dhcp4_parser.cc"
    break;

  case 265: // persist: "persist" ":" "boolean"
#line 1057 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2002 "dhcp4_parser.cc"
    break;

  case 266: // lfc_interval: "lfc-interval" ":" "integer"
#line 1063 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2012 "dhcp4_parser.cc"
    break;

  case 267: // readonly: "readonly" ":" "boolean"
#line 1069 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2022 "dhcp4_parser.cc"
    break;

  case 268: // connect_timeout: "connect-timeout" ":" "integer"
#line 1075 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2032 "dhcp4_parser.cc"
    break;

  case 269: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1081 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2042 "dhcp4_parser.cc"
    break;

  case 270: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1087 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2052 "dhcp4_parser.cc"
    break;

  case 271: // $@42: %empty
#line 1093 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2061 "dhcp4_parser.cc"
    break;

  case 272: // on_fail: "on-fail" $@42 ":" on_fail_mode
#line 1096 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2070 "dhcp4_parser.cc"
    break;

  case 273: // on_fail_mode: "stop-retry-exit"
#line 1101 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2076 "dhcp4_parser.cc"
    break;

  case 274: // on_fail_mode: "serve-retry-exit"
#line 1102 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2082 "dhcp4_parser.cc"
    break;

  case 275: // on_fail_mode: "serve-retry-continue"
#line 1103 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2088 "dhcp4_parser.cc"
    break;

  case 276: // max_row_errors: "max-row-errors" ":" "integer"
#line 1106 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2098 "dhcp4_parser.cc"
    break;

  case 277: // $@43: %empty
#line 1112 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2107 "dhcp4_parser.cc"
    break;

  case 278: // trust_anchor: "trust-anchor" $@43 ":" "constant string"
#line 1115 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2117 "dhcp4_parser.cc"
    break;

  case 279: // $@44: %empty
#line 1121 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2126 "dhcp4_parser.cc"
    break;

  case 280: // cert_file: "cert-file" $@44 ":" "constant string"
#line 1124 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2136 "dhcp4_parser.cc"
    break;

  case 281: // $@45: %empty
#line 1130 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2145 "dhcp4_parser.cc"
    break;

  case 282: // key_file: "key-file" $@45 ":" "constant string"
#line 1133 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2155 "dhcp4_parser.cc"
    break;

  case 283: // $@46: %empty
#line 1139 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2164 "dhcp4_parser.cc"
    break;

  case 284: // cipher_list: "cipher-list" $@46 ":" "constant string"
#line 1142 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2174 "dhcp4_parser.cc"
    break;

  case 285: // $@47: %empty
#line 1148 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2186 "dhcp4_parser.cc"
    break;

  case 286: // host_reservation_identifiers: "host-reservation-identifiers" $@47 ":" "[" host_reservation_identifiers_list "]"
#line 1154 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2195 "dhcp4_parser.cc"
    break;

  case 289: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1161 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2203 "dhcp4_parser.cc"
    break;

  case 295: // duid_id: "duid"
#line 1173 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2212 "dhcp4_parser.cc"
    break;

  case 296: // hw_address_id: "hw-address"
#line 1178 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2221 "dhcp4_parser.cc"
    break;

  case 297: // circuit_id: "circuit-id"
#line 1183 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2230 "dhcp4_parser.cc"
    break;

  case 298: // client_id: "client-id"
#line 1188 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2239 "dhcp4_parser.cc"
    break;

  case 299: // flex_id: "flex-id"
#line 1193 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2248 "dhcp4_parser.cc"
    break;

  case 300: // $@48: %empty
#line 1200 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2260 "dhcp4_parser.cc"
    break;

  case 301: // dhcp_multi_threading: "multi-threading" $@48 ":" "{" multi_threading_params "}"
#line 1206 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2271 "dhcp4_parser.cc"
    break;

  case 304: // multi_threading_params: multi_threading_params ","
#line 1215 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2279 "dhcp4_parser.cc"
    break;

  case 311: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1228 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2289 "dhcp4_parser.cc"
    break;

  case 312: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1234 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2299 "dhcp4_parser.cc"
    break;

  case 313: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1240 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2309 "dhcp4_parser.cc"
    break;

  case 314: // $@49: %empty
#line 1246 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2321 "dhcp4_parser.cc"
    break;

  case 315: // hooks_libraries: "hooks-libraries" $@49 ":" "[" hooks_libraries_list "]"
#line 1252 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2330 "dhcp4_parser.cc"
    break;

  case 320: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1263 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2338 "dhcp4_parser.cc"
    break;

  case 321: // $@50: %empty
#line 1268 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2348 "dhcp4_parser.cc"
    break;

  case 322: // hooks_library: "{" $@50 hooks_params "}"
#line 1272 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2358 "dhcp4_parser.cc"
    break;

  case 323: // $@51: %empty
#line 1278 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2368 "dhcp4_parser.cc"
    break;

  case 324: // sub_hooks_library: "{" $@51 hooks_params "}"
#line 1282 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2378 "dhcp4_parser.cc"
    break;

  case 327: // hooks_params: hooks_params ","
#line 1290 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2386 "dhcp4_parser.cc"
    break;

  case 331: // $@52: %empty
#line 1300 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2395 "dhcp4_parser.cc"
    break;

  case 332: // library: "library" $@52 ":" "constant string"
#line 1303 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2405 "dhcp4_parser.cc"
    break;

  case 333: // $@53: %empty
#line 1309 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2414 "dhcp4_parser.cc"
    break;

  case 334: // parameters: "parameters" $@53 ":" map_value
#line 1312 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2423 "dhcp4_parser.cc"
    break;

  case 335: // $@54: %empty
#line 1318 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 336: // expired_leases_processing: "expired-leases-processing" $@54 ":" "{" expired_leases_params "}"
#line 1324 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 339: // expired_leases_params: expired_leases_params ","
#line 1332 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2453 "dhcp4_parser.cc"
    break;

  case 346: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1345 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2463 "dhcp4_parser.cc"
    break;

  case 347: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1351 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 348: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1357 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2483 "dhcp4_parser.cc"
    break;

  case 349: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1363 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2493 "dhcp4_parser.cc"
    break;

  case 350: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1369 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2503 "dhcp4_parser.cc"
    break;

  case 351: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1375 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2513 "dhcp4_parser.cc"
    break;

  case 352: // $@55: %empty
#line 1384 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2525 "dhcp4_parser.cc"
    break;

  case 353: // subnet4_list: "subnet4" $@55 ":" "[" subnet4_list_content "]"
#line 1390 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2534 "dhcp4_parser.cc"
    break;

  case 358: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1404 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2542 "dhcp4_parser.cc"
    break;

  case 359: // $@56: %empty
#line 1413 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2552 "dhcp4_parser.cc"
    break;

  case 360: // subnet4: "{" $@56 subnet4_params "}"
#line 1417 "dhcp4_parser.yy"
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
#line 2578 "dhcp4_parser.cc"
    break;

  case 361: // $@57: %empty
#line 1439 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2588 "dhcp4_parser.cc"
    break;

  case 362: // sub_subnet4: "{" $@57 subnet4_params "}"
#line 1443 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2598 "dhcp4_parser.cc"
    break;

  case 365: // subnet4_params: subnet4_params ","
#line 1452 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2606 "dhcp4_parser.cc"
    break;

  case 411: // $@58: %empty
#line 1505 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2615 "dhcp4_parser.cc"
    break;

  case 412: // subnet: "subnet" $@58 ":" "constant string"
#line 1508 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2625 "dhcp4_parser.cc"
    break;

  case 413: // $@59: %empty
#line 1514 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2634 "dhcp4_parser.cc"
    break;

  case 414: // subnet_4o6_interface: "4o6-interface" $@59 ":" "constant string"
#line 1517 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2644 "dhcp4_parser.cc"
    break;

  case 415: // $@60: %empty
#line 1523 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2653 "dhcp4_parser.cc"
    break;

  case 416: // subnet_4o6_interface_id: "4o6-interface-id" $@60 ":" "constant string"
#line 1526 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2663 "dhcp4_parser.cc"
    break;

  case 417: // $@61: %empty
#line 1532 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2672 "dhcp4_parser.cc"
    break;

  case 418: // subnet_4o6_subnet: "4o6-subnet" $@61 ":" "constant string"
#line 1535 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2682 "dhcp4_parser.cc"
    break;

  case 419: // $@62: %empty
#line 1541 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2691 "dhcp4_parser.cc"
    break;

  case 420: // interface: "interface" $@62 ":" "constant string"
#line 1544 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2701 "dhcp4_parser.cc"
    break;

  case 421: // $@63: %empty
#line 1550 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2710 "dhcp4_parser.cc"
    break;

  case 422: // client_class: "client-class" $@63 ":" "constant string"
#line 1553 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2720 "dhcp4_parser.cc"
    break;

  case 423: // $@64: %empty
#line 1559 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2732 "dhcp4_parser.cc"
    break;

  case 424: // require_client_classes: "require-client-classes" $@64 ":" list_strings
#line 1565 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2741 "dhcp4_parser.cc"
    break;

  case 425: // reservations_global: "reservations-global" ":" "boolean"
#line 1570 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2751 "dhcp4_parser.cc"
    break;

  case 426: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1576 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2761 "dhcp4_parser.cc"
    break;

  case 427: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1582 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 428: // $@65: %empty
#line 1588 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2780 "dhcp4_parser.cc"
    break;

  case 429: // reservation_mode: "reservation-mode" $@65 ":" hr_mode
#line 1591 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2789 "dhcp4_parser.cc"
    break;

  case 430: // hr_mode: "disabled"
#line 1596 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2795 "dhcp4_parser.cc"
    break;

  case 431: // hr_mode: "out-of-pool"
#line 1597 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2801 "dhcp4_parser.cc"
    break;

  case 432: // hr_mode: "global"
#line 1598 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2807 "dhcp4_parser.cc"
    break;

  case 433: // hr_mode: "all"
#line 1599 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2813 "dhcp4_parser.cc"
    break;

  case 434: // id: "id" ":" "integer"
#line 1602 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2823 "dhcp4_parser.cc"
    break;

  case 435: // $@66: %empty
#line 1610 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2835 "dhcp4_parser.cc"
    break;

  case 436: // shared_networks: "shared-networks" $@66 ":" "[" shared_networks_content "]"
#line 1616 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2844 "dhcp4_parser.cc"
    break;

  case 441: // shared_networks_list: shared_networks_list ","
#line 1629 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2852 "dhcp4_parser.cc"
    break;

  case 442: // $@67: %empty
#line 1634 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2862 "dhcp4_parser.cc"
    break;

  case 443: // shared_network: "{" $@67 shared_network_params "}"
#line 1638 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2870 "dhcp4_parser.cc"
    break;

  case 446: // shared_network_params: shared_network_params ","
#line 1644 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2878 "dhcp4_parser.cc"
    break;

  case 487: // $@68: %empty
#line 1695 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 488: // option_def_list: "option-def" $@68 ":" "[" option_def_list_content "]"
#line 1701 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2899 "dhcp4_parser.cc"
    break;

  case 489: // $@69: %empty
#line 1709 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2908 "dhcp4_parser.cc"
    break;

  case 490: // sub_option_def_list: "{" $@69 option_def_list "}"
#line 1712 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2916 "dhcp4_parser.cc"
    break;

  case 495: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1724 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2924 "dhcp4_parser.cc"
    break;

  case 496: // $@70: %empty
#line 1731 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2934 "dhcp4_parser.cc"
    break;

  case 497: // option_def_entry: "{" $@70 option_def_params "}"
#line 1735 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2946 "dhcp4_parser.cc"
    break;

  case 498: // $@71: %empty
#line 1746 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2956 "dhcp4_parser.cc"
    break;

  case 499: // sub_option_def: "{" $@71 option_def_params "}"
#line 1750 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2968 "dhcp4_parser.cc"
    break;

  case 504: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1766 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2976 "dhcp4_parser.cc"
    break;

  case 516: // code: "code" ":" "integer"
#line 1785 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2986 "dhcp4_parser.cc"
    break;

  case 518: // $@72: %empty
#line 1793 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2995 "dhcp4_parser.cc"
    break;

  case 519: // option_def_type: "type" $@72 ":" "constant string"
#line 1796 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3005 "dhcp4_parser.cc"
    break;

  case 520: // $@73: %empty
#line 1802 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3014 "dhcp4_parser.cc"
    break;

  case 521: // option_def_record_types: "record-types" $@73 ":" "constant string"
#line 1805 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3024 "dhcp4_parser.cc"
    break;

  case 522: // $@74: %empty
#line 1811 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3033 "dhcp4_parser.cc"
    break;

  case 523: // space: "space" $@74 ":" "constant string"
#line 1814 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 525: // $@75: %empty
#line 1822 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 526: // option_def_encapsulate: "encapsulate" $@75 ":" "constant string"
#line 1825 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 527: // option_def_array: "array" ":" "boolean"
#line 1831 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 528: // $@76: %empty
#line 1841 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3084 "dhcp4_parser.cc"
    break;

  case 529: // option_data_list: "option-data" $@76 ":" "[" option_data_list_content "]"
#line 1847 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3093 "dhcp4_parser.cc"
    break;

  case 534: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1862 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3101 "dhcp4_parser.cc"
    break;

  case 535: // $@77: %empty
#line 1869 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3111 "dhcp4_parser.cc"
    break;

  case 536: // option_data_entry: "{" $@77 option_data_params "}"
#line 1873 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3120 "dhcp4_parser.cc"
    break;

  case 537: // $@78: %empty
#line 1881 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3130 "dhcp4_parser.cc"
    break;

  case 538: // sub_option_data: "{" $@78 option_data_params "}"
#line 1885 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 543: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1901 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3147 "dhcp4_parser.cc"
    break;

  case 554: // $@79: %empty
#line 1921 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3156 "dhcp4_parser.cc"
    break;

  case 555: // option_data_data: "data" $@79 ":" "constant string"
#line 1924 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3166 "dhcp4_parser.cc"
    break;

  case 558: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1934 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3176 "dhcp4_parser.cc"
    break;

  case 559: // option_data_always_send: "always-send" ":" "boolean"
#line 1940 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 560: // $@80: %empty
#line 1949 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3198 "dhcp4_parser.cc"
    break;

  case 561: // pools_list: "pools" $@80 ":" "[" pools_list_content "]"
#line 1955 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3207 "dhcp4_parser.cc"
    break;

  case 566: // not_empty_pools_list: not_empty_pools_list ","
#line 1968 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3215 "dhcp4_parser.cc"
    break;

  case 567: // $@81: %empty
#line 1973 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 568: // pool_list_entry: "{" $@81 pool_params "}"
#line 1977 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3235 "dhcp4_parser.cc"
    break;

  case 569: // $@82: %empty
#line 1983 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3245 "dhcp4_parser.cc"
    break;

  case 570: // sub_pool4: "{" $@82 pool_params "}"
#line 1987 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3255 "dhcp4_parser.cc"
    break;

  case 573: // pool_params: pool_params ","
#line 1995 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3263 "dhcp4_parser.cc"
    break;

  case 581: // $@83: %empty
#line 2009 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3272 "dhcp4_parser.cc"
    break;

  case 582: // pool_entry: "pool" $@83 ":" "constant string"
#line 2012 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3282 "dhcp4_parser.cc"
    break;

  case 583: // $@84: %empty
#line 2018 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3290 "dhcp4_parser.cc"
    break;

  case 584: // user_context: "user-context" $@84 ":" map_value
#line 2020 "dhcp4_parser.yy"
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
#line 3317 "dhcp4_parser.cc"
    break;

  case 585: // $@85: %empty
#line 2043 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3325 "dhcp4_parser.cc"
    break;

  case 586: // comment: "comment" $@85 ":" "constant string"
#line 2045 "dhcp4_parser.yy"
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
#line 3354 "dhcp4_parser.cc"
    break;

  case 587: // $@86: %empty
#line 2073 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3366 "dhcp4_parser.cc"
    break;

  case 588: // reservations: "reservations" $@86 ":" "[" reservations_list "]"
#line 2079 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3375 "dhcp4_parser.cc"
    break;

  case 593: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2090 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3383 "dhcp4_parser.cc"
    break;

  case 594: // $@87: %empty
#line 2095 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3393 "dhcp4_parser.cc"
    break;

  case 595: // reservation: "{" $@87 reservation_params "}"
#line 2099 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3402 "dhcp4_parser.cc"
    break;

  case 596: // $@88: %empty
#line 2104 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3412 "dhcp4_parser.cc"
    break;

  case 597: // sub_reservation: "{" $@88 reservation_params "}"
#line 2108 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3421 "dhcp4_parser.cc"
    break;

  case 602: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2119 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3429 "dhcp4_parser.cc"
    break;

  case 618: // $@89: %empty
#line 2142 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3438 "dhcp4_parser.cc"
    break;

  case 619: // next_server: "next-server" $@89 ":" "constant string"
#line 2145 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3448 "dhcp4_parser.cc"
    break;

  case 620: // $@90: %empty
#line 2151 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3457 "dhcp4_parser.cc"
    break;

  case 621: // server_hostname: "server-hostname" $@90 ":" "constant string"
#line 2154 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3467 "dhcp4_parser.cc"
    break;

  case 622: // $@91: %empty
#line 2160 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3476 "dhcp4_parser.cc"
    break;

  case 623: // boot_file_name: "boot-file-name" $@91 ":" "constant string"
#line 2163 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3486 "dhcp4_parser.cc"
    break;

  case 624: // $@92: %empty
#line 2169 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3495 "dhcp4_parser.cc"
    break;

  case 625: // ip_address: "ip-address" $@92 ":" "constant string"
#line 2172 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3505 "dhcp4_parser.cc"
    break;

  case 626: // $@93: %empty
#line 2178 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3517 "dhcp4_parser.cc"
    break;

  case 627: // ip_addresses: "ip-addresses" $@93 ":" list_strings
#line 2184 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3526 "dhcp4_parser.cc"
    break;

  case 628: // $@94: %empty
#line 2189 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 629: // duid: "duid" $@94 ":" "constant string"
#line 2192 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 630: // $@95: %empty
#line 2198 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 631: // hw_address: "hw-address" $@95 ":" "constant string"
#line 2201 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3564 "dhcp4_parser.cc"
    break;

  case 632: // $@96: %empty
#line 2207 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 633: // client_id_value: "client-id" $@96 ":" "constant string"
#line 2210 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3583 "dhcp4_parser.cc"
    break;

  case 634: // $@97: %empty
#line 2216 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 635: // circuit_id_value: "circuit-id" $@97 ":" "constant string"
#line 2219 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3602 "dhcp4_parser.cc"
    break;

  case 636: // $@98: %empty
#line 2225 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 637: // flex_id_value: "flex-id" $@98 ":" "constant string"
#line 2228 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3621 "dhcp4_parser.cc"
    break;

  case 638: // $@99: %empty
#line 2234 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3630 "dhcp4_parser.cc"
    break;

  case 639: // hostname: "hostname" $@99 ":" "constant string"
#line 2237 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3640 "dhcp4_parser.cc"
    break;

  case 640: // $@100: %empty
#line 2243 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3652 "dhcp4_parser.cc"
    break;

  case 641: // reservation_client_classes: "client-classes" $@100 ":" list_strings
#line 2249 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3661 "dhcp4_parser.cc"
    break;

  case 642: // $@101: %empty
#line 2257 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3673 "dhcp4_parser.cc"
    break;

  case 643: // relay: "relay" $@101 ":" "{" relay_map "}"
#line 2263 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3682 "dhcp4_parser.cc"
    break;

  case 646: // $@102: %empty
#line 2275 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3694 "dhcp4_parser.cc"
    break;

  case 647: // client_classes: "client-classes" $@102 ":" "[" client_classes_list "]"
#line 2281 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3703 "dhcp4_parser.cc"
    break;

  case 650: // client_classes_list: client_classes_list ","
#line 2288 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3711 "dhcp4_parser.cc"
    break;

  case 651: // $@103: %empty
#line 2293 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3721 "dhcp4_parser.cc"
    break;

  case 652: // client_class_entry: "{" $@103 client_class_params "}"
#line 2297 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3731 "dhcp4_parser.cc"
    break;

  case 657: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2309 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3739 "dhcp4_parser.cc"
    break;

  case 673: // $@104: %empty
#line 2332 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3748 "dhcp4_parser.cc"
    break;

  case 674: // client_class_test: "test" $@104 ":" "constant string"
#line 2335 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3758 "dhcp4_parser.cc"
    break;

  case 675: // only_if_required: "only-if-required" ":" "boolean"
#line 2341 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3768 "dhcp4_parser.cc"
    break;

  case 676: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2349 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3778 "dhcp4_parser.cc"
    break;

  case 677: // $@105: %empty
#line 2357 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3790 "dhcp4_parser.cc"
    break;

  case 678: // control_socket: "control-socket" $@105 ":" "{" control_socket_params "}"
#line 2363 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3799 "dhcp4_parser.cc"
    break;

  case 681: // control_socket_params: control_socket_params ","
#line 2370 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3807 "dhcp4_parser.cc"
    break;

  case 687: // $@106: %empty
#line 2382 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3816 "dhcp4_parser.cc"
    break;

  case 688: // control_socket_type: "socket-type" $@106 ":" "constant string"
#line 2385 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3826 "dhcp4_parser.cc"
    break;

  case 689: // $@107: %empty
#line 2391 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3835 "dhcp4_parser.cc"
    break;

  case 690: // control_socket_name: "socket-name" $@107 ":" "constant string"
#line 2394 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3845 "dhcp4_parser.cc"
    break;

  case 691: // $@108: %empty
#line 2403 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3857 "dhcp4_parser.cc"
    break;

  case 692: // dhcp_queue_control: "dhcp-queue-control" $@108 ":" "{" queue_control_params "}"
#line 2409 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3868 "dhcp4_parser.cc"
    break;

  case 695: // queue_control_params: queue_control_params ","
#line 2418 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3876 "dhcp4_parser.cc"
    break;

  case 702: // enable_queue: "enable-queue" ":" "boolean"
#line 2431 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3886 "dhcp4_parser.cc"
    break;

  case 703: // $@109: %empty
#line 2437 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3895 "dhcp4_parser.cc"
    break;

  case 704: // queue_type: "queue-type" $@109 ":" "constant string"
#line 2440 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3905 "dhcp4_parser.cc"
    break;

  case 705: // capacity: "capacity" ":" "integer"
#line 2446 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3915 "dhcp4_parser.cc"
    break;

  case 706: // $@110: %empty
#line 2452 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3924 "dhcp4_parser.cc"
    break;

  case 707: // arbitrary_map_entry: "constant string" $@110 ":" value
#line 2455 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3933 "dhcp4_parser.cc"
    break;

  case 708: // $@111: %empty
#line 2462 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3945 "dhcp4_parser.cc"
    break;

  case 709: // dhcp_ddns: "dhcp-ddns" $@111 ":" "{" dhcp_ddns_params "}"
#line 2468 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3956 "dhcp4_parser.cc"
    break;

  case 710: // $@112: %empty
#line 2475 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3966 "dhcp4_parser.cc"
    break;

  case 711: // sub_dhcp_ddns: "{" $@112 dhcp_ddns_params "}"
#line 2479 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3976 "dhcp4_parser.cc"
    break;

  case 714: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2487 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3984 "dhcp4_parser.cc"
    break;

  case 733: // enable_updates: "enable-updates" ":" "boolean"
#line 2512 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3994 "dhcp4_parser.cc"
    break;

  case 734: // $@113: %empty
#line 2518 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4003 "dhcp4_parser.cc"
    break;

  case 735: // server_ip: "server-ip" $@113 ":" "constant string"
#line 2521 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4013 "dhcp4_parser.cc"
    break;

  case 736: // server_port: "server-port" ":" "integer"
#line 2527 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4023 "dhcp4_parser.cc"
    break;

  case 737: // $@114: %empty
#line 2533 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4032 "dhcp4_parser.cc"
    break;

  case 738: // sender_ip: "sender-ip" $@114 ":" "constant string"
#line 2536 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4042 "dhcp4_parser.cc"
    break;

  case 739: // sender_port: "sender-port" ":" "integer"
#line 2542 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4052 "dhcp4_parser.cc"
    break;

  case 740: // max_queue_size: "max-queue-size" ":" "integer"
#line 2548 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4062 "dhcp4_parser.cc"
    break;

  case 741: // $@115: %empty
#line 2554 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4071 "dhcp4_parser.cc"
    break;

  case 742: // ncr_protocol: "ncr-protocol" $@115 ":" ncr_protocol_value
#line 2557 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4080 "dhcp4_parser.cc"
    break;

  case 743: // ncr_protocol_value: "udp"
#line 2563 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4086 "dhcp4_parser.cc"
    break;

  case 744: // ncr_protocol_value: "tcp"
#line 2564 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4092 "dhcp4_parser.cc"
    break;

  case 745: // $@116: %empty
#line 2567 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4101 "dhcp4_parser.cc"
    break;

  case 746: // ncr_format: "ncr-format" $@116 ":" "JSON"
#line 2570 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4111 "dhcp4_parser.cc"
    break;

  case 747: // $@117: %empty
#line 2577 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4120 "dhcp4_parser.cc"
    break;

  case 748: // dep_qualifying_suffix: "qualifying-suffix" $@117 ":" "constant string"
#line 2580 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4130 "dhcp4_parser.cc"
    break;

  case 749: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2587 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4140 "dhcp4_parser.cc"
    break;

  case 750: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2594 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4150 "dhcp4_parser.cc"
    break;

  case 751: // $@118: %empty
#line 2601 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4159 "dhcp4_parser.cc"
    break;

  case 752: // dep_replace_client_name: "replace-client-name" $@118 ":" ddns_replace_client_name_value
#line 2604 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4168 "dhcp4_parser.cc"
    break;

  case 753: // $@119: %empty
#line 2610 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4177 "dhcp4_parser.cc"
    break;

  case 754: // dep_generated_prefix: "generated-prefix" $@119 ":" "constant string"
#line 2613 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4187 "dhcp4_parser.cc"
    break;

  case 755: // $@120: %empty
#line 2620 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4196 "dhcp4_parser.cc"
    break;

  case 756: // dep_hostname_char_set: "hostname-char-set" $@120 ":" "constant string"
#line 2623 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4206 "dhcp4_parser.cc"
    break;

  case 757: // $@121: %empty
#line 2630 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4215 "dhcp4_parser.cc"
    break;

  case 758: // dep_hostname_char_replacement: "hostname-char-replacement" $@121 ":" "constant string"
#line 2633 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4225 "dhcp4_parser.cc"
    break;

  case 759: // $@122: %empty
#line 2642 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4237 "dhcp4_parser.cc"
    break;

  case 760: // config_control: "config-control" $@122 ":" "{" config_control_params "}"
#line 2648 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4247 "dhcp4_parser.cc"
    break;

  case 761: // $@123: %empty
#line 2654 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4257 "dhcp4_parser.cc"
    break;

  case 762: // sub_config_control: "{" $@123 config_control_params "}"
#line 2658 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4266 "dhcp4_parser.cc"
    break;

  case 765: // config_control_params: config_control_params ","
#line 2666 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4274 "dhcp4_parser.cc"
    break;

  case 768: // $@124: %empty
#line 2676 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4286 "dhcp4_parser.cc"
    break;

  case 769: // config_databases: "config-databases" $@124 ":" "[" database_list "]"
#line 2682 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4295 "dhcp4_parser.cc"
    break;

  case 770: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2687 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4305 "dhcp4_parser.cc"
    break;

  case 771: // $@125: %empty
#line 2695 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4317 "dhcp4_parser.cc"
    break;

  case 772: // loggers: "loggers" $@125 ":" "[" loggers_entries "]"
#line 2701 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4326 "dhcp4_parser.cc"
    break;

  case 775: // loggers_entries: loggers_entries ","
#line 2710 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4334 "dhcp4_parser.cc"
    break;

  case 776: // $@126: %empty
#line 2716 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4344 "dhcp4_parser.cc"
    break;

  case 777: // logger_entry: "{" $@126 logger_params "}"
#line 2720 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4352 "dhcp4_parser.cc"
    break;

  case 780: // logger_params: logger_params ","
#line 2726 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4360 "dhcp4_parser.cc"
    break;

  case 788: // debuglevel: "debuglevel" ":" "integer"
#line 2740 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4370 "dhcp4_parser.cc"
    break;

  case 789: // $@127: %empty
#line 2746 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4379 "dhcp4_parser.cc"
    break;

  case 790: // severity: "severity" $@127 ":" "constant string"
#line 2749 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4389 "dhcp4_parser.cc"
    break;

  case 791: // $@128: %empty
#line 2755 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4401 "dhcp4_parser.cc"
    break;

  case 792: // output_options_list: "output_options" $@128 ":" "[" output_options_list_content "]"
#line 2761 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4410 "dhcp4_parser.cc"
    break;

  case 795: // output_options_list_content: output_options_list_content ","
#line 2768 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4418 "dhcp4_parser.cc"
    break;

  case 796: // $@129: %empty
#line 2773 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4428 "dhcp4_parser.cc"
    break;

  case 797: // output_entry: "{" $@129 output_params_list "}"
#line 2777 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4436 "dhcp4_parser.cc"
    break;

  case 800: // output_params_list: output_params_list ","
#line 2783 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4444 "dhcp4_parser.cc"
    break;

  case 806: // $@130: %empty
#line 2795 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4453 "dhcp4_parser.cc"
    break;

  case 807: // output: "output" $@130 ":" "constant string"
#line 2798 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4463 "dhcp4_parser.cc"
    break;

  case 808: // flush: "flush" ":" "boolean"
#line 2804 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4473 "dhcp4_parser.cc"
    break;

  case 809: // maxsize: "maxsize" ":" "integer"
#line 2810 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4483 "dhcp4_parser.cc"
    break;

  case 810: // maxver: "maxver" ":" "integer"
#line 2816 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4493 "dhcp4_parser.cc"
    break;

  case 811: // $@131: %empty
#line 2822 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4502 "dhcp4_parser.cc"
    break;

  case 812: // pattern: "pattern" $@131 ":" "constant string"
#line 2825 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4512 "dhcp4_parser.cc"
    break;

  case 813: // $@132: %empty
#line 2831 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4524 "dhcp4_parser.cc"
    break;

  case 814: // compatibility: "compatibility" $@132 ":" "{" compatibility_params "}"
#line 2837 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4533 "dhcp4_parser.cc"
    break;

  case 817: // compatibility_params: compatibility_params ","
#line 2844 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4541 "dhcp4_parser.cc"
    break;

  case 820: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2853 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4551 "dhcp4_parser.cc"
    break;


#line 4555 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -971;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     429,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,    39,    38,    26,    48,    62,    74,
      92,    96,   106,   114,   118,   140,   148,   163,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,    38,  -152,   125,   132,   126,   294,
     -50,   315,   -16,    80,   200,   -84,   617,    77,  -971,   181,
     154,   228,   209,   258,  -971,    34,  -971,  -971,  -971,  -971,
     264,   266,   275,  -971,  -971,  -971,  -971,  -971,  -971,   276,
     300,   325,   332,   348,   360,   361,   373,   377,   383,   384,
    -971,   385,   386,   387,   388,   389,  -971,  -971,  -971,   391,
     400,   401,  -971,  -971,  -971,   405,  -971,  -971,  -971,  -971,
     406,   408,   409,  -971,  -971,  -971,  -971,  -971,   412,  -971,
    -971,  -971,  -971,  -971,  -971,   415,   416,   417,  -971,  -971,
     419,  -971,    56,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
     421,   422,   423,   424,  -971,    79,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,   425,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
      85,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,    93,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,   343,   427,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,   426,
    -971,  -971,   428,  -971,  -971,  -971,   431,  -971,  -971,   435,
     433,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,   442,   443,  -971,  -971,  -971,  -971,
     444,   448,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,   120,  -971,  -971,  -971,   449,  -971,
    -971,   450,  -971,   451,   452,  -971,  -971,   454,   456,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,   121,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,   458,   128,  -971,  -971,  -971,  -971,
      38,    38,  -971,   263,   459,  -971,  -971,   462,   466,   472,
     274,   277,   278,   477,   480,   482,   483,   484,   489,   295,
     298,   299,   302,   303,   290,   308,   309,   316,   306,   311,
     515,   318,   320,   319,   321,   322,   521,   526,   527,   333,
     334,   335,   528,   538,   539,   341,   542,   544,   545,   546,
     346,   349,   351,   556,   557,   560,   562,   563,   365,   567,
     568,   570,   574,   575,   578,   378,   379,   399,   586,   587,
    -971,   132,  -971,   588,   601,   602,   407,   432,   410,   411,
     126,  -971,   627,   628,   630,   632,   634,   636,   436,   642,
     643,   644,   294,  -971,   645,   -50,  -971,   646,   648,   649,
     650,   651,   652,   655,   656,  -971,   315,  -971,   657,   658,
     460,   667,   671,   673,   473,  -971,    80,   675,   475,   476,
    -971,   200,   678,   679,   179,  -971,   479,   685,   686,   488,
     688,   490,   502,   702,   703,   503,   516,   718,   721,   722,
     723,   617,  -971,   728,   530,    77,  -971,  -971,  -971,   730,
     729,   732,   734,   736,  -971,  -971,  -971,   533,   543,   548,
     737,   739,   746,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,   551,  -971,  -971,  -971,  -971,  -971,
     -94,   554,   558,  -971,  -971,  -971,   753,   754,   756,  -971,
     757,   758,   564,   231,  -971,  -971,  -971,   759,   762,   763,
     764,   777,  -971,   778,   779,   780,   781,   590,   591,  -971,
    -971,  -971,   765,   782,  -971,   789,   172,   301,  -971,  -971,
    -971,  -971,  -971,   593,   594,   595,   793,   597,   598,  -971,
     789,   599,   795,  -971,   603,  -971,   789,   604,   605,   608,
     609,   610,   611,   612,  -971,   613,   614,  -971,   615,   616,
     618,  -971,  -971,   619,  -971,  -971,  -971,   620,   758,  -971,
    -971,   621,   622,  -971,   623,  -971,  -971,    13,   659,  -971,
    -971,   -94,   624,   626,   629,  -971,   798,  -971,  -971,    38,
     132,    77,   126,   802,  -971,  -971,  -971,   552,   552,   797,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,   823,
     825,   826,   827,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,   -17,   828,   829,   831,   119,    82,   184,   147,   617,
    -971,  -971,   832,  -144,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,   833,  -971,  -971,  -971,  -971,
     122,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,   797,
    -971,   136,   151,   170,  -971,   171,  -971,  -971,  -971,  -971,
    -971,  -971,   837,   838,   839,   840,   841,   842,   843,  -971,
     844,  -971,  -971,  -971,  -971,  -971,   178,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,   213,  -971,   845,   846,
    -971,  -971,   847,   849,  -971,  -971,   848,   852,  -971,  -971,
     850,   854,  -971,  -971,   853,   855,  -971,  -971,  -971,  -971,
    -971,  -971,    94,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
     150,  -971,  -971,   856,   857,  -971,  -971,   858,   860,  -971,
     861,   862,   863,   864,   865,   866,   215,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,   867,   868,   869,  -971,   257,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
     259,  -971,  -971,  -971,   870,  -971,   871,  -971,  -971,  -971,
     261,  -971,  -971,  -971,  -971,  -971,   268,  -971,   185,  -971,
     872,  -971,   269,  -971,  -971,   676,  -971,   873,   874,  -971,
    -971,  -971,  -971,   875,   876,  -971,  -971,  -971,   877,   802,
    -971,   880,   881,   882,   883,   647,   683,   677,   684,   687,
     689,   690,   887,   691,   891,   892,   893,   894,   552,  -971,
    -971,   552,  -971,   797,   294,  -971,   823,    80,  -971,   825,
     200,  -971,   826,   635,  -971,   827,   -17,  -971,   555,   828,
    -971,   315,  -971,   829,   -84,  -971,   831,   696,   697,   698,
     699,   700,   701,   119,  -971,   704,   705,   708,    82,  -971,
     901,   902,   184,  -971,   707,   910,   712,   916,   147,  -971,
    -971,   135,   832,  -971,   717,  -144,  -971,  -971,   919,   927,
     -50,  -971,   833,   942,  -971,  -971,   747,  -971,   305,   750,
     772,   783,  -971,  -971,  -971,  -971,  -971,  -971,  -971,   331,
    -971,   787,   788,   799,   800,  -971,   280,  -971,   292,  -971,
     923,  -971,   956,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,   293,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,   977,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,   974,  1012,  -971,  -971,  -971,  -971,  -971,  1037,
    -971,   310,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,   859,   878,  -971,  -971,   879,  -971,
      38,  -971,  -971,  1045,  -971,  -971,  -971,  -971,  -971,   312,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,   884,   327,
    -971,   789,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,   635,  -971,  1046,   851,  -971,   555,  -971,  -971,
    -971,  -971,  -971,  -971,  1050,   885,  1051,   135,  -971,  -971,
    -971,  -971,  -971,   888,  -971,  -971,  1052,  -971,   889,  -971,
    -971,  1053,  -971,  -971,   347,  -971,  -100,  1053,  -971,  -971,
    1054,  1055,  1058,  -971,   330,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  1059,   890,   886,   895,  1060,  -100,  -971,   897,
    -971,  -971,  -971,   899,  -971,  -971,  -971
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   192,     9,   361,    11,   569,    13,
     596,    15,   489,    17,   498,    19,   537,    21,   323,    23,
     710,    25,   761,    27,    46,    39,     0,     0,     0,     0,
       0,   598,     0,   500,   539,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   759,   177,   210,
       0,     0,     0,   618,   620,   622,   208,   218,   220,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,     0,     0,     0,     0,   154,   161,   163,     0,
       0,     0,   352,   487,   528,     0,   435,   583,   585,   428,
       0,     0,     0,   285,   646,   587,   314,   335,     0,   300,
     677,   691,   708,   167,   169,     0,     0,     0,   771,   813,
       0,   133,     0,    67,    70,    71,    72,    73,    74,   108,
     109,   110,   111,   112,    75,   103,   132,    92,    93,    94,
     116,   117,   118,   119,   120,   121,   122,   123,   114,   115,
     124,   125,   126,   128,   129,   130,    78,    79,   100,    80,
      81,    82,   127,    86,    87,    76,   105,   106,   107,   104,
      77,    84,    85,    98,    99,   101,    95,    96,    97,    83,
      88,    89,    90,    91,   102,   113,   131,   194,   196,   200,
       0,     0,     0,     0,   191,     0,   179,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   413,   415,   417,   560,
     411,   419,     0,   423,   421,   642,   410,   366,   367,   368,
     369,   370,   394,   395,   396,   397,   398,   384,   385,   399,
     400,   401,   402,   403,   404,   405,   406,   407,   408,   409,
       0,   363,   373,   389,   390,   391,   374,   376,   377,   380,
     381,   382,   379,   375,   371,   372,   392,   393,   378,   386,
     387,   388,   383,   581,   580,   576,   577,   575,     0,   571,
     574,   578,   579,   640,   628,   630,   634,   632,   638,   636,
     624,   617,   611,   615,   616,     0,   599,   600,   612,   613,
     614,   608,   603,   609,   605,   606,   607,   610,   604,     0,
     518,   263,     0,   522,   520,   525,     0,   514,   515,     0,
     501,   502,   505,   517,   506,   507,   508,   524,   509,   510,
     511,   512,   513,   554,     0,     0,   552,   553,   556,   557,
       0,   540,   541,   544,   545,   546,   547,   548,   549,   550,
     551,   331,   333,   328,     0,   325,   329,   330,     0,   747,
     734,     0,   737,     0,     0,   741,   745,     0,     0,   751,
     753,   755,   757,   732,   730,   731,     0,   712,   715,   716,
     717,   718,   719,   720,   721,   722,   727,   723,   724,   725,
     726,   728,   729,   768,     0,     0,   763,   766,   767,    45,
      50,     0,    37,    43,     0,    64,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    69,    66,     0,     0,     0,     0,     0,     0,     0,
     181,   193,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   365,   362,     0,   573,   570,     0,     0,     0,
       0,     0,     0,     0,     0,   597,   602,   490,     0,     0,
       0,     0,     0,     0,     0,   499,   504,     0,     0,     0,
     538,   543,     0,     0,   327,   324,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   714,   711,     0,     0,   765,   762,    49,    41,     0,
       0,     0,     0,     0,   148,   149,   150,     0,     0,     0,
       0,     0,     0,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,     0,   172,   173,   151,   152,   153,
       0,     0,     0,   165,   166,   171,     0,     0,     0,   147,
       0,     0,     0,     0,   425,   426,   427,     0,     0,     0,
       0,     0,   676,     0,     0,     0,     0,     0,     0,   174,
     175,   176,     0,     0,    68,     0,     0,     0,   204,   205,
     206,   207,   180,     0,     0,     0,     0,     0,     0,   434,
       0,     0,     0,   364,     0,   572,     0,     0,     0,     0,
       0,     0,     0,     0,   601,     0,     0,   516,     0,     0,
       0,   527,   503,     0,   558,   559,   542,     0,     0,   326,
     733,     0,     0,   736,     0,   739,   740,     0,     0,   749,
     750,     0,     0,     0,     0,   713,     0,   770,   764,     0,
       0,     0,     0,     0,   619,   621,   623,     0,     0,   222,
     146,   156,   157,   158,   159,   160,   155,   162,   164,   354,
     491,   530,   437,    38,   584,   586,   430,   431,   432,   433,
     429,     0,     0,   589,   316,     0,     0,     0,     0,     0,
     168,   170,     0,     0,    51,   195,   198,   199,   197,   202,
     203,   201,   414,   416,   418,   562,   412,   420,   424,   422,
       0,   582,   641,   629,   631,   635,   633,   639,   637,   625,
     519,   264,   523,   521,   526,   555,   332,   334,   748,   735,
     738,   743,   744,   742,   746,   752,   754,   756,   758,   222,
      42,     0,     0,     0,   216,     0,   212,   215,   251,   256,
     258,   260,     0,     0,     0,     0,     0,     0,     0,   271,
       0,   277,   279,   281,   283,   250,     0,   229,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,     0,   227,     0,   223,
     224,   359,     0,   355,   356,   496,     0,   492,   493,   535,
       0,   531,   532,   442,     0,   438,   439,   295,   296,   297,
     298,   299,     0,   287,   290,   291,   292,   293,   294,   651,
       0,   648,   594,     0,   590,   591,   321,     0,   317,   318,
       0,     0,     0,     0,     0,     0,     0,   337,   340,   341,
     342,   343,   344,   345,     0,     0,     0,   310,     0,   302,
     305,   306,   307,   308,   309,   687,   689,   686,   684,   685,
       0,   679,   682,   683,     0,   703,     0,   706,   699,   700,
       0,   693,   696,   697,   698,   701,     0,   776,     0,   773,
       0,   819,     0,   815,   818,    53,   567,     0,   563,   564,
     626,   644,   645,     0,     0,    62,   760,   178,     0,   214,
     211,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   231,   209,
     219,     0,   221,   226,     0,   353,   358,   500,   488,   495,
     539,   529,   534,     0,   436,   441,   289,   286,   653,   650,
     647,   598,   588,   593,     0,   315,   320,     0,     0,     0,
       0,     0,     0,   339,   336,     0,     0,     0,   304,   301,
       0,     0,   681,   678,     0,     0,     0,     0,   695,   692,
     709,     0,   775,   772,     0,   817,   814,    55,     0,    54,
       0,   561,   566,     0,   643,   769,     0,   213,     0,     0,
       0,     0,   262,   265,   266,   267,   268,   269,   270,     0,
     276,     0,     0,     0,     0,   230,     0,   225,     0,   357,
       0,   494,     0,   533,   486,   465,   466,   467,   450,   451,
     470,   471,   472,   473,   474,   453,   454,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   447,   448,
     449,   463,   464,   460,   461,   462,   459,     0,   444,   452,
     468,   469,   455,   456,   457,   458,   440,   288,   673,     0,
     668,   669,   670,   671,   672,   661,   662,   666,   667,   663,
     664,   665,     0,   654,   655,   658,   659,   660,   649,     0,
     592,     0,   319,   346,   347,   348,   349,   350,   351,   338,
     311,   312,   313,   303,     0,     0,   680,   702,     0,   705,
       0,   694,   791,     0,   789,   787,   781,   785,   786,     0,
     778,   783,   784,   782,   774,   820,   816,    52,    57,     0,
     565,     0,   217,   253,   254,   255,   252,   257,   259,   261,
     273,   274,   275,   272,   278,   280,   282,   284,   228,   360,
     497,   536,   446,   443,     0,     0,   652,   657,   595,   322,
     688,   690,   704,   707,     0,     0,     0,   780,   777,    56,
     568,   627,   445,     0,   675,   656,     0,   788,     0,   779,
     674,     0,   790,   796,     0,   793,     0,   795,   792,   806,
       0,     0,     0,   811,     0,   798,   801,   802,   803,   804,
     805,   794,     0,     0,     0,     0,     0,   800,   797,     0,
     808,   809,   810,     0,   799,   807,   812
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,   -54,  -971,  -583,  -971,   183,
    -971,  -971,  -971,  -971,  -971,  -971,  -635,  -971,  -971,  -971,
     -67,  -971,  -971,  -971,  -971,  -971,  -971,  -971,   366,   576,
       4,    10,    23,   -40,   -23,   -12,    22,    25,    29,    33,
    -971,  -971,  -971,  -971,  -971,    35,    40,    43,    45,    46,
      47,  -971,   374,    50,  -971,    51,  -971,    53,    57,    58,
    -971,    61,  -971,    63,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,   367,   571,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,   123,  -971,  -971,  -971,  -971,  -971,  -971,   279,
    -971,    97,  -971,  -696,   105,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,   -33,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,    88,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,    67,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,    81,  -971,  -971,  -971,    84,
     532,  -971,  -971,  -971,  -971,  -971,  -971,  -971,    76,  -971,
    -971,  -971,  -971,  -971,  -971,  -970,  -971,  -971,  -971,   107,
    -971,  -971,  -971,   108,   572,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -959,  -971,   -65,  -971,    70,  -971,    64,
      65,    68,    69,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
     100,  -971,  -971,  -105,   -46,  -971,  -971,  -971,  -971,  -971,
     113,  -971,  -971,  -971,   116,  -971,   561,  -971,   -63,  -971,
    -971,  -971,  -971,  -971,   -42,  -971,  -971,  -971,  -971,  -971,
     -35,  -971,  -971,  -971,   112,  -971,  -971,  -971,   124,  -971,
     565,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,    71,  -971,  -971,  -971,    72,   592,  -971,  -971,
     -51,  -971,    -8,  -971,   -39,  -971,  -971,  -971,   115,  -971,
    -971,  -971,   127,  -971,   579,   -55,  -971,   -15,  -971,     3,
    -971,   350,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -956,
    -971,  -971,  -971,  -971,  -971,   130,  -971,  -971,  -971,   -88,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,    99,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,    95,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,   375,   559,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,   414,   547,
    -971,  -971,  -971,  -971,  -971,  -971,   101,  -971,  -971,   -91,
    -971,  -971,  -971,  -971,  -971,  -971,  -110,  -971,  -971,  -126,
    -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,  -971,
     103,  -971
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   724,
      82,    83,    39,    64,    79,    80,   745,   935,  1028,  1029,
     815,    41,    66,    85,   424,    86,    43,    67,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   450,   166,   167,   168,   169,   170,   171,   172,
     173,   456,   716,   174,   457,   175,   458,   176,   177,   178,
     483,   179,   484,   180,   181,   182,   183,   184,   185,   186,
     428,   225,   226,    45,    68,   227,   493,   228,   494,   748,
     229,   495,   751,   230,   231,   232,   233,   187,   436,   188,
     429,   795,   796,   797,   948,   189,   437,   190,   438,   838,
     839,   840,   971,   816,   817,   818,   951,  1176,   819,   952,
     820,   953,   821,   954,   822,   823,   529,   824,   825,   826,
     827,   828,   829,   830,   962,  1183,   831,   832,   964,   833,
     965,   834,   966,   835,   967,   191,   473,   862,   863,   864,
     865,   866,   867,   868,   192,   479,   898,   899,   900,   901,
     902,   193,   476,   877,   878,   879,   994,    59,    75,   374,
     375,   376,   542,   377,   543,   194,   477,   886,   887,   888,
     889,   890,   891,   892,   893,   195,   462,   842,   843,   844,
     974,    47,    69,   270,   271,   272,   506,   273,   502,   274,
     503,   275,   504,   276,   507,   277,   510,   278,   509,   196,
     197,   198,   199,   469,   730,   283,   200,   466,   854,   855,
     856,   983,  1097,  1098,   201,   463,    53,    72,   846,   847,
     848,   977,    55,    73,   339,   340,   341,   342,   343,   344,
     345,   528,   346,   532,   347,   531,   348,   349,   533,   350,
     202,   464,   850,   851,   852,   980,    57,    74,   360,   361,
     362,   363,   364,   537,   365,   366,   367,   368,   285,   505,
     937,   938,   939,  1030,    49,    70,   298,   299,   300,   514,
     203,   467,   204,   468,   205,   475,   873,   874,   875,   991,
      51,    71,   315,   316,   317,   206,   433,   207,   434,   208,
     435,   321,   524,   942,  1033,   322,   518,   323,   519,   324,
     521,   325,   520,   326,   523,   327,   522,   328,   517,   292,
     511,   943,   209,   474,   870,   871,   988,  1122,  1123,  1124,
    1125,  1126,  1194,  1127,   210,   211,   480,   910,   911,   912,
    1010,   913,  1011,   212,   481,   920,   921,   922,   923,  1015,
     924,   925,  1017,   213,   482,    61,    76,   396,   397,   398,
     399,   548,   400,   401,   550,   402,   403,   404,   553,   783,
     405,   554,   406,   547,   407,   408,   409,   557,   410,   558,
     411,   559,   412,   560,   214,   427,    63,    77,   415,   416,
     417,   563,   418,   215,   488,   928,   929,  1021,  1159,  1160,
    1161,  1162,  1206,  1163,  1204,  1224,  1225,  1226,  1234,  1235,
    1236,  1242,  1237,  1238,  1239,  1240,  1246,   216,   489,   932,
     933,   934
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     151,   224,   246,   294,   311,   295,   337,   356,   373,   393,
      78,   358,   836,  1089,   289,   758,   318,   234,   286,   301,
     313,   762,   351,   369,  1090,   394,   329,  1105,   723,   250,
     288,   781,   359,    40,   284,   297,   312,   425,   124,    28,
     338,   357,   426,    29,   930,    30,   251,    31,   371,   372,
      81,   293,   127,   128,   290,    42,   319,   252,   150,   491,
     235,   287,   302,   314,   492,   352,   370,   243,   395,    44,
     244,   123,   291,   247,   320,   711,   712,   713,   714,   248,
    1229,    46,   500,  1230,  1231,  1232,  1233,   501,   512,   413,
     414,   253,   249,   513,   254,   723,   515,   986,   255,    48,
     987,   516,   256,    50,   257,   857,   858,   859,   860,   258,
     861,   715,   259,    52,   260,   261,   262,   330,   150,   263,
     264,    54,   265,   544,   561,    56,   266,   267,   545,   562,
     268,   565,   269,   279,   280,    84,   566,   281,   282,   491,
     296,   217,   218,    87,   945,   219,    88,    58,   220,   221,
     222,   223,   150,   989,   565,    60,   990,   420,    89,   946,
      90,    91,    92,    93,    94,    95,    96,    97,    98,   331,
      62,   332,   333,   500,   949,   334,   335,   336,   947,   950,
     782,   968,   127,   128,   127,   128,   969,   419,  1022,   746,
     747,  1023,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   968,   422,  1003,   123,
     124,   970,  1089,  1004,   331,   894,   895,   896,   127,   128,
     125,   126,   421,  1090,   127,   128,  1105,   127,   128,   129,
      32,    33,    34,    35,   130,   131,   132,   133,   134,   127,
     128,   310,   940,   135,   880,   881,   882,   883,   884,   885,
    1008,   423,  1012,   136,  1018,  1009,   137,  1013,   430,  1019,
     431,   561,  1025,   138,   139,  1056,  1020,  1026,   140,   432,
     439,   141,   150,   968,   150,   142,   127,   128,  1188,   331,
     353,   332,   333,   354,   355,   512,  1192,   914,   915,   916,
    1189,  1193,   127,   128,   440,   143,   144,   145,   146,   147,
     148,   371,   372,   544,  1152,  1207,  1153,  1154,  1199,   149,
    1208,   749,   750,    91,    92,    93,    94,    95,   150,   441,
     515,   905,   906,  1247,   150,  1210,   442,   150,  1248,   726,
     727,   728,   729,  1173,  1174,  1175,    93,    94,    95,   917,
    1227,   525,   443,  1228,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   444,   445,   567,   568,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   446,   236,   237,
     238,   447,   124,  1180,  1181,  1182,   150,   448,   449,   451,
     452,   453,   454,   455,   239,   459,   127,   128,   240,   241,
     242,   129,   150,   124,   460,   461,   130,   131,   132,   465,
     470,   243,   471,   472,   244,   135,   478,   127,   128,   485,
     486,   487,   245,   490,   151,   496,   497,   498,   499,   508,
     526,   303,   530,   224,   527,   534,   536,   304,   305,   306,
     307,   308,   309,   535,   310,   246,   538,   539,   294,   234,
     295,   541,   540,   546,   549,   551,   552,   289,   555,   311,
     556,   286,   564,   570,   301,   569,   571,   143,   144,   337,
     572,   318,   250,   288,   356,   313,   573,   284,   358,   574,
     297,   577,   575,   576,   578,   351,   579,   580,   581,   251,
     369,   312,   235,   582,   393,   588,   150,   290,   583,   359,
     252,   584,   585,   338,   287,   586,   587,   302,   357,   592,
     394,   319,   589,   590,   593,   291,   247,   150,   314,   594,
     591,   595,   248,   596,   597,   600,   598,   599,   352,   320,
     601,   602,   606,   370,   253,   249,  1211,   254,   603,   604,
     605,   255,   607,   608,   609,   256,   610,   257,   611,   612,
     613,   614,   258,   395,   615,   259,   616,   260,   261,   262,
     617,   618,   263,   264,   619,   265,   620,   621,   622,   266,
     267,   623,   624,   268,   625,   269,   279,   280,   626,   627,
     281,   282,   628,   629,   630,   296,    93,    94,    95,   798,
     632,   633,   635,   799,   800,   801,   802,   803,   804,   805,
     806,   807,   808,   809,   631,   636,   637,   810,   811,   812,
     813,   814,   638,   640,   641,    99,   100,   101,     1,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   643,   644,   151,   645,   224,   646,   639,   647,   649,
     648,   331,   123,   124,   331,   790,   650,   651,   652,   654,
     656,   234,   657,   658,   659,   660,   661,   127,   128,   662,
     663,   665,   666,   667,    91,    92,    93,    94,    95,   897,
     907,   668,   393,  1108,  1109,   669,   931,   670,   671,   673,
     674,   675,   677,   678,   680,   903,   908,   918,   394,   681,
     682,   683,   684,   685,   235,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   686,   687,   688,   689,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   127,
     128,   690,   691,   124,   331,   692,   693,   694,   904,   909,
     919,   395,   696,   697,   699,   704,   700,   127,   128,   701,
     241,   702,   129,   703,   707,   705,   708,   130,   131,   132,
     706,   709,   243,   710,   150,   244,   717,   150,   719,   720,
     718,   721,   722,   245,   731,    30,   725,   732,   733,   734,
     742,   378,   379,   380,   381,   382,   383,   384,   385,   386,
     387,   388,   389,   390,   735,   736,   737,   738,   739,   743,
     391,   392,   740,   741,   744,   752,   753,   754,   755,   756,
     757,   759,   760,   789,   837,   761,   763,   764,   143,   144,
     765,   766,   767,   768,   769,   770,   771,   772,   773,   150,
     774,   775,   776,   778,   779,   780,   786,   784,   787,   794,
     841,   788,   845,   849,   853,   869,   872,   150,   876,   927,
     936,   955,   956,   957,   958,   959,   960,   961,   963,   973,
    1042,   972,   976,   975,   978,   979,   981,   982,   985,   984,
     993,   777,   992,   996,   995,   997,   998,   999,  1000,  1001,
    1002,  1005,  1006,  1007,  1014,  1016,  1024,  1032,  1027,  1031,
    1044,  1036,  1035,  1034,  1038,  1039,  1040,  1041,  1043,  1045,
    1046,  1049,  1047,  1048,  1050,  1051,  1052,  1053,  1054,  1133,
    1134,  1135,  1136,  1137,  1138,  1144,  1145,   246,  1141,  1140,
     337,  1142,  1147,   356,  1148,  1149,  1064,   358,  1091,   289,
    1150,  1110,  1165,   286,   311,  1167,   351,   373,  1102,   369,
    1168,  1190,  1100,  1119,   250,   288,   318,  1117,   359,   284,
     313,   897,  1115,  1068,   338,   907,  1171,   357,  1099,  1172,
    1088,   251,  1177,  1116,  1155,  1114,   312,   903,   931,   290,
    1069,   908,   252,   294,  1191,   295,   287,   918,  1103,   352,
    1157,  1070,   370,  1120,  1178,  1101,   319,   291,   247,   301,
    1118,  1195,  1196,   314,   248,  1179,  1104,  1065,  1156,  1184,
    1185,  1121,  1111,  1066,   320,   297,   253,   249,  1112,   254,
     904,  1186,  1187,   255,   909,  1071,  1067,   256,  1072,   257,
     919,  1113,  1073,  1158,   258,  1197,  1074,   259,  1075,   260,
     261,   262,   302,  1076,   263,   264,  1077,   265,  1078,  1079,
    1080,   266,   267,  1081,  1082,   268,  1083,   269,   279,   280,
    1084,  1085,   281,   282,  1086,  1198,  1087,  1093,  1094,  1205,
    1213,  1095,  1096,  1092,  1216,  1218,  1214,  1221,  1243,  1244,
    1223,  1200,  1245,  1249,  1253,   785,   791,   634,   944,   793,
    1057,   642,  1037,  1055,  1107,  1143,   679,  1132,  1131,  1139,
    1201,  1202,  1058,  1059,   653,  1106,  1209,  1212,  1217,  1251,
    1220,  1222,  1061,  1060,  1063,  1250,  1203,   672,  1252,  1255,
     296,  1256,  1169,  1170,  1062,   664,   676,   655,  1130,  1215,
     941,  1146,   698,  1151,   926,   792,  1219,  1241,  1129,  1128,
     695,  1254,     0,  1164,     0,  1064,     0,  1091,  1166,     0,
    1110,     0,     0,     0,     0,     0,     0,  1102,     0,     0,
    1155,  1100,  1119,     0,     0,     0,  1117,     0,     0,     0,
       0,  1115,  1068,     0,     0,     0,  1157,  1099,     0,  1088,
       0,     0,  1116,     0,  1114,     0,     0,     0,     0,  1069,
       0,     0,     0,     0,  1156,     0,     0,  1103,     0,     0,
    1070,     0,  1120,     0,  1101,     0,     0,     0,     0,  1118,
       0,     0,     0,     0,     0,  1104,  1065,     0,     0,  1158,
    1121,  1111,  1066,     0,     0,     0,     0,  1112,     0,     0,
       0,     0,     0,     0,  1071,  1067,     0,  1072,     0,     0,
    1113,  1073,     0,     0,     0,  1074,     0,  1075,     0,     0,
       0,     0,  1076,     0,     0,  1077,     0,  1078,  1079,  1080,
       0,     0,  1081,  1082,     0,  1083,     0,     0,     0,  1084,
    1085,     0,     0,  1086,     0,  1087,  1093,  1094,     0,     0,
    1095,  1096,  1092
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,    74,   708,   983,    69,   650,    71,    68,    69,    70,
      71,   656,    73,    74,   983,    76,    72,   983,   611,    69,
      69,    18,    74,     7,    69,    70,    71,     3,    88,     0,
      73,    74,     8,     5,   188,     7,    69,     9,   132,   133,
     202,   101,   102,   103,    69,     7,    71,    69,   202,     3,
      68,    69,    70,    71,     8,    73,    74,   117,    76,     7,
     120,    87,    69,    69,    71,   169,   170,   171,   172,    69,
     180,     7,     3,   183,   184,   185,   186,     8,     3,    12,
      13,    69,    69,     8,    69,   678,     3,     3,    69,     7,
       6,     8,    69,     7,    69,   122,   123,   124,   125,    69,
     127,   205,    69,     7,    69,    69,    69,    37,   202,    69,
      69,     7,    69,     3,     3,     7,    69,    69,     8,     8,
      69,     3,    69,    69,    69,    10,     8,    69,    69,     3,
      70,    15,    16,    11,     8,    19,    14,     7,    22,    23,
      24,    25,   202,     3,     3,     7,     6,     3,    26,     8,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    89,
       7,    91,    92,     3,     3,    95,    96,    97,     8,     8,
     167,     3,   102,   103,   102,   103,     8,     6,     3,    17,
      18,     6,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     3,     8,     3,    87,
      88,     8,  1192,     8,    89,   143,   144,   145,   102,   103,
      98,    99,     4,  1192,   102,   103,  1192,   102,   103,   107,
     202,   203,   204,   205,   112,   113,   114,   115,   116,   102,
     103,   129,   130,   121,   135,   136,   137,   138,   139,   140,
       3,     3,     3,   131,     3,     8,   134,     8,     4,     8,
       4,     3,     3,   141,   142,   971,     8,     8,   146,     4,
       4,   149,   202,     3,   202,   153,   102,   103,     8,    89,
      90,    91,    92,    93,    94,     3,     3,   150,   151,   152,
       8,     8,   102,   103,     4,   173,   174,   175,   176,   177,
     178,   132,   133,     3,   179,     3,   181,   182,     8,   187,
       8,    20,    21,    29,    30,    31,    32,    33,   202,     4,
       3,   147,   148,     3,   202,     8,     4,   202,     8,   108,
     109,   110,   111,    38,    39,    40,    31,    32,    33,   202,
       3,     8,     4,     6,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,     4,     4,   420,   421,    74,    75,
      76,    77,    78,    79,    80,    81,    82,     4,    84,    85,
      86,     4,    88,    52,    53,    54,   202,     4,     4,     4,
       4,     4,     4,     4,   100,     4,   102,   103,   104,   105,
     106,   107,   202,    88,     4,     4,   112,   113,   114,     4,
       4,   117,     4,     4,   120,   121,     4,   102,   103,     4,
       4,     4,   128,     4,   491,     4,     4,     4,     4,     4,
       3,   116,     4,   500,     8,     4,     3,   122,   123,   124,
     125,   126,   127,     8,   129,   512,     4,     4,   515,   500,
     515,     3,     8,     4,     4,     4,     4,   512,     4,   526,
       4,   512,     4,     4,   515,   202,     4,   173,   174,   536,
       4,   526,   512,   512,   541,   526,     4,   512,   541,   205,
     515,     4,   205,   205,     4,   536,     4,     4,     4,   512,
     541,   526,   500,     4,   561,   205,   202,   512,   203,   541,
     512,   203,   203,   536,   512,   203,   203,   515,   541,   203,
     561,   526,   204,   204,   203,   512,   512,   202,   526,     4,
     204,   203,   512,   203,   205,     4,   205,   205,   536,   526,
       4,     4,     4,   541,   512,   512,  1171,   512,   205,   205,
     205,   512,     4,     4,   203,   512,     4,   512,     4,     4,
       4,   205,   512,   561,   205,   512,   205,   512,   512,   512,
       4,     4,   512,   512,     4,   512,     4,     4,   203,   512,
     512,     4,     4,   512,     4,   512,   512,   512,     4,     4,
     512,   512,     4,   205,   205,   515,    31,    32,    33,    37,
       4,     4,     4,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,   205,     4,     4,    55,    56,    57,
      58,    59,   205,   203,   203,    60,    61,    62,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,     4,     4,   700,     4,   702,     4,   205,     4,   203,
       4,    89,    87,    88,    89,   699,     4,     4,     4,     4,
       4,   702,     4,     4,     4,     4,     4,   102,   103,     4,
       4,     4,     4,   203,    29,    30,    31,    32,    33,   736,
     737,     4,   739,   118,   119,     4,   743,     4,   205,     4,
     205,   205,     4,     4,   205,   736,   737,   738,   739,     4,
       4,   203,     4,   203,   702,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,   203,     4,     4,   205,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,   102,
     103,   205,     4,    88,    89,     4,     4,     4,   736,   737,
     738,   739,     4,   203,     4,   202,     7,   102,   103,     7,
     105,     7,   107,     7,     7,   202,     7,   112,   113,   114,
     202,     5,   117,   202,   202,   120,   202,   202,     5,     5,
     202,     5,     5,   128,     5,     7,   202,     5,     5,     5,
       5,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,     7,     7,     7,     7,     7,     7,
     173,   174,   202,   202,     5,   202,   202,   202,     5,   202,
     202,   202,     7,     5,     7,   202,   202,   202,   173,   174,
     202,   202,   202,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   168,   202,    27,
       7,   202,     7,     7,     7,     7,     7,   202,     7,     7,
       7,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     203,     6,     3,     6,     6,     3,     6,     3,     3,     6,
       3,   678,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   202,     6,
     203,     4,     6,     8,     4,     4,     4,     4,   205,   205,
     203,     4,   203,   203,   203,     4,     4,     4,     4,   203,
     203,   203,   203,   203,   203,     4,     4,   974,   203,   205,
     977,   203,   205,   980,     4,   203,   983,   980,   983,   974,
       4,   988,   205,   974,   991,     6,   977,   994,   983,   980,
       3,     8,   983,   988,   974,   974,   991,   988,   980,   974,
     991,  1008,   988,   983,   977,  1012,     4,   980,   983,   202,
     983,   974,   202,   988,  1021,   988,   991,  1008,  1025,   974,
     983,  1012,   974,  1030,     8,  1030,   974,  1018,   983,   977,
    1021,   983,   980,   988,   202,   983,   991,   974,   974,  1030,
     988,     4,     8,   991,   974,   202,   983,   983,  1021,   202,
     202,   988,   988,   983,   991,  1030,   974,   974,   988,   974,
    1008,   202,   202,   974,  1012,   983,   983,   974,   983,   974,
    1018,   988,   983,  1021,   974,     3,   983,   974,   983,   974,
     974,   974,  1030,   983,   974,   974,   983,   974,   983,   983,
     983,   974,   974,   983,   983,   974,   983,   974,   974,   974,
     983,   983,   974,   974,   983,     8,   983,   983,   983,     4,
       4,   983,   983,   983,     4,     4,   205,     5,     4,     4,
       7,   202,     4,     4,     4,   691,   700,   491,   789,   702,
     973,   500,   949,   968,   986,  1008,   544,   996,   994,  1003,
     202,   202,   974,   976,   512,   985,   202,  1192,   203,   203,
     202,   202,   979,   977,   982,   205,  1150,   536,   203,   202,
    1030,   202,  1030,  1032,   980,   526,   541,   515,   993,  1197,
     760,  1012,   565,  1018,   739,   701,  1207,  1227,   991,   989,
     561,  1247,    -1,  1022,    -1,  1192,    -1,  1192,  1025,    -1,
    1197,    -1,    -1,    -1,    -1,    -1,    -1,  1192,    -1,    -1,
    1207,  1192,  1197,    -1,    -1,    -1,  1197,    -1,    -1,    -1,
      -1,  1197,  1192,    -1,    -1,    -1,  1207,  1192,    -1,  1192,
      -1,    -1,  1197,    -1,  1197,    -1,    -1,    -1,    -1,  1192,
      -1,    -1,    -1,    -1,  1207,    -1,    -1,  1192,    -1,    -1,
    1192,    -1,  1197,    -1,  1192,    -1,    -1,    -1,    -1,  1197,
      -1,    -1,    -1,    -1,    -1,  1192,  1192,    -1,    -1,  1207,
    1197,  1197,  1192,    -1,    -1,    -1,    -1,  1197,    -1,    -1,
      -1,    -1,    -1,    -1,  1192,  1192,    -1,  1192,    -1,    -1,
    1197,  1192,    -1,    -1,    -1,  1192,    -1,  1192,    -1,    -1,
      -1,    -1,  1192,    -1,    -1,  1192,    -1,  1192,  1192,  1192,
      -1,    -1,  1192,  1192,    -1,  1192,    -1,    -1,    -1,  1192,
    1192,    -1,    -1,  1192,    -1,  1192,  1192,  1192,    -1,    -1,
    1192,  1192,  1192
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,     0,     5,
       7,     9,   202,   203,   204,   205,   221,   222,   223,   228,
       7,   237,     7,   242,     7,   289,     7,   397,     7,   480,
       7,   496,     7,   432,     7,   438,     7,   462,     7,   373,
       7,   561,     7,   592,   229,   224,   238,   243,   290,   398,
     481,   497,   433,   439,   463,   374,   562,   593,   221,   230,
     231,   202,   226,   227,    10,   239,   241,    11,    14,    26,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    87,    88,    98,    99,   102,   103,   107,
     112,   113,   114,   115,   116,   121,   131,   134,   141,   142,
     146,   149,   153,   173,   174,   175,   176,   177,   178,   187,
     202,   236,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   259,   260,   261,   262,
     263,   264,   265,   266,   269,   271,   273,   274,   275,   277,
     279,   280,   281,   282,   283,   284,   285,   303,   305,   311,
     313,   351,   360,   367,   381,   391,   415,   416,   417,   418,
     422,   430,   456,   486,   488,   490,   501,   503,   505,   528,
     540,   541,   549,   559,   590,   599,   623,    15,    16,    19,
      22,    23,    24,    25,   236,   287,   288,   291,   293,   296,
     299,   300,   301,   302,   486,   488,    84,    85,    86,   100,
     104,   105,   106,   117,   120,   128,   236,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   261,   262,   263,
     264,   265,   266,   269,   271,   273,   274,   275,   277,   279,
     399,   400,   401,   403,   405,   407,   409,   411,   413,   415,
     416,   417,   418,   421,   456,   474,   486,   488,   490,   501,
     503,   505,   525,   101,   236,   411,   413,   456,   482,   483,
     484,   486,   488,   116,   122,   123,   124,   125,   126,   127,
     129,   236,   456,   486,   488,   498,   499,   500,   501,   503,
     505,   507,   511,   513,   515,   517,   519,   521,   523,   430,
      37,    89,    91,    92,    95,    96,    97,   236,   331,   440,
     441,   442,   443,   444,   445,   446,   448,   450,   452,   453,
     455,   486,   488,    90,    93,    94,   236,   331,   444,   450,
     464,   465,   466,   467,   468,   470,   471,   472,   473,   486,
     488,   132,   133,   236,   375,   376,   377,   379,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   173,   174,   236,   486,   488,   563,   564,   565,   566,
     568,   569,   571,   572,   573,   576,   578,   580,   581,   582,
     584,   586,   588,    12,    13,   594,   595,   596,   598,     6,
       3,     4,     8,     3,   240,     3,     8,   591,   286,   306,
       4,     4,     4,   502,   504,   506,   304,   312,   314,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     258,     4,     4,     4,     4,     4,   267,   270,   272,     4,
       4,     4,   392,   431,   457,     4,   423,   487,   489,   419,
       4,     4,     4,   352,   529,   491,   368,   382,     4,   361,
     542,   550,   560,   276,   278,     4,     4,     4,   600,   624,
       4,     3,     8,   292,   294,   297,     4,     4,     4,     4,
       3,     8,   404,   406,   408,   475,   402,   410,     4,   414,
     412,   526,     3,     8,   485,     3,     8,   524,   512,   514,
     518,   516,   522,   520,   508,     8,     3,     8,   447,   332,
       4,   451,   449,   454,     4,     8,     3,   469,     4,     4,
       8,     3,   378,   380,     3,     8,     4,   579,   567,     4,
     570,     4,     4,   574,   577,     4,     4,   583,   585,   587,
     589,     3,     8,   597,     4,     3,     8,   221,   221,   202,
       4,     4,     4,     4,   205,   205,   205,     4,     4,     4,
       4,     4,     4,   203,   203,   203,   203,   203,   205,   204,
     204,   204,   203,   203,     4,   203,   203,   205,   205,   205,
       4,     4,     4,   205,   205,   205,     4,     4,     4,   203,
       4,     4,     4,     4,   205,   205,   205,     4,     4,     4,
       4,     4,   203,     4,     4,     4,     4,     4,     4,   205,
     205,   205,     4,     4,   245,     4,     4,     4,   205,   205,
     203,   203,   288,     4,     4,     4,     4,     4,     4,   203,
       4,     4,     4,   400,     4,   483,     4,     4,     4,     4,
       4,     4,     4,     4,   500,     4,     4,   203,     4,     4,
       4,   205,   442,     4,   205,   205,   466,     4,     4,   376,
     205,     4,     4,   203,     4,   203,   203,     4,     4,   205,
     205,     4,     4,     4,     4,   564,     4,   203,   595,     4,
       7,     7,     7,     7,   202,   202,   202,     7,     7,     5,
     202,   169,   170,   171,   172,   205,   268,   202,   202,     5,
       5,     5,     5,   223,   225,   202,   108,   109,   110,   111,
     420,     5,     5,     5,     5,     7,     7,     7,     7,     7,
     202,   202,     5,     7,     5,   232,    17,    18,   295,    20,
      21,   298,   202,   202,   202,     5,   202,   202,   232,   202,
       7,   202,   232,   202,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   225,   202,   202,
     202,    18,   167,   575,   168,   268,   202,   202,   202,     5,
     221,   244,   594,   287,    27,   307,   308,   309,    37,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      55,    56,    57,    58,    59,   236,   319,   320,   321,   324,
     326,   328,   330,   331,   333,   334,   335,   336,   337,   338,
     339,   342,   343,   345,   347,   349,   319,     7,   315,   316,
     317,     7,   393,   394,   395,     7,   434,   435,   436,     7,
     458,   459,   460,     7,   424,   425,   426,   122,   123,   124,
     125,   127,   353,   354,   355,   356,   357,   358,   359,     7,
     530,   531,     7,   492,   493,   494,     7,   369,   370,   371,
     135,   136,   137,   138,   139,   140,   383,   384,   385,   386,
     387,   388,   389,   390,   143,   144,   145,   236,   362,   363,
     364,   365,   366,   486,   488,   147,   148,   236,   486,   488,
     543,   544,   545,   547,   150,   151,   152,   202,   486,   488,
     551,   552,   553,   554,   556,   557,   563,     7,   601,   602,
     188,   236,   625,   626,   627,   233,     7,   476,   477,   478,
     130,   507,   509,   527,   315,     8,     8,     8,   310,     3,
       8,   322,   325,   327,   329,     4,     4,     4,     4,     4,
       4,     4,   340,     4,   344,   346,   348,   350,     3,     8,
       8,   318,     6,     3,   396,     6,     3,   437,     6,     3,
     461,     6,     3,   427,     6,     3,     3,     6,   532,     3,
       6,   495,     6,     3,   372,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,     4,     4,     4,     3,     8,
     546,   548,     3,     8,     4,   555,     4,   558,     3,     8,
       8,   603,     3,     6,     4,     3,     8,   202,   234,   235,
     479,     6,     3,   510,     8,     6,     4,   308,     4,     4,
       4,     4,   203,   205,   203,   205,   203,   203,   203,     4,
     203,     4,     4,     4,     4,   320,   319,   317,   399,   395,
     440,   436,   464,   460,   236,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   261,   262,   263,   264,   265,
     266,   269,   271,   273,   274,   275,   277,   279,   331,   391,
     409,   411,   413,   415,   416,   417,   418,   428,   429,   456,
     486,   488,   501,   503,   505,   525,   426,   354,   118,   119,
     236,   246,   247,   248,   331,   430,   456,   486,   488,   501,
     503,   505,   533,   534,   535,   536,   537,   539,   531,   498,
     494,   375,   371,   203,   203,   203,   203,   203,   203,   384,
     205,   203,   203,   363,     4,     4,   544,   205,     4,   203,
       4,   552,   179,   181,   182,   236,   331,   486,   488,   604,
     605,   606,   607,   609,   602,   205,   626,     6,     3,   482,
     478,     4,   202,    38,    39,    40,   323,   202,   202,   202,
      52,    53,    54,   341,   202,   202,   202,   202,     8,     8,
       8,     8,     3,     8,   538,     4,     8,     3,     8,     8,
     202,   202,   202,   221,   610,     4,   608,     3,     8,   202,
       8,   232,   429,     4,   205,   535,     4,   203,     4,   605,
     202,     5,   202,     7,   611,   612,   613,     3,     6,   180,
     183,   184,   185,   186,   614,   615,   616,   618,   619,   620,
     621,   612,   617,     4,     4,     4,   622,     3,     8,     4,
     205,   203,   203,     4,   615,   202,   202
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   206,   208,   207,   209,   207,   210,   207,   211,   207,
     212,   207,   213,   207,   214,   207,   215,   207,   216,   207,
     217,   207,   218,   207,   219,   207,   220,   207,   221,   221,
     221,   221,   221,   221,   221,   222,   224,   223,   225,   226,
     226,   227,   227,   227,   229,   228,   230,   230,   231,   231,
     231,   233,   232,   234,   234,   235,   235,   235,   236,   238,
     237,   240,   239,   239,   241,   243,   242,   244,   244,   244,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   258,   257,   259,   260,   261,
     262,   263,   264,   265,   267,   266,   268,   268,   268,   268,
     268,   270,   269,   272,   271,   273,   274,   276,   275,   278,
     277,   279,   280,   281,   282,   283,   284,   286,   285,   287,
     287,   287,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   290,   289,   292,   291,   294,   293,   295,   295,
     297,   296,   298,   298,   299,   300,   301,   302,   304,   303,
     306,   305,   307,   307,   307,   308,   310,   309,   312,   311,
     314,   313,   315,   315,   316,   316,   316,   318,   317,   319,
     319,   319,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,   320,   320,   320,   320,   320,
     320,   322,   321,   323,   323,   323,   325,   324,   327,   326,
     329,   328,   330,   332,   331,   333,   334,   335,   336,   337,
     338,   340,   339,   341,   341,   341,   342,   344,   343,   346,
     345,   348,   347,   350,   349,   352,   351,   353,   353,   353,
     354,   354,   354,   354,   354,   355,   356,   357,   358,   359,
     361,   360,   362,   362,   362,   363,   363,   363,   363,   363,
     363,   364,   365,   366,   368,   367,   369,   369,   370,   370,
     370,   372,   371,   374,   373,   375,   375,   375,   375,   376,
     376,   378,   377,   380,   379,   382,   381,   383,   383,   383,
     384,   384,   384,   384,   384,   384,   385,   386,   387,   388,
     389,   390,   392,   391,   393,   393,   394,   394,   394,   396,
     395,   398,   397,   399,   399,   399,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
     400,   402,   401,   404,   403,   406,   405,   408,   407,   410,
     409,   412,   411,   414,   413,   415,   416,   417,   419,   418,
     420,   420,   420,   420,   421,   423,   422,   424,   424,   425,
     425,   425,   427,   426,   428,   428,   428,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   431,   430,   433,
     432,   434,   434,   435,   435,   435,   437,   436,   439,   438,
     440,   440,   441,   441,   441,   442,   442,   442,   442,   442,
     442,   442,   442,   442,   442,   443,   444,   445,   447,   446,
     449,   448,   451,   450,   452,   454,   453,   455,   457,   456,
     458,   458,   459,   459,   459,   461,   460,   463,   462,   464,
     464,   465,   465,   465,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   467,   469,   468,   470,   471,   472,   473,
     475,   474,   476,   476,   477,   477,   477,   479,   478,   481,
     480,   482,   482,   482,   483,   483,   483,   483,   483,   483,
     483,   485,   484,   487,   486,   489,   488,   491,   490,   492,
     492,   493,   493,   493,   495,   494,   497,   496,   498,   498,
     499,   499,   499,   500,   500,   500,   500,   500,   500,   500,
     500,   500,   500,   500,   500,   500,   500,   500,   502,   501,
     504,   503,   506,   505,   508,   507,   510,   509,   512,   511,
     514,   513,   516,   515,   518,   517,   520,   519,   522,   521,
     524,   523,   526,   525,   527,   527,   529,   528,   530,   530,
     530,   532,   531,   533,   533,   534,   534,   534,   535,   535,
     535,   535,   535,   535,   535,   535,   535,   535,   535,   535,
     535,   535,   536,   538,   537,   539,   540,   542,   541,   543,
     543,   543,   544,   544,   544,   544,   544,   546,   545,   548,
     547,   550,   549,   551,   551,   551,   552,   552,   552,   552,
     552,   552,   553,   555,   554,   556,   558,   557,   560,   559,
     562,   561,   563,   563,   563,   564,   564,   564,   564,   564,
     564,   564,   564,   564,   564,   564,   564,   564,   564,   564,
     564,   564,   564,   565,   567,   566,   568,   570,   569,   571,
     572,   574,   573,   575,   575,   577,   576,   579,   578,   580,
     581,   583,   582,   585,   584,   587,   586,   589,   588,   591,
     590,   593,   592,   594,   594,   594,   595,   595,   597,   596,
     598,   600,   599,   601,   601,   601,   603,   602,   604,   604,
     604,   605,   605,   605,   605,   605,   605,   605,   606,   608,
     607,   610,   609,   611,   611,   611,   613,   612,   614,   614,
     614,   615,   615,   615,   615,   615,   617,   616,   618,   619,
     620,   622,   621,   624,   623,   625,   625,   625,   626,   626,
     627
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
       1,     0,     4,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     0,     4,     1,     1,     1,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     3,     0,     6,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     0,     4,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     2,     0,     4,     0,
       4,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     6,     1,     1,     0,     6,     1,     3,
       2,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     0,     6,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     4,     1,     3,     2,     1,     1,     0,     6,
       3,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       3
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
  "lfc_interval", "readonly", "connect_timeout", "max_reconnect_tries",
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
       0,   295,   295,   295,   296,   296,   297,   297,   298,   298,
     299,   299,   300,   300,   301,   301,   302,   302,   303,   303,
     304,   304,   305,   305,   306,   306,   307,   307,   315,   316,
     317,   318,   319,   320,   321,   324,   329,   329,   340,   343,
     344,   347,   352,   358,   363,   363,   370,   371,   374,   378,
     382,   388,   388,   395,   396,   399,   403,   407,   417,   426,
     426,   441,   441,   455,   458,   464,   464,   473,   474,   475,
     482,   483,   484,   485,   486,   487,   488,   489,   490,   491,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,   513,   514,   515,   516,   517,   518,   519,   520,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   548,   554,   560,   566,   572,   578,
     584,   590,   596,   602,   608,   614,   614,   623,   629,   635,
     641,   647,   653,   659,   665,   665,   674,   677,   680,   683,
     686,   692,   692,   701,   701,   710,   716,   722,   722,   731,
     731,   740,   746,   752,   758,   764,   770,   776,   776,   788,
     789,   790,   795,   796,   797,   798,   799,   800,   801,   802,
     803,   804,   807,   807,   816,   816,   827,   827,   835,   836,
     839,   839,   847,   849,   853,   859,   865,   871,   877,   877,
     890,   890,   901,   902,   903,   908,   910,   910,   929,   929,
     942,   942,   953,   954,   957,   958,   959,   964,   964,   974,
     975,   976,   981,   982,   983,   984,   985,   986,   987,   988,
     989,   990,   991,   992,   993,   994,   995,   996,   997,   998,
     999,  1002,  1002,  1010,  1011,  1012,  1015,  1015,  1024,  1024,
    1033,  1033,  1042,  1048,  1048,  1057,  1063,  1069,  1075,  1081,
    1087,  1093,  1093,  1101,  1102,  1103,  1106,  1112,  1112,  1121,
    1121,  1130,  1130,  1139,  1139,  1148,  1148,  1159,  1160,  1161,
    1166,  1167,  1168,  1169,  1170,  1173,  1178,  1183,  1188,  1193,
    1200,  1200,  1213,  1214,  1215,  1220,  1221,  1222,  1223,  1224,
    1225,  1228,  1234,  1240,  1246,  1246,  1257,  1258,  1261,  1262,
    1263,  1268,  1268,  1278,  1278,  1288,  1289,  1290,  1293,  1296,
    1297,  1300,  1300,  1309,  1309,  1318,  1318,  1330,  1331,  1332,
    1337,  1338,  1339,  1340,  1341,  1342,  1345,  1351,  1357,  1363,
    1369,  1375,  1384,  1384,  1398,  1399,  1402,  1403,  1404,  1413,
    1413,  1439,  1439,  1450,  1451,  1452,  1458,  1459,  1460,  1461,
    1462,  1463,  1464,  1465,  1466,  1467,  1468,  1469,  1470,  1471,
    1472,  1473,  1474,  1475,  1476,  1477,  1478,  1479,  1480,  1481,
    1482,  1483,  1484,  1485,  1486,  1487,  1488,  1489,  1490,  1491,
    1492,  1493,  1494,  1495,  1496,  1497,  1498,  1499,  1500,  1501,
    1502,  1505,  1505,  1514,  1514,  1523,  1523,  1532,  1532,  1541,
    1541,  1550,  1550,  1559,  1559,  1570,  1576,  1582,  1588,  1588,
    1596,  1597,  1598,  1599,  1602,  1610,  1610,  1622,  1623,  1627,
    1628,  1629,  1634,  1634,  1642,  1643,  1644,  1649,  1650,  1651,
    1652,  1653,  1654,  1655,  1656,  1657,  1658,  1659,  1660,  1661,
    1662,  1663,  1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,
    1672,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,  1681,
    1682,  1683,  1684,  1685,  1686,  1687,  1688,  1695,  1695,  1709,
    1709,  1718,  1719,  1722,  1723,  1724,  1731,  1731,  1746,  1746,
    1760,  1761,  1764,  1765,  1766,  1771,  1772,  1773,  1774,  1775,
    1776,  1777,  1778,  1779,  1780,  1783,  1785,  1791,  1793,  1793,
    1802,  1802,  1811,  1811,  1820,  1822,  1822,  1831,  1841,  1841,
    1854,  1855,  1860,  1861,  1862,  1869,  1869,  1881,  1881,  1893,
    1894,  1899,  1900,  1901,  1908,  1909,  1910,  1911,  1912,  1913,
    1914,  1915,  1916,  1919,  1921,  1921,  1930,  1932,  1934,  1940,
    1949,  1949,  1962,  1963,  1966,  1967,  1968,  1973,  1973,  1983,
    1983,  1993,  1994,  1995,  2000,  2001,  2002,  2003,  2004,  2005,
    2006,  2009,  2009,  2018,  2018,  2043,  2043,  2073,  2073,  2084,
    2085,  2088,  2089,  2090,  2095,  2095,  2104,  2104,  2113,  2114,
    2117,  2118,  2119,  2125,  2126,  2127,  2128,  2129,  2130,  2131,
    2132,  2133,  2134,  2135,  2136,  2137,  2138,  2139,  2142,  2142,
    2151,  2151,  2160,  2160,  2169,  2169,  2178,  2178,  2189,  2189,
    2198,  2198,  2207,  2207,  2216,  2216,  2225,  2225,  2234,  2234,
    2243,  2243,  2257,  2257,  2268,  2269,  2275,  2275,  2286,  2287,
    2288,  2293,  2293,  2303,  2304,  2307,  2308,  2309,  2314,  2315,
    2316,  2317,  2318,  2319,  2320,  2321,  2322,  2323,  2324,  2325,
    2326,  2327,  2330,  2332,  2332,  2341,  2349,  2357,  2357,  2368,
    2369,  2370,  2375,  2376,  2377,  2378,  2379,  2382,  2382,  2391,
    2391,  2403,  2403,  2416,  2417,  2418,  2423,  2424,  2425,  2426,
    2427,  2428,  2431,  2437,  2437,  2446,  2452,  2452,  2462,  2462,
    2475,  2475,  2485,  2486,  2487,  2492,  2493,  2494,  2495,  2496,
    2497,  2498,  2499,  2500,  2501,  2502,  2503,  2504,  2505,  2506,
    2507,  2508,  2509,  2512,  2518,  2518,  2527,  2533,  2533,  2542,
    2548,  2554,  2554,  2563,  2564,  2567,  2567,  2577,  2577,  2587,
    2594,  2601,  2601,  2610,  2610,  2620,  2620,  2630,  2630,  2642,
    2642,  2654,  2654,  2664,  2665,  2666,  2672,  2673,  2676,  2676,
    2687,  2695,  2695,  2708,  2709,  2710,  2716,  2716,  2724,  2725,
    2726,  2731,  2732,  2733,  2734,  2735,  2736,  2737,  2740,  2746,
    2746,  2755,  2755,  2766,  2767,  2768,  2773,  2773,  2781,  2782,
    2783,  2788,  2789,  2790,  2791,  2792,  2795,  2795,  2804,  2810,
    2816,  2822,  2822,  2831,  2831,  2842,  2843,  2844,  2849,  2850,
    2853
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
#line 6142 "dhcp4_parser.cc"

#line 2859 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
