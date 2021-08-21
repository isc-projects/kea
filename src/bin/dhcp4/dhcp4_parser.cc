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
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 270 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 470 "dhcp4_parser.cc"
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
#line 279 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 280 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 281 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 762 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 282 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 283 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 774 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 284 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 285 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 786 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 286 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 792 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 287 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 798 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 288 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 804 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 289 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 810 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 290 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 816 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 291 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 822 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 299 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 300 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 301 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 302 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 303 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 304 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 305 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 308 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 873 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 313 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 318 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 894 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 324 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 900 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 331 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 909 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 335 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 919 "dhcp4_parser.cc"
    break;

  case 43: // $@15: %empty
#line 342 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 928 "dhcp4_parser.cc"
    break;

  case 44: // list_generic: "[" $@15 list_content "]"
#line 345 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 936 "dhcp4_parser.cc"
    break;

  case 47: // not_empty_list: value
#line 353 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 945 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: not_empty_list "," value
#line 357 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 954 "dhcp4_parser.cc"
    break;

  case 49: // $@16: %empty
#line 364 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 962 "dhcp4_parser.cc"
    break;

  case 50: // list_strings: "[" $@16 list_strings_content "]"
#line 366 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 971 "dhcp4_parser.cc"
    break;

  case 53: // not_empty_list_strings: "constant string"
#line 375 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 980 "dhcp4_parser.cc"
    break;

  case 54: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 379 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 989 "dhcp4_parser.cc"
    break;

  case 55: // unknown_map_entry: "constant string" ":"
#line 390 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 56: // $@17: %empty
#line 399 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1011 "dhcp4_parser.cc"
    break;

  case 57: // syntax_map: "{" $@17 global_objects "}"
#line 404 "dhcp4_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1024 "dhcp4_parser.cc"
    break;

  case 61: // $@18: %empty
#line 422 "dhcp4_parser.yy"
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
#line 1039 "dhcp4_parser.cc"
    break;

  case 62: // dhcp4_object: "Dhcp4" $@18 ":" "{" global_params "}"
#line 431 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1049 "dhcp4_parser.cc"
    break;

  case 63: // $@19: %empty
#line 439 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1059 "dhcp4_parser.cc"
    break;

  case 64: // sub_dhcp4: "{" $@19 global_params "}"
#line 443 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1068 "dhcp4_parser.cc"
    break;

  case 121: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 510 "dhcp4_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1077 "dhcp4_parser.cc"
    break;

  case 122: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 515 "dhcp4_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 123: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 520 "dhcp4_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1095 "dhcp4_parser.cc"
    break;

  case 124: // renew_timer: "renew-timer" ":" "integer"
#line 525 "dhcp4_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 125: // rebind_timer: "rebind-timer" ":" "integer"
#line 530 "dhcp4_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 126: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 535 "dhcp4_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1122 "dhcp4_parser.cc"
    break;

  case 127: // t1_percent: "t1-percent" ":" "floating point"
#line 540 "dhcp4_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 128: // t2_percent: "t2-percent" ":" "floating point"
#line 545 "dhcp4_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 129: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 550 "dhcp4_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1149 "dhcp4_parser.cc"
    break;

  case 130: // $@20: %empty
