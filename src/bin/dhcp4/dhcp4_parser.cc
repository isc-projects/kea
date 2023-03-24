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
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 297 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 297 "dhcp4_parser.yy"
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
#line 306 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 307 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 308 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 309 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 310 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 311 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 312 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 313 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 314 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 315 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 316 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 317 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 318 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 326 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 327 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 328 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 329 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 330 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 331 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 332 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 335 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 340 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 345 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 351 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 358 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 363 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 369 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 374 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 377 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 385 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 389 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 393 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 399 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 401 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 410 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 414 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 418 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 428 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 437 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 442 "dhcp4_parser.yy"
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
#line 452 "dhcp4_parser.yy"
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
#line 461 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 469 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 475 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 479 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 486 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 136: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 561 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 137: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 567 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 138: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 573 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 139: // renew_timer: "renew-timer" ":" "integer"
#line 579 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 140: // rebind_timer: "rebind-timer" ":" "integer"
#line 585 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 141: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 591 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 142: // t1_percent: "t1-percent" ":" "floating point"
#line 597 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 143: // t2_percent: "t2-percent" ":" "floating point"
#line 603 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 144: // cache_threshold: "cache-threshold" ":" "floating point"
#line 609 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 145: // cache_max_age: "cache-max-age" ":" "integer"
#line 615 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 146: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 621 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 147: // $@20: %empty
#line 627 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 148: // server_tag: "server-tag" $@20 ":" "constant string"
#line 630 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 149: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 636 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 150: // $@21: %empty
#line 642 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1269 "dhcp4_parser.cc"
    break;

  case 151: // allocator: "allocator" $@21 ":" "constant string"
#line 645 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 152: // echo_client_id: "echo-client-id" ":" "boolean"
#line 651 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1289 "dhcp4_parser.cc"
    break;

  case 153: // match_client_id: "match-client-id" ":" "boolean"
#line 657 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1299 "dhcp4_parser.cc"
    break;

  case 154: // authoritative: "authoritative" ":" "boolean"
#line 663 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1309 "dhcp4_parser.cc"
    break;

  case 155: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 669 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1319 "dhcp4_parser.cc"
    break;

  case 156: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 675 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 157: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 681 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1339 "dhcp4_parser.cc"
    break;

  case 158: // $@22: %empty
#line 687 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1348 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 690 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "when-present"
#line 696 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1365 "dhcp4_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "never"
#line 699 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1373 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "always"
#line 702 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-not-present"
#line 705 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "boolean"
#line 708 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1398 "dhcp4_parser.cc"
    break;

  case 165: // $@23: %empty
#line 714 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 166: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 717 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 167: // $@24: %empty
#line 723 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp4_parser.cc"
    break;

  case 168: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 726 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1436 "dhcp4_parser.cc"
    break;

  case 169: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 732 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 170: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 738 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 171: // $@25: %empty
#line 744 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 172: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 747 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 173: // $@26: %empty
#line 753 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1484 "dhcp4_parser.cc"
    break;

  case 174: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 756 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 175: // store_extended_info: "store-extended-info" ":" "boolean"
#line 762 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1504 "dhcp4_parser.cc"
    break;

  case 176: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 768 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1514 "dhcp4_parser.cc"
    break;

  case 177: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 774 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 178: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 780 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 179: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 786 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 180: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 792 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1554 "dhcp4_parser.cc"
    break;

  case 181: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 798 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 182: // $@27: %empty
#line 804 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 183: // interfaces_config: "interfaces-config" $@27 ":" "{" interfaces_config_params "}"
#line 810 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 186: // interfaces_config_params: interfaces_config_params ","
#line 818 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1594 "dhcp4_parser.cc"
    break;

  case 197: // $@28: %empty
#line 835 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 198: // sub_interfaces4: "{" $@28 interfaces_config_params "}"
#line 839 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1613 "dhcp4_parser.cc"
    break;

  case 199: // $@29: %empty
#line 844 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 200: // interfaces_list: "interfaces" $@29 ":" list_strings
#line 850 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 201: // $@30: %empty
#line 855 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1643 "dhcp4_parser.cc"
    break;

  case 202: // dhcp_socket_type: "dhcp-socket-type" $@30 ":" socket_type
#line 858 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1652 "dhcp4_parser.cc"
    break;

  case 203: // socket_type: "raw"
#line 863 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1658 "dhcp4_parser.cc"
    break;

  case 204: // socket_type: "udp"
#line 864 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1664 "dhcp4_parser.cc"
    break;

  case 205: // $@31: %empty
#line 867 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1673 "dhcp4_parser.cc"
    break;

  case 206: // outbound_interface: "outbound-interface" $@31 ":" outbound_interface_value
#line 870 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1682 "dhcp4_parser.cc"
    break;

  case 207: // outbound_interface_value: "same-as-inbound"
#line 875 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1690 "dhcp4_parser.cc"
    break;

  case 208: // outbound_interface_value: "use-routing"
#line 877 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1698 "dhcp4_parser.cc"
    break;

  case 209: // re_detect: "re-detect" ":" "boolean"
#line 881 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1708 "dhcp4_parser.cc"
    break;

  case 210: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 887 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 211: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 893 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 212: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 899 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 213: // $@32: %empty
#line 905 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1750 "dhcp4_parser.cc"
    break;

  case 214: // lease_database: "lease-database" $@32 ":" "{" database_map_params "}"
#line 911 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1761 "dhcp4_parser.cc"
    break;

  case 215: // $@33: %empty
#line 918 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1773 "dhcp4_parser.cc"
    break;

  case 216: // sanity_checks: "sanity-checks" $@33 ":" "{" sanity_checks_params "}"
#line 924 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1782 "dhcp4_parser.cc"
    break;

  case 219: // sanity_checks_params: sanity_checks_params ","
#line 931 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1790 "dhcp4_parser.cc"
    break;

  case 222: // $@34: %empty
#line 940 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1799 "dhcp4_parser.cc"
    break;

  case 223: // lease_checks: "lease-checks" $@34 ":" "constant string"
#line 943 "dhcp4_parser.yy"
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
#line 1819 "dhcp4_parser.cc"
    break;

  case 224: // $@35: %empty
#line 959 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1828 "dhcp4_parser.cc"
    break;

  case 225: // extended_info_checks: "extended-info-checks" $@35 ":" "constant string"
#line 962 "dhcp4_parser.yy"
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
#line 1847 "dhcp4_parser.cc"
    break;

  case 226: // $@36: %empty
#line 977 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1859 "dhcp4_parser.cc"
    break;

  case 227: // hosts_database: "hosts-database" $@36 ":" "{" database_map_params "}"
#line 983 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1870 "dhcp4_parser.cc"
    break;

  case 228: // $@37: %empty
#line 990 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1882 "dhcp4_parser.cc"
    break;

  case 229: // hosts_databases: "hosts-databases" $@37 ":" "[" database_list "]"
#line 996 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1891 "dhcp4_parser.cc"
    break;

  case 234: // not_empty_database_list: not_empty_database_list ","
#line 1007 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1899 "dhcp4_parser.cc"
    break;

  case 235: // $@38: %empty
#line 1012 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1909 "dhcp4_parser.cc"
    break;

  case 236: // database: "{" $@38 database_map_params "}"
#line 1016 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1919 "dhcp4_parser.cc"
    break;

  case 239: // database_map_params: database_map_params ","
#line 1024 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1927 "dhcp4_parser.cc"
    break;

  case 262: // $@39: %empty
#line 1053 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1936 "dhcp4_parser.cc"
    break;

  case 263: // database_type: "type" $@39 ":" db_type
#line 1056 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1945 "dhcp4_parser.cc"
    break;

  case 264: // db_type: "memfile"
#line 1061 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1951 "dhcp4_parser.cc"
    break;

  case 265: // db_type: "mysql"
#line 1062 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1957 "dhcp4_parser.cc"
    break;

  case 266: // db_type: "postgresql"
#line 1063 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1963 "dhcp4_parser.cc"
    break;

  case 267: // $@40: %empty
#line 1066 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 268: // user: "user" $@40 ":" "constant string"
#line 1069 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1982 "dhcp4_parser.cc"
    break;

  case 269: // $@41: %empty
#line 1075 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 270: // password: "password" $@41 ":" "constant string"
#line 1078 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 271: // $@42: %empty
#line 1084 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 272: // host: "host" $@42 ":" "constant string"
#line 1087 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 273: // port: "port" ":" "integer"
#line 1093 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2030 "dhcp4_parser.cc"
    break;

  case 274: // $@43: %empty
#line 1099 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2039 "dhcp4_parser.cc"
    break;

  case 275: // name: "name" $@43 ":" "constant string"
#line 1102 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2049 "dhcp4_parser.cc"
    break;

  case 276: // persist: "persist" ":" "boolean"
#line 1108 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 277: // lfc_interval: "lfc-interval" ":" "integer"
#line 1114 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 278: // readonly: "readonly" ":" "boolean"
#line 1120 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 279: // connect_timeout: "connect-timeout" ":" "integer"
#line 1126 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 280: // read_timeout: "read-timeout" ":" "integer"
#line 1132 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 281: // write_timeout: "write-timeout" ":" "integer"
#line 1138 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 282: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1144 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2119 "dhcp4_parser.cc"
    break;

  case 283: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1150 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2129 "dhcp4_parser.cc"
    break;

  case 284: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1156 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2139 "dhcp4_parser.cc"
    break;

  case 285: // $@44: %empty
#line 1162 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2148 "dhcp4_parser.cc"
    break;

  case 286: // on_fail: "on-fail" $@44 ":" on_fail_mode
#line 1165 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2157 "dhcp4_parser.cc"
    break;

  case 287: // on_fail_mode: "stop-retry-exit"
#line 1170 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2163 "dhcp4_parser.cc"
    break;

  case 288: // on_fail_mode: "serve-retry-exit"
#line 1171 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2169 "dhcp4_parser.cc"
    break;

  case 289: // on_fail_mode: "serve-retry-continue"
#line 1172 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2175 "dhcp4_parser.cc"
    break;

  case 290: // max_row_errors: "max-row-errors" ":" "integer"
#line 1175 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2185 "dhcp4_parser.cc"
    break;

  case 291: // $@45: %empty
#line 1181 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp4_parser.cc"
    break;

  case 292: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1184 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2204 "dhcp4_parser.cc"
    break;

  case 293: // $@46: %empty
#line 1190 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2213 "dhcp4_parser.cc"
    break;

  case 294: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1193 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2223 "dhcp4_parser.cc"
    break;

  case 295: // $@47: %empty
#line 1199 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2232 "dhcp4_parser.cc"
    break;

  case 296: // key_file: "key-file" $@47 ":" "constant string"
#line 1202 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2242 "dhcp4_parser.cc"
    break;

  case 297: // $@48: %empty
#line 1208 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 298: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1211 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2261 "dhcp4_parser.cc"
    break;

  case 299: // $@49: %empty
#line 1217 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2273 "dhcp4_parser.cc"
    break;

  case 300: // host_reservation_identifiers: "host-reservation-identifiers" $@49 ":" "[" host_reservation_identifiers_list "]"
#line 1223 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2282 "dhcp4_parser.cc"
    break;

  case 303: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1230 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2290 "dhcp4_parser.cc"
    break;

  case 309: // duid_id: "duid"
#line 1242 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2299 "dhcp4_parser.cc"
    break;

  case 310: // hw_address_id: "hw-address"
#line 1247 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2308 "dhcp4_parser.cc"
    break;

  case 311: // circuit_id: "circuit-id"
#line 1252 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2317 "dhcp4_parser.cc"
    break;

  case 312: // client_id: "client-id"
#line 1257 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2326 "dhcp4_parser.cc"
    break;

  case 313: // flex_id: "flex-id"
#line 1262 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2335 "dhcp4_parser.cc"
    break;

  case 314: // $@50: %empty
#line 1269 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 315: // dhcp_multi_threading: "multi-threading" $@50 ":" "{" multi_threading_params "}"
#line 1275 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2358 "dhcp4_parser.cc"
    break;

  case 318: // multi_threading_params: multi_threading_params ","
#line 1284 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2366 "dhcp4_parser.cc"
    break;

  case 325: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1297 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 326: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1303 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 327: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1309 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2396 "dhcp4_parser.cc"
    break;

  case 328: // $@51: %empty
#line 1315 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2408 "dhcp4_parser.cc"
    break;

  case 329: // hooks_libraries: "hooks-libraries" $@51 ":" "[" hooks_libraries_list "]"
#line 1321 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2417 "dhcp4_parser.cc"
    break;

  case 334: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1332 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2425 "dhcp4_parser.cc"
    break;

  case 335: // $@52: %empty
