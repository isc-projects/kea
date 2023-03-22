// A Bison parser, made by GNU Bison 3.7.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
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
    YYUSE (yyoutput);
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
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_on_fail_mode: // on_fail_mode
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 296 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 296 "dhcp4_parser.yy"
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
#line 305 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 761 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 306 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 767 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 307 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 773 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 308 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 779 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 309 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 785 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 310 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 791 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 311 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 797 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 312 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 803 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 313 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 809 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 314 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 815 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 315 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 821 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 316 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 827 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 317 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 833 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 325 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 326 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 327 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 851 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 328 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 857 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 329 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 863 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 330 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 869 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 331 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 875 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 334 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 884 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 339 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 895 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 344 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 905 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 350 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 911 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 357 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 362 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 932 "dhcp4_parser.cc"
    break;

  case 43: // not_empty_map: not_empty_map ","
#line 368 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 940 "dhcp4_parser.cc"
    break;

  case 44: // $@15: %empty
#line 373 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 949 "dhcp4_parser.cc"
    break;

  case 45: // list_generic: "[" $@15 list_content "]"
#line 376 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 957 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: value
#line 384 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 966 "dhcp4_parser.cc"
    break;

  case 49: // not_empty_list: not_empty_list "," value
#line 388 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 975 "dhcp4_parser.cc"
    break;

  case 50: // not_empty_list: not_empty_list ","
#line 392 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 983 "dhcp4_parser.cc"
    break;

  case 51: // $@16: %empty
#line 398 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 991 "dhcp4_parser.cc"
    break;

  case 52: // list_strings: "[" $@16 list_strings_content "]"
#line 400 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 55: // not_empty_list_strings: "constant string"
#line 409 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1009 "dhcp4_parser.cc"
    break;

  case 56: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 413 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1018 "dhcp4_parser.cc"
    break;

  case 57: // not_empty_list_strings: not_empty_list_strings ","
#line 417 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // unknown_map_entry: "constant string" ":"
#line 427 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 59: // $@17: %empty
#line 436 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 60: // syntax_map: "{" $@17 global_object "}"
#line 441 "dhcp4_parser.yy"
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
#line 451 "dhcp4_parser.yy"
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
#line 460 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 64: // global_object_comma: global_object ","
#line 468 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 65: // $@19: %empty
#line 474 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 66: // sub_dhcp4: "{" $@19 global_params "}"
#line 478 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 69: // global_params: global_params ","
#line 485 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1121 "dhcp4_parser.cc"
    break;

  case 136: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 560 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 137: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 566 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1141 "dhcp4_parser.cc"
    break;

  case 138: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 572 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1151 "dhcp4_parser.cc"
    break;

  case 139: // renew_timer: "renew-timer" ":" "integer"
#line 578 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 140: // rebind_timer: "rebind-timer" ":" "integer"
#line 584 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 141: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 590 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1181 "dhcp4_parser.cc"
    break;

  case 142: // t1_percent: "t1-percent" ":" "floating point"
#line 596 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1191 "dhcp4_parser.cc"
    break;

  case 143: // t2_percent: "t2-percent" ":" "floating point"
#line 602 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1201 "dhcp4_parser.cc"
    break;

  case 144: // cache_threshold: "cache-threshold" ":" "floating point"
#line 608 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 145: // cache_max_age: "cache-max-age" ":" "integer"
#line 614 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 146: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 620 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1231 "dhcp4_parser.cc"
    break;

  case 147: // $@20: %empty
#line 626 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 148: // server_tag: "server-tag" $@20 ":" "constant string"
#line 629 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1250 "dhcp4_parser.cc"
    break;

  case 149: // parked_packet_limit: "parked-packet-limit" ":" "integer"
#line 635 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1260 "dhcp4_parser.cc"
    break;

  case 150: // $@21: %empty
