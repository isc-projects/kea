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
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ddns_replace_client_name_value: // ddns_replace_client_name_value
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_socket_type: // socket_type
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_outbound_interface_value: // outbound_interface_value
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_db_type: // db_type
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_hr_mode: // hr_mode
#line 271 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp4_parser.cc"
        break;

      case symbol_kind::S_ncr_protocol_value: // ncr_protocol_value
#line 271 "dhcp4_parser.yy"
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
#line 280 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp4_parser.cc"
    break;

  case 4: // $@2: %empty
#line 281 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp4_parser.cc"
    break;

  case 6: // $@3: %empty
#line 282 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 762 "dhcp4_parser.cc"
    break;

  case 8: // $@4: %empty
#line 283 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp4_parser.cc"
    break;

  case 10: // $@5: %empty
#line 284 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 774 "dhcp4_parser.cc"
    break;

  case 12: // $@6: %empty
#line 285 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp4_parser.cc"
    break;

  case 14: // $@7: %empty
#line 286 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 786 "dhcp4_parser.cc"
    break;

  case 16: // $@8: %empty
#line 287 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 792 "dhcp4_parser.cc"
    break;

  case 18: // $@9: %empty
#line 288 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 798 "dhcp4_parser.cc"
    break;

  case 20: // $@10: %empty
#line 289 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 804 "dhcp4_parser.cc"
    break;

  case 22: // $@11: %empty
#line 290 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 810 "dhcp4_parser.cc"
    break;

  case 24: // $@12: %empty
#line 291 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 816 "dhcp4_parser.cc"
    break;

  case 26: // $@13: %empty
#line 292 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 822 "dhcp4_parser.cc"
    break;

  case 28: // value: "integer"
#line 300 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc"
    break;

  case 29: // value: "floating point"
#line 301 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc"
    break;

  case 30: // value: "boolean"
#line 302 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc"
    break;

  case 31: // value: "constant string"
#line 303 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc"
    break;

  case 32: // value: "null"
#line 304 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp4_parser.cc"
    break;

  case 33: // value: map2
#line 305 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc"
    break;

  case 34: // value: list_generic
#line 306 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp4_parser.cc"
    break;

  case 35: // sub_json: value
#line 309 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 873 "dhcp4_parser.cc"
    break;

  case 36: // $@14: %empty
#line 314 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc"
    break;

  case 37: // map2: "{" $@14 map_content "}"
#line 319 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 894 "dhcp4_parser.cc"
    break;

  case 38: // map_value: map2
#line 325 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 900 "dhcp4_parser.cc"
    break;

  case 41: // not_empty_map: "constant string" ":" value
#line 332 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 910 "dhcp4_parser.cc"
    break;

  case 42: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 337 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 921 "dhcp4_parser.cc"
    break;

  case 43: // $@15: %empty
#line 345 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 930 "dhcp4_parser.cc"
    break;

  case 44: // list_generic: "[" $@15 list_content "]"
#line 348 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 938 "dhcp4_parser.cc"
    break;

  case 47: // not_empty_list: value
#line 356 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp4_parser.cc"
    break;

  case 48: // not_empty_list: not_empty_list "," value
#line 360 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 956 "dhcp4_parser.cc"
    break;

  case 49: // $@16: %empty
#line 367 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 964 "dhcp4_parser.cc"
    break;

  case 50: // list_strings: "[" $@16 list_strings_content "]"
#line 369 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 973 "dhcp4_parser.cc"
    break;

  case 53: // not_empty_list_strings: "constant string"
#line 378 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp4_parser.cc"
    break;

  case 54: // not_empty_list_strings: not_empty_list_strings "," "constant string"
#line 382 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 991 "dhcp4_parser.cc"
    break;

  case 55: // unknown_map_entry: "constant string" ":"
#line 393 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1002 "dhcp4_parser.cc"
    break;

  case 56: // $@17: %empty
#line 402 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1013 "dhcp4_parser.cc"
    break;

  case 57: // syntax_map: "{" $@17 global_object "}"
#line 407 "dhcp4_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1026 "dhcp4_parser.cc"
    break;

  case 58: // $@18: %empty
#line 417 "dhcp4_parser.yy"
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
#line 1041 "dhcp4_parser.cc"
    break;

  case 59: // global_object: "Dhcp4" $@18 ":" "{" global_params "}"
#line 426 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1051 "dhcp4_parser.cc"
    break;

  case 60: // $@19: %empty
#line 434 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1061 "dhcp4_parser.cc"
    break;

  case 61: // sub_dhcp4: "{" $@19 global_params "}"
#line 438 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1070 "dhcp4_parser.cc"
    break;

  case 119: // valid_lifetime: "valid-lifetime" ":" "integer"
#line 506 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1080 "dhcp4_parser.cc"
    break;

  case 120: // min_valid_lifetime: "min-valid-lifetime" ":" "integer"
#line 512 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 121: // max_valid_lifetime: "max-valid-lifetime" ":" "integer"
#line 518 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1100 "dhcp4_parser.cc"
    break;

  case 122: // renew_timer: "renew-timer" ":" "integer"
#line 524 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1110 "dhcp4_parser.cc"
    break;

  case 123: // rebind_timer: "rebind-timer" ":" "integer"
#line 530 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1120 "dhcp4_parser.cc"
    break;

  case 124: // calculate_tee_times: "calculate-tee-times" ":" "boolean"
#line 536 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1130 "dhcp4_parser.cc"
    break;

  case 125: // t1_percent: "t1-percent" ":" "floating point"
#line 542 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 126: // t2_percent: "t2-percent" ":" "floating point"
#line 548 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1150 "dhcp4_parser.cc"
    break;

  case 127: // cache_threshold: "cache-threshold" ":" "floating point"
#line 554 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1160 "dhcp4_parser.cc"
    break;

  case 128: // cache_max_age: "cache-max-age" ":" "integer"
#line 560 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1170 "dhcp4_parser.cc"
    break;

  case 129: // decline_probation_period: "decline-probation-period" ":" "integer"
#line 566 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1180 "dhcp4_parser.cc"
    break;

  case 130: // $@20: %empty
#line 572 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1189 "dhcp4_parser.cc"
    break;

  case 131: // server_tag: "server-tag" $@20 ":" "constant string"
#line 575 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1199 "dhcp4_parser.cc"
    break;

  case 132: // echo_client_id: "echo-client-id" ":" "boolean"
#line 581 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1209 "dhcp4_parser.cc"
    break;

  case 133: // match_client_id: "match-client-id" ":" "boolean"
#line 587 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1219 "dhcp4_parser.cc"
    break;

  case 134: // authoritative: "authoritative" ":" "boolean"
#line 593 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 135: // ddns_send_updates: "ddns-send-updates" ":" "boolean"
#line 599 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1239 "dhcp4_parser.cc"
    break;

  case 136: // ddns_override_no_update: "ddns-override-no-update" ":" "boolean"
#line 605 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1249 "dhcp4_parser.cc"
    break;

  case 137: // ddns_override_client_update: "ddns-override-client-update" ":" "boolean"
#line 611 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1259 "dhcp4_parser.cc"
    break;

  case 138: // $@21: %empty
#line 617 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1268 "dhcp4_parser.cc"
    break;

  case 139: // ddns_replace_client_name: "ddns-replace-client-name" $@21 ":" ddns_replace_client_name_value
#line 620 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1277 "dhcp4_parser.cc"
    break;

  case 140: // ddns_replace_client_name_value: "when-present"
#line 626 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1285 "dhcp4_parser.cc"
    break;

  case 141: // ddns_replace_client_name_value: "never"
#line 629 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1293 "dhcp4_parser.cc"
    break;

  case 142: // ddns_replace_client_name_value: "always"
#line 632 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1301 "dhcp4_parser.cc"
    break;

  case 143: // ddns_replace_client_name_value: "when-not-present"
#line 635 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1309 "dhcp4_parser.cc"
    break;

  case 144: // ddns_replace_client_name_value: "boolean"
#line 638 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1318 "dhcp4_parser.cc"
    break;

  case 145: // $@22: %empty
#line 644 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1327 "dhcp4_parser.cc"
    break;

  case 146: // ddns_generated_prefix: "ddns-generated-prefix" $@22 ":" "constant string"
#line 647 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1337 "dhcp4_parser.cc"
    break;

  case 147: // $@23: %empty
#line 653 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1346 "dhcp4_parser.cc"
    break;

  case 148: // ddns_qualifying_suffix: "ddns-qualifying-suffix" $@23 ":" "constant string"
#line 656 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1356 "dhcp4_parser.cc"
    break;

  case 149: // ddns_update_on_renew: "ddns-update-on-renew" ":" "boolean"
#line 662 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1366 "dhcp4_parser.cc"
    break;

  case 150: // $@24: %empty
#line 668 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1375 "dhcp4_parser.cc"
    break;

  case 151: // hostname_char_set: "hostname-char-set" $@24 ":" "constant string"
#line 671 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1385 "dhcp4_parser.cc"
    break;

  case 152: // $@25: %empty
#line 677 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1394 "dhcp4_parser.cc"
    break;

  case 153: // hostname_char_replacement: "hostname-char-replacement" $@25 ":" "constant string"
#line 680 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1404 "dhcp4_parser.cc"
    break;

  case 154: // store_extended_info: "store-extended-info" ":" "boolean"
#line 686 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1414 "dhcp4_parser.cc"
    break;

  case 155: // statistic_default_sample_count: "statistic-default-sample-count" ":" "integer"
#line 692 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1424 "dhcp4_parser.cc"
    break;

  case 156: // statistic_default_sample_age: "statistic-default-sample-age" ":" "integer"
#line 698 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1434 "dhcp4_parser.cc"
    break;

  case 157: // $@26: %empty
#line 704 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 158: // interfaces_config: "interfaces-config" $@26 ":" "{" interfaces_config_params "}"
#line 710 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1456 "dhcp4_parser.cc"
    break;

  case 168: // $@27: %empty
#line 729 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1466 "dhcp4_parser.cc"
    break;

  case 169: // sub_interfaces4: "{" $@27 interfaces_config_params "}"
#line 733 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 170: // $@28: %empty
#line 738 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1487 "dhcp4_parser.cc"
    break;

  case 171: // interfaces_list: "interfaces" $@28 ":" list_strings
#line 744 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1496 "dhcp4_parser.cc"
    break;

  case 172: // $@29: %empty
#line 749 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1505 "dhcp4_parser.cc"
    break;

  case 173: // dhcp_socket_type: "dhcp-socket-type" $@29 ":" socket_type
#line 752 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1514 "dhcp4_parser.cc"
    break;

  case 174: // socket_type: "raw"
#line 757 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1520 "dhcp4_parser.cc"
    break;

  case 175: // socket_type: "udp"
#line 758 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1526 "dhcp4_parser.cc"
    break;

  case 176: // $@30: %empty
#line 761 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1535 "dhcp4_parser.cc"
    break;

  case 177: // outbound_interface: "outbound-interface" $@30 ":" outbound_interface_value
#line 764 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 178: // outbound_interface_value: "same-as-inbound"
#line 769 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1552 "dhcp4_parser.cc"
    break;

  case 179: // outbound_interface_value: "use-routing"
#line 771 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1560 "dhcp4_parser.cc"
    break;

  case 180: // re_detect: "re-detect" ":" "boolean"
#line 775 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1570 "dhcp4_parser.cc"
    break;

  case 181: // $@31: %empty
#line 782 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1582 "dhcp4_parser.cc"
    break;

  case 182: // lease_database: "lease-database" $@31 ":" "{" database_map_params "}"
#line 788 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1593 "dhcp4_parser.cc"
    break;

  case 183: // $@32: %empty
#line 795 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1605 "dhcp4_parser.cc"
    break;

  case 184: // sanity_checks: "sanity-checks" $@32 ":" "{" sanity_checks_params "}"
#line 801 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1614 "dhcp4_parser.cc"
    break;

  case 188: // $@33: %empty
#line 811 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1623 "dhcp4_parser.cc"
    break;

  case 189: // lease_checks: "lease-checks" $@33 ":" "constant string"
#line 814 "dhcp4_parser.yy"
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
#line 1643 "dhcp4_parser.cc"
    break;

  case 190: // $@34: %empty