#line 1337 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 336: // hooks_library: "{" $@52 hooks_params "}"
#line 1341 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 337: // $@53: %empty
#line 1347 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp4_parser.cc"
    break;

  case 338: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1351 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2465 "dhcp4_parser.cc"
    break;

  case 341: // hooks_params: hooks_params ","
#line 1359 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2473 "dhcp4_parser.cc"
    break;

  case 345: // $@54: %empty
#line 1369 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 346: // library: "library" $@54 ":" "constant string"
#line 1372 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 347: // $@55: %empty
#line 1378 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 348: // parameters: "parameters" $@55 ":" map_value
#line 1381 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2510 "dhcp4_parser.cc"
    break;

  case 349: // $@56: %empty
#line 1387 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2522 "dhcp4_parser.cc"
    break;

  case 350: // expired_leases_processing: "expired-leases-processing" $@56 ":" "{" expired_leases_params "}"
#line 1393 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2532 "dhcp4_parser.cc"
    break;

  case 353: // expired_leases_params: expired_leases_params ","
#line 1401 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2540 "dhcp4_parser.cc"
    break;

  case 360: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1414 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 361: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1420 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2560 "dhcp4_parser.cc"
    break;

  case 362: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1426 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2570 "dhcp4_parser.cc"
    break;

  case 363: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1432 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 364: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1438 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 365: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1444 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2600 "dhcp4_parser.cc"
    break;

  case 366: // $@57: %empty
#line 1453 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2612 "dhcp4_parser.cc"
    break;

  case 367: // subnet4_list: "subnet4" $@57 ":" "[" subnet4_list_content "]"
#line 1459 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2621 "dhcp4_parser.cc"
    break;

  case 372: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1473 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2629 "dhcp4_parser.cc"
    break;

  case 373: // $@58: %empty
#line 1482 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2639 "dhcp4_parser.cc"
    break;

  case 374: // subnet4: "{" $@58 subnet4_params "}"
#line 1486 "dhcp4_parser.yy"
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
#line 2665 "dhcp4_parser.cc"
    break;

  case 375: // $@59: %empty
#line 1508 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2675 "dhcp4_parser.cc"
    break;

  case 376: // sub_subnet4: "{" $@59 subnet4_params "}"
#line 1512 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2685 "dhcp4_parser.cc"
    break;

  case 379: // subnet4_params: subnet4_params ","
#line 1521 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2693 "dhcp4_parser.cc"
    break;

  case 427: // $@60: %empty
#line 1576 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 428: // subnet: "subnet" $@60 ":" "constant string"
#line 1579 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 429: // $@61: %empty
#line 1585 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 430: // subnet_4o6_interface: "4o6-interface" $@61 ":" "constant string"
#line 1588 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2731 "dhcp4_parser.cc"
    break;

  case 431: // $@62: %empty
#line 1594 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp4_parser.cc"
    break;

  case 432: // subnet_4o6_interface_id: "4o6-interface-id" $@62 ":" "constant string"
#line 1597 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2750 "dhcp4_parser.cc"
    break;

  case 433: // $@63: %empty
#line 1603 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp4_parser.cc"
    break;

  case 434: // subnet_4o6_subnet: "4o6-subnet" $@63 ":" "constant string"
#line 1606 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2769 "dhcp4_parser.cc"
    break;

  case 435: // $@64: %empty
#line 1612 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2778 "dhcp4_parser.cc"
    break;

  case 436: // interface: "interface" $@64 ":" "constant string"
#line 1615 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2788 "dhcp4_parser.cc"
    break;

  case 437: // $@65: %empty
#line 1621 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2797 "dhcp4_parser.cc"
    break;

  case 438: // client_class: "client-class" $@65 ":" "constant string"
#line 1624 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2807 "dhcp4_parser.cc"
    break;

  case 439: // $@66: %empty
#line 1630 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2819 "dhcp4_parser.cc"
    break;

  case 440: // require_client_classes: "require-client-classes" $@66 ":" list_strings
#line 1636 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2828 "dhcp4_parser.cc"
    break;

  case 441: // reservations_global: "reservations-global" ":" "boolean"
#line 1641 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2838 "dhcp4_parser.cc"
    break;

  case 442: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1647 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2848 "dhcp4_parser.cc"
    break;

  case 443: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1653 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2858 "dhcp4_parser.cc"
    break;

  case 444: // $@67: %empty
#line 1659 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2867 "dhcp4_parser.cc"
    break;

  case 445: // reservation_mode: "reservation-mode" $@67 ":" hr_mode
#line 1662 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2876 "dhcp4_parser.cc"
    break;

  case 446: // hr_mode: "disabled"
#line 1667 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2882 "dhcp4_parser.cc"
    break;

  case 447: // hr_mode: "out-of-pool"
#line 1668 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2888 "dhcp4_parser.cc"
    break;

  case 448: // hr_mode: "global"
#line 1669 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2894 "dhcp4_parser.cc"
    break;

  case 449: // hr_mode: "all"
#line 1670 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2900 "dhcp4_parser.cc"
    break;

  case 450: // id: "id" ":" "integer"
#line 1673 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2910 "dhcp4_parser.cc"
    break;

  case 451: // $@68: %empty
#line 1681 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2922 "dhcp4_parser.cc"
    break;

  case 452: // shared_networks: "shared-networks" $@68 ":" "[" shared_networks_content "]"
#line 1687 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2931 "dhcp4_parser.cc"
    break;

  case 457: // shared_networks_list: shared_networks_list ","
#line 1700 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2939 "dhcp4_parser.cc"
    break;

  case 458: // $@69: %empty
#line 1705 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2949 "dhcp4_parser.cc"
    break;

  case 459: // shared_network: "{" $@69 shared_network_params "}"
#line 1709 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2957 "dhcp4_parser.cc"
    break;

  case 462: // shared_network_params: shared_network_params ","
#line 1715 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2965 "dhcp4_parser.cc"
    break;

  case 505: // $@70: %empty
#line 1768 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2977 "dhcp4_parser.cc"
    break;

  case 506: // option_def_list: "option-def" $@70 ":" "[" option_def_list_content "]"
#line 1774 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2986 "dhcp4_parser.cc"
    break;

  case 507: // $@71: %empty
#line 1782 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2995 "dhcp4_parser.cc"
    break;

  case 508: // sub_option_def_list: "{" $@71 option_def_list "}"
#line 1785 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3003 "dhcp4_parser.cc"
    break;

  case 513: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1797 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3011 "dhcp4_parser.cc"
    break;

  case 514: // $@72: %empty
#line 1804 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3021 "dhcp4_parser.cc"
    break;

  case 515: // option_def_entry: "{" $@72 option_def_params "}"
#line 1808 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3033 "dhcp4_parser.cc"
    break;

  case 516: // $@73: %empty
#line 1819 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 517: // sub_option_def: "{" $@73 option_def_params "}"
#line 1823 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3055 "dhcp4_parser.cc"
    break;

  case 522: // not_empty_option_def_params: not_empty_option_def_params ","
#line 1839 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3063 "dhcp4_parser.cc"
    break;

  case 534: // code: "code" ":" "integer"
#line 1858 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3073 "dhcp4_parser.cc"
    break;

  case 536: // $@74: %empty
#line 1866 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3082 "dhcp4_parser.cc"
    break;

  case 537: // option_def_type: "type" $@74 ":" "constant string"
#line 1869 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3092 "dhcp4_parser.cc"
    break;

  case 538: // $@75: %empty
#line 1875 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 539: // option_def_record_types: "record-types" $@75 ":" "constant string"
#line 1878 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3111 "dhcp4_parser.cc"
    break;

  case 540: // $@76: %empty
#line 1884 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3120 "dhcp4_parser.cc"
    break;

  case 541: // space: "space" $@76 ":" "constant string"
#line 1887 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3130 "dhcp4_parser.cc"
    break;

  case 543: // $@77: %empty
#line 1895 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 544: // option_def_encapsulate: "encapsulate" $@77 ":" "constant string"
#line 1898 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 545: // option_def_array: "array" ":" "boolean"
#line 1904 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3159 "dhcp4_parser.cc"
    break;

  case 546: // $@78: %empty
#line 1914 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3171 "dhcp4_parser.cc"
    break;

  case 547: // option_data_list: "option-data" $@78 ":" "[" option_data_list_content "]"
#line 1920 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3180 "dhcp4_parser.cc"
    break;

  case 552: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1935 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3188 "dhcp4_parser.cc"
    break;

  case 553: // $@79: %empty
#line 1942 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3198 "dhcp4_parser.cc"
    break;

  case 554: // option_data_entry: "{" $@79 option_data_params "}"
#line 1946 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3207 "dhcp4_parser.cc"
    break;

  case 555: // $@80: %empty
#line 1954 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3217 "dhcp4_parser.cc"
    break;

  case 556: // sub_option_data: "{" $@80 option_data_params "}"
#line 1958 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3226 "dhcp4_parser.cc"
    break;

  case 561: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1974 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3234 "dhcp4_parser.cc"
    break;

  case 573: // $@81: %empty
#line 1995 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3243 "dhcp4_parser.cc"
    break;

  case 574: // option_data_data: "data" $@81 ":" "constant string"
#line 1998 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3253 "dhcp4_parser.cc"
    break;

  case 577: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2008 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 578: // option_data_always_send: "always-send" ":" "boolean"
#line 2014 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 579: // option_data_never_send: "never-send" ":" "boolean"
#line 2020 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 580: // $@82: %empty
#line 2029 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3295 "dhcp4_parser.cc"
    break;

  case 581: // pools_list: "pools" $@82 ":" "[" pools_list_content "]"
#line 2035 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3304 "dhcp4_parser.cc"
    break;

  case 586: // not_empty_pools_list: not_empty_pools_list ","
#line 2048 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3312 "dhcp4_parser.cc"
    break;

  case 587: // $@83: %empty
#line 2053 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 588: // pool_list_entry: "{" $@83 pool_params "}"
#line 2057 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 589: // $@84: %empty
#line 2063 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 590: // sub_pool4: "{" $@84 pool_params "}"
#line 2067 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3352 "dhcp4_parser.cc"
    break;

  case 593: // pool_params: pool_params ","
#line 2075 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3360 "dhcp4_parser.cc"
    break;

  case 601: // $@85: %empty
#line 2089 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3369 "dhcp4_parser.cc"
    break;

  case 602: // pool_entry: "pool" $@85 ":" "constant string"
#line 2092 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3379 "dhcp4_parser.cc"
    break;

  case 603: // $@86: %empty
#line 2098 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3387 "dhcp4_parser.cc"
    break;

  case 604: // user_context: "user-context" $@86 ":" map_value
#line 2100 "dhcp4_parser.yy"
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
#line 3414 "dhcp4_parser.cc"
    break;

  case 605: // $@87: %empty
#line 2123 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3422 "dhcp4_parser.cc"
    break;

  case 606: // comment: "comment" $@87 ":" "constant string"
#line 2125 "dhcp4_parser.yy"
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
#line 3451 "dhcp4_parser.cc"
    break;

  case 607: // $@88: %empty
#line 2153 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3463 "dhcp4_parser.cc"
    break;

  case 608: // reservations: "reservations" $@88 ":" "[" reservations_list "]"
#line 2159 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3472 "dhcp4_parser.cc"
    break;

  case 613: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2170 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3480 "dhcp4_parser.cc"
    break;

  case 614: // $@89: %empty
#line 2175 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3490 "dhcp4_parser.cc"
    break;

  case 615: // reservation: "{" $@89 reservation_params "}"
#line 2179 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3499 "dhcp4_parser.cc"
    break;

  case 616: // $@90: %empty
#line 2184 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3509 "dhcp4_parser.cc"
    break;

  case 617: // sub_reservation: "{" $@90 reservation_params "}"
#line 2188 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3518 "dhcp4_parser.cc"
    break;

  case 622: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2199 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3526 "dhcp4_parser.cc"
    break;

  case 638: // $@91: %empty
#line 2222 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 639: // next_server: "next-server" $@91 ":" "constant string"
#line 2225 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 640: // $@92: %empty
#line 2231 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 641: // server_hostname: "server-hostname" $@92 ":" "constant string"
#line 2234 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3564 "dhcp4_parser.cc"
    break;

  case 642: // $@93: %empty
#line 2240 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 643: // boot_file_name: "boot-file-name" $@93 ":" "constant string"
#line 2243 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3583 "dhcp4_parser.cc"
    break;

  case 644: // $@94: %empty
#line 2249 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 645: // ip_address: "ip-address" $@94 ":" "constant string"
#line 2252 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3602 "dhcp4_parser.cc"
    break;

  case 646: // $@95: %empty
#line 2258 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3614 "dhcp4_parser.cc"
    break;

  case 647: // ip_addresses: "ip-addresses" $@95 ":" list_strings