#line 555 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 131: // server_tag: "server-tag" $@20 ":" "constant string"
#line 557 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 132: // echo_client_id: "echo-client-id" ":" "boolean"
#line 563 "dhcp4_parser.yy"
                                             {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1176 "dhcp4_parser.cc"
    break;

  case 133: // match_client_id: "match-client-id" ":" "boolean"
#line 568 "dhcp4_parser.yy"
                                               {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1185 "dhcp4_parser.cc"
    break;

  case 134: // authoritative: "authoritative" ":" "boolean"
#line 573 "dhcp4_parser.yy"
                                           {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1194 "dhcp4_parser.cc"
    break;

  case 135: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 578 "dhcp4_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1203 "dhcp4_parser.cc"
    break;

  case 136: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 583 "dhcp4_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1212 "dhcp4_parser.cc"
    break;

  case 137: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 588 "dhcp4_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 138: // $@21: %empty
#line 593 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 139: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 595 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 140: // ddns_replace_client_name_value: "when-present"
#line 601 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1246 "dhcp4_parser.cc"
    break;

  case 141: // ddns_replace_client_name_value: "never"
#line 604 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1254 "dhcp4_parser.cc"
    break;

  case 142: // ddns_replace_client_name_value: "always"
#line 607 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1262 "dhcp4_parser.cc"
    break;

  case 143: // ddns_replace_client_name_value: "when-not-present"
#line 610 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1270 "dhcp4_parser.cc"
    break;

  case 144: // ddns_replace_client_name_value: "boolean"
#line 613 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1279 "dhcp4_parser.cc"
    break;

  case 145: // $@22: %empty
#line 619 "dhcp4_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1287 "dhcp4_parser.cc"
    break;

  case 146: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 621 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1297 "dhcp4_parser.cc"
    break;

  case 147: // $@23: %empty
#line 627 "dhcp4_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 148: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 629 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 149: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 635 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1325 "dhcp4_parser.cc"
    break;

  case 150: // ddns_use_conflict_resolution: "ddns-use-conflict-resolution" ":" "boolean"
#line 641 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1335 "dhcp4_parser.cc"
    break;

  case 151: // $@24: %empty
#line 647 "dhcp4_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1343 "dhcp4_parser.cc"
    break;

  case 152: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 649 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1353 "dhcp4_parser.cc"
    break;

  case 153: // $@25: %empty
#line 655 "dhcp4_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1361 "dhcp4_parser.cc"
    break;

  case 154: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 657 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1371 "dhcp4_parser.cc"
    break;

  case 155: // store_extended_info: "store-extended-info" ":" "boolean"
#line 663 "dhcp4_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1380 "dhcp4_parser.cc"
    break;

  case 156: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 668 "dhcp4_parser.yy"
                                                                             {
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1389 "dhcp4_parser.cc"
    break;

  case 157: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 673 "dhcp4_parser.yy"
                                                                         {
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1398 "dhcp4_parser.cc"
    break;

  case 158: // $@26: %empty
#line 678 "dhcp4_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1409 "dhcp4_parser.cc"
    break;

  case 159: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 683 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1419 "dhcp4_parser.cc"
    break;

  case 169: // $@27: %empty
#line 702 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1429 "dhcp4_parser.cc"
    break;

  case 170: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 706 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1438 "dhcp4_parser.cc"
    break;

  case 171: // $@28: %empty
#line 711 "dhcp4_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1449 "dhcp4_parser.cc"
    break;

  case 172: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 716 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1458 "dhcp4_parser.cc"
    break;

  case 173: // $@29: %empty
#line 721 "dhcp4_parser.yy"
                                   {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1466 "dhcp4_parser.cc"
    break;

  case 174: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 723 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 175: // socket_type: "raw"
#line 728 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1481 "dhcp4_parser.cc"
    break;

  case 176: // socket_type: "udp"
#line 729 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1487 "dhcp4_parser.cc"
    break;

  case 177: // $@30: %empty
#line 732 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1495 "dhcp4_parser.cc"
    break;

  case 178: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 734 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1504 "dhcp4_parser.cc"
    break;

  case 179: // outbound_interface_value: "same-as-inbound"
#line 739 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1512 "dhcp4_parser.cc"
    break;

  case 180: // outbound_interface_value: "use-routing"
#line 741 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1520 "dhcp4_parser.cc"
    break;

  case 181: // re_detect: "re-detect" ":" "boolean"
#line 745 "dhcp4_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1529 "dhcp4_parser.cc"
    break;

  case 182: // $@31: %empty
#line 751 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1540 "dhcp4_parser.cc"
    break;

  case 183: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 756 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1551 "dhcp4_parser.cc"
    break;

  case 184: // $@32: %empty
#line 763 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1562 "dhcp4_parser.cc"
    break;

  case 185: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 768 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1571 "dhcp4_parser.cc"
    break;

  case 189: // $@33: %empty
#line 778 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1579 "dhcp4_parser.cc"
    break;

  case 190: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 780 "dhcp4_parser.yy"
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
#line 1599 "dhcp4_parser.cc"
    break;

  case 191: // $@34: %empty
#line 796 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1610 "dhcp4_parser.cc"
    break;

  case 192: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 801 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1621 "dhcp4_parser.cc"
    break;

  case 193: // $@35: %empty
#line 808 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1632 "dhcp4_parser.cc"
    break;

  case 194: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 813 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1641 "dhcp4_parser.cc"
    break;

  case 199: // $@36: %empty
#line 826 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1651 "dhcp4_parser.cc"
    break;

  case 200: // database: "{" $@36 database_map_params "}"
#line 830 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1661 "dhcp4_parser.cc"
    break;

  case 224: // $@37: %empty
#line 863 "dhcp4_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1669 "dhcp4_parser.cc"
    break;

  case 225: // database_type: "type" $@37 ":" db_type
#line 865 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1678 "dhcp4_parser.cc"
    break;

  case 226: // db_type: "memfile"
#line 870 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1684 "dhcp4_parser.cc"
    break;

  case 227: // db_type: "mysql"
#line 871 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1690 "dhcp4_parser.cc"
    break;

  case 228: // db_type: "postgresql"
#line 872 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1696 "dhcp4_parser.cc"
    break;

  case 229: // db_type: "cql"
#line 873 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1702 "dhcp4_parser.cc"
    break;

  case 230: // $@38: %empty
#line 876 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1710 "dhcp4_parser.cc"
    break;

  case 231: // user: "user" $@38 ":" "constant string"
#line 878 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1720 "dhcp4_parser.cc"
    break;

  case 232: // $@39: %empty
#line 884 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1728 "dhcp4_parser.cc"
    break;

  case 233: // password: "password" $@39 ":" "constant string"
#line 886 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 234: // $@40: %empty
#line 892 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1746 "dhcp4_parser.cc"
    break;

  case 235: // host: "host" $@40 ":" "constant string"
#line 894 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1756 "dhcp4_parser.cc"
    break;

  case 236: // port: "port" ":" "integer"
#line 900 "dhcp4_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1765 "dhcp4_parser.cc"
    break;

  case 237: // $@41: %empty
#line 905 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1773 "dhcp4_parser.cc"
    break;

  case 238: // name: "name" $@41 ":" "constant string"
#line 907 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1783 "dhcp4_parser.cc"
    break;

  case 239: // persist: "persist" ":" "boolean"
#line 913 "dhcp4_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1792 "dhcp4_parser.cc"
    break;

  case 240: // lfc_interval: "lfc-interval" ":" "integer"
#line 918 "dhcp4_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1801 "dhcp4_parser.cc"
    break;

  case 241: // readonly: "readonly" ":" "boolean"
#line 923 "dhcp4_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1810 "dhcp4_parser.cc"
    break;

  case 242: // connect_timeout: "connect-timeout" ":" "integer"
#line 928 "dhcp4_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1819 "dhcp4_parser.cc"
    break;

  case 243: // request_timeout: "request-timeout" ":" "integer"
#line 933 "dhcp4_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1828 "dhcp4_parser.cc"
    break;

  case 244: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 938 "dhcp4_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1837 "dhcp4_parser.cc"
    break;

  case 245: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 943 "dhcp4_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1846 "dhcp4_parser.cc"
    break;

  case 246: // $@42: %empty
#line 948 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1854 "dhcp4_parser.cc"
    break;

  case 247: // contact_points: "contact-points" $@42 ":" "constant string"
#line 950 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1864 "dhcp4_parser.cc"
    break;

  case 248: // $@43: %empty
#line 956 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1872 "dhcp4_parser.cc"
    break;

  case 249: // keyspace: "keyspace" $@43 ":" "constant string"
#line 958 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1882 "dhcp4_parser.cc"
    break;

  case 250: // $@44: %empty
#line 964 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1890 "dhcp4_parser.cc"
    break;

  case 251: // consistency: "consistency" $@44 ":" "constant string"
#line 966 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1900 "dhcp4_parser.cc"
    break;

  case 252: // $@45: %empty
#line 972 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1908 "dhcp4_parser.cc"
    break;

  case 253: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 974 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1918 "dhcp4_parser.cc"
    break;

  case 254: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 980 "dhcp4_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1927 "dhcp4_parser.cc"
    break;

  case 255: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 985 "dhcp4_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1936 "dhcp4_parser.cc"
    break;

  case 256: // max_row_errors: "max-row-errors" ":" "integer"
#line 990 "dhcp4_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1945 "dhcp4_parser.cc"
    break;

  case 257: // $@46: %empty
#line 996 "dhcp4_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1956 "dhcp4_parser.cc"
    break;

  case 258: // host_reservation_identifiers: "host-reservation-identifiers" $@46 ":" "[" host_reservation_identifiers_list "]"
#line 1001 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1965 "dhcp4_parser.cc"
    break;

  case 266: // duid_id: "duid"
#line 1017 "dhcp4_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1974 "dhcp4_parser.cc"
    break;

  case 267: // hw_address_id: "hw-address"
#line 1022 "dhcp4_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1983 "dhcp4_parser.cc"
    break;

  case 268: // circuit_id: "circuit-id"
#line 1027 "dhcp4_parser.yy"
                        {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1992 "dhcp4_parser.cc"
    break;

  case 269: // client_id: "client-id"
#line 1032 "dhcp4_parser.yy"
                      {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 270: // flex_id: "flex-id"
#line 1037 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 271: // $@47: %empty
#line 1044 "dhcp4_parser.yy"
                                           {
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2021 "dhcp4_parser.cc"
    break;

  case 272: // dhcp_multi_threading: "multi-threading" $@47 ":" "{" multi_threading_params "}"
#line 1049 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2032 "dhcp4_parser.cc"
    break;

  case 281: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1068 "dhcp4_parser.yy"
                                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2041 "dhcp4_parser.cc"
    break;

  case 282: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1073 "dhcp4_parser.yy"
                                                 {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 283: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1078 "dhcp4_parser.yy"
                                                   {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 284: // $@48: %empty
#line 1083 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2070 "dhcp4_parser.cc"
    break;

  case 285: // hooks_libraries: "hooks-libraries" $@48 ":" "[" hooks_libraries_list "]"
#line 1088 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 290: // $@49: %empty
#line 1101 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 291: // hooks_library: "{" $@49 hooks_params "}"
#line 1105 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 292: // $@50: %empty
#line 1111 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 293: // sub_hooks_library: "{" $@50 hooks_params "}"
#line 1115 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2119 "dhcp4_parser.cc"
    break;

  case 299: // $@51: %empty
#line 1130 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2127 "dhcp4_parser.cc"
    break;

  case 300: // library: "library" $@51 ":" "constant string"
#line 1132 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2137 "dhcp4_parser.cc"
    break;

  case 301: // $@52: %empty
#line 1138 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2145 "dhcp4_parser.cc"
    break;

  case 302: // parameters: "parameters" $@52 ":" map_value
#line 1140 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2154 "dhcp4_parser.cc"
    break;

  case 303: // $@53: %empty
#line 1146 "dhcp4_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2165 "dhcp4_parser.cc"
    break;

  case 304: // expired_leases_processing: "expired-leases-processing" $@53 ":" "{" expired_leases_params "}"
#line 1151 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2175 "dhcp4_parser.cc"
    break;

  case 313: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1169 "dhcp4_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2184 "dhcp4_parser.cc"
    break;

  case 314: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1174 "dhcp4_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2193 "dhcp4_parser.cc"
    break;

  case 315: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1179 "dhcp4_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2202 "dhcp4_parser.cc"
    break;

  case 316: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1184 "dhcp4_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2211 "dhcp4_parser.cc"
    break;

  case 317: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1189 "dhcp4_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2220 "dhcp4_parser.cc"
    break;

  case 318: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1194 "dhcp4_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2229 "dhcp4_parser.cc"
    break;

  case 319: // $@54: %empty
#line 1202 "dhcp4_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2240 "dhcp4_parser.cc"
    break;

  case 320: // subnet4_list: "subnet4" $@54 ":" "[" subnet4_list_content "]"
#line 1207 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2249 "dhcp4_parser.cc"
    break;

  case 325: // $@55: %empty
#line 1227 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2259 "dhcp4_parser.cc"
    break;

  case 326: // subnet4: "{" $@55 subnet4_params "}"
#line 1231 "dhcp4_parser.yy"
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
#line 2285 "dhcp4_parser.cc"
    break;

  case 327: // $@56: %empty
#line 1253 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2295 "dhcp4_parser.cc"
    break;

  case 328: // sub_subnet4: "{" $@56 subnet4_params "}"
#line 1257 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2305 "dhcp4_parser.cc"
    break;

  case 371: // $@57: %empty
#line 1311 "dhcp4_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2313 "dhcp4_parser.cc"
    break;

  case 372: // subnet: "subnet" $@57 ":" "constant string"
#line 1313 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2323 "dhcp4_parser.cc"
    break;

  case 373: // $@58: %empty
#line 1319 "dhcp4_parser.yy"
                                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2331 "dhcp4_parser.cc"
    break;

  case 374: // subnet_4o6_interface: "4o6-interface" $@58 ":" "constant string"
#line 1321 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2341 "dhcp4_parser.cc"
    break;

  case 375: // $@59: %empty
#line 1327 "dhcp4_parser.yy"
                                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2349 "dhcp4_parser.cc"
    break;

  case 376: // subnet_4o6_interface_id: "4o6-interface-id" $@59 ":" "constant string"
#line 1329 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2359 "dhcp4_parser.cc"
    break;

  case 377: // $@60: %empty
#line 1335 "dhcp4_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2367 "dhcp4_parser.cc"
    break;

  case 378: // subnet_4o6_subnet: "4o6-subnet" $@60 ":" "constant string"
#line 1337 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2377 "dhcp4_parser.cc"
    break;

  case 379: // $@61: %empty
#line 1343 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2385 "dhcp4_parser.cc"
    break;

  case 380: // interface: "interface" $@61 ":" "constant string"
#line 1345 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2395 "dhcp4_parser.cc"
    break;

  case 381: // $@62: %empty
#line 1351 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2403 "dhcp4_parser.cc"
    break;

  case 382: // client_class: "client-class" $@62 ":" "constant string"
#line 1353 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2413 "dhcp4_parser.cc"
    break;

  case 383: // $@63: %empty
#line 1359 "dhcp4_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2424 "dhcp4_parser.cc"
    break;

  case 384: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1364 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2433 "dhcp4_parser.cc"
    break;

  case 385: // $@64: %empty
#line 1369 "dhcp4_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2441 "dhcp4_parser.cc"
    break;

  case 386: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1371 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2450 "dhcp4_parser.cc"
    break;

  case 387: // hr_mode: "disabled"
#line 1376 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2456 "dhcp4_parser.cc"
    break;

  case 388: // hr_mode: "out-of-pool"
#line 1377 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2462 "dhcp4_parser.cc"
    break;

  case 389: // hr_mode: "global"
#line 1378 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2468 "dhcp4_parser.cc"
    break;

  case 390: // hr_mode: "all"
#line 1379 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2474 "dhcp4_parser.cc"
    break;

  case 391: // id: "id" ":" "integer"
#line 1382 "dhcp4_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2483 "dhcp4_parser.cc"
    break;

  case 392: // $@65: %empty
#line 1389 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2494 "dhcp4_parser.cc"
    break;

  case 393: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1394 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2503 "dhcp4_parser.cc"
    break;

  case 398: // $@66: %empty
#line 1409 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2513 "dhcp4_parser.cc"
    break;

  case 399: // shared_network: "{" $@66 shared_network_params "}"
#line 1413 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2521 "dhcp4_parser.cc"
    break;

  case 437: // $@67: %empty
#line 1462 "dhcp4_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2532 "dhcp4_parser.cc"
    break;

  case 438: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1467 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2541 "dhcp4_parser.cc"
    break;

  case 439: // $@68: %empty
#line 1475 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 440: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1478 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2558 "dhcp4_parser.cc"
    break;

  case 445: // $@69: %empty
#line 1494 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2568 "dhcp4_parser.cc"
    break;

  case 446: // option_def_entry: "{" $@69 option_def_params "}"
#line 1498 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2580 "dhcp4_parser.cc"
    break;

  case 447: // $@70: %empty
#line 1509 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2590 "dhcp4_parser.cc"
    break;

  case 448: // sub_option_def: "{" $@70 option_def_params "}"
#line 1513 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2602 "dhcp4_parser.cc"
    break;

  case 464: // code: "code" ":" "integer"
#line 1545 "dhcp4_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2611 "dhcp4_parser.cc"
    break;

  case 466: // $@71: %empty
#line 1552 "dhcp4_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2619 "dhcp4_parser.cc"
    break;

  case 467: // option_def_type: "type" $@71 ":" "constant string"
#line 1554 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2629 "dhcp4_parser.cc"
    break;

  case 468: // $@72: %empty
#line 1560 "dhcp4_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2637 "dhcp4_parser.cc"
    break;

  case 469: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1562 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2647 "dhcp4_parser.cc"
    break;

  case 470: // $@73: %empty
#line 1568 "dhcp4_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2655 "dhcp4_parser.cc"
    break;

  case 471: // space: "space" $@73 ":" "constant string"
#line 1570 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2665 "dhcp4_parser.cc"
    break;

  case 473: // $@74: %empty
#line 1578 "dhcp4_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 474: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1580 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 475: // option_def_array: "array" ":" "boolean"
#line 1586 "dhcp4_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 476: // $@75: %empty
#line 1595 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2703 "dhcp4_parser.cc"
    break;

  case 477: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1600 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2712 "dhcp4_parser.cc"
    break;

  case 482: // $@76: %empty
#line 1619 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2722 "dhcp4_parser.cc"
    break;

  case 483: // option_data_entry: "{" $@76 option_data_params "}"
#line 1623 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2731 "dhcp4_parser.cc"
    break;

  case 484: // $@77: %empty
#line 1631 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2741 "dhcp4_parser.cc"
    break;

  case 485: // sub_option_data: "{" $@77 option_data_params "}"
#line 1635 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2750 "dhcp4_parser.cc"
    break;

  case 500: // $@78: %empty
#line 1668 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2758 "dhcp4_parser.cc"
    break;

  case 501: // option_data_data: "data" $@78 ":" "constant string"
#line 1670 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2768 "dhcp4_parser.cc"
    break;

  case 504: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1680 "dhcp4_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2777 "dhcp4_parser.cc"
    break;

  case 505: // option_data_always_send: "always-send" ":" "boolean"
#line 1685 "dhcp4_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2786 "dhcp4_parser.cc"
    break;

  case 506: // $@79: %empty
#line 1693 "dhcp4_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2797 "dhcp4_parser.cc"
    break;

  case 507: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1698 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2806 "dhcp4_parser.cc"
    break;

  case 512: // $@80: %empty
#line 1713 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2816 "dhcp4_parser.cc"
    break;

  case 513: // pool_list_entry: "{" $@80 pool_params "}"
#line 1717 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2826 "dhcp4_parser.cc"
    break;

  case 514: // $@81: %empty
#line 1723 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2836 "dhcp4_parser.cc"
    break;

  case 515: // sub_pool4: "{" $@81 pool_params "}"
#line 1727 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2846 "dhcp4_parser.cc"
    break;

  case 525: // $@82: %empty
#line 1746 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2854 "dhcp4_parser.cc"
    break;

  case 526: // pool_entry: "pool" $@82 ":" "constant string"
#line 1748 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2864 "dhcp4_parser.cc"
    break;

  case 527: // $@83: %empty
#line 1754 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2872 "dhcp4_parser.cc"
    break;

  case 528: // user_context: "user-context" $@83 ":" map_value
#line 1756 "dhcp4_parser.yy"
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
#line 2899 "dhcp4_parser.cc"
    break;

  case 529: // $@84: %empty
#line 1779 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2907 "dhcp4_parser.cc"
    break;

  case 530: // comment: "comment" $@84 ":" "constant string"
#line 1781 "dhcp4_parser.yy"
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
#line 2936 "dhcp4_parser.cc"
    break;

  case 531: // $@85: %empty
#line 1809 "dhcp4_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 532: // reservations: "reservations" $@85 ":" "[" reservations_list "]"
#line 1814 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2956 "dhcp4_parser.cc"
    break;

  case 537: // $@86: %empty
#line 1827 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2966 "dhcp4_parser.cc"
    break;

  case 538: // reservation: "{" $@86 reservation_params "}"
#line 1831 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2975 "dhcp4_parser.cc"
    break;

  case 539: // $@87: %empty
#line 1836 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2985 "dhcp4_parser.cc"
    break;

  case 540: // sub_reservation: "{" $@87 reservation_params "}"
#line 1840 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2994 "dhcp4_parser.cc"
    break;

  case 560: // $@88: %empty
#line 1871 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3002 "dhcp4_parser.cc"
    break;

  case 561: // next_server: "next-server" $@88 ":" "constant string"
#line 1873 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3012 "dhcp4_parser.cc"
    break;

  case 562: // $@89: %empty
#line 1879 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3020 "dhcp4_parser.cc"
    break;

  case 563: // server_hostname: "server-hostname" $@89 ":" "constant string"
#line 1881 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3030 "dhcp4_parser.cc"
    break;

  case 564: // $@90: %empty
#line 1887 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3038 "dhcp4_parser.cc"
    break;

  case 565: // boot_file_name: "boot-file-name" $@90 ":" "constant string"
#line 1889 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3048 "dhcp4_parser.cc"
    break;

  case 566: // $@91: %empty
#line 1895 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3056 "dhcp4_parser.cc"
    break;

  case 567: // ip_address: "ip-address" $@91 ":" "constant string"
#line 1897 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3066 "dhcp4_parser.cc"
    break;

  case 568: // $@92: %empty
#line 1903 "dhcp4_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3077 "dhcp4_parser.cc"
    break;

  case 569: // ip_addresses: "ip-addresses" $@92 ":" list_strings
#line 1908 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3086 "dhcp4_parser.cc"
    break;

  case 570: // $@93: %empty
#line 1913 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3094 "dhcp4_parser.cc"
    break;

  case 571: // duid: "duid" $@93 ":" "constant string"
#line 1915 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3104 "dhcp4_parser.cc"
    break;

  case 572: // $@94: %empty
#line 1921 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3112 "dhcp4_parser.cc"
    break;

  case 573: // hw_address: "hw-address" $@94 ":" "constant string"
#line 1923 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3122 "dhcp4_parser.cc"
    break;

  case 574: // $@95: %empty
#line 1929 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3130 "dhcp4_parser.cc"
    break;

  case 575: // client_id_value: "client-id" $@95 ":" "constant string"
#line 1931 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3140 "dhcp4_parser.cc"
    break;

  case 576: // $@96: %empty
#line 1937 "dhcp4_parser.yy"
                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3148 "dhcp4_parser.cc"
    break;

  case 577: // circuit_id_value: "circuit-id" $@96 ":" "constant string"
#line 1939 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3158 "dhcp4_parser.cc"
    break;

  case 578: // $@97: %empty
#line 1945 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3166 "dhcp4_parser.cc"
    break;

  case 579: // flex_id_value: "flex-id" $@97 ":" "constant string"
#line 1947 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3176 "dhcp4_parser.cc"
    break;

  case 580: // $@98: %empty
#line 1953 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3184 "dhcp4_parser.cc"
    break;

  case 581: // hostname: "hostname" $@98 ":" "constant string"
#line 1955 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3194 "dhcp4_parser.cc"
    break;

  case 582: // $@99: %empty
#line 1961 "dhcp4_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3205 "dhcp4_parser.cc"
    break;

  case 583: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 1966 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 584: // $@100: %empty
#line 1974 "dhcp4_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 585: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 1979 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3234 "dhcp4_parser.cc"
    break;

  case 588: // $@101: %empty
#line 1991 "dhcp4_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3245 "dhcp4_parser.cc"
    break;

  case 589: // client_classes: "client-classes" $@101 ":" "[" client_classes_list "]"
#line 1996 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 592: // $@102: %empty
#line 2005 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3264 "dhcp4_parser.cc"
    break;

  case 593: // client_class_entry: "{" $@102 client_class_params "}"
#line 2009 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3274 "dhcp4_parser.cc"
    break;

  case 610: // $@103: %empty
#line 2038 "dhcp4_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3282 "dhcp4_parser.cc"
    break;

  case 611: // client_class_test: "test" $@103 ":" "constant string"
#line 2040 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3292 "dhcp4_parser.cc"
    break;

  case 612: // only_if_required: "only-if-required" ":" "boolean"
#line 2046 "dhcp4_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3301 "dhcp4_parser.cc"
    break;

  case 613: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2053 "dhcp4_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3310 "dhcp4_parser.cc"
    break;

  case 614: // $@104: %empty
#line 2060 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3321 "dhcp4_parser.cc"
    break;

  case 615: // control_socket: "control-socket" $@104 ":" "{" control_socket_params "}"
#line 2065 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3330 "dhcp4_parser.cc"
    break;

  case 623: // $@105: %empty
#line 2081 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3338 "dhcp4_parser.cc"
    break;

  case 624: // control_socket_type: "socket-type" $@105 ":" "constant string"
#line 2083 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3348 "dhcp4_parser.cc"
    break;

  case 625: // $@106: %empty
#line 2089 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3356 "dhcp4_parser.cc"
    break;

  case 626: // control_socket_name: "socket-name" $@106 ":" "constant string"
#line 2091 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3366 "dhcp4_parser.cc"
    break;

  case 627: // $@107: %empty
#line 2100 "dhcp4_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3377 "dhcp4_parser.cc"
    break;

  case 628: // dhcp_queue_control: "dhcp-queue-control" $@107 ":" "{" queue_control_params "}"
#line 2105 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3388 "dhcp4_parser.cc"
    break;

  case 637: // enable_queue: "enable-queue" ":" "boolean"
#line 2124 "dhcp4_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3397 "dhcp4_parser.cc"
    break;

  case 638: // $@108: %empty
#line 2129 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3405 "dhcp4_parser.cc"
    break;

  case 639: // queue_type: "queue-type" $@108 ":" "constant string"
#line 2131 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3415 "dhcp4_parser.cc"
    break;

  case 640: // capacity: "capacity" ":" "integer"
#line 2137 "dhcp4_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3424 "dhcp4_parser.cc"
    break;

  case 641: // $@109: %empty
#line 2142 "dhcp4_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3432 "dhcp4_parser.cc"
    break;

  case 642: // arbitrary_map_entry: "constant string" $@109 ":" value
#line 2144 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3441 "dhcp4_parser.cc"
    break;

  case 643: // $@110: %empty
#line 2151 "dhcp4_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3452 "dhcp4_parser.cc"
    break;

  case 644: // dhcp_ddns: "dhcp-ddns" $@110 ":" "{" dhcp_ddns_params "}"
#line 2156 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3463 "dhcp4_parser.cc"
    break;

  case 645: // $@111: %empty
#line 2163 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 646: // sub_dhcp_ddns: "{" $@111 dhcp_ddns_params "}"
#line 2167 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3483 "dhcp4_parser.cc"
    break;

  case 667: // enable_updates: "enable-updates" ":" "boolean"
#line 2197 "dhcp4_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3492 "dhcp4_parser.cc"
    break;

  case 668: // $@112: %empty
#line 2202 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3500 "dhcp4_parser.cc"
    break;

  case 669: // server_ip: "server-ip" $@112 ":" "constant string"
#line 2204 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3510 "dhcp4_parser.cc"
    break;

  case 670: // server_port: "server-port" ":" "integer"
#line 2210 "dhcp4_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3519 "dhcp4_parser.cc"
    break;

  case 671: // $@113: %empty
#line 2215 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3527 "dhcp4_parser.cc"
    break;

  case 672: // sender_ip: "sender-ip" $@113 ":" "constant string"
#line 2217 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3537 "dhcp4_parser.cc"
    break;

  case 673: // sender_port: "sender-port" ":" "integer"
#line 2223 "dhcp4_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3546 "dhcp4_parser.cc"
    break;

  case 674: // max_queue_size: "max-queue-size" ":" "integer"
#line 2228 "dhcp4_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3555 "dhcp4_parser.cc"
    break;

  case 675: // $@114: %empty
#line 2233 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 676: // ncr_protocol: "ncr-protocol" $@114 ":" ncr_protocol_value
#line 2235 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3572 "dhcp4_parser.cc"
    break;

  case 677: // ncr_protocol_value: "udp"
#line 2241 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3578 "dhcp4_parser.cc"
    break;

  case 678: // ncr_protocol_value: "tcp"
#line 2242 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3584 "dhcp4_parser.cc"
    break;

  case 679: // $@115: %empty
#line 2245 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 680: // ncr_format: "ncr-format" $@115 ":" "JSON"
#line 2247 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3602 "dhcp4_parser.cc"
    break;

  case 681: // $@116: %empty
#line 2254 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3610 "dhcp4_parser.cc"
    break;

  case 682: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2256 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3620 "dhcp4_parser.cc"
    break;

  case 683: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2263 "dhcp4_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3629 "dhcp4_parser.cc"
    break;

  case 684: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2269 "dhcp4_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3638 "dhcp4_parser.cc"
    break;

  case 685: // $@117: %empty
#line 2275 "dhcp4_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3646 "dhcp4_parser.cc"
    break;

  case 686: // dep_replace_client_name: "replace-client-name" $@117 ":" ddns_replace_client_name_value
#line 2277 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3655 "dhcp4_parser.cc"
    break;

  case 687: // $@118: %empty
#line 2283 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3663 "dhcp4_parser.cc"
    break;

  case 688: // dep_generated_prefix: "generated-prefix" $@118 ":" "constant string"
#line 2285 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3673 "dhcp4_parser.cc"
    break;

  case 689: // $@119: %empty
#line 2292 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3681 "dhcp4_parser.cc"
    break;

  case 690: // dep_hostname_char_set: "hostname-char-set" $@119 ":" "constant string"
#line 2294 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3691 "dhcp4_parser.cc"
    break;

  case 691: // $@120: %empty
#line 2301 "dhcp4_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3699 "dhcp4_parser.cc"
    break;

  case 692: // dep_hostname_char_replacement: "hostname-char-replacement" $@120 ":" "constant string"
#line 2303 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3709 "dhcp4_parser.cc"
    break;

  case 693: // $@121: %empty
#line 2312 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3720 "dhcp4_parser.cc"
    break;

  case 694: // config_control: "config-control" $@121 ":" "{" config_control_params "}"
#line 2317 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3730 "dhcp4_parser.cc"
    break;

  case 695: // $@122: %empty
#line 2323 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3740 "dhcp4_parser.cc"
    break;

  case 696: // sub_config_control: "{" $@122 config_control_params "}"
#line 2327 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3749 "dhcp4_parser.cc"
    break;

  case 701: // $@123: %empty
#line 2342 "dhcp4_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 702: // config_databases: "config-databases" $@123 ":" "[" database_list "]"
#line 2347 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3769 "dhcp4_parser.cc"
    break;

  case 703: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2352 "dhcp4_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3778 "dhcp4_parser.cc"
    break;

  case 704: // $@124: %empty
#line 2359 "dhcp4_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3789 "dhcp4_parser.cc"
    break;

  case 705: // loggers: "loggers" $@124 ":" "[" loggers_entries "]"
#line 2364 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3798 "dhcp4_parser.cc"
    break;

  case 708: // $@125: %empty
#line 2376 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 709: // logger_entry: "{" $@125 logger_params "}"
#line 2380 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3816 "dhcp4_parser.cc"
    break;

  case 719: // debuglevel: "debuglevel" ":" "integer"
#line 2397 "dhcp4_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3825 "dhcp4_parser.cc"
    break;

  case 720: // $@126: %empty
#line 2402 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3833 "dhcp4_parser.cc"
    break;

  case 721: // severity: "severity" $@126 ":" "constant string"
#line 2404 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3843 "dhcp4_parser.cc"
    break;

  case 722: // $@127: %empty
#line 2410 "dhcp4_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3854 "dhcp4_parser.cc"
    break;

  case 723: // output_options_list: "output_options" $@127 ":" "[" output_options_list_content "]"
#line 2415 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 726: // $@128: %empty
#line 2424 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3873 "dhcp4_parser.cc"
    break;

  case 727: // output_entry: "{" $@128 output_params_list "}"
#line 2428 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 3881 "dhcp4_parser.cc"
    break;

  case 735: // $@129: %empty
#line 2443 "dhcp4_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3889 "dhcp4_parser.cc"
    break;

  case 736: // output: "output" $@129 ":" "constant string"
#line 2445 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3899 "dhcp4_parser.cc"
    break;

  case 737: // flush: "flush" ":" "boolean"
#line 2451 "dhcp4_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3908 "dhcp4_parser.cc"
    break;

  case 738: // maxsize: "maxsize" ":" "integer"
#line 2456 "dhcp4_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3917 "dhcp4_parser.cc"
    break;

  case 739: // maxver: "maxver" ":" "integer"
#line 2461 "dhcp4_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3926 "dhcp4_parser.cc"
    break;

  case 740: // $@130: %empty
#line 2466 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3934 "dhcp4_parser.cc"
    break;

  case 741: // pattern: "pattern" $@130 ":" "constant string"
#line 2468 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3944 "dhcp4_parser.cc"
    break;


#line 3948 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -905;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     525,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,    31,    41,    59,    72,    74,   151,
     155,   162,   188,   194,   198,   211,   217,   218,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,    41,  -151,   224,   114,    67,   234,
     229,   170,   -31,    69,   275,   -84,   400,    95,  -905,   231,
     232,   244,   230,   249,  -905,    53,  -905,  -905,  -905,  -905,
    -905,   268,   271,   277,  -905,  -905,  -905,  -905,  -905,  -905,
     278,   285,   295,   296,   297,   312,   325,   339,   340,  -905,
     391,   392,   399,   404,   405,  -905,  -905,  -905,   406,   407,
     408,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,   409,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,   411,  -905,    84,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,   415,  -905,    94,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,   416,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,    97,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   118,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,   248,   376,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   385,
    -905,  -905,   419,  -905,  -905,  -905,   420,  -905,  -905,   396,
     422,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   423,   429,  -905,  -905,  -905,  -905,
     428,   435,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   121,  -905,  -905,  -905,   436,  -905,
    -905,   439,  -905,   445,   446,  -905,  -905,   448,   449,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,   124,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   450,   130,  -905,  -905,  -905,  -905,
      41,    41,  -905,  -141,   451,   224,  -905,   453,   455,   456,
     273,   274,   280,   462,   469,   470,   471,   473,   474,   250,
     292,   300,   303,   304,   293,   310,   313,   316,   481,   321,
     322,   311,   317,   324,   482,   500,   514,   332,   353,   367,
     518,   555,   556,   557,   558,   559,   562,   563,   564,   565,
     566,   568,   384,   570,   571,   572,   573,   575,   577,   578,
    -905,   114,  -905,   579,   581,   582,   393,    67,  -905,   583,
     585,   586,   587,   589,   590,   410,   591,   593,   594,   234,
    -905,   596,   229,  -905,   597,   598,   599,   600,   601,   607,
     608,   609,  -905,   170,  -905,   612,   614,   430,   616,   617,
     618,   432,  -905,    69,   620,   434,   437,  -905,   275,   622,
     623,    70,  -905,   438,   630,   631,   457,   641,   458,   459,
     655,   656,   475,   476,   657,   658,   661,   664,   400,  -905,
     665,   485,    95,  -905,  -905,  -905,   674,   673,  -905,   675,
     676,   677,  -905,  -905,  -905,   497,   498,   499,   682,   683,
     687,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
     505,  -905,  -905,  -905,  -905,  -905,    80,   506,   507,  -905,
    -905,  -905,   691,   692,   693,   708,   707,   527,   252,   711,
     712,   713,   714,   715,  -905,   716,   717,   718,   719,   532,
     533,   722,  -905,   723,   113,   183,  -905,  -905,   541,   542,
     543,   727,   545,   546,  -905,   723,   547,   729,  -905,   549,
    -905,   723,   550,   551,   552,   553,   554,   560,   561,  -905,
     567,   569,  -905,   574,   576,   584,  -905,  -905,   588,  -905,
    -905,  -905,   592,   707,  -905,  -905,   595,   602,  -905,   603,
    -905,  -905,    12,   604,  -905,  -905,    80,   605,   606,   610,
    -905,   738,  -905,  -905,    41,   114,    95,    67,   726,  -905,
    -905,  -905,   487,   487,   739,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   740,   744,   745,   746,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,   -41,   747,   749,   751,
     221,    14,   -54,    71,   400,  -905,  -905,   752,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   753,
    -905,  -905,  -905,  -905,    96,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,   739,  -905,   149,   225,   241,  -905,   242,
    -905,  -905,  -905,  -905,  -905,  -905,   757,   761,   762,   763,
     765,  -905,  -905,  -905,  -905,   766,   767,   769,   770,   771,
     773,  -905,   262,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   265,  -905,   772,   776,  -905,  -905,
     775,   779,  -905,  -905,   778,   782,  -905,  -905,   780,   784,
    -905,  -905,   783,   785,  -905,  -905,  -905,  -905,  -905,  -905,
      61,  -905,  -905,  -905,  -905,  -905,  -905,  -905,    90,  -905,
    -905,   786,   792,  -905,  -905,   790,   794,  -905,   795,   796,
     797,   798,   799,   800,   266,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,   801,   802,   803,  -905,   315,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   319,  -905,
    -905,  -905,   804,  -905,   805,  -905,  -905,  -905,   333,  -905,
    -905,  -905,  -905,  -905,   362,  -905,   112,  -905,   624,  -905,
     807,   808,  -905,  -905,  -905,  -905,   806,   809,  -905,  -905,
    -905,   812,   726,  -905,   813,   814,   815,   816,   621,   632,
     633,   634,   635,   817,   822,   823,   824,   640,   642,   643,
     644,   639,   645,   487,  -905,  -905,   487,  -905,   739,   234,
    -905,   740,    69,  -905,   744,   275,  -905,   745,   580,  -905,
     746,   -41,  -905,   291,   747,  -905,   170,  -905,   749,   -84,
    -905,   751,   646,   647,   648,   649,   650,   651,   221,  -905,
     652,   653,   659,    14,  -905,   837,   840,   -54,  -905,   654,
     842,   660,   843,    71,  -905,  -905,    39,   752,  -905,  -905,
     844,   848,   229,  -905,   753,   849,  -905,  -905,   666,  -905,
     331,   668,   669,   672,  -905,  -905,  -905,  -905,  -905,   679,
     688,   704,   709,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
     373,  -905,   374,  -905,   867,  -905,   872,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,   375,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   892,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   901,   907,
    -905,  -905,  -905,  -905,  -905,   905,  -905,   377,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
     728,   735,  -905,  -905,   736,  -905,    41,  -905,  -905,   927,
    -905,  -905,  -905,  -905,  -905,   383,  -905,  -905,  -905,  -905,
    -905,  -905,   789,   386,  -905,   723,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,   580,  -905,   928,   743,  -905,   291,  -905,
    -905,  -905,  -905,  -905,  -905,   970,   793,   977,    39,  -905,
    -905,  -905,  -905,  -905,   810,  -905,  -905,   978,  -905,   811,
    -905,  -905,   979,  -905,  -905,   148,  -905,  -119,   979,  -905,
    -905,   980,   981,   983,  -905,   389,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,   984,   818,   819,   821,   985,  -119,  -905,
     825,  -905,  -905,  -905,   826,  -905,  -905,  -905
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    63,     7,   169,     9,   327,    11,   514,    13,
     539,    15,   439,    17,   447,    19,   484,    21,   292,    23,
     645,    25,   695,    27,    45,    39,     0,     0,     0,     0,
       0,   541,     0,   449,   486,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    61,     0,    58,    60,   693,   158,
     184,     0,     0,     0,   560,   562,   564,   182,   191,   193,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   130,
       0,     0,     0,     0,     0,   138,   145,   147,     0,     0,
       0,   319,   437,   476,   392,   527,   529,   385,   257,   588,
     531,   284,   303,     0,   271,   614,   627,   643,   151,   153,
     704,     0,   120,     0,    65,    67,    68,    69,    70,    71,
     102,   103,   104,    72,   100,    89,    90,    91,   108,   109,
     110,   111,   112,   113,   114,   115,   106,   107,   116,   117,
     118,    75,    76,    97,    77,    78,    79,   119,    83,    84,
      73,   101,    74,    81,    82,    95,    96,    98,    92,    93,
      94,    80,    85,    86,    87,    88,    99,   105,   171,   173,
     177,     0,   168,     0,   160,   162,   163,   164,   165,   166,
     167,   373,   375,   377,   506,   371,   379,     0,   383,   381,
     584,   370,   331,   332,   333,   334,   335,   356,   357,   358,
     346,   347,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,     0,   329,   338,   351,   352,   353,   339,
     341,   342,   344,   340,   336,   337,   354,   355,   343,   348,
     349,   350,   345,   525,   524,   520,   521,   519,     0,   516,
     518,   522,   523,   582,   570,   572,   576,   574,   580,   578,
     566,   559,   553,   557,   558,     0,   542,   543,   554,   555,
     556,   550,   545,   551,   547,   548,   549,   552,   546,     0,
     466,   237,     0,   470,   468,   473,     0,   462,   463,     0,
     450,   451,   453,   465,   454,   455,   456,   472,   457,   458,
     459,   460,   461,   500,     0,     0,   498,   499,   502,   503,
       0,   487,   488,   490,   491,   492,   493,   494,   495,   496,
     497,   299,   301,   296,     0,   294,   297,   298,     0,   681,
     668,     0,   671,     0,     0,   675,   679,     0,     0,   685,
     687,   689,   691,   666,   664,   665,     0,   647,   649,   650,
     651,   652,   653,   654,   655,   656,   661,   657,   658,   659,
     660,   662,   663,   701,     0,     0,   697,   699,   700,    44,
       0,     0,    37,     0,     0,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      55,     0,    64,     0,     0,     0,     0,     0,   170,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     328,     0,     0,   515,     0,     0,     0,     0,     0,     0,
       0,     0,   540,     0,   440,     0,     0,     0,     0,     0,
       0,     0,   448,     0,     0,     0,     0,   485,     0,     0,
       0,     0,   293,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   646,
       0,     0,     0,   696,    48,    41,     0,     0,    59,     0,
       0,     0,   132,   133,   134,     0,     0,     0,     0,     0,
       0,   121,   122,   123,   124,   125,   126,   127,   128,   129,
       0,   156,   157,   135,   136,   137,     0,     0,     0,   149,
     150,   155,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   613,     0,     0,     0,     0,     0,
       0,     0,    66,     0,     0,     0,   181,   161,     0,     0,
       0,     0,     0,     0,   391,     0,     0,     0,   330,     0,
     517,     0,     0,     0,     0,     0,     0,     0,     0,   544,
       0,     0,   464,     0,     0,     0,   475,   452,     0,   504,
     505,   489,     0,     0,   295,   667,     0,     0,   670,     0,
     673,   674,     0,     0,   683,   684,     0,     0,     0,     0,
     648,     0,   703,   698,     0,     0,     0,     0,     0,   561,
     563,   565,     0,     0,   195,   131,   140,   141,   142,   143,
     144,   139,   146,   148,   321,   441,   478,   394,    38,   528,
     530,   387,   388,   389,   390,   386,     0,     0,   533,   286,
       0,     0,     0,     0,     0,   152,   154,     0,    49,   172,
     175,   176,   174,   179,   180,   178,   374,   376,   378,   508,
     372,   380,   384,   382,     0,   526,   583,   571,   573,   577,
     575,   581,   579,   567,   467,   238,   471,   469,   474,   501,
     300,   302,   682,   669,   672,   677,   678,   676,   680,   686,
     688,   690,   692,   195,    42,     0,     0,     0,   189,     0,
     186,   188,   224,   230,   232,   234,     0,     0,     0,     0,
       0,   246,   248,   250,   252,     0,     0,     0,     0,     0,
       0,   223,     0,   201,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   216,   217,   218,   213,   219,   220,
     221,   214,   215,   222,     0,   199,     0,   196,   197,   325,
       0,   322,   323,   445,     0,   442,   443,   482,     0,   479,
     480,   398,     0,   395,   396,   266,   267,   268,   269,   270,
       0,   259,   261,   262,   263,   264,   265,   592,     0,   590,
     537,     0,   534,   535,   290,     0,   287,   288,     0,     0,
       0,     0,     0,     0,     0,   305,   307,   308,   309,   310,
     311,   312,     0,     0,     0,   280,     0,   273,   275,   276,
     277,   278,   279,   623,   625,   622,   620,   621,     0,   616,
     618,   619,     0,   638,     0,   641,   634,   635,     0,   629,
     631,   632,   633,   636,     0,   708,     0,   706,    51,   512,
       0,   509,   510,   568,   586,   587,     0,     0,    62,   694,
     159,     0,     0,   185,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   183,   192,     0,   194,     0,     0,
     320,     0,   449,   438,     0,   486,   477,     0,     0,   393,
       0,     0,   258,   594,     0,   589,   541,   532,     0,     0,
     285,     0,     0,     0,     0,     0,     0,     0,     0,   304,
       0,     0,     0,     0,   272,     0,     0,     0,   615,     0,
       0,     0,     0,     0,   628,   644,     0,     0,   705,    53,
       0,    52,     0,   507,     0,     0,   585,   702,     0,   187,
       0,     0,     0,     0,   236,   239,   240,   241,   242,     0,
       0,     0,     0,   254,   255,   243,   244,   245,   256,   202,
       0,   198,     0,   324,     0,   444,     0,   481,   436,   417,
     418,   419,   405,   406,   422,   423,   424,   408,   409,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     402,   403,   404,   415,   416,   414,     0,   400,   407,   420,
     421,   410,   411,   412,   413,   397,   260,   610,     0,   608,
     609,   601,   602,   606,   607,   603,   604,   605,     0,   595,
     596,   598,   599,   600,   591,     0,   536,     0,   289,   313,
     314,   315,   316,   317,   318,   306,   281,   282,   283,   274,
       0,     0,   617,   637,     0,   640,     0,   630,   722,     0,
     720,   718,   712,   716,   717,     0,   710,   714,   715,   713,
     707,    50,     0,     0,   511,     0,   190,   226,   227,   228,
     229,   225,   231,   233,   235,   247,   249,   251,   253,   200,
     326,   446,   483,     0,   399,     0,     0,   593,     0,   538,
     291,   624,   626,   639,   642,     0,     0,     0,     0,   709,
      54,   513,   569,   401,     0,   612,   597,     0,   719,     0,
     711,   611,     0,   721,   726,     0,   724,     0,     0,   723,
     735,     0,     0,     0,   740,     0,   728,   730,   731,   732,
     733,   734,   725,     0,     0,     0,     0,     0,     0,   727,
       0,   737,   738,   739,     0,   729,   736,   741
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,   -52,  -905,  -533,  -905,   368,
    -905,  -905,  -905,  -905,  -905,  -905,  -580,  -905,  -905,  -905,
     -67,  -905,  -905,  -905,   611,  -905,  -905,  -905,  -905,   345,
     544,   -40,   -28,   -24,    -1,     1,    11,    19,    22,  -905,
    -905,  -905,  -905,    25,    26,    29,    30,    32,    37,  -905,
     356,    40,  -905,    43,  -905,    44,    45,    47,  -905,    48,
    -905,    50,  -905,  -905,  -905,  -905,   346,   537,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   104,  -905,  -905,  -905,  -905,  -905,
    -905,   264,  -905,    82,  -905,  -640,    88,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,   -63,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
      73,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,    49,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,    62,  -905,  -905,
    -905,    66,   510,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
      64,  -905,  -905,  -905,  -905,  -905,  -905,  -904,  -905,  -905,
    -905,    86,  -905,  -905,  -905,    98,   615,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -901,  -905,   -65,  -905,    52,
    -905,    51,  -905,  -905,  -905,  -905,  -905,  -905,  -905,    85,
    -905,  -905,  -107,   -46,  -905,  -905,  -905,  -905,  -905,    99,
    -905,  -905,  -905,   100,  -905,   526,  -905,   -42,  -905,  -905,
    -905,  -905,  -905,   -36,  -905,  -905,  -905,  -905,  -905,   -35,
    -905,  -905,  -905,    91,  -905,  -905,  -905,   101,  -905,   522,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,    54,  -905,  -905,  -905,    55,   613,  -905,  -905,   -51,
    -905,   -11,  -905,   -25,  -905,  -905,  -905,    83,  -905,  -905,
    -905,    89,  -905,   548,   -55,  -905,     0,  -905,     7,  -905,
     326,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -900,  -905,
    -905,  -905,  -905,  -905,   102,  -905,  -905,  -905,   -99,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,    75,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,    76,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,   349,   517,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,   394,   515,  -905,
    -905,  -905,  -905,  -905,  -905,    77,  -905,  -905,  -100,  -905,
    -905,  -905,  -905,  -905,  -905,  -117,  -905,  -905,  -136,  -905,
    -905,  -905,  -905,  -905,  -905,  -905
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
       0,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   669,
      82,    83,    39,    64,    79,    80,   689,   878,   970,   971,
     761,    41,    66,    85,    86,    87,   394,    43,    67,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   418,   155,   156,   157,   158,   159,   160,   161,   424,
     661,   162,   425,   163,   426,   164,   165,   166,   447,   167,
     448,   168,   169,   170,   171,   398,   203,   204,    45,    68,
     205,   453,   206,   454,   692,   207,   455,   695,   208,   172,
     406,   173,   399,   739,   740,   741,   891,   174,   407,   175,
     408,   786,   787,   788,   916,   762,   763,   764,   894,  1111,
     765,   895,   766,   896,   767,   897,   768,   769,   486,   770,
     771,   772,   773,   774,   775,   776,   777,   903,   778,   904,
     779,   905,   780,   906,   781,   782,   783,   176,   437,   810,
     811,   812,   813,   814,   815,   816,   177,   443,   846,   847,
     848,   849,   850,   178,   440,   825,   826,   827,   939,    59,
      75,   344,   345,   346,   499,   347,   500,   179,   441,   834,
     835,   836,   837,   838,   839,   840,   841,   180,   430,   790,
     791,   792,   919,    47,    69,   243,   244,   245,   463,   246,
     459,   247,   460,   248,   461,   249,   464,   250,   467,   251,
     466,   181,   436,   675,   253,   182,   433,   802,   803,   804,
     928,  1036,  1037,   183,   431,    53,    72,   794,   795,   796,
     922,    55,    73,   309,   310,   311,   312,   313,   314,   315,
     485,   316,   489,   317,   488,   318,   319,   490,   320,   184,
     432,   798,   799,   800,   925,    57,    74,   330,   331,   332,
     333,   334,   494,   335,   336,   337,   338,   255,   462,   880,
     881,   882,   972,    49,    70,   268,   269,   270,   471,   185,
     434,   186,   435,   187,   439,   821,   822,   823,   936,    51,
      71,   285,   286,   287,   188,   403,   189,   404,   190,   405,
     291,   481,   885,   975,   292,   475,   293,   476,   294,   478,
     295,   477,   296,   480,   297,   479,   298,   474,   262,   468,
     886,   191,   438,   818,   819,   933,  1058,  1059,  1060,  1061,
    1062,  1125,  1063,   192,   193,   444,   858,   859,   860,   955,
     861,   956,   194,   445,   868,   869,   870,   871,   960,   872,
     873,   962,   195,   446,    61,    76,   366,   367,   368,   369,
     505,   370,   371,   507,   372,   373,   374,   510,   727,   375,
     511,   376,   504,   377,   378,   379,   514,   380,   515,   381,
     516,   382,   517,   196,   397,    63,    77,   385,   386,   387,
     520,   388,   197,   449,   876,   877,   966,  1095,  1096,  1097,
    1098,  1137,  1099,  1135,  1155,  1156,  1157,  1165,  1166,  1167,
    1173,  1168,  1169,  1170,  1171,  1177
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     142,   202,   221,   264,   281,   265,   307,   326,   343,   363,
     308,   327,    78,   784,   259,   702,   288,   209,   256,   271,
     283,   706,   321,   339,  1031,   364,   299,  1032,  1044,   222,
     725,    28,   328,   668,   254,   267,   282,    81,   329,   341,
     342,   223,   125,   126,   258,   224,    29,   526,    30,  1160,
      31,   122,  1161,  1162,  1163,  1164,   395,   210,   257,   272,
     284,   396,   322,   340,   931,   365,    40,   932,   225,   260,
     226,   289,   805,   806,   807,   808,   261,   809,   290,    42,
     227,    44,   198,   199,   853,   854,   200,   451,   228,   201,
     668,   229,   452,   934,   230,   231,   935,   457,   232,   233,
     469,   234,   458,   300,   141,   470,   235,   383,   384,   236,
     125,   126,   237,   238,   239,   967,   240,   241,   968,   242,
     252,   472,   266,   301,   501,    88,   473,   518,    89,   502,
     690,   691,   519,   522,   141,   125,   126,    90,   523,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   842,   843,
     844,  1158,   451,   301,  1159,   302,   303,   888,    46,   304,
     305,   306,    48,   125,   126,   125,   126,   125,   126,    50,
     726,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   341,   342,    52,   122,   123,    94,    95,
      96,    54,   141,   693,   694,    56,  1088,   124,  1089,  1090,
     125,   126,   862,   863,   864,   127,   280,   883,    58,  1031,
     128,   129,  1032,  1044,    60,    62,   130,   141,   522,    32,
      33,    34,    35,   889,    84,   390,   131,   389,   392,   132,
     656,   657,   658,   659,   457,   892,   133,   134,   391,   890,
     893,   135,   393,   123,   136,   141,   482,   141,   137,   865,
      92,    93,    94,    95,    96,   913,   125,   126,   913,   948,
     914,   660,   400,   915,   949,   401,  1000,   273,   138,   139,
     140,   402,   409,   274,   275,   276,   277,   278,   279,   410,
     280,   100,   101,   102,   103,   104,   105,   106,   107,   411,
     412,   413,   141,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   123,   211,   212,   213,   414,   123,   953,    94,
      95,    96,   957,   954,   263,   125,   126,   958,   214,   415,
     125,   126,   215,   216,   217,   127,   963,   218,   524,   525,
     219,   964,   218,   416,   417,   219,   130,   828,   829,   830,
     831,   832,   833,   220,   671,   672,   673,   674,   141,   301,
     323,   302,   303,   324,   325,   518,  1107,  1108,  1109,  1110,
     965,   125,   126,   122,   123,   301,   913,   469,  1123,   483,
     501,  1119,  1120,  1124,   142,  1130,  1138,   125,   126,   472,
     202,  1139,  1178,   484,  1141,   419,   420,  1179,   138,   139,
    1047,  1048,   221,   421,   492,   264,   209,   265,   422,   423,
     427,   428,   429,   442,   259,   450,   281,   141,   256,   456,
     465,   271,   141,   487,   491,   493,   307,   495,   288,   222,
     308,   326,   283,   496,   254,   327,   497,   267,   498,   541,
     503,   223,   321,   506,   258,   224,   210,   339,   282,   508,
     509,   363,   512,   513,   521,   527,   328,   529,   257,   530,
     531,   272,   329,   141,   532,   533,   535,   364,   225,   260,
     226,   534,   284,   536,   537,   538,   261,   539,   540,   141,
     227,   542,   322,   289,   546,   550,   556,   340,   228,   543,
     290,   229,   544,   545,   230,   231,   125,   126,   232,   233,
     547,   234,   553,   548,   557,   549,   235,   365,   554,   236,
     551,   552,   237,   238,   239,   555,   240,   241,   558,   242,
     252,   742,   562,   559,   266,  1142,   743,   744,   745,   746,
     747,   748,   749,   750,   751,   752,   753,   754,   755,   756,
     757,   758,   759,   760,   560,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   561,   563,
     564,   565,   566,   567,   361,   362,   568,   569,   570,   571,
     572,   301,   573,   574,   575,   576,   577,   578,   142,   579,
     202,   580,   581,   583,   586,   584,   585,   588,   141,   589,
     590,   591,   734,   592,   593,   595,   209,   596,   597,   594,
     599,   601,   602,   603,   604,   605,    92,    93,    94,    95,
      96,   606,   607,   608,   845,   855,   610,   363,   611,   612,
     613,   614,   615,   616,   618,   619,   622,   623,   620,   625,
     851,   856,   866,   364,   626,   627,   210,   100,   101,   102,
     103,   104,   105,   106,   107,   629,   628,   630,   631,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   632,
     633,   636,   637,   123,   301,   638,   634,   635,   639,   641,
     852,   857,   867,   365,   642,   141,   125,   126,   644,   216,
     645,   127,   646,   647,   648,   649,   650,   651,   218,   652,
     653,   219,   654,   655,   662,   663,   664,   665,   666,   220,
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   667,    30,   670,   676,   677,   678,   679,
     685,   686,   680,   681,   682,   683,   684,   687,   688,   696,
     697,   698,   699,   700,   701,   703,   704,   705,   707,   708,
     709,   710,   711,   733,   138,   139,   785,   789,   712,   713,
     738,   793,   797,   801,   817,   714,   820,   715,   824,   875,
     879,   898,   716,   728,   717,   899,   900,   901,   141,   902,
     907,   908,   718,   909,   910,   911,   719,   912,   917,   918,
     720,   920,   921,   722,   923,   924,   926,   927,   930,   929,
     723,   724,   937,   730,   731,   938,   940,   941,   732,   942,
     943,   944,   945,   946,   947,   950,   951,   952,   959,   961,
     984,   974,   969,   973,   976,   977,   978,   980,   981,   982,
     983,   989,   986,   985,   988,   987,   990,   991,   992,   993,
     997,   994,   995,   996,   998,  1069,  1070,  1071,  1072,  1073,
    1074,  1080,  1077,  1076,  1081,  1083,  1084,  1086,  1078,  1085,
    1101,  1102,   221,  1105,  1106,   307,  1112,  1113,   326,   308,
    1114,  1008,   327,  1033,   259,  1030,  1049,  1115,   256,   281,
    1050,   321,   343,  1041,   339,  1121,  1116,  1039,  1055,   222,
    1122,   288,  1053,   328,   254,   283,   845,  1051,  1009,   329,
     855,   223,  1117,  1038,   258,   224,  1126,  1118,  1052,  1091,
    1010,   282,   851,  1092,  1011,   264,   856,   265,   257,  1127,
    1128,   322,   866,  1129,   340,  1093,  1131,  1040,   225,   260,
     226,   271,  1054,  1132,  1133,   284,   261,  1012,  1042,  1013,
     227,  1136,  1144,  1056,  1145,  1043,   289,   267,   228,  1014,
    1057,   229,   852,   290,   230,   231,   857,  1015,   232,   233,
    1016,   234,   867,  1017,  1018,  1094,   235,  1019,  1020,   236,
    1021,   272,   237,   238,   239,  1022,   240,   241,  1023,   242,
     252,  1024,  1025,  1026,  1147,  1027,  1028,  1140,  1029,  1035,
    1034,  1149,  1148,  1152,  1174,  1175,  1154,  1176,  1180,  1184,
     735,   721,   729,   737,   587,   582,   979,   887,  1151,  1153,
    1001,   999,  1079,  1068,  1046,  1067,   528,  1003,  1182,  1181,
    1183,   624,  1075,  1186,  1187,  1045,  1143,  1002,  1007,   617,
     621,  1066,  1004,  1005,   266,  1065,  1006,  1103,  1104,  1146,
     884,   609,  1082,   874,  1134,   640,  1064,   643,  1150,  1087,
     736,  1172,  1185,     0,  1100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1008,     0,  1033,     0,
    1030,  1049,     0,     0,     0,  1050,     0,     0,  1041,     0,
       0,  1091,  1039,  1055,     0,  1092,     0,  1053,     0,     0,
       0,     0,  1051,  1009,   598,   600,     0,  1093,  1038,     0,
       0,     0,     0,  1052,     0,  1010,     0,     0,     0,  1011,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1040,     0,     0,     0,     0,  1054,     0,     0,
       0,     0,  1012,  1042,  1013,     0,     0,  1094,  1056,     0,
    1043,     0,     0,     0,  1014,  1057,     0,     0,     0,     0,
       0,     0,  1015,     0,     0,  1016,     0,     0,  1017,  1018,
       0,     0,  1019,  1020,     0,  1021,     0,     0,     0,     0,
    1022,     0,     0,  1023,     0,     0,  1024,  1025,  1026,     0,
    1027,  1028,     0,  1029,  1035,  1034
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   653,    69,   595,    71,    68,    69,    70,
      71,   601,    73,    74,   928,    76,    72,   928,   928,    69,
      18,     0,    74,   566,    69,    70,    71,   188,    74,   123,
     124,    69,    96,    97,    69,    69,     5,   188,     7,   168,
       9,    82,   171,   172,   173,   174,     3,    68,    69,    70,
      71,     8,    73,    74,     3,    76,     7,     6,    69,    69,
      69,    71,   113,   114,   115,   116,    69,   118,    71,     7,
      69,     7,    15,    16,   138,   139,    19,     3,    69,    22,
     623,    69,     8,     3,    69,    69,     6,     3,    69,    69,
       3,    69,     8,    34,   188,     8,    69,    12,    13,    69,
      96,    97,    69,    69,    69,     3,    69,    69,     6,    69,
      69,     3,    70,    84,     3,    11,     8,     3,    14,     8,
      17,    18,     8,     3,   188,    96,    97,    23,     8,    25,
      26,    27,    28,    29,    30,    31,    32,    33,   134,   135,
     136,     3,     3,    84,     6,    86,    87,     8,     7,    90,
      91,    92,     7,    96,    97,    96,    97,    96,    97,     7,
     158,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,   123,   124,     7,    82,    83,    28,    29,
      30,     7,   188,    20,    21,     7,   167,    93,   169,   170,
      96,    97,   141,   142,   143,   101,   120,   121,     7,  1123,
     106,   107,  1123,  1123,     7,     7,   112,   188,     3,   188,
     189,   190,   191,     8,    10,     3,   122,     6,     8,   125,
     160,   161,   162,   163,     3,     3,   132,   133,     4,     8,
       8,   137,     3,    83,   140,   188,     8,   188,   144,   188,
      26,    27,    28,    29,    30,     3,    96,    97,     3,     3,
       8,   191,     4,     8,     8,     4,   916,   107,   164,   165,
     166,     4,     4,   113,   114,   115,   116,   117,   118,     4,
     120,    57,    58,    59,    60,    61,    62,    63,    64,     4,
       4,     4,   188,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    83,    79,    80,    81,     4,    83,     3,    28,
      29,    30,     3,     8,    95,    96,    97,     8,    94,     4,
      96,    97,    98,    99,   100,   101,     3,   108,   390,   391,
     111,     8,   108,     4,     4,   111,   112,   126,   127,   128,
     129,   130,   131,   119,   102,   103,   104,   105,   188,    84,
      85,    86,    87,    88,    89,     3,    35,    36,    37,    38,
       8,    96,    97,    82,    83,    84,     3,     3,     3,     3,
       3,     8,     8,     8,   451,     8,     3,    96,    97,     3,
     457,     8,     3,     8,     8,     4,     4,     8,   164,   165,
     109,   110,   469,     4,     8,   472,   457,   472,     4,     4,
       4,     4,     4,     4,   469,     4,   483,   188,   469,     4,
       4,   472,   188,     4,     4,     3,   493,     4,   483,   469,
     493,   498,   483,     4,   469,   498,     8,   472,     3,   189,
       4,   469,   493,     4,   469,   469,   457,   498,   483,     4,
       4,   518,     4,     4,     4,     4,   498,     4,   469,     4,
       4,   472,   498,   188,   191,   191,     4,   518,   469,   469,
     469,   191,   483,     4,     4,     4,   469,     4,     4,   188,
     469,   189,   493,   483,   191,     4,     4,   498,   469,   189,
     483,   469,   189,   189,   469,   469,    96,    97,   469,   469,
     190,   469,   191,   190,     4,   189,   469,   518,   191,   469,
     189,   189,   469,   469,   469,   191,   469,   469,     4,   469,
     469,    34,     4,   191,   472,  1105,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,   191,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   191,     4,
       4,     4,     4,     4,   164,   165,     4,     4,     4,     4,
       4,    84,     4,   189,     4,     4,     4,     4,   645,     4,
     647,     4,     4,     4,   191,     4,     4,     4,   188,     4,
       4,     4,   644,     4,     4,     4,   647,     4,     4,   189,
       4,     4,     4,     4,     4,     4,    26,    27,    28,    29,
      30,     4,     4,     4,   681,   682,     4,   684,     4,   189,
       4,     4,     4,   191,     4,   191,     4,     4,   191,   191,
     681,   682,   683,   684,     4,     4,   647,    57,    58,    59,
      60,    61,    62,    63,    64,     4,   189,   189,   189,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,     4,
       4,     4,     4,    83,    84,     4,   191,   191,     4,     4,
     681,   682,   683,   684,   189,   188,    96,    97,     4,    99,
       7,   101,     7,     7,     7,   188,   188,   188,   108,     7,
       7,   111,     5,   188,   188,   188,     5,     5,     5,   119,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,     5,     7,   188,     5,     5,     5,     5,
     188,   188,     7,     7,     7,     7,     7,     5,     5,   188,
     188,   188,     5,   188,   188,   188,     7,   188,   188,   188,
     188,   188,   188,     5,   164,   165,     7,     7,   188,   188,
      24,     7,     7,     7,     7,   188,     7,   188,     7,     7,
       7,     4,   188,   159,   188,     4,     4,     4,   188,     4,
       4,     4,   188,     4,     4,     4,   188,     4,     6,     3,
     188,     6,     3,   188,     6,     3,     6,     3,     3,     6,
     188,   188,     6,   188,   188,     3,     6,     3,   188,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     189,     3,   188,     6,     8,     6,     4,     4,     4,     4,
       4,     4,   189,   191,   189,   191,     4,     4,     4,   189,
     191,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,     4,   189,   191,     4,   191,     4,     4,   189,   189,
       6,     3,   919,     4,   188,   922,   188,   188,   925,   922,
     188,   928,   925,   928,   919,   928,   933,   188,   919,   936,
     933,   922,   939,   928,   925,     8,   188,   928,   933,   919,
       8,   936,   933,   925,   919,   936,   953,   933,   928,   925,
     957,   919,   188,   928,   919,   919,     4,   188,   933,   966,
     928,   936,   953,   966,   928,   972,   957,   972,   919,     8,
       3,   922,   963,     8,   925,   966,   188,   928,   919,   919,
     919,   972,   933,   188,   188,   936,   919,   928,   928,   928,
     919,     4,     4,   933,   191,   928,   936,   972,   919,   928,
     933,   919,   953,   936,   919,   919,   957,   928,   919,   919,
     928,   919,   963,   928,   928,   966,   919,   928,   928,   919,
     928,   972,   919,   919,   919,   928,   919,   919,   928,   919,
     919,   928,   928,   928,     4,   928,   928,   188,   928,   928,
     928,     4,   189,     5,     4,     4,     7,     4,     4,     4,
     645,   623,   636,   647,   457,   451,   892,   733,   188,   188,
     918,   913,   953,   941,   931,   939,   395,   921,   189,   191,
     189,   501,   948,   188,   188,   930,  1123,   919,   927,   493,
     498,   938,   922,   924,   972,   936,   925,   972,   974,  1128,
     704,   483,   957,   684,  1086,   518,   934,   522,  1138,   963,
     646,  1158,  1178,    -1,   967,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1123,    -1,  1123,    -1,
    1123,  1128,    -1,    -1,    -1,  1128,    -1,    -1,  1123,    -1,
      -1,  1138,  1123,  1128,    -1,  1138,    -1,  1128,    -1,    -1,
      -1,    -1,  1128,  1123,   469,   472,    -1,  1138,  1123,    -1,
      -1,    -1,    -1,  1128,    -1,  1123,    -1,    -1,    -1,  1123,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1123,    -1,    -1,    -1,    -1,  1128,    -1,    -1,
      -1,    -1,  1123,  1123,  1123,    -1,    -1,  1138,  1128,    -1,
    1123,    -1,    -1,    -1,  1123,  1128,    -1,    -1,    -1,    -1,
      -1,    -1,  1123,    -1,    -1,  1123,    -1,    -1,  1123,  1123,
      -1,    -1,  1123,  1123,    -1,  1123,    -1,    -1,    -1,    -1,
    1123,    -1,    -1,  1123,    -1,    -1,  1123,  1123,  1123,    -1,
    1123,  1123,    -1,  1123,  1123,  1123
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,     0,     5,
       7,     9,   188,   189,   190,   191,   207,   208,   209,   214,
       7,   223,     7,   229,     7,   270,     7,   375,     7,   455,
       7,   471,     7,   407,     7,   413,     7,   437,     7,   351,
       7,   536,     7,   567,   215,   210,   224,   230,   271,   376,
     456,   472,   408,   414,   438,   352,   537,   568,   207,   216,
     217,   188,   212,   213,    10,   225,   226,   227,    11,    14,
      23,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    82,    83,    93,    96,    97,   101,   106,   107,
     112,   122,   125,   132,   133,   137,   140,   144,   164,   165,
     166,   188,   222,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   244,   245,   246,   247,   248,
     249,   250,   253,   255,   257,   258,   259,   261,   263,   264,
     265,   266,   281,   283,   289,   291,   329,   338,   345,   359,
     369,   393,   397,   405,   431,   461,   463,   465,   476,   478,
     480,   503,   515,   516,   524,   534,   565,   574,    15,    16,
      19,    22,   222,   268,   269,   272,   274,   277,   280,   461,
     463,    79,    80,    81,    94,    98,    99,   100,   108,   111,
     119,   222,   233,   234,   235,   236,   237,   238,   239,   240,
     245,   246,   247,   248,   249,   250,   253,   255,   257,   258,
     259,   261,   263,   377,   378,   379,   381,   383,   385,   387,
     389,   391,   393,   396,   431,   449,   461,   463,   465,   476,
     478,   480,   500,    95,   222,   389,   391,   431,   457,   458,
     459,   461,   463,   107,   113,   114,   115,   116,   117,   118,
     120,   222,   431,   461,   463,   473,   474,   475,   476,   478,
     480,   482,   486,   488,   490,   492,   494,   496,   498,   405,
      34,    84,    86,    87,    90,    91,    92,   222,   309,   415,
     416,   417,   418,   419,   420,   421,   423,   425,   427,   428,
     430,   461,   463,    85,    88,    89,   222,   309,   419,   425,
     439,   440,   441,   442,   443,   445,   446,   447,   448,   461,
     463,   123,   124,   222,   353,   354,   355,   357,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   164,   165,   222,   461,   463,   538,   539,   540,   541,
     543,   544,   546,   547,   548,   551,   553,   555,   556,   557,
     559,   561,   563,    12,    13,   569,   570,   571,   573,     6,
       3,     4,     8,     3,   228,     3,     8,   566,   267,   284,
       4,     4,     4,   477,   479,   481,   282,   290,   292,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   243,     4,
       4,     4,     4,     4,   251,   254,   256,     4,     4,     4,
     370,   406,   432,   398,   462,   464,   394,   330,   504,   466,
     346,   360,     4,   339,   517,   525,   535,   260,   262,   575,
       4,     3,     8,   273,   275,   278,     4,     3,     8,   382,
     384,   386,   450,   380,   388,     4,   392,   390,   501,     3,
       8,   460,     3,     8,   499,   487,   489,   493,   491,   497,
     495,   483,     8,     3,     8,   422,   310,     4,   426,   424,
     429,     4,     8,     3,   444,     4,     4,     8,     3,   356,
     358,     3,     8,     4,   554,   542,     4,   545,     4,     4,
     549,   552,     4,     4,   558,   560,   562,   564,     3,     8,
     572,     4,     3,     8,   207,   207,   188,     4,   226,     4,
       4,     4,   191,   191,   191,     4,     4,     4,     4,     4,
       4,   189,   189,   189,   189,   189,   191,   190,   190,   189,
       4,   189,   189,   191,   191,   191,     4,     4,     4,   191,
     191,   191,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   189,     4,     4,     4,     4,     4,
       4,     4,   232,     4,     4,     4,   191,   269,     4,     4,
       4,     4,     4,     4,   189,     4,     4,     4,   378,     4,
     458,     4,     4,     4,     4,     4,     4,     4,     4,   475,
       4,     4,   189,     4,     4,     4,   191,   417,     4,   191,
     191,   441,     4,     4,   354,   191,     4,     4,   189,     4,
     189,   189,     4,     4,   191,   191,     4,     4,     4,     4,
     539,     4,   189,   570,     4,     7,     7,     7,     7,   188,
     188,   188,     7,     7,     5,   188,   160,   161,   162,   163,
     191,   252,   188,   188,     5,     5,     5,     5,   209,   211,
     188,   102,   103,   104,   105,   395,     5,     5,     5,     5,
       7,     7,     7,     7,     7,   188,   188,     5,     5,   218,
      17,    18,   276,    20,    21,   279,   188,   188,   188,     5,
     188,   188,   218,   188,     7,   188,   218,   188,   188,   188,
     188,   188,   188,   188,   188,   188,   188,   188,   188,   188,
     188,   211,   188,   188,   188,    18,   158,   550,   159,   252,
     188,   188,   188,     5,   207,   231,   569,   268,    24,   285,
     286,   287,    34,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   222,   297,   298,   299,   302,   304,   306,   308,   309,
     311,   312,   313,   314,   315,   316,   317,   318,   320,   322,
     324,   326,   327,   328,   297,     7,   293,   294,   295,     7,
     371,   372,   373,     7,   409,   410,   411,     7,   433,   434,
     435,     7,   399,   400,   401,   113,   114,   115,   116,   118,
     331,   332,   333,   334,   335,   336,   337,     7,   505,   506,
       7,   467,   468,   469,     7,   347,   348,   349,   126,   127,
     128,   129,   130,   131,   361,   362,   363,   364,   365,   366,
     367,   368,   134,   135,   136,   222,   340,   341,   342,   343,
     344,   461,   463,   138,   139,   222,   461,   463,   518,   519,
     520,   522,   141,   142,   143,   188,   461,   463,   526,   527,
     528,   529,   531,   532,   538,     7,   576,   577,   219,     7,
     451,   452,   453,   121,   482,   484,   502,   293,     8,     8,
       8,   288,     3,     8,   300,   303,   305,   307,     4,     4,
       4,     4,     4,   319,   321,   323,   325,     4,     4,     4,
       4,     4,     4,     3,     8,     8,   296,     6,     3,   374,
       6,     3,   412,     6,     3,   436,     6,     3,   402,     6,
       3,     3,     6,   507,     3,     6,   470,     6,     3,   350,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   521,   523,     3,     8,     4,
     530,     4,   533,     3,     8,     8,   578,     3,     6,   188,
     220,   221,   454,     6,     3,   485,     8,     6,     4,   286,
       4,     4,     4,     4,   189,   191,   189,   191,   189,     4,
       4,     4,     4,   189,   189,   189,   189,   191,   189,   298,
     297,   295,   377,   373,   415,   411,   439,   435,   222,   233,
     234,   235,   236,   237,   238,   239,   240,   245,   246,   247,
     248,   249,   250,   253,   255,   257,   258,   259,   261,   263,
     309,   369,   387,   389,   391,   393,   403,   404,   431,   461,
     463,   476,   478,   480,   500,   401,   332,   109,   110,   222,
     309,   405,   431,   461,   463,   476,   478,   480,   508,   509,
     510,   511,   512,   514,   506,   473,   469,   353,   349,   189,
     189,   189,   189,   189,   189,   362,   191,   189,   189,   341,
       4,     4,   519,   191,     4,   189,     4,   527,   167,   169,
     170,   222,   309,   461,   463,   579,   580,   581,   582,   584,
     577,     6,     3,   457,   453,     4,   188,    35,    36,    37,
      38,   301,   188,   188,   188,   188,   188,   188,   188,     8,
       8,     8,     8,     3,     8,   513,     4,     8,     3,     8,
       8,   188,   188,   188,   207,   585,     4,   583,     3,     8,
     188,     8,   218,   404,     4,   191,   510,     4,   189,     4,
     580,   188,     5,   188,     7,   586,   587,   588,     3,     6,
     168,   171,   172,   173,   174,   589,   590,   591,   593,   594,
     595,   596,   587,   592,     4,     4,     4,   597,     3,     8,
       4,   191,   189,   189,     4,   590,   188,   188
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   192,   194,   193,   195,   193,   196,   193,   197,   193,
     198,   193,   199,   193,   200,   193,   201,   193,   202,   193,
     203,   193,   204,   193,   205,   193,   206,   193,   207,   207,
     207,   207,   207,   207,   207,   208,   210,   209,   211,   212,
     212,   213,   213,   215,   214,   216,   216,   217,   217,   219,
     218,   220,   220,   221,   221,   222,   224,   223,   225,   225,
     226,   228,   227,   230,   229,   231,   231,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     243,   242,   244,   245,   246,   247,   248,   249,   251,   250,
     252,   252,   252,   252,   252,   254,   253,   256,   255,   257,
     258,   260,   259,   262,   261,   263,   264,   265,   267,   266,
     268,   268,   269,   269,   269,   269,   269,   269,   269,   271,
     270,   273,   272,   275,   274,   276,   276,   278,   277,   279,
     279,   280,   282,   281,   284,   283,   285,   285,   286,   288,
     287,   290,   289,   292,   291,   293,   293,   294,   294,   296,
     295,   297,   297,   298,   298,   298,   298,   298,   298,   298,
     298,   298,   298,   298,   298,   298,   298,   298,   298,   298,
     298,   298,   298,   298,   300,   299,   301,   301,   301,   301,
     303,   302,   305,   304,   307,   306,   308,   310,   309,   311,
     312,   313,   314,   315,   316,   317,   319,   318,   321,   320,
     323,   322,   325,   324,   326,   327,   328,   330,   329,   331,
     331,   332,   332,   332,   332,   332,   333,   334,   335,   336,
     337,   339,   338,   340,   340,   341,   341,   341,   341,   341,
     341,   342,   343,   344,   346,   345,   347,   347,   348,   348,
     350,   349,   352,   351,   353,   353,   353,   354,   354,   356,
     355,   358,   357,   360,   359,   361,   361,   362,   362,   362,
     362,   362,   362,   363,   364,   365,   366,   367,   368,   370,
     369,   371,   371,   372,   372,   374,   373,   376,   375,   377,
     377,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   380,   379,   382,   381,   384,   383,   386,   385,   388,
     387,   390,   389,   392,   391,   394,   393,   395,   395,   395,
     395,   396,   398,   397,   399,   399,   400,   400,   402,   401,
     403,   403,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   406,   405,   408,
     407,   409,   409,   410,   410,   412,   411,   414,   413,   415,
     415,   416,   416,   417,   417,   417,   417,   417,   417,   417,
     417,   417,   417,   418,   419,   420,   422,   421,   424,   423,
     426,   425,   427,   429,   428,   430,   432,   431,   433,   433,
     434,   434,   436,   435,   438,   437,   439,   439,   440,   440,
     441,   441,   441,   441,   441,   441,   441,   441,   441,   442,
     444,   443,   445,   446,   447,   448,   450,   449,   451,   451,
     452,   452,   454,   453,   456,   455,   457,   457,   458,   458,
     458,   458,   458,   458,   458,   460,   459,   462,   461,   464,
     463,   466,   465,   467,   467,   468,   468,   470,   469,   472,
     471,   473,   473,   474,   474,   475,   475,   475,   475,   475,
     475,   475,   475,   475,   475,   475,   475,   475,   475,   475,
     477,   476,   479,   478,   481,   480,   483,   482,   485,   484,
     487,   486,   489,   488,   491,   490,   493,   492,   495,   494,
     497,   496,   499,   498,   501,   500,   502,   502,   504,   503,
     505,   505,   507,   506,   508,   508,   509,   509,   510,   510,
     510,   510,   510,   510,   510,   510,   510,   510,   510,   511,
     513,   512,   514,   515,   517,   516,   518,   518,   519,   519,
     519,   519,   519,   521,   520,   523,   522,   525,   524,   526,
     526,   527,   527,   527,   527,   527,   527,   528,   530,   529,
     531,   533,   532,   535,   534,   537,   536,   538,   538,   539,
     539,   539,   539,   539,   539,   539,   539,   539,   539,   539,
     539,   539,   539,   539,   539,   539,   539,   540,   542,   541,
     543,   545,   544,   546,   547,   549,   548,   550,   550,   552,
     551,   554,   553,   555,   556,   558,   557,   560,   559,   562,
     561,   564,   563,   566,   565,   568,   567,   569,   569,   570,
     570,   572,   571,   573,   575,   574,   576,   576,   578,   577,
     579,   579,   580,   580,   580,   580,   580,   580,   580,   581,
     583,   582,   585,   584,   586,   586,   588,   587,   589,   589,
     590,   590,   590,   590,   590,   592,   591,   593,   594,   595,
     597,   596
  };

  const signed char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       1,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       3,     0,     4,     0,     4,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     1,     1,     0,     4,     1,
       1,     3,     0,     6,     0,     6,     1,     3,     1,     0,
       4,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     1,     0,     6,
       1,     3,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     0,     6,     3,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       0,     4
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
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"max-row-errors\"", "\"valid-lifetime\"", "\"min-valid-lifetime\"",
  "\"max-valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"calculate-tee-times\"", "\"t1-percent\"", "\"t2-percent\"",
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
  "\"out-of-pool\"", "\"global\"", "\"all\"",
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
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
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
  "global_objects", "global_object", "dhcp4_object", "$@18", "sub_dhcp4",
  "$@19", "global_params", "global_param", "valid_lifetime",
  "min_valid_lifetime", "max_valid_lifetime", "renew_timer",
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@20", "echo_client_id",
  "match_client_id", "authoritative", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@21", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@22", "ddns_qualifying_suffix", "$@23",
  "ddns_update_on_renew", "ddns_use_conflict_resolution",
  "hostname_char_set", "$@24", "hostname_char_replacement", "$@25",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "interfaces_config", "$@26",
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
  "max_reconnect_tries", "reconnect_wait_time", "max_row_errors",
  "host_reservation_identifiers", "$@46",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@47", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@48", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@49",
  "sub_hooks_library", "$@50", "hooks_params", "hooks_param", "library",
  "$@51", "parameters", "$@52", "expired_leases_processing", "$@53",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@54",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@55",
  "sub_subnet4", "$@56", "subnet4_params", "subnet4_param", "subnet",
  "$@57", "subnet_4o6_interface", "$@58", "subnet_4o6_interface_id",
  "$@59", "subnet_4o6_subnet", "$@60", "interface", "$@61", "client_class",
  "$@62", "require_client_classes", "$@63", "reservation_mode", "$@64",
  "hr_mode", "id", "shared_networks", "$@65", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@66",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@67", "sub_option_def_list", "$@68", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@69",
  "sub_option_def", "$@70", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@71",
  "option_def_record_types", "$@72", "space", "$@73", "option_def_space",
  "option_def_encapsulate", "$@74", "option_def_array", "option_data_list",
  "$@75", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@76", "sub_option_data", "$@77",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@78",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@79", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@80", "sub_pool4", "$@81",
  "pool_params", "pool_param", "pool_entry", "$@82", "user_context",
  "$@83", "comment", "$@84", "reservations", "$@85", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@86", "sub_reservation",
  "$@87", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@88", "server_hostname", "$@89",
  "boot_file_name", "$@90", "ip_address", "$@91", "ip_addresses", "$@92",
  "duid", "$@93", "hw_address", "$@94", "client_id_value", "$@95",
  "circuit_id_value", "$@96", "flex_id_value", "$@97", "hostname", "$@98",
  "reservation_client_classes", "$@99", "relay", "$@100", "relay_map",
  "client_classes", "$@101", "client_classes_list", "client_class_entry",
  "$@102", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@103",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@104",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@105", "control_socket_name", "$@106", "dhcp_queue_control", "$@107",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@108", "capacity", "arbitrary_map_entry", "$@109",
  "dhcp_ddns", "$@110", "sub_dhcp_ddns", "$@111", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@112", "server_port",
  "sender_ip", "$@113", "sender_port", "max_queue_size", "ncr_protocol",
  "$@114", "ncr_protocol_value", "ncr_format", "$@115",
  "dep_qualifying_suffix", "$@116", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@117",
  "dep_generated_prefix", "$@118", "dep_hostname_char_set", "$@119",
  "dep_hostname_char_replacement", "$@120", "config_control", "$@121",
  "sub_config_control", "$@122", "config_control_params",
  "config_control_param", "config_databases", "$@123",
  "config_fetch_wait_time", "loggers", "$@124", "loggers_entries",
  "logger_entry", "$@125", "logger_params", "logger_param", "debuglevel",
  "severity", "$@126", "output_options_list", "$@127",
  "output_options_list_content", "output_entry", "$@128",
  "output_params_list", "output_params", "output", "$@129", "flush",
  "maxsize", "maxver", "pattern", "$@130", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   279,   279,   279,   280,   280,   281,   281,   282,   282,
     283,   283,   284,   284,   285,   285,   286,   286,   287,   287,
     288,   288,   289,   289,   290,   290,   291,   291,   299,   300,
     301,   302,   303,   304,   305,   308,   313,   313,   324,   327,
     328,   331,   335,   342,   342,   349,   350,   353,   357,   364,
     364,   371,   372,   375,   379,   390,   399,   399,   414,   415,
     419,   422,   422,   439,   439,   448,   449,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   491,   492,   493,   494,   495,   496,
     497,   498,   499,   500,   501,   502,   503,   504,   505,   506,
     507,   510,   515,   520,   525,   530,   535,   540,   545,   550,
     555,   555,   563,   568,   573,   578,   583,   588,   593,   593,
     601,   604,   607,   610,   613,   619,   619,   627,   627,   635,
     641,   647,   647,   655,   655,   663,   668,   673,   678,   678,
     689,   690,   693,   694,   695,   696,   697,   698,   699,   702,
     702,   711,   711,   721,   721,   728,   729,   732,   732,   739,
     741,   745,   751,   751,   763,   763,   773,   774,   776,   778,
     778,   796,   796,   808,   808,   818,   819,   822,   823,   826,
     826,   836,   837,   840,   841,   842,   843,   844,   845,   846,
     847,   848,   849,   850,   851,   852,   853,   854,   855,   856,
     857,   858,   859,   860,   863,   863,   870,   871,   872,   873,
     876,   876,   884,   884,   892,   892,   900,   905,   905,   913,
     918,   923,   928,   933,   938,   943,   948,   948,   956,   956,
     964,   964,   972,   972,   980,   985,   990,   996,   996,  1006,
    1007,  1010,  1011,  1012,  1013,  1014,  1017,  1022,  1027,  1032,
    1037,  1044,  1044,  1056,  1057,  1060,  1061,  1062,  1063,  1064,
    1065,  1068,  1073,  1078,  1083,  1083,  1093,  1094,  1097,  1098,
    1101,  1101,  1111,  1111,  1121,  1122,  1123,  1126,  1127,  1130,
    1130,  1138,  1138,  1146,  1146,  1157,  1158,  1161,  1162,  1163,
    1164,  1165,  1166,  1169,  1174,  1179,  1184,  1189,  1194,  1202,
    1202,  1215,  1216,  1219,  1220,  1227,  1227,  1253,  1253,  1264,
    1265,  1269,  1270,  1271,  1272,  1273,  1274,  1275,  1276,  1277,
    1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,  1286,  1287,
    1288,  1289,  1290,  1291,  1292,  1293,  1294,  1295,  1296,  1297,
    1298,  1299,  1300,  1301,  1302,  1303,  1304,  1305,  1306,  1307,
    1308,  1311,  1311,  1319,  1319,  1327,  1327,  1335,  1335,  1343,
    1343,  1351,  1351,  1359,  1359,  1369,  1369,  1376,  1377,  1378,
    1379,  1382,  1389,  1389,  1400,  1401,  1405,  1406,  1409,  1409,
    1417,  1418,  1421,  1422,  1423,  1424,  1425,  1426,  1427,  1428,
    1429,  1430,  1431,  1432,  1433,  1434,  1435,  1436,  1437,  1438,
    1439,  1440,  1441,  1442,  1443,  1444,  1445,  1446,  1447,  1448,
    1449,  1450,  1451,  1452,  1453,  1454,  1455,  1462,  1462,  1475,
    1475,  1484,  1485,  1488,  1489,  1494,  1494,  1509,  1509,  1523,
    1524,  1527,  1528,  1531,  1532,  1533,  1534,  1535,  1536,  1537,
    1538,  1539,  1540,  1543,  1545,  1550,  1552,  1552,  1560,  1560,
    1568,  1568,  1576,  1578,  1578,  1586,  1595,  1595,  1607,  1608,
    1613,  1614,  1619,  1619,  1631,  1631,  1643,  1644,  1649,  1650,
    1655,  1656,  1657,  1658,  1659,  1660,  1661,  1662,  1663,  1666,
    1668,  1668,  1676,  1678,  1680,  1685,  1693,  1693,  1705,  1706,
    1709,  1710,  1713,  1713,  1723,  1723,  1733,  1734,  1737,  1738,
    1739,  1740,  1741,  1742,  1743,  1746,  1746,  1754,  1754,  1779,
    1779,  1809,  1809,  1819,  1820,  1823,  1824,  1827,  1827,  1836,
    1836,  1845,  1846,  1849,  1850,  1854,  1855,  1856,  1857,  1858,
    1859,  1860,  1861,  1862,  1863,  1864,  1865,  1866,  1867,  1868,
    1871,  1871,  1879,  1879,  1887,  1887,  1895,  1895,  1903,  1903,
    1913,  1913,  1921,  1921,  1929,  1929,  1937,  1937,  1945,  1945,
    1953,  1953,  1961,  1961,  1974,  1974,  1984,  1985,  1991,  1991,
    2001,  2002,  2005,  2005,  2015,  2016,  2019,  2020,  2023,  2024,
    2025,  2026,  2027,  2028,  2029,  2030,  2031,  2032,  2033,  2036,
    2038,  2038,  2046,  2053,  2060,  2060,  2070,  2071,  2074,  2075,
    2076,  2077,  2078,  2081,  2081,  2089,  2089,  2100,  2100,  2112,
    2113,  2116,  2117,  2118,  2119,  2120,  2121,  2124,  2129,  2129,
    2137,  2142,  2142,  2151,  2151,  2163,  2163,  2173,  2174,  2177,
    2178,  2179,  2180,  2181,  2182,  2183,  2184,  2185,  2186,  2187,
    2188,  2189,  2190,  2191,  2192,  2193,  2194,  2197,  2202,  2202,
    2210,  2215,  2215,  2223,  2228,  2233,  2233,  2241,  2242,  2245,
    2245,  2254,  2254,  2263,  2269,  2275,  2275,  2283,  2283,  2292,
    2292,  2301,  2301,  2312,  2312,  2323,  2323,  2333,  2334,  2338,
    2339,  2342,  2342,  2352,  2359,  2359,  2371,  2372,  2376,  2376,
    2384,  2385,  2388,  2389,  2390,  2391,  2392,  2393,  2394,  2397,
    2402,  2402,  2410,  2410,  2420,  2421,  2424,  2424,  2432,  2433,
    2436,  2437,  2438,  2439,  2440,  2443,  2443,  2451,  2456,  2461,
    2466,  2466
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
#line 5452 "dhcp4_parser.cc"

#line 2474 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