#line 830 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 191: // hosts_database: "hosts-database" $@34 ":" "{" database_map_params "}"
#line 836 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1666 "dhcp4_parser.cc"
    break;

  case 192: // $@35: %empty
#line 843 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1678 "dhcp4_parser.cc"
    break;

  case 193: // hosts_databases: "hosts-databases" $@35 ":" "[" database_list "]"
#line 849 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1687 "dhcp4_parser.cc"
    break;

  case 198: // $@36: %empty
#line 862 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1697 "dhcp4_parser.cc"
    break;

  case 199: // database: "{" $@36 database_map_params "}"
#line 866 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1707 "dhcp4_parser.cc"
    break;

  case 223: // $@37: %empty
#line 899 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1716 "dhcp4_parser.cc"
    break;

  case 224: // database_type: "type" $@37 ":" db_type
#line 902 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1725 "dhcp4_parser.cc"
    break;

  case 225: // db_type: "memfile"
#line 907 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1731 "dhcp4_parser.cc"
    break;

  case 226: // db_type: "mysql"
#line 908 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1737 "dhcp4_parser.cc"
    break;

  case 227: // db_type: "postgresql"
#line 909 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1743 "dhcp4_parser.cc"
    break;

  case 228: // db_type: "cql"
#line 910 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1749 "dhcp4_parser.cc"
    break;

  case 229: // $@38: %empty
#line 913 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1758 "dhcp4_parser.cc"
    break;

  case 230: // user: "user" $@38 ":" "constant string"
#line 916 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1768 "dhcp4_parser.cc"
    break;

  case 231: // $@39: %empty
#line 922 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1777 "dhcp4_parser.cc"
    break;

  case 232: // password: "password" $@39 ":" "constant string"
#line 925 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1787 "dhcp4_parser.cc"
    break;

  case 233: // $@40: %empty
#line 931 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1796 "dhcp4_parser.cc"
    break;

  case 234: // host: "host" $@40 ":" "constant string"
#line 934 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1806 "dhcp4_parser.cc"
    break;

  case 235: // port: "port" ":" "integer"
#line 940 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1816 "dhcp4_parser.cc"
    break;

  case 236: // $@41: %empty
#line 946 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1825 "dhcp4_parser.cc"
    break;

  case 237: // name: "name" $@41 ":" "constant string"
#line 949 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1835 "dhcp4_parser.cc"
    break;

  case 238: // persist: "persist" ":" "boolean"
#line 955 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1845 "dhcp4_parser.cc"
    break;

  case 239: // lfc_interval: "lfc-interval" ":" "integer"
#line 961 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1855 "dhcp4_parser.cc"
    break;

  case 240: // readonly: "readonly" ":" "boolean"
#line 967 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1865 "dhcp4_parser.cc"
    break;

  case 241: // connect_timeout: "connect-timeout" ":" "integer"
#line 973 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1875 "dhcp4_parser.cc"
    break;

  case 242: // request_timeout: "request-timeout" ":" "integer"