#line 2264 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3623 "dhcp4_parser.cc"
    break;

  case 648: // $@96: %empty
#line 2269 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3632 "dhcp4_parser.cc"
    break;

  case 649: // duid: "duid" $@96 ":" "constant string"
#line 2272 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3642 "dhcp4_parser.cc"
    break;

  case 650: // $@97: %empty
#line 2278 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3651 "dhcp4_parser.cc"
    break;

  case 651: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2281 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3661 "dhcp4_parser.cc"
    break;

  case 652: // $@98: %empty
#line 2287 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3670 "dhcp4_parser.cc"
    break;

  case 653: // client_id_value: "client-id" $@98 ":" "constant string"
#line 2290 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3680 "dhcp4_parser.cc"
    break;

  case 654: // $@99: %empty
#line 2296 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3689 "dhcp4_parser.cc"
    break;

  case 655: // circuit_id_value: "circuit-id" $@99 ":" "constant string"
#line 2299 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3699 "dhcp4_parser.cc"
    break;

  case 656: // $@100: %empty
#line 2305 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3708 "dhcp4_parser.cc"
    break;

  case 657: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2308 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3718 "dhcp4_parser.cc"
    break;

  case 658: // $@101: %empty
#line 2314 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3727 "dhcp4_parser.cc"
    break;

  case 659: // hostname: "hostname" $@101 ":" "constant string"
#line 2317 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3737 "dhcp4_parser.cc"
    break;

  case 660: // $@102: %empty
#line 2323 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3749 "dhcp4_parser.cc"
    break;

  case 661: // reservation_client_classes: "client-classes" $@102 ":" list_strings
#line 2329 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3758 "dhcp4_parser.cc"
    break;

  case 662: // $@103: %empty
#line 2337 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3770 "dhcp4_parser.cc"
    break;

  case 663: // relay: "relay" $@103 ":" "{" relay_map "}"
#line 2343 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3779 "dhcp4_parser.cc"
    break;

  case 666: // $@104: %empty
#line 2355 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3791 "dhcp4_parser.cc"
    break;

  case 667: // client_classes: "client-classes" $@104 ":" "[" client_classes_list "]"
#line 2361 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3800 "dhcp4_parser.cc"
    break;

  case 670: // client_classes_list: client_classes_list ","
#line 2368 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3808 "dhcp4_parser.cc"
    break;

  case 671: // $@105: %empty
#line 2373 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3818 "dhcp4_parser.cc"
    break;

  case 672: // client_class_entry: "{" $@105 client_class_params "}"
#line 2377 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3828 "dhcp4_parser.cc"
    break;

  case 677: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2389 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3836 "dhcp4_parser.cc"
    break;

  case 695: // $@106: %empty
#line 2414 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3845 "dhcp4_parser.cc"
    break;

  case 696: // client_class_test: "test" $@106 ":" "constant string"
#line 2417 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3855 "dhcp4_parser.cc"
    break;

  case 697: // $@107: %empty
#line 2423 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3864 "dhcp4_parser.cc"
    break;

  case 698: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2426 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3874 "dhcp4_parser.cc"
    break;

  case 699: // only_if_required: "only-if-required" ":" "boolean"
#line 2432 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3884 "dhcp4_parser.cc"
    break;

  case 700: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2440 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3894 "dhcp4_parser.cc"
    break;

  case 701: // $@108: %empty
#line 2448 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3906 "dhcp4_parser.cc"
    break;

  case 702: // control_socket: "control-socket" $@108 ":" "{" control_socket_params "}"
#line 2454 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3915 "dhcp4_parser.cc"
    break;

  case 705: // control_socket_params: control_socket_params ","
#line 2461 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3923 "dhcp4_parser.cc"
    break;

  case 711: // $@109: %empty
#line 2473 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3932 "dhcp4_parser.cc"
    break;

  case 712: // control_socket_type: "socket-type" $@109 ":" "constant string"
#line 2476 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3942 "dhcp4_parser.cc"
    break;

  case 713: // $@110: %empty
#line 2482 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3951 "dhcp4_parser.cc"
    break;

  case 714: // control_socket_name: "socket-name" $@110 ":" "constant string"
#line 2485 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3961 "dhcp4_parser.cc"
    break;

  case 715: // $@111: %empty
#line 2494 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3973 "dhcp4_parser.cc"
    break;

  case 716: // dhcp_queue_control: "dhcp-queue-control" $@111 ":" "{" queue_control_params "}"
#line 2500 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3984 "dhcp4_parser.cc"
    break;

  case 719: // queue_control_params: queue_control_params ","
#line 2509 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3992 "dhcp4_parser.cc"
    break;

  case 726: // enable_queue: "enable-queue" ":" "boolean"
#line 2522 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4002 "dhcp4_parser.cc"
    break;

  case 727: // $@112: %empty
#line 2528 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4011 "dhcp4_parser.cc"
    break;

  case 728: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2531 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4021 "dhcp4_parser.cc"
    break;

  case 729: // capacity: "capacity" ":" "integer"
#line 2537 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4031 "dhcp4_parser.cc"
    break;

  case 730: // $@113: %empty
#line 2543 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4040 "dhcp4_parser.cc"
    break;

  case 731: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2546 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4049 "dhcp4_parser.cc"
    break;

  case 732: // $@114: %empty
#line 2553 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 4061 "dhcp4_parser.cc"
    break;

  case 733: // dhcp_ddns: "dhcp-ddns" $@114 ":" "{" dhcp_ddns_params "}"
#line 2559 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4072 "dhcp4_parser.cc"
    break;

  case 734: // $@115: %empty
#line 2566 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4082 "dhcp4_parser.cc"
    break;

  case 735: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2570 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4092 "dhcp4_parser.cc"
    break;

  case 738: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2578 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4100 "dhcp4_parser.cc"
    break;

  case 757: // enable_updates: "enable-updates" ":" "boolean"
#line 2603 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4110 "dhcp4_parser.cc"
    break;

  case 758: // $@116: %empty
#line 2609 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4119 "dhcp4_parser.cc"
    break;

  case 759: // server_ip: "server-ip" $@116 ":" "constant string"
#line 2612 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4129 "dhcp4_parser.cc"
    break;

  case 760: // server_port: "server-port" ":" "integer"
#line 2618 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4139 "dhcp4_parser.cc"
    break;

  case 761: // $@117: %empty
#line 2624 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4148 "dhcp4_parser.cc"
    break;

  case 762: // sender_ip: "sender-ip" $@117 ":" "constant string"
#line 2627 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4158 "dhcp4_parser.cc"
    break;

  case 763: // sender_port: "sender-port" ":" "integer"
#line 2633 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4168 "dhcp4_parser.cc"
    break;

  case 764: // max_queue_size: "max-queue-size" ":" "integer"
#line 2639 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4178 "dhcp4_parser.cc"
    break;

  case 765: // $@118: %empty
#line 2645 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4187 "dhcp4_parser.cc"
    break;

  case 766: // ncr_protocol: "ncr-protocol" $@118 ":" ncr_protocol_value
#line 2648 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4196 "dhcp4_parser.cc"
    break;

  case 767: // ncr_protocol_value: "udp"
#line 2654 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4202 "dhcp4_parser.cc"
    break;

  case 768: // ncr_protocol_value: "tcp"
#line 2655 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4208 "dhcp4_parser.cc"
    break;

  case 769: // $@119: %empty
#line 2658 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4217 "dhcp4_parser.cc"
    break;

  case 770: // ncr_format: "ncr-format" $@119 ":" "JSON"
#line 2661 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4227 "dhcp4_parser.cc"
    break;

  case 771: // $@120: %empty
#line 2668 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4236 "dhcp4_parser.cc"
    break;

  case 772: // dep_qualifying_suffix: "qualifying-suffix" $@120 ":" "constant string"
#line 2671 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4246 "dhcp4_parser.cc"
    break;

  case 773: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2678 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4256 "dhcp4_parser.cc"
    break;

  case 774: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2685 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4266 "dhcp4_parser.cc"
    break;

  case 775: // $@121: %empty
#line 2692 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4275 "dhcp4_parser.cc"
    break;

  case 776: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2695 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4284 "dhcp4_parser.cc"
    break;

  case 777: // $@122: %empty
#line 2701 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4293 "dhcp4_parser.cc"
    break;

  case 778: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2704 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4303 "dhcp4_parser.cc"
    break;

  case 779: // $@123: %empty
#line 2711 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4312 "dhcp4_parser.cc"
    break;

  case 780: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2714 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4322 "dhcp4_parser.cc"
    break;

  case 781: // $@124: %empty
#line 2721 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4331 "dhcp4_parser.cc"
    break;

  case 782: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2724 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4341 "dhcp4_parser.cc"
    break;

  case 783: // $@125: %empty
#line 2733 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4353 "dhcp4_parser.cc"
    break;

  case 784: // config_control: "config-control" $@125 ":" "{" config_control_params "}"
#line 2739 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4363 "dhcp4_parser.cc"
    break;

  case 785: // $@126: %empty
#line 2745 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4373 "dhcp4_parser.cc"
    break;

  case 786: // sub_config_control: "{" $@126 config_control_params "}"
#line 2749 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4382 "dhcp4_parser.cc"
    break;

  case 789: // config_control_params: config_control_params ","
#line 2757 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4390 "dhcp4_parser.cc"
    break;

  case 792: // $@127: %empty
#line 2767 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4402 "dhcp4_parser.cc"
    break;

  case 793: // config_databases: "config-databases" $@127 ":" "[" database_list "]"
#line 2773 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4411 "dhcp4_parser.cc"
    break;

  case 794: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2778 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4421 "dhcp4_parser.cc"
    break;

  case 795: // $@128: %empty
#line 2786 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4433 "dhcp4_parser.cc"
    break;

  case 796: // loggers: "loggers" $@128 ":" "[" loggers_entries "]"
#line 2792 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4442 "dhcp4_parser.cc"
    break;

  case 799: // loggers_entries: loggers_entries ","
#line 2801 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4450 "dhcp4_parser.cc"
    break;

  case 800: // $@129: %empty
#line 2807 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4460 "dhcp4_parser.cc"
    break;

  case 801: // logger_entry: "{" $@129 logger_params "}"
#line 2811 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4468 "dhcp4_parser.cc"
    break;

  case 804: // logger_params: logger_params ","
#line 2817 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4476 "dhcp4_parser.cc"
    break;

  case 812: // debuglevel: "debuglevel" ":" "integer"
#line 2831 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4486 "dhcp4_parser.cc"
    break;

  case 813: // $@130: %empty
#line 2837 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4495 "dhcp4_parser.cc"
    break;

  case 814: // severity: "severity" $@130 ":" "constant string"
#line 2840 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4505 "dhcp4_parser.cc"
    break;

  case 815: // $@131: %empty
#line 2846 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4517 "dhcp4_parser.cc"
    break;

  case 816: // output_options_list: "output_options" $@131 ":" "[" output_options_list_content "]"
#line 2852 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4526 "dhcp4_parser.cc"
    break;

  case 819: // output_options_list_content: output_options_list_content ","
#line 2859 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4534 "dhcp4_parser.cc"
    break;

  case 820: // $@132: %empty
#line 2864 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4544 "dhcp4_parser.cc"
    break;

  case 821: // output_entry: "{" $@132 output_params_list "}"
#line 2868 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4552 "dhcp4_parser.cc"
    break;

  case 824: // output_params_list: output_params_list ","
#line 2874 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4560 "dhcp4_parser.cc"
    break;

  case 830: // $@133: %empty
#line 2886 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4569 "dhcp4_parser.cc"
    break;

  case 831: // output: "output" $@133 ":" "constant string"
#line 2889 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4579 "dhcp4_parser.cc"
    break;

  case 832: // flush: "flush" ":" "boolean"
#line 2895 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4589 "dhcp4_parser.cc"
    break;

  case 833: // maxsize: "maxsize" ":" "integer"
#line 2901 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4599 "dhcp4_parser.cc"
    break;

  case 834: // maxver: "maxver" ":" "integer"
#line 2907 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4609 "dhcp4_parser.cc"
    break;

  case 835: // $@134: %empty
#line 2913 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4618 "dhcp4_parser.cc"
    break;

  case 836: // pattern: "pattern" $@134 ":" "constant string"
#line 2916 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4628 "dhcp4_parser.cc"
    break;

  case 837: // $@135: %empty
#line 2922 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4640 "dhcp4_parser.cc"
    break;

  case 838: // compatibility: "compatibility" $@135 ":" "{" compatibility_params "}"
#line 2928 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4649 "dhcp4_parser.cc"
    break;

  case 841: // compatibility_params: compatibility_params ","
#line 2935 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4657 "dhcp4_parser.cc"
    break;

  case 847: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2947 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4667 "dhcp4_parser.cc"
    break;

  case 848: // ignore_dhcp_server_identifier: "ignore-dhcp-server-identifier" ":" "boolean"