#line 641 "dhcp4_parser.yy"
                     {
    ctx.unique("allocator", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1269 "dhcp4_parser.cc"
    break;

  case 151: // allocator: "allocator" $@21 ":" "constant string"
#line 644 "dhcp4_parser.yy"
               {
    ElementPtr al(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
}
#line 1279 "dhcp4_parser.cc"
    break;

  case 152: // echo_client_id: "echo-client-id" ":" "boolean"
#line 650 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1289 "dhcp4_parser.cc"
    break;

  case 153: // match_client_id: "match-client-id" ":" "boolean"
#line 656 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1299 "dhcp4_parser.cc"
    break;

  case 154: // authoritative: "authoritative" ":" "boolean"
#line 662 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1309 "dhcp4_parser.cc"
    break;

  case 155: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 668 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1319 "dhcp4_parser.cc"
    break;

  case 156: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 674 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 157: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 680 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1339 "dhcp4_parser.cc"
    break;

  case 158: // $@22: %empty
#line 686 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1348 "dhcp4_parser.cc"
    break;

  case 159: // ddns_replace_client_name: "ddns-replace-client-name" $@22 ":" ddns_replace_client_name_value
#line 689 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1357 "dhcp4_parser.cc"
    break;

  case 160: // ddns_replace_client_name_value: "when-present"
#line 695 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1365 "dhcp4_parser.cc"
    break;

  case 161: // ddns_replace_client_name_value: "never"
#line 698 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1373 "dhcp4_parser.cc"
    break;

  case 162: // ddns_replace_client_name_value: "always"
#line 701 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1381 "dhcp4_parser.cc"
    break;

  case 163: // ddns_replace_client_name_value: "when-not-present"
#line 704 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1389 "dhcp4_parser.cc"
    break;

  case 164: // ddns_replace_client_name_value: "boolean"
#line 707 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1398 "dhcp4_parser.cc"
    break;

  case 165: // $@23: %empty
#line 713 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1407 "dhcp4_parser.cc"
    break;

  case 166: // ddns_generated_prefix: "ddns-generated-prefix" $@23 ":" "constant string"
#line 716 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1417 "dhcp4_parser.cc"
    break;

  case 167: // $@24: %empty
#line 722 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1426 "dhcp4_parser.cc"
    break;

  case 168: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@24 ":" "constant string"
#line 725 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1436 "dhcp4_parser.cc"
    break;

  case 169: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 731 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 170: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 737 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 171: // $@25: %empty
#line 743 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "dhcp4_parser.cc"
    break;

  case 172: // hostname_char_set: "hostname-char-set" $@25 ":" "constant string"
#line 746 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 173: // $@26: %empty
#line 752 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1484 "dhcp4_parser.cc"
    break;

  case 174: // hostname_char_replacement: "hostname-char-replacement" $@26 ":" "constant string"
#line 755 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1494 "dhcp4_parser.cc"
    break;

  case 175: // store_extended_info: "store-extended-info" ":" "boolean"
#line 761 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1504 "dhcp4_parser.cc"
    break;

  case 176: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 767 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1514 "dhcp4_parser.cc"
    break;

  case 177: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 773 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1524 "dhcp4_parser.cc"
    break;

  case 178: // early_global_reservations_lookup: "early-global-reservations-lookup" ":" "boolean"
#line 779 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1534 "dhcp4_parser.cc"
    break;

  case 179: // ip_reservations_unique: "ip-reservations-unique" ":" "boolean"
#line 785 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 180: // reservations_lookup_first: "reservations-lookup-first" ":" "boolean"
#line 791 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1554 "dhcp4_parser.cc"
    break;

  case 181: // offer_lifetime: "offer-lifetime" ":" "integer"
#line 797 "dhcp4_parser.yy"
                                        {
    ctx.unique("offer-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr offer_lifetime(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("offer-lifetime", offer_lifetime);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 182: // $@27: %empty
#line 803 "dhcp4_parser.yy"
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
#line 809 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 186: // interfaces_config_params: interfaces_config_params ","
#line 817 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1594 "dhcp4_parser.cc"
    break;

  case 197: // $@28: %empty
#line 834 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1604 "dhcp4_parser.cc"
    break;

  case 198: // sub_interfaces4: "{" $@28 interfaces_config_params "}"
#line 838 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1613 "dhcp4_parser.cc"
    break;

  case 199: // $@29: %empty
#line 843 "dhcp4_parser.yy"
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
#line 849 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1634 "dhcp4_parser.cc"
    break;

  case 201: // $@30: %empty
#line 854 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1643 "dhcp4_parser.cc"
    break;

  case 202: // dhcp_socket_type: "dhcp-socket-type" $@30 ":" socket_type
#line 857 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1652 "dhcp4_parser.cc"
    break;

  case 203: // socket_type: "raw"
#line 862 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1658 "dhcp4_parser.cc"
    break;

  case 204: // socket_type: "udp"
#line 863 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1664 "dhcp4_parser.cc"
    break;

  case 205: // $@31: %empty
#line 866 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1673 "dhcp4_parser.cc"
    break;

  case 206: // outbound_interface: "outbound-interface" $@31 ":" outbound_interface_value
#line 869 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1682 "dhcp4_parser.cc"
    break;

  case 207: // outbound_interface_value: "same-as-inbound"
#line 874 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1690 "dhcp4_parser.cc"
    break;

  case 208: // outbound_interface_value: "use-routing"
#line 876 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1698 "dhcp4_parser.cc"
    break;

  case 209: // re_detect: "re-detect" ":" "boolean"
#line 880 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1708 "dhcp4_parser.cc"
    break;

  case 210: // service_sockets_require_all: "service-sockets-require-all" ":" "boolean"
#line 886 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 211: // service_sockets_retry_wait_time: "service-sockets-retry-wait-time" ":" "integer"
#line 892 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 212: // service_sockets_max_retries: "service-sockets-max-retries" ":" "integer"
#line 898 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 213: // $@32: %empty
#line 904 "dhcp4_parser.yy"
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
#line 910 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1761 "dhcp4_parser.cc"
    break;

  case 215: // $@33: %empty
#line 917 "dhcp4_parser.yy"
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
#line 923 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1782 "dhcp4_parser.cc"
    break;

  case 219: // sanity_checks_params: sanity_checks_params ","
#line 930 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1790 "dhcp4_parser.cc"
    break;

  case 222: // $@34: %empty
#line 939 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1799 "dhcp4_parser.cc"
    break;

  case 223: // lease_checks: "lease-checks" $@34 ":" "constant string"
#line 942 "dhcp4_parser.yy"
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
#line 958 "dhcp4_parser.yy"
                                           {
    ctx.unique("extended-info-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1828 "dhcp4_parser.cc"
    break;

  case 225: // extended_info_checks: "extended-info-checks" $@35 ":" "constant string"
#line 961 "dhcp4_parser.yy"
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
#line 976 "dhcp4_parser.yy"
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
#line 982 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1870 "dhcp4_parser.cc"
    break;

  case 228: // $@37: %empty
#line 989 "dhcp4_parser.yy"
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
#line 995 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1891 "dhcp4_parser.cc"
    break;

  case 234: // not_empty_database_list: not_empty_database_list ","
#line 1006 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1899 "dhcp4_parser.cc"
    break;

  case 235: // $@38: %empty
#line 1011 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1909 "dhcp4_parser.cc"
    break;

  case 236: // database: "{" $@38 database_map_params "}"
#line 1015 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1919 "dhcp4_parser.cc"
    break;

  case 239: // database_map_params: database_map_params ","
#line 1023 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1927 "dhcp4_parser.cc"
    break;

  case 262: // $@39: %empty
#line 1052 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1936 "dhcp4_parser.cc"
    break;

  case 263: // database_type: "type" $@39 ":" db_type
#line 1055 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1945 "dhcp4_parser.cc"
    break;

  case 264: // db_type: "memfile"
#line 1060 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1951 "dhcp4_parser.cc"
    break;

  case 265: // db_type: "mysql"
#line 1061 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1957 "dhcp4_parser.cc"
    break;

  case 266: // db_type: "postgresql"
#line 1062 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1963 "dhcp4_parser.cc"
    break;

  case 267: // $@40: %empty
#line 1065 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 268: // user: "user" $@40 ":" "constant string"
#line 1068 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1982 "dhcp4_parser.cc"
    break;

  case 269: // $@41: %empty
#line 1074 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 270: // password: "password" $@41 ":" "constant string"
#line 1077 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 271: // $@42: %empty
#line 1083 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 272: // host: "host" $@42 ":" "constant string"
#line 1086 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 2020 "dhcp4_parser.cc"
    break;

  case 273: // port: "port" ":" "integer"
#line 1092 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 2030 "dhcp4_parser.cc"
    break;

  case 274: // $@43: %empty
#line 1098 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2039 "dhcp4_parser.cc"
    break;

  case 275: // name: "name" $@43 ":" "constant string"
#line 1101 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 2049 "dhcp4_parser.cc"
    break;

  case 276: // persist: "persist" ":" "boolean"
#line 1107 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 277: // lfc_interval: "lfc-interval" ":" "integer"
#line 1113 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 278: // readonly: "readonly" ":" "boolean"
#line 1119 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 279: // connect_timeout: "connect-timeout" ":" "integer"
#line 1125 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 280: // read_timeout: "read-timeout" ":" "integer"
#line 1131 "dhcp4_parser.yy"
                                         {
    ctx.unique("read-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("read-timeout", n);
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 281: // write_timeout: "write-timeout" ":" "integer"
#line 1137 "dhcp4_parser.yy"
                                           {
    ctx.unique("write-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("write-timeout", n);
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 282: // tcp_user_timeout: "tcp-user-timeout" ":" "integer"
#line 1143 "dhcp4_parser.yy"
                                                 {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
}
#line 2119 "dhcp4_parser.cc"
    break;

  case 283: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1149 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2129 "dhcp4_parser.cc"
    break;

  case 284: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1155 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2139 "dhcp4_parser.cc"
    break;

  case 285: // $@44: %empty
#line 1161 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2148 "dhcp4_parser.cc"
    break;

  case 286: // on_fail: "on-fail" $@44 ":" on_fail_mode
#line 1164 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2157 "dhcp4_parser.cc"
    break;

  case 287: // on_fail_mode: "stop-retry-exit"
#line 1169 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2163 "dhcp4_parser.cc"
    break;

  case 288: // on_fail_mode: "serve-retry-exit"
#line 1170 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2169 "dhcp4_parser.cc"
    break;

  case 289: // on_fail_mode: "serve-retry-continue"
#line 1171 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2175 "dhcp4_parser.cc"
    break;

  case 290: // max_row_errors: "max-row-errors" ":" "integer"
#line 1174 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2185 "dhcp4_parser.cc"
    break;

  case 291: // $@45: %empty
#line 1180 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2194 "dhcp4_parser.cc"
    break;

  case 292: // trust_anchor: "trust-anchor" $@45 ":" "constant string"
#line 1183 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2204 "dhcp4_parser.cc"
    break;

  case 293: // $@46: %empty
#line 1189 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2213 "dhcp4_parser.cc"
    break;

  case 294: // cert_file: "cert-file" $@46 ":" "constant string"
#line 1192 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2223 "dhcp4_parser.cc"
    break;

  case 295: // $@47: %empty
#line 1198 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2232 "dhcp4_parser.cc"
    break;

  case 296: // key_file: "key-file" $@47 ":" "constant string"
#line 1201 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2242 "dhcp4_parser.cc"
    break;

  case 297: // $@48: %empty
#line 1207 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2251 "dhcp4_parser.cc"
    break;

  case 298: // cipher_list: "cipher-list" $@48 ":" "constant string"
#line 1210 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2261 "dhcp4_parser.cc"
    break;

  case 299: // $@49: %empty
#line 1216 "dhcp4_parser.yy"
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
#line 1222 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2282 "dhcp4_parser.cc"
    break;

  case 303: // host_reservation_identifiers_list: host_reservation_identifiers_list ","
#line 1229 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2290 "dhcp4_parser.cc"
    break;

  case 309: // duid_id: "duid"
#line 1241 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2299 "dhcp4_parser.cc"
    break;

  case 310: // hw_address_id: "hw-address"
#line 1246 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2308 "dhcp4_parser.cc"
    break;

  case 311: // circuit_id: "circuit-id"
#line 1251 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2317 "dhcp4_parser.cc"
    break;

  case 312: // client_id: "client-id"
#line 1256 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2326 "dhcp4_parser.cc"
    break;

  case 313: // flex_id: "flex-id"
#line 1261 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2335 "dhcp4_parser.cc"
    break;

  case 314: // $@50: %empty
#line 1268 "dhcp4_parser.yy"
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
#line 1274 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2358 "dhcp4_parser.cc"
    break;

  case 318: // multi_threading_params: multi_threading_params ","
#line 1283 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2366 "dhcp4_parser.cc"
    break;

  case 325: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1296 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2376 "dhcp4_parser.cc"
    break;

  case 326: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1302 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2386 "dhcp4_parser.cc"
    break;

  case 327: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1308 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2396 "dhcp4_parser.cc"
    break;

  case 328: // $@51: %empty
#line 1314 "dhcp4_parser.yy"
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
#line 1320 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2417 "dhcp4_parser.cc"
    break;

  case 334: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 1331 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2425 "dhcp4_parser.cc"
    break;

  case 335: // $@52: %empty
#line 1336 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2435 "dhcp4_parser.cc"
    break;

  case 336: // hooks_library: "{" $@52 hooks_params "}"
#line 1340 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 337: // $@53: %empty
#line 1346 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp4_parser.cc"
    break;

  case 338: // sub_hooks_library: "{" $@53 hooks_params "}"
#line 1350 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2465 "dhcp4_parser.cc"
    break;

  case 341: // hooks_params: hooks_params ","
#line 1358 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2473 "dhcp4_parser.cc"
    break;

  case 345: // $@54: %empty
#line 1368 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 346: // library: "library" $@54 ":" "constant string"
#line 1371 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 347: // $@55: %empty
#line 1377 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 348: // parameters: "parameters" $@55 ":" map_value
#line 1380 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2510 "dhcp4_parser.cc"
    break;

  case 349: // $@56: %empty
#line 1386 "dhcp4_parser.yy"
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
#line 1392 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2532 "dhcp4_parser.cc"
    break;

  case 353: // expired_leases_params: expired_leases_params ","
#line 1400 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2540 "dhcp4_parser.cc"
    break;

  case 360: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1413 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 361: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1419 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2560 "dhcp4_parser.cc"
    break;

  case 362: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1425 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2570 "dhcp4_parser.cc"
    break;

  case 363: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1431 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 364: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1437 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 365: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1443 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2600 "dhcp4_parser.cc"
    break;

  case 366: // $@57: %empty
#line 1452 "dhcp4_parser.yy"
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
#line 1458 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2621 "dhcp4_parser.cc"
    break;

  case 372: // not_empty_subnet4_list: not_empty_subnet4_list ","
#line 1472 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2629 "dhcp4_parser.cc"
    break;

  case 373: // $@58: %empty
#line 1481 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2639 "dhcp4_parser.cc"
    break;

  case 374: // subnet4: "{" $@58 subnet4_params "}"
#line 1485 "dhcp4_parser.yy"
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
#line 1507 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2675 "dhcp4_parser.cc"
    break;

  case 376: // sub_subnet4: "{" $@59 subnet4_params "}"
#line 1511 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2685 "dhcp4_parser.cc"
    break;

  case 379: // subnet4_params: subnet4_params ","
#line 1520 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2693 "dhcp4_parser.cc"
    break;

  case 427: // $@60: %empty
#line 1575 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 428: // subnet: "subnet" $@60 ":" "constant string"
#line 1578 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 429: // $@61: %empty
#line 1584 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 430: // subnet_4o6_interface: "4o6-interface" $@61 ":" "constant string"
#line 1587 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2731 "dhcp4_parser.cc"
    break;

  case 431: // $@62: %empty
#line 1593 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2740 "dhcp4_parser.cc"
    break;

  case 432: // subnet_4o6_interface_id: "4o6-interface-id" $@62 ":" "constant string"
#line 1596 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2750 "dhcp4_parser.cc"
    break;

  case 433: // $@63: %empty
#line 1602 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2759 "dhcp4_parser.cc"
    break;

  case 434: // subnet_4o6_subnet: "4o6-subnet" $@63 ":" "constant string"
#line 1605 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2769 "dhcp4_parser.cc"
    break;

  case 435: // $@64: %empty
#line 1611 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2778 "dhcp4_parser.cc"
    break;

  case 436: // interface: "interface" $@64 ":" "constant string"
#line 1614 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2788 "dhcp4_parser.cc"
    break;

  case 437: // $@65: %empty
#line 1620 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2797 "dhcp4_parser.cc"
    break;

  case 438: // client_class: "client-class" $@65 ":" "constant string"
#line 1623 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2807 "dhcp4_parser.cc"
    break;

  case 439: // $@66: %empty
#line 1629 "dhcp4_parser.yy"
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
#line 1635 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2828 "dhcp4_parser.cc"
    break;

  case 441: // reservations_global: "reservations-global" ":" "boolean"
#line 1640 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2838 "dhcp4_parser.cc"
    break;

  case 442: // reservations_in_subnet: "reservations-in-subnet" ":" "boolean"
#line 1646 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2848 "dhcp4_parser.cc"
    break;

  case 443: // reservations_out_of_pool: "reservations-out-of-pool" ":" "boolean"
#line 1652 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2858 "dhcp4_parser.cc"
    break;

  case 444: // $@67: %empty
#line 1658 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2867 "dhcp4_parser.cc"
    break;

  case 445: // reservation_mode: "reservation-mode" $@67 ":" hr_mode
#line 1661 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2876 "dhcp4_parser.cc"
    break;

  case 446: // hr_mode: "disabled"
#line 1666 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2882 "dhcp4_parser.cc"
    break;

  case 447: // hr_mode: "out-of-pool"
#line 1667 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2888 "dhcp4_parser.cc"
    break;

  case 448: // hr_mode: "global"
#line 1668 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2894 "dhcp4_parser.cc"
    break;

  case 449: // hr_mode: "all"
#line 1669 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2900 "dhcp4_parser.cc"
    break;

  case 450: // id: "id" ":" "integer"
#line 1672 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2910 "dhcp4_parser.cc"
    break;

  case 451: // $@68: %empty
#line 1680 "dhcp4_parser.yy"
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
#line 1686 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2931 "dhcp4_parser.cc"
    break;

  case 457: // shared_networks_list: shared_networks_list ","
#line 1699 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2939 "dhcp4_parser.cc"
    break;

  case 458: // $@69: %empty
#line 1704 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2949 "dhcp4_parser.cc"
    break;

  case 459: // shared_network: "{" $@69 shared_network_params "}"
#line 1708 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2957 "dhcp4_parser.cc"
    break;

  case 462: // shared_network_params: shared_network_params ","
#line 1714 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2965 "dhcp4_parser.cc"
    break;

  case 505: // $@70: %empty
#line 1767 "dhcp4_parser.yy"
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
#line 1773 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2986 "dhcp4_parser.cc"
    break;

  case 507: // $@71: %empty
#line 1781 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2995 "dhcp4_parser.cc"
    break;

  case 508: // sub_option_def_list: "{" $@71 option_def_list "}"
#line 1784 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 3003 "dhcp4_parser.cc"
    break;

  case 513: // not_empty_option_def_list: not_empty_option_def_list ","
#line 1796 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 3011 "dhcp4_parser.cc"
    break;

  case 514: // $@72: %empty
#line 1803 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3021 "dhcp4_parser.cc"
    break;

  case 515: // option_def_entry: "{" $@72 option_def_params "}"
#line 1807 "dhcp4_parser.yy"
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
#line 1818 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 517: // sub_option_def: "{" $@73 option_def_params "}"
#line 1822 "dhcp4_parser.yy"
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
#line 1838 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3063 "dhcp4_parser.cc"
    break;

  case 534: // code: "code" ":" "integer"
#line 1857 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 3073 "dhcp4_parser.cc"
    break;

  case 536: // $@74: %empty
#line 1865 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3082 "dhcp4_parser.cc"
    break;

  case 537: // option_def_type: "type" $@74 ":" "constant string"
#line 1868 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3092 "dhcp4_parser.cc"
    break;

  case 538: // $@75: %empty
#line 1874 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 539: // option_def_record_types: "record-types" $@75 ":" "constant string"
#line 1877 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3111 "dhcp4_parser.cc"
    break;

  case 540: // $@76: %empty
#line 1883 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3120 "dhcp4_parser.cc"
    break;

  case 541: // space: "space" $@76 ":" "constant string"
#line 1886 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3130 "dhcp4_parser.cc"
    break;

  case 543: // $@77: %empty
#line 1894 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3139 "dhcp4_parser.cc"
    break;

  case 544: // option_def_encapsulate: "encapsulate" $@77 ":" "constant string"
#line 1897 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3149 "dhcp4_parser.cc"
    break;

  case 545: // option_def_array: "array" ":" "boolean"
#line 1903 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3159 "dhcp4_parser.cc"
    break;

  case 546: // $@78: %empty
#line 1913 "dhcp4_parser.yy"
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
#line 1919 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3180 "dhcp4_parser.cc"
    break;

  case 552: // not_empty_option_data_list: not_empty_option_data_list ","
#line 1934 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3188 "dhcp4_parser.cc"
    break;

  case 553: // $@79: %empty
#line 1941 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3198 "dhcp4_parser.cc"
    break;

  case 554: // option_data_entry: "{" $@79 option_data_params "}"
#line 1945 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3207 "dhcp4_parser.cc"
    break;

  case 555: // $@80: %empty
#line 1953 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3217 "dhcp4_parser.cc"
    break;

  case 556: // sub_option_data: "{" $@80 option_data_params "}"
#line 1957 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3226 "dhcp4_parser.cc"
    break;

  case 561: // not_empty_option_data_params: not_empty_option_data_params ","
#line 1973 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3234 "dhcp4_parser.cc"
    break;

  case 573: // $@81: %empty
#line 1994 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3243 "dhcp4_parser.cc"
    break;

  case 574: // option_data_data: "data" $@81 ":" "constant string"
#line 1997 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3253 "dhcp4_parser.cc"
    break;

  case 577: // option_data_csv_format: "csv-format" ":" "boolean"
#line 2007 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr csv(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", csv);
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 578: // option_data_always_send: "always-send" ":" "boolean"
#line 2013 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 579: // option_data_never_send: "never-send" ":" "boolean"
#line 2019 "dhcp4_parser.yy"
                                                 {
    ctx.unique("never-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr cancel(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("never-send", cancel);
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 580: // $@82: %empty
#line 2028 "dhcp4_parser.yy"
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
#line 2034 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3304 "dhcp4_parser.cc"
    break;

  case 586: // not_empty_pools_list: not_empty_pools_list ","
#line 2047 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3312 "dhcp4_parser.cc"
    break;

  case 587: // $@83: %empty
#line 2052 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 588: // pool_list_entry: "{" $@83 pool_params "}"
#line 2056 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 589: // $@84: %empty
#line 2062 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 590: // sub_pool4: "{" $@84 pool_params "}"
#line 2066 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3352 "dhcp4_parser.cc"
    break;

  case 593: // pool_params: pool_params ","
#line 2074 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3360 "dhcp4_parser.cc"
    break;

  case 601: // $@85: %empty
#line 2088 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3369 "dhcp4_parser.cc"
    break;

  case 602: // pool_entry: "pool" $@85 ":" "constant string"
#line 2091 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3379 "dhcp4_parser.cc"
    break;

  case 603: // $@86: %empty
#line 2097 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3387 "dhcp4_parser.cc"
    break;

  case 604: // user_context: "user-context" $@86 ":" map_value
#line 2099 "dhcp4_parser.yy"
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
#line 2122 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3422 "dhcp4_parser.cc"
    break;

  case 606: // comment: "comment" $@87 ":" "constant string"
#line 2124 "dhcp4_parser.yy"
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
#line 2152 "dhcp4_parser.yy"
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
#line 2158 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3472 "dhcp4_parser.cc"
    break;

  case 613: // not_empty_reservations_list: not_empty_reservations_list ","
#line 2169 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3480 "dhcp4_parser.cc"
    break;

  case 614: // $@89: %empty
#line 2174 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3490 "dhcp4_parser.cc"
    break;

  case 615: // reservation: "{" $@89 reservation_params "}"
#line 2178 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3499 "dhcp4_parser.cc"
    break;

  case 616: // $@90: %empty
#line 2183 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3509 "dhcp4_parser.cc"
    break;

  case 617: // sub_reservation: "{" $@90 reservation_params "}"
#line 2187 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3518 "dhcp4_parser.cc"
    break;

  case 622: // not_empty_reservation_params: not_empty_reservation_params ","
#line 2198 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3526 "dhcp4_parser.cc"
    break;

  case 638: // $@91: %empty
#line 2221 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 639: // next_server: "next-server" $@91 ":" "constant string"
#line 2224 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 640: // $@92: %empty
#line 2230 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 641: // server_hostname: "server-hostname" $@92 ":" "constant string"
#line 2233 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3564 "dhcp4_parser.cc"
    break;

  case 642: // $@93: %empty
#line 2239 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3573 "dhcp4_parser.cc"
    break;

  case 643: // boot_file_name: "boot-file-name" $@93 ":" "constant string"
#line 2242 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3583 "dhcp4_parser.cc"
    break;

  case 644: // $@94: %empty
#line 2248 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 645: // ip_address: "ip-address" $@94 ":" "constant string"
#line 2251 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3602 "dhcp4_parser.cc"
    break;

  case 646: // $@95: %empty
#line 2257 "dhcp4_parser.yy"
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
#line 2263 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3623 "dhcp4_parser.cc"
    break;

  case 648: // $@96: %empty
#line 2268 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3632 "dhcp4_parser.cc"
    break;

  case 649: // duid: "duid" $@96 ":" "constant string"
#line 2271 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3642 "dhcp4_parser.cc"
    break;

  case 650: // $@97: %empty
#line 2277 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3651 "dhcp4_parser.cc"
    break;

  case 651: // hw_address: "hw-address" $@97 ":" "constant string"
#line 2280 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3661 "dhcp4_parser.cc"
    break;

  case 652: // $@98: %empty
#line 2286 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3670 "dhcp4_parser.cc"
    break;

  case 653: // client_id_value: "client-id" $@98 ":" "constant string"
#line 2289 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3680 "dhcp4_parser.cc"
    break;

  case 654: // $@99: %empty
#line 2295 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3689 "dhcp4_parser.cc"
    break;

  case 655: // circuit_id_value: "circuit-id" $@99 ":" "constant string"
#line 2298 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3699 "dhcp4_parser.cc"
    break;

  case 656: // $@100: %empty
#line 2304 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3708 "dhcp4_parser.cc"
    break;

  case 657: // flex_id_value: "flex-id" $@100 ":" "constant string"
#line 2307 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3718 "dhcp4_parser.cc"
    break;

  case 658: // $@101: %empty
#line 2313 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3727 "dhcp4_parser.cc"
    break;

  case 659: // hostname: "hostname" $@101 ":" "constant string"
#line 2316 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3737 "dhcp4_parser.cc"
    break;

  case 660: // $@102: %empty
#line 2322 "dhcp4_parser.yy"
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
#line 2328 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3758 "dhcp4_parser.cc"
    break;

  case 662: // $@103: %empty
#line 2336 "dhcp4_parser.yy"
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
#line 2342 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3779 "dhcp4_parser.cc"
    break;

  case 666: // $@104: %empty
#line 2354 "dhcp4_parser.yy"
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
#line 2360 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3800 "dhcp4_parser.cc"
    break;

  case 670: // client_classes_list: client_classes_list ","
#line 2367 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3808 "dhcp4_parser.cc"
    break;

  case 671: // $@105: %empty
#line 2372 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3818 "dhcp4_parser.cc"
    break;

  case 672: // client_class_entry: "{" $@105 client_class_params "}"
#line 2376 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3828 "dhcp4_parser.cc"
    break;

  case 677: // not_empty_client_class_params: not_empty_client_class_params ","
#line 2388 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3836 "dhcp4_parser.cc"
    break;

  case 695: // $@106: %empty
#line 2413 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3845 "dhcp4_parser.cc"
    break;

  case 696: // client_class_test: "test" $@106 ":" "constant string"
#line 2416 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3855 "dhcp4_parser.cc"
    break;

  case 697: // $@107: %empty
#line 2422 "dhcp4_parser.yy"
                                          {
    ctx.unique("template-test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3864 "dhcp4_parser.cc"
    break;

  case 698: // client_class_template_test: "template-test" $@107 ":" "constant string"
#line 2425 "dhcp4_parser.yy"
               {
    ElementPtr template_test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
}
#line 3874 "dhcp4_parser.cc"
    break;

  case 699: // only_if_required: "only-if-required" ":" "boolean"
#line 2431 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3884 "dhcp4_parser.cc"
    break;

  case 700: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2439 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3894 "dhcp4_parser.cc"
    break;

  case 701: // $@108: %empty
#line 2447 "dhcp4_parser.yy"
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
#line 2453 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3915 "dhcp4_parser.cc"
    break;

  case 705: // control_socket_params: control_socket_params ","
#line 2460 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3923 "dhcp4_parser.cc"
    break;

  case 711: // $@109: %empty
#line 2472 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3932 "dhcp4_parser.cc"
    break;

  case 712: // control_socket_type: "socket-type" $@109 ":" "constant string"
#line 2475 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3942 "dhcp4_parser.cc"
    break;

  case 713: // $@110: %empty
#line 2481 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3951 "dhcp4_parser.cc"
    break;

  case 714: // control_socket_name: "socket-name" $@110 ":" "constant string"
#line 2484 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3961 "dhcp4_parser.cc"
    break;

  case 715: // $@111: %empty
#line 2493 "dhcp4_parser.yy"
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
#line 2499 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3984 "dhcp4_parser.cc"
    break;

  case 719: // queue_control_params: queue_control_params ","
#line 2508 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3992 "dhcp4_parser.cc"
    break;

  case 726: // enable_queue: "enable-queue" ":" "boolean"
#line 2521 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 4002 "dhcp4_parser.cc"
    break;

  case 727: // $@112: %empty
#line 2527 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4011 "dhcp4_parser.cc"
    break;

  case 728: // queue_type: "queue-type" $@112 ":" "constant string"
#line 2530 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 4021 "dhcp4_parser.cc"
    break;

  case 729: // capacity: "capacity" ":" "integer"
#line 2536 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 4031 "dhcp4_parser.cc"
    break;

  case 730: // $@113: %empty
#line 2542 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4040 "dhcp4_parser.cc"
    break;

  case 731: // arbitrary_map_entry: "constant string" $@113 ":" value
#line 2545 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4049 "dhcp4_parser.cc"
    break;

  case 732: // $@114: %empty
#line 2552 "dhcp4_parser.yy"
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
#line 2558 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4072 "dhcp4_parser.cc"
    break;

  case 734: // $@115: %empty
#line 2565 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4082 "dhcp4_parser.cc"
    break;

  case 735: // sub_dhcp_ddns: "{" $@115 dhcp_ddns_params "}"
#line 2569 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 4092 "dhcp4_parser.cc"
    break;

  case 738: // dhcp_ddns_params: dhcp_ddns_params ","
#line 2577 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 4100 "dhcp4_parser.cc"
    break;

  case 757: // enable_updates: "enable-updates" ":" "boolean"
#line 2602 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 4110 "dhcp4_parser.cc"
    break;

  case 758: // $@116: %empty
#line 2608 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4119 "dhcp4_parser.cc"
    break;

  case 759: // server_ip: "server-ip" $@116 ":" "constant string"
#line 2611 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4129 "dhcp4_parser.cc"
    break;

  case 760: // server_port: "server-port" ":" "integer"
#line 2617 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4139 "dhcp4_parser.cc"
    break;

  case 761: // $@117: %empty
#line 2623 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4148 "dhcp4_parser.cc"
    break;

  case 762: // sender_ip: "sender-ip" $@117 ":" "constant string"
#line 2626 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4158 "dhcp4_parser.cc"
    break;

  case 763: // sender_port: "sender-port" ":" "integer"
#line 2632 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4168 "dhcp4_parser.cc"
    break;

  case 764: // max_queue_size: "max-queue-size" ":" "integer"
#line 2638 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4178 "dhcp4_parser.cc"
    break;

  case 765: // $@118: %empty
#line 2644 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4187 "dhcp4_parser.cc"
    break;

  case 766: // ncr_protocol: "ncr-protocol" $@118 ":" ncr_protocol_value
#line 2647 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4196 "dhcp4_parser.cc"
    break;

  case 767: // ncr_protocol_value: "udp"
#line 2653 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4202 "dhcp4_parser.cc"
    break;

  case 768: // ncr_protocol_value: "tcp"
#line 2654 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4208 "dhcp4_parser.cc"
    break;

  case 769: // $@119: %empty
#line 2657 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4217 "dhcp4_parser.cc"
    break;

  case 770: // ncr_format: "ncr-format" $@119 ":" "JSON"
#line 2660 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4227 "dhcp4_parser.cc"
    break;

  case 771: // $@120: %empty
#line 2667 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4236 "dhcp4_parser.cc"
    break;

  case 772: // dep_qualifying_suffix: "qualifying-suffix" $@120 ":" "constant string"
#line 2670 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4246 "dhcp4_parser.cc"
    break;

  case 773: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2677 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4256 "dhcp4_parser.cc"
    break;

  case 774: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2684 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4266 "dhcp4_parser.cc"
    break;

  case 775: // $@121: %empty
#line 2691 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4275 "dhcp4_parser.cc"
    break;

  case 776: // dep_replace_client_name: "replace-client-name" $@121 ":" ddns_replace_client_name_value
#line 2694 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4284 "dhcp4_parser.cc"
    break;

  case 777: // $@122: %empty
#line 2700 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4293 "dhcp4_parser.cc"
    break;

  case 778: // dep_generated_prefix: "generated-prefix" $@122 ":" "constant string"
#line 2703 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4303 "dhcp4_parser.cc"
    break;

  case 779: // $@123: %empty
#line 2710 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4312 "dhcp4_parser.cc"
    break;

  case 780: // dep_hostname_char_set: "hostname-char-set" $@123 ":" "constant string"
#line 2713 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4322 "dhcp4_parser.cc"
    break;

  case 781: // $@124: %empty
#line 2720 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4331 "dhcp4_parser.cc"
    break;

  case 782: // dep_hostname_char_replacement: "hostname-char-replacement" $@124 ":" "constant string"
#line 2723 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4341 "dhcp4_parser.cc"
    break;

  case 783: // $@125: %empty
#line 2732 "dhcp4_parser.yy"
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
#line 2738 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4363 "dhcp4_parser.cc"
    break;

  case 785: // $@126: %empty
#line 2744 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4373 "dhcp4_parser.cc"
    break;

  case 786: // sub_config_control: "{" $@126 config_control_params "}"
#line 2748 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4382 "dhcp4_parser.cc"
    break;

  case 789: // config_control_params: config_control_params ","
#line 2756 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4390 "dhcp4_parser.cc"
    break;

  case 792: // $@127: %empty
#line 2766 "dhcp4_parser.yy"
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
#line 2772 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4411 "dhcp4_parser.cc"
    break;

  case 794: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2777 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4421 "dhcp4_parser.cc"
    break;

  case 795: // $@128: %empty
#line 2785 "dhcp4_parser.yy"
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
#line 2791 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4442 "dhcp4_parser.cc"
    break;

  case 799: // loggers_entries: loggers_entries ","
#line 2800 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4450 "dhcp4_parser.cc"
    break;

  case 800: // $@129: %empty
#line 2806 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4460 "dhcp4_parser.cc"
    break;

  case 801: // logger_entry: "{" $@129 logger_params "}"
#line 2810 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4468 "dhcp4_parser.cc"
    break;

  case 804: // logger_params: logger_params ","
#line 2816 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4476 "dhcp4_parser.cc"
    break;

  case 812: // debuglevel: "debuglevel" ":" "integer"
#line 2830 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4486 "dhcp4_parser.cc"
    break;

  case 813: // $@130: %empty
#line 2836 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4495 "dhcp4_parser.cc"
    break;

  case 814: // severity: "severity" $@130 ":" "constant string"
#line 2839 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4505 "dhcp4_parser.cc"
    break;

  case 815: // $@131: %empty
#line 2845 "dhcp4_parser.yy"
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
#line 2851 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4526 "dhcp4_parser.cc"
    break;

  case 819: // output_options_list_content: output_options_list_content ","
#line 2858 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4534 "dhcp4_parser.cc"
    break;

  case 820: // $@132: %empty
#line 2863 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4544 "dhcp4_parser.cc"
    break;

  case 821: // output_entry: "{" $@132 output_params_list "}"
#line 2867 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4552 "dhcp4_parser.cc"
    break;

  case 824: // output_params_list: output_params_list ","
#line 2873 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4560 "dhcp4_parser.cc"
    break;

  case 830: // $@133: %empty
#line 2885 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4569 "dhcp4_parser.cc"
    break;

  case 831: // output: "output" $@133 ":" "constant string"
#line 2888 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4579 "dhcp4_parser.cc"
    break;

  case 832: // flush: "flush" ":" "boolean"
#line 2894 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4589 "dhcp4_parser.cc"
    break;

  case 833: // maxsize: "maxsize" ":" "integer"
#line 2900 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4599 "dhcp4_parser.cc"
    break;

  case 834: // maxver: "maxver" ":" "integer"
#line 2906 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4609 "dhcp4_parser.cc"
    break;

  case 835: // $@134: %empty
#line 2912 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4618 "dhcp4_parser.cc"
    break;

  case 836: // pattern: "pattern" $@134 ":" "constant string"
#line 2915 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4628 "dhcp4_parser.cc"
    break;

  case 837: // $@135: %empty
#line 2921 "dhcp4_parser.yy"
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
#line 2927 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4649 "dhcp4_parser.cc"
    break;

  case 841: // compatibility_params: compatibility_params ","
#line 2934 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4657 "dhcp4_parser.cc"
    break;

  case 846: // lenient_option_parsing: "lenient-option-parsing" ":" "boolean"
#line 2945 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4667 "dhcp4_parser.cc"
    break;

  case 847: // ignore-rai-link-selection: "ignore-rai-link-selection" ":" "boolean"
#line 2951 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ignore-rai-link-selection", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ignore-rai-link-selection", b);
}
#line 4677 "dhcp4_parser.cc"
    break;

  case 848: // exclude_first_last_24: "exclude-first-last-24" ":" "boolean"
#line 2957 "dhcp4_parser.yy"
                                                           {
    ctx.unique("exclude-first-last-24", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("exclude-first-last-24", b);
}
#line 4687 "dhcp4_parser.cc"
    break;


#line 4691 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -997;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     427,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,    34,    42,    43,    68,    79,    81,
      85,    87,   101,   119,   122,   156,   175,   176,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,    42,  -164,   112,   123,   149,   258,
     -25,   288,   -19,   173,   201,  -108,   626,    88,  -997,   134,
     163,    54,   178,   211,  -997,    28,  -997,  -997,  -997,  -997,
     213,   221,   234,  -997,  -997,  -997,   243,  -997,  -997,  -997,
     244,   246,   247,   257,   264,   274,   281,   298,   299,   315,
     329,  -997,   330,   332,   342,   346,   348,  -997,  -997,  -997,
     349,   356,   358,  -997,  -997,  -997,   360,  -997,  -997,  -997,
    -997,  -997,   370,   376,   379,  -997,  -997,  -997,  -997,  -997,
     380,  -997,  -997,  -997,  -997,  -997,  -997,   389,   391,   426,
    -997,  -997,   431,  -997,    61,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   440,   441,   460,   470,  -997,    71,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   471,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   104,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   111,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,   228,   403,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,   252,  -997,  -997,   477,  -997,
    -997,  -997,   478,  -997,  -997,   365,   405,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     480,   482,   485,  -997,  -997,  -997,  -997,   384,   435,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,   115,  -997,  -997,  -997,   486,  -997,  -997,   489,
    -997,   492,   494,  -997,  -997,   495,   498,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   133,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,   500,   159,  -997,  -997,  -997,  -997,    42,    42,
    -997,  -150,   504,  -997,  -997,   505,   507,   509,  -138,   238,
     248,   511,   513,   515,   307,   524,   526,   527,   321,   324,
     325,   326,   328,   335,   322,   338,   339,   343,   344,   556,
     352,   354,   353,   357,   361,   557,   560,   567,   364,   367,
     368,   571,   582,   583,   377,   585,   589,   590,   593,   597,
     387,   424,   425,   614,   615,   616,   637,   638,   432,   639,
     640,   642,   644,   647,   648,   438,   439,   442,   652,   654,
    -997,   123,  -997,   655,   657,   658,   450,   453,   437,   456,
     149,  -997,   659,   660,   662,   666,   667,   668,   461,   669,
     671,   678,   258,  -997,   679,   -25,  -997,   684,   685,   686,
     688,   689,   690,   691,   692,  -997,   288,  -997,   693,   694,
     487,   695,   697,   702,   493,  -997,   173,   703,   522,   523,
     528,  -997,   201,   705,   706,   -70,  -997,   529,   737,   738,
     532,   742,   534,   535,   745,   746,   537,   538,   750,   753,
     755,   757,   626,  -997,   758,   550,    88,  -997,  -997,  -997,
     760,   761,   762,   764,   765,  -997,  -997,  -997,   563,   564,
     565,  -997,   771,   772,   775,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   569,  -997,  -997,  -997,
    -997,  -997,  -125,   572,   573,  -997,  -997,  -997,   778,   781,
     782,  -997,   591,   796,   795,   592,   430,  -997,  -997,  -997,
     800,   801,   804,   805,   806,  -997,   807,   808,   809,   810,
     599,   600,  -997,  -997,  -997,   813,   812,  -997,   815,    64,
      95,  -997,  -997,  -997,  -997,  -997,   609,   610,   611,   819,
     613,   617,  -997,   815,   618,   824,  -997,   620,  -997,   815,
     621,   622,   623,   624,   625,   627,   628,  -997,   629,   630,
    -997,   631,   632,   633,  -997,  -997,   634,  -997,  -997,  -997,
    -997,   635,   795,  -997,  -997,   636,   641,  -997,   643,  -997,
    -997,    38,   650,  -997,  -997,  -125,   645,   649,   651,  -997,
     844,  -997,  -997,    42,   123,    88,   149,   142,  -997,  -997,
    -997,   561,   561,   843,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,   845,   847,   849,  -997,   852,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,    91,   853,   855,   857,
     256,    67,    75,   154,   626,  -997,  -997,   858,  -101,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     859,  -997,  -997,  -997,  -997,    13,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   843,  -997,   231,   232,   263,  -997,
    -997,   278,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   863,
     864,   865,   866,   867,   868,   869,   870,   871,   872,  -997,
     873,  -997,  -997,  -997,  -997,  -997,   351,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   388,
    -997,   874,   848,  -997,  -997,   875,   876,  -997,  -997,   877,
     879,  -997,  -997,   878,   882,  -997,  -997,   880,   884,  -997,
    -997,  -997,  -997,  -997,  -997,    39,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,    57,  -997,  -997,   883,   885,  -997,  -997,
     886,   887,  -997,   889,   890,   891,   892,   893,   894,   402,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,   895,   896,   897,
    -997,   404,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,   406,  -997,  -997,  -997,   898,  -997,   899,
    -997,  -997,  -997,   421,  -997,  -997,  -997,  -997,  -997,   433,
    -997,   127,  -997,   900,   901,   902,  -997,   434,  -997,  -997,
    -997,  -997,   696,  -997,   903,   888,  -997,  -997,  -997,  -997,
     904,   905,  -997,  -997,  -997,   906,   909,   142,  -997,   910,
     911,   912,   913,   665,   704,   707,   708,   709,   711,   712,
     713,   714,   715,   914,   716,   917,   926,   927,   928,   561,
    -997,  -997,   561,  -997,   843,   258,  -997,   845,   173,  -997,
     847,   201,  -997,   849,   646,  -997,   852,    91,  -997,   323,
     853,  -997,   288,  -997,   855,  -108,  -997,   857,   720,   721,
     722,   723,   724,   726,   256,  -997,   725,   729,   730,    67,
    -997,   941,   942,    75,  -997,   739,   957,   751,   963,   154,
    -997,  -997,   337,   858,  -997,   767,   768,   773,  -101,  -997,
    -997,   962,   974,   -25,  -997,   859,   975,  -997,  -997,   774,
     787,  -997,   275,   793,   816,   823,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   369,  -997,   827,   838,
     881,   907,  -997,   448,  -997,   449,  -997,   979,  -997,  1012,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   451,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  1020,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  1023,  1082,  -997,  -997,  -997,  -997,  -997,
    -997,  1078,  -997,   459,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,   908,   915,  -997,  -997,
     916,  -997,    42,  -997,  -997,  1085,  -997,  -997,  -997,  -997,
    -997,   463,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,   918,   469,  -997,   815,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,   646,  -997,  1090,
    1091,   919,  -997,   323,  -997,  -997,  -997,  -997,  -997,  -997,
    1092,   920,  1093,   337,  -997,  -997,  -997,  -997,  -997,   923,
     924,  -997,  -997,  1094,  -997,   925,  -997,  -997,  -997,  1095,
    -997,  -997,   141,  -997,   -13,  1095,  -997,  -997,  1096,  1097,
    1099,  -997,   475,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    1100,   929,   930,   932,  1101,   -13,  -997,   934,  -997,  -997,
    -997,   935,  -997,  -997,  -997
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
     800,     0,   797,     0,     0,     0,   845,     0,   839,   842,
     843,   844,    53,   587,     0,   583,   584,   646,   664,   665,
       0,     0,    62,   784,   183,     0,     0,   219,   216,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   239,
     214,   227,     0,   229,   234,     0,   367,   372,   518,   506,
     513,   557,   547,   552,     0,   452,   457,   303,   300,   673,
     670,   667,   618,   608,   613,     0,   329,   334,     0,     0,
       0,     0,     0,     0,   353,   350,     0,     0,     0,   318,
     315,     0,     0,   705,   702,     0,     0,     0,     0,   719,
     716,   733,     0,   799,   796,     0,     0,     0,   841,   838,
      55,     0,    54,     0,   581,   586,     0,   663,   793,     0,
       0,   218,     0,     0,     0,     0,   273,   276,   277,   278,
     279,   280,   281,   282,   283,   284,     0,   290,     0,     0,
       0,     0,   238,     0,   233,     0,   371,     0,   512,     0,
     551,   504,   481,   482,   483,   466,   467,   486,   487,   488,
     489,   490,   502,   469,   470,   491,   492,   493,   494,   495,
     496,   497,   498,   499,   500,   501,   503,   463,   464,   465,
     479,   480,   476,   477,   478,   475,     0,   460,   468,   484,
     485,   471,   472,   473,   474,   456,   302,   695,   697,     0,
     689,   690,   691,   692,   693,   694,   682,   683,   687,   688,
     684,   685,   686,     0,   674,   675,   678,   679,   680,   681,
     669,     0,   612,     0,   333,   360,   361,   362,   363,   364,
     365,   352,   325,   326,   327,   317,     0,     0,   704,   726,
       0,   729,     0,   718,   815,     0,   813,   811,   805,   809,
     810,     0,   802,   807,   808,   806,   798,   846,   847,   848,
     840,    52,    57,     0,   585,     0,   223,   225,   264,   265,
     266,   263,   268,   270,   272,   287,   288,   289,   286,   292,
     294,   296,   298,   236,   374,   515,   554,   462,   459,     0,
       0,     0,   672,   677,   615,   336,   712,   714,   728,   731,
       0,     0,     0,   804,   801,    56,   588,   647,   461,     0,
       0,   699,   676,     0,   812,     0,   803,   696,   698,     0,
     814,   820,     0,   817,     0,   819,   816,   830,     0,     0,
       0,   835,     0,   822,   825,   826,   827,   828,   829,   818,
       0,     0,     0,     0,     0,   824,   821,     0,   832,   833,
     834,     0,   823,   831,   836
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,   -53,  -997,  -587,  -997,   215,
    -997,  -997,  -997,  -997,  -997,  -997,  -646,  -997,  -997,  -997,
     -67,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   392,   606,
      -8,    11,    29,   -54,   -34,   -12,   -10,     3,    37,    40,
    -997,  -997,  -997,  -997,    41,  -997,  -997,    44,    48,    51,
      52,    55,    56,  -997,   393,    58,  -997,    59,  -997,    62,
      63,    66,  -997,    69,  -997,    70,  -997,  -997,  -997,  -997,
    -997,    33,  -997,  -997,   394,   598,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,   132,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,   308,  -997,   107,  -997,  -708,   114,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
     -45,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,    97,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,    82,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,    89,  -997,  -997,  -997,    90,   562,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,    84,  -997,  -997,  -997,
    -997,  -997,  -997,  -996,  -997,  -997,  -997,   116,  -997,  -997,
    -997,   117,   602,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -988,  -997,   -65,  -997,    78,  -997,    73,    74,    76,
      77,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   109,  -997,
    -997,  -111,   -62,  -997,  -997,  -997,  -997,  -997,   121,  -997,
    -997,  -997,   124,  -997,   594,  -997,   -61,  -997,  -997,  -997,
    -997,  -997,   -58,  -997,  -997,  -997,  -997,  -997,    -4,  -997,
    -997,  -997,   125,  -997,  -997,  -997,   118,  -997,   596,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,    86,  -997,  -997,  -997,    92,   653,  -997,  -997,   -49,
    -997,   -30,  -997,   -57,  -997,  -997,  -997,   126,  -997,  -997,
    -997,   120,  -997,   661,     7,  -997,    18,  -997,    22,  -997,
     374,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -984,  -997,
    -997,  -997,  -997,  -997,   136,  -997,  -997,  -997,   -91,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   110,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,   105,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   407,   586,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,   444,
     581,  -997,  -997,  -997,  -997,  -997,  -997,   113,  -997,  -997,
     -93,  -997,  -997,  -997,  -997,  -997,  -997,  -113,  -997,  -997,
    -132,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,  -997,
    -997,   106,  -997,  -997,  -997
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   739,
      82,    83,    39,    64,    79,    80,   760,   962,  1061,  1062,
     835,    41,    66,    85,   432,    86,    43,    67,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   459,   168,   169,   475,   170,   171,   172,   173,
     174,   175,   176,   465,   730,   177,   466,   178,   467,   179,
     180,   181,   493,   182,   494,   183,   184,   185,   186,   187,
     188,   189,   190,   436,   229,   230,    45,    68,   231,   503,
     232,   504,   763,   233,   505,   766,   234,   235,   236,   237,
     191,   445,   192,   437,   811,   812,   813,   975,   814,   976,
     193,   446,   194,   447,   861,   862,   863,  1002,   836,   837,
     838,   979,  1221,   839,   980,   840,   981,   841,   982,   842,
     843,   539,   844,   845,   846,   847,   848,   849,   850,   851,
     852,   853,   993,  1228,   854,   855,   995,   856,   996,   857,
     997,   858,   998,   195,   483,   885,   886,   887,   888,   889,
     890,   891,   196,   489,   921,   922,   923,   924,   925,   197,
     486,   900,   901,   902,  1025,    59,    75,   382,   383,   384,
     553,   385,   554,   198,   487,   909,   910,   911,   912,   913,
     914,   915,   916,   199,   471,   865,   866,   867,  1005,    47,
      69,   276,   277,   278,   516,   279,   512,   280,   513,   281,
     514,   282,   517,   283,   520,   284,   519,   200,   201,   202,
     203,   479,   745,   289,   204,   476,   877,   878,   879,  1014,
    1136,  1137,   205,   472,    53,    72,   869,   870,   871,  1008,
      55,    73,   345,   346,   347,   348,   349,   350,   351,   538,
     352,   542,   353,   541,   354,   355,   543,   356,   206,   473,
     873,   874,   875,  1011,    57,    74,   367,   368,   369,   370,
     371,   547,   372,   373,   374,   375,   376,   291,   515,   964,
     965,   966,  1063,    49,    70,   304,   305,   306,   524,   207,
     477,   208,   478,   209,   485,   896,   897,   898,  1022,    51,
      71,   321,   322,   323,   210,   441,   211,   442,   212,   443,
     327,   534,   969,  1066,   328,   528,   329,   529,   330,   531,
     331,   530,   332,   533,   333,   532,   334,   527,   298,   521,
     970,   213,   484,   893,   894,  1019,  1163,  1164,  1165,  1166,
    1167,  1239,  1168,  1240,  1169,   214,   215,   490,   933,   934,
     935,  1041,   936,  1042,   216,   491,   943,   944,   945,   946,
    1046,   947,   948,  1048,   217,   492,    61,    76,   404,   405,
     406,   407,   559,   408,   409,   561,   410,   411,   412,   564,
     798,   413,   565,   414,   558,   415,   416,   417,   568,   418,
     569,   419,   570,   420,   571,   218,   435,    63,    77,   423,
     424,   425,   574,   426,   219,   498,   951,   952,  1052,  1201,
    1202,  1203,  1204,  1252,  1205,  1250,  1272,  1273,  1274,  1282,
    1283,  1284,  1290,  1285,  1286,  1287,  1288,  1294,   220,   499,
     957,   958,   959,   960,   961
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     153,   228,   250,   300,   317,   301,   343,   363,   381,   401,
     335,    78,   294,   365,   859,   254,   366,   773,  1128,   238,
     292,   307,   319,   777,   357,   377,  1129,   402,   344,   364,
    1144,   433,   379,   380,    28,   255,   434,   738,   239,   293,
     308,   320,  1017,   358,   378,  1018,   403,    29,    81,    30,
      40,    31,   725,   726,   727,   728,   796,   256,   429,   257,
    1020,   251,   580,  1021,   501,   290,   303,   318,   125,   502,
     379,   380,   258,   124,   510,    42,   295,   585,   324,   511,
     252,   761,   762,   299,   129,   130,    44,   296,    46,   325,
     729,   297,    48,   326,    50,   953,   954,   955,   253,   247,
     421,   422,   275,   248,   152,   738,   259,   522,    52,   260,
     261,   152,   523,   262,   525,   764,   765,   263,   555,   526,
     264,   265,    84,   556,   266,   267,    54,   268,   269,    56,
    1053,   270,   271,  1054,    87,   272,   572,    88,   273,   274,
     427,   573,   285,   286,  1275,   287,   288,  1276,   302,    89,
     316,   967,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   576,    58,   221,   222,   428,   577,   223,   809,
     810,   224,   225,   226,   227,  1277,   129,   130,  1278,  1279,
    1280,  1281,    60,    62,   129,   130,   430,   152,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   336,   797,   431,   124,   125,   438,   917,   918,
     919,   880,   881,   882,   883,   439,   884,   126,   127,   128,
     928,   929,   129,   130,   501,   576,   535,   131,   440,   972,
     973,  1128,   132,   133,   134,   135,   136,   444,   448,  1129,
     449,   450,   137,  1144,    32,    33,    34,    35,   129,   130,
     537,   451,   138,   129,   130,   139,   510,   337,   452,   338,
     339,   974,   140,   141,   340,   341,   342,   142,   453,   152,
     143,   977,   129,   130,   144,   454,   978,   152,    91,    92,
      93,    94,    95,    96,  1093,   337,   359,   338,   339,   360,
     361,   362,   455,   456,   145,   146,   147,   148,   149,   150,
     129,   130,   937,   938,   939,  1218,  1219,  1220,   151,   457,
      93,    94,    95,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   458,   460,   152,   461,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   462,   240,   241,   242,
     463,   125,   464,   468,   999,    93,    94,    95,    96,  1000,
     469,   152,   470,   127,   474,   243,   940,   129,   130,   244,
     245,   246,   131,   545,   480,   578,   579,   132,   133,   134,
     481,   125,   247,   482,   488,   152,   248,   137,   100,   101,
     102,   999,   551,   495,   249,   496,  1001,   129,   130,   903,
     904,   905,   906,   907,   908,  1034,   536,  1039,   546,  1043,
    1035,   309,  1040,   152,  1044,   124,   125,   337,   310,   311,
     312,   313,   314,   315,  1049,   316,  1225,  1226,  1227,  1050,
     497,   337,   129,   130,   153,   500,   572,  1058,   552,   145,
     146,  1051,  1059,   228,   506,   507,   129,   130,  1147,  1148,
    1149,   999,   522,   586,  1237,   250,  1233,  1234,   300,  1238,
     301,   238,   555,   587,   508,   294,  1253,  1245,   254,   317,
     152,  1254,   525,   292,   509,   518,   307,  1256,  1295,   343,
     239,   540,   544,  1296,   548,   363,   549,   319,   255,   550,
     557,   365,   293,   560,   366,   308,   562,   357,   563,   566,
     152,   344,   567,   377,   575,   401,   320,   364,   581,   582,
     256,   583,   257,   584,   251,   588,   358,   589,   290,   590,
     591,   303,   378,   402,  1194,   258,  1195,  1196,   592,   295,
     593,   594,   318,   252,   595,   152,   601,   596,   597,   598,
     296,   599,   403,   324,   297,   741,   742,   743,   744,   152,
     600,   253,   602,   603,   325,   275,   604,   605,   326,   259,
     606,   612,   260,   261,   613,   607,   262,   608,   609,  1257,
     263,   614,   610,   264,   265,   618,   611,   266,   267,   615,
     268,   269,   616,   617,   270,   271,   619,   620,   272,   622,
     621,   273,   274,   623,   624,   285,   286,   625,   287,   288,
     815,   626,   627,   302,   816,   817,   818,   819,   820,   821,
     822,   823,   824,   825,   826,   827,   828,   829,   630,   631,
     632,   830,   831,   832,   833,   834,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,   628,
     629,   633,   634,   636,   637,   635,   638,   153,   639,   228,
     653,   640,   641,   642,   643,   337,   645,   644,   646,   648,
     805,   649,   650,   656,   657,   651,   658,   238,   652,   654,
     659,   660,   661,   663,   662,   664,    91,    92,    93,    94,
      95,    96,   665,   667,   920,   930,   239,   401,   669,   670,
     671,   956,   672,   673,   674,   675,   676,   678,   679,   681,
     680,   682,   926,   931,   941,   402,   683,   686,   684,   691,
     692,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   927,   932,   942,   403,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   129,   130,   687,   688,   125,
     337,   695,   696,   689,   694,   697,   698,   699,   700,   701,
     702,   127,   703,   704,   705,   129,   130,   706,   245,   707,
     131,   708,   710,   711,   713,   132,   133,   134,   714,   715,
     247,   716,   717,   152,   248,   718,   719,   720,   721,   722,
     723,   724,   249,   733,   731,   732,   734,   735,   386,   387,
     388,   389,   390,   391,   392,   393,   394,   395,   396,   397,
     398,   737,    30,   736,   740,   746,   747,   399,   400,   748,
     749,   755,   756,   750,   751,   752,   753,   754,   757,   758,
     759,   767,   768,   769,   770,   771,   799,   145,   146,   772,
     774,   775,   776,   778,   779,   780,   781,   782,   152,   783,
     784,   785,   786,   787,   788,   789,   790,   791,   793,   804,
     860,  1004,   864,   794,   868,   795,   872,   801,   152,   876,
     892,   802,   895,   803,   899,   950,   963,   983,   984,   985,
     986,   987,   988,   989,   990,   991,   992,   994,  1076,  1007,
    1003,  1006,  1010,  1009,  1012,  1013,  1015,  1016,  1024,  1023,
    1027,  1065,  1026,  1028,  1029,  1030,  1031,  1032,  1033,  1036,
    1037,  1038,  1045,  1047,  1055,  1056,  1057,   792,  1060,  1064,
    1069,  1068,  1067,  1070,  1072,  1073,  1074,  1075,  1086,  1077,
    1078,  1088,  1080,  1079,  1081,  1082,  1083,  1084,  1085,  1087,
    1089,  1090,  1091,  1175,  1176,  1177,  1178,  1179,   250,  1180,
    1182,   343,  1183,  1184,   363,  1186,  1187,  1101,   294,  1130,
     365,   254,  1150,   366,  1189,   317,   292,  1156,   381,   357,
    1105,  1190,   377,   344,  1191,  1139,   364,  1192,  1211,  1127,
    1158,   255,   920,   319,  1155,   293,   930,  1212,   358,  1215,
    1106,   378,  1207,  1208,  1140,  1197,  1216,  1235,  1209,  1159,
     926,   956,   320,   256,   931,   257,   300,   251,   301,  1217,
     941,   290,  1107,  1199,  1108,  1222,  1102,  1198,   258,   927,
    1138,  1151,   295,   932,   307,  1157,   252,  1109,   318,   942,
    1236,  1141,  1200,   296,  1241,  1103,  1160,   297,  1223,   324,
    1152,  1242,  1142,   308,   253,  1224,  1143,  1161,   275,  1229,
     325,  1162,   259,  1104,   326,   260,   261,  1126,  1153,   262,
    1230,  1110,  1154,   263,  1111,  1112,   264,   265,  1113,   303,
     266,   267,  1114,   268,   269,  1115,  1116,   270,   271,  1117,
    1118,   272,  1119,  1120,   273,   274,  1121,  1122,   285,   286,
    1123,   287,   288,  1124,  1125,  1243,  1244,  1132,  1133,  1251,
    1134,  1135,  1131,  1231,  1259,  1260,  1263,  1265,   800,  1269,
    1291,  1292,  1271,  1293,  1297,  1301,   806,   647,   655,  1071,
     808,  1094,   971,  1092,  1146,  1173,  1174,   693,  1181,  1232,
    1246,  1185,  1095,  1096,   666,  1145,  1258,  1247,  1248,  1099,
    1255,  1098,  1097,  1264,  1261,  1267,  1268,  1270,  1100,  1249,
     685,   302,  1171,  1299,  1298,  1300,  1303,  1304,   690,   968,
    1172,  1214,  1262,  1188,  1193,  1213,  1170,   712,   709,   807,
    1266,   949,  1289,  1302,  1210,     0,  1206,     0,     0,     0,
    1101,     0,  1130,     0,     0,     0,  1150,     0,   668,     0,
       0,  1156,     0,  1105,     0,     0,  1197,     0,  1139,     0,
       0,     0,  1127,     0,  1158,     0,     0,   677,  1155,     0,
       0,     0,     0,  1106,  1199,     0,     0,  1140,  1198,     0,
       0,     0,     0,  1159,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1200,     0,  1107,     0,  1108,     0,  1102,
       0,     0,     0,  1138,     0,  1151,     0,     0,     0,  1157,
    1109,     0,     0,     0,  1141,     0,     0,     0,  1103,     0,
    1160,     0,     0,     0,  1152,  1142,     0,     0,     0,  1143,
       0,  1161,     0,     0,     0,  1162,  1104,     0,     0,     0,
    1126,     0,  1153,     0,  1110,     0,  1154,  1111,  1112,     0,
       0,  1113,     0,     0,     0,  1114,     0,     0,  1115,  1116,
       0,     0,  1117,  1118,     0,  1119,  1120,     0,     0,  1121,
    1122,     0,     0,  1123,     0,     0,  1124,  1125,     0,     0,
    1132,  1133,     0,  1134,  1135,  1131
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      72,    64,    69,    74,   722,    69,    74,   663,  1014,    68,
      69,    70,    71,   669,    73,    74,  1014,    76,    73,    74,
    1014,     3,   140,   141,     0,    69,     8,   624,    68,    69,
      70,    71,     3,    73,    74,     6,    76,     5,   212,     7,
       7,     9,   177,   178,   179,   180,    18,    69,     4,    69,
       3,    69,   212,     6,     3,    69,    70,    71,    93,     8,
     140,   141,    69,    92,     3,     7,    69,   215,    71,     8,
      69,    17,    18,   108,   109,   110,     7,    69,     7,    71,
     215,    69,     7,    71,     7,   196,   197,   198,    69,   124,
      12,    13,    69,   128,   212,   692,    69,     3,     7,    69,
      69,   212,     8,    69,     3,    20,    21,    69,     3,     8,
      69,    69,    10,     8,    69,    69,     7,    69,    69,     7,
       3,    69,    69,     6,    11,    69,     3,    14,    69,    69,
       6,     8,    69,    69,     3,    69,    69,     6,    70,    26,
     137,   138,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,     3,     7,    15,    16,     3,     8,    19,    27,
      28,    22,    23,    24,    25,   188,   109,   110,   191,   192,
     193,   194,     7,     7,   109,   110,     8,   212,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    39,   175,     3,    92,    93,     4,   151,   152,
     153,   130,   131,   132,   133,     4,   135,   104,   105,   106,
     155,   156,   109,   110,     3,     3,     8,   114,     4,     8,
       8,  1237,   119,   120,   121,   122,   123,     4,     4,  1237,
       4,     4,   129,  1237,   212,   213,   214,   215,   109,   110,
       8,     4,   139,   109,   110,   142,     3,    94,     4,    96,
      97,     8,   149,   150,   101,   102,   103,   154,     4,   212,
     157,     3,   109,   110,   161,     4,     8,   212,    30,    31,
      32,    33,    34,    35,  1002,    94,    95,    96,    97,    98,
      99,   100,     4,     4,   181,   182,   183,   184,   185,   186,
     109,   110,   158,   159,   160,    40,    41,    42,   195,     4,
      32,    33,    34,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     4,     4,   212,     4,    79,    80,    81,
      82,    83,    84,    85,    86,    87,     4,    89,    90,    91,
       4,    93,     4,     4,     3,    32,    33,    34,    35,     8,
       4,   212,     4,   105,     4,   107,   212,   109,   110,   111,
     112,   113,   114,     8,     4,   428,   429,   119,   120,   121,
       4,    93,   124,     4,     4,   212,   128,   129,    65,    66,
      67,     3,     8,     4,   136,     4,     8,   109,   110,   143,
     144,   145,   146,   147,   148,     3,     3,     3,     3,     3,
       8,   123,     8,   212,     8,    92,    93,    94,   130,   131,
     132,   133,   134,   135,     3,   137,    57,    58,    59,     8,
       4,    94,   109,   110,   501,     4,     3,     3,     3,   181,
     182,     8,     8,   510,     4,     4,   109,   110,   125,   126,
     127,     3,     3,   215,     3,   522,     8,     8,   525,     8,
     525,   510,     3,   215,     4,   522,     3,     8,   522,   536,
     212,     8,     3,   522,     4,     4,   525,     8,     3,   546,
     510,     4,     4,     8,     4,   552,     4,   536,   522,     4,
       4,   552,   522,     4,   552,   525,     4,   546,     4,     4,
     212,   546,     4,   552,     4,   572,   536,   552,     4,     4,
     522,     4,   522,     4,   522,     4,   546,     4,   522,     4,
     213,   525,   552,   572,   187,   522,   189,   190,     4,   522,
       4,     4,   536,   522,   213,   212,   214,   213,   213,   213,
     522,   213,   572,   536,   522,   115,   116,   117,   118,   212,
     215,   522,   214,   214,   536,   522,   213,   213,   536,   522,
       4,     4,   522,   522,     4,   213,   522,   213,   215,  1215,
     522,     4,   215,   522,   522,     4,   215,   522,   522,   215,
     522,   522,   215,   215,   522,   522,     4,     4,   522,     4,
     213,   522,   522,     4,     4,   522,   522,     4,   522,   522,
      39,     4,   215,   525,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,     4,     4,
       4,    60,    61,    62,    63,    64,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   215,
     215,     4,     4,     4,     4,   213,     4,   714,     4,   716,
     213,     4,     4,   215,   215,    94,     4,   215,     4,     4,
     713,     4,     4,     4,     4,   215,     4,   716,   215,   213,
       4,     4,     4,     4,   213,     4,    30,    31,    32,    33,
      34,    35,     4,     4,   751,   752,   716,   754,     4,     4,
       4,   758,     4,     4,     4,     4,     4,     4,     4,     4,
     213,     4,   751,   752,   753,   754,     4,     4,   215,     4,
       4,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,   751,   752,   753,   754,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,   109,   110,   215,   215,    93,
      94,     4,     4,   215,   215,   213,     4,   213,   213,     4,
       4,   105,   215,   215,     4,   109,   110,     4,   112,     4,
     114,     4,     4,   213,     4,   119,   120,   121,     7,     7,
     124,     7,     7,   212,   128,   212,   212,   212,     7,     7,
       5,   212,   136,     5,   212,   212,     5,     5,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,     5,     7,   212,   212,     5,     5,   181,   182,     5,
       5,   212,   212,     7,     7,     7,     7,     7,     5,     7,
       5,   212,   212,   212,     5,   212,   176,   181,   182,   212,
     212,     7,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,     5,
       7,     3,     7,   212,     7,   212,     7,   212,   212,     7,
       7,   212,     7,   212,     7,     7,     7,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   213,     3,
       6,     6,     3,     6,     6,     3,     6,     3,     3,     6,
       3,     3,     6,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   692,   212,     6,
       4,     6,     8,     4,     4,     4,     4,     4,     4,   215,
     213,     4,   213,   215,   213,   213,   213,   213,   213,   213,
       4,     4,     4,   213,   213,   213,   213,   213,  1005,   213,
     215,  1008,   213,   213,  1011,     4,     4,  1014,  1005,  1014,
    1011,  1005,  1019,  1011,   215,  1022,  1005,  1019,  1025,  1008,
    1014,     4,  1011,  1008,   213,  1014,  1011,     4,     6,  1014,
    1019,  1005,  1039,  1022,  1019,  1005,  1043,     3,  1008,     4,
    1014,  1011,   215,   215,  1014,  1052,   212,     8,   215,  1019,
    1039,  1058,  1022,  1005,  1043,  1005,  1063,  1005,  1063,   212,
    1049,  1005,  1014,  1052,  1014,   212,  1014,  1052,  1005,  1039,
    1014,  1019,  1005,  1043,  1063,  1019,  1005,  1014,  1022,  1049,
       8,  1014,  1052,  1005,     4,  1014,  1019,  1005,   212,  1022,
    1019,     8,  1014,  1063,  1005,   212,  1014,  1019,  1005,   212,
    1022,  1019,  1005,  1014,  1022,  1005,  1005,  1014,  1019,  1005,
     212,  1014,  1019,  1005,  1014,  1014,  1005,  1005,  1014,  1063,
    1005,  1005,  1014,  1005,  1005,  1014,  1014,  1005,  1005,  1014,
    1014,  1005,  1014,  1014,  1005,  1005,  1014,  1014,  1005,  1005,
    1014,  1005,  1005,  1014,  1014,     3,     8,  1014,  1014,     4,
    1014,  1014,  1014,   212,     4,     4,     4,     4,   705,     5,
       4,     4,     7,     4,     4,     4,   714,   501,   510,   977,
     716,  1004,   804,   999,  1017,  1025,  1027,   555,  1034,   212,
     212,  1039,  1005,  1007,   522,  1016,  1237,   212,   212,  1011,
     212,  1010,  1008,   213,   215,   212,   212,   212,  1013,  1192,
     546,  1063,  1022,   213,   215,   213,   212,   212,   552,   775,
    1024,  1065,  1243,  1043,  1049,  1063,  1020,   576,   572,   715,
    1253,   754,  1275,  1295,  1058,    -1,  1053,    -1,    -1,    -1,
    1237,    -1,  1237,    -1,    -1,    -1,  1243,    -1,   525,    -1,
      -1,  1243,    -1,  1237,    -1,    -1,  1253,    -1,  1237,    -1,
      -1,    -1,  1237,    -1,  1243,    -1,    -1,   536,  1243,    -1,
      -1,    -1,    -1,  1237,  1253,    -1,    -1,  1237,  1253,    -1,
      -1,    -1,    -1,  1243,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1253,    -1,  1237,    -1,  1237,    -1,  1237,
      -1,    -1,    -1,  1237,    -1,  1243,    -1,    -1,    -1,  1243,
    1237,    -1,    -1,    -1,  1237,    -1,    -1,    -1,  1237,    -1,
    1243,    -1,    -1,    -1,  1243,  1237,    -1,    -1,    -1,  1237,
      -1,  1243,    -1,    -1,    -1,  1243,  1237,    -1,    -1,    -1,
    1237,    -1,  1243,    -1,  1237,    -1,  1243,  1237,  1237,    -1,
      -1,  1237,    -1,    -1,    -1,  1237,    -1,    -1,  1237,  1237,
      -1,    -1,  1237,  1237,    -1,  1237,  1237,    -1,    -1,  1237,
    1237,    -1,    -1,  1237,    -1,    -1,  1237,  1237,    -1,    -1,
    1237,  1237,    -1,  1237,  1237,  1237
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,     0,     5,
       7,     9,   212,   213,   214,   215,   231,   232,   233,   238,
       7,   247,     7,   252,     7,   302,     7,   415,     7,   499,
       7,   515,     7,   450,     7,   456,     7,   480,     7,   391,
       7,   582,     7,   613,   239,   234,   248,   253,   303,   416,
     500,   516,   451,   457,   481,   392,   583,   614,   231,   240,
     241,   212,   236,   237,    10,   249,   251,    11,    14,    26,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    92,    93,   104,   105,   106,   109,
     110,   114,   119,   120,   121,   122,   123,   129,   139,   142,
     149,   150,   154,   157,   161,   181,   182,   183,   184,   185,
     186,   195,   212,   246,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   269,   270,
     272,   273,   274,   275,   276,   277,   278,   281,   283,   285,
     286,   287,   289,   291,   292,   293,   294,   295,   296,   297,
     298,   316,   318,   326,   328,   369,   378,   385,   399,   409,
     433,   434,   435,   436,   440,   448,   474,   505,   507,   509,
     520,   522,   524,   547,   561,   562,   570,   580,   611,   620,
     644,    15,    16,    19,    22,    23,    24,    25,   246,   300,
     301,   304,   306,   309,   312,   313,   314,   315,   505,   507,
      89,    90,    91,   107,   111,   112,   113,   124,   128,   136,
     246,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   270,   273,   274,   275,   276,   277,   278,   281,   283,
     285,   286,   287,   289,   291,   297,   417,   418,   419,   421,
     423,   425,   427,   429,   431,   433,   434,   435,   436,   439,
     474,   493,   505,   507,   509,   520,   522,   524,   544,   108,
     246,   429,   431,   474,   501,   502,   503,   505,   507,   123,
     130,   131,   132,   133,   134,   135,   137,   246,   474,   505,
     507,   517,   518,   519,   520,   522,   524,   526,   530,   532,
     534,   536,   538,   540,   542,   448,    39,    94,    96,    97,
     101,   102,   103,   246,   346,   458,   459,   460,   461,   462,
     463,   464,   466,   468,   470,   471,   473,   505,   507,    95,
      98,    99,   100,   246,   346,   462,   468,   482,   483,   484,
     485,   486,   488,   489,   490,   491,   492,   505,   507,   140,
     141,   246,   393,   394,   395,   397,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   181,
     182,   246,   505,   507,   584,   585,   586,   587,   589,   590,
     592,   593,   594,   597,   599,   601,   602,   603,   605,   607,
     609,    12,    13,   615,   616,   617,   619,     6,     3,     4,
       8,     3,   250,     3,     8,   612,   299,   319,     4,     4,
       4,   521,   523,   525,     4,   317,   327,   329,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   268,
       4,     4,     4,     4,     4,   279,   282,   284,     4,     4,
       4,   410,   449,   475,     4,   271,   441,   506,   508,   437,
       4,     4,     4,   370,   548,   510,   386,   400,     4,   379,
     563,   571,   581,   288,   290,     4,     4,     4,   621,   645,
       4,     3,     8,   305,   307,   310,     4,     4,     4,     4,
       3,     8,   422,   424,   426,   494,   420,   428,     4,   432,
     430,   545,     3,     8,   504,     3,     8,   543,   531,   533,
     537,   535,   541,   539,   527,     8,     3,     8,   465,   347,
       4,   469,   467,   472,     4,     8,     3,   487,     4,     4,
       4,     8,     3,   396,   398,     3,     8,     4,   600,   588,
       4,   591,     4,     4,   595,   598,     4,     4,   604,   606,
     608,   610,     3,     8,   618,     4,     3,     8,   231,   231,
     212,     4,     4,     4,     4,   215,   215,   215,     4,     4,
       4,   213,     4,     4,     4,   213,   213,   213,   213,   213,
     215,   214,   214,   214,   213,   213,     4,   213,   213,   215,
     215,   215,     4,     4,     4,   215,   215,   215,     4,     4,
       4,   213,     4,     4,     4,     4,     4,   215,   215,   215,
       4,     4,     4,     4,     4,   213,     4,     4,     4,     4,
       4,     4,   215,   215,   215,     4,     4,   255,     4,     4,
       4,   215,   215,   213,   213,   301,     4,     4,     4,     4,
       4,     4,   213,     4,     4,     4,   418,     4,   502,     4,
       4,     4,     4,     4,     4,     4,     4,   519,     4,     4,
     213,     4,     4,     4,   215,   460,     4,   215,   215,   215,
     484,     4,     4,   394,   215,     4,     4,   213,     4,   213,
     213,     4,     4,   215,   215,     4,     4,     4,     4,   585,
       4,   213,   616,     4,     7,     7,     7,     7,   212,   212,
     212,     7,     7,     5,   212,   177,   178,   179,   180,   215,
     280,   212,   212,     5,     5,     5,   212,     5,   233,   235,
     212,   115,   116,   117,   118,   438,     5,     5,     5,     5,
       7,     7,     7,     7,     7,   212,   212,     5,     7,     5,
     242,    17,    18,   308,    20,    21,   311,   212,   212,   212,
       5,   212,   212,   242,   212,     7,   212,   242,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   235,   212,   212,   212,    18,   175,   596,   176,
     280,   212,   212,   212,     5,   231,   254,   615,   300,    27,
      28,   320,   321,   322,   324,    39,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      60,    61,    62,    63,    64,   246,   334,   335,   336,   339,
     341,   343,   345,   346,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   360,   361,   363,   365,   367,   334,
       7,   330,   331,   332,     7,   411,   412,   413,     7,   452,
     453,   454,     7,   476,   477,   478,     7,   442,   443,   444,
     130,   131,   132,   133,   135,   371,   372,   373,   374,   375,
     376,   377,     7,   549,   550,     7,   511,   512,   513,     7,
     387,   388,   389,   143,   144,   145,   146,   147,   148,   401,
     402,   403,   404,   405,   406,   407,   408,   151,   152,   153,
     246,   380,   381,   382,   383,   384,   505,   507,   155,   156,
     246,   505,   507,   564,   565,   566,   568,   158,   159,   160,
     212,   505,   507,   572,   573,   574,   575,   577,   578,   584,
       7,   622,   623,   196,   197,   198,   246,   646,   647,   648,
     649,   650,   243,     7,   495,   496,   497,   138,   526,   528,
     546,   330,     8,     8,     8,   323,   325,     3,     8,   337,
     340,   342,   344,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   358,     4,   362,   364,   366,   368,     3,
       8,     8,   333,     6,     3,   414,     6,     3,   455,     6,
       3,   479,     6,     3,   445,     6,     3,     3,     6,   551,
       3,     6,   514,     6,     3,   390,     6,     3,     4,     4,
       4,     4,     4,     4,     3,     8,     4,     4,     4,     3,
       8,   567,   569,     3,     8,     4,   576,     4,   579,     3,
       8,     8,   624,     3,     6,     4,     4,     4,     3,     8,
     212,   244,   245,   498,     6,     3,   529,     8,     6,     4,
       4,   321,     4,     4,     4,     4,   213,   215,   213,   215,
     213,   213,   213,   213,   213,   213,     4,   213,     4,     4,
       4,     4,   335,   334,   332,   417,   413,   458,   454,   482,
     478,   246,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   270,   273,   274,   275,   276,   277,   278,   281,
     283,   285,   286,   287,   289,   291,   297,   346,   409,   427,
     429,   431,   433,   434,   435,   436,   446,   447,   474,   505,
     507,   520,   522,   524,   544,   444,   372,   125,   126,   127,
     246,   256,   257,   258,   297,   346,   448,   474,   505,   507,
     520,   522,   524,   552,   553,   554,   555,   556,   558,   560,
     550,   517,   513,   393,   389,   213,   213,   213,   213,   213,
     213,   402,   215,   213,   213,   381,     4,     4,   565,   215,
       4,   213,     4,   573,   187,   189,   190,   246,   346,   505,
     507,   625,   626,   627,   628,   630,   623,   215,   215,   215,
     647,     6,     3,   501,   497,     4,   212,   212,    40,    41,
      42,   338,   212,   212,   212,    57,    58,    59,   359,   212,
     212,   212,   212,     8,     8,     8,     8,     3,     8,   557,
     559,     4,     8,     3,     8,     8,   212,   212,   212,   231,
     631,     4,   629,     3,     8,   212,     8,   242,   447,     4,
       4,   215,   554,     4,   213,     4,   626,   212,   212,     5,
     212,     7,   632,   633,   634,     3,     6,   188,   191,   192,
     193,   194,   635,   636,   637,   639,   640,   641,   642,   633,
     638,     4,     4,     4,   643,     3,     8,     4,   215,   213,
     213,     4,   636,   212,   212
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   216,   218,   217,   219,   217,   220,   217,   221,   217,
     222,   217,   223,   217,   224,   217,   225,   217,   226,   217,
     227,   217,   228,   217,   229,   217,   230,   217,   231,   231,
     231,   231,   231,   231,   231,   232,   234,   233,   235,   236,
     236,   237,   237,   237,   239,   238,   240,   240,   241,   241,
     241,   243,   242,   244,   244,   245,   245,   245,   246,   248,
     247,   250,   249,   249,   251,   253,   252,   254,   254,   254,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   255,   255,   255,   255,
     255,   255,   255,   255,   255,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   268,   267,   269,
     271,   270,   272,   273,   274,   275,   276,   277,   279,   278,
     280,   280,   280,   280,   280,   282,   281,   284,   283,   285,
     286,   288,   287,   290,   289,   291,   292,   293,   294,   295,
     296,   297,   299,   298,   300,   300,   300,   301,   301,   301,
     301,   301,   301,   301,   301,   301,   301,   303,   302,   305,
     304,   307,   306,   308,   308,   310,   309,   311,   311,   312,
     313,   314,   315,   317,   316,   319,   318,   320,   320,   320,
     321,   321,   323,   322,   325,   324,   327,   326,   329,   328,
     330,   330,   331,   331,   331,   333,   332,   334,   334,   334,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   335,   335,   335,   335,   335,   335,   335,   335,
     335,   335,   337,   336,   338,   338,   338,   340,   339,   342,
     341,   344,   343,   345,   347,   346,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   358,   357,   359,   359,   359,
     360,   362,   361,   364,   363,   366,   365,   368,   367,   370,
     369,   371,   371,   371,   372,   372,   372,   372,   372,   373,
     374,   375,   376,   377,   379,   378,   380,   380,   380,   381,
     381,   381,   381,   381,   381,   382,   383,   384,   386,   385,
     387,   387,   388,   388,   388,   390,   389,   392,   391,   393,
     393,   393,   393,   394,   394,   396,   395,   398,   397,   400,
     399,   401,   401,   401,   402,   402,   402,   402,   402,   402,
     403,   404,   405,   406,   407,   408,   410,   409,   411,   411,
     412,   412,   412,   414,   413,   416,   415,   417,   417,   417,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   418,   418,   418,
     418,   418,   418,   418,   418,   418,   418,   420,   419,   422,
     421,   424,   423,   426,   425,   428,   427,   430,   429,   432,
     431,   433,   434,   435,   437,   436,   438,   438,   438,   438,
     439,   441,   440,   442,   442,   443,   443,   443,   445,   444,
     446,   446,   446,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   447,   447,   447,   447,   447,
     447,   447,   447,   447,   447,   449,   448,   451,   450,   452,
     452,   453,   453,   453,   455,   454,   457,   456,   458,   458,
     459,   459,   459,   460,   460,   460,   460,   460,   460,   460,
     460,   460,   460,   461,   462,   463,   465,   464,   467,   466,
     469,   468,   470,   472,   471,   473,   475,   474,   476,   476,
     477,   477,   477,   479,   478,   481,   480,   482,   482,   483,
     483,   483,   484,   484,   484,   484,   484,   484,   484,   484,
     484,   484,   485,   487,   486,   488,   489,   490,   491,   492,
     494,   493,   495,   495,   496,   496,   496,   498,   497,   500,
     499,   501,   501,   501,   502,   502,   502,   502,   502,   502,
     502,   504,   503,   506,   505,   508,   507,   510,   509,   511,
     511,   512,   512,   512,   514,   513,   516,   515,   517,   517,
     518,   518,   518,   519,   519,   519,   519,   519,   519,   519,
     519,   519,   519,   519,   519,   519,   519,   519,   521,   520,
     523,   522,   525,   524,   527,   526,   529,   528,   531,   530,
     533,   532,   535,   534,   537,   536,   539,   538,   541,   540,
     543,   542,   545,   544,   546,   546,   548,   547,   549,   549,
     549,   551,   550,   552,   552,   553,   553,   553,   554,   554,
     554,   554,   554,   554,   554,   554,   554,   554,   554,   554,
     554,   554,   554,   554,   555,   557,   556,   559,   558,   560,
     561,   563,   562,   564,   564,   564,   565,   565,   565,   565,
     565,   567,   566,   569,   568,   571,   570,   572,   572,   572,
     573,   573,   573,   573,   573,   573,   574,   576,   575,   577,
     579,   578,   581,   580,   583,   582,   584,   584,   584,   585,
     585,   585,   585,   585,   585,   585,   585,   585,   585,   585,
     585,   585,   585,   585,   585,   585,   585,   586,   588,   587,
     589,   591,   590,   592,   593,   595,   594,   596,   596,   598,
     597,   600,   599,   601,   602,   604,   603,   606,   605,   608,
     607,   610,   609,   612,   611,   614,   613,   615,   615,   615,
     616,   616,   618,   617,   619,   621,   620,   622,   622,   622,
     624,   623,   625,   625,   625,   626,   626,   626,   626,   626,
     626,   626,   627,   629,   628,   631,   630,   632,   632,   632,
     634,   633,   635,   635,   635,   636,   636,   636,   636,   636,
     638,   637,   639,   640,   641,   643,   642,   645,   644,   646,
     646,   646,   647,   647,   647,   647,   648,   649,   650
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
       3,     2,     1,     1,     1,     1,     3,     3,     3
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
  "ignore-rai-link-selection", "exclude_first_last_24", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   305,   305,   305,   306,   306,   307,   307,   308,   308,
     309,   309,   310,   310,   311,   311,   312,   312,   313,   313,
     314,   314,   315,   315,   316,   316,   317,   317,   325,   326,
     327,   328,   329,   330,   331,   334,   339,   339,   350,   353,
     354,   357,   362,   368,   373,   373,   380,   381,   384,   388,
     392,   398,   398,   405,   406,   409,   413,   417,   427,   436,
     436,   451,   451,   465,   468,   474,   474,   483,   484,   485,
     492,   493,   494,   495,   496,   497,   498,   499,   500,   501,
     502,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,   513,   514,   515,   516,   517,   518,   519,   520,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   560,   566,   572,   578,
     584,   590,   596,   602,   608,   614,   620,   626,   626,   635,
     641,   641,   650,   656,   662,   668,   674,   680,   686,   686,
     695,   698,   701,   704,   707,   713,   713,   722,   722,   731,
     737,   743,   743,   752,   752,   761,   767,   773,   779,   785,
     791,   797,   803,   803,   815,   816,   817,   822,   823,   824,
     825,   826,   827,   828,   829,   830,   831,   834,   834,   843,
     843,   854,   854,   862,   863,   866,   866,   874,   876,   880,
     886,   892,   898,   904,   904,   917,   917,   928,   929,   930,
     935,   936,   939,   939,   958,   958,   976,   976,   989,   989,
    1000,  1001,  1004,  1005,  1006,  1011,  1011,  1021,  1022,  1023,
    1028,  1029,  1030,  1031,  1032,  1033,  1034,  1035,  1036,  1037,
    1038,  1039,  1040,  1041,  1042,  1043,  1044,  1045,  1046,  1047,
    1048,  1049,  1052,  1052,  1060,  1061,  1062,  1065,  1065,  1074,
    1074,  1083,  1083,  1092,  1098,  1098,  1107,  1113,  1119,  1125,
    1131,  1137,  1143,  1149,  1155,  1161,  1161,  1169,  1170,  1171,
    1174,  1180,  1180,  1189,  1189,  1198,  1198,  1207,  1207,  1216,
    1216,  1227,  1228,  1229,  1234,  1235,  1236,  1237,  1238,  1241,
    1246,  1251,  1256,  1261,  1268,  1268,  1281,  1282,  1283,  1288,
    1289,  1290,  1291,  1292,  1293,  1296,  1302,  1308,  1314,  1314,
    1325,  1326,  1329,  1330,  1331,  1336,  1336,  1346,  1346,  1356,
    1357,  1358,  1361,  1364,  1365,  1368,  1368,  1377,  1377,  1386,
    1386,  1398,  1399,  1400,  1405,  1406,  1407,  1408,  1409,  1410,
    1413,  1419,  1425,  1431,  1437,  1443,  1452,  1452,  1466,  1467,
    1470,  1471,  1472,  1481,  1481,  1507,  1507,  1518,  1519,  1520,
    1526,  1527,  1528,  1529,  1530,  1531,  1532,  1533,  1534,  1535,
    1536,  1537,  1538,  1539,  1540,  1541,  1542,  1543,  1544,  1545,
    1546,  1547,  1548,  1549,  1550,  1551,  1552,  1553,  1554,  1555,
    1556,  1557,  1558,  1559,  1560,  1561,  1562,  1563,  1564,  1565,
    1566,  1567,  1568,  1569,  1570,  1571,  1572,  1575,  1575,  1584,
    1584,  1593,  1593,  1602,  1602,  1611,  1611,  1620,  1620,  1629,
    1629,  1640,  1646,  1652,  1658,  1658,  1666,  1667,  1668,  1669,
    1672,  1680,  1680,  1692,  1693,  1697,  1698,  1699,  1704,  1704,
    1712,  1713,  1714,  1719,  1720,  1721,  1722,  1723,  1724,  1725,
    1726,  1727,  1728,  1729,  1730,  1731,  1732,  1733,  1734,  1735,
    1736,  1737,  1738,  1739,  1740,  1741,  1742,  1743,  1744,  1745,
    1746,  1747,  1748,  1749,  1750,  1751,  1752,  1753,  1754,  1755,
    1756,  1757,  1758,  1759,  1760,  1767,  1767,  1781,  1781,  1790,
    1791,  1794,  1795,  1796,  1803,  1803,  1818,  1818,  1832,  1833,
    1836,  1837,  1838,  1843,  1844,  1845,  1846,  1847,  1848,  1849,
    1850,  1851,  1852,  1855,  1857,  1863,  1865,  1865,  1874,  1874,
    1883,  1883,  1892,  1894,  1894,  1903,  1913,  1913,  1926,  1927,
    1932,  1933,  1934,  1941,  1941,  1953,  1953,  1965,  1966,  1971,
    1972,  1973,  1980,  1981,  1982,  1983,  1984,  1985,  1986,  1987,
    1988,  1989,  1992,  1994,  1994,  2003,  2005,  2007,  2013,  2019,
    2028,  2028,  2041,  2042,  2045,  2046,  2047,  2052,  2052,  2062,
    2062,  2072,  2073,  2074,  2079,  2080,  2081,  2082,  2083,  2084,
    2085,  2088,  2088,  2097,  2097,  2122,  2122,  2152,  2152,  2163,
    2164,  2167,  2168,  2169,  2174,  2174,  2183,  2183,  2192,  2193,
    2196,  2197,  2198,  2204,  2205,  2206,  2207,  2208,  2209,  2210,
    2211,  2212,  2213,  2214,  2215,  2216,  2217,  2218,  2221,  2221,
    2230,  2230,  2239,  2239,  2248,  2248,  2257,  2257,  2268,  2268,
    2277,  2277,  2286,  2286,  2295,  2295,  2304,  2304,  2313,  2313,
    2322,  2322,  2336,  2336,  2347,  2348,  2354,  2354,  2365,  2366,
    2367,  2372,  2372,  2382,  2383,  2386,  2387,  2388,  2393,  2394,
    2395,  2396,  2397,  2398,  2399,  2400,  2401,  2402,  2403,  2404,
    2405,  2406,  2407,  2408,  2411,  2413,  2413,  2422,  2422,  2431,
    2439,  2447,  2447,  2458,  2459,  2460,  2465,  2466,  2467,  2468,
    2469,  2472,  2472,  2481,  2481,  2493,  2493,  2506,  2507,  2508,
    2513,  2514,  2515,  2516,  2517,  2518,  2521,  2527,  2527,  2536,
    2542,  2542,  2552,  2552,  2565,  2565,  2575,  2576,  2577,  2582,
    2583,  2584,  2585,  2586,  2587,  2588,  2589,  2590,  2591,  2592,
    2593,  2594,  2595,  2596,  2597,  2598,  2599,  2602,  2608,  2608,
    2617,  2623,  2623,  2632,  2638,  2644,  2644,  2653,  2654,  2657,
    2657,  2667,  2667,  2677,  2684,  2691,  2691,  2700,  2700,  2710,
    2710,  2720,  2720,  2732,  2732,  2744,  2744,  2754,  2755,  2756,
    2762,  2763,  2766,  2766,  2777,  2785,  2785,  2798,  2799,  2800,
    2806,  2806,  2814,  2815,  2816,  2821,  2822,  2823,  2824,  2825,
    2826,  2827,  2830,  2836,  2836,  2845,  2845,  2856,  2857,  2858,
    2863,  2863,  2871,  2872,  2873,  2878,  2879,  2880,  2881,  2882,
    2885,  2885,  2894,  2900,  2906,  2912,  2912,  2921,  2921,  2932,
    2933,  2934,  2939,  2940,  2941,  2942,  2945,  2951,  2957
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
#line 6316 "dhcp4_parser.cc"

#line 2963 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