#line 979 "dhcp4_parser.yy"
                                               {
    ctx.unique("request-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1885 "dhcp4_parser.cc"
    break;

  case 243: // tcp_keepalive: "tcp-keepalive" ":" "integer"
#line 985 "dhcp4_parser.yy"
                                           {
    ctx.unique("tcp-keepalive", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1895 "dhcp4_parser.cc"
    break;

  case 244: // tcp_nodelay: "tcp-nodelay" ":" "boolean"
#line 991 "dhcp4_parser.yy"
                                       {
    ctx.unique("tcp-nodelay", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1905 "dhcp4_parser.cc"
    break;

  case 245: // $@42: %empty
#line 997 "dhcp4_parser.yy"
                               {
    ctx.unique("contact-points", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1914 "dhcp4_parser.cc"
    break;

  case 246: // contact_points: "contact-points" $@42 ":" "constant string"
#line 1000 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1924 "dhcp4_parser.cc"
    break;

  case 247: // $@43: %empty
#line 1006 "dhcp4_parser.yy"
                   {
    ctx.unique("keyspace", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1933 "dhcp4_parser.cc"
    break;

  case 248: // keyspace: "keyspace" $@43 ":" "constant string"
#line 1009 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1943 "dhcp4_parser.cc"
    break;

  case 249: // $@44: %empty
#line 1015 "dhcp4_parser.yy"
                         {
    ctx.unique("consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1952 "dhcp4_parser.cc"
    break;

  case 250: // consistency: "consistency" $@44 ":" "constant string"
#line 1018 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 251: // $@45: %empty
#line 1024 "dhcp4_parser.yy"
                                       {
    ctx.unique("serial-consistency", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 252: // serial_consistency: "serial-consistency" $@45 ":" "constant string"
#line 1027 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 253: // max_reconnect_tries: "max-reconnect-tries" ":" "integer"
#line 1033 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 254: // reconnect_wait_time: "reconnect-wait-time" ":" "integer"
#line 1039 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 255: // max_row_errors: "max-row-errors" ":" "integer"
#line 1045 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2011 "dhcp4_parser.cc"
    break;

  case 256: // $@46: %empty
#line 1052 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2023 "dhcp4_parser.cc"
    break;

  case 257: // host_reservation_identifiers: "host-reservation-identifiers" $@46 ":" "[" host_reservation_identifiers_list "]"
#line 1058 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2032 "dhcp4_parser.cc"
    break;

  case 265: // duid_id: "duid"
#line 1074 "dhcp4_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2041 "dhcp4_parser.cc"
    break;

  case 266: // hw_address_id: "hw-address"
#line 1079 "dhcp4_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 267: // circuit_id: "circuit-id"
#line 1084 "dhcp4_parser.yy"
                        {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 268: // client_id: "client-id"
#line 1089 "dhcp4_parser.yy"
                      {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2068 "dhcp4_parser.cc"
    break;

  case 269: // flex_id: "flex-id"
#line 1094 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2077 "dhcp4_parser.cc"
    break;

  case 270: // $@47: %empty
#line 1101 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 271: // dhcp_multi_threading: "multi-threading" $@47 ":" "{" multi_threading_params "}"
#line 1107 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 280: // enable_multi_threading: "enable-multi-threading" ":" "boolean"
#line 1126 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 281: // thread_pool_size: "thread-pool-size" ":" "integer"
#line 1132 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2120 "dhcp4_parser.cc"
    break;

  case 282: // packet_queue_size: "packet-queue-size" ":" "integer"
#line 1138 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2130 "dhcp4_parser.cc"
    break;

  case 283: // $@48: %empty
#line 1144 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2142 "dhcp4_parser.cc"
    break;

  case 284: // hooks_libraries: "hooks-libraries" $@48 ":" "[" hooks_libraries_list "]"
#line 1150 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2151 "dhcp4_parser.cc"
    break;

  case 289: // $@49: %empty
#line 1163 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2161 "dhcp4_parser.cc"
    break;

  case 290: // hooks_library: "{" $@49 hooks_params "}"
#line 1167 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2171 "dhcp4_parser.cc"
    break;

  case 291: // $@50: %empty
#line 1173 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2181 "dhcp4_parser.cc"
    break;

  case 292: // sub_hooks_library: "{" $@50 hooks_params "}"
#line 1177 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2191 "dhcp4_parser.cc"
    break;

  case 298: // $@51: %empty
#line 1192 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2200 "dhcp4_parser.cc"
    break;

  case 299: // library: "library" $@51 ":" "constant string"
#line 1195 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2210 "dhcp4_parser.cc"
    break;

  case 300: // $@52: %empty
#line 1201 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2219 "dhcp4_parser.cc"
    break;

  case 301: // parameters: "parameters" $@52 ":" map_value
#line 1204 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2228 "dhcp4_parser.cc"
    break;

  case 302: // $@53: %empty
#line 1210 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2240 "dhcp4_parser.cc"
    break;

  case 303: // expired_leases_processing: "expired-leases-processing" $@53 ":" "{" expired_leases_params "}"
#line 1216 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2250 "dhcp4_parser.cc"
    break;

  case 312: // reclaim_timer_wait_time: "reclaim-timer-wait-time" ":" "integer"
#line 1234 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2260 "dhcp4_parser.cc"
    break;

  case 313: // flush_reclaimed_timer_wait_time: "flush-reclaimed-timer-wait-time" ":" "integer"
#line 1240 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2270 "dhcp4_parser.cc"
    break;

  case 314: // hold_reclaimed_time: "hold-reclaimed-time" ":" "integer"
#line 1246 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2280 "dhcp4_parser.cc"
    break;

  case 315: // max_reclaim_leases: "max-reclaim-leases" ":" "integer"
#line 1252 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2290 "dhcp4_parser.cc"
    break;

  case 316: // max_reclaim_time: "max-reclaim-time" ":" "integer"
#line 1258 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2300 "dhcp4_parser.cc"
    break;

  case 317: // unwarned_reclaim_cycles: "unwarned-reclaim-cycles" ":" "integer"
#line 1264 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2310 "dhcp4_parser.cc"
    break;

  case 318: // $@54: %empty
#line 1273 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2322 "dhcp4_parser.cc"
    break;

  case 319: // subnet4_list: "subnet4" $@54 ":" "[" subnet4_list_content "]"
#line 1279 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2331 "dhcp4_parser.cc"
    break;

  case 324: // $@55: %empty
#line 1299 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2341 "dhcp4_parser.cc"
    break;

  case 325: // subnet4: "{" $@55 subnet4_params "}"
#line 1303 "dhcp4_parser.yy"
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
#line 2367 "dhcp4_parser.cc"
    break;

  case 326: // $@56: %empty
#line 1325 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2377 "dhcp4_parser.cc"
    break;

  case 327: // sub_subnet4: "{" $@56 subnet4_params "}"
#line 1329 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2387 "dhcp4_parser.cc"
    break;

  case 371: // $@57: %empty
#line 1384 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2396 "dhcp4_parser.cc"
    break;

  case 372: // subnet: "subnet" $@57 ":" "constant string"
#line 1387 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 373: // $@58: %empty
#line 1393 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2415 "dhcp4_parser.cc"
    break;

  case 374: // subnet_4o6_interface: "4o6-interface" $@58 ":" "constant string"
#line 1396 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 375: // $@59: %empty
#line 1402 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2434 "dhcp4_parser.cc"
    break;

  case 376: // subnet_4o6_interface_id: "4o6-interface-id" $@59 ":" "constant string"
#line 1405 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2444 "dhcp4_parser.cc"
    break;

  case 377: // $@60: %empty
#line 1411 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2453 "dhcp4_parser.cc"
    break;

  case 378: // subnet_4o6_subnet: "4o6-subnet" $@60 ":" "constant string"
#line 1414 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2463 "dhcp4_parser.cc"
    break;

  case 379: // $@61: %empty
#line 1420 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2472 "dhcp4_parser.cc"
    break;

  case 380: // interface: "interface" $@61 ":" "constant string"
#line 1423 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 381: // $@62: %empty
#line 1429 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 382: // client_class: "client-class" $@62 ":" "constant string"
#line 1432 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 383: // $@63: %empty
#line 1438 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2513 "dhcp4_parser.cc"
    break;

  case 384: // require_client_classes: "require-client-classes" $@63 ":" list_strings
#line 1444 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2522 "dhcp4_parser.cc"
    break;

  case 385: // $@64: %empty
#line 1449 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2531 "dhcp4_parser.cc"
    break;

  case 386: // reservation_mode: "reservation-mode" $@64 ":" hr_mode
#line 1452 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2540 "dhcp4_parser.cc"
    break;

  case 387: // hr_mode: "disabled"
#line 1457 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2546 "dhcp4_parser.cc"
    break;

  case 388: // hr_mode: "out-of-pool"
#line 1458 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2552 "dhcp4_parser.cc"
    break;

  case 389: // hr_mode: "global"
#line 1459 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2558 "dhcp4_parser.cc"
    break;

  case 390: // hr_mode: "all"
#line 1460 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2564 "dhcp4_parser.cc"
    break;

  case 391: // id: "id" ":" "integer"
#line 1463 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2574 "dhcp4_parser.cc"
    break;

  case 392: // $@65: %empty
#line 1471 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2586 "dhcp4_parser.cc"
    break;

  case 393: // shared_networks: "shared-networks" $@65 ":" "[" shared_networks_content "]"
#line 1477 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2595 "dhcp4_parser.cc"
    break;

  case 398: // $@66: %empty
#line 1492 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2605 "dhcp4_parser.cc"
    break;

  case 399: // shared_network: "{" $@66 shared_network_params "}"
#line 1496 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2613 "dhcp4_parser.cc"
    break;

  case 438: // $@67: %empty
#line 1546 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2625 "dhcp4_parser.cc"
    break;

  case 439: // option_def_list: "option-def" $@67 ":" "[" option_def_list_content "]"
#line 1552 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2634 "dhcp4_parser.cc"
    break;

  case 440: // $@68: %empty
#line 1560 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2643 "dhcp4_parser.cc"
    break;

  case 441: // sub_option_def_list: "{" $@68 option_def_list "}"
#line 1563 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2651 "dhcp4_parser.cc"
    break;

  case 446: // $@69: %empty
#line 1579 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2661 "dhcp4_parser.cc"
    break;

  case 447: // option_def_entry: "{" $@69 option_def_params "}"
#line 1583 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 448: // $@70: %empty
#line 1594 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 449: // sub_option_def: "{" $@70 option_def_params "}"
#line 1598 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2695 "dhcp4_parser.cc"
    break;

  case 465: // code: "code" ":" "integer"
#line 1630 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2705 "dhcp4_parser.cc"
    break;

  case 467: // $@71: %empty
#line 1638 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2714 "dhcp4_parser.cc"
    break;

  case 468: // option_def_type: "type" $@71 ":" "constant string"
#line 1641 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2724 "dhcp4_parser.cc"
    break;

  case 469: // $@72: %empty
#line 1647 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2733 "dhcp4_parser.cc"
    break;

  case 470: // option_def_record_types: "record-types" $@72 ":" "constant string"
#line 1650 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2743 "dhcp4_parser.cc"
    break;

  case 471: // $@73: %empty
#line 1656 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2752 "dhcp4_parser.cc"
    break;

  case 472: // space: "space" $@73 ":" "constant string"
#line 1659 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 474: // $@74: %empty
#line 1667 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 475: // option_def_encapsulate: "encapsulate" $@74 ":" "constant string"
#line 1670 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 476: // option_def_array: "array" ":" "boolean"
#line 1676 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2791 "dhcp4_parser.cc"
    break;

  case 477: // $@75: %empty
#line 1686 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2803 "dhcp4_parser.cc"
    break;

  case 478: // option_data_list: "option-data" $@75 ":" "[" option_data_list_content "]"
#line 1692 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2812 "dhcp4_parser.cc"
    break;

  case 483: // $@76: %empty
#line 1711 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2822 "dhcp4_parser.cc"
    break;

  case 484: // option_data_entry: "{" $@76 option_data_params "}"
#line 1715 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2831 "dhcp4_parser.cc"
    break;

  case 485: // $@77: %empty
#line 1723 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2841 "dhcp4_parser.cc"
    break;

  case 486: // sub_option_data: "{" $@77 option_data_params "}"
#line 1727 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2850 "dhcp4_parser.cc"
    break;

  case 501: // $@78: %empty
#line 1760 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2859 "dhcp4_parser.cc"
    break;

  case 502: // option_data_data: "data" $@78 ":" "constant string"
#line 1763 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2869 "dhcp4_parser.cc"
    break;

  case 505: // option_data_csv_format: "csv-format" ":" "boolean"
#line 1773 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2879 "dhcp4_parser.cc"
    break;

  case 506: // option_data_always_send: "always-send" ":" "boolean"
#line 1779 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2889 "dhcp4_parser.cc"
    break;

  case 507: // $@79: %empty
#line 1788 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2901 "dhcp4_parser.cc"
    break;

  case 508: // pools_list: "pools" $@79 ":" "[" pools_list_content "]"
#line 1794 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2910 "dhcp4_parser.cc"
    break;

  case 513: // $@80: %empty
#line 1809 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2920 "dhcp4_parser.cc"
    break;

  case 514: // pool_list_entry: "{" $@80 pool_params "}"
#line 1813 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2930 "dhcp4_parser.cc"
    break;

  case 515: // $@81: %empty
#line 1819 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2940 "dhcp4_parser.cc"
    break;

  case 516: // sub_pool4: "{" $@81 pool_params "}"
#line 1823 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2950 "dhcp4_parser.cc"
    break;

  case 526: // $@82: %empty
#line 1842 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2959 "dhcp4_parser.cc"
    break;

  case 527: // pool_entry: "pool" $@82 ":" "constant string"
#line 1845 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2969 "dhcp4_parser.cc"
    break;

  case 528: // $@83: %empty
#line 1851 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2977 "dhcp4_parser.cc"
    break;

  case 529: // user_context: "user-context" $@83 ":" map_value
#line 1853 "dhcp4_parser.yy"
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
#line 3004 "dhcp4_parser.cc"
    break;

  case 530: // $@84: %empty
#line 1876 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3012 "dhcp4_parser.cc"
    break;

  case 531: // comment: "comment" $@84 ":" "constant string"
#line 1878 "dhcp4_parser.yy"
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
#line 3041 "dhcp4_parser.cc"
    break;

  case 532: // $@85: %empty
#line 1906 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3053 "dhcp4_parser.cc"
    break;

  case 533: // reservations: "reservations" $@85 ":" "[" reservations_list "]"
#line 1912 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3062 "dhcp4_parser.cc"
    break;

  case 538: // $@86: %empty
#line 1925 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 539: // reservation: "{" $@86 reservation_params "}"
#line 1929 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 540: // $@87: %empty
#line 1934 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3091 "dhcp4_parser.cc"
    break;

  case 541: // sub_reservation: "{" $@87 reservation_params "}"
#line 1938 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3100 "dhcp4_parser.cc"
    break;

  case 561: // $@88: %empty
#line 1969 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3109 "dhcp4_parser.cc"
    break;

  case 562: // next_server: "next-server" $@88 ":" "constant string"
#line 1972 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3119 "dhcp4_parser.cc"
    break;

  case 563: // $@89: %empty
#line 1978 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3128 "dhcp4_parser.cc"
    break;

  case 564: // server_hostname: "server-hostname" $@89 ":" "constant string"
#line 1981 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3138 "dhcp4_parser.cc"
    break;

  case 565: // $@90: %empty
#line 1987 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3147 "dhcp4_parser.cc"
    break;

  case 566: // boot_file_name: "boot-file-name" $@90 ":" "constant string"
#line 1990 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3157 "dhcp4_parser.cc"
    break;

  case 567: // $@91: %empty
#line 1996 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3166 "dhcp4_parser.cc"
    break;

  case 568: // ip_address: "ip-address" $@91 ":" "constant string"
#line 1999 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3176 "dhcp4_parser.cc"
    break;

  case 569: // $@92: %empty
#line 2005 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3188 "dhcp4_parser.cc"
    break;

  case 570: // ip_addresses: "ip-addresses" $@92 ":" list_strings
#line 2011 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3197 "dhcp4_parser.cc"
    break;

  case 571: // $@93: %empty
#line 2016 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3206 "dhcp4_parser.cc"
    break;

  case 572: // duid: "duid" $@93 ":" "constant string"
#line 2019 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3216 "dhcp4_parser.cc"
    break;

  case 573: // $@94: %empty
#line 2025 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 574: // hw_address: "hw-address" $@94 ":" "constant string"
#line 2028 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3235 "dhcp4_parser.cc"
    break;

  case 575: // $@95: %empty
#line 2034 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3244 "dhcp4_parser.cc"
    break;

  case 576: // client_id_value: "client-id" $@95 ":" "constant string"
#line 2037 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 577: // $@96: %empty
#line 2043 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3263 "dhcp4_parser.cc"
    break;

  case 578: // circuit_id_value: "circuit-id" $@96 ":" "constant string"
#line 2046 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 579: // $@97: %empty
#line 2052 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3282 "dhcp4_parser.cc"
    break;

  case 580: // flex_id_value: "flex-id" $@97 ":" "constant string"
#line 2055 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3292 "dhcp4_parser.cc"
    break;

  case 581: // $@98: %empty
#line 2061 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3301 "dhcp4_parser.cc"
    break;

  case 582: // hostname: "hostname" $@98 ":" "constant string"
#line 2064 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3311 "dhcp4_parser.cc"
    break;

  case 583: // $@99: %empty
#line 2070 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3323 "dhcp4_parser.cc"
    break;

  case 584: // reservation_client_classes: "client-classes" $@99 ":" list_strings
#line 2076 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 585: // $@100: %empty
#line 2084 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3344 "dhcp4_parser.cc"
    break;

  case 586: // relay: "relay" $@100 ":" "{" relay_map "}"
#line 2090 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3353 "dhcp4_parser.cc"
    break;

  case 589: // $@101: %empty
#line 2102 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3365 "dhcp4_parser.cc"
    break;

  case 590: // client_classes: "client-classes" $@101 ":" "[" client_classes_list "]"
#line 2108 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3374 "dhcp4_parser.cc"
    break;

  case 593: // $@102: %empty
#line 2117 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3384 "dhcp4_parser.cc"
    break;

  case 594: // client_class_entry: "{" $@102 client_class_params "}"
#line 2121 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3394 "dhcp4_parser.cc"
    break;

  case 611: // $@103: %empty
#line 2150 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3403 "dhcp4_parser.cc"
    break;

  case 612: // client_class_test: "test" $@103 ":" "constant string"
#line 2153 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3413 "dhcp4_parser.cc"
    break;

  case 613: // only_if_required: "only-if-required" ":" "boolean"
#line 2159 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3423 "dhcp4_parser.cc"
    break;

  case 614: // dhcp4o6_port: "dhcp4o6-port" ":" "integer"
#line 2167 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3433 "dhcp4_parser.cc"
    break;

  case 615: // $@104: %empty
#line 2175 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3445 "dhcp4_parser.cc"
    break;

  case 616: // control_socket: "control-socket" $@104 ":" "{" control_socket_params "}"
#line 2181 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3454 "dhcp4_parser.cc"
    break;

  case 624: // $@105: %empty
#line 2197 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3463 "dhcp4_parser.cc"
    break;

  case 625: // control_socket_type: "socket-type" $@105 ":" "constant string"
#line 2200 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3473 "dhcp4_parser.cc"
    break;

  case 626: // $@106: %empty
#line 2206 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3482 "dhcp4_parser.cc"
    break;

  case 627: // control_socket_name: "socket-name" $@106 ":" "constant string"
#line 2209 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3492 "dhcp4_parser.cc"
    break;

  case 628: // $@107: %empty
#line 2218 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3504 "dhcp4_parser.cc"
    break;

  case 629: // dhcp_queue_control: "dhcp-queue-control" $@107 ":" "{" queue_control_params "}"
#line 2224 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3515 "dhcp4_parser.cc"
    break;

  case 638: // enable_queue: "enable-queue" ":" "boolean"
#line 2243 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 639: // $@108: %empty
#line 2249 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3534 "dhcp4_parser.cc"
    break;

  case 640: // queue_type: "queue-type" $@108 ":" "constant string"
#line 2252 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3544 "dhcp4_parser.cc"
    break;

  case 641: // capacity: "capacity" ":" "integer"
#line 2258 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 642: // $@109: %empty
#line 2264 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 643: // arbitrary_map_entry: "constant string" $@109 ":" value
#line 2267 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3572 "dhcp4_parser.cc"
    break;

  case 644: // $@110: %empty
#line 2274 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3584 "dhcp4_parser.cc"
    break;

  case 645: // dhcp_ddns: "dhcp-ddns" $@110 ":" "{" dhcp_ddns_params "}"
#line 2280 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3595 "dhcp4_parser.cc"
    break;

  case 646: // $@111: %empty
#line 2287 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3605 "dhcp4_parser.cc"
    break;

  case 647: // sub_dhcp_ddns: "{" $@111 dhcp_ddns_params "}"
#line 2291 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3615 "dhcp4_parser.cc"
    break;

  case 668: // enable_updates: "enable-updates" ":" "boolean"
#line 2321 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3625 "dhcp4_parser.cc"
    break;

  case 669: // $@112: %empty
#line 2327 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3634 "dhcp4_parser.cc"
    break;

  case 670: // server_ip: "server-ip" $@112 ":" "constant string"
#line 2330 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3644 "dhcp4_parser.cc"
    break;

  case 671: // server_port: "server-port" ":" "integer"
#line 2336 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3654 "dhcp4_parser.cc"
    break;

  case 672: // $@113: %empty
#line 2342 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3663 "dhcp4_parser.cc"
    break;

  case 673: // sender_ip: "sender-ip" $@113 ":" "constant string"
#line 2345 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3673 "dhcp4_parser.cc"
    break;

  case 674: // sender_port: "sender-port" ":" "integer"
#line 2351 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 675: // max_queue_size: "max-queue-size" ":" "integer"
#line 2357 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3693 "dhcp4_parser.cc"
    break;

  case 676: // $@114: %empty
#line 2363 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3702 "dhcp4_parser.cc"
    break;

  case 677: // ncr_protocol: "ncr-protocol" $@114 ":" ncr_protocol_value
#line 2366 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3711 "dhcp4_parser.cc"
    break;

  case 678: // ncr_protocol_value: "udp"
#line 2372 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3717 "dhcp4_parser.cc"
    break;

  case 679: // ncr_protocol_value: "tcp"
#line 2373 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3723 "dhcp4_parser.cc"
    break;

  case 680: // $@115: %empty
#line 2376 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 681: // ncr_format: "ncr-format" $@115 ":" "JSON"
#line 2379 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3742 "dhcp4_parser.cc"
    break;

  case 682: // $@116: %empty
#line 2386 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 683: // dep_qualifying_suffix: "qualifying-suffix" $@116 ":" "constant string"
#line 2389 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3761 "dhcp4_parser.cc"
    break;

  case 684: // dep_override_no_update: "override-no-update" ":" "boolean"
#line 2396 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3771 "dhcp4_parser.cc"
    break;

  case 685: // dep_override_client_update: "override-client-update" ":" "boolean"
#line 2403 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3781 "dhcp4_parser.cc"
    break;

  case 686: // $@117: %empty
#line 2410 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3790 "dhcp4_parser.cc"
    break;

  case 687: // dep_replace_client_name: "replace-client-name" $@117 ":" ddns_replace_client_name_value
#line 2413 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3799 "dhcp4_parser.cc"
    break;

  case 688: // $@118: %empty
#line 2419 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3808 "dhcp4_parser.cc"
    break;

  case 689: // dep_generated_prefix: "generated-prefix" $@118 ":" "constant string"
#line 2422 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3818 "dhcp4_parser.cc"
    break;

  case 690: // $@119: %empty
#line 2429 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3827 "dhcp4_parser.cc"
    break;

  case 691: // dep_hostname_char_set: "hostname-char-set" $@119 ":" "constant string"
#line 2432 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3837 "dhcp4_parser.cc"
    break;

  case 692: // $@120: %empty
#line 2439 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3846 "dhcp4_parser.cc"
    break;

  case 693: // dep_hostname_char_replacement: "hostname-char-replacement" $@120 ":" "constant string"
#line 2442 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3856 "dhcp4_parser.cc"
    break;

  case 694: // $@121: %empty
#line 2451 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3868 "dhcp4_parser.cc"
    break;

  case 695: // config_control: "config-control" $@121 ":" "{" config_control_params "}"
#line 2457 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3878 "dhcp4_parser.cc"
    break;

  case 696: // $@122: %empty
#line 2463 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3888 "dhcp4_parser.cc"
    break;

  case 697: // sub_config_control: "{" $@122 config_control_params "}"
#line 2467 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3897 "dhcp4_parser.cc"
    break;

  case 702: // $@123: %empty
#line 2482 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3909 "dhcp4_parser.cc"
    break;

  case 703: // config_databases: "config-databases" $@123 ":" "[" database_list "]"
#line 2488 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3918 "dhcp4_parser.cc"
    break;

  case 704: // config_fetch_wait_time: "config-fetch-wait-time" ":" "integer"
#line 2493 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3928 "dhcp4_parser.cc"
    break;

  case 705: // $@124: %empty
#line 2501 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3940 "dhcp4_parser.cc"
    break;

  case 706: // loggers: "loggers" $@124 ":" "[" loggers_entries "]"
#line 2507 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3949 "dhcp4_parser.cc"
    break;

  case 709: // $@125: %empty
#line 2519 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3959 "dhcp4_parser.cc"
    break;

  case 710: // logger_entry: "{" $@125 logger_params "}"
#line 2523 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3967 "dhcp4_parser.cc"
    break;

  case 720: // debuglevel: "debuglevel" ":" "integer"
#line 2540 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3977 "dhcp4_parser.cc"
    break;

  case 721: // $@126: %empty
#line 2546 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3986 "dhcp4_parser.cc"
    break;

  case 722: // severity: "severity" $@126 ":" "constant string"
#line 2549 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3996 "dhcp4_parser.cc"
    break;

  case 723: // $@127: %empty
#line 2555 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4008 "dhcp4_parser.cc"
    break;

  case 724: // output_options_list: "output_options" $@127 ":" "[" output_options_list_content "]"
#line 2561 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4017 "dhcp4_parser.cc"
    break;

  case 727: // $@128: %empty
#line 2570 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4027 "dhcp4_parser.cc"
    break;

  case 728: // output_entry: "{" $@128 output_params_list "}"
#line 2574 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4035 "dhcp4_parser.cc"
    break;

  case 736: // $@129: %empty
#line 2589 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4044 "dhcp4_parser.cc"
    break;

  case 737: // output: "output" $@129 ":" "constant string"
#line 2592 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4054 "dhcp4_parser.cc"
    break;

  case 738: // flush: "flush" ":" "boolean"
#line 2598 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4064 "dhcp4_parser.cc"
    break;

  case 739: // maxsize: "maxsize" ":" "integer"
#line 2604 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4074 "dhcp4_parser.cc"
    break;

  case 740: // maxver: "maxver" ":" "integer"
#line 2610 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4084 "dhcp4_parser.cc"
    break;

  case 741: // $@130: %empty
#line 2616 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4093 "dhcp4_parser.cc"
    break;

  case 742: // pattern: "pattern" $@130 ":" "constant string"
#line 2619 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4103 "dhcp4_parser.cc"
    break;


#line 4107 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -915;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     555,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,    31,    41,    49,    54,    59,    70,
      72,    78,    95,   108,   111,   121,   145,   161,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,    41,  -156,    27,   115,    68,   235,
     193,   245,   -32,    66,   181,   -82,   564,   123,  -915,   133,
     166,   191,   162,   212,  -915,   210,  -915,  -915,  -915,   222,
     223,   225,  -915,  -915,  -915,  -915,  -915,  -915,   239,   248,
     254,   268,   283,   299,   310,   314,   316,   327,   334,  -915,
     354,   361,   365,   373,   385,  -915,  -915,  -915,   386,   393,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,   394,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     395,  -915,    89,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,   398,  -915,   102,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,   400,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,   119,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   122,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   242,   402,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     380,  -915,  -915,   405,  -915,  -915,  -915,   406,  -915,  -915,
     403,   409,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   410,   412,  -915,  -915,  -915,
    -915,   413,   415,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   129,  -915,  -915,  -915,   416,
    -915,  -915,   419,  -915,   421,   422,  -915,  -915,   424,   433,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,   159,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   435,   200,  -915,  -915,  -915,
    -915,    41,    41,  -915,   224,   436,  -915,   437,   440,   447,
     258,   261,   262,   451,   452,   454,   456,   457,   460,   275,
     276,   277,   282,   288,   287,   289,   291,   294,   296,   297,
     486,   303,   304,   305,   306,   309,   499,   500,   501,   317,
     319,   502,   508,   512,   515,   518,   520,   523,   524,   529,
     530,   531,   532,   333,   533,   534,   535,   536,   537,   538,
     541,  -915,   115,  -915,   542,   543,   544,   357,    68,  -915,
     546,   547,   548,   550,   551,   572,   387,   574,   576,   578,
     235,  -915,   579,   193,  -915,   580,   582,   583,   584,   585,
     586,   587,   588,  -915,   245,  -915,   590,   591,   408,   592,
     595,   596,   411,  -915,    66,   597,   414,   420,  -915,   181,
     598,   601,   203,  -915,   425,   609,   610,   429,   616,   431,
     432,   619,   620,   434,   438,   621,   623,   624,   625,   564,
    -915,   632,   458,   123,  -915,  -915,  -915,   645,   643,   644,
     656,   657,  -915,  -915,  -915,   396,   478,   479,   662,   663,
     670,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,   487,  -915,  -915,  -915,  -915,  -915,   -89,   488,
     491,  -915,  -915,   677,   679,   680,   681,   682,   498,   180,
     683,   686,   687,   689,   688,  -915,   690,   691,   692,   693,
     507,   513,   698,  -915,   699,   132,   140,  -915,  -915,   516,
     517,   539,   702,   556,   559,  -915,   699,   560,   716,  -915,
     561,  -915,   699,   562,   563,   565,   566,   567,   568,   569,
    -915,   570,   571,  -915,   573,   575,   577,  -915,  -915,   589,
    -915,  -915,  -915,   593,   682,  -915,  -915,   594,   599,  -915,
     600,  -915,  -915,    12,   549,  -915,  -915,   -89,   602,   603,
     604,  -915,   719,  -915,  -915,    41,   115,   123,    68,   701,
    -915,  -915,  -915,   519,   519,   720,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   737,   754,   756,   758,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,   257,   760,   761,
     762,   194,    99,   -58,    58,   564,  -915,  -915,   764,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     765,  -915,  -915,  -915,  -915,   246,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,   720,  -915,   202,   211,   213,  -915,
     234,  -915,  -915,  -915,  -915,  -915,  -915,   722,   769,   770,
     771,   772,  -915,  -915,  -915,  -915,   773,   775,   776,   777,
     780,   781,  -915,   236,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   237,  -915,   784,   783,  -915,
    -915,   788,   792,  -915,  -915,   790,   794,  -915,  -915,   793,
     795,  -915,  -915,   796,   797,  -915,  -915,  -915,  -915,  -915,
    -915,    61,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    83,
    -915,  -915,   798,   800,  -915,  -915,   799,   803,  -915,   804,
     805,   806,   807,   808,   809,   243,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   810,   811,   812,  -915,   251,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   338,
    -915,  -915,  -915,   813,  -915,   814,  -915,  -915,  -915,   342,
    -915,  -915,  -915,  -915,  -915,   346,  -915,    90,  -915,   612,
    -915,   801,   816,  -915,  -915,  -915,  -915,   779,   815,  -915,
    -915,  -915,   818,   701,  -915,   819,   820,   821,   822,   630,
     635,   638,   637,   640,   827,   828,   829,   830,   646,   647,
     648,   649,   650,   651,   519,  -915,  -915,   519,  -915,   720,
     235,  -915,   737,    66,  -915,   754,   181,  -915,   756,   581,
    -915,   758,   257,  -915,   446,   760,  -915,   245,  -915,   761,
     -82,  -915,   762,   653,   654,   655,   658,   659,   660,   194,
    -915,   665,   661,   664,    99,  -915,   831,   836,   -58,  -915,
     666,   842,   671,   843,    58,  -915,  -915,    36,   764,  -915,
    -915,   846,   852,   193,  -915,   765,   864,  -915,  -915,   704,
    -915,   358,   708,   709,   721,  -915,  -915,  -915,  -915,  -915,
     725,   728,   735,   736,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,   348,  -915,   349,  -915,   868,  -915,   869,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   372,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     877,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     903,   929,  -915,  -915,  -915,  -915,  -915,   925,  -915,   375,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,   746,   789,  -915,  -915,   802,  -915,    41,  -915,
    -915,   977,  -915,  -915,  -915,  -915,  -915,   376,  -915,  -915,
    -915,  -915,  -915,  -915,   817,   378,  -915,   699,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   581,  -915,   979,   823,  -915,
     446,  -915,  -915,  -915,  -915,  -915,  -915,   981,   824,   982,
      36,  -915,  -915,  -915,  -915,  -915,   832,  -915,  -915,   983,
    -915,   833,  -915,  -915,   980,  -915,  -915,   105,  -915,  -120,
     980,  -915,  -915,   985,   986,   988,  -915,   384,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   989,   825,   826,   834,   990,
    -120,  -915,   838,  -915,  -915,  -915,   839,  -915,  -915,  -915
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    60,     7,   168,     9,   326,    11,   515,    13,
     540,    15,   440,    17,   448,    19,   485,    21,   291,    23,
     646,    25,   696,    27,    45,    39,     0,     0,     0,     0,
       0,   542,     0,   450,   487,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    58,     0,   694,   157,   183,     0,
       0,     0,   561,   563,   565,   181,   190,   192,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   130,
       0,     0,     0,     0,     0,   138,   145,   147,     0,     0,
     318,   438,   477,   392,   528,   530,   385,   256,   589,   532,
     283,   302,     0,   270,   615,   628,   644,   150,   152,   705,
       0,   118,     0,    62,    64,    65,    66,    67,    68,    99,
     100,   101,   102,   103,    69,    97,    86,    87,    88,   107,
     108,   109,   110,   111,   112,   113,   105,   106,   114,   115,
     116,    72,    73,    94,    74,    75,    76,   117,    80,    81,
      70,    98,    71,    78,    79,    92,    93,    95,    89,    90,
      91,    77,    82,    83,    84,    85,    96,   104,   170,   172,
     176,     0,   167,     0,   159,   161,   162,   163,   164,   165,
     166,   373,   375,   377,   507,   371,   379,     0,   383,   381,
     585,   370,   330,   331,   332,   333,   334,   355,   356,   357,
     358,   359,   345,   346,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,     0,   328,   337,   350,   351,   352,
     338,   340,   341,   343,   339,   335,   336,   353,   354,   342,
     347,   348,   349,   344,   526,   525,   521,   522,   520,     0,
     517,   519,   523,   524,   583,   571,   573,   577,   575,   581,
     579,   567,   560,   554,   558,   559,     0,   543,   544,   555,
     556,   557,   551,   546,   552,   548,   549,   550,   553,   547,
       0,   467,   236,     0,   471,   469,   474,     0,   463,   464,
       0,   451,   452,   454,   466,   455,   456,   457,   473,   458,
     459,   460,   461,   462,   501,     0,     0,   499,   500,   503,
     504,     0,   488,   489,   491,   492,   493,   494,   495,   496,
     497,   498,   298,   300,   295,     0,   293,   296,   297,     0,
     682,   669,     0,   672,     0,     0,   676,   680,     0,     0,
     686,   688,   690,   692,   667,   665,   666,     0,   648,   650,
     651,   652,   653,   654,   655,   656,   657,   662,   658,   659,
     660,   661,   663,   664,   702,     0,     0,   698,   700,   701,
      44,     0,     0,    37,     0,     0,    57,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    55,     0,    61,     0,     0,     0,     0,     0,   169,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   327,     0,     0,   516,     0,     0,     0,     0,     0,
       0,     0,     0,   541,     0,   441,     0,     0,     0,     0,
       0,     0,     0,   449,     0,     0,     0,     0,   486,     0,
       0,     0,     0,   292,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     647,     0,     0,     0,   697,    48,    41,     0,     0,     0,
       0,     0,   132,   133,   134,     0,     0,     0,     0,     0,
       0,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,     0,   155,   156,   135,   136,   137,     0,     0,
       0,   149,   154,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   614,     0,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,   180,   160,     0,
       0,     0,     0,     0,     0,   391,     0,     0,     0,   329,
       0,   518,     0,     0,     0,     0,     0,     0,     0,     0,
     545,     0,     0,   465,     0,     0,     0,   476,   453,     0,
     505,   506,   490,     0,     0,   294,   668,     0,     0,   671,
       0,   674,   675,     0,     0,   684,   685,     0,     0,     0,
       0,   649,     0,   704,   699,     0,     0,     0,     0,     0,
     562,   564,   566,     0,     0,   194,   131,   140,   141,   142,
     143,   144,   139,   146,   148,   320,   442,   479,   394,    38,
     529,   531,   387,   388,   389,   390,   386,     0,     0,   534,
     285,     0,     0,     0,     0,     0,   151,   153,     0,    49,
     171,   174,   175,   173,   178,   179,   177,   374,   376,   378,
     509,   372,   380,   384,   382,     0,   527,   584,   572,   574,
     578,   576,   582,   580,   568,   468,   237,   472,   470,   475,
     502,   299,   301,   683,   670,   673,   678,   679,   677,   681,
     687,   689,   691,   693,   194,    42,     0,     0,     0,   188,
       0,   185,   187,   223,   229,   231,   233,     0,     0,     0,
       0,     0,   245,   247,   249,   251,     0,     0,     0,     0,
       0,     0,   222,     0,   200,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   215,   216,   217,   212,   218,
     219,   220,   213,   214,   221,     0,   198,     0,   195,   196,
     324,     0,   321,   322,   446,     0,   443,   444,   483,     0,
     480,   481,   398,     0,   395,   396,   265,   266,   267,   268,
     269,     0,   258,   260,   261,   262,   263,   264,   593,     0,
     591,   538,     0,   535,   536,   289,     0,   286,   287,     0,
       0,     0,     0,     0,     0,     0,   304,   306,   307,   308,
     309,   310,   311,     0,     0,     0,   279,     0,   272,   274,
     275,   276,   277,   278,   624,   626,   623,   621,   622,     0,
     617,   619,   620,     0,   639,     0,   642,   635,   636,     0,
     630,   632,   633,   634,   637,     0,   709,     0,   707,    51,
     513,     0,   510,   511,   569,   587,   588,     0,     0,    59,
     695,   158,     0,     0,   184,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   191,     0,   193,     0,
       0,   319,     0,   450,   439,     0,   487,   478,     0,     0,
     393,     0,     0,   257,   595,     0,   590,   542,   533,     0,
       0,   284,     0,     0,     0,     0,     0,     0,     0,     0,
     303,     0,     0,     0,     0,   271,     0,     0,     0,   616,
       0,     0,     0,     0,     0,   629,   645,     0,     0,   706,
      53,     0,    52,     0,   508,     0,     0,   586,   703,     0,
     186,     0,     0,     0,     0,   235,   238,   239,   240,   241,
       0,     0,     0,     0,   253,   254,   242,   243,   244,   255,
     201,     0,   197,     0,   323,     0,   445,     0,   482,   437,
     417,   418,   419,   405,   406,   422,   423,   424,   425,   426,
     408,   409,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   402,   403,   404,   415,   416,   414,     0,   400,
     407,   420,   421,   410,   411,   412,   413,   397,   259,   611,
       0,   609,   610,   602,   603,   607,   608,   604,   605,   606,
       0,   596,   597,   599,   600,   601,   592,     0,   537,     0,
     288,   312,   313,   314,   315,   316,   317,   305,   280,   281,
     282,   273,     0,     0,   618,   638,     0,   641,     0,   631,
     723,     0,   721,   719,   713,   717,   718,     0,   711,   715,
     716,   714,   708,    50,     0,     0,   512,     0,   189,   225,
     226,   227,   228,   224,   230,   232,   234,   246,   248,   250,
     252,   199,   325,   447,   484,     0,   399,     0,     0,   594,
       0,   539,   290,   625,   627,   640,   643,     0,     0,     0,
       0,   710,    54,   514,   570,   401,     0,   613,   598,     0,
     720,     0,   712,   612,     0,   722,   727,     0,   725,     0,
       0,   724,   736,     0,     0,     0,   741,     0,   729,   731,
     732,   733,   734,   735,   726,     0,     0,     0,     0,     0,
       0,   728,     0,   738,   739,   740,     0,   730,   737,   742
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   -52,  -915,  -520,  -915,   371,
    -915,  -915,  -915,  -915,  -915,  -915,  -575,  -915,  -915,  -915,
     -67,  -915,  -915,  -915,  -915,  -915,  -915,   350,   545,   -40,
     -28,   -24,    -1,     1,    11,    19,    22,    25,    26,  -915,
    -915,  -915,  -915,    29,    30,    32,    37,    40,    43,  -915,
     362,    44,  -915,    45,  -915,    47,    48,  -915,    50,  -915,
      51,  -915,  -915,  -915,  -915,   352,   540,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   109,  -915,  -915,  -915,  -915,  -915,  -915,
     267,  -915,    84,  -915,  -641,    91,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   -63,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    75,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    56,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,    62,  -915,  -915,  -915,
      69,   506,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    63,
    -915,  -915,  -915,  -915,  -915,  -915,  -914,  -915,  -915,  -915,
      96,  -915,  -915,  -915,    93,   553,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -905,  -915,   -65,  -915,    53,  -915,
      55,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    80,  -915,
    -915,  -106,   -46,  -915,  -915,  -915,  -915,  -915,   100,  -915,
    -915,  -915,    97,  -915,   552,  -915,   -42,  -915,  -915,  -915,
    -915,  -915,   -36,  -915,  -915,  -915,  -915,  -915,   -35,  -915,
    -915,  -915,   101,  -915,  -915,  -915,   104,  -915,   554,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
      57,  -915,  -915,  -915,    60,   558,  -915,  -915,   -51,  -915,
     -11,  -915,   -25,  -915,  -915,  -915,    98,  -915,  -915,  -915,
     103,  -915,   557,   -55,  -915,     0,  -915,     7,  -915,   329,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -901,  -915,  -915,
    -915,  -915,  -915,   107,  -915,  -915,  -915,   -95,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,    81,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,    74,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   359,   526,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   401,   527,  -915,  -915,
    -915,  -915,  -915,  -915,    79,  -915,  -915,   -97,  -915,  -915,
    -915,  -915,  -915,  -915,  -111,  -915,  -915,  -129,  -915,  -915,
    -915,  -915,  -915,  -915,  -915
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   670,
      82,    83,    39,    64,    79,    80,   690,   879,   971,   972,
     762,    41,    66,    85,   395,    43,    67,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   420,   156,   157,   158,   159,   160,   161,   162,   426,
     662,   163,   427,   164,   428,   165,   166,   448,   167,   449,
     168,   169,   170,   171,   398,   203,   204,    45,    68,   205,
     454,   206,   455,   693,   207,   456,   696,   208,   172,   406,
     173,   399,   740,   741,   742,   892,   174,   407,   175,   408,
     787,   788,   789,   917,   763,   764,   765,   895,  1113,   766,
     896,   767,   897,   768,   898,   769,   770,   487,   771,   772,
     773,   774,   775,   776,   777,   778,   904,   779,   905,   780,
     906,   781,   907,   782,   783,   784,   176,   438,   811,   812,
     813,   814,   815,   816,   817,   177,   444,   847,   848,   849,
     850,   851,   178,   441,   826,   827,   828,   940,    59,    75,
     345,   346,   347,   500,   348,   501,   179,   442,   835,   836,
     837,   838,   839,   840,   841,   842,   180,   431,   791,   792,
     793,   920,    47,    69,   244,   245,   246,   464,   247,   460,
     248,   461,   249,   462,   250,   465,   251,   468,   252,   467,
     181,   437,   676,   254,   182,   434,   803,   804,   805,   929,
    1038,  1039,   183,   432,    53,    72,   795,   796,   797,   923,
      55,    73,   310,   311,   312,   313,   314,   315,   316,   486,
     317,   490,   318,   489,   319,   320,   491,   321,   184,   433,
     799,   800,   801,   926,    57,    74,   331,   332,   333,   334,
     335,   495,   336,   337,   338,   339,   256,   463,   881,   882,
     883,   973,    49,    70,   269,   270,   271,   472,   185,   435,
     186,   436,   187,   440,   822,   823,   824,   937,    51,    71,
     286,   287,   288,   188,   403,   189,   404,   190,   405,   292,
     482,   886,   976,   293,   476,   294,   477,   295,   479,   296,
     478,   297,   481,   298,   480,   299,   475,   263,   469,   887,
     191,   439,   819,   820,   934,  1060,  1061,  1062,  1063,  1064,
    1127,  1065,   192,   193,   445,   859,   860,   861,   956,   862,
     957,   194,   446,   869,   870,   871,   872,   961,   873,   874,
     963,   195,   447,    61,    76,   367,   368,   369,   370,   506,
     371,   372,   508,   373,   374,   375,   511,   728,   376,   512,
     377,   505,   378,   379,   380,   515,   381,   516,   382,   517,
     383,   518,   196,   397,    63,    77,   386,   387,   388,   521,
     389,   197,   450,   877,   878,   967,  1097,  1098,  1099,  1100,
    1139,  1101,  1137,  1157,  1158,  1159,  1167,  1168,  1169,  1175,
    1170,  1171,  1172,  1173,  1179
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     141,   202,   221,   265,   282,   266,   308,   327,   344,   364,
     309,   328,    78,   785,   260,  1033,   289,   209,   257,   272,
     284,   703,   322,   340,  1034,   365,   300,   707,  1046,   222,
     726,    28,   329,    81,   255,   268,   283,    84,   330,   124,
     125,   223,   342,   343,   259,   224,    29,   669,    30,  1162,
      31,   121,  1163,  1164,  1165,  1166,    40,   210,   258,   273,
     285,    42,   323,   341,   932,   366,    44,   933,   225,   261,
     226,   290,   657,   658,   659,   660,   262,    46,   291,    48,
     227,   854,   855,   198,   199,    50,   935,   200,   228,   936,
     201,   229,   452,   968,   230,   231,   969,   453,   232,   233,
     301,   234,    52,   661,   669,   458,   235,   140,  1160,   236,
     459,  1161,   237,   238,   239,    54,   240,   241,    56,   242,
     243,   302,   470,   267,   253,   473,    86,   471,    58,    87,
     474,   140,   502,   124,   125,   384,   385,   503,    88,   390,
      89,    90,    91,    92,    93,    94,    95,    96,    97,   691,
     692,   302,    60,   303,   304,   124,   125,   305,   306,   307,
     694,   695,   519,   124,   125,   124,   125,   520,    62,   391,
     393,   727,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   392,   124,   125,   121,   122,
     863,   864,   865,   523,  1090,   452,  1091,  1092,   524,   123,
     889,  1033,   124,   125,   523,   394,   458,   126,   396,   890,
    1034,   891,   127,   128,  1046,   140,   400,   401,   129,   402,
      32,    33,    34,    35,   843,   844,   845,   893,   130,   914,
     914,   131,   894,   409,   915,   916,   949,   866,   132,   133,
     483,   950,   410,   134,   954,   140,   135,   140,   411,   955,
     136,    90,    91,    92,    93,    94,   302,   324,   303,   304,
     325,   326,   412,    92,    93,    94,  1001,   122,   124,   125,
     137,   138,   139,   672,   673,   674,   675,   413,   140,   264,
     124,   125,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   218,   414,   140,   219,   112,   113,   114,   115,
     116,   117,   118,   119,   415,   211,   212,   213,   416,   122,
     417,   829,   830,   831,   832,   833,   834,   342,   343,   122,
     214,   418,   124,   125,   215,   216,   217,   126,   419,   525,
     526,   958,   124,   125,   218,   964,   959,   219,   129,   519,
     965,   914,   470,   274,   966,   220,  1121,  1122,   421,   275,
     276,   277,   278,   279,   280,   422,   281,   281,   884,   423,
     140,   806,   807,   808,   809,  1125,   810,   424,   502,  1140,
    1126,   473,   140,  1132,  1141,   141,  1143,  1180,   485,   425,
     429,   202,  1181,  1109,  1110,  1111,  1112,   430,   443,   451,
     137,   138,   457,   221,   466,   484,   265,   209,   266,   488,
     492,   493,   494,   527,   496,   260,   497,   282,   499,   257,
     504,   498,   272,   507,   140,   509,   510,   308,   513,   289,
     222,   309,   327,   284,   140,   255,   328,   514,   268,   522,
     528,   529,   223,   322,   530,   259,   224,   210,   340,   283,
     532,   531,   364,   533,   534,   535,   536,   329,   537,   258,
     538,   539,   273,   330,   540,   541,   542,   543,   365,   225,
     261,   226,   544,   285,    92,    93,    94,   262,   545,   546,
     547,   227,   548,   323,   290,   549,   550,   551,   341,   228,
     552,   291,   229,   553,   554,   230,   231,   555,   556,   232,
     233,   557,   234,   558,   559,   560,   563,   235,   366,   561,
     236,   562,   564,   237,   238,   239,   565,   240,   241,   566,
     242,   243,   567,   575,   568,   253,   267,   569,   570,   121,
     122,   302,  1144,   571,   572,   573,   574,   576,   577,   578,
     579,   580,   581,   124,   125,   582,   584,   585,   586,   587,
     589,   590,   591,   743,   592,   593,  1049,  1050,   744,   745,
     746,   747,   748,   749,   750,   751,   752,   753,   754,   755,
     756,   757,   758,   759,   760,   761,   594,   595,   596,   141,
     597,   202,   598,   600,   602,   650,   603,   604,   605,   606,
     607,   608,   609,   735,   611,   612,   614,   209,   613,   615,
     616,   619,   623,   617,   302,   624,   620,    90,    91,    92,
      93,    94,   621,   627,   628,   846,   856,   626,   364,   629,
     630,   631,   632,   633,   634,   637,   635,   638,   639,   640,
     636,   852,   857,   867,   365,   140,   642,   210,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   643,   645,
     646,   647,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   124,   125,   648,   649,   122,   302,   651,   652,   653,
     654,   853,   858,   868,   366,   655,   656,   663,   124,   125,
     664,   216,   665,   126,   666,   667,   668,   671,   677,    30,
     218,   678,   679,   219,   680,   681,   686,   682,   683,   684,
     685,   220,   687,   688,   689,   697,   698,   700,   140,   729,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   705,   734,   739,   899,   786,   699,   362,
     363,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   790,   701,   137,   138,   702,   704,
     706,   708,   709,   140,   710,   711,   712,   713,   714,   715,
     716,   794,   717,   798,   718,   802,   719,   818,   821,   825,
     140,   876,   880,   900,   901,   902,   903,   908,   720,   909,
     910,   911,   721,   723,   912,   913,   919,   977,   724,   725,
     918,   731,   732,   733,   921,   922,   924,   925,   928,   927,
     931,   970,   930,   939,   938,   941,   942,   974,   943,   944,
     945,   946,   947,   948,   951,   952,   953,   960,   962,   975,
     985,   978,   979,   981,   982,   983,   984,   986,   987,   988,
     989,   990,   991,   992,   993,  1082,   994,   995,   996,   997,
    1083,   999,   998,  1071,  1072,  1073,  1086,  1088,  1074,  1075,
    1076,  1079,  1103,   221,  1080,  1104,   308,  1078,  1085,   327,
     309,  1087,  1009,   328,  1035,   260,  1032,  1051,  1107,   257,
     282,  1052,   322,   344,  1043,   340,  1123,  1124,  1041,  1057,
     222,  1128,   289,  1055,   329,   255,   284,   846,  1053,  1010,
     330,   856,   223,  1108,  1040,   259,   224,  1114,  1115,  1054,
    1093,  1011,   283,   852,  1094,  1012,   265,   857,   266,   258,
    1116,  1129,   323,   867,  1117,   341,  1095,  1118,  1042,   225,
     261,   226,   272,  1056,  1119,  1120,   285,   262,  1013,  1044,
    1014,   227,  1130,  1131,  1058,  1133,  1045,   290,   268,   228,
    1015,  1059,   229,   853,   291,   230,   231,   858,  1016,   232,
     233,  1017,   234,   868,  1018,  1019,  1096,   235,  1020,  1021,
     236,  1022,   273,   237,   238,   239,  1023,   240,   241,  1024,
     242,   243,  1025,  1026,  1027,   253,  1028,  1029,  1134,  1030,
    1031,  1138,  1036,  1146,  1037,  1149,  1151,  1156,  1154,  1176,
    1177,  1135,  1178,  1182,  1186,   722,   736,   583,   588,   730,
     738,   888,   980,  1002,  1070,  1000,  1142,  1048,   625,  1069,
    1081,  1047,  1077,  1003,  1150,  1147,  1184,  1183,  1004,  1145,
    1005,  1153,  1155,   599,  1185,  1006,   267,  1188,  1189,  1008,
    1007,   601,  1106,  1105,   885,  1148,  1136,  1068,  1089,  1084,
    1067,   610,  1066,  1152,   875,   641,   618,  1102,   737,  1174,
     644,  1187,     0,   622,     0,     0,     0,     0,  1009,     0,
    1035,     0,  1032,  1051,     0,     0,     0,  1052,     0,     0,
    1043,     0,     0,  1093,  1041,  1057,     0,  1094,     0,  1055,
       0,     0,     0,     0,  1053,  1010,     0,     0,     0,  1095,
    1040,     0,     0,     0,     0,  1054,     0,  1011,     0,     0,
       0,  1012,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1042,     0,     0,     0,     0,  1056,
       0,     0,     0,     0,  1013,  1044,  1014,     0,     0,  1096,
    1058,     0,  1045,     0,     0,     0,  1015,  1059,     0,     0,
       0,     0,     0,     0,  1016,     0,     0,  1017,     0,     0,
    1018,  1019,     0,     0,  1020,  1021,     0,  1022,     0,     0,
       0,     0,  1023,     0,     0,  1024,     0,     0,  1025,  1026,
    1027,     0,  1028,  1029,     0,  1030,  1031,     0,  1036,     0,
    1037
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   654,    69,   929,    71,    68,    69,    70,
      71,   596,    73,    74,   929,    76,    72,   602,   929,    69,
      18,     0,    74,   189,    69,    70,    71,    10,    74,    97,
      98,    69,   124,   125,    69,    69,     5,   567,     7,   169,
       9,    83,   172,   173,   174,   175,     7,    68,    69,    70,
      71,     7,    73,    74,     3,    76,     7,     6,    69,    69,
      69,    71,   161,   162,   163,   164,    69,     7,    71,     7,
      69,   139,   140,    15,    16,     7,     3,    19,    69,     6,
      22,    69,     3,     3,    69,    69,     6,     8,    69,    69,
      34,    69,     7,   192,   624,     3,    69,   189,     3,    69,
       8,     6,    69,    69,    69,     7,    69,    69,     7,    69,
      69,    85,     3,    70,    69,     3,    11,     8,     7,    14,
       8,   189,     3,    97,    98,    12,    13,     8,    23,     6,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    17,
      18,    85,     7,    87,    88,    97,    98,    91,    92,    93,
      20,    21,     3,    97,    98,    97,    98,     8,     7,     3,
       8,   159,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,     4,    97,    98,    83,    84,
     142,   143,   144,     3,   168,     3,   170,   171,     8,    94,
       8,  1125,    97,    98,     3,     3,     3,   102,     8,     8,
    1125,     8,   107,   108,  1125,   189,     4,     4,   113,     4,
     189,   190,   191,   192,   135,   136,   137,     3,   123,     3,
       3,   126,     8,     4,     8,     8,     3,   189,   133,   134,
       8,     8,     4,   138,     3,   189,   141,   189,     4,     8,
     145,    26,    27,    28,    29,    30,    85,    86,    87,    88,
      89,    90,     4,    28,    29,    30,   917,    84,    97,    98,
     165,   166,   167,   103,   104,   105,   106,     4,   189,    96,
      97,    98,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,   109,     4,   189,   112,    71,    72,    73,    74,
      75,    76,    77,    78,     4,    80,    81,    82,     4,    84,
       4,   127,   128,   129,   130,   131,   132,   124,   125,    84,
      95,     4,    97,    98,    99,   100,   101,   102,     4,   391,
     392,     3,    97,    98,   109,     3,     8,   112,   113,     3,
       8,     3,     3,   108,     8,   120,     8,     8,     4,   114,
     115,   116,   117,   118,   119,     4,   121,   121,   122,     4,
     189,   114,   115,   116,   117,     3,   119,     4,     3,     3,
       8,     3,   189,     8,     8,   452,     8,     3,     8,     4,
       4,   458,     8,    35,    36,    37,    38,     4,     4,     4,
     165,   166,     4,   470,     4,     3,   473,   458,   473,     4,
       4,     8,     3,   189,     4,   470,     4,   484,     3,   470,
       4,     8,   473,     4,   189,     4,     4,   494,     4,   484,
     470,   494,   499,   484,   189,   470,   499,     4,   473,     4,
       4,     4,   470,   494,     4,   470,   470,   458,   499,   484,
     192,     4,   519,   192,   192,     4,     4,   499,     4,   470,
       4,     4,   473,   499,     4,   190,   190,   190,   519,   470,
     470,   470,   190,   484,    28,    29,    30,   470,   190,   192,
     191,   470,   191,   494,   484,   191,   190,   190,   499,   470,
       4,   484,   470,   190,   190,   470,   470,   192,   192,   470,
     470,   192,   470,     4,     4,     4,     4,   470,   519,   192,
     470,   192,     4,   470,   470,   470,     4,   470,   470,     4,
     470,   470,     4,   190,     4,   470,   473,     4,     4,    83,
      84,    85,  1107,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,    97,    98,     4,     4,     4,     4,   192,
       4,     4,     4,    34,     4,     4,   110,   111,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,     4,   190,     4,   646,
       4,   648,     4,     4,     4,   189,     4,     4,     4,     4,
       4,     4,     4,   645,     4,     4,     4,   648,   190,     4,
       4,     4,     4,   192,    85,     4,   192,    26,    27,    28,
      29,    30,   192,     4,     4,   682,   683,   192,   685,   190,
       4,   190,   190,     4,     4,     4,   192,     4,     4,     4,
     192,   682,   683,   684,   685,   189,     4,   648,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,   190,     4,
       7,     7,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    97,    98,     7,     7,    84,    85,   189,   189,     7,
       7,   682,   683,   684,   685,     5,   189,   189,    97,    98,
     189,   100,     5,   102,     5,     5,     5,   189,     5,     7,
     109,     5,     5,   112,     5,     7,   189,     7,     7,     7,
       7,   120,   189,     5,     5,   189,   189,     5,   189,   160,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,     7,     5,    24,     4,     7,   189,   165,
     166,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,     7,   189,   165,   166,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,     7,   189,     7,   189,     7,   189,     7,     7,     7,
     189,     7,     7,     4,     4,     4,     4,     4,   189,     4,
       4,     4,   189,   189,     4,     4,     3,     8,   189,   189,
       6,   189,   189,   189,     6,     3,     6,     3,     3,     6,
       3,   189,     6,     3,     6,     6,     3,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     190,     6,     4,     4,     4,     4,     4,   192,   190,   192,
     190,     4,     4,     4,     4,     4,   190,   190,   190,   190,
       4,   190,   192,   190,   190,   190,     4,     4,   190,   190,
     190,   190,     6,   920,   190,     3,   923,   192,   192,   926,
     923,   190,   929,   926,   929,   920,   929,   934,     4,   920,
     937,   934,   923,   940,   929,   926,     8,     8,   929,   934,
     920,     4,   937,   934,   926,   920,   937,   954,   934,   929,
     926,   958,   920,   189,   929,   920,   920,   189,   189,   934,
     967,   929,   937,   954,   967,   929,   973,   958,   973,   920,
     189,     8,   923,   964,   189,   926,   967,   189,   929,   920,
     920,   920,   973,   934,   189,   189,   937,   920,   929,   929,
     929,   920,     3,     8,   934,   189,   929,   937,   973,   920,
     929,   934,   920,   954,   937,   920,   920,   958,   929,   920,
     920,   929,   920,   964,   929,   929,   967,   920,   929,   929,
     920,   929,   973,   920,   920,   920,   929,   920,   920,   929,
     920,   920,   929,   929,   929,   920,   929,   929,   189,   929,
     929,     4,   929,     4,   929,     4,     4,     7,     5,     4,
       4,   189,     4,     4,     4,   624,   646,   452,   458,   637,
     648,   734,   893,   919,   942,   914,   189,   932,   502,   940,
     954,   931,   949,   920,   190,   192,   190,   192,   922,  1125,
     923,   189,   189,   470,   190,   925,   973,   189,   189,   928,
     926,   473,   975,   973,   705,  1130,  1088,   939,   964,   958,
     937,   484,   935,  1140,   685,   519,   494,   968,   647,  1160,
     523,  1180,    -1,   499,    -1,    -1,    -1,    -1,  1125,    -1,
    1125,    -1,  1125,  1130,    -1,    -1,    -1,  1130,    -1,    -1,
    1125,    -1,    -1,  1140,  1125,  1130,    -1,  1140,    -1,  1130,
      -1,    -1,    -1,    -1,  1130,  1125,    -1,    -1,    -1,  1140,
    1125,    -1,    -1,    -1,    -1,  1130,    -1,  1125,    -1,    -1,
      -1,  1125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1125,    -1,    -1,    -1,    -1,  1130,
      -1,    -1,    -1,    -1,  1125,  1125,  1125,    -1,    -1,  1140,
    1130,    -1,  1125,    -1,    -1,    -1,  1125,  1130,    -1,    -1,
      -1,    -1,    -1,    -1,  1125,    -1,    -1,  1125,    -1,    -1,
    1125,  1125,    -1,    -1,  1125,  1125,    -1,  1125,    -1,    -1,
      -1,    -1,  1125,    -1,    -1,  1125,    -1,    -1,  1125,  1125,
    1125,    -1,  1125,  1125,    -1,  1125,  1125,    -1,  1125,    -1,
    1125
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,     0,     5,
       7,     9,   189,   190,   191,   192,   208,   209,   210,   215,
       7,   224,     7,   228,     7,   270,     7,   375,     7,   455,
       7,   471,     7,   407,     7,   413,     7,   437,     7,   351,
       7,   536,     7,   567,   216,   211,   225,   229,   271,   376,
     456,   472,   408,   414,   438,   352,   537,   568,   208,   217,
     218,   189,   213,   214,    10,   226,    11,    14,    23,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    83,    84,    94,    97,    98,   102,   107,   108,   113,
     123,   126,   133,   134,   138,   141,   145,   165,   166,   167,
     189,   223,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   245,   246,   247,   248,
     249,   250,   251,   254,   256,   258,   259,   261,   263,   264,
     265,   266,   281,   283,   289,   291,   329,   338,   345,   359,
     369,   393,   397,   405,   431,   461,   463,   465,   476,   478,
     480,   503,   515,   516,   524,   534,   565,   574,    15,    16,
      19,    22,   223,   268,   269,   272,   274,   277,   280,   461,
     463,    80,    81,    82,    95,    99,   100,   101,   109,   112,
     120,   223,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   246,   247,   248,   249,   250,   251,   254,   256,
     258,   259,   261,   263,   377,   378,   379,   381,   383,   385,
     387,   389,   391,   393,   396,   431,   449,   461,   463,   465,
     476,   478,   480,   500,    96,   223,   389,   391,   431,   457,
     458,   459,   461,   463,   108,   114,   115,   116,   117,   118,
     119,   121,   223,   431,   461,   463,   473,   474,   475,   476,
     478,   480,   482,   486,   488,   490,   492,   494,   496,   498,
     405,    34,    85,    87,    88,    91,    92,    93,   223,   309,
     415,   416,   417,   418,   419,   420,   421,   423,   425,   427,
     428,   430,   461,   463,    86,    89,    90,   223,   309,   419,
     425,   439,   440,   441,   442,   443,   445,   446,   447,   448,
     461,   463,   124,   125,   223,   353,   354,   355,   357,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   165,   166,   223,   461,   463,   538,   539,   540,
     541,   543,   544,   546,   547,   548,   551,   553,   555,   556,
     557,   559,   561,   563,    12,    13,   569,   570,   571,   573,
       6,     3,     4,     8,     3,   227,     8,   566,   267,   284,
       4,     4,     4,   477,   479,   481,   282,   290,   292,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     244,     4,     4,     4,     4,     4,   252,   255,   257,     4,
       4,   370,   406,   432,   398,   462,   464,   394,   330,   504,
     466,   346,   360,     4,   339,   517,   525,   535,   260,   262,
     575,     4,     3,     8,   273,   275,   278,     4,     3,     8,
     382,   384,   386,   450,   380,   388,     4,   392,   390,   501,
       3,     8,   460,     3,     8,   499,   487,   489,   493,   491,
     497,   495,   483,     8,     3,     8,   422,   310,     4,   426,
     424,   429,     4,     8,     3,   444,     4,     4,     8,     3,
     356,   358,     3,     8,     4,   554,   542,     4,   545,     4,
       4,   549,   552,     4,     4,   558,   560,   562,   564,     3,
       8,   572,     4,     3,     8,   208,   208,   189,     4,     4,
       4,     4,   192,   192,   192,     4,     4,     4,     4,     4,
       4,   190,   190,   190,   190,   190,   192,   191,   191,   191,
     190,   190,     4,   190,   190,   192,   192,   192,     4,     4,
       4,   192,   192,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   190,     4,     4,     4,     4,
       4,     4,     4,   231,     4,     4,     4,   192,   269,     4,
       4,     4,     4,     4,     4,   190,     4,     4,     4,   378,
       4,   458,     4,     4,     4,     4,     4,     4,     4,     4,
     475,     4,     4,   190,     4,     4,     4,   192,   417,     4,
     192,   192,   441,     4,     4,   354,   192,     4,     4,   190,
       4,   190,   190,     4,     4,   192,   192,     4,     4,     4,
       4,   539,     4,   190,   570,     4,     7,     7,     7,     7,
     189,   189,   189,     7,     7,     5,   189,   161,   162,   163,
     164,   192,   253,   189,   189,     5,     5,     5,     5,   210,
     212,   189,   103,   104,   105,   106,   395,     5,     5,     5,
       5,     7,     7,     7,     7,     7,   189,   189,     5,     5,
     219,    17,    18,   276,    20,    21,   279,   189,   189,   189,
       5,   189,   189,   219,   189,     7,   189,   219,   189,   189,
     189,   189,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   189,   212,   189,   189,   189,    18,   159,   550,   160,
     253,   189,   189,   189,     5,   208,   230,   569,   268,    24,
     285,   286,   287,    34,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,   223,   297,   298,   299,   302,   304,   306,   308,
     309,   311,   312,   313,   314,   315,   316,   317,   318,   320,
     322,   324,   326,   327,   328,   297,     7,   293,   294,   295,
       7,   371,   372,   373,     7,   409,   410,   411,     7,   433,
     434,   435,     7,   399,   400,   401,   114,   115,   116,   117,
     119,   331,   332,   333,   334,   335,   336,   337,     7,   505,
     506,     7,   467,   468,   469,     7,   347,   348,   349,   127,
     128,   129,   130,   131,   132,   361,   362,   363,   364,   365,
     366,   367,   368,   135,   136,   137,   223,   340,   341,   342,
     343,   344,   461,   463,   139,   140,   223,   461,   463,   518,
     519,   520,   522,   142,   143,   144,   189,   461,   463,   526,
     527,   528,   529,   531,   532,   538,     7,   576,   577,   220,
       7,   451,   452,   453,   122,   482,   484,   502,   293,     8,
       8,     8,   288,     3,     8,   300,   303,   305,   307,     4,
       4,     4,     4,     4,   319,   321,   323,   325,     4,     4,
       4,     4,     4,     4,     3,     8,     8,   296,     6,     3,
     374,     6,     3,   412,     6,     3,   436,     6,     3,   402,
       6,     3,     3,     6,   507,     3,     6,   470,     6,     3,
     350,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,     4,     4,     4,     3,     8,   521,   523,     3,     8,
       4,   530,     4,   533,     3,     8,     8,   578,     3,     6,
     189,   221,   222,   454,     6,     3,   485,     8,     6,     4,
     286,     4,     4,     4,     4,   190,   192,   190,   192,   190,
       4,     4,     4,     4,   190,   190,   190,   190,   192,   190,
     298,   297,   295,   377,   373,   415,   411,   439,   435,   223,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     246,   247,   248,   249,   250,   251,   254,   256,   258,   259,
     261,   263,   309,   369,   387,   389,   391,   393,   403,   404,
     431,   461,   463,   476,   478,   480,   500,   401,   332,   110,
     111,   223,   309,   405,   431,   461,   463,   476,   478,   480,
     508,   509,   510,   511,   512,   514,   506,   473,   469,   353,
     349,   190,   190,   190,   190,   190,   190,   362,   192,   190,
     190,   341,     4,     4,   519,   192,     4,   190,     4,   527,
     168,   170,   171,   223,   309,   461,   463,   579,   580,   581,
     582,   584,   577,     6,     3,   457,   453,     4,   189,    35,
      36,    37,    38,   301,   189,   189,   189,   189,   189,   189,
     189,     8,     8,     8,     8,     3,     8,   513,     4,     8,
       3,     8,     8,   189,   189,   189,   208,   585,     4,   583,
       3,     8,   189,     8,   219,   404,     4,   192,   510,     4,
     190,     4,   580,   189,     5,   189,     7,   586,   587,   588,
       3,     6,   169,   172,   173,   174,   175,   589,   590,   591,
     593,   594,   595,   596,   587,   592,     4,     4,     4,   597,
       3,     8,     4,   192,   190,   190,     4,   590,   189,   189
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   193,   195,   194,   196,   194,   197,   194,   198,   194,
     199,   194,   200,   194,   201,   194,   202,   194,   203,   194,
     204,   194,   205,   194,   206,   194,   207,   194,   208,   208,
     208,   208,   208,   208,   208,   209,   211,   210,   212,   213,
     213,   214,   214,   216,   215,   217,   217,   218,   218,   220,
     219,   221,   221,   222,   222,   223,   225,   224,   227,   226,
     229,   228,   230,   230,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   231,
     231,   231,   231,   231,   231,   231,   231,   231,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     244,   243,   245,   246,   247,   248,   249,   250,   252,   251,
     253,   253,   253,   253,   253,   255,   254,   257,   256,   258,
     260,   259,   262,   261,   263,   264,   265,   267,   266,   268,
     268,   269,   269,   269,   269,   269,   269,   269,   271,   270,
     273,   272,   275,   274,   276,   276,   278,   277,   279,   279,
     280,   282,   281,   284,   283,   285,   285,   286,   288,   287,
     290,   289,   292,   291,   293,   293,   294,   294,   296,   295,
     297,   297,   298,   298,   298,   298,   298,   298,   298,   298,
     298,   298,   298,   298,   298,   298,   298,   298,   298,   298,
     298,   298,   298,   300,   299,   301,   301,   301,   301,   303,
     302,   305,   304,   307,   306,   308,   310,   309,   311,   312,
     313,   314,   315,   316,   317,   319,   318,   321,   320,   323,
     322,   325,   324,   326,   327,   328,   330,   329,   331,   331,
     332,   332,   332,   332,   332,   333,   334,   335,   336,   337,
     339,   338,   340,   340,   341,   341,   341,   341,   341,   341,
     342,   343,   344,   346,   345,   347,   347,   348,   348,   350,
     349,   352,   351,   353,   353,   353,   354,   354,   356,   355,
     358,   357,   360,   359,   361,   361,   362,   362,   362,   362,
     362,   362,   363,   364,   365,   366,   367,   368,   370,   369,
     371,   371,   372,   372,   374,   373,   376,   375,   377,   377,
     378,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   378,   378,   378,   378,   378,   378,   378,   378,   378,
     378,   380,   379,   382,   381,   384,   383,   386,   385,   388,
     387,   390,   389,   392,   391,   394,   393,   395,   395,   395,
     395,   396,   398,   397,   399,   399,   400,   400,   402,   401,
     403,   403,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   404,   404,   404,   404,   406,   405,
     408,   407,   409,   409,   410,   410,   412,   411,   414,   413,
     415,   415,   416,   416,   417,   417,   417,   417,   417,   417,
     417,   417,   417,   417,   418,   419,   420,   422,   421,   424,
     423,   426,   425,   427,   429,   428,   430,   432,   431,   433,
     433,   434,   434,   436,   435,   438,   437,   439,   439,   440,
     440,   441,   441,   441,   441,   441,   441,   441,   441,   441,
     442,   444,   443,   445,   446,   447,   448,   450,   449,   451,
     451,   452,   452,   454,   453,   456,   455,   457,   457,   458,
     458,   458,   458,   458,   458,   458,   460,   459,   462,   461,
     464,   463,   466,   465,   467,   467,   468,   468,   470,   469,
     472,   471,   473,   473,   474,   474,   475,   475,   475,   475,
     475,   475,   475,   475,   475,   475,   475,   475,   475,   475,
     475,   477,   476,   479,   478,   481,   480,   483,   482,   485,
     484,   487,   486,   489,   488,   491,   490,   493,   492,   495,
     494,   497,   496,   499,   498,   501,   500,   502,   502,   504,
     503,   505,   505,   507,   506,   508,   508,   509,   509,   510,
     510,   510,   510,   510,   510,   510,   510,   510,   510,   510,
     511,   513,   512,   514,   515,   517,   516,   518,   518,   519,
     519,   519,   519,   519,   521,   520,   523,   522,   525,   524,
     526,   526,   527,   527,   527,   527,   527,   527,   528,   530,
     529,   531,   533,   532,   535,   534,   537,   536,   538,   538,
     539,   539,   539,   539,   539,   539,   539,   539,   539,   539,
     539,   539,   539,   539,   539,   539,   539,   539,   540,   542,
     541,   543,   545,   544,   546,   547,   549,   548,   550,   550,
     552,   551,   554,   553,   555,   556,   558,   557,   560,   559,
     562,   561,   564,   563,   566,   565,   568,   567,   569,   569,
     570,   570,   572,   571,   573,   575,   574,   576,   576,   578,
     577,   579,   579,   580,   580,   580,   580,   580,   580,   580,
     581,   583,   582,   585,   584,   586,   586,   588,   587,   589,
     589,   590,   590,   590,   590,   590,   592,   591,   593,   594,
     595,   597,   596
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     3,
       0,     4,     0,     4,     3,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     1,     1,     0,     4,     1,     1,
       3,     0,     6,     0,     6,     1,     3,     1,     0,     4,
       0,     6,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     1,     1,     1,
       1,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     1,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     0,     6,     3,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4
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
  "\"cache-threshold\"", "\"cache-max-age\"",
  "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"store-extended-info\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
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
       0,   280,   280,   280,   281,   281,   282,   282,   283,   283,
     284,   284,   285,   285,   286,   286,   287,   287,   288,   288,
     289,   289,   290,   290,   291,   291,   292,   292,   300,   301,
     302,   303,   304,   305,   306,   309,   314,   314,   325,   328,
     329,   332,   337,   345,   345,   352,   353,   356,   360,   367,
     367,   374,   375,   378,   382,   393,   402,   402,   417,   417,
     434,   434,   443,   444,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   506,
     512,   518,   524,   530,   536,   542,   548,   554,   560,   566,
     572,   572,   581,   587,   593,   599,   605,   611,   617,   617,
     626,   629,   632,   635,   638,   644,   644,   653,   653,   662,
     668,   668,   677,   677,   686,   692,   698,   704,   704,   716,
     717,   720,   721,   722,   723,   724,   725,   726,   729,   729,
     738,   738,   749,   749,   757,   758,   761,   761,   769,   771,
     775,   782,   782,   795,   795,   806,   807,   809,   811,   811,
     830,   830,   843,   843,   854,   855,   858,   859,   862,   862,
     872,   873,   876,   877,   878,   879,   880,   881,   882,   883,
     884,   885,   886,   887,   888,   889,   890,   891,   892,   893,
     894,   895,   896,   899,   899,   907,   908,   909,   910,   913,
     913,   922,   922,   931,   931,   940,   946,   946,   955,   961,
     967,   973,   979,   985,   991,   997,   997,  1006,  1006,  1015,
    1015,  1024,  1024,  1033,  1039,  1045,  1052,  1052,  1063,  1064,
    1067,  1068,  1069,  1070,  1071,  1074,  1079,  1084,  1089,  1094,
    1101,  1101,  1114,  1115,  1118,  1119,  1120,  1121,  1122,  1123,
    1126,  1132,  1138,  1144,  1144,  1155,  1156,  1159,  1160,  1163,
    1163,  1173,  1173,  1183,  1184,  1185,  1188,  1189,  1192,  1192,
    1201,  1201,  1210,  1210,  1222,  1223,  1226,  1227,  1228,  1229,
    1230,  1231,  1234,  1240,  1246,  1252,  1258,  1264,  1273,  1273,
    1287,  1288,  1291,  1292,  1299,  1299,  1325,  1325,  1336,  1337,
    1341,  1342,  1343,  1344,  1345,  1346,  1347,  1348,  1349,  1350,
    1351,  1352,  1353,  1354,  1355,  1356,  1357,  1358,  1359,  1360,
    1361,  1362,  1363,  1364,  1365,  1366,  1367,  1368,  1369,  1370,
    1371,  1372,  1373,  1374,  1375,  1376,  1377,  1378,  1379,  1380,
    1381,  1384,  1384,  1393,  1393,  1402,  1402,  1411,  1411,  1420,
    1420,  1429,  1429,  1438,  1438,  1449,  1449,  1457,  1458,  1459,
    1460,  1463,  1471,  1471,  1483,  1484,  1488,  1489,  1492,  1492,
    1500,  1501,  1504,  1505,  1506,  1507,  1508,  1509,  1510,  1511,
    1512,  1513,  1514,  1515,  1516,  1517,  1518,  1519,  1520,  1521,
    1522,  1523,  1524,  1525,  1526,  1527,  1528,  1529,  1530,  1531,
    1532,  1533,  1534,  1535,  1536,  1537,  1538,  1539,  1546,  1546,
    1560,  1560,  1569,  1570,  1573,  1574,  1579,  1579,  1594,  1594,
    1608,  1609,  1612,  1613,  1616,  1617,  1618,  1619,  1620,  1621,
    1622,  1623,  1624,  1625,  1628,  1630,  1636,  1638,  1638,  1647,
    1647,  1656,  1656,  1665,  1667,  1667,  1676,  1686,  1686,  1699,
    1700,  1705,  1706,  1711,  1711,  1723,  1723,  1735,  1736,  1741,
    1742,  1747,  1748,  1749,  1750,  1751,  1752,  1753,  1754,  1755,
    1758,  1760,  1760,  1769,  1771,  1773,  1779,  1788,  1788,  1801,
    1802,  1805,  1806,  1809,  1809,  1819,  1819,  1829,  1830,  1833,
    1834,  1835,  1836,  1837,  1838,  1839,  1842,  1842,  1851,  1851,
    1876,  1876,  1906,  1906,  1917,  1918,  1921,  1922,  1925,  1925,
    1934,  1934,  1943,  1944,  1947,  1948,  1952,  1953,  1954,  1955,
    1956,  1957,  1958,  1959,  1960,  1961,  1962,  1963,  1964,  1965,
    1966,  1969,  1969,  1978,  1978,  1987,  1987,  1996,  1996,  2005,
    2005,  2016,  2016,  2025,  2025,  2034,  2034,  2043,  2043,  2052,
    2052,  2061,  2061,  2070,  2070,  2084,  2084,  2095,  2096,  2102,
    2102,  2113,  2114,  2117,  2117,  2127,  2128,  2131,  2132,  2135,
    2136,  2137,  2138,  2139,  2140,  2141,  2142,  2143,  2144,  2145,
    2148,  2150,  2150,  2159,  2167,  2175,  2175,  2186,  2187,  2190,
    2191,  2192,  2193,  2194,  2197,  2197,  2206,  2206,  2218,  2218,
    2231,  2232,  2235,  2236,  2237,  2238,  2239,  2240,  2243,  2249,
    2249,  2258,  2264,  2264,  2274,  2274,  2287,  2287,  2297,  2298,
    2301,  2302,  2303,  2304,  2305,  2306,  2307,  2308,  2309,  2310,
    2311,  2312,  2313,  2314,  2315,  2316,  2317,  2318,  2321,  2327,
    2327,  2336,  2342,  2342,  2351,  2357,  2363,  2363,  2372,  2373,
    2376,  2376,  2386,  2386,  2396,  2403,  2410,  2410,  2419,  2419,
    2429,  2429,  2439,  2439,  2451,  2451,  2463,  2463,  2473,  2474,
    2478,  2479,  2482,  2482,  2493,  2501,  2501,  2514,  2515,  2519,
    2519,  2527,  2528,  2531,  2532,  2533,  2534,  2535,  2536,  2537,
    2540,  2546,  2546,  2555,  2555,  2566,  2567,  2570,  2570,  2578,
    2579,  2582,  2583,  2584,  2585,  2586,  2589,  2589,  2598,  2604,
    2610,  2616,  2616
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
#line 5613 "dhcp4_parser.cc"

#line 2625 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