#line 2953 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("ignore-dhcp-server-identifier", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-dhcp-server-identifier", b);
}
#line 4677 "dhcp4_parser.cc"
    break;

  case 849: // ignore_rai_link_selection: "ignore-rai-link-selection" ":" "boolean"
#line 2959 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4687 "dhcp4_parser.cc"
    break;

  case 850: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 2965 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4697 "dhcp4_parser.cc"
    break;


#line 4701 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -1001;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     400, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,    34,    31,    61,    66,    94,   100,
     111,   118,   122,   130,   142,   144,   165,   172, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,    31,  -151,   137,   197,    87,   642,
      74,    43,   -21,   265,   233,   -94,   254,   212, -1001,   175,
      80,   181,   187,   213, -1001,    78, -1001, -1001, -1001, -1001,
     238,   294,   308, -1001, -1001, -1001,   311, -1001, -1001, -1001,
     319,   320,   321,   330,   331,   333,   334,   337,   365,   367,
     368, -1001,   369,   387,   389,   404,   405, -1001, -1001, -1001,
     425,   426,   427, -1001, -1001, -1001,   437, -1001, -1001, -1001,
   -1001, -1001,   447,   448,   452, -1001, -1001, -1001, -1001, -1001,
     453, -1001, -1001, -1001, -1001, -1001, -1001,   455,   458,   459,
   -1001, -1001,   460, -1001,   114, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,   461,   462,   466,   470, -1001,   132,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,   471, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,   140, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,   147, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001,   287,   353, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   432, -1001, -1001,   473, -1001,
   -1001, -1001,   476, -1001, -1001,   442,   478, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
     479,   480,   482, -1001, -1001, -1001, -1001,   474,   487, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001,   202, -1001, -1001, -1001,   489, -1001, -1001,   494,
   -1001,   498,   500, -1001, -1001,   502,   504, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,   214, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001,   505,   235, -1001, -1001, -1001, -1001,    31,    31,
   -1001,  -148,   507, -1001, -1001,   509,   510,   512,   301,   303,
     304,   514,   517,   520,   313,   524,   525,   526,   317,   318,
     323,   326,   327,   328,   332,   335,   338,   329,   340,   529,
     343,   346,   336,   339,   347,   530,   542,   552,   354,   355,
     356,   555,   563,   564,   361,   574,   579,   581,   582,   584,
     373,   374,   377,   592,   609,   610,   611,   612,   403,   614,
     615,   616,   617,   618,   619,   408,   409,   410,   623,   624,
   -1001,   197, -1001,   625,   626,   627,   416,   417,   420,   421,
      87, -1001,   632,   633,   634,   635,   636,   637,   428,   639,
     640,   641,   642, -1001,   644,    74, -1001,   646,   647,   648,
     649,   650,   651,   652,   653, -1001,    43, -1001,   654,   655,
     449,   656,   658,   660,   450, -1001,   265,   661,   454,   463,
     464, -1001,   233,   664,   665,   -92, -1001,   465,   667,   674,
     468,   679,   472,   475,   684,   686,   477,   481,   688,   690,
     691,   692,   254, -1001,   694,   485,   212, -1001, -1001, -1001,
     696,   710,   711,   712,   713, -1001, -1001, -1001,   433,   488,
     521, -1001,   723,   729,   732, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,   527, -1001, -1001, -1001,
   -1001, -1001,  -123,   532,   533, -1001, -1001, -1001,   733,   734,
     743, -1001,   537,   752,   751,   546,    53, -1001, -1001, -1001,
     755,   759,   760,   762,   761, -1001,   765,   766,   767,   768,
     556,   566, -1001, -1001, -1001,   771,   770, -1001,   775,   222,
     237, -1001, -1001, -1001, -1001, -1001,   568,   569,   570,   779,
     572,   573, -1001,   775,   575,   780, -1001,   576, -1001,   775,
     577,   578,   580,   583,   585,   586,   587, -1001,   588,   589,
   -1001,   590,   591,   593, -1001, -1001,   594, -1001, -1001, -1001,
   -1001,   595,   751, -1001, -1001,   596,   597, -1001,   598, -1001,
   -1001,    15,   621, -1001, -1001,  -123,   599,   600,   601, -1001,
     787, -1001, -1001,    31,   197,   212,    87,   232, -1001, -1001,
   -1001,   351,   351,   788, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001,   798,   808,   809, -1001,   810, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,    56,   811,   812,   813,
     241,    48,   -59,     5,   254, -1001, -1001,   814,  -109, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
     815, -1001, -1001, -1001, -1001,   184, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,   788, -1001,   283,   285,   289, -1001,
   -1001,   291, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   790,
     821,   822,   823,   824,   825,   826,   827,   834,   835, -1001,
     836, -1001, -1001, -1001, -1001, -1001,   302, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   305,
   -1001,   837,   838, -1001, -1001,   839,   841, -1001, -1001,   840,
     844, -1001, -1001,   842,   846, -1001, -1001,   845,   847, -1001,
   -1001, -1001, -1001, -1001, -1001,    64, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001,    88, -1001, -1001,   848,   849, -1001, -1001,
     850,   854, -1001,   855,   856,   857,   858,   859,   860,   306,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001,   861,   862,   873,
   -1001,   341, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001,   342, -1001, -1001, -1001,   874, -1001,   875,
   -1001, -1001, -1001,   345, -1001, -1001, -1001, -1001, -1001,   349,
   -1001,   200, -1001,   876,   887,   888,   889, -1001,   352, -1001,
   -1001, -1001, -1001, -1001,   629, -1001,   852,   891, -1001, -1001,
   -1001, -1001,   890,   893, -1001, -1001, -1001,   896,   897,   232,
   -1001,   898,   899,   900,   901,   683,   693,   699,   701,   704,
     705,   706,   714,   715,   717,   902,   718,   904,   906,   911,
     920,   351, -1001, -1001,   351, -1001,   788,   642, -1001,   798,
     265, -1001,   808,   233, -1001,   809,   802, -1001,   810,    56,
   -1001,   127,   811, -1001,    43, -1001,   812,   -94, -1001,   813,
     719,   720,   721,   722,   725,   727,   241, -1001,   709,   728,
     730,    48, -1001,   923,   933,   -59, -1001,   731,   941,   741,
     944,     5, -1001, -1001,   -57,   814, -1001,   750,   753,   754,
     769,  -109, -1001, -1001,   998,  1005,    74, -1001,   815,  1008,
   -1001, -1001,   805,   877, -1001,    38,   881,   882,   883, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   192,
   -1001,   884,   885,   886,   892, -1001,   362, -1001,   429, -1001,
    1013, -1001,  1014, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   430,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001,  1021, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,  1018,  1025, -1001, -1001,
   -1001, -1001, -1001, -1001,  1030, -1001,   436, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   894,
     895, -1001, -1001,   903, -1001,    31, -1001, -1001,  1044, -1001,
   -1001, -1001, -1001, -1001,   439, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,   905,   445, -1001,   775,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001,   802, -1001,  1045,  1083,   907, -1001,   127, -1001, -1001,
   -1001, -1001, -1001, -1001,  1096,   908,  1097,   -57, -1001, -1001,
   -1001, -1001, -1001,   912,   913, -1001, -1001,  1098, -1001,   914,
   -1001, -1001, -1001,  1095, -1001, -1001,   201, -1001,    21,  1095,
   -1001, -1001,  1100,  1102,  1105, -1001,   446, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,  1106,   915,   910,   916,  1107,    21,
   -1001,   919, -1001, -1001, -1001,   921, -1001, -1001, -1001
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   197,     9,   375,    11,   589,    13,
     616,    15,   507,    17,   516,    19,   555,    21,   337,    23,
     734,    25,   785,    27,    46,    39,     0,     0,     0,     0,
       0,   618,     0,   518,   557,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   783,   182,   215,
       0,     0,     0,   638,   640,   642,     0,   213,   226,   228,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   147,     0,     0,     0,     0,     0,   158,   165,   167,
       0,     0,     0,   366,   505,   546,     0,   150,   451,   603,
     605,   444,     0,     0,     0,   299,   666,   607,   328,   349,
       0,   314,   701,   715,   732,   171,   173,     0,     0,     0,
     795,   837,     0,   135,     0,    67,    70,    71,    72,    73,
      74,   108,   109,   110,   111,   112,    75,   103,   132,   133,
      92,    93,    94,   116,   117,   118,   119,   120,   121,   122,
     123,   114,   115,   124,   125,   126,   128,   129,   130,   134,
      78,    79,   100,    80,    81,    82,   127,    86,    87,    76,
     105,   106,   107,   104,    77,    84,    85,    98,    99,   101,
      95,    96,    97,    83,    88,    89,    90,    91,   102,   113,
     131,   199,   201,   205,     0,     0,     0,     0,   196,     0,
     184,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     429,   431,   433,   580,   427,   435,     0,   439,   437,   662,
     426,   380,   381,   382,   383,   384,   408,   409,   410,   411,
     412,   424,   398,   399,   413,   414,   415,   416,   417,   418,
     419,   420,   421,   422,   423,   425,     0,   377,   387,   403,
     404,   405,   388,   390,   391,   394,   395,   396,   393,   389,
     385,   386,   406,   407,   392,   400,   401,   402,   397,   601,
     600,   596,   597,   595,     0,   591,   594,   598,   599,   660,
     648,   650,   654,   652,   658,   656,   644,   637,   631,   635,
     636,     0,   619,   620,   632,   633,   634,   628,   623,   629,
     625,   626,   627,   630,   624,     0,   536,   274,     0,   540,
     538,   543,     0,   532,   533,     0,   519,   520,   523,   535,
     524,   525,   526,   542,   527,   528,   529,   530,   531,   573,
       0,     0,     0,   571,   572,   575,   576,     0,   558,   559,
     562,   563,   564,   565,   566,   567,   568,   569,   570,   345,
     347,   342,     0,   339,   343,   344,     0,   771,   758,     0,
     761,     0,     0,   765,   769,     0,     0,   775,   777,   779,
     781,   756,   754,   755,     0,   736,   739,   740,   741,   742,
     743,   744,   745,   746,   751,   747,   748,   749,   750,   752,
     753,   792,     0,     0,   787,   790,   791,    45,    50,     0,
      37,    43,     0,    64,    60,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,    69,    66,     0,     0,     0,     0,     0,     0,     0,
     186,   198,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   379,   376,     0,   593,   590,     0,     0,     0,
       0,     0,     0,     0,     0,   617,   622,   508,     0,     0,
       0,     0,     0,     0,     0,   517,   522,     0,     0,     0,
       0,   556,   561,     0,     0,   341,   338,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   738,   735,     0,     0,   789,   786,    49,    41,
       0,     0,     0,     0,     0,   152,   153,   154,     0,     0,
       0,   181,     0,     0,     0,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,     0,   176,   177,   155,
     156,   157,     0,     0,     0,   169,   170,   175,     0,     0,
       0,   149,     0,     0,     0,     0,     0,   441,   442,   443,
       0,     0,     0,     0,     0,   700,     0,     0,     0,     0,
       0,     0,   178,   179,   180,     0,     0,    68,     0,     0,
       0,   209,   210,   211,   212,   185,     0,     0,     0,     0,
       0,     0,   450,     0,     0,     0,   378,     0,   592,     0,
       0,     0,     0,     0,     0,     0,     0,   621,     0,     0,
     534,     0,     0,     0,   545,   521,     0,   577,   578,   579,
     560,     0,     0,   340,   757,     0,     0,   760,     0,   763,
     764,     0,     0,   773,   774,     0,     0,     0,     0,   737,
       0,   794,   788,     0,     0,     0,     0,     0,   639,   641,
     643,     0,     0,   230,   148,   160,   161,   162,   163,   164,
     159,   166,   168,   368,   509,   548,   151,   453,    38,   604,
     606,   446,   447,   448,   449,   445,     0,     0,   609,   330,
       0,     0,     0,     0,     0,   172,   174,     0,     0,    51,
     200,   203,   204,   202,   207,   208,   206,   430,   432,   434,
     582,   428,   436,   440,   438,     0,   602,   661,   649,   651,
     655,   653,   659,   657,   645,   537,   275,   541,   539,   544,
     574,   346,   348,   772,   759,   762,   767,   768,   766,   770,
     776,   778,   780,   782,   230,    42,     0,     0,     0,   222,
     224,     0,   217,   220,   221,   262,   267,   269,   271,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   285,
       0,   291,   293,   295,   297,   261,     0,   237,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,     0,
     235,     0,   231,   232,   373,     0,   369,   370,   514,     0,
     510,   511,   553,     0,   549,   550,   458,     0,   454,   455,
     309,   310,   311,   312,   313,     0,   301,   304,   305,   306,
     307,   308,   671,     0,   668,   614,     0,   610,   611,   335,
       0,   331,   332,     0,     0,     0,     0,     0,     0,     0,
     351,   354,   355,   356,   357,   358,   359,     0,     0,     0,
     324,     0,   316,   319,   320,   321,   322,   323,   711,   713,
     710,   708,   709,     0,   703,   706,   707,     0,   727,     0,
     730,   723,   724,     0,   717,   720,   721,   722,   725,     0,
     800,     0,   797,     0,     0,     0,     0,   846,     0,   839,
     842,   843,   844,   845,    53,   587,     0,   583,   584,   646,
     664,   665,     0,     0,    62,   784,   183,     0,     0,   219,
     216,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   239,   214,   227,     0,   229,   234,     0,   367,   372,
     518,   506,   513,   557,   547,   552,     0,   452,   457,   303,
     300,   673,   670,   667,   618,   608,   613,     0,   329,   334,
       0,     0,     0,     0,     0,     0,   353,   350,     0,     0,
       0,   318,   315,     0,     0,   705,   702,     0,     0,     0,
       0,   719,   716,   733,     0,   799,   796,     0,     0,     0,
       0,   841,   838,    55,     0,    54,     0,   581,   586,     0,
     663,   793,     0,     0,   218,     0,     0,     0,     0,   273,
     276,   277,   278,   279,   280,   281,   282,   283,   284,     0,
     290,     0,     0,     0,     0,   238,     0,   233,     0,   371,
       0,   512,     0,   551,   504,   481,   482,   483,   466,   467,
     486,   487,   488,   489,   490,   502,   469,   470,   491,   492,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   503,
     463,   464,   465,   479,   480,   476,   477,   478,   475,     0,
     460,   468,   484,   485,   471,   472,   473,   474,   456,   302,
     695,   697,     0,   689,   690,   691,   692,   693,   694,   682,
     683,   687,   688,   684,   685,   686,     0,   674,   675,   678,
     679,   680,   681,   669,     0,   612,     0,   333,   360,   361,
     362,   363,   364,   365,   352,   325,   326,   327,   317,     0,
       0,   704,   726,     0,   729,     0,   718,   815,     0,   813,
     811,   805,   809,   810,     0,   802,   807,   808,   806,   798,
     847,   848,   849,   850,   840,    52,    57,     0,   585,     0,
     223,   225,   264,   265,   266,   263,   268,   270,   272,   287,
     288,   289,   286,   292,   294,   296,   298,   236,   374,   515,
     554,   462,   459,     0,     0,     0,   672,   677,   615,   336,
     712,   714,   728,   731,     0,     0,     0,   804,   801,    56,
     588,   647,   461,     0,     0,   699,   676,     0,   812,     0,
     803,   696,   698,     0,   814,   820,     0,   817,     0,   819,
     816,   830,     0,     0,     0,   835,     0,   822,   825,   826,
     827,   828,   829,   818,     0,     0,     0,     0,     0,   824,
     821,     0,   832,   833,   834,     0,   823,   831,   836
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   -52, -1001,  -593, -1001,   161,
   -1001, -1001, -1001, -1001, -1001, -1001,  -637, -1001, -1001, -1001,
     -67, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   398,   613,
     -30,   -28,    26,   -54,   -34,   -27,     0,    16,    23,    39,
   -1001, -1001, -1001, -1001,    44, -1001, -1001,    47,    51,    52,
      54,    55,    57, -1001,   412,    58, -1001,    59, -1001,    62,
      65,    69, -1001,    70, -1001,    72, -1001, -1001, -1001, -1001,
   -1001,    36, -1001, -1001,   397,   605, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,   141, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001,   315, -1001,   115, -1001,  -708,   128,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
     -45, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,   109, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001,    92, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001,   106, -1001, -1001, -1001,   110,   602, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001,   102, -1001, -1001, -1001,
   -1001, -1001, -1001, -1000, -1001, -1001, -1001,   131, -1001, -1001,
   -1001,   129,   620, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001,  -993, -1001,   -65, -1001,   -53, -1001,    73,    75,    76,
      77, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   121, -1001,
   -1001,  -100,   -62, -1001, -1001, -1001, -1001, -1001,   133, -1001,
   -1001, -1001,   134, -1001,   603, -1001,   -63, -1001, -1001, -1001,
   -1001, -1001,   -61, -1001, -1001, -1001, -1001, -1001,   -26, -1001,
   -1001, -1001,   135, -1001, -1001, -1001,   138, -1001,   604, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001,    79, -1001, -1001, -1001,    82,   628, -1001, -1001,   -49,
   -1001,   -10, -1001,   -51, -1001, -1001, -1001,   120, -1001, -1001,
   -1001,   136, -1001,   622,     3, -1001,    13, -1001,    29, -1001,
     379, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,  -986, -1001,
   -1001, -1001, -1001, -1001,   139, -1001, -1001, -1001,   -95, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   117,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001,   104, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   411,   606,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,   444,
     607, -1001, -1001, -1001, -1001, -1001, -1001,   108, -1001, -1001,
     -93, -1001, -1001, -1001, -1001, -1001, -1001,  -113, -1001, -1001,
    -132, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001, -1001,
   -1001,   107, -1001, -1001, -1001, -1001
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   739,
      82,    83,    39,    64,    79,    80,   760,   964,  1064,  1065,
     835,    41,    66,    85,   432,    86,    43,    67,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   459,   168,   169,   475,   170,   171,   172,   173,
     174,   175,   176,   465,   730,   177,   466,   178,   467,   179,
     180,   181,   493,   182,   494,   183,   184,   185,   186,   187,
     188,   189,   190,   436,   229,   230,    45,    68,   231,   503,
     232,   504,   763,   233,   505,   766,   234,   235,   236,   237,
     191,   445,   192,   437,   811,   812,   813,   977,   814,   978,
     193,   446,   194,   447,   861,   862,   863,  1004,   836,   837,
     838,   981,  1225,   839,   982,   840,   983,   841,   984,   842,
     843,   539,   844,   845,   846,   847,   848,   849,   850,   851,
     852,   853,   995,  1232,   854,   855,   997,   856,   998,   857,
     999,   858,  1000,   195,   483,   885,   886,   887,   888,   889,
     890,   891,   196,   489,   921,   922,   923,   924,   925,   197,
     486,   900,   901,   902,  1027,    59,    75,   382,   383,   384,
     553,   385,   554,   198,   487,   909,   910,   911,   912,   913,
     914,   915,   916,   199,   471,   865,   866,   867,  1007,    47,
      69,   276,   277,   278,   516,   279,   512,   280,   513,   281,
     514,   282,   517,   283,   520,   284,   519,   200,   201,   202,
     203,   479,   745,   289,   204,   476,   877,   878,   879,  1016,
    1139,  1140,   205,   472,    53,    72,   869,   870,   871,  1010,
      55,    73,   345,   346,   347,   348,   349,   350,   351,   538,
     352,   542,   353,   541,   354,   355,   543,   356,   206,   473,
     873,   874,   875,  1013,    57,    74,   367,   368,   369,   370,
     371,   547,   372,   373,   374,   375,   376,   291,   515,   966,
     967,   968,  1066,    49,    70,   304,   305,   306,   524,   207,
     477,   208,   478,   209,   485,   896,   897,   898,  1024,    51,
      71,   321,   322,   323,   210,   441,   211,   442,   212,   443,
     327,   534,   971,  1069,   328,   528,   329,   529,   330,   531,
     331,   530,   332,   533,   333,   532,   334,   527,   298,   521,
     972,   213,   484,   893,   894,  1021,  1166,  1167,  1168,  1169,
    1170,  1243,  1171,  1244,  1172,   214,   215,   490,   933,   934,
     935,  1043,   936,  1044,   216,   491,   943,   944,   945,   946,
    1048,   947,   948,  1050,   217,   492,    61,    76,   404,   405,
     406,   407,   559,   408,   409,   561,   410,   411,   412,   564,
     798,   413,   565,   414,   558,   415,   416,   417,   568,   418,
     569,   419,   570,   420,   571,   218,   435,    63,    77,   423,
     424,   425,   574,   426,   219,   498,   951,   952,  1054,  1204,
    1205,  1206,  1207,  1256,  1208,  1254,  1276,  1277,  1278,  1286,
    1287,  1288,  1294,  1289,  1290,  1291,  1292,  1298,   220,   499,
     958,   959,   960,   961,   962,   963
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     153,   228,   250,   300,   317,   301,   343,   363,   381,   401,
     335,   365,    78,   366,   859,   254,  1131,   302,   294,   238,
     292,   307,   319,  1132,   357,   377,   773,   402,   344,   364,
    1147,   738,   777,   796,    28,   255,    29,   337,    30,   251,
      31,   252,   256,   290,   303,   318,   379,   380,   379,   380,
     129,   130,   129,   130,   725,   726,   727,   728,   239,   293,
     308,   320,    81,   358,   378,   580,   403,  1019,    40,   257,
    1020,   124,   295,    42,   324,    93,    94,    95,  1222,  1223,
    1224,   433,   296,   428,   325,   258,   434,   953,   954,   955,
     956,  1022,   259,   729,  1023,   253,   928,   929,   297,   738,
     326,    44,   221,   222,   152,   275,   223,    46,   260,   224,
     225,   226,   227,   261,   129,   130,   262,   501,    48,   152,
     263,   264,   502,   265,   266,    50,   267,   268,   269,    52,
    1197,   270,  1198,  1199,   271,   510,   125,    54,   272,   273,
     511,   274,   285,   522,   286,   287,   288,    84,   523,    56,
     525,    58,   129,   130,   152,   526,   152,   129,   130,    93,
      94,    95,    96,   937,   938,   939,   309,   125,   741,   742,
     743,   744,    60,   310,   311,   312,   313,   314,   315,    62,
     316,   427,   299,   129,   130,   429,   880,   881,   882,   883,
     797,   884,   100,   101,   102,   430,   129,   130,   247,   917,
     918,   919,   248,  1055,  1279,   555,  1056,  1280,    87,  1281,
     556,    88,  1282,  1283,  1284,  1285,   431,   572,   940,   124,
     125,   337,   573,    89,   421,   422,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   129,   130,   576,   761,
     762,  1131,   438,   577,    32,    33,    34,    35,  1132,  1229,
    1230,  1231,  1150,  1151,  1152,  1147,   152,   764,   765,   809,
     810,   152,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   501,   152,   576,   124,
     125,   974,   510,   975,   979,   535,  1096,   976,   439,   980,
     152,   126,   127,   128,   336,  1001,   129,   130,  1001,  1036,
    1002,   131,   440,  1003,  1037,   444,   132,   133,   134,   135,
     136,   316,   969,   448,   449,   450,   137,   337,   359,   338,
     339,   360,   361,   362,   451,   452,   138,   453,   454,   139,
     152,   455,   129,   130,  1041,  1045,   140,   141,  1051,  1042,
    1046,   142,   572,  1052,   143,  1061,   536,  1053,   144,   337,
    1062,   338,   339,   129,   130,  1001,   340,   341,   342,   456,
    1237,   457,   458,   460,   129,   130,   578,   579,   145,   146,
     147,   148,   149,   150,   903,   904,   905,   906,   907,   908,
     815,   461,   151,   462,   816,   817,   818,   819,   820,   821,
     822,   823,   824,   825,   826,   827,   828,   829,   463,   464,
     152,   830,   831,   832,   833,   834,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   468,
     469,   470,   522,  1241,   153,   399,   400,  1238,  1242,   555,
     537,   474,  1257,   228,  1249,   337,   152,  1258,   525,  1299,
     545,   480,   481,  1260,  1300,   250,   482,   488,   300,   495,
     301,   238,   496,   497,   500,   506,   507,   152,   254,   317,
     508,   294,   302,   292,   509,   518,   307,   540,   152,   343,
     544,   546,   551,   548,   549,   363,   550,   319,   255,   365,
     552,   366,   251,   557,   252,   256,   290,   357,   560,   303,
     239,   344,   562,   377,   563,   401,   566,   364,   567,   575,
     318,   581,   293,   582,   583,   308,   584,   585,   588,   586,
     587,   589,   257,   402,   590,   295,   320,   591,   592,   593,
     594,   595,   596,   606,   612,   296,   358,   597,   258,   324,
     598,   599,   378,   604,   600,   259,   613,   601,   253,   325,
     602,   297,   609,   603,   605,   610,   614,   607,   275,   618,
     608,   260,   403,   611,   152,   326,   261,   619,   620,   262,
     615,   616,   617,   263,   264,   621,   265,   266,   622,   267,
     268,   269,  1261,   623,   270,   624,   625,   271,   626,   627,
     628,   272,   273,   629,   274,   285,   630,   286,   287,   288,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   631,   632,   633,   634,   635,   636,   637,
     638,   639,   640,   641,   642,   643,   644,   645,   646,   648,
     649,   650,   651,   652,   653,   654,   656,   657,   658,   659,
     660,   661,   662,   663,   664,   665,   718,   153,   667,   228,
     669,   670,   671,   672,   673,   674,   675,   676,   678,   679,
     681,   805,   682,   680,   683,   686,   684,   238,   691,   692,
     687,   695,    91,    92,    93,    94,    95,    96,   696,   688,
     689,   694,   697,   698,   920,   930,   699,   401,   701,   700,
     702,   957,   705,   703,   706,   707,   708,   704,   710,   711,
     713,   719,   926,   931,   941,   402,   239,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   714,   715,   716,
     717,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     721,   240,   241,   242,   720,   125,   722,   723,   733,   734,
     724,   927,   932,   942,   403,   731,   732,   127,   735,   243,
     736,   129,   130,   244,   245,   246,   131,   737,    30,   740,
     746,   132,   133,   134,   747,   748,   247,   749,   750,   755,
     248,   137,   751,   752,   753,   754,   757,   758,   249,   756,
     759,   767,   768,   769,   770,   771,   772,   775,   774,   776,
     778,   779,   804,   780,   985,   860,   781,   799,   782,   783,
     784,   785,   786,   787,   788,   864,   789,   790,   791,   793,
     794,   795,   801,   802,   803,   868,   872,   876,   892,   895,
     899,   950,   965,   145,   146,   986,   987,   988,   989,   990,
     991,   992,    91,    92,    93,    94,    95,    96,   993,   994,
     996,  1006,  1063,  1005,  1009,  1008,  1011,  1012,  1014,  1015,
    1018,  1017,  1026,   792,  1025,   152,  1028,  1029,  1067,  1030,
    1031,  1032,  1033,  1034,  1035,  1038,  1039,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,  1040,  1047,  1049,
    1057,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,  1058,  1059,  1060,  1068,   125,   337,  1079,  1070,  1071,
    1072,  1073,  1075,  1076,  1077,  1078,  1089,   127,  1091,  1080,
    1092,   129,   130,  1081,   245,  1093,   131,  1082,  1083,  1084,
    1085,   132,   133,   134,  1094,  1185,   247,  1189,  1086,  1087,
     248,  1088,  1090,  1178,  1179,  1180,  1181,  1190,   249,  1182,
     250,  1183,  1186,   343,  1187,  1193,   363,  1192,  1195,  1104,
     365,  1133,   366,   254,  1153,  1194,   294,   317,   292,  1159,
     381,   357,  1108,  1134,   377,   344,  1210,  1142,   364,  1211,
    1212,  1130,  1161,   255,   920,   319,  1158,   251,   930,   252,
     256,   290,  1109,   145,   146,  1213,  1105,  1200,  1106,  1110,
    1141,  1154,   926,  1155,   957,  1160,   931,   293,   318,   300,
     358,   301,   941,   378,  1215,  1202,  1143,   257,  1216,  1201,
     295,  1162,  1219,   302,   320,   152,  1111,   307,  1220,  1144,
     296,  1239,  1240,   258,  1163,  1245,  1246,   324,  1247,  1145,
     259,   927,  1112,   253,  1164,   932,   297,   325,  1248,  1113,
     303,   942,  1107,   275,  1203,  1146,   260,  1156,  1255,  1263,
    1165,   261,  1129,   326,   262,  1114,   308,  1157,   263,   264,
    1115,   265,   266,  1116,   267,   268,   269,  1117,  1118,   270,
    1119,  1120,   271,  1121,  1122,  1123,   272,   273,  1124,   274,
     285,  1125,   286,   287,   288,  1126,  1127,  1264,  1128,  1135,
    1221,  1136,  1137,  1138,  1226,  1227,  1228,  1233,  1234,  1235,
    1267,  1269,  1275,  1273,  1295,  1236,  1296,  1250,  1251,  1297,
    1301,  1305,   806,   808,   647,   655,  1252,   800,  1259,   973,
    1074,  1097,  1268,  1265,  1303,  1271,  1272,  1274,  1149,  1095,
    1304,  1302,  1307,  1188,  1308,  1177,  1098,  1176,  1184,  1148,
    1099,  1262,   666,  1253,  1100,  1101,  1175,  1218,  1217,   685,
    1103,  1102,  1266,   668,   970,  1196,   690,   693,   677,   807,
    1174,  1173,  1191,  1209,  1270,   949,  1293,  1306,  1214,     0,
       0,     0,     0,     0,  1104,     0,  1133,     0,   709,     0,
    1153,     0,     0,   712,     0,  1159,     0,  1108,  1134,     0,
    1200,     0,  1142,     0,     0,     0,  1130,     0,  1161,     0,
       0,     0,  1158,     0,     0,     0,     0,  1109,  1202,     0,
       0,  1105,  1201,  1106,  1110,  1141,     0,  1154,     0,  1155,
       0,  1160,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1143,     0,     0,     0,     0,     0,  1162,     0,     0,
       0,  1111,     0,     0,  1144,     0,     0,  1203,     0,     0,
    1163,     0,     0,     0,  1145,     0,     0,  1112,     0,     0,
    1164,     0,     0,     0,  1113,     0,     0,  1107,     0,     0,
    1146,     0,     0,  1156,     0,     0,  1165,  1129,     0,     0,
    1114,     0,     0,  1157,     0,  1115,     0,     0,  1116,     0,
       0,     0,  1117,  1118,     0,  1119,  1120,     0,  1121,  1122,
    1123,     0,     0,  1124,     0,     0,  1125,     0,     0,     0,
    1126,  1127,     0,  1128,  1135,     0,  1136,  1137,  1138
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      72,    74,    64,    74,   722,    69,  1016,    70,    69,    68,
      69,    70,    71,  1016,    73,    74,   663,    76,    73,    74,
    1016,   624,   669,    18,     0,    69,     5,    94,     7,    69,
       9,    69,    69,    69,    70,    71,   140,   141,   140,   141,
     109,   110,   109,   110,   177,   178,   179,   180,    68,    69,
      70,    71,   213,    73,    74,   213,    76,     3,     7,    69,
       6,    92,    69,     7,    71,    32,    33,    34,    40,    41,
      42,     3,    69,     3,    71,    69,     8,   196,   197,   198,
     199,     3,    69,   216,     6,    69,   155,   156,    69,   692,
      71,     7,    15,    16,   213,    69,    19,     7,    69,    22,
      23,    24,    25,    69,   109,   110,    69,     3,     7,   213,
      69,    69,     8,    69,    69,     7,    69,    69,    69,     7,
     187,    69,   189,   190,    69,     3,    93,     7,    69,    69,
       8,    69,    69,     3,    69,    69,    69,    10,     8,     7,
       3,     7,   109,   110,   213,     8,   213,   109,   110,    32,
      33,    34,    35,   158,   159,   160,   123,    93,   115,   116,
     117,   118,     7,   130,   131,   132,   133,   134,   135,     7,
     137,     6,   108,   109,   110,     4,   130,   131,   132,   133,
     175,   135,    65,    66,    67,     8,   109,   110,   124,   151,
     152,   153,   128,     3,     3,     3,     6,     6,    11,   188,
       8,    14,   191,   192,   193,   194,     3,     3,   213,    92,
      93,    94,     8,    26,    12,    13,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   109,   110,     3,    17,
      18,  1241,     4,     8,   213,   214,   215,   216,  1241,    57,
      58,    59,   125,   126,   127,  1241,   213,    20,    21,    27,
      28,   213,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,     3,   213,     3,    92,
      93,     8,     3,     8,     3,     8,  1004,     8,     4,     8,
     213,   104,   105,   106,    39,     3,   109,   110,     3,     3,
       8,   114,     4,     8,     8,     4,   119,   120,   121,   122,
     123,   137,   138,     4,     4,     4,   129,    94,    95,    96,
      97,    98,    99,   100,     4,     4,   139,     4,     4,   142,
     213,     4,   109,   110,     3,     3,   149,   150,     3,     8,
       8,   154,     3,     8,   157,     3,     3,     8,   161,    94,
       8,    96,    97,   109,   110,     3,   101,   102,   103,     4,
       8,     4,     4,     4,   109,   110,   428,   429,   181,   182,
     183,   184,   185,   186,   143,   144,   145,   146,   147,   148,
      39,     4,   195,     4,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,     4,     4,
     213,    60,    61,    62,    63,    64,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,     4,
       4,     4,     3,     3,   501,   181,   182,     8,     8,     3,
       8,     4,     3,   510,     8,    94,   213,     8,     3,     3,
       8,     4,     4,     8,     8,   522,     4,     4,   525,     4,
     525,   510,     4,     4,     4,     4,     4,   213,   522,   536,
       4,   522,   525,   522,     4,     4,   525,     4,   213,   546,
       4,     3,     8,     4,     4,   552,     4,   536,   522,   552,
       3,   552,   522,     4,   522,   522,   522,   546,     4,   525,
     510,   546,     4,   552,     4,   572,     4,   552,     4,     4,
     536,     4,   522,     4,     4,   525,     4,   216,     4,   216,
     216,     4,   522,   572,     4,   522,   536,   214,     4,     4,
       4,   214,   214,     4,     4,   522,   546,   214,   522,   536,
     214,   214,   552,   214,   216,   522,     4,   215,   522,   536,
     215,   522,   216,   215,   214,   216,     4,   214,   522,     4,
     214,   522,   572,   216,   213,   536,   522,     4,     4,   522,
     216,   216,   216,   522,   522,   214,   522,   522,     4,   522,
     522,   522,  1219,     4,   522,     4,     4,   522,     4,   216,
     216,   522,   522,   216,   522,   522,     4,   522,   522,   522,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,     4,     4,     4,     4,   214,     4,     4,
       4,     4,     4,     4,   216,   216,   216,     4,     4,     4,
       4,     4,   216,   216,   214,   214,     4,     4,     4,     4,
       4,     4,   214,     4,     4,     4,   213,   714,     4,   716,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   713,     4,   214,     4,     4,   216,   716,     4,     4,
     216,     4,    30,    31,    32,    33,    34,    35,     4,   216,
     216,   216,   214,     4,   751,   752,   214,   754,     4,   214,
       4,   758,     4,   216,     4,     4,     4,   216,     4,   214,
       4,   213,   751,   752,   753,   754,   716,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,     7,     7,     7,
       7,    79,    80,    81,    82,    83,    84,    85,    86,    87,
       7,    89,    90,    91,   213,    93,     7,     5,     5,     5,
     213,   751,   752,   753,   754,   213,   213,   105,     5,   107,
     213,   109,   110,   111,   112,   113,   114,     5,     7,   213,
       5,   119,   120,   121,     5,     5,   124,     5,     7,   213,
     128,   129,     7,     7,     7,     7,     5,     7,   136,   213,
       5,   213,   213,   213,     5,   213,   213,     7,   213,   213,
     213,   213,     5,   213,     4,     7,   213,   176,   213,   213,
     213,   213,   213,   213,   213,     7,   213,   213,   213,   213,
     213,   213,   213,   213,   213,     7,     7,     7,     7,     7,
       7,     7,     7,   181,   182,     4,     4,     4,     4,     4,
       4,     4,    30,    31,    32,    33,    34,    35,     4,     4,
       4,     3,   213,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     3,   692,     6,   213,     6,     3,     6,     4,
       4,     4,     4,     4,     4,     4,     4,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,     4,     4,     4,
       4,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,     4,     4,     4,     3,    93,    94,   214,     8,     6,
       4,     4,     4,     4,     4,     4,     4,   105,     4,   216,
       4,   109,   110,   214,   112,     4,   114,   216,   214,   214,
     214,   119,   120,   121,     4,   216,   124,     4,   214,   214,
     128,   214,   214,   214,   214,   214,   214,     4,   136,   214,
    1007,   214,   214,  1010,   214,     4,  1013,   216,     4,  1016,
    1013,  1016,  1013,  1007,  1021,   214,  1007,  1024,  1007,  1021,
    1027,  1010,  1016,  1016,  1013,  1010,   216,  1016,  1013,   216,
     216,  1016,  1021,  1007,  1041,  1024,  1021,  1007,  1045,  1007,
    1007,  1007,  1016,   181,   182,   216,  1016,  1054,  1016,  1016,
    1016,  1021,  1041,  1021,  1061,  1021,  1045,  1007,  1024,  1066,
    1010,  1066,  1051,  1013,     6,  1054,  1016,  1007,     3,  1054,
    1007,  1021,     4,  1066,  1024,   213,  1016,  1066,   213,  1016,
    1007,     8,     8,  1007,  1021,     4,     8,  1024,     3,  1016,
    1007,  1041,  1016,  1007,  1021,  1045,  1007,  1024,     8,  1016,
    1066,  1051,  1016,  1007,  1054,  1016,  1007,  1021,     4,     4,
    1021,  1007,  1016,  1024,  1007,  1016,  1066,  1021,  1007,  1007,
    1016,  1007,  1007,  1016,  1007,  1007,  1007,  1016,  1016,  1007,
    1016,  1016,  1007,  1016,  1016,  1016,  1007,  1007,  1016,  1007,
    1007,  1016,  1007,  1007,  1007,  1016,  1016,     4,  1016,  1016,
     213,  1016,  1016,  1016,   213,   213,   213,   213,   213,   213,
       4,     4,     7,     5,     4,   213,     4,   213,   213,     4,
       4,     4,   714,   716,   501,   510,   213,   705,   213,   804,
     979,  1006,   214,   216,   214,   213,   213,   213,  1019,  1001,
     214,   216,   213,  1041,   213,  1029,  1007,  1027,  1036,  1018,
    1009,  1241,   522,  1195,  1010,  1012,  1026,  1068,  1066,   546,
    1015,  1013,  1247,   525,   775,  1051,   552,   555,   536,   715,
    1024,  1022,  1045,  1055,  1257,   754,  1279,  1299,  1061,    -1,
      -1,    -1,    -1,    -1,  1241,    -1,  1241,    -1,   572,    -1,
    1247,    -1,    -1,   576,    -1,  1247,    -1,  1241,  1241,    -1,
    1257,    -1,  1241,    -1,    -1,    -1,  1241,    -1,  1247,    -1,
      -1,    -1,  1247,    -1,    -1,    -1,    -1,  1241,  1257,    -1,
      -1,  1241,  1257,  1241,  1241,  1241,    -1,  1247,    -1,  1247,
      -1,  1247,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1241,    -1,    -1,    -1,    -1,    -1,  1247,    -1,    -1,
      -1,  1241,    -1,    -1,  1241,    -1,    -1,  1257,    -1,    -1,
    1247,    -1,    -1,    -1,  1241,    -1,    -1,  1241,    -1,    -1,
    1247,    -1,    -1,    -1,  1241,    -1,    -1,  1241,    -1,    -1,
    1241,    -1,    -1,  1247,    -1,    -1,  1247,  1241,    -1,    -1,
    1241,    -1,    -1,  1247,    -1,  1241,    -1,    -1,  1241,    -1,
      -1,    -1,  1241,  1241,    -1,  1241,  1241,    -1,  1241,  1241,
    1241,    -1,    -1,  1241,    -1,    -1,  1241,    -1,    -1,    -1,
    1241,  1241,    -1,  1241,  1241,    -1,  1241,  1241,  1241
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,     0,     5,
       7,     9,   213,   214,   215,   216,   232,   233,   234,   239,
       7,   248,     7,   253,     7,   303,     7,   416,     7,   500,
       7,   516,     7,   451,     7,   457,     7,   481,     7,   392,
       7,   583,     7,   614,   240,   235,   249,   254,   304,   417,
     501,   517,   452,   458,   482,   393,   584,   615,   232,   241,
     242,   213,   237,   238,    10,   250,   252,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    92,    93,   104,   105,   106,   109,
     110,   114,   119,   120,   121,   122,   123,   129,   139,   142,
     149,   150,   154,   157,   161,   181,   182,   183,   184,   185,
     186,   195,   213,   247,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   270,   271,
     273,   274,   275,   276,   277,   278,   279,   282,   284,   286,
     287,   288,   290,   292,   293,   294,   295,   296,   297,   298,
     299,   317,   319,   327,   329,   370,   379,   386,   400,   410,
     434,   435,   436,   437,   441,   449,   475,   506,   508,   510,
     521,   523,   525,   548,   562,   563,   571,   581,   612,   621,
     645,    15,    16,    19,    22,    23,    24,    25,   247,   301,
     302,   305,   307,   310,   313,   314,   315,   316,   506,   508,
      89,    90,    91,   107,   111,   112,   113,   124,   128,   136,
     247,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   271,   274,   275,   276,   277,   278,   279,   282,   284,
     286,   287,   288,   290,   292,   298,   418,   419,   420,   422,
     424,   426,   428,   430,   432,   434,   435,   436,   437,   440,
     475,   494,   506,   508,   510,   521,   523,   525,   545,   108,
     247,   430,   432,   475,   502,   503,   504,   506,   508,   123,
     130,   131,   132,   133,   134,   135,   137,   247,   475,   506,
     508,   518,   519,   520,   521,   523,   525,   527,   531,   533,
     535,   537,   539,   541,   543,   449,    39,    94,    96,    97,
     101,   102,   103,   247,   347,   459,   460,   461,   462,   463,
     464,   465,   467,   469,   471,   472,   474,   506,   508,    95,
      98,    99,   100,   247,   347,   463,   469,   483,   484,   485,
     486,   487,   489,   490,   491,   492,   493,   506,   508,   140,
     141,   247,   394,   395,   396,   398,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   181,
     182,   247,   506,   508,   585,   586,   587,   588,   590,   591,
     593,   594,   595,   598,   600,   602,   603,   604,   606,   608,
     610,    12,    13,   616,   617,   618,   620,     6,     3,     4,
       8,     3,   251,     3,     8,   613,   300,   320,     4,     4,
       4,   522,   524,   526,     4,   318,   328,   330,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   269,
       4,     4,     4,     4,     4,   280,   283,   285,     4,     4,
       4,   411,   450,   476,     4,   272,   442,   507,   509,   438,
       4,     4,     4,   371,   549,   511,   387,   401,     4,   380,
     564,   572,   582,   289,   291,     4,     4,     4,   622,   646,
       4,     3,     8,   306,   308,   311,     4,     4,     4,     4,
       3,     8,   423,   425,   427,   495,   421,   429,     4,   433,
     431,   546,     3,     8,   505,     3,     8,   544,   532,   534,
     538,   536,   542,   540,   528,     8,     3,     8,   466,   348,
       4,   470,   468,   473,     4,     8,     3,   488,     4,     4,
       4,     8,     3,   397,   399,     3,     8,     4,   601,   589,
       4,   592,     4,     4,   596,   599,     4,     4,   605,   607,
     609,   611,     3,     8,   619,     4,     3,     8,   232,   232,
     213,     4,     4,     4,     4,   216,   216,   216,     4,     4,
       4,   214,     4,     4,     4,   214,   214,   214,   214,   214,
     216,   215,   215,   215,   214,   214,     4,   214,   214,   216,
     216,   216,     4,     4,     4,   216,   216,   216,     4,     4,
       4,   214,     4,     4,     4,     4,     4,   216,   216,   216,
       4,     4,     4,     4,     4,   214,     4,     4,     4,     4,
       4,     4,   216,   216,   216,     4,     4,   256,     4,     4,
       4,   216,   216,   214,   214,   302,     4,     4,     4,     4,
       4,     4,   214,     4,     4,     4,   419,     4,   503,     4,
       4,     4,     4,     4,     4,     4,     4,   520,     4,     4,
     214,     4,     4,     4,   216,   461,     4,   216,   216,   216,
     485,     4,     4,   395,   216,     4,     4,   214,     4,   214,
     214,     4,     4,   216,   216,     4,     4,     4,     4,   586,
       4,   214,   617,     4,     7,     7,     7,     7,   213,   213,
     213,     7,     7,     5,   213,   177,   178,   179,   180,   216,
     281,   213,   213,     5,     5,     5,   213,     5,   234,   236,
     213,   115,   116,   117,   118,   439,     5,     5,     5,     5,
       7,     7,     7,     7,     7,   213,   213,     5,     7,     5,
     243,    17,    18,   309,    20,    21,   312,   213,   213,   213,
       5,   213,   213,   243,   213,     7,   213,   243,   213,   213,
     213,   213,   213,   213,   213,   213,   213,   213,   213,   213,
     213,   213,   236,   213,   213,   213,    18,   175,   597,   176,
     281,   213,   213,   213,     5,   232,   255,   616,   301,    27,
      28,   321,   322,   323,   325,    39,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      60,    61,    62,    63,    64,   247,   335,   336,   337,   340,
     342,   344,   346,   347,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   361,   362,   364,   366,   368,   335,
       7,   331,   332,   333,     7,   412,   413,   414,     7,   453,
     454,   455,     7,   477,   478,   479,     7,   443,   444,   445,
     130,   131,   132,   133,   135,   372,   373,   374,   375,   376,
     377,   378,     7,   550,   551,     7,   512,   513,   514,     7,
     388,   389,   390,   143,   144,   145,   146,   147,   148,   402,
     403,   404,   405,   406,   407,   408,   409,   151,   152,   153,
     247,   381,   382,   383,   384,   385,   506,   508,   155,   156,
     247,   506,   508,   565,   566,   567,   569,   158,   159,   160,
     213,   506,   508,   573,   574,   575,   576,   578,   579,   585,
       7,   623,   624,   196,   197,   198,   199,   247,   647,   648,
     649,   650,   651,   652,   244,     7,   496,   497,   498,   138,
     527,   529,   547,   331,     8,     8,     8,   324,   326,     3,
       8,   338,   341,   343,   345,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   359,     4,   363,   365,   367,
     369,     3,     8,     8,   334,     6,     3,   415,     6,     3,
     456,     6,     3,   480,     6,     3,   446,     6,     3,     3,
       6,   552,     3,     6,   515,     6,     3,   391,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,     4,     4,
       4,     3,     8,   568,   570,     3,     8,     4,   577,     4,
     580,     3,     8,     8,   625,     3,     6,     4,     4,     4,
       4,     3,     8,   213,   245,   246,   499,     6,     3,   530,
       8,     6,     4,     4,   322,     4,     4,     4,     4,   214,
     216,   214,   216,   214,   214,   214,   214,   214,   214,     4,
     214,     4,     4,     4,     4,   336,   335,   333,   418,   414,
     459,   455,   483,   479,   247,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   271,   274,   275,   276,   277,
     278,   279,   282,   284,   286,   287,   288,   290,   292,   298,
     347,   410,   428,   430,   432,   434,   435,   436,   437,   447,
     448,   475,   506,   508,   521,   523,   525,   545,   445,   373,
     125,   126,   127,   247,   257,   258,   259,   298,   347,   449,
     475,   506,   508,   521,   523,   525,   553,   554,   555,   556,
     557,   559,   561,   551,   518,   514,   394,   390,   214,   214,
     214,   214,   214,   214,   403,   216,   214,   214,   382,     4,
       4,   566,   216,     4,   214,     4,   574,   187,   189,   190,
     247,   347,   506,   508,   626,   627,   628,   629,   631,   624,
     216,   216,   216,   216,   648,     6,     3,   502,   498,     4,
     213,   213,    40,    41,    42,   339,   213,   213,   213,    57,
      58,    59,   360,   213,   213,   213,   213,     8,     8,     8,
       8,     3,     8,   558,   560,     4,     8,     3,     8,     8,
     213,   213,   213,   232,   632,     4,   630,     3,     8,   213,
       8,   243,   448,     4,     4,   216,   555,     4,   214,     4,
     627,   213,   213,     5,   213,     7,   633,   634,   635,     3,
       6,   188,   191,   192,   193,   194,   636,   637,   638,   640,
     641,   642,   643,   634,   639,     4,     4,     4,   644,     3,
       8,     4,   216,   214,   214,     4,   637,   213,   213
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   217,   219,   218,   220,   218,   221,   218,   222,   218,
     223,   218,   224,   218,   225,   218,   226,   218,   227,   218,
     228,   218,   229,   218,   230,   218,   231,   218,   232,   232,
     232,   232,   232,   232,   232,   233,   235,   234,   236,   237,
     237,   238,   238,   238,   240,   239,   241,   241,   242,   242,
     242,   244,   243,   245,   245,   246,   246,   246,   247,   249,
     248,   251,   250,   250,   252,   254,   253,   255,   255,   255,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   269,   268,   270,
     272,   271,   273,   274,   275,   276,   277,   278,   280,   279,
     281,   281,   281,   281,   281,   283,   282,   285,   284,   286,
     287,   289,   288,   291,   290,   292,   293,   294,   295,   296,
     297,   298,   300,   299,   301,   301,   301,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   304,   303,   306,
     305,   308,   307,   309,   309,   311,   310,   312,   312,   313,
     314,   315,   316,   318,   317,   320,   319,   321,   321,   321,
     322,   322,   324,   323,   326,   325,   328,   327,   330,   329,
     331,   331,   332,   332,   332,   334,   333,   335,   335,   335,
     336,   336,   336,   336,   336,   336,   336,   336,   336,   336,
     336,   336,   336,   336,   336,   336,   336,   336,   336,   336,
     336,   336,   338,   337,   339,   339,   339,   341,   340,   343,
     342,   345,   344,   346,   348,   347,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   359,   358,   360,   360,   360,
     361,   363,   362,   365,   364,   367,   366,   369,   368,   371,
     370,   372,   372,   372,   373,   373,   373,   373,   373,   374,
     375,   376,   377,   378,   380,   379,   381,   381,   381,   382,
     382,   382,   382,   382,   382,   383,   384,   385,   387,   386,
     388,   388,   389,   389,   389,   391,   390,   393,   392,   394,
     394,   394,   394,   395,   395,   397,   396,   399,   398,   401,
     400,   402,   402,   402,   403,   403,   403,   403,   403,   403,
     404,   405,   406,   407,   408,   409,   411,   410,   412,   412,
     413,   413,   413,   415,   414,   417,   416,   418,   418,   418,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   419,   419,   419,   419,   419,   421,   420,   423,
     422,   425,   424,   427,   426,   429,   428,   431,   430,   433,
     432,   434,   435,   436,   438,   437,   439,   439,   439,   439,
     440,   442,   441,   443,   443,   444,   444,   444,   446,   445,
     447,   447,   447,   448,   448,   448,   448,   448,   448,   448,
     448,   448,   448,   448,   448,   448,   448,   448,   448,   448,
     448,   448,   448,   448,   448,   448,   448,   448,   448,   448,
     448,   448,   448,   448,   448,   448,   448,   448,   448,   448,
     448,   448,   448,   448,   448,   450,   449,   452,   451,   453,
     453,   454,   454,   454,   456,   455,   458,   457,   459,   459,
     460,   460,   460,   461,   461,   461,   461,   461,   461,   461,
     461,   461,   461,   462,   463,   464,   466,   465,   468,   467,
     470,   469,   471,   473,   472,   474,   476,   475,   477,   477,
     478,   478,   478,   480,   479,   482,   481,   483,   483,   484,
     484,   484,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   486,   488,   487,   489,   490,   491,   492,   493,
     495,   494,   496,   496,   497,   497,   497,   499,   498,   501,
     500,   502,   502,   502,   503,   503,   503,   503,   503,   503,
     503,   505,   504,   507,   506,   509,   508,   511,   510,   512,
     512,   513,   513,   513,   515,   514,   517,   516,   518,   518,
     519,   519,   519,   520,   520,   520,   520,   520,   520,   520,
     520,   520,   520,   520,   520,   520,   520,   520,   522,   521,
     524,   523,   526,   525,   528,   527,   530,   529,   532,   531,
     534,   533,   536,   535,   538,   537,   540,   539,   542,   541,
     544,   543,   546,   545,   547,   547,   549,   548,   550,   550,
     550,   552,   551,   553,   553,   554,   554,   554,   555,   555,
     555,   555,   555,   555,   555,   555,   555,   555,   555,   555,
     555,   555,   555,   555,   556,   558,   557,   560,   559,   561,
     562,   564,   563,   565,   565,   565,   566,   566,   566,   566,
     566,   568,   567,   570,   569,   572,   571,   573,   573,   573,
     574,   574,   574,   574,   574,   574,   575,   577,   576,   578,
     580,   579,   582,   581,   584,   583,   585,   585,   585,   586,
     586,   586,   586,   586,   586,   586,   586,   586,   586,   586,
     586,   586,   586,   586,   586,   586,   586,   587,   589,   588,
     590,   592,   591,   593,   594,   596,   595,   597,   597,   599,
     598,   601,   600,   602,   603,   605,   604,   607,   606,   609,
     608,   611,   610,   613,   612,   615,   614,   616,   616,   616,
     617,   617,   619,   618,   620,   622,   621,   623,   623,   623,
     625,   624,   626,   626,   626,   627,   627,   627,   627,   627,
     627,   627,   628,   630,   629,   632,   631,   633,   633,   633,
     635,   634,   636,   636,   636,   637,   637,   637,   637,   637,
     639,   638,   640,   641,   642,   644,   643,   646,   645,   647,
     647,   647,   648,   648,   648,   648,   648,   649,   650,   651,
     652
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
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     4,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     0,     6,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     1,     1,     0,     4,     1,     1,     3,
       3,     3,     3,     0,     6,     0,     6,     1,     3,     2,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     1,     0,     6,     0,     4,     0,
       1,     1,     3,     2,     0,     4,     0,     4,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     3,     3,
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
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     0,     6,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     2,
       1,     1,     0,     6,     3,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     3,     3,     3,
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
  "\"lease-checks\"", "\"extended-info-checks\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"authoritative\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"offer-lifetime\"",
  "\"lease-database\"", "\"hosts-database\"", "\"hosts-databases\"",
  "\"type\"", "\"memfile\"", "\"mysql\"", "\"postgresql\"", "\"user\"",
  "\"password\"", "\"host\"", "\"port\"", "\"persist\"",
  "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
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
  "\"lenient-option-parsing\"", "\"ignore-dhcp-server-identifier\"",
  "\"ignore-rai-link-selection\"", "\"exclude-first-last-24\"",
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
  "ip_reservations_unique", "reservations_lookup_first", "offer_lifetime",
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
  "ignore_dhcp_server_identifier", "ignore_rai_link_selection",
  "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   306,   306,   306,   307,   307,   308,   308,   309,   309,
     310,   310,   311,   311,   312,   312,   313,   313,   314,   314,
     315,   315,   316,   316,   317,   317,   318,   318,   326,   327,
     328,   329,   330,   331,   332,   335,   340,   340,   351,   354,
     355,   358,   363,   369,   374,   374,   381,   382,   385,   389,
     393,   399,   399,   406,   407,   410,   414,   418,   428,   437,
     437,   452,   452,   466,   469,   475,   475,   484,   485,   486,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   504,   505,   506,   507,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,   518,   519,   520,   521,   522,
     523,   524,   525,   526,   527,   528,   529,   530,   531,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   542,
     543,   544,   545,   546,   547,   548,   549,   550,   551,   552,
     553,   554,   555,   556,   557,   558,   561,   567,   573,   579,
     585,   591,   597,   603,   609,   615,   621,   627,   627,   636,
     642,   642,   651,   657,   663,   669,   675,   681,   687,   687,
     696,   699,   702,   705,   708,   714,   714,   723,   723,   732,
     738,   744,   744,   753,   753,   762,   768,   774,   780,   786,
     792,   798,   804,   804,   816,   817,   818,   823,   824,   825,
     826,   827,   828,   829,   830,   831,   832,   835,   835,   844,
     844,   855,   855,   863,   864,   867,   867,   875,   877,   881,
     887,   893,   899,   905,   905,   918,   918,   929,   930,   931,
     936,   937,   940,   940,   959,   959,   977,   977,   990,   990,
    1001,  1002,  1005,  1006,  1007,  1012,  1012,  1022,  1023,  1024,
    1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,  1038,
    1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,  1048,
    1049,  1050,  1053,  1053,  1061,  1062,  1063,  1066,  1066,  1075,
    1075,  1084,  1084,  1093,  1099,  1099,  1108,  1114,  1120,  1126,
    1132,  1138,  1144,  1150,  1156,  1162,  1162,  1170,  1171,  1172,
    1175,  1181,  1181,  1190,  1190,  1199,  1199,  1208,  1208,  1217,
    1217,  1228,  1229,  1230,  1235,  1236,  1237,  1238,  1239,  1242,
    1247,  1252,  1257,  1262,  1269,  1269,  1282,  1283,  1284,  1289,
    1290,  1291,  1292,  1293,  1294,  1297,  1303,  1309,  1315,  1315,
    1326,  1327,  1330,  1331,  1332,  1337,  1337,  1347,  1347,  1357,
    1358,  1359,  1362,  1365,  1366,  1369,  1369,  1378,  1378,  1387,
    1387,  1399,  1400,  1401,  1406,  1407,  1408,  1409,  1410,  1411,
    1414,  1420,  1426,  1432,  1438,  1444,  1453,  1453,  1467,  1468,
    1471,  1472,  1473,  1482,  1482,  1508,  1508,  1519,  1520,  1521,
    1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,  1536,
    1537,  1538,  1539,  1540,  1541,  1542,  1543,  1544,  1545,  1546,
    1547,  1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,  1556,
    1557,  1558,  1559,  1560,  1561,  1562,  1563,  1564,  1565,  1566,
    1567,  1568,  1569,  1570,  1571,  1572,  1573,  1576,  1576,  1585,
    1585,  1594,  1594,  1603,  1603,  1612,  1612,  1621,  1621,  1630,
    1630,  1641,  1647,  1653,  1659,  1659,  1667,  1668,  1669,  1670,
    1673,  1681,  1681,  1693,  1694,  1698,  1699,  1700,  1705,  1705,
    1713,  1714,  1715,  1720,  1721,  1722,  1723,  1724,  1725,  1726,
    1727,  1728,  1729,  1730,  1731,  1732,  1733,  1734,  1735,  1736,
    1737,  1738,  1739,  1740,  1741,  1742,  1743,  1744,  1745,  1746,
    1747,  1748,  1749,  1750,  1751,  1752,  1753,  1754,  1755,  1756,
    1757,  1758,  1759,  1760,  1761,  1768,  1768,  1782,  1782,  1791,
    1792,  1795,  1796,  1797,  1804,  1804,  1819,  1819,  1833,  1834,
    1837,  1838,  1839,  1844,  1845,  1846,  1847,  1848,  1849,  1850,
    1851,  1852,  1853,  1856,  1858,  1864,  1866,  1866,  1875,  1875,
    1884,  1884,  1893,  1895,  1895,  1904,  1914,  1914,  1927,  1928,
    1933,  1934,  1935,  1942,  1942,  1954,  1954,  1966,  1967,  1972,
    1973,  1974,  1981,  1982,  1983,  1984,  1985,  1986,  1987,  1988,
    1989,  1990,  1993,  1995,  1995,  2004,  2006,  2008,  2014,  2020,
    2029,  2029,  2042,  2043,  2046,  2047,  2048,  2053,  2053,  2063,
    2063,  2073,  2074,  2075,  2080,  2081,  2082,  2083,  2084,  2085,
    2086,  2089,  2089,  2098,  2098,  2123,  2123,  2153,  2153,  2164,
    2165,  2168,  2169,  2170,  2175,  2175,  2184,  2184,  2193,  2194,
    2197,  2198,  2199,  2205,  2206,  2207,  2208,  2209,  2210,  2211,
    2212,  2213,  2214,  2215,  2216,  2217,  2218,  2219,  2222,  2222,
    2231,  2231,  2240,  2240,  2249,  2249,  2258,  2258,  2269,  2269,
    2278,  2278,  2287,  2287,  2296,  2296,  2305,  2305,  2314,  2314,
    2323,  2323,  2337,  2337,  2348,  2349,  2355,  2355,  2366,  2367,
    2368,  2373,  2373,  2383,  2384,  2387,  2388,  2389,  2394,  2395,
    2396,  2397,  2398,  2399,  2400,  2401,  2402,  2403,  2404,  2405,
    2406,  2407,  2408,  2409,  2412,  2414,  2414,  2423,  2423,  2432,
    2440,  2448,  2448,  2459,  2460,  2461,  2466,  2467,  2468,  2469,
    2470,  2473,  2473,  2482,  2482,  2494,  2494,  2507,  2508,  2509,
    2514,  2515,  2516,  2517,  2518,  2519,  2522,  2528,  2528,  2537,
    2543,  2543,  2553,  2553,  2566,  2566,  2576,  2577,  2578,  2583,
    2584,  2585,  2586,  2587,  2588,  2589,  2590,  2591,  2592,  2593,
    2594,  2595,  2596,  2597,  2598,  2599,  2600,  2603,  2609,  2609,
    2618,  2624,  2624,  2633,  2639,  2645,  2645,  2654,  2655,  2658,
    2658,  2668,  2668,  2678,  2685,  2692,  2692,  2701,  2701,  2711,
    2711,  2721,  2721,  2733,  2733,  2745,  2745,  2755,  2756,  2757,
    2763,  2764,  2767,  2767,  2778,  2786,  2786,  2799,  2800,  2801,
    2807,  2807,  2815,  2816,  2817,  2822,  2823,  2824,  2825,  2826,
    2827,  2828,  2831,  2837,  2837,  2846,  2846,  2857,  2858,  2859,
    2864,  2864,  2872,  2873,  2874,  2879,  2880,  2881,  2882,  2883,
    2886,  2886,  2895,  2901,  2907,  2913,  2913,  2922,  2922,  2933,
    2934,  2935,  2940,  2941,  2942,  2943,  2944,  2947,  2953,  2959,
    2965
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
#line 6333 "dhcp4_parser.cc"

#line 2971 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
